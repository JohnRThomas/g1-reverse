#!/usr/bin/env python3
"""Fail-closed identity and namespace checks for COLLISION-04."""

import hashlib
import json
import subprocess
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
NAME = "g1_recon_nrfx_wdt_channel_alloc"
VA = 0x00067E8C
NM = (Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin") /
      "arm-zephyr-eabi-nm")
NRFX_ARCHIVE = BUILD / "modules/hal_nordic/nrfx/libmodules__hal_nordic__nrfx.a"
DPPI_OBJECT = (BUILD / "modules/hal_nordic/nrfx/CMakeFiles/"
               "modules__hal_nordic__nrfx.dir/Users/freedomcoder/ncs251/"
               "modules/hal/nordic/nrfx/drivers/src/nrfx_dppi.c.obj")


class WdtNamespaceTest(unittest.TestCase):
    def test_durable_backmap_is_namespaced_and_bijective(self):
        names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        row = names["by_address"]["0x00067e8c"]
        self.assertEqual("FUN_00067e8c", row["raw_name"])
        self.assertEqual(NAME, row["name"])
        self.assertEqual("0x00067e8c", names["by_name"][NAME])
        self.assertNotIn("nrfx_dppi_channel_alloc", names["by_name"])

    def test_generated_owner_preserves_raw_provenance(self):
        canonical = ROOT / "recon/app/src/FUN_00067e8c.c"
        verified = ROOT / "recon/verified/src/FUN_00067e8c.c"
        self.assertEqual(canonical.read_bytes(), verified.read_bytes())
        self.assertIn(b"uint32_t FUN_00067e8c(int* param_1, uint8_t* param_2)",
                      canonical.read_bytes())
        for tree in ("named", "symbolized/app"):
            source = ROOT / "recon" / tree / (NAME + ".c")
            text = source.read_text()
            self.assertIn("identity: FUN_00067e8c @ 0x00067e8c", text)
            self.assertIn("public-name: " + NAME, text)
            self.assertIn("uint32_t " + NAME + "(", text)
            self.assertFalse((source.parent / "nrfx_dppi_channel_alloc.c").exists())

    def test_firmware_identity_is_wdt_not_dppi(self):
        image = (ROOT / "app_update.bin").read_bytes()
        offset = VA - 0xC200 + 512
        firmware = image[offset:offset + 114]
        self.assertEqual(114, len(firmware))
        self.assertEqual("6a25aa415c2096bcbeb4b87db5ba3c49700439ccaf0be7df85c07143c60376ef",
                         hashlib.sha256(firmware).hexdigest())
        for address, expected in ((0xF7A32, b"p_channel_id"),
                                  (0xF7052, b"p_cb->state == NRFX_DRV_STATE_INITIALIZED"),
                                  (0xF79C8, b"nrfx/drivers/src/nrfx_wdt.c")):
            start = address - 0xC200 + 512
            value = image[start:start + 160].split(b"\0", 1)[0]
            self.assertIn(expected, value)
        with DPPI_OBJECT.open("rb") as stream:
            dppi = ELFFile(stream).get_section_by_name(
                ".text.nrfx_dppi_channel_alloc").data()
        self.assertEqual(12, len(dppi))
        self.assertNotEqual(firmware, dppi)

    def test_retain_link_keeps_distinct_recon_and_sdk_owners(self):
        retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()
        self.assertIn("/" + NAME + ".c", retained)
        self.assertNotIn("/nrfx_dppi_channel_alloc.c", retained)
        app_nm = subprocess.run([str(NM), "-g", str(BUILD / "app/libapp.a")],
                                check=True, capture_output=True, text=True).stdout
        nrfx_nm = subprocess.run([str(NM), "-g", str(NRFX_ARCHIVE)],
                                 check=True, capture_output=True, text=True).stdout
        self.assertEqual(1, sum(line.endswith(" T " + NAME)
                                for line in app_nm.splitlines()))
        self.assertFalse(any(line.endswith(" T nrfx_dppi_channel_alloc")
                             for line in app_nm.splitlines()))
        self.assertEqual(1, sum(line.endswith(" T nrfx_dppi_channel_alloc")
                                for line in nrfx_nm.splitlines()))
        link_map = (BUILD / "zephyr/zephyr_pre0.map").read_text()
        self.assertIn("app/libapp.a(" + NAME + ".c.obj)", link_map)
        self.assertIn(".text.nrfx_dppi_channel_alloc", link_map)


if __name__ == "__main__":
    unittest.main()
