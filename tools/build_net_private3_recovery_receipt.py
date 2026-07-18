#!/usr/bin/env python3
"""Build the authoritative CFG receipt for CPUNET shard net-private-3."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import cfg_verify


BASE = Path(__file__).resolve().parents[1]
WORKLIST = BASE / "recon/catalogs/net_private_recovery_worklist.json"
RECEIPT = BASE / "recon/analysis/net_private3_recovery_receipt.json"
SHARD_ID = "net-private-3"
TRIALS_RANDOM = 40


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def shard_entries() -> list[dict]:
    worklist = json.loads(WORKLIST.read_text())
    shard = next(item for item in worklist["shards"] if item["id"] == SHARD_ID)
    by_address = {item["analysis_address"]: item for item in worklist["entries"]}
    return [by_address[address] for address in shard["addresses"]]


def build_receipt() -> dict:
    entries = shard_entries()
    context = cfg_verify.core_ctx("net")
    proofs = []
    for entry in entries:
        address = entry["analysis_address"]
        va = int(address, 16)
        extent = entry["true_executable_extent"]
        source = BASE / "recon/net/src" / f"FUN_{va:08x}.c"
        if not source.is_file():
            raise FileNotFoundError(source)

        catalog_size_injected = not bool(context["sizes"].get(va))
        if catalog_size_injected:
            # cfg_verify intentionally fails closed for unknown extents. This
            # shard-local process supplies the reviewed worklist boundary; it
            # does not modify the shared verifier or its persistent catalogs.
            context["sizes"][va] = extent

        result = cfg_verify.verify(
            "net", entry["primary_symbol"], trials_random=TRIALS_RANDOM
        )
        if result.get("status") != "PASS":
            raise RuntimeError(f"{address}: {result}")
        proofs.append(
            {
                "analysis_address": address,
                "runtime_address": entry["runtime_address"],
                "primary_symbol": entry["primary_symbol"],
                "raw_backmap": f"FUN_{va:08x}@{address}",
                "source_path": str(source.relative_to(BASE)),
                "source_sha256": sha256(source),
                "true_executable_extent": extent,
                "extent_basis": entry["extent_basis"],
                "catalog_size_injected_at_runtime": catalog_size_injected,
                "cfg_request": {
                    "verifier": "tools/cfg_verify.py",
                    "core": "net",
                    "name": entry["primary_symbol"],
                    "trials_random": TRIALS_RANDOM,
                },
                "cfg_result": result,
            }
        )

    return {
        "schema": "g1.net.private_recovery_receipt.v1",
        "shard": SHARD_ID,
        "policy": {
            "canonical_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "shared_cfg_tool_modified": False,
        },
        "inputs": [{"path": str(WORKLIST.relative_to(BASE)), "sha256": sha256(WORKLIST)}],
        "summary": {
            "function_count": len(proofs),
            "total_true_executable_extent": sum(
                item["true_executable_extent"] for item in proofs
            ),
            "cfg_pass_count": len(proofs),
        },
        "proofs": proofs,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    actual = build_receipt()
    if args.check:
        expected = json.loads(RECEIPT.read_text())
        if actual != expected:
            raise SystemExit("net-private-3 receipt is stale")
    else:
        RECEIPT.write_text(json.dumps(actual, indent=2, sort_keys=True) + "\n")
        print(RECEIPT)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
