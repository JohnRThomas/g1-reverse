#!/usr/bin/env python3
"""Fail-closed gates for the exact-root CPUAPP stock collision snapshot."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_root_stock_collision_ownership.json"

CANDIDATE = {
    "lseek", "stream_flash_init", "mgmt_find_handler",
    "smp_process_request_packet", "smp_add_cmd_err",
    "img_mgmt_erase_slot", "img_mgmt_set_next_boot_slot",
    "img_mgmt_state_write", "img_mgmt_ver_str", "img_mgmt_read_info",
    "img_mgmt_get_next_boot_slot", "smp_transport_init",
    "smp_rx_remove_invalid", "smp_free_buf", "boot_set_next",
    "zcbor_process_backup", "zcbor_simple_put",
}
FULL_EXACT = CANDIDATE
# Historical retain-all collision snapshot predates the corrected durable name;
# the receipt intentionally preserves the linker symbol seen in that build.
RETAIN = {"pthread_attr_getstack"}


class AppRootStockCollisionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = json.loads(RECEIPT.read_text())
        cls.rows = {row["current_symbol"]: row
                    for row in cls.data["functions"]}

    def test_snapshot_is_complete_and_partitioned(self):
        self.assertEqual(CANDIDATE | RETAIN, set(self.rows))
        self.assertEqual(18, self.data["summary"]["collisions"])
        self.assertEqual(17, self.data["summary"][
            "identity_threshold_candidates"])
        self.assertEqual(13, self.data["summary"]["source_units"])

    def test_exact_candidates_are_not_automatically_authorized(self):
        for symbol in CANDIDATE:
            row = self.rows[symbol]
            self.assertTrue(row["identity_threshold_candidate"])
            self.assertFalse(row["safe_to_exclude"])
            self.assertEqual("adopt_sdk_whole_public_owner",
                             row["safe_action"])
        for symbol in FULL_EXACT:
            self.assertTrue(self.rows[symbol]["signature_match"][
                "normalized_exact"])

    def test_nonexact_owners_remain_retained(self):
        for symbol in RETAIN:
            row = self.rows[symbol]
            self.assertFalse(row["signature_match"]["normalized_exact"])
            self.assertFalse(row["safe_to_exclude"])
            self.assertEqual("retain_reconstruction", row["safe_action"])

    def test_real_link_and_exact_configuration_are_recorded(self):
        for row in self.rows.values():
            inclusion = row["configured_inclusion"]
            self.assertTrue(inclusion["selected_by_real_link"])
            self.assertTrue(inclusion["indexed_object_present"])
            self.assertEqual(
                "a33a336176935d1d2e31ba2c79f558a0952f4c8cdffb93fccc654bd02f126efe",
                inclusion["zephyr_config_sha256"])
            self.assertTrue(row["upstream"]["object_sha256"])
            self.assertTrue(row["upstream"]["source"]["sha256"])

    def test_policy_is_report_only_and_sdc_unchanged(self):
        self.assertTrue(self.data["policy"][
            "no_implementation_mutations_authorized"])
        report = RECEIPT.with_suffix(".md").read_text()
        self.assertIn("report-only audit", report)
        self.assertEqual(0, self.data["summary"]["safe_to_exclude"])


if __name__ == "__main__":
    unittest.main()
