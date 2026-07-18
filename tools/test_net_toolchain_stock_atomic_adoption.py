import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "net_toolchain_stock",
    ROOT / "tools/build_net_toolchain_stock_adoption.py")
BUILDER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BUILDER)
RECEIPT = ROOT / "recon/ownership/net_toolchain_stock_atomic_adoption.json"


class NetToolchainStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_is_reproducible_from_archives_and_firmware(self):
        self.assertEqual(BUILDER.build(), self.receipt)

    def test_exact_requested_identity_set(self):
        rows = {row["va"]: row for row in self.receipt["functions"]}
        self.assertEqual({
            "0x01025d38": "__udivmoddi4",
            "0x0102a244": "strcmp",
            "0x0103b5c4": "strnlen",
            "0x0103b614": "__aeabi_memcpy4",
            "0x0103b62e": "memset",
        }, {va: row["resolved_identity"] for va, row in rows.items()})
        self.assertTrue(all(row["raw_firmware_byte_exact"] for row in rows.values()))
        self.assertTrue(all(not row["executable_relocations"] for row in rows.values()))

    def test_memcpy_aliases_are_not_falsely_split(self):
        row = next(row for row in self.receipt["functions"]
                   if row["va"] == "0x0103b614")
        self.assertEqual({"memcpy", "__aeabi_memcpy", "__aeabi_memcpy4",
                          "__aeabi_memcpy8"},
                         set(row["elf_function_aliases"]))
        self.assertIn("caller relocation context",
                      self.receipt["policy"]["memcpy_alias_note"])

    def test_all_recorded_call_sites_resolve_to_the_owner(self):
        for row in self.receipt["functions"]:
            for caller in row["callers"]:
                self.assertTrue(caller["direct_calls"])
                for call in caller["direct_calls"]:
                    self.assertEqual(row["va"], call["resolved_target"])

    def test_libgcc_caller_boundary_and_relocations_are_closed(self):
        row = self.receipt["supporting_closure"][
            "libgcc_unsigned_division_entry"]
        self.assertEqual("__aeabi_uldivmod", row["identity"])
        self.assertEqual(48, row["section_size"])
        self.assertEqual(50, row["catalog_extent_size"])
        self.assertEqual({"__aeabi_ldiv0", "__udivmoddi4"},
                         {item["symbol"] for item in row["relocations"]})
        self.assertEqual("0x0100826c",
                         row["resolved_targets"]["__aeabi_ldiv0"])
        self.assertEqual("0x01025d38",
                         row["resolved_targets"]["__udivmoddi4"])

    def test_abi_and_version_claims_are_fail_closed(self):
        for row in self.receipt["functions"]:
            attrs = "\n".join(row["elf_attributes"])
            self.assertIn('Tag_CPU_name: "8-M.MAIN"', attrs)
            if row["archive_member"].endswith(".S.o"):
                self.assertIn("hand-written assembly",
                              row["optimization_evidence"])
            else:
                self.assertIn("Aggressive Size", attrs)
            self.assertIn("nofp", row["archive_path"])
            self.assertIn("not asserted unique", row["version_claim_strength"])

    def test_raw_catalog_evidence_remains_present(self):
        ownership = json.loads((
            ROOT / "recon/ownership/net_function_ownership.json").read_text())
        entries = ownership["entries"]
        for row in self.receipt["functions"]:
            raw = entries[row["va"]]
            self.assertEqual("sdk_library", raw["status"])
            self.assertEqual(row["raw_identity"], raw["name"])
            self.assertEqual(1.0, raw["signature_match"]["ratio"])
            self.assertTrue(row["preserve_raw_reconstruction_evidence"])

    def test_private_sdc_policy_is_unchanged(self):
        self.assertTrue(self.receipt["policy"]["private_sdc_report_only"])


if __name__ == "__main__":
    unittest.main()
