#!/usr/bin/env python3
"""Fail-closed validator for the 1,131-source CPUNET CFG overlay."""

import json

from build_cfg_sweep_net_current_overlay import OUT_JSON, OUT_MD, build, markdown


def main():
    expected = build()
    if json.loads(OUT_JSON.read_text()) != expected:
        raise ValueError("stale CPUNET current overlay JSON")
    if OUT_MD.read_text() != markdown(expected):
        raise ValueError("stale CPUNET current overlay Markdown")
    if expected["previous_current_inventory_count"] != 1123:
        raise ValueError("previous CPUNET inventory count drift")
    if expected["overlay_counts"] != {
            "PASS": 1131, "FAIL": 0, "compile_error": 0,
            "other": 0, "timeout": 0, "source_changed": 0}:
        raise ValueError("unexpected CPUNET current aggregate")
    if expected["unresolved_count"] != 0 or expected["source_drift"]:
        raise ValueError("CPUNET current corpus remains unresolved")
    print("CPUNET current CFG overlay validated: 1131 PASS, unresolved=0")


if __name__ == "__main__":
    main()
