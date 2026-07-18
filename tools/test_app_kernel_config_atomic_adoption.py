#!/usr/bin/env python3
"""Fail-closed gates for the atomic kernel-config/mem-slab adoption."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_kernel_config_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"


def sha(data):
    return hashlib.sha256(data).hexdigest()


class AppKernelConfigAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_configuration_and_atomic_boundary_are_exact(self):
        self.assertEqual("authorized_atomic", self.audit["status"])
        self.assertEqual(8, len(self.rows))
        expected = {"baseline": 82, "config_only": 85, "adopted": 80}
        self.assertEqual(expected, self.audit["expected_normal_link_counts"])
        config = Path(self.audit["configured_build_receipts"][0]).read_text()
        for key, value in self.audit["required_config"].items():
            needle = ("# %s is not set" % key if value == "n" else
                      "%s=%s" % (key, value))
            self.assertIn(needle, config)
        group = sorted(self.audit["atomic_group"])
        self.assertTrue(all(sorted(row["atomic_group"]) == group
                            for row in self.rows.values()))
        self.assertTrue(all(sorted(row["whole_unit_closure"]["exclude_only"]) == group
                            for row in self.rows.values()))

    def test_all_eight_configured_sections_are_relocation_exact(self):
        image = IMAGE.read_bytes()
        for va_text, row in self.rows.items():
            va = int(va_text, 16)
            with Path(row["upstream_object"]).open("rb") as stream:
                elf = ELFFile(stream)
                section = elf.get_section_by_name(".text." + row["symbol"])
                candidate = bytearray(section.data())
                relocations = elf.get_section_by_name(
                    ".rel.text." + row["symbol"])
                offsets = ([] if relocations is None else
                           [item["r_offset"] for item in relocations.iter_relocations()])
            firmware = bytearray(image[va - 0xC000:
                                       va - 0xC000 + row["firmware_code_size"]])
            self.assertEqual(len(candidate), len(firmware), row["symbol"])
            for offset in offsets:
                candidate[offset:offset + 4] = b"\0" * 4
                firmware[offset:offset + 4] = b"\0" * 4
            self.assertEqual(candidate, firmware, row["symbol"])
            self.assertEqual(row["normalized_code_sha256"], sha(firmware))

    def test_manifest_names_and_retained_sources_are_cohesive(self):
        manifest = json.loads(MANIFEST.read_text())
        entries = {row["va"]: row for row in manifest["cores"]["app"]["entries"]}
        names = json.loads(NAMES.read_text())["by_address"]
        retained = RETAINED.read_text()
        for va, authorization in self.rows.items():
            self.assertTrue(entries[va]["exclude_reconstruction"], va)
            self.assertEqual(authorization["symbol"], names[va]["name"])
            self.assertEqual(authorization["raw_symbol"], names[va]["raw_name"])
            self.assertNotIn("/" + authorization["symbol"] + ".c", retained)
        self.assertNotIn("g1_recon_k_heap_free_validated", retained)
        self.assertNotIn("g1_recon_k_aligned_alloc_asserting", retained)
        self.assertNotIn("g1_recon_z_impl_k_queue_init", retained)

    def test_dmic_gap_remains_explicitly_report_only(self):
        gap = self.audit["report_only_open"]["dmic_stream_start"]
        self.assertIn("does not close", gap)
        self.assertIn("mem-slab calls", gap)


if __name__ == "__main__":
    unittest.main()
