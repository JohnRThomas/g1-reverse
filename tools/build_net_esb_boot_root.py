#!/usr/bin/env python3
"""Prove the missing Zephyr background-thread root and recovered G1 main."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
OBJECT = Path("/private/tmp/g1-net-heap-auto-0718/zephyr/kernel/CMakeFiles/kernel.dir/init.c.obj")
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/kernel/init.c")
MAIN_SOURCE = ROOT / "recon/net/src/FUN_0102a720.c"
OUTPUT = ROOT / "recon/ownership/net_esb_boot_root.json"
BG_VA = 0x01035B20
MAIN_VA = 0x0102A720


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def decode_thumb_call(raw: bytes, va: int) -> int:
    first, second = struct.unpack("<HH", raw)
    s = (first >> 10) & 1
    j1 = (second >> 13) & 1
    j2 = (second >> 11) & 1
    i1, i2 = int(not (j1 ^ s)), int(not (j2 ^ s))
    imm = (s << 24) | (i1 << 23) | (i2 << 22) | ((first & 0x3ff) << 12) | ((second & 0x7ff) << 1)
    if s:
        imm -= 1 << 25
    return ((va + 4 + imm) & 0xffffffff) & ~1


def stock_bg_proof():
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(".text.bg_thread_main")
        relocation = elf.get_section_by_name(".rel.text.bg_thread_main")
        candidate = bytearray(section.data())
        offsets = sorted(int(row["r_offset"]) for row in relocation.iter_relocations())
    firmware = bytearray(IMAGE.read_bytes()[BG_VA - 0x01008000:BG_VA - 0x01008000 + 0x34])
    if len(candidate) != 0x34 or offsets != [0x0a, 0x0e, 0x14, 0x18, 0x1c, 0x2c, 0x30]:
        raise ValueError("unexpected bg_thread_main section/relocations")
    normalized_candidate = bytearray(candidate)
    normalized_firmware = bytearray(firmware)
    for offset in offsets:
        normalized_candidate[offset:offset + 4] = bytes(4)
        normalized_firmware[offset:offset + 4] = bytes(4)
    if normalized_candidate != normalized_firmware:
        raise ValueError("bg_thread_main non-relocation bytes differ")
    calls = [decode_thumb_call(firmware[o:o + 4], BG_VA + o)
             for o in (0x0a, 0x0e, 0x14, 0x18, 0x1c)]
    expected = [0x01035AD8, 0x01038A28, 0x01035AD8, 0x0103601C, MAIN_VA]
    if calls != expected:
        raise ValueError("bg_thread_main call topology differs")
    literals = list(struct.unpack("<II", firmware[0x2c:0x34]))
    if literals != [0x21006461, 0x21004440]:
        raise ValueError("bg_thread_main state literals differ")
    return firmware, offsets, calls, literals


def build():
    firmware, relocations, calls, literals = stock_bg_proof()
    verdict = cfg_verify.verify("net", "FUN_0102a720", trials_random=0)
    if verdict.get("status") != "PASS" or verdict.get("checked") != 5:
        raise ValueError("g1_cpunet_main directed CFG proof failed: %r" % verdict)
    return {
        "schema_version": 1,
        "core": "net",
        "result": "production root and custom main proven",
        "stock_root": {
            "analysis_va": "0x01035b20",
            "identity": "bg_thread_main",
            "extent": 52,
            "source": str(SOURCE),
            "object": str(OBJECT),
            "section": ".text.bg_thread_main",
            "object_sha256": sha(OBJECT.read_bytes()),
            "source_sha256": sha(SOURCE.read_bytes()),
            "firmware_sha256": sha(firmware),
            "relocation_offsets": relocations,
            "normalized_instruction_exact": True,
            "call_targets": ["0x%08x" % value for value in calls],
            "state_literals": ["0x%08x" % value for value in literals],
            "catalog_status": "Ghidra-missed standalone static root",
            "retained_body": "normal configured Zephyr kernel/init.c owner",
        },
        "custom_main": {
            "analysis_va": "0x0102a720",
            "raw_identity": "FUN_0102a720",
            "readable_identity": "g1_cpunet_main",
            "production_identity": "main",
            "catalog_extent": 902,
            "reviewed_true_extent": 1000,
            "source": str(MAIN_SOURCE.relative_to(ROOT)),
            "source_sha256": sha(MAIN_SOURCE.read_bytes()),
            "cfg_status": verdict["status"],
            "directed_cases": verdict["checked"],
            "prefix_events": cfg_verify.REVIEWED_PREFIX_PROOFS[("net", MAIN_VA)],
            "families": ["role-1", "role-2", "other/fallback",
                         "periodic-10s-publication", "hysteresis-publication"],
            "raw_backmap_preserved": True,
        },
        "production_topology": {
            "proven": True,
            "edge": "bg_thread_main +0x1c BL -> g1_cpunet_main",
            "reason": "the exact configured kernel root directly invokes the recovered product main",
        },
        "sdc_policy": "report-only; no SDC source removal or archive substitution",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise SystemExit("stale " + str(OUTPUT))
    else:
        OUTPUT.write_text(text)
        print(OUTPUT)


if __name__ == "__main__":
    main()
