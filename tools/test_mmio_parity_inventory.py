#!/usr/bin/env python3
"""Fail-closed checks for the APP/NET MMIO parity impact inventory."""

import hashlib
import json
import unittest
from pathlib import Path

import build_mmio_parity_inventory as inventory


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/catalogs/mmio_parity_coverage_inventory.json"


class MmioParityInventoryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.current = json.loads(RECEIPT.read_text())

    def test_static_inventory_regenerates(self):
        static = inventory.build_static()
        recorded = dict(self.current)
        recorded.pop("targeted_reverify")
        self.assertEqual(static, recorded)
        self.assertEqual({
            "mmio_reference_functions": 212,
            "ordered_read_trace_functions": 104,
            "canonical_read_trace_targets": 89,
        }, {key: static["summary"][key] for key in (
            "mmio_reference_functions", "ordered_read_trace_functions",
            "canonical_read_trace_targets")})

    def test_every_target_source_hash_is_exact(self):
        rows = self.current["targeted_reverify"]["functions"]
        self.assertEqual(89, len(rows))
        for row in rows:
            source = ROOT / row["source"]
            self.assertEqual(row["source_sha256"],
                             hashlib.sha256(source.read_bytes()).hexdigest())

    def test_reverify_results_are_complete_and_failures_classified(self):
        reverify = self.current["targeted_reverify"]
        self.assertEqual({"PASS": 89},
                         reverify["summary"]["status_counts"])
        self.assertEqual({"pass": 89},
                         reverify["summary"]["classification_counts"])

    def test_all_six_mmio_repairs_and_assertion_fixture_now_pass(self):
        rows = {(row["core"], row["va"]): row for row in
                self.current["targeted_reverify"]["functions"]}
        repaired = {
            ("app", "0x00050558"), ("app", "0x00066050"),
            ("net", "0x010313ec"), ("net", "0x01033888"),
            ("net", "0x01033b18"), ("net", "0x0103499c"),
        }
        for key in repaired:
            self.assertEqual("PASS", rows[key]["status"], key)
            self.assertEqual("pass", rows[key]["classification"], key)
        assertion = rows[("net", "0x01008d00")]
        self.assertEqual("PASS", assertion["status"])
        self.assertEqual(6, assertion["cover_cases"])
        self.assertEqual(6, assertion["checked"])

    def test_rtc_counter_false_proof_is_in_static_and_dynamic_evidence(self):
        static = next(row for row in self.current["functions"]
                      if row["core"] == "net" and
                      row["analysis_address"] == "0x010313ec")
        reads = static["original_mmio_reads"]
        self.assertEqual(1, len(reads))
        self.assertTrue(all(access["address"] == "0x41016504"
                            for access in reads))
        self.assertEqual(2, len(reads[0]["instruction_addresses"]))
        result = next(row for row in
                      self.current["targeted_reverify"]["functions"]
                      if row["core"] == "net" and
                      row["va"] == "0x010313ec")
        self.assertEqual("PASS", result["status"])
        self.assertEqual("pass", result["classification"])


if __name__ == "__main__":
    unittest.main()
