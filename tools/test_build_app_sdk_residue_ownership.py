#!/usr/bin/env python3
"""Integrity tests for the durable CPUAPP SDK-residue ownership catalog."""

import hashlib
import json
import os
import re
import sys
import unittest
from pathlib import Path


sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__))), "tools"))
import build_app_sdk_residue_ownership as builder  # noqa: E402


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
        expected = {
            "FUN_0007def6", "FUN_00080fd2",
            "__nrfy_internal_spim_event_handle", "buffer_write",
            "compare_int_lock", "event_clear", "flag_test_and_clear",
            "free_list_remove_bidx", "k_uptime_get_0", "k_uptime_get_4",
            "k_uptime_get_7", "merge_chunks", "net_buf_tailroom",
        }
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
        self.assertEqual("net_buf_simple_tailroom",
                         by_symbol["net_buf_tailroom"]["semantic_owner"])
        self.assertEqual("archive_public",
                         by_symbol["net_buf_tailroom"]["owner_kind"])
        self.assertEqual("exact_public_owner",
                         by_symbol["net_buf_tailroom"]["resolution"]["strategy"])

    def test_report_only_policy(self):
        self.assertTrue(self.catalog["policy"]["report_only"])
        self.assertTrue(self.catalog["policy"]["no_build_or_reconstruction_edits"])
        self.assertTrue(self.catalog["policy"]["weak_aliases_forbidden"])
        self.assertTrue(self.catalog["policy"]["duplicate_bodies_forbidden"])
        self.assertEqual(builder.ORIGIN_RESIDUE, self.catalog["scope_origin"])

    def test_safe_candidates_are_exactly_public_exports(self):
        candidates = [row for row in self.entries
                      if row["safe_automatic_link_owner"]]
        self.assertEqual(["net_buf_tailroom"],
                         [row["symbol"] for row in candidates])
        self.assertTrue(all(row["owner_kind"] == "archive_public"
                            for row in candidates))

    def test_every_resolution_is_fail_closed_and_has_source_receipt(self):
        self.assertEqual(13, self.catalog["summary"]["resolved"])
        self.assertEqual(0, self.catalog["summary"]["manual"])
        for row in self.entries:
            self.assertEqual("resolved", row["resolution"]["status"])
            self.assertFalse(row["resolution"]["weak_alias_allowed"])
            self.assertFalse(row["resolution"]["duplicate_body_allowed"])
            receipt = row["source_receipt"]
            self.assertIsNotNone(receipt, row["symbol"])
            source = os.path.join(builder.NCS, receipt["path"])
            with open(source, "rb") as stream:
                digest = hashlib.sha256(stream.read()).hexdigest()
            self.assertEqual(digest, receipt["sha256"], row["symbol"])
            self.assertGreater(receipt["definition_line"], 0)

    def test_no_duplicate_reconstruction_body_or_weak_alias(self):
        text = "\n".join(
            path.read_text(encoding="utf-8")
            for path in Path(ROOT, "recon/app/src").glob("*.c"))
        for row in self.entries:
            owner = row["semantic_owner"]
            definition = re.compile(
                r"^(?!static\s)[A-Za-z_][^\n;{}]*\b%s\s*\([^;{}]*\)\s*\{" %
                re.escape(owner), re.M)
            self.assertIsNone(definition.search(text), row["symbol"])
        for filename in os.listdir(os.path.join(ROOT, "recon/symbols")):
            if not filename.endswith(".ld"):
                continue
            path = os.path.join(ROOT, "recon/symbols", filename)
            ld_text = Path(path).read_text(encoding="utf-8")
            self.assertNotIn("net_buf_tailroom", ld_text, filename)

    def test_current_residue_is_fail_closed_subset_of_original_tail(self):
        current = {row["symbol"] for row in self.residue["entries"]
                   if row["category"] == "sdk_or_config_symbol"}
        original = {row["symbol"] for row in self.entries}
        self.assertLessEqual(current, original)
        self.assertNotIn("net_buf_tailroom", current)
        self.assertNotIn("__nrfy_internal_spim_event_handle", current)
        self.assertNotIn("flag_test_and_clear", current)
        self.assertEqual(len(original) - len(current),
                         self.catalog["summary"]["integrated"])
        self.assertEqual(len(current),
                         self.catalog["summary"]["pending_in_current_residue"])
        for row in self.entries:
            expected = ("pending_caller_cohesion" if row["symbol"] in current
                        else "integrated_no_undefined_residue")
            self.assertEqual(expected, row["integration_status"])


if __name__ == "__main__":
    unittest.main()
