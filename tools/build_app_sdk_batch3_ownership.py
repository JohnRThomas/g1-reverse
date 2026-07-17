#!/usr/bin/env python3
"""Build the fail-closed ownership record for CPUAPP SDK residue batch 3."""

import argparse
import hashlib
import json
import os


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")
JSON_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch3_ownership.json")
MD_OUT = os.path.join(ROOT, "recon/ownership/app_sdk_batch3_ownership.md")

OWNERS = {
    "flash_settings_read": {
        "va": "0x000225b4", "size": 150, "checked": 80,
        "upstream_owner": "G1 application flash-settings wrapper",
        "linkage": "application_function",
        "config": ["device API read callback at +0x1030", "11 attempts", "0x0ccd tick backoff"],
        "sha256": "75d79d28b02cca0a693a59fd8bfe572e063527520e759b843c19376b5f00450e"},
    "atomic_or": {
        "va": "0x00080e6a", "size": 22, "checked": 80,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic_builtin.h:atomic_or",
        "linkage": "header_inline_outlined", "config": ["__ATOMIC_SEQ_CST", "32-bit atomic_t"],
        "sha256": "79ae9d3a44efbddfe4baa8f63352210beab277eec843ee1fb288bf0a713c24eb"},
    "atomic_and_2": {
        "va": "0x000813b4", "size": 22, "checked": 80,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic_builtin.h:atomic_and",
        "linkage": "header_inline_outlined", "config": ["__ATOMIC_SEQ_CST", "32-bit atomic_t"],
        "sha256": "1b42192ea04c30132efc57ad7754f18a755e8f02f093888c746935b1f51758ee"},
    "atomic_or_0": {
        "va": "0x000826e0", "size": 22, "checked": 80,
        "upstream_owner": "zephyr/include/zephyr/sys/atomic_builtin.h:atomic_or",
        "linkage": "header_inline_outlined", "config": ["__ATOMIC_SEQ_CST", "second outlined instance"],
        "sha256": "ce748a407dff28e09c4f0f5d61becbccd1c98fe7d8518f8cfd62c811fa64da86"},
    "qspi_get_zephyr_ret_code": {
        "va": "0x00060990", "size": 24, "checked": 300,
        "upstream_owner": "zephyr/drivers/flash/nrf_qspi_nor.c:qspi_get_zephyr_ret_code",
        "linkage": "source_static_inline_outlined",
        "config": ["nrfx_err_t range 0x0bad0000..0x0bad000a", "firmware error table"],
        "sha256": "3d8d94b198eb762e33fc2f884794eb2e08ef57ffd8198d5753eb7f3d59a069b9"},
    "spim_pin_uninit": {
        "va": "0x00067138", "size": 146, "checked": 300,
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_spim.c:spim_pin_uninit",
        "linkage": "source_static_configured",
        "config": ["NRFX_SPIM_EXTENDED_ENABLED", "PIN_CNF masked to disconnected input"],
        "sha256": "2bea3e5df9626fd85700791fd4dac14d16f8ab48e30247017cf8335e25521833"},
    "qspi_activate": {
        "va": "0x000664f0", "size": 40, "checked": 302,
        "upstream_owner": "modules/hal/nordic/nrfx/drivers/src/nrfx_qspi.c:qspi_activate",
        "linkage": "source_static_configured",
        "config": ["NRFX_QSPI_ACTIVATION_WAIT", "both wait selector cases covered"],
        "sha256": "30f0090799c6dea5409664fa5054daa32228b71967a64610cf4b9537126c0ef7"},
    "print_formatted": {
        "va": "0x0004da6c", "size": 30, "checked": 300,
        "upstream_owner": "zephyr/subsys/logging/log_output.c:print_formatted",
        "linkage": "source_static_configured",
        "config": ["cbvprintf formatter", "log_output callback at 0x0004daad"],
        "sha256": "cedf05addc7a4b523521d75e34dc257ec0ea4a8cd2db56574212680c291abc23"},
}


def digest(path):
    value = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1 << 16), b""):
            value.update(block)
    return value.hexdigest()


def build():
    with open(RESIDUE, encoding="utf-8") as stream:
        references = {row["symbol"]: row for row in json.load(stream)["entries"]}
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
        residue = references.get(symbol)
        if residue is None:
            raise RuntimeError("symbol absent from input residue: %s" % symbol)
        rows.append({
            "symbol": symbol, **owner, "source": source, "verified_mirror": mirror,
            "reference_count_before": residue["reference_count"],
            "reference_sites_before": residue["reference_sites"],
            "verification": "cfg_verify.py app %s: PASS (%d checked)" %
                            (symbol, owner["checked"]),
            "decision": "retain_cfg_verified_configured_reconstruction",
        })
    return {
        "schema": 1, "core": "app",
        "policy": {
            "fail_closed": True,
            "reason": ("Application/static/header-inline identities cannot be supplied by a "
                       "distinct public SDK export; retain their verified configured bodies."),
            "forbid": ["weak stub", "byte blob", "assembly wrapper", "same-name alias guess"],
            "shared_derivatives": "delegated_to_centralized_batch3_batch4_consolidation",
        },
        "summary": {
            "function_count": len(rows),
            "reference_count_before": sum(row["reference_count_before"] for row in rows),
            "cfg_verified": len(rows),
            "application_functions": sum(row["linkage"] == "application_function" for row in rows),
            "configured_sdk_helpers": sum(row["linkage"] != "application_function" for row in rows),
        },
        "functions": rows,
    }


def markdown(data):
    lines = [
        "# CPUAPP SDK residue batch 3 ownership", "",
        "These eight firmware identities retain CFG-verified configured C bodies.",
        "The seven SDK-derived helpers are private/static or outlined header inlines;",
        "`flash_settings_read` is application code and is explicitly reclassified.", "",
        "| Symbol | VA | Bytes | Prior refs | Pinned owner | Decision |",
        "|---|---:|---:|---:|---|---|",
    ]
    for row in data["functions"]:
        lines.append("| `{symbol}` | `{va}` | {size} | {reference_count_before} | "
                     "`{upstream_owner}` | `{decision}` |".format(**row))
    lines += ["", "Coverage: **%d functions / %d prior references**. Shared readable and "
              "link derivatives are intentionally left to centralized batch consolidation."
              % (data["summary"]["function_count"],
                 data["summary"]["reference_count_before"]), ""]
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
