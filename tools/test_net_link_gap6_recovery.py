#!/usr/bin/env python3
"""Fail-closed gates for the sixth retained CPUNET gap shard."""

import hashlib
import json
import unittest
from pathlib import Path

import cfg_verify
import build_net_link_gap6_recovery as builder


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap6_recovery.json"


class NetLinkGap6RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuild_is_exact(self):
        rebuilt = json.loads(json.dumps(builder.build()))
        self.assertEqual(self.receipt, rebuilt)

    def test_sources_and_policy_are_fail_closed(self):
        self.assertEqual(4, self.receipt["summary"]["function_count"])
        self.assertEqual(136, self.receipt["summary"]["total_true_executable_extent"])
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_readable_c_only"])
        self.assertFalse(policy["blobs_used"])
        self.assertFalse(policy["archive_substitution_used"])
        self.assertTrue(policy["private_sdc_retained_report_only"])
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            text = data.decode()
            self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertIn(row["readable_identity"], text)
            self.assertNotIn(".incbin", text)
            self.assertNotIn(".byte", text)

    def test_reviewed_directed_cases_remain_green(self):
        saved_state = dict(cfg_verify.REVIEWED_STATE_CASES)
        saved_oracle = dict(cfg_verify.REVIEWED_ORACLE_CASES)
        saved_nptr = dict(cfg_verify.REVIEWED_NPTR_COUNTS)
        saved_arities = dict(cfg_verify.REVIEWED_TARGET_CALL_ARITIES)
        try:
            builder.install_reviewed_cases()
            for row in self.receipt["functions"]:
                with self.subTest(symbol=row["raw_symbol"]):
                    verdict = cfg_verify.verify("net", row["raw_symbol"], trials_random=0)
                    self.assertEqual("PASS", verdict["status"])
                    self.assertGreater(verdict["checked"], 0)
        finally:
            cfg_verify.REVIEWED_STATE_CASES.clear()
            cfg_verify.REVIEWED_STATE_CASES.update(saved_state)
            cfg_verify.REVIEWED_ORACLE_CASES.clear()
            cfg_verify.REVIEWED_ORACLE_CASES.update(saved_oracle)
            cfg_verify.REVIEWED_NPTR_COUNTS.clear()
            cfg_verify.REVIEWED_NPTR_COUNTS.update(saved_nptr)
            cfg_verify.REVIEWED_TARGET_CALL_ARITIES.clear()
            cfg_verify.REVIEWED_TARGET_CALL_ARITIES.update(saved_arities)


if __name__ == "__main__":
    unittest.main()
