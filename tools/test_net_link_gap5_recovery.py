#!/usr/bin/env python3
"""Fail-closed checks for the retained CPUNET link-gap-5 recovery."""

import hashlib
import json
import unittest
from pathlib import Path

import build_net_link_gap5_recovery as recovery


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap5_recovery.json"


class NetLinkGap5RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuilds_with_directed_cfg_proofs(self):
        self.assertEqual(recovery.build(), self.receipt)
        self.assertEqual(4, self.receipt["summary"]["function_count"])
        self.assertEqual(4, self.receipt["summary"]["cfg_pass_count"])
        self.assertEqual(16, self.receipt["summary"]["directed_case_count"])
        self.assertEqual(16, self.receipt["summary"]["checked_case_count"])

    def test_sources_are_hashed_readable_retained_c(self):
        for row in self.receipt["functions"]:
            path = ROOT / row["source"]
            data = path.read_bytes()
            source = data.decode()
            self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
            self.assertIn(row["raw_symbol"], source)
            self.assertIn(row["readable_symbol"], source)
            self.assertNotIn(".incbin", source)
            self.assertNotIn(".byte", source)
            self.assertNotIn(".inst", source)

    def test_policy_forbids_sdc_or_archive_removal(self):
        policy = self.receipt["policy"]
        self.assertEqual("retained_report_only", policy["private_controller_sdc"])
        self.assertTrue(policy["archive_or_stock_substitution_forbidden"])
        self.assertTrue(policy["directed_cases_are_process_local"])
        self.assertTrue(policy["shared_generated_and_cfg_outputs_untouched"])


if __name__ == "__main__":
    unittest.main()
