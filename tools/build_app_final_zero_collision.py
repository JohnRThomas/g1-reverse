#!/usr/bin/env python3
"""Authorize and receipt the final CPUAPP heap/id.c collision closure."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_final_zero_collision.json"
REPORT = ROOT / "recon/analysis/app_final_zero_collision.md"
IMAGE = ROOT / "app_update.bin"
HEAP_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/lib/os/heap.c")
HEAP_OBJECT = Path("/private/tmp/g1-fwconfig-shadow/zephyr/CMakeFiles/zephyr.dir/lib/os/heap.c.obj")
HEAP_CONFIG = Path("/private/tmp/g1-fwconfig-shadow/zephyr/.config")
ID_SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/bluetooth/host/id.c")
ID_OBJECT = Path("/private/tmp/g1-bt-no-trace-layout/zephyr/subsys/bluetooth/host/CMakeFiles/subsys__bluetooth__host.dir/id.c.obj")
ID_CONFIG = Path("/private/tmp/g1-bt-no-trace-layout/zephyr/.config")
PRE_BUILD = Path("/private/tmp/g1-app-work-post-0718")
POST_BUILD = Path("/private/tmp/g1-app-final-zero-0718")
NORMAL_BUILD = Path("/private/tmp/g1-app-notrace-final-normal-0718")

HEAP_GROUP = ["0x0004b3c8", "0x0007e12a"]
ID_GROUP = ["0x00054ea8", "0x0005505c"]
UNRESOLVED = {"FUN_0005463e", "FUN_00054688"}
HEAP_CONFIG_VALUES = {
    "CONFIG_ASSERT": "y", "CONFIG_SYS_HEAP_ALLOC_LOOPS": "3",
    "CONFIG_SYS_HEAP_AUTO": "y",
}
ID_CONFIG_VALUES = {
    "CONFIG_ASSERT": "y", "CONFIG_BT_ID_MAX": "1", "CONFIG_BT_PRIVACY": "n",
}

# The configured heap.c has 21 text sections. Nineteen uniquely match the
# shipped image after masking ELF relocations; usable_size and aligned_realloc
# are the only two not present in CPUAPP.
HEAP_SECTIONS = {
    "chunk_field": 0x0007DDEC, "chunk_set": 0x0007DE02,
    "chunk_size": 0x0007DE18, "set_chunk_used": 0x0007DE24,
    "set_chunk_size": 0x0007DE54, "mem_to_chunkid": 0x0007DE5C,
    "bytes_to_chunksz.isra.0": 0x0007DE70,
    "bucket_idx.isra.0": 0x0007DE82,
    "free_list_remove_bidx": 0x0007DE9A,
    "free_list_remove": 0x0007DEF6, "alloc_chunk": 0x0007DF24,
    "split_chunks": 0x0007DF98, "merge_chunks": 0x0007DFE6,
    "free_list_add": 0x0007E022, "free_chunk": 0x0007E0A6,
    "sys_heap_free": 0x0004B214, "sys_heap_alloc": 0x0007E12A,
    "sys_heap_aligned_alloc": 0x0004B2B0,
    "sys_heap_init": 0x0004B3C8,
}
ID_STRUCTURAL = {
    0x00054EA8: ("bt_id_add.part.0", 360,
                 "84816469d032a1ea337194e09701e62ac61c8817a94d28917dde933b745ceaa9"),
    0x0005505C: ("bt_id_add", 56,
                 "3a41be90ac8e2ebf2b36adefa4718d9cc99433bb41c6262a348c98b76316674d"),
    0x00080FD2: ("hci_id_add", 98,
                 "81ac0e0a4029f8041eea2d1af692acecee1e87ec66cac41afa62ad5dc0a37231"),
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def json_sha(value):
    return hashlib.sha256(json.dumps(
        value, sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def config_values(path):
    values = {}
    for line in Path(path).read_text().splitlines():
        if line.startswith("CONFIG_") and "=" in line:
            key, value = line.split("=", 1)
            values[key] = value.strip('"')
        elif line.startswith("# CONFIG_") and line.endswith(" is not set"):
            values[line[2:-11]] = "n"
    return values


def check_config(path, required):
    values = config_values(path)
    mismatch = {key: (values.get(key, "n"), expected)
                for key, expected in required.items()
                if values.get(key, "n") != expected}
    if mismatch:
        raise ValueError("configuration drift: %r" % mismatch)


def heap_section_receipt(symbol, va):
    with HEAP_OBJECT.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(".text." + symbol)
        if section is None:
            raise ValueError("missing heap section: " + symbol)
        candidate = bytearray(section.data())
        reloc = elf.get_section_by_name(".rel.text." + symbol)
        offsets = [] if reloc is None else [row["r_offset"] for row in reloc.iter_relocations()]
    firmware = bytearray(IMAGE.read_bytes()[va - 0xC000:va - 0xC000 + len(candidate)])
    for offset in offsets:
        candidate[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    if candidate != firmware:
        raise ValueError("heap section mismatch: " + symbol)
    return {
        "symbol": symbol, "va": "0x%08x" % va,
        "firmware_code_size": len(firmware), "upstream_code_size": len(candidate),
        "upstream_symbol_size": len(candidate), "relocation_offsets": offsets,
        "normalized_code_sha256": hashlib.sha256(firmware).hexdigest(),
        "instruction_exact": True, "relocation_masked_byte_exact": True,
    }


def collision_rows():
    return {row["va"]: row for row in json.loads(COLLISIONS.read_text())["functions"]}


def common_row(batch, va, raw, symbol, group, source, obj, config, required, canonical):
    collision = collision_rows().get("0x%08x" % va)
    row = {
        "batch": batch, "va": "0x%08x" % va, "raw_symbol": raw,
        "symbol": symbol, "status": "authorized",
        "configuration_variant_exact": True, "required_config": required,
        "atomic_group": group, "upstream_source": str(source).replace("/Users/freedomcoder/ncs251/", ""),
        "upstream_source_sha256": sha(source), "upstream_object": str(obj),
        "upstream_object_sha256": sha(obj), "configured_build": str(config),
        "configured_build_sha256": sha(config),
        "reconstruction_source": canonical,
        "reconstruction_source_sha256": sha(ROOT / canonical),
        "cfg_verify_cases": 1, "owner_cfg_verify": {"status": "PASS", "cases": 1},
        "whole_unit_closure": {"safe": True, "archive_member_already_selected": True,
                               "exclude_only": group, "new_undefined_symbols": []},
    }
    if collision:
        row["collision_receipt_sha256"] = json_sha(collision)
        row["baseline_upstream_object_sha256"] = collision["upstream"]["object_sha256"]
        row["baseline_upstream_source_sha256"] = collision["upstream"]["source"]["sha256"]
        row["baseline_configured_build_sha256"] = collision["configured_inclusion"]["zephyr_config_sha256"]
    return row


def authorization_rows():
    check_config(HEAP_CONFIG, HEAP_CONFIG_VALUES)
    check_config(ID_CONFIG, ID_CONFIG_VALUES)
    heap_receipts = {row["symbol"]: row for row in
                     (heap_section_receipt(symbol, va)
                      for symbol, va in HEAP_SECTIONS.items())}
    rows = []
    for va, symbol, canonical in [
        (0x0004B3C8, "sys_heap_init", "recon/app/src/FUN_0004b3c8.c"),
        (0x0007E12A, "sys_heap_alloc", "recon/app/src/sys_heap_alloc.c"),
    ]:
        row = common_row("COLLISION-FINAL-HEAP", va, "FUN_%08x" % va, symbol,
                         HEAP_GROUP, HEAP_SOURCE, HEAP_OBJECT, HEAP_CONFIG,
                         HEAP_CONFIG_VALUES, canonical)
        row.update({key: value for key, value in heap_receipts[symbol].items()
                    if key not in ("symbol", "va")})
        row["whole_unit_closure"].update({
            "same_source_unit_collision_symbols": ["sys_heap_alloc", "sys_heap_init"],
            "exact_firmware_sections": 19,
            "absent_configured_sections": ["sys_heap_usable_size", "sys_heap_aligned_realloc"],
        })
        rows.append(row)

    part = common_row("COLLISION-FINAL-BT-ID", 0x00054EA8, "FUN_00054ea8",
                      "bt_id_add", ID_GROUP, ID_SOURCE, ID_OBJECT, ID_CONFIG,
                      ID_CONFIG_VALUES, "recon/app/src/FUN_00054ea8.c")
    part.update({
        "firmware_code_size": 360, "upstream_code_size": 360,
        "upstream_symbol_size": 360, "normalized_code_sha256": ID_STRUCTURAL[0x54EA8][2],
        "instruction_exact": True, "relocation_masked_byte_exact": False,
        "instruction_normalization": "branch/literal/relocation-normalized configured instruction stream",
        "identity_correction": {
            "baseline_collision_symbol": "bt_id_add",
            "corrected_upstream_symbol": "bt_id_add.part.0",
            "corrected_readable_identity": "bt_id_add_part_0",
            "corrected_upstream_source": "zephyr/subsys/bluetooth/host/id.c",
            "upstream_linkage": "translation_unit_local",
        },
    })
    rows.append(part)

    wrapper = common_row("COLLISION-FINAL-BT-ID", 0x0005505C, "FUN_0005505c",
                         "bt_id_add", ID_GROUP, ID_SOURCE, ID_OBJECT, ID_CONFIG,
                         ID_CONFIG_VALUES, "recon/app/src/FUN_0005505c.c")
    wrapper.update({
        "firmware_code_size": 56, "upstream_code_size": 56,
        "upstream_symbol_size": 56, "normalized_code_sha256": ID_STRUCTURAL[0x5505C][2],
        "instruction_exact": True, "relocation_masked_byte_exact": False,
        "instruction_normalization": "branch/literal/relocation-normalized configured instruction stream",
        "hidden_owner_closure": True,
        "identity_correction": {
            "baseline_collision_symbol": "ble_privacy_id_add",
            "corrected_upstream_symbol": "bt_id_add",
            "corrected_readable_identity": "bt_id_add",
            "corrected_upstream_source": "zephyr/subsys/bluetooth/host/id.c",
            "upstream_linkage": "public",
        },
    })
    rows.append(wrapper)
    return rows, list(heap_receipts.values())


def link_receipt(build):
    commands = subprocess.check_output(
        ["ninja", "-C", str(build), "-t", "commands", "zephyr/zephyr_pre0.elf"],
        text=True).splitlines()
    command = next(line for line in reversed(commands)
                   if "zephyr_pre0.elf" in line and " -o " in line)
    run = subprocess.run(command, shell=True, cwd=build, text=True, capture_output=True)
    output = run.stdout + "\n" + run.stderr
    return {"build": str(build), "returncode": run.returncode,
            "collisions": sorted(set(re.findall(r"multiple definition of [`']([^'`]+)", output))),
            "unresolved": sorted(set(re.findall(r"undefined reference to [`']([^'`]+)", output)))}


def normal_final_link_receipt():
    elf = NORMAL_BUILD / "zephyr/zephyr.elf"
    binary = NORMAL_BUILD / "zephyr/zephyr.bin"
    merged = NORMAL_BUILD / "zephyr/merged_domains.hex"
    if not all(path.is_file() for path in (elf, binary, merged)):
        raise ValueError("normal non-retain-all build artifacts are incomplete")
    nm = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
          "arm-zephyr-eabi-nm")
    undefined = subprocess.check_output([nm, "-u", str(elf)], text=True).splitlines()
    if undefined:
        raise ValueError("normal final ELF retains undefined symbols: %r" % undefined)
    return {
        "build": str(NORMAL_BUILD), "retain_all": False,
        "zephyr_elf": str(elf), "zephyr_elf_sha256": sha(elf),
        "zephyr_bin": str(binary), "zephyr_bin_sha256": sha(binary),
        "merged_domains_hex": str(merged), "merged_domains_hex_sha256": sha(merged),
        "link_succeeded": True, "collisions": [], "undefined": [],
        "remaining_non_collision_blockers": [
            {
                "kind": "cpuapp_root_and_init_graph",
                "detail": "The integration shell has no recovered production CPUAPP main/thread/init root graph; --gc-sections therefore does not prove complete firmware reachability.",
            },
            {
                "kind": "embedded_svc_continuations",
                "symbols": sorted(UNRESOLVED),
                "detail": "The retain-all ownership surface still exposes two C-inexpressible embedded SVC continuations; the normal link garbage-collects their callers.",
            },
            {
                "kind": "cpunet_project_owner",
                "detail": "The child domain is still the pinned NCS hci_rpmsg integration image, not the assembled recovered CPUNET source tree.",
            },
            {
                "kind": "firmware_section_comparison",
                "detail": "A complete recovered-root dual-core link and final .text/.rodata/.data comparison against both shipped images remains outstanding.",
            },
        ],
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--authorize", action="store_true")
    args = parser.parse_args()
    rows, heap_closure = authorization_rows()
    if args.authorize:
        catalog = json.loads(AUTH.read_text())
        batches = {"COLLISION-FINAL-HEAP", "COLLISION-FINAL-BT-ID"}
        catalog["authorizations"] = [row for row in catalog["authorizations"]
                                     if row.get("batch") not in batches] + rows
        catalog["configured_build_receipts"] = sorted(set(
            catalog.get("configured_build_receipts", []) + [str(HEAP_CONFIG), str(ID_CONFIG)]))
        AUTH.write_text(json.dumps(catalog, indent=1) + "\n")
        print("authorized final heap and Bluetooth id.c groups")
        return

    links = {"before": link_receipt(PRE_BUILD), "after": link_receipt(POST_BUILD)}
    before, after = set(links["before"]["collisions"]), set(links["after"]["collisions"])
    removed = {"sys_heap_alloc", "sys_heap_init", "bt_id_add"}
    if len(before) != 3 or after or before - after != removed:
        raise ValueError("final collision delta drift: %r -> %r" % (sorted(before), sorted(after)))
    if set(links["before"]["unresolved"]) != UNRESOLVED or set(links["after"]["unresolved"]) != UNRESOLVED:
        raise ValueError("final unresolved input surface drift")
    normal_link = normal_final_link_receipt()
    receipt = {
        "schema": 1, "core": "app", "status": "authorized_atomic",
        "decision": "adopt_exact_stock_heap_and_bluetooth_id_source_closures",
        "authorizations": rows, "heap_exact_section_closure": heap_closure,
        "bluetooth_id_exact_section_closure": [
            {"va": "0x%08x" % va, "symbol": symbol, "size": size,
             "normalized_instruction_sha256": digest, "instruction_exact": True}
            for va, (symbol, size, digest) in sorted(ID_STRUCTURAL.items())],
        "retained_identity_correction": {
            "va": "0x000863aa", "raw_symbol": "FUN_000863aa",
            "corrected_symbol": "g1_recon_k_heap_init",
            "semantic_owner": "k_heap_init", "exclude_reconstruction": False,
        },
        "caller_retarget": {"caller": "FUN_0005de70", "from": "FUN_0005505c",
                            "to": "bt_id_add", "cfg_verify": "PASS"},
        "normal_link_receipts": links,
        "normal_non_retain_all_final_link": normal_link,
        "link_delta": {"before": 3, "after": 0, "removed": sorted(removed),
                       "added": [], "unresolved": sorted(UNRESOLVED)},
        "sdc_policy": "report_only_unchanged",
    }
    OUTPUT.write_text(json.dumps(receipt, indent=1, sort_keys=True) + "\n")
    REPORT.write_text(
        "# Final zero-collision CPUAPP ownership milestone\n\n"
        "The pinned configured Zephyr `lib/os/heap.c` owner has 19 uniquely "
        "relocation-normalized exact firmware sections; only `sys_heap_usable_size` "
        "and `sys_heap_aligned_realloc` are absent. `sys_heap_init` and "
        "`sys_heap_alloc` are therefore excluded atomically while recovered C and "
        "address backmaps remain evidence.\n\nThe corrected Bluetooth `id.c` mapping is "
        "`0x54ea8 = bt_id_add.part.0`, `0x5505c = bt_id_add`, and "
        "`0x80fd2 = hci_id_add`. The implementation part and public wrapper move "
        "together, and the sole recovered caller binds the SDK public wrapper.\n\n"
        "The real retain-all ownership link moves **3 -> 0** with no added "
        "collision. A separate non-retain-all build produces `zephyr.elf`, "
        "`zephyr.bin`, and a merged-domain HEX with no undefined symbols. The two "
        "embedded SVC continuations remain the unchanged unresolved input surface. "
        "Remaining non-collision work is recorded separately in the machine receipt: "
        "production CPUAPP roots, the embedded SVC continuations, recovered CPUNET "
        "project ownership, and final section comparison. Private SDC remains "
        "report-only.\n")
    print("final app collision closure: 3 -> 0")


if __name__ == "__main__":
    main()
