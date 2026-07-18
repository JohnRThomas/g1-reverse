#!/usr/bin/env python3
"""Fail-closed gates for the configured CPUNET Zephyr source closures."""

import json
import unittest
from pathlib import Path

import build_net_zephyr_stock_adoption as stock
import build_adoption_manifest as adoption


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/net_zephyr_stock_atomic_adoption.json"
BASELINE = ROOT / "recon/ownership/adoption_manifest_baseline.json"
OVERRIDES = ROOT / "recon/catalogs/function_name_overrides.json"


class NetZephyrStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        # Exercise the integration hook directly.  The shared generated final
        # manifest is refreshed by the root integration wave.
        cls.manifest = adoption.build(dict(adoption.DEFAULTS))

    def test_receipt_regenerates_complete_exact_closure(self):
        rebuilt = stock.build()
        self.assertEqual(self.audit, rebuilt)
        self.assertEqual(40, len(rebuilt["section_matches"]))
        self.assertEqual({
            "onoff": 7, "buf_simple": 6, "msg_q": 4,
            "work": 10, "timer": 4, "poll": 9,
        }, {row["unit"]: row["live_section_count"]
            for row in rebuilt["source_units"]})
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in rebuilt["section_matches"]))

    def test_every_call_relocation_has_exact_resolved_target(self):
        checked = {(row["caller"], row["offset"]): row
                   for row in self.audit["call_target_checks"]}
        expected = 0
        for section in self.audit["section_matches"]:
            for relocation in section["relocations"]:
                if relocation["type"] in (10, 30):
                    expected += 1
                    row = checked[(section["symbol"], relocation["offset"])]
                    self.assertEqual(relocation["target"],
                                     row["target_symbol"])
        self.assertEqual(expected, len(checked))
        add_mem = next(row for row in self.audit["section_matches"]
                       if row["symbol"] == "net_buf_simple_add_mem")
        call = next(row for row in add_mem["relocations"]
                    if row["target"] == "net_buf_simple_add")
        resolved = checked[("net_buf_simple_add_mem", call["offset"])]
        self.assertEqual("0x01030084", resolved["target_va"])
        self.assertEqual("0x0103a478", add_mem["va"])

    def test_private_state_is_complete_and_address_exact(self):
        states = {(row["unit"], row["section"]):
                  (row["runtime_address"], row["size"])
                  for row in self.audit["private_state_sections"]}
        self.assertEqual({
            ("work", ".bss.pending_cancels"): ("0x21004b50", 8),
            ("work", ".bss.lock"): ("0x21004b58", 4),
            ("timer", ".bss.lock"): ("0x21004b74", 4),
            ("poll", ".bss.lock"): ("0x21004b78", 4),
            ("poll", ".data.wait_q.0"): ("0x21000758", 8),
        }, states)

    def test_manifest_adopts_all_owners_and_removes_recovered_sources(self):
        entries = {row["va"]: row for row in
                   self.manifest["cores"]["net"]["entries"]}
        for owner in self.audit["manifest_functions"]:
            row = entries[owner["va"]]
            self.assertEqual("zephyr_os_kernel_stock", row["component"])
            self.assertEqual(owner["upstream_symbol"],
                             row["upstream_symbol"])
            self.assertTrue(row["exclude_reconstruction"])
            if owner["reconstruction_present"]:
                self.assertTrue((ROOT / owner["reconstruction_source"]).is_file())
                self.assertIn(owner["va"],
                              self.audit["recovered_atomic_group"])

    def test_readable_names_preserve_raw_address_backmaps(self):
        names = json.loads(OVERRIDES.read_text())["net"]
        for owner in self.audit["manifest_functions"]:
            self.assertEqual(owner["durable_symbol"],
                             names[owner["va"]]["name"])
            self.assertEqual("FUN_" + owner["va"][2:],
                             owner["raw_symbol"])

    def test_sdc_is_unchanged_outside_corrected_false_fingerprint(self):
        baseline = json.loads(BASELINE.read_text())
        adopted = set(self.audit["atomic_group"])
        before = {row["va"]: (row["exclude_reconstruction"],
                              row["upstream_symbol"])
                  for row in baseline["cores"]["net"]["entries"]
                  if row["component"] == "softdevice_controller" and
                  row["va"] not in adopted}
        after = {row["va"]: (row["exclude_reconstruction"],
                             row["upstream_symbol"])
                 for row in self.manifest["cores"]["net"]["entries"]
                 if row["component"] == "softdevice_controller" and
                 row["va"] not in adopted}
        self.assertEqual(before, after)
        self.assertEqual("report_only_unchanged",
                         self.audit["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
