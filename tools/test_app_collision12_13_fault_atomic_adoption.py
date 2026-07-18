#!/usr/bin/env python3
"""Fail-closed checks for atomic ARM fault C/assembly owner adoption."""

import copy
import hashlib
import json
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_adoption_manifest as adoption


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/catalogs/app_collision12_13_fault_atomic.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"
POST_BUILD = Path("/private/tmp/g1-app-fault-post-0718i")
NM = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm")
VAS = {"0x000503d8", "0x00050558", "0x000506ac", "0x000507d4"}
REMOVED = {"z_arm_mpu_fault", "z_arm_bus_fault", "z_arm_usage_fault",
           "z_arm_fault"}


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def normalized_section(obj, section):
    with Path(obj).open("rb") as stream:
        elf = ELFFile(stream)
        data = bytearray(elf.get_section_by_name(section).data())
        reloc = elf.get_section_by_name(".rel" + section)
        ranges = []
        if reloc is not None:
            for item in reloc.iter_relocations():
                ranges.append((item["r_offset"], 4))
        for offset, size in ranges:
            data[offset:offset + size] = b"\0" * size
        return data, ranges


def normalized_firmware(va, size, ranges):
    image = IMAGE.read_bytes()
    offset = va - 0xC200 + 512
    data = bytearray(image[offset:offset + size])
    for start, length in ranges:
        data[start:start + length] = b"\0" * length
    return data


def link_sets(path):
    text = Path(path).read_text(errors="ignore")
    collisions = set(re.findall(r"multiple definition of `([^']+)'", text))
    unresolved = set(re.findall(r"undefined reference to `([^']+)'", text))
    return collisions, unresolved


class FaultAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.auth = json.loads(AUTH.read_text())
        cls.rows = [row for row in cls.auth["authorizations"]
                    if row.get("batch") == "COLLISION-12/13"]

    def test_four_corrected_owners_are_one_atomic_unit(self):
        self.assertEqual(VAS, {row["va"] for row in self.rows})
        for row in self.rows:
            self.assertEqual(VAS, set(row["atomic_group"]))
            self.assertEqual(VAS, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
        names = json.loads(NAMES.read_text())["by_address"]
        self.assertEqual("arm_mem_manage_fault_helper",
                         names["0x000503d8"]["name"])
        self.assertEqual("arm_bus_fault_helper",
                         names["0x00050558"]["name"])
        self.assertEqual("arm_usage_fault_helper",
                         names["0x000506ac"]["name"])
        for va in VAS:
            self.assertTrue((ROOT / "recon/app/src" /
                             ("FUN_%s.c" % va[2:])).exists())

    def test_fault_c_sections_are_relocation_normalized_exact(self):
        owner = self.audit["fault_c"]
        self.assertEqual(owner["source_sha256"], sha(
            "/Users/freedomcoder/ncs251/" + owner["source"]))
        self.assertEqual(owner["object_sha256"], sha(owner["object"]))
        for row in owner["functions"]:
            configured, ranges = normalized_section(owner["object"], row["section"])
            firmware = normalized_firmware(int(row["va"], 16), len(configured), ranges)
            self.assertEqual(firmware, configured, row["va"])
            self.assertEqual(row["normalized_sha256"],
                             hashlib.sha256(configured).hexdigest())

    def test_fault_s_is_exact_and_owns_public_exception_aliases(self):
        owner = self.audit["fault_s"]
        self.assertEqual(owner["source_sha256"], sha(
            "/Users/freedomcoder/ncs251/" + owner["source"]))
        self.assertEqual(owner["object_sha256"], sha(owner["object"]))
        configured, ranges = normalized_section(owner["object"], owner["section"])
        firmware = normalized_firmware(int(owner["entry_va"], 16),
                                       len(configured), ranges)
        self.assertEqual(firmware, configured)
        self.assertEqual(owner["normalized_sha256"],
                         hashlib.sha256(configured).hexdigest())
        with Path(owner["object"]).open("rb") as stream:
            elf = ELFFile(stream)
            symbols = {sym.name for sym in
                       elf.get_section_by_name(".symtab").iter_symbols()}
        self.assertTrue(set(owner["public_aliases"]) <= symbols)
        archive = (POST_BUILD / "zephyr/arch/arch/arm/core/aarch32/cortex_m/"
                   "libarch__arm__core__aarch32__cortex_m.a")
        sdk = subprocess.run([str(NM), "-A", "-g", str(archive)], check=True,
                             capture_output=True, text=True).stdout
        app = subprocess.run([str(NM), "-A", "-g",
                              str(POST_BUILD / "app/libapp.a")], check=True,
                             capture_output=True, text=True).stdout
        for symbol in ("z_arm_mpu_fault", "z_arm_bus_fault",
                       "z_arm_usage_fault"):
            self.assertEqual(1, sum(line.endswith(" T " + symbol)
                                    for line in sdk.splitlines()))
            self.assertFalse(any(line.endswith(" T " + symbol)
                                 for line in app.splitlines()))
        link_map = (POST_BUILD / "zephyr/zephyr_pre0.map").read_text()
        self.assertIn("a(fault.c.obj)", link_map)
        self.assertIn("a(fault_s.S.obj)", link_map)

    def test_config_manifest_and_retained_list_are_fail_closed(self):
        config = Path(self.audit["evidence"]["configured_build"])
        self.assertEqual(self.audit["evidence"]["configured_build_sha256"],
                         sha(config))
        values = adoption._kconfig_values(config)
        self.assertEqual(self.audit["required_config"],
                         {key: values.get(key)
                          for key in self.audit["required_config"]})
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        self.assertTrue(all(entries[va]["exclude_reconstruction"] for va in VAS))
        self.assertEqual("mem_manage_fault.constprop.0",
                         entries["0x000503d8"]["upstream_symbol"])
        retained = RETAINED.read_text()
        for name in ("arm_mem_manage_fault_helper", "arm_bus_fault_helper",
                     "arm_usage_fault_helper", "z_arm_fault"):
            self.assertNotIn("/%s.c" % name, retained)

    def test_link_delta_is_exact_and_unresolved_stable(self):
        evidence = self.audit["evidence"]
        before, unresolved_before = link_sets(evidence["pre_build_log"])
        after, unresolved_after = link_sets(evidence["post_build_log"])
        delta = self.audit["link_delta"]
        self.assertEqual((91, 87), (len(before), len(after)))
        self.assertEqual(REMOVED, before - after)
        self.assertEqual(set(), after - before)
        self.assertEqual({"FUN_0005463e", "FUN_00054688"}, unresolved_before)
        self.assertEqual(unresolved_before, unresolved_after)
        self.assertEqual(set(delta["removed"]), before - after)

    def test_missing_peer_and_identity_or_config_drift_fail_closed(self):
        changed = copy.deepcopy(self.auth)
        changed["authorizations"] = [row for row in changed["authorizations"]
                                      if row.get("va") != "0x000506ac"]
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "authorizations.json"
            path.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["app_collision_authorizations"] = str(path)
            with self.assertRaisesRegex(ValueError,
                                        "incomplete atomic authorization"):
                adoption.build(paths)

        for mutation, message in (("config", "required config mismatch"),
                                  ("identity", "authorization did not pass")):
            changed = copy.deepcopy(self.auth)
            with tempfile.TemporaryDirectory() as temp:
                if mutation == "config":
                    config = Path(temp) / ".config"
                    config.write_text("# CONFIG_ASSERT is not set\n"
                                      "CONFIG_ASSERT_LEVEL=2\n"
                                      "CONFIG_ASSERT_VERBOSE=y\n"
                                      "# CONFIG_ASSERT_NO_FILE_INFO is not set\n"
                                      "# CONFIG_ASSERT_NO_COND_INFO is not set\n"
                                      "# CONFIG_ASSERT_NO_MSG_INFO is not set\n"
                                      "# CONFIG_EXTRA_EXCEPTION_INFO is not set\n")
                    digest = sha(config)
                    for row in changed["authorizations"]:
                        if row.get("batch") == "COLLISION-12/13":
                            row["configured_build"] = str(config)
                            row["configured_build_sha256"] = digest
                else:
                    row = next(row for row in changed["authorizations"]
                               if row.get("va") == "0x000503d8")
                    row["identity_correction"]["corrected_upstream_symbol"] = ""
                path = Path(temp) / "authorizations.json"
                path.write_text(json.dumps(changed))
                paths = dict(adoption.DEFAULTS)
                paths["app_collision_authorizations"] = str(path)
                with self.assertRaisesRegex(ValueError, message):
                    adoption.build(paths)


if __name__ == "__main__":
    unittest.main()
