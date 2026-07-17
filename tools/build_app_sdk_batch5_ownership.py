#!/usr/bin/env python3
"""Build the fail-closed ownership record for CPUAPP SDK residue batch 5."""

import argparse
import hashlib
import json
import os


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
JSON_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch5_ownership.json")
MD_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch5_ownership.md")

OWNERS = {
    "gatt_discover_next": {
        "va": "0x00082d2e", "size": 60, "cfg_cases": 2, "checked": 42,
        "upstream_owner": "zephyr/subsys/bluetooth/host/gatt.c:gatt_discover_next",
        "linkage": "source_static", "config": ["CONFIG_BT=y"],
        "sha256": "2653a1b8037806a414267144fb0eef15210bbe321e55c1d1db0c4d950fa7cbd4"},
    "flash_settings_write_and_verify": {
        "va": "0x00022658", "size": 332, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "firmware application settings-flash owner",
        "linkage": "application_misclassified",
        "config": ["4 KiB read/erase/write transaction", "read-back verification"],
        "sha256": "b2afef95181d5cd64148253e034066e35717e7af37b8ca30aec8d000c744528b"},
    "bt_addr_le_eq": {
        "va": "0x00080fa4", "size": 16, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "zephyr/include/zephyr/bluetooth/addr.h:bt_addr_le_eq",
        "linkage": "header_inline_outlined", "config": ["CONFIG_BT=y", "bt_addr_le_t size=7"],
        "sha256": "5222671ed361166325e406a107635141b901725a8afa7e0deb590e11735b08e6"},
    "atomic_clear_bit_1": {
        "va": "0x0008304c", "size": 22, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic.h:atomic_clear_bit",
        "linkage": "header_inline_outlined", "config": ["32-bit atomic_t", "sequentially consistent"],
        "sha256": "689a8394fd4ffe91b4ff0102452a1e2629f8f97b917565e4ccd6cb065bf59190"},
    "atomic_and_3": {
        "va": "0x00080ea8", "size": 16, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and",
        "linkage": "header_inline_outlined", "config": ["32-bit atomic_t", "sequentially consistent"],
        "sha256": "2e521fc9f97b1d3be95b8ffb341224607165d364405b74789778aaf51ab2fdbd"},
    "atomic_and": {
        "va": "0x0007c08e", "size": 22, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and",
        "linkage": "header_inline_outlined", "config": ["32-bit atomic_t", "sequentially consistent"],
        "sha256": "d00593ffecb50ee7fe2cbe816952e485799c90c742550c287b6e376e95b78501"},
    "FUN_00066e70": {
        "va": "0x00066e70", "size": 76, "cfg_cases": 3, "checked": 43,
        "readable_name": "pin_init",
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c:pin_init",
        "linkage": "source_static", "config": ["CONFIG_NRFX_SPIM=y", "nRF5340 GPIO PIN_CNF ABI"],
        "sha256": "9902ed2d890612033f2e3628b705f9b46a787cc03a53acfe3422dd89f14b603a"},
    "qspi_nor_write_protection_set": {
        "va": "0x00083954", "size": 42, "cfg_cases": 0, "checked": 40,
        "upstream_owner": "zephyr/drivers/flash/nrf_qspi_nor.c:qspi_nor_write_protection_set",
        "linkage": "source_static", "config": ["CONFIG_FLASH=y", "CONFIG_NORDIC_QSPI_NOR=y"],
        "sha256": "7f0e6874a967303260866d8323e28e0df6c248b474bcda1bbf9fc2d88a4bdcf8"},
}


def digest(path):
    with open(path, "rb") as stream:
        return hashlib.sha256(stream.read()).hexdigest()


def build():
    with open(RESIDUE, encoding="utf-8") as stream:
        references = {row["symbol"]: row for row in json.load(stream)["entries"]}
    rows = []
    for symbol, owner in OWNERS.items():
        source = "recon/app/src/%s.c" % symbol
        mirror = "recon/verified/src/%s.c" % symbol
        actual = digest(os.path.join(ROOT, source))
        if actual != owner["sha256"] or digest(os.path.join(ROOT, mirror)) != actual:
            raise RuntimeError("unverified source or mirror drift: %s" % symbol)
        residue = references.get(symbol)
        expected_refs = 4 if symbol == "qspi_nor_write_protection_set" else 5
        if residue is None or residue["reference_count"] != expected_refs:
            raise RuntimeError("unexpected input residue for %s" % symbol)
        rows.append({
            "symbol": symbol, **owner, "source": source, "verified_mirror": mirror,
            "reference_count_before": residue["reference_count"],
            "reference_sites_before": residue["reference_sites"],
            "verification": "cfg_verify.py app %s: PASS (%d checked; CFG cases=%d)" %
                            (symbol, owner["checked"], owner["cfg_cases"]),
            "decision": "retain_cfg_verified_configured_reconstruction",
        })
    return {
        "schema": 1, "core": "app",
        "policy": {
            "fail_closed": True,
            "reason": "Static/header-inline/configured and application owners need separately linkable verified bodies.",
            "forbid": ["weak stub", "byte blob", "assembly wrapper", "same-name alias guess"],
        },
        "summary": {
            "function_count": len(rows),
            "reference_count_before": sum(row["reference_count_before"] for row in rows),
            "cfg_verified": len(rows), "canonical_strong_owner_count": len(rows),
        },
        "integration": {
            "derivatives": "pending centralized readable-tree consolidation",
            "retain_all_result": "not claimed by this canonical-only milestone",
        },
        "functions": rows,
    }


def markdown(data):
    lines = [
        "# CPUAPP SDK residue batch 5 ownership", "",
        "Eight pinned NCS 2.5.1/Zephyr 3.4.99 configured owners are retained as",
        "separately linkable, CFG-verified C. `FUN_00066e70` is identified as",
        "`pin_init`; its raw public identity remains the reversible address backmap.", "",
        "| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |",
        "|---|---:|---:|---:|---|---|",
    ]
    for row in data["functions"]:
        lines.append("| `{symbol}` | `{va}` | {size} | {reference_count_before} | `{upstream_owner}` | PASS ({checked} checked) |".format(**row))
    lines += ["", "Canonical result: **%d functions / %d prior references**, all digest-pinned and CFG-verified."
              % (data["summary"]["function_count"], data["summary"]["reference_count_before"]), ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    encoded = json.dumps(data, indent=1) + "\n"
    rendered = markdown(data)
    if args.check:
        with open(JSON_OUT, encoding="utf-8") as stream:
            assert stream.read() == encoded
        with open(MD_OUT, encoding="utf-8") as stream:
            assert stream.read() == rendered
        return
    with open(JSON_OUT, "w", encoding="utf-8") as stream:
        stream.write(encoded)
    with open(MD_OUT, "w", encoding="utf-8") as stream:
        stream.write(rendered)


if __name__ == "__main__":
    main()
