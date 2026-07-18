#!/usr/bin/env python3
"""Fail-closed checks for COLLISION-34 Zephyr net_buf adoption."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_collision34_net_buf_atomic_adoption.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
GROUP = {
    "0x0005ee6c", "0x0005eeb4", "0x0005f074", "0x0005f148",
    "0x0005f200", "0x0005f24c", "0x0005f2d4", "0x0005f304",
    "0x0005f338", "0x0005f390", "0x0005f3d8", "0x0005f450",
}
REMOVED = {
    "net_buf_reset", "net_buf_slist_put", "net_buf_slist_get", "net_buf_put",
    "net_buf_unref", "net_buf_ref", "net_buf_frag_last",
    "net_buf_frag_insert", "net_buf_frag_add", "net_buf_append_bytes",
}


class AppCollision34NetBufAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_atomic_authorization_and_hidden_identity_corrections(self):
        self.assertEqual(GROUP, set(self.rows))
        for row in self.rows.values():
            self.assertEqual(GROUP, set(row["atomic_group"]))
            self.assertEqual(GROUP, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertGreaterEqual(row["cfg_verify_cases"], 1)
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual("net_buf_alloc_len", names["0x0005eeb4"]["name"])
        self.assertEqual("net_buf_frag_del", names["0x0005f3d8"]["name"])
        self.assertEqual({"0x0005eeb4", "0x0005f3d8"},
                         {va for va, row in self.rows.items()
                          if row.get("hidden_owner_closure")})

    def test_true_reachable_extents_are_relocation_exact(self):
        image = IMAGE.read_bytes()
        for va_text, row in self.rows.items():
            extent = row["firmware_code_size"]
            with Path(row["upstream_object"]).open("rb") as stream:
                elf = ELFFile(stream)
                section_name = ".text." + row["symbol"]
                section = elf.get_section_by_name(section_name)
                selected = bytearray(section.data()[:extent])
                self.assertEqual(row["upstream_symbol_size"], len(section.data()))
                self.assertEqual(row["literal_pool_tail_size"],
                                 len(section.data()) - extent)
                reloc = elf.get_section_by_name(".rel" + section_name)
                offsets = ([] if reloc is None else
                           [item["r_offset"] for item in reloc.iter_relocations()
                            if item["r_offset"] < extent])
            firmware = bytearray(image[
                int(va_text, 16) - 0xC000:
                int(va_text, 16) - 0xC000 + extent])
            for offset in offsets:
                selected[offset:offset + 4] = b"\0" * 4
                firmware[offset:offset + 4] = b"\0" * 4
            self.assertEqual(selected, firmware, row["symbol"])
            self.assertEqual(row["normalized_code_sha256"],
                             hashlib.sha256(firmware).hexdigest())

    def test_manifest_retention_and_private_source_unit_cohesion(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(entries[va]["exclude_reconstruction"])
            self.assertNotIn("/" + row["symbol"] + ".c", retained)
            closure = row["whole_unit_closure"]
            self.assertIn("net_buf_slist_lock", closure["private_state"])
            self.assertIn("_net_buf_pool_list_start", closure["private_state"])
            self.assertIn("generic_data_ref", closure["private_helpers"])
        self.assertEqual({"0x0005ee08": "net_buf_pool_get",
                          "0x0005ee18": "net_buf_id"},
                         self.audit["sdk_only_exact_owners"])

    def test_only_hidden_owner_callers_were_retargeted(self):
        for relative in ("recon/app/src/FUN_0005f450.c",
                         "recon/app/src/FUN_000836de.c"):
            text = (ROOT / relative).read_text()
            self.assertIn("net_buf_alloc_len", text)
            self.assertNotIn("FUN_0005eeb4(", text)
        text = (ROOT / "recon/app/src/FUN_00081852.c").read_text()
        self.assertIn("net_buf_frag_del", text)
        self.assertNotIn("FUN_0005f3d8(", text)

    def test_link_delta_is_exact(self):
        delta = self.audit["link_delta"]
        self.assertEqual((76, 66), (delta["before"], delta["after"]))
        self.assertEqual(REMOVED, set(delta["removed"]))
        self.assertEqual([], delta["added"])
        expected = {"FUN_0005463e", "FUN_00054688"}
        self.assertEqual(expected, set(delta["unresolved_before"]))
        self.assertEqual(expected, set(delta["unresolved_after"]))

    def test_unrelated_sdc_and_corrected_gppi_policies_are_unchanged(self):
        self.assertEqual("report_only_unchanged", self.audit["sdc_policy"])
        self.assertEqual("namespaced_correction_unchanged",
                         self.audit["gppi_0x000850dc_policy"])
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual("g1_recon_nrfx_gppi_channel_endpoints_setup",
                         names["0x000850dc"]["name"])


if __name__ == "__main__":
    unittest.main()
