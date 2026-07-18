#!/usr/bin/env python3
"""Build the fail-closed receipt for four retained CPUNET controller gaps."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "recon/ownership/net_link_gap5_recovery.json"
TARGETS = {
    0x01028010: (0x24, "controller_primary_slot_is_configured"),
    0x01028034: (0x8A, "controller_active_slot_value_get"),
    0x01028134: (0x122, "controller_access_address_conflicts"),
    0x010283B8: (0x46, "controller_group2_activity_busy"),
}


def _hash(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def _slot_value_cases():
    base = emu.SCRATCH + 0x1000
    cases = []
    for slot, first_state, second_state in (
            (2, 2, 0), (2, 0, 2), (0, 3, 0), (0, 0, 3), (2, 1, 4)):
        image = bytearray(0x40)
        image[0x14 + slot] = first_state
        image[0x15 + slot] = second_state
        image[2 * (0x0C + slot):2 * (0x0C + slot) + 2] = \
            (0x2468).to_bytes(2, "little")
        image[2 * (0x0D + slot):2 * (0x0D + slot) + 2] = \
            (0x1357).to_bytes(2, "little")
        cases.append(({0: base}, [(base, bytes(image))], {0: {0: slot}}))
    return cases


def _access_address_cases():
    item = emu.SCRATCH + 0x1800
    pointer = int(item).to_bytes(4, "little")
    # All seven families empty; first family collides immediately; and one
    # non-conflicting item followed by exhaustion and six empty families.
    return [
        ({0: 0x8E89BED6, 1: 0}, [],
         {i: {0: 2} for i in range(7)}),
        ({0: 0x8E89BED6, 1: 1}, [(item, bytes(0x200))],
         {0: {0: 0}, 1: {0: 1}},
         {0: [(0, 0, pointer, 0x01009DD8)]}),
        ({0: 0x8E89BED6, 1: 1}, [(item, bytes(0x200))],
         {0: {0: 0}, 1: {0: 0}, **{i: {0: 2} for i in range(2, 9)}},
         {0: [(0, 0, pointer, 0x01009DD8)]}),
    ]


def _activity_cases():
    item = emu.SCRATCH + 0x1C00
    pointer = int(item).to_bytes(4, "little")
    return [
        ({}, [], {0: {0: 1}, 1: {0: 1}}),
        ({}, [], {0: {0: 1}, 1: {0: 0}, 2: {0: 2}}),
        ({}, [], {0: {0: 0}, 1: {0: 2}}),
        ({}, [(item, bytes(0x140))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 0}, 3: {0: 2}},
         {1: [(0, 0, pointer, 0x01009DD8)]}),
        ({}, [(item, bytes(0x140))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 1}, 3: {0: 0}, 4: {0: 2}},
         {1: [(0, 0, pointer, 0x01009DD8)]}),
        ({}, [(item, bytes(0x140))],
         {0: {0: 0}, 1: {0: 0}, 2: {0: 1}, 3: {0: 1}},
         {1: [(0, 0, pointer, 0x01009DD8)]}),
    ]


DIRECTED = {
    0x01028010: [({}, [], {0: {0: 0}}), ({}, [], {0: {0: 7}})],
    0x01028034: _slot_value_cases(),
    0x01028134: _access_address_cases(),
    0x010283B8: _activity_cases(),
}


def _verify(va: int, symbol: str, source: str) -> dict:
    key = ("net", va)
    old_cases = cfg_verify.REVIEWED_ORACLE_CASES.get(key)
    old_stack = cfg_verify.REVIEWED_STACK_POINTER_CALLS.get(key)
    try:
        cfg_verify.REVIEWED_ORACLE_CASES[key] = DIRECTED[va]
        if va == 0x01028134:
            cfg_verify.REVIEWED_STACK_POINTER_CALLS[key] = {
                i: {0} for i in range(9)
            }
        elif va == 0x010283B8:
            cfg_verify.REVIEWED_STACK_POINTER_CALLS[key] = {
                i: {0} for i in range(1, 5)
            }
        verdict = cfg_verify.verify(
            "net", symbol, trials_random=0, source_override=source)
    finally:
        if old_cases is None:
            cfg_verify.REVIEWED_ORACLE_CASES.pop(key, None)
        else:
            cfg_verify.REVIEWED_ORACLE_CASES[key] = old_cases
        if old_stack is None:
            cfg_verify.REVIEWED_STACK_POINTER_CALLS.pop(key, None)
        else:
            cfg_verify.REVIEWED_STACK_POINTER_CALLS[key] = old_stack
    if verdict.get("status") != "PASS":
        raise RuntimeError(f"directed CFG proof failed for {symbol}: {verdict}")
    return verdict


def build() -> dict:
    rows = []
    for va, (extent, readable) in TARGETS.items():
        raw = f"FUN_{va:08x}"
        path = ROOT / "recon/net/src" / f"{raw}.c"
        source = path.read_text()
        address = re.search(r"@\s+(0x[0-9a-fA-F]+)", source.splitlines()[0])
        if not address or int(address.group(1), 16) != va:
            raise RuntimeError(f"bad provenance header: {path}")
        if raw not in source or f"#define {readable} {raw}" not in source:
            raise RuntimeError(f"missing readable/raw backmap: {path}")
        if any(marker in source.lower() for marker in (".incbin", ".byte", ".inst")):
            raise RuntimeError(f"blob-like retained source: {path}")
        verdict = _verify(va, raw, source)
        rows.append({
            "analysis_address": f"0x{va:08x}",
            "raw_symbol": raw,
            "readable_symbol": readable,
            "true_executable_extent": extent,
            "extent_basis": "catalog boundary confirmed by terminal return and next entry",
            "source": path.relative_to(ROOT).as_posix(),
            "source_sha256": _hash(path),
            "cfg_verify": {
                "status": verdict["status"],
                "checked": verdict["checked"],
                "directed_cases": len(DIRECTED[va]),
                "cover_cases": verdict.get("cover_cases", 0),
            },
        })
    return {
        "schema": "g1.net.link_gap_recovery.v1",
        "cluster": "net-link-gap-5",
        "policy": {
            "canonical_readable_c_only": True,
            "raw_address_backmaps_required": True,
            "private_controller_sdc": "retained_report_only",
            "archive_or_stock_substitution_forbidden": True,
            "authoritative_verifier": "tools/cfg_verify.py",
            "directed_cases_are_process_local": True,
            "shared_generated_and_cfg_outputs_untouched": True,
        },
        "summary": {
            "function_count": len(rows),
            "total_true_executable_extent": sum(r["true_executable_extent"] for r in rows),
            "cfg_pass_count": sum(r["cfg_verify"]["status"] == "PASS" for r in rows),
            "directed_case_count": sum(r["cfg_verify"]["directed_cases"] for r in rows),
            "checked_case_count": sum(r["cfg_verify"]["checked"] for r in rows),
        },
        "functions": rows,
    }


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=2, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.is_file() or OUTPUT.read_text() != rendered:
            raise SystemExit("net link-gap-5 receipt is stale")
    else:
        OUTPUT.write_text(rendered)


if __name__ == "__main__":
    main()
