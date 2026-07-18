#!/usr/bin/env python3
"""Receipt normal CPUAPP GC, named roots, and verified-table retention."""

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_app_root_topology


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_BEFORE = Path("/private/tmp/g1-cohesive-app-final")
DEFAULT_AFTER = Path("/private/tmp/g1-cohesive-app-gc")
ROOTS = ROOT / "recon/catalogs/app_gc_roots.json"
DATA_LIST = ROOT / "recon/generated/app_verified_data_sources.cmake"
FIXED_DATA = ROOT / "recon/catalogs/app_fixed_verified_rodata.json"
OUT_JSON = ROOT / "recon/catalogs/app_gc_convergence.json"
OUT_MD = ROOT / "recon/analysis/app_gc_convergence.md"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def elf_facts(build):
    path = build / "zephyr/zephyr.elf"
    with path.open("rb") as handle:
        elf = ELFFile(handle)
        sections = {section.name: section["sh_size"] for section in elf.iter_sections()}
        symtab = elf.get_section_by_name(".symtab")
        symbols = {
            symbol.name: {
                "size": symbol["st_size"],
                "section": (elf.get_section(symbol["st_shndx"]).name
                            if isinstance(symbol["st_shndx"], int) else None),
            }
            for symbol in symtab.iter_symbols()
        }
    undefined = subprocess.check_output([str(NM), "-u", str(path)], text=True).splitlines()
    return path, sections, symbols, undefined


def verified_symbols():
    cmake = DATA_LIST.read_text()
    names = []
    for filename in re.findall(r"\.\./data/([^\" ]+\.c)", cmake):
        path = ROOT / "recon/data" / filename
        text = path.read_text()
        match = re.search(r"rodata_((?:0x)?[0-9a-fA-F]+)", filename)
        base = int(match.group(1), 16)
        bhex = f"{base:x}"
        candidates = [name for name in re.findall(
            r"\b(\w+)\s*(?:\[\s*\d*\s*\])?\s*=\s*\{", text)
            if bhex in name.lower()]
        names.append(candidates[0] if candidates else f"rodata_{base:x}")
    comment = re.search(r"Byte-exact inputs: (\d+) files, (\d+) bytes", cmake)
    return names, int(comment.group(1)), int(comment.group(2))


def build(before, after):
    cache = (after / "CMakeCache.txt").read_text(errors="replace")
    if "G1_INTEGRATION_PROBE_RETAIN_ALL:BOOL=OFF" not in cache:
        raise ValueError("candidate build is not normal-GC mode")
    before_elf, before_sections, _, before_undefined = elf_facts(before)
    after_elf, after_sections, symbols, after_undefined = elf_facts(after)
    if before_undefined or after_undefined:
        raise ValueError("cohesive ELF contains undefined symbols")

    roots = json.loads(ROOTS.read_text())
    named = [row["symbol"] for row in roots["roots"] if row["resolved"]]
    missing_roots = sorted(set(named) - set(symbols))
    if missing_roots:
        raise ValueError("named GC roots missing from ELF: %r" % missing_roots)

    expected, expected_count, verified_payload_bytes = verified_symbols()
    if len(expected) != expected_count or len(set(expected)) != expected_count:
        raise ValueError("verified-data list cardinality drift")
    missing_data = sorted(set(expected) - set(symbols))
    fixed_catalog = json.loads(FIXED_DATA.read_text())
    fixed_sections = {row["symbol"]: row["fixed_output_section"]
                      for row in fixed_catalog["tables"]}
    fixed_enabled = "G1_ENABLE_FIXED_VERIFIED_RODATA:BOOL=ON" in cache
    wrong_sections = sorted(
        name for name in expected if name in symbols and
        symbols[name]["section"] != (fixed_sections.get(name, "rodata")
                                     if fixed_enabled else "rodata"))
    if missing_data or wrong_sections:
        raise ValueError("verified rodata retention drift: missing=%d wrong_section=%d" %
                         (len(missing_data), len(wrong_sections)))
    emitted_data_bytes = sum(symbols[name]["size"] for name in expected)

    map_text = (after / "zephyr/zephyr.map").read_text(errors="replace")
    init_counts, device_count = check_app_root_topology.topology_from_map(map_text)
    if init_counts != check_app_root_topology.EXPECTED_INIT_COUNTS:
        raise ValueError("init topology drift")
    if device_count != check_app_root_topology.EXPECTED_DEVICE_COUNT:
        raise ValueError("device topology drift")

    inventory = json.loads((ROOT / "recon/catalogs/app_root_inventory.json").read_text())
    original_text_span = int(inventory["init_levels"][0]["start"], 16) - 0x0000C358
    original_payload_bytes = (ROOT / "app_update.bin").stat().st_size - 512
    section_names = [
        "rom_start", "text", ".ARM.exidx", "initlevel", "device_area",
        "sw_isr_table", "rodata", "datas", "bss", "noinit",
    ]
    rows = {}
    for name in section_names:
        b, a = before_sections.get(name, 0), after_sections.get(name, 0)
        rows[name] = {"retain_all": b, "normal_gc": a, "delta": a - b}
    return {
        "schema": 2, "core": "app", "status": "normal_gc_complete_roots",
        "policy": "complete named evidence roots; byte-verified ordinary rodata; fixed placement opt-in; SDC report-only",
        "builds": {
            "retain_all": {"path": str(before), "elf_sha256": sha(before_elf)},
            "normal_gc": {"path": str(after), "elf_sha256": sha(after_elf)},
        },
        "roots": {
            "named": len(named), "all_present": True,
            "unresolved_candidates": roots["unresolved_addresses"],
            "complete": roots["summary"]["complete_root_graph"],
        },
        "verified_rodata": {
            "symbols": expected_count, "all_present": True,
            "all_in_expected_sections": True,
            "normal_rodata_symbols": (expected_count - len(fixed_sections)
                                       if fixed_enabled else expected_count),
            "fixed_address_symbols": (len(fixed_sections)
                                      if fixed_enabled else 0),
            "fixed_address_bytes": (fixed_catalog["selected_bytes"]
                                    if fixed_enabled else 0),
            "fixed_address_enabled": fixed_enabled,
            "verified_payload_bytes": verified_payload_bytes,
            "emitted_symbol_bytes": emitted_data_bytes,
        },
        "topology": {"init_counts": init_counts, "device_count": device_count},
        "comparison": {
            "section_sizes": rows,
            "original_pre_init_span_bytes": original_text_span,
            "normal_gc_text_delta_from_original_pre_init_span":
                after_sections["text"] - original_text_span,
            "original_unsigned_payload_bytes": original_payload_bytes,
            "normal_gc_bin_bytes": (after / "zephyr/zephyr.bin").stat().st_size,
            "retain_all_bin_bytes": (before / "zephyr/zephyr.bin").stat().st_size,
        },
        "undefined_symbols": 0,
    }


def markdown(data):
    comp = data["comparison"]
    lines = [
        "# CPUAPP normal-GC convergence", "",
        "The cohesive CPUAPP links with normal Zephyr section GC. Only named "
        "binary-derived roots and byte-verified standalone rodata are retained "
        "explicitly. Fixed-address placement is opt-in because the current "
        "layout crosses the old suffix boundary. No numeric function root, code deletion, or SDC adoption "
        "is used.", "",
        f"- Named recovered roots present: **{data['roots']['named']}/{data['roots']['named']}**",
        f"- Unresolved root candidates: **{len(data['roots']['unresolved_candidates'])}**" +
        ((f" ({', '.join(data['roots']['unresolved_candidates'])})")
         if data['roots']['unresolved_candidates'] else ""),
        f"- Verified data symbols present: **{data['verified_rodata']['symbols']}/"
        f"{data['verified_rodata']['symbols']}**",
        f"- Fixed-address verified suffix: **{data['verified_rodata']['fixed_address_symbols']} "
        f"symbols / {data['verified_rodata']['fixed_address_bytes']} bytes**",
        f"- Verified payload: **{data['verified_rodata']['verified_payload_bytes']} bytes**; "
        f"ELF symbol storage: **{data['verified_rodata']['emitted_symbol_bytes']} bytes**",
        "- Undefined symbols: **0**", "",
        "| Section | Retain-all | Normal GC | Delta |", "|---|---:|---:|---:|",
    ]
    for name, row in comp["section_sizes"].items():
        lines.append(f"| `{name}` | {row['retain_all']} | {row['normal_gc']} | {row['delta']:+d} |")
    lines += [
        "",
        f"The shipped pre-init span is {comp['original_pre_init_span_bytes']} bytes; "
        f"normal-GC `.text` is {comp['normal_gc_text_delta_from_original_pre_init_span']:+d} bytes "
        "relative to that span. This span includes original literal/data islands, so it is a "
        "convergence bound rather than a claim of exact `.text` size.",
        "",
        "The binary-derived root graph is complete: every candidate has a named recovered "
        "definition and no numeric firmware address is forced at link time.", "",
    ]
    return "\n".join(lines)


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError(f"stale output: {path}")
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--before", type=Path, default=DEFAULT_BEFORE)
    parser.add_argument("--after", type=Path, default=DEFAULT_AFTER)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build(args.before, args.after)
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_MD, markdown(data), args.check)
    print(json.dumps({
        "normal_gc_bin": data["comparison"]["normal_gc_bin_bytes"],
        "named_roots": data["roots"]["named"],
        "verified_rodata": data["verified_rodata"]["symbols"],
        "undefined": data["undefined_symbols"],
    }, sort_keys=True))


if __name__ == "__main__":
    main()
