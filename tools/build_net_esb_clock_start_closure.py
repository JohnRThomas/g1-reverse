#!/usr/bin/env python3
"""Build the fail-closed receipt for the CPUNET ESB clock callback closure."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

import cfg_verify
import net_recon_kit


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_esb_clock_start_closure.json"
RUNTIME_DELTA = 0x800
CALLBACK_LITERAL = 0x0102B660
CALLBACK_ANALYSIS = 0x0102B758

ENTRIES = (
    (0x0102B31C, 0xA2, "g1_esb_radio_configure", "product_private", 40),
    (0x0102B3F0, 0x98, "g1_esb_start_announcement", "product_private", 0),
    (0x0102B664, 0x96, "g1_esb_radio_release", "product_private", 0),
    (0x0102B718, 0x30, "g1_esb_transport_start", "product_private", 40),
    (0x0102B758, 0x30, "g1_esb_clock_transition", "product_private", 40),
    (0x01033858, 0x26, "esb_start_tx", "ncs_2_5_1_esb_public", 0),
    (0x010339D0, 0x0E, "esb_tx_full", "ncs_2_5_1_esb_public", 0),
)


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _state(address: int, data: bytes):
    return ({}, [(address, data)])


def install_reviewed_cases() -> None:
    """Install closure-local extents and production-shaped non-argument state."""
    context = cfg_verify.core_ctx("net")
    for va, extent, _name, _owner, _trials in ENTRIES:
        context["sizes"][va] = extent
        cfg_verify.TRUE_SIZE_OVERRIDES[("net", va)] = extent
        net_recon_kit.TRUE_SIZE_OVERRIDES[va] = extent

    # Startup announcement: off, fallback identity, real identity, publish
    # failure, TX-pending retry, and all receive-mode branches. Oracle ordinals
    # are the dynamic call order in this routine.
    mode = lambda value: [(0x21004FA1, bytes((0x5A, value, 0xA5)))]
    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x0102B3F0)] = [
        ({0: 0}, mode(0), {1: {0: 0}}),
        ({0: 0}, mode(1), {}),
        ({0: 1}, mode(0), {1: {0: 0}, 3: {0: 0}, 4: {0: 0}}),
        ({0: 1}, mode(0), {1: {0: 4}, 3: {0: 0}, 4: {0: 0}}),
        ({0: 1}, mode(1), {1: {0: 4}, 3: {0: 0}, 4: {0: 0}}),
        ({0: 1}, mode(1), {1: {0: 4}, 3: {0: 1}}),
        ({0: 1}, mode(2), {1: {0: 4}, 3: {0: 0}}),
    ]

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0102B664)] = [
        _state(0x21004FA1, bytes((0x5A, value))) for value in (0, 1, 2)
    ]
    cfg_verify.ABSOLUTE_READ_TRANSITION_CASES[("net", 0x0102B664)] = [
        [(0x41008110, 2, 1)], [], []
    ]

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x01033858)] = [
        ({}, [(0x21006458, bytes((1,))), (0x21004A88, (0).to_bytes(4, "little"))]),
        ({}, [(0x21006458, bytes((0,))), (0x21004A88, (0).to_bytes(4, "little"))]),
        ({}, [(0x21006458, bytes((0,))), (0x21004A88, (1).to_bytes(4, "little"))]),
    ]
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x010339D0)] = [
        _state(0x21004A88, count.to_bytes(4, "little"))
        for count in (0, 7, 8, 9)
    ]


def build_receipt() -> dict:
    install_reviewed_cases()
    image = IMAGE.read_bytes()
    callback_word = struct.unpack_from(
        "<I", image, CALLBACK_LITERAL - 0x01008000
    )[0]
    expected_runtime_thumb = CALLBACK_ANALYSIS + RUNTIME_DELTA + 1
    if callback_word != expected_runtime_thumb:
        raise RuntimeError(
            f"callback pointer 0x{callback_word:08x} != 0x{expected_runtime_thumb:08x}"
        )

    proofs = []
    for va, extent, readable, owner, trials in ENTRIES:
        source = ROOT / "recon/net/src" / f"FUN_{va:08x}.c"
        result = cfg_verify.verify("net", f"FUN_{va:08x}", trials_random=trials)
        if result.get("status") != "PASS":
            raise RuntimeError(f"0x{va:08x}: {result}")
        result = json.loads(json.dumps(result))
        firmware = image[va - 0x01008000:va - 0x01008000 + extent]
        proofs.append({
            "analysis_address": f"0x{va:08x}",
            "runtime_address": f"0x{va + RUNTIME_DELTA:08x}",
            "raw_symbol": f"FUN_{va:08x}",
            "readable_identity": readable,
            "owner": owner,
            "source": str(source.relative_to(ROOT)),
            "source_sha256": _sha256(source.read_bytes()),
            "true_executable_extent": extent,
            "firmware_extent_sha256": _sha256(firmware),
            "cfg_result": result,
        })

    return {
        "schema": "g1.net.esb_clock_start_closure.v1",
        "ownership": (
            "Product ESB transport glue plus exact configured NCS 2.5.1 ESB "
            "public leaves; this is not an MPSL timeslot closure."
        ),
        "production_root": {
            "analysis_address": f"0x{CALLBACK_ANALYSIS:08x}",
            "raw_symbol": f"FUN_{CALLBACK_ANALYSIS:08x}",
            "evidence_literal_analysis_address": f"0x{CALLBACK_LITERAL:08x}",
            "stored_runtime_thumb_pointer": f"0x{callback_word:08x}",
            "runtime_to_analysis_delta": f"0x{RUNTIME_DELTA:x}",
            "registrar": "FUN_0102b5bc",
        },
        "policy": {
            "canonical_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
            "public_esb_duplicates_retained_pending_exact_source_assembly": True,
        },
        "exact_adopted_descendants": ["memset", "memcpy", "__memcpy_chk"],
        "summary": {
            "function_count": len(proofs),
            "cfg_pass_count": len(proofs),
            "total_true_executable_extent": sum(row[1] for row in ENTRIES),
        },
        "inputs": [{"path": "netcore_image.bin", "sha256": _sha256(image)}],
        "proofs": proofs,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    actual = build_receipt()
    if args.check:
        if actual != json.loads(OUTPUT.read_text()):
            raise SystemExit("ESB clock/start closure receipt is stale")
    else:
        OUTPUT.write_text(json.dumps(actual, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
