#!/usr/bin/env python3
"""Fail-closed tests for the final CPUAPP zero-collision milestone."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_final_zero_collision.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"


class AppFinalZeroCollisionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.manifest = {row["va"]: row for row in
                        json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}

    def test_real_normal_link_reaches_zero_without_surface_drift(self):
        delta = self.audit["link_delta"]
        self.assertEqual((3, 0), (delta["before"], delta["after"]))
        self.assertEqual({"sys_heap_alloc", "sys_heap_init", "bt_id_add"},
                         set(delta["removed"]))
        self.assertEqual([], delta["added"])
        self.assertEqual({"FUN_0005463e", "FUN_00054688"}, set(delta["unresolved"]))
        self.assertEqual([], self.audit["normal_link_receipts"]["after"]["collisions"])

    def test_heap_has_complete_19_section_exact_closure(self):
        rows = self.audit["heap_exact_section_closure"]
        self.assertEqual(19, len(rows))
        self.assertEqual(19, len({row["va"] for row in rows}))
        for row in rows:
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["relocation_masked_byte_exact"])
            self.assertEqual(row["firmware_code_size"], row["upstream_code_size"])

    def test_bluetooth_id_mapping_and_caller_are_correct(self):
        rows = {row["va"]: row for row in self.audit["bluetooth_id_exact_section_closure"]}
        self.assertEqual("bt_id_add.part.0", rows["0x00054ea8"]["symbol"])
        self.assertEqual("bt_id_add", rows["0x0005505c"]["symbol"])
        self.assertEqual("hci_id_add", rows["0x00080fd2"]["symbol"])
        self.assertTrue(all(row["instruction_exact"] for row in rows.values()))
        self.assertEqual({"caller": "FUN_0005de70", "from": "FUN_0005505c",
                          "to": "bt_id_add", "cfg_verify": "PASS"},
                         self.audit["caller_retarget"])
        stock = json.loads((ROOT / "recon/ownership/app_bluetooth_stock_atomic_adoption.json").read_text())
        closure = stock["id_source_closure"]
        self.assertTrue(all(row["required_config"]["CONFIG_TRACING"] == "n"
                            for row in stock["authorizations"]))
        app_config = (ROOT / "recon/application/app/prj.conf").read_text()
        self.assertIn("# CONFIG_TRACING is not set", app_config)
        self.assertNotIn("CONFIG_TRACING=y", app_config)
        self.assertEqual("781199a9c752f84e8ce938bff81e1824114badc1b7f5e301c330f1870710163b",
                         closure["source_sha256"])
        self.assertEqual("64ac028ed9238ed6afc5fe027b6f0f9e2f6a2279d6ef6c86807c83a853df8311",
                         closure["configured_object_sha256"])
        self.assertEqual(0, closure["final_normal_link_collisions"])

    def test_manifest_excludes_only_adopted_groups_and_retains_k_heap(self):
        for va in ("0x0004b3c8", "0x0007e12a", "0x00054ea8", "0x0005505c"):
            self.assertTrue(self.manifest[va]["exclude_reconstruction"], va)
        kheap = self.manifest["0x000863aa"]
        self.assertFalse(kheap["exclude_reconstruction"])
        self.assertEqual("g1_recon_k_heap_init", kheap["current_symbol"])
        self.assertEqual("k_heap_init", kheap["upstream_symbol"])
        retained = RETAINED.read_text()
        self.assertIn("/g1_recon_k_heap_init.c", retained)
        for name in ("/sys_heap_init.c", "/sys_heap_alloc.c",
                     "/bt_id_add_part_0.c", "/bt_id_add.c"):
            self.assertNotIn(name, retained)

    def test_recovered_c_and_sdc_policy_remain_intact(self):
        for path in ("recon/app/src/FUN_0004b3c8.c", "recon/app/src/sys_heap_alloc.c",
                     "recon/app/src/FUN_00054ea8.c", "recon/app/src/FUN_0005505c.c"):
            self.assertTrue((ROOT / path).is_file(), path)
        self.assertEqual("report_only_unchanged", self.audit["sdc_policy"])

    def test_normal_non_retain_all_link_is_clean_and_blockers_are_separate(self):
        link = self.audit["normal_non_retain_all_final_link"]
        self.assertTrue(link["link_succeeded"])
        self.assertEqual([], link["collisions"])
        self.assertEqual([], link["undefined"])
        kinds = {row["kind"] for row in link["remaining_non_collision_blockers"]}
        self.assertEqual({"cpuapp_root_and_init_graph", "embedded_svc_continuations",
                          "cpunet_project_owner", "firmware_section_comparison"}, kinds)


if __name__ == "__main__":
    unittest.main()
