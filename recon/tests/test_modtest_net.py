#!/usr/bin/env python3
"""Net-core executable suite: positive replay, tree agreement, negative controls.

Run:
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_net.py
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_net.py --probe 40
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_net.py --shard 0/6

This is the net twin of `recon/tests/test_modtest_pilot.py` and deliberately
reuses that file's three negative-control corruptions and its `replay`, so the
two cores are graded by the same code.  It differs in exactly two ways, both
forced by the net core rather than chosen:

  1. the trees come from `recon/tests/net_modtest.py::net_trees`, which indexes
     the net half of each stage tree FLAT.  `index.default_trees` builds the
     stage-09 tree with `modules_only=True` and therefore yields ZERO net units
     (see recon/analysis/net_test_coverage.md §1.2);
  2. the negative-control probe is not capped at six symbols.  A suite whose
     anti-vacuity evidence is six symbols out of ~300 is not evidence; this
     runs every symbol that qualifies, up to `--probe`.

A control that never applied is printed as `n/a`, never skipped silently.
"""

import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO, "recon", "tests"))
sys.path.insert(0, os.path.join(REPO, "tools"))

# net_modtest resolves and pins the harness version (see its MODTEST_DIR note);
# import it FIRST so `mutate` / `core` come from the same snapshot the vectors
# were generated with, not from a tree a concurrent agent is editing.
import net_modtest                                 # noqa: E402
sys.path.insert(0, net_modtest.MODTEST_DIR)

import mutate as mtmutate                          # noqa: E402
import test_modtest_pilot as pilot                 # noqa: E402


def main(argv):
    probe_limit = 24
    shard = None
    for index, arg in enumerate(argv):
        if arg == "--probe":
            probe_limit = int(argv[index + 1])
        elif arg == "--shard":
            shard = tuple(int(x) for x in argv[index + 1].split("/"))
    trees = net_modtest.net_trees()
    records = pilot.load("net")
    records.sort(key=lambda r: r["symbol"])
    if shard:
        records = [r for i, r in enumerate(records) if i % shard[1] == shard[0]]
    print("vectors: %d symbols" % len(records))

    failures = []
    agree = disagree = absent = 0
    covered = total = 0
    for record in records:
        covered += record["coverage"]["covered"]
        total += record["coverage"]["total"]
        results = {}
        for label, tree in trees.items():
            if tree.unit_for(record["symbol"]) is None:
                results[label] = None
                continue
            bad, cases = pilot.replay(record, tree, stop_on_first=False)
            results[label] = (bad, cases)
            if bad:
                failures.append((record["symbol"], label, bad, cases))
        pair = [v for v in results.values() if v is not None]
        if len(pair) < 2:
            absent += 1
        elif pair[0][0] == pair[1][0]:
            agree += 1
        else:
            disagree += 1
            print("  TREE DISAGREEMENT %s: %s" % (record["symbol"], results))
    print("POSITIVE: %d symbols, %d failing (symbol,tree) pairs, "
          "trees agree on %d, disagree on %d, absent-from-one %d"
          % (len(records), len(failures), agree, disagree, absent))
    print("COVERAGE: %d/%d shipped CFG instructions = %.1f%%"
          % (covered, total, 100.0 * covered / max(total, 1)))
    for symbol, label, bad, cases in failures:
        print("  FAIL %-40s %-34s %d/%d" % (symbol, label, bad, cases))

    probe = [r for r in records
             if r["coverage"]["ratio"] >= 0.9 and len(r["cases"]) >= 3]
    probe = probe[:probe_limit]
    print("\nNEGATIVE CONTROLS on %d symbols (>=90%% coverage, >=3 fixtures)"
          % len(probe))
    unkilled = []
    killed = inapplicable = 0
    for record in probe:
        tree = trees["refactored"]
        unit = tree.unit_for(record["symbol"])
        if unit is None:
            continue
        text = unit.text
        span = mtmutate.member_span(text, record["symbol"])
        low, high = span if span else (0, len(text))
        for name, corrupt in pilot.NEGATIVE_CONTROLS:
            mutant = corrupt(text, low, high)
            if mutant is None or mutant == text:
                inapplicable += 1
                print("  n/a      %-40s %s" % (record["symbol"], name))
                continue
            bad, cases = pilot.replay(record, tree, source_override=mutant)
            if bad:
                killed += 1
                print("  killed   %-40s %-16s (%d/%d)"
                      % (record["symbol"], name, bad, cases))
            else:
                unkilled.append((record["symbol"], name))
                print("  SURVIVED %-40s %-16s <-- vectors do not see this"
                      % (record["symbol"], name))
    print("negative controls: %d killed, %d survived, %d not applicable"
          % (killed, len(unkilled), inapplicable))
    return 1 if (failures or unkilled or disagree) else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
