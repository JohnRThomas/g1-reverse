#!/usr/bin/env python3
"""Validate readable CPUAPP back-maps and generate linker aliases."""

import json
import os
import re
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs/app_readable_alias_resolutions.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
SWEEP = ROOT / "recon/analysis/cfg_sweep_authoritative_app.json"
SOURCE = ROOT / "recon/symbolized/app"
OUTPUT = ROOT / "recon/symbols/g1_app_readable_aliases.ld"
MARKDOWN = ROOT / "recon/catalogs/app_readable_alias_resolutions.md"
IDENT = re.compile(r"^[A-Za-z_$][A-Za-z0-9_$]*$")


def _passing_identities(data):
    """Accept the durable authoritative sweep schemas used by this repo."""
    passing = set(data.get("PASS", []))
    passing.update(data.get("by_status", {}).get("PASS", []))
    passing.update(data.get("baseline_by_status", {}).get("PASS", []))
    for row in data.get("functions", []):
        if row.get("status") == "PASS":
            passing.add(row.get("name"))
    for row in data.get("entries", []):
        if row.get("status") == "PASS":
            passing.add(row.get("name"))
    for row in data.get("results", []):
        if row.get("status") == "PASS":
            passing.add(row.get("name"))
    return {name for name in passing if name}


def validate():
    catalog = json.loads(CATALOG.read_text())
    names = json.loads(NAMES.read_text())["by_address"]
    passing = _passing_identities(json.loads(SWEEP.read_text()))
    seen = set()
    for row in catalog["aliases"]:
        symbol, target, va = row["symbol"], row["target"], row["va"].lower()
        if not IDENT.fullmatch(symbol) or not IDENT.fullmatch(target):
            raise ValueError("invalid alias identifier: %r" % row)
        if symbol in seen:
            raise ValueError("duplicate readable alias: %s" % symbol)
        seen.add(symbol)
        identity = names.get(va)
        if not identity:
            raise ValueError("alias VA absent from function map: %s" % va)
        if target not in (identity["raw_name"], identity["name"]):
            raise ValueError("alias target does not own %s: %s" % (va, target))
        source = SOURCE / (identity["name"] + ".c")
        if not source.is_file():
            raise ValueError("alias target source missing: %s" % source)
        raw = identity["raw_name"]
        if raw not in passing and identity["name"] not in passing:
            raise ValueError("alias target absent from authoritative PASS corpus: %s" % raw)
        callers = []
        for path in SOURCE.glob("*.c"):
            text = path.read_text(errors="replace")
            declaration = (re.search(r"\b%s\s*\(" % re.escape(symbol), text) and
                           re.search(r"/\*\s*%s\s*\*/" % re.escape(raw), text))
            if declaration:
                callers.append(path.name)
        if not callers:
            raise ValueError("readable/raw caller back-map missing: %s -> %s" %
                             (symbol, raw))
    return catalog


def render(catalog):
    lines = [
        "/* Generated from app_readable_alias_resolutions.json.",
        " * Every alias has a readable/raw caller back-map and CFG-proven target. */",
    ]
    for row in sorted(catalog["aliases"], key=lambda item: item["symbol"]):
        lines.append("PROVIDE(%s = %s); /* %s */" %
                     (row["symbol"], row["target"], row["va"]))
    return "\n".join(lines) + "\n"


def render_markdown(catalog):
    lines = ["# CPUAPP readable alias resolutions", "",
             "These aliases resolve human-readable call spellings back to their",
             "CFG-proven firmware identities without changing function bodies.", "",
             "| Symbol | Target | VA | Evidence |", "|---|---|---:|---|"]
    for row in catalog["aliases"]:
        lines.append("| `%s` | `%s` | %s | %s |" %
                     (row["symbol"], row["target"], row["va"], row["evidence"]))
    return "\n".join(lines) + "\n"


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    check = argv == ["--check"]
    if argv not in ([], ["--check"]):
        raise SystemExit("usage: build_app_readable_alias_resolutions.py [--check]")
    catalog = validate()
    outputs = {OUTPUT: render(catalog), MARKDOWN: render_markdown(catalog)}
    stale = [path for path, content in outputs.items()
             if not path.exists() or path.read_text() != content]
    if check and stale:
        raise SystemExit("app readable alias artifacts are stale: %s" %
                         ", ".join(str(path) for path in stale))
    if not check:
        for path, content in outputs.items():
            path.write_text(content)
    print("app readable alias catalog and fragment: valid")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
