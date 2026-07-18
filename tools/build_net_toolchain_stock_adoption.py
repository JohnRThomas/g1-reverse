#!/usr/bin/env python3
"""Prove exact CPUNET GCC/libgcc and Picolibc selected-section ownership."""

import argparse
import hashlib
import io
import json
import re
import subprocess
import tempfile
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
SDK_ROOT = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1")
SDK = SDK_ROOT / "arm-zephyr-eabi"
AR = SDK / "bin/arm-zephyr-eabi-ar"
READELF = SDK / "bin/arm-zephyr-eabi-readelf"
LIBGCC = (SDK / "lib/gcc/arm-zephyr-eabi/12.2.0/thumb/"
          "v8-m.main/nofp/libgcc.a")
PICOLIBC = (SDK / "picolibc/arm-zephyr-eabi/lib/thumb/"
            "v8-m.main/nofp/libc.a")
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_toolchain_stock_atomic_adoption.json"
BASE = 0x01008000

ARCHIVE_SHA256 = {
    "libgcc": "6b84bf826f380e4c16a95aca8a508a1ad8aa388b84762dc21ee56f1040390eb9",
    "picolibc": "1aab30f2d746ad97b271efdfb98a8b62996b7ad82263897edede2b0504e2832e",
}

TARGETS = (
    (0x01025D38, "FUN_01025d38", "__udivmoddi4", "libgcc",
     "_udivmoddi4.o", ".text"),
    (0x0102A244, "FUN_0102a244", "strcmp", "picolibc",
     "strcmp.S.o", ".text"),
    (0x0103B5C4, "FUN_0103b5c4", "strnlen", "picolibc",
     "libc_string_strnlen.c.o", ".text.strnlen"),
    (0x0103B614, "FUN_0103b614", "__aeabi_memcpy4", "picolibc",
     "memcpy.c.o", ".text.memcpy"),
    (0x0103B62E, "FUN_0103b62e", "memset", "picolibc",
     "memset.c.o", ".text.memset"),
)

# Exact direct call/tail-call sites recovered from the firmware CFG. Raw caller
# addresses remain the stable back-map; readable identities are supplied only
# where independently established.
CALLERS = {
    0x01025D38: {
        0x0100823C: ([0x0100825C], "__aeabi_uldivmod",
                     "exact selected libgcc member"),
    },
    0x0102A244: {
        0x0103510C: ([0x01035130], "metal_generic_dev_open",
                     "libmetal source-shape and configured-object identity"),
        0x01039F4C: ([0x01039F58, 0x01039F64],
                     "get_ept_slot_with_name",
                     "exact configured object-index identity"),
    },
    0x0103B5C4: {
        0x01039190: ([0x01039384], "z_cbvprintf_impl",
                     "configuration-specific Zephyr source identity"),
    },
    0x0103B614: {
        0x0102A698: ([0x0102A6A8], "FUN_0102a698", "raw back-map"),
        0x0102A6E0: ([0x0102A6EC, 0x0102A70A], "FUN_0102a6e0", "raw back-map"),
        0x0102BBEC: ([0x0102BFA8], "FUN_0102bbec", "raw back-map"),
        0x0102BFE4: ([0x0102C1BE], "FUN_0102bfe4", "raw back-map"),
        0x0102EDAC: ([0x0102EDDA], "FUN_0102edac", "raw back-map"),
        0x010323CC: ([0x010323E4], "FUN_010323cc", "raw back-map"),
        0x01033660: ([0x010336BC, 0x01033712], "FUN_01033660", "raw back-map"),
        0x01033A60: ([0x01033A7A], "FUN_01033a60", "raw back-map"),
        0x01036198: ([0x0103620E, 0x0103624C], "z_impl_k_msgq_put", "exact Zephyr identity"),
        0x010362D0: ([0x01036338, 0x01036380], "z_impl_k_msgq_get", "exact Zephyr identity"),
        0x01038F34: ([0x01038F52], "FUN_01038f34", "raw back-map"),
        0x0103A2CC: ([0x0103A2E4], "FUN_0103a2cc", "raw back-map"),
        0x0103A2F8: ([0x0103A318], "FUN_0103a2f8", "raw back-map"),
        0x0103A478: ([0x0103A48C], "net_buf_simple_add_mem", "exact Zephyr identity"),
        0x0103B53A: ([0x0103B55C], "FUN_0103b53a", "raw back-map"),
    },
    0x0103B62E: {
        0x0102A394: ([0x0102A39E], "FUN_0102a394", "raw back-map"),
        0x0102A720: ([0x0102A752, 0x0102A976], "FUN_0102a720", "raw back-map"),
        0x0102B15C: ([0x0102B16C], "FUN_0102b15c", "raw back-map"),
        0x0102B2AC: ([0x0102B2C0], "FUN_0102b2ac", "raw back-map"),
        0x0102C5EC: ([0x0102C67A], "FUN_0102c5ec", "raw back-map"),
        0x0102CBD8: ([0x0102CBE2], "mpsc_pbuf_init", "exact Zephyr identity"),
        0x0102EDAC: ([0x0102EDE6], "FUN_0102edac", "raw back-map"),
        0x0102FA4C: ([0x0102FA5E], "FUN_0102fa4c", "raw back-map"),
        0x01030BAC: ([0x01030BD2], "FUN_01030bac", "raw back-map"),
        0x01033354: ([0x0103338A], "FUN_01033354", "raw back-map"),
        0x010333E4: ([0x010333FE, 0x010334C0], "FUN_010333e4", "raw back-map"),
        0x0103499C: ([0x010349AE], "FUN_0103499c", "raw back-map"),
        0x01035830: ([0x01035850], "FUN_01035830", "raw back-map"),
        0x01036BEC: ([0x01036C1A], "k_work_init", "exact Zephyr identity"),
        0x01038F34: ([0x01038F44], "FUN_01038f34", "raw back-map"),
        0x01039138: ([0x01039148], "FUN_01039138", "raw back-map"),
        0x0103963C: ([0x0103964E], "FUN_0103963c", "raw back-map"),
        0x01039B62: ([0x01039B78], "onoff_manager_init", "exact Zephyr identity"),
        0x0103B5A4: ([0x0103B5BC], "strncpy", "exact Picolibc identity"),
    },
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def member_bytes(archive, member):
    return subprocess.check_output([str(AR), "p", str(archive), member])


def attributes(obj):
    with tempfile.NamedTemporaryFile() as stream:
        stream.write(obj)
        stream.flush()
        text = subprocess.check_output(
            [str(READELF), "-A", stream.name], text=True)
    wanted = ("Tag_CPU_name", "Tag_CPU_arch", "Tag_CPU_arch_profile",
              "Tag_THUMB_ISA_use", "Tag_ABI_optimization_goals")
    return [line.strip() for line in text.splitlines()
            if any(item in line for item in wanted)]


def section_record(archive, member, section_name, firmware, va):
    obj = member_bytes(archive, member)
    elf = ELFFile(io.BytesIO(obj))
    section = elf.get_section_by_name(section_name)
    if section is None:
        raise ValueError("missing section %s(%s)" % (member, section_name))
    data = section.data()
    reloc = elf.get_section_by_name(".rel" + section_name)
    text_relocs = [] if reloc is None else [
        int(row["r_offset"]) for row in reloc.iter_relocations()]
    actual = firmware[va - BASE:va - BASE + len(data)]
    if text_relocs or actual != data:
        raise ValueError("target section is not raw byte-exact: %s" % member)
    symtab = elf.get_section_by_name(".symtab")
    section_index = elf.get_section_index(section_name)
    aliases = sorted({symbol.name for symbol in symtab.iter_symbols()
                      if symbol.name and
                      symbol["st_info"]["type"] == "STT_FUNC" and
                      symbol["st_shndx"] == section_index})
    return {
        "archive_member": member,
        "archive_member_sha256": sha(obj),
        "section": section_name,
        "section_size": len(data),
        "section_sha256": sha(data),
        "executable_relocations": text_relocs,
        "raw_firmware_byte_exact": True,
        "elf_function_aliases": aliases,
        "elf_attributes": attributes(obj),
    }


def direct_target(firmware, site):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    insns = list(md.disasm(firmware[site - BASE:site - BASE + 4], site, 1))
    if len(insns) != 1 or insns[0].mnemonic not in ("bl", "b.w"):
        raise ValueError("not a direct call at 0x%08x" % site)
    match = re.fullmatch(r"#(0x[0-9a-f]+)", insns[0].op_str)
    if not match:
        raise ValueError("non-immediate call at 0x%08x" % site)
    return int(match.group(1), 16), insns[0].mnemonic


def caller_records(firmware, target):
    rows = []
    for entry, (sites, identity, proof) in sorted(CALLERS[target].items()):
        calls = []
        for site in sites:
            resolved, mnemonic = direct_target(firmware, site)
            if resolved != target:
                raise ValueError("call target drift at 0x%08x" % site)
            calls.append({"site": "0x%08x" % site,
                          "mnemonic": mnemonic,
                          "resolved_target": "0x%08x" % resolved})
        rows.append({
            "caller_va": "0x%08x" % entry,
            "caller_raw_identity": "FUN_%08x" % entry,
            "caller_readable_identity": identity,
            "identity_proof": proof,
            "direct_calls": calls,
        })
    return rows


def supporting_uldivmod(firmware):
    obj = member_bytes(LIBGCC, "_aeabi_uldivmod.o")
    elf = ELFFile(io.BytesIO(obj))
    section = elf.get_section_by_name(".text")
    data = section.data()
    reloc = elf.get_section_by_name(".rel.text")
    symtab = elf.get_section(reloc["sh_link"])
    relocations = []
    mask = set()
    for row in reloc.iter_relocations():
        offset = int(row["r_offset"])
        symbol = symtab.get_symbol(row["r_info_sym"]).name
        mask.update(range(offset, min(offset + 4, len(data))))
        relocations.append({"offset": offset, "type": int(row["r_info_type"]),
                            "symbol": symbol})
    va = 0x0100823C
    actual = firmware[va - BASE:va - BASE + len(data)]
    if not all(actual[i] == data[i] for i in range(len(data)) if i not in mask):
        raise ValueError("__aeabi_uldivmod non-relocation bytes differ")
    targets = {
        "__aeabi_ldiv0": direct_target(firmware, 0x01008250)[0],
        "__udivmoddi4": direct_target(firmware, 0x0100825C)[0],
    }
    if targets != {"__aeabi_ldiv0": 0x0100826C,
                   "__udivmoddi4": 0x01025D38}:
        raise ValueError("__aeabi_uldivmod relocation targets changed")
    if firmware[0x0100826C - BASE:0x0100826E - BASE] != b"\x70\x47":
        raise ValueError("__aeabi_ldiv0 stub changed")
    return {
        "va": "0x0100823c",
        "identity": "__aeabi_uldivmod",
        "archive_member": "_aeabi_uldivmod.o",
        "archive_member_sha256": sha(obj),
        "section_size": len(data),
        "catalog_extent_size": 50,
        "catalog_boundary_correction": (
            "The selected member is 48 bytes. The following two-byte bx-lr "
            "at 0x0100826c is the separately targeted __aeabi_ldiv0 stub."),
        "relocations": relocations,
        "resolved_targets": {key: "0x%08x" % value
                             for key, value in targets.items()},
        "non_relocation_bytes_exact": True,
    }


def build():
    firmware = IMAGE.read_bytes()
    archives = {"libgcc": LIBGCC, "picolibc": PICOLIBC}
    for key, path in archives.items():
        if sha(path.read_bytes()) != ARCHIVE_SHA256[key]:
            raise ValueError("%s archive changed" % key)
    functions = []
    for va, raw, identity, family, member, section in TARGETS:
        record = section_record(
            archives[family], member, section, firmware, va)
        record.update({
            "va": "0x%08x" % va,
            "raw_identity": raw,
            "resolved_identity": identity,
            "archive_family": family,
            "archive_path": str(archives[family].relative_to(SDK_ROOT)),
            "archive_sha256": ARCHIVE_SHA256[family],
            "abi": ("Cortex-M33 mainline, Thumb, no-FP multilib; soft-float "
                    "CPUNET ABI"),
            "optimization_evidence": (
                "hand-written assembly member; no optimization-goal ELF tag"
                if member.endswith(".S.o") else
                "ELF Tag_ABI_optimization_goals: Aggressive Size"),
            "compiler_or_libc_version": (
                "GCC 12.2.0" if family == "libgcc" else "Picolibc 1.8.6"),
            "version_claim_strength": (
                "configured Zephyr SDK archive provenance plus exact selected "
                "member/section; the body is not asserted unique to this "
                "patch version"),
            "library_identity_note": (
                "The CPUNET no-FP selected-link archive establishes the "
                "provider. Generic short libc bodies may be byte-identical "
                "in other libc implementations and are not provenance alone."
                if family == "picolibc" else
                "The 668-byte helper and exact libgcc caller relocation "
                "closure strongly identify the selected GCC helper family."),
            "callers": caller_records(firmware, va),
            "preserve_raw_reconstruction_evidence": True,
            "safe_to_resolve_to_stock_provider": True,
        })
        functions.append(record)
    return {
        "schema": 1,
        "core": "net",
        "component": "cpunet_toolchain_selected_members",
        "status": "authorized_exact_stock_provider",
        "safe": True,
        "source_exclusion_required": False,
        "raw_reconstruction_policy": "preserve; no canonical raw source deletion",
        "image": "netcore_image.bin",
        "image_sha256": sha(firmware),
        "address_space": "analysis; runtime/link address is analysis + 0x800",
        "sdk_package": "Zephyr SDK 0.16.5-1",
        "functions": functions,
        "supporting_closure": {
            "libgcc_unsigned_division_entry": supporting_uldivmod(firmware),
        },
        "policy": {
            "private_sdc_report_only": True,
            "archive_hash_alone_is_not_ownership": True,
            "exact_selected_section_and_call_targets_required": True,
            "memcpy_alias_note": (
                "memcpy, __aeabi_memcpy, __aeabi_memcpy4 and "
                "__aeabi_memcpy8 are the same selected Picolibc section. "
                "The requested readable identity is __aeabi_memcpy4; caller "
                "relocation context may use another alias."),
        },
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=1) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise SystemExit("net toolchain stock receipt is stale")
        print("net toolchain stock receipt is current")
    else:
        OUTPUT.write_text(rendered)
        print("wrote %s" % OUTPUT)


if __name__ == "__main__":
    main()
