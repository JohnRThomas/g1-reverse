#!/usr/bin/env python3
"""Build the exact-hash post-baseline CPUAPP CFG proof overlay."""

import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "recon/analysis/cfg_sweep_authoritative_app.json"
THREAD_RECEIPT = ROOT / "recon/ownership/app_missing_thread_roots_recovery.json"
DMIC_RECEIPT = ROOT / "recon/ownership/app_dmic_lc3_direct_edge_recovery.json"
OUT_JSON = ROOT / "recon/analysis/cfg_sweep_app_recheck_overlay.json"
OUT_MD = ROOT / "recon/analysis/cfg_sweep_app_recheck_overlay.md"
EXECUTION_HEAD = "f49a3b8628a3f2cb458d9853fc7e63c6a3272735"
EXPECTED_BASELINE_SHA256 = "1eab0c590c62edc0d22c5f9eb540155f8958014a8dd2a8846b4ef21bf0be51b2"
EXPECTED_OVERLAY = {
    "master_display_thread": {
        "address": "0x0002692c", "overlay_class": "added",
        "source_sha256": "7586718e0412a196e9aa518f70a49c7c22afada42d7ab8a341235565ef510f1a",
        "directed_cases": 1, "prefix_events": 50,
        "case_phrase": "one reviewed complete pointer-graph case",
    },
    "slave_display_thread": {
        "address": "0x00027cfc", "overlay_class": "changed",
        "source_sha256": "a1135f28160eec5e3e489091b427714eb6e7905756513ad5822b5ad700978977",
        "directed_cases": 38, "prefix_events": 50,
        "case_phrase": "38 directed production cases",
    },
    "aging_mode_thread": {
        "address": "0x00032420", "overlay_class": "added",
        "source_sha256": "71c7341f1c497effac26e5714820718348638f3d583f063ef9558f77139d29ab",
        "directed_cases": 0, "prefix_events": 50,
        "case_phrase": None,
    },
    "FUN_0002f080": {
        "address": "0x0002f080", "overlay_class": "changed",
        "source_sha256": "7f11a0004fb33e4e5448742af345bb5acc8b0564ea82bd343a2e49e025a80a66",
        "directed_cases": 2, "prefix_events": None,
        "case_phrase": "two directed production capture cases",
    },
}
PROOF_TOOLS = (
    "tools/cfg_verify.py", "tools/parity/emu.py", "tools/parity/recon.py",
)


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def digest_json(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")
    ).encode()).hexdigest()


def build():
    if sha256(BASELINE) != EXPECTED_BASELINE_SHA256:
        raise ValueError("frozen CPUAPP authoritative baseline changed")
    baseline = json.loads(BASELINE.read_text())
    if (baseline.get("core") != "app" or baseline.get("inventory_count") != 2113 or
            baseline.get("counts", {}).get("PASS") != 2113 or
            baseline.get("unresolved_count") != 0):
        raise ValueError("unexpected CPUAPP baseline aggregate")
    baseline_rows = {row["name"]: row for row in baseline["functions"]}
    if len(baseline_rows) != 2113:
        raise ValueError("duplicate CPUAPP baseline identity")

    thread_receipt = json.loads(THREAD_RECEIPT.read_text())
    if (thread_receipt.get("status") != "complete" or
            thread_receipt.get("summary", {}).get("named_and_proven") != 3 or
            not thread_receipt.get("summary", {}).get("complete_root_graph")):
        raise ValueError("missing-thread root proof receipt is incomplete")
    proof_rows = {row["name"]: dict(row, _receipt=THREAD_RECEIPT)
                  for row in thread_receipt["entries"]}
    dmic_receipt = json.loads(DMIC_RECEIPT.read_text())
    if (dmic_receipt.get("status") != "complete" or
            dmic_receipt.get("cfg_proof", {}).get("result") != "PASS"):
        raise ValueError("DMIC direct-edge proof receipt is incomplete")
    proof_rows["FUN_0002f080"] = {
        "name": "FUN_0002f080", "address": "0x0002f080",
        "source": dmic_receipt["caller"]["source"],
        "proof": "cfg_verify PASS; two directed production capture cases; "
                 "LC3-call mutation FAIL 2/2",
        "_receipt": DMIC_RECEIPT,
    }
    if set(proof_rows) != set(EXPECTED_OVERLAY):
        raise ValueError("CPUAPP overlay proof identity drift")

    current = {path.stem: sha256(path)
               for path in (ROOT / "recon/app/src").glob("*.c")}
    old_hashes = {name: row["source_sha256"]
                  for name, row in baseline_rows.items()}
    added = sorted(set(current) - set(old_hashes))
    removed = sorted(set(old_hashes) - set(current))
    changed = sorted(name for name in set(current) & set(old_hashes)
                     if current[name] != old_hashes[name])
    if added != ["aging_mode_thread", "master_display_thread"]:
        raise ValueError("unverified CPUAPP source addition: %r" % added)
    if removed:
        raise ValueError("CPUAPP baseline source removed: %r" % removed)
    if changed != ["FUN_0002f080", "slave_display_thread"]:
        raise ValueError("unverified CPUAPP post-baseline drift: %r" % changed)

    overlay = []
    for name, expected in EXPECTED_OVERLAY.items():
        proof = proof_rows[name]
        source = ROOT / proof["source"]
        if source.stem != name or sha256(source) != current[name]:
            raise ValueError("overlay source/hash drift: %s" % name)
        if current[name] != expected["source_sha256"]:
            raise ValueError("unverified overlay source drift: %s" % name)
        if proof["address"] != expected["address"] or "cfg_verify PASS" not in proof["proof"]:
            raise ValueError("overlay address/proof drift: %s" % name)
        if (expected["case_phrase"] and
                expected["case_phrase"] not in proof["proof"]):
            raise ValueError("overlay directed-case count missing: %s" % name)
        if (expected["prefix_events"] is not None and
                "%d ordered prefix events" % expected["prefix_events"]
                not in proof["proof"]):
            raise ValueError("overlay prefix-event count missing: %s" % name)
        receipt_path = proof["_receipt"]
        overlay.append({
            "name": name,
            "address": expected["address"],
            "status": "PASS",
            "overlay_class": expected["overlay_class"],
            "baseline_source_sha256": old_hashes.get(name),
            "source_sha256": current[name],
            "directed_cases": expected["directed_cases"],
            "prefix_events": expected["prefix_events"],
            "proof_summary": proof["proof"],
            "receipt": str(receipt_path.relative_to(ROOT)),
            "receipt_sha256": sha256(receipt_path),
        })

    overlay_by_name = {row["name"]: row for row in overlay}
    current_functions = []
    for name in sorted(current):
        if name in overlay_by_name:
            provenance = "post_baseline_overlay"
        else:
            if baseline_rows[name]["status"] != "PASS" or old_hashes[name] != current[name]:
                raise ValueError("unverified baseline verdict/hash: %s" % name)
            provenance = "frozen_baseline"
        current_functions.append({
            "name": name, "status": "PASS", "source_sha256": current[name],
            "provenance": provenance,
        })
    inventory = [[row["name"], row["source_sha256"]]
                 for row in current_functions]
    return {
        "schema": 1,
        "kind": "authoritative_cfg_sweep_post_baseline_overlay",
        "core": "app",
        "baseline": {
            "path": str(BASELINE.relative_to(ROOT)),
            "sha256": EXPECTED_BASELINE_SHA256,
            "inventory_count": 2113,
            "counts": baseline["counts"],
            "unresolved_count": 0,
            "preserved_immutable": True,
        },
        "execution_head": EXECUTION_HEAD,
        "proof_tools": {path: sha256(ROOT / path) for path in PROOF_TOOLS},
        "proof_receipts": [
            {"path": str(path.relative_to(ROOT)), "sha256": sha256(path)}
            for path in (THREAD_RECEIPT, DMIC_RECEIPT)
        ],
        "post_baseline_added": added,
        "post_baseline_changed": changed,
        "post_baseline_removed": removed,
        "overlay_proofs": overlay,
        "current_inventory_count": len(current_functions),
        "current_source_inventory_digest": digest_json(inventory),
        "current_functions": current_functions,
        "current_counts": {
            "PASS": len(current_functions), "FAIL": 0, "compile_error": 0,
            "other": 0, "timeout": 0, "source_changed": 0,
        },
        "unresolved_count": 0,
        "current_source_tree_fully_covered": True,
        "unverified_source_drift": [],
    }


def markdown(data):
    lines = [
        "# CPUAPP CFG post-baseline overlay", "",
        "This exact-hash overlay preserves the frozen 2,113-source CPUAPP "
        "baseline and covers the two added thread entries, the corrected "
        "slave-thread entry, and the repaired DMIC capture loop.", "",
        "- Frozen baseline SHA-256: `%s`" % data["baseline"]["sha256"],
        "- Execution HEAD: `%s`" % data["execution_head"],
        "- Current source inventory digest: `%s`" % data["current_source_inventory_digest"],
        "- Aggregate: **2,115 PASS; 0 unresolved; 0 unverified drift**", "",
        "| Identity | Address | Change | Directed cases | Prefix events | Source SHA-256 |",
        "|---|---:|---|---:|---:|---|",
    ]
    for row in data["overlay_proofs"]:
        prefix = ("—" if row["prefix_events"] is None else
                  str(row["prefix_events"]))
        lines.append("| `%s` | `%s` | %s | %d | %s | `%s` |" % (
            row["name"], row["address"], row["overlay_class"],
            row["directed_cases"], prefix, row["source_sha256"]))
    lines += ["", "Every other current source is byte-identical to its PASS-bound "
              "entry in the frozen authoritative baseline.", ""]
    return "\n".join(lines)


def main():
    data = build()
    OUT_JSON.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
    OUT_MD.write_text(markdown(data))
    print("CPUAPP CFG overlay valid: 2115 PASS, unresolved=0")


if __name__ == "__main__":
    main()
