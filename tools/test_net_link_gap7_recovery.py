#!/usr/bin/env python3
"""Fail-closed gates for four retained private CPUNET helpers."""

import hashlib
import json
import unittest
from pathlib import Path

import build_net_link_gap7_recovery as builder


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap7_recovery.json"


class NetLinkGap7RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_replays_authoritative_proofs(self):
        rebuilt = builder.build()
        self.assertEqual(self.receipt, rebuilt)
        self.assertEqual(4, rebuilt["summary"]["function_count"])
        self.assertEqual(4, rebuilt["summary"]["cfg_pass_count"])
        self.assertEqual(0x144, rebuilt["summary"]["total_true_executable_extent"])
        self.assertEqual(14, rebuilt["summary"]["cfg_directed_cover_cases"])

    def test_sources_and_firmware_extents_are_hash_locked(self):
        firmware = (ROOT / "netcore_image.bin").read_bytes()
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            self.assertEqual(row["source_sha256"], hashlib.sha256(data).hexdigest())
            text = data.decode()
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["readable_identity"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertNotIn(".incbin", text)
            va = int(row["analysis_address"], 16)
            extent = row["true_executable_extent"]
            image = firmware[va - 0x01008000:va - 0x01008000 + extent]
            self.assertEqual(row["firmware_extent_sha256"],
                             hashlib.sha256(image).hexdigest())

    def test_sdc_policy_remains_report_only(self):
        self.assertEqual({
            "canonical_readable_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "private_sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        }, self.receipt["policy"])


if __name__ == "__main__":
    unittest.main()
