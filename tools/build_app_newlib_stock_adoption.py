#!/usr/bin/env python3
"""Authorize exact Newlib-nano stdio, allocator, strtoul, and string closures."""

import argparse
import hashlib
import io
import json
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
ARCHIVE = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a")
AR = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-ar")
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISION_CATALOG = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_newlib_stock_atomic_adoption.json"
IMAGE = ROOT / "app_update.bin"
CONFIG = Path("/tmp/g1-fwconfig-shadow/zephyr/.config")
ARCHIVE_SHA256 = "c6a3f8bf0d33e395061c64e8f523e7fb11aaf7fb679c25ff0124e5cd77eaa5cc"
NEWLIB_COMMIT = "4e150303bcc1e44f4d90f3489a4417433980d5ff"

# VA, readable identity, archive member, emitted section, closure.
MEMBERS = [
    (0x76b48, "newlib_stdio_init_stream", "lib_a-findfp.o", ".text.std", "findfp"),
    (0x76b9c, "__sfp_lock_acquire", "lib_a-findfp.o", ".text.__sfp_lock_acquire", "findfp"),
    (0x76ba8, "__sfp_lock_release", "lib_a-findfp.o", ".text.__sfp_lock_release", "findfp"),
    (0x76bb4, "__sinit_lock_acquire", "lib_a-findfp.o", ".text.__sinit_lock_acquire", "findfp"),
    (0x76bc0, "__sinit_lock_release", "lib_a-findfp.o", ".text.__sinit_lock_release", "findfp"),
    (0x76bcc, "__sinit", "lib_a-findfp.o", ".text.__sinit", "findfp"),
    (0x76c3c, "__sfp", "lib_a-findfp.o", ".text.__sfp", "findfp"),
    (0x86b14, "__sfmoreglue", "lib_a-findfp.o", ".text.__sfmoreglue", "findfp"),
    (0x76d6c, "malloc", "lib_a-malloc.o", ".text.malloc", "allocator"),
    (0x76d7c, "free", "lib_a-malloc.o", ".text.free", "allocator"),
    (0x76d8c, "_free_r", "lib_a-nano-freer.o", ".text._free_r", "allocator"),
    (0x76e20, "_malloc_r", "lib_a-nano-mallocr.o", ".text._malloc_r", "allocator"),
    (0x876d0, "_calloc_r", "lib_a-nano-callocr.o", ".text._calloc_r", "allocator"),
    (0x876ec, "_realloc_r", "lib_a-nano-reallocr.o", ".text._realloc_r", "allocator"),
    (0x87996, "_malloc_usable_size_r", "lib_a-nano-msizer.o", ".text._malloc_usable_size_r", "allocator"),
    (0x77b38, "_strtoul_r", "lib_a-strtoul.o", ".text._strtoul_l.constprop.0", "strtoul"),
    (0x77c1c, "strtoul", "lib_a-strtoul.o", ".text.strtoul", "strtoul"),
    (0x0eefe, "strcmp", "lib_a-strcmp.o", ".text", "strings"),
    (0x0ef12, "strlen", "lib_a-strlen.o", ".text", "strings"),
]
COLLISIONS = {"__sinit", "__sinit_lock_release", "_malloc_r", "_strtoul_r", "malloc"}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    encoded = json.dumps(value, sort_keys=True, separators=(",", ":")).encode()
    return hashlib.sha256(encoded).hexdigest()


def object_bytes(member):
    return subprocess.check_output([str(AR), "p", str(ARCHIVE), member])


def normalized_receipt(va, member, section_name):
    obj = object_bytes(member)
    elf = ELFFile(io.BytesIO(obj))
    section = elf.get_section_by_name(section_name)
    if section is None:
        raise ValueError("missing section %s(%s)" % (member, section_name))
    upstream = bytearray(section.data())
    firmware = bytearray(IMAGE.read_bytes()[va - 0xc000:va - 0xc000 + len(upstream)])
    reloc = elf.get_section_by_name(".rel" + section_name)
    offsets = [] if reloc is None else [item["r_offset"] for item in reloc.iter_relocations()]
    for offset in offsets:
        upstream[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if upstream != firmware:
        raise ValueError("normalized archive mismatch at 0x%08x" % va)
    return {
        "firmware_code_size": len(upstream), "upstream_code_size": len(upstream),
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
        "archive_member_sha256": hashlib.sha256(obj).hexdigest(),
    }


def canonical(va):
    raw = ROOT / ("recon/app/src/FUN_%08x.c" % va)
    if raw.exists():
        return raw
    names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
    name = names["by_address"]["0x%08x" % va]["name"]
    path = ROOT / "recon/app/src" / (name + ".c")
    if not path.exists():
        raise ValueError("missing canonical evidence for 0x%08x" % va)
    return path


def rows():
    group = ["0x%08x" % va for va, *_ in MEMBERS]
    config_sha = sha(CONFIG)
    collisions = json.loads(COLLISION_CATALOG.read_text())
    collisions = {row["va"]: row for row in collisions["functions"]}
    result = []
    for va, symbol, member, section, closure in MEMBERS:
        hidden = symbol not in COLLISIONS
        row = {
            "batch": "COLLISION-01", "va": "0x%08x" % va,
            "raw_symbol": "FUN_%08x" % va, "symbol": symbol,
            "status": "authorized", "instruction_exact": True,
            "configuration_variant_exact": True, "cfg_verify_cases": 1,
            "archive_member_exact": True,
            "atomic_group": group, "hidden_owner_closure": hidden,
            "upstream_source": "newlib/%s" % ({
                "findfp": "libc/stdio/findfp.c",
                "allocator": "libc/stdlib/nano allocator",
                "strtoul": "libc/stdlib/strtoul.c",
                "strings": ("libc/string/strcmp.c" if symbol == "strcmp" else
                            "libc/string/strlen.c"),
            }[closure]),
            "upstream_object": str(ARCHIVE), "archive_member": member,
            "upstream_object_sha256": ARCHIVE_SHA256,
            "upstream_archive_sha256": ARCHIVE_SHA256,
            "configured_link_owner": "%s(%s)" % (ARCHIVE, member),
            "configured_build": str(CONFIG), "configured_build_sha256": config_sha,
            "required_config": {
                "CONFIG_NEWLIB_LIBC": "y",
                "CONFIG_NEWLIB_LIBC_NANO": "y",
            },
            "reconstruction_source": str(canonical(va)),
            "reconstruction_source_sha256": sha(canonical(va)),
            "newlib_release": "3.3.0", "newlib_commit": NEWLIB_COMMIT,
            "version_identity": {
                "manifest_provenance": "Zephyr SDK 0.16.5-1",
                "archive_release": "newlib 3.3.0",
                "archive_commit": NEWLIB_COMMIT,
                "body_discrimination": (
                    "exact for the pinned archive member; the short generic "
                    "string body alone is not a unique patch-level fingerprint"),
            },
            "whole_unit_closure": {
                "safe": True, "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": sorted(COLLISIONS),
                "exclude_only": group, "new_undefined_symbols": [],
                "private_state": (["__malloc_free_list", "__malloc_sbrk_start"]
                                  if closure == "allocator" else
                                  ["stdio FILE pool", "recursive stdio/init locks"]
                                  if closure == "findfp" else []),
            },
        }
        collision = collisions.get(row["va"])
        if collision is not None:
            row["collision_receipt_sha256"] = json_sha(collision)
            row["baseline_configured_build_sha256"] = collision[
                "configured_inclusion"]["zephyr_config_sha256"]
        if hidden:
            row["identity_correction"] = {
                "baseline_collision_symbol": symbol,
                "corrected_readable_identity": symbol,
                "corrected_upstream_symbol": symbol,
                "upstream_linkage": ("translation_unit_local" if symbol == "newlib_stdio_init_stream" else "public"),
            }
        if va == 0x77b38:
            row["public_veneer_backmap"] = {
                "firmware_public_entry": "0x00077b38",
                "matched_archive_body": ".text._strtoul_l.constprop.0",
                "archive_public_symbol": ".text._strtoul_r",
                "archive_public_veneer_size": 4,
            }
        row.update(normalized_receipt(va, member, section))
        result.append(row)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--authorize", action="store_true")
    args = parser.parse_args()
    if sha(ARCHIVE) != ARCHIVE_SHA256:
        raise ValueError("libc_nano archive drift")
    selected = rows()
    receipt = {
        "schema": 1, "core": "app", "batch": "COLLISION-01",
        "status": "authorized_atomic", "decision": "adopt_exact_stock_newlib_nano_closures",
        "archive": str(ARCHIVE), "archive_sha256": ARCHIVE_SHA256,
        "newlib_release": "3.3.0", "newlib_commit": NEWLIB_COMMIT,
        "policy": {"retain_recovered_c_as_evidence": True,
                   "fdlibm_prebuilt_archive_adoption": False,
                   "sdc_remains_report_only": True},
        "closures": {name: ["0x%08x" % va for va, _, _, _, group in MEMBERS if group == name]
                     for name in ("findfp", "allocator", "strtoul", "strings")},
        "authorizations": selected,
        "expected_link_delta": {"before": 66, "after": 61,
                                "removed": sorted(COLLISIONS), "added": [],
                                "unresolved": ["FUN_0005463e", "FUN_00054688"]},
    }
    OUTPUT.write_text(json.dumps(receipt, indent=1) + "\n")
    if args.authorize:
        data = json.loads(AUTH.read_text())
        data["authorizations"] = [row for row in data["authorizations"]
                                  if row.get("batch") != "COLLISION-01"] + selected
        AUTH.write_text(json.dumps(data, indent=1) + "\n")
    print("wrote exact Newlib closure receipt (%d recovered bodies)" % len(selected))


if __name__ == "__main__":
    main()
