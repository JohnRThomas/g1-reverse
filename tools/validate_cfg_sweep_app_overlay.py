#!/usr/bin/env python3
"""Fail-closed validator for the exact-hash CPUAPP CFG overlay."""

import json

from build_cfg_sweep_app_overlay import OUT_JSON, OUT_MD, build, markdown


def main():
    expected = build()
    if json.loads(OUT_JSON.read_text()) != expected:
        raise ValueError("stale CPUAPP CFG overlay JSON")
    if OUT_JSON.read_text() != json.dumps(expected, indent=1, sort_keys=True) + "\n":
        raise ValueError("CPUAPP CFG overlay serialization drift")
    if OUT_MD.read_text() != markdown(expected):
        raise ValueError("stale CPUAPP CFG overlay Markdown")
    if expected["current_counts"] != {
            "PASS": 2115, "FAIL": 0, "compile_error": 0,
            "other": 0, "timeout": 0, "source_changed": 0}:
        raise ValueError("unexpected CPUAPP overlay aggregate")
    if expected["unresolved_count"] or expected["unverified_source_drift"]:
        raise ValueError("CPUAPP overlay is not fully resolved")
    print("CPUAPP CFG overlay validated: 2115 PASS, unresolved=0")


if __name__ == "__main__":
    main()
