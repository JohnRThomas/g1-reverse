#!/usr/bin/env python3
"""Fail-closed checks for CPUNET busy-wait and Picolibc runtime owners."""

import json
import unittest
from pathlib import Path

import build_net_runtime_stock_adoption as stock


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_runtime_stock_atomic_adoption.json"
OVERRIDES = ROOT / "recon/catalogs/function_name_overrides.json"


class NetRuntimeStockAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.by_va = {row["va"]: row
                     for row in cls.receipt["manifest_functions"]}

    def test_receipt_regenerates_from_pinned_inputs(self):
        self.assertEqual(self.receipt, stock.build())
        self.assertTrue(self.receipt["safe"])
        self.assertEqual("authorized_atomic", self.receipt["status"])
        self.assertEqual(4, self.receipt["summary"]["owners"])
        self.assertEqual(0,
                         self.receipt["summary"]["unresolved_anomalies"])

    def test_runtime_analysis_translation_resolves_real_targets(self):
        proof = self.receipt["coordinate_proof"]
        self.assertEqual("0x800",
                         self.receipt["policy"]["runtime_minus_analysis"])
        self.assertEqual("0x0103c8a0", proof["arch_literal_runtime_value"])
        self.assertEqual("0x0103c0a0", proof["arch_literal_analysis_target"])
        self.assertEqual("0338fdd87047",
                         proof["arch_delay_machine_code_hex"])
        self.assertEqual("0x0103dd15", proof["chk_literal_runtime_value"])
        self.assertEqual("0x0103d515", proof["chk_literal_analysis_target"])
        self.assertEqual("* buffer overflow detected *\n",
                         proof["chk_literal_ascii"])

    def test_true_extents_and_relocations_are_exact(self):
        self.assertEqual((20, 16, 4), tuple(self.by_va["0x0102d25c"][key]
                         for key in ("firmware_size", "true_code_size",
                                     "literal_size")))
        self.assertEqual((24, 20, 4), tuple(self.by_va["0x0102fa84"][key]
                         for key in ("firmware_size", "true_code_size",
                                     "literal_size")))
        self.assertEqual({".rodata.delay_machine_code.0"},
                         {row["target"] for row in
                          self.by_va["0x0102d25c"]["relocations"]})
        self.assertEqual({"printk", ".rodata.__chk_fail.str1.1"},
                         {row["target"] for row in
                          self.by_va["0x0102fa84"]["relocations"]})
        self.assertEqual({"__chk_fail", "memcpy"},
                         {row["target"] for row in
                          self.by_va["0x0103b53a"]["relocations"]})
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in self.by_va.values()))

    def test_call_graph_and_noreturn_svc_are_not_functions(self):
        busy_targets = self.by_va["0x0103b0e8"]["firmware_branch_targets"]
        memcpy_targets = self.by_va["0x0103b53a"]["firmware_branch_targets"]
        self.assertEqual(["0x0102d25c"],
                         [row["target"] for row in busy_targets])
        self.assertEqual(["0x0102fa84", "0x0103b614"],
                         [row["target"] for row in memcpy_targets])
        self.assertIn("K_ERR_STACK_CHK_FAIL(2)",
                      self.receipt["coordinate_proof"]["chk_svc_semantics"])
        self.assertEqual("report_only_unchanged",
                         self.receipt["policy"]["sdc_policy"])

    def test_reversible_names_and_atomic_source_replacement(self):
        overrides = json.loads(OVERRIDES.read_text())["net"]
        expected = {
            "0x0102d25c": "arch_busy_wait",
            "0x0103b0e8": "z_impl_k_busy_wait",
            "0x0102fa84": "__chk_fail",
            "0x0103b53a": "__memcpy_chk",
        }
        self.assertEqual(expected,
                         {va: overrides[va]["name"] for va in expected})
        self.assertEqual(set(expected), set(self.receipt["atomic_group"]))
        for va, row in self.by_va.items():
            self.assertEqual("FUN_" + va[2:], row["raw_symbol"])
            self.assertTrue(row["safe_to_adopt"])
            self.assertTrue(row["exclude_reconstruction"])
            self.assertTrue(row["raw_mapping_preserved"])


if __name__ == "__main__":
    unittest.main()
