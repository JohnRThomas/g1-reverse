#!/usr/bin/env python3
"""Fail-closed evidence checks for COLLISION-16."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
AUDIT = ROOT / "recon/catalogs/app_collision_16_k_aligned_alloc.json"
OBJECT = BUILD / "zephyr/kernel/CMakeFiles/kernel.dir/mempool.c.obj"


def firmware(va, size):
    image = (ROOT / "app_update.bin").read_bytes()
    start = va - 0xC200 + 512
    return bytearray(image[start:start + size])


def section(name):
    with OBJECT.open("rb") as stream:
        return bytearray(ELFFile(stream).get_section_by_name(name).data())


@unittest.skip("superseded by the atomic firmware-kernel-config adoption gate")
class KAlignedAllocAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())

    def test_evidence_policy_rejects_sdk_adoption_and_namespace_is_integrated(self):
        self.assertEqual("non_exact_namespace_retain_required",
                         self.audit["status"])
        self.assertEqual({"shared_naming_mutated": False,
                          "manifest_mutated": False,
                          "retained_sources_mutated": False},
                         self.audit["policy"])
        retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()
        self.assertIn("/g1_recon_k_aligned_alloc_asserting.c", retained)
        self.assertNotIn("/k_aligned_alloc.c", retained)
        names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        self.assertEqual("0x000758cc",
                         names["by_name"]["g1_recon_k_aligned_alloc_asserting"])
        self.assertNotIn("k_aligned_alloc", names["by_name"])

    def test_firmware_extent_digest_and_cfg_receipt_are_pinned(self):
        row = self.audit["firmware"]
        code = firmware(0x758CC, row["true_code_extent"])
        self.assertEqual(row["code_sha256"], hashlib.sha256(code).hexdigest())
        self.assertEqual({"status": "PASS", "cases": 3,
                          "selectors": {"0": [2, 3, 4]}},
                         row["cfg_verify"])
        self.assertEqual("0x200037d8", row["system_heap"])

    def test_configured_owner_is_pinned_and_structurally_non_exact(self):
        owner = self.audit["configured_owner"]
        source = Path("/Users/freedomcoder/ncs251") / owner["source"]
        self.assertEqual(owner["source_sha256"],
                         hashlib.sha256(source.read_bytes()).hexdigest())
        self.assertEqual(owner["object_sha256"],
                         hashlib.sha256(OBJECT.read_bytes()).hexdigest())
        sdk = section(".text.k_aligned_alloc")
        self.assertEqual(16, len(sdk))
        self.assertEqual(owner["section_sha256"], hashlib.sha256(sdk).hexdigest())
        self.assertNotEqual(firmware(0x758CC, 16), sdk)
        self.assertEqual(5, len(self.audit["non_exact_reasons"]))

    def test_firmware_embeds_both_assertion_paths(self):
        image = (ROOT / "app_update.bin").read_bytes()
        values = []
        for va in (0xF899C, 0xF89D9, 0xF891E, 0xF075E, 0xF0779):
            start = va - 0xC200 + 512
            values.append(image[start:start + 180].split(b"\0", 1)[0].decode())
        evidence = self.audit["assertion_evidence"]
        self.assertTrue(all(condition in values for condition in evidence["conditions"]))
        self.assertTrue(all(any(message in value for value in values)
                            for message in evidence["messages"]))
        self.assertTrue(any("zephyr/kernel/mempool.c" in value for value in values))

    def test_single_caller_is_exact_alignment_four_wrapper(self):
        caller = self.audit["caller_closure"]
        self.assertEqual(1, len(caller))
        self.assertEqual("0x000868c2", caller[0]["va"])
        original = firmware(0x868C2, 8)
        configured = section(".text.k_malloc")
        original[4:8] = b"\0" * 4
        configured[4:8] = b"\0" * 4
        self.assertEqual(original, configured)
        self.assertEqual(caller[0]["normalized_sha256"],
                         hashlib.sha256(original).hexdigest())
        self.assertEqual({"status": "PASS", "cases": 0},
                         caller[0]["cfg_verify"])


if __name__ == "__main__":
    unittest.main()
