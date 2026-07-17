#!/usr/bin/env python3
"""Audit the single retain-all owner selected for CPUNET bt_uuid_to_str."""

from __future__ import annotations

import argparse
import json
import re
from pathlib import Path


SYMBOL = "bt_uuid_to_str"
EXPECTED_OWNER = "app/libapp.a(uuid.c.obj)"


def audit(map_text: str, link_text: str) -> dict:
    section_rows = re.findall(
        r"(?m)^ \.text\.bt_uuid_to_str\s*\n"
        r"\s+0x[0-9a-fA-F]+\s+0x[0-9a-fA-F]+\s+(\S+)",
        map_text,
    )
    export_count = len(re.findall(
        r"(?m)^\s+0x[0-9a-fA-F]+\s+bt_uuid_to_str$", map_text
    ))
    undefined_count = len(re.findall(
        r"undefined reference to [`']bt_uuid_to_str'", link_text
    ))
    multiple_count = len(re.findall(
        r"multiple definition of [`']bt_uuid_to_str'", link_text
    ))
    passed = (
        section_rows == [EXPECTED_OWNER]
        and export_count == 1
        and undefined_count == 0
        and multiple_count == 0
    )
    return {
        "symbol": SYMBOL,
        "passed": passed,
        "strong_definition_count": len(section_rows),
        "owners": section_rows,
        "export_count": export_count,
        "undefined_reference_count": undefined_count,
        "multiple_definition_count": multiple_count,
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--map", required=True, type=Path)
    parser.add_argument("--link-log", required=True, type=Path)
    parser.add_argument("--json", type=Path)
    args = parser.parse_args()
    report = audit(args.map.read_text(errors="replace"),
                   args.link_log.read_text(errors="replace"))
    rendered = json.dumps(report, indent=1) + "\n"
    if args.json:
        args.json.write_text(rendered)
    print(rendered, end="")
    if not report["passed"]:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
