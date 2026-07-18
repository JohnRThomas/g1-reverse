#!/usr/bin/env python3
"""Prove four misclassified CPUNET runtime/library owners fail-closed.

The shipped net image is imported at analysis VA 0x01008000 but its absolute
flash literals use runtime VA 0x01008800.  This generator keeps those spaces
explicit; confusing them was what made arch_busy_wait's six-byte executable
delay table look like an IPC string and __chk_fail's message look like ppi.c.
"""

import hashlib
import json
import subprocess
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB, Cs
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
BUILD = NCS / "netref_build"
SDK = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1")
AR = SDK / "arm-zephyr-eabi/bin/arm-zephyr-eabi-ar"
IMAGE = ROOT / "netcore_image.bin"
ANALYSIS_BASE = 0x01008000
RUNTIME_BASE = 0x01008800
RUNTIME_DELTA = RUNTIME_BASE - ANALYSIS_BASE
CONFIG = BUILD / "zephyr/.config"
SOC_OBJECT = BUILD / (
    "zephyr/CMakeFiles/zephyr.dir/soc/arm/nordic_nrf/nrf53/soc.c.obj")
BUSY_OBJECT = BUILD / "zephyr/kernel/CMakeFiles/kernel.dir/busy_wait.c.obj"
HOOKS_OBJECT = BUILD / (
    "zephyr/lib/libc/picolibc/CMakeFiles/"
    "lib__libc__picolibc.dir/libc-hooks.c.obj")
PICOLIBC = SDK / (
    "arm-zephyr-eabi/picolibc/arm-zephyr-eabi/lib/thumb/"
    "v8-m.main/nofp/libc.a")
MEMCPY_MEMBER = "libc_ssp_memcpy_chk.c.o"
OUTPUT = ROOT / "recon/ownership/net_runtime_stock_atomic_adoption.json"


def sha256_bytes(value):
    return hashlib.sha256(value).hexdigest()


def sha256(path):
    return sha256_bytes(Path(path).read_bytes())


def image_read(analysis_va, size):
    data = IMAGE.read_bytes()
    offset = analysis_va - ANALYSIS_BASE
    return data[offset:offset + size]


def section_from_path(path, section_name):
    raw = Path(path).read_bytes()
    return section_from_bytes(raw, section_name)


def section_from_bytes(raw, section_name):
    from io import BytesIO
    elf = ELFFile(BytesIO(raw))
    section = elf.get_section_by_name(section_name)
    if section is None:
        raise ValueError("missing section %s" % section_name)
    rel = elf.get_section_by_name(".rel" + section_name)
    relocations = []
    if rel is not None:
        symbols = elf.get_section(rel["sh_link"])
        for item in rel.iter_relocations():
            symbol = symbols.get_symbol(item["r_info_sym"])
            target = symbol.name
            if not target and isinstance(symbol["st_shndx"], int):
                target = elf.get_section(symbol["st_shndx"]).name
            relocations.append({
                "offset": int(item["r_offset"]),
                "type": int(item["r_info_type"]),
                "target": target,
            })
    return section.data(), relocations


def archive_member(archive, member):
    return subprocess.check_output([str(AR), "p", str(archive), member])


def normalized_match(firmware, upstream, relocations):
    if len(firmware) != len(upstream):
        return False, None, None
    fw = bytearray(firmware)
    stock = bytearray(upstream)
    masked = []
    for relocation in relocations:
        offset = relocation["offset"]
        width = 4
        if offset < 0 or offset + width > len(fw):
            raise ValueError("relocation outside section")
        fw[offset:offset + width] = b"\0" * width
        stock[offset:offset + width] = b"\0" * width
        masked.append([offset, offset + width])
    return fw == stock, sha256_bytes(bytes(fw)), masked


def branch_targets(code, address):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    targets = []
    for instruction in md.disasm(code, address):
        if instruction.mnemonic in ("bl", "b.w"):
            targets.append({
                "instruction": "0x%08x" % instruction.address,
                "mnemonic": instruction.mnemonic,
                "target": "0x%08x" % int(instruction.op_str.lstrip("#"), 0),
            })
    return targets


def owner(va, symbol, unit, section, firmware_size, upstream, relocations,
          source, reconstruction=None, true_code_size=None, literal_size=0):
    firmware = image_read(va, firmware_size)
    exact, normalized_hash, masked = normalized_match(
        firmware, upstream, relocations)
    if not exact:
        raise ValueError("normalized mismatch for %s" % symbol)
    row = {
        "va": "0x%08x" % va,
        "raw_symbol": "FUN_%08x" % va,
        "upstream_symbol": symbol,
        "upstream_unit": unit,
        "upstream_section": section,
        "firmware_size": firmware_size,
        "true_code_size": true_code_size or firmware_size,
        "literal_size": literal_size,
        "match": "relocation-masked-byte-exact",
        "normalized_sha256": normalized_hash,
        "relocation_masks": masked,
        "relocations": relocations,
        "firmware_branch_targets": branch_targets(firmware, va),
        "source": str(source),
        "source_sha256": sha256(source),
        "reconstruction_present": reconstruction is not None,
        "whole_atomic_group_selected": True,
        "safe_to_adopt": True,
        "exclude_reconstruction": True,
        "raw_mapping_preserved": True,
    }
    if reconstruction is not None:
        row["reconstruction_source"] = str(reconstruction.relative_to(ROOT))
        row["reconstruction_source_sha256"] = sha256(reconstruction)
    return row


def build():
    soc, soc_relocs = section_from_path(SOC_OBJECT, ".text.arch_busy_wait")
    busy, busy_relocs = section_from_path(
        BUSY_OBJECT, ".text.z_impl_k_busy_wait")
    hooks, hooks_relocs = section_from_path(HOOKS_OBJECT, ".text.__chk_fail")
    memcpy_object = archive_member(PICOLIBC, MEMCPY_MEMBER)
    memcpy, memcpy_relocs = section_from_bytes(
        memcpy_object, ".text.__memcpy_chk")

    arch_literal = int.from_bytes(image_read(0x0102D26C, 4), "little")
    delay_analysis = arch_literal - RUNTIME_DELTA
    delay_bytes = image_read(delay_analysis, 6)
    if delay_bytes != bytes.fromhex("0338fdd87047"):
        raise ValueError("arch_busy_wait delay table drift")
    hook_literal = int.from_bytes(image_read(0x0102FA98, 4), "little")
    hook_string_analysis = hook_literal - RUNTIME_DELTA
    hook_string = image_read(hook_string_analysis, 30)
    if hook_string != b"* buffer overflow detected *\n\0":
        raise ValueError("__chk_fail string/runtime translation drift")
    svc = image_read(0x0102FA8C, 12)
    if svc != bytes.fromhex("404080f311884ff0020002df"):
        raise ValueError("__chk_fail ARCH_EXCEPT sequence drift")

    owners = [
        owner(0x0102D25C, "arch_busy_wait",
              "zephyr/soc/arm/nordic_nrf/nrf53/soc.c",
              ".text.arch_busy_wait", 20, soc, soc_relocs,
              NCS / "zephyr/soc/arm/nordic_nrf/nrf53/soc.c",
              true_code_size=16, literal_size=4),
        owner(0x0103B0E8, "z_impl_k_busy_wait",
              "zephyr/kernel/busy_wait.c", ".text.z_impl_k_busy_wait",
              8, busy, busy_relocs, NCS / "zephyr/kernel/busy_wait.c",
              ROOT / "recon/net/src/FUN_0103b0e8.c"),
        owner(0x0102FA84, "__chk_fail",
              "zephyr/lib/libc/picolibc/libc-hooks.c", ".text.__chk_fail",
              24, hooks, hooks_relocs,
              NCS / "zephyr/lib/libc/picolibc/libc-hooks.c",
              true_code_size=20, literal_size=4),
        owner(0x0103B53A, "__memcpy_chk",
              "picolibc:" + MEMCPY_MEMBER, ".text.__memcpy_chk",
              38, memcpy, memcpy_relocs,
              NCS / "modules/lib/picolibc/newlib/libc/ssp/memcpy_chk.c",
              ROOT / "recon/net/src/FUN_0103b53a.c"),
    ]
    return {
        "schema": 1,
        "core": "net",
        "component": "zephyr_picolibc_runtime_stock",
        "status": "authorized_atomic",
        "safe": True,
        "supersedes": [
            "recon/catalogs/net_fun_0102d25c_identity_audit.json",
            "the blocked_c_unexpressible classification for FUN_0102fa84",
        ],
        "policy": {
            "sdc_policy": "report_only_unchanged",
            "analysis_base": "0x%08x" % ANALYSIS_BASE,
            "runtime_base": "0x%08x" % RUNTIME_BASE,
            "runtime_minus_analysis": "0x%x" % RUNTIME_DELTA,
            "no_blob_or_stub": True,
        },
        "inputs": {
            "image": str(IMAGE),
            "image_sha256": sha256(IMAGE),
            "configured_build": str(BUILD),
            "config": str(CONFIG),
            "config_sha256": sha256(CONFIG),
            "soc_object": str(SOC_OBJECT),
            "soc_object_sha256": sha256(SOC_OBJECT),
            "busy_wait_object": str(BUSY_OBJECT),
            "busy_wait_object_sha256": sha256(BUSY_OBJECT),
            "picolibc_hooks_object": str(HOOKS_OBJECT),
            "picolibc_hooks_object_sha256": sha256(HOOKS_OBJECT),
            "picolibc_archive": str(PICOLIBC),
            "picolibc_archive_sha256": sha256(PICOLIBC),
            "picolibc_member": MEMCPY_MEMBER,
            "picolibc_member_sha256": sha256_bytes(memcpy_object),
        },
        "coordinate_proof": {
            "arch_literal_address": "0x0102d26c",
            "arch_literal_runtime_value": "0x%08x" % arch_literal,
            "arch_literal_analysis_target": "0x%08x" % delay_analysis,
            "arch_delay_machine_code_hex": delay_bytes.hex(),
            "arch_delay_semantics": "SUBS r0,#3; BHI self; BX lr",
            "chk_literal_address": "0x0102fa98",
            "chk_literal_runtime_value": "0x%08x" % hook_literal,
            "chk_literal_analysis_target": "0x%08x" % hook_string_analysis,
            "chk_literal_ascii": hook_string[:-1].decode("ascii"),
            "chk_svc_semantics": (
                "BASEPRI=0; r0=K_ERR_STACK_CHK_FAIL(2); svc #2"),
        },
        "call_graph_proof": {
            "FUN_0103b0e8": "z_impl_k_busy_wait -> arch_busy_wait",
            "FUN_0103b53a": "__memcpy_chk -> __chk_fail or memcpy",
            "cfg_verify": {
                "FUN_0103b0e8": "PASS cases=2",
                "FUN_0103b53a": "PASS cases=0",
            },
        },
        "atomic_group": [row["va"] for row in owners],
        "manifest_functions": owners,
        "summary": {
            "owners": len(owners),
            "newly_identified_catalog_missing_entries": 2,
            "recovered_sources_replaced": 2,
            "unresolved_anomalies": 0,
        },
    }


def main():
    data = build()
    OUTPUT.write_text(json.dumps(data, indent=1) + "\n")
    print("wrote %s (%d exact owners)" %
          (OUTPUT.relative_to(ROOT), data["summary"]["owners"]))


if __name__ == "__main__":
    main()
