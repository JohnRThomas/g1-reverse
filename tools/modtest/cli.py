"""modtest driver.

  gen   <core> <symbol>...     derive golden vectors from the SHIPPED image
  run   <core> <symbol>...     replay them against one or both trees
  grade <core> <symbol>...     mutation kill rate for the vectors
  module <core> <module>       gen+run+grade every symbol of a module

Every subcommand prints coverage.  A pass without a coverage number is not a
result in this harness.
"""

from __future__ import annotations

import argparse
import json
import os
import sys
import traceback

_HERE = os.path.dirname(os.path.abspath(__file__))
for _p in (_HERE, os.path.dirname(_HERE)):
    if _p not in sys.path:
        sys.path.insert(0, _p)

import core as mtcore                                  # noqa: E402
import generate as mtgen                               # noqa: E402
import index as mtindex                                # noqa: E402
import mutate as mtmutate                              # noqa: E402
from core import Fixture                               # noqa: E402


def _ret_kind(core, va):
    try:
        if core == "app":
            import recon_kit
            return recon_kit._ret_kind(va)
        import net_recon_kit
        return net_recon_kit._ret_kind(va)
    except Exception:                                   # noqa: BLE001
        return "i32"


def _size(core, va):
    """(size_used, ghidra_size).  See core.true_extent for why they differ."""
    sizes = mtcore.core_ctx(core)["sizes"]
    ghidra = sizes.get(va) or sizes.get(va & ~1)
    if not ghidra:
        return None, None
    return mtcore.true_extent(core, va, ghidra), ghidra


def _resolve(core, symbol, trees):
    """(va, module).  The MODULE always comes from the refactored tree.

    The canonical tree is flat, so it has no module to offer; taking its empty
    string would file every vector under "unsorted" and quietly destroy the
    module grouping the whole plan is organised around.
    """
    va = None
    module = None
    for label in ("refactored", "canonical"):
        tree = trees.get(label)
        unit = tree.unit_for(symbol) if tree else None
        if unit is None:
            continue
        for name, _raw, member_va in unit.members:
            if name != symbol:
                continue
            if va is None:
                va = member_va
            if module is None and unit.module:
                module = unit.module
                # a module is <module>[/<submodule>]; keep the top level only
    return va, module


# --------------------------------------------------------------------------

def cmd_gen(args, trees):
    core = args.core
    out = []
    for symbol in args.symbols:
        va, module = _resolve(core, symbol, trees)
        if va is None:
            print("SKIP %-40s not in any tree" % symbol)
            continue
        size, ghidra_size = _size(core, va)
        if not size:
            print("SKIP %-40s no catalogued size for 0x%x" % (symbol, va))
            continue
        ret_kind = _ret_kind(core, va)
        try:
            kept, covered, denominator, unresolved, globals_, stats = mtgen.select(
                core, va, size, ret_kind=ret_kind, nptr=args.nptr,
                budget=args.budget)
        except Exception as exc:                        # noqa: BLE001
            print("ERROR %-40s %s" % (symbol, exc))
            if args.traceback:
                traceback.print_exc()
            continue
        record = {
            "core": core, "symbol": symbol, "module": module or "unsorted",
            "va": "0x%08x" % va, "size": size,
            "ghidra_size": ghidra_size, "ret_kind": ret_kind,
            "nptr": args.nptr,
            "oracle": {"source": "shipped image",
                       "image_sha256": mtcore.image_digest(core)},
            "coverage": {"covered": len(covered), "total": len(denominator),
                         "unresolved_indirect": unresolved,
                         "ratio": round(len(covered) / max(len(denominator), 1), 4)},
            "globals": ["0x%08x" % g for g in globals_],
            "search": stats,
            "cases": [],
        }
        for fixture, state, hit in kept:
            record["cases"].append({
                "fixture": fixture,
                "expect": mtcore.observable_key(state, ret_kind),
                # Diagnostics only -- never part of the verdict.  The verdict
                # uses the sha256 of the COMPLETE trace; this bounded prefix
                # exists so a divergence localises to an event instead of to a
                # hash, which is the difference between a usable failure and an
                # unusable one.
                "events_head": [repr(e) for e in mtcore.normalise_events(
                    state.get("events", ()))[:48]],
                "call_targets": state.get("call_targets_full", []),
                "call_arities": state.get("call_arities_used_full", []),
                "call_float_arities": state.get("call_float_arities_used_full", []),
                "call_return_kinds": state.get("call_return_kinds_used_full", []),
                "new_instructions": len(hit),
            })
        path = mtcore.save_vectors(record)
        print("GEN  %-40s va=%s size=%-5d cases=%-3d cov=%d/%d (%.0f%%) "
              "globals=%d -> %s"
              % (symbol, record["va"], size, len(record["cases"]),
                 len(covered), len(denominator),
                 100 * record["coverage"]["ratio"], len(globals_),
                 os.path.relpath(path, mtcore.REPO)))
        out.append(record)
    return out


def _replay(core, symbol, tree, record, extra_cflags=None, source_override=None):
    """Replay every case against one tree.  Returns (ok, detail)."""
    va = int(record["va"], 16)
    ret_kind = record["ret_kind"]
    failures = []
    covered = set()
    for case in record["cases"]:
        fixture = Fixture(case["fixture"])
        golden = {"orig_size": record["size"],
                  "call_arities": case["call_arities"],
                  "call_float_arities": case["call_float_arities"],
                  "call_return_kinds": case["call_return_kinds"],
                  "call_targets": case["call_targets"]}
        try:
            key, hit, meta = mtcore.run_candidate(
                core, symbol, tree, va, fixture, golden, ret_kind=ret_kind,
                extra_cflags=extra_cflags, text_override=source_override)
        except RuntimeError as exc:
            return False, {"stage": "compile", "error": str(exc)[:400]}
        covered |= hit
        if key != case["expect"]:
            golden_events = case.get("events_head", [])
            got_events = [repr(e) for e in mtcore.normalise_events(
                meta["state"].get("events", ()))[:48]]
            first = next((i for i, (x, y) in
                          enumerate(zip(golden_events, got_events)) if x != y),
                         None)
            where = None
            if first is not None:
                where = {"event": first, "golden": golden_events[first][:200],
                         "candidate": got_events[first][:200]}
            elif len(golden_events) != len(got_events):
                where = {"event": min(len(golden_events), len(got_events)),
                         "golden_len": len(golden_events),
                         "candidate_len": len(got_events)}
            failures.append({"fixture": fixture["id"],
                             "expected": case["expect"], "got": key,
                             "first_divergence": where})
        elif meta["target_identity"] is not None:
            failures.append({"fixture": fixture["id"],
                             "target_identity": meta["target_identity"]})
    return (not failures), {"failures": failures[:5],
                            "n_failures": len(failures),
                            "cases": len(record["cases"]),
                            "candidate_insns": len(covered)}


def cmd_run(args, trees):
    rows = []
    for symbol in args.symbols:
        va, module = _resolve(args.core, symbol, trees)
        if va is None:
            print("SKIP %-40s not in any tree" % symbol)
            continue
        try:
            record = mtcore.load_vectors(args.core, module or "unsorted", symbol)
        except FileNotFoundError:
            print("SKIP %-40s no vectors (run `gen` first)" % symbol)
            continue
        line = ["%-40s" % symbol]
        row = {"symbol": symbol, "module": module}
        for label, tree in trees.items():
            if tree.unit_for(symbol) is None:
                line.append("%s=ABSENT" % label)
                row[label] = "absent"
                continue
            ok, detail = _replay(args.core, symbol, tree, record)
            row[label] = {"ok": ok, **detail}
            if detail.get("stage") == "compile":
                line.append("%s=CCFAIL" % label)
            else:
                line.append("%s=%s(%d/%d)" % (
                    label, "OK" if ok else "FAIL",
                    detail["cases"] - detail["n_failures"], detail["cases"]))
        line.append("cov=%.0f%%" % (100 * record["coverage"]["ratio"]))
        print("  ".join(line))
        for label in trees:
            entry = row.get(label)
            if isinstance(entry, dict) and not entry.get("ok"):
                if entry.get("stage") == "compile":
                    print("      %s compile: %s" % (label, entry["error"][:300]))
                for failure in entry.get("failures", [])[:3]:
                    print("      %s %s" % (label, json.dumps(failure)[:400]))
        rows.append(row)
    if args.json:
        with open(args.json, "w") as handle:
            json.dump(rows, handle, indent=1)
    return rows


def cmd_grade(args, trees):
    """Mutation kill rate.  A vector set that kills nothing is vacuous."""
    results = []
    for symbol in args.symbols:
        va, module = _resolve(args.core, symbol, trees)
        if va is None:
            continue
        try:
            record = mtcore.load_vectors(args.core, module or "unsorted", symbol)
        except FileNotFoundError:
            print("SKIP %-40s no vectors" % symbol)
            continue
        tree = trees[args.tree]
        unit = tree.unit_for(symbol)
        if unit is None:
            print("SKIP %-40s absent from %s" % (symbol, args.tree))
            continue
        text = unit.text
        baseline_ok, _ = _replay(args.core, symbol, tree, record)
        mutants = mtmutate.generate(text, symbol, limit=args.mutants)
        killed = survived = invalid = 0
        survivors = []
        for name, mutant in mutants:
            # The mutant is compiled from an in-memory override.  NOTHING in
            # this harness writes to a tree -- an earlier version restored the
            # file in a `finally`, which is one interrupted process away from
            # leaving a mutated source in the repository.
            ok, detail = _replay(args.core, symbol, tree, record,
                                 source_override=mutant)
            if detail.get("stage") == "compile":
                invalid += 1
            elif ok:
                survived += 1
                survivors.append(name)
            else:
                killed += 1
        total = killed + survived
        print("GRADE %-38s baseline=%s mutants=%d killed=%d survived=%d "
              "invalid=%d  kill_rate=%s"
              % (symbol, "OK" if baseline_ok else "FAIL", len(mutants),
                 killed, survived, invalid,
                 ("%.0f%%" % (100 * killed / total)) if total else "n/a"))
        if survivors:
            print("      survivors: %s" % ", ".join(survivors[:8]))
        results.append({"symbol": symbol, "baseline_ok": baseline_ok,
                        "killed": killed, "survived": survived,
                        "invalid": invalid, "survivors": survivors})
    if args.json:
        with open(args.json, "w") as handle:
            json.dump(results, handle, indent=1)
    return results


def main(argv=None):
    parser = argparse.ArgumentParser(prog="modtest")
    parser.add_argument("command", choices=("gen", "run", "grade", "index"))
    parser.add_argument("core", nargs="?", default="app")
    parser.add_argument("symbols", nargs="*")
    parser.add_argument("--module", help="expand to every symbol of a module")
    parser.add_argument("--tree", default="refactored")
    parser.add_argument("--nptr", type=int, default=2)
    parser.add_argument("--budget", type=int, default=400)
    parser.add_argument("--mutants", type=int, default=24)
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--json")
    parser.add_argument("--traceback", action="store_true")
    args = parser.parse_args(argv)

    trees = mtindex.default_trees(args.core)
    if args.module:
        tree = trees["refactored"]
        names = []
        for unit in tree.units.values():
            if unit.module != args.module:
                continue
            names.extend(name for name, _raw, _va in unit.members)
        args.symbols = sorted(set(names)) if not args.symbols else args.symbols
    if args.limit:
        args.symbols = args.symbols[:args.limit]

    if args.command == "index":
        for label, tree in trees.items():
            print("%-22s units=%5d symbols=%5d" %
                  (label, len(tree.units),
                   len([k for k in tree.by_symbol if not k.startswith("!dup:")])))
        return 0
    if args.command == "gen":
        cmd_gen(args, trees)
    elif args.command == "run":
        cmd_run(args, trees)
    elif args.command == "grade":
        cmd_grade(args, trees)
    return 0


if __name__ == "__main__":
    sys.exit(main())
