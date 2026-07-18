#!/usr/bin/env python3
"""Prove the remaining public CPUNET Zephyr identities fail-closed.

This deliberately distinguishes linkable function owners from Zephyr's C
facades: z_except_reason is an ARCH_EXCEPT macro, and k_timer_stop is a
generated inline syscall wrapper in this non-userspace configuration.
"""

from __future__ import annotations

import gzip
import hashlib
import json
import re
import struct
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile

from build_net_zephyr_stock_adoption import decode_thumb_call


ROOT = Path(__file__).resolve().parents[1]
ZEPHYR = Path("/Users/freedomcoder/ncs251/zephyr")
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "netcore_image.bin"
REFGRAPH = ROOT / "recon/catalogs/refgraph_net.json.gz"
OUTPUT = ROOT / "recon/ownership/net_public_zephyr_identities.json"
REPORT = ROOT / "recon/analysis/net_public_zephyr_identities.md"
BASE = 0x01008000
COMMIT = "83980fe1679441be9b0e1db556a353f6118fe14f"
TAGS = (
    "v3.3.99-ncs1-3", "v3.4.99-ncs1", "v3.4.99-ncs1-1",
    "v3.4.99-ncs1-2", "v3.4.99-ncs1-3", "v3.5.99-ncs1",
)
SUPPORTED_RELOCATIONS = {2, 10, 30, 108}

OWNERS = (
    {
        "va": 0x0102EB2C, "symbol": "arch_irq_enable",
        "source": "arch/arm/core/aarch32/irq_manage.c",
        "object": ("zephyr/arch/arch/arm/core/aarch32/CMakeFiles/"
                   "arch__arm__core__aarch32.dir/irq_manage.c.obj"),
        "required_config": {"CONFIG_ARMV7_M_ARMV8_M_MAINLINE": "y"},
    },
    {
        "va": 0x0102FBAC, "symbol": "bt_hci_driver_register",
        "source": "subsys/bluetooth/host/hci_raw.c",
        "object": ("zephyr/subsys/bluetooth/host/CMakeFiles/"
                   "subsys__bluetooth__host.dir/hci_raw.c.obj"),
        "required_config": {
            "CONFIG_BT_HCI_RAW": "y", "CONFIG_BT_HCI_RAW_CMD_EXT": "n",
        },
    },
    {
        "va": 0x0103B304, "symbol": "sys_timepoint_calc",
        "source": "kernel/timeout.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/timeout.c.obj",
        "required_config": {
            "CONFIG_TIMEOUT_64BIT": "y", "CONFIG_TICKLESS_KERNEL": "y",
        },
    },
    {
        "va": 0x0103B34C, "symbol": "sys_timepoint_timeout",
        "source": "kernel/timeout.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/timeout.c.obj",
        "required_config": {
            "CONFIG_TIMEOUT_64BIT": "y", "CONFIG_TICKLESS_KERNEL": "y",
        },
    },
    {
        "va": 0x01039BB0, "symbol": "assert_post_action",
        "source": "lib/os/assert.c",
        "object": "zephyr/CMakeFiles/zephyr.dir/lib/os/assert.c.obj",
        "required_config": {
            "CONFIG_ASSERT": "y", "CONFIG_ASSERT_NO_FILE_INFO": "n",
            "CONFIG_USERSPACE": "n",
            "CONFIG_ARMV7_M_ARMV8_M_MAINLINE": "y",
        },
    },
    {
        "va": 0x0103B3A6, "symbol": "z_impl_k_timer_stop",
        "source": "kernel/timer.c",
        "object": "zephyr/kernel/CMakeFiles/kernel.dir/timer.c.obj",
        "required_config": {
            "CONFIG_MULTITHREADING": "y", "CONFIG_USERSPACE": "n",
            "CONFIG_TRACING": "n",
        },
    },
)

EXPECTED_CALLS = {
    "sys_clock_tick_get": 0x01038284,
    "z_abort_timeout": 0x010380D8,
    "z_unpend1_no_timeout": 0x01037960,
    "z_ready_thread": 0x0103705C,
    "z_reschedule_irqlock": 0x0103B29C,
}
EXPECTED_ABSOLUTES = {"bt_dev": 0x210047F8}
NAME_OVERRIDES = {
    "0x0102eb2c": "arch_irq_enable",
    "0x0102fbac": "bt_hci_driver_register",
    "0x0103b304": "sys_timepoint_calc",
    "0x0103b34c": "sys_timepoint_timeout",
    "0x01039bb0": "assert_post_action",
    "0x0103b3a6": "z_impl_k_timer_stop",
}


def digest(value: bytes) -> str:
    return hashlib.sha256(value).hexdigest()


def sha256(path: Path) -> str:
    return digest(path.read_bytes())


def config_values() -> dict[str, str]:
    values = {}
    for line in CONFIG.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            values[key] = value
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            values[line[2:-11]] = "n"
    return values


def git_blob(tag: str, source: str) -> str | None:
    result = subprocess.run(
        ["git", "-C", str(ZEPHYR), "rev-parse", f"{tag}:{source}"],
        capture_output=True, text=True,
    )
    return result.stdout.strip() if result.returncode == 0 else None


def relocation_symbol(elf: ELFFile, relocation) -> str:
    symbols = elf.get_section_by_name(".symtab")
    symbol = symbols.get_symbol(relocation["r_info_sym"])
    if symbol.name:
        return symbol.name
    if isinstance(symbol["st_shndx"], int):
        return elf.get_section(symbol["st_shndx"]).name
    raise ValueError("unnamed relocation target")


def source_callers(needle: str) -> list[str]:
    rows = []
    for path in sorted((ROOT / "recon/net/src").glob("*.c")):
        if needle in path.read_text(errors="ignore"):
            rows.append(str(path.relative_to(ROOT)))
    return rows


def build() -> dict:
    if subprocess.check_output(
            ["git", "-C", str(ZEPHYR), "rev-parse", "HEAD"],
            text=True).strip() != COMMIT:
        raise ValueError("Zephyr checkout is not the manifest-pinned commit")

    config = config_values()
    firmware = IMAGE.read_bytes()
    with gzip.open(REFGRAPH, "rt") as stream:
        graph = json.load(stream)["functions"]

    owners = []
    source_units = {}
    for definition in OWNERS:
        va = definition["va"]
        symbol = definition["symbol"]
        for key, expected in definition["required_config"].items():
            if config.get(key, "n") != expected:
                raise ValueError(f"configuration mismatch for {symbol}: {key}")

        object_path = BUILD / definition["object"]
        section_name = ".text." + symbol
        with object_path.open("rb") as stream:
            elf = ELFFile(stream)
            section = elf.get_section_by_name(section_name)
            if section is None:
                raise ValueError(f"missing configured section {section_name}")
            candidate = bytearray(section.data())
            original = bytearray(firmware[va - BASE:va - BASE + len(candidate)])
            relocation_section = elf.get_section_by_name(".rel" + section_name)
            relocations = []
            if relocation_section is not None:
                for relocation in relocation_section.iter_relocations():
                    offset = int(relocation["r_offset"])
                    kind = int(relocation["r_info_type"])
                    if kind not in SUPPORTED_RELOCATIONS:
                        raise ValueError(f"unsupported relocation {kind} in {symbol}")
                    target = relocation_symbol(elf, relocation)
                    linked = bytes(original[offset:offset + 4])
                    row = {"offset": offset, "type": kind, "target": target}
                    if kind in (10, 30):
                        actual = decode_thumb_call(linked, va + offset)
                        expected = EXPECTED_CALLS.get(target)
                        if expected != actual:
                            raise ValueError(
                                f"call target mismatch {symbol}+0x{offset:x}: "
                                f"{target}=0x{actual:08x}")
                        row["firmware_target"] = f"0x{actual:08x}"
                    else:
                        actual = struct.unpack("<I", linked)[0]
                        expected = EXPECTED_ABSOLUTES.get(target)
                        if expected != actual:
                            raise ValueError(
                                f"absolute target mismatch {symbol}+0x{offset:x}: "
                                f"{target}=0x{actual:08x}")
                        row["firmware_target"] = f"0x{actual:08x}"
                    relocations.append(row)
                    candidate[offset:offset + 4] = bytes(4)
                    original[offset:offset + 4] = bytes(4)
        if candidate != original:
            mismatch = next(index for index, pair in enumerate(zip(candidate, original))
                            if pair[0] != pair[1])
            raise ValueError(f"non-relocation mismatch {symbol}+0x{mismatch:x}")

        va_key = "0x%x" % va
        raw = f"FUN_{va:08x}"
        reconstruction = ROOT / "recon/net/src" / (raw + ".c")
        callers = graph.get(va_key, {}).get("callers", [])
        owners.append({
            "va": f"0x{va:08x}", "raw_symbol": raw,
            "upstream_symbol": symbol,
            "upstream_source": "zephyr/" + definition["source"],
            "upstream_section": section_name,
            "size": len(candidate),
            "match": "relocation-masked-byte-exact",
            "normalized_sha256": digest(bytes(original)),
            "relocations": relocations,
            "firmware_callers": callers,
            "canonical_reference_sources": sorted(set(
                source_callers(raw) + source_callers(symbol))),
            "required_config": definition["required_config"],
            "reconstruction_present": reconstruction.is_file(),
            "reconstruction_source": (str(reconstruction.relative_to(ROOT))
                                      if reconstruction.is_file() else None),
            "safe_to_adopt": True,
            "exclude_reconstruction": True,
            "raw_mapping_preserved": True,
        })

        source = definition["source"]
        if source not in source_units:
            source_path = ZEPHYR / source
            source_units[source] = {
                "source": "zephyr/" + source,
                "source_sha256": sha256(source_path),
                "manifest_commit_blob": git_blob(COMMIT, source),
                "tag_blob_matrix": {tag: git_blob(tag, source) for tag in TAGS},
            }

    assert_owner = next(row for row in owners
                        if row["upstream_symbol"] == "assert_post_action")
    expected_except = bytes.fromhex("404080f311884ff0040002df7047")
    if firmware[0x01039BB0 - BASE:0x01039BB0 - BASE + 14] != expected_except:
        raise ValueError("assert_post_action ARCH_EXCEPT expansion drift")
    if assert_owner["size"] != 14:
        raise ValueError("configured assert_post_action extent drift")

    generated_syscall = BUILD / "zephyr/include/generated/syscalls/kernel.h"
    generated_text = generated_syscall.read_text()
    timer_facade = re.search(
        r"static inline void k_timer_stop\(.*?\n\}", generated_text, re.S)
    if not timer_facade or "z_impl_k_timer_stop(timer);" not in timer_facade.group(0):
        raise ValueError("generated k_timer_stop facade drift")

    selected_blobs = {unit["manifest_commit_blob"] for unit in source_units.values()}
    if None in selected_blobs:
        raise ValueError("missing manifest source blob")
    return {
        "schema": 1,
        "core": "net",
        "component": "zephyr_public_function_and_macro_owners",
        "status": "authorized_scoped",
        "safe": True,
        "policy": {
            "sdc_policy": "report_only_unchanged",
            "no_linker_aliases": True,
            "no_generated_tree_or_manifest_mutation": True,
            "raw_backmaps_preserved": True,
        },
        "inputs": {
            "image": "netcore_image.bin", "image_sha256": sha256(IMAGE),
            "configured_build": str(BUILD),
            "config": str(CONFIG), "config_sha256": sha256(CONFIG),
            "zephyr_commit": COMMIT,
            "zephyr_tag": "v3.4.99-ncs1-1",
            "abi": "Cortex-M33 Thumb-2 soft-float -Os GCC 12.2",
        },
        "version_precision": {
            "manifest_exact_tag": "v3.4.99-ncs1-1",
            "body_selected_family": "v3.4.99-ncs1",
            "indistinguishable_patch_tags": [
                "v3.4.99-ncs1", "v3.4.99-ncs1-1",
                "v3.4.99-ncs1-2", "v3.4.99-ncs1-3",
            ],
            "note": ("irq_manage.c, hci_raw.c, and timeout.c reject the "
                     "v3.3.99-ncs1-3 source blobs; exact -1 provenance is "
                     "the shipped manifest pin, not a claim inferred from "
                     "source-identical 3.4 patch tags."),
        },
        "source_units": [source_units[key] for key in sorted(source_units)],
        "owners": owners,
        "api_facades": {
            "z_except_reason": {
                "kind": "preprocessor_macro",
                "expands_to": "ARCH_EXCEPT(reason)",
                "selected_owner": "assert_post_action@0x01039bb0",
                "firmware_bytes": expected_except.hex(),
                "semantics": "BASEPRI=0; r0=K_ERR_KERNEL_PANIC(4); svc #2; bx lr",
                "no_linkable_symbol": True,
            },
            "k_timer_stop": {
                "kind": "generated_inline_syscall_facade",
                "userspace": False,
                "calls": "z_impl_k_timer_stop",
                "selected_owner": "z_impl_k_timer_stop@0x0103b3a6",
                "generated_header": str(generated_syscall),
                "generated_header_sha256": sha256(generated_syscall),
                "no_independent_linkable_owner": True,
            },
        },
        "name_overrides": NAME_OVERRIDES,
        "manifest_functions": owners,
        "summary": {
            "exact_function_owners": len(owners),
            "macro_or_inline_facades": 2,
            "relocations_checked": sum(len(row["relocations"]) for row in owners),
        },
    }


def write_report(data: dict) -> None:
    lines = [
        "# CPUNET public Zephyr identity closure", "",
        "Six configured public owners are relocation-masked byte-exact at the "
        "firmware addresses below. Raw `FUN_` identities remain reversible.", "",
        "| VA | owner | bytes | relocations | callers |", "|---|---|---:|---:|---:|",
    ]
    for row in data["owners"]:
        lines.append(
            f"| `{row['va']}` | `{row['upstream_symbol']}` | {row['size']} | "
            f"{len(row['relocations'])} | {len(row['firmware_callers'])} |")
    lines += [
        "", "`z_except_reason` is not a function in this configuration: "
        "`assert_post_action` expands it to the exact ARM Mainline `svc #2` "
        "sequence. `k_timer_stop` is likewise a generated inline facade for "
        "the proven `z_impl_k_timer_stop` section because userspace is off.", "",
        "The three source units that distinguish the adjacent older family "
        "reject their v3.3.99 blobs. The four v3.4.99 patch tags have identical "
        "source blobs here, so the OTA manifest—not body overclaiming—pins "
        "`v3.4.99-ncs1-1`. SDC remains report-only.", "",
    ]
    REPORT.write_text("\n".join(lines))


def main() -> int:
    data = build()
    OUTPUT.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
    write_report(data)
    print("CPUNET public Zephyr identities: 6 exact owners, 2 API facades")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
