#!/usr/bin/env python3
"""Build the CPUNET SPIN_VALIDATE/SMP layout-discrimination receipt."""

from __future__ import annotations

import argparse
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_kernel_config_exact.json"
BASE = 0x01008000
UNITS = {
    "zephyr/CMakeFiles/zephyr.dir/lib/os/onoff.c.obj": {
        "process_recheck": 0x01039ADE,
        "validate_args": 0x01039B16,
        "notify_one": 0x01039B36,
        "onoff_manager_init": 0x01039B62,
    },
    "zephyr/kernel/CMakeFiles/kernel.dir/thread.c.obj": {
        "z_spin_lock_valid": 0x0103610C,
        "z_spin_unlock_valid": 0x01036128,
        "z_spin_lock_set_owner": 0x01036144,
    },
    "zephyr/kernel/CMakeFiles/kernel.dir/msg_q.c.obj": {
        "k_msgq_init": 0x0103B164,
        "z_impl_k_msgq_alloc_init": 0x0103B18C,
    },
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def config_values() -> dict[str, str]:
    values = {}
    for line in CONFIG.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            values[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            values[line[2:-11]] = "n"
    return values


def build() -> dict:
    values = config_values()
    required = {"CONFIG_SPIN_VALIDATE": "y", "CONFIG_SMP": "n"}
    if any(values.get(key, "n") != value for key, value in required.items()):
        raise ValueError("corrected CPUNET kernel configuration drifted")
    firmware_image = IMAGE.read_bytes()
    matches = []
    object_receipts = {}
    for relative, symbols in UNITS.items():
        path = BUILD / relative
        object_receipts[relative] = digest(path.read_bytes())
        with path.open("rb") as stream:
            elf = ELFFile(stream)
            for symbol, va in symbols.items():
                name = ".text." + symbol
                section = elf.get_section_by_name(name)
                candidate = bytearray(section.data())
                firmware = bytearray(firmware_image[
                    va - BASE:va - BASE + len(candidate)])
                relocation_section = elf.get_section_by_name(".rel" + name)
                relocations = []
                if relocation_section is not None:
                    for relocation in relocation_section.iter_relocations():
                        offset = int(relocation["r_offset"])
                        candidate[offset:offset + 4] = b"\0" * 4
                        firmware[offset:offset + 4] = b"\0" * 4
                        relocations.append({
                            "offset": offset,
                            "type": int(relocation["r_info_type"]),
                        })
                if candidate != firmware:
                    raise ValueError(f"kernel config mismatch: {symbol}")
                matches.append({
                    "symbol": symbol, "va": f"0x{va:08x}",
                    "object": relative, "size": len(candidate),
                    "match": "relocation-masked-byte-exact",
                    "normalized_sha256": digest(bytes(firmware)),
                    "relocations": relocations,
                })
    return {
        "schema": 1,
        "core": "net",
        "status": "configuration_exact_no_adoption_authority",
        "zephyr_commit": "83980fe1679441be9b0e1db556a353f6118fe14f",
        "configured_build": str(BUILD),
        "configured_build_sha256": digest(CONFIG.read_bytes()),
        "required_config": required,
        "layout_discriminators": {
            "onoff_manager_size": 0x20,
            "onoff_manager_size_if_smp": 0x24,
            "k_msgq_init_size": 40,
        },
        "object_sha256": object_receipts,
        "section_matches": matches,
        "sdc_policy": "report_only_unchanged",
        "authorizes_source_exclusion": False,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    encoded = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.is_file() or OUTPUT.read_text() != encoded:
            raise SystemExit("stale net kernel configuration receipt")
    else:
        OUTPUT.write_text(encoded)
    print("net kernel config SPIN_VALIDATE=y SMP=n sections=9 exact")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
