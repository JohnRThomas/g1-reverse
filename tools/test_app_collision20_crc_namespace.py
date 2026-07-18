#!/usr/bin/env python3
"""Fail-closed COLLISION-20 rejection and namespace-isolation checks."""

import hashlib
import json
import subprocess
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
OBJECT = BUILD / "zephyr/CMakeFiles/zephyr.dir/lib/crc/crc16_sw.c.obj"
APP_ARCHIVE = BUILD / "app/libapp.a"
SDK_ARCHIVE = BUILD / "zephyr/libzephyr.a"
MAP = BUILD / "zephyr/zephyr_pre0.map"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/") / \
    "arm-zephyr-eabi-nm"


def sha256(data):
    return hashlib.sha256(data).hexdigest()


class CrcNamespaceIsolationTest(unittest.TestCase):
    def test_configured_sdk_owner_is_pinned_and_not_authorized(self):
        collision = next(row for row in json.loads(COLLISIONS.read_text())[
            "functions"] if row["va"] == "0x0007d9c0")
        self.assertFalse(collision["identity_threshold_candidate"])
        self.assertEqual(
            ["instruction_length_score_below_threshold",
             "opcode_score_below_threshold",
             "operand_shape_score_below_threshold"],
            collision["exclusion_blockers"])
        self.assertEqual("503c615e86ab849c827afcd175194849648b656c3977407126e2ddccf6ffd86b",
                         sha256(OBJECT.read_bytes()))
        self.assertFalse(any(row["va"] == "0x0007d9c0" for row in
                             json.loads(AUTH.read_text())["authorizations"]))

    def test_no_relocation_can_mask_the_instruction_mismatch(self):
        with OBJECT.open("rb") as stream:
            elf = ELFFile(stream)
            code = elf.get_section_by_name(".text.crc16_reflect").data()
            relocations = elf.get_section_by_name(
                ".rel.text.crc16_reflect")
        self.assertEqual(42, len(code))
        self.assertEqual("a118102d4a564f306bbfe2de38512ca7f878728f368c4dc1ddf03d4689d1b74a",
                         sha256(code))
        self.assertTrue(relocations is None or
                        relocations.num_relocations() == 0)
        offset = 0x0007d9c0 - 0x0000c200 + 512
        firmware = (ROOT / "app_update.bin").read_bytes()[offset:offset + 138]
        self.assertEqual("f139580dbdc1df0fd61ae6b4c3074a8096c380e4e2a988c615bc6d8bac8fbcfe",
                         sha256(firmware))
        self.assertEqual(3, sum(left == right for left, right in
                                zip(firmware, code)))

    def test_durable_names_and_machine_word_abis_are_exact(self):
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual("g1_recon_crc16_configurable",
                         names["0x0007d9c0"]["name"])
        self.assertEqual("FUN_0007d9c0",
                         names["0x0007d9c0"]["raw_name"])
        self.assertIn("crc16_reflect", names["0x0007d9c0"]["aliases"])
        self.assertEqual("g1_recon_crc16_ansi_seeded",
                         names["0x0007da4a"]["name"])
        self.assertEqual("FUN_0007da4a",
                         names["0x0007da4a"]["raw_name"])
        owner = (ROOT / "recon/app/src/FUN_0007d9c0.c").read_text()
        wrapper = (ROOT / "recon/app/src/FUN_0007da4a.c").read_text()
        self.assertIn("unsigned FUN_0007d9c0(unsigned seed, unsigned polynomial, unsigned xor_out,", owner)
        self.assertIn("int reflect_input, char reflect_output,", owner)
        self.assertIn("const unsigned char *src, int len)", owner)
        self.assertIn("unsigned int FUN_0007da4a(unsigned int seed, const unsigned char *src, int len)", wrapper)
        self.assertIn("FUN_0007d9c0(seed, 0x8005, 0xffff, 1, 1, src, len)", wrapper)
        self.assertNotIn("param_4", wrapper)

    def test_generated_sources_retain_both_namespaced_owners(self):
        retained = RETAINED.read_text()
        self.assertIn("/g1_recon_crc16_configurable.c", retained)
        self.assertIn("/g1_recon_crc16_ansi_seeded.c", retained)
        self.assertNotIn("/crc16_reflect.c", retained)
        self.assertNotIn("/crc16_ansi.c", retained)
        self.assertTrue((ROOT / "recon/symbolized/app/"
                         "g1_recon_crc16_configurable.c").exists())
        self.assertTrue((ROOT / "recon/symbolized/app/"
                         "g1_recon_crc16_ansi_seeded.c").exists())

    def test_real_link_has_distinct_sdk_and_reconstruction_owners(self):
        sdk_nm = subprocess.run(
            [str(NM), "-A", "-g", str(SDK_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        app_nm = subprocess.run(
            [str(NM), "-A", "-g", str(APP_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        self.assertEqual(1, sum(line.endswith(" T crc16_reflect")
                                for line in sdk_nm.splitlines()))
        self.assertFalse(any(line.endswith(" T crc16_reflect")
                             for line in app_nm.splitlines()))
        for symbol in ("g1_recon_crc16_configurable",
                       "g1_recon_crc16_ansi_seeded"):
            self.assertEqual(1, sum(line.endswith(" T " + symbol)
                                    for line in app_nm.splitlines()))
        link_map = MAP.read_text()
        self.assertIn("zephyr/libzephyr.a(crc16_sw.c.obj)", link_map)
        self.assertIn("app/libapp.a(g1_recon_crc16_configurable.c.obj)",
                      link_map)
        self.assertIn("app/libapp.a(g1_recon_crc16_ansi_seeded.c.obj)",
                      link_map)


if __name__ == "__main__":
    unittest.main()
