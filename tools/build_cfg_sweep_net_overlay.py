#!/usr/bin/env python3
"""Build the exact-hash post-sweep CPUNET proof overlay."""

import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "recon/analysis/cfg_sweep_authoritative_net.json"
RECHECKS = ROOT / "recon/analysis/cfg_sweep_net_recheck_receipts.json"
OUT_JSON = ROOT / "recon/analysis/cfg_sweep_net_recheck_overlay.json"
OUT_MD = ROOT / "recon/analysis/cfg_sweep_net_recheck_overlay.md"
DEDICATED = {
    "FUN_0100ef08": ("recon/ownership/net_private_shard8_recovery.json", "functions", "primary_symbol", "cfg_verify"),
    "FUN_01011664": ("recon/ownership/net_private_7_recovery.json", "functions", "raw_backmap", "cfg_verify"),
    "FUN_01014b18": ("recon/ownership/net_private_shard1.json", None, None, "cfg_verification"),
    "FUN_01018df8": ("recon/ownership/net_private_7_recovery.json", "functions", "raw_backmap", "cfg_verify"),
    "FUN_0101d890": ("recon/analysis/net_private3_recovery_receipt.json", "proofs", "primary_symbol", "cfg_result"),
    "FUN_0102665c": ("recon/ownership/net_private_shard8_recovery.json", "functions", "primary_symbol", "cfg_verify"),
    "FUN_010292ec": ("recon/ownership/net_private_shard8_recovery.json", "functions", "primary_symbol", "cfg_verify"),
    "FUN_0102a1e0": ("recon/ownership/net_private_shard8_recovery.json", "functions", "primary_symbol", "cfg_verify"),
}


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")
    ).encode()).hexdigest()


def dedicated_row(name):
    rel, collection, identity, proof_key = DEDICATED[name]
    path = ROOT / rel
    data = json.loads(path.read_text())
    if collection is None:
        row = data["function"]
        proof = data[proof_key]
        status = proof["reviewed_status"]
        checked = proof["total_checked"]
    else:
        rows = [row for row in data[collection] if row.get(identity) == name]
        if len(rows) != 1:
            raise ValueError("dedicated receipt identity drift: %s" % name)
        row = rows[0]
        proof = row[proof_key]
        status = proof["status"]
        checked = proof["checked"]
    if status != "PASS":
        raise ValueError("dedicated proof is not PASS: %s" % name)
    source_hash = sha256(ROOT / "recon/net/src" / (name + ".c"))
    if source_hash != row["source_sha256"]:
        raise ValueError("dedicated source hash drift: %s" % name)
    return {
        "name": name,
        "status": "PASS",
        "source_sha256": source_hash,
        "checked": checked,
        "receipt": rel,
        "receipt_sha256": sha256(path),
    }


def build():
    baseline = json.loads(BASELINE.read_text())
    if (baseline.get("core") != "net" or baseline.get("inventory_count") != 1090 or
            baseline.get("unresolved_count") != 17):
        raise ValueError("unexpected CPUNET baseline")
    raw = json.loads(RECHECKS.read_text())
    expected_rechecks = set(baseline["by_status"]["FAIL"] +
                            baseline["by_status"]["timeout"])
    rechecks = {row["name"]: row for row in raw["rechecks"]}
    if set(rechecks) != expected_rechecks:
        raise ValueError("recheck target coverage drift")
    for name, row in rechecks.items():
        if row["status"] != "PASS" or row["exit_code"] != 0:
            raise ValueError("recheck did not PASS: %s" % name)
        expected_prefix = "%s PASS cases=%d " % (name, row["cases"])
        if (not row["stdout"].startswith(expected_prefix) or
                not row["stdout"].endswith(
                    "mismatches=None\ndetail=None\n")):
            raise ValueError("malformed recheck stdout: %s" % name)
        source_hash = sha256(ROOT / "recon/net/src" / (name + ".c"))
        if source_hash != row["source_sha256"]:
            raise ValueError("rechecked source hash drift: %s" % name)
    catalog_missed = [dedicated_row(name) for name in sorted(DEDICATED)]
    if set(DEDICATED) != set(baseline["by_status"]["other"]):
        raise ValueError("catalog-missed overlay coverage drift")

    old = {row["name"]: row["source_sha256"] for row in baseline["functions"]}
    current = {path.stem: sha256(path)
               for path in (ROOT / "recon/net/src").glob("*.c")}
    if set(old) != set(current):
        raise ValueError("canonical CPUNET inventory membership drift")
    changed = sorted(name for name in old if old[name] != current[name])
    if any(name not in rechecks for name in changed):
        raise ValueError("unverified post-baseline source drift")
    # Every unchanged baseline PASS remains bound to the same bytes. Every
    # changed source and every non-PASS baseline identity is covered above.
    current_inventory = [[name, current[name]] for name in sorted(current)]
    direct_rows = [rechecks[name] for name in sorted(rechecks)]
    return {
        "schema": 1,
        "kind": "authoritative_cfg_sweep_recheck_overlay",
        "core": "net",
        "baseline": {
            "path": str(BASELINE.relative_to(ROOT)),
            "sha256": sha256(BASELINE),
            "inventory_count": baseline["inventory_count"],
            "counts": baseline["counts"],
            "unresolved_count": baseline["unresolved_count"],
        },
        "execution_head": raw["execution_head"],
        "timeout_seconds": raw["timeout_seconds"],
        "tool_hashes": raw["tool_hashes"],
        "raw_rechecks": {
            "path": str(RECHECKS.relative_to(ROOT)),
            "sha256": sha256(RECHECKS),
        },
        "post_baseline_source_drift": changed,
        "current_inventory_count": len(current_inventory),
        "current_source_inventory_digest": digest_json(current_inventory),
        "current_source_tree_fully_covered": True,
        "resolved_fail": [row for row in direct_rows
                          if row["name"] in baseline["by_status"]["FAIL"]],
        "resolved_timeout": [row for row in direct_rows
                             if row["name"] in baseline["by_status"]["timeout"]],
        "resolved_catalog_missed": catalog_missed,
        "overlay_counts": {
            "PASS": 1090,
            "FAIL": 0,
            "compile_error": 0,
            "other": 0,
            "timeout": 0,
            "source_changed": 0,
        },
        "unresolved_count": 0,
    }


def markdown(data):
    lines = [
        "# CPUNET CFG recheck overlay", "",
        "This exact-hash overlay preserves the frozen 1,090-source baseline, "
        "then closes every non-PASS identity with a current authoritative "
        "recheck or its catalog-missed dedicated proof receipt.", "",
        "- Execution HEAD: `%s`" % data["execution_head"],
        "- Current source inventory digest: `%s`" % data["current_source_inventory_digest"],
        "- Aggregate: **1,090 PASS; 0 unresolved**", "",
        "## Former FAIL", "",
    ]
    lines.extend("- `%s` — PASS, source `%s`" %
                 (row["name"], row["source_sha256"])
                 for row in data["resolved_fail"])
    lines += ["", "## Former timeout", ""]
    lines.extend("- `%s` — PASS within a %s-second bound, source `%s`" %
                 (row["name"], data["timeout_seconds"], row["source_sha256"])
                 for row in data["resolved_timeout"])
    lines += ["", "## Catalog-missed dedicated proofs", ""]
    lines.extend("- `%s` — PASS (%d checks), `%s`" %
                 (row["name"], row["checked"], row["receipt"])
                 for row in data["resolved_catalog_missed"])
    lines += ["", "## Post-baseline source changes", ""]
    lines.extend("- `%s`" % name for name in data["post_baseline_source_drift"])
    lines += ["", "## Recheck tool hashes", ""]
    lines.extend("- `%s`: `%s`" % item
                 for item in sorted(data["tool_hashes"].items()))
    return "\n".join(lines) + "\n"


def main():
    data = build()
    OUT_JSON.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
    OUT_MD.write_text(markdown(data))
    print("CPUNET CFG overlay valid: unresolved=0")


if __name__ == "__main__":
    main()
