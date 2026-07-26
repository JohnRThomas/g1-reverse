#!/usr/bin/env python3
"""Measure how many of cfg_verify's directed/random negative controls BITE.

`cfg_verify.py --self-test` asserts each control FAILs, so the very first
control that does not bite aborts the whole suite and hides every one after it.
That is how two stale source anchors were able to mask the rest of the corpus.

This tool runs the same controls without asserting and reports, per control:

  BITE          the mutated source is rejected (status FAIL)  -- what we want
  VACUOUS       the mutation applies but the verdict is still PASS
  STALE-ANCHOR  the `correct` text no longer occurs in the named source
  NO-SOURCE     the named source file does not exist
  NOOP          `correct` and `wrong` produce identical text
  ERROR         the run raised

Static-only pass (`--static`) is instant and catches STALE-ANCHOR / NO-SOURCE /
NOOP; the dynamic pass runs verify() per control and is slow (hours for the
whole corpus), so `--limit`, `--list-name` and `--core` exist to shard it.
"""

import argparse
import ast
import json
import os
import sys
import time

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(BASE, "tools"))
import cfg_verify


def controls():
    """(list_name, core, function, correct, wrong) for every 3-tuple/dict control."""
    source = open(os.path.join(BASE, "tools", "cfg_verify.py")).read()
    tree = ast.parse(source)
    fn = next(n for n in ast.walk(tree)
              if isinstance(n, ast.FunctionDef) and n.name == "self_test")
    out = []
    for node in ast.walk(fn):
        if not (isinstance(node, ast.Assign) and len(node.targets) == 1
                and isinstance(node.targets[0], ast.Name)):
            continue
        name = node.targets[0].id
        if not name.endswith("negative_sources"):
            continue
        try:
            value = ast.literal_eval(node.value)
        except Exception:
            continue
        # `blocker_negative_sources` names net functions despite its name; the
        # remaining lists follow the net_/<default app> convention.
        core = "net" if (name.startswith("net_") or
                         name == "blocker_negative_sources") else "app"
        items = value.items() if isinstance(value, dict) else value
        for item in items:
            if isinstance(value, dict):
                function, pair = item
                if not (isinstance(pair, (tuple, list)) and len(pair) == 2):
                    continue
                correct, wrong = pair
            elif isinstance(item, (tuple, list)) and len(item) == 3:
                function, correct, wrong = item
            else:
                continue
            out.append((name, core, function, correct, wrong))
    return out


def classify_static(core, function, correct, wrong):
    try:
        path = cfg_verify._resolve_source_path(
            core, function, os.path.join(BASE, "recon", core, "src"))
    except Exception:
        path = None
    if not path or not os.path.exists(path):
        return "NO-SOURCE", None
    text = open(path).read()
    if correct not in text:
        return "STALE-ANCHOR", text
    if text.replace(correct, wrong, 1) == text:
        return "NOOP", text
    return None, text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--static", action="store_true")
    ap.add_argument("--list-name", default=None)
    ap.add_argument("--core", default=None)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--start", type=int, default=0)
    ap.add_argument("--json", default=None)
    args = ap.parse_args()

    rows = controls()
    if args.list_name:
        rows = [r for r in rows if r[0] == args.list_name]
    if args.core:
        rows = [r for r in rows if r[1] == args.core]
    rows = rows[args.start:]
    if args.limit:
        rows = rows[:args.limit]

    results = []
    for index, (list_name, core, function, correct, wrong) in enumerate(rows):
        verdict, text = classify_static(core, function, correct, wrong)
        if verdict is None:
            if args.static:
                verdict = "STATIC-OK"
            else:
                started = time.time()
                try:
                    # Mirror the suite's own budget per list: the `*_directed_*`
                    # lists assert with trials_random=0 (CFG-derived cases
                    # only), the rest with a small random budget.  Auditing a
                    # directed control with extra random trials can make it
                    # BITE here while the suite still sees it as vacuous, which
                    # would be a comfortable but wrong answer.
                    budget = 0 if "directed" in list_name else 8
                    out = cfg_verify.verify(
                        core, function, trials_random=budget,
                        source_override=text.replace(correct, wrong, 1))
                    if out.get("status") == "FAIL" and out.get("checked", 0) > 0:
                        verdict = "BITE"
                    elif out.get("status") == "FAIL":
                        # verify() reports FAIL when NOTHING was checked, so
                        # this control satisfies the suite's assertion while
                        # exercising nothing at all.  That is the worst kind of
                        # dead control: it looks green.
                        verdict = "VACUOUS-FAIL"
                    elif out.get("status") == "PASS":
                        verdict = "VACUOUS"
                    else:
                        verdict = "INCONCLUSIVE:" + str(out.get("status"))
                except Exception as exc:
                    verdict = "ERROR:" + type(exc).__name__
                results.append({"list": list_name, "core": core,
                                "function": function, "verdict": verdict,
                                "seconds": round(time.time() - started, 1),
                                "anchor": correct[:80]})
                print("%-6s %-32s %-22s %s" % (verdict, list_name, function,
                                               correct[:50].replace("\n", " ")),
                      flush=True)
                continue
        results.append({"list": list_name, "core": core, "function": function,
                        "verdict": verdict, "anchor": correct[:80]})
        if verdict != "STATIC-OK":
            print("%-13s %-32s %-22s %s" % (verdict, list_name, function,
                                            correct[:50].replace("\n", " ")),
                  flush=True)

    counts = {}
    for row in results:
        counts[row["verdict"]] = counts.get(row["verdict"], 0) + 1
    print("\ncontrols examined: %d" % len(results))
    for key in sorted(counts):
        print("  %-16s %d" % (key, counts[key]))
    if args.json:
        json.dump({"counts": counts, "results": results},
                  open(args.json, "w"), indent=1)
        print("wrote %s" % args.json)


if __name__ == "__main__":
    main()
