#!/usr/bin/env python3
"""Regression for CPUNET helpers that normalize dirty narrow ABI inputs."""

import unittest
from pathlib import Path

from cfg_verify import verify


ROOT = Path("/Users/freedomcoder/Projects/G1disasm2")
SOURCE = ROOT / "recon/net/src"


class NetNarrowAbiCfgTest(unittest.TestCase):
    def test_raw_register_width_is_preserved_in_sources(self):
        reserve = (SOURCE / "FUN_01009bc4.c").read_text()
        update = (SOURCE / "FUN_01009c68.c").read_text()

        self.assertIn("unsigned int channel_raw", reserve)
        self.assertIn("(unsigned char)channel_raw", reserve)
        self.assertIn("unsigned int event_counter_raw", update)
        self.assertIn("unsigned int channel_raw", update)
        self.assertIn("(unsigned short)event_counter_raw", update)
        self.assertIn("(unsigned char)channel_raw", update)

    def test_dirty_upper_register_bits_match_shipped_normalization(self):
        for name in ("FUN_01009bc4", "FUN_01009c68"):
            with self.subTest(name=name):
                verdict = verify("net", name, trials_random=40)
                self.assertEqual("PASS", verdict["status"], verdict)
                self.assertEqual(40, verdict["checked"], verdict)

    def test_narrow_formal_regression_is_rejected(self):
        source = (SOURCE / "FUN_01009bc4.c").read_text()
        wrong = source.replace(
            "unsigned int channel_raw", "unsigned char channel_raw", 1)
        verdict = verify(
            "net", "FUN_01009bc4", trials_random=40,
            source_override=wrong,
        )
        self.assertEqual("FAIL", verdict["status"], verdict)
        self.assertGreater(verdict["mismatches"], 0, verdict)


if __name__ == "__main__":
    unittest.main()
