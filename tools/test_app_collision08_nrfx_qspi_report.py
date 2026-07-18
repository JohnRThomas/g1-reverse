#!/usr/bin/env python3
"""Regression tests for the COLLISION-08 NRFX QSPI report."""

import json
import os
import re
import sys
import unittest
from pathlib import Path

sys.path.insert(0, os.path.dirname(__file__))
import build_app_collision08_nrfx_qspi_report as report

ROOT = Path(__file__).resolve().parents[1]


class AppCollision08NrfxQspiReportTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = report.build()
        cls.rows = {row["va"]: row for row in cls.data["functions"]}

    def test_immutable_baseline_and_fail_closed_decision(self):
        self.assertTrue(self.data["baseline"]["immutable"])
        self.assertEqual(self.data["baseline"]["sha256"],
                         report.BASELINE_SHA256)
        self.assertEqual(self.data["decision"],
                         "retain_namespace_corrected_qspi_closure")
        self.assertFalse(self.data["adoption_authorized"])
        self.assertEqual(self.data["expected_collision_delta"], -3)

    def test_corrected_identity_swaps(self):
        self.assertEqual(self.rows["0x00066994"]["corrected_identity"],
                         "nrfx_qspi_init")
        self.assertFalse(self.rows["0x00066994"]
                         ["identity_correction_required"])
        self.assertEqual(self.rows["0x000669f4"]["baseline_collision_symbol"],
                         "nrfx_qspi_erase")
        self.assertEqual(self.rows["0x000669f4"]["corrected_identity"],
                         "nrfx_qspi_cinstr_xfer")
        self.assertEqual(self.rows["0x00066bc4"]["baseline_collision_symbol"],
                         "nrfx_qspi_read")
        self.assertEqual(self.rows["0x00066bc4"]["corrected_identity"],
                         "nrfx_qspi_erase")

    def test_corrected_extents_instruction_counts_and_scores(self):
        expected = {
            "0x00066994": (70, 25, 64, 26, 0.431373, 0.431373),
            "0x000669f4": (200, 72, 172, 65, 0.700730, 0.671533),
            "0x00066bc4": (158, 56, 156, 59, 0.782609, 0.765217),
        }
        for va, values in expected.items():
            row = self.rows[va]
            score = row["corrected_signature_match"]
            self.assertEqual((row["firmware_size"],
                              row["firmware_instructions"],
                              row["configured_sdk_size"],
                              row["configured_sdk_instructions"],
                              score["opcode"], score["shape"]), values)
            self.assertFalse(score["normalized_exact"])

    def test_missing_mem_busy_check_is_mandatory_closure(self):
        closure = {row["va"]: row
                   for row in self.data["required_caller_closure"]}
        busy = closure["0x00066ae0"]
        self.assertEqual(busy["symbol"], "nrfx_qspi_mem_busy_check")
        self.assertEqual(busy["status"], "missing_reconstruction")
        self.assertEqual(busy["direct_sites"],
                         [["0x00060a5c", "0x00060a7e"],
                          ["0x00060b48", "0x00060b86"]])
        self.assertEqual(busy["calls"],
                         [["0x000669f4", "0x00066af8"]])
        self.assertEqual(busy["current_status"], "reconstructed")
        self.assertEqual((busy["firmware_size"], busy["true_code_extent"]),
                         (68, 54))

    def test_direct_and_tail_caller_sites_are_explicit(self):
        self.assertEqual(self.rows["0x00066994"]["direct_caller_sites"],
                         [["0x00060a10", "0x00060a34"],
                          ["0x00060b48", "0x00060bd4"],
                          ["0x00060c00", "0x00060c34"]])
        self.assertIn(["0x0008520c", "0x00085210", "tail"],
                      self.rows["0x00066bc4"]["direct_caller_sites"])

    def test_catalog_is_deterministic(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(report.OUT_JSON.read_text(), expected)
        self.assertEqual(report.OUT_MD.read_text(),
                         report.markdown(self.data))

    def test_measured_integration_receipt(self):
        integration = self.data["integration"]
        self.assertEqual((integration["baseline_collision_count"],
                          integration["result_collision_count"],
                          integration["collision_delta"]), (87, 84, -3))
        self.assertEqual(integration["removed_collision_symbols"],
                         ["nrfx_qspi_erase", "nrfx_qspi_init",
                          "nrfx_qspi_read"])
        self.assertEqual(integration["new_collision_symbols"], [])
        self.assertEqual(integration["actionable_unresolved_before"],
                         integration["actionable_unresolved_after"])
        self.assertEqual(integration["full_link"],
                         {"compiled": 3106, "failed_compile": 0,
                          "link_rc": 0})

    def test_durable_namespaces_and_complete_generated_targets(self):
        names = json.loads((ROOT / "recon/catalogs/function_names_app.json")
                           .read_text())
        mappings = {
            "0x00066994": "g1_recon_nrfx_qspi_init",
            "0x000669f4": "g1_recon_nrfx_qspi_cinstr_xfer",
            "0x00066ae0": "g1_recon_nrfx_qspi_mem_busy_check",
            "0x00066bc4": "g1_recon_nrfx_qspi_erase",
            "0x0008520c": "g1_recon_nrfx_qspi_chip_erase",
        }
        for va, symbol in mappings.items():
            self.assertEqual(names["by_address"][va]["name"], symbol)
            self.assertEqual(names["by_name"][symbol], va)
            self.assertTrue((ROOT / "recon/symbolized/app" /
                             (symbol + ".c")).exists())

        callers = {
            "qspi_nor_acquire.c": ["g1_recon_nrfx_qspi_init"],
            "qspi_nor_pm_action.c": ["g1_recon_nrfx_qspi_init",
                                      "g1_recon_nrfx_qspi_mem_busy_check"],
            "qspi_nor_configure.c": ["g1_recon_nrfx_qspi_init"],
            "qspi_nor_send_cinstr.c": ["g1_recon_nrfx_qspi_cinstr_xfer"],
            "qspi_nor_erase.c": ["g1_recon_nrfx_qspi_erase",
                                  "g1_recon_nrfx_qspi_chip_erase"],
            "g1_recon_nrfx_qspi_chip_erase.c":
                ["g1_recon_nrfx_qspi_erase"],
            "g1_recon_nrfx_qspi_mem_busy_check.c":
                ["g1_recon_nrfx_qspi_cinstr_xfer"],
        }
        for filename, expected in callers.items():
            text = (ROOT / "recon/symbolized/app" / filename).read_text()
            for symbol in expected:
                self.assertIn(symbol + "(", text)

    def test_busy_loop_direct_target_has_a_mutation_control(self):
        path = ROOT / "recon/symbolized/app/FUN_00060a5c.c"
        text = path.read_text()

        def bounded_gate(source):
            calls = re.findall(
                r"\bg1_recon_nrfx_qspi_mem_busy_check\s*\(", source)
            if len(calls) != 2:  # declaration plus the one loop call
                raise AssertionError("busy-loop target closure changed")
            if re.search(r"\bFUN_00066ae0\s*\(", source):
                raise AssertionError("raw busy-loop target escaped namespace")

        bounded_gate(text)
        with self.assertRaises(AssertionError):
            bounded_gate(text.replace("g1_recon_nrfx_qspi_mem_busy_check",
                                      "nrfx_qspi_mem_busy_check"))


if __name__ == "__main__":
    unittest.main()
