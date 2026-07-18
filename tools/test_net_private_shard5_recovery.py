#!/usr/bin/env python3
"""Fail-closed tests for the CPUNET private shard-5 recovery receipt."""

import hashlib
import json
import unittest
from pathlib import Path

import build_net_private_shard5_recovery as shard


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_private_shard5_recovery.json"


class NetPrivateShard5RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuilds_with_authoritative_cfg_verify(self):
        self.assertEqual(shard.build(), self.receipt)
        self.assertEqual(12, self.receipt["summary"]["function_count"])
        self.assertEqual(1012,
                         self.receipt["summary"]["total_true_executable_extent"])
        self.assertEqual(12, self.receipt["summary"]["cfg_pass_count"])

    def test_sources_preserve_backmaps_hashes_and_readable_bodies(self):
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            text = data.decode()
            self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertTrue(row["readable_role"])
            self.assertNotIn(".incbin", text)
            self.assertNotIn(".byte", text)
            self.assertNotIn(".inst", text)

    def test_policy_remains_fail_closed(self):
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_readable_c_only"])
        self.assertTrue(policy["archive_or_blob_substitution_forbidden"])
        self.assertEqual("report_only_unchanged", policy["private_sdc_mpsl"])
        self.assertTrue(
            policy["shared_generated_name_adoption_cfg_outputs_untouched"])

    def test_object_level_optimization_observation_is_recorded(self):
        observation = self.receipt["build_observations"]
        self.assertIn("optimize(O2)", observation["buffer_descriptor_helpers"])
        self.assertIn("object-level", observation["interpretation"])


if __name__ == "__main__":
    unittest.main()
