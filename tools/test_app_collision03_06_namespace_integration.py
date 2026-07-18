#!/usr/bin/env python3
"""Selected-build checks for combined COLLISION-03/06 isolation."""

import json
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
RECEIPT = ROOT / "recon/analysis/app_collision03_06_namespace_integration.json"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
          "arm-zephyr-eabi-nm")
APP_ARCHIVE = BUILD / "app/libapp.a"
NRFX_ARCHIVE = (BUILD / "modules/hal_nordic/nrfx/"
                "libmodules__hal_nordic__nrfx.a")
MAP = BUILD / "zephyr/zephyr_pre0.map"

MAPPINGS = {
    "0x00065000": "g1_clock_stop_impl",
    "0x00065190": "g1_nrfx_clock_init_checked",
    "0x00065f1c": "g1_recon_nrfx_nvmc_page_erase",
    "0x00065f80": "g1_recon_nrfx_nvmc_word_write",
    "0x0006125c": "flash_nrf_erase",
    "0x00061310": "flash_nrf_write",
}


class AppCollision0306NamespaceIntegrationTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.names = json.loads(NAMES.read_text())
        cls.retained = RETAINED.read_text()
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.app_nm = subprocess.run(
            [str(NM), "-A", "-g", str(APP_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        cls.nrfx_nm = subprocess.run(
            [str(NM), "-A", "-g", str(NRFX_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        cls.map_text = MAP.read_text(errors="replace")

    def test_durable_address_backmaps_select_namespaces(self):
        for address, name in MAPPINGS.items():
            self.assertEqual(self.names["by_address"][address]["name"], name)
            self.assertEqual(self.names["by_name"][name], address)

    def test_generated_callers_target_namespaced_nvmc_owners(self):
        erase = (ROOT / "recon/symbolized/app/flash_nrf_erase.c").read_text()
        write = (ROOT / "recon/symbolized/app/flash_nrf_write.c").read_text()
        self.assertIn("g1_recon_nrfx_nvmc_page_erase(address);", erase)
        self.assertIn("g1_recon_nrfx_nvmc_word_write(address + offset", write)
        self.assertIn("FUN_00065f1c @ 0x00065f1c", erase)
        self.assertIn("FUN_00065f80 @ 0x00065f80", write)

    def test_retained_list_has_namespaces_not_colliding_sources(self):
        expected = ["g1_clock_stop_impl.c", "g1_nrfx_clock_init_checked.c",
                    "g1_recon_nrfx_nvmc_page_erase.c",
                    "g1_recon_nrfx_nvmc_word_write.c"]
        for filename in expected:
            self.assertIn("/symbolized/app/" + filename, self.retained)
        for filename in ("nrfx_clock_init.c", "nrfx_clock_stop.c",
                         "nrfx_nvmc_page_erase.c", "nrfx_nvmc_word_write.c"):
            self.assertNotIn("/symbolized/app/" + filename, self.retained)

    def test_nm_and_map_have_distinct_reconstruction_and_sdk_owners(self):
        public = ("nrfx_clock_init", "nrfx_clock_stop",
                  "nrfx_nvmc_page_erase", "nrfx_nvmc_word_write")
        namespaced = ("g1_nrfx_clock_init_checked", "g1_nrfx_clock_stop_checked",
                      "g1_recon_nrfx_nvmc_page_erase",
                      "g1_recon_nrfx_nvmc_word_write")
        for symbol in public:
            self.assertFalse(any(line.endswith(" T " + symbol)
                                 for line in self.app_nm.splitlines()))
            self.assertEqual(1, sum(line.endswith(" T " + symbol)
                                    for line in self.nrfx_nm.splitlines()))
            self.assertIn(".text." + symbol, self.map_text)
        for symbol in namespaced:
            self.assertEqual(1, sum(line.endswith(" T " + symbol)
                                    for line in self.app_nm.splitlines()))
            self.assertIn(".text." + symbol, self.map_text)

    def test_exact_build_delta_and_unresolved_set(self):
        self.assertEqual(self.receipt["baseline_collision_count"], 105)
        self.assertEqual(self.receipt["result_collision_count"], 101)
        self.assertEqual(self.receipt["collision_delta"], -4)
        self.assertEqual(self.receipt["new_collision_symbols"], [])
        self.assertEqual(self.receipt["unresolved_before"],
                         self.receipt["unresolved_after"])
        self.assertEqual(self.receipt["full_link"], {
            "compiled": 3104, "failed_compile": 0, "link_rc": 0})


if __name__ == "__main__":
    unittest.main()
