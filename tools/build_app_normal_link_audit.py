#!/usr/bin/env python3
"""Audit the real CPUAPP link with retain-all diagnostics disabled."""

import argparse
import collections
import hashlib
import json
import os
import re
from pathlib import Path


BASE = Path("/Users/freedomcoder/Projects/G1disasm2")
BUILD = Path("/private/tmp/g1-app-normal-0718b")
LOG = BUILD / "build.log"
MAP = BUILD / "zephyr/zephyr_pre0.map"
ELF = BUILD / "zephyr/zephyr.elf"
CACHE = BUILD / "CMakeCache.txt"
COLLISIONS = BASE / "recon/ownership/app_build_collision_ownership.json"
OUT_JSON = BASE / "recon/catalogs/app_normal_link_audit.json"
OUT_MD = BASE / "recon/catalogs/app_normal_link_audit.md"


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def build():
    for path in (LOG, MAP, CACHE, COLLISIONS):
        if not path.exists():
            raise ValueError("missing normal-link evidence: %s" % path)
    cache = CACHE.read_text(errors="replace")
    if "G1_INTEGRATION_PROBE_RETAIN_ALL:BOOL=OFF" not in cache:
        raise ValueError("normal-link probe was not configured retain-all OFF")
    if "ZEPHYR_BASE:PATH=/Users/freedomcoder/ncs251/zephyr" not in cache:
        raise ValueError("normal-link probe did not use pinned NCS 2.5.1 tree")
    log = LOG.read_text(errors="replace")
    collision_symbols = re.findall(
        r"multiple definition of [`']([^`']+)[`']", log)
    unresolved = re.findall(r"undefined reference to [`']([^`']+)[`']", log)
    catalog = json.loads(COLLISIONS.read_text())
    functions = catalog["functions"]
    expected = {row["current_symbol"] for row in functions}
    observed = set(collision_symbols)
    if len(collision_symbols) != 112 or len(observed) != 112:
        raise ValueError("normal link does not contain exactly 112 unique collisions")
    if observed != expected:
        raise ValueError("normal-link collision set differs from authority catalog")
    if ELF.exists():
        raise ValueError("normal-link ELF unexpectedly exists; regenerate audit")
    if unresolved:
        raise ValueError("normal link gained unresolved-reference diagnostics")
    rows = []
    for row in sorted(functions, key=lambda item: item["current_symbol"]):
        symbol = row["current_symbol"]
        rows.append({
            "symbol": symbol,
            "va": row["va"],
            "source_unit": row["implementation_source_unit"],
            "catalog_decision": row["decision"],
            "reconstruction_owner": row["retained_owner"]["archive_or_object"],
            "upstream_owner": (row["upstream"]["archive_or_object"] + "(" +
                               row["upstream"]["archive_member"] + ")"),
            "normal_link_state": "duplicate_strong_definitions",
            "winning_owner": None,
            "duplicate_body": True,
            "wrong_owner_assessment": "not_assessable_no_elf",
            "actionable_link_blocker": True,
        })
    batches = {row["source_unit"] for row in rows}
    decisions = collections.Counter(row["catalog_decision"] for row in rows)
    return {
        "schema": 1,
        "core": "app",
        "source_commit": "f7de5a53",
        "policy": "normal link; no retain-all, allow-multiple-definition, or archive mutation",
        "evidence": {
            "build_dir": str(BUILD),
            "build_log_sha256": sha256(LOG),
            "pre0_map_sha256": sha256(MAP),
            "cmake_cache_sha256": sha256(CACHE),
            "retain_all": False,
            "zephyr_base": "/Users/freedomcoder/ncs251/zephyr",
            "elf_exists": False,
        },
        "summary": {
            "final_elf_links": False,
            "collision_diagnostics": len(collision_symbols),
            "unique_collision_symbols": len(observed),
            "collision_source_units": len(batches),
            "catalog_batches": catalog["summary"]["batches"],
            "duplicate_bodies": len(rows),
            "winning_owners": 0,
            "unresolved_reference_diagnostics": 0,
            "wrong_owner_findings": 0,
            "wrong_owner_not_assessable": len(rows),
            "actionable_symbol_blockers": len(rows),
            "actionable_source_unit_batches": len(batches),
            "by_catalog_decision": dict(sorted(decisions.items())),
        },
        "entries": rows,
    }


def markdown(data):
    summary = data["summary"]
    lines = [
        "# CPUAPP normal cohesive-link audit", "",
        "Configured against pinned NCS 2.5.1 with "
        "`G1_INTEGRATION_PROBE_RETAIN_ALL=OFF`. No linker relaxation or archive mutation.", "",
        "The final ELF **does not link**. GNU ld rejects all 112 strong-symbol collisions "
        "before any owner can win; they are real cohesive-link blockers, not retain-all-only diagnostics.", "",
        "- Collision symbols: **%d**" % summary["unique_collision_symbols"],
        "- Source-unit batches: **%d**" % summary["actionable_source_unit_batches"],
        "- Undefined-reference diagnostics: **0**",
        "- Winning owners: **0**",
        "- Wrong-owner findings: **0 assessable** (no ELF; 112 not assessable)", "",
        "| Symbol | Firmware VA | Reconstruction owner | Upstream owner | Catalog decision |", "|---|---:|---|---|---|",
    ]
    for row in data["entries"]:
        lines.append("| `%s` | `%s` | `%s` | `%s` | `%s` |" %
                     (row["symbol"], row["va"], row["reconstruction_owner"],
                      row["upstream_owner"], row["catalog_decision"]))
    lines.append("")
    return "\n".join(lines)


def update(path, content, check):
    old = path.read_text() if path.exists() else None
    if check and old != content:
        raise ValueError("stale output: %s" % path)
    if not check and old != content:
        path.write_text(content)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    update(OUT_JSON, json.dumps(data, indent=1, sort_keys=True) + "\n", args.check)
    update(OUT_MD, markdown(data), args.check)
    print(json.dumps(data["summary"], sort_keys=True))


if __name__ == "__main__":
    main()
