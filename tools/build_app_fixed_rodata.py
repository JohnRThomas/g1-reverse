#!/usr/bin/env python3
"""Generate fail-closed fixed-address CPUAPP tables above the linked ROM image.

The normal cohesive link deliberately keeps its code and SDK layout free to use
Zephyr's ordinary garbage collection.  A verified table is moved out of its C
translation unit only when its complete object bytes match the shipped payload
and its original address is beyond every file-backed section in the recorded
normal-GC baseline.  Anything else remains in the ordinary ``.rodata`` output.
"""

import argparse
import hashlib
import json
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent))
from compare_firmware_sections import load_payload


ROOT = Path(__file__).resolve().parents[1]
CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")
CFLAGS = ["-c", "-Os", "-mcpu=cortex-m33", "-mthumb", "-ffreestanding", "-w",
          "-fdata-sections"]
RUNTIME_BASE = 0x0000C200


class GenerationError(RuntimeError):
    """The fixed-address subset cannot be generated without guessing."""


@dataclass(frozen=True)
class Table:
    source: Path
    symbol: str
    address: int
    data: bytes
    alignment: int
    complete_owner: bool = True

    @property
    def end(self):
        return self.address + len(self.data)


def sha256(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def verified_sources(path):
    text = Path(path).read_text()
    names = re.findall(r'\.\./data/([^"\s]+\.c)', text)
    if not names:
        raise GenerationError("verified source list is empty")
    return [ROOT / "recon" / "data" / name for name in names]


def source_identity(path):
    text = Path(path).read_text()
    match = re.search(r'rodata_((?:0x)?[0-9a-fA-F]+)', path.name)
    if not match:
        raise GenerationError("cannot derive table VA from %s" % path)
    address = int(match.group(1), 16)
    address_hex = "%x" % address
    candidates = [name for name in
                  re.findall(r'\b(\w+)\s*(?:\[\s*\d*\s*\])?\s*=\s*\{', text)
                  if address_hex in name.lower()]
    if not candidates:
        raise GenerationError("expected an address-bearing symbol in %s" % path)
    declared = re.search(r'(\d+)\s*bytes', text)
    return address, candidates[0], int(declared.group(1)) if declared else None


def compile_table(path, output):
    result = subprocess.run([str(CC), *CFLAGS, str(path), "-o", str(output)],
                            capture_output=True, text=True)
    if result.returncode:
        raise GenerationError("compile failed for %s:\n%s" % (path, result.stderr))


def object_symbol(path, symbol):
    with Path(path).open("rb") as stream:
        elf = ELFFile(stream)
        symtab = elf.get_section_by_name(".symtab")
        matches = [entry for entry in symtab.iter_symbols() if entry.name == symbol]
        if len(matches) != 1 or not isinstance(matches[0]["st_shndx"], int):
            raise GenerationError("expected one defined symbol %s in %s" % (symbol, path))
        entry = matches[0]
        section = elf.get_section(entry["st_shndx"])
        start = int(entry["st_value"])
        size = int(entry["st_size"])
        defined_objects = [candidate.name for candidate in symtab.iter_symbols()
                           if isinstance(candidate["st_shndx"], int) and
                           candidate["st_info"]["type"] == "STT_OBJECT" and
                           int(candidate["st_size"])]
        return (section.data()[start:start + size], int(section["sh_addralign"]),
                defined_objects)


def baseline_end(report_path):
    report = json.loads(Path(report_path).read_text())
    sections = report.get("sections", [])
    if not sections or report.get("summary", {}).get("overlaps"):
        raise GenerationError("baseline comparison has no valid non-overlapping section receipt")
    ends = [int(row["lma"], 16) + int(row["size"]) for row in sections]
    end = max(ends)
    return end, {
        "path": str(Path(report_path).resolve()),
        "sha256": sha256(report_path),
        "elf": report.get("elf"),
        "rom_end_exclusive": "0x%08x" % end,
    }


def select_tables(tables, rom_end, payload_end, rejection_receipt=None):
    """Return safe tables and a reason count for every rejected table."""
    selected = []
    rejected = {"below_baseline_rom_end": 0, "outside_payload": 0,
                "misaligned": 0, "overlap": 0, "multi_symbol_owner": 0}
    def reject(table, reason):
        rejected[reason] += 1
        if rejection_receipt is not None:
            rejection_receipt.append({
                "source": str(table.source.relative_to(ROOT)),
                "symbol": table.symbol,
                "address": "0x%08x" % table.address,
                "size": len(table.data),
                "reason": reason,
                "retained_owner": "C source",
                "current_output_section": ".rodata",
            })

    for table in sorted(tables, key=lambda item: (item.address, item.symbol)):
        if table.address < rom_end:
            reject(table, "below_baseline_rom_end")
            continue
        if not table.complete_owner:
            reject(table, "multi_symbol_owner")
            continue
        if table.end > payload_end:
            reject(table, "outside_payload")
            continue
        if table.address % max(table.alignment, 1):
            reject(table, "misaligned")
            continue
        if selected and table.address < selected[-1].end:
            reject(table, "overlap")
            continue
        selected.append(table)
    return selected, rejected


def asm_text(tables):
    lines = ["/* Generated by tools/build_app_fixed_rodata.py; do not edit. */"]
    for table in tables:
        section = ".g1_verified.rodata.%08x" % table.address
        lines += ["", '.section %s,"a",%%progbits' % section,
                  ".balign %d" % max(table.alignment, 1),
                  ".global %s" % table.symbol,
                  ".type %s, %%object" % table.symbol,
                  "%s:" % table.symbol]
        for offset in range(0, len(table.data), 16):
            chunk = table.data[offset:offset + 16]
            lines.append(".byte " + ",".join("0x%02x" % byte for byte in chunk))
        lines.append(".size %s, .-%s" % (table.symbol, table.symbol))
    lines += ["", '.section .note.GNU-stack,"",%progbits', ""]
    return "\n".join(lines)


def linker_text(tables):
    lines = ["/* Generated by tools/build_app_fixed_rodata.py; do not edit. */"]
    for table in tables:
        token = "%08x" % table.address
        lines += ["", ".g1_verified_rodata_%s 0x%s :" % (token, token), "{",
                  "  KEEP(*(.g1_verified.rodata.%s))" % token,
                  "} > FLASH"]
    return "\n".join(lines) + "\n"


def cmake_text(tables):
    lines = ["# Generated by tools/build_app_fixed_rodata.py; do not edit.",
             "set(G1_FIXED_VERIFIED_DATA_C_SOURCES"]
    for table in tables:
        lines.append('  "${CMAKE_CURRENT_LIST_DIR}/../data/%s"' % table.source.name)
    lines += [")", "set(G1_FIXED_VERIFIED_DATA_ASM",
              '  "${CMAKE_CURRENT_LIST_DIR}/app_fixed_verified_rodata.S")',
              "set(G1_FIXED_VERIFIED_DATA_LINKER",
              '  "${CMAKE_CURRENT_LIST_DIR}/app_fixed_verified_rodata.ld")', ""]
    return "\n".join(lines)


def write_if_changed(path, content):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_text() != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--baseline-report", type=Path,
                        default=ROOT / "recon/analysis/app_binary_section_comparison.json")
    parser.add_argument("--source-list", type=Path,
                        default=ROOT / "recon/generated/app_verified_data_sources.cmake")
    parser.add_argument("--firmware", type=Path, default=ROOT / "app_update.bin")
    parser.add_argument("--generated-dir", type=Path,
                        default=ROOT / "recon/generated")
    parser.add_argument("--catalog", type=Path,
                        default=ROOT / "recon/catalogs/app_fixed_verified_rodata.json")
    args = parser.parse_args()

    payload, firmware_receipt = load_payload(args.firmware)
    rom_end, baseline_receipt = baseline_end(args.baseline_report)
    payload_end = RUNTIME_BASE + len(payload)
    tables = []
    padding_rejections = 0
    rejection_receipt = []
    with tempfile.TemporaryDirectory() as temp:
        for index, source in enumerate(verified_sources(args.source_list)):
            address, symbol, declared_size = source_identity(source)
            obj = Path(temp) / ("table_%04d.o" % index)
            compile_table(source, obj)
            emitted, alignment, defined_objects = object_symbol(obj, symbol)
            if declared_size is not None and declared_size != len(emitted):
                padding_rejections += 1
                rejection_receipt.append({
                    "source": str(source.relative_to(ROOT)),
                    "symbol": symbol,
                    "address": "0x%08x" % address,
                    "verified_prefix_size": declared_size,
                    "compiler_symbol_size": len(emitted),
                    "reason": "object_padding",
                    "retained_owner": "C source",
                    "current_output_section": ".rodata",
                })
                continue
            if payload[address - RUNTIME_BASE:address - RUNTIME_BASE + len(emitted)] != emitted:
                raise GenerationError("verified source no longer matches firmware: %s" % source)
            tables.append(Table(source, symbol, address, emitted, alignment,
                                defined_objects == [symbol]))

    selected, rejected = select_tables(tables, rom_end, payload_end,
                                       rejection_receipt)
    rejected["object_padding"] = padding_rejections
    if not selected:
        raise GenerationError("no safe fixed-address tables selected")

    generated = args.generated_dir
    write_if_changed(generated / "app_fixed_verified_rodata.S", asm_text(selected))
    write_if_changed(generated / "app_fixed_verified_rodata.ld", linker_text(selected))
    write_if_changed(generated / "app_fixed_verified_rodata.cmake", cmake_text(selected))

    catalog = {
        "schema": 1,
        "policy": "complete byte-exact objects strictly beyond normal-GC ROM end",
        "runtime_base": "0x%08x" % RUNTIME_BASE,
        "payload_end_exclusive": "0x%08x" % payload_end,
        "baseline": baseline_receipt,
        "firmware": firmware_receipt,
        "verified_source_count": len(verified_sources(args.source_list)),
        "selected_count": len(selected),
        "selected_bytes": sum(len(table.data) for table in selected),
        "rejected": rejected,
        "tables": [{"source": str(table.source.relative_to(ROOT)),
                    "symbol": table.symbol,
                    "address": "0x%08x" % table.address,
                    "end_exclusive": "0x%08x" % table.end,
                    "size": len(table.data),
                    "alignment": table.alignment,
                    "generated_input_section": ".g1_verified.rodata.%08x" % table.address,
                    "fixed_output_section": ".g1_verified_rodata_%08x" % table.address,
                    "sha256": hashlib.sha256(table.data).hexdigest()}
                   for table in selected],
        "rejected_tables": sorted(rejection_receipt,
                                  key=lambda row: (row["address"], row["symbol"])),
    }
    args.catalog.parent.mkdir(parents=True, exist_ok=True)
    args.catalog.write_text(json.dumps(catalog, indent=2, sort_keys=True) + "\n")
    print("selected %d tables / %d bytes at 0x%x..0x%x; rejected %s" %
          (len(selected), catalog["selected_bytes"], selected[0].address,
           selected[-1].end, rejected))


if __name__ == "__main__":
    main()
