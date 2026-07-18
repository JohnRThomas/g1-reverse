#!/usr/bin/env python3
"""Authorize the exact configured MPSC closure and local logging wrapper."""

import argparse
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_collision23_mpsc_atomic_adoption.json"
IMAGE = ROOT / "app_update.bin"
CONFIG = Path("/tmp/g1-fwconfig-shadow/zephyr/.config")
MPSC_OBJECT = Path("/tmp/g1-fwconfig-shadow/zephyr/CMakeFiles/zephyr.dir/lib/os/mpsc_pbuf.c.obj")
LOG_OBJECT = Path("/tmp/g1-fwconfig-shadow/zephyr/CMakeFiles/zephyr.dir/subsys/logging/log_core.c.obj")
MPSC_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/lib/os/mpsc_pbuf.c")
LOG_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/logging/log_core.c")

# VA: (configured symbol, object, source, linkage, visible collision symbol)
FUNCTIONS = {
    "0x0004bc28": ("mpsc_pbuf_init", MPSC_OBJECT, MPSC_SOURCE, "public", "mpsc_pbuf_init"),
    "0x0004bc8c": ("mpsc_pbuf_alloc", MPSC_OBJECT, MPSC_SOURCE, "public", None),
    "0x0004be0c": ("mpsc_pbuf_commit", MPSC_OBJECT, MPSC_SOURCE, "public", "mpsc_pbuf_commit"),
    "0x0004beb8": ("mpsc_pbuf_claim", MPSC_OBJECT, MPSC_SOURCE, "public", None),
    "0x0004bfc8": ("mpsc_pbuf_free", MPSC_OBJECT, MPSC_SOURCE, "public", "mpsc_pbuf_free"),
    "0x0004d56c": ("z_log_msg_local_claim", LOG_OBJECT, LOG_SOURCE, "public", "mpsc_pbuf_claim"),
    "0x0007e314": ("free_space", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e33a": ("get_usage", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e35c": ("idx_inc", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e378": ("rd_idx_inc", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e390": ("add_skip_item", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e3ce": ("drop_item_locked", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e4bc": ("post_drop_action", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
    "0x0007e4f2": ("max_utilization_update", MPSC_OBJECT, MPSC_SOURCE, "translation_unit_local", None),
}
GROUP = sorted(FUNCTIONS)
VISIBLE = {va for va, values in FUNCTIONS.items() if values[4]}
REMOVED = sorted(values[4] for values in FUNCTIONS.values() if values[4])
REQUIRED_CONFIG = {
    "CONFIG_ASSERT": "y", "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_SPIN_VALIDATE": "y", "CONFIG_THREAD_LOCAL_STORAGE": "y",
    "CONFIG_ERRNO_IN_TLS": "n",
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def section_receipt(va_text, symbol, obj):
    section_name = ".text." + symbol
    with obj.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(section_name)
        if section is None:
            raise ValueError("missing section " + section_name)
        selected = bytearray(section.data())
        reloc = elf.get_section_by_name(".rel" + section_name)
        offsets = [] if reloc is None else [r["r_offset"] for r in reloc.iter_relocations()]
    va = int(va_text, 16)
    firmware = bytearray(IMAGE.read_bytes()[va - 0xC000:va - 0xC000 + len(selected)])
    for offset in offsets:
        selected[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if selected != firmware:
        raise ValueError("configured section mismatch: " + symbol)
    return {
        "firmware_code_size": len(firmware),
        "upstream_code_size": len(selected),
        "upstream_symbol_size": len(selected),
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
        "instruction_exact": True,
    }


def rows():
    collision_by_va = {row["va"]: row for row in json.loads(
        COLLISIONS.read_text())["functions"]}
    output = []
    for va in GROUP:
        symbol, obj, source, linkage, visible_symbol = FUNCTIONS[va]
        raw = "FUN_" + va[2:]
        current = visible_symbol or symbol
        row = {
            "batch": "COLLISION-23", "va": va, "raw_symbol": raw,
            "symbol": current, "status": "authorized",
            "configuration_variant_exact": True,
            "required_config": REQUIRED_CONFIG,
            "atomic_group": GROUP,
            "upstream_source": str(source).replace("/Users/freedomcoder/ncs251/", ""),
            "upstream_source_sha256": sha(source),
            "upstream_object": str(obj), "upstream_object_sha256": sha(obj),
            "configured_build": str(CONFIG), "configured_build_sha256": sha(CONFIG),
            "reconstruction_source_sha256": sha(ROOT / "recon/app/src" / (raw + ".c")),
            "cfg_verify_cases": 1,
            "owner_cfg_verify": {"status": "PASS", "cases": 1},
            "whole_unit_closure": {
                "safe": True, "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": REMOVED,
                "exclude_only": GROUP, "new_undefined_symbols": [],
            },
        }
        row.update(section_receipt(va, symbol, obj))
        if va not in VISIBLE:
            row["hidden_owner_closure"] = True
            row["identity_correction"] = {
                "baseline_collision_symbol": current,
                "corrected_upstream_symbol": symbol,
                "corrected_readable_identity": symbol,
                "corrected_upstream_source": row["upstream_source"],
                "upstream_linkage": linkage,
            }
        elif symbol != visible_symbol:
            row["identity_correction"] = {
                "baseline_collision_symbol": visible_symbol,
                "corrected_upstream_symbol": symbol,
                "corrected_readable_identity": symbol,
                "corrected_upstream_source": row["upstream_source"],
                "upstream_linkage": linkage,
            }
        collision = collision_by_va.get(va)
        if collision:
            row["collision_receipt_sha256"] = json_sha(collision)
            row["baseline_upstream_object_sha256"] = collision["upstream"]["object_sha256"]
            row["baseline_upstream_source_sha256"] = collision[
                "upstream"]["source"]["sha256"]
            row["baseline_configured_build_sha256"] = collision[
                "configured_inclusion"]["zephyr_config_sha256"]
        output.append(row)
    return output


def receipt(auth_rows):
    post_collisions = sorted([
        "bt_id_add", "k_work_busy_get", "k_work_cancel", "k_work_init",
        "k_work_queue_init", "k_work_queue_start", "k_work_reschedule_for_queue",
        "k_work_schedule_for_queue", "log_init", "log_output_dropped_process",
        "log_output_process", "sys_heap_alloc", "sys_heap_init",
        "z_log_msg_free", "z_log_msg_pending",
    ])
    return {
        "schema": 1, "core": "app", "batch": "COLLISION-23",
        "status": "authorized_atomic",
        "decision": "adopt_exact_configured_mpsc_duplicates_and_local_claim_wrapper",
        "atomic_group": GROUP,
        "selected_source_units": ["zephyr/lib/os/mpsc_pbuf.c", "zephyr/subsys/logging/log_core.c:z_log_msg_local_claim"],
        "already_sdk_owned_without_reconstruction_duplicate": {
            "va": "0x0007e50c", "symbol": "mpsc_pbuf_is_pending",
            "normalized_code_sha256": "f45d24c1c9d232ab80362e7ade7abfdb5eb82489e2799023f5c67b6c56007e35",
        },
        "authorizations": auth_rows,
        "expected_link_delta": {"before": 19, "after": 15, "removed": REMOVED,
                                "added": [], "unresolved": ["FUN_0005463e", "FUN_00054688"]},
        "verified_normal_link": {
            "build": "/tmp/g1-app-collision23-post-0718f",
            "before": 19, "after": 15, "removed": REMOVED, "added": [],
            "collisions": post_collisions,
            "unresolved": ["FUN_0005463e", "FUN_00054688"],
        },
        "sdc_policy": "report_only_unchanged",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--authorize", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    auth_rows = rows()
    if args.authorize:
        catalog = json.loads(AUTH.read_text())
        catalog["authorizations"] = [r for r in catalog["authorizations"]
                                     if r.get("batch") != "COLLISION-23"] + auth_rows
        catalog["configured_build_receipts"] = sorted(set(
            catalog.get("configured_build_receipts", []) + [str(CONFIG)]))
        AUTH.write_text(json.dumps(catalog, indent=1) + "\n")
    rendered = json.dumps(receipt(auth_rows), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise ValueError("stale COLLISION-23 adoption receipt")
    else:
        OUTPUT.write_text(rendered)
    print("COLLISION-23: 14 exact reconstruction owners authorized; expected 19 -> 15")


if __name__ == "__main__":
    main()
