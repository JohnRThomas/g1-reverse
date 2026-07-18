#!/usr/bin/env python3
"""Fail-closed checks for the configured COLLISION-23 MPSC adoption."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_collision23_mpsc_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
GROUP = {
    "0x0004bc28", "0x0004bc8c", "0x0004be0c", "0x0004beb8",
    "0x0004bfc8", "0x0004d56c", "0x0007e314", "0x0007e33a",
    "0x0007e35c", "0x0007e378", "0x0007e390", "0x0007e3ce",
    "0x0007e4bc", "0x0007e4f2",
}
REMOVED = {"mpsc_pbuf_init", "mpsc_pbuf_commit", "mpsc_pbuf_free", "mpsc_pbuf_claim"}


class AppCollision23MpscAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_all_reconstruction_duplicates_are_exact_and_atomic(self):
        self.assertEqual(GROUP, set(self.rows))
        for row in self.rows.values():
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertEqual(GROUP, set(row["atomic_group"]))
            self.assertEqual(GROUP, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertEqual([], row["whole_unit_closure"]["new_undefined_symbols"])

    def test_corrected_claim_identities_are_separate(self):
        local = self.rows["0x0004d56c"]
        self.assertEqual("mpsc_pbuf_claim", local["symbol"])
        self.assertEqual("z_log_msg_local_claim",
                         local["identity_correction"]["corrected_upstream_symbol"])
        true_claim = self.rows["0x0004beb8"]
        self.assertTrue(true_claim["hidden_owner_closure"])
        self.assertEqual("mpsc_pbuf_claim",
                         true_claim["identity_correction"]["corrected_upstream_symbol"])

    def test_manifest_excludes_the_complete_duplicate_set(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        retained = RETAINED.read_text()
        for va in GROUP:
            self.assertTrue(entries[va]["exclude_reconstruction"], va)
        self.assertNotIn("/mpsc_pbuf_init.c", retained)
        self.assertNotIn("/mpsc_pbuf_commit.c", retained)
        self.assertNotIn("/mpsc_pbuf_free.c", retained)
        self.assertNotIn("/mpsc_pbuf_claim.c", retained)

    def test_normal_link_delta_and_residue_are_exact(self):
        link = self.audit["verified_normal_link"]
        self.assertEqual((19, 15), (link["before"], link["after"]))
        self.assertEqual(REMOVED, set(link["removed"]))
        self.assertEqual([], link["added"])
        self.assertEqual({"FUN_0005463e", "FUN_00054688"}, set(link["unresolved"]))
        self.assertEqual(15, len(link["collisions"]))

    def test_other_log_core_bodies_remain_namespaced_and_retained(self):
        names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        by_address = names["by_address"]
        self.assertEqual("g1_recon_z_log_msg_alloc", by_address["0x0004d55c"]["name"])
        self.assertEqual("g1_recon_z_log_msg_commit", by_address["0x0004d8b8"]["name"])
        retained = RETAINED.read_text()
        self.assertIn("/g1_recon_z_log_msg_alloc.c", retained)
        self.assertIn("/g1_recon_z_log_msg_commit.c", retained)


if __name__ == "__main__":
    unittest.main()
