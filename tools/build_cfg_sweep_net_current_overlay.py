#!/usr/bin/env python3
"""Compose the immutable CPUNET sweep overlay with all later proven roots."""

import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "recon/analysis/cfg_sweep_authoritative_net.json"
PREVIOUS = ROOT / "recon/analysis/cfg_sweep_net_recheck_overlay.json"
OUT_JSON = ROOT / "recon/analysis/cfg_sweep_net_current_overlay.json"
OUT_MD = ROOT / "recon/analysis/cfg_sweep_net_current_overlay.md"

INPUT_HASHES = {
    "recon/analysis/cfg_sweep_authoritative_net.json": "fea47af658122b8fc4dd3364bbc6e94ec348611b1168ee175e6d84e727275db4",
    "recon/analysis/cfg_sweep_net_recheck_overlay.json": "bb0936acde02f12ea6f0d3eb163bb210853c6c8e4fa109f6cb371345f25b8f55",
    "recon/ownership/net_link_gap_recovery.json": "5bf1304c8429532d9a819d16d7429c5eac1d70cadd1301bdb9d5b69dacb94e24",
    "recon/analysis/net_link_gap2_recovery_receipt.json": "11c6b8c32d85d4475ba58c4514cbff5faf31eecb4179649881afdcd4e81b0476",
    "recon/ownership/net_link_gap3_recovery.json": "72bb0db3108049b3323c9b634fd2272a9318497d0565c65d22cb6a605e3651d7",
    "recon/ownership/net_link_gap4_recovery.json": "c626b16cc78a1a1aefe43288d0ea05cc649ee3bae3410ea1e855c4dddaa9a9e1",
    "recon/ownership/net_link_gap5_recovery.json": "7c40f6b453743ac2350ff94da705238f3158e8459bd6cc40a8ade4f2daf9d4a2",
    "recon/ownership/net_link_gap6_recovery.json": "4aaf35bc07f3bfc8f66ed65f5824dfc0a1957f5c9a698fe6765c12e91729743b",
    "recon/ownership/net_link_gap7_recovery.json": "4e366d56e54a9db172914b663e3e2bfb94a8857c37be8873f639ea707f57bd5a",
    "recon/ownership/net_link_gap8_recovery.json": "b8a601d522f3abca0c3045cc14a77eef22b9a2f51f1d7b2f2b2d5307bfa00cb4",
    "recon/ownership/net_link_gap9_recovery.json": "049f5d8dd33ea22b4d3532c0b22fdf07ad40e0ce05916a795db433c9d99bbc63",
    "recon/ownership/net_sdc_event_publish_recovery.json": "6153a508f8e75686af4249d349152a62a6644c6ef3aa0bb85017e31c826b024e",
    "recon/ownership/net_esb_clock_start_closure.json": "7ef95ccf3ca2839ecc35d7073ea71d65dea76d215c06d31c90d5fa0c51b06766",
    "recon/ownership/net_esb_boot_root.json": "a569b54e5f32a6bd9fa6bf53c89d94e8a80adcf4f9789527a23c1cb9dabb67d4",
}
TOOL_HASHES = {
    "tools/cfg_verify.py": "56a51d52bdb25fce73454ff47d836220464518defc66b42c56f965f1eda9b2a7",
    "tools/net_recon_kit.py": "9fde04632cdc6ba306352b83a75f3d8fe0ab453da8524fff060d17832aedfef0",
    "tools/net_extract.py": "ec80c6ed622adce759db81b78a874dc70d9338215800e1d25c023ca08403a6d9",
    "tools/parity/emu.py": "0e2503bbe2c517ee4c397a41ceec4e5e7e6d9e8ff26f5f5ff3257537f8e6ace0",
    "tools/parity/recon.py": "22c5cc8d8113ac203fb96091fcffa392902dccd22792148958fcba40a4d5bbc2",
}
GAPS = [
    ("recon/ownership/net_link_gap_recovery.json", "functions", "gap1"),
    ("recon/analysis/net_link_gap2_recovery_receipt.json", "proofs", "gap2"),
    ("recon/ownership/net_link_gap3_recovery.json", "functions", "gap3"),
    ("recon/ownership/net_link_gap4_recovery.json", "functions", "gap4"),
    ("recon/ownership/net_link_gap5_recovery.json", "functions", "gap5"),
    ("recon/ownership/net_link_gap6_recovery.json", "functions", "gap6"),
    ("recon/ownership/net_link_gap7_recovery.json", "functions", "gap7"),
    ("recon/ownership/net_link_gap8_recovery.json", "functions", "gap8"),
    ("recon/ownership/net_link_gap9_recovery.json", "functions", "gap9"),
]


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value):
    encoded = json.dumps(value, sort_keys=True, separators=(",", ":")).encode()
    return hashlib.sha256(encoded).hexdigest()


def pinned_inputs():
    for relative, expected in {**INPUT_HASHES, **TOOL_HASHES}.items():
        if sha256(ROOT / relative) != expected:
            raise ValueError("pinned input drift: %s" % relative)


def prior_inventory():
    baseline = json.loads(BASELINE.read_text())
    previous = json.loads(PREVIOUS.read_text())
    if (baseline.get("inventory_count") != 1090 or
            previous.get("current_inventory_count") != 1090 or
            previous.get("unresolved_count") != 0 or
            previous.get("overlay_counts", {}).get("PASS") != 1090):
        raise ValueError("unexpected frozen CPUNET sweep parent")
    expected = {row["name"]: row["source_sha256"]
                for row in baseline["functions"]}
    for key in ("resolved_fail", "resolved_timeout",
                "resolved_catalog_missed"):
        for row in previous[key]:
            expected[row["name"]] = row["source_sha256"]
    return expected


def gap_rows():
    result = []
    for relative, collection, label in GAPS:
        receipt = json.loads((ROOT / relative).read_text())
        rows = receipt[collection]
        if len(rows) != (1 if label == "gap9" else 4):
            raise ValueError("unexpected %s receipt cardinality" % label)
        for row in rows:
            name = row["raw_symbol"]
            source_relative = row.get("source", row.get("source_path"))
            source_hash = row["source_sha256"]
            proof = row.get("cfg_verify", row.get("cfg_result"))
            if proof is None:
                checked = int(row.get("ordinary_cfg_checked", 0)) + int(
                    row.get("directed_cases", 0))
                status = "PASS" if checked > 0 else None
            else:
                checked = int(proof.get("checked", 0))
                status = proof.get("status")
            if (status != "PASS" or checked <= 0 or
                    Path(source_relative).stem != name or
                    sha256(ROOT / source_relative) != source_hash):
                raise ValueError("invalid dedicated CFG proof: %s" % name)
            result.append({
                "name": name,
                "analysis_address": row["analysis_address"],
                "status": "PASS",
                "checked": checked,
                "source": source_relative,
                "source_sha256": source_hash,
                "receipt": relative,
                "receipt_sha256": INPUT_HASHES[relative],
            })
    if len(result) != 33 or len({row["name"] for row in result}) != 33:
        raise ValueError("prior added-root coverage drift")
    return sorted(result, key=lambda row: row["name"])


def sdc_addition():
    relative = "recon/ownership/net_sdc_event_publish_recovery.json"
    receipt = json.loads((ROOT / relative).read_text())
    row = receipt["function"]
    proof = row["cfg_verify"]
    source = row["source"]
    if (row["raw_symbol"] != "FUN_0101b4f4" or
            row["analysis_address"] != "0x0101b4f4" or
            row["true_executable_extent"] != 88 or
            proof != {"status": "PASS", "cover_cases": 5, "checked": 5,
                      "case_families": proof["case_families"]} or
            len(proof["case_families"]) != 5 or
            sha256(ROOT / source) != row["source_sha256"]):
        raise ValueError("sdc_event_publish proof drift")
    return {
        "name": row["raw_symbol"],
        "readable_name": row["primary_symbol"],
        "analysis_address": row["analysis_address"],
        "true_executable_extent": row["true_executable_extent"],
        "status": "PASS",
        "cover_cases": proof["cover_cases"],
        "checked": proof["checked"],
        "source": source,
        "source_sha256": row["source_sha256"],
        "receipt": relative,
        "receipt_sha256": INPUT_HASHES[relative],
    }


def esb_closure():
    relative = "recon/ownership/net_esb_clock_start_closure.json"
    receipt = json.loads((ROOT / relative).read_text())
    if receipt.get("summary") != {
            "function_count": 7, "cfg_pass_count": 7,
            "total_true_executable_extent": 612}:
        raise ValueError("ESB clock/start receipt summary drift")
    result = []
    for row in receipt["proofs"]:
        proof = row["cfg_result"]
        if (proof.get("status") != "PASS" or proof.get("checked", 0) <= 0 or
                sha256(ROOT / row["source"]) != row["source_sha256"]):
            raise ValueError("ESB closure proof drift: %s" % row["raw_symbol"])
        result.append({
            "name": row["raw_symbol"],
            "readable_name": row["readable_identity"],
            "analysis_address": row["analysis_address"],
            "true_executable_extent": row["true_executable_extent"],
            "status": "PASS",
            "cover_cases": proof.get("cover_cases", 0),
            "checked": proof["checked"],
            "source": row["source"],
            "source_sha256": row["source_sha256"],
            "receipt": relative,
            "receipt_sha256": INPUT_HASHES[relative],
        })
    if len(result) != 7 or len({row["name"] for row in result}) != 7:
        raise ValueError("ESB closure identity drift")
    return sorted(result, key=lambda row: row["name"])


def esb_boot_addition():
    relative = "recon/ownership/net_esb_boot_root.json"
    receipt = json.loads((ROOT / relative).read_text())
    row = receipt["custom_main"]
    source = row["source"]
    if (row["raw_identity"] != "FUN_0102a720" or
            row["analysis_va"] != "0x0102a720" or
            row["reviewed_true_extent"] != 1000 or
            row["cfg_status"] != "PASS" or row["directed_cases"] != 5 or
            row["prefix_events"] != 512 or
            len(row["families"]) != 5 or
            sha256(ROOT / source) != row["source_sha256"]):
        raise ValueError("ESB boot-root proof drift")
    return {
        "name": row["raw_identity"],
        "readable_name": row["readable_identity"],
        "analysis_address": row["analysis_va"],
        "true_executable_extent": row["reviewed_true_extent"],
        "status": "PASS",
        "cover_cases": row["directed_cases"],
        "checked": row["directed_cases"],
        "prefix_events": row["prefix_events"],
        "source": source,
        "source_sha256": row["source_sha256"],
        "receipt": relative,
        "receipt_sha256": INPUT_HASHES[relative],
    }


def build():
    pinned_inputs()
    expected = prior_inventory()
    additions = gap_rows()
    for row in additions:
        if row["name"] in expected:
            raise ValueError("prior addition overlaps frozen sweep: %s" % row["name"])
        expected[row["name"]] = row["source_sha256"]
    if len(expected) != 1123:
        raise ValueError("previous current-corpus count drift")
    latest = sdc_addition()
    if latest["name"] in expected:
        raise ValueError("new root already covered by prior corpus")
    expected[latest["name"]] = latest["source_sha256"]

    closure = esb_closure()
    existing = [row for row in closure if row["name"] == "FUN_0102b31c"]
    added_closure = [row for row in closure if row["name"] != "FUN_0102b31c"]
    if len(existing) != 1 or len(added_closure) != 6:
        raise ValueError("ESB existing/addition partition drift")
    expected[existing[0]["name"]] = existing[0]["source_sha256"]
    for row in added_closure:
        if row["name"] in expected:
            raise ValueError("ESB closure root already covered: %s" % row["name"])
        expected[row["name"]] = row["source_sha256"]
    boot = esb_boot_addition()
    if boot["name"] in expected:
        raise ValueError("ESB boot root already covered")
    expected[boot["name"]] = boot["source_sha256"]

    current = {path.stem: sha256(path)
               for path in (ROOT / "recon/net/src").glob("*.c")}
    if set(current) != set(expected):
        raise ValueError("current CPUNET inventory membership drift")
    drift = sorted(name for name in expected if expected[name] != current[name])
    if drift:
        raise ValueError("current CPUNET source hash drift: %s" % drift)
    inventory = [[name, current[name]] for name in sorted(current)]
    return {
        "schema": 1,
        "kind": "authoritative_cfg_sweep_current_corpus_overlay",
        "core": "net",
        "frozen_parent": {
            "path": str(PREVIOUS.relative_to(ROOT)),
            "sha256": INPUT_HASHES[str(PREVIOUS.relative_to(ROOT))],
            "inventory_count": 1090,
            "unresolved_count": 0,
        },
        "previous_current_inventory_count": 1123,
        "prior_added_proofs": additions,
        "current_additions": [latest, boot] + added_closure,
        "reverified_existing": existing,
        "current_inventory_count": 1131,
        "current_source_inventory_digest": digest_json(inventory),
        "current_source_tree_fully_covered": True,
        "source_drift": [],
        "tool_hashes": TOOL_HASHES,
        "overlay_counts": {
            "PASS": 1131, "FAIL": 0, "compile_error": 0,
            "other": 0, "timeout": 0, "source_changed": 0,
        },
        "unresolved_count": 0,
    }


def markdown(data):
    row = data["current_additions"][0]
    boot = data["current_additions"][1]
    return "\n".join([
        "# CPUNET current-corpus CFG overlay", "",
        "This exact-hash layer preserves the frozen 1,090-source sweep and "
        "all 33 previously proven link-gap roots (1,123 sources), then adds "
        "the catalog-missed `sdc_event_publish` root and the seven recovered "
        "ESB production roots.", "",
        "- Previous covered inventory: **1,123 PASS; 0 unresolved**",
        "- Current covered inventory: **1,131 PASS; 0 unresolved**",
        "- Inventory digest: `%s`" % data["current_source_inventory_digest"],
        "- New proof: `%s` / `%s`, extent `%d`, CFG **PASS %d/%d**" % (
            row["name"], row["readable_name"], row["true_executable_extent"],
            row["checked"], row["cover_cases"]),
        "- Source: `%s` (`%s`)" % (row["source"], row["source_sha256"]),
        "- Receipt: `%s` (`%s`)" % (row["receipt"], row["receipt_sha256"]),
        "- ESB main: `%s` / `%s`, extent `%d`, CFG **PASS %d/%d**, prefix %d events" % (
            boot["name"], boot["readable_name"], boot["true_executable_extent"],
            boot["checked"], boot["cover_cases"], boot["prefix_events"]),
        "- ESB clock/start closure: 6 new PASS roots; `FUN_0102b31c` freshly reverified",
        "", "## Current verifier tool hashes", "",
        *["- `%s`: `%s`" % item for item in sorted(data["tool_hashes"].items())],
        "",
    ])


def main():
    data = build()
    OUT_JSON.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
    OUT_MD.write_text(markdown(data))
    print("CPUNET current CFG overlay valid: 1131 PASS, unresolved=0")


if __name__ == "__main__":
    main()
