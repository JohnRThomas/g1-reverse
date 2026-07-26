"""Stage 02 -- repeated code blocks -> inlinable functions and macros.

WHAT THIS DOES
--------------
Five sub-batches, ordered MOST-MECHANICAL / LEAST-RISKY FIRST so that if
observable side-effect equivalence later breaks we can tell which sub-batch
broke it.  Each sub-batch is independently accounted for in the MANIFEST.

  A  volatile-cast accessor SPELLING normalisation, one C type only
     ``*(volatile int*)`` / ``*(volatile int *)``          -> one spelling
     ``*(volatile unsigned*)``                             -> ``unsigned int``
     Purely textual.  C11 6.7.2 makes ``unsigned`` and ``unsigned int`` the
     SAME type, and whitespace is not part of a type at all, so no access is
     added, removed, widened, re-signed or reordered.  ``int`` is NEVER merged
     with ``unsigned int`` and no typedef is ever resolved -- that is stage 04.

  B  ``expr; __builtin_unreachable();``  ->  ``G1_NORETURN_CALL(expr);``
     (cluster G7-C12).  Token-identical expansion.

  C  ``if (cond) { log_message(A); } else { debug_print(A); }``
       ->  ``G1_LOG_ROUTE(cond, A);``                      (cluster G7-C06)
     APPLIED ONLY where the two argument lists are TEXTUALLY IDENTICAL.  The
     condition is carried VERBATIM as the first macro argument and evaluated
     exactly once, so the plan's "confirm the sense of the comparison per
     site" risk is structurally impossible: the macro cannot invert a test it
     never parses.

  D  ``printk(P); assert_post_action(Q);``
       ->  ``G1_ASSERT_FAIL(P, Q);``                       (cluster G7-C01)
     where P and Q are PARENTHESISED ARGUMENT PACKS pasted verbatim.  This is
     the whole point of the pack form: the plan's dominant hazard for this
     cluster is that "collapsing a 5-argument site into a 4-argument macro
     silently drops a register argument", and a pack macro cannot change an
     arity it never enumerates.  Nine distinct (print-arity, post-arity)
     shapes are live; all nine survive unchanged.

  E  withdraw the per-file ``extern`` declarations of the recovered logging
     entry points in favour of the ONE authoritative header
     ``recon/headers/g1_log.h`` (G7-B2 / cluster G7-C10), which G7-B2 could
     not reach in every file.  A file is only converted when EVERY call site
     in it is compatible with the authoritative prototype
     ``void f(uintptr_t format, ...)`` -- i.e. at least one argument.  Files
     with an incompatible site are QUARANTINED and their sites are written to
     ``DEFECTS.json`` as candidate LATENT RECONSTRUCTION DEFECTS: the shipped
     image loads r0 (and usually r1/r2) before every one of those ``bl``s, so
     a zero-argument reconstruction is dropping arguments the parity harness
     structurally cannot see.

     Setting ``G1_STAGE02_FORCE_LOG_HEADER=1`` withdraws the extern in the
     quarantined files TOO.  That build is EXPECTED TO FAIL; it exists to turn
     the static prediction into a compiler measurement (stage 99).

R8 -- WHICH OF THESE COULD REORDER OR COALESCE A VOLATILE MMIO ACCESS
----------------------------------------------------------------------
* A: none.  Whitespace and a same-type respelling change no access.
* B: none.  ``do { (expr); __builtin_unreachable(); } while (0)`` is the same
  token sequence in the same order.
* C: **the one to watch**, and the reason the macro is shaped the way it is.
  The gate condition very often IS a volatile read
  (``*(volatile int *)&g_log_use_alt_sink == 0``).  The macro parameter
  ``cond`` is expanded EXACTLY ONCE, in the same syntactic position, so the
  read happens exactly once, in the same order, at the same sequence point.
  A macro that mentioned ``cond`` twice would double the bus transaction --
  which is precisely why this one does not.  Sites whose condition contains a
  top-level comma are refused (they would re-split as macro arguments).
* D: none.  Both packs are pasted verbatim; the sequence point between the
  two calls is preserved by the ``;`` inside the macro body.
* E: none.  A declaration emits no instruction.  It can CHANGE codegen where
  the local declaration was wrong -- that is the point of the batch -- but it
  cannot reorder an access.
"""

from __future__ import annotations

import json
import os
import re
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(_HERE))
sys.path.insert(0, _HERE)

import stagelib  # noqa: E402
from guard import REPO_ROOT, check_write  # noqa: E402
from t01_literal_inline import mask  # noqa: E402

HEADER_REL = "recon/headers/g1_dedupe.h"
LOG_HEADER_REL = "recon/headers/g1_log.h"

#: authoritative variadic entry points -- ONE fixed parameter then `...`,
#: read off the shipped prologues (recon/headers/g1_log.h, G7-B2 1.1).
#: A call with ZERO arguments cannot be reconciled with that prototype.
VARIADIC_LOG_ENTRIES = ("debug_print", "log_message", "DEBUG_PRINT", "printk")

FORCE_LOG_HEADER = os.environ.get("G1_STAGE02_FORCE_LOG_HEADER") == "1"

# --------------------------------------------------------------------------
# generic C-ish scanning helpers.  All of them run over the MASKED text
# (comments and string bodies blanked, offsets preserved) produced by
# t01_literal_inline.mask, so a provenance comment or a string body can never
# be matched, while offsets still index the ORIGINAL text.
# --------------------------------------------------------------------------
def _match_paren(s: str, i: int) -> int:
    d = 0
    while i < len(s):
        if s[i] == "(":
            d += 1
        elif s[i] == ")":
            d -= 1
            if d == 0:
                return i + 1
        i += 1
    return -1


def _match_brace(s: str, i: int) -> int:
    d = 0
    while i < len(s):
        if s[i] == "{":
            d += 1
        elif s[i] == "}":
            d -= 1
            if d == 0:
                return i + 1
        i += 1
    return -1


def _has_top_level_comma(inner: str) -> bool:
    d = 0
    for ch in inner:
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == "," and d == 0:
            return True
    return False


def _n_args(inner: str) -> int:
    if inner.strip() == "":
        return 0
    d, n = 0, 1
    for ch in inner:
        if ch in "([{":
            d += 1
        elif ch in ")]}":
            d -= 1
        elif ch == "," and d == 0:
            n += 1
    return n


def _in_statement_position(s: str, pos: int) -> bool:
    """True iff the token at ``pos`` starts a statement inside a block.

    Required before replacing a statement with a ``do { } while (0)`` form:
    an unbraced ``if (x) <site> else Z;`` would otherwise become
    ``if (x) do {...} while (0); else Z;``, which is a hard error.  Also
    refuses any site inside a line-continued macro BODY, where a
    ``do { } while (0)`` would swallow the continuation.
    """
    i = pos - 1
    while i >= 0 and s[i] in " \t\r\n":
        if s[i] == "\n" and i > 0 and s[i - 1] == "\\":
            return False                     # inside a line-continued macro
        i -= 1
    if i < 0:
        return False
    if s[i] not in "{};:":
        return False
    # a `:` only counts when it closed a label / case arm, not `a ? b : c`
    if s[i] == ":":
        ls = s.rfind("\n", 0, i) + 1
        if "?" in s[ls:i]:
            return False
    return True


def _line_is_continued(s: str, pos: int) -> bool:
    """True iff ``pos`` sits on a line that a backslash continues (macro body)."""
    ls = s.rfind("\n", 0, pos) + 1
    nl = s.find("\n", pos)
    nl = len(s) if nl < 0 else nl
    if s[nl - 1: nl] == "\\" or s[max(ls - 2, 0): ls - 1] == "\\":
        return True
    # walk back: is any earlier line in this logical line continued?
    j = ls
    while j > 0 and s[j - 2: j - 1] == "\\":
        j = s.rfind("\n", 0, j - 1) + 1
    return j != ls


# --------------------------------------------------------------------------
# sub-batch A -- volatile-cast accessor spelling normalisation
# --------------------------------------------------------------------------
_VOL = re.compile(r"\*[ \t]*\([ \t]*volatile[ \t]+([A-Za-z_][A-Za-z_0-9 \t]*?)[ \t]*\*[ \t]*\)")

#: same-type respellings ONLY.  C11 6.7.2: `unsigned` and `unsigned int` are
#: the same type; `signed` and `signed int` are the same type.  NOTHING else is
#: merged -- no typedef is resolved, `int` is never folded into `unsigned int`.
_SAME_TYPE = {
    "unsigned": "unsigned int",
    "signed": "signed int",
}


def _canon_type(words: str) -> str:
    t = re.sub(r"[ \t]+", " ", words).strip()
    return _SAME_TYPE.get(t, t)


def batch_a(text: dict, masked: dict, stats: dict) -> None:
    sites = 0
    per_file = {}
    spell_before, spell_after = {}, {}
    for rel in list(text):
        if not rel.endswith((".c", ".inc", ".h")):
            continue
        mt = masked[rel]
        edits = []
        for m in _VOL.finditer(mt):
            old = mt[m.start():m.end()]
            new = "*(volatile %s *)" % _canon_type(m.group(1))
            spell_before[re.sub(r"[ \t]+", " ", old)] = \
                spell_before.get(re.sub(r"[ \t]+", " ", old), 0) + 1
            spell_after[new] = spell_after.get(new, 0) + 1
            if old != new:
                edits.append((m.start(), m.end(), new))
        if not edits:
            continue
        t = text[rel]
        for s, e, new in reversed(edits):
            t = t[:s] + new + t[e:]
        text[rel] = t
        masked[rel] = mask(t)
        per_file[rel] = len(edits)
        sites += len(edits)
    stats["A_volatile_spelling"] = {
        "sites_rewritten": sites,
        "files": len(per_file),
        "distinct_spellings_before": len(spell_before),
        "distinct_spellings_after": len(spell_after),
        "total_accessor_sites_seen": sum(spell_before.values()),
        "per_file": per_file,
    }


# --------------------------------------------------------------------------
# sub-batch B -- G1_NORETURN_CALL
# --------------------------------------------------------------------------
_UNREACH = re.compile(r"__builtin_unreachable[ \t]*\([ \t]*\)[ \t]*;")


def batch_b(text: dict, masked: dict, stats: dict) -> None:
    sites, per_file, refused = 0, {}, []
    for rel in list(text):
        if not rel.endswith((".c", ".inc", ".h")):
            continue
        mt = masked[rel]
        edits = []
        for m in _UNREACH.finditer(mt):
            if _line_is_continued(mt, m.start()):
                refused.append({"file": rel, "reason": "inside a line-continued macro body"})
                continue
            # walk back over whitespace to the `;` that ends the previous stmt
            i = m.start() - 1
            while i >= 0 and mt[i] in " \t\r\n":
                i -= 1
            if i < 0 or mt[i] != ";":
                refused.append({"file": rel, "reason": "no adjacent preceding statement"})
                continue
            semi = i
            # the previous statement must be a single call expression
            j = semi - 1
            while j >= 0 and mt[j] in " \t\r\n":
                j -= 1
            if j < 0 or mt[j] != ")":
                refused.append({"file": rel,
                                "reason": "preceding statement is not a call expression"})
                continue
            # find the matching '(' of that call
            d, k = 0, j
            while k >= 0:
                if mt[k] == ")":
                    d += 1
                elif mt[k] == "(":
                    d -= 1
                    if d == 0:
                        break
                k -= 1
            if k < 0:
                continue
            head = mt[:k].rstrip()
            hm = re.search(r"[A-Za-z_][A-Za-z_0-9]*$", head)
            if not hm:
                refused.append({"file": rel, "reason": "call head is not a plain identifier"})
                continue
            start = len(head) - len(hm.group(0))
            if not _in_statement_position(mt, start):
                refused.append({"file": rel, "reason": "not in statement position"})
                continue
            if _line_is_continued(mt, start):
                refused.append({"file": rel, "reason": "inside a line-continued macro body"})
                continue
            call = text[rel][start:semi]
            edits.append((start, m.end(), "G1_NORETURN_CALL(%s);" % call.strip()))
        if not edits:
            continue
        t = text[rel]
        for s, e, new in reversed(edits):
            t = t[:s] + new + t[e:]
        text[rel] = t
        masked[rel] = mask(t)
        per_file[rel] = len(edits)
        sites += len(edits)
    stats["B_noreturn_call"] = {"sites_rewritten": sites, "files": len(per_file),
                                "refused": refused, "per_file": per_file}


# --------------------------------------------------------------------------
# sub-batch C -- G1_LOG_ROUTE
# --------------------------------------------------------------------------
_IF = re.compile(r"\bif[ \t\r\n]*\(")
_LOG_A = ("log_message", "DEBUG_PRINT")
_ONE_CALL = re.compile(r"\s*([A-Za-z_][A-Za-z_0-9]*)\s*\((.*)\)\s*;\s*", re.S)


def batch_c(text: dict, masked: dict, stats: dict, defects: list) -> None:
    sites, per_file, refused = 0, {}, {}
    seen = 0
    for rel in list(text):
        if not rel.endswith((".c", ".inc", ".h")):
            continue
        mt = masked[rel]
        raw = text[rel]
        edits = []
        for m in _IF.finditer(mt):
            po = m.end() - 1
            pe = _match_paren(mt, po)
            if pe < 0:
                continue
            j = pe
            while j < len(mt) and mt[j].isspace():
                j += 1
            if j >= len(mt) or mt[j] != "{":
                continue
            be = _match_brace(mt, j)
            if be < 0:
                continue
            k = be
            while k < len(mt) and mt[k].isspace():
                k += 1
            if mt[k:k + 4] != "else":
                continue
            k2 = k + 4
            while k2 < len(mt) and mt[k2].isspace():
                k2 += 1
            if k2 >= len(mt) or mt[k2] != "{":
                continue
            be2 = _match_brace(mt, k2)
            if be2 < 0:
                continue
            A = _ONE_CALL.fullmatch(mt[j + 1:be - 1])
            B = _ONE_CALL.fullmatch(mt[k2 + 1:be2 - 1])
            if not (A and B):
                continue
            if A.group(1) not in _LOG_A or B.group(1) != "debug_print":
                continue
            seen += 1
            a_args = raw[j + 1 + A.start(2): j + 1 + A.end(2)]
            b_args = raw[k2 + 1 + B.start(2): k2 + 1 + B.end(2)]
            na, nb = _n_args(A.group(2)), _n_args(B.group(2))
            if re.sub(r"\s+", "", a_args) != re.sub(r"\s+", "", b_args):
                # THE HARVEST: the two branches of one gate disagree.
                kind = ("else_branch_dropped_ALL_arguments" if nb == 0 and na > 0
                        else ("argument_count_differs" if na != nb
                              else "same_arity_different_argument_text"))
                defects.append({
                    "class": "log_route_branch_disagreement",
                    "subclass": kind, "file": rel,
                    "log_message_args": na, "debug_print_args": nb,
                    "line": raw.count("\n", 0, m.start()) + 1,
                    "snippet": " ".join(raw[m.start():be2].split())[:260],
                })
                refused[kind] = refused.get(kind, 0) + 1
                continue
            if na == 0:
                refused["empty_argument_list"] = refused.get("empty_argument_list", 0) + 1
                continue
            cond = raw[po + 1: pe - 1]
            if _has_top_level_comma(mt[po + 1: pe - 1]):
                refused["condition_has_top_level_comma"] = \
                    refused.get("condition_has_top_level_comma", 0) + 1
                continue
            if not _in_statement_position(mt, m.start()):
                refused["not_in_statement_position"] = \
                    refused.get("not_in_statement_position", 0) + 1
                continue
            if _line_is_continued(mt, m.start()):
                refused["inside_line_continued_macro"] = \
                    refused.get("inside_line_continued_macro", 0) + 1
                continue
            edits.append((m.start(), be2,
                          "G1_LOG_ROUTE(%s, %s);" % (cond.strip(), a_args.strip())))
        if not edits:
            continue
        t = text[rel]
        for s, e, new in reversed(edits):
            t = t[:s] + new + t[e:]
        text[rel] = t
        masked[rel] = mask(t)
        per_file[rel] = len(edits)
        sites += len(edits)
    stats["C_log_route"] = {"pairs_seen": seen, "sites_rewritten": sites,
                            "files": len(per_file), "refused": refused,
                            "per_file": per_file}


# --------------------------------------------------------------------------
# sub-batch D -- G1_ASSERT_FAIL / G1_NET_ASSERT_FAIL
# --------------------------------------------------------------------------
_PRINT_HALF = re.compile(r"(?<![A-Za-z_0-9])(printk|assert_print)[ \t\r\n]*\(")
_POST_HALF = re.compile(r"assert_post_action[ \t\r\n]*\(")
_MACRO_NAME = {"printk": "G1_ASSERT_FAIL", "assert_print": "G1_NET_ASSERT_FAIL"}


def batch_d(text: dict, masked: dict, stats: dict, defects: list) -> None:
    sites, per_file, refused, shapes = 0, {}, {}, {}
    for rel in list(text):
        if not rel.endswith((".c", ".inc", ".h")):
            continue
        mt = masked[rel]
        raw = text[rel]
        edits = []
        for m in _PRINT_HALF.finditer(mt):
            pe = _match_paren(mt, m.end() - 1)
            if pe < 0:
                continue
            j = pe
            while j < len(mt) and mt[j] in " \t":
                j += 1
            if mt[j:j + 1] != ";":
                continue
            k = j + 1
            while k < len(mt) and mt[k].isspace():
                k += 1
            pm = _POST_HALF.match(mt, k)
            if not pm:
                continue
            pe2 = _match_paren(mt, pm.end() - 1)
            if pe2 < 0:
                continue
            j2 = pe2
            while j2 < len(mt) and mt[j2] in " \t":
                j2 += 1
            if mt[j2:j2 + 1] != ";":
                continue
            if not _in_statement_position(mt, m.start()):
                refused["not_in_statement_position"] = \
                    refused.get("not_in_statement_position", 0) + 1
                continue
            if _line_is_continued(mt, m.start()) or _line_is_continued(mt, k):
                refused["inside_line_continued_macro"] = \
                    refused.get("inside_line_continued_macro", 0) + 1
                continue
            p_args = raw[m.end():pe - 1]
            q_args = raw[pm.end():pe2 - 1]
            np_, nq_ = _n_args(mt[m.end():pe - 1]), _n_args(mt[pm.end():pe2 - 1])
            if np_ == 0:
                # A ZERO-ARGUMENT print half is not a duplication candidate, it
                # is a defect: the shipped __ASSERT expansion always passes the
                # format, the stringified condition, the file and the line.
                # Refusing it here also keeps it visible to sub-batch E, which
                # would otherwise see the call already folded inside a macro.
                refused["print_half_has_zero_arguments"] = \
                    refused.get("print_half_has_zero_arguments", 0) + 1
                defects.append({
                    "class": "zero_argument_assert_expansion",
                    "file": rel, "print_entry_point": m.group(1),
                    "print_args": 0, "post_args": nq_,
                    "line": raw.count("\n", 0, m.start()) + 1,
                    "snippet": " ".join(raw[m.start():j2 + 1].split())[:200],
                    "why": "cluster G7-C01 records the shipped app expansion as "
                           "printk(fmt, #cond, file, line) -- 4 or 5 register "
                           "arguments.  A zero-argument reconstruction of both "
                           "halves has dropped every one of them, and only "
                           "compiles because the file carries its own "
                           "`extern void printk(void);`.",
                })
                continue
            key = "%s(%d)+post(%d)" % (m.group(1), np_, nq_)
            shapes[key] = shapes.get(key, 0) + 1
            edits.append((m.start(), j2 + 1,
                          "%s((%s), (%s));" % (_MACRO_NAME[m.group(1)],
                                               " ".join(p_args.split()),
                                               " ".join(q_args.split()))))
        if not edits:
            continue
        t = text[rel]
        for s, e, new in reversed(edits):
            t = t[:s] + new + t[e:]
        text[rel] = t
        masked[rel] = mask(t)
        per_file[rel] = len(edits)
        sites += len(edits)
    stats["D_assert_fail"] = {"sites_rewritten": sites, "files": len(per_file),
                              "refused": refused, "shapes_preserved": shapes,
                              "per_file": per_file}


# --------------------------------------------------------------------------
# sub-batch E -- withdraw per-file log externs in favour of g1_log.h
# --------------------------------------------------------------------------
_EXTERN_LOG = re.compile(
    r"^[ \t]*extern[ \t][^;\n{]*?\b(%s)\b[ \t]*\([^;{]*\)[^;\n]*;[ \t]*\n"
    % "|".join(VARIADIC_LOG_ENTRIES), re.M)
_CALL_OF = {e: re.compile(r"(?<![A-Za-z_0-9])%s[ \t\r\n]*\(" % e)
            for e in VARIADIC_LOG_ENTRIES}


def batch_e(text: dict, masked: dict, orig_masked: dict, stats: dict,
            defects: list) -> None:
    converted, quarantined, per_file = 0, [], {}
    decls_withdrawn = 0
    zero_arg_total = 0
    for rel in list(text):
        if not rel.endswith((".c", ".inc", ".h")):
            continue
        mt = masked[rel]
        decls = list(_EXTERN_LOG.finditer(mt))
        if not decls:
            continue
        # Every call site in this file must be compatible with `f(fmt, ...)`.
        # The scan runs over the PRE-TRANSFORM text: an earlier sub-batch may
        # have folded a call inside a macro invocation, where this scan would
        # no longer see it.  (Round 1 of this transformer got that wrong and
        # the compiler caught it -- see the report's first-try triage.)
        om = orig_masked[rel]
        odecls = list(_EXTERN_LOG.finditer(om))
        bad = []
        for e, pat in _CALL_OF.items():
            for cm in pat.finditer(om):
                pe = _match_paren(om, cm.end() - 1)
                if pe < 0:
                    continue
                # skip the declarations themselves
                if any(d.start() <= cm.start() < d.end() for d in odecls):
                    continue
                if _n_args(om[cm.end():pe - 1]) == 0:
                    bad.append({"entry_point": e,
                                "line": om.count("\n", 0, cm.start()) + 1})
        if bad:
            zero_arg_total += len(bad)
            quarantined.append({"file": rel, "zero_argument_sites": len(bad),
                                "declarations": len(decls)})
            defects.append({
                "class": "zero_argument_call_to_variadic_log_entry_point",
                "file": rel, "sites": len(bad),
                "detail": bad[:40],
                "why": "recon/headers/g1_log.h is the authoritative declaration "
                       "(one fixed parameter then `...`, read off the shipped "
                       "prologue).  A zero-argument call cannot be reconciled "
                       "with it; the shipped image loads r0 before every one of "
                       "these bl sites.  The local `extern void f(void);` in this "
                       "file is what lets it compile today.",
            })
            if not FORCE_LOG_HEADER:
                continue
        t = text[rel]
        for d in reversed(decls):
            t = t[:d.start()] + t[d.end():]
        decls_withdrawn += len(decls)
        t = _insert_include(t, rel, LOG_HEADER_REL)
        text[rel] = t
        masked[rel] = mask(t)
        per_file[rel] = len(decls)
        converted += 1
    stats["E_log_prototype_convergence"] = {
        "files_converted": converted,
        "declarations_withdrawn": decls_withdrawn,
        "files_quarantined": len(quarantined),
        "zero_argument_sites_found": zero_arg_total,
        "forced": FORCE_LOG_HEADER,
        "quarantined": quarantined,
        "per_file": per_file,
    }


# --------------------------------------------------------------------------
def _insert_include(t: str, rel: str, header_rel: str) -> str:
    inc = os.path.relpath(header_rel, os.path.dirname(rel)).replace(os.sep, "/")
    line = '#include "%s"\n' % inc
    if line in t:
        return t
    # insert after the LAST leading #include, else at the very top
    mt = mask(t)
    last = None
    for m in re.finditer(r"^[ \t]*#[ \t]*include[^\n]*\n", mt, re.M):
        # only the leading include block: stop at the first real statement
        if re.search(r"[A-Za-z_0-9;{}]", re.sub(r"^[ \t]*#[^\n]*\n", "",
                                                mt[:m.start()], flags=re.M)):
            break
        last = m
    if last is not None:
        return t[:last.end()] + line + t[last.end():]
    return line + t


_HEADER_TEXT = '''/*
 * g1_dedupe.h -- the ONE definition of each duplicated code block that
 * refactor stage 02 collapsed.  GENERATED by
 * recon/refactor/transforms/t02_block_dedupe.py.  Do not edit: a stage tree
 * is regenerated, never hand-patched (recon/refactor/README.md C4).
 *
 * Every macro here is a TOKEN-IDENTICAL expansion of the block it replaces.
 * That is the acceptance rule for this stage, and it is what makes the gate a
 * byte-identical `.o` rather than an argument about equivalence.
 *
 * R8 (recon/refactor/README.md C8) -- anything that reorders or coalesces a
 * volatile MMIO access, or changes the number or order of bus transactions,
 * is directly observable from outside the chip.  Two properties below are
 * load-bearing for that and must survive any future edit:
 *
 *   1. G1_LOG_ROUTE expands `cond` EXACTLY ONCE.  In the shipped corpus that
 *      condition is very often a volatile read of the log-sink selector
 *      (`*(volatile int *)&g_log_use_alt_sink == 0`).  Mentioning `cond`
 *      twice would double a real bus transaction.
 *   2. G1_ASSERT_FAIL takes PARENTHESISED ARGUMENT PACKS, not an argument
 *      list.  cluster G7-C01 of recon/ownership/code_dedupe_plan.json records
 *      that the print half and the post half do NOT pair 1:1 -- nine distinct
 *      (print-arity, post-arity) shapes are live in the compilable tree -- and
 *      that "collapsing a 5-argument site into a 4-argument macro silently
 *      drops a register argument", which the Unicorn differential harness is
 *      structurally blind to.  A pack macro cannot change an arity it never
 *      enumerates.
 *
 * Each macro is a statement macro in the `do { } while (0)` form, so it is
 * usable anywhere the block it replaced was usable and still requires its
 * terminating semicolon.
 */
#ifndef G1_DEDUPE_H
#define G1_DEDUPE_H

/* cluster G7-C12 -- `expr; __builtin_unreachable();`
 *
 * recon/net/src/FUN_01013650.c records WHY the tail exists: a test double
 * that returns must not execute the bytes of the following, unrelated
 * function.  The expansion keeps the barrier in the same position. */
#define G1_NORETURN_CALL(...)          \\
    do {                               \\
        (__VA_ARGS__);                 \\
        __builtin_unreachable();       \\
    } while (0)

/* cluster G7-C06 -- the log-sink route.
 *
 *     if (cond) { log_message(A); } else { debug_print(A); }
 *
 * `cond` is carried verbatim and expanded ONCE (see R8 note 1 above); the
 * macro never parses it, so it cannot invert the sense of the comparison --
 * which is the risk the plan flags for this cluster.  `__VA_ARGS__` carries
 * the shared argument list, which the transform applied ONLY where the two
 * branches spell it identically. */
#define G1_LOG_ROUTE(cond, ...)        \\
    do {                               \\
        if (cond) {                    \\
            log_message(__VA_ARGS__);  \\
        } else {                       \\
            debug_print(__VA_ARGS__);  \\
        }                              \\
    } while (0)

/* cluster G7-C01 -- the Zephyr __ASSERT expansion, application core.
 *
 *     printk P; assert_post_action Q;
 *
 * P and Q are PARENTHESISED PACKS pasted verbatim (see R8 note 2 above). */
#define G1_ASSERT_FAIL(print_pack, post_pack)   \\
    do {                                        \\
        printk print_pack;                      \\
        assert_post_action post_pack;           \\
    } while (0)

/* cluster G7-C01 -- the same expansion on the network core, where the print
 * half is `assert_print` rather than `printk`. */
#define G1_NET_ASSERT_FAIL(print_pack, post_pack)   \\
    do {                                            \\
        assert_print print_pack;                    \\
        assert_post_action post_pack;               \\
    } while (0)

#endif /* G1_DEDUPE_H */
'''


# --------------------------------------------------------------------------
def run(stage, source_root: str, relpaths: list[str]) -> dict:
    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")
    masked = {rel: mask(t) for rel, t in text.items()
              if rel.endswith((".c", ".inc", ".h"))}
    orig_masked = dict(masked)

    stats: dict = {}
    defects: list = []

    batch_a(text, masked, stats)
    batch_b(text, masked, stats)
    batch_c(text, masked, stats, defects)
    batch_d(text, masked, stats, defects)
    batch_e(text, masked, orig_masked, stats, defects)

    # every file that now uses a g1_dedupe.h macro must include it
    users = set()
    for key in ("B_noreturn_call", "C_log_route", "D_assert_fail"):
        users |= set(stats[key]["per_file"])
    for rel in sorted(users):
        text[rel] = _insert_include(text[rel], rel, HEADER_REL)
    stats["header_include_sites"] = len(users)

    # ---- emit ---------------------------------------------------------
    touched = 0
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        changed = data != src[rel]
        touched += 1 if changed else 0
        tr = {}
        if changed:
            for key, label in (("A_volatile_spelling", "volatile_spelling_sites"),
                               ("B_noreturn_call", "noreturn_call_sites"),
                               ("C_log_route", "log_route_sites"),
                               ("D_assert_fail", "assert_fail_sites"),
                               ("E_log_prototype_convergence", "log_externs_withdrawn")):
                n = stats[key]["per_file"].get(rel)
                if n:
                    tr[label] = n
            if rel in users:
                tr["includes_g1_dedupe_h"] = True
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    # the generated header is an OUTPUT of the transformer, not an input, so it
    # is written directly into the stage tree and recorded in manifest_extra --
    # putting it in `files` would make staleness look for a source that does
    # not exist.
    hpath = os.path.join(stage.tree, HEADER_REL)
    check_write(hpath, stage.dir)
    os.makedirs(os.path.dirname(hpath), exist_ok=True)
    if os.path.islink(hpath):
        os.unlink(hpath)
    with open(hpath, "w", encoding="utf-8") as fh:
        fh.write(_HEADER_TEXT)

    dpath = os.path.join(stage.dir, "DEFECTS.json")
    check_write(dpath, stage.dir)
    with open(dpath, "w", encoding="utf-8") as fh:
        json.dump({
            "schema": "g1.refactor.defects/1",
            "stage": stage.number,
            "note": "Candidate LATENT RECONSTRUCTION DEFECTS exposed by stage 02. "
                    "These are NOT transformer bugs: they are places where the "
                    "recovered C disagrees with itself about how many arguments "
                    "an entry point takes.  The Unicorn differential harness is "
                    "structurally blind to a dropped register argument (19 "
                    "confirmed instances, see code_dedupe_plan.json hard_rule); "
                    "an authoritative declaration is not.  Each entry needs a "
                    "disassembly-level fix in the CANONICAL tree, which this "
                    "pipeline may never write (R1).",
            "count": len(defects),
            "entries": defects,
        }, fh, indent=1)
        fh.write("\n")

    qpath = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qpath, stage.dir)
    quarantine = {
        "schema": "g1.refactor.quarantine/1",
        "stage": stage.number,
        "note": "Sites NOT automatable under this stage's acceptance rules. "
                "Left UNTRANSFORMED.  None was hand-edited.",
        "C_log_route_refused": stats["C_log_route"]["refused"],
        "D_assert_fail_refused": stats["D_assert_fail"]["refused"],
        "B_noreturn_refused": stats["B_noreturn_call"]["refused"],
        "E_files_quarantined": stats["E_log_prototype_convergence"]["quarantined"],
    }
    with open(qpath, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    report = {
        "A_volatile_spelling_sites": stats["A_volatile_spelling"]["sites_rewritten"],
        "A_files": stats["A_volatile_spelling"]["files"],
        "A_spellings_before_after": [stats["A_volatile_spelling"]["distinct_spellings_before"],
                                     stats["A_volatile_spelling"]["distinct_spellings_after"]],
        "B_noreturn_sites": stats["B_noreturn_call"]["sites_rewritten"],
        "C_log_route_sites": stats["C_log_route"]["sites_rewritten"],
        "C_log_route_pairs_seen": stats["C_log_route"]["pairs_seen"],
        "D_assert_fail_sites": stats["D_assert_fail"]["sites_rewritten"],
        "E_files_converted": stats["E_log_prototype_convergence"]["files_converted"],
        "E_declarations_withdrawn":
            stats["E_log_prototype_convergence"]["declarations_withdrawn"],
        "E_files_quarantined": stats["E_log_prototype_convergence"]["files_quarantined"],
        "latent_defects_found": len(defects),
        "files_changed_total": touched,
    }
    slim = {k: {kk: vv for kk, vv in v.items() if kk != "per_file"}
            if isinstance(v, dict) else v for k, v in stats.items()}
    return {
        "report": report,
        "manifest_extra": {
            "transform": "block_dedupe",
            "sub_batches": slim,
            "generated_headers": [HEADER_REL],
            "defects_file": "DEFECTS.json",
            "quarantine_file": "QUARANTINE.json",
        },
    }
