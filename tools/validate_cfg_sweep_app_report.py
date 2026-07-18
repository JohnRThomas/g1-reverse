#!/usr/bin/env python3
"""Validate the durable CPUAPP CFG checkpoint and optionally current sources."""

import argparse
import json

from build_cfg_sweep_app_report import (
    OUT_JSON, OUT_MD, build, markdown,
)
from build_cfg_sweep_app_overlay import (
    OUT_JSON as OVERLAY_JSON,
    OUT_MD as OVERLAY_MD,
    build as build_overlay,
    markdown as overlay_markdown,
)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check-current", action="store_true")
    args = parser.parse_args()
    # The 2,113-source report is an immutable baseline. Current-tree checking
    # composes that checkpoint with the exact-hash post-baseline overlay rather
    # than mutating or pretending to regenerate the frozen lane receipts.
    expected = build(require_current=False)
    actual = json.loads(OUT_JSON.read_text())
    if actual != expected:
        raise ValueError("CPUAPP CFG JSON report drift")
    if OUT_JSON.read_text() != json.dumps(
            actual, indent=1, sort_keys=True) + "\n":
        raise ValueError("CPUAPP CFG JSON serialization drift")
    if OUT_MD.read_text() != markdown(actual):
        raise ValueError("CPUAPP CFG Markdown report drift")
    if args.check_current:
        overlay = build_overlay()
        if json.loads(OVERLAY_JSON.read_text()) != overlay:
            raise ValueError("CPUAPP current CFG overlay JSON drift")
        if OVERLAY_MD.read_text() != overlay_markdown(overlay):
            raise ValueError("CPUAPP current CFG overlay Markdown drift")
        print("CPUAPP CFG report valid: inventory=%d unresolved=%d" %
              (overlay["current_inventory_count"], overlay["unresolved_count"]))
    else:
        print("CPUAPP CFG baseline valid: inventory=%d unresolved=%d" %
              (actual["inventory_count"], actual["unresolved_count"]))


if __name__ == "__main__":
    main()
