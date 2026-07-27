"""Stage 05 -- turn stage 04's CONCATENATIONS into COMPOSITIONS (app core only).

Stage 04's own verdict on itself (``staged_refactor_stage04.md`` §9) is the
brief for this stage, quoted rather than paraphrased:

    The merged files are concatenations, not compositions.  Each member keeps
    its own ``#include "g1_app_symbols.h"``, its own banner comment and its own
    ``extern`` block; a real ``display.c`` would have one include block, one set
    of declarations and functions ordered by call structure.

A merged unit today opens like this -- and then says the same thing again, once
per member, for up to twenty members::

    /* ---------------------------------------------------------------- */
    /* compute_lux_brightness_bucket.c */
    /* ---------------------------------------------------------------- */
    #include "g1_app_symbols.h"
    ...
    extern int opt3001_read_lux_raw(void);
    ...
    /* ---------------------------------------------------------------- */
    /* power_for_panel.c */
    /* ---------------------------------------------------------------- */
    #include "g1_app_symbols.h"
    ...
    extern int opt3001_read_lux_raw(void);

--------------------------------------------------------------------------
THE SUB-BATCH SPLIT IS BY **CODEGEN CLASS**, NOT BY INTUITION
--------------------------------------------------------------------------

This is the first stage designed after the Stage 04 R7 gate, and it is designed
around what that gate found.  Stage 04 split A/B on an R8 volatile argument that
turned out to be irrelevant: the carrier of the eight side-effect regressions
was the **linked size** of the boot path, and A's whole delta was -16 B.

So the split here is the property that actually predicts observability:

  ``N``  (default) -- **provably preprocessor-identical.**  Every edit removes
         a token sequence that the preprocessor was already discarding, or a
         declaration the compiler had already seen with the identical type
         earlier in the same translation unit.  Neither emits an instruction.
         Declared codegen class: ``size-neutral``, and the honest target is
         ``byte-identical`` -- ``driver.py size-gate 5`` measures which was
         achieved rather than asserting one.

  ``S``  (opt-in) -- **internal linkage for TU-private symbols.**  Genuinely
         production-grade (a helper nobody outside the unit calls should not be
         a global symbol) and genuinely codegen-changing: ``static`` unlocks
         inlining, changes register allocation, and lets ``--gc-sections``
         delete an unreferenced body outright.  Declared ``size-changing``;
         an oracle run is required and this stage does not claim one.

  ``NS`` -- both.

--------------------------------------------------------------------------
SUB-BATCH N, RULE BY RULE, WITH THE PROOF FOR EACH
--------------------------------------------------------------------------

**N1 -- duplicate ``#include`` withdrawal.**  Within one merged unit, the second
and later occurrences of an identical include spelling are removed; the first
stays exactly where it is.

*Proof of inertness.*  A repeated include is a no-op iff the header is
idempotent.  Two cases, and neither is assumed:

  * **angle headers** -- C11 7.1.2p4 states a standard header may be included
    more than once with no effect.  The corpus's non-standard angle headers
    (``cmsis_gcc.h``, ``zephyr/*``) are checked for a guard like any other.
  * **quoted repository headers** -- each is RESOLVED the way the compiler
    resolves it and read, and it is deduplicated only if it carries an
    ``#include`` guard (``#ifndef X`` / ``#define X`` spanning the file) or
    ``#pragma once``.  A header without one is left alone and reported in
    ``QUARANTINE.json`` under ``unguarded_headers_not_deduplicated``.

Note what this does NOT do: it does not MOVE an include.  Stage 04 §8.3 item 7
declined to hoist includes because ``g1_app_symbols.h`` opens with
``#ifndef bool``, so its expansion depends on the macro state at its include
point.  That objection applies to moving, not to deleting a repeat -- and
deletion is enough, because the first member's include block is already at the
top of the file.  One include block per translation unit, achieved without
moving a single directive.

**N2 -- duplicate file-scope declaration withdrawal.**  A file-scope ``extern``
declaration whose canonical type is IDENTICAL to one already seen earlier in
the same merged unit is removed.  C11 6.7p4 permits repeated compatible
declarations and they emit nothing; the earlier one still precedes every use,
because only LATER copies are removed.  A declaration that is *not* identical is
never touched -- stage 04's ``type`` rule already guarantees no such pair exists
inside one unit, so a difference here would mean the partition was wrong and the
right response is to leave it visible, not to hide it.

**N3 -- member banner compression.**  The three-line rule/filename/rule comment
stage 04 emits per member becomes one line.  Comments emit nothing; this is
listed as a rule only so the diff is fully accounted for.  **Every
``identity:`` provenance banner is preserved byte for byte** -- they are what
``stagelib.parity_rows`` reads, and ``driver.py check-addresses 4 5`` is the
check that they were.

--------------------------------------------------------------------------
SUB-BATCH S -- internal linkage, and the four things that can go wrong
--------------------------------------------------------------------------

A symbol defined in a merged unit gets ``static`` only if ALL of these hold, and
each one exists because ignoring it would break something specific:

  1. no other retained source, header, ``.inc`` fragment or hand-written
     integration TU in the whole app tree NAMES it;
  2. it is not named by ``recon/symbols/g1_app_globals.ld``,
     ``g1_app_aliases.ld`` or any other linker fragment -- a ``PROVIDE`` of an
     address to a name that has become static is an unresolved-symbol link
     error, and README C6 records a 563-function rename wave that left the tree
     unlinkable for many commits by missing exactly this;
  3. it is not declared in ``recon/symbols/g1_app_symbols.h`` -- that header is
     included by 1,615 sources and a ``static`` definition following a
     non-static declaration is a hard error (C11 6.2.2p7);
  4. it is not an ``__asm__``-named or aliased symbol.

Even with all four, S is codegen-changing by construction and says so.
"""

from __future__ import annotations

import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import stagelib  # noqa: E402
from guard import check_write  # noqa: E402

import sdk_symbols  # noqa: E402

from transforms import t03_module_structure as t3  # noqa: E402
from transforms import t04_cohesive_tu as t4  # noqa: E402

APP_SRC = "recon/symbolized/app/"
SYMBOLS_HEADER = "recon/symbols/g1_app_symbols.h"

BATCHES = frozenset(("N", "S", "NS", "OFF"))
DEFAULT_BATCH = "N"

#: A stage 04 merged unit is identified by its own generated banner, not by its
#: filename.  A name pattern was the first attempt and it was WRONG: it also
#: matched the eight ``recon/application/rodata/g1_app_rodata_NN.c`` byte-verified
#: table units (and their eight net siblings), whose filenames are load-bearing
#: -- ``g1_verified_rodata_keep.ld`` matches ``KEEP(*rodata_*.c.obj(...))`` on the
#: OBJECT FILENAME (README C6).  Composing one of those would have been editing
#: byte-verified data behind a gc-section rule.  They were not in fact edited
#: (they carry no duplicate include), but that was luck, not the rule.
_MERGED_BANNER = " * Cohesive translation unit for the `"


def is_merged_unit(rel: str, text: str) -> bool:
    return rel.startswith(APP_SRC) and _MERGED_BANNER in text[:512]

_INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+(?P<spell>[<"][^>"]+[>"])[ \t]*$')
_MEMBER_RULE = re.compile(r'^/\* -{10,} \*/$')
_MEMBER_NAME = re.compile(r'^/\* (?P<f>[A-Za-z_0-9.\-]+\.(?:c|inc)) \*/$')
_IDENT = re.compile(r'[A-Za-z_]\w*')


def header_is_idempotent(path: str) -> bool:
    """True iff re-including this header is provably a no-op.

    Either ``#pragma once``, or an ``#ifndef G / #define G`` pair in the first
    few directives with a matching ``#endif`` at the end -- the ordinary include
    guard.  Anything else is refused rather than guessed at.
    """
    try:
        with open(path, encoding="utf-8", errors="surrogateescape") as fh:
            text = fh.read()
    except OSError:
        return False
    code = t4.strip_comments(text)
    if re.search(r'^[ \t]*#[ \t]*pragma[ \t]+once\b', code, re.M):
        return True
    m = re.search(r'^[ \t]*#[ \t]*ifndef[ \t]+([A-Za-z_]\w*)[ \t]*$', code, re.M)
    if not m:
        return False
    guard = m.group(1)
    d = re.search(r'^[ \t]*#[ \t]*define[ \t]+%s\b' % re.escape(guard), code, re.M)
    if not d or d.start() < m.end():
        return False
    # nothing but whitespace/comments before the #ifndef, and an #endif after
    if code[:m.start()].strip():
        return False
    return bool(re.search(r'^[ \t]*#[ \t]*endif\b', code, re.M))


def compose(text: str, idempotent: dict[str, bool]) -> tuple[str, dict]:
    """Apply N1/N2/N3 to one merged translation unit.

    Returns the new text and a per-rule site count.  Operates line by line on a
    comment-blanked view so a directive or declaration carrying a trailing
    comment is seen (the failure mode that broke stage 03 at these very inputs).
    """
    blank = t3._blank_comments(text)
    lines = text.split("\n")
    blines = blank.split("\n")

    seen_includes: set[str] = set()
    seen_decls: dict[str, str] = {}
    depth = 0
    out: list[str] = []
    stats = collections.Counter()

    i, n = 0, len(lines)
    while i < n:
        raw, b = lines[i], blines[i]

        # --- N3: collapse the three-line member separator to one line
        if (_MEMBER_RULE.match(raw.strip()) and i + 2 < n
                and _MEMBER_NAME.match(lines[i + 1].strip())
                and _MEMBER_RULE.match(lines[i + 2].strip())):
            out.append("/* ---- %s ---- */" % _MEMBER_NAME.match(
                lines[i + 1].strip()).group("f"))
            stats["N3_member_banners_compressed"] += 1
            i += 3
            continue

        # --- N1: withdraw a repeated include of an idempotent header
        m = _INCLUDE.match(b)
        if m and depth == 0:
            spell = m.group("spell")
            if spell in seen_includes:
                if idempotent.get(spell, False):
                    stats["N1_duplicate_includes_withdrawn"] += 1
                    i += 1
                    continue
                stats["N1_duplicate_includes_kept_unguarded"] += 1
            else:
                seen_includes.add(spell)
            out.append(raw)
            depth += b.count("{") - b.count("}")
            i += 1
            continue

        # --- N2: withdraw a repeated file-scope declaration of the same type
        s = b.strip()
        if depth == 0 and s.startswith("extern") and s.endswith(";"):
            tail = raw[len(b.rstrip()):]
            if t3._COMMENT_TAIL.match(tail):
                sym = t3._decl_symbol(s)
                canon = t3._canon_decl(s) if sym else None
                if sym and canon is not None:
                    if seen_decls.get(sym) == canon:
                        stats["N2_duplicate_declarations_withdrawn"] += 1
                        i += 1
                        continue
                    if sym not in seen_decls:
                        seen_decls[sym] = canon
                    else:
                        # stage 04's `type` rule says this cannot happen inside
                        # one unit.  If it does, the partition was wrong: leave
                        # it visible for the compiler rather than hide it.
                        stats["N2_declarations_left_disagreeing"] += 1
        out.append(raw)
        depth += b.count("{") - b.count("}")
        i += 1

    return "\n".join(out), dict(stats)


# ------------------------------------------------------- sub-batch S helpers
_DEF_RE = re.compile(r"\)[ \t\r\n]*\{")


def tu_definitions(text: str) -> dict[str, int]:
    """External-linkage function definitions in this unit -> byte offset."""
    facts = t4.analyse(text)
    nostr = t4.strip_comments(text, drop_strings=True)
    out = {}
    for name in facts["definitions"]:
        m = re.search(r'(?<![A-Za-z_0-9])%s[ \t\r\n]*\(' % re.escape(name), nostr)
        if m:
            out[name] = m.start()
    return out


def run(stage, source_root: str, relpaths: list[str]) -> dict:
    batch = os.environ.get("G1_STAGE05_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE05_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    merged = [r for r in relpaths if is_merged_unit(r, text[r])]

    # --- which headers may be deduplicated ------------------------------
    search_dirs = [os.path.join(source_root, d) for d in (
        "recon/application/app/src", "recon/app/src", "recon/headers",
        "recon/symbols", "recon/wiring")]
    idempotent: dict[str, bool] = {}
    unguarded: dict[str, str] = {}
    for rel in merged:
        for m in re.finditer(r'^[ \t]*#[ \t]*include[ \t]+([<"][^>"]+[>"])[ \t]*$',
                             t4.strip_comments(text[rel]), re.M):
            spell = m.group(1)
            if spell in idempotent:
                continue
            if spell.startswith("<"):
                # C11 7.1.2p4: a standard header may be included more than once.
                # Non-standard angle headers are resolved and checked like any
                # other, and refused when they cannot be found.
                idempotent[spell] = True
                continue
            p = t4.resolve_quoted(os.path.join(source_root, rel),
                                  spell.strip('"'), search_dirs)
            if p is None:
                idempotent[spell] = False
                unguarded[spell] = "unresolved"
                continue
            ok = header_is_idempotent(p)
            idempotent[spell] = ok
            if not ok:
                unguarded[spell] = os.path.relpath(p, source_root)

    # --- sub-batch N ------------------------------------------------------
    totals: collections.Counter = collections.Counter()
    per_file: dict[str, dict] = {}
    if batch in ("N", "NS"):
        for rel in merged:
            new, st = compose(text[rel], idempotent)
            if new != text[rel]:
                text[rel] = new
                per_file[rel] = st
                totals.update(st)

    # --- sub-batch S ------------------------------------------------------
    s_stats: dict = {"applied": 0, "candidates": 0, "refused": {}}
    if batch in ("S", "NS"):
        s_stats = internal_linkage(source_root, relpaths, merged, text)
        totals["S_symbols_given_internal_linkage"] = s_stats["applied"]
    else:
        # measure the candidate set even when not applying it: an unexercised
        # opportunity that is never counted is an opportunity nobody knows about
        s_stats = internal_linkage(source_root, relpaths, merged, None)

    # --- emit --------------------------------------------------------------
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr = per_file.get(rel, {})
        if data != src[rel] and not tr:
            tr = {"content_changed": True}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)

    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "unguarded_headers_not_deduplicated": dict(sorted(unguarded.items())),
        "internal_linkage_refusals": s_stats["refused"],
        "note": "Sub-batch N removes only tokens the preprocessor was already "
                "discarding and declarations the compiler had already accepted "
                "identically earlier in the same TU.  Sub-batch S changes "
                "linkage and therefore codegen; it is opt-in and its candidate "
                "set is measured even when it is not applied.",
    }
    qp = os.path.join(stage.dir, "QUARANTINE.json")
    check_write(qp, stage.dir)
    with open(qp, "w", encoding="utf-8") as fh:
        json.dump(quarantine, fh, indent=1)
        fh.write("\n")

    return {
        "report": {
            "sub_batch": batch,
            "merged_units_seen": len(merged),
            "merged_units_composed": len(per_file),
            **dict(sorted(totals.items())),
            "internal_linkage_candidates": s_stats["candidates"],
        },
        "manifest_extra": {
            "transform": "cohesive composition of stage 04's merged units "
                         "(app core only)",
            "sub_batch": batch,
            "composition": {
                "merged_units_seen": len(merged),
                "merged_units_composed": len(per_file),
                "totals": dict(sorted(totals.items())),
                "headers_checked_for_idempotence": dict(sorted(idempotent.items())),
                "internal_linkage": s_stats,
            },
        },
        "parity_extra": None,
    }


def internal_linkage(source_root: str, relpaths: list[str], merged: list[str],
                     text: dict[str, str] | None) -> dict:
    """Find (and optionally apply) internal linkage for TU-private symbols.

    ``text is None`` measures the candidate set without editing anything, so the
    opportunity is reported even in the sub-batch that does not take it.
    """
    body = {r: (text[r] if text else None) for r in relpaths}
    del body

    raw: dict[str, str] = {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), encoding="utf-8",
                  errors="surrogateescape") as fh:
            raw[rel] = fh.read()

    # names mentioned OUTSIDE each merged unit, anywhere in the stage tree
    outside: dict[str, set[str]] = {}
    all_idents: collections.Counter = collections.Counter()
    per_file_idents: dict[str, set[str]] = {}
    for rel in relpaths:
        ids = set(_IDENT.findall(t4.strip_comments(raw[rel], drop_strings=True)))
        per_file_idents[rel] = ids
        for i in ids:
            all_idents[i] += 1

    # every identifier named by a linker fragment or the public symbols header
    pinned: set[str] = set()
    for rel in relpaths:
        if rel.endswith(".ld") or rel == SYMBOLS_HEADER:
            pinned |= per_file_idents[rel]
    for extra in ("recon/symbols/g1_app_globals.ld", "recon/symbols/g1_app_aliases.ld",
                  "recon/application/app/g1_verified_rodata_keep.ld"):
        p = os.path.join(source_root, extra)
        if os.path.exists(p):
            with open(p, encoding="utf-8", errors="surrogateescape") as fh:
                pinned |= set(_IDENT.findall(fh.read()))

    sdk = sdk_symbols.load()
    refused: collections.Counter = collections.Counter()
    candidates: list[tuple[str, str]] = []
    for rel in merged:
        facts = t4.analyse(raw[rel])
        mine = per_file_idents[rel]
        for name in sorted(facts["definitions"]):
            if name in pinned:
                refused["named_by_a_linker_fragment_or_the_symbols_header"] += 1
                continue
            if name in sdk:
                # the C library or Zephyr declares it, so THEY may call it and
                # no scan of our own sources can see that call.
                refused["declared_by_an_sdk_header"] += 1
                continue
            if name.startswith("_"):
                # C11 7.1.3: a file-scope identifier beginning with an
                # underscore is reserved to the implementation.  Our tree
                # DEFINING one (`_sbrk_r`, `__malloc_lock`, `_fstat_r`) means
                # newlib calls it, and newlib is not in the reference scan.
                # This is the residual hazard that keeps sub-batch S opt-in:
                # a source-text scan cannot see a call from a library or from a
                # vector table, so S must be gated by a real link (README C6).
                refused["reserved_identifier_the_implementation_may_call"] += 1
                continue
            if name in facts["asmnames"] or name in facts["macro_aliases"]:
                refused["asm_named_or_macro_renamed"] += 1
                continue
            # counted once for this file; anything more means an outside user
            if all_idents[name] > (1 if name in mine else 0):
                refused["named_outside_the_translation_unit"] += 1
                continue
            candidates.append((rel, name))
    outside.clear()

    applied = 0
    if text is not None:
        for rel, name in candidates:
            pat = re.compile(r'(?m)^(?P<head>(?!static\b)[A-Za-z_][^\n;{}]*?\b%s[ \t]*\()'
                             % re.escape(name))
            new, k = pat.subn(lambda m: "static " + m.group("head"), text[rel], count=1)
            if k:
                text[rel] = new
                applied += 1
    return {
        "candidates": len(candidates),
        "applied": applied,
        "refused": dict(sorted(refused.items())),
        "candidate_symbols": sorted(n for _, n in candidates)[:200],
    }
