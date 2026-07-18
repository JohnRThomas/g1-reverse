#!/usr/bin/env python3
"""Fail-closed validator for the durable final CPUNET CFG report."""

import json

from build_cfg_sweep_net_report import OUT_JSON, OUT_MD, build, markdown


def main():
    expected = build()
    actual = json.loads(OUT_JSON.read_text())
    if actual != expected:
        raise ValueError("stale CPUNET CFG JSON report")
    if OUT_MD.read_text() != markdown(expected):
        raise ValueError("stale CPUNET CFG Markdown report")
    if expected["counts"] != {
            "PASS": 1073, "FAIL": 8, "compile_error": 0,
            "other": 8, "timeout": 1, "source_changed": 0}:
        raise ValueError("unexpected final CPUNET aggregate")
    print("CPUNET CFG report validated: 1090 exact sources")


if __name__ == "__main__":
    main()
