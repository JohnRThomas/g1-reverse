#!/usr/bin/env python3
"""Fail-closed COLLISION-02 ownership and selected-link checks."""

import hashlib
import json
import subprocess
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/modules/hal/libmetal/libmetal/lib/device.c")
OBJECT = BUILD / "modules/libmetal/libmetal/lib/CMakeFiles/metal.dir/device.c.obj"
ARCHIVE = BUILD / "modules/libmetal/libmetal/lib/libmetal.a"
APP_ARCHIVE = BUILD / "app/libapp.a"
MAP = BUILD / "zephyr/zephyr_pre0.map"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/") / \
    "arm-zephyr-eabi-nm"


def sha256(data):
    return hashlib.sha256(data).hexdigest()


class MetalBusUnregisterAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(AUTH.read_text())
        cls.authorization = cls.catalog["authorizations"][0]

    def test_single_exact_authorization_and_pinned_digests(self):
        self.assertEqual(1, len(self.catalog["authorizations"]))
        row = self.authorization
        self.assertEqual("COLLISION-02", row["batch"])
        self.assertEqual("0x000680f8", row["va"])
        self.assertEqual("metal_bus_unregister", row["symbol"])
        self.assertEqual(sha256(SOURCE.read_bytes()),
                         row["upstream_source_sha256"])
        self.assertEqual(sha256(OBJECT.read_bytes()),
                         row["upstream_object_sha256"])
        self.assertEqual(sha256((BUILD / "zephyr/.config").read_bytes()),
                         row["configured_build_sha256"])

    def test_relocation_normalized_code_is_instruction_exact(self):
        row = self.authorization
        image_offset = 0x000680f8 - 0x0000c200 + 512
        firmware = IMAGE.read_bytes()[image_offset:image_offset + 60]
        with OBJECT.open("rb") as stream:
            upstream = ELFFile(stream).get_section_by_name(
                ".text.metal_bus_unregister").data()
        self.assertEqual(60, len(firmware))
        self.assertEqual(60, len(upstream))
        self.assertEqual([52, 56], row["literal_relocation_offsets"])
        self.assertEqual(firmware[:52], upstream[:52])
        self.assertEqual(row["normalized_code_sha256"],
                         sha256(firmware[:52]))
        self.assertTrue(row["instruction_exact"])

    def test_collision_and_caller_closure_are_exactly_scoped(self):
        collision = next(item for item in json.loads(COLLISIONS.read_text())[
            "functions"] if item["va"] == "0x000680f8")
        self.assertTrue(collision["identity_threshold_candidate"])
        self.assertEqual([], collision["exclusion_blockers"])
        self.assertEqual("device.c.obj",
                         collision["upstream"]["archive_member"])
        self.assertEqual(["0x000680f8"], self.authorization[
            "whole_unit_closure"]["exclude_only"])
        self.assertEqual([], self.authorization[
            "whole_unit_closure"]["new_undefined_symbols"])
        self.assertEqual([{"va": "0x000682a8",
                           "raw_symbol": "FUN_000682a8",
                           "cfg_verify": "PASS"}],
                         self.authorization["callers"])

    def test_manifest_and_retained_list_exclude_only_this_owner(self):
        manifest = json.loads(MANIFEST.read_text())
        row = next(item for item in manifest["cores"]["app"]["entries"]
                   if item["va"] == "0x000680f8")
        self.assertTrue(row["exclude_reconstruction"])
        self.assertEqual("metal_bus_unregister", row["upstream_symbol"])
        evidence = [item for item in row["evidence"] if item["type"] ==
                    "explicit_collision_adoption_authority"]
        self.assertEqual(1, len(evidence))
        retained = RETAINED.read_text()
        self.assertNotIn("/metal_bus_unregister.c", retained)
        self.assertTrue((ROOT / "recon/app/src/FUN_000680f8.c").exists())

    def test_real_retain_all_selects_one_upstream_global_owner(self):
        upstream_nm = subprocess.run(
            [str(NM), "-A", "-g", str(ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        app_nm = subprocess.run(
            [str(NM), "-A", "-g", str(APP_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        upstream = [line for line in upstream_nm.splitlines()
                    if line.endswith(" T metal_bus_unregister")]
        self.assertEqual(1, len(upstream))
        app_definitions = [line for line in app_nm.splitlines()
                           if line.endswith(" T metal_bus_unregister")]
        self.assertEqual([], app_definitions)
        link_map = MAP.read_text()
        self.assertIn("libmetal.a(device.c.obj)", link_map)
        self.assertNotIn("app/libapp.a(metal_bus_unregister.c.obj)", link_map)


if __name__ == "__main__":
    unittest.main()
