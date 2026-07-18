#!/usr/bin/env python3
"""Fail-closed tests for CPUNET public Zephyr identity adoption."""

import json
import unittest
from pathlib import Path

import build_net_public_zephyr_identities as public


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_public_zephyr_identities.json"
OVERRIDES = ROOT / "recon/catalogs/function_name_overrides.json"


class NetPublicZephyrIdentitiesTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.by_symbol = {row["upstream_symbol"]: row
                         for row in cls.receipt["owners"]}

    def test_receipt_regenerates_from_configured_objects(self):
        self.assertEqual(self.receipt, public.build())
        self.assertTrue(self.receipt["safe"])
        self.assertEqual(6, self.receipt["summary"]["exact_function_owners"])
        self.assertEqual(7, self.receipt["summary"]["relocations_checked"])
        self.assertTrue(all(row["match"] == "relocation-masked-byte-exact"
                            for row in self.receipt["owners"]))

    def test_calls_and_absolute_state_are_resolved(self):
        timeout_targets = {
            relocation["firmware_target"]
            for symbol in ("sys_timepoint_calc", "sys_timepoint_timeout")
            for relocation in self.by_symbol[symbol]["relocations"]
        }
        self.assertEqual({"0x01038284"}, timeout_targets)
        timer_targets = {row["firmware_target"] for row in
                         self.by_symbol["z_impl_k_timer_stop"]["relocations"]}
        self.assertEqual({"0x010380d8", "0x01037960", "0x0103705c",
                          "0x0103b29c"}, timer_targets)
        self.assertEqual("0x210047f8",
                         self.by_symbol["bt_hci_driver_register"]
                         ["relocations"][0]["firmware_target"])

    def test_macro_and_inline_facades_are_not_invented_functions(self):
        facades = self.receipt["api_facades"]
        self.assertTrue(facades["z_except_reason"]["no_linkable_symbol"])
        self.assertEqual("assert_post_action@0x01039bb0",
                         facades["z_except_reason"]["selected_owner"])
        self.assertEqual("404080f311884ff0040002df7047",
                         facades["z_except_reason"]["firmware_bytes"])
        self.assertTrue(facades["k_timer_stop"]
                        ["no_independent_linkable_owner"])
        self.assertEqual("z_impl_k_timer_stop",
                         facades["k_timer_stop"]["calls"])

    def test_precise_revision_claim_does_not_overclaim_patch_tag(self):
        precision = self.receipt["version_precision"]
        self.assertEqual("v3.4.99-ncs1-1", precision["manifest_exact_tag"])
        self.assertEqual(4, len(precision["indistinguishable_patch_tags"]))
        for unit in self.receipt["source_units"]:
            matrix = unit["tag_blob_matrix"]
            self.assertEqual(matrix["v3.4.99-ncs1-1"],
                             unit["manifest_commit_blob"])
            self.assertEqual(matrix["v3.4.99-ncs1"],
                             matrix["v3.4.99-ncs1-3"])

    def test_scoped_overrides_preserve_raw_backmaps(self):
        overrides = json.loads(OVERRIDES.read_text())["net"]
        expected = self.receipt["name_overrides"]
        self.assertEqual(expected,
                         {va: overrides[va]["name"] for va in expected})
        for row in self.receipt["owners"]:
            self.assertEqual("FUN_" + row["va"][2:], row["raw_symbol"])
            self.assertTrue(row["raw_mapping_preserved"])

    def test_sdc_and_shared_generation_are_untouched(self):
        policy = self.receipt["policy"]
        self.assertEqual("report_only_unchanged", policy["sdc_policy"])
        self.assertTrue(policy["no_generated_tree_or_manifest_mutation"])
        self.assertTrue(policy["no_linker_aliases"])


if __name__ == "__main__":
    unittest.main()
