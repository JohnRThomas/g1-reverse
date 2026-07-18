#!/usr/bin/env python3
"""Fail-closed checks for COLLISION-18 scheduler source-unit adoption."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_collision18_sched_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
NAMES = ROOT / "recon/catalogs/address_names_app.json"
IMAGE = ROOT / "app_update.bin"
GROUP = {"0x000739f0", "0x00074184", "0x000744a4", "0x000748b8"}
REMOVED = {
    "z_reschedule", "z_thread_priority_set", "z_unpend_first_thread",
    "z_thread_abort",
}


class AppCollision18SchedAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_atomic_authorization_is_complete(self):
        self.assertEqual("authorized_atomic", self.audit["status"])
        self.assertEqual(GROUP, set(self.rows))
        for row in self.rows.values():
            self.assertEqual(GROUP, set(row["atomic_group"]))
            self.assertEqual(GROUP, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertGreaterEqual(row["cfg_verify_cases"], 1)

    def test_true_code_extents_are_relocation_exact(self):
        image = IMAGE.read_bytes()
        for va_text, row in self.rows.items():
            extent = row["firmware_code_size"]
            with Path(row["upstream_object"]).open("rb") as stream:
                elf = ELFFile(stream)
                section_name = ".text." + row["symbol"]
                section = elf.get_section_by_name(section_name)
                candidate = bytearray(section.data()[:extent])
                self.assertEqual(row["upstream_symbol_size"], len(section.data()))
                self.assertEqual(row["literal_pool_tail_size"], len(section.data()) - extent)
                reloc = elf.get_section_by_name(".rel" + section_name)
                offsets = ([] if reloc is None else
                           [item["r_offset"] for item in reloc.iter_relocations()
                            if item["r_offset"] < extent])
            va = int(va_text, 16)
            firmware = bytearray(image[va - 0xC000:va - 0xC000 + extent])
            for offset in offsets:
                candidate[offset:offset + 4] = b"\0" * 4
                firmware[offset:offset + 4] = b"\0" * 4
            self.assertEqual(candidate, firmware, row["symbol"])
            self.assertEqual(row["normalized_code_sha256"],
                             hashlib.sha256(firmware).hexdigest())

    def test_link_delta_and_unresolved_set_are_exact(self):
        delta = self.audit["link_delta"]
        self.assertEqual((80, 76), (delta["before"], delta["after"]))
        self.assertEqual(REMOVED, set(delta["removed"]))
        self.assertEqual([], delta["added"])
        expected = {"FUN_0005463e", "FUN_00054688"}
        self.assertEqual(expected, set(delta["unresolved_before"]))
        self.assertEqual(expected, set(delta["unresolved_after"]))
        pre = set(self.audit["normal_link_receipts"]["pre_overlay"]["collisions"])
        post = set(self.audit["normal_link_receipts"]["adopted"]["collisions"])
        self.assertEqual(REMOVED, pre - post)
        self.assertEqual(set(), post - pre)

    def test_manifest_retention_and_state_names_are_cohesive(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(entries[va]["exclude_reconstruction"])
            self.assertNotIn("/" + row["symbol"] + ".c", retained)
        names = json.loads(NAMES.read_text())
        self.assertEqual("_kernel", names["by_address"]["0x2000b448"]["name"])
        self.assertEqual("mutex_spinlock_b470",
                         names["by_address"]["0x2000b470"]["name"])
        self.assertEqual("sched_spinlock",
                         names["by_address"]["0x2000b490"]["name"])
        self.assertEqual("0x2000b448", names["by_name"]["_kernel"])
        self.assertEqual("0x2000b490", names["by_name"]["sched_spinlock"])
        header = (ROOT / "recon/symbols/g1_app_symbols.h").read_text()
        linker = (ROOT / "recon/symbols/g1_app_globals.ld").read_text()
        self.assertIn("extern struct z_kernel _kernel;", header)
        self.assertIn("PROVIDE(_kernel = 0x2000b448);", linker)
        self.assertIn("PROVIDE(sched_spinlock = 0x2000b490);", linker)

    def test_sdc_policy_remains_report_only(self):
        self.assertEqual("report_only_unchanged", self.audit["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
