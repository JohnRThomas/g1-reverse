#!/usr/bin/env python3
"""Fail-closed checks for the exact CPUNET IPC endpoint owner."""

import hashlib
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs/net_sdk_public_ownership.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/net_retained_sources.cmake"
OWNERSHIP = ROOT / "recon/ownership/net_function_ownership.json"
IMAGE = ROOT / "netcore_image.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/ipc/ipc_service/ipc_service.c")


class NetIpcServicePublicOwnerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(CATALOG.read_text())
        cls.row = next(item for item in cls.catalog["functions"]
                       if item["va"] == "0x0102d5b4")

    def test_pinned_source_abi_and_configuration(self):
        self.assertEqual(
            hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            self.row["source_sha256"],
        )
        self.assertEqual(self.catalog["upstream"]["zephyr_commit"],
                         "83980fe1679441be9b0e1db556a353f6118fe14f")
        config = self.row["required_config"]
        self.assertIs(config["CONFIG_IPC_SERVICE"], True)
        self.assertIs(config["CONFIG_LOG_MODE_DEFERRED"], True)
        self.assertEqual(config["CONFIG_IPC_SERVICE_LOG_LEVEL"], 3)
        self.assertEqual(self.row["object"],
                         "zephyr/libzephyr.a(ipc_service.c.obj)")
        self.assertEqual(
            self.row["abi"],
            "int ipc_service_register_endpoint(const struct device *instance, "
            "struct ipc_ept *ept, const struct ipc_ept_cfg *cfg)",
        )

    def test_recorded_relocation_normalized_firmware_digest(self):
        self.assertEqual(self.row["firmware_code_size"], 0x64)
        self.assertEqual(self.row["reference_code_size"], 0x64)
        body = bytearray(IMAGE.read_bytes()[0x0102d5b4 - 0x01008000:
                                           0x0102d618 - 0x01008000])
        offsets = [int(value, 0) for value in
                   self.row["normalized_relocation_offsets"]]
        self.assertEqual(offsets, [0x1a, 0x3e, 0x58, 0x5c, 0x60])
        for offset in offsets:
            body[offset:offset + 4] = b"\0" * 4
        self.assertEqual(hashlib.sha256(body).hexdigest(),
                         self.row["normalized_code_sha256"])
        self.assertEqual(self.row["match_score"], 1.0)
        self.assertIs(self.row["exclude_reconstruction"], True)

    def test_generic_ownership_catalog_agrees_on_extent_and_owner(self):
        ownership = json.loads(OWNERSHIP.read_text())["entries"]["0x0102d5b4"]
        self.assertEqual(ownership["size"], 0x64)
        self.assertEqual(ownership["confidence"], 1.0)
        self.assertEqual(ownership["signature_match"]["symbol"],
                         "ipc_service_register_endpoint")
        self.assertEqual(ownership["signature_match"]["ratio"], 1.0)

    def test_generated_selection_preserves_canonical_backmap(self):
        manifest = json.loads(MANIFEST.read_text())
        row = next(item for item in manifest["cores"]["net"]["entries"]
                   if item["va"] == "0x0102d5b4")
        self.assertEqual(row["raw_symbol"], "FUN_0102d5b4")
        self.assertEqual(row["current_symbol"],
                         "ipc_service_register_endpoint")
        self.assertEqual(row["upstream_symbol"],
                         "ipc_service_register_endpoint")
        self.assertEqual(row["upstream_unit"],
                         "zephyr/libzephyr.a(ipc_service.c.obj)")
        self.assertEqual(row["decision"],
                         "adopt_upstream_exclude_reconstruction")
        retained = RETAINED.read_text()
        self.assertNotIn("/ipc_service_register_endpoint.c", retained)
        self.assertTrue((ROOT / "recon/net/src/FUN_0102d5b4.c").exists())


if __name__ == "__main__":
    unittest.main()
