#!/usr/bin/env python3
"""Evidence task: WHICH SYMBOLS ARE REFERENCED FROM OUTSIDE THEIR OWN OBJECT?

This is the evidence stage 05 §7 item 1 named and could not supply.  Sub-batch
S (internal linkage) was implemented, measured at 241 candidates and
**deliberately not applied**, for a stated and correct reason::

    The first candidate list contained `__malloc_lock', `_sbrk_r', `_fstat_r',
    `_puts_r' -- newlib callbacks that NEWLIB calls and that no scan of our own
    sources can see.

A source-text reference scan answers the wrong question.  ``static`` is a
property of the LINK, so the evidence has to come from the link: a symbol may be
given internal linkage exactly when nothing outside its own translation unit
references it, and "references it" is a relocation, not an occurrence of the
name in a ``.c`` file.

--------------------------------------------------------------------------
WHAT IS MEASURED
--------------------------------------------------------------------------

``zephyr/zephyr.map`` records the link inputs of the app image as ``LOAD``
lines -- 74 of them: the loose objects, every Zephyr/module archive, the
nrfxlib binary blobs and the toolchain's ``libc_nano.a``.  For each input,
``nm --undefined-only`` lists the symbols it REFERENCES and does not define.
An archive is scanned **whole**, every member, including members this link did
not pull in: a member that is not needed today is still evidence about what
references the symbol, and over-refusing costs a candidate while under-refusing
costs a link error or, worse, a silently different image.

The union of those undefined symbols is the answer.  ``_sbrk_r`` is in it --
contributed by ``libc_nano.a``, which is exactly the object no source scan can
read -- and so are the rest of the newlib callback family.  That is the
measurement that turns "S is unsafe because a library might call it" from an
argument into a number.

--------------------------------------------------------------------------
WHAT IT DOES NOT COVER, STATED RATHER THAN IMPLIED
--------------------------------------------------------------------------

1. **Linker scripts.**  ``PROVIDE(name = 0xADDR)`` and ``KEEP()`` name symbols
   with no relocation anywhere.  They are scanned separately by the consumer
   (README C6 records a rename wave that left the tree unlinkable by missing
   exactly this); this file does not attempt it.
2. **A future link.**  The evidence describes the archives as they exist, which
   is stronger than the link as it happened, but a source change that starts
   calling a symbol from a new place invalidates it.  That is why the consumer
   is a STAGE, regenerated from its inputs, and why this file records the build
   it was measured from.
3. **Assembly and self-modifying dispatch.**  A reference from hand-written
   assembly produces a relocation and IS covered; a computed address that never
   names the symbol is not, and cannot be by any static method.

USAGE::

    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py generate \\
        --build /private/tmp/g1-s6-base

writes ``recon/refactor/link_referenced_symbols.json``.  Consumers call
``load()``.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from guard import REPO_ROOT  # noqa: E402

DATA = os.path.join(REPO_ROOT, "recon", "refactor", "link_referenced_symbols.json")

DEFAULT_NM = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
              "arm-zephyr-eabi-nm")

_LOAD = re.compile(r'^LOAD (?P<path>\S.*)$')

#: ``nm`` prints ``        U name`` for an undefined reference and
#: ``        w name`` for a WEAK undefined reference.  A weak undefined
#: reference is still a reference: if the symbol exists it is used, and making
#: it ``static`` changes which definition (if any) the weak reference binds to.
_UNDEF = re.compile(r'^\s*(?P<type>[Uvw])\s+(?P<name>\S+)\s*$')
_DEFINED = re.compile(r'^[0-9a-fA-F]+\s+(?P<type>[A-Za-z])\s+(?P<name>\S+)\s*$')


def load_lines(map_path: str) -> list[str]:
    """The ``LOAD`` inputs of a link, in map order, minus ``linker stubs``."""
    out = []
    with open(map_path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = _LOAD.match(line.rstrip("\n"))
            if not m:
                continue
            p = m.group("path").strip()
            if p == "linker stubs":
                continue
            if p not in out:
                out.append(p)
    return out


def nm_symbols(nm: str, path: str) -> tuple[set[str], set[str]]:
    """(undefined, defined) symbol names of one object or archive."""
    p = subprocess.run([nm, "--undefined-only", path],
                       capture_output=True, text=True)
    undef = {m.group("name") for m in
             (_UNDEF.match(l) for l in p.stdout.splitlines()) if m}
    q = subprocess.run([nm, "--defined-only", path],
                       capture_output=True, text=True)
    defined = {m.group("name") for m in
               (_DEFINED.match(l) for l in q.stdout.splitlines()) if m}
    return undef, defined


def generate(build_dir: str, nm: str, map_name: str = "zephyr.map") -> dict:
    map_path = os.path.join(build_dir, "zephyr", map_name)
    inputs = load_lines(map_path)

    referenced: set[str] = set()
    app_defined: set[str] = set()
    non_app_referenced: set[str] = set()
    per_input: dict[str, int] = {}
    missing: list[str] = []
    #: which inputs contribute a reference, for the symbols a consumer will ask
    #: about.  Kept for the whole set: the file is an evidence record and
    #: "who references it" is the question asked when a refusal is disputed.
    referrers: dict[str, list[str]] = {}

    for rel in inputs:
        path = rel if os.path.isabs(rel) else os.path.join(build_dir, rel)
        if not os.path.exists(path):
            missing.append(rel)
            continue
        undef, defined = nm_symbols(nm, path)
        per_input[rel] = len(undef)
        referenced |= undef
        is_app = rel == "app/libapp.a"
        if is_app:
            app_defined |= defined
        else:
            non_app_referenced |= undef
        for s in undef:
            referrers.setdefault(s, [])
            if len(referrers[s]) < 4 and rel not in referrers[s]:
                referrers[s].append(rel)

    return {
        "schema": "g1.refactor.link-referenced-symbols/1",
        "purpose": "The set of symbols REFERENCED (as an undefined symbol, i.e. "
                   "through a relocation) by any input of the app link.  A "
                   "symbol our tree defines and that is NOT in this set is "
                   "referenced by nothing outside its own object, which is the "
                   "actual precondition for internal linkage.  A source-text "
                   "scan cannot answer this: newlib's libc_nano.a references "
                   "`_sbrk_r' and no .c file in this repository mentions it.",
        "generated_by": "recon/refactor/link_evidence.py generate",
        "provenance": {
            "build_dir": os.path.abspath(build_dir),
            "map": os.path.abspath(map_path),
            "nm": nm,
            "link_inputs": len(inputs),
            "link_inputs_missing_on_disk": missing,
            "undefined_symbols_per_input": dict(sorted(per_input.items())),
            "archives_scanned_whole": True,
            "app_archive": "app/libapp.a",
            "app_defined_symbol_count": len(app_defined),
            "referenced_by_a_non_app_input": len(non_app_referenced),
        },
        "referenced_count": len(referenced),
        "referenced": sorted(referenced),
        "referenced_by_non_app_inputs": sorted(non_app_referenced),
        "app_defined": sorted(app_defined),
        "referrers": {k: v for k, v in sorted(referrers.items())},
    }


_cache: dict | None = None


def load() -> dict:
    """The measured evidence, or empty structures when it has not been generated.

    Same policy as ``sdk_symbols.load``: absent evidence must reproduce the
    pre-evidence behaviour exactly rather than raise, so this file can never
    turn a passing pipeline red merely by being missing.  A consumer that
    DEPENDS on it says so in its own statistics.
    """
    global _cache
    if _cache is None:
        if os.path.exists(DATA):
            with open(DATA, encoding="utf-8") as fh:
                doc = json.load(fh)
            _cache = {
                "present": True,
                "referenced": set(doc["referenced"]),
                "referenced_by_non_app_inputs":
                    set(doc.get("referenced_by_non_app_inputs", [])),
                "app_defined": set(doc.get("app_defined", [])),
                "referrers": doc.get("referrers", {}),
                "build_dir": doc["provenance"]["build_dir"],
            }
        else:
            _cache = {"present": False, "referenced": set(),
                      "referenced_by_non_app_inputs": set(),
                      "app_defined": set(), "referrers": {}, "build_dir": None}
    return _cache


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("generate")
    g.add_argument("--build", required=True)
    g.add_argument("--nm", default=DEFAULT_NM)
    g.add_argument("--map", default="zephyr.map")
    g.add_argument("--out", default=DATA)
    args = ap.parse_args(argv)

    doc = generate(args.build, args.nm, args.map)
    with open(args.out, "w", encoding="utf-8") as fh:
        json.dump(doc, fh, indent=1)
        fh.write("\n")
    print(json.dumps({
        "link_inputs": doc["provenance"]["link_inputs"],
        "referenced": doc["referenced_count"],
        "referenced_by_non_app_inputs":
            doc["provenance"]["referenced_by_a_non_app_input"],
        "app_defined": doc["provenance"]["app_defined_symbol_count"],
        "written": args.out}, indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
