#!/usr/bin/env python3
"""Measure the isolated normal-GC impact of CPUAPP address-taken roots."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "recon/catalogs/app_address_taken_roots.json"
OUT_JSON = ROOT / "recon/analysis/app_address_taken_root_build.json"
OUT_MD = ROOT / "recon/analysis/app_address_taken_root_build.md"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def facts(build):
    elf_path = build / "zephyr/zephyr.elf"
    cache = (build / "CMakeCache.txt").read_text(errors="replace")
    with elf_path.open("rb") as stream:
        elf = ELFFile(stream)
        section_rows = {section.name: section for section in elf.iter_sections()}
        sections = {name: section["sh_size"] for name, section in section_rows.items()}
        functions = [symbol for symbol in elf.get_section_by_name(".symtab").iter_symbols()
                     if symbol["st_info"]["type"] == "STT_FUNC" and
                     symbol["st_shndx"] != "SHN_UNDEF"]
        function_sizes = {symbol.name: symbol["st_size"] for symbol in functions}
    undefined = subprocess.check_output([str(NM), "-u", str(elf_path)], text=True).splitlines()
    return {
        "build": str(build), "elf_sha256": sha(elf_path),
        "bin_bytes": (build / "zephyr/zephyr.bin").stat().st_size,
        "sections": {name: sections.get(name, 0) for name in
                     ("text", "rodata", "datas", "bss", "noinit")},
        "section_addresses": {name: "0x%08x" % section_rows[name]["sh_addr"]
                              for name in ("text", "rodata", "datas")},
        "function_symbol_entries": len(functions),
        "function_symbol_bytes": sum(symbol["st_size"] for symbol in functions),
        "function_sizes": function_sizes,
        "undefined_symbols": undefined,
        "config": {
            "normal_gc": "G1_INTEGRATION_PROBE_RETAIN_ALL:BOOL=OFF" in cache,
            "address_taken_roots": "G1_ENABLE_ADDRESS_TAKEN_ROOTS:BOOL=ON" in cache,
            "fixed_verified_rodata": "G1_ENABLE_FIXED_VERIFIED_RODATA:BOOL=ON" in cache,
        },
    }


def build(baseline, rooted, baseline_comparison, rooted_comparison):
    before, after = facts(baseline), facts(rooted)
    if not before["config"]["normal_gc"] or not after["config"]["normal_gc"]:
        raise ValueError("both measurements must use normal section GC")
    if before["config"]["address_taken_roots"]:
        raise ValueError("baseline unexpectedly enables address-taken roots")
    if not after["config"]["address_taken_roots"]:
        raise ValueError("rooted build does not enable address-taken roots")
    if before["config"]["fixed_verified_rodata"] or after["config"]["fixed_verified_rodata"]:
        raise ValueError("isolated closure comparison requires ordinary verified rodata")
    if before["undefined_symbols"] or after["undefined_symbols"]:
        raise ValueError("measurement ELF contains undefined symbols")

    ledger = json.loads(LEDGER.read_text())
    roots = {row["link_symbol"] for row in ledger["entries"] if row["emitted_root"]}
    missing = sorted(roots - set(after["function_sizes"]))
    if missing:
        raise ValueError("emitted roots absent from rooted ELF: %r" % missing)
    new_names = sorted(set(after["function_sizes"]) - set(before["function_sizes"]))
    section_delta = {name: after["sections"][name] - before["sections"][name]
                     for name in before["sections"]}
    comparisons = {}
    for label, path in (("baseline", baseline_comparison), ("rooted", rooted_comparison)):
        receipt = json.loads(path.read_text())
        comparisons[label] = {
            "path": str(path), "sha256": sha(path),
            "summary": receipt["summary"],
        }
    fixed_start, fixed_end = 0x0008B264, 0x0008B2C0
    before_ro_start = int(before["section_addresses"]["rodata"], 16)
    after_ro_start = int(after["section_addresses"]["rodata"], 16)
    before_ro_end = before_ro_start + before["sections"]["rodata"]
    after_ro_end = after_ro_start + after["sections"]["rodata"]
    result = {
        "schema": 1, "core": "app", "status": "linked_normal_gc_audit",
        "policy": "isolated named-root closure; fixed verified placement disabled only for layout audit",
        "baseline": {key: value for key, value in before.items() if key != "function_sizes"},
        "rooted": {key: value for key, value in after.items() if key != "function_sizes"},
        "delta": {
            "bin_bytes": after["bin_bytes"] - before["bin_bytes"],
            "sections": section_delta,
            "function_symbol_entries": (after["function_symbol_entries"] -
                                        before["function_symbol_entries"]),
            "function_symbol_bytes": (after["function_symbol_bytes"] -
                                      before["function_symbol_bytes"]),
            "new_unique_function_names": len(new_names),
            "new_unique_function_bytes": sum(after["function_sizes"][name] for name in new_names),
        },
        "roots": {"requested": len(roots), "all_present": True,
                  "symbols": sorted(roots)},
        "comparator": comparisons,
        "fixed_placement_gate": {
            "status": "blocked_overlap",
            "baseline_ordinary_rodata_lma": ["0x%08x" % before_ro_start,
                                               "0x%08x" % before_ro_end],
            "rooted_ordinary_rodata_lma": ["0x%08x" % after_ro_start,
                                             "0x%08x" % after_ro_end],
            "first_fixed_table_lma": ["0x0008b264", "0x0008b2c0"],
            "baseline_already_overlaps_after_dmic_lc3_edge":
                before_ro_start < fixed_end and fixed_start < before_ro_end,
            "rooted_overlaps": after_ro_start < fixed_end and fixed_start < after_ro_end,
            "action": "keep roots opt-in; final section layout must move ordinary rodata without overlap",
        },
    }
    result["comparator"]["equal_bytes_delta"] = (
        comparisons["rooted"]["summary"]["equal_bytes"] -
        comparisons["baseline"]["summary"]["equal_bytes"])
    return result


def markdown(data):
    delta = data["delta"]
    return "\n".join([
        "# CPUAPP address-taken root build impact", "",
        "A clean normal-GC pair isolates the generated named roots. Both builds "
        "use ordinary byte-verified rodata because the added live closure reaches "
        "the currently fixed suffix; production admission therefore remains opt-in.", "",
        "- Emitted roots present: **%d/%d**" %
            (data["roots"]["requested"], data["roots"]["requested"]),
        "- FLASH/bin delta: **%+d bytes**" % delta["bin_bytes"],
        "- `.text` delta: **%+d bytes**" % delta["sections"]["text"],
        "- `.rodata` delta: **%+d bytes**" % delta["sections"]["rodata"],
        "- Function-symbol entry delta: **%+d**" % delta["function_symbol_entries"],
        "- New unique function names/bytes: **%d / %d**" %
            (delta["new_unique_function_names"], delta["new_unique_function_bytes"]),
        "- Firmware comparator equal-byte delta: **%+d**" %
            data["comparator"]["equal_bytes_delta"],
        "- Undefined symbols: **0**", "",
        "After the independent DMIC→LC3 direct-edge repair, baseline ordinary "
        "`rodata` already spans `%s..%s`; the rooted build spans `%s..%s`. Both "
        "overlap the first fixed table at `0x0008b264`. Address-taken roots remain "
        "opt-in while final section layout is unresolved. No table address, padding, "
        "broad `KEEP`, or function body was changed to hide the collision." % (
            data["fixed_placement_gate"]["baseline_ordinary_rodata_lma"][0],
            data["fixed_placement_gate"]["baseline_ordinary_rodata_lma"][1],
            data["fixed_placement_gate"]["rooted_ordinary_rodata_lma"][0],
            data["fixed_placement_gate"]["rooted_ordinary_rodata_lma"][1]), "",
    ])


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError("stale generated file: %s" % path)
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--baseline", type=Path,
                        default=Path("/private/tmp/g1-cohesive-app-address-baseline"))
    parser.add_argument("--rooted", type=Path,
                        default=Path("/private/tmp/g1-cohesive-app-address-roots"))
    parser.add_argument("--baseline-comparison", type=Path,
                        default=Path("/private/tmp/app-address-baseline-comparison.json"))
    parser.add_argument("--rooted-comparison", type=Path,
                        default=Path("/private/tmp/app-address-roots-comparison.json"))
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build(args.baseline, args.rooted,
                 args.baseline_comparison, args.rooted_comparison)
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_MD, markdown(data), args.check)
    print(json.dumps(data["delta"], sort_keys=True))


if __name__ == "__main__":
    main()
