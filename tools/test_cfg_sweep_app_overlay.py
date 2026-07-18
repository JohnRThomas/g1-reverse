#!/usr/bin/env python3
"""Regression gates for the authoritative CPUAPP post-baseline overlay."""

import json
import subprocess
import sys
import unittest

from build_cfg_sweep_app_overlay import (
    BASELINE, EXPECTED_BASELINE_SHA256, EXPECTED_OVERLAY, OUT_JSON, build, sha256,
)


class AppCfgSweepOverlayTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = build()

    def test_frozen_baseline_is_immutable(self):
        self.assertEqual(EXPECTED_BASELINE_SHA256, sha256(BASELINE))
        self.assertTrue(self.data["baseline"]["preserved_immutable"])
        self.assertEqual(2113, self.data["baseline"]["inventory_count"])

    def test_overlay_covers_roots_and_repaired_dmic(self):
        rows = {row["name"]: row for row in self.data["overlay_proofs"]}
        self.assertEqual(set(EXPECTED_OVERLAY), set(rows))
        self.assertEqual(["aging_mode_thread", "master_display_thread"],
                         self.data["post_baseline_added"])
        self.assertEqual(["FUN_0002f080", "slave_display_thread"],
                         self.data["post_baseline_changed"])
        self.assertEqual([], self.data["post_baseline_removed"])
        self.assertTrue(all(row["status"] == "PASS" for row in rows.values()))

    def test_current_inventory_is_fully_hash_covered(self):
        self.assertEqual(2115, self.data["current_inventory_count"])
        self.assertEqual(2115, len(self.data["current_functions"]))
        self.assertEqual(2115, self.data["current_counts"]["PASS"])
        self.assertEqual(0, self.data["unresolved_count"])
        self.assertTrue(self.data["current_source_tree_fully_covered"])
        self.assertEqual([], self.data["unverified_source_drift"])

    def test_committed_output_matches_builder(self):
        if OUT_JSON.exists():
            self.assertEqual(self.data, json.loads(OUT_JSON.read_text()))

    def test_authoritative_validator_composes_overlay(self):
        result = subprocess.run(
            [sys.executable, "tools/validate_cfg_sweep_app_report.py", "--check-current"],
            cwd=OUT_JSON.parents[2], text=True, capture_output=True)
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn("inventory=2115 unresolved=0", result.stdout)


if __name__ == "__main__":
    unittest.main()
