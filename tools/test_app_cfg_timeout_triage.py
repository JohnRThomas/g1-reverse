#!/usr/bin/env python3
"""Focused integrity tests for CPUAPP timeout/OTHER triage."""

from __future__ import annotations

import hashlib
import json
import unittest
from pathlib import Path


BASE = Path(__file__).resolve().parents[1]
RECEIPT = BASE / "recon/analysis/app_cfg_timeout_other_triage.json"


class AppCfgTimeoutTriageTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.data = json.loads(RECEIPT.read_text())

    def test_inventory_and_classifications_are_complete(self) -> None:
        records = self.data["records"]
        self.assertEqual(len(records), 24)
        self.assertEqual(sum(r["initial_outcome"] == "TIMEOUT" for r in records), 22)
        self.assertEqual(sum(r["initial_outcome"] == "OTHER" for r in records), 2)
        self.assertEqual(self.data["summary"]["source_defects_proven"], 0)
        self.assertTrue(all(not r["source_defect"] for r in records))

    def test_source_hashes_are_current(self) -> None:
        for record in self.data["records"]:
            with self.subTest(name=record["name"]):
                source = BASE / record["source_path"]
                self.assertEqual(
                    hashlib.sha256(source.read_bytes()).hexdigest(),
                    record["source_sha256"],
                )

    def test_report_only_policy(self) -> None:
        self.assertEqual(self.data["policy"], {
            "app_sources_modified": False,
            "parity_or_mmio_tools_modified": False,
            "report_only": True,
            "shared_verifier_modified": False,
        })


if __name__ == "__main__":
    unittest.main()
