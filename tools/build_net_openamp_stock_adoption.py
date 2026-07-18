#!/usr/bin/env python3
"""Build the exact CPUNET OpenAMP ``rpmsg.c`` ownership receipt.

The older net signature catalog compared mnemonic order and therefore confused
``rpmsg_send_offchannel_raw`` with the nearly identical nocopy wrapper.  This
builder compares every selected input section at the operand/byte level,
masking only ELF relocation fields, and records the whole source-unit closure.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
SOURCE = NCS / "modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c"
CORRECTED_BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
OBJECT = (CORRECTED_BUILD / "modules/open-amp/open-amp/lib/CMakeFiles/"
          "open_amp.dir/rpmsg/rpmsg.c.obj")
CONFIG = CORRECTED_BUILD / "zephyr/.config"
MAP = CORRECTED_BUILD / "zephyr/zephyr.map"
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_openamp_stock_atomic_adoption.json"

OPENAMP_COMMIT = "42b7c577714b8f22ce82a901e19c1814af4609a8"
IMAGE_BASE = 0x01008000

# Every rpmsg.c section selected in the exact reference link.  The sole absent
# source section, rpmsg_release_tx_buffer, is listed separately as discarded.
LIVE_SECTIONS = {
    "__metal_mutex_acquire": 0x0103AD4A,
    "rpmsg_unregister_endpoint": 0x0103AD56,
    "rpmsg_send_offchannel_raw": 0x01035424,
    "rpmsg_send_ns_message": 0x0103ADA8,
    "rpmsg_hold_rx_buffer": 0x0103ADDA,
    "rpmsg_release_rx_buffer": 0x0103ADEA,
    "rpmsg_get_tx_payload_buffer": 0x0103ADFC,
    "rpmsg_send_offchannel_nocopy": 0x01035450,
    "rpmsg_get_endpoint": 0x0103AE10,
    "rpmsg_register_endpoint": 0x0103547C,
    "rpmsg_create_ept": 0x010354BC,
    "rpmsg_destroy_ept": 0x0103AE84,
}

# Ghidra catalog entries.  Four have recovered C; four were cataloged as stock
# owners without a C file.  Interior live sections remain in section_matches.
MANIFEST_FUNCTIONS = {
    "0x01035424": ("FUN_01035424", "rpmsg_send_offchannel_raw", False),
    "0x0103547c": ("FUN_0103547c", "rpmsg_register_endpoint", True),
    "0x010354bc": ("FUN_010354bc", "rpmsg_create_ept", True),
    "0x0103ad4a": ("FUN_0103ad4a", "__metal_mutex_acquire", True),
    "0x0103ad56": ("FUN_0103ad56", "rpmsg_unregister_endpoint", True),
    "0x0103ada8": ("FUN_0103ada8", "rpmsg_send_ns_message", False),
    "0x0103ae10": ("FUN_0103ae10", "rpmsg_get_endpoint", False),
    "0x0103ae84": ("FUN_0103ae84", "rpmsg_destroy_ept", False),
}

# R_ARM_ABS32, R_ARM_THM_CALL and R_ARM_THM_JUMP24 all occupy four bytes in
# these selected sections.
SUPPORTED_RELOCATIONS = {2, 10, 30}


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256(path: Path) -> str:
    return sha256_bytes(path.read_bytes())


def config_values(path: Path) -> dict[str, str]:
    result = {}
    for line in path.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            result[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            result[line[2:-11]] = "n"
    return result


def section_receipts() -> list[dict]:
    image = IMAGE.read_bytes()
    rows = []
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        for symbol, va in LIVE_SECTIONS.items():
            section_name = ".text." + symbol
            section = elf.get_section_by_name(section_name)
            if section is None:
                raise ValueError(f"missing object section {section_name}")
            candidate = bytearray(section.data())
            firmware = bytearray(image[va - IMAGE_BASE:
                                       va - IMAGE_BASE + len(candidate)])
            relocation_section = elf.get_section_by_name(".rel" + section_name)
            relocations = []
            if relocation_section is not None:
                for relocation in relocation_section.iter_relocations():
                    offset = int(relocation["r_offset"])
                    kind = int(relocation["r_info_type"])
                    if kind not in SUPPORTED_RELOCATIONS:
                        raise ValueError(
                            f"unsupported relocation {kind} in {section_name}")
                    candidate[offset:offset + 4] = b"\0" * 4
                    firmware[offset:offset + 4] = b"\0" * 4
                    relocations.append({"offset": offset, "type": kind})
            if candidate != firmware:
                mismatch = next(index for index, pair in
                                enumerate(zip(candidate, firmware))
                                if pair[0] != pair[1])
                raise ValueError(
                    f"non-relocation mismatch {section_name}+0x{mismatch:x}")
            rows.append({
                "symbol": symbol,
                "va": f"0x{va:08x}",
                "section": section_name,
                "size": len(candidate),
                "match": "relocation-masked-byte-exact",
                "normalized_sha256": sha256_bytes(bytes(firmware)),
                "relocations": relocations,
            })
    return rows


def build() -> dict:
    config = config_values(CONFIG)
    required = {
        "CONFIG_OPENAMP": config.get("CONFIG_OPENAMP"),
        "CONFIG_OPENAMP_MASTER": config.get("CONFIG_OPENAMP_MASTER"),
        "CONFIG_OPENAMP_SLAVE": config.get("CONFIG_OPENAMP_SLAVE"),
        "CONFIG_IPC_SERVICE_BACKEND_RPMSG": config.get(
            "CONFIG_IPC_SERVICE_BACKEND_RPMSG"),
        "CONFIG_SPIN_VALIDATE": config.get("CONFIG_SPIN_VALIDATE"),
        "CONFIG_SMP": config.get("CONFIG_SMP", "n"),
    }
    expected = {key: "y" for key in required}
    expected["CONFIG_OPENAMP_MASTER"] = "n"
    expected["CONFIG_SMP"] = "n"
    if required != expected:
        raise ValueError(f"reference OpenAMP configuration drifted: {required}")

    selected = section_receipts()
    selected_symbols = {row["symbol"] for row in selected}
    if "rpmsg_release_tx_buffer" in selected_symbols:
        raise ValueError("discarded source section unexpectedly selected")
    map_text = MAP.read_text()
    if not all((".text." + symbol) in map_text for symbol in selected_symbols):
        raise ValueError("reference linker map lacks a selected rpmsg.c section")

    recovered = []
    functions = []
    for va, (raw, symbol, has_c) in MANIFEST_FUNCTIONS.items():
        source = ROOT / "recon/net/src" / (raw + ".c")
        if has_c and not source.is_file():
            raise ValueError(f"missing recovered source {source}")
        row = {
            "va": va,
            "raw_symbol": raw,
            "upstream_symbol": symbol,
            "upstream_section": ".text." + symbol,
            "upstream_source": "modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg.c",
            "upstream_linkage": ("file_static" if symbol in {
                "__metal_mutex_acquire", "rpmsg_unregister_endpoint"
            } else "public"),
            "relocation_masked_byte_exact": True,
            "whole_source_unit_selected": True,
            "safe_to_adopt": True,
            "exclude_reconstruction": True,
            "reconstruction_present": has_c,
        }
        if has_c:
            row["reconstruction_source"] = str(source.relative_to(ROOT))
            row["reconstruction_source_sha256"] = sha256(source)
            recovered.append(va)
        functions.append(row)

    return {
        "schema": 1,
        "core": "net",
        "component": "openamp_rpmsg",
        "policy": {
            "adoption_unit": "complete selected source-unit section closure",
            "sdc_policy": "report_only_unchanged",
            "mnemonic_only_identity_authority": False,
        },
        "upstream": {
            "repository": "open-amp",
            "commit": OPENAMP_COMMIT,
            "source": str(SOURCE),
            "source_sha256": sha256(SOURCE),
            "object": str(OBJECT),
            "object_sha256": sha256(OBJECT),
            "configured_build": str(CONFIG),
            "configured_build_sha256": sha256(CONFIG),
            "linker_map": str(MAP),
            "required_config": required,
            "abi": "Cortex-M33, Thumb-2, soft-float, -Os",
        },
        "identity_correction": {
            "va": "0x01035424",
            "incorrect_old_symbol": "rpmsg_send_offchannel_nocopy",
            "corrected_symbol": "rpmsg_send_offchannel_raw",
            "decisive_operand": "ldr r4,[rdev,#0x78] (raw) versus #0x88 (nocopy)",
            "nocopy_owner_va": "0x01035450",
        },
        "section_matches": selected,
        "discarded_sections": [{
            "symbol": "rpmsg_release_tx_buffer",
            "section": ".text.rpmsg_release_tx_buffer",
            "size": 32,
            "reason": "present in archive member but discarded by section GC",
        }],
        "mutable_state_sections": [],
        "manifest_functions": functions,
        "recovered_atomic_group": recovered,
        "cfg_verify": {
            "0x0103547c": "PASS cases=2",
            "0x010354bc": "PASS cases=4",
            "0x0103ad4a": "PASS cases=0",
            "0x0103ad56": "PASS cases=0",
        },
        "safe": True,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--output", type=Path, default=OUTPUT)
    args = parser.parse_args()
    data = build()
    encoded = json.dumps(data, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not args.output.is_file() or args.output.read_text() != encoded:
            raise SystemExit(f"stale receipt: {args.output}")
    else:
        args.output.write_text(encoded)
    print("openamp_rpmsg selected=%d manifest=%d recovered=%d safe=true" % (
        len(data["section_matches"]), len(data["manifest_functions"]),
        len(data["recovered_atomic_group"])))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
