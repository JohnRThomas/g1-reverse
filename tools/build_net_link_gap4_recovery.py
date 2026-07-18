#!/usr/bin/env python3
"""Build the fail-closed receipt for four retained private CPUNET targets."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
EXPECTED = {
    0x010271DA: (
        "FUN_010271da", "sdc_free_list_advance", 0x1C,
        "BX LR ends at 0x010271f6; FUN_010271f6 starts there",
    ),
    0x0102722C: (
        "FUN_0102722c", "sdc_free_block_can_split", 0x2C,
        "BX LR ends at 0x01027258; FUN_01027258 starts there",
    ),
    0x010278E4: (
        "FUN_010278e4", "sdc_intrusive_list_remove", 0x90,
        "POP return ends at 0x01027974; FUN_01027974 starts there",
    ),
    0x01027E1C: (
        "FUN_01027e1c", "sdc_double_buffer_take_ready", 0xB8,
        "POP return ends at 0x01027ed4; FUN_01027ed4 starts there",
    ),
}


def _sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def _put16(image: bytearray, offset: int, value: int) -> None:
    image[offset:offset + 2] = int(value).to_bytes(2, "little")


def _put32(image: bytearray, offset: int, value: int) -> None:
    image[offset:offset + 4] = int(value).to_bytes(4, "little")


def install_reviewed_cases() -> None:
    """Install production-shaped branch fixtures in this process only."""
    scratch = emu.SCRATCH

    head, node, following = scratch + 0x1000, scratch + 0x1100, scratch + 0x1200
    head_image, node_image = bytearray(8), bytearray(8)
    _put32(head_image, 0, node)
    _put32(node_image, 0, following)
    cfg_verify.REVIEWED_STATE_CASES[("net", 0x010271DA)] = [
        ({0: head}, [(head, bytes(head_image)), (node, bytes(node_image))]),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x010271DA)] = 1

    block = scratch + 0x2000

    def split_case(capacity: int, payload: int):
        image = bytearray(8)
        _put16(image, 4, capacity)
        return ({0: block, 1: payload}, [(block, bytes(image))])

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x0102722C)] = [
        split_case(7, 0), split_case(8, 0),
        split_case(14, 7), split_case(15, 7),
        split_case(0, 0xFFFF), split_case(7, 0xFFFF),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0102722C)] = 1

    list_head = scratch + 0x3000
    first, second, third = scratch + 0x3100, scratch + 0x3200, scratch + 0x3300

    def list_case(target: int, nodes: list[int]):
        image = bytearray(4)
        _put32(image, 0, nodes[0] if nodes else 0)
        memory = [(list_head, bytes(image))]
        for index, address in enumerate(nodes):
            link = bytearray(4)
            _put32(link, 0, nodes[index + 1] if index + 1 < len(nodes) else 0)
            memory.append((address, bytes(link)))
        return ({0: list_head, 1: target}, memory)

    cfg_verify.REVIEWED_STATE_CASES[("net", 0x010278E4)] = [
        list_case(first, [first, second, third]),
        list_case(second, [first, second, third]),
        list_case(third, [first, second, third]),
        list_case(scratch + 0x3400, [first, second, third]),
        list_case(first, []),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x010278E4)] = 2
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x010278E4)] = {
        0x01027894: 1, 0x010278BC: 1,
    }

    state, output = scratch + 0x4000, scratch + 0x4100

    def buffer_case(status: list[int], base: int, *, mode: int = 1,
                    output_address: int = output, busy: int = 0):
        image = bytearray(0x30)
        image[2] = busy
        for index, value in enumerate(status):
            image[0x14 + index] = value
        for index in range(4):
            _put32(image, 4 + index * 4, 0x11110000 + index)
            _put16(image, 0x18 + index * 2, 0x2200 + index)
        memory = [(state, bytes(image))]
        if output_address:
            memory.append((output_address, bytes(8)))
        return ({0: state, 1: output_address, 2: mode}, memory,
                {0: {0: base}})

    cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01027E1C)] = [
        # The high bits prove the raw AAPCS mode is explicitly narrowed.
        buffer_case([2, 0, 0, 0], 0, mode=0x12340001),
        buffer_case([0, 2, 0, 0], 0),
        buffer_case([0, 0, 0, 0], 0),
        buffer_case([0, 0, 2, 0], 2, mode=0),
        buffer_case([0, 0, 0, 2], 2, mode=0),
        buffer_case([2, 0, 0, 0], 0, output_address=0),
        buffer_case([2, 0, 0, 0], 0, busy=1),
    ]
    cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01027E1C)] = 2
    cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x01027E1C)] = {
        0x01027AD2: 1,
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
                    key: verified[key] for key in (
                        "status", "selectors", "pointer_cases", "callback_slots",
                        "data_pointer_slots", "cover_cases", "checked")
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
        "schema": "g1.net.link_gap4_recovery.v1",
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
