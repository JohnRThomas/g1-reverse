#!/usr/bin/env python3
"""Build the durable final CPUNET CFG-sweep report."""

import gzip
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SNAPSHOT = ROOT / "recon/analysis/cfg_sweep_net_final_lanes.json"
OUT_JSON = ROOT / "recon/analysis/cfg_sweep_authoritative_net.json"
OUT_MD = ROOT / "recon/analysis/cfg_sweep_authoritative_net.md"
CATALOG = ROOT / "recon/catalogs/net_funcs.json.gz"
BUCKETS = ("PASS", "FAIL", "compile_error", "other", "timeout",
           "source_changed")
RECEIPTS = {
    "FUN_0100ef08": "recon/ownership/net_private_shard8_recovery.json",
    "FUN_01011664": "recon/ownership/net_private_7_recovery.json",
    "FUN_01014b18": "recon/ownership/net_private_shard1.json",
    "FUN_01018df8": "recon/ownership/net_private_7_recovery.json",
    "FUN_0101d890": "recon/analysis/net_private3_recovery_receipt.json",
    "FUN_0102665c": "recon/ownership/net_private_shard8_recovery.json",
    "FUN_010292ec": "recon/ownership/net_private_shard8_recovery.json",
    "FUN_0102a1e0": "recon/ownership/net_private_shard8_recovery.json",
}
POST_SWEEP_REPAIR_DRIFT = [
    "FUN_01009bc4", "FUN_01009c68", "FUN_010313ec",
    "FUN_01033888", "FUN_01033b18", "FUN_0103499c",
]


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")
    ).encode()).hexdigest()


def build():
    snapshot = json.loads(SNAPSHOT.read_text())
    if (snapshot.get("schema") != 1 or snapshot.get("core") != "net" or
            snapshot.get("kind") != "cfg_sweep_lane_snapshot"):
        raise ValueError("invalid final CPUNET lane snapshot")

    functions = {}
    tool_hashes = None
    inventory_digest = None
    core_inventory_digest = None
    for lane in range(8):
        receipt = snapshot["lanes"][str(lane)]["receipt"]
        if (receipt.get("_shard_count") != 8 or
                receipt.get("_shard_index") != lane):
            raise ValueError("invalid lane identity %d" % lane)
        if tool_hashes is None:
            tool_hashes = receipt["_tool_hashes"]
            inventory_digest = receipt["_inventory_digest"]
            core_inventory_digest = receipt["_core_inventory_digest"]
        elif (receipt["_tool_hashes"] != tool_hashes or
              receipt["_inventory_digest"] != inventory_digest or
              receipt["_core_inventory_digest"] != core_inventory_digest):
            raise ValueError("lane input/tool drift")
        hashes = receipt.get("_source_hashes", {})
        for status in BUCKETS:
            for name in receipt.get(status, []):
                if name in functions:
                    raise ValueError("duplicate verdict: %s" % name)
                if status != "source_changed" and name not in hashes:
                    raise ValueError("missing source hash: %s" % name)
                functions[name] = {
                    "name": name,
                    "lane": lane,
                    "status": status,
                    "source_sha256": hashes.get(name),
                }

    source_dir = ROOT / "recon/net/src"
    if len(functions) != snapshot["inventory_count"]:
        raise ValueError("incomplete final CPUNET inventory")

    with gzip.open(CATALOG, "rt") as fp:
        catalog = json.load(fp)
    catalog_vas = {int(row["entry"]) for row in catalog["functions"]}
    other = sorted(name for name, row in functions.items()
                   if row["status"] == "other")
    missed = []
    for name in other:
        first = (source_dir / (name + ".c")).read_text().splitlines()[0]
        marker = first.split("@", 1)[1].strip().split()[0].rstrip(".,")
        va = int(marker, 16)
        if va in catalog_vas:
            raise ValueError("OTHER unexpectedly present in net catalog: %s" % name)
        receipt_path = ROOT / RECEIPTS[name]
        if name not in receipt_path.read_text():
            raise ValueError("dedicated receipt does not name %s" % name)
        missed.append({
            "name": name,
            "address": "0x%08x" % va,
            "reason": "absent_from_net_funcs_catalog",
            "dedicated_receipt": RECEIPTS[name],
            "dedicated_receipt_sha256": sha256(receipt_path),
        })

    ordered = [functions[name] for name in sorted(functions)]
    by_status = {status: [row["name"] for row in ordered
                          if row["status"] == status]
                 for status in BUCKETS}
    counts = {status: len(by_status[status]) for status in BUCKETS}
    if counts != snapshot["counts"]:
        raise ValueError("snapshot aggregate mismatch")
    source_inventory = [[row["name"], row["source_sha256"]]
                        for row in ordered]
    if digest_json(source_inventory) != core_inventory_digest:
        raise ValueError("source inventory digest mismatch")

    return {
        "schema": 1,
        "kind": "authoritative_cfg_directed_side_effect_sweep",
        "core": "net",
        "verifier_commits": ["30340066", "3de1cf81"],
        "inventory_count": len(ordered),
        "source_inventory_digest": core_inventory_digest,
        "combined_app_net_inventory_digest": inventory_digest,
        "function_name_digest": digest_json([row["name"] for row in ordered]),
        "source_tree_unchanged_during_each_verdict": True,
        "post_sweep_repair_drift_observed_before_commit": (
            POST_SWEEP_REPAIR_DRIFT
        ),
        "lane_snapshot": {
            "path": str(SNAPSHOT.relative_to(ROOT)),
            "sha256": sha256(SNAPSHOT),
        },
        "tool_hashes": tool_hashes,
        "counts": counts,
        "unresolved_count": sum(counts[s] for s in BUCKETS if s != "PASS"),
        "by_status": by_status,
        "catalog_missed": missed,
        "coverage_note": (
            "The generic CFG sweep inventories every canonical source, but "
            "cannot derive original size/CFG for sources absent from the "
            "net_funcs catalog. Those eight entries are fail-closed as OTHER; "
            "their dedicated reconstruction receipts are mapped here and are "
            "not promoted to generic-sweep PASS."
        ),
        "drift_note": (
            "Six failing sources were repaired after their frozen lane "
            "verdicts and before this baseline was committed. Their baseline "
            "FAIL verdicts and pre-repair source hashes remain unchanged here; "
            "repair rechecks must be captured as separate overlay receipts."
        ),
        "functions": ordered,
    }


def markdown(data):
    c = data["counts"]
    lines = [
        "# Authoritative CPUNET CFG sweep", "",
        "This checkpoint binds all generic-sweep verdicts to the exact frozen "
        "1,090-source canonical CPUNET inventory and verifier tool hashes.", "",
        "- Source inventory digest: `%s`" % data["source_inventory_digest"],
        "- Result: **%d PASS, %d FAIL, %d compile error, %d OTHER, %d timeout, %d source drift**"
        % (c["PASS"], c["FAIL"], c["compile_error"], c["other"],
           c["timeout"], c["source_changed"]),
        "- Unresolved by this generic sweep: **%d**" % data["unresolved_count"],
        "", "## Post-sweep repair drift", "", data["drift_note"], "",
    ]
    lines.extend("- `%s`" % name
                 for name in data["post_sweep_repair_drift_observed_before_commit"])
    lines += [
        "", "## FAIL", "",
    ]
    lines.extend("- `%s`" % name for name in data["by_status"]["FAIL"])
    lines += ["", "## Timeout", ""]
    lines.extend("- `%s`" % name for name in data["by_status"]["timeout"])
    lines += ["", "## Catalog-missed OTHER", "", data["coverage_note"], ""]
    lines.extend("- `%s` (`%s`) — dedicated receipt: `%s`" %
                 (row["name"], row["address"], row["dedicated_receipt"])
                 for row in data["catalog_missed"])
    lines += ["", "## Tool hashes", ""]
    lines.extend("- `%s`: `%s`" % item
                 for item in sorted(data["tool_hashes"].items()))
    return "\n".join(lines) + "\n"


def main():
    data = build()
    OUT_JSON.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
    OUT_MD.write_text(markdown(data))
    print("CPUNET CFG report valid: %s" % data["counts"])


if __name__ == "__main__":
    main()
