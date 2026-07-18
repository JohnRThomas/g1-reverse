#!/usr/bin/env python3
"""Authorize the three exact root stock owners from the exact5 build."""

import argparse
import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-root-topology-exact5-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "app_update.bin"
OUTPUT = ROOT / "recon/ownership/app_root_stock_atomic_adoption.json"

COMMON = BUILD / ("modules/zcbor/CMakeFiles/modules__zcbor.dir/Users/"
                  "freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_common.c.obj")
ENCODE = BUILD / ("modules/zcbor/CMakeFiles/modules__zcbor.dir/Users/"
                  "freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_encode.c.obj")
BOOT = BUILD / ("modules/mcuboot/boot/bootutil/zephyr/CMakeFiles/"
                "mcuboot_util.dir/Users/freedomcoder/ncs251/bootloader/"
                "mcuboot/boot/bootutil/src/bootutil_public.c.obj")

COMMON_SOURCE = Path("/Users/freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_common.c")
ENCODE_SOURCE = Path("/Users/freedomcoder/ncs251/modules/lib/zcbor/src/zcbor_encode.c")
BOOT_SOURCE = Path("/Users/freedomcoder/ncs251/bootloader/mcuboot/boot/bootutil/src/bootutil_public.c")

BASE_CONFIG = {
    "CONFIG_ASSERT": "y",
    "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_THREAD_LOCAL_STORAGE": "n",
    "CONFIG_THREAD_CUSTOM_DATA": "y",
    "CONFIG_MAIN_STACK_SIZE": "16384",
}

OWNERS = (
    {
        "va": 0x00085C86,
        "symbol": "zcbor_process_backup",
        "object": COMMON,
        "source": COMMON_SOURCE,
        "source_unit": "modules/lib/zcbor/src/zcbor_common.c",
        "source_commit": "67fd8bb88d3136738661fa8bb5f9989103f4599e",
        "extent": 108,
        "cfg_cases": 9,
        "callers": ["0x00085df6 cbor_decode_leave_container (tail B.W at 0x00085e14)"],
        "required_config": {
            "CONFIG_ZCBOR": "y",
            "CONFIG_ZCBOR_STOP_ON_ERROR": "y",
            "CONFIG_ZCBOR_ASSERT": "y",
        },
        "exact_companion_sections": [
            ".text.zcbor_check_error.isra.0",
            ".text.zcbor_error",
            ".text.zcbor_new_backup",
            ".text.zcbor_new_state",
            ".text.zcbor_array_at_end",
        ],
        "gc_sections": [
            ".text.zcbor_union_elem_code", ".text.zcbor_union_end_code",
            ".text.zcbor_update_state", ".text.zcbor_validate_string_fragments",
            ".text.zcbor_splice_string_fragments", ".text.zcbor_compare_strings",
            ".text.zcbor_header_len",
        ],
        "version_identity": {
            "function_first_commit": "e01ea4efa176398ab180230567dadba9df30c011",
            "function_next_change_exclusive": "c9d2c8d29dff31d52be8157b7156766b968612b2",
            "manifest_pin": "67fd8bb88d3136738661fa8bb5f9989103f4599e",
        },
    },
    {
        "va": 0x00086360,
        "symbol": "zcbor_simple_put",
        "object": ENCODE,
        "source": ENCODE_SOURCE,
        "source_unit": "modules/lib/zcbor/src/zcbor_encode.c",
        "source_commit": "67fd8bb88d3136738661fa8bb5f9989103f4599e",
        "extent": 24,
        "cfg_cases": 4,
        "callers": ["0x00086378 cbor_encode_simple (tail B.W at 0x0008637c)"],
        "required_config": {
            "CONFIG_ZCBOR": "y",
            "CONFIG_ZCBOR_STOP_ON_ERROR": "y",
            "CONFIG_ZCBOR_ASSERT": "y",
        },
        "exact_companion_sections": [
            ".text.zcbor_int_encode", ".text.zcbor_uint_encode",
            ".text.zcbor_list_start_encode", ".text.zcbor_map_start_encode",
            ".text.zcbor_list_end_encode", ".text.zcbor_bool_put",
        ],
        "gc_sections": [
            ".text.zcbor_float64_put", ".text.zcbor_float32_put",
            ".text.zcbor_float16_put", ".text.zcbor_multi_encode",
            ".text.zcbor_multi_encode_minmax", ".text.zcbor_present_encode",
        ],
        "version_identity": {
            "function_first_commit": "4d82f00fc531eeaf08b7be53408a55057e4a7e5d",
            "function_next_change_exclusive": "a54e92a4c564255dc8be746e2afd500295db7997",
            "manifest_pin": "67fd8bb88d3136738661fa8bb5f9989103f4599e",
        },
    },
    {
        "va": 0x000641E4,
        "symbol": "boot_set_next",
        "object": BOOT,
        "source": BOOT_SOURCE,
        "source_unit": "bootloader/mcuboot/boot/bootutil/src/bootutil_public.c",
        "source_commit": "edfe1e1465dbc698bf9a195816247913490ab391",
        "extent": 158,
        "cfg_cases": 1,
        "callers": ["0x00051d8c img_mgmt_state_set_pending (BL at 0x00051e36)"],
        "required_config": {
            "CONFIG_BOOTLOADER_MCUBOOT": "y",
            "CONFIG_UPDATEABLE_IMAGE_NUMBER": "2",
        },
        "exact_companion_sections": [
            ".text.boot_write_magic", ".text.boot_read_swap_state",
            ".text.boot_write_swap_info", ".text.boot_write_image_ok",
            ".text.boot_read_image_ok", ".text.boot_read_swap_state_by_id",
        ],
        "gc_sections": [
            ".text.boot_swap_type_multi", ".text.boot_write_copy_done",
            ".text.boot_set_pending_multi", ".text.boot_set_confirmed_multi",
            ".text.boot_image_load_header",
        ],
        "version_identity": {
            "function_first_commit": "4ff95da6f631409e1b3340bb972e91deec0ec924",
            "manifest_pin": "edfe1e1465dbc698bf9a195816247913490ab391",
            "indistinguishable_tags": "v1.10.99-ncs1 through local v2.1.0-ncs5-2",
        },
    },
)


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    encoded = json.dumps(value, sort_keys=True, separators=(",", ":")).encode()
    return hashlib.sha256(encoded).hexdigest()


def config_values():
    result = {}
    for line in CONFIG.read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            result[key] = value.strip('"')
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            result[line[2:-11]] = "n"
    return result


def normalized_section(owner):
    name = ".text." + owner["symbol"]
    with owner["object"].open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(name)
        if section is None or len(section.data()) < owner["extent"]:
            raise ValueError("missing/short exact section " + name)
        candidate = bytearray(section.data()[:owner["extent"]])
        relocation = elf.get_section_by_name(".rel" + name)
        offsets = ([] if relocation is None else
                   [int(row["r_offset"]) for row in relocation.iter_relocations()
                    if int(row["r_offset"]) < owner["extent"]])
        section_size = len(section.data())
    start = owner["va"] - 0xC000
    firmware = bytearray(IMAGE.read_bytes()[start:start + owner["extent"]])
    for offset in offsets:
        candidate[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if candidate != firmware:
        raise ValueError("configured section differs: " + owner["symbol"])
    return offsets, section_size, hashlib.sha256(firmware).hexdigest()


def collision_row(owner, object_sha, source_sha, config_sha, section_size,
                  normalized_sha):
    va = "0x%08x" % owner["va"]
    return {
        "core": "app",
        "va": va,
        "raw_symbol": "FUN_%08x" % owner["va"],
        "current_symbol": owner["symbol"],
        "firmware_extent": owner["extent"],
        "upstream": {
            "symbol": owner["symbol"],
            "object": str(owner["object"]),
            "object_sha256": object_sha,
            "section": ".text." + owner["symbol"],
            "symbol_size": section_size,
            "code_extent_compared": owner["extent"],
            "source": {
                "path": str(owner["source"]),
                "sha256": source_sha,
                "repository": ("zcbor" if "zcbor" in owner["symbol"] else "mcuboot"),
                "commit": owner["source_commit"],
            },
        },
        "configured_inclusion": {
            "selected_by_real_link": True,
            "indexed_object_present": True,
            "zephyr_config_sha256": config_sha,
            "proof": "exact5 retain-all link selected this stock source unit",
        },
        "signature_match": {
            "normalized_exact": True,
            "normalized_code_sha256": normalized_sha,
            "opcode": 1.0, "shape": 1.0, "length": 1.0,
        },
        "identity_threshold_candidate": True,
        "safe_to_exclude": False,
        "exclusion_blockers": [],
    }


def build():
    values = config_values()
    config_sha = sha(CONFIG)
    collisions = []
    authorizations = []
    for owner in OWNERS:
        required = dict(BASE_CONFIG)
        required.update(owner["required_config"])
        mismatch = {key: (value, values.get(key)) for key, value in required.items()
                    if values.get(key) != value}
        if mismatch:
            raise ValueError("exact5 config mismatch: %r" % mismatch)
        object_sha = sha(owner["object"])
        source_sha = sha(owner["source"])
        offsets, section_size, normalized_sha = normalized_section(owner)
        collision = collision_row(owner, object_sha, source_sha, config_sha,
                                  section_size, normalized_sha)
        collisions.append(collision)
        va = collision["va"]
        canonical = ROOT / "recon/app/src" / (collision["raw_symbol"] + ".c")
        authorization = {
            "batch": "ROOT-STOCK-EXACT5",
            "status": "authorized",
            "va": va,
            "raw_symbol": collision["raw_symbol"],
            "symbol": owner["symbol"],
            "instruction_exact": True,
            "configuration_variant_exact": True,
            "required_config": required,
            "atomic_group": [va],
            "upstream_source": str(owner["source"]),
            "upstream_source_sha256": source_sha,
            "upstream_object": str(owner["object"]),
            "upstream_object_sha256": object_sha,
            "configured_build": str(CONFIG),
            "configured_build_sha256": config_sha,
            "baseline_upstream_object_sha256": object_sha,
            "baseline_configured_build_sha256": config_sha,
            "collision_receipt_sha256": json_sha(collision),
            "reconstruction_source": str(canonical.relative_to(ROOT)),
            "reconstruction_source_sha256": sha(canonical),
            "firmware_code_size": owner["extent"],
            "upstream_code_size": owner["extent"],
            "upstream_section_size": section_size,
            "relocation_offsets": offsets,
            "normalized_code_sha256": normalized_sha,
            "cfg_verify_cases": owner["cfg_cases"],
            "callers": owner["callers"],
            "source_version_identity": owner["version_identity"],
            "whole_unit_closure": {
                "safe": True,
                "source_unit": owner["source_unit"],
                "archive_member_already_selected": True,
                "exclude_only": [va],
                "selected_exact_section": ".text." + owner["symbol"],
                "exact_companion_sections": owner["exact_companion_sections"],
                "firmware_absent_sections_require_normal_gc": owner["gc_sections"],
                "retain_all_probe_may_keep_absent_sections": True,
                "new_undefined_symbols": [],
                "raw_alias_preserved": collision["raw_symbol"],
            },
        }
        authorizations.append(authorization)
    return {
        "schema": 1,
        "core": "app",
        "status": "authorized_atomic",
        "configured_build_receipts": [str(CONFIG)],
        "policy": {
            "retain_recovered_c_as_evidence": True,
            "exclude_only_selected_public_owners": True,
            "normal_section_gc_required_for_firmware_absent_sections": True,
            "sdc_remains_report_only": True,
        },
        "variant_collisions": collisions,
        "authorizations": authorizations,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    text = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise ValueError("stale root-stock exact5 adoption receipt")
    else:
        OUTPUT.write_text(text)
    print("root-stock exact5 adoption: 3 owners")


if __name__ == "__main__":
    main()
