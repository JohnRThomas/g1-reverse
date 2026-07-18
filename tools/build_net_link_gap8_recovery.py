#!/usr/bin/env python3
"""Build a fail-closed proof receipt for four retained CPUNET targets."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0x01027AD2: (
        "FUN_01027ad2", "sdc_double_buffer_bank_base", 0x20,
        "BX LR ends at 0x01027af2; FUN_01027af2 starts there",
    ),
    0x01027FA6: (
        "FUN_01027fa6", "sdc_double_buffer_has_slot_value", 0x46,
        "POP {r7,pc} ends at 0x01027fec; FUN_01027fec starts there",
    ),
    0x01028112: (
        "FUN_01028112", "controller_access_address_conflict", 0x22,
        "final branch rejoins POP ending at 0x01028134; FUN_01028134 starts there",
    ),
    0x010283A4: (
        "FUN_010283a4", "controller_state_is_4_or_5", 0x14,
        "POP {r3,pc} ends at 0x010283b8; FUN_010283b8 starts there",
    ),
}


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def install_reviewed_cases() -> None:
    """Install branch-complete, production-shaped fixtures process-locally."""
    state = emu.SCRATCH + 0x1000

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x01027AD2)] = [
        ({0: 0}, []), ({0: 1}, []), ({0: 0x100}, []),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01027AD2)] = 0

    def slots(side: int, bank: int, first: int, second: int):
        image = bytearray(0x20)
        image[(0x0c + bank) * 2:(0x0c + bank) * 2 + 2] = \
            first.to_bytes(2, "little")
        image[(0x0d + bank) * 2:(0x0d + bank) * 2 + 2] = \
            second.to_bytes(2, "little")
        return ({0: state, 1: side}, [(state, bytes(image))], {0: {0: bank}})

    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01027FA6)] = [
        slots(0, 2, 0, 0),
        slots(0, 2, 0x1234, 0),
        slots(0, 2, 0, 0x5678),
        slots(1, 0, 0, 0),
        slots(1, 0, 0x1234, 0),
        slots(1, 0, 0, 0x5678),
        slots(0x100, 2, 0x1234, 0),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01027FA6)] = 1
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x01027FA6)] = {
        0x01027AD2: 1,
    }

    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01028112)] = [
        ({0: 0x8e89bed6, 1: 0x8e89bed6, 2: 0}, [], {}),
        ({0: 0x8e89bed6, 1: 0x8e89bed7, 2: 0}, [], {}),
        ({0: 0x8e89bed6, 1: 0x8e89bed7, 2: 1}, [], {0: {0: 1}}),
        ({0: 0x8e89bed6, 1: 0x8e89bed4, 2: 1}, [], {0: {0: 2}}),
        ({0: 0x8e89bed6, 1: 0x8e89bed4, 2: 7}, [], {0: {0: 0}}),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01028112)] = 0
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x01028112)] = {
        0x0100F6B0: 1,
    }

    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x010283A4)] = [
        ({}, [], {0: {0: value}}) for value in (3, 4, 5, 6, 0x104)
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x010283A4)] = 0
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x010283A4)] = {
        0x0101B74C: 0,
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
            if ".incbin" in lowered or "__attribute__((naked))" in lowered:
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
                "firmware_extent_sha256": _sha256(
                    firmware[offset:offset + extent]),
                "cfg_verify": {
                    **{key: verified[key] for key in (
                        "status", "pointer_cases", "callback_slots",
                        "data_pointer_slots", "cover_cases", "checked")},
                    "selectors": {
                        str(key): values
                        for key, values in verified["selectors"].items()
                    },
                },
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
        "schema": "g1.net.link_gap8_recovery.v1",
        "policy": {
            "canonical_readable_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "private_sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        },
        "summary": {
            "function_count": len(rows),
            "cfg_pass_count": sum(row["cfg_verify"]["status"] == "PASS"
                                  for row in rows),
            "total_true_executable_extent": sum(
                row["true_executable_extent"] for row in rows),
            "cfg_checked_trials": sum(row["cfg_verify"]["checked"] for row in rows),
            "cfg_directed_cover_cases": sum(
                row["cfg_verify"]["cover_cases"] for row in rows),
        },
        "functions": rows,
    }


if __name__ == "__main__":
    print(json.dumps(build(), indent=2, sort_keys=True))
