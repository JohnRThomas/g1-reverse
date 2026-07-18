#!/usr/bin/env python3
"""Integrity tests for the current CPUAPP strong-collision audit."""

import hashlib
import json
import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import build_app_collision_ownership as builder

CATALOG = os.path.join(
    ROOT, "recon/ownership/app_build_collision_ownership.json")
MARKDOWN = os.path.join(
    ROOT, "recon/ownership/app_build_collision_ownership.md")


def digest(path):
    value = hashlib.sha256()
    with open(path, "rb") as stream:
        for block in iter(lambda: stream.read(1 << 16), b""):
            value.update(block)
    return value.hexdigest()


class AppCollisionOwnershipTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        with open(CATALOG, encoding="utf-8") as stream:
            cls.catalog = json.load(stream)
        cls.functions = cls.catalog["functions"]
        cls.batches = cls.catalog["implementation_batches"]

    def test_exact_current_scope_and_actions(self):
        summary = self.catalog["summary"]
        self.assertEqual(2, self.catalog["schema"])
        self.assertEqual(112, summary["unique_symbols"])
        self.assertEqual(112, summary["diagnostic_occurrences"])
        self.assertEqual(37, summary["source_units"])
        self.assertEqual(9, summary["identity_threshold_candidates"])
        self.assertEqual(0, summary["safe_to_exclude"])
        self.assertEqual({
            "adopt_sdk_whole_public_owner": 9,
            "blocked": 8,
            "caller_cohesion": 11,
            "retain_reconstruction": 84,
        }, summary["by_action"])
        self.assertEqual(len(self.functions), len({
            row["current_symbol"] for row in self.functions}))

    def test_every_row_has_exact_retained_and_selected_owner_evidence(self):
        for row in self.functions:
            self.assertEqual(row["va"], row["retained_owner"]["va"])
            retained = os.path.join(ROOT, row["retained_owner"]["source"])
            self.assertTrue(os.path.exists(retained), row["current_symbol"])
            upstream = row["upstream"]
            self.assertTrue(upstream["archive_or_object"], row["current_symbol"])
            self.assertTrue(row["configured_inclusion"]["selected_by_real_link"])
            self.assertTrue(row["configured_inclusion"]["zephyr_config_sha256"])
            if upstream["object"]:
                self.assertTrue(os.path.exists(upstream["object"]), row["current_symbol"])
                self.assertEqual(digest(upstream["object"]),
                                 upstream["object_sha256"])
                self.assertTrue(upstream["source"]["sha256"], row["current_symbol"])

    def test_actions_are_fail_closed_and_mutually_exclusive(self):
        for row in self.functions:
            action = row["safe_action"]
            self.assertIn(action, builder.ALLOWED_ACTIONS)
            self.assertFalse(row["safe_to_exclude"], row["current_symbol"])
            if action == "adopt_sdk_whole_public_owner":
                self.assertTrue(row["identity_threshold_candidate"])
                self.assertEqual("STB_GLOBAL", row["upstream"]["binding"])
                self.assertTrue(row["upstream"]["abi"])
                self.assertFalse(row["exclusion_blockers"])
            else:
                self.assertFalse(row["identity_threshold_candidate"])
            if action == "blocked":
                blockers = set(row["exclusion_blockers"])
                self.assertTrue({"selected_owner_not_indexed",
                                 "missing_dwarf_abi"} & blockers)

    def test_batches_partition_symbols_and_source_units_exactly_once(self):
        catalog_symbols = {row["current_symbol"] for row in self.functions}
        batch_symbols = [symbol for batch in self.batches
                         for symbol in batch["symbols"]]
        self.assertEqual(catalog_symbols, set(batch_symbols))
        self.assertEqual(len(batch_symbols), len(set(batch_symbols)))
        source_units = [batch["source_unit"] for batch in self.batches]
        self.assertEqual(len(source_units), len(set(source_units)))
        for batch in self.batches:
            rows = [row for row in self.functions
                    if row["implementation_source_unit"] == batch["source_unit"]]
            self.assertEqual(batch["count"], len(rows))
            self.assertEqual(set(batch["actions"]),
                             {row["safe_action"] for row in rows})

    def test_caller_cohesion_is_limited_to_reviewed_units(self):
        actual = {row["implementation_source_unit"] for row in self.functions
                  if row["safe_action"] == "caller_cohesion"}
        self.assertEqual(builder.CALLER_COHESION_SOURCE_UNITS, actual)

    def test_markdown_is_generated_from_catalog(self):
        with open(MARKDOWN, encoding="utf-8") as stream:
            markdown = stream.read()
        self.assertEqual(builder.render_markdown(self.catalog), markdown)
        self.assertIn("| Strong duplicate symbols | 112 |", markdown)


if __name__ == "__main__":
    unittest.main()
