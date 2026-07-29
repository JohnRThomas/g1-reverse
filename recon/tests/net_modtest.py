#!/usr/bin/env python3
"""Net-core driver for the modtest golden-vector harness.

WHY THIS FILE EXISTS AT ALL.  `tools/modtest/cli.py` is owned by a concurrent
agent working the app core, so it must not be edited here.  It has exactly one
net-blocking defect, and this file works around it without touching it:

    index.default_trees(core) builds the "refactored" (stage 09) tree with
    modules_only=True.  That is correct for app, where stage 03 created 22
    module directories.  The NET half of every stage tree is FLAT -- 1,155
    top-level .c files at stage 00 and still 1,155 at stage 09, zero module
    directories -- so `modules_only=True` yields an index of ZERO units and
    every net symbol reports `refactored=ABSENT`.  Measured:

        $ tools/modtest/index.py net
        canonical   units= 1155 symbols= 1155 merged_units=0
        refactored  units=    0 symbols=    0 merged_units=0

    The required change is one line and is written out in
    recon/analysis/net_test_coverage.md for the owner of that file.

Everything else in the harness is genuinely core-parametric and needed no
change: `core_ctx("net")` reads netcore_image.bin through `net_extract`,
`emu.NET_CODE_BASE` maps the CPUNET flash window, `net_recon_kit._ret_kind`
supplies the ABI return kind, and `PIN_FRAGMENTS` already selects
`g1_net_globals.ld` for core == "net".

ADDRESS SPACE.  Every VA this driver handles is an ANALYSIS address
(base 0x01008000): that is what the provenance banners carry, what
`net_funcs.json` is keyed by, and what `net_extract.read` expects.  The
runtime/link base (0x01008800, delta 0x800) appears only inside the image as
stored absolute flash pointers, and `emu` already resolves those through
`net_extract.read_runtime` (tools/parity/emu.py::_firmware_readonly_extent).
This driver never converts between the two spaces, which is the only way to be
sure it cannot get the conversion wrong.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

#: HARNESS VERSION PINNING.  `tools/modtest/**` is owned by a concurrent agent
#: working the app core and was edited FOUR TIMES while this pass's vector
#: generation was in flight (core.py 22:04, cli.py 22:07, mutate.py 22:12,
#: generate.py 22:21 on 2026-07-28).  One of those edits flipped
#: `core.STACK_ARG_WINDOW` from 0 to 48, which changes what the observable key
#: contains -- so a vector generated before the edit and replayed after it
#: would compare two different things and fail for a reason that has nothing to
#: do with the reconstruction.
#:
#: So this driver imports the harness from a FIXED SNAPSHOT of the reviewed
#: version (git HEAD, commit f3dc81b9, the one recon/analysis/
#: test_architecture.md documents), taken with `git show HEAD:tools/modtest/*`.
#: Set G1_MODTEST_DIR to override; unset falls back to the live tree.
_SNAPSHOT = os.environ.get("G1_MODTEST_DIR")
MODTEST_DIR = _SNAPSHOT if (_SNAPSHOT and os.path.isdir(_SNAPSHOT)) \
    else os.path.join(REPO, "tools", "modtest")
#: 2026-07-29, pass 2: STILL NEEDED, for a different reason than the one above.
#: `core.harness_rev()` now fingerprints core/generate/cli/mutate into every
#: vector at `gen` and `cli._replay` refuses a mismatched one (`STALE-VECTOR`),
#: which does close the changed-stamp hole.  It does NOT close two others:
#:   * an UNSTAMPED vector is permitted silently (`vector_staleness` returns
#:     None when `rev` is absent) -- and all 233 net vectors inherited from
#:     pass 1 were unstamped;
#:   * `harness_rev()` is computed LAZILY from the files on disk, so a long
#:     `gen` run stamps whatever content it happened to hash first while its
#:     BEHAVIOUR is whatever it imported at start-up.
#: `tools/modtest/core.py` was edited at 05:38, 05:44 and 06:01 on 2026-07-29,
#: inside this pass's sweeps.  Pass 2 therefore pinned to `<repo>/.modtest_pin/`
#: (a COPY of tools/modtest plus symlinks to tools/*) and generated AND
#: replayed everything under it: harness_rev 936cee0b67396ca5.  See
#: net_test_coverage.md §9.  Delete the pin once tools/modtest settles, and
#: regenerate -- the vectors will then read STALE-VECTOR, which is correct.
for _p in (os.path.join(REPO, "tools"), MODTEST_DIR):
    if _p not in sys.path:
        sys.path.insert(0, _p)

import cli as mtcli                      # noqa: E402  tools/modtest/cli.py
import core as mtcore                    # noqa: E402
import index as mtindex                  # noqa: E402

MANIFEST = os.path.join(REPO, "recon", "ownership", "adoption_manifest.json")

#: Name-prefix -> subsystem.  Applied FIRST, because a human name in this tree
#: was assigned from recovered evidence (recon/catalogs/function_names_net.json)
#: and is stronger than a component label that covers a whole archive.
_PREFIX = (
    ("controller_", "controller"),
    ("schedule_", "controller"),
    ("radio_", "radio"),
    ("rtc_", "controller"),
    ("sdc_", "sdc"),
    ("ocrypto_", "crypto"),
    ("ipc_", "ipc"),
    ("rpmsg", "ipc"),
    ("mpsl_", "mpsl"),
    ("esb_", "esb"),
    ("thunk_", "thunk"),
    ("ble_", "sdc"),
)
#: Manifest component -> subsystem, for files with no recovered name.
_COMPONENT = {
    "softdevice_controller": "sdc",
    "net_sdk_or_glue": "glue",
    "zephyr_ipc_rpmsg_variant": "ipc",
}


def ownership():
    """(retained, excluded, name_by_va) derived from the manifest itself.

    `retained`  -- sources the build COMPILES from our reconstruction.
    `excluded`  -- sources the manifest adopts byte-exact from an upstream
                   archive instead (`exclude_reconstruction: true`), i.e. stock
                   SDK/Zephyr code that is not ours to restructure.

    This is re-derived here rather than parsed out of
    recon/generated/net_retained_sources.cmake, because that file's header line
    is easy to misread: its "matched sources: 232" counts the EXCLUSIONS that
    matched a source file, not the recovered sources.  923 of 1,155 net sources
    are retained.
    """
    with open(MANIFEST) as handle:
        rows = json.load(handle)["cores"]["net"]["entries"]
    excluded_va = {int(r["va"], 16) & ~1 for r in rows
                   if r.get("exclude_reconstruction")}
    component = {int(r["va"], 16) & ~1: r.get("component") for r in rows}
    return excluded_va, component


def subsystem(symbol, va, excluded_va, component):
    if va in excluded_va:
        return "stock"
    for prefix, module in _PREFIX:
        if symbol.startswith(prefix):
            return module
    return _COMPONENT.get(component.get(va), "unsorted")


def net_trees():
    """Both stage trees, indexed FLAT (the net half has no module dirs)."""
    excluded_va, component = ownership()
    trees = {}
    for label, stage in (("canonical", "stage_00_snapshot"),
                         ("refactored", "stage_09_call_cohesion")):
        tree = mtindex.build(os.path.join(REPO, "recon/refactor", stage, "tree"),
                             core="net", name="%s(%s)" % (label, stage),
                             modules_only=False)
        # Give every flat unit the subsystem bucket its vectors are filed
        # under.  `cli._resolve` reads `unit.module`, so this makes
        # `--module <m>` selection and the vector directory layout work
        # unchanged, with no edit to tools/modtest.
        for unit in tree.units.values():
            if not unit.members:
                continue
            symbol, _raw, va = unit.members[0]
            unit.module = subsystem(symbol, va & ~1, excluded_va, component)
        trees[label] = tree
    return trees


def census(trees):
    excluded_va, component = ownership()
    tree = trees["canonical"]
    rows = []
    for unit in tree.units.values():
        for symbol, raw, va in unit.members:
            rows.append((symbol, raw, va & ~1, unit.module,
                         component.get(va & ~1) or "<no manifest row>"))
    return rows, excluded_va


def main(argv=None):
    parser = argparse.ArgumentParser(prog="net_modtest")
    parser.add_argument("command",
                        choices=("gen", "run", "grade", "index", "census"))
    parser.add_argument("symbols", nargs="*")
    parser.add_argument("--module")
    parser.add_argument("--tree", default="refactored")
    #: -1 = DERIVE the pointer-argument mask from the shipped instructions
    #: (generate.pointer_arg_mask, landed in tools/modtest after the previous
    #: net pass).  The old default of 2 is what net_test_coverage.md §6.2
    #: measured as wrong in BOTH directions -- it made
    #: `ocrypto_constant_time_is_zero`'s length parameter a pointer and its
    #: countdown loop then hit the 200,000-instruction cap on 100 % of
    #: candidates.  Derived is now the default; pass --nptr 2 to reproduce the
    #: old behaviour for comparison.
    parser.add_argument("--nptr", type=int, default=-1)
    parser.add_argument("--budget", type=int, default=400)
    parser.add_argument("--mutants", type=int, default=16)
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--shard", default="")       # "i/n"
    parser.add_argument("--json")
    parser.add_argument("--traceback", action="store_true")
    args = parser.parse_args(argv)
    args.core = "net"

    trees = net_trees()

    if args.command == "index":
        for label, tree in trees.items():
            print("%-28s units=%5d symbols=%5d" %
                  (label, len(tree.units), len(tree.by_symbol)))
        return 0
    if args.command == "census":
        rows, excluded_va = census(trees)
        import collections
        by_module = collections.Counter(r[3] for r in rows)
        by_component = collections.Counter(r[4] for r in rows)
        print("net symbols indexed: %d" % len(rows))
        print("manifest exclusions matching a source (STOCK): %d" %
              sum(1 for r in rows if r[2] in excluded_va))
        print("\n-- subsystem bucket --")
        for key, value in by_module.most_common():
            print("   %-14s %5d" % (key, value))
        print("\n-- manifest component --")
        for key, value in by_component.most_common():
            print("   %-34s %5d" % (key, value))
        if args.json:
            with open(args.json, "w") as handle:
                json.dump([{"symbol": s, "raw": r, "va": "0x%08x" % v,
                            "module": m, "component": c,
                            "stock": v in excluded_va}
                           for s, r, v, m, c in rows], handle, indent=1)
        return 0

    if args.module:
        names = []
        for unit in trees["refactored"].units.values():
            if unit.module != args.module:
                continue
            names.extend(name for name, _raw, _va in unit.members)
        if not args.symbols:
            args.symbols = sorted(set(names))
    if args.shard:
        i, n = (int(x) for x in args.shard.split("/"))
        args.symbols = [s for k, s in enumerate(sorted(args.symbols))
                        if k % n == i]
    if args.limit:
        args.symbols = args.symbols[:args.limit]

    if args.command == "gen":
        mtcli.cmd_gen(args, trees)
    elif args.command == "run":
        mtcli.cmd_run(args, trees)
    elif args.command == "grade":
        mtcli.cmd_grade(args, trees)
    return 0


if __name__ == "__main__":
    sys.exit(main())
