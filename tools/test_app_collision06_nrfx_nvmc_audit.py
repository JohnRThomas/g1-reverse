#!/usr/bin/env python3
"""Regression tests for the COLLISION-06 NRFX NVMC audit."""

import json
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))
import build_app_collision06_nrfx_nvmc_audit as audit


class AppCollision06NrfxNvmcAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_batch_fails_closed_without_overlay(self):
        self.assertEqual(self.data["decision"],
                         "retain_and_namespace_both_reconstructions")
        self.assertFalse(self.data["adoption_authorized"])
        self.assertFalse(self.data["overlay_changed"])
        self.assertEqual(self.data["namespace_status"], "implemented")
        self.assertEqual(self.data["collision_delta"], -2)
        self.assertEqual(self.data["new_undefined_symbols"], [])

    def test_abis_match_but_configured_bodies_do_not(self):
        self.assertEqual(self.rows["nrfx_nvmc_page_erase"]["abi"]["params"],
                         ["uint32_t"])
        self.assertEqual(self.rows["nrfx_nvmc_word_write"]["abi"]["params"],
                         ["uint32_t", "uint32_t"])
        for row in self.rows.values():
            self.assertFalse(row["signature_match"]["normalized_exact"])
            self.assertNotEqual(row["firmware_size"],
                                row["configured_sdk_size"])

    def test_active_firmware_assertions_are_decisive(self):
        self.assertEqual(self.data["configured_assert_policy"],
                         "NRFX_ASSERT(expression) expands empty")
        self.assertEqual(self.rows["nrfx_nvmc_page_erase"]
                         ["firmware_assertions"],
                         ["is_valid_address(addr, 0)"])
        self.assertEqual(len(self.rows["nrfx_nvmc_word_write"]
                             ["firmware_assertions"]), 2)
        self.assertTrue(all(not row["configured_sdk_assertions"]
                            for row in self.rows.values()))

    def test_retained_cfg_passes_and_sdk_semantics_fail(self):
        for row in self.rows.values():
            self.assertEqual(row["cfg_verify"]["retained"]["status"], "PASS")
            negative = row["cfg_verify"][
                "configured_sdk_semantics_negative_control"]
            self.assertEqual(negative["status"], "FAIL")
            self.assertGreater(negative["mismatches"], 0)
            self.assertEqual(negative["cases"], 3)

    def test_mmio_and_configured_helper_relocations(self):
        for row in self.rows.values():
            self.assertEqual(row["mmio_accesses"],
                             ["0x50039584 CONFIGNS", "0x50039504 CONFIG",
                              "0x50039400 READY"])
        self.assertEqual(self.rows["nrfx_nvmc_page_erase"]
                         ["configured_sdk_relocations"],
                         ["nvmc_readonly_mode_set"])
        self.assertEqual(self.rows["nrfx_nvmc_word_write"]
                         ["configured_sdk_relocations"],
                         ["nvmc_word_write", "nvmc_readonly_mode_set"])

    def test_both_callers_are_recovered_and_cfg_verified(self):
        page = self.rows["nrfx_nvmc_page_erase"]["caller_closure"]
        word = self.rows["nrfx_nvmc_word_write"]["caller_closure"]
        self.assertEqual(page, [{"va": "0x6125c", "branch_site": "0x000612d8",
                                 "reconstruction": "recovered", "cfg_verify": "PASS",
                                 "cases": 4}])
        self.assertEqual(word, [{"va": "0x61310", "branch_site": "0x000613a8",
                                 "reconstruction": "recovered", "cfg_verify": "PASS",
                                 "cases": 4}])

    def test_catalog_is_deterministic(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(audit.OUT_JSON.read_text(), expected)
        self.assertEqual(audit.OUT_MD.read_text(), audit.markdown(self.data))


if __name__ == "__main__":
    unittest.main()
