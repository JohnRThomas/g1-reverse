#!/usr/bin/env python3
"""Evidence task: WHICH SYMBOLS DO THE SDK ANGLE HEADERS DECLARE?

This is the one-off measurement that
``recon/analysis/staged_refactor_stage04.md`` §10 step 3 named as a
prerequisite, and that the Stage 05 pass found it also needed for a *different*
reason.  It is deliberately a **generator plus a committed data file**, not a
compile step inside a transformer: a transformer must stay a pure function of
its input bytes, and it must not need a Zephyr build directory to run.

--------------------------------------------------------------------------
WHY IT IS NEEDED -- a latent defect the Stage 05 regeneration exposed
--------------------------------------------------------------------------

Stage 03 hoists a module's byte-identically-spelled ``extern`` declarations into
a generated module header and makes every file that lost a copy include it.  A
file therefore acquires declarations it never wrote -- which is the whole point
of a module header, and is harmless right up to the moment one of those
declarations names a symbol the C library or Zephyr **already declared
authoritatively** in that translation unit.

Regenerating stage 03 at HEAD ``ff99f0c6`` (653 inputs moved by the concurrent
agent's type-disagreement repair 2) made three such declarations newly hoistable
and the stage 03 baseline **stopped compiling**::

    unsorted/g1_unsorted.h:38: error: conflicting types for 'k_sem_give';
        have 'void(int)'
      .../generated/syscalls/kernel.h:1110: note: previous definition of
        'k_sem_give' with type 'void(struct k_sem *)'
    unsorted/g1_unsorted.h:39: error: conflicting types for 'k_sleep'
    unsorted/g1_unsorted.h:44: error: conflicting types for 'strlen';
        have 'int(int)'

``unsorted/imu_fusion_init.c`` includes ``<zephyr/kernel.h>`` on line 1 and the
generated module header on line 43.  It never declared ``k_sem_give`` itself; it
acquired the reconstructed spelling from the header.

This is the same shape as stage 04 §2's ``wchar_t`` failure and it carries the
same lesson: **stage 03 landed green and is red at these inputs through no
change of its own.**  A transformer whose safety depends on which declarations
happen to agree this week is not safe; it is lucky.

--------------------------------------------------------------------------
WHAT IS MEASURED
--------------------------------------------------------------------------

For every angle header the app corpus includes, a probe translation unit that
includes only that header is compiled with the project's own flag set and
``-aux-info``, which makes GCC emit one line per declaration it saw --
prototypes from the header itself and from everything it includes.  The
identifier of every such declaration is recorded.

The flag set is lifted verbatim from a real ``build_cohesive.sh`` compile
command, so the measurement is taken under the same ``-D``/``-I``/``-imacros``
environment the build uses.  Anything else would answer a different question.

--------------------------------------------------------------------------
USAGE
--------------------------------------------------------------------------

    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/sdk_symbols.py generate \\
        --build /private/tmp/g1-s5-base-app \\
        --command-file /private/tmp/g1-s5/sdk/cmd.txt

writes ``recon/refactor/sdk_declared_symbols.json``.  Consumers just call
``load()``.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shlex
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from guard import REPO_ROOT  # noqa: E402

DATA = os.path.join(REPO_ROOT, "recon", "refactor", "sdk_declared_symbols.json")

#: the angle headers the app corpus includes, taken from the corpus itself by
#: ``census()`` and recorded in the data file's provenance.
_ANGLE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+<([^>]+)>', re.M)

#: One ``-aux-info`` line is a LOCATION COMMENT, then the declaration, then --
#: for a declaration that is also a DEFINITION in this translation unit -- a
#: TRAILING COMMENT carrying the old-style parameter list::
#:
#:   /* /ncs251/zephyr/lib/libc/.../string.h:44:NF */ extern void *memcpy (void *, const void *, size_t);
#:   /* /ncs251/modules/hal/cmsis/.../cmsis_gcc.h:269:NF */ static void __DSB (void); /* () */
#:
#: THE FIRST PARSER OF THIS FILE WAS ``^[^:]*:\d+:\d*:?[A-Z]*:?\s*(.*);\s*$`` --
#: the terminating ``;`` anchored at END OF LINE.  The trailing ``/* () */``
#: moves it, so **every line that was a definition rather than a bare prototype
#: was silently dropped**, and the definitions are exactly the
#: ``static __inline`` bodies.  That is why ``cmsis_gcc.h`` measured **0**
#: identifiers in ``sdk_declared_symbols.json`` while its ``.aux`` file had 122
#: lines: the stage 05 report recorded the symptom ("``-aux-info`` does not
#: report ``__STATIC_FORCEINLINE`` bodies") and attributed it to GCC.  It is
#: our regex.  Measured after the fix: ``cmsis_gcc.h`` 0 -> **121**,
#: ``zephyr/kernel.h`` 467 -> **857** (``k_msleep``, ``k_uptime_get``,
#: ``k_cycle_get_32``, the whole ``ARM_MPU_*`` family), ``zephyr/device.h``
#: 53 -> **151**, and **0** identifiers are lost anywhere.
#:
#: This is the THIRD time in this pipeline that a line-anchored scan has been
#: defeated by a trailing comment (stage 03's ``memset_bytes`` declaration,
#: stage 04's multi-line declarations, and now this).  The parser below is
#: therefore structural rather than anchored: take the text after the location
#: comment, strip any trailing comments, and require what remains to end in
#: ``;``.
_AUX_LOC = re.compile(r'^/\*(?:[^*]|\*(?!/))*\*/\s*(?P<rest>.*)$')
_AUX_TRAILING_COMMENT = re.compile(r'\s*/\*(?:[^*]|\*(?!/))*\*/\s*$')


def parse_aux_line(line: str) -> str | None:
    """The declaration text of one ``-aux-info`` line, or None."""
    m = _AUX_LOC.match(line.rstrip("\n"))
    if not m:
        return None
    rest = m.group("rest").strip()
    while True:
        stripped = _AUX_TRAILING_COMMENT.sub("", rest)
        if stripped == rest:
            break
        rest = stripped.strip()
    if not rest.endswith(";"):
        return None
    return rest[:-1]


def aux_identifiers(path: str) -> set[str]:
    """Every identifier declared by an ``-aux-info`` output file."""
    out: set[str] = set()
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            decl = parse_aux_line(line)
            if decl is None:
                continue
            ident = _declared_identifier(decl)
            if ident:
                out.add(ident)
    return out

#: Standard-library headers NO corpus file includes today, measured anyway.
#: The justification is specific rather than "to be safe": stages 03-05 actively
#: change which declaration reaches which translation unit, so "no file includes
#: <stdio.h> this week" is not a property a transformer may rely on.  Measured
#: cost of including them, reported by ``generate``.  ``core/g1_core.h`` really
#: does publish ``extern unsigned int snprintf(unsigned int, unsigned int,
#: unsigned int, unsigned int, unsigned int);`` today, and GCC already says
#: "'snprintf' is declared in header '<stdio.h>'" as a warning -- one #include
#: away from being the k_sem_give error.
EXTRA_HEADERS = ("stdio.h", "stdlib.h", "errno.h", "time.h", "assert.h")

#: Headers whose macro NAMES are recorded individually, not just counted.
#:
#: The full macro census is 27,838 names, ~98,000 per-header entries, and it is
#: dominated by the generated devicetree table: ``<zephyr/kernel.h>`` alone
#: contributes 27,532 ``DT_N_S_soc_S_...`` names.  Writing all of those into a
#: committed evidence file would add megabytes to answer a question nothing
#: asks.  What DOES ask a question is stage 06 sub-batch H, which may only move
#: an ``#include`` earlier in a translation unit if no identifier in the code it
#: jumps over is a macro of that header -- and the only angle headers that ever
#: appear after the first include block of a merged unit are, measured over all
#: 249 merged units, ``<stdint.h>`` (88 occurrences) and ``<stddef.h>`` (8).
#:
#: So the individual names are recorded for the C standard's type/limit headers
#: -- 822 names in total -- and every other header is recorded by count only.
#: A consumer that needs a name-level answer for a header not on this list gets
#: no evidence and must refuse, which is the correct failure direction.
MACRO_DETAIL_HEADERS = ("stdint.h", "stddef.h", "stdbool.h", "stdarg.h",
                        "limits.h", "inttypes.h", "sys/types.h")

#: probe preludes tried in order when a header will not compile standalone.
#: ``cmsis_gcc.h`` uses ``int32_t`` without including <stdint.h> itself.
PRELUDES = ("", "#include <stdint.h>\n", "#include <zephyr/kernel.h>\n")


def census(roots: list[str]) -> dict[str, int]:
    """Angle headers included by the corpus, with occurrence counts."""
    out: dict[str, int] = {}
    for root in roots:
        for dirpath, _dirs, names in os.walk(root):
            for n in names:
                if not n.endswith((".c", ".h", ".inc")):
                    continue
                with open(os.path.join(dirpath, n), encoding="utf-8",
                          errors="surrogateescape") as fh:
                    for m in _ANGLE.finditer(fh.read()):
                        out[m.group(1)] = out.get(m.group(1), 0) + 1
    return dict(sorted(out.items()))


def _declared_identifier(decl: str) -> str | None:
    """The identifier a -aux-info declaration line declares."""
    d = decl.strip()
    d = re.sub(r"\b(extern|static|inline|__inline__|__inline|register)\b", " ", d)
    # function declarator:  ... name (params)
    m = re.search(r"([A-Za-z_]\w*)\s*\(", d)
    if m:
        return m.group(1)
    ids = re.findall(r"[A-Za-z_]\w*", d)
    return ids[-1] if ids else None


_DEFINE = re.compile(r'^#define[ \t]+([A-Za-z_]\w*)')


def probe_macros(cc, flags, td, source: str) -> set[str]:
    """Every macro NAME defined after preprocessing ``source``.

    ``-aux-info`` reports declarations; it structurally cannot see a macro.
    That residue is not hypothetical: CMSIS spells the NVIC API as
    ``#define NVIC_EnableIRQ __NVIC_EnableIRQ`` over a ``static __inline``
    definition, so the *function* the fixed parser now records is
    ``__NVIC_EnableIRQ`` and the name a reconstructed declaration would
    collide with is ``NVIC_EnableIRQ``.  A transformer that publishes
    ``extern int NVIC_EnableIRQ(int);`` into a translation unit that includes
    the CMSIS core header does not merely shadow a declaration -- the
    preprocessor rewrites its own declaration to name a different symbol.

    ``-dM -E`` makes GCC dump the macro table it ends with, which is the
    ground truth for that question and needs no parsing of header text.
    """
    probe = os.path.join(td, "macro_probe.c")
    with open(probe, "w", encoding="utf-8") as fh:
        fh.write(source)
    p = subprocess.run([cc] + flags + ["-dM", "-E", "-w", probe],
                       capture_output=True, text=True)
    out: set[str] = set()
    for line in p.stdout.splitlines():
        m = _DEFINE.match(line)
        if m:
            out.add(m.group(1))
    return out


def _probe_symbols(cc, flags, td, source: str) -> set[str]:
    """Declarations a bare prelude contributes on its own."""
    probe = os.path.join(td, "prelude.c")
    aux = os.path.join(td, "prelude.aux")
    if os.path.exists(aux):
        os.remove(aux)
    with open(probe, "w", encoding="utf-8") as fh:
        fh.write(source)
    subprocess.run([cc] + flags + ["-fsyntax-only", "-w", "-aux-info", aux, probe],
                   capture_output=True, text=True)
    return aux_identifiers(aux) if os.path.exists(aux) else set()


def generate(command_file: str, build_dir: str, roots: list[str]) -> dict:
    with open(command_file, encoding="utf-8") as fh:
        argv = shlex.split(fh.read().strip())
    cc = argv[0]
    # drop the compile-specific tail: -MD/-MT/-MF/-o/-c and the source path
    flags, i = [], 1
    while i < len(argv):
        a = argv[i]
        if a in ("-MT", "-MF", "-o"):
            i += 2
            continue
        if a in ("-MD", "-c"):
            i += 1
            continue
        if a.endswith(".c") and not a.startswith("-"):
            i += 1
            continue
        flags.append(a)
        i += 1

    hdrs = census(roots)
    probe_list = list(hdrs) + [h for h in EXTRA_HEADERS if h not in hdrs]
    symbols: set[str] = set()
    in_corpus_headers: set[str] = set()
    per_header: dict[str, int] = {}
    by_header: dict[str, list[str]] = {}
    preluded: dict[str, str] = {}
    failed: dict[str, str] = {}
    macros: set[str] = set()
    macros_per_header: dict[str, int] = {}
    macros_by_header: dict[str, list[str]] = {}
    in_corpus_macros: set[str] = set()
    with tempfile.TemporaryDirectory() as td:
        # the compiler's own built-in macros, present with no #include at all;
        # they are not a header's contribution and are subtracted from each.
        builtin_macros = probe_macros(cc, flags, td, "")
        for h in probe_list:
            probe = os.path.join(td, "probe.c")
            aux = os.path.join(td, "probe.aux")
            got, err = None, "(no output)"
            for prelude in PRELUDES:
                if os.path.exists(aux):
                    os.remove(aux)
                with open(probe, "w", encoding="utf-8") as fh:
                    fh.write(prelude + "#include <%s>\n" % h)
                p = subprocess.run(
                    [cc] + flags + ["-fsyntax-only", "-w", "-aux-info", aux, probe],
                    capture_output=True, text=True)
                if not os.path.exists(aux):
                    err = (p.stderr.strip().splitlines() or ["(no output)"])[-1]
                    continue
                got = aux_identifiers(aux)
                if prelude:
                    preluded[h] = prelude.strip()
                    # a prelude contributes its OWN declarations; subtract them
                    got -= _probe_symbols(cc, flags, td, prelude)
                break
            if got is None:
                failed[h] = err
                continue
            per_header[h] = len(got)
            by_header[h] = sorted(got)
            symbols |= got
            if h in hdrs:
                in_corpus_headers |= got
            mine = probe_macros(cc, flags, td,
                                preluded.get(h, "") + "\n#include <%s>\n" % h)
            mine -= builtin_macros
            if h in preluded:
                mine -= (probe_macros(cc, flags, td, preluded[h] + "\n")
                         - builtin_macros)
            macros_per_header[h] = len(mine)
            macros |= mine
            if h in MACRO_DETAIL_HEADERS:
                macros_by_header[h] = sorted(mine)
            if h in hdrs:
                in_corpus_macros |= mine

    doc = {
        "schema": "g1.refactor.sdk-declared-symbols/1",
        "purpose": "The set of identifiers the SDK ANGLE headers used by the app "
                   "corpus declare.  A transformer may not publish a "
                   "reconstructed declaration of any of these into a translation "
                   "unit that also includes the header that declares it: the "
                   "compiler will reject it (measured -- see the module "
                   "docstring), and where it does NOT reject it, the "
                   "reconstructed spelling would silently win.",
        "generated_by": "recon/refactor/sdk_symbols.py generate",
        "provenance": {
            "aux_info_parser": "structural: strip the leading location comment, "
                               "strip trailing comments, require a terminating "
                               "`;'.  The previous parser anchored the `;' at "
                               "end of line and therefore dropped every "
                               "-aux-info line that was a DEFINITION (those "
                               "carry a trailing `/* (params) */'), which is "
                               "exactly the `static __inline' bodies -- the "
                               "measured cause of the cmsis_gcc.h `gap'.",
            "compiler": cc,
            "flag_source": os.path.abspath(command_file),
            "build_dir": os.path.abspath(build_dir),
            "angle_headers_in_corpus": hdrs,
            "extra_headers_probed_not_in_corpus": [
                h for h in EXTRA_HEADERS if h not in hdrs],
            "declarations_per_header": dict(sorted(per_header.items())),
            "headers_needing_a_prelude_to_compile_standalone": preluded,
            "headers_that_would_not_compile_standalone": failed,
            "symbols_from_corpus_headers_only": len(in_corpus_headers),
            "symbols_added_by_the_extra_headers": len(symbols - in_corpus_headers),
            "macro_source": "gcc -dM -E per header, minus the compiler's built-in "
                            "macro table and minus any prelude's own macros",
            "macros_per_header": dict(sorted(macros_per_header.items())),
            "macros_from_corpus_headers_only": len(in_corpus_macros),
            "macro_names_recorded_individually_for": list(MACRO_DETAIL_HEADERS),
            "macro_names_that_are_also_declared_identifiers":
                len(macros & symbols),
        },
        "symbol_count": len(symbols),
        "symbols": sorted(symbols),
        "symbols_by_header": dict(sorted(by_header.items())),
        "macro_count": len(macros),
        "macros": sorted(macros),
        "macros_by_header": dict(sorted(macros_by_header.items())),
    }
    return doc


_cache: set[str] | None = None
_macro_cache: set[str] | None = None


def load_macros() -> set[str]:
    """The measured MACRO names, or the empty set when absent (see ``load``).

    A macro name is a different hazard from a declared identifier and is kept
    in its own set so a consumer can report the two separately: shadowing a
    declaration is a type conflict the compiler will usually catch, while
    shadowing a macro silently rewrites the transformer's own output before the
    compiler ever sees it.
    """
    global _macro_cache
    if _macro_cache is None:
        _macro_cache = set()
        if os.path.exists(DATA):
            with open(DATA, encoding="utf-8") as fh:
                _macro_cache = set(json.load(fh).get("macros", []))
    return _macro_cache


def load() -> set[str]:
    """The measured symbol set, or the empty set when it has not been generated.

    Returning an empty set rather than raising is deliberate: a consumer that
    has no evidence must behave exactly as it did before the evidence existed,
    so this file can never turn a passing pipeline red merely by being absent.
    Callers that DEPEND on it say so (``t03`` records ``sdk_evidence_present``
    in its statistics, and ``test_sdk_symbols.py`` asserts it is there).
    """
    global _cache
    if _cache is None:
        if os.path.exists(DATA):
            with open(DATA, encoding="utf-8") as fh:
                _cache = set(json.load(fh)["symbols"])
        else:
            _cache = set()
    return _cache


_macro_detail_cache: dict | None = None


def load_macro_detail() -> dict:
    """Per-header macro NAME lists, for the headers that record them.

    Only the headers in ``MACRO_DETAIL_HEADERS`` appear.  A consumer asking
    about any other header gets no key, which it must read as "no evidence" and
    refuse -- never as "no macros".
    """
    global _macro_detail_cache
    if _macro_detail_cache is None:
        _macro_detail_cache = {}
        if os.path.exists(DATA):
            with open(DATA, encoding="utf-8") as fh:
                _macro_detail_cache = json.load(fh).get("macros_by_header", {})
    return _macro_detail_cache


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("generate")
    g.add_argument("--command-file", required=True)
    g.add_argument("--build", required=True)
    g.add_argument("--root", action="append", default=None)
    sub.add_parser("census")
    args = ap.parse_args(argv)

    roots = args.root or [os.path.join(REPO_ROOT, "recon", "symbolized", "app")]
    if args.cmd == "census":
        print(json.dumps(census(roots), indent=1))
        return 0
    doc = generate(args.command_file, args.build, roots)
    with open(DATA, "w", encoding="utf-8") as fh:
        json.dump(doc, fh, indent=1)
        fh.write("\n")
    print(json.dumps({"symbols": doc["symbol_count"],
                      "headers": len(doc["provenance"]["angle_headers_in_corpus"]),
                      "failed": list(doc["provenance"][
                          "headers_that_would_not_compile_standalone"]),
                      "written": DATA}, indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
