"""Stage 06 -- finish the composition stage 05 started (app core only).

Stage 05 §7 left an enumerated NOT-DONE list.  Two of its items are pure
composition depth, they emit nothing, and they are what this stage does:

  **D -- module-private declaration demotion** (§7 item 4).  Stage 03 hoisted
  every declaration on whose type a module agreed into a generated
  ``g1_<module>.h``.  Stage 04 then merged most of that module's files into a
  handful of translation units -- so a declaration that needed to be module-wide
  when it had eleven separate users may now have exactly ONE user, and being in
  the module header publishes it to every other translation unit of the module
  for no reason.  D moves such a declaration OUT of the module header and into
  the single unit that uses it, at the exact point where the header was
  included, and DELETES outright a hoisted declaration that no longer has any
  user at all.

  **H -- include hoisting** (§7 item 6).  Stage 05 deliberately deleted repeated
  includes and never MOVED one, so 158 of the 249 merged units still carry an
  ``#include`` after their first block -- 285 directives in total -- because a
  later member legitimately introduced a header no earlier member had.  H moves
  those to the end of the unit's first include block, under a proof.

--------------------------------------------------------------------------
WHY THIS STAGE CAN DECLARE ``byte-identical``
--------------------------------------------------------------------------

Neither rule emits an instruction, and each is checked rather than assumed.

**D.**  A file-scope ``extern`` declaration emits nothing.  Moving one from a
header to the single translation unit that uses it changes the *preprocessed
token stream* of that unit only in where the declaration sits relative to the
OTHER declarations of the same generated header -- and a generated module header
is, by construction, ``#include <stdint.h>``, ``#include <stddef.h>`` and then a
flat list of ``extern`` declarations that do not refer to each other.  File-scope
declarations are order-independent among themselves (C11 6.2.1: file scope
begins at the declarator and runs to the end of the unit; the only ordering
constraint is declare-before-use, and the demoted declaration is inserted
exactly where the header was included, so every use still follows it).  For
every OTHER unit of the module the change is the removal of a declaration it
does not use.

*The one thing that could go wrong is the reference scan being wrong*, and the
answer is that the compiler is the check: if a unit uses a symbol whose
declaration has left, it will not compile, and under R4 a compile failure is
proof the transformer is wrong.  This is a rule that fails loudly.

**H.**  Moving an ``#include`` earlier is a no-op for the code it jumps over iff
that code's meaning does not depend on the macro state the header changes.  Two
conditions are required, both checked:

  1. **no preprocessor directive other than ``#include`` between the unit's
     first include block and the directive's own position.**  This is what makes
     the move well-defined at all -- it guarantees the include is not inside a
     conditional, that no ``#define``/``#undef`` in the intervening text is
     being reordered against it, and that the top block really is where the
     directive is going.  Measured over the 249 merged units: 256 of the 285
     late includes satisfy it; the other 29 are refused and reported.

  2. **no identifier in the intervening code is a macro of the header being
     moved.**  This is the condition that makes it *provable* rather than
     probable.  For a quoted repository header the macro set is computed here,
     transitively through its own quoted includes.  For an angle header the set
     comes from the measured evidence file (``sdk_symbols`` records the macro
     names of the C standard type/limit headers individually), and a header for
     which there is no name-level evidence is REFUSED -- no evidence means no
     hoist, never "probably fine".

Both are conservative in the same direction: a refusal costs a directive, an
error costs an image.  The stage nonetheless declares ``byte-identical`` and
``driver.py size-gate 6`` measures whether that held, because a declaration that
is checked by a build is worth more than one that is argued.

--------------------------------------------------------------------------
WHAT THIS STAGE DOES **NOT** DO
--------------------------------------------------------------------------

Internal linkage (stage 05 §7 item 1) and call-order reordering (item 5) both
change codegen and are therefore NOT in this stage at any setting.  They are
stages 07 and 08, each declared ``size-changing`` with ``oracle_required``, so
that a stage which can move linked size can never be blended into one that
cannot.  That separation is the C7b mechanism used as intended.
"""

from __future__ import annotations

import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import sdk_symbols  # noqa: E402
import stagelib  # noqa: E402
from guard import check_write  # noqa: E402

from transforms import t03_module_structure as t3  # noqa: E402
from transforms import t04_cohesive_tu as t4  # noqa: E402
from transforms import t05_cohesive_composition as t5  # noqa: E402

APP_SRC = "recon/symbolized/app/"

BATCHES = frozenset(("D", "H", "DH", "OFF"))
DEFAULT_BATCH = "DH"

#: a stage 03 generated module header identifies itself; a filename pattern
#: would also match a hand-written repository header (README C6's lesson about
#: name-keyed rules, applied again).
_GENERATED_HEADER_BANNER = "GENERATED by recon/refactor/transforms/t03_module_structure.py"

_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+(?P<spell>[<"][^>"]+[>"])[ \t]*$')
_DIRECTIVE = re.compile(r'^[ \t]*#[ \t]*(?P<kw>[A-Za-z_]\w*)')
_IDENT = re.compile(r'[A-Za-z_]\w*')
_DEFINE = re.compile(r'^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)', re.M)


def is_generated_module_header(rel: str, text: str) -> bool:
    return (rel.startswith(APP_SRC) and rel.endswith(".h")
            and _GENERATED_HEADER_BANNER in text[:2048])


def identifiers(text: str) -> set[str]:
    """Identifiers of the code, with comments AND string literals removed."""
    return set(_IDENT.findall(t4.strip_comments(text, drop_strings=True)))


# ------------------------------------------------------------------ batch D
def demote_declarations(source_root: str, relpaths: list[str],
                        text: dict[str, str]) -> dict:
    """Move each module-header declaration into the one unit that uses it."""
    headers = [r for r in relpaths if is_generated_module_header(r, text[r])]
    ids = {r: identifiers(text[r]) for r in relpaths
           if r.endswith((".c", ".h", ".inc"))}

    stats: collections.Counter = collections.Counter()
    per_header: dict[str, dict] = {}
    demoted_symbols: list[dict] = []
    kept: collections.Counter = collections.Counter()

    for h in headers:
        module_dir = os.path.dirname(h)
        hname = os.path.basename(h)
        blank = t3._blank_comments(text[h])
        lines, blines = text[h].split("\n"), blank.split("\n")

        # symbol -> line index, for every declaration this header publishes
        decl_at: dict[str, int] = {}
        for i, b in enumerate(blines):
            s = b.strip()
            if not (s.startswith("extern") and s.endswith(";")):
                continue
            tail = lines[i][len(b.rstrip()):]
            if not t3._COMMENT_TAIL.match(tail):
                continue          # a line whose tail opens an unclosed comment
            sym = t3._decl_symbol(s)
            if sym:
                decl_at[sym] = i

        drop: set[int] = set()
        move_to: dict[str, list[str]] = {}
        for sym, i in sorted(decl_at.items()):
            users = [r for r, idset in ids.items() if r != h and sym in idset]
            if not users:
                drop.add(i)
                stats["D_declarations_withdrawn_no_user_left"] += 1
                continue
            if len(users) != 1:
                kept["more_than_one_user"] += 1
                continue
            u = users[0]
            if not u.endswith(".c") or os.path.dirname(u) != module_dir:
                kept["single_user_outside_the_module_directory"] += 1
                continue
            if ('#include "%s"' % hname) not in text[u]:
                kept["single_user_does_not_include_the_module_header"] += 1
                continue
            drop.add(i)
            move_to.setdefault(u, []).append(lines[i])
            stats["D_declarations_demoted_into_their_only_user"] += 1
            demoted_symbols.append({"symbol": sym, "from": h, "to": u})

        if not drop:
            continue
        text[h] = "\n".join(l for i, l in enumerate(lines) if i not in drop)
        for u, decls in move_to.items():
            text[u] = _insert_after_include(text[u], hname, decls)
        per_header[h] = {"declarations_seen": len(decl_at),
                         "withdrawn_or_demoted": len(drop)}

    return {"totals": dict(stats), "kept": dict(kept),
            "per_header": dict(sorted(per_header.items())),
            "headers_seen": len(headers),
            "demoted": demoted_symbols}


def _insert_after_include(text: str, hname: str, decls: list[str]) -> str:
    """Put ``decls`` immediately after ``#include "hname"``.

    That position is exactly where the header's own declarations arrived, so
    declare-before-use is preserved for every existing use by construction.
    """
    needle = '#include "%s"' % hname
    blank = t3._blank_comments(text)
    lines, blines = text.split("\n"), blank.split("\n")
    for i, b in enumerate(blines):
        if b.strip() == needle:
            return "\n".join(lines[:i + 1] + decls + lines[i + 1:])
    return text


# ------------------------------------------------------------------ batch H
def header_macro_names(path: str, search_dirs: list[str],
                       _seen: set[str] | None = None) -> set[str] | None:
    """Macro names a QUOTED repository header defines, transitively.

    Returns ``None`` when the closure cannot be computed -- an unresolvable
    quoted include, or an angle include whose macro set this function has no
    evidence for.  ``None`` means "no evidence", and the caller refuses.
    """
    _seen = _seen if _seen is not None else set()
    if path in _seen:
        return set()
    _seen.add(path)
    try:
        with open(path, encoding="utf-8", errors="surrogateescape") as fh:
            body = fh.read()
    except OSError:
        return None
    code = t4.strip_comments(body)
    names = set(_DEFINE.findall(code))
    for m in re.finditer(r'^[ \t]*#[ \t]*include[ \t]+([<"][^>"]+[>"])[ \t]*$',
                         code, re.M):
        spell = m.group(1)
        if spell.startswith("<"):
            sub = angle_macro_names(spell)
        else:
            p = t4.resolve_quoted(path, spell.strip('"'), search_dirs)
            sub = header_macro_names(p, search_dirs, _seen) if p else None
        if sub is None:
            return None
        names |= sub
    return names


def angle_macro_names(spell: str) -> set[str] | None:
    """Macro names of an angle header, from the measured evidence, or None."""
    doc = sdk_symbols.load_macro_detail()
    key = spell.strip("<>")
    if key in doc:
        return set(doc[key])
    return None


def top_include_block_end(blines: list[str]) -> int:
    """Index just past the unit's FIRST include block.

    The block is the leading run of blank lines, comment-only lines and
    ``#include`` directives.  ``blines`` is a comment-BLANKED view, so a
    comment-only line reads as blank and the run is found without parsing
    comments twice.
    """
    i, n = 0, len(blines)
    last_include = -1
    while i < n:
        s = blines[i].strip()
        if not s:
            i += 1
            continue
        if _INCLUDE.match(blines[i]):
            last_include = i
            i += 1
            continue
        break
    return last_include + 1 if last_include >= 0 else 0


def hoist_includes(source_root: str, merged: list[str], text: dict[str, str],
                   search_dirs: list[str]) -> dict:
    stats: collections.Counter = collections.Counter()
    refused: collections.Counter = collections.Counter()
    refused_detail: dict[str, int] = collections.Counter()
    per_file: dict[str, int] = {}

    macro_cache: dict[str, set[str] | None] = {}

    for rel in merged:
        body = text[rel]
        blank = t3._blank_comments(body)
        lines, blines = body.split("\n"), blank.split("\n")
        top = top_include_block_end(blines)
        if top == 0:
            refused["unit_has_no_leading_include_block"] += 1
            continue

        hoisted_idx: list[int] = []
        for i in range(top, len(lines)):
            m = _INCLUDE.match(blines[i])
            if not m:
                continue
            spell = m.group("spell")
            stats["H_late_includes_seen"] += 1

            # (1) no non-include directive between the top block and here
            blocking = set()
            for k in range(top, i):
                d = _DIRECTIVE.match(blines[k])
                if d and d.group("kw") != "include":
                    blocking.add(d.group("kw"))
            if blocking:
                refused["intervening_preprocessor_directive"] += 1
                refused_detail["|".join(sorted(blocking))] += 1
                continue

            # (2) no identifier in the intervening code is a macro of the header
            if spell not in macro_cache:
                if spell.startswith("<"):
                    macro_cache[spell] = angle_macro_names(spell)
                else:
                    p = t4.resolve_quoted(os.path.join(source_root, rel),
                                          spell.strip('"'), search_dirs)
                    macro_cache[spell] = (
                        header_macro_names(p, search_dirs) if p else None)
            macros = macro_cache[spell]
            if macros is None:
                refused["no_macro_evidence_for_this_header"] += 1
                refused_detail["no-evidence:" + spell] += 1
                continue
            jumped = "\n".join(lines[top:i])
            if macros & identifiers(jumped):
                refused["intervening_code_names_a_macro_of_the_header"] += 1
                refused_detail["macro-collision:" + spell] += 1
                continue

            hoisted_idx.append(i)

        if not hoisted_idx:
            continue
        moved = [lines[i] for i in hoisted_idx]
        keep = [l for i, l in enumerate(lines) if i not in set(hoisted_idx)]
        text[rel] = "\n".join(keep[:top] + moved + keep[top:])
        stats["H_includes_hoisted"] += len(moved)
        per_file[rel] = len(moved)

    return {"totals": dict(stats), "refused": dict(refused),
            "refused_detail": dict(sorted(refused_detail.items())),
            "units_changed": len(per_file)}


# --------------------------------------------------------------------- run
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    batch = os.environ.get("G1_STAGE06_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE06_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    # The stage 03 module headers are GENERATED OUTPUTS, not manifest inputs:
    # `driver.materialize` inherits them into the stage tree verbatim and they
    # never appear in `relpaths`.  A stage that edits declarations therefore has
    # to enumerate them itself -- the first version of this transformer did not,
    # and sub-batch D silently demoted NOTHING while reporting success.  They
    # are read here and written back through `check_write` at the end, and they
    # stay out of MANIFEST["files"] so staleness does not hunt for a source that
    # never existed.
    inherited = []
    known = set(relpaths)
    for root, dirs, names in os.walk(source_root):
        dirs[:] = [d for d in dirs if not os.path.islink(os.path.join(root, d))]
        for name in names:
            ap = os.path.join(root, name)
            if os.path.islink(ap):
                continue
            rel = os.path.relpath(ap, source_root).replace(os.sep, "/")
            if rel not in known and rel.endswith((".c", ".h", ".inc")):
                inherited.append(rel)
    inherited.sort()

    src, text = {}, {}
    for rel in list(relpaths) + inherited:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    merged = [r for r in relpaths if t5.is_merged_unit(r, text[r])]
    search_dirs = [os.path.join(source_root, d) for d in (
        "recon/application/app/src", "recon/app/src", "recon/headers",
        "recon/symbols", "recon/wiring")]

    d_stats: dict = {"skipped": True}
    h_stats: dict = {"skipped": True}
    if batch in ("D", "DH"):
        d_stats = demote_declarations(source_root, list(relpaths) + inherited,
                                      text)
    if batch in ("H", "DH"):
        h_stats = hoist_includes(source_root, merged, text, search_dirs)

    changed = 0
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr: dict = {}
        if data != src[rel]:
            changed += 1
            tr = {"content_changed": True}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    generated_rewritten = []
    for rel in inherited:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        if data == src[rel]:
            continue
        out = os.path.join(stage.tree, rel)
        check_write(out, stage.dir)
        with open(out, "wb") as fh:
            fh.write(data)
        generated_rewritten.append(rel)

    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "D_declarations_kept_in_the_module_header": d_stats.get("kept", {}),
        "H_includes_refused": h_stats.get("refused", {}),
        "H_includes_refused_detail": h_stats.get("refused_detail", {}),
        "note": "Both rules emit nothing: a file-scope declaration and an "
                "#include directive are not instructions.  A refusal here costs "
                "a directive; a wrong hoist costs an image, so every refusal is "
                "in the safe direction and every one of them is counted.",
    }
    qp = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qp, stage.dir)
    with open(qp, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    return {
        "report": {
            "sub_batch": batch,
            "files_changed": changed,
            "generated_module_headers_rewritten": len(generated_rewritten),
            "merged_units_seen": len(merged),
            **d_stats.get("totals", {}),
            **h_stats.get("totals", {}),
        },
        "manifest_extra": {
            "transform": "composition depth: module-private declaration "
                         "demotion (D) and include hoisting (H), app core only",
            "sub_batch": batch,
            "declaration_demotion": {k: v for k, v in d_stats.items()
                                     if k != "demoted"},
            "include_hoisting": h_stats,
        },
        "parity_extra": None,
    }
