#!/usr/bin/env python3
"""Prove the configured CPUNET Nordic RTC timer owner closure.

The old catalog trusted Ghidra's 0x100-byte extent for ``compare_set``.  The
real function is 0x124 bytes: its final stores and two relocated state words
were incorrectly treated as trailing data.  This builder compares complete
ELF sections, resolves every relocation, and records the neighboring NCS
source history so the ownership decision cannot silently broaden to a merely
similar SDK version.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
ZEPHYR = NCS / "zephyr"
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
CONFIG = BUILD / "zephyr/.config"
OBJECT = (BUILD / "zephyr/drivers/timer/CMakeFiles/"
          "drivers__timer.dir/nrf_rtc_timer.c.obj")
SOURCE = ZEPHYR / "drivers/timer/nrf_rtc_timer.c"
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/catalogs/net_rtc_timer_ownership.json"
REPORT = ROOT / "recon/analysis/net_rtc_timer_atomic_adoption.md"
BASE = 0x01008000
ZEPHYR_COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"
ZEPHYR_TAG = "v3.4.99-ncs1-1"
SUPPORTED_RELOCATIONS = {2, 10, 30}

# This is the complete call/state closure needed to replace the previously
# retained compare_set reconstruction, plus the two already adopted public
# roots which prove the channel count and nRF53 pretick configuration.
SECTIONS = {
    "compare_int_lock": 0x01031248,
    "compare_int_unlock": 0x010312D0,
    "z_nrf_rtc_timer_read": 0x010313A8,
    "compare_set": 0x010313EC,
    "rtc_nrf_isr": 0x010315F0,
    "event_clear": 0x0103A6AE,
}

CALL_TARGETS = {
    "compare_int_lock": 0x01031248,
    "compare_int_unlock": 0x010312D0,
    "z_nrf_rtc_timer_read": 0x010313A8,
    "event_clear": 0x0103A6AE,
    "rtc_pretick_rtc1_isr_hook": 0x01039E4E,
}

STATE_TARGETS = {
    ".bss.cc_data": 0x21002B60,
    ".bss.anchor": 0x21002B88,
    ".bss.force_isr_mask": 0x21004964,
    ".bss.int_mask": 0x2100496C,
    ".bss.overflow_cnt": 0x21004970,
}

REQUIRED_CONFIG = {
    "CONFIG_NRF_RTC_TIMER": "y",
    "CONFIG_NRF_RTC_TIMER_LOCK_ZERO_LATENCY_IRQS": "y",
    "CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT": "1",
    "CONFIG_SOC_NRF53_RTC_PRETICK": "y",
    "CONFIG_SOC_NRF5340_CPUNET": "y",
    "CONFIG_TICKLESS_KERNEL": "y",
}

VERSION_CANDIDATES = (
    ("v2.4.0", "v3.3.99-ncs1"),
    ("v2.4.1", "v3.3.99-ncs1-1"),
    ("v2.5.0", "v3.4.99-ncs1"),
    ("v2.5.1", "v3.4.99-ncs1-1"),
    ("v2.5.2", "v3.4.99-ncs1-2"),
    ("v2.6.0", "v3.5.99-ncs1"),
    ("v2.6.1", "v3.5.99-ncs1-1"),
)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256(path: Path) -> str:
    return digest(path.read_bytes())


def config_values() -> dict[str, str]:
    values = {}
    for line in CONFIG.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            values[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            values[line[2:-11]] = "n"
    return values


def decode_thumb_call(raw: bytes, instruction_va: int) -> int:
    first, second = struct.unpack("<HH", raw)
    sign = (first >> 10) & 1
    j1 = (second >> 13) & 1
    j2 = (second >> 11) & 1
    i1 = (~(j1 ^ sign)) & 1
    i2 = (~(j2 ^ sign)) & 1
    immediate = ((sign << 24) | (i1 << 23) | (i2 << 22) |
                 ((first & 0x3FF) << 12) | ((second & 0x7FF) << 1))
    if sign:
        immediate -= 1 << 25
    return (instruction_va + 4 + immediate) & 0xFFFFFFFF


def relocation_symbol(elf: ELFFile, relocation) -> str:
    symbols = elf.get_section_by_name(".symtab")
    symbol = symbols.get_symbol(relocation["r_info_sym"])
    if symbol.name:
        return symbol.name
    index = symbol["st_shndx"]
    if isinstance(index, int):
        return elf.get_section(index).name
    raise ValueError("unnamed relocation target")


def git_blob(ref: str) -> str:
    return subprocess.check_output([
        "git", "-C", str(ZEPHYR), "rev-parse",
        f"{ref}:drivers/timer/nrf_rtc_timer.c",
    ], text=True).strip()


def version_matrix() -> list[dict]:
    rows = []
    pinned_blob = git_blob(ZEPHYR_TAG)
    for ncs_tag, zephyr_ref in VERSION_CANDIDATES:
        blob = git_blob(zephyr_ref)
        rows.append({
            "ncs_tag": ncs_tag,
            "zephyr_ref": zephyr_ref,
            "source_blob": blob,
            "same_source_as_pinned": blob == pinned_blob,
            "verdict": (
                "source_incompatible" if ncs_tag.startswith("v2.4.") else
                "body_compatible_not_patch_discriminating"
            ),
            "source_discriminators": (
                [
                    "lacks nRF53 RTC_PRETICK hook",
                    "lacks exact-alarm argument and -EINVAL paths",
                    "lacks z_nrf_rtc_timer_exact_set",
                ] if ncs_tag.startswith("v2.4.") else [
                    "no source delta from pinned nrf_rtc_timer.c",
                ]
            ),
        })
    if any(row["same_source_as_pinned"] for row in rows
           if row["ncs_tag"].startswith("v2.4.")):
        raise ValueError("NCS 2.4 RTC source unexpectedly matches pinned source")
    if any(not row["same_source_as_pinned"] for row in rows
           if row["ncs_tag"].startswith(("v2.5.", "v2.6."))):
        raise ValueError("neighboring 2.5/2.6 RTC source history drifted")
    return rows


def build() -> dict:
    config = config_values()
    if any(config.get(key, "n") != value
           for key, value in REQUIRED_CONFIG.items()):
        raise ValueError("configured CPUNET RTC discriminators drifted")

    firmware = IMAGE.read_bytes()
    matches = []
    call_checks = []
    state_checks = []
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        for symbol, va in SECTIONS.items():
            section_name = ".text." + symbol
            section = elf.get_section_by_name(section_name)
            if section is None:
                raise ValueError(f"missing configured section {section_name}")
            candidate = bytearray(section.data())
            original = bytearray(
                firmware[va - BASE:va - BASE + len(candidate)])
            reloc_section = elf.get_section_by_name(".rel" + section_name)
            relocations = []
            if reloc_section is not None:
                for relocation in reloc_section.iter_relocations():
                    offset = int(relocation["r_offset"])
                    kind = int(relocation["r_info_type"])
                    target = relocation_symbol(elf, relocation)
                    if kind not in SUPPORTED_RELOCATIONS:
                        raise ValueError(
                            f"unsupported relocation {kind} in {symbol}")
                    linked = bytes(original[offset:offset + 4])
                    row = {"offset": offset, "type": kind, "target": target}
                    if kind in (10, 30):
                        actual = decode_thumb_call(linked, va + offset)
                        expected = CALL_TARGETS.get(target)
                        if expected is None or actual != expected:
                            raise ValueError(
                                f"call target mismatch {symbol}+0x{offset:x} "
                                f"{target}: 0x{actual:08x} != {expected!r}")
                        row["runtime_target"] = f"0x{actual:08x}"
                        call_checks.append({"caller": symbol, **row})
                    else:
                        actual = struct.unpack("<I", linked)[0]
                        expected = STATE_TARGETS.get(target)
                        if expected is None or actual != expected:
                            raise ValueError(
                                f"state target mismatch {symbol}+0x{offset:x} "
                                f"{target}: 0x{actual:08x} != {expected!r}")
                        row["runtime_target"] = f"0x{actual:08x}"
                        state_checks.append({"caller": symbol, **row})
                    relocations.append(row)
                    candidate[offset:offset + 4] = b"\0" * 4
                    original[offset:offset + 4] = b"\0" * 4
            if candidate != original:
                mismatch = next(index for index, pair in
                                enumerate(zip(candidate, original))
                                if pair[0] != pair[1])
                raise ValueError(
                    f"non-relocation mismatch {symbol}+0x{mismatch:x}")
            matches.append({
                "symbol": symbol,
                "va": f"0x{va:08x}",
                "section": section_name,
                "size": len(candidate),
                "match": "relocation-masked-byte-exact",
                "normalized_sha256": digest(bytes(original)),
                "relocations": relocations,
            })

    sizes = {row["symbol"]: row["size"] for row in matches}
    if sizes != {
        "compare_int_lock": 0x40,
        "compare_int_unlock": 0x4C,
        "z_nrf_rtc_timer_read": 0x44,
        "compare_set": 0x124,
        "rtc_nrf_isr": 0xF4,
        "event_clear": 0x18,
    }:
        raise ValueError(f"configured RTC section sizes drifted: {sizes}")

    functions = []
    for symbol, va in SECTIONS.items():
        linkage = "global" if symbol in {
            "z_nrf_rtc_timer_read", "rtc_nrf_isr"
        } else "file_static"
        functions.append({
            "va": f"0x{va:08x}",
            "raw_symbol": f"FUN_{va:08x}",
            "upstream_symbol": symbol,
            "linkage": linkage,
            "abi": {
                "compare_int_lock": "static bool compare_int_lock(int32_t chan)",
                "compare_int_unlock": (
                    "static void compare_int_unlock(int32_t chan, bool key)"),
                "z_nrf_rtc_timer_read": "uint64_t z_nrf_rtc_timer_read(void)",
                "compare_set": (
                    "static int compare_set(int32_t, uint64_t, handler, "
                    "void *, bool)"),
                "rtc_nrf_isr": "void rtc_nrf_isr(const void *arg)",
                "event_clear": "static void event_clear(int32_t chan)",
            }[symbol],
            "firmware_size": sizes[symbol],
            "reference_size": sizes[symbol],
            "match": "relocation-masked-byte-exact",
            "match_score": 1.0,
            "exclude_reconstruction": True,
            "evidence": (
                "Complete configured ELF section is exact after masking only "
                "verified call/state relocations."
            ),
        })

    declared_size = 0x100
    compare_va = SECTIONS["compare_set"]
    compare_size = sizes["compare_set"]
    omitted_tail = firmware[
        compare_va - BASE + declared_size:
        compare_va - BASE + compare_size
    ]
    compare_match = next(row for row in matches
                         if row["symbol"] == "compare_set")
    omitted_relocations = [
        row for row in compare_match["relocations"]
        if row["offset"] >= declared_size
    ]
    if [row["offset"] for row in omitted_relocations] != [0x114, 0x120]:
        raise ValueError("compare_set omitted-tail relocation closure drifted")
    compare_bytes = firmware[
        compare_va - BASE:compare_va - BASE + compare_size
    ]
    constants = {
        "COUNTER_HALF_SPAN_plus_one": struct.unpack_from(
            "<I", compare_bytes, 0x110)[0],
        "RTC1_register_base": struct.unpack_from(
            "<I", compare_bytes, 0x118)[0],
        "COUNTER_HALF_SPAN_minus_MIN_CYCLES": struct.unpack_from(
            "<I", compare_bytes, 0x11C)[0],
    }
    if constants != {
        "COUNTER_HALF_SPAN_plus_one": 0x00800001,
        "RTC1_register_base": 0x41016000,
        "COUNTER_HALF_SPAN_minus_MIN_CYCLES": 0x007FFFFD,
    }:
        raise ValueError(f"compare_set constants drifted: {constants}")

    return {
        "schema": 2,
        "core": "net",
        "component": "zephyr_nrf_rtc_timer",
        "status": "authorized_atomic_compare_closure",
        "safe": True,
        "upstream": {
            "repository": str(ZEPHYR),
            "commit": ZEPHYR_COMMIT,
            "tag": ZEPHYR_TAG,
            "source": "drivers/timer/nrf_rtc_timer.c",
            "source_sha256": sha256(SOURCE),
            "object": str(OBJECT),
            "object_sha256": sha256(OBJECT),
            "configured_build": str(BUILD),
            "configured_build_sha256": sha256(CONFIG),
            "abi": "Cortex-M33, Thumb-2, soft-float, -Os",
        },
        "required_config": REQUIRED_CONFIG,
        "derived_config": {
            "RTC_PRETICK": True,
            "CHAN_COUNT": 2,
            "cc_data_stride": 16,
        },
        "binary_discriminators": {
            "compare_set_constants": {
                key: f"0x{value:08x}" for key, value in constants.items()
            },
            "cc_data_layout": {
                "callback_offset": 0,
                "user_context_offset": 4,
                "target_time_low_offset": 8,
                "target_time_high_offset": 12,
                "stride": 16,
            },
            "resolved_call_targets": CALL_TARGETS,
            "resolved_state_targets": STATE_TARGETS,
        },
        "version_precision": {
            "candidate_matrix": version_matrix(),
            "strongest_local_boundary": (
                "NCS 2.4 is excluded by the pre-tick/exact-alarm source and "
                "control-flow changes. This source unit is unchanged across "
                "NCS 2.5.x and 2.6.x, so it does not independently distinguish "
                "those tags; the exact v2.5.1 commit remains manifest-pinned."
            ),
        },
        "policy": {
            "adoption_unit": "complete_compare_set_call_and_state_closure",
            "ghidra_declared_size_authoritative": False,
            "sdc_policy": "report_only_unchanged",
        },
        "extent_correction": {
            "va": "0x010313ec",
            "symbol": "compare_set",
            "ghidra_declared_size": declared_size,
            "true_elf_section_size": compare_size,
            "omitted_tail_size": len(omitted_tail),
            "omitted_tail_hex": omitted_tail.hex(),
            "omitted_tail_sha256": digest(omitted_tail),
            "omitted_tail_relocations": omitted_relocations,
            "omitted_live_operations": [
                "cc_data slot address calculation at compare_set+0x100",
                "zero success result at compare_set+0x104",
                "target_time store at compare_set+0x106",
                "user_context store at compare_set+0x10a",
                "branch to compare_int_unlock at compare_set+0x10c",
            ],
            "old_harness_blind_spot": (
                "The retained C treated the RTC 0x41016504 event register as "
                "unmapped/zero and deleted the live event-check and retry "
                "branch. Random parity could not observe that MMIO arm; full "
                "configured-section comparison is authoritative here."
            ),
        },
        "functions": functions,
        "section_matches": matches,
        "call_target_checks": call_checks,
        "state_target_checks": state_checks,
    }


def write_report(data: dict) -> None:
    rows = data["section_matches"]
    lines = [
        "# CPUNET Nordic RTC timer atomic adoption", "",
        "The pinned Zephyr `v3.4.99-ncs1-1` object is relocation-masked "
        "byte-exact for the complete `compare_set` call/state closure. The "
        "firmware function at `0x010313ec` is **0x124 bytes**, not Ghidra's "
        "0x100-byte declaration; the omitted tail contains live state stores "
        "and literal relocations. The old parity candidate also treated the "
        "RTC event register at `0x41016504` as permanently unmapped/zero and "
        "therefore deleted a live retry arm; the complete stock-section proof "
        "supersedes that blind spot.", "",
        "| function | firmware VA | bytes |", "|---|---:|---:|",
    ]
    for row in rows:
        lines.append(
            f"| `{row['symbol']}` | `{row['va']}` | {row['size']} |")
    lines += [
        "", data["version_precision"]["strongest_local_boundary"], "",
        "The exact config is `CONFIG_NRF_RTC_TIMER_USER_CHAN_COUNT=1`, "
        "`CONFIG_NRF_RTC_TIMER_LOCK_ZERO_LATENCY_IRQS=y`, "
        "`CONFIG_SOC_NRF53_RTC_PRETICK=y`, and `CONFIG_TICKLESS_KERNEL=y`. "
        "Private SDC ownership is unchanged and remains report-only.", "",
    ]
    REPORT.write_text("\n".join(lines))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    encoded = json.dumps(data, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.is_file() or OUTPUT.read_text() != encoded:
            raise SystemExit("stale CPUNET RTC timer adoption receipt")
    else:
        OUTPUT.write_text(encoded)
        write_report(data)
    print("CPUNET RTC timer: 6-section compare closure exact")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
