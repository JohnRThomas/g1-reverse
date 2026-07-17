#!/usr/bin/env python3
"""Build the fail-closed ownership record for five CPUAPP SDK residues."""

import argparse
import hashlib
import json
import os


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
JSON_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch2_ownership.json")
MD_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch2_ownership.md")

# Digests are deliberately pinned.  Changing a configured reconstruction must
# invalidate this catalog until it has been run through cfg_verify again.
OWNERS = {
    "bt_addr_le_eq_0": {
        "va": "0x000826b2", "size": 16,
        "upstream_owner": "zephyr/include/zephyr/bluetooth/addr.h:bt_addr_le_eq",
        "linkage": "header_inline", "config": ["bt_addr_le_cmp length=7"],
        "sha256": "653ba5b2da449a2dc3ff50dab34c9f08dd5963282fdb3d3ac9f711027166ac62"},
    "get_pin_idx": {
        "va": "0x00065434", "size": 16,
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:get_pin_idx",
        "linkage": "source_static", "config": ["FULL_PORTS_PRESENT=0", "port_offset=0x000f6ba7"],
        "sha256": "049cd7fd3d8f9b6ab353d9fcf9206ef76a7f53eddafe9118dfe2e6054d9ef741"},
    "__nrfy_internal_twim_events_process": {
        "va": "0x0008539a", "size": 84,
        "upstream_owner": "modules/hal/nordic/nrfx/haly/nrfy_twim.h:__nrfy_internal_twim_events_process",
        "linkage": "header_inline_outlined", "config": ["p_xfer specialized away", "7 event handlers"],
        "sha256": "b42137f9f23a41b3fab860c08a1f2725eea36bf4a2eb436bd159fe191270f217"},
    "k_uptime_get_1": {
        "va": "0x0007cb2c", "size": 28,
        "upstream_owner": "zephyr/include/zephyr/kernel.h:k_uptime_get",
        "linkage": "header_inline_outlined", "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768"],
        "sha256": "57fa41adf0a126cade6e4e132d274aa26820a4e26ded9fd53f25e06448873e9a"},
    "smp_create_pdu": {
        "va": "0x000830b0", "size": 62,
        "upstream_owner": "zephyr/subsys/bluetooth/host/smp.c:smp_create_pdu",
        "linkage": "source_static", "config": ["CONFIG_BT=y", "CONFIG_BT_SMP=y", "unused len specialized away"],
        "sha256": "ac44ae2cc6d92aa93694b03148c6a1614da08816428d0ec41d335ff9f41ec3be"},
}

DEPENDENCIES = {
    "__nrfy_internal_twim_event_handle": {
        "va": "0x00085378", "size": 34,
        "upstream_owner": "modules/hal/nordic/nrfx/haly/nrfy_twim.h:__nrfy_internal_twim_event_handle",
        "linkage": "header_inline_outlined",
        "config": ["TWIM event register offsets", "corrects prior cross-peripheral PWM label"],
        "sha256": "e67d4759faa3d4d0d2c8dff072d0ea894f13939d94cb0b3de94047ce76f7bb6f"},
}


def digest(path):
    with open(path, "rb") as stream:
        return hashlib.sha256(stream.read()).hexdigest()


def build():
    with open(RESIDUE, encoding="utf-8") as stream:
        residue = json.load(stream)
    references = {row["symbol"]: row for row in residue["entries"]}
    rows = []
    for symbol, owner in OWNERS.items():
        source = "recon/app/src/%s.c" % symbol
        mirror = "recon/verified/src/%s.c" % symbol
        source_path = os.path.join(ROOT, source)
        mirror_path = os.path.join(ROOT, mirror)
        if not os.path.exists(source_path) or not os.path.exists(mirror_path):
            raise RuntimeError("missing configured reconstruction: %s" % symbol)
        actual = digest(source_path)
        if actual != owner["sha256"] or digest(mirror_path) != actual:
            raise RuntimeError("unverified source drift: %s" % symbol)
        residue_row = references.get(symbol)
        if residue_row is None:
            raise RuntimeError("symbol absent from input residue: %s" % symbol)
        rows.append({
            "symbol": symbol, **owner, "source": source, "verified_mirror": mirror,
            "reference_count_before": residue_row["reference_count"],
            "reference_sites_before": residue_row["reference_sites"],
            "reference_count_after_retain_all": 0,
            "strong_owner_count_after_retain_all": 1,
            "verification": "cfg_verify.py app %s: PASS (40 checked)" % symbol,
            "decision": "retain_cfg_verified_configured_reconstruction",
        })
    dependencies = []
    for symbol, owner in DEPENDENCIES.items():
        source = "recon/app/src/%s.c" % symbol
        mirror = "recon/verified/src/%s.c" % symbol
        actual = digest(os.path.join(ROOT, source))
        if actual != owner["sha256"] or digest(os.path.join(ROOT, mirror)) != actual:
            raise RuntimeError("unverified dependency source drift: %s" % symbol)
        dependencies.append({
            "symbol": symbol, **owner, "source": source, "verified_mirror": mirror,
            "verification": "cfg_verify.py app %s: PASS (40 checked)" % symbol,
            "decision": "retain_cfg_verified_configured_dependency",
        })
    return {
        "schema": 1, "core": "app",
        "policy": {
            "fail_closed": True,
            "reason": "Static/header-inline owners are not externally bindable from their SDK translation units.",
            "forbid": ["weak stub", "byte blob", "assembly wrapper", "same-name alias guess"],
        },
        "summary": {
            "function_count": len(rows),
            "reference_count_before": sum(row["reference_count_before"] for row in rows),
            "reference_count_after_retain_all": 0,
            "resolved_reference_delta": sum(row["reference_count_before"] for row in rows),
            "cfg_verified": len(rows),
            "dependency_count": len(dependencies),
        },
        "build_verification": {
            "retain_all_build": "/private/tmp/g1_cpuapp_shell_build_0717j",
            "result": "expected aggregate residue remains; all six configured objects compiled",
            "target_symbols_undefined": [],
            "target_symbols_duplicate": [],
            "full_link": "2915/2915 objects compiled; partial link rc=0",
            "global_residue_before_unique": 192,
            "global_residue_after_unique": 185,
            "note": "The exact batch delta is 46 references across five symbols; the global unique delta also includes concurrent reviewed integrations.",
        },
        "functions": rows, "dependencies": dependencies,
    }


def markdown(data):
    lines = [
        "# CPUAPP SDK residue batch 2 ownership", "",
        "All five configured bodies are retained reconstructions of pinned NCS 2.5.1",
        "static or header-inline owners. Each body is digest-pinned and CFG-verified;",
        "the catalog generator fails on source or verified-mirror drift.", "",
        "| Symbol | VA | Bytes | Prior refs | Pinned owner | Decision |", "|---|---:|---:|---:|---|---|",
    ]
    for row in data["functions"]:
        lines.append("| `{symbol}` | `{va}` | {size} | {reference_count_before} | `{upstream_owner}` | `{decision}` |".format(**row))
    lines += ["", "Configured dependency:", ""]
    for row in data["dependencies"]:
        lines.append("- `{symbol}` at `{va}` ({size} bytes): `{upstream_owner}`; `{decision}`.".format(**row))
    lines += ["", "Retain-all result: **%d -> %d** target references; one strong owner per target, no target duplicates."
              % (data["summary"]["reference_count_before"],
                 data["summary"]["reference_count_after_retain_all"]), ""]
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
