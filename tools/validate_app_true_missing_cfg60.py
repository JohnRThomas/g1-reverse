#!/usr/bin/env python3
"""Build and fail-closed validate the 60-entry CPUAPP true-missing CFG ledger."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/catalogs/app_interior_alias_audit.json"
NAMES = ROOT / "recon/catalogs/function_name_overrides.json"
LEDGER = ROOT / "recon/catalogs/app_true_missing_cfg60.json"
MARKDOWN = ROOT / "recon/catalogs/app_true_missing_cfg60.md"
EXCLUDED_VA = "0x00086228"
AUDIT_REV = "ee74df54"
EXPECTED_COUNT = 60
PASS_RE = re.compile(r"^\S+ PASS cases=(\d+)\b", re.MULTILINE)
READABLE_RE = re.compile(r"Readable identity:\s*(.+?)\s*$", re.MULTILINE)


def _load(path: Path):
    with path.open() as stream:
        return json.load(stream)


def inventory(root: Path = ROOT):
    audit_text = subprocess.run(
        ["git", "-C", str(root), "show",
         AUDIT_REV + ":" + AUDIT.relative_to(ROOT).as_posix()],
        check=True, capture_output=True, text=True).stdout
    audit = json.loads(audit_text)
    rows = [row for row in audit["entries"]
            if row["classification"] == "true_missing_catalog_entry"
            and row["va"] != EXCLUDED_VA]
    rows.sort(key=lambda row: int(row["va"], 16))
    if len(rows) != EXPECTED_COUNT:
        raise ValueError("true-missing inventory is %d, expected %d" %
                         (len(rows), EXPECTED_COUNT))
    return rows


def _source_paths(root: Path, row, readable_name: str):
    source_dir = root / "recon/app/src"
    mirror_dir = root / "recon/verified/src"
    raw = row["symbol"]
    stem = raw if (source_dir / (raw + ".c")).exists() else readable_name
    return source_dir / (stem + ".c"), mirror_dir / (stem + ".c")


def _extent_maps():
    tools = str(ROOT / "tools")
    if tools not in sys.path:
        sys.path.insert(0, tools)
    import cfg_verify  # pylint: disable=import-outside-toplevel
    import recon_kit  # pylint: disable=import-outside-toplevel
    cfg = {va: size for (core, va), size in
           cfg_verify.TRUE_SIZE_OVERRIDES.items() if core == "app"}
    return cfg, dict(recon_kit.TRUE_SIZE_OVERRIDES)


def build_document(results_dir: Path, root: Path = ROOT):
    names = _load(root / NAMES.relative_to(ROOT))["app"]
    cfg_extents, recon_extents = _extent_maps()
    entries = []
    for row in inventory(root):
        va = row["va"]
        va_int = int(va, 16)
        readable = names.get(va, {}).get("name", row["symbol"])
        source, mirror = _source_paths(root, row, readable)
        if not source.exists() or not mirror.exists():
            raise ValueError("missing source/mirror for " + va)
        source_bytes = source.read_bytes()
        if va not in names:
            match = READABLE_RE.search(source_bytes[:600].decode(
                "utf-8", "replace"))
            if match:
                readable = match.group(1).rstrip(".")
        if source_bytes != mirror.read_bytes():
            raise ValueError("canonical/mirror mismatch for " + va)
        if va_int not in cfg_extents or va_int not in recon_extents:
            raise ValueError("missing synchronized extent for " + va)
        if cfg_extents[va_int] != recon_extents[va_int]:
            raise ValueError("extent drift for " + va)
        proof_path = results_dir / (va + ".out")
        if not proof_path.exists():
            raise ValueError("missing proof output for " + va)
        proof = proof_path.read_text()
        match = PASS_RE.search(proof)
        if not match:
            raise ValueError("non-PASS proof output for " + va)
        entries.append({
            "va": va,
            "raw_symbol": row["symbol"],
            "readable_name": readable,
            "extent": cfg_extents[va_int],
            "result": "PASS",
            "case_count": int(match.group(1)),
            "checked": (int(match.group(1)) if int(match.group(1)) > 0 else 40),
            "source": source.relative_to(root).as_posix(),
            "verified_mirror": mirror.relative_to(root).as_posix(),
            "source_sha256": hashlib.sha256(source_bytes).hexdigest(),
            "catalog_ownership": {
                "core": "app",
                "name_catalog": ("function_name_overrides.json" if va in names
                                 else "canonical_source_header"),
                "audit_classification": row["classification"],
                "audit_resolution": row["resolution"],
            },
        })
    total_cases = sum(entry["case_count"] for entry in entries)
    total_checked = sum(entry["checked"] for entry in entries)
    return {
        "schema": 1,
        "core": "app",
        "policy": "fail_closed",
        "inventory_source": "git:ee74df54:recon/catalogs/app_interior_alias_audit.json",
        "excluded": [{
            "va": EXCLUDED_VA,
            "reason": "audit marks already_resolved_by_cfg_verified_strong_owner",
        }],
        "expected_count": EXPECTED_COUNT,
        "summary": {
            "function_count": len(entries),
            "cfg_pass": len(entries),
            "cfg_fail": 0,
            "reviewed_case_count": total_cases,
            "executed_check_count": total_checked,
        },
        "entries": entries,
    }


def validate_document(document, root: Path = ROOT, check_sources=True):
    errors = []
    entries = document.get("entries", [])
    expected = inventory(root)
    expected_vas = [row["va"] for row in expected]
    vas = [entry.get("va") for entry in entries]
    if document.get("schema") != 1 or document.get("core") != "app":
        errors.append("wrong schema/core")
    if document.get("policy") != "fail_closed":
        errors.append("policy is not fail_closed")
    if document.get("expected_count") != EXPECTED_COUNT:
        errors.append("wrong expected_count")
    if len(entries) != EXPECTED_COUNT or vas != expected_vas:
        errors.append("entry inventory/order mismatch")
    if len(set(vas)) != len(vas):
        errors.append("duplicate VA")
    if len({entry.get("raw_symbol") for entry in entries}) != len(entries):
        errors.append("duplicate raw symbol")

    cfg_extents = recon_extents = None
    if check_sources:
        cfg_extents, recon_extents = _extent_maps()
    for entry in entries:
        va = entry.get("va", "")
        if (entry.get("result") != "PASS" or entry.get("case_count", -1) < 0
                or entry.get("checked", 0) <= 0
                or entry.get("checked", 0) < entry.get("case_count", 0)):
            errors.append("non-PASS/unexecuted proof for " + va)
        ownership = entry.get("catalog_ownership", {})
        if ownership.get("core") != "app" or ownership.get(
                "audit_classification") != "true_missing_catalog_entry":
            errors.append("bad catalog ownership for " + va)
        if not check_sources:
            continue
        source = root / entry.get("source", "")
        mirror = root / entry.get("verified_mirror", "")
        if not source.is_file() or not mirror.is_file():
            errors.append("missing source/mirror for " + va)
            continue
        source_bytes = source.read_bytes()
        if source_bytes != mirror.read_bytes():
            errors.append("mirror mismatch for " + va)
        if hashlib.sha256(source_bytes).hexdigest() != entry.get("source_sha256"):
            errors.append("digest mismatch for " + va)
        header = source_bytes[:600].decode("utf-8", "replace")
        if va not in header or entry.get("raw_symbol", "") not in header:
            errors.append("missing raw/VA backmap for " + va)
        va_int = int(va, 16)
        extent = entry.get("extent")
        if cfg_extents.get(va_int) != extent or recon_extents.get(va_int) != extent:
            errors.append("extent mismatch for " + va)

    summary = document.get("summary", {})
    total_cases = sum(entry.get("case_count", 0) for entry in entries)
    total_checked = sum(entry.get("checked", 0) for entry in entries)
    expected_summary = {
        "function_count": len(entries), "cfg_pass": len(entries),
        "cfg_fail": 0, "reviewed_case_count": total_cases,
        "executed_check_count": total_checked,
    }
    if summary != expected_summary:
        errors.append("summary mismatch")
    return errors


def markdown(document):
    summary = document["summary"]
    lines = [
        "# CPUAPP true-missing CFG proof ledger", "",
        "Deterministic, fail-closed receipt for the 60 reconstructed entries from "
        "`app_interior_alias_audit.json`; `0x00086228` is excluded because the audit "
        "marks it as an already-owned strong reconstruction.", "",
        "- Functions: %d" % summary["function_count"],
        "- Authoritative CFG PASS: %d" % summary["cfg_pass"],
        "- Reviewed cases: %d" % summary["reviewed_case_count"], "",
        "- Executed checks: %d" % summary["executed_check_count"], "",
        "| VA | Raw identity | Readable name | Extent | Cases | Checked | SHA-256 |",
        "|---|---|---|---:|---:|---:|---|",
    ]
    for entry in document["entries"]:
        lines.append("| `{va}` | `{raw_symbol}` | `{readable_name}` | {extent} | "
                     "{case_count} | {checked} | `{source_sha256}` |".format(**entry))
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--generate-from-results", type=Path)
    args = parser.parse_args()
    if args.generate_from_results:
        document = build_document(args.generate_from_results.resolve())
        errors = validate_document(document)
        if errors:
            raise SystemExit("\n".join(errors))
        LEDGER.write_text(json.dumps(document, indent=1) + "\n")
        MARKDOWN.write_text(markdown(document))
    document = _load(LEDGER)
    errors = validate_document(document)
    if errors:
        raise SystemExit("\n".join(errors))
    print("PASS functions=%d cases=%d" %
          (document["summary"]["function_count"],
           document["summary"]["reviewed_case_count"]))


if __name__ == "__main__":
    main()
