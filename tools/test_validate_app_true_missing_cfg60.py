#!/usr/bin/env python3
"""Regression tests for the fail-closed CPUAPP CFG60 proof ledger."""

from __future__ import annotations

import copy
import json
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import validate_app_true_missing_cfg60 as validator  # noqa: E402


class ValidateCfg60LedgerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.document = json.loads(validator.LEDGER.read_text())

    def test_committed_ledger_is_valid(self):
        self.assertEqual([], validator.validate_document(self.document))
        self.assertEqual(60, len(self.document["entries"]))
        self.assertNotIn(
            validator.EXCLUDED_VA,
            {entry["va"] for entry in self.document["entries"]},
        )

    def test_rejects_failed_or_unexecuted_proof(self):
        document = copy.deepcopy(self.document)
        document["entries"][0]["result"] = "FAIL"
        self.assertTrue(any(
            "non-PASS/unexecuted" in error
            for error in validator.validate_document(document, check_sources=False)
        ))

        document = copy.deepcopy(self.document)
        document["entries"][0]["checked"] = 0
        self.assertTrue(any(
            "non-PASS/unexecuted" in error
            for error in validator.validate_document(document, check_sources=False)
        ))

    def test_rejects_duplicate_inventory(self):
        document = copy.deepcopy(self.document)
        document["entries"][1]["va"] = document["entries"][0]["va"]
        errors = validator.validate_document(document, check_sources=False)
        self.assertIn("entry inventory/order mismatch", errors)
        self.assertIn("duplicate VA", errors)

    def test_rejects_digest_and_extent_drift(self):
        document = copy.deepcopy(self.document)
        document["entries"][0]["source_sha256"] = "0" * 64
        self.assertTrue(any(
            "digest mismatch" in error
            for error in validator.validate_document(document)
        ))

        document = copy.deepcopy(self.document)
        document["entries"][0]["extent"] += 2
        self.assertTrue(any(
            "extent mismatch" in error
            for error in validator.validate_document(document)
        ))

    def test_rejects_summary_drift(self):
        document = copy.deepcopy(self.document)
        document["summary"]["cfg_pass"] -= 1
        self.assertIn(
            "summary mismatch",
            validator.validate_document(document, check_sources=False),
        )


if __name__ == "__main__":
    unittest.main()
