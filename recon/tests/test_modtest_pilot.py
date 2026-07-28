"""Executable pilot suite + harness self-tests.

Run:
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_pilot.py
    PYTHONSAFEPATH=1 .venv/bin/python recon/tests/test_modtest_pilot.py --quick

WHAT THIS FILE IS FOR.  `tools/modtest/cli.py run` replays the vectors; this
file is the part that must exist so the suite is not self-certifying:

  * POSITIVE controls -- the vectors pass against both trees;
  * NEGATIVE controls -- a deliberately corrupted candidate must FAIL.  Every
    negative control below is asserted to fail; if the harness ever stops
    catching one, this file breaks.  Four fixtures in this project have passed
    vacuously (AGENTS.md), and the only defence that has ever worked here is an
    executed negative control rather than a stated intention.
"""

import json
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO, "tools", "modtest"))
sys.path.insert(0, os.path.join(REPO, "tools"))

import core as mtcore          # noqa: E402
import index as mtindex        # noqa: E402
import mutate as mtmutate      # noqa: E402
from core import Fixture       # noqa: E402

VECTORS = os.path.join(REPO, "recon", "tests", "vectors")


def load(core="app"):
    out = []
    root = os.path.join(VECTORS, core)
    for module in sorted(os.listdir(root)) if os.path.isdir(root) else []:
        path = os.path.join(root, module)
        if not os.path.isdir(path):
            continue
        for name in sorted(os.listdir(path)):
            if name.endswith(".json"):
                with open(os.path.join(path, name)) as handle:
                    out.append(json.load(handle))
    return out


def replay(record, tree, source_override=None, stop_on_first=True):
    """(failures, cases).  A compile failure counts as a total failure."""
    va = int(record["va"], 16)
    failures = 0
    for case in record["cases"]:
        golden = {"orig_size": record["size"],
                  "call_arities": case["call_arities"],
                  "call_float_arities": case["call_float_arities"],
                  "call_return_kinds": case["call_return_kinds"],
                  "call_targets": case["call_targets"]}
        try:
            key, _cov, meta = mtcore.run_candidate(
                record["core"], record["symbol"], tree, va,
                Fixture(case["fixture"]), golden, ret_kind=record["ret_kind"],
                text_override=source_override)
        except RuntimeError:
            return len(record["cases"]), len(record["cases"])
        if key != case["expect"] or meta["target_identity"] is not None:
            failures += 1
            if stop_on_first:
                return failures, len(record["cases"])
    return failures, len(record["cases"])


# --------------------------------------------------------------------------
# NEGATIVE CONTROLS.  Each is a specific, realistic defect class; each MUST
# be caught.  `None` means "no such site in this source", which is reported
# rather than silently skipped -- a control that never applied is not a
# control, and this project has shipped two of those.
# --------------------------------------------------------------------------

def _corrupt_return_constant(text, low, high):
    """Turn one `return <expr>;` into `return 0;` -- wrong result."""
    index = text.find("return ", low)
    if index < 0 or index >= high:
        return None
    end = text.find(";", index)
    if end < 0 or end > high or text[index:end].strip() == "return 0":
        return None
    return text[:index] + "return 0" + text[end:]


def _drop_last_call(text, low, high):
    """Delete the last statement that is a bare call -- a dropped side effect."""
    lines = text.split("\n")
    offset = 0
    bounds = []
    for line in lines:
        bounds.append(offset)
        offset += len(line) + 1
    for index in range(len(lines) - 1, -1, -1):
        if not (low <= bounds[index] < high):
            continue
        stripped = lines[index].strip()
        if (stripped.endswith(");") and "(" in stripped and
                "=" not in stripped and
                not stripped.startswith(("extern", "static", "if", "while",
                                         "for", "return", "*", "#", "/"))):
            return "\n".join(lines[:index] + lines[index + 1:])
    return None


def _flip_first_comparison(text, low, high):
    for old, new in ((" == ", " != "), (" != ", " == "), (" < ", " >= "),
                     (" > ", " <= ")):
        index = text.find(old, low)
        if low <= index < high:
            return text[:index] + new + text[index + len(old):]
    return None


NEGATIVE_CONTROLS = (("return-constant", _corrupt_return_constant),
                     ("drop-call", _drop_last_call),
                     ("flip-comparison", _flip_first_comparison))


def main(argv):
    quick = "--quick" in argv
    trees = mtindex.default_trees("app")
    records = load("app")
    if quick:
        records = [r for r in records if len(r["cases"]) <= 8 or
                   r["symbol"] in ("opt3001_read_lux_raw", "floorf",
                                   "ipc_read_u16_field")]
    print("vectors: %d symbols" % len(records))

    failures = []
    agree = disagree = 0
    covered = total = 0
    for record in records:
        covered += record["coverage"]["covered"]
        total += record["coverage"]["total"]
        results = {}
        for label, tree in trees.items():
            if tree.unit_for(record["symbol"]) is None:
                results[label] = None
                continue
            bad, cases = replay(record, tree, stop_on_first=False)
            results[label] = (bad, cases)
            if bad:
                failures.append((record["symbol"], label, bad, cases))
        pair = [v for v in results.values() if v is not None]
        if len(pair) == 2:
            if pair[0][0] == pair[1][0]:
                agree += 1
            else:
                disagree += 1
                print("  TREE DISAGREEMENT %s: %s" % (record["symbol"], results))
    print("POSITIVE: %d symbols, %d failing pairs, trees agree on %d, "
          "disagree on %d" % (len(records), len(failures), agree, disagree))
    print("COVERAGE: %d/%d shipped CFG instructions = %.1f%%"
          % (covered, total, 100.0 * covered / max(total, 1)))
    for symbol, label, bad, cases in failures:
        print("  FAIL %-38s %-12s %d/%d" % (symbol, label, bad, cases))

    # ---- negative controls -------------------------------------------------
    probe = [r for r in records
             if r["coverage"]["ratio"] >= 0.9 and len(r["cases"]) >= 3][:6]
    print("\nNEGATIVE CONTROLS on %d symbols" % len(probe))
    unkilled = []
    inapplicable = 0
    for record in probe:
        tree = trees["refactored"]
        unit = tree.unit_for(record["symbol"])
        if unit is None:
            continue
        text = unit.text
        # A merged TU holds up to 39 functions.  A control that corrupts a
        # SIBLING cannot be killed by this symbol's vectors and would be
        # reported as a blind spot that does not exist -- the same defect that
        # graded `ipc_read_u16_field` at 0/16 before it was found.
        span = mtmutate.member_span(text, record["symbol"])
        low, high = span if span else (0, len(text))
        for name, corrupt in NEGATIVE_CONTROLS:
            mutant = corrupt(text, low, high)
            if mutant is None or mutant == text:
                inapplicable += 1
                print("  n/a    %-34s %s" % (record["symbol"], name))
                continue
            bad, cases = replay(record, tree, source_override=mutant)
            if bad:
                print("  killed %-34s %s (%d/%d)"
                      % (record["symbol"], name, bad, cases))
            else:
                unkilled.append((record["symbol"], name))
                print("  SURVIVED %-32s %s  <-- vectors do not see this"
                      % (record["symbol"], name))
    print("negative controls: %d survived, %d not applicable"
          % (len(unkilled), inapplicable))
    return 1 if (failures or unkilled or disagree) else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
