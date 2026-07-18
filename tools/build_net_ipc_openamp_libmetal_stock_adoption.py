#!/usr/bin/env python3
"""Build the exact CPUNET IPC/OpenAMP/libmetal stock-source receipt."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
BUILD = Path("/private/tmp/g1-net-spin-ref-0718")
IMAGE = ROOT / "netcore_image.bin"
BASE = 0x01008000
OUTPUT = ROOT / "recon/ownership/net_ipc_openamp_libmetal_stock_adoption.json"
REPORT = ROOT / "recon/analysis/net_ipc_openamp_libmetal_stock_adoption.md"

UNITS = {
    "openamp": {
        "repo": NCS / "modules/lib/open-amp",
        "commit": "42b7c577714b8f22ce82a901e19c1814af4609a8",
        "source": NCS / "modules/lib/open-amp/open-amp/lib/virtio/virtqueue.c",
        "object": BUILD / "modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/virtio/virtqueue.c.obj",
    },
    "libmetal": {
        "repo": NCS / "modules/hal/libmetal",
        "commit": "b91611a6f47dd29fb24c46e5621e797557f80ec6",
        "source": NCS / "modules/hal/libmetal/libmetal/lib/io.c",
        "object": BUILD / "modules/libmetal/libmetal/lib/CMakeFiles/metal.dir/io.c.obj",
    },
    "zephyr": {
        "repo": NCS / "zephyr",
        "commit": "83980fe1679441be9b0e1db556a353f6118fe14f",
        "source": NCS / "zephyr/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c",
        "object": BUILD / "zephyr/CMakeFiles/zephyr.dir/subsys/ipc/ipc_service/backends/ipc_rpmsg_static_vrings.c.obj",
    },
}

TARGETS = (
    (0x010353EC, "FUN_010353ec", "virtqueue_add_consumed_buffer", "openamp",
     ".text.virtqueue_add_consumed_buffer"),
    (0x0103AB0E, "FUN_0103ab0e", "metal_io_block_write", "libmetal",
     ".text.metal_io_block_write"),
    (0x0103AC50, "FUN_0103ac50", "virtqueue_get_available_buffer", "openamp",
     ".text.virtqueue_get_available_buffer"),
    (0x0103A056, "FUN_0103a056", "ipc_static_vrings_shm_size", "zephyr",
     ".text.shm_size"),
)

HELPERS = (
    (0x0103AB86, "metal_io_phys", "openamp", ".text.metal_io_phys"),
    (0x0103ABBE, "metal_io_phys_to_virt", "openamp",
     ".text.metal_io_phys_to_virt"),
)

CALLERS = {
    0x010353EC: {0x010355BC: [0x01035638], 0x0103566C: [0x0103573C],
                 0x0103AFAC: [0x0103AFDC]},
    0x0103AB0E: {0x010355BC: [0x010355F2], 0x0103576C: [0x010357A8]},
    0x0103AC50: {0x0103566C: [0x0103569E, 0x01035750],
                 0x0103AFF2: [0x0103B09A]},
    0x0103A056: {0x0102D708: [0x0102D740, 0x0102D768]},
}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def git(repo, *args):
    return subprocess.check_output(["git", "-C", str(repo), *args], text=True).strip()


def direct_target(firmware, site):
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    rows = list(md.disasm(firmware[site - BASE:site - BASE + 4], site, 1))
    if len(rows) != 1 or rows[0].mnemonic not in ("bl", "b.w"):
        raise ValueError("not a direct branch at 0x%08x" % site)
    match = re.fullmatch(r"#(0x[0-9a-f]+)", rows[0].op_str)
    if not match:
        raise ValueError("non-immediate branch at 0x%08x" % site)
    return int(match.group(1), 16), rows[0].mnemonic


def section_record(unit, section_name, va, firmware):
    with UNITS[unit]["object"].open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(section_name)
        if section is None:
            raise ValueError("missing %s in %s" % (section_name, unit))
        expected = section.data()
        relsec = elf.get_section_by_name(".rel" + section_name)
        relocations = []
        masked = set()
        if relsec is not None:
            symtab = elf.get_section(relsec["sh_link"])
            for rel in relsec.iter_relocations():
                offset = int(rel["r_offset"])
                symbol = symtab.get_symbol(rel["r_info_sym"]).name
                relocations.append({"offset": offset,
                                    "type": int(rel["r_info_type"]),
                                    "symbol": symbol})
                masked.update(range(offset, min(offset + 4, len(expected))))
    actual = firmware[va - BASE:va - BASE + len(expected)]
    if not all(actual[i] == expected[i] for i in range(len(expected))
               if i not in masked):
        raise ValueError("non-relocation bytes differ for %s" % section_name)
    resolved = []
    for rel in relocations:
        if rel["type"] not in (10, 30):  # R_ARM_THM_CALL / R_ARM_THM_JUMP24
            raise ValueError("unexpected state/data relocation in %s" % section_name)
        target, mnemonic = direct_target(firmware, va + rel["offset"])
        resolved.append({**rel, "site": "0x%08x" % (va + rel["offset"]),
                         "mnemonic": mnemonic, "resolved_target": "0x%08x" % target})
    return {
        "section": section_name,
        "section_size": len(expected),
        "section_sha256": sha(expected),
        "relocation_masked_firmware_exact": True,
        "raw_firmware_byte_exact": not relocations and actual == expected,
        "executable_relocations": resolved,
        "mutable_state_relocations": [],
    }


def caller_records(target, firmware):
    rows = []
    for entry, sites in sorted(CALLERS[target].items()):
        calls = []
        for site in sites:
            resolved, mnemonic = direct_target(firmware, site)
            if resolved != target:
                raise ValueError("caller drift at 0x%08x" % site)
            calls.append({"site": "0x%08x" % site, "mnemonic": mnemonic,
                          "resolved_target": "0x%08x" % resolved})
        rows.append({"caller_va": "0x%08x" % entry,
                     "caller_raw_identity": "FUN_%08x" % entry,
                     "direct_calls": calls})
    return rows


def unit_records():
    compile_db = json.loads((BUILD / "compile_commands.json").read_text())
    records = {}
    for name, unit in UNITS.items():
        if git(unit["repo"], "rev-parse", "HEAD") != unit["commit"]:
            raise ValueError("%s checkout drift" % name)
        source = unit["source"].read_bytes()
        obj = unit["object"].read_bytes()
        command = next(row["command"] for row in compile_db
                       if Path(row["file"]) == unit["source"])
        records[name] = {
            "repository": str(unit["repo"]), "commit": unit["commit"],
            "source": str(unit["source"]), "source_sha256": sha(source),
            "configured_object": str(unit["object"]),
            "configured_object_sha256": sha(obj),
            "compile_command_sha256": sha(command.encode()),
            "compile_contract": {
                "optimization": "-Os", "cpu": "cortex-m33+nodsp",
                "abi": "AAPCS Thumb soft-float CPUNET",
                "function_sections": True,
                "virtio_device_only": "-DVIRTIO_DEVICE_ONLY" in command,
            },
        }
    return records


def build():
    firmware = IMAGE.read_bytes()
    units = unit_records()
    helpers = []
    helper_targets = {}
    for va, identity, unit, section in HELPERS:
        row = section_record(unit, section, va, firmware)
        row.update({"va": "0x%08x" % va, "identity": identity, "unit": unit})
        helpers.append(row)
        helper_targets[identity] = va
    functions = []
    for va, raw, identity, unit, section in TARGETS:
        row = section_record(unit, section, va, firmware)
        row.update({"va": "0x%08x" % va, "raw_identity": raw,
                    "resolved_identity": identity, "unit": unit,
                    "callers": caller_records(va, firmware),
                    "preserve_raw_backmap": True})
        functions.append(row)
    expected_relocs = {
        "metal_io_phys_to_virt": {"metal_io_phys": "0x0103ab86"},
        "virtqueue_get_available_buffer": {
            "metal_io_phys_to_virt": "0x0103abbe"},
    }
    actual_relocs = {}
    for row in helpers + functions:
        if row["executable_relocations"]:
            actual_relocs[row.get("identity", row.get("resolved_identity"))] = {
                rel["symbol"]: rel["resolved_target"]
                for rel in row["executable_relocations"]}
    if actual_relocs != expected_relocs:
        raise ValueError("helper relocation closure changed: %r" % actual_relocs)
    return {
        "schema_version": 1,
        "scope": "CPUNET selected public IPC/OpenAMP/libmetal source closure",
        "firmware_sha256": sha(firmware),
        "configured_sdk": {
            "ncs": "v2.5.1", "zephyr": "v3.4.99-ncs1-1",
            "zephyr_commit": UNITS["zephyr"]["commit"],
            "gcc": "Zephyr SDK 0.16.5-1 GCC 12.2.0",
            "config": ["CONFIG_LIBMETAL=y", "CONFIG_OPENAMP=y",
                       "CONFIG_OPENAMP_SLAVE=y", "CONFIG_IPC_SERVICE=y",
                       "CONFIG_IPC_SERVICE_BACKEND_RPMSG=y",
                       "CONFIG_IPC_SERVICE_STATIC_VRINGS=y",
                       "CONFIG_IPC_SERVICE_STATIC_VRINGS_MEM_ALIGNMENT=4"],
        },
        "version_claim": {
            "exact_build_inputs": True,
            "module_revisions_are_shared_across_ncs_2_4_through_2_6": True,
            "interpretation": ("The exact configured NCS 2.5.1 objects prove source and "
                               "configuration ownership. The module commits are unchanged "
                               "in NCS 2.4.0 through 2.6.1, so these bodies alone do not "
                               "uniquely fingerprint the top-level NCS patch release."),
        },
        "units": units,
        "supporting_helper_closure": helpers,
        "functions": functions,
        "manifest_functions": [{"va": row["va"], "raw_name": row["raw_identity"],
                                "resolved_name": row["resolved_identity"],
                                "owner": row["unit"], "action": "adopt_stock_source"}
                               for row in functions],
        "policy": {"selected_sections_only": True,
                   "no_private_or_sdc_removal": True,
                   "shared_generated_trees_not_regenerated": True},
    }


def markdown(receipt):
    lines = ["# CPUNET IPC/OpenAMP/libmetal stock adoption", "",
             "All four selected functions match their configured NCS 2.5.1 object sections; "
             "only call relocations are masked, and every one resolves into the proven helper closure.", "",
             "| Address | Raw back-map | Stock identity | Owner | Match |", "|---|---|---|---|---|"]
    for row in receipt["functions"]:
        match = "raw exact" if row["raw_firmware_byte_exact"] else "relocation-masked exact"
        lines.append("| `{}` | `{}` | `{}` | {} | {} |".format(
            row["va"], row["raw_identity"], row["resolved_identity"], row["unit"], match))
    lines += ["", "The static-vrings symbol is the compiler-emitted `.text.shm_size` helper; "
              "`ipc_static_vrings_shm_size` is its collision-safe durable name.", "",
              "Version precision: OpenAMP `{}` and libmetal `{}` are the exact manifest commits. "
              "Those revisions are shared by NCS 2.4.0 through 2.6.1, so the functions do not "
              "uniquely identify a top-level patch version; the configured build is NCS 2.5.1 / "
              "Zephyr v3.4.99-ncs1-1.".format(UNITS["openamp"]["commit"], UNITS["libmetal"]["commit"]), "",
              "No selected section has a mutable-state relocation. This receipt does not remove "
              "private/SDC code and does not regenerate shared named, symbolized, manifest, or CMake outputs.", ""]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    receipt = build()
    expected_json = json.dumps(receipt, indent=2, sort_keys=True) + "\n"
    expected_md = markdown(receipt)
    if args.check:
        if OUTPUT.read_text() != expected_json or REPORT.read_text() != expected_md:
            raise SystemExit("generated IPC/OpenAMP/libmetal evidence is stale")
    else:
        OUTPUT.write_text(expected_json)
        REPORT.write_text(expected_md)


if __name__ == "__main__":
    main()
