"""Stage 07 -- internal linkage for translation-unit-private symbols (app core).

Stage 05 §7 item 1 in full::

    I did not apply sub-batch S (internal linkage).  241 candidates measured,
    0 applied.  It needs a real link gate AND an oracle run, and a source-text
    reference scan structurally cannot see a call from newlib or from a vector
    table -- the `_sbrk_r' / `__malloc_lock' class.  Two evidence-driven
    refusals (SDK-declared, C11 7.1.3 reserved) catch 38 of them; I do not
    claim they catch all.

The claim not to make was the right one, and this stage replaces the reasoning
that produced it rather than the conclusion.  ``static`` is a property of the
LINK; the evidence therefore has to come from the link.
``recon/refactor/link_evidence.py`` runs ``nm --undefined-only`` over all 66
inputs of the app link -- every Zephyr and module archive scanned WHOLE, the
nrfxlib blobs, and the toolchain's ``libc_nano.a`` -- and records the 5,420
symbols something references through a relocation.

That measurement settles the open question with a name and a referrer rather
than an argument::

    _sbrk_r        referenced  by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a
    __malloc_lock  referenced  by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a
    _fstat_r       referenced  by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a

and it does more than confirm the known class.  Cross-checked against the
source-text scan over the same 1,158 merged-unit definitions:

  * the source scan produced 240 candidates;
  * **58 of those 240 are referenced by a relocation** -- a quarter of the set.
    They are not newlib callbacks; they are ordinary firmware functions
    (``bt_ancs_data_source_handler``, ``flash_ops_thread``, ``gatt_ccc_write``,
    ``mic_transm_thread``, ...) whose only reference is from an object the
    scan cannot read or through a table the scan does not follow.  The source
    scan was not merely incomplete for a known corner; it was wrong at 24 %.
  * 9 symbols go the other way -- the heuristics refused them and no relocation
    names them.

--------------------------------------------------------------------------
THE RULE
--------------------------------------------------------------------------

A function defined in a merged unit becomes ``static`` iff ALL hold:

  1. **no input of the app link references it** (the link evidence above).
     This subsumes and replaces "no other source names it".
  2. it is not named by ``g1_app_globals.ld`` / ``g1_app_aliases.ld`` /
     ``g1_verified_rodata_keep.ld`` / ``g1_app_symbols.h``.  A linker script
     names a symbol with no relocation anywhere, so evidence (1) cannot see it,
     and README C6 records a rename wave that left the tree unlinkable for many
     commits by missing exactly this.
  3. it is not ``__asm__``-named or macro-renamed.
  4. it is not declared by an SDK header and its name is not an SDK macro.
     Kept as a belt over the link evidence, and its cost is measured rather
     than assumed.
  5. it is not a reserved identifier (C11 7.1.3).  Also a belt; measured cost
     is reported, and the one symbol it costs (``_puts_r``) is named.

Applying it is not just a keyword: C11 6.2.2p7 makes a ``static`` definition
following a non-``static`` declaration of the same identifier a hard error, so
the transaction ALSO rewrites the symbol's own ``extern`` declaration inside
that unit and withdraws it from the generated module header.  The compiler is
the check that this was done completely (R4).

--------------------------------------------------------------------------
AND ONE NAMED EXCLUSION, WHICH IS NOT PART OF THE RULE
--------------------------------------------------------------------------

``MEASURED_EXCLUSIONS`` below holds **one symbol**, refused **by name**, on the
strength of an end-to-end emulator measurement and on nothing else.  It is not
a predicate, it does not generalise, and it must not be read as one: everything
above this paragraph is decidable from the link, the sources and the build, and
this is not.  See ``MEASURED_EXCLUSIONS``' own docstring for the mechanism, the
numbers and the standing caveat.

--------------------------------------------------------------------------
CODEGEN CLASS: ``size-changing``, AND NOT NEGOTIABLE
--------------------------------------------------------------------------

``static`` unlocks inlining, changes register allocation and lets
``--gc-sections`` delete a body nothing references.  Three measurements in this
project (+60 B, +16 B, **-16 B**) show a change of that order re-phases the
boot path and breaks byte-equality of a peripheral bus stream **in either
direction**.  This stage therefore declares ``size-changing`` and
``oracle_required``, and no measured section total may be used to argue
otherwise.
"""

from __future__ import annotations

import collections
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import link_evidence  # noqa: E402
import sdk_symbols  # noqa: E402
import stagelib  # noqa: E402
from guard import check_write  # noqa: E402

from transforms import t03_module_structure as t3  # noqa: E402
from transforms import t04_cohesive_tu as t4  # noqa: E402
from transforms import t05_cohesive_composition as t5  # noqa: E402
from transforms import t06_unit_composition as t6  # noqa: E402

#: THIS STAGE'S CORRECTNESS DEPENDS ON A TRANSLATION-UNIT PARTITION, not just
#: on the bytes of the evidence file it reads.  `link_referenced_symbols.json'
#: answers "what does something outside this symbol's own OBJECT reference?",
#: and that question has a different answer when the sources are grouped into
#: objects differently.  On 2026-07-27 stage 04's partition moved underneath
#: frozen evidence, `display_close_screen.c' left `g1_display_12.c', its call
#: to `display_close' became a relocation, this stage still read the old
#: evidence and made `display_close' static, and the app link failed from here
#: upward while `driver.py status' said `current'.
#:
#: Declaring this makes `driver.py materialize' record the partition agreement
#: in the MANIFEST and `stagelib.staleness' re-check it on every `status'.
CONSUMES_PARTITION_EVIDENCE = True

BATCHES = frozenset(("S", "OFF"))
DEFAULT_BATCH = "S"

#: SYMBOLS REFUSED BY NAME, EACH WITH THE MEASUREMENT THAT REFUSED IT.
#:
#: **This is not a rule and it does not generalise.**  Every other refusal in
#: this stage is a predicate over evidence a transformer may legitimately hold
#: -- the link's relocations, the linker scripts, the build's `--undefined='
#: roots, the SDK headers, C11 7.1.3.  An entry here is none of those: it is one
#: symbol's name, excluded because the R7 oracle measured this stage failing
#: with it and passing without it, and for no other reason.  The pipeline owner
#: decided that on 2026-07-28; the alternatives and why they were rejected are
#: recorded in `recon/emulator/reports/our_boot_bringup.md' section 52.5/52.6.
#:
#: A future reader must NOT extract a predicate from this table.  In particular
#: the two rules that were designed for it both fail:
#:
#:   * "refuse a candidate the evidence build's link still emits as an
#:     out-of-line text symbol" (section 48.10) refuses FOURTEEN symbols; twelve
#:     of them are measured null and the thirteenth carries a different,
#:     already-repaired effect.  It costs ~200 B of `text' to buy an effect
#:     that costs 8 B.
#:   * "refuse a candidate that internal linkage lets the link inline away
#:     entirely" catches ELEVEN of the thirteen; one of the eleven matters.
#:
#: So the honest statement of what this table is: **the gate's own answer,
#: written back into the stage, for exactly one symbol, deliberately, with the
#: measurement attached.**  Adding a second entry is a decision of the same
#: kind and needs the same evidence -- a full seeded two-stimulus R7 capture
#: naming the symbol as necessary and sufficient -- not an argument from
#: similarity to this one.
MEASURED_EXCLUSIONS = {
    "serialization_ipc_ept_register":
        "EMPIRICAL, NOT A RULE.  Refused by name on the R7 oracle's own "
        "measurement (our_boot_bringup.md sections 52.1-52.4, 2026-07-28), not "
        "on any property of the symbol a transformer can decide.  MEASUREMENT: "
        "all thirteen candidates that section 51.5.3 implicated were probed ONE "
        "AT A TIME (exhaustive, never a bisection, so a combination could not "
        "hide); this symbol ALONE moves the seeded navigation trigger -- the "
        "nPM1300 rail enable, TWIM1 dev=0x6B W data=080001 -- from 3,711.430 ms "
        "to 3,761.850 ms, and the other twelve each leave it at 3,711.430 ms.  "
        "On the published gate (W = 100.513 ms, R = 1.160 ms, untouched) the "
        "symbol alone reproduces the whole of stage 07's failure to the "
        "microsecond (spim_a/jbd_display D = 50.410 ms = 0.502 slots, "
        "twim1/opt3001_ambient D = 50.600 ms = 0.503 slots, both FAIL Q1), "
        "while stage 07 with only this symbol withheld -- 131 of 132 still "
        "static -- reads D = 0.000 ms on all six streams of BOTH stimuli, k = 0, "
        "S = 0.000, with 4/4 shipped golden framebuffers.  MECHANISM (measured "
        "end to end, section 52.4): `static' lets GCC inline the body into its "
        "single in-unit caller st25dv_read_chip_ids (0x88 + 0xa8 -> 0x128; both "
        "forms disassembled and semantically identical instruction for "
        "instruction, and the firmware's own 4.2 s console is 185 lines of "
        "IDENTICAL text), which moves that function's own ST25DV I2C traffic by "
        "-30 us at t = 98.720 ms -- the first departing event in the capture -- "
        "drifting to a few hundred microseconds of ordinary scheduler jitter by "
        "1.7 s, at which point the app core's acknowledgement of a GATT-sweep "
        "write falls on the far side of a 30 ms BLE connection-event boundary "
        "(CONNECT_IND Interval = 0x0018), so the navigation frame is delivered "
        "at data event #70 instead of #69, which are 60.3 ms apart, less 9.9 ms "
        "of panel-rail latency difference = the observed 50.4 ms.  CONTROLS: it "
        "is NOT size (the symbol plus 16 B of inert .text lands the image at the "
        "base's exact 956,636 B and the trigger does not move) and NOT code "
        "displacement (16 B and 32 B pads on the base are byte-exactly inert "
        "over all 318 traced bus events of the first 4.5 s, as are the other 131 "
        "static-ifications).  NOTHING IS WRONG WITH EITHER FORM OF THE CODE: "
        "this is not a defect fix, and no repair is available or needed.  COST: "
        "8 bytes of .text, 131 of 132 conversions retained.",
}

SYMBOLS_HEADER = "recon/symbols/g1_app_symbols.h"

#: Directories searched for LINKER FRAGMENTS.  They are DISCOVERED, never
#: listed.
#:
#: The measured-but-unapplied version of this transformation named three files
#: (``g1_app_globals.ld``, ``g1_app_aliases.ld``,
#: ``g1_verified_rodata_keep.ld``).  The repository has **eighteen**, and the
#: build failed at the link on one of the fifteen that were missing::
#:
#:   ld.bfd: zephyr/linker_zephyr_pre0.cmd:313: undefined symbol
#:           `wait_touch_key_release_or_timeout' referenced in expression
#:
#: from ``recon/symbols/g1_app_function_aliases.ld``::
#:
#:   PROVIDE(prepare_new_task = wait_touch_key_release_or_timeout);
#:
#: This is the same failure shape as the first size gate keying on a list of
#: section names (README C7b) and as README C6's rename wave: a rule keyed on a
#: hand-maintained list of filenames is a rule that silently stops covering the
#: thing it was written for.  It is also exactly why C6 requires a REAL LINK as
#: the gate for this class of change -- a linker-script expression names a
#: symbol with no relocation anywhere, so no amount of ``nm`` evidence can see
#: it, and the link is the only oracle that can.
LD_SEARCH_DIRS = ("recon/symbols", "recon/application", "recon/generated",
                  "recon/board", "recon/wiring")

#: ``-Wl,--undefined=NAME`` forces a symbol onto the link.  It is a reference
#: that exists only in the build system, so it is invisible to ``nm`` in exactly
#: the way a linker-script expression is -- and in THIS build it is never
#: written literally: the app CMakeLists says
#: ``foreach(_g1_root IN LISTS G1_RECOVERED_GC_ROOTS) ...
#: zephyr_ld_options("-Wl,--undefined=${_g1_root}")``, with the 20 names living
#: in the generated ``recon/generated/app_gc_roots.cmake``.  Matching only the
#: literal spelling would have found ZERO of them.
_FORCE_UNDEFINED = re.compile(r'--undefined=([A-Za-z_]\w*)')
_FORCE_UNDEFINED_VAR = re.compile(r'--undefined=\$\{([A-Za-z_]\w*)\}')
_SET_BLOCK = re.compile(r'(?ms)^[ \t]*set[ \t]*\([ \t]*([A-Za-z_]\w*)([^()]*?)\)')
_FOREACH = re.compile(r'(?m)^[ \t]*foreach[ \t]*\([ \t]*([A-Za-z_]\w*)([^)]*)\)')


def _cmake_forced_symbols(texts: dict[str, str]) -> set[str]:
    """Symbols a CMake build forces onto the link with ``--undefined=``.

    Resolves the indirection structurally: literal names, ``foreach(VAR a b c)``
    bodies whose loop variable is interpolated into ``--undefined=``, and
    ``foreach(VAR IN LISTS L)`` through the ``set(L ...)`` that defines ``L``
    in any of the scanned files.
    """
    setvars: dict[str, set[str]] = {}
    for body in texts.values():
        for m in _SET_BLOCK.finditer(body):
            setvars.setdefault(m.group(1), set()).update(
                _IDENT.findall(re.sub(r"#[^\n]*", " ", m.group(2))))
    out: set[str] = set()
    for body in texts.values():
        out |= set(_FORCE_UNDEFINED.findall(body)) - {"undefined"}
        loopvars = set(_FORCE_UNDEFINED_VAR.findall(body))
        if not loopvars:
            continue
        for m in _FOREACH.finditer(body):
            if m.group(1) not in loopvars:
                continue
            args = m.group(2)
            lists = re.search(r'\bIN[ \t]+LISTS[ \t]+(.*)$', args)
            if lists:
                for v in _IDENT.findall(lists.group(1)):
                    out |= setvars.get(v, set())
            else:
                out |= set(_IDENT.findall(args))
    return {n for n in out if n not in ("IN", "LISTS", "ITEMS")}

_IDENT = re.compile(r'[A-Za-z_]\w*')


def pinned_by_the_build(source_root: str) -> tuple[set[str], list[str]]:
    """Identifiers named by a linker fragment or forced onto the link."""
    names: set[str] = set()
    seen: list[str] = []
    cmake_texts: dict[str, str] = {}
    for d in LD_SEARCH_DIRS:
        base = os.path.join(source_root, d)
        if not os.path.isdir(base):
            continue
        for root, dirs, files in os.walk(base):
            for f in sorted(files):
                p = os.path.join(root, f)
                rel = os.path.relpath(p, source_root).replace(os.sep, "/")
                if f.endswith(".ld"):
                    with open(p, encoding="utf-8", errors="surrogateescape") as fh:
                        names |= set(_IDENT.findall(fh.read()))
                    seen.append(rel)
                elif f == "CMakeLists.txt" or f.endswith(".cmake"):
                    with open(p, encoding="utf-8", errors="surrogateescape") as fh:
                        cmake_texts[rel] = fh.read()
    forced = _cmake_forced_symbols(cmake_texts)
    if forced:
        names |= forced
        seen.append("--undefined= roots from %d CMake files: %d symbols"
                    % (len(cmake_texts), len(forced)))
    return names, sorted(seen)


def definition_start(text: str, name: str) -> int | None:
    """Byte offset of the first token of ``name``'s file-scope definition.

    Found STRUCTURALLY, by the same walk ``t04.analyse`` uses to find the
    definition at all, and then back to the previous file-scope ``;`` / ``}`` /
    start of file.  A line-anchored ``^[A-Za-z_].*name[ \\t]*\\(`` rule -- which
    is what the measured-but-unapplied version of this transformation used --
    cannot see ``typedef unsigned char u8;u8 is_battery_critical(void){...}``,
    and this corpus writes exactly that (t04.analyse's own docstring records
    the two cases).  Line anchoring has now failed three times in this
    pipeline; it is not used here.
    """
    nostr = t4.strip_comments(text, drop_strings=True)
    depth = t4._depths(nostr)
    for m in re.finditer(r"\)[ \t\r\n]*\{", nostr):
        if depth[m.start()] != 0:
            continue
        i, level = m.start(), 0
        while i >= 0:
            if nostr[i] == ")":
                level += 1
            elif nostr[i] == "(":
                level -= 1
                if level == 0:
                    break
            i -= 1
        if i < 0:
            continue
        nm = re.search(r"([A-Za-z_]\w*)[ \t\r\n]*$", nostr[:i])
        if nm is None or nm.group(1) != name:
            continue
        # ---- back to the boundary that starts this declaration.
        #
        # THE FIRST VERSION OF THIS WALK WAS WRONG and the build caught it
        # (`error: duplicate 'static'' in `ble/g1_ble_02.c' and
        # `notify/g1_notify_02.c').  It accepted a `}' only when
        # ``depth[j-1] == 0``, but ``depth`` is the depth BEFORE a character, and
        # the depth before a function body's closing brace is 1, never 0.  So a
        # `}' was never a boundary, the walk skipped back over whole function
        # bodies, and THREE candidates in one file all resolved to the start of
        # the SAME earlier definition -- which is how one function acquired two
        # `static' keywords while two others silently kept external linkage.
        # A closing brace is a boundary when the depth AFTER it is 0, which is
        # ``depth[j]``.
        j = i
        while j > 0:
            ch = nostr[j - 1]
            if ch == ";" and depth[j - 1] == 0:
                break
            if ch == "}" and depth[j] == 0:
                break
            if ch == "\n" and _preprocessor_line_ends_at(nostr, j - 1):
                break
            j -= 1
        while j < len(nostr) and nostr[j] in " \t\r\n":
            j += 1
        # ---- invariant: what lies between the boundary and the parameter list
        # must be declaration specifiers and the declarator, nothing else.  This
        # is the check that would have caught the bug above at materialise time
        # instead of at the build, so it is asserted rather than trusted.
        span = nostr[j:i]
        if not span.strip() or any(c in span for c in ";{}#()"):
            return None
        return j
    return None


def _preprocessor_line_ends_at(nostr: str, nl: int) -> bool:
    """True iff the line ending at offset ``nl`` is a preprocessor directive."""
    start = nostr.rfind("\n", 0, nl) + 1
    return nostr[start:nl].lstrip().startswith("#")


def candidates(source_root: str, relpaths: list[str], merged: list[str],
               text: dict[str, str]) -> tuple[list[tuple[str, str]], dict, dict]:
    ev = link_evidence.load()
    sdk = sdk_symbols.load()
    sdk_macros = sdk_symbols.load_macros()

    pinned: set[str] = set()
    for rel in relpaths:
        if rel.endswith(".ld") or rel == SYMBOLS_HEADER:
            pinned |= set(_IDENT.findall(text[rel]))
    build_pins, pin_sources = pinned_by_the_build(source_root)
    pinned |= build_pins

    refused: collections.Counter = collections.Counter()
    excluded: list[dict] = []
    out: list[tuple[str, str]] = []
    total_defs = 0
    for rel in merged:
        facts = t4.analyse(text[rel])
        for name in sorted(facts["definitions"]):
            total_defs += 1
            if facts["statics"].get(name) == "func":
                # ``t04.analyse`` reports EVERY file-scope function definition
                # in ``definitions``, including ones that are already
                # ``static``; it keeps the linkage in a separate ``statics``
                # map.  Omitting this test produced `error: duplicate 'static''
                # in `ble/g1_ble_02.c' and `notify/g1_notify_02.c' on the first
                # build of this stage -- and it is a bug with teeth beyond the
                # duplicate keyword, because a symbol that is ALREADY internal
                # can never appear in the link evidence's referenced set, so
                # every already-static function looked like a perfect candidate.
                refused["already_has_internal_linkage"] += 1
            elif name in pinned:
                refused["named_by_a_linker_fragment_or_the_symbols_header"] += 1
            elif name in facts["asmnames"] or name in facts["macro_aliases"]:
                refused["asm_named_or_macro_renamed"] += 1
            elif name in ev["referenced"]:
                refused["referenced_by_a_relocation"] += 1
            elif name in sdk:
                refused["declared_by_an_sdk_header"] += 1
            elif name in sdk_macros:
                refused["named_by_an_sdk_macro"] += 1
            elif name.startswith("_"):
                refused["reserved_identifier_c11_7_1_3"] += 1
            elif name in MEASURED_EXCLUSIONS:
                # LAST in the chain on purpose: a symbol reaches this arm only
                # when every decidable rule above would have ACCEPTED it, so the
                # counter below is the exact price of the owner's decision and
                # cannot be confused with a rule doing its job.
                refused["measured_exclusion_named_by_the_pipeline_owner"] += 1
                excluded.append({"symbol": name, "file": rel,
                                 "kind": "named exclusion -- empirical, not a rule",
                                 "reason": MEASURED_EXCLUSIONS[name]})
            else:
                out.append((rel, name))
    unseen = sorted(set(MEASURED_EXCLUSIONS) - {e["symbol"] for e in excluded})
    meta = {
        "link_evidence_present": ev["present"],
        "link_evidence_build": ev["build_dir"],
        "link_referenced_symbols": len(ev["referenced"]),
        "external_linkage_definitions_in_merged_units": total_defs,
        "linker_fragments_and_build_pins_discovered": pin_sources,
        "identifiers_pinned_by_the_build": len(pinned),
        #: an entry that stops matching a definition is an entry that has gone
        #: stale (renamed symbol, moved unit, or a rule above it now refusing
        #: it first).  Reported so it cannot rot silently.
        "measured_exclusions_declared": sorted(MEASURED_EXCLUSIONS),
        "measured_exclusions_that_bit": sorted(e["symbol"] for e in excluded),
        "measured_exclusions_that_matched_nothing": unseen,
        #: the entries themselves, reason text and all.  Carried inside `meta'
        #: rather than as a fourth return value so that every existing caller of
        #: `candidates()' -- including the out-of-tree subset instrument the R7
        #: bisections are run with -- keeps working unchanged.
        "measured_exclusion_entries": excluded,
    }
    return out, dict(refused), meta


def apply_static(text: dict[str, str], header_text: dict[str, str],
                 cand: list[tuple[str, str]]) -> dict:
    stats: collections.Counter = collections.Counter()
    failed: list[str] = []
    by_name = {}
    for rel, name in cand:
        off = definition_start(text[rel], name)
        if off is None:
            failed.append(name)
            stats["definition_site_not_found"] += 1
            continue
        text[rel] = text[rel][:off] + "static " + text[rel][off:]
        stats["definitions_given_internal_linkage"] += 1
        by_name[name] = rel

    # C11 6.2.2p7: a `static' definition after a non-`static' declaration of the
    # same identifier is a hard error, so every surviving declaration of the
    # symbol has to move with it -- inside the unit, and in the generated
    # module header that publishes it.
    names = set(by_name)
    for rel in set(by_name.values()):
        text[rel], n = _restate_declarations(text[rel], names)
        stats["in_unit_extern_declarations_made_static"] += n
    for h in list(header_text):
        header_text[h], n = _withdraw_declarations(header_text[h], names)
        stats["module_header_declarations_withdrawn"] += n
    return {"totals": dict(stats), "failed": failed}


def _restate_declarations(body: str, names: set[str]) -> tuple[str, int]:
    blank = t3._blank_comments(body)
    lines, blines = body.split("\n"), blank.split("\n")
    out, n = [], 0
    depth = 0
    for line, b in zip(lines, blines):
        s = b.strip()
        if depth == 0 and s.startswith("extern") and s.endswith(";"):
            sym = t3._decl_symbol(s)
            if sym in names and t3._COMMENT_TAIL.match(line[len(b.rstrip()):]):
                out.append(line.replace("extern", "static", 1))
                n += 1
                depth += b.count("{") - b.count("}")
                continue
        out.append(line)
        depth += b.count("{") - b.count("}")
    return "\n".join(out), n


def _withdraw_declarations(body: str, names: set[str]) -> tuple[str, int]:
    blank = t3._blank_comments(body)
    lines, blines = body.split("\n"), blank.split("\n")
    out, n = [], 0
    for line, b in zip(lines, blines):
        s = b.strip()
        if s.startswith("extern") and s.endswith(";"):
            sym = t3._decl_symbol(s)
            if sym in names and t3._COMMENT_TAIL.match(line[len(b.rstrip()):]):
                n += 1
                continue
        out.append(line)
    return "\n".join(out), n


def run(stage, source_root: str, relpaths: list[str]) -> dict:
    batch = os.environ.get("G1_STAGE07_BATCH", DEFAULT_BATCH).upper()
    if batch not in BATCHES:
        raise SystemExit("G1_STAGE07_BATCH must be one of %s, got %r"
                         % (sorted(BATCHES), batch))

    src, text = {}, {}
    for rel in relpaths:
        with open(os.path.join(source_root, rel), "rb") as fh:
            src[rel] = fh.read()
        text[rel] = src[rel].decode("utf-8", errors="surrogateescape")

    # generated module headers are inherited outputs, not manifest inputs
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
    hsrc, htext = {}, {}
    for rel in inherited:
        with open(os.path.join(source_root, rel), "rb") as fh:
            hsrc[rel] = fh.read()
        htext[rel] = hsrc[rel].decode("utf-8", errors="surrogateescape")

    merged = [r for r in relpaths if t5.is_merged_unit(r, text[r])]
    cand, refused, meta = candidates(source_root, relpaths, merged, text)

    applied: dict = {"totals": {}, "failed": []}
    if batch == "S":
        applied = apply_static(text, htext, cand)

    changed = 0
    for rel in relpaths:
        data = text[rel].encode("utf-8", errors="surrogateescape")
        tr: dict = {}
        if data != src[rel]:
            changed += 1
            tr = {"content_changed": True}
        stage.emit(rel, data, os.path.join(source_root, rel),
                   stagelib.sha256_bytes(src[rel]), tr)
    for rel in inherited:
        data = htext[rel].encode("utf-8", errors="surrogateescape")
        if data == hsrc[rel]:
            continue
        out = os.path.join(stage.tree, rel)
        check_write(out, stage.dir)
        with open(out, "wb") as fh:
            fh.write(data)

    quarantine = {
        "schema": "g1.refactor.stage-quarantine/1",
        "stage": stage.number,
        "sub_batch": batch,
        "internal_linkage_refusals": refused,
        "evidence": meta,
        "note": "A refusal here is a symbol left with external linkage, which "
                "is what it has today: refusing costs nothing but an "
                "opportunity.  Applying wrongly costs a link error at best and "
                "a silently rebound call at worst, so every rule fails closed.",
        "measured_exclusions": {
            "count": len(meta["measured_exclusion_entries"]),
            "what_this_is": "Symbols refused BY NAME on an R7 oracle "
                            "measurement, not by any predicate.  Each entry "
                            "carries the measurement that refused it.  This is "
                            "NOT a defect fix -- no repair is available or "
                            "needed for these symbols -- and it is NOT a "
                            "general rule: nothing here may be turned into "
                            "one.  See the MEASURED_EXCLUSIONS docstring in "
                            "transforms/t07_internal_linkage.py and "
                            "recon/emulator/reports/our_boot_bringup.md "
                            "sections 52.5/52.6 and 53.",
            "entries": meta["measured_exclusion_entries"],
            "declared_but_matched_nothing":
                meta["measured_exclusions_that_matched_nothing"],
        },
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
            "merged_units_seen": len(merged),
            "candidates": len(cand),
            "measured_exclusions": meta["measured_exclusions_that_bit"],
            **applied["totals"],
        },
        "manifest_extra": {
            "transform": "internal linkage for TU-private symbols, decided by "
                         "link evidence (app core only)",
            "sub_batch": batch,
            "internal_linkage": {
                "candidates": len(cand),
                "candidate_symbols": sorted(n for _, n in cand),
                "refused": refused,
                "evidence": meta,
                "applied": applied["totals"],
                "definition_sites_not_found": applied["failed"],
            },
        },
        "parity_extra": None,
    }
