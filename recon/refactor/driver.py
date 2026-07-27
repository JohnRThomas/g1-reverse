#!/usr/bin/env python3
"""Idempotent stage driver for the G1 staged refactor.

    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py status
    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize 0
    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize 1
    PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py check-addresses 0 1

Properties this file is responsible for:

* **idempotent** -- running ``materialize N`` twice produces byte-identical
  stage trees and MANIFESTs (the transformers are pure functions of their
  input bytes).
* **write-guarded** -- every write goes through ``guard.check_write``, which
  refuses any path inside a protected evidence tree (R1) and any path outside
  the stage's own directory.  ``test_guard.py`` proves both refusals.
* **staleness-reporting** -- ``status`` reports, per stage, whether any input's
  content hash has moved since the stage was generated.  The only repair is
  regeneration.
* **integrity-checking** -- ``check-addresses A B`` asserts that the SET of
  original addresses carried by two consecutive stages is identical.  An
  address that gains or loses an entry means a transformation dropped or
  duplicated a function.
"""

from __future__ import annotations

import argparse
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import input_set  # noqa: E402
import stagelib  # noqa: E402
from guard import REPO_ROOT, check_write  # noqa: E402

# Stage registry.  Ordered most-mechanical / least-risky first, so that if
# side-effect equivalence later breaks we learn WHICH stage broke it.
#
# The fifth field is the stage's DECLARED CODEGEN CLASS -- a first-class,
# checkable property added after the Stage 04 R7 gate found the hard way that
# a -16 B change of `.text` re-phases the boot path and breaks byte-equality of
# two peripheral bus streams.  See `stagelib.CODEGEN_CLASSES` for the full
# reasoning and `driver.py size-gate` for the check.
#
#   byte-identical  the linked image must be byte-identical to the input
#                   stage's; gate is `cmp zephyr.bin`; no oracle run needed
#   size-neutral    the image may differ but every allocatable section size is
#                   unchanged
#   size-changing   section sizes move; an ORACLE RUN IS REQUIRED and may not
#                   be inferred, argued or borrowed from a previous stage
STAGES = [
    (0, "snapshot", "verbatim snapshot of the compilable input set (identity transform)",
     "t00_snapshot", "byte-identical"),
    (1, "literal_inline", "inline byte-verified .rodata string literals whose every "
     "live reference is a string-consuming call argument, withdrawing the backing "
     "object, its PROVIDE pin and its extern declaration in the same transaction.  "
     "DECLARED size-changing since 2026-07-27: it had been declared byte-identical "
     "and NO SIZE GATE HAD EVER BEEN RUN FOR IT.  When one was, it measured "
     "size-changing -- rodata -124 B, text -4 B -- which is exactly what the "
     "transform does: withdrawing 100 backing objects worth 3,997 B cannot leave "
     "the image byte-identical, and the stage's own harvest says so.  The "
     "behavioural obligation IS discharged for this image (the phase-tolerant pass "
     "captured stages 01/02/03 and the image is cmp-identical to the one it "
     "booted), but it was discharged by accident rather than by the declaration.",
     "t01_literal_inline", "size-changing"),
    (2, "block_dedupe", "replace repeated code blocks with inlinable macros: "
     "volatile-accessor spelling normalisation (same C type only), the noreturn "
     "tail, the log-sink route, the assert expansion, and convergence of the "
     "per-file logging externs onto the one authoritative prototype",
     "t02_block_dedupe", "byte-identical"),
    (3, "module_structure", "FIRST STRUCTURAL STAGE, app core only: move every "
     "retained app source into a cohesive module directory (regenerating the "
     "two build artifacts that name sources by path, in the SAME transaction "
     "and with list order preserved exactly), then hoist each module's "
     "byte-identically-spelled extern declarations into a generated module "
     "header.  The net core is frozen and is not touched.",
     "t03_module_structure", "byte-identical"),
    (4, "cohesive_tu", "SCOPED cohesive translation-unit merge, app core only: "
     "concatenate each maximal ORDER-PRESERVING run of consecutive retained "
     "sources within one module directory that provably cannot collide (no "
     "symbol declared with two types, no internal-linkage identifier named by "
     "another member, no local typedef or macro visible to a member that names "
     "it, no duplicate assembler name), rewriting the generated source list in "
     "the same transaction.  This is the FIRST stage whose image cannot be "
     "byte-identical by construction: merging changes inlining opportunities.",
     "t04_cohesive_tu", "size-changing"),
    (5, "cohesive_composition", "COMPOSITION, app core only: turn stage 04's "
     "concatenated merged units into composed translation units -- one include "
     "block per unit (repeated includes of PROVABLY idempotent headers "
     "withdrawn, never moved), one declaration site per symbol per unit "
     "(repeated file-scope externs of identical canonical type withdrawn), and "
     "one-line member banners, with every `identity:' provenance banner "
     "preserved byte for byte.  Sub-batch N is preprocessor-identical by "
     "construction; sub-batch S (internal linkage for TU-private symbols) is "
     "opt-in and codegen-changing.",
     "t05_cohesive_composition", "size-neutral"),
    (6, "unit_composition", "COMPOSITION DEPTH, app core only: move each "
     "generated module-header declaration into the SINGLE translation unit "
     "that still uses it (and delete outright one that no longer has any "
     "user), and hoist a late `#include' to the unit's first include block "
     "under two checks -- no intervening preprocessor directive, and no "
     "identifier in the code it jumps over is a macro of that header.  "
     "Neither rule emits an instruction; the stage declares byte-identical "
     "and `size-gate 6' measures whether that held.",
     "t06_unit_composition", "byte-identical"),
    (7, "internal_linkage", "INTERNAL LINKAGE for translation-unit-private "
     "symbols, app core only, decided by LINK EVIDENCE rather than by a "
     "source-text scan: a symbol may become `static' only when no input of the "
     "app link references it through a relocation (recon/refactor/"
     "link_evidence.py, which reads newlib's own archive and therefore SEES "
     "the `_sbrk_r' class the source scan structurally cannot).  `static' "
     "unlocks inlining and lets --gc-sections delete an unreferenced body, so "
     "this stage is size-changing BY CONSTRUCTION and an oracle run is "
     "required.",
     "t07_internal_linkage", "size-changing"),
    (8, "call_order", "CALL-ORDER FUNCTION REORDERING within a merged unit: "
     "emit each unit's functions in a call-structure order (definition before "
     "use where the unit's own call graph is acyclic) instead of the link "
     "order stage 04 inherited.  Reordering changes `.text' LAYOUT even at "
     "identical total size, and layout is exactly what re-phases the boot "
     "path, so this stage is size-changing by default and its declaration is "
     "not weakened on the strength of a measured byte total.",
     "t08_call_order", "size-changing"),
    (9, "call_cohesion", "CALL-COHESION GROUPING, app core only: group "
     "translation units that CALL ONE ANOTHER inside a module directory, "
     "instead of stage 04's runs of link-order-adjacent sources.  Stage 08 "
     "measured 11 call edges inside all 249 stage 04 units against 1,224 "
     "intra-module edges between distinct units, which is the measurement "
     "that says stage 04 groups on the wrong axis.  Candidates are visited "
     "in generated-source-list order and placed first-fit into a group they "
     "have a call edge into and that stage 04's seven refusal rules clear "
     "them against, member by member.  Members were NOT adjacent, so every "
     "member after the first moves position: the layout disturbance is "
     "strictly larger than stage 04's and the declaration is not weakened "
     "on any measured byte total.",
     "t09_call_cohesion", "size-changing"),
    (99, "defect_probe", "DIAGNOSTIC, NOT A STAGE: stage 02 with "
     "G1_STAGE02_FORCE_LOG_HEADER=1, which withdraws the local log externs in "
     "the files stage 02 quarantines.  This tree is EXPECTED NOT TO COMPILE; "
     "its compile errors are the measurement that turns stage 02's static "
     "prediction of latent defects into a compiler-confirmed count.",
     "t02_block_dedupe", "size-changing"),
]

#: directories that must be REAL in a stage tree (not symlinks), because a
#: relative `..` traversal starts inside them.  If one of these were a symlink,
#: an OS-level (physical) `..` resolution would escape the stage tree and
#: silently compile the LIVE repository instead -- a silent-wrong failure.
FORCE_REAL_DIRS = (
    "recon",
    "recon/generated",
    "recon/headers",
    "recon/symbols",
    "recon/symbolized",
    "recon/symbolized/app",
    "recon/symbolized/net",
    "recon/application",
    "recon/application/app",
    "recon/application/app/src",
    "recon/application/net",
    "recon/application/net/src",
    "recon/application/rodata",
)

SKIP_ROOT_ENTRIES = {".git", ".venv"}


def _stage(number: int):
    for row in STAGES:
        if row[0] == number:
            return row
    raise SystemExit("no such stage: %d" % number)


def _relsym(target_abs: str, link_abs: str) -> str:
    return os.path.relpath(target_abs, os.path.dirname(link_abs))


def build_tree_skeleton(stage) -> None:
    """Create the buildable root: real dirs where needed, symlinks elsewhere.

    The result is a directory that ``build_cohesive.sh`` can be invoked from
    exactly as if it were the repository root, so a stage is built under
    conditions identical to the in-tree build with no build-file edits at all.
    """
    tree = stage.tree
    check_write(tree, stage.dir)
    os.makedirs(tree, exist_ok=True)

    # repo-root entries other than recon/: carried by reference
    for entry in sorted(os.listdir(REPO_ROOT)):
        if entry in SKIP_ROOT_ENTRIES or entry == "recon":
            continue
        link = os.path.join(tree, entry)
        _place_symlink(link, os.path.join(REPO_ROOT, entry), stage)
    # the virtualenv is found by build_cohesive.sh via ${repo_root}/.venv
    _place_symlink(os.path.join(tree, ".venv"), os.path.join(REPO_ROOT, ".venv"), stage)

    real = set(FORCE_REAL_DIRS)
    for d in sorted(real):
        p = os.path.join(tree, d)
        check_write(p, stage.dir)
        os.makedirs(p, exist_ok=True)

    for d in sorted(real):
        src_dir = os.path.join(REPO_ROOT, d)
        if not os.path.isdir(src_dir):
            continue
        for entry in sorted(os.listdir(src_dir)):
            rel = d + "/" + entry
            if rel in real:
                continue          # already a real dir, filled by its own pass
            if rel == "recon/refactor":
                continue          # never recurse into the pipeline itself
            link = os.path.join(tree, rel)
            if os.path.exists(link) and not os.path.islink(link):
                continue          # a materialised file already owns this slot
            _place_symlink(link, os.path.join(src_dir, entry), stage)


def _place_symlink(link_abs: str, target_abs: str, stage) -> None:
    check_write(link_abs, stage.dir)
    if os.path.islink(link_abs):
        os.unlink(link_abs)
    elif os.path.isdir(link_abs):
        return
    elif os.path.exists(link_abs):
        os.remove(link_abs)
    os.makedirs(os.path.dirname(link_abs), exist_ok=True)
    os.symlink(_relsym(target_abs, link_abs), link_abs)


def materialize(number: int) -> dict:
    n, slug, desc, modname, codegen_class = _stage(number)
    mod = __import__("transforms." + modname, fromlist=["run"])
    stage = stagelib.Stage(n, slug, desc)

    # a stage is regenerated wholesale; drop any previous materialised files so
    # a removed input cannot linger (hand-patching is never the repair path)
    if os.path.isdir(stage.tree):
        import shutil
        check_write(stage.tree, stage.dir)
        shutil.rmtree(stage.tree)
    build_tree_skeleton(stage)

    if n == 0:
        source_root = REPO_ROOT
        iset = input_set.derive()
        relpaths = list(iset.transformable)
        input_stage = None
    else:
        # stage 99 is the diagnostic re-run of stage 02's transformer with the
        # forcing environment variable set; its input is stage 02's input.
        pn, pslug = _stage(1 if n == 99 else n - 1)[:2]
        prev = stagelib.Stage(pn, pslug, "")
        prev_man = stagelib.load_manifest(pn, pslug)
        if prev_man is None:
            raise SystemExit("stage %d must be materialized before stage %d" % (pn, n))
        source_root = prev.tree
        relpaths = sorted(prev_man["files"])
        iset = None
        input_stage = {"stage": pn, "slug": pslug,
                       "tree": os.path.relpath(prev.tree, REPO_ROOT)}

    # A transformer may emit GENERATED artifacts that are outputs, not inputs
    # (stage 02's recon/headers/g1_dedupe.h, stage 03's module headers).  They
    # are deliberately absent from MANIFEST["files"] -- staleness would
    # otherwise hunt for a source that never existed -- so the next stage would
    # not see them in `relpaths` and its tree would be missing a header 235
    # sources include.  Inherit them explicitly: any REAL file in the previous
    # stage's tree that its manifest does not list is a generated artifact of
    # that stage, and it is carried forward verbatim.
    inherited = []
    if n != 0:
        known = set(relpaths)
        for root, dirs, names in os.walk(source_root):
            dirs[:] = [d for d in dirs if not os.path.islink(os.path.join(root, d))]
            for name in names:
                ap = os.path.join(root, name)
                if os.path.islink(ap):
                    continue
                rel = os.path.relpath(ap, source_root).replace(os.sep, "/")
                if rel in known:
                    continue
                dst = os.path.join(stage.tree, rel)
                check_write(dst, stage.dir)
                os.makedirs(os.path.dirname(dst), exist_ok=True)
                if os.path.islink(dst):
                    os.unlink(dst)
                with open(ap, "rb") as fh:
                    data = fh.read()
                with open(dst, "wb") as fh:
                    fh.write(data)
                inherited.append(rel)
        inherited.sort()

    summary = mod.run(stage, source_root, relpaths)

    extra = {"input_stage": input_stage,
             "evidence_inputs": stagelib.evidence_hashes(),
             "declared_codegen_class": codegen_class,
             "oracle_required": codegen_class == "size-changing",
             "inherited_generated_outputs": inherited}
    if iset is not None:
        extra["input_provenance"] = iset.provenance
        extra["quarantined_protected_build_inputs"] = iset.quarantined_protected
    extra.update(summary.get("manifest_extra", {}))
    stage.write_manifest(extra)
    rows = stagelib.parity_rows(stage.tree, sorted(stage.files))
    stage.write_parity_map(rows, summary.get("parity_extra"))
    return {"stage": n, "slug": slug, "files": len(stage.files),
            "declared_codegen_class": codegen_class,
            "parity_rows": len(rows), **summary.get("report", {})}


def status() -> list[dict]:
    out = []
    for row in STAGES:
        st = stagelib.staleness(row[0], row[1])
        st["declared_codegen_class"] = row[4]
        out.append(st)
    return out


def check_addresses(a: int, b: int) -> dict:
    an, aslug = _stage(a)[:2]
    bn, bslug = _stage(b)[:2]
    sa = stagelib.address_set(an, aslug)
    sb = stagelib.address_set(bn, bslug)
    return {
        "stage_a": an, "stage_b": bn,
        "count_a": len(sa), "count_b": len(sb),
        "only_in_a": sorted(sa - sb),
        "only_in_b": sorted(sb - sa),
        "identical": sa == sb,
    }


def size_gate(number: int, base_build: str, stage_build: str,
              write: bool = True) -> dict:
    """Measure a stage's ACHIEVED codegen class against the one it declares.

    ``base_build`` and ``stage_build`` are ``build_cohesive.sh`` output
    directories.  The result is written to the stage directory as
    ``SIZE_GATE.json`` so the claim, the measurement and the verdict are all
    part of the stage's own record rather than a number in a report.
    """
    n, slug, _desc, _mod, declared = _stage(number)
    st = stagelib.Stage(n, slug, "")

    def _elf(d):
        return os.path.join(d, "zephyr", "zephyr.elf")

    def _bin(d):
        return os.path.join(d, "zephyr", "zephyr.bin")

    doc = stagelib.size_gate(declared, _elf(base_build), _elf(stage_build),
                             _bin(base_build), _bin(stage_build))
    doc["stage"] = n
    doc["slug"] = slug
    if write:
        p = os.path.join(st.dir, "SIZE_GATE.json")
        check_write(p, st.dir)
        with open(p, "w", encoding="utf-8") as fh:
            json.dump(doc, fh, indent=1)
            fh.write("\n")
        doc["written"] = os.path.relpath(p, REPO_ROOT)
    return doc


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("status")
    m = sub.add_parser("materialize")
    m.add_argument("stage", type=int)
    c = sub.add_parser("check-addresses")
    c.add_argument("a", type=int)
    c.add_argument("b", type=int)
    sub.add_parser("input-set")
    g = sub.add_parser("size-gate", help="declared vs achieved codegen class")
    g.add_argument("stage", type=int)
    g.add_argument("base_build")
    g.add_argument("stage_build")
    args = ap.parse_args(argv)

    if args.cmd == "status":
        print(json.dumps(status(), indent=1))
    elif args.cmd == "materialize":
        print(json.dumps(materialize(args.stage), indent=1))
    elif args.cmd == "check-addresses":
        r = check_addresses(args.a, args.b)
        print(json.dumps(r, indent=1))
        return 0 if r["identical"] else 1
    elif args.cmd == "size-gate":
        r = size_gate(args.stage, args.base_build, args.stage_build)
        print(json.dumps(r, indent=1))
        return 0 if r["pass"] else 1
    elif args.cmd == "input-set":
        s = input_set.derive()
        print(json.dumps({"transformable": len(s.transformable),
                          "quarantined_protected": s.quarantined_protected,
                          "provenance": s.provenance}, indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
