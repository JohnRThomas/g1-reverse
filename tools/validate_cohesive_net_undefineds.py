#!/usr/bin/env python3
"""Validate the durable cohesive CPUNET undefined-symbol classification."""

from __future__ import annotations

import argparse
import hashlib
import json
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / "recon/catalogs/net_cohesive_undefined_classification.json"
CATEGORIES = {
    "private_sdc_mpsl_report_only",
    "stock_sdk_or_glue",
    "interior_or_anomalous_identity",
}


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def validate(report: dict, *, check_inputs: bool = False) -> None:
    assert report["schema"] == "g1.net.cohesive_undefined.v1"
    assert report["core"] == "net"
    assert report["policy"] == {
        "private_sdc_mpsl_report_only": True,
        "automatic_private_archive_alias_or_removal": False,
        "canonical_sources_modified": False,
    }
    entries = report["entries"]
    symbols = [row["symbol"] for row in entries]
    assert symbols == sorted(symbols)
    assert len(symbols) == len(set(symbols)) == 150
    assert all(row["caller_count"] == len(row["caller_objects"]) > 0 for row in entries)
    assert all(row["link_reference_count"] >= row["caller_count"] for row in entries)
    assert all(row["category"] in CATEGORIES for row in entries)

    counts = Counter(row["category"] for row in entries)
    assert counts == Counter({
        "private_sdc_mpsl_report_only": 93,
        "stock_sdk_or_glue": 55,
        "interior_or_anomalous_identity": 2,
    })
    assert report["summary"]["by_category"] == {
        category: counts[category]
        for category in (
            "private_sdc_mpsl_report_only",
            "stock_sdk_or_glue",
            "interior_or_anomalous_identity",
        )
    }
    assert report["summary"]["private_by_family"] == {
        "mpsl": 29, "softdevice_controller": 64,
    }
    assert report["summary"]["private_unique_archive_identities"] == {
        "softdevice_controller": 53, "mpsl": 28,
    }
    assert report["summary"]["private_manifest_policy_conflicts"] == 29

    for row in entries:
        if row["category"] == "private_sdc_mpsl_report_only":
            assert row["provider"]["safe_to_auto_resolve"] is False
        if row["manifest_policy_conflict"]:
            assert row["provider"]["family"] == "mpsl"
            assert row["provider"]["recommended_disposition"] == "retain_or_restore_report_only"
            assert row["provider"]["per_va_unique_archive_identity_proven"] is False
            assert row["provider"]["member_selection_state_closure_proven"] is False

    aliases = {row["symbol"] for row in entries
               if row["resolution_kind"] == "existing_readable_alias_not_linked"}
    stock = {row["symbol"] for row in entries
             if row["resolution_kind"] == "stock_provider_requires_call_identity_integration"}
    anomalies = {row["symbol"] for row in entries
                 if row["category"] == "interior_or_anomalous_identity"}
    assert len(aliases) == 33
    assert len(stock) == 22
    assert not aliases & stock
    assert anomalies == {"FUN_0102d25c", "FUN_0102fa84"}
    assert aliases | stock == {
        row["symbol"] for row in entries if row["category"] == "stock_sdk_or_glue"
    }

    versions = report["archive_version_discrimination"]
    assert versions["manifest_selected_tag"] == "v2.5.1"
    assert versions["binary_archive_indistinguishable_tags"] == ["v2.5.0", "v2.5.1"]
    exact = []
    for row in versions["tags"]:
        if all(family["whole_archive_identical_to_v2_5_1"]
               for family in row["families"].values()):
            exact.append(row["tag"])
    assert exact == ["v2.5.0", "v2.5.1"]

    if check_inputs:
        for record in report["inputs"]:
            path = Path(record["path"])
            assert path.exists(), path
            assert sha256(path) == record["sha256"], path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--report", type=Path, default=REPORT)
    parser.add_argument("--check-inputs", action="store_true")
    args = parser.parse_args()
    validate(json.loads(args.report.read_text()), check_inputs=args.check_inputs)
    print("cohesive CPUNET undefined classification: PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
