#!/usr/bin/env python3
"""Fail-closed tests for the pinned CPUNET OpenAMP rpmsg.c adoption."""

import json
import unittest
from pathlib import Path

import build_net_openamp_stock_adoption as openamp


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/net_openamp_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
BASELINE = ROOT / "recon/ownership/adoption_manifest_baseline.json"
NAMES = ROOT / "recon/catalogs/function_names_net.json"
RETAINED = ROOT / "recon/generated/net_retained_sources.cmake"


class NetOpenampStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.manifest = json.loads(MANIFEST.read_text())

    def test_receipt_regenerates_and_all_selected_sections_are_exact(self):
        rebuilt = openamp.build()
        self.assertEqual(self.audit, rebuilt)
        self.assertEqual(12, len(rebuilt["section_matches"]))
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in rebuilt["section_matches"]))
        self.assertEqual([], rebuilt["mutable_state_sections"])
        self.assertEqual(["rpmsg_release_tx_buffer"], [
            row["symbol"] for row in rebuilt["discarded_sections"]])

    def test_raw_and_nocopy_are_distinguished_by_operand(self):
        correction = self.audit["identity_correction"]
        self.assertEqual("rpmsg_send_offchannel_raw",
                         correction["corrected_symbol"])
        self.assertEqual("0x01035450", correction["nocopy_owner_va"])
        rows = {row["symbol"]: row for row in self.audit["section_matches"]}
        self.assertEqual("0x01035424",
                         rows["rpmsg_send_offchannel_raw"]["va"])
        self.assertEqual("0x01035450",
                         rows["rpmsg_send_offchannel_nocopy"]["va"])

    def test_manifest_uses_whole_source_unit_for_all_catalog_entries(self):
        entries = {row["va"]: row for row in
                   self.manifest["cores"]["net"]["entries"]}
        expected = {row["va"]: row for row in
                    self.audit["manifest_functions"]}
        self.assertEqual(8, len(expected))
        for va, owner in expected.items():
            row = entries[va]
            self.assertEqual("openamp_rpmsg", row["component"])
            self.assertEqual(owner["upstream_symbol"], row["upstream_symbol"])
            self.assertTrue(row["exclude_reconstruction"])
            self.assertEqual("adopt_upstream_exclude_reconstruction",
                             row["decision"])

    def test_only_four_recovered_sources_are_removed(self):
        retained = RETAINED.read_text()
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual({
            "0x0103547c", "0x010354bc", "0x0103ad4a", "0x0103ad56"
        }, set(self.audit["recovered_atomic_group"]))
        for row in self.audit["manifest_functions"]:
            if row["reconstruction_present"]:
                self.assertNotIn(Path(row["reconstruction_source"]).name,
                                 retained)
                self.assertNotIn(names[row["va"]]["name"] + ".c", retained)

    def test_readable_names_keep_reversible_raw_backmaps(self):
        names = json.loads(NAMES.read_text())["by_address"]
        for row in self.audit["manifest_functions"]:
            record = names[row["va"]]
            self.assertEqual(row["raw_symbol"], record["raw_name"])
            self.assertEqual(row["upstream_symbol"], record["name"])
            self.assertIn(row["raw_symbol"], record["aliases"])

    def test_private_sdc_decisions_are_unchanged(self):
        baseline = json.loads(BASELINE.read_text())
        before = {row["va"]: (row["exclude_reconstruction"],
                              row["upstream_symbol"])
                  for row in baseline["cores"]["net"]["entries"]
                  if row["component"] == "softdevice_controller"}
        after = {row["va"]: (row["exclude_reconstruction"],
                             row["upstream_symbol"])
                 for row in self.manifest["cores"]["net"]["entries"]
                 if row["component"] == "softdevice_controller"}
        self.assertEqual(before, after)
        self.assertEqual("report_only_unchanged",
                         self.audit["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
