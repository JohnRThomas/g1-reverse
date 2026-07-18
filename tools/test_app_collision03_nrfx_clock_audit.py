#!/usr/bin/env python3
"""Fail-closed evidence checks for the report-only COLLISION-03 audit."""

import difflib
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
from build_upstream_index import extract_features


AUDIT = ROOT / "recon/ownership/app_collision03_nrfx_clock_audit.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
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
    data = IMAGE.read_bytes()
    offset = va - APP_BASE + APP_FILE_OFFSET
    return data[offset:offset + size]


def sequence_score(left, right):
    return difflib.SequenceMatcher(
        None, left, right, autojunk=False).ratio()


class AppCollision03NrfxClockAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.functions = {row["va"]: row for row in cls.audit["functions"]}
        cls.collisions = json.loads(COLLISIONS.read_text())
        cls.object_path = Path(cls.audit["inputs"]["configured_object"])

    def test_report_only_decision_and_pinned_inputs(self):
        audit = self.audit
        self.assertEqual(audit["batch"], "COLLISION-03")
        self.assertEqual(audit["status"], "audited_report_only")
        self.assertEqual(audit["decision"],
                         "namespaced_reconstruction_retain")
        self.assertIs(audit["safe_for_sdk_adoption"], False)
        inputs = audit["inputs"]
        self.assertEqual(sha256(self.object_path.read_bytes()),
                         inputs["configured_object_sha256"])
        source = NCS / inputs["configured_source"]
        self.assertEqual(sha256(source.read_bytes()),
                         inputs["configured_source_sha256"])
        self.assertEqual(sha256(CONFIG.read_bytes()),
                         inputs["zephyr_config_sha256"])
        glue = (NCS / "modules/hal/nordic/nrfx/templates/nrfx_glue.h")
        self.assertIn("#define NRFX_ASSERT(expression)\n", glue.read_text())
        self.assertEqual(inputs["configured_nrfx_assert"], "empty_macro")

    def test_collision_receipts_and_current_identity_mismatch(self):
        collision_rows = {
            row["va"]: row for row in self.collisions["functions"]
            if row["va"] in ("0x00065000", "0x00065190")
        }
        self.assertEqual(set(collision_rows),
                         {"0x00065000", "0x00065190"})
        for va in collision_rows:
            row = self.functions[va]
            self.assertEqual(row["collision_receipt_sha256"],
                             adoption._json_sha256(collision_rows[va]))
            self.assertFalse(row["comparison"]["relocation_masked_exact"])
        self.assertEqual(self.functions["0x00065000"]["actual_identity"],
                         "clock_stop")
        self.assertEqual(collision_rows["0x00065000"]["current_symbol"],
                         "nrfx_clock_stop")
        self.assertEqual(self.functions["0x00065324"]["actual_identity"],
                         "firmware_checked_nrfx_clock_stop")

    def test_selected_object_symbols_state_and_relocations(self):
        with self.object_path.open("rb") as stream:
            elf = ELFFile(stream)
            symbols = elf.get_section_by_name(".symtab")
            by_name = {}
            for symbol in symbols.iter_symbols():
                if symbol.name in ("clock_stop", "nrfx_clock_init",
                                    "nrfx_clock_stop", "m_clock_cb"):
                    by_name[symbol.name] = symbol
            self.assertEqual(by_name["clock_stop"]["st_info"]["bind"],
                             "STB_LOCAL")
            self.assertEqual(by_name["clock_stop"]["st_size"], 354)
            self.assertEqual(by_name["nrfx_clock_init"]["st_info"]["bind"],
                             "STB_GLOBAL")
            self.assertEqual(by_name["nrfx_clock_init"]["st_size"], 32)
            self.assertEqual(by_name["nrfx_clock_stop"]["st_info"]["bind"],
                             "STB_GLOBAL")
            self.assertEqual(by_name["nrfx_clock_stop"]["st_size"], 4)
            self.assertEqual(by_name["m_clock_cb"]["st_info"]["bind"],
                             "STB_LOCAL")
            self.assertEqual(by_name["m_clock_cb"]["st_size"], 8)

            expected_relocations = {
                ".rel.text.clock_stop": [
                    (164, 10, "nrfx_busy_wait"),
                    (222, 10, "nrfx_busy_wait"),
                    (280, 10, "nrfx_busy_wait"),
                    (334, 10, "nrfx_busy_wait"),
                ],
                ".rel.text.nrfx_clock_init": [(20, 2, ".bss.m_clock_cb")],
                ".rel.text.nrfx_clock_stop": [(0, 30, "clock_stop")],
            }
            for section_name, expected in expected_relocations.items():
                relocations = elf.get_section_by_name(section_name)
                linked_symbols = elf.get_section(relocations["sh_link"])
                actual = []
                for relocation in relocations.iter_relocations():
                    symbol = linked_symbols.get_symbol(relocation["r_info_sym"])
                    target = symbol.name
                    if not target and isinstance(symbol["st_shndx"], int):
                        target = elf.get_section(symbol["st_shndx"]).name
                    actual.append((relocation["r_offset"],
                                   relocation["r_info_type"], target))
                self.assertEqual(actual, expected)

        state = self.audit["shared_state"]
        self.assertEqual(state["firmware_address"], "0x2000b31c")
        self.assertEqual(state["configured_object_binding"], "STB_LOCAL")
        self.assertEqual(state["identity"],
                         "same_layout_different_link_storage")
        self.assertEqual(int.from_bytes(firmware_bytes(0x651CC, 4), "little"),
                         0x2000B31C)

    def test_firmware_and_upstream_section_digests_and_scores(self):
        comparisons = [
            ("0x00065000", 384, ".text.clock_stop"),
            ("0x00065190", 48, ".text.nrfx_clock_init"),
            ("0x00065324", 40, ".text.nrfx_clock_stop"),
        ]
        with self.object_path.open("rb") as stream:
            elf = ELFFile(stream)
            for va_text, code_size, section_name in comparisons:
                row = self.functions[va_text]
                va = int(va_text, 16)
                firmware = firmware_bytes(va, row["firmware_extent"])
                upstream = elf.get_section_by_name(section_name).data()
                self.assertEqual(sha256(firmware), row["firmware_sha256"])
                self.assertEqual(sha256(upstream), row["upstream_sha256"])
                firmware_features = extract_features(
                    firmware[:code_size], va)
                upstream_features = extract_features(upstream, 0)
                comparison = row["comparison"]
                self.assertAlmostEqual(
                    sequence_score(firmware_features["mnemonics"],
                                   upstream_features["mnemonics"]),
                    comparison["relocation_aware_opcode_score"], places=6)
                self.assertAlmostEqual(
                    sequence_score(firmware_features["operand_shapes"],
                                   upstream_features["operand_shapes"]),
                    comparison["operand_shape_score"], places=6)
                length_score = min(
                    firmware_features["instruction_count"],
                    upstream_features["instruction_count"]) / max(
                        firmware_features["instruction_count"],
                        upstream_features["instruction_count"])
                self.assertAlmostEqual(
                    length_score, comparison["instruction_length_score"],
                    places=6)

    def test_exact_firmware_call_closure(self):
        decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        image = IMAGE.read_bytes()[APP_FILE_OFFSET:]
        expected = {
            0x65000: [0x65276, 0x65348],
            0x65190: [0x6059E],
            0x65324: [0x60766, 0x83876, 0x8387C, 0x83882],
        }
        for target, expected_sites in expected.items():
            sites = []
            for offset in range(0, len(image) - 4, 2):
                instructions = list(decoder.disasm(
                    image[offset:offset + 4], APP_BASE + offset, count=1))
                if not instructions:
                    continue
                instruction = instructions[0]
                if (instruction.mnemonic in ("b.w", "bl", "blx") and
                        instruction.op_str == "#" + hex(target)):
                    sites.append(instruction.address)
            self.assertEqual(sites, expected_sites)

        init_calls = self.functions["0x00065190"]["direct_call_sites"]
        self.assertEqual(["0x0006059e"], [row["site"] for row in init_calls])
        stop_calls = self.functions["0x00065324"]["direct_call_sites"]
        self.assertEqual(["0x00060766", "0x00083876", "0x0008387c",
                          "0x00083882"],
                         [row["site"] for row in stop_calls])

    def test_cfg_proofs_and_fail_closed_retention(self):
        self.assertEqual(self.functions["0x00065000"]["cfg_verify"], {
            "status": "PASS", "cases": 9,
            "selectors": {"arg0": [0, 1, 2, 3, 4]},
        })
        self.assertEqual(self.functions["0x00065190"]["cfg_verify"], {
            "status": "PASS", "cases": 2,
            "selectors": {"arg0": [0, 1]},
        })
        self.assertEqual(self.functions["0x00065324"]["cfg_verify"],
                         {"status": "PASS", "cases": 1})
        closure = self.audit["implementation_closure"]
        self.assertEqual(closure["exclude_reconstruction_vas"], [])
        self.assertEqual(closure["adopt_configured_sdk_symbols"], [])
        self.assertEqual(closure["action"],
                         "rename_reconstructed_firmware_owners_and_retarget_firmware_callers")

        retained = RETAINED.read_text()
        self.assertIn("/nrfx_clock_stop.c", retained)
        self.assertIn("/nrfx_clock_init.c", retained)
        self.assertIn("/FUN_00065324.c", retained)
        manifest = json.loads(MANIFEST.read_text())
        init = next(row for row in manifest["cores"]["app"]["entries"]
                    if row["va"] == "0x00065190")
        self.assertFalse(init["exclude_reconstruction"])


if __name__ == "__main__":
    unittest.main()
