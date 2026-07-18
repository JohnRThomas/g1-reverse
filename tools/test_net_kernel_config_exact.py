#!/usr/bin/env python3
"""Fail-closed regression for the CPUNET spinlock/layout configuration."""

import json
import unittest
from pathlib import Path

import build_net_kernel_config_receipt as receipt


ROOT = Path(__file__).resolve().parents[1]
PRJ = ROOT / "recon/application/net/prj.conf"
AUDIT = ROOT / "recon/ownership/net_kernel_config_exact.json"


class NetKernelConfigExactTest(unittest.TestCase):
    def test_canonical_config_pins_the_discriminating_pair(self):
        text = PRJ.read_text()
        self.assertIn("CONFIG_SPIN_VALIDATE=y", text)
        self.assertIn("CONFIG_SMP=n", text)

    def test_fresh_stock_reference_reproduces_nine_firmware_sections(self):
        current = json.loads(AUDIT.read_text())
        self.assertEqual(current, receipt.build())
        self.assertEqual(9, len(current["section_matches"]))
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in current["section_matches"]))
        self.assertEqual(0x20, current["layout_discriminators"][
            "onoff_manager_size"])
        self.assertEqual(0x24, current["layout_discriminators"][
            "onoff_manager_size_if_smp"])

    def test_receipt_cannot_authorize_sdc_or_source_removal(self):
        current = json.loads(AUDIT.read_text())
        self.assertFalse(current["authorizes_source_exclusion"])
        self.assertEqual("report_only_unchanged", current["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
