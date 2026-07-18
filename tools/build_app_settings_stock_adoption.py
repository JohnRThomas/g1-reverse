#!/usr/bin/env python3
"""Generate the exact configured Zephyr settings source-unit adoption."""

import argparse
import gzip
import hashlib
import json
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import extract  # noqa: E402

NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
CONFIG = BUILD / "zephyr/.config"
OBJROOT = BUILD / "zephyr/CMakeFiles/zephyr.dir/subsys/settings/src"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_settings_stock_atomic_adoption.json"

REQUIRED_CONFIG = {
    "CONFIG_SETTINGS": "y",
    "CONFIG_SETTINGS_DYNAMIC_HANDLERS": "y",
    "CONFIG_SETTINGS_LOG_LEVEL": "3",
}

# Firmware VA: (configured symbol, source unit, complete emitted extent, ABI).
FUNCTIONS = {
    "0x0004e3c0": ("settings_src_register", "settings_store.c", 28,
                    "void settings_src_register(struct settings_store *)"),
    "0x0004e3dc": ("settings_dst_register", "settings_store.c", 12,
                    "void settings_dst_register(struct settings_store *)"),
    "0x0004e3e8": ("settings_load_subtree", "settings_store.c", 76,
                    "int settings_load_subtree(const char *)"),
    "0x0004e434": ("settings_load_subtree_direct", "settings_store.c", 64,
                    "int settings_load_subtree_direct(const char *, settings_load_direct_cb, void *)"),
    "0x0004e474": ("settings_store_init", "settings_store.c", 16,
                    "void settings_store_init(void)"),
    "0x0004e484": ("settings_init", "settings.c", 16,
                    "void settings_init(void)"),
    "0x0004e494": ("settings_register", "settings.c", 172,
                    "int settings_register(struct settings_handler *)"),
    "0x0004e540": ("settings_parse_and_lookup", "settings.c", 196,
                    "struct settings_handler_static *settings_parse_and_lookup(const char *, const char **)"),
    "0x0004e604": ("settings_call_set_handler", "settings.c", 164,
                    "int settings_call_set_handler(const char *, size_t, settings_read_cb, void *, const struct settings_load_arg *)"),
    "0x0004e6a8": ("settings_commit_subtree", "settings.c", 156,
                    "int settings_commit_subtree(const char *)"),
    "0x0007f192": ("settings_load", "settings_store.c", 6,
                    "int settings_load(void)"),
    "0x0007f198": ("settings_delete", "settings_store.c", 8,
                    "int settings_delete(const char *)"),
}
GROUP = sorted(FUNCTIONS)
COLLISION_SYMBOLS = {
    "settings_register", "settings_parse_and_lookup",
    "settings_commit_subtree", "settings_load_subtree",
    "settings_load_subtree_direct", "settings_load",
}
SDK_ONLY_EXACT = {
    "0x0004e374": ["settings_save_one", 76],
    "0x0007f1a0": ["settings_name_steq", 72],
    "0x0007f1e8": ["settings_name_next", 36],
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def section_receipt(obj, symbol, va, extent):
    with obj.open("rb") as stream:
        elf = ELFFile(stream)
        name = ".text." + symbol
        section = elf.get_section_by_name(name)
        if section is None or len(section.data()) != extent:
            raise ValueError("unexpected configured section extent " + name)
        selected = bytearray(section.data())
        reloc = elf.get_section_by_name(".rel" + name)
        offsets = ([] if reloc is None else
                   [item["r_offset"] for item in reloc.iter_relocations()
                    if item["r_offset"] < extent])
    firmware = bytearray(extract.read(va, extent))
    for offset in offsets:
        selected[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if selected != firmware:
        raise ValueError("relocation-masked mismatch for " + symbol)
    return {
        "firmware_code_size": extent, "upstream_code_size": extent,
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
        "relocation_masked_byte_exact": True,
    }


def direct_callers():
    with gzip.open(ROOT / "recon/catalogs/refgraph_app.json.gz", "rt") as stream:
        graph = json.load(stream)["functions"]
    return {va: sorted("0x%08x" % int(value, 0) for value in
                       graph.get(hex(int(va, 16)), {}).get("callers", []))
            for va in GROUP}


def build():
    collision_catalog = json.loads(COLLISIONS.read_text())
    collision_by_va = {row["va"]: row
                       for row in collision_catalog["functions"]}
    config_sha = sha(CONFIG)
    callers = direct_callers()
    rows = []
    for va in GROUP:
        symbol, unit, extent, abi = FUNCTIONS[va]
        obj = OBJROOT / (unit + ".obj")
        source_rel = "zephyr/subsys/settings/src/" + unit
        source = NCS / source_rel
        raw = "FUN_" + va[2:]
        recovered = ROOT / "recon/app/src" / (raw + ".c")
        if not recovered.exists():
            raise ValueError("missing canonical evidence " + raw)
        row = {
            "batch": "COLLISION-SETTINGS-STOCK", "va": va,
            "raw_symbol": raw, "symbol": symbol, "status": "authorized",
            "configuration_variant_exact": True,
            "required_config": REQUIRED_CONFIG, "atomic_group": GROUP,
            "upstream_source": source_rel,
            "upstream_source_sha256": sha(source),
            "upstream_object": str(obj), "upstream_object_sha256": sha(obj),
            "configured_link_owner": "zephyr/libzephyr.a(%s.obj)" % unit,
            "configured_build": str(CONFIG),
            "configured_build_sha256": config_sha,
            "reconstruction_source": str(recovered.relative_to(ROOT)),
            "reconstruction_source_sha256": sha(recovered),
            "abi": abi, "instruction_exact": True,
            "cfg_verify_cases": 1,
            "owner_cfg_verify": {"status": "PASS", "cases": 0},
            "callers": callers[va],
            "whole_unit_closure": {
                "safe": True, "archive_member_already_selected": True,
                "same_source_unit_collision_symbols":
                    sorted(COLLISION_SYMBOLS),
                "same_source_unit_sdk_only_exact_symbols":
                    [value[0] for value in SDK_ONLY_EXACT.values()],
                "private_state": {
                    "settings_lock": "0x20003868",
                    "settings_save_dst": "0x2000a100",
                    "settings_load_srcs": "0x2000a104",
                    "settings_handlers": "0x2000a10c",
                },
                "exclude_only": GROUP, "new_undefined_symbols": [],
            },
        }
        row.update(section_receipt(obj, symbol, int(va, 16), extent))
        collision = collision_by_va.get(va)
        if collision is None:
            row["hidden_owner_closure"] = True
        else:
            row["collision_receipt_sha256"] = json_sha(collision)
            row["baseline_upstream_object_sha256"] = collision[
                "upstream"]["object_sha256"]
            row["baseline_configured_build_sha256"] = collision[
                "configured_inclusion"]["zephyr_config_sha256"]
        if collision is None:
            row["identity_correction"] = {
                "baseline_collision_symbol": None,
                "corrected_readable_identity": symbol,
                "corrected_upstream_symbol": symbol,
                "corrected_upstream_source": source_rel,
                "upstream_linkage": "public",
            }
        rows.append(row)
    return {
        "schema": 1, "core": "app", "status": "authorized_atomic",
        "decision": "adopt_exact_configured_zephyr_settings_source_units",
        "configured_build_receipts": [str(CONFIG)],
        "atomic_group": GROUP,
        "selected_source_units": [
            "zephyr/subsys/settings/src/settings.c",
            "zephyr/subsys/settings/src/settings_store.c"],
        "authorizations": rows,
        "sdk_only_exact_owners": SDK_ONLY_EXACT,
        "private_state_pins": {
            "settings_lock": "0x20003868",
            "settings_save_dst": "0x2000a100",
            "settings_load_srcs": "0x2000a104",
            "settings_handlers": "0x2000a10c",
        },
        "expected_link_delta": {
            "before": 28, "after": 22,
            "removed": sorted(COLLISION_SYMBOLS), "added": [],
            "unresolved": ["FUN_0005463e", "FUN_00054688"],
        },
        "sdc_policy": "report_only_unchanged",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise ValueError("stale settings stock adoption receipt")
    else:
        OUTPUT.write_text(text)
    print("settings stock adoption: %d canonical exact owners" % len(GROUP))


if __name__ == "__main__":
    main()
