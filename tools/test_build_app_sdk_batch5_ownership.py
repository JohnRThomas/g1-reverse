#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch5_ownership as ownership


class AppSdkBatch5OwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_exact_scope_and_reference_delta(self):
        self.assertEqual(set(ownership.OWNERS), set(self.rows))
        self.assertEqual(8, self.data["summary"]["function_count"])
        self.assertEqual(39, self.data["summary"]["reference_count_before"])
        self.assertEqual(4, self.rows["qspi_nor_write_protection_set"]["reference_count_before"])

    def test_fail_closed_policy(self):
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertTrue(all(row["decision"] ==
                            "retain_cfg_verified_configured_reconstruction"
                            for row in self.rows.values()))
        self.assertEqual("not claimed by this canonical-only milestone",
                         self.data["integration"]["retain_all_result"])

    def test_cfg_and_raw_backmaps(self):
        for symbol, row in self.rows.items():
            self.assertIn("PASS (%d checked" % row["checked"], row["verification"])
            with open(os.path.join(ownership.ROOT, row["source"]), encoding="utf-8") as stream:
                source = stream.read()
            self.assertIn(row["va"], source)
            self.assertIn("FUN_%08x" % int(row["va"], 16), source)
        self.assertEqual(2, self.rows["gatt_discover_next"]["cfg_cases"])
        self.assertEqual(3, self.rows["FUN_00066e70"]["cfg_cases"])

    def test_pinned_abi_details(self):
        self.assertEqual("pin_init", self.rows["FUN_00066e70"]["readable_name"])
        self.assertIn("bt_addr_le_t size=7", self.rows["bt_addr_le_eq"]["config"])
        self.assertIn("read-back verification",
                      self.rows["flash_settings_write_and_verify"]["config"])
        self.assertTrue(all("sequentially consistent" in self.rows[name]["config"]
                            for name in ("atomic_and", "atomic_and_3", "atomic_clear_bit_1")))


if __name__ == "__main__":
    unittest.main()
