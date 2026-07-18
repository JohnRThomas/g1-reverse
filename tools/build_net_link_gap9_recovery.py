#!/usr/bin/env python3
"""Build the fail-closed receipt for retained CPUNET link gap 9."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
VA = 0x0100F6B0
RAW_SYMBOL = "FUN_0100f6b0"
READABLE_IDENTITY = "controller_word_popcount"
EXTENT = 0x38


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def install_reviewed_cases() -> None:
    """Exercise counts 0..32 and patterns used by the sole caller."""
    values = (
        0x00000000,
        0x00000001,
        0x00000002,
        0x00000003,
        0x000000ff,
        0x00010000,
        0x80000000,
        0x55555555,
        0xaaaaaaaa,
        0x01234567,
        0xffffffff,
    )
    cfg_verify.REVIEWED_STATE_CASES[("net", VA)] = [
        ({0: value}, []) for value in values
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", VA)] = 0


def build() -> dict:
    saved_state = dict(cfg_verify.REVIEWED_STATE_CASES)
    saved_nptr = dict(cfg_verify.REVIEWED_NPTR_COUNTS)
    try:
        install_reviewed_cases()
        source = ROOT / "recon/net/src" / f"{RAW_SYMBOL}.c"
        data = source.read_bytes()
        text = data.decode()
        if not all(item in text for item in (
                RAW_SYMBOL, READABLE_IDENTITY, f"0x{VA:08x}")):
            raise RuntimeError(f"missing readable/raw identity in {source}")
        lowered = text.lower()
        if any(marker in lowered for marker in (".incbin", ".byte", "naked")):
            raise RuntimeError(f"forbidden blob-like source in {source}")

        verified = cfg_verify.verify("net", RAW_SYMBOL, trials_random=40)
        if verified.get("status") != "PASS":
            raise RuntimeError(f"CFG verification failed: {verified}")

        firmware = (ROOT / "netcore_image.bin").read_bytes()
        offset = VA - 0x01008000
        row = {
            "analysis_address": f"0x{VA:08x}",
            "raw_symbol": RAW_SYMBOL,
            "readable_identity": READABLE_IDENTITY,
            "archive_family": "softdevice_controller",
            "archive_identity_is_provenance_only": True,
            "true_executable_extent": EXTENT,
            "boundary_evidence": (
                "BX LR at 0x0100f6e6; next entry begins at 0x0100f6e8"
            ),
            "caller": "0x01028112",
            "callees": [],
            "source": source.relative_to(ROOT).as_posix(),
            "source_sha256": _sha256(data),
            "firmware_extent_sha256": _sha256(
                firmware[offset:offset + EXTENT]),
            "cfg_verify": {key: verified[key] for key in (
                "status", "selectors", "pointer_cases", "callback_slots",
                "data_pointer_slots", "cover_cases", "checked")},
        }
    finally:
        cfg_verify.REVIEWED_STATE_CASES.clear()
        cfg_verify.REVIEWED_STATE_CASES.update(saved_state)
        cfg_verify.REVIEWED_NPTR_COUNTS.clear()
        cfg_verify.REVIEWED_NPTR_COUNTS.update(saved_nptr)

    return {
        "schema": "g1.net.link_gap9_recovery.v1",
        "policy": {
            "canonical_readable_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "private_sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        },
        "summary": {
            "function_count": 1,
            "cfg_pass_count": 1,
            "total_true_executable_extent": EXTENT,
            "cfg_checked_trials": verified["checked"],
            "cfg_directed_cover_cases": verified["cover_cases"],
        },
        "functions": [row],
    }


if __name__ == "__main__":
    print(json.dumps(build(), indent=2, sort_keys=True))
