#!/usr/bin/env python3
"""Fail-closed source and back-map checks for COLLISION-03 isolation."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
OVERRIDES = ROOT / "recon/catalogs/function_name_overrides.json"

NAMES = {
    "0x00060744": ("FUN_00060744", "g1_clock_release_hfclk_checked"),
    "0x00065000": ("FUN_00065000", "g1_clock_stop_impl"),
    "0x00065190": ("FUN_00065190", "g1_nrfx_clock_init_checked"),
    "0x0006522c": ("FUN_0006522c", "g1_nrfx_clock_start_checked"),
    "0x00065324": ("FUN_00065324", "g1_nrfx_clock_stop_checked"),
    "0x00083874": ("FUN_00083874", "g1_nrfx_clock_stop_hfaudio"),
    "0x0008387a": ("FUN_0008387a", "g1_nrfx_clock_stop_hfclk192m"),
    "0x00083880": ("FUN_00083880", "g1_nrfx_clock_stop_lfclk"),
}


class NrfxClockNamespaceSourceTest(unittest.TestCase):
    def test_durable_names_preserve_every_raw_backmap(self):
        overrides = json.loads(OVERRIDES.read_text())["app"]
        for address, (raw_name, readable_name) in NAMES.items():
            with self.subTest(address=address):
                self.assertEqual(readable_name, overrides[address]["name"])
                self.assertEqual(raw_name, overrides[address]["raw_name"])
                self.assertIn(address, overrides[address]["evidence"])

    def test_canonical_and_verified_sources_are_identical(self):
        for raw_name, _ in NAMES.values():
            canonical = ROOT / "recon/app/src" / f"{raw_name}.c"
            mirror = ROOT / "recon/verified/src" / f"{raw_name}.c"
            with self.subTest(raw_name=raw_name):
                self.assertTrue(canonical.exists())
                self.assertEqual(canonical.read_bytes(), mirror.read_bytes())

    def test_corrected_checked_owner_abis_are_one_argument(self):
        init = (ROOT / "recon/app/src/FUN_00065190.c").read_text()
        stop = (ROOT / "recon/app/src/FUN_00065324.c").read_text()
        self.assertIn("uint32_t FUN_00065190(uintptr_t event_handler)", init)
        self.assertIn("void FUN_00065324(int domain)", stop)
        self.assertIn("FUN_00065000(domain);", stop)
        self.assertNotIn("param_2", init)
        self.assertNotIn("param_2", stop)

    def test_recovered_sources_encode_exact_seven_site_closure(self):
        expected = {
            "FUN_00060744": ["FUN_00065324(1);"],
            "FUN_0006522c": ["FUN_00065000(0);"],
            "FUN_00065324": ["FUN_00065000(domain);"],
            "FUN_00083874": ["FUN_00065324(3);"],
            "FUN_0008387a": ["FUN_00065324(2);"],
            "FUN_00083880": ["FUN_00065324(0);"],
        }
        count = 0
        for raw_name, calls in expected.items():
            source = (ROOT / "recon/app/src" / f"{raw_name}.c").read_text()
            for call in calls:
                self.assertIn(call, source)
                count += source.count(call)
        # Six recovered bodies encode six sites; the independently recovered
        # FUN_0006058c -> FUN_00065190 site completes the seven-site closure.
        init_caller = (ROOT / "recon/app/src/FUN_0006058c.c").read_text()
        self.assertIn("FUN_00065190", init_caller)
        self.assertEqual(7, count + 1)


if __name__ == "__main__":
    unittest.main()
