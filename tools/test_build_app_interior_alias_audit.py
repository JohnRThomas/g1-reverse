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
        self.assertEqual(66, self.data["summary"]["residue_count"])
        self.assertEqual({"same_entry_alias": 1,
                          "legitimate_interior_tail_or_island": 4,
                          "data_or_literal_misreference": 0,
                          "true_missing_catalog_entry": 61},
                         self.data["summary"]["classification_counts"])

    def test_fail_closed_policy(self):
        policy = self.data["policy"]
        self.assertTrue(policy["fail_closed"])
        self.assertFalse(policy["aliases_emitted"])
        self.assertFalse(policy["invented_bodies"])
        self.assertFalse(policy["derivatives_regenerated"])

    def test_internal_island_caller_was_corrected(self):
        row = self.rows["FUN_0006446c"]
        self.assertEqual("legitimate_interior_tail_or_island",
                         row["classification"])
        self.assertEqual("caller_corrected_to_internal_failure_result",
                         row["resolution"])

    def test_unsafe_islands_remain_blocked(self):
        for symbol in ("FUN_0005463e", "FUN_00054688",
                       "FUN_0008131c", "thunk_FUN_0007f7d2"):
            self.assertTrue(self.rows[symbol]["resolution"].startswith("blocked_"))

    def test_missing_entries_are_not_promoted_to_aliases(self):
        missing = [row for row in self.data["entries"]
                   if row["classification"] == "true_missing_catalog_entry"]
        self.assertEqual(61, len(missing))
        self.assertEqual(60, self.data["summary"]["requires_reconstruction"])
        self.assertEqual("already_resolved_by_cfg_verified_strong_owner",
                         self.rows["FUN_00086228"]["resolution"])
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
