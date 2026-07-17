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
        self.assertEqual(173, len(actual))
        self.assertEqual(len(actual), len(set(actual)))
        self.assertEqual(expected, set(actual))

    def test_every_symbol_has_owner_and_action(self):
        for row in self.entries:
            self.assertTrue(row["semantic_owner"], row["symbol"])
            self.assertTrue(row["owner_kind"], row["symbol"])
            self.assertTrue(row["action"], row["symbol"])
            self.assertTrue(row["source_or_archive"], row["symbol"])
            self.assertTrue(row["owning_config"], row["symbol"])

    def test_no_local_symbol_is_safe_public_link(self):
        for row in self.entries:
            if row["owner_kind"] in {
                    "archive_local", "source_local", "header_inline"}:
                self.assertFalse(row["safe_automatic_link_owner"], row["symbol"])

    def test_known_runtime_and_static_owners(self):
        by_symbol = {row["symbol"]: row for row in self.entries}
        self.assertEqual("__fixdfsi", by_symbol["FUN_0000de58"]["semantic_owner"])
        self.assertEqual("archive_public", by_symbol["FUN_0000de58"]["owner_kind"])
        self.assertEqual("archive_local", by_symbol["FUN_0004c4e4"]["owner_kind"])
        self.assertEqual("reconcile_inline_at_callsite",
                         by_symbol["atomic_and_0"]["action"])
        self.assertEqual("reclassify_application_owner",
                         by_symbol["adc_nfc_init"]["action"])

    def test_report_only_policy(self):
        self.assertTrue(self.catalog["policy"]["report_only"])
        self.assertTrue(self.catalog["policy"]["no_build_or_reconstruction_edits"])

    def test_safe_candidates_are_exactly_public_exports(self):
        candidates = [row for row in self.entries
                      if row["safe_automatic_link_owner"]]
        self.assertEqual(28, len(candidates))
        self.assertTrue(all(row["owner_kind"] == "archive_public"
                            for row in candidates))

    def test_cc312_same_name_collision_is_not_linkable(self):
        row = next(row for row in self.entries
                   if row["symbol"] == "nrf_cc3xx_platform_abort")
        self.assertFalse(row["safe_automatic_link_owner"])
        self.assertEqual("0x00050af8", row["collision"]["requested_firmware_identity"])
        self.assertEqual("0x00079590", row["collision"]["already_adopted_cc312_identity"])


if __name__ == "__main__":
    unittest.main()
