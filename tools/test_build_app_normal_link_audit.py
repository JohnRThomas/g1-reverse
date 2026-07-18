#!/usr/bin/env python3
"""Regression tests for the normal CPUAPP cohesive-link audit."""

import json
import os
import sys
import unittest
from pathlib import Path

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_app_normal_link_audit as audit


class NormalLinkAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()

    def test_normal_link_is_real_and_fails(self):
        self.assertFalse(self.data["evidence"]["retain_all"])
        self.assertFalse(self.data["summary"]["final_elf_links"])
        self.assertFalse(audit.ELF.exists())

    def test_collision_set_is_exact(self):
        self.assertEqual(self.data["summary"]["collision_diagnostics"], 112)
        self.assertEqual(self.data["summary"]["unique_collision_symbols"], 112)
        self.assertEqual(len(self.data["entries"]), 112)

    def test_every_collision_has_two_strong_owners_and_no_winner(self):
        for row in self.data["entries"]:
            self.assertTrue(row["reconstruction_owner"])
            self.assertTrue(row["upstream_owner"])
            self.assertIsNone(row["winning_owner"])
            self.assertTrue(row["duplicate_body"])
            self.assertTrue(row["actionable_link_blocker"])

    def test_no_unresolved_or_assessable_wrong_owner(self):
        self.assertEqual(self.data["summary"]["unresolved_reference_diagnostics"], 0)
        self.assertEqual(self.data["summary"]["wrong_owner_findings"], 0)
        self.assertEqual(self.data["summary"]["wrong_owner_not_assessable"], 112)

    def test_actionable_batch_count_matches_catalog(self):
        self.assertEqual(self.data["summary"]["actionable_source_unit_batches"], 37)
        self.assertEqual(self.data["summary"]["catalog_batches"], 37)

    def test_catalog_is_current(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(Path(audit.OUT_JSON).read_text(), expected)


if __name__ == "__main__":
    unittest.main()
