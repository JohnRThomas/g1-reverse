#!/usr/bin/env python3
"""Fail-closed arithmetic and policy gate for CPUNET size convergence."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/analysis/net_size_convergence_receipt.json"
DOC = ROOT / "recon/analysis/net_layout_convergence.md"


class NetSizeConvergenceReceiptTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_measurement_arithmetic(self):
        baseline = self.receipt["baseline"]
        combined = self.receipt["combined"]
        self.assertEqual(baseline["overflow"],
                         baseline["flash_used"] - baseline["flash_capacity"])
        self.assertEqual(combined["overflow"],
                         combined["flash_used"] - combined["flash_capacity"])
        self.assertEqual(-128,
                         combined["flash_used"] - baseline["flash_used"])
        self.assertEqual(128, baseline["overflow"] - combined["overflow"])
        self.assertEqual(0x37AF9, baseline["flash_used"])
        self.assertEqual(0x37A79, combined["flash_used"])

    def test_commit_deltas_and_receipts_are_pinned(self):
        commits = self.receipt["shrink_commits"]
        self.assertEqual(
            ["127c0f4c", "2ebf5e43", "144e82d9"],
            [row["commit"][:8] for row in commits],
        )
        self.assertEqual([-4, -76, -44],
                         [row["production_object_bytes_delta"] for row in commits])
        self.assertEqual(-124, sum(
            row["production_object_bytes_delta"] for row in commits))
        for row in commits:
            self.assertTrue((ROOT / row["receipt"]).is_file(), row["receipt"])

    def test_alignment_accounts_for_whole_image_delta(self):
        combined = self.receipt["combined"]
        self.assertEqual(
            combined["whole_image_bytes_delta"],
            combined["production_object_bytes_delta"]
            + combined["alignment_bytes_delta"],
        )

    def test_policy_stays_fail_closed(self):
        policy = self.receipt["policy"]
        self.assertTrue(policy["normal_gc"])
        self.assertFalse(policy["retain_all"])
        self.assertFalse(policy["proven_roots_removed"])
        self.assertFalse(policy["automatic_sdc_removal"])
        self.assertTrue(policy["sdc_remains_report_only"])
        self.assertFalse(policy["padding_or_region_growth_used"])
        self.assertEqual(0, self.receipt["baseline"]["undefined_symbol_diagnostics"])
        self.assertEqual(0, self.receipt["combined"]["undefined_symbol_diagnostics"])

    def test_document_records_current_gate(self):
        text = DOC.read_text()
        for token in ("0x37af9", "0x37a79", "761", "633",
                      "net_size_convergence_receipt.json"):
            self.assertIn(token, text)


if __name__ == "__main__":
    unittest.main()
