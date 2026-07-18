#!/usr/bin/env python3
"""Fail-closed checks for the four CPUNET link-gap reconstructions."""

import hashlib
import json
import unittest
from pathlib import Path

import build_net_link_gap3_recovery as recovery


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap3_recovery.json"


class NetLinkGap3RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuilds_with_authoritative_and_directed_proofs(self):
        rebuilt = recovery.build()
        self.assertEqual(self.receipt, rebuilt)
        self.assertEqual(4, rebuilt["summary"]["function_count"])
        self.assertEqual(0xEC, rebuilt["summary"]["total_true_executable_extent"])
        self.assertEqual(4, rebuilt["summary"]["cfg_pass_count"])
        self.assertEqual(9, rebuilt["summary"]["additional_directed_trials"])

    def test_sources_hashes_names_and_raw_backmaps_are_fail_closed(self):
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
            text = data.decode()
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertIn(row["recommended_readable_name"], text)

    def test_no_archive_or_blob_policy_expansion(self):
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_c_required"])
        self.assertTrue(policy["no_blobs"])
        self.assertTrue(policy["archive_replacement_forbidden"])
        self.assertEqual("report_only_unchanged", policy["private_sdc_mpsl"])
        self.assertTrue(all(row["archive_identity_is_provenance_only"]
                            for row in self.receipt["functions"]))


if __name__ == "__main__":
    unittest.main()
