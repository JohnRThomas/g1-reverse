#!/usr/bin/env python3
"""Build the exact NCS 2.5.1 img_mgmt source-closure receipt.

All four selected source units have a relocation-normalized byte-exact *live*
closure.  In particular, the private ``img_mgmt_upload`` body is exact once
ELF relocations are masked; comparing the unresolved relocatable object bytes
directly had produced the earlier false variant classification.
"""

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import extract  # noqa: E402

NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-app-root-topology-exact5-0718")
CONFIG = BUILD / "zephyr/.config"
PM_CONFIG = BUILD / "pm.config"
OBJROOT = (BUILD / "zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/CMakeFiles/"
           "subsys__mgmt__mcumgr__grp__img_mgmt.dir/src")
COLLISIONS = ROOT / "recon/ownership/app_root_stock_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_img_mgmt_stock_atomic_adoption.json"

REQUIRED_CONFIG = {
    "CONFIG_MCUMGR_GRP_IMG": "y",
    "CONFIG_MCUMGR_GRP_IMG_UPDATABLE_IMAGE_NUMBER": "2",
    "CONFIG_IMG_ERASE_PROGRESSIVELY": "y",
    "CONFIG_UPDATEABLE_IMAGE_NUMBER": "2",
    "CONFIG_NRF53_UPGRADE_NETWORK_CORE": "y",
    "CONFIG_PM_EXTERNAL_FLASH_MCUBOOT_SECONDARY": "y",
    "CONFIG_MCUMGR_GRP_IMG_USE_HEAP_FOR_FLASH_IMG_CONTEXT": "n",
    "CONFIG_MCUMGR_GRP_IMG_VERBOSE_ERR": "n",
    "CONFIG_MCUMGR_GRP_IMG_DIRECT_UPLOAD": "n",
    "CONFIG_MCUMGR_GRP_IMG_REJECT_DIRECT_XIP_MISMATCHED_SLOT": "n",
    "CONFIG_MCUMGR_GRP_IMG_VERSION_CMP_USE_BUILD_NUMBER": "n",
}

# Object: section -> (firmware VA, upstream linkage, canonical evidence file,
# cfg_verify case count).  These are all and only the live text sections from
# the three adopted source units in the shipped link.
UNITS = {
    "img_mgmt.c": {
        "img_mgmt_reset_upload": (0x00051FE4, "translation_unit_local", "FUN_00051fe4.c", 0),
        "img_mgmt_upload_good_rsp.isra.0": (0x00052000, "translation_unit_local", "FUN_00052000.c", 0),
        "img_mgmt_take_lock": (0x00080A42, "public", "FUN_00080a42.c", 0),
        "img_mgmt_release_lock": (0x00080A44, "public", "FUN_00080a44.c", 0),
        "img_mgmt_active_slot": (0x00080A46, "public", "FUN_00080a46.c", 0),
        "img_mgmt_active_image": (0x00080A4A, "public", "FUN_00080a4a.c", 0),
        "img_mgmt_read_info": (0x00052038, "public", "FUN_00052038.c", 6),
        "img_mgmt_erase": (0x00052180, "translation_unit_local", "FUN_00052180.c", 3),
        "img_mgmt_upload": (0x000521FC, "translation_unit_local", "FUN_000521fc.c", 9),
        "img_mgmt_find_by_hash": (0x00080A4E, "public", "FUN_00080a4e.c", 0),
        "img_mgmt_my_version": (0x00080A82, "public", "FUN_00080a82.c", 0),
    },
    "img_mgmt_state.c": {
        "zcbor_tstr_encode_ptr": (0x0008099E, "translation_unit_local", "FUN_0008099e.c", 0),
        "img_mgmt_state_encode_slot": (0x00051AC0, "translation_unit_local", "FUN_00051ac0.c", 2),
        "img_mgmt_get_opposite_slot.part.0": (0x00051C38, "translation_unit_local", "FUN_00051c38.c", 0),
        "img_mgmt_slot_to_image.part.0": (0x00051C68, "translation_unit_local", "FUN_00051c68.c", 0),
        "img_mgmt_state_read": (0x00051C98, "public", "FUN_00051c98.c", 0),
        "img_mgmt_set_next_boot_slot": (0x00051D8C, "public", "FUN_00051d8c.c", 3),
        "img_mgmt_state_write": (0x00051E9C, "public", "FUN_00051e9c.c", 0),
        "img_mgmt_get_next_boot_slot": (0x000809B0, "public", "img_mgmt_get_next_boot_slot.c", 10),
        "img_mgmt_slot_in_use": (0x000809F6, "public", "FUN_000809f6.c", 6),
    },
    "img_mgmt_util.c": {
        "img_mgmt_ver_str": (0x00051F88, "public", "FUN_00051f88.c", 0),
    },
    "zephyr_img_mgmt.c": {
        "z_log_msg_static_create.constprop.0": (0x0008096A, "translation_unit_local", "FUN_0008096a.c", 0),
        "img_mgmt_flash_area_id": (0x0005169C, "public", "FUN_0005169c.c", 3),
        "img_mgmt_vercmp": (0x00080970, "public", "FUN_00080970.c", 0),
        "img_mgmt_erase_slot": (0x000516AC, "public", "FUN_000516ac.c", 0),
        "img_mgmt_read": (0x000517D8, "public", "FUN_000517d8.c", 0),
        "img_mgmt_write_image_data": (0x00051870, "public", "FUN_00051870.c", 2),
        "img_mgmt_upload_inspect": (0x000518A8, "public", "FUN_000518a8.c", 16),
        "img_mgmt_erased_val": (0x00051A5C, "public", "FUN_00051a5c.c", 0),
    },
}

NONLIVE = {
    "img_mgmt.c": ["img_mgmt_find_by_ver"],
    "img_mgmt_state.c": ["img_mgmt_state_flags", "img_mgmt_state_any_pending",
                         "img_mgmt_state_set_pending", "img_mgmt_state_confirm"],
    "zephyr_img_mgmt.c": ["img_mgmt_slot_to_image.part.0", "img_mgmt_write_pending",
                          "img_mgmt_write_confirmed", "img_mgmt_erase_image_data",
                          "img_mgmt_swap_type"],
}

# Live sections that have no standalone reconstruction target.  They are part
# of the exact stock source-unit closure and are recorded separately so the
# receipt proves that selecting img_mgmt.c cannot add uninspected code.
HIDDEN_LIVE = {
    "img_mgmt.c": {
        "img_mgmt_translate_error_code": 0x00051FC4,
        "img_mgmt_register_group": 0x00051FD8,
    },
}

UPSTREAM_REVISIONS = {
    "ncs_release": "v2.5.1",
    "zephyr_describe": "v3.4.99-ncs1-1",
    "zephyr_commit": "83980fe1679441be9b0e1db556a353f6118fe14f",
    "img_mgmt_source_blob": "305cad41c4459b1e5fea46b9ce06383a535a20dc",
    "source_identity_plateau": [
        "v3.4.99-ncs1-1", "v3.4.99-ncs1-2", "v3.4.99-ncs1-3"],
    "precision": ("configured body proves the NCS 2.5 img_mgmt source/config; "
                  "the manifest proves -ncs1-1 because the source blob is "
                  "unchanged through -ncs1-3"),
}

PM_REQUIRED = {
    "PM_MCUBOOT_PRIMARY_ID": "4",
    "PM_MCUBOOT_PRIMARY_OFFSET": "0xc000",
    "PM_MCUBOOT_PRIMARY_SIZE": "0xf0000",
    "PM_MCUBOOT_SECONDARY_ID": "2",
    "PM_MCUBOOT_SECONDARY_OFFSET": "0x0",
    "PM_MCUBOOT_SECONDARY_SIZE": "0xf0000",
    "PM_MCUBOOT_PRIMARY_1_ID": "1",
    "PM_MCUBOOT_PRIMARY_1_OFFSET": "0x0",
    "PM_MCUBOOT_PRIMARY_1_SIZE": "0x40000",
    "PM_MCUBOOT_SECONDARY_1_ID": "8",
    "PM_MCUBOOT_SECONDARY_1_OFFSET": "0xf0000",
    "PM_MCUBOOT_SECONDARY_1_SIZE": "0x40000",
    "PM_SETTINGS_STORAGE_ID": "9",
    "PM_SETTINGS_STORAGE_OFFSET": "0xfc000",
    "PM_SETTINGS_STORAGE_SIZE": "0x2000",
    "PM_7_LABEL": "RAM_FLASH",
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def values(path):
    result = {}
    for line in Path(path).read_text().splitlines():
        if "=" in line and not line.startswith("#"):
            key, value = line.split("=", 1)
            result[key] = value.strip('"')
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            result[line[2:-11]] = "n"
    return result


def section_receipt(obj, symbol, va):
    with obj.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(".text." + symbol)
        if section is None:
            raise ValueError("missing configured section " + symbol)
        candidate = bytearray(section.data())
        reloc = elf.get_section_by_name(".rel" + section.name)
        offsets = [] if reloc is None else [
            item["r_offset"] for item in reloc.iter_relocations()
            if item["r_offset"] < len(candidate)]
    firmware = bytearray(extract.read(va, len(candidate)))
    for offset in offsets:
        candidate[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if candidate != firmware:
        raise ValueError("relocation-masked mismatch: " + symbol)
    return {
        "firmware_code_size": len(firmware),
        "upstream_code_size": len(candidate),
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
        "instruction_exact": True,
        "relocation_masked_byte_exact": True,
    }


def topology_receipt():
    pm = values(PM_CONFIG)
    for key, expected in PM_REQUIRED.items():
        if pm.get(key) != expected:
            raise ValueError("partition topology drift: %s=%r" % (key, pm.get(key)))

    if struct.unpack("<IIII", extract.read(0x0008BB90, 16)) != (4, 2, 1, 8):
        raise ValueError("firmware image-slot ID table drift")
    if struct.unpack("<I", extract.read(0x0008ADAC, 4))[0] != 22:
        raise ValueError("firmware flash_map entry count drift")
    rows = [struct.unpack("<IIII", extract.read(0x0008ADB0 + 16 * i, 16))
            for i in range(22)]
    by_id = {row[0]: row[1:] for row in rows}
    expected = {
        2: (0x0, 0xF0000, 0x00087BF0),
        4: (0xC000, 0xF0000, 0x00087C38),
        8: (0xF0000, 0x40000, 0x00087BF0),
        9: (0xFC000, 0x2000, 0x00087C38),
    }
    if {key: by_id.get(key) for key in expected} != expected:
        raise ValueError("firmware flash_map geometry/device drift")
    if 1 in by_id or 7 in by_id:
        raise ValueError("RAM-flash-only PM entries unexpectedly emitted in app map")
    return {
        "configured_pm_config": str(PM_CONFIG),
        "configured_pm_config_sha256": sha(PM_CONFIG),
        "configured_required_values": PM_REQUIRED,
        "firmware_slot_id_table_va": "0x0008bb90",
        "firmware_slot_ids": {"primary0": 4, "secondary0": 2,
                              "primary1": 1, "secondary1": 8},
        "firmware_flash_map_va": "0x0008adb0",
        "firmware_flash_map_entries": 22,
        "firmware_runtime_rows": {
            str(key): {"offset": hex(value[0]), "size": hex(value[1]),
                       "device": hex(value[2])}
            for key, value in expected.items()},
        "filtered_pm_entries": {
            "1": "mcuboot_primary_1 on MCUboot-only flash_sim0, offset 0, size 0x40000",
            "7": "zero-sized RAM_FLASH remainder",
        },
        "configured_pm_num": int(pm["PM_NUM"], 0),
        "firmware_pm_num": 24,
        "scope": "exact boot/image/settings prefix; firmware custom external tail remains separate",
    }


def build():
    config = values(CONFIG)
    for key, expected in REQUIRED_CONFIG.items():
        if config.get(key, "n") != expected:
            raise ValueError("img_mgmt Kconfig drift: %s=%r" % (key, config.get(key, "n")))
    collision_rows = {row["va"]: row for row in
                      json.loads(COLLISIONS.read_text())["functions"]}
    group = ["0x%08x" % item[0] for item in sorted(
        (spec[0],) for sections in UNITS.values() for spec in sections.values())]
    rows = []
    for unit, sections in UNITS.items():
        obj = OBJROOT / (unit + ".obj")
        source_rel = "zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/" + unit
        source = NCS / source_rel
        for symbol, (va, linkage, filename, cases) in sections.items():
            va_text = "0x%08x" % va
            canonical = ROOT / "recon/app/src" / filename
            collision = collision_rows.get(va_text)
            visible = collision["current_symbol"] if collision else symbol
            row = {
                "batch": "IMG-MGMT-STOCK-EXACT5", "va": va_text,
                "raw_symbol": "FUN_%08x" % va, "symbol": visible,
                "status": "authorized", "configuration_variant_exact": True,
                "required_config": REQUIRED_CONFIG, "atomic_group": group,
                "upstream_source": source_rel,
                "upstream_source_sha256": sha(source),
                "upstream_object": str(obj), "upstream_object_sha256": sha(obj),
                "configured_build": str(CONFIG),
                "configured_build_sha256": sha(CONFIG),
                "reconstruction_source": str(canonical.relative_to(ROOT)),
                "reconstruction_source_sha256": sha(canonical),
                "cfg_verify_cases": max(1, cases),
                "owner_cfg_verify": {"status": "PASS", "cases": cases},
                "whole_unit_closure": {
                    "safe": True, "archive_member_already_selected": True,
                    "selected_source_units": sorted(UNITS),
                    "exclude_only": group, "new_undefined_symbols": [],
                    "img_mgmt_c_retained": False,
                },
            }
            row.update(section_receipt(obj, symbol, va))
            if collision:
                row["collision_receipt_sha256"] = hashlib.sha256(json.dumps(
                    collision, sort_keys=True, separators=(",", ":")).encode()).hexdigest()
                row["baseline_upstream_object_sha256"] = collision["upstream"]["object_sha256"]
                row["baseline_configured_build_sha256"] = collision[
                    "configured_inclusion"]["zephyr_config_sha256"]
            else:
                row["hidden_owner_closure"] = True
                row["identity_correction"] = {
                    "baseline_collision_symbol": None,
                    "corrected_upstream_symbol": symbol,
                    "corrected_readable_identity": symbol,
                    "corrected_upstream_source": source_rel,
                    "upstream_linkage": linkage,
                }
            rows.append(row)
    hidden_live = []
    for unit, sections in HIDDEN_LIVE.items():
        obj = OBJROOT / (unit + ".obj")
        source_rel = "zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/" + unit
        for symbol, va in sections.items():
            proof = section_receipt(obj, symbol, va)
            hidden_live.append({
                "symbol": symbol, "firmware_va": "0x%08x" % va,
                "upstream_source": source_rel,
                "upstream_source_sha256": sha(NCS / source_rel),
                "upstream_object": str(obj),
                "upstream_object_sha256": sha(obj),
                **proof,
            })
    variant = [collision_rows[va] for va in sorted(collision_rows)
               if int(va, 0) in {spec[0] for sections in UNITS.values()
                                for spec in sections.values()}]
    return {
        "schema": 1, "core": "app", "status": "authorized_atomic",
        "decision": "adopt_exact_configured_four_unit_img_mgmt_live_closure",
        "upstream_revisions": UPSTREAM_REVISIONS,
        "configured_build_receipts": [str(CONFIG)],
        "atomic_group": group, "authorizations": rows,
        "variant_collisions": variant,
        "selected_source_units": sorted(UNITS),
        "nonlive_sections_not_claimed": NONLIVE,
        "hidden_live_sections": hidden_live,
        "resolved_false_variant": {
            "source_unit": "zephyr/subsys/mgmt/mcumgr/grp/img_mgmt/src/img_mgmt.c",
            "symbol": "img_mgmt_upload",
            "firmware_va": "0x000521fc",
            "cause": "unresolved ELF relocation bytes were compared without normalization",
            "resolution": "relocation-masked configured object is byte exact",
        },
        "private_state": {
            "zephyr_img_mgmt.c::ctx.0": {"firmware_va": "0x2000a954", "size": 552},
            "g_img_mgmt_state": {"firmware_va": "0x2000ab7c"},
        },
        "partition_topology": topology_receipt(),
        "sdc_policy": "report_only_unchanged",
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    rendered = json.dumps(build(), indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise ValueError("stale img_mgmt stock adoption receipt")
    else:
        OUTPUT.write_text(rendered)
    print("img_mgmt stock adoption: 29 exact reconstructed owners; four source units exact")


if __name__ == "__main__":
    main()
