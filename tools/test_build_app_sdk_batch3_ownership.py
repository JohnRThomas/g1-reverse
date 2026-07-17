#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch3_ownership as ownership


class AppSdkBatch3OwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_scope_and_reference_count_are_exact(self):
        self.assertEqual(set(ownership.OWNERS), set(self.rows))
        self.assertEqual(8, self.data["summary"]["function_count"])
        self.assertEqual(48, self.data["summary"]["reference_count_before"])
        self.assertEqual(8, self.data["summary"]["cfg_verified"])

    def test_private_or_application_owners_are_retained(self):
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertEqual(1, self.data["summary"]["application_functions"])
        self.assertEqual(7, self.data["summary"]["configured_sdk_helpers"])
        self.assertTrue(all(row["decision"] ==
                            "retain_cfg_verified_configured_reconstruction"
                            for row in self.rows.values()))

    def test_cfg_evidence_is_per_symbol(self):
        for symbol, row in self.rows.items():
            self.assertEqual("cfg_verify.py app %s: PASS (%d checked)" %
                             (symbol, row["checked"]), row["verification"])
        self.assertEqual(302, self.rows["qspi_activate"]["checked"])
        self.assertIn("both wait selector cases covered",
                      self.rows["qspi_activate"]["config"])

    def test_semantic_ownership_is_not_conflated(self):
        self.assertEqual("application_function",
                         self.rows["flash_settings_read"]["linkage"])
        self.assertIn("atomic_builtin.h:atomic_and",
                      self.rows["atomic_and_2"]["upstream_owner"])
        self.assertIn("log_output.c:print_formatted",
                      self.rows["print_formatted"]["upstream_owner"])

    def test_source_and_verified_mirror_are_digest_pinned(self):
        for symbol, row in self.rows.items():
            self.assertEqual(row["sha256"], ownership.digest(
                os.path.join(ownership.ROOT, row["source"])), symbol)
            self.assertEqual(row["sha256"], ownership.digest(
                os.path.join(ownership.ROOT, row["verified_mirror"])), symbol)


if __name__ == "__main__":
    unittest.main()
