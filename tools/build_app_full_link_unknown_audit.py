#!/usr/bin/env python3
"""Build the fail-closed audit of CPUAPP full_link UNKNOWN symbols."""

# Resolvable pipeline scratchpad (tools/g1_paths.py).  This used to be one
# literal /private/tmp path belonging to a finished agent session; see that
# module for the resolution order and the fail-closed catalog fallback.
import os as _g1_os, sys as _g1_sys
_G1_TOOLS = _g1_os.path.dirname(_g1_os.path.abspath(__file__))
if _g1_os.path.basename(_G1_TOOLS) != "tools":
    _G1_TOOLS = _g1_os.path.dirname(_G1_TOOLS)
if _G1_TOOLS not in _g1_sys.path:
    _g1_sys.path.insert(0, _G1_TOOLS)
import g1_paths as _g1_paths

import argparse
import collections
import hashlib
import json
import os
import re
from pathlib import Path


BASE = "/Users/freedomcoder/Projects/G1disasm2"
SCRATCH_REPORT = (_g1_paths.scratchpad() + '/fulllink_app.json')
DEFAULT_JSON = BASE + "/recon/catalogs/app_full_link_unknown_audit.json"
DEFAULT_MD = BASE + "/recon/catalogs/app_full_link_unknown_audit.md"
RETAINED = BASE + "/recon/generated/app_retained_sources.cmake"

BLOCKED = set()
PSEUDO = {"thunk_FUN_00086c78"}
DUPLICATE = {
    "FUN_0004c4e4", "FUN_00051c38", "FUN_0007a3a4", "FUN_0007e53e", "FUN_0007e574",
    "FUN_0007e5da", "FUN_0007e624", "FUN_0007e672", "FUN_0007e6e2",
    "FUN_0007e776", "FUN_0007e7ea", "FUN_0007e83a", "_ctype_",
    "_double_byte", "cc_mbedtls_ctr_drbg_random_with_add", "ceilf",
    "encode_uint", "getTrngSource", "hex2bin", "mbedtls_zeroize_internal",
    "outs", "rpmsg_deinit_vdev", "rpmsg_send_offchannel_raw",
    "tc_aes128_set_encrypt_key", "tc_aes_encrypt", "FUN_00080a46",
}
EXTERNAL = {
    "__strcat_chk", "__strcpy_chk", "__swsetup_r", "_strtod_l",
    "cbpprintf_external", "conn_lookup_handle", "floorf", "fmaf",
    "get_adv_name_type_param", "ipc_service_send", "ipc_static_vrings_init",
    "is_ptr", "metal_bus_find", "metal_io_block_set", "metal_io_block_write",
    "mpsc_pbuf_is_pending", "onoff_manager_init", "pinctrl_lookup_state",
    "rpmsg_create_ept", "rpmsg_get_endpoint", "rpmsg_register_endpoint",
    "rpmsg_virtio_init_shm_pool", "rpmsg_virtio_shm_pool_get_buffer",
    "snprintk", "tc_cmac_setup", "tc_hmac_prng_init", "tc_hmac_prng_reseed",
    "u8_to_dec", "virtio_create_virtqueues", "virtqueue_add_buffer",
    "virtqueue_get_buffer", "virtqueue_get_buffer_length",
}

CALLERS = {
    "FUN_0004c4e4": ["nvs_mount"],
    "FUN_00051c38": ["img_mgmt_get_next_boot_slot"],
    "FUN_0007a3a4": ["FUN_0007a2b8"],
    "FUN_0007e53e": ["nvs_mount", "nvs_read_hist"],
    "FUN_0007e574": ["nvs_write"], "FUN_0007e5da": ["nvs_mount"],
    "FUN_0007e624": ["nvs_mount"],
    "FUN_0007e672": ["nvs_mount", "nvs_read_hist", "nvs_write"],
    "FUN_0007e6e2": ["nvs_read_hist", "nvs_write"],
    "FUN_0007e776": ["nvs_write"], "FUN_0007e7ea": ["nvs_write"],
    "FUN_0007e83a": ["nvs_mount", "nvs_write"],
    "FUN_00080a46": ["img_mgmt_get_next_boot_slot"],
    "__strcat_chk": ["local_store_write"],
    "__strcpy_chk": ["bt_start", "spec_ble_command_hook"],
    "__swsetup_r": ["__swbuf_r"], "_ctype_": ["z_cbvprintf_impl"],
    "_double_byte": ["mult_row_column_0"], "_strtod_l": ["FUN_00077a10"],
    "cbpprintf_external": ["FUN_0004db04"],
    "cc_mbedtls_ctr_drbg_random_with_add": ["FUN_00079668"],
    "ceilf": ["lc3_spec_analyze"], "conn_lookup_handle": ["ble_conn_lookup_masked"],
    "encode_uint": ["z_cbvprintf_impl"],
    "floorf": ["FUN_000868fc", "lc3_sns_analyze"],
    "fmaf": ["FUN_00075f88", "curve_table_interp_201pt", "lc3_mdct_fft",
             "lc3_sns_analyze", "log2f", "logf_core"],
    "getTrngSource": ["LLF_RND_GetTrngSource"],
    "get_adv_name_type_param": ["ble_conn_le_prepare_and_connect"],
    "hex2bin": ["bt_settings_decode_key"],
    "ipc_service_send": ["global_ipc_service_send"],
    "ipc_static_vrings_init": ["FUN_0004cd4c"], "is_ptr": ["FUN_0004abc0"],
    "mbedtls_zeroize_internal": ["FUN_0007abe8"],
    "metal_bus_find": ["FUN_00068170", "metal_device_open"],
    "metal_io_block_set": ["rpmsg_virtqueue_channel_init"],
    "metal_io_block_write": ["FUN_000710b4", "FUN_00071294"],
    "mpsc_pbuf_is_pending": ["z_log_msg_pending"],
    "onoff_manager_init": ["FUN_0006058c"], "outs": ["z_cbvprintf_impl"],
    "pinctrl_lookup_state": ["FUN_000838dc", "FUN_00083cde", "FUN_00084b14"],
    "rpmsg_create_ept": ["FUN_0004d0c4"], "rpmsg_deinit_vdev": ["ipc_rpmsg_deinit"],
    "rpmsg_get_endpoint": ["FUN_0007118c"],
    "rpmsg_register_endpoint": ["rpmsg_virtqueue_channel_init"],
    "rpmsg_send_offchannel_raw": ["rpmsg_send_ns_message"],
    "rpmsg_virtio_init_shm_pool": ["FUN_0004d100"],
    "rpmsg_virtio_shm_pool_get_buffer": ["FUN_00085b0c", "rpmsg_virtqueue_channel_init"],
    "snprintk": ["att_timeout", "bt_settings_delete", "bt_settings_encode_key",
                 "bt_settings_store", "format_bt_addr_str", "log_output_dropped_process", "random"],
    "tc_aes128_set_encrypt_key": ["bt_encrypt_le"], "tc_aes_encrypt": ["bt_encrypt_le"],
    "tc_cmac_setup": ["gatt_db_hash_gen"],
    "tc_hmac_prng_init": ["ble_rng_get_random_bytes"],
    "tc_hmac_prng_reseed": ["ble_rng_seed_from_uptime"],
    "thunk_FUN_00086c78": ["FUN_0007ab20"],
    "u8_to_dec": ["bt_gatt_connected", "bt_settings_delete", "bt_settings_store"],
    "virtio_create_virtqueues": ["rpmsg_virtqueue_channel_init"],
    "virtqueue_add_buffer": ["FUN_000710b4", "FUN_0007118c", "FUN_00085a9c",
                             "rpmsg_virtqueue_channel_init"],
    "virtqueue_get_buffer": ["FUN_0007118c", "FUN_00085b0c"],
    "virtqueue_get_buffer_length": ["FUN_000710b4", "FUN_00085a9c"],
}

TOOLCHAIN = {"__strcat_chk", "__strcpy_chk", "__swsetup_r", "_strtod_l",
             "floorf", "fmaf"}
BT_HOST = {"conn_lookup_handle", "get_adv_name_type_param"}
LIBMETAL = {"metal_bus_find", "metal_io_block_set", "metal_io_block_write"}
OPENAMP = {"rpmsg_create_ept", "rpmsg_get_endpoint", "rpmsg_register_endpoint",
           "rpmsg_virtio_init_shm_pool", "rpmsg_virtio_shm_pool_get_buffer",
           "virtio_create_virtqueues", "virtqueue_add_buffer", "virtqueue_get_buffer",
           "virtqueue_get_buffer_length"}
COMPILER_EXPANDED_REFERENCES = {"_ctype_", "__strcat_chk", "__strcpy_chk"}


def provider(symbol):
    if symbol in TOOLCHAIN:
        return "zephyr-sdk-0.16.5-1:newlib-nano/libm:v8-m.main+fp/hard"
    if symbol in BT_HOST:
        return "NCS-2.5.1:subsys/bluetooth/host"
    if symbol in LIBMETAL:
        return "NCS-2.5.1:modules/libmetal"
    if symbol in OPENAMP:
        return "NCS-2.5.1:modules/open-amp"
    if symbol == "pinctrl_lookup_state":
        return "NCS-2.5.1:drivers/pinctrl"
    return "NCS-2.5.1:zephyr/libzephyr.a"


def build():
    classes = BLOCKED | PSEUDO | DUPLICATE | EXTERNAL
    if len(classes) != 59 or set(CALLERS) != classes:
        raise ValueError("classification/caller partition is not exactly 59 symbols")
    scratch_sha = None
    if os.path.exists(SCRATCH_REPORT):
        raw = Path(SCRATCH_REPORT).read_bytes()
        scratch_sha = hashlib.sha256(raw).hexdigest()
        current = set(json.loads(raw)["unknown"])
        if current != classes:
            raise ValueError("current fulllink_app UNKNOWN set differs from pinned audit")
    retained_text = Path(RETAINED).read_text()
    retained = set(re.findall(r"/([^/]+)\.c(?:\s|\")", retained_text))
    provided = set()
    for path in Path(BASE + "/recon/symbols").glob("g1_app_*.ld"):
        provided.update(re.findall(r"PROVIDE\(([^\s=)]+)", path.read_text()))
    pinned_unknown = classes & provided
    if pinned_unknown:
        raise ValueError("UNKNOWN symbols already pinned/aliased: %s" %
                         sorted(pinned_unknown))
    names = json.loads(Path(BASE +
        "/recon/catalogs/function_names_app.json").read_text())
    if names["by_address"]["0x00086c78"]["name"] != "memset_bytes":
        raise ValueError("pseudo thunk target mapping changed")
    rows = []
    source_text = {path.stem: path.read_text(errors="replace")
                   for path in Path(BASE + "/recon/symbolized/app").glob("*.c")}
    for symbol in sorted(classes):
        resolved_hints = []
        for caller in CALLERS[symbol]:
            resolved = caller
            match = re.fullmatch(r"FUN_([0-9a-fA-F]{8})", caller)
            if match:
                identity = names["by_address"].get("0x" + match.group(1).lower())
                if identity:
                    resolved = identity["name"]
            resolved_hints.append(resolved)
        callers = sorted(stem for stem, text in source_text.items()
                         if re.search(r"\b%s\b" % re.escape(symbol), text))
        if symbol in COMPILER_EXPANDED_REFERENCES:
            callers = sorted(set(callers) |
                             {name for name in resolved_hints if name in source_text})
        retained_callers = sorted(set(callers) & retained)
        if symbol in BLOCKED:
            category = "blocked_interior"
            evidence = "app_interior_alias_audit:blocked_embedded_noreturn_svc_island"
        elif symbol in PSEUDO:
            category = "ghidra_compiler_pseudo"
            evidence = "excluded CC312 caller; thunk spelling targets mapped memset_bytes VA"
        elif retained_callers:
            category = "genuine_sdk_library_external"
            evidence = provider(symbol)
        else:
            category = "duplicate_owner_byproduct"
            evidence = "all referencing reconstruction objects excluded from retained build"
        rows.append({"symbol": symbol, "category": category, "callers": callers,
                     "retained_callers": retained_callers, "evidence": evidence,
                     "action": "report_only"})
    counts = collections.Counter(row["category"] for row in rows)
    return {"schema": 2, "core": "app", "source_commit": "readable-alias-resolution",
            "source": {"full_link_report": SCRATCH_REPORT,
                       "full_link_report_sha256": scratch_sha,
                       "retain_all_link_log": "/private/tmp/g1-app-residue-current-0718/link-final-regenerated.log",
                       "retain_all_duplicate_diagnostics": 112},
            "summary": {"symbols": len(rows), "by_category": dict(sorted(counts.items())),
                        "actionable_gaps": 0,
                        "pinned_data_globals": len(pinned_unknown)},
            "entries": rows}


def markdown(data):
    lines = ["# CPUAPP full-link UNKNOWN audit", "",
             "Pinned to the current full-link report after readable back-map resolution;",
             "report-only classification, no function-body substitutions.", "",
             "| Symbol | Category | Retained callers | Evidence |", "|---|---|---|---|"]
    for row in data["entries"]:
        lines.append("| `%s` | `%s` | `%s` | %s |" %
                     (row["symbol"], row["category"], ", ".join(row["retained_callers"]),
                      row["evidence"]))
    lines += ["", "Actionable gaps: **0**.", ""]
    return "\n".join(lines)


def write(path, content, check):
    old = Path(path).read_text() if os.path.exists(path) else None
    if check:
        if old != content:
            raise ValueError("stale output: " + path)
    elif old != content:
        with open(path, "w") as stream:
            stream.write(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    write(DEFAULT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    write(DEFAULT_MD, markdown(data), args.check)
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
