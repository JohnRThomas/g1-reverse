#!/usr/bin/env python3
"""Fail-closed gates for the CPUNET scheduler/queue/heap stock receipt."""

import json
import unittest
from pathlib import Path

import build_net_kernel_private_stock_adoption as stock


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_kernel_private_stock_adoption.json"
CONFIG = ROOT / "recon/application/net/prj.conf"


class NetKernelPrivateStockAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_regenerates_complete_exact_closure(self):
        rebuilt = stock.build()
        self.assertEqual(self.receipt, rebuilt)
        self.assertEqual(71, len(rebuilt["section_matches"]))
        self.assertEqual({
            "sched": 37, "queue": 5, "kheap": 4,
            "mempool": 6, "heap": 19,
        }, {row["unit"]: row["live_section_count"]
            for row in rebuilt["source_units"]})
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in rebuilt["section_matches"]))

    def test_every_thumb_relocation_has_an_exact_firmware_target(self):
        checked = {(row["caller_va"], row["offset"]): row
                   for row in self.receipt["call_target_checks"]}
        expected = 0
        for section in self.receipt["section_matches"]:
            for relocation in section["relocations"]:
                if relocation["type"] in (10, 30):
                    expected += 1
                    row = checked[(section["va"], relocation["offset"])]
                    self.assertEqual(relocation["target"],
                                     row["target_symbol"])
        self.assertEqual(expected, len(checked))
        self.assertEqual(344, expected)

    def test_scheduler_private_state_and_heap_layout_are_address_exact(self):
        states = {row["target"]: (row["runtime_address"], row["size"])
                  for row in self.receipt["private_state_sections"]}
        self.assertEqual({
            ".bss.pending_current": ("0x21004b5c", 4),
            ".bss.slice_expired": ("0x21006462", 1),
            ".bss.slice_timeouts": ("0x210044d8", 24),
            ".bss.slice_max_prio": ("0x21004b60", 4),
            ".bss.slice_ticks": ("0x21004b64", 4),
            "sched_spinlock": ("0x21004b68", 4),
        }, states)
        structural = {(row["unit"], row["target"]):
                      row["runtime_addresses"]
                      for row in self.receipt["structural_absolute_targets"]}
        self.assertEqual(["0x210008b4"],
                         structural[("mempool", "_system_heap")])
        self.assertEqual(["0x210008cc"],
                         structural[("kheap", "_k_heap_list_end")])

    def test_auto_heap_is_positive_and_small_only_is_negative_evidence(self):
        required = self.receipt["upstream"]["required_config"]
        self.assertEqual("y", required["CONFIG_SYS_HEAP_AUTO"])
        self.assertEqual("n", required["CONFIG_SYS_HEAP_SMALL_ONLY"])
        rejected = self.receipt["wrong_config_rejection"]
        self.assertEqual(19, rejected["selected_heap_sections"])
        self.assertEqual([], rejected["exact_sections"])
        config = CONFIG.read_text()
        self.assertIn("CONFIG_SYS_HEAP_AUTO=y", config)

    def test_version_precision_does_not_overclaim_patch_discrimination(self):
        history = self.receipt["version_precision"]["source_blob_ids_by_tag"]
        patch_tags = ["v3.4.99-ncs1-1", "v3.4.99-ncs1-2",
                      "v3.4.99-ncs1-3"]
        for unit in stock.UNITS:
            self.assertEqual(1, len({history[tag][unit]
                                     for tag in patch_tags}), unit)
        self.assertNotEqual(history["v3.3.99-ncs1-3"]["sched"],
                            history["v3.4.99-ncs1-1"]["sched"])
        self.assertNotEqual(history["v3.5.99-ncs1-1"]["sched"],
                            history["v3.4.99-ncs1-1"]["sched"])
        self.assertIn("manifest pin", self.receipt["version_precision"]
                      ["conclusion"])

    def test_raw_backmaps_and_sdc_policy_are_preserved(self):
        for row in self.receipt["manifest_functions"]:
            self.assertEqual("FUN_" + row["va"][2:], row["raw_symbol"])
            if row["reconstruction_present"]:
                self.assertTrue((ROOT / row["reconstruction_source"]).is_file())
        self.assertEqual("report_only_unchanged",
                         self.receipt["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
