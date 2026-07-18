#!/usr/bin/env python3
"""Build the fail-closed receipt for the sixth retained CPUNET gap shard."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0x0100D3A0: ("FUN_0100d3a0", "reverse_copy_u8", 0x1E,
                 "BX LR at 0x0100d3bc; next entry is 0x0100d3c0"),
    0x0100F5B4: ("FUN_0100f5b4", "controller_payload_time_get", 0x16,
                 "BX LR at 0x0100f5c8; next entry is 0x0100f5cc"),
    0x01019088: ("FUN_01019088", "controller_state_is_eligible", 0x38,
                 "BX LR at 0x010190be; literal at 0x010190c0 follows"),
    0x01025FD4: ("FUN_01025fd4", "controller_feature_pair_enabled", 0x1C,
                 "POP return at 0x01025fee; next entry is 0x01025ff0"),
}


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def install_reviewed_cases() -> None:
    scratch = emu.SCRATCH

    destination, source = scratch + 0x1000, scratch + 0x1400
    source_image = bytes((index * 29 + 7) & 0xff for index in range(0x200))
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0100D3A0)] = [
        ({0: destination, 1: source, 2: length},
         [(destination, bytes(0x200)), (source, source_image)])
        for length in (0, 1, 4, 0xff, 0x100, 0x101)
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0100D3A0)] = 2

    timing = scratch + 0x2000
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0100F5B4)] = [
        ({0: timing, 1: overhead},
         [(timing, total.to_bytes(4, "little"))])
        for total, overhead in (
            (0x9b, 0), (0x9c, 0), (0x9d, 0),
            (0x19c, 0x100), (0x19d, 0x100),
            (0xffffffff, 0xffffff63),
        )
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0100F5B4)] = 1

    def controller_state(mode: int, flags: int, active: int):
        image = bytearray(0x58)
        image[0x54:0x57] = bytes((mode, flags, active))
        return ({}, [(0x21000F90, bytes(image))])

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x01019088)] = [
        controller_state(mode, flags, active)
        for mode, flags, active in (
            (0, 1, 0), (1, 1, 0), (1, 3, 0),
            (2, 1, 0), (2, 5, 0), (3, 0, 0),
            (3, 0, 1), (4, 1, 1),
        )
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01019088)] = 0

    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01025FD4)] = [
        ({0: 0x3d, 1: 5}, [], {0: {0: 1}}),
        ({0: 0x3e, 1: 5}, [], {0: {0: 0}}),
        ({0: 0x3e, 1: 5}, [], {0: {0: 1}, 1: {0: 0}}),
        ({0: 0x3e, 1: 0x1a}, [], {0: {0: 1}, 1: {0: 1}}),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01025FD4)] = 0
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x01025FD4)] = {
        0x0100930C: 1, 0x0100938C: 1,
    }


def build() -> dict:
    saved_state = dict(cfg_verify.REVIEWED_STATE_CASES)
    saved_oracle = dict(cfg_verify.REVIEWED_ORACLE_CASES)
    saved_nptr = dict(cfg_verify.REVIEWED_NPTR_COUNTS)
    saved_arities = dict(cfg_verify.REVIEWED_TARGET_CALL_ARITIES)
    rows = []
    try:
        install_reviewed_cases()
        firmware = (ROOT / "netcore_image.bin").read_bytes()
        for va, (symbol, readable, extent, boundary) in EXPECTED.items():
            source = ROOT / "recon/net/src" / f"{symbol}.c"
            data = source.read_bytes()
            text = data.decode()
            if symbol not in text or f"0x{va:08x}" not in text or readable not in text:
                raise RuntimeError(f"missing readable/raw identity in {source}")
            lowered = text.lower()
            if any(marker in lowered for marker in (".incbin", ".byte", "naked")):
                raise RuntimeError(f"forbidden blob-like source in {source}")
            verified = cfg_verify.verify("net", symbol, trials_random=40)
            if verified.get("status") != "PASS":
                raise RuntimeError(f"CFG verification failed for {symbol}: {verified}")
            offset = va - 0x01008000
            rows.append({
                "analysis_address": f"0x{va:08x}",
                "raw_symbol": symbol,
                "readable_identity": readable,
                "archive_family": "softdevice_controller",
                "archive_identity_is_provenance_only": True,
                "true_executable_extent": extent,
                "boundary_evidence": boundary,
                "source": source.relative_to(ROOT).as_posix(),
                "source_sha256": _sha256(data),
                "firmware_extent_sha256": _sha256(firmware[offset:offset + extent]),
                "cfg_verify": {key: verified[key] for key in (
                    "status", "selectors", "pointer_cases", "callback_slots",
                    "data_pointer_slots", "cover_cases", "checked")},
            })
    finally:
        cfg_verify.REVIEWED_STATE_CASES.clear()
        cfg_verify.REVIEWED_STATE_CASES.update(saved_state)
        cfg_verify.REVIEWED_ORACLE_CASES.clear()
        cfg_verify.REVIEWED_ORACLE_CASES.update(saved_oracle)
        cfg_verify.REVIEWED_NPTR_COUNTS.clear()
        cfg_verify.REVIEWED_NPTR_COUNTS.update(saved_nptr)
        cfg_verify.REVIEWED_TARGET_CALL_ARITIES.clear()
        cfg_verify.REVIEWED_TARGET_CALL_ARITIES.update(saved_arities)

    return {
        "schema": "g1.net.link_gap6_recovery.v1",
        "policy": {
            "canonical_readable_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "private_sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        },
        "summary": {
            "function_count": len(rows),
            "cfg_pass_count": sum(row["cfg_verify"]["status"] == "PASS" for row in rows),
            "total_true_executable_extent": sum(row["true_executable_extent"] for row in rows),
            "cfg_checked_trials": sum(row["cfg_verify"]["checked"] for row in rows),
            "cfg_directed_cover_cases": sum(row["cfg_verify"]["cover_cases"] for row in rows),
        },
        "functions": rows,
    }


if __name__ == "__main__":
    print(json.dumps(build(), indent=2, sort_keys=True))
