#!/usr/bin/env python3
"""Reproducible fail-closed checks for COLLISION-11 evidence."""

import hashlib
import json
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_adoption_manifest as adoption

BUILD = Path("/private/tmp/g1-app-residue-current-0718")
AUDIT = ROOT / "recon/catalogs/app_collision_11_virtqueue_free.json"
IMAGE = ROOT / "app_update.bin"
VQ_OBJ = (BUILD / "modules/open-amp/open-amp/lib/CMakeFiles/open_amp.dir/"
          "virtio/virtqueue.c.obj")
CALLER_OBJ = (BUILD / "zephyr/CMakeFiles/zephyr.dir/subsys/ipc/ipc_service/"
              "lib/ipc_static_vrings.c.obj")
NM = (Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin") /
      "arm-zephyr-eabi-nm")


def firmware(va, size):
    image = IMAGE.read_bytes()
    offset = va - 0xC200 + 512
    return bytearray(image[offset:offset + size])


def section(path, name):
    with path.open("rb") as stream:
        return bytearray(ELFFile(stream).get_section_by_name(name).data())


def mask(data, ranges):
    output = bytearray(data)
    for offset, size in ranges:
        output[offset:offset + size] = b"\0" * size
    return output


class VirtqueueFreeAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())

    def test_audit_is_activated_without_shared_naming_mutation(self):
        self.assertEqual("exact_sdk_adoption_activated",
                         self.audit["status"])
        self.assertEqual({"manifest_mutated": True,
                          "retained_sources_mutated": True,
                          "shared_naming_mutated": False},
                         self.audit["policy"])
        retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()
        self.assertNotIn("/virtqueue_free.c", retained)
        manifest = json.loads((ROOT / "recon/ownership/adoption_manifest.json").read_text())
        row = next(item for item in manifest["cores"]["app"]["entries"]
                   if item["va"] == "0x00070ee4")
        self.assertTrue(row["exclude_reconstruction"])

    def test_inflated_extent_override_fails_closed_on_size_drift(self):
        auth_path = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
        catalog = json.loads(auth_path.read_text())
        row = next(item for item in catalog["authorizations"]
                   if item["va"] == "0x00070ee4")
        self.assertTrue(row["catalog_extent_inflated"])
        self.assertEqual(46, row["firmware_code_size"])
        self.assertEqual(46, row["upstream_code_size"])
        row["upstream_code_size"] = 47
        with tempfile.TemporaryDirectory() as temp:
            changed = Path(temp) / "authorizations.json"
            changed.write_text(json.dumps(catalog))
            paths = dict(adoption.DEFAULTS)
            paths["app_collision_authorizations"] = str(changed)
            with self.assertRaisesRegex(ValueError,
                                        "did not pass exclusion gates"):
                adoption.build(paths)

    def test_owner_is_relocation_normalized_instruction_exact(self):
        match = self.audit["normalized_match"]
        ranges = [(item["offset"], item["size"])
                  for item in match["relocations"]]
        original = mask(firmware(0x70EE4, 56), ranges)
        configured = mask(section(VQ_OBJ, ".text.virtqueue_free"), ranges)
        self.assertEqual(original, configured)
        self.assertEqual(match["sha256"], hashlib.sha256(original).hexdigest())
        self.assertEqual(46, self.audit["firmware"]["true_code_extent"])
        self.assertEqual(186, self.audit["firmware"]["ghidra_catalog_extent"])

    def test_source_object_config_and_public_owner_are_pinned(self):
        owner = self.audit["configured_owner"]
        self.assertEqual(owner["source_sha256"], hashlib.sha256(
            Path(owner["source"]).read_bytes()).hexdigest())
        self.assertEqual(owner["object_sha256"], hashlib.sha256(
            VQ_OBJ.read_bytes()).hexdigest())
        self.assertEqual(owner["config_sha256"], hashlib.sha256(
            (BUILD / "zephyr/.config").read_bytes()).hexdigest())
        archive = BUILD / "modules/open-amp/open-amp/lib/libopen_amp.a"
        output = subprocess.run([str(NM), "-A", "-g", str(archive)], check=True,
                                capture_output=True, text=True).stdout
        self.assertEqual(1, sum(line.endswith(" T virtqueue_free")
                                for line in output.splitlines()))
        app_output = subprocess.run(
            [str(NM), "-A", "-g", str(BUILD / "app/libapp.a")], check=True,
            capture_output=True, text=True).stdout
        self.assertFalse(any(line.endswith(" T virtqueue_free")
                             for line in app_output.splitlines()))
        link_map = (BUILD / "zephyr/zephyr_pre0.map").read_text()
        self.assertIn("libopen_amp.a(virtqueue.c.obj)", link_map)
        self.assertNotIn("app/libapp.a(virtqueue_free.c.obj)", link_map)

    def test_abi_state_and_literal_semantics_match_source(self):
        source = Path(self.audit["configured_owner"]["source"]).read_text()
        self.assertIn("void virtqueue_free(struct virtqueue *vq)", source)
        self.assertIn("vq->vq_free_cnt != vq->vq_nentries", source)
        self.assertIn("vq->vq_name", source)
        self.assertIn("metal_free_memory(vq)", source)
        with VQ_OBJ.open("rb") as stream:
            elf = ELFFile(stream)
            rodata = elf.get_section_by_name(
                ".rodata.virtqueue_free.str1.1").data()
        self.assertEqual(b"%s: freeing non-empty virtqueue\r\n\0", rodata)
        self.assertEqual("void virtqueue_free(struct virtqueue *vq)",
                         self.audit["firmware"]["abi"])

    def test_sole_caller_is_complete_normalized_exact_closure(self):
        caller = self.audit["callers"]
        self.assertEqual(1, len(caller))
        self.assertEqual("0x0007eda4", caller[0]["va"])
        self.assertEqual(2, caller[0]["direct_calls"])
        ranges = [(offset, 4) for offset in
                  (0x08, 0x14, 0x20, 0x28, 0x30, 0x3E, 0x42, 0x58)]
        original = mask(firmware(0x7EDA4, 96), ranges)
        configured = mask(section(
            CALLER_OBJ, ".text.ipc_static_vrings_deinit"), ranges)
        self.assertEqual(original, configured)
        self.assertEqual(caller[0]["normalized_sha256"],
                         hashlib.sha256(original).hexdigest())
        self.assertEqual(["virtqueue_free"], self.audit[
            "whole_unit_closure"]["same_source_unit_collision_symbols"])
        self.assertEqual([], self.audit[
            "whole_unit_closure"]["new_undefined_symbols"])


if __name__ == "__main__":
    unittest.main()
