#!/usr/bin/env python3
"""Fail-closed gates for exact stock Newlib-nano closure adoption."""

import hashlib
import importlib.util
import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_newlib_stock_atomic_adoption.json"
_SPEC = importlib.util.spec_from_file_location(
    "build_app_newlib_stock_adoption",
    ROOT / "tools/build_app_newlib_stock_adoption.py")
builder = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(builder)


class AppNewlibStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        manifest = json.loads(
            (ROOT / "recon/ownership/adoption_manifest.json").read_text())
        cls.entries = {row["va"]: row
                       for row in manifest["cores"]["app"]["entries"]}
        cls.names = json.loads(
            (ROOT / "recon/catalogs/function_names_app.json").read_text())

    def test_archive_version_and_policy_are_pinned(self):
        self.assertEqual(builder.ARCHIVE_SHA256,
                         hashlib.sha256(builder.ARCHIVE.read_bytes()).hexdigest())
        self.assertEqual("3.3.0", self.receipt["newlib_release"])
        self.assertEqual(builder.NEWLIB_COMMIT, self.receipt["newlib_commit"])
        self.assertFalse(
            self.receipt["policy"]["fdlibm_prebuilt_archive_adoption"])
        self.assertTrue(
            self.receipt["policy"]["retain_recovered_c_as_evidence"])

    def test_every_archive_member_is_normalized_instruction_exact(self):
        self.assertEqual(17, len(self.rows))
        for va, symbol, member, section, _ in builder.MEMBERS:
            row = self.rows["0x%08x" % va]
            self.assertEqual(symbol, row["symbol"])
            self.assertEqual(member, row["archive_member"])
            self.assertTrue(row["archive_member_exact"])
            self.assertEqual({"CONFIG_NEWLIB_LIBC": "y",
                              "CONFIG_NEWLIB_LIBC_NANO": "y"},
                             row["required_config"])
            actual = builder.normalized_receipt(va, member, section)
            self.assertEqual(row["normalized_code_sha256"],
                             actual["normalized_code_sha256"])
            self.assertEqual(row["archive_member_sha256"],
                             actual["archive_member_sha256"])

    def test_atomic_closure_excludes_generated_build_inputs_not_evidence(self):
        group = sorted(self.rows)
        retained = (ROOT /
                    "recon/generated/app_retained_sources.cmake").read_text()
        for va, row in self.rows.items():
            self.assertEqual(group, sorted(row["atomic_group"]))
            self.assertEqual(group, sorted(
                row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(self.entries[va]["exclude_reconstruction"])
            self.assertNotIn("/" + row["symbol"] + ".c", retained)
            self.assertTrue(Path(row["reconstruction_source"]).exists())
            self.assertTrue((ROOT / "recon/named" /
                             (row["symbol"] + ".c")).exists())
            self.assertEqual(row["symbol"],
                             self.names["by_address"][va]["name"])

    def test_strtoul_constprop_backmap_and_normal_link_delta(self):
        backmap = self.rows["0x00077b38"]["public_veneer_backmap"]
        self.assertEqual(".text._strtoul_l.constprop.0",
                         backmap["matched_archive_body"])
        self.assertEqual(4, backmap["archive_public_veneer_size"])
        link = json.loads((ROOT /
            "recon/ownership/app_newlib_stock_normal_link.json").read_text())
        self.assertEqual((66, 61), (link["collision_count_before"],
                                   link["collision_count_after"]))
        self.assertEqual(sorted(builder.COLLISIONS), link["removed"])
        self.assertEqual([], link["added"])
        self.assertEqual(link["unresolved_before"], link["unresolved_after"])


if __name__ == "__main__":
    unittest.main()
