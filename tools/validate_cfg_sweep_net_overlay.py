#!/usr/bin/env python3
"""Fail-closed validator for the exact-hash CPUNET CFG overlay."""

import json

from build_cfg_sweep_net_overlay import OUT_JSON, OUT_MD, build, markdown


def main():
    expected = build()
    if json.loads(OUT_JSON.read_text()) != expected:
        raise ValueError("stale CPUNET CFG overlay JSON")
    if OUT_MD.read_text() != markdown(expected):
        raise ValueError("stale CPUNET CFG overlay Markdown")
    if expected["overlay_counts"] != {
            "PASS": 1090, "FAIL": 0, "compile_error": 0,
            "other": 0, "timeout": 0, "source_changed": 0}:
        raise ValueError("unexpected CPUNET overlay aggregate")
    if expected["unresolved_count"] != 0:
        raise ValueError("CPUNET overlay remains unresolved")
    print("CPUNET CFG overlay validated: 1090 PASS, unresolved=0")


if __name__ == "__main__":
    main()
