#!/usr/bin/env python3
"""Build the durable CPUAPP SDK/config residue ownership catalog.

The input classification is intentionally not trusted as an ownership verdict.
This tool resolves its 173 ``sdk_or_config_symbol`` rows against the exact
CPUAPP shell archives, GCC/newlib-nano multilibs, and pinned NCS source units.
It is report-only and never edits reconstruction or build inputs.
"""

import argparse
import collections
import hashlib
import json
import os
import re
import subprocess


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NCS = "/Users/freedomcoder/ncs251"
SDK = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi"
BUILD = "/private/tmp/g1_cpuapp_shell_build_0717j"
NM = os.path.join(SDK, "bin/arm-zephyr-eabi-nm")
LIBGCC = os.path.join(
    SDK, "lib/gcc/arm-zephyr-eabi/12.2.0/thumb/v8-m.main+fp/hard/libgcc.a")
LIBC = os.path.join(
    SDK, "arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a")
CC312 = os.path.join(
    NCS, "nrfxlib/crypto/nrf_cc312_platform/lib/cortex-m33/hard-float/"
         "libnrf_cc312_platform_0.9.18.a")

CUSTOM_APPLICATION = {
    "adc_nfc_init", "adc_nfc_run", "bt_start", "flash_settings_read",
    "flash_settings_write_and_verify", "get_display_atomic_state",
    "log_message",
}

EXPLICIT_OWNERS = {
    "__nrfy_internal_twim_events_process": {
        "source": "modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_NRFX_TWIM=y"]},
    "gatt_req_send": {
        "source": "zephyr/subsys/bluetooth/host/gatt.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_BT=y"]},
    "is_tx_ready": {
        "source": "zephyr/drivers/serial/uart_nrfx_uarte.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_SERIAL=y", "CONFIG_UART_NRFX=y"]},
    "k_msleep_ticks32768_a": {
        "owner": "k_msleep", "source": "zephyr/include/zephyr/kernel.h",
        "kind": "header_inline", "action": "reconcile_inline_at_callsite",
        "config": ["CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768"]},
    "nrf_qspi_cinstrdata_get": {
        "source": "modules/hal/nordic/nrfx/hal/nrf_qspi.h",
        "kind": "header_inline", "action": "reconcile_inline_at_callsite",
        "config": ["CONFIG_NRFX_QSPI=y"]},
    "nrf_qspi_cinstrdata_set": {
        "source": "modules/hal/nordic/nrfx/hal/nrf_qspi.h",
        "kind": "header_inline", "action": "reconcile_inline_at_callsite",
        "config": ["CONFIG_NRFX_QSPI=y"]},
    "nrf_qspi_pins_set": {
        "source": "modules/hal/nordic/nrfx/hal/nrf_qspi.h",
        "kind": "header_inline", "action": "reconcile_inline_at_callsite",
        "config": ["CONFIG_NRFX_QSPI=y"]},
    "nvs_al_size": {
        "source": "zephyr/subsys/fs/nvs/nvs.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_NVS=y"]},
    "qspi_rdsr": {
        "source": "zephyr/drivers/flash/nrf_qspi_nor.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_NORDIC_QSPI_NOR=y"]},
    "smp_create_pdu": {
        "source": "zephyr/subsys/bluetooth/host/smp.c",
        "kind": "source_local", "action": "adopt_complete_source_unit",
        "config": ["CONFIG_BT=y", "CONFIG_BT_SMP=y"]},
    "z_fdtable_call_ioctl": {
        "source": "zephyr/include/zephyr/sys/fdtable.h",
        "kind": "header_inline", "action": "reconcile_inline_at_callsite",
        "config": ["CONFIG_POSIX_API=y"]},
}

INLINE_HEADERS = {
    "atomic": "zephyr/include/zephyr/sys/atomic.h",
    "atomic_get": "zephyr/include/zephyr/sys/atomic_builtin.h",
    "bt_addr_le_eq": "zephyr/include/zephyr/bluetooth/addr.h",
    "bt_gatt_foreach_attr": "zephyr/include/zephyr/bluetooth/gatt.h",
    "k_msleep": "zephyr/include/zephyr/kernel.h",
    "k_uptime_get": "zephyr/include/zephyr/kernel.h",
    "k_uptime_get_32": "zephyr/include/zephyr/kernel.h",
    "net_buf_frags_len": "zephyr/include/zephyr/net/buf.h",
    "sys_slist_find_and_remove": "zephyr/include/zephyr/sys/slist.h",
}


def load(path):
    with open(path, encoding="utf-8") as stream:
        return json.load(stream)


def relative(path):
    if path.startswith(NCS + os.sep):
        return os.path.relpath(path, NCS)
    if path.startswith(ROOT + os.sep):
        return os.path.relpath(path, ROOT)
    return path


def semantic_owner(row):
    for identity in row.get("identities", []):
        signature = identity.get("library_signature")
        if signature:
            return signature["name"], signature.get("ratio")
    symbol = row["symbol"]
    if symbol == "FUN_0007c18e":
        return "k_uptime_get", None
    if symbol == "strtoll_internal":
        return "_strtoll_l.constprop.0", None
    if symbol == "z_log_dropped_read_and_clear_0":
        return "z_log_dropped_read_and_clear", None
    # Decompiler disambiguators are not part of the C identifier.  Preserve
    # genuine API suffixes such as k_uptime_get_32.
    match = re.match(r"(.+)_([0-9]+)$", symbol)
    if match and symbol not in {"k_uptime_get_32"}:
        base = match.group(1)
        if (base.startswith("atomic_") or base in {
                "bt_addr_le_eq", "bt_gatt_foreach_attr", "k_uptime_get",
                "net_buf_frags_len", "sys_slist_find_and_remove"}):
            return base, None
    return symbol, None


def archives(build):
    found = []
    for directory, _dirs, files in os.walk(build):
        for filename in files:
            if filename.endswith(".a") and "/hci_rpmsg/" not in directory:
                found.append(os.path.join(directory, filename))
    found.extend([LIBGCC, LIBC, CC312])
    return sorted(dict.fromkeys(path for path in found if os.path.exists(path)))


def nm_index(paths):
    index = collections.defaultdict(list)
    for archive in paths:
        result = subprocess.run(
            [NM, "-A", "--defined-only", archive], text=True,
            stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, check=False)
        if result.returncode:
            continue
        for line in result.stdout.splitlines():
            # archive:member:address TYPE symbol
            match = re.match(r"(.+):([^:]+):([0-9a-fA-F]+)\s+([A-Za-z])\s+(.+)$", line)
            if not match:
                continue
            archive_path, member, _address, kind, symbol = match.groups()
            index[symbol].append({
                "archive": relative(archive_path),
                "member": member,
                "nm_type": kind,
                "linkage": "public" if kind.isupper() else "local",
            })
    return index


def compile_sources(build):
    path = os.path.join(build, "compile_commands.json")
    result = collections.defaultdict(list)
    if not os.path.exists(path):
        return result
    for command in load(path):
        output = command.get("output", "")
        member = os.path.basename(output)
        if member:
            result[member].append(relative(command["file"]))
    return result


def pick_hit(hits):
    if not hits:
        return None
    # Prefer the actual shell over standalone vendor archives, and the app
    # core over child-image objects.  Ties are stable and deterministic.
    return sorted(hits, key=lambda hit: (
        0 if hit["archive"].startswith(BUILD) else 1,
        hit["archive"], hit["member"]))[0]


def source_for(hit, source_index):
    if not hit:
        return None
    candidates = source_index.get(hit["member"], [])
    if not candidates:
        return None
    archive = hit["archive"]
    tokens = set(re.split(r"[/_.]+", archive))
    return sorted(candidates, key=lambda source: (
        -sum(token in source for token in tokens if len(token) > 3), source))[0]


def inline_header(owner):
    if owner.startswith("atomic_"):
        if owner in {"atomic_and", "atomic_or", "atomic_set", "atomic_get"}:
            return INLINE_HEADERS.get(owner, INLINE_HEADERS["atomic_get"])
        return INLINE_HEADERS["atomic"]
    return INLINE_HEADERS.get(owner)


def configs(source, owner):
    source = source or ""
    if "subsys/bluetooth/host" in source:
        values = ["CONFIG_BT=y"]
        if "smp.c" in source:
            values.append("CONFIG_BT_SMP=y")
        return values
    if "gatt_dm" in source:
        return ["CONFIG_BT=y", "CONFIG_BT_GATT_DM=y"]
    if "ancs_client" in source:
        return ["CONFIG_BT=y", "CONFIG_BT_ANCS_CLIENT=y"]
    if "/nvs/" in source or owner.startswith("nvs_"):
        return ["CONFIG_NVS=y"]
    if "logging/" in source or "log_" in source:
        return ["CONFIG_LOG=y"]
    if "nrfx_qspi" in source:
        return ["CONFIG_NRFX_QSPI=y"]
    if "nrfx_spim" in source:
        return ["CONFIG_NRFX_SPIM=y"]
    if "nrfx_twim" in source:
        return ["CONFIG_NRFX_TWIM=y"]
    if "open-amp" in source:
        return ["CONFIG_OPENAMP=y"]
    if "libmetal" in source:
        return ["CONFIG_LIBMETAL=y"]
    if "ipc_service" in source:
        return ["CONFIG_IPC_SERVICE=y"]
    if "nrf_cc312" in source or "cc312" in source or owner.startswith("nrf_cc3xx"):
        return ["CONFIG_NRF_CC3XX_PLATFORM=y", "CONFIG_FPU=y"]
    if source in (LIBC, relative(LIBC)) or owner in {
            "memcmp", "memmove", "strncmp", "strstr", "__strcat_chk",
            "__strcpy_chk", "_strtoll_l.constprop.0"}:
        return ["CONFIG_NEWLIB_LIBC=y", "CONFIG_NEWLIB_LIBC_NANO=y"]
    if source == LIBGCC or "libgcc.a" in source:
        return ["GCC 12.2.0 cortex-m33 hard-float multilib"]
    if source.startswith("firmware application identity"):
        return ["not applicable: firmware application owner, not SDK/config"]
    if "atomic" in source:
        return ["GCC __atomic builtins via Zephyr atomic_builtin.h"]
    if "kernel/" in source:
        if "timer.c" in source or "poll.c" in source or "timeout.c" in source:
            return ["CONFIG_MULTITHREADING=y", "CONFIG_SYS_CLOCK_EXISTS=y"]
        return ["CONFIG_MULTITHREADING=y"]
    if "/heap" in source:
        return ["CONFIG_HEAP_MEM_POOL_SIZE=16384"]
    if "cbprintf_complete.c" in source:
        return ["CONFIG_CBPRINTF_COMPLETE=y"]
    if "mpsc_pbuf.c" in source or "onoff.c" in source:
        return ["Zephyr core utility unit (no independent Kconfig gate)"]
    if "arm_mpu.c" in source:
        return ["CONFIG_ARM_MPU=y", "CONFIG_MPU=y"]
    if "nrfx_gpiote.c" in source:
        return ["CONFIG_GPIO=y", "CONFIG_NRFX_GPIOTE=y"]
    if "nrfx_nvmc.c" in source:
        return ["CONFIG_FLASH=y", "CONFIG_NRFX_NVMC=y"]
    if "nrf_qspi_nor.c" in source:
        return ["CONFIG_FLASH=y", "CONFIG_NORDIC_QSPI_NOR=y"]
    if "uart_nrfx_uarte.c" in source:
        return ["CONFIG_SERIAL=y", "CONFIG_UART_NRFX=y"]
    if "bluetooth/crypto" in source:
        return ["CONFIG_BT=y", "CONFIG_BT_HOST_CRYPTO=y"]
    if "bluetooth/addr.h" in source or "bluetooth/gatt.h" in source:
        return ["CONFIG_BT=y"]
    if "kernel.h" in source:
        return ["CONFIG_MULTITHREADING=y", "CONFIG_SYS_CLOCK_EXISTS=y"]
    if "net/buf.h" in source:
        return ["Zephyr net_buf header inline (no independent Kconfig gate)"]
    if "sys/slist.h" in source:
        return ["Zephyr sys_slist header inline (no independent Kconfig gate)"]
    return ["compiled in actual CPUAPP shell; no independent Kconfig gate identified"]


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def action_for(row, owner, hit, header):
    symbol = row["symbol"]
    if symbol in CUSTOM_APPLICATION:
        return "reclassify_application_owner", False
    if symbol == "nrf_cc3xx_platform_abort":
        # The same local spelling exists in the adopted CC312 archive at a
        # different firmware VA.  It cannot safely satisfy 0x00050af8.
        return "identity_collision_review", False
    if header:
        return "reconcile_inline_at_callsite", False
    if not hit:
        return "manual_owner_review", False
    if hit["linkage"] == "local":
        return "adopt_complete_source_unit", False
    if owner.startswith("__fix") or hit["archive"] in {LIBGCC, LIBC}:
        return "link_compiler_runtime_public_symbol", True
    return "enable_or_adopt_public_owner", True


def build(args):
    report = load(args.input)
    rows = [row for row in report["entries"]
            if row["category"] == "sdk_or_config_symbol"]
    index = nm_index(archives(args.build))
    sources = compile_sources(args.build)
    entries = []
    for row in rows:
        owner, ratio = semantic_owner(row)
        override = EXPLICIT_OWNERS.get(row["symbol"], {})
        owner = override.get("owner", owner)
        header = inline_header(owner)
        hit = pick_hit(index.get(owner, []))
        source = override.get("source") or header or source_for(hit, sources)
        if hit and hit["archive"] in {LIBGCC, LIBC}:
            source = hit["archive"]
        if owner == "nrf_cc3xx_platform_abort" and hit:
            source = ("nrfxlib/crypto/nrf_cc312_platform/lib/cortex-m33/"
                      "hard-float/libnrf_cc312_platform_0.9.18.a")
        action, safe = action_for(row, owner, hit, header)
        action = override.get("action", action)
        if override:
            safe = False
        owner_kind = (
            override.get("kind") or
            ("application_misclassified" if row["symbol"] in CUSTOM_APPLICATION else
             "header_inline" if header else
             "archive_local" if hit and hit["linkage"] == "local" else
             "archive_public" if hit else "unresolved"))
        if row["symbol"] in CUSTOM_APPLICATION:
            source = "firmware application identity %s (not an SDK source)" % (
                ",".join(item["va"] for item in row.get("identities", [])))
        entry = {
            "symbol": row["symbol"],
            "semantic_owner": owner,
            "signature_ratio": ratio,
            "firmware_identities": [item["va"] for item in row.get("identities", [])],
            "owner_kind": owner_kind,
            "source_or_archive": source,
            "archive_evidence": hit,
            "owning_config": override.get("config", configs(source, owner)),
            "action": action,
            "safe_automatic_link_owner": safe,
            "adoption_evidence_gate": (
                "exact_signature" if ratio == 1.0 else
                "approximate_signature_requires_abi_check" if ratio is not None else
                "direct_symbol_and_archive_export" if safe else
                "not_a_public_link_candidate"),
            "reference_count": row["reference_count"],
        }
        if row["symbol"] == "nrf_cc3xx_platform_abort":
            entry["collision"] = {
                "requested_firmware_identity": "0x00050af8",
                "already_adopted_cc312_identity": "0x00079590",
                "reason": ("the vendor archive symbol is local and belongs to a "
                           "different firmware address; name equality is unsafe"),
            }
        entries.append(entry)
    counts = collections.Counter(item["action"] for item in entries)
    return {
        "schema": 1,
        "core": "app",
        "policy": {
            "report_only": True,
            "no_build_or_reconstruction_edits": True,
            "local_symbols_require_whole_source_unit": True,
        },
        "pinned_environment": {
            "ncs": "v2.5.1 / Zephyr 3.4.99",
            "compiler": "arm-zephyr-eabi GCC 12.2.0",
            "abi": "cortex-m33 hard-float",
            "libc": "newlib-nano",
            "shell_build": args.build,
            "shell_config_sha256": sha256(os.path.join(
                args.build, "zephyr/.config")),
            "revisions": {
                "zephyr": "83980fe1679441be9b0e1db556a353f6118fe14f",
                "nrf": "87355af5914e498f449b7a68bb5641031a7b8885",
                "nrfxlib": "ab72f33c86db7252dbf9a3ffec86c6b7fc6a9da7",
            },
        },
        "summary": {
            "symbols": len(entries),
            "by_action": dict(sorted(counts.items())),
            "public_safe_candidates": sum(
                item["safe_automatic_link_owner"] for item in entries),
            "source_unit_or_inline": sum(item["action"] in {
                "adopt_complete_source_unit", "reconcile_inline_at_callsite"}
                for item in entries),
        },
        "entries": entries,
    }


def markdown(catalog):
    lines = [
        "# CPUAPP SDK/config residue ownership", "",
        "Report-only resolution of the 173 SDK/config rows from the retain-all link.",
        "A local (`t`) symbol is evidence for its translation unit, not a public",
        "link target; these rows explicitly require whole-source-unit ownership.", "",
        "## Summary", "",
        "| Action | Symbols |", "|---|---:|",
    ]
    for action, count in catalog["summary"]["by_action"].items():
        lines.append("| `%s` | %d |" % (action, count))
    lines += ["", "Public safe candidates: **%d**. Source-unit/inline cases: **%d**."
              % (catalog["summary"]["public_safe_candidates"],
                 catalog["summary"]["source_unit_or_inline"]), "",
              "## Public link/adoption candidates (28)", "",
              "These have public archive exports. Exact signature hits can be adopted",
              "directly; approximate hits retain an explicit ABI-check gate.", "",
              ", ".join("`%s`" % item["symbol"] for item in catalog["entries"]
                         if item["safe_automatic_link_owner"]), "",
              "## Deliberate exclusions", "",
              "Application-owner classifier false positives (7): " +
              ", ".join("`%s`" % item["symbol"] for item in catalog["entries"]
                         if item["owner_kind"] == "application_misclassified") + ".", "",
              "`nrf_cc3xx_platform_abort` at `0x00050af8` is not satisfied by",
              "the same-named local CC312 archive function already adopted at",
              "`0x00079590`; it remains an identity-collision review item.", "",
              "## Per-symbol action", "",
              "| Symbol | Owner | Kind | Source/archive | Action |",
              "|---|---|---|---|---|"]
    for item in catalog["entries"]:
        lines.append("| `%s` | `%s` | `%s` | `%s` | `%s` |" % (
            item["symbol"], item["semantic_owner"], item["owner_kind"],
            item["source_or_archive"] or "unresolved", item["action"]))
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", default=os.path.join(
        ROOT, "recon/analysis/app_link_residue.json"))
    parser.add_argument("--build", default=BUILD)
    parser.add_argument("--json", default=os.path.join(
        ROOT, "recon/catalogs/app_sdk_residue_ownership.json"))
    parser.add_argument("--markdown", default=os.path.join(
        ROOT, "recon/catalogs/app_sdk_residue_ownership.md"))
    args = parser.parse_args()
    catalog = build(args)
    with open(args.json, "w", encoding="utf-8") as stream:
        json.dump(catalog, stream, indent=1)
        stream.write("\n")
    with open(args.markdown, "w", encoding="utf-8") as stream:
        stream.write(markdown(catalog))
    print(json.dumps(catalog["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
