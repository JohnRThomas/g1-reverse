#!/usr/bin/env python3
"""Build the durable COLLISION-18 scheduler atomic-adoption receipt."""

import hashlib
import json
import re
import subprocess
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
OUTPUT = ROOT / "recon/ownership/app_collision18_sched_atomic_adoption.json"
REPORT = ROOT / "recon/analysis/app_collision18_sched_atomic_adoption.md"
IMAGE = ROOT / "app_update.bin"
PRE_BUILD = Path("/tmp/g1-sched-pre-final2")
POST_BUILD = Path("/tmp/g1-sched-adopt-final")
GROUP = ["0x%08x" % va for va in (0x739F0, 0x74184, 0x744A4, 0x748B8)]
REMOVED = {
    "z_reschedule", "z_thread_priority_set", "z_unpend_first_thread",
    "z_thread_abort",
}
UNRESOLVED = {"FUN_0005463e", "FUN_00054688"}
CALLERS = {
    "0x000739f0": [
        "0x00070ee4", "0x00071b2c", "0x00071cf4", "0x000720d0",
        "0x00072240", "0x000723b8", "0x00072558", "0x00072674",
        "0x00072880", "0x000729fc", "0x00073a78", "0x000757b0",
    ],
    "0x00074184": ["0x00074554"],
    "0x000744a4": [
        "0x00071cf4", "0x000720d0", "0x00072240", "0x00072558",
        "0x00072674", "0x00072880", "0x000729fc",
    ],
    "0x000748b8": ["0x00050b8c"],
}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


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


def normalized_section(row):
    extent = row["firmware_code_size"]
    with Path(row["upstream_object"]).open("rb") as stream:
        elf = ELFFile(stream)
        section_name = ".text." + row["symbol"]
        section = elf.get_section_by_name(section_name)
        if section is None or len(section.data()) < extent:
            raise ValueError("missing/short selected section: " + row["symbol"])
        candidate = bytearray(section.data()[:extent])
        relocations = elf.get_section_by_name(".rel" + section_name)
        offsets = ([] if relocations is None else
                   [item["r_offset"] for item in relocations.iter_relocations()
                    if item["r_offset"] < extent])
    firmware = bytearray(IMAGE.read_bytes()[
        int(row["va"], 16) - 0xC000:
        int(row["va"], 16) - 0xC000 + extent])
    for offset in offsets:
        candidate[offset:offset + 4] = b"\0" * 4
        firmware[offset:offset + 4] = b"\0" * 4
    return candidate, firmware, offsets


def main():
    rows = [row for row in json.loads(AUTH.read_text())["authorizations"]
            if row.get("batch") == "COLLISION-18"]
    by_va = {row["va"]: row for row in rows}
    if sorted(by_va) != GROUP:
        raise ValueError("COLLISION-18 authorization group is incomplete")
    group = set(GROUP)
    for row in rows:
        if set(row["atomic_group"]) != group:
            raise ValueError("atomic group drift: " + row["va"])
        if set(row["whole_unit_closure"]["exclude_only"]) != group:
            raise ValueError("exclude-only group drift: " + row["va"])
        if not row["instruction_exact"] or not row["configuration_variant_exact"]:
            raise ValueError("non-exact owner: " + row["va"])
        if sha(row["upstream_object"]) != row["upstream_object_sha256"]:
            raise ValueError("configured object drift: " + row["symbol"])
        if sha(ROOT / "recon/app/src" / (row["raw_symbol"] + ".c")) != row["reconstruction_source_sha256"]:
            raise ValueError("reconstruction source drift: " + row["symbol"])
        candidate, firmware, _ = normalized_section(row)
        if candidate != firmware:
            raise ValueError("relocation-normalized prefix mismatch: " + row["symbol"])
        if hashlib.sha256(firmware).hexdigest() != row["normalized_code_sha256"]:
            raise ValueError("normalized digest drift: " + row["symbol"])

    links = {"pre_overlay": link_receipt(PRE_BUILD),
             "adopted": link_receipt(POST_BUILD)}
    before = set(links["pre_overlay"]["collisions"])
    after = set(links["adopted"]["collisions"])
    if (len(before), len(after)) != (80, 76):
        raise ValueError("normal-link counts changed")
    if before - after != REMOVED or after - before:
        raise ValueError("normal-link collision delta changed")
    if set(links["pre_overlay"]["undefined"]) != UNRESOLVED:
        raise ValueError("pre-overlay unresolved set changed")
    if set(links["adopted"]["undefined"]) != UNRESOLVED:
        raise ValueError("adopted unresolved set changed")

    entries = {row["va"]: row for row in
               json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
    if not all(entries[va]["exclude_reconstruction"] for va in GROUP):
        raise ValueError("manifest did not exclude the complete group")

    receipt = {
        "schema": 1,
        "core": "app",
        "batch": "COLLISION-18",
        "status": "authorized_atomic",
        "decision": "adopt_exact_configured_zephyr_sched_owners",
        "atomic_group": GROUP,
        "selected_source_unit": "zephyr/kernel/sched.c",
        "authorizations": rows,
        "direct_callers": CALLERS,
        "link_delta": {
            "before": 80, "after": 76,
            "removed": sorted(REMOVED), "added": [],
            "unresolved_before": sorted(UNRESOLVED),
            "unresolved_after": sorted(UNRESOLVED),
        },
        "normal_link_receipts": links,
        "state_symbol_convergence": {
            "0x2000b448": "_kernel",
            "0x2000b470": "mutex_spinlock_b470",
            "0x2000b490": "sched_spinlock",
        },
        "sdc_policy": "report_only_unchanged",
    }
    OUTPUT.write_text(json.dumps(receipt, indent=1) + "\n")
    REPORT.write_text(
        "# COLLISION-18 scheduler atomic adoption\n\n"
        "The firmware-configured Zephyr `kernel/sched.c` object is the exact "
        "owner of `z_reschedule`, `z_thread_priority_set`, "
        "`z_unpend_first_thread`, and `z_thread_abort`. Each selected ELF "
        "section matches the firmware's true reachable code extent after "
        "masking relocations; the remaining section bytes are literal-pool "
        "tails, not executable extent.\n\n"
        "The four owners are adopted as one source-unit closure. The fresh "
        "normal-link collision set moves **80 -> 76**, removing exactly those "
        "four symbols, adding none. The unresolved set stays exactly "
        "`FUN_0005463e` and `FUN_00054688`.\n\n"
        "Scheduler state references converge on Zephyr's `_kernel` and "
        "`sched_spinlock`; the distinct object at `0x2000b470` remains "
        "`mutex_spinlock_b470`. Address provenance comments remain in the "
        "symbolized sources. SDC ownership remains report-only and unchanged.\n"
    )
    print("wrote", OUTPUT)


if __name__ == "__main__":
    main()
