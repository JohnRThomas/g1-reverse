#!/usr/bin/env python3
"""Regression gates for the composed current CPUNET CFG corpus."""

import json
import unittest

from build_cfg_sweep_net_current_overlay import OUT_JSON, build


class NetCurrentCfgOverlayTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = json.loads(OUT_JSON.read_text())

    def test_serialization_and_complete_inventory_are_exact(self):
        self.assertEqual(self.data, build())
        self.assertEqual(self.data["previous_current_inventory_count"], 1131)
        self.assertEqual(self.data["current_inventory_count"], 1142)
        self.assertEqual(len(self.data["prior_added_proofs"]), 33)
        self.assertEqual(self.data["unresolved_count"], 0)
        self.assertEqual(self.data["source_drift"], [])

    def test_sdc_event_publish_is_exactly_the_new_proof(self):
        row = self.data["current_additions"][0]
        self.assertEqual(row["name"], "FUN_0101b4f4")
        self.assertEqual(row["readable_name"], "sdc_event_publish")
        self.assertEqual(row["analysis_address"], "0x0101b4f4")
        self.assertEqual(row["true_executable_extent"], 88)
        self.assertEqual((row["status"], row["checked"], row["cover_cases"]),
                         ("PASS", 5, 5))

    def test_esb_roots_and_existing_recheck_are_complete(self):
        additions = {row["name"]: row for row in self.data["current_additions"]}
        self.assertEqual(len(additions), 8)
        self.assertEqual(additions["FUN_0102a720"]["prefix_events"], 512)
        self.assertEqual(additions["FUN_0102a720"]["cover_cases"], 5)
        self.assertEqual(
            set(additions) - {"FUN_0101b4f4", "FUN_0102a720"},
            {"FUN_0102b3f0", "FUN_0102b664", "FUN_0102b718",
             "FUN_0102b758", "FUN_01033858", "FUN_010339d0"},
        )
        self.assertEqual(
            [row["name"] for row in self.data["reverified_existing"]],
            ["FUN_0102b31c"],
        )

    def test_frozen_parent_is_not_rewritten(self):
        self.assertEqual(
            self.data["frozen_parent"]["path"],
            "recon/analysis/cfg_sweep_net_recheck_overlay.json",
        )
        self.assertEqual(self.data["frozen_parent"]["inventory_count"], 1090)
        self.assertEqual(self.data["frozen_parent"]["unresolved_count"], 0)

    def test_latest_callback_receipt_closes_all_current_drift(self):
        added = {row["name"] for row in self.data["latest_added_proofs"]}
        changed = {row["name"] for row in self.data["latest_changed_proofs"]}
        self.assertEqual(len(added), 11)
        self.assertEqual(len(changed), 6)
        self.assertEqual(
            changed,
            {"FUN_0102a720", "FUN_0102ac0c", "FUN_0102acb4",
             "FUN_0102afbc", "FUN_0102b2ac", "FUN_0102b900"},
        )
        self.assertEqual(
            sum(row["checked"] for row in
                self.data["latest_added_proofs"] +
                self.data["latest_changed_proofs"]),
            376,
        )
        self.assertEqual(self.data["latest_proof_receipt"]["integration_commit"],
                         "c0fe95af")


if __name__ == "__main__":
    unittest.main()
