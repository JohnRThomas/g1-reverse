#!/usr/bin/env python3
"""Fail-closed checks for COLLISION-35 net_buf_simple adoption."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_collision35_net_buf_simple_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
GROUP = {"0x0005f4d4", "0x0005f518", "0x0005f5d0"}
REMOVED = {"net_buf_simple_reserve", "net_buf_simple_push",
           "net_buf_simple_add"}


class AppCollision35NetBufSimpleAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_atomic_exact_group(self):
        self.assertEqual(GROUP, set(self.rows))
        for row in self.rows.values():
            self.assertEqual(GROUP, set(row["atomic_group"]))
            self.assertEqual(GROUP,
                             set(row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(row["configuration_variant_exact"])
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["relocation_masked_byte_exact"])
            self.assertGreaterEqual(row["cfg_verify_cases"], 1)

    def test_relocation_masked_code_is_exact(self):
        image = IMAGE.read_bytes()
        for va_text, row in self.rows.items():
            extent = row["firmware_code_size"]
            name = ".text." + row["symbol"]
            with Path(row["upstream_object"]).open("rb") as stream:
                elf = ELFFile(stream)
                section = elf.get_section_by_name(name)
                selected = bytearray(section.data()[:extent])
                reloc = elf.get_section_by_name(".rel" + name)
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

    def test_manifest_excludes_only_the_three_reconstructions(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(entries[va]["exclude_reconstruction"])
            self.assertNotIn("/" + row["symbol"] + ".c", retained)

    def test_link_contract_and_caller_closure(self):
        delta = self.audit["expected_link_delta"]
        self.assertEqual((22, 19), (delta["before"], delta["after"]))
        self.assertEqual(REMOVED, set(delta["removed"]))
        self.assertEqual([], delta["added"])
        self.assertEqual({"FUN_0005463e", "FUN_00054688"},
                         set(delta["unresolved"]))
        verified = self.audit["verified_normal_link"]
        self.assertEqual((22, 19),
                         (verified["before"], verified["after"]))
        self.assertEqual(REMOVED, set(verified["removed"]))
        self.assertEqual([], verified["added"])
        self.assertEqual({"FUN_0005463e", "FUN_00054688"},
                         set(verified["post_unresolved"]))
        closure = self.audit["caller_closure"]
        self.assertEqual((58, 71),
                         (closure["actual_unique_callers"],
                          closure["actual_direct_call_sites"]))

    def test_corrected_gppi_identity_is_unchanged(self):
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual("nrfx_gppi_channel_endpoints_setup",
                         names["0x000850dc"]["name"])
        self.assertNotEqual("net_buf_simple_push_mem",
                            names["0x000850dc"]["name"])
        self.assertEqual("corrected_gppi_identity_unchanged",
                         self.audit["gppi_0x000850dc_policy"])


if __name__ == "__main__":
    unittest.main()
