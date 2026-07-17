#!/usr/bin/env python3
"""Fail-closed checks for the CPUNET retain-all UUID formatter owner."""

import hashlib
import importlib.util
import json
import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / "recon/catalogs/net_bt_uuid_to_str_owner.json"
IMAGE = ROOT / "netcore_image.bin"
SOURCE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/bluetooth/host/uuid.c")
HEADER = Path("/Users/freedomcoder/ncs251/zephyr/include/zephyr/bluetooth/uuid.h")
HOST_CMAKE = Path("/Users/freedomcoder/ncs251/zephyr/subsys/bluetooth/host/CMakeLists.txt")
NET_CMAKE = ROOT / "recon/application/net/CMakeLists.txt"
NET_CONF = ROOT / "recon/application/net/prj.conf"

spec = importlib.util.spec_from_file_location(
    "audit_net_bt_uuid_to_str_owner",
    ROOT / "tools/audit_net_bt_uuid_to_str_owner.py",
)
audit_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit_module)


class NetBtUuidToStrOwnerTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = json.loads(CATALOG.read_text())

    def test_pinned_public_source_and_abi(self):
        upstream = self.catalog["upstream"]
        self.assertEqual(
            hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            upstream["source_sha256"],
        )
        self.assertEqual(upstream["zephyr_commit"],
                         "83980fe1679441be9b0e1db556a353f6118fe14f")
        declaration = (
            "void bt_uuid_to_str(const struct bt_uuid *uuid, char *str, size_t len);"
        )
        self.assertIn(declaration, HEADER.read_text())
        self.assertIn(declaration[:-1], SOURCE.read_text())
        self.assertEqual(upstream["linkage"], "public_global")

    def test_hci_raw_excludes_normal_host_owner(self):
        conf = NET_CONF.read_text()
        self.assertRegex(conf, r"(?m)^CONFIG_BT_HCI_RAW=y$")
        self.assertNotRegex(conf, r"(?m)^CONFIG_BT_HCI_HOST=y$")
        host_cmake = HOST_CMAKE.read_text()
        self.assertIsNotNone(re.search(
            r"if\(CONFIG_BT_HCI_HOST\).*?\buuid\.c\b.*?endif\(\)",
            host_cmake,
            re.S,
        ))
        config = self.catalog["configuration"]
        self.assertIs(config["normal_gc_requires_owner"], False)
        self.assertIs(config["retain_all_probe_requires_owner"], True)

    def test_probe_selects_upstream_source_without_firmware_adoption(self):
        cmake = NET_CMAKE.read_text()
        probe = re.search(
            r"if\(G1_INTEGRATION_PROBE_RETAIN_ALL\)(.*?)endif\(\)",
            cmake,
            re.S,
        )
        self.assertIsNotNone(probe)
        self.assertIn(
            '"${ZEPHYR_BASE}/subsys/bluetooth/host/uuid.c"',
            probe.group(1),
        )
        firmware = self.catalog["firmware"]
        decision = self.catalog["decision"]
        self.assertIs(firmware["function_present"], False)
        self.assertIsNone(firmware["va"])
        self.assertEqual(firmware["callers"], [])
        self.assertIs(decision["adopt_as_firmware_function"], False)
        self.assertIs(decision["exclude_reconstruction"], False)
        self.assertFalse(any(decision[key] for key in ("weak_stub", "blob", "alias")))

        proof = self.catalog["proof"]
        self.assertEqual(proof["status"], "passed")
        link = proof["retain_all_partial_link"]
        self.assertEqual(link["strong_definition_count"], 1)
        self.assertEqual(link["selected_owner"], "app/libapp.a(uuid.c.obj)")
        self.assertEqual(link["undefined_reference_count"], 0)
        self.assertEqual(link["multiple_definition_count"], 0)

    def test_firmware_lacks_uuid_formatter_specific_strings(self):
        image = IMAGE.read_bytes()
        self.assertNotIn(b"%04x\0", image)
        self.assertNotIn(b"%08x-%04x-%04x-%04x-%08x%04x\0", image)
        evidence = self.catalog["firmware"]["evidence"]
        self.assertEqual(evidence["uuid16_format_occurrences"], [])
        self.assertEqual(evidence["complete_uuid128_format_occurrences"], [])

    def test_retain_all_auditor_is_fail_closed(self):
        good_map = (
            " .text.bt_uuid_to_str\n"
            "                0x0103da84       0x70 app/libapp.a(uuid.c.obj)\n"
            "                0x0103da84                bt_uuid_to_str\n"
        )
        self.assertTrue(audit_module.audit(good_map, "")["passed"])
        self.assertFalse(audit_module.audit(good_map, (
            "undefined reference to `bt_uuid_to_str'\n"
        ))["passed"])
        duplicate = good_map + good_map.replace("0x0103da84", "0x0103daf4")
        self.assertFalse(audit_module.audit(duplicate, "")["passed"])


if __name__ == "__main__":
    unittest.main()
