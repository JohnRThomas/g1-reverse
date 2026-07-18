#!/usr/bin/env python3
"""Compare a linked Zephyr ELF with a shipped G1 firmware payload.

The comparison is based on load-memory addresses (LMAs), not ELF file offsets
or section VMAs.  That distinction is required for initialized RAM sections.
CPUAPP inputs may be MCUboot containers; CPUNET inputs may be either the
MCUboot container or the header-stripped payload used by the reconstruction
pipeline.

Executable bytes are reported as diagnostics because reconstructed C is not
expected to reproduce every instruction encoding.  Non-executable loadable
sections form the optional fail-closed exact-byte gate (``--strict-data``).
"""

import argparse
import difflib
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB, Cs
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
MCUBOOT_MAGIC = 0x96F3B83D
SHF_WRITE = 0x1
SHF_ALLOC = 0x2
SHF_EXECINSTR = 0x4
DEFAULTS = {
    "app": {
        "firmware": ROOT / "app_update.bin",
        "runtime_base": 0x0000C200,
        "analysis_base": 0x0000C200,
    },
    "net": {
        "firmware": ROOT / "netcore_image.bin",
        "runtime_base": 0x01008800,
        "analysis_base": 0x01008000,
    },
}


class ComparisonError(ValueError):
    """An input is malformed or cannot be compared without guessing."""


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def load_payload(path):
    """Return payload bytes and an explicit container receipt."""
    path = Path(path)
    raw = path.read_bytes()
    receipt = {
        "path": str(path.resolve()),
        "container_size": len(raw),
        "container_sha256": sha256(raw),
        "format": "raw",
        "payload_offset": 0,
        "payload_size": len(raw),
    }
    if len(raw) >= 32 and struct.unpack_from("<I", raw)[0] == MCUBOOT_MAGIC:
        magic, load_address, header_size, protected_tlv_size, image_size, flags = (
            struct.unpack_from("<IIHHII", raw))
        payload_end = header_size + image_size
        if header_size < 32 or payload_end > len(raw):
            raise ComparisonError(
                "invalid MCUboot bounds: header=%#x image=%#x container=%#x" %
                (header_size, image_size, len(raw)))
        receipt.update({
            "format": "mcuboot",
            "magic": "0x%08x" % magic,
            "header_size": header_size,
            "protected_tlv_size": protected_tlv_size,
            "image_size": image_size,
            "flags": "0x%08x" % flags,
            "header_load_address": "0x%08x" % load_address,
            "payload_offset": header_size,
            "payload_size": image_size,
            "trailing_bytes": len(raw) - payload_end,
        })
        payload = raw[header_size:payload_end]
    else:
        payload = raw
    receipt["payload_sha256"] = sha256(payload)
    return payload, receipt


def diff_ranges(expected, actual, base):
    """Return compact absolute-address ranges for unequal/missing bytes."""
    limit = max(len(expected), len(actual))
    unequal = [index for index in range(limit)
               if index >= len(expected) or index >= len(actual) or
               expected[index] != actual[index]]
    ranges = []
    for index in unequal:
        if not ranges or index != ranges[-1][1]:
            ranges.append([index, index + 1])
        else:
            ranges[-1][1] += 1
    return [{"start": "0x%08x" % (base + first),
             "end_exclusive": "0x%08x" % (base + last),
             "size": last - first}
            for first, last in ranges]


def opcode_sequence(data, address):
    disassembler = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    instructions = list(disassembler.disasm(data, address))
    return ([instruction.mnemonic.split(".")[0]
             for instruction in instructions],
            sum(instruction.size for instruction in instructions))


def opcode_ratio(expected, actual, address):
    left, left_bytes = opcode_sequence(expected, address)
    right, right_bytes = opcode_sequence(actual, address)
    if not left and not right:
        return None, 0, 0, left_bytes, right_bytes
    return (difflib.SequenceMatcher(None, left, right).ratio(),
            len(left), len(right), left_bytes, right_bytes)


def parse_map(path):
    """Extract top-level output-section placement from a GNU linker map."""
    if path is None:
        return None
    path = Path(path)
    pattern = re.compile(
        r"^([A-Za-z_.][A-Za-z0-9_.$-]*)\s+"
        r"0x([0-9a-fA-F]+)\s+0x([0-9a-fA-F]+)\s*$")
    rows = []
    seen = set()
    for line in path.read_text(errors="replace").splitlines():
        match = pattern.match(line)
        if not match or match.group(1) in seen:
            continue
        seen.add(match.group(1))
        rows.append({
            "name": match.group(1),
            "vma": "0x%08x" % int(match.group(2), 16),
            "size": int(match.group(3), 16),
        })
    return {
        "path": str(path.resolve()),
        "sha256": sha256(path.read_bytes()),
        "output_sections": rows,
    }


def loadable_sections(elf):
    segments = [segment for segment in elf.iter_segments()
                if segment["p_type"] == "PT_LOAD" and segment["p_filesz"]]
    rows = []
    for section in elf.iter_sections():
        flags = int(section["sh_flags"])
        size = int(section["sh_size"])
        if not size or not (flags & SHF_ALLOC) or section["sh_type"] == "SHT_NOBITS":
            continue
        owners = [segment for segment in segments
                  if segment.section_in_segment(section)]
        if len(owners) != 1:
            raise ComparisonError(
                "%s belongs to %d file-backed PT_LOAD segments" %
                (section.name, len(owners)))
        segment = owners[0]
        vma = int(section["sh_addr"])
        lma = int(segment["p_paddr"]) + vma - int(segment["p_vaddr"])
        rows.append((section, vma, lma, flags))
    return rows


def classify_section(name, flags, vma, lma):
    # Zephyr's ``rom_start`` is WAX even though it is predominantly the vector
    # table.  Treat it as an exact layout object, not as code whose encodings
    # may legitimately drift.  Unwind tables likewise carry address/layout
    # information and belong to the exact gate.
    if name == "rom_start":
        return "vectors"
    if name == ".ARM.exidx":
        return "immutable"
    if flags & SHF_EXECINSTR:
        return "executable"
    if vma != lma or flags & SHF_WRITE:
        return "data_initializer"
    return "immutable"


def compare(core, elf_path, firmware_path=None, map_path=None,
            runtime_base=None, analysis_base=None):
    defaults = DEFAULTS[core]
    runtime_base = defaults["runtime_base"] if runtime_base is None else runtime_base
    analysis_base = defaults["analysis_base"] if analysis_base is None else analysis_base
    firmware_path = defaults["firmware"] if firmware_path is None else firmware_path
    payload, container = load_payload(firmware_path)
    elf_path = Path(elf_path)
    sections = []
    intervals = []
    with elf_path.open("rb") as stream:
        elf = ELFFile(stream)
        for section, vma, lma, flags in loadable_sections(elf):
            data = section.data()
            offset = lma - runtime_base
            in_range = offset >= 0 and offset + len(data) <= len(payload)
            original = payload[offset:offset + len(data)] if in_range else b""
            equal = (data == original) if in_range else False
            equal_bytes = (sum(left == right for left, right in zip(data, original))
                           if in_range else 0)
            category = classify_section(section.name, flags, vma, lma)
            row = {
                "name": section.name,
                "category": category,
                "vma": "0x%08x" % vma,
                "lma": "0x%08x" % lma,
                "analysis_lma": "0x%08x" % (lma - runtime_base + analysis_base),
                "size": len(data),
                "alignment": int(section["sh_addralign"]),
                "flags": {
                    "alloc": bool(flags & SHF_ALLOC),
                    "write": bool(flags & SHF_WRITE),
                    "execute": bool(flags & SHF_EXECINSTR),
                },
                "in_original_payload": in_range,
                "elf_sha256": sha256(data),
                "original_sha256": sha256(original) if in_range else None,
                "byte_exact": equal,
                "equal_bytes": equal_bytes,
                "exact_byte_ratio": round(equal_bytes / len(data), 8),
                "first_difference": None,
                "difference_ranges": [],
            }
            if not equal:
                ranges = diff_ranges(data, original, lma)
                row["difference_ranges"] = ranges[:64]
                row["difference_range_count"] = len(ranges)
                row["difference_ranges_truncated"] = len(ranges) > 64
                row["first_difference"] = ranges[0]["start"] if ranges else None
            if category == "executable" and in_range:
                ratio, elf_count, original_count, elf_decoded, original_decoded = (
                    opcode_ratio(data, original, lma))
                elf_coverage = elf_decoded / len(data)
                original_coverage = original_decoded / len(original)
                complete = elf_coverage >= 0.95 and original_coverage >= 0.95
                row["text_similarity"] = {
                    "method": "ordered_thumb_mnemonic_sequence",
                    "status": "complete" if complete else "partial_decode",
                    "opcode_ratio": (round(ratio, 8)
                                     if ratio is not None and complete else None),
                    "partial_opcode_ratio": (None if ratio is None
                                               else round(ratio, 8)),
                    "elf_instruction_count": elf_count,
                    "original_instruction_count": original_count,
                    "elf_decode_coverage": round(elf_coverage, 8),
                    "original_decode_coverage": round(original_coverage, 8),
                    "relocation_masking": "unavailable_in_final_linked_elf",
                    "hard_gate": False,
                }
            sections.append(row)
            intervals.append((lma, lma + len(data), section.name))

    overlaps = []
    for previous, current in zip(sorted(intervals), sorted(intervals)[1:]):
        if current[0] < previous[1]:
            overlaps.append({
                "first": previous[2], "second": current[2],
                "start": "0x%08x" % current[0],
                "end_exclusive": "0x%08x" % min(previous[1], current[1]),
            })
    non_text = [row for row in sections if row["category"] != "executable"]
    executable = [row for row in sections if row["category"] == "executable"]
    out_of_range = [row["name"] for row in sections
                    if not row["in_original_payload"]]
    elf_load_base = min((first for first, _last, _name in intervals),
                        default=None)
    load_base_matches = elf_load_base == runtime_base
    report = {
        "schema": 1,
        "generated_by": "tools/compare_firmware_sections.py",
        "core": core,
        "coordinate_spaces": {
            "runtime_base": "0x%08x" % runtime_base,
            "analysis_base": "0x%08x" % analysis_base,
            "analysis_to_runtime_delta": "0x%x" % (runtime_base - analysis_base),
            "elf_sections_compared_by": "load_memory_address",
        },
        "firmware": container,
        "elf": {
            "path": str(elf_path.resolve()),
            "size": elf_path.stat().st_size,
            "sha256": sha256(elf_path.read_bytes()),
        },
        "linker_map": parse_map(map_path),
        "sections": sections,
        "summary": {
            "loadable_file_backed_sections": len(sections),
            "payload_size": len(payload),
            "payload_runtime_end": "0x%08x" % (runtime_base + len(payload)),
            "elf_load_base": (None if elf_load_base is None
                              else "0x%08x" % elf_load_base),
            "executable_sections": len(executable),
            "non_executable_sections": len(non_text),
            "exact_sections": sum(row["byte_exact"] for row in sections),
            "exact_non_executable_sections": sum(row["byte_exact"] for row in non_text),
            "compared_bytes": sum(row["size"] for row in sections
                                  if row["in_original_payload"]),
            "equal_bytes": sum(row["equal_bytes"] for row in sections),
            "out_of_range_sections": out_of_range,
            "overlaps": overlaps,
        },
        "gates": {
            "load_base_matches_runtime": load_base_matches,
            "structural_pass": load_base_matches and not out_of_range and not overlaps,
            "non_executable_exact_pass": bool(non_text) and all(
                row["byte_exact"] for row in non_text),
            "text_policy": "diagnostic_only_semantic_CFG_proof_remains_authoritative",
        },
    }
    return report


def int_argument(value):
    return int(value, 0)


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("core", choices=sorted(DEFAULTS))
    parser.add_argument("elf")
    parser.add_argument("--firmware")
    parser.add_argument("--map", dest="map_path")
    parser.add_argument("--runtime-base", type=int_argument)
    parser.add_argument("--analysis-base", type=int_argument)
    parser.add_argument("--output")
    parser.add_argument("--strict-data", action="store_true",
                        help="fail unless every non-executable loadable section is exact")
    args = parser.parse_args(argv)
    try:
        report = compare(args.core, args.elf, args.firmware, args.map_path,
                         args.runtime_base, args.analysis_base)
    except (ComparisonError, OSError, ValueError) as error:
        print("comparison error: %s" % error, file=sys.stderr)
        return 2
    rendered = json.dumps(report, indent=1, sort_keys=True) + "\n"
    if args.output:
        Path(args.output).write_text(rendered)
    else:
        print(rendered, end="")
    if not report["gates"]["structural_pass"]:
        return 2
    if args.strict_data and not report["gates"]["non_executable_exact_pass"]:
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
