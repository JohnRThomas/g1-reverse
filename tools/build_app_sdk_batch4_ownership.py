#!/usr/bin/env python3
"""Build the fail-closed ownership record for CPUAPP SDK residue batch 4."""

import argparse
import hashlib
import json
import os


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
JSON_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch4_ownership.json")
MD_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch4_ownership.md")

OWNERS = {
    "pin_in_use_by_te": {
        "va": "0x00065460", "size": 20,
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:pin_in_use_by_te",
        "linkage": "source_static", "cfg_cases": 0,
        "config": ["m_cb=0x20002bc0", "pin_flags offset=0x10", "PIN_FLAG_TE_USED=BIT(5)"],
        "sha256": "39ba48d756dfe5aace12df72298d65df415d6bfbcfd9d3ff518d453599d95a35"},
    "pin_is_output": {
        "va": "0x00065494", "size": 20,
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c:pin_is_output",
        "linkage": "source_static", "cfg_cases": 0,
        "config": ["m_cb=0x20002bc0", "pin_flags offset=0x10", "PIN_FLAG_OUTPUT=BIT(1)"],
        "sha256": "ac214f3cfb62e115cad5a2a0812c66efa1284b75225028ab7d86b0db8d417fe9"},
    "nrf_gpio_cfg_sense_set": {
        "va": "0x000851ca", "size": 30,
        "upstream_owner": "modules/hal/nordic/nrfx/hal/nrf_gpio.h:nrf_gpio_cfg_sense_set",
        "linkage": "header_inline_outlined", "cfg_cases": 0,
        "config": ["nrf_gpio_reconfigure specialization", "sense pointer is sixth argument"],
        "sha256": "ee5c187d2113a54afb4fc28bb17d3c127ae9369d05cd65c3fcbe98150485e407"},
    "net_buf_frags_len": {
        "va": "0x00081616", "size": 16,
        "upstream_owner": "zephyr/include/zephyr/net/buf.h:net_buf_frags_len",
        "linkage": "header_inline_outlined", "cfg_cases": 2,
        "config": ["32-bit net_buf ABI", "frags offset=4", "len offset=16"],
        "sha256": "2ae98afc586b178a1b5d31f47eaca0b37fe30b92dcfc7fcdd10e9709f9a88ecb"},
    "k_uptime_get_6": {
        "va": "0x0007d33a", "size": 28,
        "upstream_owner": "zephyr/include/zephyr/kernel.h:k_uptime_get",
        "linkage": "header_inline_outlined", "cfg_cases": 0,
        "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768", "uptime_ticks_get=FUN_00086698"],
        "sha256": "76b55333569b558ecb5e254ab6683cc56bb73cdba8da5654e6e2f011ecb079f7"},
    "k_uptime_get_8": {
        "va": "0x0007d382", "size": 28,
        "upstream_owner": "zephyr/include/zephyr/kernel.h:k_uptime_get",
        "linkage": "header_inline_outlined", "cfg_cases": 0,
        "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768", "uptime_ticks_get=FUN_00086698"],
        "sha256": "c6450f97ddbc3e8bd543894ccb249586da184d39369b16de9ae86c140c6a1e59"},
    "k_uptime_get_9": {
        "va": "0x0007d9a4", "size": 28,
        "upstream_owner": "zephyr/include/zephyr/kernel.h:k_uptime_get",
        "linkage": "header_inline_outlined", "cfg_cases": 0,
        "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768", "uptime_ticks_get=FUN_00086698"],
        "sha256": "b4fecedce060027c9c8679a3757310b8bc35cd28eae3550e2ca6c5a448b9ebbf"},
    "k_uptime_get_10": {
        "va": "0x0007daa4", "size": 28,
        "upstream_owner": "zephyr/include/zephyr/kernel.h:k_uptime_get",
        "linkage": "header_inline_outlined", "cfg_cases": 0,
        "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768", "uptime_ticks_get=FUN_00086698"],
        "sha256": "0c9e6343d425af038e7466e82627d845933edbcdbd9881d8619aaff2c6966eff"},
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
        actual = digest(source_path)
        if actual != owner["sha256"] or digest(mirror_path) != actual:
            raise RuntimeError("unverified source or mirror drift: %s" % symbol)
        residue_row = references.get(symbol)
        if residue_row is None or residue_row["reference_count"] != 5:
            raise RuntimeError("unexpected input residue for %s" % symbol)
        rows.append({
            "symbol": symbol, **owner, "source": source, "verified_mirror": mirror,
            "reference_count_before": residue_row["reference_count"],
            "reference_sites_before": residue_row["reference_sites"],
            "verification": "cfg_verify.py app %s: PASS (CFG cases=%d, random=40)" %
                            (symbol, owner["cfg_cases"]),
            "decision": "retain_cfg_verified_configured_reconstruction",
        })
    return {
        "schema": 1, "core": "app",
        "policy": {
            "fail_closed": True,
            "reason": "Pinned static/header-inline SDK owners require separately linkable configured bodies.",
            "forbid": ["weak stub", "byte blob", "assembly wrapper", "same-name alias guess"],
        },
        "summary": {
            "function_count": len(rows),
            "reference_count_before": sum(row["reference_count_before"] for row in rows),
            "cfg_verified": len(rows),
            "canonical_strong_owner_count": len(rows),
        },
        "integration": {
            "derivatives": "pending centralized batch3+batch4 readable-tree consolidation",
            "retain_all_result": "not claimed by this canonical-only milestone",
        },
        "functions": rows,
    }


def markdown(data):
    lines = [
        "# CPUAPP SDK residue batch 4 ownership", "",
        "Eight pinned NCS 2.5.1/Zephyr 3.4.99 static or header-inline owners are",
        "retained as separately linkable, CFG-verified configured C bodies. Raw identities",
        "remain in each source as address backmaps. Derivative integration is deliberately",
        "left to the centralized batch 3+4 consolidation.", "",
        "| Symbol | VA | Bytes | Prior refs | Pinned owner | CFG |", "|---|---:|---:|---:|---|---|",
    ]
    for row in data["functions"]:
        lines.append("| `{symbol}` | `{va}` | {size} | {reference_count_before} | `{upstream_owner}` | PASS ({cfg_cases}+40) |".format(**row))
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
