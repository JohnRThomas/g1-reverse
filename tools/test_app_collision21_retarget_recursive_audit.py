#!/usr/bin/env python3
"""Regression tests for the COLLISION-21 recursive-lock audit."""

import json
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import build_app_collision21_retarget_recursive_audit as audit


class AppCollision21RetargetRecursiveAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_fails_closed_without_build_mutation(self):
        self.assertEqual(self.data["decision"],
                         "retain_and_namespace_both_reconstructions")
        self.assertFalse(self.data["adoption_authorized"])
        self.assertFalse(self.data["overlay_changed"])

    def test_abi_and_state_model_are_shared_but_assertions_are_not(self):
        for row in self.rows.values():
            self.assertEqual(row["abi"]["params"], ["_LOCK_T"])
            self.assertEqual(row["abi"]["return"], "void")
            self.assertEqual(row["state_model"]["owned_globals"], [])
            self.assertTrue(row["assertion"]["firmware_active"])
            self.assertFalse(row["assertion"]["configured_object_present"])
            self.assertFalse(row["signature_match"]["normalized_exact"])

    def test_true_extents_stop_before_literal_pools(self):
        acquire = self.rows["__retarget_lock_acquire_recursive"]
        release = self.rows["__retarget_lock_release_recursive"]
        self.assertEqual((acquire["true_code_extent"],
                          acquire["literal_pool_starts_at"]),
                         (44, "0x00051128"))
        self.assertEqual((release["true_code_extent"],
                          release["literal_pool_starts_at"]),
                         (36, "0x00051158"))

    def test_cfg_proves_retained_and_rejects_sdk_semantics(self):
        for row in self.rows.values():
            self.assertEqual(row["cfg_verify"]["retained"], {
                "status": "PASS", "cases": 2,
                "selectors": {0: [0, 1]}})
            negative = row["cfg_verify"][
                "configured_sdk_semantics_negative_control"]
            self.assertEqual(negative["status"], "FAIL")
            self.assertEqual(negative["mismatches"], 1)
            self.assertEqual(negative["mismatch_kinds"], ["direct-target"])

    def test_complete_caller_and_direct_site_closure(self):
        acquire = self.rows["__retarget_lock_acquire_recursive"]
        release = self.rows["__retarget_lock_release_recursive"]
        self.assertEqual(len(acquire["callers"]), 6)
        self.assertEqual(len(acquire["direct_branch_sites"]), 6)
        self.assertEqual(len(release["callers"]), 6)
        self.assertEqual(len(release["direct_branch_sites"]), 7)
        self.assertEqual(sum(item["va"] == "0x76ed4"
                             for item in release["callers"]), 1)
        self.assertIn("0x00076f46", release["direct_branch_sites"])
        self.assertIn("0x000770e8", release["direct_branch_sites"])
        self.assertTrue(all(item["cfg_verify"] == "PASS"
                            for row in self.rows.values()
                            for item in row["callers"]))

    def test_configured_relocations_are_minimal_tail_calls(self):
        self.assertEqual(self.rows["__retarget_lock_acquire_recursive"]
                         ["configured_sdk_relocations"],
                         ["z_impl_k_mutex_lock"])
        self.assertEqual(self.rows["__retarget_lock_release_recursive"]
                         ["configured_sdk_relocations"],
                         ["z_impl_k_mutex_unlock"])

    def test_catalog_is_deterministic(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(audit.OUT_JSON.read_text(), expected)
        self.assertEqual(audit.OUT_MD.read_text(), audit.markdown(self.data))


if __name__ == "__main__":
    unittest.main()
