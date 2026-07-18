#!/usr/bin/env python3
"""Build a fail-closed receipt for four retained private CPUNET helpers."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0x0102602E: (
        "FUN_0102602e", "sdc_legacy_adv_report_encode", 0x70,
        "POP return ends at 0x0102609e; FUN_0102609e starts there",
    ),
    0x0102609E: (
        "FUN_0102609e", "sdc_extended_adv_report_encode", 0x84,
        "BX LR ends at 0x01026122; FUN_01026122 starts there",
    ),
    0x01027894: (
        "FUN_01027894", "sdc_intrusive_list_pop_head", 0x28,
        "BX LR ends at 0x010278bc; FUN_010278bc starts there",
    ),
    0x010278BC: (
        "FUN_010278bc", "sdc_intrusive_list_unlink_after", 0x28,
        "BX LR ends at 0x010278e4; FUN_010278e4 starts there",
    ),
}


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _put16(image: bytearray, offset: int, value: int) -> None:
    image[offset:offset + 2] = (value & 0xffff).to_bytes(2, "little")


def _put32(image: bytearray, offset: int, value: int) -> None:
    image[offset:offset + 4] = (value & 0xffffffff).to_bytes(4, "little")


def install_reviewed_cases() -> None:
    """Install branch/state fixtures in this process only."""
    scratch = emu.SCRATCH
    event = scratch + 0x1000
    record = scratch + 0x1800
    payload = scratch + 0x2000

    def report_case(length: int, *, aliased: bool, header: int,
                    tail: int, type_bits: int, flags: int):
        event_image = bytearray(0x300)
        event_image[1] = header
        event_image[3] = tail
        record_image = bytearray(12)
        _put32(record_image, 0, event + 4 if aliased else payload)
        _put16(record_image, 4, type_bits)
        _put16(record_image, 6, length)
        record_image[8] = flags
        record_image[9] = flags >> 2
        memory = [(event, bytes(event_image)), (record, bytes(record_image))]
        if not aliased:
            memory.append((payload, bytes((i & 0xff for i in range(0x300)))))
        return ({0: event, 1: record}, memory)

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0102602E)] = [
        report_case(0, aliased=True, header=0xff, tail=0xa5,
                    type_bits=0xabcd, flags=0),
        report_case(1, aliased=False, header=0x00, tail=0x00,
                    type_bits=0x0123, flags=1),
        report_case(0xfa, aliased=False, header=0xc0, tail=0x3f,
                    type_bits=0xfedc, flags=2),
        report_case(0xfb, aliased=False, header=0x40, tail=0xc0,
                    type_bits=0x8001, flags=3),
        report_case(0xffff, aliased=False, header=0x80, tail=0x7e,
                    type_bits=0x5aa5, flags=0xff),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0102602E)] = 2
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102602E)] = {
        0x01025998: 3,
    }

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0102609E)] = [
        report_case(0, aliased=True, header=0xff, tail=0xff,
                    type_bits=0xabcd, flags=0),
        report_case(1, aliased=False, header=0x00, tail=0x00,
                    type_bits=0x0123, flags=1),
        report_case(0xff, aliased=False, header=0xc0, tail=0x3f,
                    type_bits=0xfedc, flags=2),
        report_case(0x100, aliased=False, header=0x40, tail=0xc0,
                    type_bits=0x8001, flags=3),
        report_case(0xffff, aliased=False, header=0x80, tail=0x7e,
                    type_bits=0x5aa5, flags=0xff),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0102609E)] = 2
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x0102609E)] = {
        0x01025998: 3,
    }

    head = scratch + 0x3000
    first = scratch + 0x3100
    second = scratch + 0x3200

    def list_case(present: bool):
        head_image = bytearray(4)
        memory = [(head, bytes(head_image))]
        if present:
            _put32(head_image, 0, first)
            first_image = bytearray(4)
            _put32(first_image, 0, second)
            memory = [(head, bytes(head_image)),
                      (first, bytes(first_image)), (second, bytes(4))]
        return ({0: head}, memory)

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x01027894)] = [
        list_case(False), list_case(True),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01027894)] = 1

    predecessor = scratch + 0x3300

    def unlink_case(present: bool):
        predecessor_image = bytearray(4)
        memory = [(predecessor, bytes(predecessor_image))]
        if present:
            _put32(predecessor_image, 0, first)
            first_image = bytearray(4)
            _put32(first_image, 0, second)
            memory = [(predecessor, bytes(predecessor_image)),
                      (first, bytes(first_image)), (second, bytes(4))]
        return ({0: predecessor}, memory)

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x010278BC)] = [
        unlink_case(False), unlink_case(True),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x010278BC)] = 1


def build() -> dict:
    saved_state = dict(cfg_verify.REVIEWED_STATE_CASES)
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
                    key: verified[key] for key in (
                        "status", "selectors", "pointer_cases", "callback_slots",
                        "data_pointer_slots", "cover_cases", "checked")
                },
            })
    finally:
        cfg_verify.REVIEWED_STATE_CASES.clear()
        cfg_verify.REVIEWED_STATE_CASES.update(saved_state)
        cfg_verify.REVIEWED_NPTR_COUNTS.clear()
        cfg_verify.REVIEWED_NPTR_COUNTS.update(saved_nptr)
        cfg_verify.REVIEWED_TARGET_CALL_ARITIES.clear()
        cfg_verify.REVIEWED_TARGET_CALL_ARITIES.update(saved_arities)

    return {
        "schema": "g1.net.link_gap7_recovery.v1",
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
