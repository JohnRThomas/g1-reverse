#!/usr/bin/env python3
"""Integrity tests for the durable CPUAPP SDK-residue ownership catalog."""

import json
import os
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CATALOG = os.path.join(ROOT, "recon/catalogs/app_sdk_residue_ownership.json")
RESIDUE = os.path.join(ROOT, "recon/analysis/app_link_residue.json")


class OwnershipCatalogTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        with open(CATALOG, encoding="utf-8") as stream:
            cls.catalog = json.load(stream)
        with open(RESIDUE, encoding="utf-8") as stream:
            cls.residue = json.load(stream)
        cls.entries = cls.catalog["entries"]

    def test_exact_scope_and_unique_symbols(self):
        expected = {row["symbol"] for row in self.residue["entries"]
                    if row["category"] == "sdk_or_config_symbol"}
        actual = [row["symbol"] for row in self.entries]
        self.assertEqual(len(expected), len(actual))
        self.assertEqual(len(actual), len(set(actual)))
        self.assertEqual(expected, set(actual))

    def test_every_symbol_has_owner_and_action(self):
        for row in self.entries:
            self.assertTrue(row["semantic_owner"], row["symbol"])
            self.assertTrue(row["owner_kind"], row["symbol"])
            self.assertTrue(row["action"], row["symbol"])
            if row["action"] != "manual_owner_review":
                self.assertTrue(row["source_or_archive"], row["symbol"])
            self.assertTrue(row["owning_config"], row["symbol"])

    def test_no_local_symbol_is_safe_public_link(self):
        for row in self.entries:
            if row["owner_kind"] in {
                    "archive_local", "source_local", "header_inline"}:
                self.assertFalse(row["safe_automatic_link_owner"], row["symbol"])

    def test_known_runtime_and_static_owners(self):
        by_symbol = {row["symbol"]: row for row in self.entries}
        self.assertEqual("free_list_remove",
                         by_symbol["FUN_0007def6"]["semantic_owner"])
        self.assertEqual("archive_local",
                         by_symbol["FUN_00080fd2"]["owner_kind"])
        self.assertEqual("reconcile_inline_at_callsite",
                         by_symbol["k_uptime_get_7"]["action"])
        self.assertEqual("manual_owner_review",
                         by_symbol["net_buf_tailroom"]["action"])

    def test_report_only_policy(self):
        self.assertTrue(self.catalog["policy"]["report_only"])
        self.assertTrue(self.catalog["policy"]["no_build_or_reconstruction_edits"])

    def test_safe_candidates_are_exactly_public_exports(self):
        candidates = [row for row in self.entries
                      if row["safe_automatic_link_owner"]]
        self.assertEqual(0, len(candidates))
        self.assertTrue(all(row["owner_kind"] == "archive_public"
                            for row in candidates))

    def test_current_residue_has_no_automatic_public_link_owner(self):
        self.assertTrue(all(not row["safe_automatic_link_owner"]
                            for row in self.entries))


if __name__ == "__main__":
    unittest.main()
