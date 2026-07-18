#!/usr/bin/env python3
"""Fail-closed tests for the configured Zephyr kernel/work.c adoption."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_work_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
VISIBLE = {
    "k_work_busy_get", "k_work_cancel", "k_work_init", "k_work_queue_init",
    "k_work_queue_start", "k_work_reschedule_for_queue",
    "k_work_schedule_for_queue",
}


class AppWorkStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_complete_recovered_owner_group_is_exact_and_atomic(self):
        self.assertEqual(21, len(self.rows))
        group = set(self.audit["atomic_group"])
        self.assertEqual(group, set(self.rows))
        for row in self.rows.values():
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["relocation_masked_byte_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertEqual(group, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertEqual([], row["whole_unit_closure"]["new_undefined_symbols"])

    def test_static_support_and_private_state_converge(self):
        support = {row["symbol"] for row in self.audit["hidden_static_closure"]}
        self.assertEqual({"work_queue_main", "work_timeout", "flag_test_and_clear",
                          "k_work_submit_to_queue"}, support)
        for row in self.audit["hidden_static_closure"]:
            self.assertTrue(row["instruction_exact"])
        state = self.audit["private_state_convergence"]
        self.assertEqual("work.c::pending_cancels", state["0x2000b478"])
        self.assertEqual("work.c::lock", state["0x2000b480"])
        self.assertTrue(state["split_state_prevented_by_complete_recovered_owner_exclusion"])

    def test_manifest_and_retained_sources_exclude_all_recovered_owners(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        for va in self.rows:
            self.assertTrue(entries[va]["exclude_reconstruction"], va)
        retained = RETAINED.read_text()
        for row in self.rows.values():
            source = Path(row["reconstruction_source"]).stem
            self.assertNotIn("/" + source + ".c", retained)

    def test_normal_link_delta_and_unresolved_pair_are_exact(self):
        delta = self.audit["link_delta"]
        self.assertEqual((10, 3), (delta["before"], delta["after"]))
        self.assertEqual(VISIBLE, set(delta["removed"]))
        self.assertEqual([], delta["added"])
        self.assertEqual({"FUN_0005463e", "FUN_00054688"}, set(delta["unresolved"]))
        self.assertEqual({"bt_id_add", "sys_heap_alloc", "sys_heap_init"},
                         set(self.audit["normal_link_receipts"]["after"]["collisions"]))

    def test_public_abis_and_cfg_callers_are_recorded(self):
        self.assertEqual(VISIBLE, set(self.audit["corrected_public_abis"]))
        self.assertEqual("PASS", self.audit["critical_cfg_callers"]["status"])
        self.assertEqual(10, self.audit["critical_cfg_callers"]["count"])
        self.assertEqual("report_only_unchanged", self.audit["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
