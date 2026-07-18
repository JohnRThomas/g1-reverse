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
        self.assertEqual({"PASS": 82, "FAIL": 7},
                         reverify["summary"]["status_counts"])
        self.assertEqual({
            "pass": 82,
            "ordered_mmio_read_divergence": 6,
            "preexisting_non_mmio_verifier_gate": 1,
        }, reverify["summary"]["classification_counts"])
        for row in reverify["functions"]:
            if row["classification"] != "ordered_mmio_read_divergence":
                continue
            divergence = row["first_event_divergence"]
            self.assertTrue(divergence["original"][0] == "R" or
                            divergence["candidate"][0] == "R")

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
        self.assertEqual("FAIL", result["status"])
        self.assertEqual("ordered_mmio_read_divergence",
                         result["classification"])
        self.assertEqual(["R", 0x41016504, 4, 0],
                         result["first_event_divergence"]["original"])


if __name__ == "__main__":
    unittest.main()
