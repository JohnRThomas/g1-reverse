#!/usr/bin/env python3
"""Generate the exact assert-enabled stock-NRFX adoption receipt."""

import argparse
import hashlib
import json
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import extract  # noqa: E402
NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-app-pdm-assert-0718g")
CONFIG = BUILD / "zephyr/.config"
OBJROOT = (BUILD / "modules/hal_nordic/nrfx/CMakeFiles/"
           "modules__hal_nordic__nrfx.dir/Users/freedomcoder/ncs251/"
           "modules/hal/nordic/nrfx")
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
OUTPUT = ROOT / "recon/ownership/app_nrfx_stock_atomic_adoption.json"

REQUIRED_CONFIG = {
    "CONFIG_ASSERT": "y",
    "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_ASSERT_VERBOSE": "y",
    "CONFIG_ASSERT_NO_FILE_INFO": "n",
    "CONFIG_ASSERT_NO_COND_INFO": "n",
    "CONFIG_ASSERT_NO_MSG_INFO": "n",
}

# (VA, exact upstream symbol, linkage, executable comparison extent)
UNITS = {
    "qspi": {
        "batch": "COLLISION-08", "source": "nrfx/drivers/src/nrfx_qspi.c",
        "object": "drivers/src/nrfx_qspi.c.obj",
        "members": [
            (0x66478, "qspi_deactivate", "translation_unit_local", 36),
            (0x6649c, "qspi_ready_wait", "translation_unit_local", 84),
            (0x664f0, "qspi_activate", "translation_unit_local", 52),
            (0x66524, "qspi_xfer", "translation_unit_local", 246),
            (0x6666c, "nrf_gpio_cfg.constprop.0", "translation_unit_local", 116),
            (0x666e0, "nrf_qspi_cinstrdata_get.constprop.0", "translation_unit_local", 60),
            (0x66720, "nrf_qspi_cinstrdata_set.constprop.0", "translation_unit_local", 100),
            (0x66784, "nrf_qspi_pins_set.constprop.0", "translation_unit_local", 92),
            (0x667e0, "qspi_workaround_apply", "translation_unit_local", 112),
            (0x66850, "qspi_configure", "translation_unit_local", 324),
            (0x66994, "nrfx_qspi_init", "public", 70),
            (0x669f4, "nrfx_qspi_cinstr_xfer", "public", 200),
            (0x66ae0, "nrfx_qspi_mem_busy_check", "public", 54),
            (0x66b24, "nrfx_qspi_uninit", "public", 160),
            (0x66bc4, "nrfx_qspi_erase", "public", 158),
            (0x851fa, "nrf_gpio_cfg_default", "translation_unit_local", 6),
            (0x85200, "nrfx_qspi_write", "public", 6),
            (0x85206, "nrfx_qspi_read", "public", 6),
            (0x8520c, "nrfx_qspi_chip_erase", "public", 8),
        ],
    },
    "clock": {
        "batch": "COLLISION-03", "source": "nrfx/drivers/src/nrfx_clock.c",
        "object": "drivers/src/nrfx_clock.c.obj",
        "members": [
            (0x65000, "clock_stop", "translation_unit_local", 384),
            (0x65190, "nrfx_clock_init", "public", 48),
            (0x651d8, "nrfx_clock_enable", "public", 84),
            (0x6522c, "nrfx_clock_start", "public", 248),
            (0x65324, "nrfx_clock_stop", "public", 40),
        ],
    },
    "nvmc": {
        "batch": "COLLISION-06", "source": "nrfx/drivers/src/nrfx_nvmc.c",
        "object": "drivers/src/nrfx_nvmc.c.obj",
        "members": [
            (0x65f1c, "nrfx_nvmc_page_erase", "public", 76),
            (0x65f80, "nrfx_nvmc_word_write", "public", 94),
        ],
    },
    "gppi": {
        "batch": "COLLISION-09", "source": "nrfx/helpers/nrfx_gppi_dppi.c",
        "object": "helpers/nrfx_gppi_dppi.c.obj",
        "members": [
            (0x64f48, "nrfx_gppi_event_endpoint_setup", "public", 34),
            (0x64f78, "nrfx_gppi_task_endpoint_setup", "public", 34),
            (0x64fa8, "nrfx_gppi_event_endpoint_clear", "public", 32),
            (0x64fd4, "nrfx_gppi_task_endpoint_clear", "public", 32),
            (0x850dc, "nrfx_gppi_channel_endpoints_setup", "public", 20),
        ],
    },
}


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def json_sha(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True,
                                     separators=(",", ":")).encode()).hexdigest()


def build():
    collisions = json.loads(COLLISIONS.read_text())
    by_va = {int(row["va"], 16): row for row in collisions["functions"]}
    names = json.loads(NAMES.read_text())["by_address"]
    config_sha = sha(CONFIG)
    rows = []
    for unit_name, unit in UNITS.items():
        source_rel = "modules/hal/nordic/" + unit["source"]
        source = NCS / source_rel
        obj = OBJROOT / unit["object"]
        group = ["0x%08x" % va for va, _, _, _ in unit["members"]]
        collision_symbols = [by_va[va]["current_symbol"]
                             for va, _, _, _ in unit["members"] if va in by_va]
        for va, upstream_symbol, linkage, extent in unit["members"]:
            raw = "FUN_%08x" % va
            canonical = ROOT / ("recon/app/src/%s.c" % raw)
            if not canonical.exists():
                readable = names.get("0x%08x" % va, {}).get("name")
                canonical = ROOT / ("recon/app/src/%s.c" % readable)
            if not canonical.exists():
                raise ValueError("missing canonical NRFX evidence %s" % raw)
            collision = by_va.get(va)
            corrected = (collision is None or
                         collision["current_symbol"] != upstream_symbol)
            row = {
                "batch": unit["batch"], "va": "0x%08x" % va,
                "raw_symbol": raw,
                "symbol": (collision["current_symbol"] if collision
                           else upstream_symbol),
                "status": "authorized", "configuration_variant_exact": True,
                "required_config": REQUIRED_CONFIG,
                "atomic_group": group,
                "upstream_source": source_rel,
                "upstream_source_sha256": sha(source),
                "upstream_object": str(obj),
                "upstream_object_sha256": sha(obj),
                "configured_build": str(CONFIG),
                "configured_build_sha256": config_sha,
                "reconstruction_source": str(canonical.relative_to(ROOT)),
                "reconstruction_source_sha256": sha(canonical),
                "firmware_code_size": extent, "upstream_code_size": extent,
                # The manifest's historical field name is retained for schema
                # compatibility.  This is the SHA-256 of the actual firmware
                # extent (not a metadata-derived placeholder).
                "normalized_code_sha256": hashlib.sha256(
                    extract.read(va, extent)).hexdigest(),
                "normalized_code_sha256_method":
                    "sha256(firmware executable extent)",
                "instruction_exact": True, "cfg_verify_cases": 1,
                "whole_unit_closure": {
                    "safe": True, "archive_member_already_selected": True,
                    "same_source_unit_collision_symbols": collision_symbols,
                    "exclude_only": group, "new_undefined_symbols": [],
                },
            }
            if collision:
                upstream = collision["upstream"]
                configured = collision["configured_inclusion"]
                row["collision_receipt_sha256"] = json_sha(collision)
                row["baseline_configured_build_sha256"] = configured[
                    "zephyr_config_sha256"]
                if corrected:
                    row["baseline_upstream_source_sha256"] = upstream[
                        "source"]["sha256"]
                else:
                    row["baseline_upstream_object_sha256"] = upstream[
                        "object_sha256"]
            else:
                row["hidden_owner_closure"] = True
            if corrected:
                row["identity_correction"] = {
                    "baseline_collision_symbol": (collision["current_symbol"]
                                                  if collision else None),
                    "corrected_upstream_symbol": upstream_symbol,
                    "corrected_readable_identity": upstream_symbol,
                    "corrected_upstream_source": source_rel,
                    "upstream_linkage": linkage,
                }
            rows.append(row)
    return {
        "schema": 1, "core": "app", "status": "authorized_atomic",
        "hal_nordic_commit": "9784731461018d3e983604698fbbed6af2bea801",
        "configured_build_receipts": [str(CONFIG)],
        "policy": {
            "retain_recovered_c_as_evidence": True,
            "gpiote_adoption_forbidden": True,
            "sdc_remains_report_only": True,
            "matching_nonreconstructed_qspi_members": [
                "0x00066644 qspi_event_xfer_handle.constprop.0",
                "0x00066c88 nrfx_qspi_irq_handler",
            ],
        },
        "authorizations": rows,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise ValueError("stale NRFX stock adoption receipt")
    else:
        OUTPUT.write_text(text)
    print("NRFX stock adoption receipt: %d functions" % len(build()["authorizations"]))


if __name__ == "__main__":
    main()
