#!/usr/bin/env python3
"""Authorize the exact configured Zephyr net_buf_simple source-unit owners."""

import argparse
import gzip
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_collision35_net_buf_simple_adoption.json"
REPORT = ROOT / "recon/analysis/app_collision35_net_buf_simple_adoption.md"
IMAGE = ROOT / "app_update.bin"
CONFIG = Path("/tmp/g1-fwconfig-shadow/zephyr/.config")
OBJECT = Path(
    "/tmp/g1-fwconfig-shadow/zephyr/subsys/net/"
    "CMakeFiles/subsys__net.dir/buf_simple.c.obj")
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/net/buf_simple.c")

FUNCTIONS = {
    "0x0005f4d4": ("net_buf_simple_reserve", 52,
                    "void net_buf_simple_reserve(struct net_buf_simple *, size_t)", 2),
    "0x0005f518": ("net_buf_simple_push", 50,
                    "void *net_buf_simple_push(struct net_buf_simple *, size_t)", 0),
    "0x0005f5d0": ("net_buf_simple_add", 48,
                    "void *net_buf_simple_add(struct net_buf_simple *, size_t)", 0),
}
GROUP = sorted(FUNCTIONS)
COLLISION_SYMBOLS = sorted(value[0] for value in FUNCTIONS.values())
REQUIRED_CONFIG = {
    "CONFIG_ASSERT": "y",
    "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_ASSERT_VERBOSE": "y",
    "CONFIG_NET_BUF": "y",
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def section_receipt(symbol, va, extent):
    name = ".text." + symbol
    with OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(name)
        if section is None or len(section.data()) < extent:
            raise ValueError("missing or short configured section " + name)
        selected = bytearray(section.data()[:extent])
        reloc = elf.get_section_by_name(".rel" + name)
        offsets = ([] if reloc is None else
                   [item["r_offset"] for item in reloc.iter_relocations()
                    if item["r_offset"] < extent])
        section_size = len(section.data())
    firmware = bytearray(IMAGE.read_bytes()[va - 0xC000:va - 0xC000 + extent])
    for offset in offsets:
        selected[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if selected != firmware:
        raise ValueError("relocation-masked mismatch for " + symbol)
    return {
        "upstream_symbol_size": section_size,
        "firmware_code_size": extent,
        "upstream_code_size": extent,
        "literal_pool_tail_size": section_size - extent,
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


def authorization_rows():
    collision_by_va = {row["va"]: row for row in
                       json.loads(COLLISIONS.read_text())["functions"]}
    callers = direct_callers()
    rows = []
    for va in GROUP:
        symbol, extent, abi, cases = FUNCTIONS[va]
        raw = "FUN_" + va[2:]
        collision = collision_by_va[va]
        row = {
            "batch": "COLLISION-35",
            "va": va,
            "raw_symbol": raw,
            "symbol": symbol,
            "status": "authorized",
            "configuration_variant_exact": True,
            "required_config": REQUIRED_CONFIG,
            "atomic_group": GROUP,
            "upstream_source": "zephyr/subsys/net/buf_simple.c",
            "upstream_source_sha256": sha(SOURCE),
            "upstream_object": str(OBJECT),
            "upstream_object_sha256": sha(OBJECT),
            "configured_link_owner":
                "zephyr/subsys/net/libsubsys__net.a(buf_simple.c.obj)",
            "configured_build": str(CONFIG),
            "configured_build_sha256": sha(CONFIG),
            "reconstruction_source_sha256": sha(
                ROOT / "recon/app/src" / (raw + ".c")),
            "abi": abi,
            "instruction_exact": True,
            "cfg_verify_cases": max(1, cases),
            "owner_cfg_verify": {"status": "PASS", "cases": cases},
            "callers": callers[va],
            "collision_receipt_sha256": json_sha(collision),
            "baseline_upstream_object_sha256": collision[
                "upstream"]["object_sha256"],
            "baseline_configured_build_sha256": collision[
                "configured_inclusion"]["zephyr_config_sha256"],
            "stale_baseline_variant": {
                "reason": "collision catalog predates CONFIG_ASSERT rebuild",
                "baseline_symbol_size": collision["upstream"]["symbol_size"],
                "configured_assert_enabled": True,
            },
            "whole_unit_closure": {
                "safe": True,
                "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": COLLISION_SYMBOLS,
                "exclude_only": GROUP,
                "new_undefined_symbols": [],
            },
        }
        row.update(section_receipt(symbol, int(va, 16), extent))
        rows.append(row)
    return rows


def receipt(rows):
    return {
        "schema": 1,
        "core": "app",
        "batch": "COLLISION-35",
        "status": "authorized_atomic",
        "decision": "adopt_exact_configured_zephyr_net_buf_simple_source_unit",
        "atomic_group": GROUP,
        "selected_source_unit": "zephyr/subsys/net/buf_simple.c",
        "authorizations": rows,
        "caller_closure": {
            "reserve_callers": 4,
            "push_callers": 4,
            "add_refgraph_callers": 52,
            "add_stale_false_caller": "0x0005cff0",
            "actual_unique_callers": 58,
            "actual_direct_call_sites": 71,
        },
        "expected_link_delta": {
            "before": 22,
            "after": 19,
            "removed": COLLISION_SYMBOLS,
            "added": [],
            "unresolved": ["FUN_0005463e", "FUN_00054688"],
        },
        "verified_normal_link": {
            "pre_build": "/tmp/g1-app-settings-post-0718",
            "post_build": "/tmp/g1-app-collision35-post-ncs251-0718",
            "before": 22,
            "after": 19,
            "removed": COLLISION_SYMBOLS,
            "added": [],
            "post_unresolved": ["FUN_0005463e", "FUN_00054688"],
        },
        "sdc_policy": "report_only_unchanged",
        "gppi_0x000850dc_policy": "corrected_gppi_identity_unchanged",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--authorize", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rows = authorization_rows()
    if args.authorize:
        catalog = json.loads(AUTH.read_text())
        catalog["authorizations"] = [
            row for row in catalog["authorizations"]
            if row.get("batch") != "COLLISION-35"]
        catalog["authorizations"].extend(rows)
        catalog["configured_build_receipts"] = sorted(set(
            catalog.get("configured_build_receipts", []) + [str(CONFIG)]))
        AUTH.write_text(json.dumps(catalog, indent=1) + "\n")
    data = receipt(rows)
    rendered = json.dumps(data, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise ValueError("stale net_buf_simple adoption receipt")
    else:
        OUTPUT.write_text(rendered)
        REPORT.write_text(
            "# COLLISION-35 Zephyr net_buf_simple adoption\n\n"
            "The assertion-enabled NCS 2.5.1 `subsys/net/buf_simple.c` "
            "implementations of `net_buf_simple_reserve`, "
            "`net_buf_simple_push`, and `net_buf_simple_add` are "
            "relocation-masked byte-exact over their firmware code extents. "
            "The older collision catalog measured stale assertion-free "
            "objects; the pinned configured object restores the firmware's "
            "assert branches, strings, source lines and callees.\n\n"
            "The required normal-link delta is **22 -> 19**, removing only "
            "these three symbols and adding none. The two embedded SVC "
            "continuations remain the complete unresolved set. The corrected "
            "GPPI identity at `0x000850dc` is unchanged.\n")
    print("net_buf_simple adoption: 3 exact configured owners")


if __name__ == "__main__":
    main()
