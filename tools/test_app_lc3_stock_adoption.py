#!/usr/bin/env python3
"""Fail-closed checks for the pinned configured libLC3 adoption closure."""

import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_lc3_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
SPEC = importlib.util.spec_from_file_location(
    "build_app_lc3_stock_adoption",
    ROOT / "tools/build_app_lc3_stock_adoption.py")
builder = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(builder)


class AppLc3StockAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        manifest = json.loads(MANIFEST.read_text())
        cls.manifest = {row["va"]: row
                        for row in manifest["cores"]["app"]["entries"]}
        cls.names = json.loads(NAMES.read_text())["by_address"]

    def test_receipt_rebuilds_from_configured_objects(self):
        self.assertEqual(self.receipt, builder.build())
        self.assertEqual(41, len(self.rows))
        self.assertEqual(28, self.receipt["summary"][
            "relocation_masked_full_section_exact"])
        self.assertEqual(13, self.receipt["summary"][
            "relocation_masked_executable_prefix_exact"])
        self.assertEqual(0, self.receipt["summary"]["unmatched_functions"])
        self.assertEqual(90, self.receipt["summary"][
            "call_relocations_checked"])

    def test_every_owner_is_exact_and_raw_mapped(self):
        accepted = {
            "relocation_masked_full_section_exact",
            "relocation_masked_executable_prefix_exact",
        }
        for va, row in self.rows.items():
            self.assertEqual("authorized", row["status"], va)
            self.assertIn(row["match"], accepted, va)
            self.assertTrue(row["raw_mapping_preserved"], va)
            self.assertTrue(all(check["exact"]
                                for check in row["call_target_checks"]), va)
            self.assertEqual("FUN_" + va[2:], row["raw_symbol"], va)
            self.assertTrue((ROOT / "recon/app/src" /
                             (row["raw_symbol"] + ".c")).exists(), va)

    def test_two_previous_identity_errors_are_corrected(self):
        resample = self.rows["0x0006aa98"]
        self.assertEqual("lc3_ltpf_arm_resample_8k_12k8",
                         resample["symbol"])
        self.assertEqual("arm_resample_8k_12k8",
                         resample["upstream_symbol"])
        self.assertEqual(214, resample["firmware_code_extent"])
        self.assertEqual(232, resample["upstream_section_size"])
        spectral = self.rows["0x0006bfc8"]
        self.assertEqual("lc3_sns_spectral_shaping", spectral["symbol"])
        self.assertEqual("spectral_shaping", spectral["upstream_symbol"])
        self.assertEqual(1940, spectral["firmware_code_extent"])
        self.assertEqual(1968, spectral["upstream_section_size"])

    def test_manifest_and_retained_sources_use_exact_authority(self):
        retained = RETAINED.read_text()
        for va, proof in self.rows.items():
            row = self.manifest[va]
            self.assertTrue(row["exclude_reconstruction"], va)
            self.assertEqual(proof["symbol"], row["current_symbol"], va)
            self.assertEqual(proof["upstream_symbol"],
                             row["upstream_symbol"], va)
            self.assertNotIn("/" + proof["symbol"] + ".c", retained)
            self.assertNotIn("/" + proof["raw_symbol"] + ".c", retained)

    def test_version_claim_is_precise_not_overstated(self):
        version = self.receipt["version_identity"]
        self.assertEqual(builder.PIN, version["west_manifest_pin"])
        self.assertEqual(builder.PIN, version["checkout_commit"])
        self.assertIn("does not distinguish", version["evidence_limit"])
        self.assertEqual("report_only_unchanged", self.receipt["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
