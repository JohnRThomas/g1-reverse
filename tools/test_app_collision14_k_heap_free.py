#!/usr/bin/env python3
"""Fail-closed evidence checks for COLLISION-14 k_heap_free."""

import hashlib
import json
import shlex
import subprocess
import tempfile
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
CATALOG = ROOT / "recon/catalogs/app_collision14_k_heap_free.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
OBJECT = BUILD / "zephyr/kernel/CMakeFiles/kernel.dir/kheap.c.obj"
COMPILE_COMMANDS = BUILD / "compile_commands.json"
IMAGE = ROOT / "app_update.bin"


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def section_and_relocations(path):
    with path.open("rb") as stream:
        elf = ELFFile(stream)
        section = elf.get_section_by_name(".text.k_heap_free")
        relocations = elf.get_section_by_name(".rel.text.k_heap_free")
        symbols = elf.get_section(relocations["sh_link"])
        rows = []
        for relocation in relocations.iter_relocations():
            symbol = symbols.get_symbol(relocation["r_info_sym"])
            target = symbol.name
            if not target and isinstance(symbol["st_shndx"], int):
                target = elf.get_section(symbol["st_shndx"]).name
            rows.append((relocation["r_offset"],
                         relocation["r_info_type"], target))
        return bytearray(section.data()), rows


class KHeapFreeCollisionAuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(CATALOG.read_text())

    def test_current_collision_receipt_is_rejected(self):
        collision = next(row for row in json.loads(COLLISIONS.read_text())[
            "functions"] if row["va"] == "0x00071b2c")
        receipt = sha256(json.dumps(
            collision, sort_keys=True, separators=(",", ":")).encode())
        self.assertEqual(self.catalog["configured_owner"][
            "collision_receipt_sha256"], receipt)
        self.assertFalse(collision["identity_threshold_candidate"])
        self.assertEqual(
            ["instruction_length_score_below_threshold",
             "opcode_score_below_threshold",
             "operand_shape_score_below_threshold"],
            collision["exclusion_blockers"])
        self.assertFalse(any(row["va"] == "0x00071b2c" for row in
                             json.loads(AUTH.read_text())["authorizations"]))

    def test_configured_object_omits_spin_validation(self):
        configured = self.catalog["configured_owner"]
        self.assertEqual(configured["object_sha256"],
                         sha256(OBJECT.read_bytes()))
        code, relocations = section_and_relocations(OBJECT)
        self.assertEqual(58, len(code))
        self.assertEqual(configured["section_sha256"], sha256(code))
        self.assertEqual(
            [(20, 10, "sys_heap_free"),
             (28, 10, "z_unpend_all"),
             (44, 30, "z_reschedule")], relocations)
        config = (BUILD / "zephyr/.config").read_text()
        self.assertIn("# CONFIG_ASSERT is not set", config)
        self.assertNotIn("CONFIG_SPIN_VALIDATE=y", config)

    def test_firmware_true_extent_and_literal_pool_are_pinned(self):
        image = IMAGE.read_bytes()
        code = image[0x00071b2c - 0x0000c000:
                     0x00071bb8 - 0x0000c000]
        self.assertEqual(140, len(code))
        self.assertEqual(self.catalog["firmware"]["code_sha256"],
                         sha256(code))
        words = [int.from_bytes(image[va - 0xc000:va - 0xc000 + 4],
                                "little")
                 for va in range(0x00071bb8, 0x00071bd0, 4)]
        self.assertEqual([0x000f08c7, 0x000f0920, 0x00099cbd,
                          0x000f0935, 0x000f08f4, 0x000f090b], words)
        self.assertEqual(0xbdf8, int.from_bytes(code[-2:], "little"))

    def test_same_source_is_instruction_exact_with_firmware_config(self):
        commands = json.loads(COMPILE_COMMANDS.read_text())
        row = next(item for item in commands
                   if item["file"].endswith("/kernel/kheap.c"))
        args = shlex.split(row["command"])
        with tempfile.TemporaryDirectory() as temp:
            output = Path(temp) / "kheap.o"
            index = args.index("-o")
            args[index + 1] = str(output)
            args[1:1] = ["-DCONFIG_ASSERT=1",
                         "-DCONFIG_ASSERT_LEVEL=2",
                         "-DCONFIG_SPIN_VALIDATE=1"]
            subprocess.run(args, cwd=row["directory"], check=True,
                           capture_output=True, text=True)
            candidate, relocations = section_and_relocations(output)
        proof = self.catalog["configuration_exact_candidate"]
        self.assertEqual(164, len(candidate))
        call_offsets = sorted(offset for offset, kind, _ in relocations
                              if offset < 140 and kind in (10, 30))
        self.assertEqual(proof["call_relocation_offsets"], call_offsets)
        firmware = bytearray(IMAGE.read_bytes()[
            0x00071b2c - 0x0000c000:0x00071bb8 - 0x0000c000])
        candidate = candidate[:140]
        for offset in call_offsets:
            firmware[offset:offset + 4] = b"\0" * 4
            candidate[offset:offset + 4] = b"\0" * 4
        self.assertEqual(firmware, candidate)
        self.assertEqual(proof["relocation_normalized_code_sha256"],
                         sha256(firmware))

    def test_caller_closure_and_missing_body_are_fail_closed(self):
        closure = self.catalog["caller_closure"]
        root = ROOT / "recon/app/src"
        adapter = closure["adapter"]
        self.assertEqual(adapter["source_sha256"],
                         sha256((root / "FUN_000868b4.c").read_bytes()))
        for caller in closure["direct_callers"]:
            path = root / ("FUN_%s.c" % caller["va"][2:])
            if caller.get("canonical_source", "present") is None:
                self.assertFalse(path.exists())
            else:
                self.assertEqual(caller["source_sha256"],
                                 sha256(path.read_bytes()))
        veneer = closure["veneer"]
        resolutions = json.loads((ROOT / "recon/catalogs/"
                                  "app_veneer_resolutions.json").read_text())
        row = next(item for item in resolutions["entries"]
                   if item["va"] == veneer["va"])
        self.assertEqual("FUN_000868b4", row["target_symbol"])
        caller = veneer["caller"]
        path = root / ("FUN_%s.c" % caller["va"][2:])
        self.assertEqual(caller["source_sha256"], sha256(path.read_bytes()))


if __name__ == "__main__":
    unittest.main()
