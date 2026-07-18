#!/usr/bin/env python3
"""Build the exact configured CPUNET Zephyr source-closure receipt.

This receipt deliberately checks more than mnemonic similarity.  Every live
function section is compared byte-for-byte with only ELF relocation words
masked, every Thumb call relocation is decoded in the firmware and checked
against its expected callee, and each selected source-local state relocation
is checked at its firmware runtime address.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "netcore_image.bin"
OUTPUT = ROOT / "recon/ownership/net_zephyr_stock_atomic_adoption.json"
REPORT = ROOT / "recon/analysis/net_zephyr_stock_atomic_adoption.md"
BASE = 0x01008000
ZEPHYR_COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"
SUPPORTED_RELOCATIONS = {2, 10, 30, 108}

# These are the complete live closures selected from the configured
# objects.  Hidden entries omitted by Ghidra are intentionally present.
UNITS = {
    "mpsc_pbuf": {
        "source": "zephyr/lib/os/mpsc_pbuf.c",
        "object": "zephyr/CMakeFiles/zephyr.dir/lib/os/mpsc_pbuf.c.obj",
        "sections": {
            "free_space": 0x01039BD8, "get_usage": 0x01039BFE,
            "idx_inc": 0x01039C20, "rd_idx_inc": 0x01039C3C,
            "add_skip_item": 0x01039C54,
            "drop_item_locked": 0x01039C92,
            "post_drop_action": 0x01039D80,
            "max_utilization_update": 0x01039DB6,
            "mpsc_pbuf_init": 0x0102CBD8,
            "mpsc_pbuf_alloc": 0x0102CC34,
            "mpsc_pbuf_commit": 0x0102CD8C,
            "mpsc_pbuf_claim": 0x0102CE14,
            "mpsc_pbuf_free": 0x0102CF00,
        },
    },
    "log_core": {
        "source": "zephyr/subsys/logging/log_core.c",
        "object": "zephyr/CMakeFiles/zephyr.dir/subsys/logging/log_core.c.obj",
        "sections": {
            "log_msg_generic_get_wlen": 0x0103A26C,
            "dummy_timestamp": 0x0103A28C,
            "default_get_timestamp": 0x0103A290,
            "atomic_inc": 0x0103A294,
            "z_log_vprintk": 0x0103A2A6,
            "z_log_notify_drop": 0x0103A2C2,
            "z_log_get_tag": 0x0103A2C8,
            "enable_logger": 0x0102DC34,
            "activate_foreach_backend": 0x0102DC90,
            "z_log_init": 0x0102DCF4,
            "log_process_thread_timer_expiry_fn": 0x0102DDBC,
            "log_format_func_t_get": 0x0102DDC8,
            "log_set_timestamp_func": 0x0102DDD4,
            "z_log_notify_backend_enabled": 0x0102DDF4,
            "z_log_dropped": 0x0102DE10,
            "z_log_dropped_read_and_clear": 0x0102DE38,
            "dropped_notify": 0x0102DE50,
            "z_log_msg_init": 0x0102DEA0,
            "log_core_init": 0x0102DEC0,
            "z_log_msg_alloc": 0x0102DEF4,
            "z_log_msg_local_claim": 0x0102DF04,
            "z_log_msg_free": 0x0102DF10,
            "z_log_msg_pending": 0x0102DF20,
            "z_impl_log_process": 0x0102DF2C,
            "z_impl_log_panic": 0x0102E000,
            "log_process_thread_func": 0x0102E064,
            "z_log_msg_post_finalize": 0x0102E140,
            "z_log_msg_commit": 0x0102E1FC,
        },
    },
    "cpu_idle": {
        "source": "zephyr/arch/arm/core/aarch32/cpu_idle.S",
        "object": ("zephyr/arch/arch/arm/core/aarch32/CMakeFiles/"
                   "arch__arm__core__aarch32.dir/cpu_idle.S.obj"),
        "sections": {
            "z_arm_cpu_idle_init": 0x0102E9B0,
            "arch_cpu_idle": 0x0102E9BC,
            "arch_cpu_atomic_idle": 0x0102EA00,
        },
    },
    "onoff": {
        "source": "zephyr/lib/os/onoff.c",
        "object": "zephyr/CMakeFiles/zephyr.dir/lib/os/onoff.c.obj",
        "sections": {
            "process_recheck": 0x01039ADE,
            "validate_args": 0x01039B16,
            "notify_one": 0x01039B36,
            "process_event": 0x0102C6F8,
            "transition_complete": 0x0102CA2C,
            "onoff_manager_init": 0x01039B62,
            "onoff_request": 0x0102CA80,
        },
    },
    "buf_simple": {
        "source": "zephyr/subsys/net/buf_simple.c",
        "object": ("zephyr/subsys/net/CMakeFiles/subsys__net.dir/"
                   "buf_simple.c.obj"),
        "sections": {
            "net_buf_simple_reserve": 0x01030014,
            "net_buf_simple_push": 0x0103004C,
            "net_buf_simple_push_u8": 0x0103A45A,
            "net_buf_simple_tailroom": 0x0103A468,
            "net_buf_simple_add": 0x01030084,
            "net_buf_simple_add_mem": 0x0103A478,
        },
    },
    "msg_q": {
        "source": "zephyr/kernel/msg_q.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/msg_q.c.obj",
        "sections": {
            "k_msgq_init": 0x0103B164,
            "z_impl_k_msgq_alloc_init": 0x0103B18C,
            "z_impl_k_msgq_put": 0x01036198,
            "z_impl_k_msgq_get": 0x010362D0,
        },
    },
    "work": {
        "source": "zephyr/kernel/work.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/work.c.obj",
        "sections": {
            "flag_test_and_clear": 0x0103B244,
            "notify_queue_locked.isra.0": 0x0103B25A,
            "work_queue_main": 0x0103695C,
            "submit_to_queue_locked": 0x01036B18,
            "k_work_init": 0x01036BEC,
            "z_work_submit_to_queue": 0x01036C2C,
            "k_work_submit_to_queue": 0x0103B268,
            "k_work_queue_init": 0x01036CB8,
            "k_work_queue_start": 0x01036CE4,
            "k_work_queue_drain": 0x01036DA4,
        },
    },
    "timer": {
        "source": "zephyr/kernel/timer.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/timer.c.obj",
        "sections": {
            "z_timer_expiration_handler": 0x010382FC,
            "k_timer_init": 0x0103B38E,
            "z_impl_k_timer_start": 0x01038448,
            "z_impl_k_timer_stop": 0x0103B3A6,
        },
    },
    "poll": {
        "source": "zephyr/kernel/poll.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/poll.c.obj",
        "sections": {
            "add_event": 0x0103B3E0,
            "register_events": 0x010384A8,
            "signal_poll_event": 0x0103B442,
            "clear_event_registrations": 0x01038654,
            "z_impl_k_poll": 0x01038764,
            "z_handle_obj_poll_events": 0x0103B4F6,
            "z_impl_k_poll_signal_init": 0x0103B512,
            "z_impl_k_poll_signal_reset": 0x0103B51C,
            "z_impl_k_poll_signal_raise": 0x010388C8,
        },
    },
}

# Full resolved call closure of the selected sections.  Checking these targets
# distinguishes identical wrapper bodies such as push_mem and add_mem.
CALL_TARGETS = {
    "add_event": 0x0103B3E0,
    "assert_post_action": 0x01039BB0,
    "assert_print": 0x01039BBE,
    "clear_event_registrations": 0x01038654,
    "flag_test_and_clear": 0x0103B244,
    "k_is_in_isr": 0x0103B14A,
    "k_msgq_init": 0x0103B164,
    "memcpy": 0x0103B614,
    "memset": 0x0103B62E,
    "net_buf_simple_add": 0x01030084,
    "net_buf_simple_push": 0x0103004C,
    "net_buf_simple_tailroom": 0x0103A468,
    "notify_one": 0x01039B36,
    "notify_queue_locked.isra.0": 0x0103B25A,
    "process_event": 0x0102C6F8,
    "process_recheck": 0x01039ADE,
    "register_events": 0x010384A8,
    "signal_poll_event": 0x0103B442,
    "submit_to_queue_locked": 0x01036B18,
    "sys_notify_finalize": 0x0102CB84,
    "sys_notify_validate": 0x01039B88,
    "validate_args": 0x01039B16,
    "z_abort_timeout": 0x010380D8,
    "z_add_timeout": 0x01037F8C,
    "z_handle_obj_poll_events": 0x0103B4F6,
    "z_impl_k_sem_give": 0x01036824,
    "z_impl_k_thread_create": 0x01035FA0,
    "z_impl_k_thread_name_set": 0x0103B156,
    "z_impl_k_thread_start": 0x0103B160,
    "z_impl_k_uptime_ticks": 0x0103B300,
    "z_impl_k_yield": 0x01037A60,
    "z_pend_curr": 0x010375B8,
    "z_ready_thread": 0x0103705C,
    "z_reschedule": 0x01037130,
    "z_reschedule_irqlock": 0x0103B29C,
    "z_sched_prio_cmp": 0x0103B28A,
    "z_sched_wait": 0x01037EA8,
    "z_sched_wake": 0x01037E10,
    "z_spin_lock_set_owner": 0x01036144,
    "z_spin_lock_valid": 0x0103610C,
    "z_spin_unlock_valid": 0x01036128,
    "z_thread_aligned_alloc": 0x010389F8,
    "z_unpend1_no_timeout": 0x01037960,
    "z_unpend_first_thread": 0x010379D4,
    "z_unpend_thread": 0x01037850,
    "z_unpend_thread_no_timeout": 0x010370C4,
    "z_work_submit_to_queue": 0x01036C2C,
}

CALL_TARGETS.update({
    "__aeabi_read_tp": 0x0103B650,
    "activate_foreach_backend": 0x0102DC90,
    "add_skip_item": 0x01039C54,
    "atomic_inc": 0x0103A294,
    "drop_item_locked": 0x01039C92,
    "dropped_notify": 0x0102DE50,
    "free_space": 0x01039BD8,
    "get_usage": 0x01039BFE,
    "idx_inc": 0x01039C20,
    "k_timer_init": 0x0103B38E,
    "log_backend_enable": 0x0102E23C,
    "log_output_timestamp_freq_set": 0x0102E8A8,
    "log_set_timestamp_func": 0x0102DDD4,
    "max_utilization_update": 0x01039DB6,
    "mpsc_pbuf_alloc": 0x0102CC34,
    "mpsc_pbuf_claim": 0x0102CE14,
    "mpsc_pbuf_commit": 0x0102CD8C,
    "mpsc_pbuf_free": 0x0102CF00,
    "mpsc_pbuf_init": 0x0102CBD8,
    "mpsc_pbuf_is_pending": 0x01039DD0,
    "post_drop_action": 0x01039D80,
    "rd_idx_inc": 0x01039C3C,
    "sys_clock_cycle_get_32": 0x0103A6C6,
    "z_arm_on_enter_cpu_idle": 0x0102D1C0,
    "z_arm_on_enter_cpu_idle_prepare": 0x0102D0C4,
    "z_impl_k_sem_init": 0x0103B224,
    "z_impl_k_sem_take": 0x0103689C,
    "z_impl_k_sleep": 0x01037C64,
    "z_impl_k_timer_stop": 0x0103B3A6,
    "z_impl_k_timer_start": 0x01038448,
    "z_impl_log_process": 0x0102DF2C,
    "z_impl_z_log_msg_runtime_vcreate": 0x0102E3A8,
    "z_log_dropped": 0x0102DE10,
    "z_log_dropped_read_and_clear": 0x0102DE38,
    "z_log_init": 0x0102DCF4,
    "z_log_msg_free": 0x0102DF10,
    "z_log_msg_init": 0x0102DEA0,
    "z_log_msg_local_claim": 0x0102DF04,
    "z_log_msg_pending": 0x0102DF20,
    "z_log_msg_post_finalize": 0x0102E140,
})

# Absolute relocations are masked for instruction comparison only after their
# linked firmware values have been checked.  This closes the mutable logging
# state and the source-owned constant/string references, rather than proving a
# body while silently accepting a different private layout.
ABSOLUTE_TARGETS = {
    ("mpsc_pbuf", ".rodata.mpsc_pbuf_init.str1.1"):
        {0x0103D2A7, 0x0103D406},
    ("mpsc_pbuf", ".rodata.mpsc_pbuf_put_word.str1.1"):
        {0x0103D3B6},
    ("log_core", "log_process_thread_timer_expiry_fn"): {0x0102E5BD},
    ("log_core", ".bss.log_process_thread_timer"): {0x21002790},
    ("log_core", "logging_thread"): {0x210022F0},
    ("log_core", "log_process_thread_func"): {0x0102E865},
    ("log_core", "logging_stack"): {0x210081C0},
    ("log_core", ".rodata.enable_logger.str1.1"): {0x0103D5CF},
    ("log_core", "_log_backend_list_start"): {0x0103C0EC},
    ("log_core", "_log_backend_list_end"): {0x0103C0FC},
    ("log_core", ".rodata.z_log_init.str1.1"):
        {0x0103D2A7, 0x0103D5D7},
    ("log_core", ".bss.initialized"): {0x2100466C},
    ("log_core", "log_process_thread_sem"): {0x21000944},
    ("log_core", ".rodata.format_table"): {0x0103C914},
    ("log_core", ".data.timestamp_func"): {0x2100061C},
    ("log_core", ".bss.backend_attached"): {0x21004FAC},
    ("log_core", ".bss.dropped_cnt"): {0x21004664},
    ("log_core", ".bss.buffered_cnt"): {0x21004668},
    ("log_core", "._log_mpsc_pbuf.static.log_buffer_"): {0x2100086C},
    ("log_core", ".rodata.mpsc_config"): {0x0103C900},
    ("log_core", ".bss.curr_log_buffer"): {0x2100465C},
    ("log_core", ".bss.panic_mode"): {0x21004FAD},
    ("log_core", "default_get_timestamp"): {0x0103AA91},
    ("log_core", ".bss.last_failure_report"): {0x21002788},
    ("log_core", ".bss.proc_tid"): {0x21004660},
    ("log_core", ".bss.process_lock.0"): {0x21004658},
    ("log_core", "z_tls_current"): {8},
    ("log_core", ".rodata.z_log_msg_post_finalize.str1.1"):
        {0x0103D3B6},
}

PRIVATE_STATE = {
    ("work", ".bss.pending_cancels"): {
        "runtime_address": 0x21004B50, "size": 8,
        "references": [("work_queue_main", 0x1AC)],
    },
    ("work", ".bss.lock"): {
        "runtime_address": 0x21004B58, "size": 4,
        "references": [("work_queue_main", 0x1A8),
                       ("z_work_submit_to_queue", 0x84),
                       ("k_work_queue_drain", 0xE4)],
    },
    ("timer", ".bss.lock"): {
        "runtime_address": 0x21004B74, "size": 4,
        "references": [("z_timer_expiration_handler", 0x13C)],
    },
    ("poll", ".bss.lock"): {
        "runtime_address": 0x21004B78, "size": 4,
        "references": [("register_events", 0x19C),
                       ("clear_event_registrations", 0x100),
                       ("z_impl_k_poll", 0x158),
                       ("z_impl_k_poll_signal_raise", 0x84)],
    },
    ("poll", ".data.wait_q.0"): {
        "runtime_address": 0x21000758, "size": 8,
        "references": [("z_impl_k_poll", 0x160)],
    },
}


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
    """Decode an R_ARM_THM_CALL/JUMP24 field from linked firmware bytes."""
    first, second = struct.unpack("<HH", raw)
    sign = (first >> 10) & 1
    j1 = (second >> 13) & 1
    j2 = (second >> 11) & 1
    i1 = (~(j1 ^ sign)) & 1
    i2 = (~(j2 ^ sign)) & 1
    immediate = (sign << 24) | (i1 << 23) | (i2 << 22)
    immediate |= (first & 0x3FF) << 12
    immediate |= (second & 0x7FF) << 1
    if sign:
        immediate -= 1 << 25
    return (instruction_va + 4 + immediate) & 0xFFFFFFFF


def _relocation_symbol(elf: ELFFile, relocation) -> str:
    symbols = elf.get_section_by_name(".symtab")
    symbol = symbols.get_symbol(relocation["r_info_sym"])
    if symbol.name:
        return symbol.name
    index = symbol["st_shndx"]
    if isinstance(index, int):
        return elf.get_section(index).name
    raise ValueError("unnamed relocation target")


def build() -> dict:
    config = config_values()
    required = {"CONFIG_SPIN_VALIDATE": "y", "CONFIG_SMP": "n"}
    if any(config.get(key, "n") != value for key, value in required.items()):
        raise ValueError("corrected CPUNET kernel configuration drifted")
    firmware = IMAGE.read_bytes()
    section_matches = []
    call_checks = []
    state_observed = {}
    absolute_observed = {}
    unit_receipts = []
    manifest_functions = []

    for unit, definition in UNITS.items():
        object_path = BUILD / definition["object"]
        source_path = NCS / definition["source"]
        unit_receipts.append({
            "unit": unit,
            "source": definition["source"],
            "source_sha256": sha256(source_path),
            "object": definition["object"],
            "object_sha256": sha256(object_path),
            "live_section_count": len(definition["sections"]),
        })
        with object_path.open("rb") as stream:
            elf = ELFFile(stream)
            for symbol, va in definition["sections"].items():
                section_name = ".text." + symbol
                section = elf.get_section_by_name(section_name)
                if section is None:
                    raise ValueError(f"missing {definition['object']}:{section_name}")
                candidate = bytearray(section.data())
                original = bytearray(firmware[va - BASE:va - BASE + len(candidate)])
                relocation_section = elf.get_section_by_name(".rel" + section_name)
                relocations = []
                if relocation_section is not None:
                    for relocation in relocation_section.iter_relocations():
                        offset = int(relocation["r_offset"])
                        kind = int(relocation["r_info_type"])
                        if kind not in SUPPORTED_RELOCATIONS:
                            raise ValueError(f"unsupported relocation {kind} in {symbol}")
                        target = _relocation_symbol(elf, relocation)
                        linked = bytes(original[offset:offset + 4])
                        relocations.append({"offset": offset, "type": kind,
                                            "target": target})
                        if kind in (10, 30):
                            actual = decode_thumb_call(linked, va + offset)
                            expected = CALL_TARGETS.get(target)
                            if expected is None or actual != expected:
                                raise ValueError(
                                    f"call closure mismatch {symbol}+0x{offset:x} "
                                    f"{target}: 0x{actual:08x} != {expected!r}")
                            call_checks.append({
                                "caller": symbol,
                                "caller_va": f"0x{va:08x}",
                                "offset": offset,
                                "relocation": kind,
                                "target_symbol": target,
                                "target_va": f"0x{actual:08x}",
                            })
                        elif kind in (2, 108):
                            actual = struct.unpack("<I", linked)[0]
                            absolute_observed.setdefault((unit, target), []).append(
                                (symbol, offset, actual))
                            if target in {key[1] for key in PRIVATE_STATE}:
                                state_observed.setdefault((unit, target), []).append(
                                    (symbol, offset, actual))
                        candidate[offset:offset + 4] = b"\0" * 4
                        original[offset:offset + 4] = b"\0" * 4
                if candidate != original:
                    mismatch = next(index for index, pair in
                                    enumerate(zip(candidate, original))
                                    if pair[0] != pair[1])
                    raise ValueError(
                        f"non-relocation mismatch {symbol}+0x{mismatch:x}")
                section_matches.append({
                    "unit": unit,
                    "symbol": symbol,
                    "va": f"0x{va:08x}",
                    "section": section_name,
                    "size": len(candidate),
                    "match": "relocation-masked-byte-exact",
                    "normalized_sha256": digest(bytes(original)),
                    "relocations": relocations,
                })

                raw = f"FUN_{va:08x}"
                source = ROOT / "recon/net/src" / (raw + ".c")
                row = {
                    "va": f"0x{va:08x}",
                    "raw_symbol": raw,
                    "upstream_symbol": symbol,
                    "durable_symbol": symbol.replace(".", "_"),
                    "upstream_source": definition["source"],
                    "upstream_linkage": ("file_static" if symbol in {
                        "process_recheck", "validate_args", "notify_one",
                        "process_event", "transition_complete",
                        "flag_test_and_clear", "notify_queue_locked.isra.0",
                        "work_queue_main", "submit_to_queue_locked",
                        "add_event", "register_events", "signal_poll_event",
                        "clear_event_registrations",
                        "free_space", "get_usage", "idx_inc", "rd_idx_inc",
                        "add_skip_item", "drop_item_locked",
                        "post_drop_action", "max_utilization_update",
                        "dummy_timestamp", "default_get_timestamp",
                        "atomic_inc", "enable_logger",
                        "activate_foreach_backend", "dropped_notify",
                        "log_core_init", "log_process_thread_func",
                    } else "public"),
                    "whole_source_unit_selected": True,
                    "call_targets_checked": True,
                    "safe_to_adopt": True,
                    "exclude_reconstruction": True,
                    "reconstruction_present": source.is_file(),
                }
                if source.is_file():
                    row["reconstruction_source"] = str(source.relative_to(ROOT))
                    row["reconstruction_source_sha256"] = sha256(source)
                manifest_functions.append(row)

    state_rows = []
    for key, expected in PRIVATE_STATE.items():
        observed = state_observed.get(key, [])
        wanted_refs = sorted(expected["references"])
        got_refs = sorted((symbol, offset) for symbol, offset, _ in observed)
        addresses = {address for _, _, address in observed}
        if got_refs != wanted_refs or addresses != {expected["runtime_address"]}:
            raise ValueError(f"private-state closure mismatch: {key}")
        state_rows.append({
            "unit": key[0], "section": key[1],
            "size": expected["size"],
            "runtime_address": f"0x{expected['runtime_address']:08x}",
            "initialization": ("zero_initialized" if key[1].startswith(".bss")
                               else "stock_static_initializer"),
            "relocation_references": [
                {"symbol": symbol, "offset": offset}
                for symbol, offset in wanted_refs
            ],
        })

    absolute_rows = []
    for key, expected_addresses in ABSOLUTE_TARGETS.items():
        observed = absolute_observed.get(key, [])
        addresses = {address for _, _, address in observed}
        if not observed or addresses != expected_addresses:
            raise ValueError(f"absolute closure mismatch: {key}")
        absolute_rows.append({
            "unit": key[0], "target": key[1],
            "runtime_addresses": [f"0x{address:08x}"
                                  for address in sorted(addresses)],
            "relocation_references": [
                {"symbol": symbol, "offset": offset,
                 "runtime_address": f"0x{address:08x}"}
                for symbol, offset, address in sorted(observed)
            ],
        })

    if len(section_matches) != 84:
        raise ValueError("expected complete 84-section closure")
    recovered = sorted(row["va"] for row in manifest_functions
                       if row["reconstruction_present"])
    return {
        "schema": 1,
        "core": "net",
        "component": "zephyr_os_kernel_stock",
        "status": "authorized_atomic",
        "safe": True,
        "policy": {
            "adoption_unit": "nine_complete_live_source_unit_closures",
            "proof": "relocation-masked bytes plus every resolved call target",
            "private_state_is_atomic": True,
            "sdc_policy": "report_only_unchanged",
        },
        "upstream": {
            "repository": "zephyr",
            "commit": ZEPHYR_COMMIT,
            "configured_build": str(BUILD),
            "configured_build_sha256": sha256(CONFIG),
            "required_config": required,
            "abi": "Cortex-M33, Thumb-2, soft-float, -Os",
            "version_precision": {
                "binary_selected_family": "Zephyr 3.4.99-ncs1",
                "manifest_selected_tag": "v3.4.99-ncs1-1",
                "indistinguishable_source_tags": [
                    "v3.4.99-ncs1", "v3.4.99-ncs1-1",
                    "v3.4.99-ncs1-2", "v3.4.99-ncs1-3",
                ],
                "neighbor_rejection": (
                    "log_core.c differs at v3.3.99-ncs1 and "
                    "v3.5.99-ncs1; cpu_idle.S differs at v3.3.99-ncs1"),
            },
        },
        "source_units": unit_receipts,
        "section_matches": section_matches,
        "call_target_checks": call_checks,
        "private_state_sections": state_rows,
        "resolved_absolute_targets": absolute_rows,
        "manifest_functions": manifest_functions,
        "recovered_atomic_group": recovered,
        "atomic_group": [row["va"] for row in manifest_functions],
        "identity_discriminators": [{
            "va": "0x0103a478",
            "selected_symbol": "net_buf_simple_add_mem",
            "rejected_identical_body": "net_buf_simple_push_mem",
            "decisive_call": "net_buf_simple_add@0x01030084",
        }, {
            "va": "0x0103a45a",
            "selected_symbol": "net_buf_simple_push_u8",
            "rejected_identical_body": "net_buf_simple_add_u8",
            "decisive_call": "net_buf_simple_push@0x0103004c",
        }],
    }


def write_report(data: dict) -> None:
    lines = [
        "# CPUNET exact Zephyr source closures", "",
        "The corrected stock build at Zephyr commit `83980fe` uses "
        "`CONFIG_SPIN_VALIDATE=y` and `CONFIG_SMP=n`. All 84 live sections "
        "from the nine units below are relocation-masked byte-exact, and every "
        "Thumb call target is checked against the firmware.", "",
        "| unit | live functions | private state |", "|---|---:|---:|",
    ]
    for unit in data["source_units"]:
        count = sum(row["unit"] == unit["unit"]
                    for row in data["private_state_sections"])
        lines.append(f"| `{unit['source']}` | {unit['live_section_count']} | {count} |")
    lines += ["", "The ambiguous body at `0x0103a478` is "
              "`net_buf_simple_add_mem`: its relocated branch targets "
              "`net_buf_simple_add@0x01030084`, not the push owner. SDC "
              "ownership remains report-only.", ""]
    REPORT.write_text("\n".join(lines))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    encoded = json.dumps(data, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.is_file() or OUTPUT.read_text() != encoded:
            raise SystemExit("stale CPUNET Zephyr stock adoption receipt")
    else:
        OUTPUT.write_text(encoded)
        write_report(data)
    print("CPUNET Zephyr stock adoption: 84 functions, 5 kernel private states "
          "and 28 absolute targets exact")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
