#!/usr/bin/env python3
"""Fail-closed COLLISION-10 OpenAMP ownership and selected-link checks."""

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
SOURCE = Path(
    "/Users/freedomcoder/ncs251/modules/lib/open-amp/open-amp/lib/rpmsg/rpmsg_virtio.c")
OBJECT = BUILD / (
    "modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/rpmsg/"
    "rpmsg_virtio.c.obj")
ARCHIVE = BUILD / "modules/open-amp/open-amp/lib/libopen_amp.a"
APP_ARCHIVE = BUILD / "app/libapp.a"
MAP = BUILD / "zephyr/zephyr_pre0.map"
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/") / \
    "arm-zephyr-eabi-nm"


def sha256(data):
    return hashlib.sha256(data).hexdigest()


class RpmsgInitVdevAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(AUTH.read_text())
        cls.authorization = next(
            row for row in cls.catalog["authorizations"]
            if row["va"] == "0x00071560")

    def test_single_exact_authorization_and_pinned_digests(self):
        self.assertEqual(1, sum(row["va"] == "0x00071560"
                                for row in self.catalog["authorizations"]))
        row = self.authorization
        self.assertEqual("COLLISION-10", row["batch"])
        self.assertEqual("rpmsg_init_vdev", row["symbol"])
        self.assertEqual(sha256(SOURCE.read_bytes()),
                         row["upstream_source_sha256"])
        self.assertEqual(sha256(OBJECT.read_bytes()),
                         row["upstream_object_sha256"])
        self.assertEqual(sha256((BUILD / "zephyr/.config").read_bytes()),
                         row["configured_build_sha256"])
        self.assertEqual(
            "4120c21a53a5bcfd41b59f75ee81e1ea06dce51d1f781166ad87d031fb95a5ad",
            sha256((ROOT / "recon/app/src/FUN_00071560.c").read_bytes()))

    def test_relocation_normalized_code_is_instruction_exact(self):
        row = self.authorization
        image_offset = 0x00071560 - 0x0000c200 + 512
        firmware = bytearray(
            IMAGE.read_bytes()[image_offset:image_offset + 44])
        with OBJECT.open("rb") as stream:
            elf = ELFFile(stream)
            upstream = bytearray(elf.get_section_by_name(
                ".text.rpmsg_init_vdev").data())
            relocations = elf.get_section_by_name(
                ".rel.text.rpmsg_init_vdev")
            symbols = elf.get_section(relocations["sh_link"])
            actual_relocations = []
            for relocation in relocations.iter_relocations():
                symbol = symbols.get_symbol(relocation["r_info_sym"])
                target = symbol.name
                if not target and isinstance(symbol["st_shndx"], int):
                    target = elf.get_section(symbol["st_shndx"]).name
                actual_relocations.append(
                    (relocation["r_offset"], relocation["r_info_type"],
                     target))
        self.assertEqual(
            [(0x20, 10, "rpmsg_init_vdev_with_config"),
             (0x28, 2, ".rodata")], actual_relocations)
        self.assertEqual([32], row["call_relocation_offsets"])
        self.assertEqual([40], row["literal_relocation_offsets"])
        for offset in (32, 40):
            firmware[offset:offset + 4] = b"\0" * 4
            upstream[offset:offset + 4] = b"\0" * 4
        self.assertEqual(firmware, upstream)
        self.assertEqual(row["normalized_code_sha256"], sha256(firmware))
        self.assertTrue(row["instruction_exact"])

    def test_collision_cfg_and_caller_closure_are_exactly_scoped(self):
        collision = next(item for item in json.loads(COLLISIONS.read_text())[
            "functions"] if item["va"] == "0x00071560")
        self.assertTrue(collision["identity_threshold_candidate"])
        self.assertEqual([], collision["exclusion_blockers"])
        self.assertEqual("rpmsg_virtio.c.obj",
                         collision["upstream"]["archive_member"])
        self.assertEqual({"status": "PASS", "cases": 0},
                         self.authorization["owner_cfg_verify"])
        self.assertEqual(6, self.authorization["cfg_verify_cases"])
        self.assertEqual(["0x00071560"], self.authorization[
            "whole_unit_closure"]["exclude_only"])
        self.assertEqual([], self.authorization[
            "whole_unit_closure"]["new_undefined_symbols"])
        caller = self.authorization["callers"]
        self.assertEqual(1, len(caller))
        self.assertEqual("0x0004d100", caller[0]["va"])
        self.assertEqual("PASS", caller[0]["cfg_verify"])
        self.assertEqual(6, caller[0]["cases"])
        self.assertEqual(
            caller[0]["source_sha256"],
            sha256((ROOT / "recon/app/src/FUN_0004d100.c").read_bytes()))

    def test_manifest_and_retained_list_exclude_only_this_owner(self):
        manifest = json.loads(MANIFEST.read_text())
        row = next(item for item in manifest["cores"]["app"]["entries"]
                   if item["va"] == "0x00071560")
        self.assertTrue(row["exclude_reconstruction"])
        self.assertEqual("rpmsg_init_vdev", row["upstream_symbol"])
        evidence = [item for item in row["evidence"] if item["type"] ==
                    "explicit_collision_adoption_authority"]
        self.assertEqual(1, len(evidence))
        retained = RETAINED.read_text()
        self.assertNotIn("/rpmsg_init_vdev.c", retained)
        self.assertTrue((ROOT / "recon/app/src/FUN_00071560.c").exists())

    def test_real_retain_all_selects_one_upstream_global_owner(self):
        upstream_nm = subprocess.run(
            [str(NM), "-A", "-g", str(ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        app_nm = subprocess.run(
            [str(NM), "-A", "-g", str(APP_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        upstream = [line for line in upstream_nm.splitlines()
                    if line.endswith(" T rpmsg_init_vdev")]
        self.assertEqual(1, len(upstream))
        app_definitions = [line for line in app_nm.splitlines()
                           if line.endswith(" T rpmsg_init_vdev")]
        self.assertEqual([], app_definitions)
        link_map = MAP.read_text()
        self.assertIn("libopen_amp.a(rpmsg_virtio.c.obj)", link_map)
        self.assertNotIn("app/libapp.a(rpmsg_init_vdev.c.obj)", link_map)


if __name__ == "__main__":
    unittest.main()
