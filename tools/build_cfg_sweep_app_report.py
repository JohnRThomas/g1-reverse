#!/usr/bin/env python3
"""Build the durable CPUAPP authoritative CFG-sweep checkpoint."""

import argparse
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SNAPSHOT = ROOT / "recon/analysis/cfg_sweep_app_baseline_lanes.json"
NET_SNAPSHOT = ROOT / "recon/analysis/cfg_sweep_net_baseline_lanes.json"
RECHECKS = ROOT / "recon/analysis/cfg_sweep_target_rechecks.json"
OUT_JSON = ROOT / "recon/analysis/cfg_sweep_authoritative_app.json"
OUT_MD = ROOT / "recon/analysis/cfg_sweep_authoritative_app.md"
BUCKETS = (
    "PASS", "FAIL", "compile_error", "other", "timeout",
    "source_changed",
)
PROOF_TOOLS = (
    "tools/cfg_verify.py", "tools/parity/emu.py", "tools/parity/recon.py",
)
RECHECK_TOOL_HASHES = {
    "tools/cfg_verify.py":
        "ded92059545200309d0eeaf0140b49164c9fffa0c9748e2c579b17e361aa61d8",
    "tools/parity/emu.py":
        "e8f650559fe3d1dd9f907b01a469072de8b6e17fb34963659c5bef255ce1d0bd",
    "tools/parity/recon.py":
        "22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2",
}


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")
    ).encode()).hexdigest()


def load_snapshot(path, core):
    data = json.loads(path.read_text())
    if (data.get("schema") != 1 or data.get("core") != core or
            data.get("kind") != "cfg_sweep_lane_snapshot"):
        raise ValueError("invalid CFG lane snapshot: %s" % path)
    return data


def baseline_functions(snapshot):
    functions = {}
    tool_sets = []
    for lane in range(8):
        receipt = snapshot["lanes"][str(lane)]["receipt"]
        if (receipt.get("_shard_count") != 8 or
                receipt.get("_shard_index") != lane):
            raise ValueError("invalid app lane %d" % lane)
        tool_sets.append(receipt["_tool_hashes"])
        source_hashes = receipt.get("_source_hashes", {})
        for status in BUCKETS:
            for name in receipt.get(status, []):
                if name in functions:
                    raise ValueError("duplicate app verdict: %s" % name)
                if name not in source_hashes:
                    raise ValueError("missing source hash: %s" % name)
                functions[name] = {
                    "name": name, "lane": lane,
                    "source_sha256": source_hashes[name],
                    "baseline_status": status,
                    "status": status,
                }
    if len(functions) != snapshot["inventory_count"]:
        raise ValueError("app snapshot coverage is incomplete")
    return functions, tool_sets


def selected_recheck(functions):
    data = json.loads(RECHECKS.read_text())
    key = "app:FUN_00081e2a"
    receipt = data["rechecks"].get(key)
    if receipt is None:
        raise ValueError("missing compile-error target recheck")
    row = functions["FUN_00081e2a"]
    if (row["baseline_status"] != "compile_error" or
            receipt.get("source_sha256") != row["source_sha256"] or
            receipt.get("status") != "PASS"):
        raise ValueError("stale compile-error target recheck")
    if receipt.get("tool_hashes") != RECHECK_TOOL_HASHES:
        raise ValueError("compile-error recheck tool drift")
    row["status"] = "PASS"
    row["history"] = {
        "baseline_status": "compile_error",
        "recheck_status": "PASS",
        "recheck_result": receipt["result"],
        "recheck_tool_hashes": receipt["tool_hashes"],
    }
    return {"key": key, "receipt": receipt,
            "receipt_digest": digest_json(receipt)}


def assert_current_sources(functions):
    source_dir = ROOT / "recon/app/src"
    current = {path.stem: sha256(path) for path in source_dir.glob("*.c")}
    expected = {name: row["source_sha256"]
                for name, row in functions.items()}
    if current != expected:
        changed = sorted(name for name in set(current) | set(expected)
                         if current.get(name) != expected.get(name))
        raise ValueError("CPUAPP source tree changed: %r" % changed)


def build(require_current=True):
    snapshot = load_snapshot(SNAPSHOT, "app")
    functions, lane_tools = baseline_functions(snapshot)
    recheck = selected_recheck(functions)
    if require_current:
        assert_current_sources(functions)
    ordered = [functions[name] for name in sorted(functions)]
    by_status = {
        status: [row["name"] for row in ordered if row["status"] == status]
        for status in BUCKETS
    }
    baseline_by_status = {
        status: [row["name"] for row in ordered
                 if row["baseline_status"] == status]
        for status in BUCKETS
    }
    net = load_snapshot(NET_SNAPSHOT, "net")
    inventory = [[row["name"], row["source_sha256"]] for row in ordered]
    return {
        "schema": 1,
        "kind": "authoritative_cfg_directed_side_effect_sweep",
        "core": "app",
        "inventory_count": len(ordered),
        "inventory_digest": digest_json(inventory),
        "function_name_digest": digest_json([row["name"] for row in ordered]),
        "source_tree_match_verified_at_generation": True,
        "lane_snapshot": {
            "path": str(SNAPSHOT.relative_to(ROOT)),
            "sha256": sha256(SNAPSHOT),
            "baseline_counts": snapshot["counts"],
            "tool_hashes": lane_tools,
        },
        "target_rechecks": [recheck],
        "baseline_counts": {status: len(baseline_by_status[status])
                            for status in BUCKETS},
        "counts": {status: len(by_status[status]) for status in BUCKETS},
        "baseline_by_status": baseline_by_status,
        "by_status": by_status,
        "functions": ordered,
        "unresolved_count": sum(len(by_status[status]) for status in BUCKETS
                                if status != "PASS"),
        "compile_error_triage": {
            "name": "FUN_00081e2a",
            "baseline_status": "compile_error",
            "runner_limitation": (
                "The original lane runner retained the status but discarded "
                "cfg_verify subprocess stdout/stderr."
            ),
            "reproduced_exact_stale_entry_error": (
                "symbol FUN_00081e2a not found after link"
            ),
            "cause": (
                "The body defines readable symbol att_chan_read; compiling "
                "with the stale raw entry name fails at post-link lookup."
            ),
            "current_readable_entry_compile": "PASS",
            "authoritative_cfg_recheck": "PASS",
        },
        "net_baseline": {
            "state": "historical_not_current",
            "reason": (
                "CPUNET canonical inventory grew after this 998-function "
                "baseline; root will rerun it after active net shards freeze."
            ),
            "path": str(NET_SNAPSHOT.relative_to(ROOT)),
            "sha256": sha256(NET_SNAPSHOT),
            "inventory_count": net["inventory_count"],
            "counts": net["counts"],
        },
    }


def markdown(data):
    c = data["counts"]
    b = data["baseline_counts"]
    lines = [
        "# Authoritative CPUAPP CFG sweep", "",
        "This checkpoint covers every canonical CPUAPP function source in the "
        "frozen 2,113-function inventory and binds each verdict to its exact "
        "source SHA-256.", "",
        "- Inventory digest: `%s`" % data["inventory_digest"],
        "- Baseline: %d PASS, %d FAIL, %d compile error, %d other, %d timeout"
        % (b["PASS"], b["FAIL"], b["compile_error"], b["other"],
           b["timeout"]),
        "- Current overlay: %d PASS, %d FAIL, %d compile error, %d other, %d "
        "timeout" % (c["PASS"], c["FAIL"], c["compile_error"], c["other"],
                     c["timeout"]),
        "- Unresolved: **%d**" % data["unresolved_count"], "",
        "## Confirmed FAIL", "",
    ]
    lines += ["- `%s`" % name for name in data["by_status"]["FAIL"]]
    lines += ["", "## Compile-error triage", "",
              "`FUN_00081e2a` was classified as a compile error by the lane. "
              "The runner did not retain stderr. Reproduction with the stale "
              "raw entry name yields exactly:", "",
              "```text", data["compile_error_triage"][
                  "reproduced_exact_stale_entry_error"], "```", "",
              "The same unchanged source compiles as `att_chan_read` and now "
              "passes authoritative CFG verification; the baseline verdict "
              "remains preserved in the machine report.", "",
              "## Timeout and verifier-error identities", ""]
    lines += ["- timeout: `%s`" % name
              for name in data["by_status"]["timeout"]]
    lines += ["- other: `%s`" % name
              for name in data["by_status"]["other"]]
    lines += ["", "## CPUNET status", "",
              "The preserved 998-function CPUNET receipt is explicitly "
              "historical, not current. Its canonical inventory grew while "
              "net repair shards were active; a new net sweep is deferred "
              "until that source tree freezes.", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build(require_current=True)
    outputs = {
        OUT_JSON: json.dumps(data, indent=1, sort_keys=True) + "\n",
        OUT_MD: markdown(data),
    }
    for path, content in outputs.items():
        old = path.read_text() if path.exists() else None
        if args.check and old != content:
            raise ValueError("stale CPUAPP CFG report: %s" % path)
        if not args.check and old != content:
            path.write_text(content)
    print(json.dumps({"counts": data["counts"],
                      "unresolved": data["unresolved_count"]},
                     sort_keys=True))


if __name__ == "__main__":
    main()
