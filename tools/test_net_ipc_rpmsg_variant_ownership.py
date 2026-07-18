#!/usr/bin/env python3
"""Fail-closed tests for the CPUNET Zephyr IPC RPMsg variant."""

import copy
import json
import unittest
from pathlib import Path

import build_adoption_manifest as manifest_builder
import build_net_ipc_rpmsg_variant_ownership as variant_builder


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_ipc_rpmsg_variant_ownership.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
BASELINE = ROOT / "recon/ownership/adoption_manifest_baseline.json"
NAMES = ROOT / "recon/catalogs/function_names_net.json"
RETAINED = ROOT / "recon/generated/net_retained_sources.cmake"
CANONICAL = ROOT / "recon/net/src/FUN_0102da84.c"
GENERATED = ROOT / "recon/symbolized/net/g1_ipc_rpmsg_register_ept.c"
CALLER = ROOT / "recon/symbolized/net/FUN_0102d938.c"


class NetIpcRpmsgVariantOwnershipTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.manifest = json.loads(MANIFEST.read_text())
        cls.names = json.loads(NAMES.read_text())

    def test_receipt_regenerates_with_complete_source_unit_closure(self):
        rebuilt = variant_builder.build()
        self.assertEqual(self.receipt, rebuilt)
        self.assertEqual(5, len(rebuilt["source_unit_sections"]))
        matches = {row["symbol"]: row["match"] for row in
                   rebuilt["source_unit_sections"]}
        self.assertEqual({
            "ns_bind_cb", "ipc_rpmsg_register_ept", "ipc_rpmsg_init",
            "ipc_rpmsg_deinit",
        }, {name for name, match in matches.items()
            if match == "relocation-masked-byte-exact"})
        self.assertEqual("fully-relocated-no-independent-identity",
                         matches["rpmsg_service_unbind"])
        self.assertEqual([], rebuilt["mutable_state_sections"])
        self.assertTrue(rebuilt["state_closure"]["complete"])
        self.assertEqual("PASS cases=7 selectors=args0,args1,args2",
                         rebuilt["cfg_verify"]["0x0102da84"])

    def test_two_live_paths_have_the_same_decisive_target_mismatch(self):
        rows = self.receipt["call_target_mismatches"]
        self.assertEqual({"ns_bind_cb", "ipc_rpmsg_register_ept"},
                         {row["owner_symbol"] for row in rows})
        self.assertTrue(all(row["stock_target_symbol"] ==
                            "rpmsg_service_unbind" for row in rows))
        self.assertTrue(all(row["firmware_target"] == "0x0103a98f"
                            for row in rows))
        self.assertTrue(all(row["firmware_target_is_function_entry"] is False
                            for row in rows))
        self.assertTrue(all(row["firmware_target_containing_function"] ==
                            "FUN_0103a924" for row in rows))
        self.assertTrue(all(row["firmware_target_first_bytes"] == "3678b600"
                            for row in rows))
        self.assertTrue(all(row["stock_target_behavior"] ==
                            "tail-branch rpmsg_destroy_ept" for row in rows))
        self.assertTrue(all(row["equivalent"] is False for row in rows))

    def test_manifest_retains_only_the_recovered_variant(self):
        row = next(row for row in self.manifest["cores"]["net"]["entries"]
                   if row["va"] == "0x0102da84")
        self.assertEqual("FUN_0102da84", row["raw_symbol"])
        self.assertEqual("g1_ipc_rpmsg_register_ept", row["current_symbol"])
        self.assertEqual("ipc_rpmsg_register_ept", row["upstream_symbol"])
        self.assertFalse(row["exclude_reconstruction"])
        self.assertEqual("retain_reconstruction", row["decision"])
        record = self.names["by_address"]["0x0102da84"]
        self.assertEqual("FUN_0102da84", record["raw_name"])
        self.assertIn("FUN_0102da84", record["aliases"])

    def test_generated_sources_and_caller_use_noncolliding_variant_name(self):
        retained = RETAINED.read_text()
        self.assertIn("g1_ipc_rpmsg_register_ept.c", retained)
        self.assertNotIn("/ipc_rpmsg_register_ept.c\"", retained)
        generated = GENERATED.read_text()
        self.assertIn("identity: FUN_0102da84 @ 0x0102da84", generated)
        self.assertIn("int g1_ipc_rpmsg_register_ept(", generated)
        self.assertIn("(void *)0x0103a98fu", generated)
        caller = CALLER.read_text()
        self.assertIn("extern int g1_ipc_rpmsg_register_ept(", caller)
        self.assertIn("g1_ipc_rpmsg_register_ept(state, 1, record)", caller)

    def test_callback_literal_is_corrected_in_canonical_source(self):
        text = CANONICAL.read_text()
        self.assertIn("Raw/address back-map: FUN_0102da84 / 0x0102da84", text)
        self.assertIn("(void *)0x0103a98fu", text)
        self.assertNotIn("0x0103cfa9", text)

    def test_retain_gate_rejects_erased_mismatch_evidence(self):
        broken = copy.deepcopy(self.receipt)
        broken["call_target_mismatches"][0]["equivalent"] = True
        names = manifest_builder._name_records(NAMES)
        with self.assertRaisesRegex(ValueError, "incomplete net IPC"):
            manifest_builder._net_ipc_rpmsg_variant_entries(
                broken, str(RECEIPT.relative_to(ROOT)), {"net": names})

    def test_sdc_report_only_decisions_are_unchanged(self):
        baseline = json.loads(BASELINE.read_text())
        before = {row["va"]: (row["exclude_reconstruction"],
                              row["upstream_symbol"])
                  for row in baseline["cores"]["net"]["entries"]
                  if row["component"] == "softdevice_controller"}
        after = {row["va"]: (row["exclude_reconstruction"],
                             row["upstream_symbol"])
                 for row in self.manifest["cores"]["net"]["entries"]
                 if row["component"] == "softdevice_controller"}
        # Later exact public/kernel corrections are allowed to replace rows;
        # this receipt itself cannot mutate any surviving SDC decision.
        common = before.keys() & after.keys()
        self.assertEqual({va: before[va] for va in common},
                         {va: after[va] for va in common})
        self.assertEqual("report_only_unchanged",
                         self.receipt["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
