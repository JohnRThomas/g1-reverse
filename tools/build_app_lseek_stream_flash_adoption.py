#!/usr/bin/env python3
"""Build exact atomic-adoption evidence for lseek and stream/flash_img."""

import hashlib
import json
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-root-topology-exact5-0718")
CONFIG = BUILD / "zephyr/.config"
IMAGE = ROOT / "app_update.bin"
OUTPUT = ROOT / "recon/ownership/app_lseek_stream_flash_atomic_adoption.json"
NCS = Path("/Users/freedomcoder/ncs251")

FDTABLE = BUILD / "zephyr/CMakeFiles/zephyr.dir/lib/os/fdtable.c.obj"
STREAM = BUILD / "zephyr/CMakeFiles/zephyr.dir/subsys/storage/stream/stream_flash.c.obj"
FLASH_IMG = BUILD / "zephyr/CMakeFiles/zephyr.dir/subsys/dfu/img_util/flash_img.c.obj"

CONFIG_SHA256 = "a33a336176935d1d2e31ba2c79f558a0952f4c8cdffb93fccc654bd02f126efe"
OBJECT_SHA256 = {
    FDTABLE: "c2f630f72d7e4648bcaed7fab3257bb97823522ff7957ece6c0e3e0733f7f153",
    STREAM: "764cc771c620750348ef33bc8ec922514fc67e63d2a9ec940c891db8756038c6",
    FLASH_IMG: "08ae33e350c5738130059d0a4dd8025fdb2f18aaf7ab7e9dccd547e488ff46ef",
}
SOURCE_SHA256 = {
    "zephyr/lib/os/fdtable.c": "98dba32ba26cbf283eef344aa42c705b8956b378163287ec1f3016df04c83c95",
    "zephyr/subsys/storage/stream/stream_flash.c": "1fc92289e8c4aee886ced85deed8f5d9a76d4ed430235368164c821e25705a64",
    "zephyr/subsys/dfu/img_util/flash_img.c": "3e8b14ad6f9312313525cf44e63d8f72040353eb6f00cbb77265aabbef7c0be2",
}

LSEEK_GROUP = ["0x0004b17c"]
FLASH_GROUP = [
    "0x0004e124", "0x0004e1ac", "0x0004e2b4", "0x0007f064",
    "0x0007f088", "0x0007f110", "0x0007f150",
]

# VA, raw owner, corrected upstream symbol, selected object, section, true code
# extent, source, linkage, cfg-directed checks, direct callers.
OWNERS = [
    (0x4B17C, "lseek", "lseek", FDTABLE, ".text.lseek", 52,
     "zephyr/lib/os/fdtable.c", "public", 1, ["0x00078598"]),
    (0x4E124, "FUN_0004e124", "stream_flash_erase_page", STREAM,
     ".text.stream_flash_erase_page", 136,
     "zephyr/subsys/storage/stream/stream_flash.c", "public", 4,
     ["0x0004e1ac", "0x0007f110"]),
    (0x4E1AC, "stream_flash_flush_buffer", "flash_sync", STREAM,
     ".text.flash_sync", 244,
     "zephyr/subsys/storage/stream/stream_flash.c", "translation_unit_local", 40,
     ["0x0007f088"]),
    (0x4E2B4, "stream_flash_init", "stream_flash_init", STREAM,
     ".text.stream_flash_init", 174,
     "zephyr/subsys/storage/stream/stream_flash.c", "public", 9,
     ["0x0007f150"]),
    (0x7F064, "FUN_0007f064", "flash_get_write_block_size", STREAM,
     ".text.flash_get_write_block_size", 12,
     "zephyr/subsys/storage/stream/stream_flash.c", "translation_unit_local", 40,
     ["0x0004e1ac", "0x0004e2b4"]),
    (0x7F088, "FUN_0007f088", "stream_flash_buffered_write", STREAM,
     ".text.stream_flash_buffered_write", 136,
     "zephyr/subsys/storage/stream/stream_flash.c", "public", 44,
     ["0x0007f110"]),
    (0x7F110, "FUN_0007f110", "flash_img_buffered_write", FLASH_IMG,
     ".text.flash_img_buffered_write", 64,
     "zephyr/subsys/dfu/img_util/flash_img.c", "public", 42,
     ["0x00051870"]),
    (0x7F150, "FUN_0007f150", "flash_img_init_id", FLASH_IMG,
     ".text.flash_img_init_id", 66,
     "zephyr/subsys/dfu/img_util/flash_img.c", "public", 40,
     ["0x00051870"]),
]

HIDDEN_EXACT = [
    (0x4E0F8, "find_flash_total_size.part.0", STREAM,
     ".text.find_flash_total_size.part.0"),
    (0x7F070, "find_flash_total_size", STREAM,
     ".text.find_flash_total_size"),
]


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def normalized_section(va, obj_path, section_name):
    with Path(obj_path).open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(section_name)
        if section is None:
            raise ValueError("missing section %s in %s" % (section_name, obj_path))
        candidate = bytearray(section.data())
        reloc = elf.get_section_by_name(".rel" + section_name)
        offsets = [] if reloc is None else sorted(
            int(row["r_offset"]) for row in reloc.iter_relocations())
    firmware = bytearray(IMAGE.read_bytes()[
        va - 0xC000:va - 0xC000 + len(candidate)])
    for offset in offsets:
        candidate[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if candidate != firmware:
        raise ValueError("normalized mismatch at 0x%08x" % va)
    return {
        "upstream_symbol_size": len(candidate),
        "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
    }


def authorization(owner):
    (va, baseline, symbol, obj, section, extent, source, linkage,
     cases, callers) = owner
    group = LSEEK_GROUP if va == 0x4B17C else FLASH_GROUP
    raw = "FUN_%08x" % va
    canonical = ROOT / "recon/app/src" / (raw + ".c")
    normalized = normalized_section(va, obj, section)
    required = ({"CONFIG_POSIX_API": "y", "CONFIG_POSIX_MAX_FDS": "16"}
                if va == 0x4B17C else
                {"CONFIG_IMG_ERASE_PROGRESSIVELY": "y",
                 "CONFIG_STREAM_FLASH": "y", "CONFIG_STREAM_FLASH_ERASE": "y"})
    return {
        "status": "authorized",
        "batch": "ROOT-LSEEK" if va == 0x4B17C else "ROOT-STREAM-FLASH",
        "va": "0x%08x" % va,
        "raw_symbol": raw,
        "symbol": baseline,
        "instruction_exact": True,
        "configuration_variant_exact": True,
        "cfg_verify_cases": cases,
        "firmware_code_size": extent,
        "upstream_code_size": extent,
        "literal_pool_tail_size": normalized["upstream_symbol_size"] - extent,
        "upstream_object": str(obj),
        "upstream_object_sha256": OBJECT_SHA256[obj],
        "upstream_source": source,
        "upstream_source_sha256": SOURCE_SHA256[source],
        "configured_build": str(CONFIG),
        "configured_build_sha256": CONFIG_SHA256,
        "required_config": required,
        "reconstruction_source": str(canonical),
        "reconstruction_source_sha256": sha(canonical),
        "atomic_group": group,
        "callers": callers,
        "hidden_owner_closure": True,
        "identity_correction": {
            "baseline_collision_symbol": baseline,
            "corrected_readable_identity": symbol,
            "corrected_upstream_symbol": symbol,
            "corrected_upstream_source": source,
            "upstream_linkage": linkage,
            "raw_identity": raw,
        },
        "whole_unit_closure": {
            "safe": True,
            "exclude_only": group,
            "new_undefined_symbols": [],
            "raw_aliases_preserved": True,
            "normal_gc_required_for_dead_sdk_helpers": True,
        },
        **normalized,
    }


def build():
    if sha(CONFIG) != CONFIG_SHA256:
        raise ValueError("exact5 config drift")
    for path, expected in OBJECT_SHA256.items():
        if sha(path) != expected:
            raise ValueError("configured object drift: %s" % path)
    for source, expected in SOURCE_SHA256.items():
        if sha(NCS / source) != expected:
            raise ValueError("pinned source drift: %s" % source)
    authorizations = [authorization(owner) for owner in OWNERS]
    hidden = []
    for va, symbol, obj, section in HIDDEN_EXACT:
        hidden.append({
            "va": "0x%08x" % va,
            "symbol": symbol,
            "upstream_object": str(obj),
            "upstream_source": "zephyr/subsys/storage/stream/stream_flash.c",
            **normalized_section(va, obj, section),
        })
    return {
        "schema": 1,
        "core": "app",
        "status": "authorized_atomic",
        "decision": "adopt_exact_lseek_and_progressive_stream_flash_closure",
        "configured_build_receipts": [str(CONFIG)],
        "required_project_config": {"CONFIG_IMG_ERASE_PROGRESSIVELY": "y"},
        "atomic_groups": {"lseek": LSEEK_GROUP, "stream_flash_and_flash_img": FLASH_GROUP},
        "authorizations": authorizations,
        "hidden_exact_source_sections": hidden,
        "caller_retarget": {
            "0x00051870": ["flash_img_init_id", "flash_img_buffered_write"],
            "preserve_raw_backmap": ["FUN_0007f150", "FUN_0007f110"],
        },
        "dead_sdk_helpers_must_gc": [
            "stream_flash_bytes_written", "flash_img_bytes_written", "flash_img_init"
        ],
        "pthread_attr_getstack": "retained_unchanged",
        "sdc_policy": "report_only_unchanged",
    }


def main():
    OUTPUT.write_text(json.dumps(build(), indent=1) + "\n")
    print("wrote", OUTPUT)


if __name__ == "__main__":
    main()
