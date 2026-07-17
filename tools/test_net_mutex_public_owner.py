#!/usr/bin/env python3
"""Fail-closed evidence checks for the exact CPUNET mutex public owner."""

import hashlib
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs/net_sdk_public_ownership.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/net_retained_sources.cmake"
IMAGE = ROOT / "netcore_image.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/kernel/mutex.c")


class NetMutexPublicOwnerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(CATALOG.read_text())
        cls.row = next(item for item in cls.catalog["functions"]
                       if item["va"] == "0x0103657c")

    def test_pinned_source_and_firmware_abi_config(self):
        self.assertEqual(
            hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            self.row["source_sha256"],
        )
        config = self.catalog["required_config"]
        self.assertIs(config["CONFIG_ASSERT_NO_MSG_INFO"], True)
        self.assertIs(config["CONFIG_THREAD_NAME"], True)
        self.assertEqual(config["CONFIG_THREAD_MAX_NAME_LEN"], 20)
        self.assertEqual(self.row["object"],
                         "zephyr/kernel/libkernel.a(mutex.c.obj)")
        self.assertEqual(self.row["abi"],
                         "int z_impl_k_mutex_unlock(struct k_mutex *mutex)")

    def test_recorded_normalized_firmware_digest(self):
        self.assertEqual(self.row["firmware_code_size"], 0xd0)
        self.assertEqual(self.row["reference_code_size"], 0xd0)
        body = bytearray(IMAGE.read_bytes()[0x0103657c - 0x01008000:
                                           0x0103657c - 0x01008000 + 0xd0])
        offsets = [int(value, 0) for value in
                   self.row["normalized_call_relocation_offsets"]]
        self.assertEqual(offsets, [
            0x10, 0x18, 0x34, 0x5a, 0x66, 0x72,
            0x7a, 0x80, 0x92, 0x9a, 0xa4, 0xb0,
        ])
        for offset in offsets:
            body[offset:offset + 4] = b"\0" * 4
        self.assertEqual(hashlib.sha256(body).hexdigest(),
                         self.row["normalized_code_sha256"])
        self.assertEqual(self.row["match_score"], 1.0)
        self.assertIs(self.row["exclude_reconstruction"], True)

    def test_generated_adoption_excludes_only_reconstruction_owner(self):
        manifest = json.loads(MANIFEST.read_text())
        row = next(item for item in manifest["cores"]["net"]["entries"]
                   if item["va"] == "0x0103657c")
        self.assertEqual(row["upstream_symbol"], "z_impl_k_mutex_unlock")
        self.assertEqual(row["upstream_unit"],
                         "zephyr/kernel/libkernel.a(mutex.c.obj)")
        self.assertEqual(row["decision"],
                         "adopt_upstream_exclude_reconstruction")
        retained = RETAINED.read_text()
        self.assertNotIn("/z_impl_k_mutex_unlock.c", retained)
        self.assertTrue((ROOT / "recon/net/src/FUN_0103657c.c").exists())


if __name__ == "__main__":
    unittest.main()
