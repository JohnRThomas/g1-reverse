#!/usr/bin/env python3
"""Prove the CPUNET scheduler/queue/heap stock source-unit closure.

The retained per-function reconstructions expose names for compiler-private
helpers (spin_lock, update_cache, queue_insert, alloc_chunk, ...).  Those names
are not linkable APIs: they are local/inlined implementation details.  This
receipt proves the complete configured stock owners that contain them before
the reconstructed copies are removed from the cohesive build.
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
BUILD = Path("/private/tmp/g1-net-heap-auto-0718")
WRONG_HEAP_BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_kernel_private_stock_adoption.json"
REPORT = ROOT / "recon/analysis/net_kernel_private_stock_adoption.md"
BASE = 0x01008000
COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"
SUPPORTED_RELOCATIONS = {2, 10, 30}


UNITS = {
    "sched": {
        "source": "zephyr/kernel/sched.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/sched.c.obj",
        "sections": {
            "sliceable": 0x01036E90, "slice_timeout": 0x01036ECC,
            "z_sched_prio_cmp": 0x0103B28A,
            "z_reset_time_slice": 0x01036F24,
            "update_cache": 0x01036F74, "ready_thread": 0x01036FCC,
            "z_ready_thread": 0x0103705C,
            "z_unpend_thread_no_timeout": 0x010370C4,
            "z_reschedule": 0x01037130, "z_sched_start": 0x0103719C,
            "z_reschedule_irqlock": 0x0103B29C,
            "z_reschedule_unlocked": 0x0103B2B4,
            "k_sched_lock": 0x0103721C, "k_sched_unlock": 0x010372B4,
            "z_priq_dumb_remove": 0x0103735C,
            "move_thread_to_end_of_prio_q": 0x01037398,
            "z_time_slice": 0x01037438, "unready_thread": 0x010374DC,
            "add_to_waitq_locked": 0x01037514,
            "pend_locked": 0x01037588, "z_pend_curr": 0x010375B8,
            "z_set_prio": 0x01037670,
            "z_impl_k_thread_suspend": 0x01037768,
            "unpend_thread_no_timeout": 0x01037814,
            "z_unpend_thread": 0x01037850,
            "z_thread_timeout": 0x0103B2C8,
            "z_unpend1_no_timeout": 0x01037960,
            "z_unpend_first_thread": 0x010379D4,
            "z_unpend_all": 0x0103B2D0, "z_sched_init": 0x01037A50,
            "z_impl_k_yield": 0x01037A60, "z_tick_sleep": 0x01037B5C,
            "z_impl_k_sleep": 0x01037C64,
            "z_impl_z_current_get": 0x01037CBC,
            "z_thread_abort": 0x01037CC8,
            "z_sched_wake": 0x01037E10, "z_sched_wait": 0x01037EA8,
        },
    },
    "queue": {
        "source": "zephyr/kernel/queue.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/queue.c.obj",
        "sections": {
            "queue_insert": 0x01036660,
            "z_impl_k_queue_get": 0x01036774,
            "z_queue_node_peek": 0x0103B1E2,
            "k_queue_append": 0x0103B1FA,
            "k_queue_prepend": 0x0103B210,
        },
    },
    "kheap": {
        "source": "zephyr/kernel/kheap.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/kheap.c.obj",
        "sections": {
            "statics_init": 0x01035CD8,
            "k_heap_aligned_alloc": 0x01035D18,
            "k_heap_free": 0x01035E1C, "k_heap_init": 0x0103B10E,
        },
    },
    "mempool": {
        "source": "zephyr/kernel/mempool.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/mempool.c.obj",
        "sections": {
            "z_heap_aligned_alloc": 0x01038958,
            "k_aligned_alloc": 0x010389A0,
            "k_thread_system_pool_assign": 0x010389EC,
            "z_thread_aligned_alloc": 0x010389F8,
            "k_free": 0x0103B522, "k_malloc": 0x0103B530,
        },
    },
    "heap": {
        "source": "zephyr/lib/os/heap.c",
        "object": "zephyr/CMakeFiles/zephyr.dir/lib/os/heap.c.obj",
        "sections": {
            "chunk_field": 0x0103973C, "chunk_set": 0x01039752,
            "chunk_size": 0x01039768, "set_chunk_used": 0x01039774,
            "set_chunk_size": 0x010397A4,
            "mem_to_chunkid": 0x010397AC,
            "bytes_to_chunksz.isra.0": 0x010397C0,
            "bucket_idx.isra.0": 0x010397D2,
            "free_list_remove_bidx": 0x010397EA,
            "free_list_remove": 0x01039846, "alloc_chunk": 0x01039874,
            "split_chunks": 0x010398E8, "merge_chunks": 0x01039936,
            "free_list_add": 0x01039972, "free_chunk": 0x010399F6,
            "sys_heap_free": 0x0102C470,
            "sys_heap_aligned_alloc": 0x0102C4E4,
            "sys_heap_init": 0x0102C5EC,
            "sys_heap_alloc": 0x01039A7A,
        },
    },
}


CALL_TARGETS = {
    "add_to_waitq_locked": 0x01037514, "alloc_chunk": 0x01039874,
    "arch_swap": 0x0102EC10, "assert_post_action": 0x01039BB0,
    "assert_print": 0x01039BBE, "bucket_idx.isra.0": 0x010397D2,
    "bytes_to_chunksz.isra.0": 0x010397C0,
    "chunk_field": 0x0103973C, "chunk_set": 0x01039752,
    "chunk_size": 0x01039768, "free_chunk": 0x010399F6,
    "free_list_add": 0x01039972, "free_list_remove": 0x01039846,
    "free_list_remove_bidx": 0x010397EA, "k_aligned_alloc": 0x010389A0,
    "k_free": 0x0103B522, "k_heap_aligned_alloc": 0x01035D18,
    "k_heap_free": 0x01035E1C, "k_heap_init": 0x0103B10E,
    "k_is_in_isr": 0x0103B14A, "k_malloc": 0x0103B530,
    "mem_to_chunkid": 0x010397AC, "memset": 0x0103B62E,
    "merge_chunks": 0x01039936,
    "move_thread_to_end_of_prio_q": 0x01037398,
    "pend_locked": 0x01037588, "queue_insert": 0x01036660,
    "ready_thread": 0x01036FCC, "set_chunk_size": 0x010397A4,
    "set_chunk_used": 0x01039774, "sliceable": 0x01036E90,
    "split_chunks": 0x010398E8,
    "sys_clock_tick_get_32": 0x0103B2F8,
    "sys_heap_aligned_alloc": 0x0102C4E4,
    "sys_heap_alloc": 0x01039A7A, "sys_heap_free": 0x0102C470,
    "sys_heap_init": 0x0102C5EC, "sys_timepoint_calc": 0x0103B304,
    "sys_timepoint_timeout": 0x0103B34C,
    "unpend_thread_no_timeout": 0x01037814,
    "unready_thread": 0x010374DC, "update_cache": 0x01036F74,
    "z_abort_timeout": 0x010380D8, "z_add_timeout": 0x01037F8C,
    "z_handle_obj_poll_events": 0x0103B4F6,
    "z_heap_aligned_alloc": 0x01038958,
    "z_impl_k_thread_suspend": 0x01037768,
    "z_impl_k_yield": 0x01037A60, "z_pend_curr": 0x010375B8,
    "z_priq_dumb_remove": 0x0103735C,
    "z_queue_node_peek": 0x0103B1E2, "z_ready_thread": 0x0103705C,
    "z_reschedule": 0x01037130, "z_reschedule_irqlock": 0x0103B29C,
    "z_reschedule_unlocked": 0x0103B2B4,
    "z_reset_time_slice": 0x01036F24,
    "z_sched_wake_thread": 0x010378C4, "z_set_prio": 0x01037670,
    "z_spin_lock_set_owner": 0x01036144,
    "z_spin_lock_valid": 0x0103610C,
    "z_spin_unlock_valid": 0x01036128,
    "z_thread_aligned_alloc": 0x010389F8,
    "z_tick_sleep": 0x01037B5C, "z_unpend_all": 0x0103B2D0,
    "z_unpend_first_thread": 0x010379D4,
    "z_unpend_thread": 0x01037850,
}


PRIVATE_STATE = {
    ("sched", ".bss.pending_current"): (0x21004B5C, 4),
    ("sched", ".bss.slice_expired"): (0x21006462, 1),
    ("sched", ".bss.slice_timeouts"): (0x210044D8, 24),
    ("sched", ".bss.slice_max_prio"): (0x21004B60, 4),
    ("sched", ".bss.slice_ticks"): (0x21004B64, 4),
    ("sched", "sched_spinlock"): (0x21004B68, 4),
}
STRUCTURAL_ABSOLUTES = {
    ("kheap", "_k_heap_list_start"): {0x210008B4},
    ("kheap", "_k_heap_list_end"): {0x210008CC},
    ("mempool", "_system_heap"): {0x210008B4},
}
STATIC_SYMBOLS = {
    "sliceable", "slice_timeout", "update_cache", "ready_thread",
    "z_reschedule_unlocked", "z_priq_dumb_remove",
    "move_thread_to_end_of_prio_q", "unready_thread",
    "add_to_waitq_locked", "pend_locked", "unpend_thread_no_timeout",
    "queue_insert", "statics_init", "z_heap_aligned_alloc",
    "chunk_field", "chunk_set", "chunk_size", "set_chunk_used",
    "set_chunk_size", "mem_to_chunkid", "bytes_to_chunksz.isra.0",
    "bucket_idx.isra.0", "free_list_remove_bidx", "free_list_remove",
    "alloc_chunk", "split_chunks", "merge_chunks", "free_list_add",
    "free_chunk",
}


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256(path: Path) -> str:
    return digest(path.read_bytes())


def config_values(path: Path = CONFIG) -> dict[str, str]:
    result = {}
    for line in path.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            result[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            result[line[2:-11]] = "n"
    return result


def decode_thumb_call(raw: bytes, instruction_va: int) -> int:
    first, second = struct.unpack("<HH", raw)
    sign = (first >> 10) & 1
    j1, j2 = (second >> 13) & 1, (second >> 11) & 1
    i1, i2 = (~(j1 ^ sign)) & 1, (~(j2 ^ sign)) & 1
    immediate = ((sign << 24) | (i1 << 23) | (i2 << 22) |
                 ((first & 0x3FF) << 12) | ((second & 0x7FF) << 1))
    if sign:
        immediate -= 1 << 25
    return (instruction_va + 4 + immediate) & 0xFFFFFFFF


def relocation_symbol(elf: ELFFile, relocation) -> str:
    symbol = elf.get_section_by_name(".symtab").get_symbol(
        relocation["r_info_sym"])
    if symbol.name:
        return symbol.name
    return elf.get_section(symbol["st_shndx"]).name


def git_blob(tag: str, source: str) -> str:
    relative = source.removeprefix("zephyr/")
    return subprocess.check_output(
        ["git", "-C", str(ZEPHYR), "rev-parse", f"{tag}:{relative}"],
        text=True).strip()


def wrong_heap_config_rejection(firmware: bytes) -> dict:
    path = WRONG_HEAP_BUILD / UNITS["heap"]["object"]
    exact = []
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        for symbol, va in UNITS["heap"]["sections"].items():
            section = elf.get_section_by_name(".text." + symbol)
            if section is None:
                continue
            candidate = bytearray(section.data())
            original = bytearray(firmware[va - BASE:va - BASE + len(candidate)])
            reloc = elf.get_section_by_name(".rel.text." + symbol)
            for row in (() if reloc is None else reloc.iter_relocations()):
                offset = int(row["r_offset"])
                candidate[offset:offset + 4] = b"\0" * 4
                original[offset:offset + 4] = b"\0" * 4
            if candidate == original:
                exact.append(symbol)
    return {
        "rejected_config": {"CONFIG_SYS_HEAP_SMALL_ONLY": "y",
                            "CONFIG_SYS_HEAP_AUTO": "n"},
        "tested_object": str(path), "tested_object_sha256": sha256(path),
        "selected_heap_sections": len(UNITS["heap"]["sections"]),
        "exact_sections": exact,
        "reason": "constant-folded small-only headers remove firmware branches",
    }


def build() -> dict:
    required = {
        "CONFIG_SPIN_VALIDATE": "y", "CONFIG_SMP": "n",
        "CONFIG_SCHED_DUMB": "y", "CONFIG_SYS_HEAP_AUTO": "y",
        "CONFIG_SYS_HEAP_SMALL_ONLY": "n", "CONFIG_SYS_HEAP_BIG_ONLY": "n",
        "CONFIG_SYS_HEAP_ALLOC_LOOPS": "3", "CONFIG_ASSERT": "y",
        "CONFIG_ASSERT_NO_COND_INFO": "y", "CONFIG_ASSERT_NO_MSG_INFO": "y",
    }
    config = config_values()
    if any(config.get(key, "n") != value for key, value in required.items()):
        raise ValueError("CPUNET kernel-private configuration drifted")

    firmware = IMAGE.read_bytes()
    section_matches, call_checks, absolute_observed = [], [], {}
    source_units, manifest_functions = [], []
    for unit, definition in UNITS.items():
        source = NCS / definition["source"]
        obj = BUILD / definition["object"]
        source_units.append({
            "unit": unit, "source": definition["source"],
            "source_sha256": sha256(source), "object": definition["object"],
            "object_sha256": sha256(obj),
            "live_section_count": len(definition["sections"]),
        })
        with obj.open("rb") as stream:
            elf = ELFFile(stream)
            for symbol, va in definition["sections"].items():
                name = ".text." + symbol
                section = elf.get_section_by_name(name)
                if section is None:
                    raise ValueError(f"missing configured section {unit}:{symbol}")
                candidate = bytearray(section.data())
                original = bytearray(firmware[va - BASE:va - BASE + len(candidate)])
                reloc = elf.get_section_by_name(".rel" + name)
                relocations = []
                if reloc is not None:
                    for row in reloc.iter_relocations():
                        offset, kind = int(row["r_offset"]), int(row["r_info_type"])
                        if kind not in SUPPORTED_RELOCATIONS:
                            raise ValueError(f"unsupported relocation {kind}")
                        target = relocation_symbol(elf, row)
                        linked = bytes(original[offset:offset + 4])
                        relocations.append({"offset": offset, "type": kind,
                                            "target": target})
                        if kind in (10, 30):
                            actual = decode_thumb_call(linked, va + offset)
                            if CALL_TARGETS.get(target) != actual:
                                raise ValueError(
                                    f"call closure mismatch {symbol}+0x{offset:x} "
                                    f"{target}: 0x{actual:08x}")
                            call_checks.append({
                                "unit": unit, "caller": symbol,
                                "caller_va": f"0x{va:08x}", "offset": offset,
                                "target_symbol": target,
                                "target_va": f"0x{actual:08x}",
                            })
                        else:
                            actual = struct.unpack("<I", linked)[0]
                            absolute_observed.setdefault((unit, target), []).append(
                                (symbol, offset, actual))
                        candidate[offset:offset + 4] = b"\0" * 4
                        original[offset:offset + 4] = b"\0" * 4
                if candidate != original:
                    mismatch = next(i for i, pair in enumerate(zip(candidate, original))
                                    if pair[0] != pair[1])
                    raise ValueError(f"non-relocation mismatch {symbol}+0x{mismatch:x}")
                section_matches.append({
                    "unit": unit, "symbol": symbol, "va": f"0x{va:08x}",
                    "size": len(candidate), "section": name,
                    "match": "relocation-masked-byte-exact",
                    "normalized_sha256": digest(bytes(original)),
                    "relocations": relocations,
                })
                raw = f"FUN_{va:08x}"
                recon = ROOT / "recon/net/src" / (raw + ".c")
                row = {
                    "va": f"0x{va:08x}", "raw_symbol": raw,
                    "upstream_symbol": symbol,
                    "durable_symbol": symbol.replace(".", "_"),
                    "upstream_source": definition["source"],
                    "upstream_linkage": ("file_static" if symbol in STATIC_SYMBOLS
                                         else "public"),
                    "whole_source_unit_selected": True,
                    "call_targets_checked": True, "safe_to_adopt": True,
                    "exclude_reconstruction": True,
                    "reconstruction_present": recon.is_file(),
                }
                if recon.is_file():
                    row["reconstruction_source"] = str(recon.relative_to(ROOT))
                    row["reconstruction_source_sha256"] = sha256(recon)
                manifest_functions.append(row)

    state_rows = []
    for key, (address, size) in PRIVATE_STATE.items():
        observed = absolute_observed.get(key, [])
        if not observed or {row[2] for row in observed} != {address}:
            raise ValueError(f"private-state closure mismatch: {key}")
        state_rows.append({
            "unit": key[0], "target": key[1], "size": size,
            "runtime_address": f"0x{address:08x}",
            "initialization": "zero_initialized",
            "relocation_references": [
                {"symbol": symbol, "offset": offset}
                for symbol, offset, _ in sorted(observed)
            ],
        })
    structural_rows = []
    for key, addresses in STRUCTURAL_ABSOLUTES.items():
        observed = absolute_observed.get(key, [])
        if not observed or {row[2] for row in observed} != addresses:
            raise ValueError(f"structural absolute mismatch: {key}")
        structural_rows.append({
            "unit": key[0], "target": key[1],
            "runtime_addresses": [f"0x{x:08x}" for x in sorted(addresses)],
        })

    expected_count = sum(len(row["sections"]) for row in UNITS.values())
    if len(section_matches) != expected_count:
        raise ValueError("incomplete kernel-private section closure")
    wrong_config = wrong_heap_config_rejection(firmware)
    if wrong_config["exact_sections"]:
        raise ValueError("SMALL_ONLY unexpectedly matched AUTO heap closure")

    tags = ["v3.3.99-ncs1-3", "v3.4.99-ncs1-1-rc1",
            "v3.4.99-ncs1-1", "v3.4.99-ncs1-2",
            "v3.4.99-ncs1-3", "v3.5.99-ncs1-1"]
    history = {
        tag: {unit: git_blob(tag, definition["source"])
              for unit, definition in UNITS.items()}
        for tag in tags
    }
    return {
        "schema": 1, "core": "net",
        "component": "zephyr_kernel_private_stock",
        "status": "authorized_atomic", "safe": True,
        "policy": {
            "adoption_unit": "five_complete_configured_source_units",
            "proof": "relocation-masked bytes plus every Thumb call target",
            "private_state_is_atomic": True,
            "raw_address_backmaps_required": True,
            "sdc_policy": "report_only_unchanged",
        },
        "upstream": {
            "repository": "zephyr", "commit": COMMIT,
            "manifest_tag": "v3.4.99-ncs1-1",
            "configured_build": str(BUILD),
            "configured_build_sha256": sha256(CONFIG),
            "required_config": required,
            "abi": "Cortex-M33+nodsp, Thumb-2, soft-float, GCC 12.2, -Os",
        },
        "version_precision": {
            "source_blob_ids_by_tag": history,
            "conclusion": (
                "the five-source closure excludes adjacent 3.3/3.5 families; "
                "the identical 3.4.99-ncs1 patch-tag sources cannot distinguish "
                "-1 from -2/-3, so the manifest pin supplies exact patch provenance"),
        },
        "wrong_config_rejection": wrong_config,
        "source_units": source_units, "section_matches": section_matches,
        "call_target_checks": call_checks,
        "private_state_sections": state_rows,
        "structural_absolute_targets": structural_rows,
        "manifest_functions": manifest_functions,
        "atomic_group": [row["va"] for row in manifest_functions],
        "recovered_atomic_group": sorted(
            row["va"] for row in manifest_functions
            if row["reconstruction_present"]),
    }


def write_report(data: dict) -> None:
    lines = [
        "# CPUNET scheduler/queue/heap stock closure", "",
        "The pinned Zephyr `83980fe` objects built with GCC 12.2/`-Os`, "
        "`CONFIG_SPIN_VALIDATE=y`, `CONFIG_SMP=n`, `CONFIG_SCHED_DUMB=y`, "
        "and `CONFIG_SYS_HEAP_AUTO=y` reproduce every selected firmware "
        "section after masking only relocation words. Every Thumb relocation "
        "is also resolved to its exact firmware target.", "",
        "| source unit | exact live sections |", "|---|---:|",
    ]
    for row in data["source_units"]:
        lines.append(f"| `{row['source']}` | {row['live_section_count']} |")
    lines += [
        "", "The default `CONFIG_SYS_HEAP_SMALL_ONLY=y` build was tested and "
        "matched zero of the 19 selected heap sections. AUTO preserves the "
        "runtime small/big header branch visible in the firmware.", "",
        "The source history excludes adjacent Zephyr 3.3/3.5 scheduler/kernel "
        "families. The 3.4.99-ncs1 patch tags contain identical copies of these "
        "sources, so exact `-1` provenance comes from the west manifest rather "
        "than an impossible body-only distinction. SDC remains report-only.", "",
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
            raise SystemExit("stale CPUNET kernel-private stock receipt")
    else:
        OUTPUT.write_text(encoded)
        write_report(data)
    print("CPUNET kernel-private stock: 71 sections, 6 private states exact")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
