#!/usr/bin/env python3
import os
import sys
import unittest


TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_app_high_fanin_sdk_ownership as ownership


class AppHighFaninSdkOwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.by_symbol = {row["symbol"]: row for row in cls.data["functions"]}

    def test_exact_fail_closed_scope(self):
        self.assertEqual({"log_message", "atomic_get_3_0", "atomic_test_bit",
                          "atomic_set_bit"}, set(self.by_symbol))
        self.assertEqual(377, self.data["summary"]["resolved_reference_count"])
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertTrue(all(row["retain_reconstruction"] for row in self.by_symbol.values()))
        self.assertTrue(all(not row["exclude_reconstruction"] for row in self.by_symbol.values()))

    def test_log_owner_is_distinct_from_debug_print(self):
        row = self.by_symbol["log_message"]
        self.assertEqual("0x0007dda4", row["va"])
        self.assertIn("vprintf", row["semantic_owner"])
        self.assertIn("0x00019c70", self.data["policy"]["forbidden_alias"])

    def test_display_accessor_is_not_generic_atomic_get(self):
        row = self.by_symbol["atomic_get_3_0"]
        self.assertEqual("display atomic-state accessor", row["semantic_owner"])
        self.assertIn("0x2000a030", row["abi"])

    def test_atomic_header_and_config_are_pinned(self):
        for symbol in ("atomic_test_bit", "atomic_set_bit"):
            row = self.by_symbol[symbol]
            self.assertEqual("zephyr/include/zephyr/sys/atomic.h",
                             row["upstream_provenance"])
            self.assertEqual(["CONFIG_ATOMIC_OPERATIONS_BUILTIN=y"], row["config"])
            self.assertIn("cfg_verify.py app %s: PASS" % symbol, row["verification"])


if __name__ == "__main__":
    unittest.main()
