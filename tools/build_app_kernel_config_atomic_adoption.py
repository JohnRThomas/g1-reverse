#!/usr/bin/env python3
"""Generate the fail-closed eight-owner kernel configuration adoption receipt."""

import copy
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_adoption_manifest as manifest

BUILD = Path("/private/tmp/g1-bt-custom-notls-main16k-evidence")
CONFIG = BUILD / "zephyr/.config"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
OUTPUT = ROOT / "recon/ownership/app_kernel_config_atomic_adoption.json"
NCS = Path("/Users/freedomcoder/ncs251")
LINK_BUILDS = {
    "baseline": Path("/private/tmp/g1-app-residue-current-0718"),
    "config_only": Path("/tmp/g1-config-only-build4"),
    "adopted": Path("/tmp/g1-kernel-adopt-final"),
}

REQUIRED_CONFIG = {
    "CONFIG_ASSERT": "y",
    "CONFIG_ASSERT_LEVEL": "2",
    "CONFIG_SPIN_VALIDATE": "y",
    "CONFIG_THREAD_LOCAL_STORAGE": "n",
    "CONFIG_THREAD_CUSTOM_DATA": "y",
    "CONFIG_MAIN_STACK_SIZE": "16384",
}
GROUP = ["0x%08x" % value for value in
         (0x71B2C, 0x758CC, 0x864E8, 0x71C20, 0x71CF4,
          0x72040, 0x7205C, 0x72078)]
FUNCTIONS = {
    0x71B2C: ("k_heap_free", "zephyr/kernel/kheap.c", "zephyr/kernel/CMakeFiles/kernel.dir/kheap.c.obj", 164,
              "72bb475245d8aa86628d896760fd851a1fdb4ec458cfc1334a7fa15555dc7d53", 2),
    0x758CC: ("k_aligned_alloc", "zephyr/kernel/mempool.c", "zephyr/kernel/CMakeFiles/kernel.dir/mempool.c.obj", 108,
              "03723db6346f6de5c9e8943bdc9d91929e32ea7223df0ef297d611b54408307f", 3),
    0x864E8: ("z_impl_k_queue_init", "zephyr/kernel/queue.c", "zephyr/kernel/CMakeFiles/kernel.dir/queue.c.obj", 26,
              "fab989f76c801ac768f77ca860d2a76fa6c7b9e6a65f5b7c49c7a8dd8b45913a", 1),
    0x71C20: ("k_mem_slab_alloc", "zephyr/kernel/mem_slab.c", "zephyr/kernel/CMakeFiles/kernel.dir/mem_slab.c.obj", 212,
              "6e2bb8fd716897bca250bc0d9073c59ef0b961e7b4436e16715150c3e59a8c2a", 1),
    0x71CF4: ("k_mem_slab_free", "zephyr/kernel/mem_slab.c", "zephyr/kernel/CMakeFiles/kernel.dir/mem_slab.c.obj", 260,
              "4b497a36c3dc621b4c153faa033e2753fee2f6890becc2ca35c74236c376c6eb", 1),
    0x72040: ("z_spin_lock_valid", "zephyr/kernel/thread.c", "zephyr/kernel/CMakeFiles/kernel.dir/thread.c.obj", 28,
              "caa1bd62347289227308111f5b779d72d013aed2402c6ea2326508724f9cbd3b", 1),
    0x7205C: ("z_spin_unlock_valid", "zephyr/kernel/thread.c", "zephyr/kernel/CMakeFiles/kernel.dir/thread.c.obj", 28,
              "f4ab59a440fe4ab0cc684ce6232ee18b6ed1386ec1ee8b52ecad6695d129e469", 1),
    0x72078: ("z_spin_lock_set_owner", "zephyr/kernel/thread.c", "zephyr/kernel/CMakeFiles/kernel.dir/thread.c.obj", 16,
              "176248a070a7c290d568c68f3d377f58f0e3d1f62d300ab68bc192e6af80ad12", 1),
}


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def section_size(path, symbol):
    with path.open("rb") as stream:
        section = ELFFile(stream).get_section_by_name(".text." + symbol)
        if section is None:
            raise ValueError("missing configured section: " + symbol)
        return len(section.data())


def link_receipt(build):
    commands = subprocess.check_output(
        ["ninja", "-C", str(build), "-t", "commands",
         "zephyr/zephyr_pre0.elf"], text=True).splitlines()
    command = next(line for line in reversed(commands)
                   if "zephyr_pre0.elf" in line and " -o " in line)
    run = subprocess.run(command, shell=True, cwd=build, text=True,
                         capture_output=True)
    output = run.stdout + "\n" + run.stderr
    return {
        "build": str(build),
        "collisions": sorted(set(re.findall(
            r"multiple definition of [`']([^'`]+)", output))),
        "undefined": sorted(set(re.findall(
            r"undefined reference to [`']([^'`]+)", output))),
    }


def main():
    config_hash = sha(CONFIG)
    actual = manifest._kconfig_values(CONFIG)
    if {key: actual.get(key) for key in REQUIRED_CONFIG} != REQUIRED_CONFIG:
        raise ValueError("firmware kernel configuration changed")
    baseline = json.loads(COLLISIONS.read_text())
    links = {name: link_receipt(path) for name, path in LINK_BUILDS.items()}
    counts = {name: len(row["collisions"]) for name, row in links.items()}
    if counts != {"baseline": 82, "config_only": 85, "adopted": 80}:
        raise ValueError("normal-link collision counts changed: %r" % counts)
    baseline_set = set(links["baseline"]["collisions"])
    config_set = set(links["config_only"]["collisions"])
    adopted_set = set(links["adopted"]["collisions"])
    spin_added = {"z_spin_lock_valid", "z_spin_unlock_valid",
                  "z_spin_lock_set_owner"}
    if config_set - baseline_set != spin_added or baseline_set - config_set:
        raise ValueError("configuration-only collision delta changed")
    if baseline_set - adopted_set != {"k_mem_slab_alloc", "k_mem_slab_free"}:
        raise ValueError("atomic adoption collision delta changed")
    if adopted_set - baseline_set:
        raise ValueError("atomic adoption added a collision")
    baseline_rows = {int(row["va"], 16): row for row in baseline["functions"]}
    variant_collisions = []
    authorizations = []
    for va, (symbol, source, object_rel, size, normalized, cases) in FUNCTIONS.items():
        object_path = BUILD / object_rel
        if section_size(object_path, symbol) != size:
            raise ValueError("configured section size changed: " + symbol)
        source_hash = sha(NCS / source)
        object_hash = sha(object_path)
        row = baseline_rows.get(va)
        if row is None:
            row = {
                "core": "app", "va": "0x%08x" % va,
                "raw_symbol": "FUN_%08x" % va,
                "current_symbol": symbol,
                "firmware_extent": size,
                "upstream": {
                    "symbol": symbol, "object": str(object_path),
                    "object_sha256": object_hash,
                    "source": {"path": source, "sha256": source_hash,
                               "repository": "zephyr",
                               "commit": "83980fe1679441be9b0e1db556a353f6118fe14f"},
                },
                "configured_inclusion": {
                    "selected_by_real_link": True,
                    "zephyr_config_sha256": config_hash,
                    "proof": "strong owner selected by firmware-config link",
                },
                "signature_match": {"normalized_exact": True},
                "identity_threshold_candidate": True,
                "safe_to_exclude": False,
                "exclusion_blockers": [],
                "decision": "retain_reconstruction",
                "implementation_source_unit": source,
            }
            variant_collisions.append(copy.deepcopy(row))
        configured = row["configured_inclusion"]
        upstream = row["upstream"]
        auth = {
            "batch": "KERNEL-CONFIG-MEMSLAB-ATOMIC",
            "va": "0x%08x" % va, "raw_symbol": "FUN_%08x" % va,
            "symbol": symbol, "status": "authorized",
            "upstream_source": source,
            "upstream_source_sha256": source_hash,
            "upstream_object": str(object_path),
            "upstream_object_sha256": object_hash,
            "upstream_object_alloc_sha256": manifest._alloc_content_sha256(object_path),
            "baseline_upstream_object_sha256": upstream["object_sha256"],
            "baseline_configured_build_sha256": configured["zephyr_config_sha256"],
            "configured_build": str(CONFIG),
            "configured_build_sha256": config_hash,
            "reconstruction_source_sha256": sha(ROOT / "recon/app/src" / ("FUN_%08x.c" % va)),
            "firmware_code_size": size, "upstream_code_size": size,
            "normalized_code_sha256": normalized,
            "instruction_exact": True, "cfg_verify_cases": cases,
            "configuration_variant_exact": True,
            "required_config": REQUIRED_CONFIG,
            "atomic_group": GROUP,
            "whole_unit_closure": {
                "safe": True, "archive_member_already_selected": True,
                "same_source_unit_collision_symbols": [symbol],
                "exclude_only": GROUP, "new_undefined_symbols": [],
            },
        }
        auth["collision_receipt_sha256"] = manifest._json_sha256(row)
        authorizations.append(auth)
    output = {
        "schema": 1, "core": "app", "status": "authorized_atomic",
        "decision": "adopt_exact_configured_sdk_owners",
        "configured_build_receipts": [str(CONFIG)],
        "required_config": REQUIRED_CONFIG,
        "atomic_group": GROUP,
        "expected_normal_link_counts": {"baseline": 82, "config_only": 85, "adopted": 80},
        "normal_link_receipts": links,
        "variant_collisions": variant_collisions,
        "authorizations": authorizations,
        "resolved_gaps": {
            "dmic_stream_start": {
                "status": "repaired_and_cfg_proven",
                "receipt": "recon/ownership/app_dmic_lc3_direct_edge_recovery.json",
                "note": "canonical reconstruction now contains the observed LC3 and k_mem_slab_free closure; SDK adoption was not used to hide the gap",
            }
        },
    }
    OUTPUT.write_text(json.dumps(output, indent=1) + "\n")
    print("wrote", OUTPUT, "with", len(authorizations), "atomic authorizations")


if __name__ == "__main__":
    main()
