"""Stage 01 -- literal inlining over the compilable tree.

WHAT THIS DOES
--------------
For a byte-verified ``.rodata`` string object whose EVERY live reference in the
compilable tree resolves to an argument of a proven byte-reading callee, it
performs the full four-part transaction that ``prerefactor_plan.md`` 1.6
requires (three parts) plus the fourth the link requires:

  1. every reference site  ``((unsigned long)&rodata_X) /*=0xVA*/``
                       ->  ``((unsigned long)"...")      /*=0xVA*/``
  2. the emitted object is deleted from ``g1_app_string_rodata.c``
  3. the ``PROVIDE(rodata_X = 0xVA);`` line is deleted from ``g1_app_globals.ld``
  4. the ``extern const unsigned char rodata_X[];`` declaration is deleted from
     ``g1_app_symbols.h``

Doing 1 without 2 GROWS flash (``KEEP(*rodata_*.c.obj(".rodata.rodata_*"))`` in
``g1_verified_rodata_keep.ld`` means ``--gc-sections`` drops nothing).  Doing 2
without 3 silently resurrects the ORIGINAL-IMAGE address at every remaining
reader (``rodata_decode_report.md`` 10).  Doing 3 without 1 is a link error --
which is the point: after this transformation a MISSED reference site cannot be
silent.  The 2026 G6-B3 batch proved that empirically when an ``.inc`` fragment
nobody's scanner enumerated turned into
``undefined reference to 'rodata_9b8fd'``.

WHY THE ACCEPTANCE RULE IS WHAT IT IS
-------------------------------------
Under R7 the bar is observable side-effect equivalence with the shipped image.
Inlining a string changes exactly one observable thing: the POINTER VALUE handed
to the consumer.  The BYTES are identical by construction (they are copied out
of the byte-verified object).  A pointer value is unobservable outside the chip
unless it is compared or stored and later compared -- so the transformation is
safe exactly where the pointer is consumed as bytes and never retained.

The rule is therefore mechanical and conservative:

  * a candidate is applied only if EVERY live reference resolves (through at
    most one level of ``#define`` or local-assignment indirection) to an
    argument position of an ACCEPTED callee;
  * a callee is ACCEPTED if it is a logging entry point whose ABI was read off
    the shipped disassembly (``recon/headers/g1_log.h``), a C library string /
    format function, or a function-like macro DEFINED IN THE SAME FILE whose
    body only calls accepted callees;
  * everything else is QUARANTINED, untransformed, and listed with its reason.

R8 note: this transformation performs no MMIO reordering or coalescing of any
kind.  It substitutes one address-valued expression for another of identical
type (``unsigned long``) in argument position.  It cannot change the number or
order of bus transactions.  The only R8-adjacent risk it carries is the pointer
identity discussed above, which the acceptance rule is designed to exclude.
"""

from __future__ import annotations

import os
import re
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(_HERE))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(_HERE))), "tools"))

import json  # noqa: E402

import stagelib  # noqa: E402
from guard import REPO_ROOT  # noqa: E402

PLAN = os.path.join(REPO_ROOT, "recon", "ownership", "literal_inline_plan.json")

STRING_OBJ_TU = "recon/application/app/src/g1_app_string_rodata.c"
PIN_LD = "recon/symbols/g1_app_globals.ld"
DECL_H = "recon/symbols/g1_app_symbols.h"

#: Callees proven to consume the value as bytes.
#: tier 1 -- variadic logging entry points; ABI read off the shipped prologues
#: in prerefactor_progress.md G7-B2 1.1 and declared once in recon/headers/g1_log.h
LOG_SINKS = {"log_message", "DEBUG_PRINT", "debug_print", "printk"}
#: tier 2 -- C library string / format functions (standard prototypes)
LIBC_STRING = {
    "printf", "sprintf", "snprintf", "snprintk", "vsnprintf", "fprintf",
    "puts", "strcmp", "strncmp", "strcasecmp", "strncasecmp", "strstr",
    "strlen", "strnlen", "strchr", "strrchr", "memcmp",
}
ACCEPTED_BASE = LOG_SINKS | LIBC_STRING

#: Contexts that are never accepted, with the reason recorded per candidate.
REFUSED_CALLEES = {
    # prerefactor_progress.md 3.2: this site passes the assert FORMAT as
    # argument 0, which is not what assert_post_action takes.  Suspicious; the
    # 2026 batch refused it too and it stays refused until read in disassembly.
    "assert_post_action": "callee refused: documented argument-shape suspicion",
}

_TOKEN_PASTE = re.compile(r"\b(U?INT(?:8|16|32|64|MAX|PTR)_C)\s*\($")

_SITE = re.compile(r"\(\(unsigned long\)&(rodata_[0-9a-fA-F]+)\)")
_IDENT_TAIL = re.compile(r"[A-Za-z_][A-Za-z_0-9]*$")
_KEYWORDS = {"if", "while", "for", "switch", "return", "sizeof", "do", "else"}


# --------------------------------------------------------------------------
# lexing helpers -- comments and string bodies are masked so that a provenance
# comment such as /*=0x99cbd*/ or a literal containing "rodata_" is never
# matched, and so that offsets in the masked text index the original text.
# --------------------------------------------------------------------------
def mask(text: str) -> str:
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(" " * (j - i))
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif c in "\"'":
            q = c
            j = i + 1
            while j < n:
                if text[j] == "\\":
                    j += 2
                    continue
                if text[j] == q:
                    j += 1
                    break
                j += 1
            out.append(" " * (j - i))
            i = j
        else:
            out.append(c)
            i += 1
    return "".join(out)


def context_of(masked: str, pos: int):
    """Classify the syntactic position of the token starting at ``pos``.

    Returns ``(kind, detail)`` where kind is one of
    ``call`` / ``define`` / ``assign`` / ``pp`` / ``stmt`` / ``none``.
    """
    ls = masked.rfind("\n", 0, pos) + 1
    nl = masked.find("\n", pos)
    nl = len(masked) if nl < 0 else nl
    line = masked[ls:nl]
    if line.lstrip().startswith("#"):
        m = re.match(r"\s*#\s*define\s+([A-Za-z_][A-Za-z_0-9]*)", line)
        return ("define", m.group(1)) if m else ("pp", line.strip()[:60])
    depth = 0
    i = pos - 1
    while i >= 0:
        c = masked[i]
        if c == ")":
            depth += 1
        elif c == "(":
            if depth == 0:
                head = masked[:i].rstrip()
                if _TOKEN_PASTE.search(head + "("):
                    return ("token_paste", _TOKEN_PASTE.search(head + "(").group(1))
                m = _IDENT_TAIL.search(head)
                if m and m.group(0) not in _KEYWORDS:
                    return ("call", m.group(0))
                # a cast or grouping paren: keep walking outward
            else:
                depth -= 1
        elif c in ";{}" and depth == 0:
            seg = masked[i + 1: pos]
            body = re.sub(r"^\s*(case\b[^:]*:|default\s*:|[A-Za-z_][A-Za-z_0-9]*\s*:)\s*",
                          "", seg)
            m = re.match(r"\s*(?:[A-Za-z_][A-Za-z_0-9 \t\*]*?\s+)?([A-Za-z_][A-Za-z_0-9]*)\s*=(?!=)",
                         body)
            if m:
                return ("assign", m.group(1))
            return ("stmt", seg.strip()[:70])
        i -= 1
    return ("none", "")


def _enclosing_block(masked: str, pos: int):
    depth = 0
    i = pos
    while i >= 0:
        if masked[i] == "}":
            depth += 1
        elif masked[i] == "{":
            if depth == 0:
                break
            depth -= 1
        i -= 1
    start = max(i, 0)
    depth = 0
    j = start
    while j < len(masked):
        if masked[j] == "{":
            depth += 1
        elif masked[j] == "}":
            depth -= 1
            if depth == 0:
                break
        j += 1
    return start, min(j + 1, len(masked))


def resolve_contexts(masked: str, pos: int) -> set:
    """One level of indirection: through a ``#define`` name or a local assignment."""
    kind, detail = context_of(masked, pos)
    if kind == "call":
        return {("call", detail)}
    if kind in ("pp", "token_paste", "stmt", "none"):
        return {(kind, detail)}
    if kind == "define":
        got = set()
        for m in re.finditer(r"\b%s\b" % re.escape(detail), masked):
            ls = masked.rfind("\n", 0, m.start()) + 1
            nl = masked.find("\n", m.start())
            nl = len(masked) if nl < 0 else nl
            if re.match(r"\s*#\s*define\s+%s\b" % re.escape(detail), masked[ls:nl]):
                continue
            k2, d2 = context_of(masked, m.start())
            got.add((k2, d2) if k2 == "call" else ("via_define_" + k2, d2))
        return got or {("define_unused", detail)}
    if kind == "assign":
        lo, hi = _enclosing_block(masked, pos)
        got = set()
        for m in re.finditer(r"\b%s\b" % re.escape(detail), masked):
            if not (lo <= m.start() < hi) or m.start() == pos:
                continue
            k2, d2 = context_of(masked, m.start())
            if k2 == "assign" and d2 == detail:
                continue          # the declaration / a re-assignment
            got.add((k2, d2) if k2 == "call" else ("via_assign_" + k2, d2))
        return got or {("assign_unused", detail)}
    return {(kind, detail)}


def macro_forwards_to_accepted(masked: str, name: str, accepted: set) -> bool:
    """A function-like macro defined in this file whose body only calls accepted callees."""
    m = re.search(r"^\s*#\s*define\s+%s\s*\((.*)$" % re.escape(name), masked, re.M)
    if not m:
        return False
    # gather the (possibly line-continued) macro body
    start = m.start()
    body_lines = []
    for line in masked[start:].split("\n"):
        body_lines.append(line)
        if not line.rstrip().endswith("\\"):
            break
    body = "\n".join(body_lines)
    calls = set(re.findall(r"\b([A-Za-z_][A-Za-z_0-9]*)\s*\(", body))
    calls -= _KEYWORDS | {name}
    calls -= {"unsigned", "int", "long", "char", "void", "const", "u32", "u8", "u16"}
    return bool(calls) and calls <= accepted


# --------------------------------------------------------------------------
def _c_string_literal(data: bytes) -> str:
    """Byte-exact C literal.  Non-ASCII becomes octal; a concatenation break is
    inserted whenever an octal escape is followed by an octal digit so the
    escape cannot absorb it; '?' is escaped so no trigraph can form."""
    out = []
    prev_octal = False
    for b in data:
        ch = chr(b)
        if prev_octal and ch in "01234567":
            out.append('" "')
        piece = None
        if b == 0x22:
            piece = '\\"'
        elif b == 0x5C:
            piece = "\\\\"
        elif b == 0x0A:
            piece = "\\n"
        elif b == 0x0D:
            piece = "\\r"
        elif b == 0x09:
            piece = "\\t"
        elif b == 0x3F:
            piece = "\\?"
        elif 0x20 <= b < 0x7F:
            piece = ch
        if piece is None:
            out.append("\\%03o" % b)
            prev_octal = True
        else:
            out.append(piece)
            prev_octal = False
    return '"' + "".join(out) + '"'


_OBJ_LINE = re.compile(
    r"^/\*\s*0x(?P<va>[0-9a-fA-F]+)\s*\*/\s*const unsigned char (?P<sym>rodata_[0-9a-fA-F]+)"
    r"\[(?P<len>\d+)\]\s*=\s*\{(?P<body>[^}]*)\};\s*$", re.M)


def parse_string_objects(text: str) -> dict:
    out = {}
    for m in _OBJ_LINE.finditer(text):
        data = bytes(int(x, 16) for x in re.findall(r"0x([0-9a-fA-F]{1,2})", m.group("body")))
        out[m.group("sym")] = {"va": int(m.group("va"), 16), "bytes": data,
                               "line": m.group(0), "declared_len": int(m.group("len"))}
    return out


# --------------------------------------------------------------------------
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    src = {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
    text = {rel: data.decode("utf-8", errors="surrogateescape") for rel, data in src.items()}
    masked = {rel: mask(t) for rel, t in text.items()
              if rel.endswith((".c", ".inc", ".h"))}

    with open(PLAN, encoding="utf-8") as fh:
        plan = json.load(fh)

    objects = parse_string_objects(text[STRING_OBJ_TU])
    pin_ld = text[PIN_LD]
    decl_h = text[DECL_H]

    # ---- 1. locate every live reference of every candidate ------------
    live = {}
    for rel, mt in masked.items():
        for m in _SITE.finditer(mt):
            live.setdefault(m.group(1), []).append((rel, m.start(), m.end()))
    # bare-token references outside the canonical ((unsigned long)&X) spelling
    other_spelling = {}
    # The object definition in g1_app_string_rodata.c, the extern declaration in
    # g1_app_symbols.h and the PROVIDE line in g1_app_globals.ld are the three
    # halves of the transaction this transform performs itself; they are not
    # "other spellings" of a reference.
    _TRANSACTION_FILES = {STRING_OBJ_TU, DECL_H, PIN_LD}
    for rel, mt in masked.items():
        if rel in _TRANSACTION_FILES:
            continue
        for m in re.finditer(r"\brodata_[0-9a-fA-F]+\b", mt):
            sym = m.group(0)
            if any(s <= m.start() < e for (r, s, e) in live.get(sym, []) if r == rel):
                continue
            other_spelling.setdefault(sym, []).append(rel)

    # ---- 2. classify -------------------------------------------------
    accepted, quarantined = [], []
    for cand in plan["candidates"]:
        sym = cand.get("pin_symbol")
        if not sym or cand.get("classification") != "inline":
            continue
        sites = live.get(sym)
        if not sites:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": cand["core"],
                                "reason": "no live reference in the compilable tree "
                                          "(already applied, or never compiled)"})
            continue
        if cand["core"] != "app":
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": cand["core"],
                                "sites": len(sites),
                                "reason": "net core is frozen: no net rodata object is wired "
                                          "into recon/application/net/CMakeLists.txt, so the "
                                          "withdraw half of the transaction does not exist and "
                                          "inlining would be pure growth on ~1.7 kB of real "
                                          "headroom"})
            continue
        obj = objects.get(sym)
        if obj is None:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites),
                                "reason": "no emitted object in g1_app_string_rodata.c -- "
                                          "nothing to withdraw, so inlining would grow flash"})
            continue
        pin = re.search(r"^PROVIDE\(%s\s*=\s*(0x[0-9a-fA-F]+)\);\s*$" % sym, pin_ld, re.M)
        if pin is None:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites),
                                "reason": "no numeric PROVIDE pin to retire"})
            continue
        decl = re.search(r"^extern const unsigned char %s\[\];.*$" % sym, decl_h, re.M)
        if decl is None:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites),
                                "reason": "no extern declaration in g1_app_symbols.h"})
            continue
        if sym in other_spelling:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites),
                                "reason": "referenced outside the canonical "
                                          "((unsigned long)&SYM) spelling in %s -- a rewrite "
                                          "anchored on that spelling would leave a dangling "
                                          "reference" % sorted(set(other_spelling[sym]))[:3]})
            continue
        # -- byte evidence, re-derived, never trusted from the plan --
        data = obj["bytes"]
        ev = _byte_evidence(obj)
        if ev is not None:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites), "reason": ev})
            continue
        # -- consumer evidence --
        ctxs, bad = set(), []
        for rel, s, _e in sites:
            mt = masked[rel]
            for kind, detail in resolve_contexts(mt, s):
                ctxs.add((kind, detail))
                if kind != "call":
                    bad.append("%s:%s" % (kind, detail))
                elif detail in REFUSED_CALLEES:
                    bad.append(REFUSED_CALLEES[detail])
                elif detail not in ACCEPTED_BASE:
                    if macro_forwards_to_accepted(mt, detail, ACCEPTED_BASE | {detail}):
                        continue
                    bad.append("callee not proven to read the value as bytes: %s" % detail)
        if bad:
            quarantined.append({"symbol": sym, "batch": cand["batch"], "core": "app",
                                "sites": len(sites),
                                "reason": "unproven consumer context",
                                "detail": sorted(set(bad))[:6]})
            continue
        accepted.append({"symbol": sym, "batch": cand["batch"], "va": obj["va"],
                         "bytes": len(data), "sites": len(sites),
                         "literal": _c_string_literal(data[:-1]),
                         "consumers": sorted({d for k, d in ctxs if k == "call"})})

    # ---- 3. apply ----------------------------------------------------
    acc_syms = {a["symbol"]: a for a in accepted}
    per_file = {}
    for sym, a in acc_syms.items():
        for rel, s, e in live[sym]:
            per_file.setdefault(rel, []).append((s, e, sym))
    for rel, edits in per_file.items():
        t = text[rel]
        for s, e, sym in sorted(edits, reverse=True):
            t = t[:s] + '((unsigned long)%s)' % acc_syms[sym]["literal"] + t[e:]
        # annotate the per-file provenance header so every literal stays traceable
        for sym in {sy for _, _, sy in edits}:
            t = re.sub(r"^(\s\*\s+%s\s+@ 0x[0-9a-fA-F]+)\s*$" % sym,
                       r"\1   [INLINED -- refactor stage 01]", t, flags=re.M)
        text[rel] = t

    withdrawn_bytes = 0
    t = text[STRING_OBJ_TU]
    for sym, a in acc_syms.items():
        t = t.replace(objects[sym]["line"] + "\n", "")
        withdrawn_bytes += len(objects[sym]["bytes"])
    text[STRING_OBJ_TU] = t

    t = text[PIN_LD]
    for sym in acc_syms:
        t = re.sub(r"^PROVIDE\(%s\s*=\s*0x[0-9a-fA-F]+\);\n" % sym, "", t, flags=re.M)
    text[PIN_LD] = t

    t = text[DECL_H]
    for sym in acc_syms:
        t = re.sub(r"^extern const unsigned char %s\[\];.*\n" % sym, "", t, flags=re.M)
    text[DECL_H] = t

    # ---- 4. emit -----------------------------------------------------
    touched = 0
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        changed = data != src[rel]
        touched += 1 if changed else 0
        tr = {}
        if changed:
            if rel in per_file:
                tr["literal_inline_sites"] = len(per_file[rel])
                tr["symbols"] = sorted({sy for _, _, sy in per_file[rel]})
            if rel == STRING_OBJ_TU:
                tr["rodata_objects_withdrawn"] = len(acc_syms)
                tr["object_bytes_withdrawn"] = withdrawn_bytes
            if rel == PIN_LD:
                tr["provide_pins_retired"] = len(acc_syms)
            if rel == DECL_H:
                tr["extern_declarations_removed"] = len(acc_syms)
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    qpath = os.path.join(stage.dir, "QUARANTINE.json")
    with open(qpath, "w", encoding="utf-8") as fh:
        json.dump({"schema": "g1.refactor.quarantine/1",
                   "stage": stage.number,
                   "note": "Sites that are NOT automatable under the acceptance rule of "
                           "t01_literal_inline.py.  They are left UNTRANSFORMED.  None of "
                           "them was hand-edited.",
                   "count": len(quarantined),
                   "entries": quarantined}, fh, indent=1)
        fh.write("\n")

    return {
        "report": {
            "candidates_accepted": len(accepted),
            "candidates_quarantined": len(quarantined),
            "sites_inlined": sum(len(v) for v in per_file.values()),
            "files_rewritten": len(per_file),
            "files_changed_total": touched,
            "rodata_objects_withdrawn": len(acc_syms),
            "object_bytes_withdrawn": withdrawn_bytes,
            "provide_pins_retired": len(acc_syms),
            "extern_declarations_removed": len(acc_syms),
        },
        "manifest_extra": {
            "transform": "literal_inline",
            "accepted_candidates": accepted,
            "quarantine_file": "QUARANTINE.json",
        },
    }


def _byte_evidence(obj) -> str | None:
    """Re-derive the byte evidence from the shipped image; return a refusal reason
    or None if the object passes every check."""
    try:
        import extract
    except Exception as exc:                      # pragma: no cover
        return "cannot verify against app_update.bin: %s" % exc
    data = obj["bytes"]
    va = obj["va"]
    if len(data) != obj["declared_len"]:
        return "object body length disagrees with its declared length"
    if len(data) <= 4:
        return ("emitted object is <= 4 B -- the rodata_decode_report.md 10 stub "
                "hazard; extent must be re-derived, never trusted")
    if data[-1] != 0 or 0 in data[:-1]:
        return ("object is not exactly ONE NUL-terminated string (string pool); "
                "withdrawing it would delete bytes other pins address")
    try:
        shipped = extract.read(va, len(data))
        before = extract.read(va - 1, 1)
    except Exception as exc:
        return "shipped-image read failed: %s" % exc
    if bytes(shipped) != data:
        return "emitted object does not match app_update.bin at its VA"
    if bytes(before) != b"\x00":
        return ("byte before the VA is not NUL -- the VA is a string INTERIOR, "
                "so the shipped image shares those bytes with a longer string")
    return None
