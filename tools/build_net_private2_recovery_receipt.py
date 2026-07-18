#!/usr/bin/env python3
"""Build the authoritative CFG receipt for CPUNET shard net-private-2."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


BASE = Path(__file__).resolve().parents[1]
WORKLIST = BASE / "recon/catalogs/net_private_recovery_worklist.json"
RECEIPT = BASE / "recon/analysis/net_private2_recovery_receipt.json"
SHARD_ID = "net-private-2"
TRIALS_RANDOM = 40
REVIEWED_EXTENTS = {
    # Catalog/worklist 0x5c2 stops at the first reachable assertion veneer.
    # Code owns all three veneers through 0x010237a2; 0x010237a4 starts the
    # literal island and the next function begins at 0x010237b0.
    0x010231C8: 0x5DC,
}
CONN_WINDOW_CASE_LABELS = [
    "thread_request_zero",
    "thread_request_one",
    "irq_priority_zero_request_zero",
    "irq_priority_one_request_one",
    "successful_empty_queue_publication",
    "thread_invalid_request_assertion",
]


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def shard_entries() -> list[dict]:
    worklist = json.loads(WORKLIST.read_text())
    shard = next(item for item in worklist["shards"] if item["id"] == SHARD_ID)
    by_address = {item["analysis_address"]: item for item in worklist["entries"]}
    return [by_address[address] for address in shard["addresses"]]


def install_conn_window_cases() -> None:
    """Drive valid pointer-backed admission paths absent from CFG selectors."""
    va = 0x010231C8
    request = emu.SCRATCH + 0x1A00
    state = bytearray(0x600)
    state[0x50] = 1  # bank-zero slot zero is pending and must be processed

    def case(request_kind: int, exception: int = 0,
             irq_priority: int | None = None) -> tuple:
        memory = [
            (request, bytes((request_kind, 0, 0, 0))),
            (0xE000ED04, int(exception).to_bytes(4, "little")),
            (0x210016F0, bytes(state)),
        ]
        if irq_priority is not None:
            memory.append((0xE000E400, bytes((irq_priority,))))
        # Valid paths call time-read then request preparation. Zero timing
        # data deliberately selects the deterministic reject/publish path.
        return ({0: 0, 1: request}, memory, {0: {0: 0, 1: 0}, 1: {}})

    success_memory = [
        (request, bytes((0, 0, 0, 0))),
        (0xE000ED04, bytes(4)),
        (0x210016F0, bytes(state)),
    ]
    timing = b"".join(
        word.to_bytes(4, "little") for word in (2, 0, 1, 0, 0, 0)
    )
    success_writes = {
        1: [(3, 0, timing, 0x010225AC)],
        2: [
            (2, 0, b"\x20", 0x01021B7C),
            (3, 0, b"\x20", 0x01021B7C),
        ],
    }
    success_case = (
        {0: 0, 1: request},
        success_memory,
        {0: {0: 0, 1: 0}, 1: {}, 2: {0: 1}},
        success_writes,
    )
    cfg_verify.REVIEWED_ORACLE_CASES[("net", va)] = [
        case(0),
        case(1),
        case(0, exception=16, irq_priority=0),
        case(1, exception=16, irq_priority=0x20),
        success_case,
        case(2),
    ]


def build_receipt() -> dict:
    entries = shard_entries()
    context = cfg_verify.core_ctx("net")
    install_conn_window_cases()
    proofs = []
    for entry in entries:
        address = entry["analysis_address"]
        va = int(address, 16)
        catalog_extent = entry["true_executable_extent"]
        extent = REVIEWED_EXTENTS.get(va, catalog_extent)
        source = BASE / "recon/net/src" / f"FUN_{va:08x}.c"
        if not source.is_file():
            raise FileNotFoundError(source)

        catalog_size_injected = context["sizes"].get(va) != extent
        if catalog_size_injected:
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
                "worklist_executable_extent": catalog_extent,
                "extent_basis": (
                    "reviewed reachable assertion veneers; code ends 0x010237a4, "
                    "literal island follows, next function 0x010237b0"
                    if va in REVIEWED_EXTENTS else entry["extent_basis"]
                ),
                "catalog_size_injected_at_runtime": catalog_size_injected,
                "cfg_request": {
                    "verifier": "tools/cfg_verify.py",
                    "core": "net",
                    "name": entry["primary_symbol"],
                    "trials_random": TRIALS_RANDOM,
                },
                "cfg_result": result,
                "reviewed_case_labels": (
                    CONN_WINDOW_CASE_LABELS if va == 0x010231C8 else []
                ),
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
        "inputs": [
            {"path": str(WORKLIST.relative_to(BASE)), "sha256": sha256(WORKLIST)}
        ],
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
            raise SystemExit("net-private-2 receipt is stale")
    else:
        RECEIPT.write_text(json.dumps(actual, indent=2, sort_keys=True) + "\n")
        print(RECEIPT)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
