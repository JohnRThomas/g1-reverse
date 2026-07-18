#!/usr/bin/env python3
"""Fail-closed checks for the exact5 img_mgmt stock adoption."""

import json
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_img_mgmt_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"


class ImgMgmtStockAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        cls.manifest = {row["va"]: row for row in
                        json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}

    def test_receipt_rebuilds_from_immutable_exact5_evidence(self):
        subprocess.run([
            str(ROOT / ".venv/bin/python"),
            str(ROOT / "tools/build_app_img_mgmt_stock_adoption.py"),
            "--check"], cwd="/tmp", env={"PYTHONSAFEPATH": "1"}, check=True)

    def test_four_complete_live_source_closures_are_exact(self):
        self.assertEqual(29, len(self.rows))
        self.assertEqual(
            ["img_mgmt.c", "img_mgmt_state.c", "img_mgmt_util.c",
             "zephyr_img_mgmt.c"],
            self.receipt["selected_source_units"])
        self.assertTrue(all(row["instruction_exact"] and
                            row["relocation_masked_byte_exact"]
                            for row in self.rows.values()))
        self.assertTrue(all(row["owner_cfg_verify"]["status"] == "PASS"
                            for row in self.rows.values()))

    def test_only_exact_live_owners_are_excluded(self):
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(self.manifest[va]["exclude_reconstruction"], va)
            self.assertNotIn(Path(row["reconstruction_source"]).name,
                             retained)
        for va in ("0x00052038", "0x00052180", "0x000521fc"):
            self.assertTrue(self.manifest[va]["exclude_reconstruction"], va)

    def test_private_upload_false_variant_is_resolved_fail_closed(self):
        resolved = self.receipt["resolved_false_variant"]
        self.assertEqual("img_mgmt_upload", resolved["symbol"])
        self.assertEqual("0x000521fc", resolved["firmware_va"])
        upload = self.rows["0x000521fc"]
        self.assertEqual(0x240, upload["firmware_code_size"])
        self.assertTrue(upload["relocation_masked_byte_exact"])
        self.assertGreater(len(upload["relocation_offsets"]), 20)
        self.assertFalse(upload["whole_unit_closure"]["img_mgmt_c_retained"])

    def test_hidden_live_helpers_are_also_exact(self):
        hidden = {row["symbol"]: row for row in
                  self.receipt["hidden_live_sections"]}
        self.assertEqual({"img_mgmt_translate_error_code",
                          "img_mgmt_register_group"}, set(hidden))
        self.assertEqual("0x00051fc4", hidden[
            "img_mgmt_translate_error_code"]["firmware_va"])
        self.assertEqual("0x00051fd8", hidden[
            "img_mgmt_register_group"]["firmware_va"])
        self.assertTrue(all(row["relocation_masked_byte_exact"]
                            for row in hidden.values()))

    def test_partition_manager_prefix_matches_firmware_contract(self):
        topology = self.receipt["partition_topology"]
        self.assertEqual(
            {"primary0": 4, "secondary0": 2,
             "primary1": 1, "secondary1": 8},
            topology["firmware_slot_ids"])
        self.assertEqual("9", topology["configured_required_values"][
            "PM_SETTINGS_STORAGE_ID"])
        self.assertEqual("RAM_FLASH", topology["configured_required_values"][
            "PM_7_LABEL"])
        self.assertEqual(22, topology["firmware_flash_map_entries"])
        self.assertEqual("83980fe1679441be9b0e1db556a353f6118fe14f",
                         self.receipt["upstream_revisions"]["zephyr_commit"])
        self.assertEqual(
            ["v3.4.99-ncs1-1", "v3.4.99-ncs1-2", "v3.4.99-ncs1-3"],
            self.receipt["upstream_revisions"]["source_identity_plateau"])

    def test_private_state_receipt_is_not_lost(self):
        state = self.receipt["private_state"]
        self.assertEqual({"firmware_va": "0x2000a954", "size": 552},
                         state["zephyr_img_mgmt.c::ctx.0"])
        self.assertEqual("0x2000ab7c",
                         state["g_img_mgmt_state"]["firmware_va"])
        self.assertEqual("report_only_unchanged", self.receipt["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
