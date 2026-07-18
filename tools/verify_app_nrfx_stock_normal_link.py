#!/usr/bin/env python3
"""Capture/verify the normal-link result after exact stock-NRFX adoption."""

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ADOPTION = ROOT / "recon/ownership/app_nrfx_stock_atomic_adoption.json"
OUTPUT = ROOT / "recon/ownership/app_nrfx_stock_normal_link.json"


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def audit(build):
    target = "zephyr/zephyr_pre0.elf"
    commands = subprocess.check_output(
        ["ninja", "-C", str(build), "-t", "commands", target], text=True
    ).splitlines()
    command = next(line for line in reversed(commands)
                   if target in line and " -o " in line)
    run = subprocess.run(command, shell=True, cwd=build, text=True,
                         capture_output=True)
    output = run.stdout + "\n" + run.stderr
    collisions = sorted(set(re.findall(
        r"multiple definition of [`']([^'`]+)", output)))
    undefined = sorted(set(re.findall(
        r"undefined reference to [`']([^'`]+)", output)))
    return {
        "schema": 1,
        "core": "app",
        "build": str(build),
        "adoption_receipt_sha256": sha(ADOPTION),
        "collision_count": len(collisions),
        "collisions": collisions,
        "collision_delta_from_pre_adoption": [],
        "undefined": undefined,
        "expected_terminal_link_failure": run.returncode != 0,
    }


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build", type=Path, required=True)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    result = audit(args.build.resolve())
    if result["collision_count"] != 66:
        raise ValueError("unexpected collision count: %d" %
                         result["collision_count"])
    if result["undefined"] != ["FUN_0005463e", "FUN_00054688"]:
        raise ValueError("unexpected undefined symbols: %r" %
                         result["undefined"])
    text = json.dumps(result, indent=1, sort_keys=True) + "\n"
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text() != text:
            raise ValueError("stale stock-NRFX normal-link receipt")
    else:
        OUTPUT.write_text(text)
    print("stock-NRFX normal link: 66 collisions, 2 known undefined")


if __name__ == "__main__":
    main()
