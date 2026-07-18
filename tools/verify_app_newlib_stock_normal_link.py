#!/usr/bin/env python3
"""Capture the exact normal-link delta after stock Newlib-nano adoption."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ADOPTION = ROOT / "recon/ownership/app_newlib_stock_atomic_adoption.json"
BASELINE = ROOT / "recon/ownership/app_nrfx_stock_normal_link.json"
OUTPUT = ROOT / "recon/ownership/app_newlib_stock_normal_link.json"
REMOVED = {"__sinit", "__sinit_lock_release", "_malloc_r", "_strtoul_r",
           "malloc"}
UNRESOLVED = {"FUN_0005463e", "FUN_00054688"}


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def link_result(build):
    target = "zephyr/zephyr_pre0.elf"
    commands = subprocess.check_output(
        ["ninja", "-C", str(build), "-t", "commands", target], text=True
    ).splitlines()
    command = next(line for line in reversed(commands)
                   if target in line and " -o " in line)
    run = subprocess.run(command, shell=True, cwd=build, text=True,
                         capture_output=True)
    output = run.stdout + "\n" + run.stderr
    collisions = set(re.findall(
        r"multiple definition of [`']([^'`]+)", output))
    undefined = set(re.findall(
        r"undefined reference to [`']([^'`]+)", output))
    nm = subprocess.check_output([
        "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
        "arm-zephyr-eabi-nm", "-u", str(build / "app/libapp.a")], text=True)
    retained_undefined = {symbol for symbol in UNRESOLVED
                          if re.search(r"\bU\s+" + symbol + r"$", nm,
                                       re.MULTILINE)}
    return run.returncode, collisions, undefined, retained_undefined


def audit(build):
    baseline = json.loads(BASELINE.read_text())
    returncode, after, diagnostics, undefined = link_result(build)
    before = set(baseline["collisions"])
    result = {
        "schema": 1,
        "core": "app",
        "build": str(build),
        "adoption_receipt_sha256": sha(ADOPTION),
        "baseline_receipt_sha256": sha(BASELINE),
        "collision_count_before": len(before),
        "collision_count_after": len(after),
        "removed": sorted(before - after),
        "added": sorted(after - before),
        "unresolved_before": baseline["undefined"],
        "unresolved_after": sorted(undefined),
        "unresolved_link_diagnostics_after": sorted(diagnostics),
        "expected_terminal_link_failure": returncode != 0,
    }
    if (result["collision_count_before"] != 66 or
            result["collision_count_after"] != 61 or
            set(result["removed"]) != REMOVED or result["added"] or
            set(result["unresolved_before"]) != UNRESOLVED or
            set(result["unresolved_after"]) != UNRESOLVED or
            not result["expected_terminal_link_failure"]):
        raise ValueError("stock Newlib normal-link delta drift: %r" % result)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build", type=Path, required=True)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    result = audit(args.build.resolve())
    rendered = json.dumps(result, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != rendered:
            raise ValueError("stale stock Newlib normal-link receipt")
    else:
        OUTPUT.write_text(rendered)
    print("stock Newlib normal link: 66 -> 61, 2 known undefined unchanged")


if __name__ == "__main__":
    main()
