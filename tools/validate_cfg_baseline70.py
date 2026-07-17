#!/usr/bin/env python3
"""Fail-closed validation for the durable 70-entry CFG recovery ledger."""

from __future__ import annotations

import argparse
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs/cfg_baseline70.json"


class CatalogError(ValueError):
    pass


def _historical_entries(data: dict) -> set[str]:
    entries: list[str] = []
    for core in ("app", "net"):
        for kind in ("other", "timeout"):
            entries.extend(f"{core}:{name}" for name in data[f"{core}_{kind}"])
    if len(entries) != 70 or len(set(entries)) != 70:
        raise CatalogError(
            f"historical partition must contain 70 unique entries, got "
            f"{len(entries)} entries/{len(set(entries))} unique"
        )
    return set(entries)


def _pass_entries(data: dict) -> set[str]:
    keys = sorted(key for key in data if key.startswith("authoritative_cfg_pass_"))
    if not keys:
        raise CatalogError("no authoritative CFG PASS waves")
    entries = [entry for key in keys for entry in data[key]]
    if len(entries) != len(set(entries)):
        raise CatalogError("authoritative CFG PASS waves overlap")
    return set(entries)


def _canonical_source(root: Path, core: str, raw_name: str) -> Path | None:
    source_dir = root / ("recon/app/src" if core == "app" else "recon/net/src")
    direct = source_dir / f"{raw_name}.c"
    if direct.is_file():
        return direct

    if not raw_name.startswith("FUN_"):
        return None
    address = "0x" + raw_name.rsplit("_", 1)[1]
    names_path = root / f"recon/catalogs/function_names_{core}.json"
    names = json.loads(names_path.read_text())["by_address"]
    record = names.get(address)
    if not record:
        return None
    renamed = source_dir / f"{record['name']}.c"
    return renamed if renamed.is_file() else None


def validate(data: dict, root: Path = ROOT, check_sources: bool = True) -> dict:
    if data.get("schema") != 2:
        raise CatalogError("cfg_baseline70 schema must be 2")

    historical = _historical_entries(data)
    passed = _pass_entries(data)
    exceptions = set(data.get("ownership_exceptions", {}))
    if passed & exceptions:
        raise CatalogError("an entry cannot be both CFG PASS and an ownership exception")
    unknown = (passed | exceptions) - historical
    unresolved = historical - passed - exceptions
    if unknown:
        raise CatalogError(f"resolution contains non-baseline entries: {sorted(unknown)}")
    if unresolved:
        raise CatalogError(f"unresolved baseline entries: {sorted(unresolved)}")

    for entry, record in data["ownership_exceptions"].items():
        if record.get("status") != "OWNED_INTERIOR":
            raise CatalogError(f"{entry}: exception must be OWNED_INTERIOR")
        if record.get("owner_cfg_status") != "PASS":
            raise CatalogError(f"{entry}: owner must have authoritative CFG PASS")
        owner = record.get("owner", "")
        if owner in historical:
            raise CatalogError(f"{entry}: interior owner must be a distinct identity")
        try:
            owner_core, owner_name = owner.split(":", 1)
        except ValueError as exc:
            raise CatalogError(f"{entry}: invalid owner {owner!r}") from exc
        receipt = data.get("verification_receipts", {}).get(
            record.get("evidence_commit", ""), {}
        ).get(owner)
        if not receipt or receipt.get("status") != "PASS":
            raise CatalogError(f"{entry}: no PASS receipt for owner {owner}")
        if receipt.get("owns_baseline_entry") != entry:
            raise CatalogError(f"{entry}: owner receipt does not point back to interior")
        if check_sources and _canonical_source(root, owner_core, owner_name) is None:
            raise CatalogError(f"{entry}: owner source {owner} is missing")

    receipts = data.get("verification_receipts", {})
    lc3_receipt = receipts.get("de85940", {})
    if set(lc3_receipt) != set(data["authoritative_cfg_pass_de85940"]):
        raise CatalogError("de85940 receipt must exactly cover its CFG PASS wave")
    if any(record.get("status") != "PASS" for record in lc3_receipt.values()):
        raise CatalogError("every de85940 function receipt must be PASS")

    final_receipt = receipts.get("0157de4", {})
    final_expected = set(data["authoritative_cfg_pass_0157de4"])
    final_expected.add("app:FUN_000778d4")
    final_expected.update(record["owner"] for record in data["ownership_exceptions"].values())
    if set(final_receipt) != final_expected or len(final_receipt) != 15:
        raise CatalogError("0157de4 receipt must exactly cover the 15-function wave")
    if any(record.get("status") != "PASS" for record in final_receipt.values()):
        raise CatalogError("every 0157de4 function receipt must be PASS")

    if check_sources:
        for entry in sorted(passed):
            core, raw_name = entry.split(":", 1)
            if _canonical_source(root, core, raw_name) is None:
                raise CatalogError(f"{entry}: canonical source is missing")

    summary = data.get("resolution_summary", {})
    actual = {
        "historical_entries": len(historical),
        "authoritative_cfg_pass": len(passed),
        "owned_interior": len(exceptions),
        "unresolved": len(unresolved),
    }
    for key, value in actual.items():
        if summary.get(key) != value:
            raise CatalogError(
                f"resolution_summary.{key}={summary.get(key)!r}, expected {value}"
            )
    return actual


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("catalog", nargs="?", type=Path, default=CATALOG)
    args = parser.parse_args()
    data = json.loads(args.catalog.read_text())
    summary = validate(data)
    print(
        "CFG baseline70: PASS "
        f"({summary['authoritative_cfg_pass']} CFG PASS, "
        f"{summary['owned_interior']} owned interior, "
        f"{summary['unresolved']} unresolved)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
