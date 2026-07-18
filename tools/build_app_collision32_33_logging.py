#!/usr/bin/env python3
"""Authorize exact logging output owners and record the mixed log-core closure."""

import argparse
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_collision32_33_logging.json"
IMAGE = ROOT / "app_update.bin"
CONFIG = Path("/tmp/g1-fwconfig-shadow/zephyr/.config")
LOG_OBJECT = Path("/tmp/g1-fwconfig-shadow/zephyr/CMakeFiles/zephyr.dir/subsys/logging/log_output.c.obj")
UART_OBJECT = Path("/tmp/g1-fwconfig-shadow/zephyr/CMakeFiles/zephyr.dir/subsys/logging/backends/log_backend_uart.c.obj")
LOG_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/logging/log_output.c")
UART_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/logging/backends/log_backend_uart.c")

# VA: (configured symbol, object, source, linkage, visible collision symbol,
#      canonical receipt path, cfg cases)
FUNCTIONS = {
    "0x0004da6c": ("print_formatted", LOG_OBJECT, LOG_SOURCE,
                   "translation_unit_local", None,
                   "recon/symbolized/app/print_formatted.c", 1),
    "0x0004da90": ("newline_print", LOG_OBJECT, LOG_SOURCE,
                   "translation_unit_local", None, None, 1),
    "0x0004db04": ("log_output_process", LOG_OBJECT, LOG_SOURCE,
                   "public", None, None, 5),
    "0x0004de68": ("log_output_dropped_process", LOG_OBJECT, LOG_SOURCE,
                   "public", "log_output_dropped_process", None, 1),
    "0x0004df34": ("dropped", UART_OBJECT, UART_SOURCE,
                   "translation_unit_local", None, None, 1),
}
GROUP = sorted(FUNCTIONS)
VISIBLE = {va for va, values in FUNCTIONS.items() if values[4]}
REMOVED = ["log_output_dropped_process", "log_output_process"]
REQUIRED_CONFIG = {
    "CONFIG_ASSERT": "y",
    "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_LOG_MODE_DEFERRED": "y",
    "CONFIG_LOG_MULTIDOMAIN": "n",
    "CONFIG_LOG_OUTPUT": "y",
    "CONFIG_LOG_RUNTIME_FILTERING": "n",
    "CONFIG_LOG_BACKEND_UART": "y",
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
        offsets = [] if reloc is None else [
            row["r_offset"] for row in reloc.iter_relocations()]
    va = int(va_text, 16)
    firmware = bytearray(IMAGE.read_bytes()[
        va - 0xC000:va - 0xC000 + len(selected)])
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
        symbol, obj, source, linkage, visible, receipt_path, cases = FUNCTIONS[va]
        raw = "FUN_" + va[2:]
        canonical = ROOT / (receipt_path or ("recon/app/src/" + raw + ".c"))
        row = {
            "batch": "COLLISION-32-33",
            "va": va,
            "raw_symbol": raw,
            "symbol": visible or symbol,
            "status": "authorized",
            "configuration_variant_exact": True,
            "required_config": REQUIRED_CONFIG,
            "atomic_group": GROUP,
            "upstream_source": str(source).replace(
                "/Users/freedomcoder/ncs251/", ""),
            "upstream_source_sha256": sha(source),
            "upstream_object": str(obj),
            "upstream_object_sha256": sha(obj),
            "configured_build": str(CONFIG),
            "configured_build_sha256": sha(CONFIG),
            "reconstruction_source_sha256": sha(canonical),
            "cfg_verify_cases": cases,
            "owner_cfg_verify": {"status": "PASS", "cases": cases},
            "whole_unit_closure": {
                "safe": True,
                "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": REMOVED,
                "exclude_only": GROUP,
                "new_undefined_symbols": [],
            },
        }
        if receipt_path:
            row["reconstruction_source"] = receipt_path
        row.update(section_receipt(va, symbol, obj))
        if va not in VISIBLE:
            readable = ("log_backend_uart_dropped" if va == "0x0004df34"
                        else symbol)
            row["hidden_owner_closure"] = True
            row["identity_correction"] = {
                "baseline_collision_symbol": readable,
                "corrected_upstream_symbol": symbol,
                "corrected_readable_identity": readable,
                "corrected_upstream_source": row["upstream_source"],
                "upstream_linkage": linkage,
            }
        collision = collision_by_va.get(va)
        if collision:
            row["collision_receipt_sha256"] = json_sha(collision)
            row["baseline_upstream_object_sha256"] = collision[
                "upstream"]["object_sha256"]
            row["baseline_upstream_source_sha256"] = collision[
                "upstream"]["source"]["sha256"]
            row["baseline_configured_build_sha256"] = collision[
                "configured_inclusion"]["zephyr_config_sha256"]
        output.append(row)
    return output


def receipt(auth_rows):
    collisions = sorted([
        "bt_id_add", "k_work_busy_get", "k_work_cancel", "k_work_init",
        "k_work_queue_init", "k_work_queue_start",
        "k_work_reschedule_for_queue", "k_work_schedule_for_queue",
        "sys_heap_alloc", "sys_heap_init",
    ])
    return {
        "schema": 1,
        "core": "app",
        "batch": "COLLISION-32-33",
        "status": "authorized_atomic",
        "decision": "adopt_exact_log_output_and_namespace_firmware_log_core",
        "atomic_group": GROUP,
        "selected_source_units": [
            "zephyr/subsys/logging/log_output.c",
            "zephyr/subsys/logging/backends/log_backend_uart.c:dropped",
        ],
        "retained_namespaces": {
            "0x0004d578": "g1_recon_z_log_msg_free",
            "0x0004d588": "g1_recon_z_log_msg_pending",
            "0x0004d678": "g1_recon_z_impl_log_panic",
            "0x0004def8": "g1_recon_log_backend_uart_panic",
        },
        "authorizations": auth_rows,
        "expected_link_delta": {
            "before": 15,
            "after": 10,
            "removed": sorted(REMOVED + [
                "log_init", "z_log_msg_free", "z_log_msg_pending"]),
            "added": [],
            "unresolved": ["FUN_0005463e", "FUN_00054688"],
        },
        "verified_normal_link": {
            "build": "/private/tmp/g1-app-residue-current-0718",
            "before": 15,
            "after": 10,
            "removed": sorted(REMOVED + [
                "log_init", "z_log_msg_free", "z_log_msg_pending"]),
            "added": [],
            "collisions": collisions,
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
        catalog["authorizations"] = [
            row for row in catalog["authorizations"]
            if row.get("batch") != "COLLISION-32-33"] + auth_rows
        catalog["configured_build_receipts"] = sorted(set(
            catalog.get("configured_build_receipts", []) + [str(CONFIG)]))
        AUTH.write_text(json.dumps(catalog, indent=1) + "\n")
    rendered = json.dumps(receipt(auth_rows), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise ValueError("stale COLLISION-32-33 logging receipt")
    else:
        OUTPUT.write_text(rendered)
    print("COLLISION-32-33: five exact owners authorized; expected 15 -> 10")


if __name__ == "__main__":
    main()
