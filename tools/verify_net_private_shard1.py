#!/usr/bin/env python3
"""Authoritative, source-local closure for CPUNET private shard 1.

The entry is absent from the historical Ghidra function catalog, so this
adapter supplies its reviewed extent and production-shaped state cases to the
unchanged cfg_verify engine.  It does not mutate shared catalogs or policy.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from collections import Counter
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB, Cs

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon/net/src/FUN_01014b18.c"
OUTPUT = ROOT / "recon/ownership/net_private_shard1.json"
IMAGE = ROOT / "netcore_image.bin"
VA = 0x01014B18
RUNTIME_VA = 0x01015318
SIZE = 0x1188
BASE = 0x01008000
CONTEXT = emu.SCRATCH + 0x5000
PACKET = emu.SCRATCH + 0x6000
PROCEDURE = emu.SCRATCH + 0x7000
DESCRIPTOR = emu.SCRATCH + 0x7800
EXTERNAL_CALLBACK = 0x01040001

BODY_RANGES = (
    (0x01014B18, 0x01014DE8), (0x01014DFC, 0x010151C4),
    (0x010151D0, 0x010154A8), (0x010154B4, 0x01015618),
    (0x01015624, 0x01015A30), (0x01015A38, 0x01015A6E),
    (0x01015A76, 0x01015A86), (0x01015A8E, 0x01015A9E),
    (0x01015AB0, 0x01015CA0),
)
LITERAL_ISLANDS = (
    (0x01014DE8, 0x01014DFC), (0x010151C4, 0x010151D0),
    (0x01015618, 0x01015624), (0x01015AA8, 0x01015AB0),
    (0x01015CA0, 0x01015CA8),
)
DISPATCH_TABLE_ISLANDS = (
    (0x010154A8, 0x010154B4), (0x01015A30, 0x01015A38),
    (0x01015A6E, 0x01015A76), (0x01015A86, 0x01015A8E),
    (0x01015A9E, 0x01015AA8),
)

EXPECTED_DIRECT_CALLS = {
    0x01008D00: 7, 0x010091F8: 2, 0x0100A17C: 1,
    0x0100B608: 1, 0x0100B614: 1,
    0x0100B624: 1, 0x0100B630: 1, 0x0100D3C0: 19,
    0x0100D5D0: 1, 0x0100E5D8: 1, 0x0100E610: 1,
    0x0100EF88: 2, 0x0100EFC8: 1, 0x0100F110: 2,
    0x0100F1F8: 1, 0x0100F784: 2, 0x0100F7B0: 1,
    0x0100F7D0: 1, 0x0100F7E0: 1, 0x0100F834: 1,
    0x0100FAE4: 1, 0x010108B8: 1, 0x01013E98: 5,
    0x01014884: 1, 0x01016250: 2, 0x0101F934: 1,
    0x010209E0: 1, 0x010209F0: 1, 0x01026D16: 1,
    0x01029882: 1,
}
EXPECTED_INDIRECT_CALLS = (
    0x01014C5C, 0x01014DD4, 0x01014F6C, 0x0101533E,
    0x01015416, 0x010157F2, 0x01015B8E,
)


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def base_memory(flags: int = 0, packet_type: int = 0xFF,
                callback: int = 0) -> tuple[bytearray, bytearray, list]:
    global_state = bytearray(0x28)
    context = bytearray(0x400)
    packet = bytearray(0x100)
    procedure = bytearray(0x100)
    struct.pack_into("<I", global_state, 4, CONTEXT)
    struct.pack_into("<I", global_state, 8, callback)
    struct.pack_into("<H", global_state, 0x0C, flags)
    struct.pack_into("<I", global_state, 0x10, PACKET)
    struct.pack_into("<I", global_state, 0x14, PROCEDURE)
    struct.pack_into("<I", context, 0xEC, 100)
    packet[3] = packet_type
    memory = [
        (0x21000F68, bytes(global_state)), (CONTEXT, bytes(context)),
        (PACKET, bytes(packet)), (PROCEDURE, bytes(procedure)),
        (0x21000124, bytes(0xB0)), (0x210001D0, bytes(16)),
        (0x21000204, bytes(16)), (0x2100020C, bytes(16)),
    ]
    return global_state, context, memory


def replace_memory(memory: list, address: int, value: bytes) -> None:
    for index, row in enumerate(memory):
        if row[0] == address:
            memory[index] = (address, value)
            return
    memory.append((address, value))


def argument_or_flag_case(flags: int, argument0: int = 0,
                          argument1: int = 0):
    _global, context, memory = base_memory(flags)
    context[0x14E] = 0
    context[0x0C7] = 7
    replace_memory(memory, CONTEXT, bytes(context))
    return ({0: argument0, 1: argument1}, memory, {0: {0: 0x1234}})


def c6_dispatch_case(selector: int):
    _global, context, memory = base_memory()
    context[0x14E] = 0xFE
    context[0x0C6] = selector
    replace_memory(memory, CONTEXT, bytes(context))
    # a17c succeeds; category 1 clears; category 4 selects the TBB family.
    return ({0: 0, 1: 0}, memory,
            {0: {0: 0x1234}, 1: {0: 0}, 2: {0: 1}})


def phy_dispatch_case(outer: int, inner: int, update_result: int):
    _global, context, memory = base_memory()
    context[0x14E] = 0xFE
    context[0x06E] = outer
    context[0x06F] = inner
    context[0x16C] = 1
    context[0x16D] = 0
    context[0x16E] = outer
    context[0x16F] = 1 if inner == 1 else 2 if inner == 2 else 4
    replace_memory(memory, CONTEXT, bytes(context))
    # Drive the classifier chain to the nested outer/inner PHY switches.
    oracles = {
        0: {0: 0x1234}, 1: {0: 0}, 2: {0: 0}, 3: {0: 0},
        4: {0: 1}, 5: {0: 0}, 6: {0: update_result},
    }
    return ({0: 0, 1: 0}, memory, oracles)


def event_callback_case(publish_descriptor: bool):
    _global, context, memory = base_memory(callback=EXTERNAL_CALLBACK)
    context[0x14E] = 0
    replace_memory(memory, CONTEXT, bytes(context))
    memory.append((DESCRIPTOR, b"\xff\x00" + bytes(30)))
    writes = {}
    if publish_descriptor:
        writes[1] = [
            (0, 0x0C, DESCRIPTOR.to_bytes(4, "little"), 0x01040000),
            (0, 0x10, b"\x02", 0x01040000),
        ]
    return ({0: 1, 1: 0}, memory,
            {0: {0: 0x1234}, 1: {0: 0}}, writes)


def packet_dispatch_case():
    _global, context, memory = base_memory(flags=1, packet_type=2)
    context[0x14E] = 0
    table = bytearray(0xB0)
    struct.pack_into("<I", table, 2 * 4, EXTERNAL_CALLBACK)
    replace_memory(memory, CONTEXT, bytes(context))
    replace_memory(memory, 0x21000124, bytes(table))
    return ({0: 0, 1: 0}, memory,
            {0: {0: 0x1234}, 1: {0: 0}, 2: {0: 1}, 3: {0: 0}})


def reviewed_cases() -> tuple[list, dict[str, int]]:
    flags = (0, 1, 2, 4, 8, 0x40, 0x100, 0x200, 0x800, 0x300, 0xF4F)
    argument_values = (0, 1, 2, 3, 8, 0x10, 0x20, 0x38, 0xFF)
    cases = [argument_or_flag_case(value) for value in flags]
    cases += [argument_or_flag_case(0, argument0, argument1)
              for argument0 in (0, 1) for argument1 in argument_values]
    counts = {"argument_and_global_flag_cases": len(cases)}

    dispatch = [c6_dispatch_case(value)
                for value in tuple(range(0x12, 0x1E)) + (0x30,)]
    cases += dispatch
    counts["c6_tbb_cases"] = len(dispatch)

    phy = [phy_dispatch_case(outer, inner, result)
           for outer in (1, 2, 4, 8) for inner in (1, 2, 4, 8)
           for result in (0, 1)]
    cases += phy
    counts["nested_phy_cases"] = len(phy)

    callbacks = [event_callback_case(False), event_callback_case(True)]
    cases += callbacks
    counts["event_callback_cases"] = len(callbacks)
    cases.append(packet_dispatch_case())
    counts["packet_table_callback_cases"] = 1
    return cases, counts


def call_closure(image: bytes) -> tuple[dict[int, int], tuple[int, ...]]:
    decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    direct = Counter()
    indirect = []
    for start, end in BODY_RANGES:
        code = image[start - BASE:end - BASE]
        for insn in decoder.disasm(code, start):
            if insn.mnemonic == "bl":
                direct[int(insn.op_str.lstrip("#"), 0)] += 1
            elif insn.mnemonic == "blx" and not insn.op_str.startswith("#"):
                indirect.append(insn.address)
    return dict(sorted(direct.items())), tuple(indirect)


def verify() -> dict:
    source = SOURCE.read_bytes()
    text = source.decode()
    if not text.startswith("/* net-core FUN_01014b18 @ 0x01014b18"):
        raise ValueError("raw address/backmap header missing")
    if ".incbin" in text or "__asm__" in text or "__attribute__((naked))" in text:
        raise ValueError("blob/assembly substitution is forbidden")
    image = IMAGE.read_bytes()
    direct, indirect = call_closure(image)
    if direct != EXPECTED_DIRECT_CALLS:
        raise ValueError(f"direct call closure drift: {direct}")
    if indirect != EXPECTED_INDIRECT_CALLS:
        raise ValueError(f"indirect call closure drift: {indirect}")

    context = cfg_verify.core_ctx("net")
    previous_size = context["sizes"].get(VA)
    key = ("net", VA)
    saved_cases = cfg_verify.REVIEWED_ORACLE_CASES.get(key)
    saved_nptr = cfg_verify.REVIEWED_NPTR_COUNTS.get(key)
    saved_stack = cfg_verify.REVIEWED_STACK_POINTER_CALLS.get(key)
    context["sizes"][VA] = SIZE
    try:
        cfg_verify.REVIEWED_ORACLE_CASES.pop(key, None)
        cfg_verify.REVIEWED_NPTR_COUNTS[key] = 0
        cfg_verify.REVIEWED_STACK_POINTER_CALLS.pop(key, None)
        generic = cfg_verify.verify("net", "FUN_01014b18", trials_random=40)
        cases, counts = reviewed_cases()
        cfg_verify.REVIEWED_ORACLE_CASES[key] = cases
        cfg_verify.REVIEWED_STACK_POINTER_CALLS[key] = {1: {0}}
        reviewed = cfg_verify.verify("net", "FUN_01014b18", trials_random=0)
    finally:
        if previous_size is None:
            context["sizes"].pop(VA, None)
        else:
            context["sizes"][VA] = previous_size
        for mapping, old in (
            (cfg_verify.REVIEWED_ORACLE_CASES, saved_cases),
            (cfg_verify.REVIEWED_NPTR_COUNTS, saved_nptr),
            (cfg_verify.REVIEWED_STACK_POINTER_CALLS, saved_stack),
        ):
            if old is None:
                mapping.pop(key, None)
            else:
                mapping[key] = old
    if generic.get("status") != "PASS" or reviewed.get("status") != "PASS":
        raise ValueError({"generic": generic, "reviewed": reviewed})

    return {
        "schema": 1,
        "core": "net",
        "shard": "net-private-1",
        "status": "cfg_verified",
        "function": {
            "analysis_address": "0x01014b18",
            "runtime_address": "0x01015318",
            "raw_symbol": "FUN_01014b18",
            "readable_identity": "sdc_conn_event_process",
            "source": str(SOURCE.relative_to(ROOT)),
            "source_sha256": sha256(source),
            "true_executable_extent": SIZE,
            "body_ranges": [[f"0x{start:08x}", f"0x{end:08x}"]
                            for start, end in BODY_RANGES],
            "literal_islands": [[f"0x{start:08x}", f"0x{end:08x}"]
                                for start, end in LITERAL_ISLANDS],
            "dispatch_table_islands": [
                [f"0x{start:08x}", f"0x{end:08x}"]
                for start, end in DISPATCH_TABLE_ISLANDS],
            "blob_or_archive_substitution": False,
            "raw_backmap_preserved": True,
        },
        "inputs": {
            "firmware": "netcore_image.bin",
            "firmware_sha256": sha256(image),
        },
        "cfg_verification": {
            "engine": "tools/cfg_verify.py",
            "generic_status": generic["status"],
            "generic_checked": generic["checked"],
            "generic_selectors": {str(argument): values for argument, values
                                  in generic["selectors"].items()},
            "reviewed_status": reviewed["status"],
            "reviewed_checked": reviewed["checked"],
            "reviewed_case_counts": counts,
            "total_checked": generic["checked"] + reviewed["checked"],
        },
        "call_state_closure": {
            "direct_callsite_count": sum(direct.values()),
            "direct_targets": {f"0x{target:08x}": count
                               for target, count in direct.items()},
            "indirect_callsites": [f"0x{address:08x}" for address in indirect],
            "terminal_tail_target": "FUN_0100a984@0x0100a984",
            "global_controller_record": "0x21000f68",
            "event_callback_stack_record_bytes": 20,
            "covered_state_families": [
                "argument bits and global event flags",
                "all c6 TBB arms plus default",
                "all valid outer/inner PHY switch combinations",
                "both PHY update outcomes",
                "event callback with and without descriptor publication",
                "packet handler-table indirect dispatch",
            ],
        },
        "policy": {
            "sdc_library_removal": "report_only_unchanged",
            "shared_catalogs_or_cfg_modified": False,
        },
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    result = verify()
    if args.check:
        if json.loads(OUTPUT.read_text()) != result:
            raise SystemExit("net-private-1 receipt is stale")
    else:
        OUTPUT.write_text(json.dumps(result, indent=1, sort_keys=True) + "\n")
    print("net-private-1: authoritative CFG PASS",
          result["cfg_verification"]["total_checked"], "cases")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
