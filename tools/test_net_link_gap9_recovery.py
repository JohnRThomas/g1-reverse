#!/usr/bin/env python3
"""Fail-closed gates for retained CPUNET link gap 9."""

import hashlib
import json
import unittest
from pathlib import Path

import cfg_verify
import build_net_link_gap9_recovery as builder


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap9_recovery.json"


class NetLinkGap9RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuild_is_exact(self):
        self.assertEqual(self.receipt, builder.build())

    def test_source_extent_and_policy_are_fail_closed(self):
        self.assertEqual(1, self.receipt["summary"]["function_count"])
        self.assertEqual(0x38,
                         self.receipt["summary"]["total_true_executable_extent"])
        row = self.receipt["functions"][0]
        self.assertEqual([], row["callees"])
        self.assertEqual("0x01028112", row["caller"])
        source = ROOT / row["source"]
        data = source.read_bytes()
        text = data.decode()
        self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
        for marker in (row["raw_symbol"], row["analysis_address"],
                       row["readable_identity"]):
            self.assertIn(marker, text)
        self.assertNotIn(".incbin", text)
        self.assertNotIn(".byte", text)
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_readable_c_only"])
        self.assertFalse(policy["blobs_used"])
        self.assertFalse(policy["archive_substitution_used"])
        self.assertTrue(policy["private_sdc_retained_report_only"])
        self.assertFalse(policy["shared_cfg_tool_modified"])

    def test_reviewed_directed_cases_remain_green(self):
        saved_state = dict(cfg_verify.REVIEWED_STATE_CASES)
        saved_nptr = dict(cfg_verify.REVIEWED_NPTR_COUNTS)
        try:
            builder.install_reviewed_cases()
            verdict = cfg_verify.verify(
                "net", builder.RAW_SYMBOL, trials_random=0)
            self.assertEqual("PASS", verdict["status"])
            self.assertEqual(11, verdict["cover_cases"])
            self.assertEqual(11, verdict["checked"])
        finally:
            cfg_verify.REVIEWED_STATE_CASES.clear()
            cfg_verify.REVIEWED_STATE_CASES.update(saved_state)
            cfg_verify.REVIEWED_NPTR_COUNTS.clear()
            cfg_verify.REVIEWED_NPTR_COUNTS.update(saved_nptr)


if __name__ == "__main__":
    unittest.main()
