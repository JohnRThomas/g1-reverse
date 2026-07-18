#!/usr/bin/env python3
"""Fail-closed gates for the exact5 root-stock atomic adoption."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_root_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
EXPECTED = {
    "0x000641e4": "boot_set_next",
    "0x00085c86": "zcbor_process_backup",
    "0x00086360": "zcbor_simple_put",
}


class RootStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        manifest = json.loads(MANIFEST.read_text())
        cls.manifest = {row["va"]: row
                        for row in manifest["cores"]["app"]["entries"]}

    def test_exact5_authority_is_complete(self):
        self.assertEqual("authorized_atomic", self.receipt["status"])
        self.assertEqual(EXPECTED, {va: row["symbol"]
                                    for va, row in self.rows.items()})
        for va, row in self.rows.items():
            self.assertTrue(row["instruction_exact"], va)
            self.assertTrue(row["configuration_variant_exact"], va)
            self.assertEqual([va], row["atomic_group"])
            self.assertEqual([va], row["whole_unit_closure"]["exclude_only"])
            self.assertEqual([], row["whole_unit_closure"]["new_undefined_symbols"])
            self.assertEqual(row["raw_symbol"],
                             row["whole_unit_closure"]["raw_alias_preserved"])

    def test_configuration_variants_are_explicit(self):
        common = self.rows["0x00085c86"]["required_config"]
        self.assertEqual("y", common["CONFIG_ZCBOR_STOP_ON_ERROR"])
        boot = self.rows["0x000641e4"]["required_config"]
        self.assertEqual("2", boot["CONFIG_UPDATEABLE_IMAGE_NUMBER"])
        for row in self.rows.values():
            self.assertEqual("n", row["required_config"][
                "CONFIG_THREAD_LOCAL_STORAGE"])
            self.assertEqual("y", row["required_config"][
                "CONFIG_THREAD_CUSTOM_DATA"])
            self.assertEqual("16384", row["required_config"][
                "CONFIG_MAIN_STACK_SIZE"])

    def test_source_unit_gc_boundary_is_recorded(self):
        for va, row in self.rows.items():
            closure = row["whole_unit_closure"]
            self.assertTrue(closure["archive_member_already_selected"], va)
            self.assertTrue(closure["retain_all_probe_may_keep_absent_sections"], va)
            self.assertTrue(closure["firmware_absent_sections_require_normal_gc"], va)
            self.assertTrue(closure["exact_companion_sections"], va)

    def test_manifest_excludes_only_selected_public_owners(self):
        for va, symbol in EXPECTED.items():
            row = self.manifest[va]
            self.assertEqual("FUN_" + va[2:], row["raw_symbol"])
            self.assertEqual(symbol, row["current_symbol"])
            self.assertEqual(symbol, row["upstream_symbol"])
            self.assertTrue(row["exclude_reconstruction"])
        text = RETAINED.read_text()
        for raw in ("FUN_000641e4.c", "FUN_00085c86.c", "FUN_00086360.c"):
            self.assertNotIn("/" + raw, text)

    def test_sdc_policy_is_unchanged(self):
        self.assertTrue(self.receipt["policy"]["sdc_remains_report_only"])


if __name__ == "__main__":
    unittest.main()
