#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch4_ownership as ownership


class AppSdkBatch4OwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_exact_scope_and_input_delta(self):
        self.assertEqual(set(ownership.OWNERS), set(self.rows))
        self.assertEqual(8, self.data["summary"]["function_count"])
        self.assertEqual(40, self.data["summary"]["reference_count_before"])
        self.assertTrue(all(row["reference_count_before"] == 5
                            for row in self.rows.values()))

    def test_policy_is_fail_closed(self):
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertTrue(all("static" in row["linkage"] or "inline" in row["linkage"]
                            for row in self.rows.values()))
        self.assertTrue(all(row["decision"] ==
                            "retain_cfg_verified_configured_reconstruction"
                            for row in self.rows.values()))
        self.assertEqual("not claimed by this canonical-only milestone",
                         self.data["integration"]["retain_all_result"])

    def test_cfg_evidence_and_backmaps_are_per_symbol(self):
        for symbol, row in self.rows.items():
            self.assertIn("PASS (CFG cases=%d, random=40)" % row["cfg_cases"],
                          row["verification"])
            with open(os.path.join(ownership.ROOT, row["source"]), encoding="utf-8") as stream:
                source = stream.read()
            self.assertIn(row["va"], source)
        self.assertEqual(2, self.rows["net_buf_frags_len"]["cfg_cases"])

    def test_critical_abi_specializations_are_recorded(self):
        self.assertIn("frags offset=4", self.rows["net_buf_frags_len"]["config"])
        self.assertIn("len offset=16", self.rows["net_buf_frags_len"]["config"])
        self.assertIn("sense pointer is sixth argument",
                      self.rows["nrf_gpio_cfg_sense_set"]["config"])
        self.assertIn("PIN_FLAG_TE_USED=BIT(5)",
                      self.rows["pin_in_use_by_te"]["config"])
        self.assertTrue(all("CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768" in self.rows[name]["config"]
                            for name in ("k_uptime_get_6", "k_uptime_get_8",
                                         "k_uptime_get_9", "k_uptime_get_10")))


if __name__ == "__main__":
    unittest.main()
