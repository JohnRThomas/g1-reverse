#!/usr/bin/env python3
"""Fail-closed proof for COLLISION-31 ``bt_settings_delete`` adoption."""

import hashlib
import json
import subprocess
import tempfile
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB


ROOT = Path(__file__).resolve().parents[1]
BUILD = Path("/private/tmp/g1-app-residue-current-0718")
AUTHORIZATIONS = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
COLLISIONS = ROOT / "recon/ownership/app_build_collision_ownership.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/bluetooth/host/settings.c")
OBJCOPY = Path(
    "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
    "arm-zephyr-eabi-objcopy"
)
NM = OBJCOPY.with_name("arm-zephyr-eabi-nm")
UPSTREAM_ARCHIVE = (BUILD / "zephyr/subsys/bluetooth/host/"
                    "libsubsys__bluetooth__host.a")
APP_ARCHIVE = BUILD / "app/libapp.a"
LINK_MAP = BUILD / "zephyr/zephyr_pre0.map"
APP_BASE = 0xC200
APP_FILE_OFFSET = 512
VA = 0x00052FBC
SIZE = 76


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def firmware_bytes(va, size):
    image = IMAGE.read_bytes()
    start = va - APP_BASE + APP_FILE_OFFSET
    return image[start:start + size]


class AppBtSettingsDeleteAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.authorizations = json.loads(AUTHORIZATIONS.read_text())
        cls.authorization = next(
            row for row in cls.authorizations["authorizations"]
            if row["va"] == "0x00052fbc"
        )
        collisions = json.loads(COLLISIONS.read_text())
        cls.collision = next(
            row for row in collisions["functions"]
            if row["va"] == "0x00052fbc"
        )

    def test_pinned_public_owner_abi_and_digests(self):
        row = self.authorization
        collision = self.collision
        upstream = collision["upstream"]
        obj = Path(row["upstream_object"])

        self.assertEqual(row["batch"], "COLLISION-31")
        self.assertEqual(row["symbol"], "bt_settings_delete")
        self.assertEqual(row["raw_symbol"], "FUN_00052fbc")
        self.assertEqual(row["status"], "authorized")
        self.assertEqual(row["upstream_source"],
                         "zephyr/subsys/bluetooth/host/settings.c")
        self.assertEqual(sha256(SOURCE.read_bytes()),
                         row["upstream_source_sha256"])
        self.assertEqual(sha256(obj.read_bytes()),
                         row["upstream_object_sha256"])
        self.assertEqual(row["upstream_source_sha256"],
                         upstream["source"]["sha256"])
        self.assertEqual(row["upstream_object_sha256"],
                         upstream["object_sha256"])
        self.assertEqual(row["configured_build_sha256"],
                         collision["configured_inclusion"]
                         ["zephyr_config_sha256"])
        self.assertEqual(row["configured_link_owner"],
                         collision["link_provenance"]["owner_input"])
        self.assertEqual(upstream["binding"], "STB_GLOBAL")
        self.assertEqual(upstream["section"], ".text.bt_settings_delete")
        self.assertEqual(upstream["symbol_size"], SIZE)
        self.assertEqual(upstream["abi"], {
            "return": "int",
            "params": ["char*", "uint8_t", "bt_addr_le_t*"],
            "variadic": False,
            "decl_line": 324,
        })
        self.assertEqual(
            row["abi"],
            "int bt_settings_delete(const char *key, uint8_t id, "
            "const bt_addr_le_t *addr)",
        )

    def test_relocation_normalized_section_is_byte_exact(self):
        row = self.authorization
        call_offsets = row["call_relocation_offsets"]
        literal_offsets = row["literal_relocation_offsets"]
        self.assertEqual(call_offsets, [0x12, 0x22, 0x28, 0x38])
        self.assertEqual(literal_offsets, [0x48])
        self.assertEqual(row["firmware_code_size"], SIZE)
        self.assertEqual(row["upstream_code_size"], SIZE)

        firmware = bytearray(firmware_bytes(VA, SIZE))
        with tempfile.TemporaryDirectory() as directory:
            section = Path(directory) / "bt_settings_delete.bin"
            subprocess.run([
                str(OBJCOPY), "--dump-section",
                ".text.bt_settings_delete=" + str(section),
                row["upstream_object"],
            ], check=True, capture_output=True)
            upstream = bytearray(section.read_bytes())

        self.assertEqual(len(firmware), SIZE)
        self.assertEqual(len(upstream), SIZE)
        for offset in call_offsets + literal_offsets:
            firmware[offset:offset + 4] = b"\0" * 4
            upstream[offset:offset + 4] = b"\0" * 4
        self.assertEqual(firmware, upstream)
        self.assertEqual(
            sha256(firmware),
            "1ba96ac4de798dbdfd6e096d90b3fc315b8c3caae42e7dc2c5b43f52352f5a7d",
        )
        self.assertEqual(sha256(firmware), row["normalized_code_sha256"])
        self.assertIs(row["instruction_exact"], True)

    def test_complete_firmware_caller_closure_and_cfg_proof(self):
        row = self.authorization
        decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        image = IMAGE.read_bytes()[APP_FILE_OFFSET:]
        sites = []
        for offset in range(0, len(image) - 4, 2):
            instructions = list(decoder.disasm(
                image[offset:offset + 4], APP_BASE + offset, count=1))
            if not instructions:
                continue
            insn = instructions[0]
            if (insn.mnemonic in ("b.w", "bl", "blx") and
                    insn.op_str == "#0x52fbc"):
                sites.append("0x%08x" % insn.address)

        self.assertEqual(sites, ["0x0005302a", "0x00053072", "0x0005318a"])
        callers = row["callers"]
        self.assertEqual(
            [(item["va"], item["branch_site"], item["upstream_symbol"],
              item["key"], item["cfg_verify"], item["cases"])
             for item in callers],
            [
                ("0x00053024", "0x0005302a", "bt_settings_delete_sc",
                 "sc", "PASS", 0),
                ("0x0005306c", "0x00053072", "bt_settings_delete_ccc",
                 "ccc", "PASS", 0),
                ("0x00053184", "0x0005318a", "bt_settings_delete_keys",
                 "keys", "PASS", 2),
            ],
        )
        self.assertEqual(row["owner_cfg_verify"], {"status": "PASS", "cases": 7})
        self.assertEqual(row["cfg_verify_cases"], 9)
        self.assertEqual(firmware_bytes(0x000F2C6B, 6), b"bt/%s\0")

    def test_manifest_excludes_only_the_reviewed_reconstruction(self):
        row = self.authorization
        closure = row["whole_unit_closure"]
        self.assertIs(closure["safe"], True)
        self.assertIs(closure["archive_member_already_selected"], True)
        self.assertEqual(closure["exclude_only"], ["0x00052fbc"])
        self.assertEqual(closure["new_undefined_symbols"], [])

        manifest = json.loads(MANIFEST.read_text())
        adopted = next(item for item in manifest["cores"]["app"]["entries"]
                       if item["va"] == "0x00052fbc")
        self.assertEqual(adopted["upstream_symbol"], "bt_settings_delete")
        self.assertEqual(adopted["decision"],
                         "adopt_upstream_exclude_reconstruction")
        self.assertTrue(adopted["exclude_reconstruction"])
        retained = RETAINED.read_text()
        self.assertNotIn("/bt_settings_delete.c", retained)
        self.assertTrue((ROOT / "recon/app/src/FUN_00052fbc.c").exists())

    def test_real_link_selects_exactly_one_upstream_global_owner(self):
        upstream_nm = subprocess.run(
            [str(NM), "-A", "-g", str(UPSTREAM_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        app_nm = subprocess.run(
            [str(NM), "-A", "-g", str(APP_ARCHIVE)], check=True,
            capture_output=True, text=True).stdout
        upstream = [line for line in upstream_nm.splitlines()
                    if line.endswith(" T bt_settings_delete")]
        reconstructed = [line for line in app_nm.splitlines()
                         if line.endswith(" T bt_settings_delete")]
        self.assertEqual(1, len(upstream))
        self.assertEqual([], reconstructed)
        link_map = LINK_MAP.read_text()
        self.assertIn("libsubsys__bluetooth__host.a(settings.c.obj)", link_map)
        self.assertNotIn("app/libapp.a(bt_settings_delete.c.obj)", link_map)


if __name__ == "__main__":
    unittest.main()
