#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_interior_alias_audit as audit


class AppInteriorAliasAuditTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()
        cls.rows = {row["symbol"]: row for row in cls.data["entries"]}

    def test_complete_manual_partition(self):
        self.assertEqual(9, self.data["summary"]["residue_count"])
        self.assertEqual({"same_entry_alias": 1,
                          "legitimate_interior_tail_or_island": 3,
                          "sdk_static_or_library_identity": 3,
                          "data_or_literal_misreference": 0,
                          "true_missing_catalog_entry": 2},
                         self.data["summary"]["classification_counts"])

    def test_fail_closed_policy(self):
        policy = self.data["policy"]
        self.assertTrue(policy["fail_closed"])
        self.assertFalse(policy["aliases_emitted"])
        self.assertFalse(policy["invented_bodies"])
        self.assertFalse(policy["derivatives_regenerated"])

    def test_sdk_and_newlib_identities_do_not_require_reconstruction(self):
        for symbol in audit.SDK_STATIC_OR_LIBRARY_IDENTITY:
            self.assertNotEqual("requires_independent_reconstruction",
                                self.rows[symbol]["resolution"])

    def test_unsafe_islands_remain_blocked(self):
        for symbol in ("FUN_0005463e", "FUN_00054688",
                       "FUN_0008131c", "thunk_FUN_0007f7d2"):
            self.assertTrue(self.rows[symbol]["resolution"].startswith("blocked_"))

    def test_missing_entries_are_not_promoted_to_aliases(self):
        missing = [row for row in self.data["entries"]
                   if row["classification"] == "true_missing_catalog_entry"]
        self.assertEqual(2, len(missing))
        self.assertEqual(0, self.data["summary"]["requires_reconstruction"])
        self.assertEqual(2, self.data["summary"]["already_strong_owners"])
        for symbol in audit.CFG_VERIFIED_STRONG_OWNERS:
            self.assertEqual("already_resolved_by_cfg_verified_strong_owner",
                             self.rows[symbol]["resolution"])
        self.assertTrue(all(row["evidence"]["decode"] for row in missing))

    def test_refgraph_and_catalog_boundaries_are_recorded(self):
        for row in self.data["entries"]:
            evidence = row["evidence"]
            self.assertIn("previous_catalog_end", evidence)
            self.assertIn("next_catalog_entry", evidence)
            self.assertIn("refgraph_entry", evidence)
            self.assertIn("refgraph_incoming_call_edges", evidence)


if __name__ == "__main__":
    unittest.main()
