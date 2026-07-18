#!/usr/bin/env python3
"""Replay the semantic gates for the focused CPUNET code-size lane C."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "recon/analysis/net_codegen_shrink_lane_c.json"

ROWS = (
    ("FUN_010250d0", 0x010250D0, 258, 300, 292,
     "radio[0x308 / 4] = mask;", "(void)mask;"),
    ("FUN_0102a122", 0x0102A122, 190, 234, 218,
     "puVar1 = (unsigned char *)FUN_01021ac0();",
     "puVar1 = (unsigned char *)0;"),
    ("FUN_0102ff54", 0x0102FF54, 76, 84, 64,
     "recovered_k_queue_append(queue, buffer);",
     "(void)queue; (void)buffer;"),
)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def compact(result: dict) -> dict:
    value = {key: result[key] for key in
             ("status", "checked", "cover_cases", "selectors")
             if key in result}
    return json.loads(json.dumps(value))


def build_receipt() -> dict:
    proofs = []
    for name, va, extent, before, after, correct, wrong in ROWS:
        canonical = ROOT / "recon/net/src" / f"{name}.c"
        named = ROOT / "recon/net/named" / f"{name}.c"
        symbolized = ROOT / "recon/symbolized/net" / f"{name}.c"
        source = canonical.read_text()
        if source.count(correct) != 1:
            raise RuntimeError(f"{name}: mutation anchor is not unique")
        good = cfg_verify.verify("net", name, trials_random=40)
        bad = cfg_verify.verify(
            "net", name, trials_random=40,
            source_override=source.replace(correct, wrong, 1))
        if good.get("status") != "PASS" or bad.get("status") != "FAIL":
            raise RuntimeError(f"{name}: good={good}, mutation={bad}")
        proofs.append({
            "analysis_address": f"0x{va:08x}",
            "raw_symbol": name,
            "true_firmware_extent": extent,
            "extent_basis": "catalog entry through next entry/literal-aware boundary",
            "canonical_source": str(canonical.relative_to(ROOT)),
            "named_source": str(named.relative_to(ROOT)),
            "production_symbolized_source": str(symbolized.relative_to(ROOT)),
            "source_sha256": sha256(canonical),
            "named_sha256": sha256(named),
            "symbolized_sha256": sha256(symbolized),
            "cfg_result": compact(good),
            "mutation": {"from": correct, "to": wrong,
                         "result": compact(bad)},
            "production_function_bytes_before": before,
            "production_function_bytes_after": after,
            "production_function_bytes_delta": after - before,
        })
    return {
        "schema": "g1.net.codegen_shrink_lane_c.v1",
        "summary": {
            "changed_function_count": len(proofs),
            "cfg_pass_count": len(proofs),
            "production_function_bytes_delta": sum(
                row[4] - row[3] for row in ROWS),
        },
        "reviewed_without_change": [
            {"raw_symbol": "FUN_010225ac", "reason":
             "No smaller human-readable lowering was established without weakening proof."},
            {"raw_symbol": "FUN_0102524c", "reason":
             "A CFG-equivalent struct lowering saved four parity-object bytes but zero production bytes."},
        ],
        "policy": {
            "sdc_functions_retained_report_only": True,
            "automatic_sdc_removal": False,
            "archive_or_stock_substitution": False,
            "raw_address_backmaps_retained": True,
            "symbolized_production_sources_updated": True,
        },
        "combined_build_observation": {
            "build_dir": "/private/tmp/g1-net-shrink-lane-c",
            "retain_all": False,
            "flash_used": 227961,
            "flash_capacity": 227328,
            "overflow": 633,
            "attribution": "combined shared-tree result; not attributed solely to lane C",
        },
        "proofs": proofs,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    receipt = build_receipt()
    if args.check:
        if receipt != json.loads(OUTPUT.read_text()):
            raise SystemExit("lane-C receipt is stale")
    else:
        OUTPUT.write_text(json.dumps(receipt, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
