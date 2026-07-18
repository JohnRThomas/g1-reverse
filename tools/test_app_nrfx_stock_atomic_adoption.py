#!/usr/bin/env python3
"""Fail-closed gates for assert-enabled stock-NRFX source-unit adoption."""

import hashlib
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_nrfx_stock_atomic_adoption.json"


class AppNrfxStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        cls.manifest = json.loads(
            (ROOT / "recon/ownership/adoption_manifest.json").read_text())
        cls.entries = {row["va"]: row for row in
                       cls.manifest["cores"]["app"]["entries"]}
        cls.names = json.loads(
            (ROOT / "recon/catalogs/function_names_app.json").read_text())

    def test_pinned_commit_config_and_fail_closed_policy(self):
        self.assertEqual("9784731461018d3e983604698fbbed6af2bea801",
                         self.receipt["hal_nordic_commit"])
        self.assertTrue(self.receipt["policy"]["retain_recovered_c_as_evidence"])
        self.assertTrue(self.receipt["policy"]["gpiote_adoption_forbidden"])
        self.assertTrue(self.receipt["policy"]["sdc_remains_report_only"])
        for row in self.rows.values():
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertEqual("y", row["required_config"]["CONFIG_ASSERT"])
            self.assertEqual("2", row["required_config"]["CONFIG_ASSERT_LEVEL"])
            self.assertEqual("y", row["required_config"]["CONFIG_ASSERT_VERBOSE"])
            firmware = (ROOT / "app_update.bin").read_bytes()
            off = int(row["va"], 16) - 0xc200 + 512
            extent = row["firmware_code_size"]
            self.assertEqual(hashlib.sha256(firmware[off:off + extent]).hexdigest(),
                             row["normalized_code_sha256"])

    def test_atomic_closures_are_complete_and_excluded(self):
        expected = {
            "COLLISION-08": 19, "COLLISION-03": 5,
            "COLLISION-06": 2, "COLLISION-09": 5,
        }
        self.assertEqual(31, len(self.rows))
        for batch, count in expected.items():
            group = [row for row in self.rows.values() if row["batch"] == batch]
            self.assertEqual(count, len(group))
            vas = sorted(row["va"] for row in group)
            for row in group:
                self.assertEqual(vas, sorted(row["atomic_group"]))
                self.assertEqual(vas, sorted(
                    row["whole_unit_closure"]["exclude_only"]))
                self.assertEqual([], row["whole_unit_closure"]["new_undefined_symbols"])
                self.assertTrue(self.entries[row["va"]]["exclude_reconstruction"])

    def test_corrected_public_names_and_evidence_are_preserved(self):
        expected = {
            "0x00066994": "nrfx_qspi_init",
            "0x000669f4": "nrfx_qspi_cinstr_xfer",
            "0x00066bc4": "nrfx_qspi_erase",
            "0x00085200": "nrfx_qspi_write",
            "0x00085206": "nrfx_qspi_read",
            "0x000850dc": "nrfx_gppi_channel_endpoints_setup",
            "0x00065190": "nrfx_clock_init",
            "0x00065f1c": "nrfx_nvmc_page_erase",
        }
        retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()
        for va, name in expected.items():
            self.assertEqual(name, self.names["by_address"][va]["name"])
            self.assertEqual(va, self.names["by_name"][name])
            self.assertTrue((ROOT / "recon/named" / (name + ".c")).exists())
            self.assertTrue((ROOT / "recon/symbolized/app" / (name + ".c")).exists())
            self.assertNotIn("/" + name + ".c", retained)
            raw = "FUN_%08x.c" % int(va, 16)
            self.assertTrue((ROOT / "recon/app/src" / raw).exists())

    def test_gpiote_is_retained_and_normal_link_is_stable(self):
        gpiote = self.entries["0x00065940"]
        self.assertFalse(gpiote["exclude_reconstruction"])
        self.assertEqual("g1_recon_nrfx_gpiote_init",
                         self.names["by_address"]["0x00065940"]["name"])
        link = json.loads((ROOT /
            "recon/ownership/app_nrfx_stock_normal_link.json").read_text())
        self.assertEqual(66, link["collision_count"])
        self.assertEqual([], link["collision_delta_from_pre_adoption"])
        self.assertEqual(["FUN_0005463e", "FUN_00054688"], link["undefined"])
        self.assertEqual(hashlib.sha256(RECEIPT.read_bytes()).hexdigest(),
                         link["adoption_receipt_sha256"])


if __name__ == "__main__":
    unittest.main()
