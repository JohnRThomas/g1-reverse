#!/usr/bin/env python3
"""Fail-closed evidence checks for report-only COLLISION-17."""

import hashlib
import json
import sys
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_adoption_manifest as adoption


AUDIT = ROOT / "recon/ownership/app_collision17_k_queue_init_audit.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
NCS = Path("/Users/freedomcoder/ncs251")
CONFIG = Path("/private/tmp/g1-app-residue-current-0718/zephyr/.config")
APP_BASE = 0xC200
APP_FILE_OFFSET = 512


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def firmware_bytes(va, size):
    offset = va - APP_BASE + APP_FILE_OFFSET
    return IMAGE.read_bytes()[offset:offset + size]


@unittest.skip("superseded by the atomic firmware-kernel-config adoption gate")
class AppCollision17QueueInitAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.function = cls.audit["function"]
        cls.object_path = Path(cls.audit["inputs"]["configured_object"])

    def test_report_only_decision_and_pinned_inputs(self):
        self.assertEqual("COLLISION-17", self.audit["batch"])
        self.assertEqual("audited_report_only", self.audit["status"])
        self.assertEqual("namespaced_reconstruction_retain",
                         self.audit["decision"])
        self.assertIs(self.audit["safe_for_sdk_adoption"], False)
        inputs = self.audit["inputs"]
        self.assertEqual(inputs["configured_object_sha256"],
                         sha256(self.object_path.read_bytes()))
        self.assertEqual(inputs["configured_source_sha256"], sha256(
            (NCS / inputs["configured_source"]).read_bytes()))
        self.assertEqual(inputs["zephyr_config_sha256"],
                         sha256(CONFIG.read_bytes()))
        config = CONFIG.read_text()
        self.assertIn("CONFIG_POLL=y", config)
        self.assertIn("CONFIG_WAITQ_DUMB=y", config)
        self.assertNotIn("CONFIG_SMP=y", config)
        self.assertNotIn("CONFIG_SPIN_VALIDATE=y", config)

    def test_collision_receipt_rejects_identity_threshold(self):
        collision = next(row for row in json.loads(COLLISIONS.read_text())[
            "functions"] if row["va"] == "0x000864e8")
        self.assertEqual(self.function["collision_receipt_sha256"],
                         adoption._json_sha256(collision))
        self.assertFalse(collision["identity_threshold_candidate"])
        self.assertEqual(["operand_shape_score_below_threshold"],
                         collision["exclusion_blockers"])
        comparison = self.function["comparison"]
        self.assertEqual(collision["signature_match"]["opcode"],
                         comparison["relocation_aware_opcode_score"])
        self.assertEqual(collision["signature_match"]["shape"],
                         comparison["operand_shape_score"])
        self.assertEqual(collision["signature_match"]["length"],
                         comparison["instruction_length_score"])
        self.assertFalse(comparison["relocation_masked_exact"])

    def test_exact_sections_have_incompatible_write_layouts(self):
        firmware = firmware_bytes(0x864E8, 26)
        self.assertEqual(self.function["firmware_sha256"], sha256(firmware))
        self.assertEqual(
            "0023c0e90033836000f10c03c0e9033300f11403c0e905337047",
            firmware.hex())
        with self.object_path.open("rb") as stream:
            elf = ELFFile(stream)
            section = elf.get_section_by_name(
                self.function["configured_section"])
            configured = section.data()
            self.assertEqual(24, len(configured))
            self.assertEqual(self.function["configured_sha256"],
                             sha256(configured))
            self.assertEqual(
                "0023c0e9003300f10803c0e9023300f11003c0e904337047",
                configured.hex())
            self.assertIsNone(elf.get_section_by_name(
                ".rel.text.z_impl_k_queue_init"))
        self.assertEqual([0, 8, 12, 20], [row["offset"] for row in
                         self.function["firmware_writes"]])
        self.assertEqual([0, 8, 16], [row["offset"] for row in
                         self.function["configured_writes"]])
        self.assertEqual("explicit_spinlock",
                         self.function["firmware_writes"][1]["role"])

    def test_extent_and_complete_all_image_caller_closure(self):
        extent = self.audit["extent_and_closure"]
        self.assertEqual("0x00086502", extent["firmware_end_exclusive"])
        self.assertEqual("0x00086502", extent["next_function"])
        decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        image = IMAGE.read_bytes()[APP_FILE_OFFSET:]
        sites = []
        for offset in range(0, len(image) - 4, 2):
            instructions = list(decoder.disasm(
                image[offset:offset + 4], APP_BASE + offset, count=1))
            if not instructions:
                continue
            instruction = instructions[0]
            if (instruction.mnemonic in ("b.w", "bl", "blx") and
                    instruction.op_str == "#0x864e8"):
                sites.append(f"0x{instruction.address:08x}")
        self.assertEqual(extent["complete_call_sites"], sites)
        self.assertEqual(11, len(sites))
        self.assertEqual(10, len(self.audit["caller_closure"]))
        self.assertEqual(2, len(next(row for row in
            self.audit["caller_closure"] if row["name"] ==
            "bt_att_accept")["sites"]))

    def test_cfg_proofs_and_fail_closed_retention(self):
        self.assertEqual({"status": "PASS", "cases": 0, "selectors": {}},
                         self.function["cfg_verify"])
        self.assertTrue(all(row["cfg_verify"].startswith("PASS") for row in
                            self.audit["caller_closure"]))
        closure = self.audit["implementation_closure"]
        self.assertEqual([], closure["exclude_reconstruction_vas"])
        self.assertEqual([], closure["adopt_configured_sdk_symbols"])
        authorizations = json.loads(AUTH.read_text())["authorizations"]
        self.assertFalse(any(row["va"] == "0x000864e8"
                             for row in authorizations))
        manifest = json.loads(MANIFEST.read_text())
        entry = next(row for row in manifest["cores"]["app"]["entries"]
                     if row["va"] == "0x000864e8")
        self.assertFalse(entry["exclude_reconstruction"])
        retained = RETAINED.read_text()
        self.assertIn("/g1_recon_z_impl_k_queue_init.c", retained)
        self.assertNotIn("/z_impl_k_queue_init.c", retained)


if __name__ == "__main__":
    unittest.main()
