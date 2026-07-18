#!/usr/bin/env python3
"""Regression tests for the CPUAPP full-link UNKNOWN audit."""

import json
import os
import sys
import unittest
from pathlib import Path

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_app_full_link_unknown_audit as audit


class FullLinkUnknownAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()
        cls.rows = {row["symbol"]: row for row in cls.data["entries"]}

    def test_exact_partition(self):
        self.assertEqual(self.data["summary"]["symbols"], 59)
        self.assertEqual(self.data["summary"]["by_category"], {
            "duplicate_owner_byproduct": 30,
            "genuine_sdk_library_external": 28, "ghidra_compiler_pseudo": 1})
        self.assertEqual(self.data["summary"]["actionable_gaps"], 0)

    def test_blocked_interiors_are_preserved(self):
        self.assertEqual({s for s, r in self.rows.items()
                          if r["category"] == "blocked_interior"}, audit.BLOCKED)

    def test_duplicate_byproducts_have_no_retained_caller(self):
        for row in self.rows.values():
            if row["category"] == "duplicate_owner_byproduct":
                self.assertEqual(row["retained_callers"], [])

    def test_externals_have_retained_callers_and_owner(self):
        for row in self.rows.values():
            if row["category"] == "genuine_sdk_library_external":
                self.assertTrue(row["retained_callers"])
                self.assertTrue(row["evidence"])

    def test_pseudo_is_not_aliased_or_materialized(self):
        row = self.rows["thunk_FUN_00086c78"]
        self.assertEqual(row["category"], "ghidra_compiler_pseudo")
        self.assertEqual(row["retained_callers"], [])
        self.assertFalse(os.path.exists(audit.BASE +
                         "/recon/symbolized/app/thunk_FUN_00086c78.c"))

    def test_catalog_is_current(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(Path(audit.DEFAULT_JSON).read_text(), expected)


if __name__ == "__main__":
    unittest.main()
