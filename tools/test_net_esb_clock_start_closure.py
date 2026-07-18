#!/usr/bin/env python3
"""Fail-closed tests for the CPUNET ESB clock callback closure."""

from __future__ import annotations

import json
import unittest
from pathlib import Path

import build_net_esb_clock_start_closure as builder


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_esb_clock_start_closure.json"


class NetEsbClockStartClosureTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_replays_all_cfg_proofs(self) -> None:
        self.assertEqual(self.receipt, builder.build_receipt())
        self.assertEqual(7, self.receipt["summary"]["function_count"])
        self.assertEqual(7, self.receipt["summary"]["cfg_pass_count"])
        for proof in self.receipt["proofs"]:
            self.assertEqual("PASS", proof["cfg_result"]["status"])
            self.assertGreater(proof["cfg_result"]["checked"], 0)

    def test_binary_callback_is_the_only_production_root_claim(self) -> None:
        root = self.receipt["production_root"]
        self.assertEqual("0x0102b758", root["analysis_address"])
        self.assertEqual("0x0102bf59", root["stored_runtime_thumb_pointer"])
        self.assertEqual("FUN_0102b5bc", root["registrar"])

    def test_sources_are_readable_and_reversibly_backmapped(self) -> None:
        for proof in self.receipt["proofs"]:
            text = (ROOT / proof["source"]).read_text()
            self.assertIn(proof["raw_symbol"], text)
            self.assertIn(proof["readable_identity"], text)
            self.assertNotIn(".incbin", text)
            self.assertNotIn("__attribute__((naked))", text)

    def test_policy_keeps_sdc_and_public_esb_duplicates(self) -> None:
        policy = self.receipt["policy"]
        self.assertTrue(policy["sdc_retained_report_only"])
        self.assertFalse(policy["archive_substitution_used"])
        self.assertTrue(policy["public_esb_duplicates_retained_pending_exact_source_assembly"])


if __name__ == "__main__":
    unittest.main()
