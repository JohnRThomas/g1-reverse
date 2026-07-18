#!/usr/bin/env python3
"""Validate the durable CPUAPP CFG checkpoint and optionally current sources."""

import argparse
import json

from build_cfg_sweep_app_report import (
    OUT_JSON, OUT_MD, build, markdown,
)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check-current", action="store_true")
    args = parser.parse_args()
    expected = build(require_current=args.check_current)
    actual = json.loads(OUT_JSON.read_text())
    if actual != expected:
        raise ValueError("CPUAPP CFG JSON report drift")
    if OUT_JSON.read_text() != json.dumps(
            actual, indent=1, sort_keys=True) + "\n":
        raise ValueError("CPUAPP CFG JSON serialization drift")
    if OUT_MD.read_text() != markdown(actual):
        raise ValueError("CPUAPP CFG Markdown report drift")
    print("CPUAPP CFG report valid: inventory=%d unresolved=%d" %
          (actual["inventory_count"], actual["unresolved_count"]))


if __name__ == "__main__":
    main()
