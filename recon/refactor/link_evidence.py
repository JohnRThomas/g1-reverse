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


_CMAKE_SRC = re.compile(r'\$\{CMAKE_CURRENT_LIST_DIR\}/\.\./symbolized/([^"\s)]+)')
RETAINED_CMAKE = "recon/generated/app_retained_sources.cmake"
APP_ARCHIVE = os.path.join("app", "libapp.a")


def archive_members(nm: str, archive: str) -> set[str]:
    """Object-file basenames inside an archive, via ``nm -A``.

    ``ar t`` is not used: the archives this toolchain writes carry an extended
    long-name table that ``ar t`` renders unusably on this host (measured --
    it prints ``/``, ``//``, ``/0`` for most members), while ``nm -A`` prints
    ``<archive>:<member>:<symbol line>`` for every symbol and is unambiguous.
    """
    p = subprocess.run([nm, "-A", archive], capture_output=True, text=True)
    out: set[str] = set()
    prefix = archive + ":"
    for line in p.stdout.splitlines():
        if not line.startswith(prefix):
            continue
        rest = line[len(prefix):]
        i = rest.find(":")
        if i > 0:
            out.add(os.path.basename(rest[:i]))
    return out


def partition_diff(ev_objs: set[str], tree_objs: set[str],
                   present_sources: set[str]) -> tuple[list[str], list[str]]:
    """The pure set logic of ``check_partition``, so it is testable with no
    toolchain: a gate that only runs where a cross-compiler is installed is a
    gate that does not run (``stagelib.elf_section_sizes`` makes the same
    argument and parses ELF by hand for the same reason).

    Returns ``(retained sources with no object in the evidence, objects in the
    evidence that are no longer retained but whose source still exists)``.
    """
    return (sorted(tree_objs - ev_objs),
            sorted((ev_objs & present_sources) - tree_objs))


def check_partition(tree_root: str, nm: str = DEFAULT_NM,
                    data: str | None = None) -> dict:
    """Does the recorded evidence still describe THIS tree's TU partition?

    WHY THIS EXISTS -- a link failure at HEAD on 2026-07-27 found it, and it is
    the project's recurring defect class expressed at the level of a build
    artifact rather than a source line.

    ``stagelib.EVIDENCE_INPUTS`` watches the CONTENT HASH of
    ``link_referenced_symbols.json``.  The file had not changed.  The **tree it
    describes** had: stage 04's merge partition moved, so
    ``display_close_screen.c`` -- a member of ``g1_display_12.c`` in the build
    the evidence was measured from -- became its own translation unit.  Its
    call to ``display_close`` stopped being intra-object and became a
    relocation, which is exactly the precondition stage 07 checks; but stage 07
    was reading evidence that predated the move, so it gave ``display_close``
    internal linkage and the app link failed with ``undefined reference to
    `display_close'`` from stage 07 upward.  ``driver.py status`` reported every
    one of those stages as **current** throughout.

    A hash of the evidence cannot see this.  The object partition can, and it is
    a set comparison: the evidence build's ``app/libapp.a`` members against the
    consuming tree's own retained source list.  A non-empty symmetric difference
    means the evidence describes a different partition and must be regenerated
    BEFORE any stage consumes it.

    Returns a report rather than raising, and reports ``"state":
    "unverifiable"`` when the evidence build directory no longer exists -- an
    absent build is not evidence of agreement.
    """
    path = data or DATA
    if not os.path.exists(path):
        return {"state": "unverifiable", "reason": "no evidence file", "path": path}
    with open(path, encoding="utf-8") as fh:
        doc = json.load(fh)
    build = doc["provenance"]["build_dir"]
    archive = os.path.join(build, APP_ARCHIVE)
    cmake = os.path.join(tree_root, RETAINED_CMAKE)
    if not os.path.exists(archive):
        return {"state": "unverifiable",
                "reason": "evidence build directory is gone",
                "evidence_build": build, "archive": archive}
    if not os.path.exists(cmake):
        return {"state": "unverifiable", "reason": "tree has no retained source list",
                "tree": tree_root, "expected": cmake}
    with open(cmake, encoding="utf-8") as fh:
        text = fh.read()
    tree_objs = {os.path.basename(m.group(1)) + ".obj"
                 for m in _CMAKE_SRC.finditer(text)
                 if m.group(1).startswith("app/")}
    ev_objs = archive_members(nm, archive)

    # The archive also carries the byte-verified rodata and fixed-data objects,
    # which come from OTHER generated lists and are not app translation units.
    # Comparing raw sets would drown the signal in ~1,000 `rodata_*.c.obj`
    # names, so the check is stated in the one direction that is sound without
    # enumerating every other list:
    #
    #   every retained source of THIS tree must have an object of that name in
    #   the evidence archive.
    #
    # A retained source with no object then did not exist as a translation unit
    # then -- either it was absorbed into a merged unit (its symbols were
    # intra-object, so any reference to them was invisible to `nm`) or the merge
    # partition has changed some other way.  Either is disqualifying.
    #
    # The reverse direction is reported for diagnosis, filtered to objects whose
    # source still exists somewhere under `recon/symbolized/app/`, so a merged
    # unit that has been renamed or dissolved is visible without the rodata
    # noise.
    app_root = os.path.join(tree_root, "recon", "symbolized", "app")
    present_sources: set[str] = set()
    for root, _dirs, names in os.walk(app_root):
        for n in names:
            if n.endswith(".c"):
                present_sources.add(n + ".obj")
    missing_from_evidence, gone_from_tree = partition_diff(
        ev_objs, tree_objs, present_sources)
    agree = not missing_from_evidence and not gone_from_tree
    return {
        "schema": "g1.refactor.link-evidence-partition/1",
        "state": "agrees" if agree else "STALE",
        "tree": tree_root,
        "evidence": path,
        "evidence_build": build,
        "objects_in_evidence_archive": len(ev_objs),
        "objects_in_tree_source_list": len(tree_objs),
        "retained_sources_with_no_object_in_the_evidence": len(missing_from_evidence),
        "objects_in_the_evidence_no_longer_retained": len(gone_from_tree),
        "only_in_tree": missing_from_evidence[:200],
        "only_in_evidence": gone_from_tree[:200],
        "consequence":
            "The evidence describes a DIFFERENT translation-unit partition from "
            "the tree that is about to consume it.  A symbol that was "
            "intra-object then and is cross-object now will be judged "
            "unreferenced and given internal linkage, and the link will fail -- "
            "or, worse, --gc-sections will delete the caller and it will not.  "
            "Regenerate the evidence from a build of THIS tree before "
            "materializing any stage that reads it."
            if not agree else
            "The evidence build's app archive and this tree's retained source "
            "list name the same objects, so a symbol's translation unit is the "
            "same in both.",
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    g = sub.add_parser("generate")
    g.add_argument("--build", required=True)
    g.add_argument("--nm", default=DEFAULT_NM)
    g.add_argument("--map", default="zephyr.map")
    g.add_argument("--out", default=DATA)
    c = sub.add_parser("check-partition",
                       help="does the recorded evidence still describe this "
                            "tree's translation-unit partition?")
    c.add_argument("tree")
    c.add_argument("--nm", default=DEFAULT_NM)
    c.add_argument("--data", default=DATA)
    args = ap.parse_args(argv)

    if args.cmd == "check-partition":
        r = check_partition(args.tree, args.nm, args.data)
        print(json.dumps(r, indent=1))
        return 0 if r.get("state") == "agrees" else 1

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
