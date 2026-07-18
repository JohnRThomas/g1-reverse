#!/usr/bin/env python3
"""Build the exact configured-object ownership receipt for CPUAPP libLC3.

The older LC3 catalog used semantic/size scores.  Those scores are useful for
identification, but are not replacement authority.  This builder compares the
firmware prefix byte-for-byte with the pinned NCS configured objects, masking
only ELF link relocations, and separately checks every call relocation target.
"""

from __future__ import annotations

import hashlib
import json
import os
import subprocess
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

import extract


ROOT = Path(__file__).resolve().parents[1]
LC3 = Path("/Users/freedomcoder/ncs251/modules/lib/liblc3")
BUILD = Path(os.environ.get(
    "G1_LC3_BUILD",
    "/private/tmp/g1-app-root-topology-exact5-0718"))
OBJECT_ROOT = BUILD / "modules/liblc3"
CONFIG = BUILD / "zephyr/.config"
CATALOG = ROOT / "recon/catalogs/lc3_ownership_app.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
OUTPUT = ROOT / "recon/ownership/app_lc3_stock_atomic_adoption.json"
PIN = "448f3de31f49a838988a162ef1e23a89ddf2d2ed"
RELOC_WIDTH = {2: 4, 10: 4, 30: 4}  # ABS32, THM_CALL, THM_JUMP24

MD = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
MD.detail = True


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256_file(path: Path) -> str:
    return sha256_bytes(path.read_bytes())


def git(*args: str) -> str:
    return subprocess.check_output(
        ["git", "-C", str(LC3), *args], text=True).strip()


def object_symbols():
    result = {}
    for path in sorted(OBJECT_ROOT.rglob("*.obj")):
        with path.open("rb") as stream:
            elf = ELFFile(stream)
            symtab = elf.get_section_by_name(".symtab")
            if symtab is None:
                continue
            section_indices = {section.name: index
                               for index, section in enumerate(elf.iter_sections())}
            relocations = {}
            for section in elf.iter_sections():
                if not isinstance(section, RelocationSection):
                    continue
                target = int(section["sh_info"])
                symbols = elf.get_section(section["sh_link"])
                relocations.setdefault(target, [])
                for relocation in section.iter_relocations():
                    relocations[target].append({
                        "offset": int(relocation["r_offset"]),
                        "type": int(relocation["r_info_type"]),
                        "symbol": symbols.get_symbol(
                            relocation["r_info_sym"]).name,
                    })
            for symbol in symtab.iter_symbols():
                if symbol["st_info"]["type"] != "STT_FUNC" or not symbol.name:
                    continue
                index = symbol["st_shndx"]
                if not isinstance(index, int):
                    continue
                section = elf.get_section(index)
                if section is None or not section.name.startswith(".text."):
                    continue
                record = {
                    "symbol": symbol.name,
                    "binding": str(symbol["st_info"]["bind"]),
                    "symbol_size": int(symbol["st_size"]),
                    "section": section.name,
                    "section_size": int(section["sh_size"]),
                    "section_bytes": section.data(),
                    "relocations": relocations.get(
                        section_indices[section.name], []),
                    "object": path,
                }
                result.setdefault(symbol.name, []).append(record)
    return result


def call_target(code: bytes, address: int):
    insns = list(MD.disasm(code, address, count=1))
    if not insns:
        return None
    immediate = next((operand.imm for operand in insns[0].operands
                      if operand.type == ARM_OP_IMM), None)
    return None if immediate is None else int(immediate) & ~1


def build():
    if git("rev-parse", "HEAD") != PIN:
        raise RuntimeError("libLC3 checkout is not at the manifest pin")
    catalog = json.loads(CATALOG.read_text())
    names = json.loads(NAMES.read_text())["by_address"]
    upstream_by_current = {
        row["name"]: row["upstream_function"]
        for row in catalog["functions"]
    }
    upstream_by_current["memset_bytes"] = "memset"
    # Allow regeneration in either order: the durable raw address remains the
    # identity while build_function_names applies these two corrected aliases.
    upstream_by_current["lc3_ltpf_arm_resample_48k_12k8"] = \
        "arm_resample_8k_12k8"
    upstream_by_current["lc3_sns_compute_scale_factors"] = \
        "spectral_shaping"
    symbols = object_symbols()
    authorizations = []

    for row in catalog["functions"]:
        candidates = symbols.get(row["upstream_function"], [])
        if len(candidates) != 1:
            raise RuntimeError("LC3 symbol is not unique: %s (%d)" %
                               (row["upstream_function"], len(candidates)))
        candidate = candidates[0]
        va = int(row["address"], 0)
        extent = int(row["firmware_extent"], 0)
        firmware = extract.read(va, extent)
        upstream = candidate["section_bytes"]
        if len(firmware) > len(upstream):
            raise RuntimeError("firmware extent exceeds section at %s" % row["address"])

        masked = set()
        call_checks = []
        reloc_rows = []
        for relocation in candidate["relocations"]:
            width = RELOC_WIDTH.get(relocation["type"])
            if width is None:
                raise RuntimeError("unsupported ARM relocation %d" %
                                   relocation["type"])
            offset = relocation["offset"]
            masked.update(range(offset, offset + width))
            reloc_rows.append({
                "offset": offset,
                "type": relocation["type"],
                "symbol": relocation["symbol"],
            })
            if relocation["type"] not in (10, 30) or offset >= extent:
                continue
            target = call_target(firmware[offset:offset + 4], va + offset)
            target_name = (names.get("0x%08x" % target, {}).get("name")
                           if target is not None else None)
            normalized = upstream_by_current.get(target_name, target_name)
            call_checks.append({
                "offset": offset,
                "upstream_symbol": relocation["symbol"],
                "firmware_target": ("0x%08x" % target
                                    if target is not None else None),
                "firmware_name": target_name,
                "normalized_firmware_name": normalized,
                "exact": normalized == relocation["symbol"],
            })

        mismatches = [offset for offset in range(extent)
                      if offset not in masked and
                      firmware[offset] != upstream[offset]]
        if mismatches:
            raise RuntimeError("unmasked mismatch at %s: %r" %
                               (row["address"], mismatches[:8]))
        if not all(check["exact"] for check in call_checks):
            raise RuntimeError("call-target mismatch at %s" % row["address"])

        normalized = bytes(upstream[offset] for offset in range(extent)
                           if offset not in masked)
        suffix = upstream[extent:]
        source = LC3 / "src" / (candidate["object"].name.split(".")[0] + ".c")
        authorizations.append({
            "status": "authorized",
            "va": row["address"],
            "raw_symbol": "FUN_%08x" % va,
            "symbol": row["name"],
            "upstream_symbol": row["upstream_function"],
            "upstream_source": str(source),
            "upstream_source_sha256": sha256_file(source),
            "upstream_object": str(candidate["object"]),
            "upstream_object_sha256": sha256_file(candidate["object"]),
            "upstream_section": candidate["section"],
            "upstream_binding": candidate["binding"],
            "firmware_code_extent": extent,
            "upstream_symbol_size": candidate["symbol_size"],
            "upstream_section_size": len(upstream),
            "match": ("relocation_masked_full_section_exact"
                      if extent == len(upstream) else
                      "relocation_masked_executable_prefix_exact"),
            "unmasked_prefix_sha256": sha256_bytes(normalized),
            "masked_relocations": reloc_rows,
            "call_target_checks": call_checks,
            "trailing_object_bytes": len(suffix),
            "trailing_object_sha256": sha256_bytes(suffix),
            "raw_mapping_preserved": True,
        })

    full = sum(row["match"].endswith("full_section_exact")
               for row in authorizations)
    prefix = len(authorizations) - full
    return {
        "schema": 1,
        "core": "app",
        "status": "authorized_atomic",
        "decision": "adopt_exact_pinned_liblc3_encoder_closure",
        "version_identity": {
            "west_manifest_pin": PIN,
            "checkout_commit": git("rev-parse", "HEAD"),
            "checkout_tree": git("rev-parse", "HEAD^{tree}"),
            "evidence_limit": (
                "The configured bytes prove this source-tree state. The same "
                "libLC3 revision is pinned by NCS 2.5.0, 2.5.1 and 2.6.0, so "
                "LC3 does not distinguish the enclosing NCS patch release."),
        },
        "configured_build": {
            "config": str(CONFIG),
            "config_sha256": sha256_file(CONFIG),
            "compiler": "Zephyr SDK 0.16.5-1 arm-zephyr-eabi GCC 12.2.0",
            "required_flags": [
                "-mcpu=cortex-m33", "-mthumb", "-mfpu=fpv5-sp-d16",
                "-mfloat-abi=hard", "-O3", "-ffast-math",
                "-ffunction-sections", "-fdata-sections",
            ],
        },
        "summary": {
            "catalog_functions": len(authorizations),
            "relocation_masked_full_section_exact": full,
            "relocation_masked_executable_prefix_exact": prefix,
            "call_relocations_checked": sum(
                len(row["call_target_checks"]) for row in authorizations),
            "unmatched_functions": 0,
            "identity_corrections": {
                "0x0006aa98": "arm_resample_8k_12k8",
                "0x0006bfc8": "spectral_shaping",
            },
        },
        "authorizations": authorizations,
        "sdc_policy": "report_only_unchanged",
    }


def main():
    data = build()
    OUTPUT.write_text(json.dumps(data, indent=1) + "\n")
    print("wrote %d exact LC3 owners -> %s" %
          (len(data["authorizations"]), OUTPUT))


if __name__ == "__main__":
    main()
