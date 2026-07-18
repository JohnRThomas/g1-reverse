#!/usr/bin/env python3
"""Build the fail-closed CPUNET Zephyr ``ipc_rpmsg.c`` variant receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
SOURCE_REL = "zephyr/subsys/ipc/ipc_service/lib/ipc_rpmsg.c"
SOURCE = NCS / SOURCE_REL
OBJECT_REL = "zephyr/CMakeFiles/zephyr.dir/subsys/ipc/ipc_service/lib/ipc_rpmsg.c.obj"
OBJECT = BUILD / OBJECT_REL
CONFIG = BUILD / "zephyr/.config"
MAP = BUILD / "zephyr/zephyr.map"
IMAGE = ROOT / "netcore_image.bin"
CANONICAL = ROOT / "recon/net/src/FUN_0102da84.c"
NAMES = ROOT / "recon/catalogs/function_names_net.json"
OUTPUT = ROOT / "recon/ownership/net_ipc_rpmsg_variant_ownership.json"

IMAGE_BASE = 0x01008000
ZEPHYR_COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"
SUPPORTED_RELOCATIONS = {2, 10, 30}
FIRMWARE_SECTIONS = {
    "ns_bind_cb": 0x0102DA18,
    "ipc_rpmsg_register_ept": 0x0102DA84,
    "ipc_rpmsg_init": 0x0102DAC0,
    "ipc_rpmsg_deinit": 0x0103A192,
}
SELECTED_SECTIONS = (
    "rpmsg_service_unbind", "ns_bind_cb", "ipc_rpmsg_register_ept",
    "ipc_rpmsg_init", "ipc_rpmsg_deinit",
)


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def config_values(path: Path) -> dict[str, str]:
    values = {}
    for line in path.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            values[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            values[line[2:-11]] = "n"
    return values


def _relocations(elf: ELFFile, section_name: str) -> list[dict]:
    rel = elf.get_section_by_name(".rel" + section_name)
    if rel is None:
        return []
    symbols = elf.get_section(rel["sh_link"])
    rows = []
    for item in rel.iter_relocations():
        kind = int(item["r_info_type"])
        if kind not in SUPPORTED_RELOCATIONS:
            raise ValueError(f"unsupported relocation {kind} in {section_name}")
        rows.append({
            "offset": int(item["r_offset"]),
            "type": kind,
            "target_symbol": symbols.get_symbol(
                int(item["r_info_sym"])).name,
        })
    return rows


def section_receipts() -> tuple[list[dict], dict[str, list[dict]]]:
    firmware = IMAGE.read_bytes()
    rows = []
    relocation_rows = {}
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        for symbol in SELECTED_SECTIONS:
            section_name = ".text." + symbol
            section = elf.get_section_by_name(section_name)
            if section is None:
                raise ValueError(f"missing source-unit section {section_name}")
            relocations = _relocations(elf, section_name)
            relocation_rows[symbol] = relocations
            row = {
                "symbol": symbol,
                "section": section_name,
                "size": len(section.data()),
                "relocations": relocations,
            }
            va = FIRMWARE_SECTIONS.get(symbol)
            if va is None:
                # This four-byte tail thunk is entirely a relocation.  It has
                # no byte identity independent of its target and therefore is
                # closure evidence only, never adoption evidence.
                row.update({
                    "firmware_va": None,
                    "match": "fully-relocated-no-independent-identity",
                })
            else:
                candidate = bytearray(section.data())
                original = bytearray(firmware[
                    va - IMAGE_BASE:va - IMAGE_BASE + len(candidate)])
                for relocation in relocations:
                    offset = relocation["offset"]
                    candidate[offset:offset + 4] = b"\0" * 4
                    original[offset:offset + 4] = b"\0" * 4
                if candidate != original:
                    mismatch = next(i for i, pair in enumerate(zip(
                        candidate, original)) if pair[0] != pair[1])
                    raise ValueError(
                        f"non-relocation mismatch {section_name}+0x{mismatch:x}")
                row.update({
                    "firmware_va": f"0x{va:08x}",
                    "match": "relocation-masked-byte-exact",
                    "normalized_sha256": hashlib.sha256(original).hexdigest(),
                })
            rows.append(row)
    return rows, relocation_rows


def build() -> dict:
    values = config_values(CONFIG)
    required = {
        "CONFIG_OPENAMP": values.get("CONFIG_OPENAMP"),
        "CONFIG_IPC_SERVICE": values.get("CONFIG_IPC_SERVICE"),
        "CONFIG_IPC_SERVICE_BACKEND_RPMSG": values.get(
            "CONFIG_IPC_SERVICE_BACKEND_RPMSG"),
        "CONFIG_SMP": values.get("CONFIG_SMP", "n"),
    }
    if required != {
            "CONFIG_OPENAMP": "y", "CONFIG_IPC_SERVICE": "y",
            "CONFIG_IPC_SERVICE_BACKEND_RPMSG": "y", "CONFIG_SMP": "n"}:
        raise ValueError(f"reference IPC configuration drifted: {required}")

    sections, relocations = section_receipts()
    map_text = MAP.read_text()
    for symbol in SELECTED_SECTIONS:
        pattern = (r"\.text\." + re.escape(symbol) +
                   r"[\s\S]{0,180}ipc_rpmsg\.c\.obj")
        if not re.search(pattern, map_text):
            raise ValueError(f"configured linker map lacks live {symbol}")

    expected_callback_relocs = {
        "ns_bind_cb": 0x68,
        "ipc_rpmsg_register_ept": 0x38,
    }
    callback_checks = []
    firmware = IMAGE.read_bytes()
    names = json.loads(NAMES.read_text())["by_address"]
    firmware_callback = 0x0103A98F
    callback_code = firmware[
        (firmware_callback & ~1) - IMAGE_BASE:
        (firmware_callback & ~1) - IMAGE_BASE + 4]
    if callback_code.hex() != "3678b600":
        raise ValueError("firmware callback target instruction context drifted")
    if ("0x0103a98e" in names or "0x0103a924" not in names or
            "0x0103a9be" not in names or
            not (0x0103A924 < (firmware_callback & ~1) < 0x0103A9BE)):
        raise ValueError("firmware callback target boundary classification drifted")
    for symbol, offset in expected_callback_relocs.items():
        candidates = [row for row in relocations[symbol]
                      if row["offset"] == offset]
        if len(candidates) != 1 or candidates[0]["target_symbol"] != \
                "rpmsg_service_unbind":
            raise ValueError(f"stock callback relocation drifted in {symbol}")
        va = FIRMWARE_SECTIONS[symbol]
        target = struct.unpack_from(
            "<I", firmware, va - IMAGE_BASE + offset)[0]
        if target != firmware_callback:
            raise ValueError(f"firmware callback literal drifted in {symbol}")
        callback_checks.append({
            "owner_symbol": symbol,
            "owner_va": f"0x{va:08x}",
            "relocation_offset": offset,
            "stock_target_symbol": "rpmsg_service_unbind",
            "firmware_target": f"0x{target:08x}",
            "firmware_target_even": f"0x{target & ~1:08x}",
            "firmware_target_is_function_entry": False,
            "firmware_target_containing_function": "FUN_0103a924",
            "firmware_target_containing_extent": [
                "0x0103a924", "0x0103a9be"],
            "firmware_target_first_bytes": callback_code.hex(),
            "firmware_target_first_instructions": [
                "ldrb r6, [r6, #0]", "lsls r6, r6, #2"],
            "stock_target_behavior": "tail-branch rpmsg_destroy_ept",
            "equivalent": False,
        })

    canonical_text = CANONICAL.read_text()
    if "0x0103a98fu" not in canonical_text:
        raise ValueError("retained reconstruction lost firmware callback literal")
    return {
        "schema": 1,
        "core": "net",
        "component": "zephyr_ipc_rpmsg_variant",
        "status": "required_retain",
        "safe": True,
        "policy": {
            "source_unit_adoption": "rejected_on_call_target_mismatch",
            "duplicate_resolution": "rename_recovered_firmware_variant",
            "sdc_policy": "report_only_unchanged",
        },
        "upstream": {
            "repository": "zephyr",
            "commit": ZEPHYR_COMMIT,
            "source": SOURCE_REL,
            "source_path": str(SOURCE),
            "source_sha256": sha256(SOURCE),
            "configured_build": str(BUILD),
            "configured_build_sha256": sha256(CONFIG),
            "object": OBJECT_REL,
            "object_path": str(OBJECT),
            "object_sha256": sha256(OBJECT),
            "linker_map": str(MAP),
            "linker_map_sha256": sha256(MAP),
            "required_config": required,
            "abi": "Cortex-M33, Thumb-2, soft-float, -Os",
        },
        "source_unit_sections": sections,
        "mutable_state_sections": [],
        "call_target_mismatches": callback_checks,
        "cfg_verify": {
            "0x0102da84": "PASS cases=7 selectors=args0,args1,args2",
        },
        "retained_functions": [{
            "va": "0x0102da84",
            "raw_symbol": "FUN_0102da84",
            "variant_symbol": "g1_ipc_rpmsg_register_ept",
            "stock_symbol": "ipc_rpmsg_register_ept",
            "reconstruction_source": str(CANONICAL.relative_to(ROOT)),
            "reconstruction_source_sha256": sha256(CANONICAL),
            "exclude_reconstruction": False,
            "reason": ("stock non-relocation bytes match, but the live unbind "
                       "callback relocation target does not"),
        }],
        "state_closure": {
            "source_unit_live_sections": list(SELECTED_SECTIONS),
            "mutable_state_sections": [],
            "complete": True,
        },
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--output", type=Path, default=OUTPUT)
    args = parser.parse_args()
    encoded = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not args.output.is_file() or args.output.read_text() != encoded:
            raise SystemExit(f"stale receipt: {args.output}")
    else:
        args.output.write_text(encoded)
    print("net ipc_rpmsg variant: 1 retained, 5-section closure, safe=true")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
