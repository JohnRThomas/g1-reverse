#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch2_ownership as ownership


class AppSdkBatch2OwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_scope_and_delta_are_exact(self):
        self.assertEqual(set(ownership.OWNERS), set(self.rows))
        self.assertEqual(46, self.data["summary"]["reference_count_before"])
        self.assertEqual(5, self.data["summary"]["cfg_verified"])
        self.assertEqual(1, self.data["summary"]["dependency_count"])

    def test_only_static_or_inline_configured_bodies_are_retained(self):
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertTrue(all("static" in row["linkage"] or "inline" in row["linkage"]
                            for row in self.rows.values()))
        self.assertTrue(all(row["decision"] == "retain_cfg_verified_configured_reconstruction"
                            for row in self.rows.values()))

    def test_cfg_evidence_is_per_symbol(self):
        for symbol, row in self.rows.items():
            self.assertEqual("cfg_verify.py app %s: PASS (40 checked)" % symbol,
                             row["verification"])
        self.assertEqual("__nrfy_internal_twim_event_handle",
                         self.data["dependencies"][0]["symbol"])
        self.assertIn("PASS (40 checked)", self.data["dependencies"][0]["verification"])

    def test_critical_config_specializations_are_recorded(self):
        self.assertIn("CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768",
                      self.rows["k_uptime_get_1"]["config"])
        self.assertIn("port_offset=0x000f6ba7", self.rows["get_pin_idx"]["config"])
        self.assertIn("p_xfer specialized away",
                      self.rows["__nrfy_internal_twim_events_process"]["config"])
        self.assertIn("unused len specialized away", self.rows["smp_create_pdu"]["config"])


if __name__ == "__main__":
    unittest.main()
