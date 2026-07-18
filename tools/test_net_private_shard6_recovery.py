#!/usr/bin/env python3
"""Fail-closed tests for the CPUNET private shard-6 recovery receipt."""

import hashlib
import json
import unittest
from pathlib import Path

import build_net_private_shard6_recovery as shard


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_private_shard6_recovery.json"


class NetPrivateShard6RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_exact_worklist_closure_and_authoritative_cfg_results(self):
        rebuilt = shard.build()
        self.assertEqual(self.receipt, rebuilt)
        self.assertEqual(12, rebuilt["summary"]["function_count"])
        self.assertEqual(1010,
                         rebuilt["summary"]["total_true_executable_extent"])
        self.assertEqual(12, rebuilt["summary"]["cfg_pass_count"])
        self.assertEqual(466, rebuilt["summary"]["cfg_checked_trials"])
        self.assertEqual(26, rebuilt["summary"]["cfg_directed_cover_cases"])

    def test_sources_raw_backmaps_and_hashes(self):
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            self.assertEqual(row["source_sha256"],
                             hashlib.sha256(data).hexdigest())
            text = data.decode()
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertTrue(row["readable_role"])

    def test_no_replacement_or_policy_expansion(self):
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_c_required"])
        self.assertTrue(policy["no_blobs"])
        self.assertTrue(policy["archive_replacement_forbidden"])
        self.assertFalse(policy["shared_verifier_mutated"])
        self.assertEqual("report_only_unchanged",
                         policy["private_sdc_mpsl"])


if __name__ == "__main__":
    unittest.main()
