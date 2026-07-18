#!/usr/bin/env python3
"""Build fail-closed proofs for four retained CPUNET private call targets."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/analysis/net_link_gap2_recovery_receipt.json"
TRIALS_RANDOM = 40
ENTRIES = (
    (0x010108B8, 0x46, "sdc_ecb_crypt_block_ordered"),
    (0x01013D90, 0x18, "controller_fixed_packet_time_get"),
    (0x01016250, 0x20, "controller_phy_uses_coded_timing"),
    (0x0101BBC8, 0x22, "controller_margin_packet_time_get"),
)
CATALOG_EXTENTS = {
    0x010108B8: 0x46,
    0x01013D90: 0x18,
    0x01016250: 0x1C,
    0x0101BBC8: 0x22,
}


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256(path: Path) -> str:
    return sha256_bytes(path.read_bytes())


def install_reviewed_cases() -> None:
    """Force both sides of the two oracle-return clamp branches."""
    timing = emu.SCRATCH + 0x1A00
    memory = [(timing, bytes.fromhex("78563412"))]
    clamp_values = (0, 0xA8F, 0xA90, 0xFFFFFFFF)
    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01013D90)] = [
        ({0: timing}, memory, {0: {0: value}}) for value in clamp_values
    ]
    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x0101BBC8)] = [
        ({0: timing}, memory, {0: {0: 0x13A}, 1: {0: value}})
        for value in clamp_values
    ]


def build_receipt() -> dict:
    install_reviewed_cases()
    context = cfg_verify.core_ctx("net")
    image = IMAGE.read_bytes()
    proofs = []

    for va, extent, readable_name in ENTRIES:
        source = ROOT / "recon/net/src" / f"FUN_{va:08x}.c"
        if not source.is_file():
            raise FileNotFoundError(source)

        original_extent = context["sizes"].get(va)
        injected = original_extent != extent
        context["sizes"][va] = extent
        result = cfg_verify.verify(
            "net", f"FUN_{va:08x}", trials_random=TRIALS_RANDOM
        )
        if result.get("status") != "PASS":
            raise RuntimeError(f"0x{va:08x}: {result}")
        # Normalize integer selector keys exactly as the durable JSON receipt
        # represents them, so replay comparison is byte-shape stable.
        result = json.loads(json.dumps(result))

        offset = va - 0x01008000
        firmware_bytes = image[offset:offset + extent]
        proofs.append({
            "analysis_address": f"0x{va:08x}",
            "raw_symbol": f"FUN_{va:08x}",
            "readable_identity": readable_name,
            "raw_backmap": f"FUN_{va:08x}@0x{va:08x}",
            "source_path": str(source.relative_to(ROOT)),
            "source_sha256": sha256(source),
            "true_executable_extent": extent,
            "catalog_executable_extent": CATALOG_EXTENTS[va],
            "catalog_size_injected_at_runtime": injected,
            "firmware_extent_sha256": sha256_bytes(firmware_bytes),
            "extent_basis": (
                "switch default owns the terminal BL at 0x0101626c; "
                "code ends 0x01016270"
                if va == 0x01016250 else
                "catalog extent ends immediately after the terminal return"
            ),
            "cfg_request": {
                "verifier": "tools/cfg_verify.py",
                "core": "net",
                "name": f"FUN_{va:08x}",
                "trials_random": TRIALS_RANDOM,
            },
            "cfg_result": result,
        })

    return {
        "schema": "g1.net.link_gap_recovery_receipt.v1",
        "scope": "net-link-gap-2",
        "policy": {
            "canonical_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        },
        "inputs": [{"path": "netcore_image.bin", "sha256": sha256(IMAGE)}],
        "summary": {
            "function_count": len(proofs),
            "cfg_pass_count": len(proofs),
            "total_true_executable_extent": sum(
                proof["true_executable_extent"] for proof in proofs
            ),
        },
        "proofs": proofs,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    actual = build_receipt()
    if args.check:
        expected = json.loads(OUTPUT.read_text())
        if actual != expected:
            raise SystemExit("net-link-gap-2 receipt is stale")
    else:
        OUTPUT.write_text(json.dumps(actual, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
