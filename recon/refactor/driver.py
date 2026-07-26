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
STAGES = [
    (0, "snapshot", "verbatim snapshot of the compilable input set (identity transform)",
     "t00_snapshot"),
    (1, "literal_inline", "inline byte-verified .rodata string literals whose every "
     "live reference is a string-consuming call argument, withdrawing the backing "
     "object, its PROVIDE pin and its extern declaration in the same transaction",
     "t01_literal_inline"),
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
    for n, slug, desc, mod in STAGES:
        if n == number:
            return n, slug, desc, mod
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
    n, slug, desc, modname = _stage(number)
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
        pn, pslug, _, _ = _stage(n - 1)
        prev = stagelib.Stage(pn, pslug, "")
        prev_man = stagelib.load_manifest(pn, pslug)
        if prev_man is None:
            raise SystemExit("stage %d must be materialized before stage %d" % (pn, n))
        source_root = prev.tree
        relpaths = sorted(prev_man["files"])
        iset = None
        input_stage = {"stage": pn, "slug": pslug,
                       "tree": os.path.relpath(prev.tree, REPO_ROOT)}

    summary = mod.run(stage, source_root, relpaths)

    extra = {"input_stage": input_stage}
    if iset is not None:
        extra["input_provenance"] = iset.provenance
        extra["quarantined_protected_build_inputs"] = iset.quarantined_protected
    extra.update(summary.get("manifest_extra", {}))
    stage.write_manifest(extra)
    rows = stagelib.parity_rows(stage.tree, sorted(stage.files))
    stage.write_parity_map(rows, summary.get("parity_extra"))
    return {"stage": n, "slug": slug, "files": len(stage.files),
            "parity_rows": len(rows), **summary.get("report", {})}


def status() -> list[dict]:
    out = []
    for n, slug, desc, _ in STAGES:
        out.append(stagelib.staleness(n, slug))
    return out


def check_addresses(a: int, b: int) -> dict:
    an, aslug, _, _ = _stage(a)
    bn, bslug, _, _ = _stage(b)
    sa = stagelib.address_set(an, aslug)
    sb = stagelib.address_set(bn, bslug)
    return {
        "stage_a": an, "stage_b": bn,
        "count_a": len(sa), "count_b": len(sb),
        "only_in_a": sorted(sa - sb),
        "only_in_b": sorted(sb - sa),
        "identical": sa == sb,
    }


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
    args = ap.parse_args(argv)

    if args.cmd == "status":
        print(json.dumps(status(), indent=1))
    elif args.cmd == "materialize":
        print(json.dumps(materialize(args.stage), indent=1))
    elif args.cmd == "check-addresses":
        r = check_addresses(args.a, args.b)
        print(json.dumps(r, indent=1))
        return 0 if r["identical"] else 1
    elif args.cmd == "input-set":
        s = input_set.derive()
        print(json.dumps({"transformable": len(s.transformable),
                          "quarantined_protected": s.quarantined_protected,
                          "provenance": s.provenance}, indent=1))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
