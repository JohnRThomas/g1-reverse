#!/usr/bin/env python3
"""Fail-closed tests for the evidence-only toolchain exact-match receipt."""

import hashlib
import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/catalogs/app_toolchain_exact_matches.json"
SPEC = importlib.util.spec_from_file_location(
    "build_app_toolchain_exact_receipt",
    ROOT / "tools/build_app_toolchain_exact_receipt.py")
builder = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(builder)


class AppToolchainExactReceiptTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.families = {row["family"]: row for row in cls.receipt["archives"]}
        cls.names = json.loads(builder.NAMES.read_text())["by_address"]

    def test_receipt_is_deterministic_and_current(self):
        self.assertEqual(self.receipt, builder.build())

    def test_archives_specs_and_versions_are_pinned(self):
        for family, expected in builder.ARCHIVE_SHA256.items():
            actual = hashlib.sha256(builder.ARCHIVES[family].read_bytes()).hexdigest()
            self.assertEqual(expected, actual)
            self.assertEqual(expected, self.families[family]["archive_sha256"])
        self.assertEqual(builder.NANO_SPECS_SHA256,
                         hashlib.sha256(builder.NANO_SPECS.read_bytes()).hexdigest())
        environment = self.receipt["environment"]
        self.assertEqual("thumb/v8-m.main+fp/hard", environment["multilib"])
        self.assertEqual("12.2.0", environment["gcc_version"])
        self.assertEqual("3.3.0", environment["newlib_release"])

    def test_complete_sweep_counts_and_sentinels(self):
        expected = {
            "libc_nano": (129, 21936, 73, 621),
            "libm_nano": (33, 9440, 33, 308),
            "libgcc": (12, 4046, 12, 22),
        }
        for family, values in expected.items():
            summary = self.families[family]["summary"]
            self.assertEqual(values, (summary["vas"], summary["representative_bytes"],
                                      summary["archive_members"],
                                      summary["relocation_sites"]))
        sentinels = {
            "libc_nano": ("0x00014b60", 3156, "lib_a-dtoa.o"),
            "libm_nano": ("0x00075e14", 372, "lib_a-e_sqrt.o"),
            "libgcc": ("0x0000d580", 888, "_arm_addsubdf3.o"),
        }
        for family, (va, size, member) in sentinels.items():
            rows = {row["va"]: row for row in self.families[family]["functions"]}
            self.assertEqual(size, rows[va]["size"])
            self.assertEqual(member, rows[va]["matches"][0]["archive_member"])

    def test_ambiguity_is_mechanical_and_asinf_is_resolved(self):
        for archive in self.receipt["archives"]:
            vas = [row["va"] for row in archive["functions"]]
            self.assertEqual(sorted(vas), vas)
            self.assertEqual(len(vas), len(set(vas)))
            for row in archive["functions"]:
                owners = {(match["archive_member"], match["section"], match["size"],
                           match["normalized_code_sha256"])
                          for match in row["matches"]}
                mechanical = len(owners) > 1 or any(
                    len(match["firmware_hits"]) > 1 for match in row["matches"])
                self.assertEqual(mechanical, row["ambiguity"], row["va"])
        libm = {row["va"]: row for row in self.families["libm_nano"]["functions"]}
        row = libm["0x00075c2c"]
        self.assertTrue(row["ambiguity"])
        self.assertEqual("asinf", row["resolution"]["readable_name"])
        self.assertEqual("lib_a-wf_asin.o", row["matches"][0]["archive_member"])
        self.assertEqual({"lib_a-wf_asin.o", "lib_a-wf_acos.o"},
                         {match["archive_member"] for match in row["matches"]})

    def test_policy_does_not_authorize_adoption(self):
        self.assertEqual("evidence_only", self.receipt["status"])
        policy = self.receipt["policy"]
        self.assertFalse(policy["bulk_adoption"])
        self.assertFalse(policy["exclude_reconstructions"])
        self.assertTrue(policy["retain_recovered_c_as_evidence"])
        self.assertTrue(policy["sdc_remains_report_only"])
        serialized = json.dumps(self.receipt)
        self.assertNotIn('"authorizations"', serialized)
        self.assertNotIn('"safe_to_adopt"', serialized)

    def test_readable_names_keep_raw_backmaps_and_historical_aliases(self):
        expected = {
            "0x00013e50": ("nan", "dtoa_get_bias_const"),
            "0x00075d5c": ("log10f", "logf"),
            "0x00076154": ("__ieee754_atan2f", "atan2f"),
            "0x00076538": ("__ieee754_logf", "logf_core"),
            "0x00076718": ("__ieee754_log10f", "log2f"),
            "0x000870ea": ("strtod_sulp", "scalbn"),
        }
        for va, (name, former) in expected.items():
            record = self.names[va]
            self.assertEqual("FUN_%08x" % int(va, 16), record["raw_name"])
            self.assertEqual(name, record["name"])
            self.assertIn(former, record["aliases"])
        for archive in self.receipt["archives"]:
            for row in archive["functions"]:
                self.assertEqual("FUN_%08x" % int(row["va"], 16), row["raw_symbol"])


if __name__ == "__main__":
    unittest.main()
