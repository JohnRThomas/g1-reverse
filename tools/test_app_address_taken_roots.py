#!/usr/bin/env python3
"""Regression gates for the fail-closed CPUAPP address-taken root ledger."""

import json
import re
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build_app_address_taken_roots as roots


class AppAddressTakenRootsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = json.loads(
            (ROOT / "recon/catalogs/app_address_taken_roots.json").read_text())
        cls.cmake = (ROOT / "recon/generated/app_address_taken_roots.cmake").read_text()

    def test_exact_binary_scan_cardinality_and_bytes(self):
        summary = self.data["summary"]
        self.assertEqual(303, summary["address_taken_identities"])
        self.assertEqual(198, summary["unmaterialized_identities"])
        self.assertEqual(38076, summary["unmaterialized_capped_bytes"])
        self.assertEqual(69, summary["pre_init_only_identities"])
        self.assertEqual(129, summary["post_init_pointer_identities"])
        self.assertEqual(130, summary["post_init_or_collision_review_identities"])

    def test_scan_is_aligned_thumb_and_outside_capped_functions(self):
        functions = roots.function_catalog()
        refs = roots.scan_pointers(functions)
        self.assertEqual(303, len(refs))
        image = (ROOT / "app_update.bin").read_bytes()
        intervals = [(row["entry"], row["entry"] + row["capped_size"])
                     for row in functions]
        for target, pointers in refs.items():
            for pointer in pointers:
                self.assertEqual(0, pointer & 3)
                raw = int.from_bytes(image[pointer - 0xC000:pointer - 0xC000 + 4], "little")
                self.assertEqual(target | 1, raw)
                self.assertFalse(any(start <= pointer < end for start, end in intervals))

    def test_only_unique_named_definitions_are_emitted(self):
        emitted = [row for row in self.data["entries"] if row["emitted_root"]]
        symbols = re.findall(r"^  ([A-Za-z_]\w*)$", self.cmake, re.MULTILINE)
        self.assertEqual(self.data["summary"]["emitted_named_roots"], len(symbols))
        self.assertEqual(sorted(row["link_symbol"] for row in emitted), symbols)
        self.assertEqual(len(symbols), len(set(symbols)))
        self.assertNotRegex(self.cmake, r"0x[0-9a-fA-F]+")
        for row in emitted:
            self.assertEqual("retained_reconstruction", row["source_ownership"]["kind"])
            self.assertTrue((ROOT / row["source_ownership"]["exact_source"]).is_file())

    def test_duplicate_live_owners_are_report_only(self):
        ambiguous = {row["current_symbol"]: row for row in self.data["entries"]
                     if row["resolution"] == "ambiguous_live_owner_rejected"}
        self.assertEqual({"convert_to_id_on_match", "mutex_init"}, set(ambiguous))
        self.assertTrue(all(not row["emitted_root"] for row in ambiguous.values()))

    def test_classified_stock_alias_examples(self):
        by_va = {row["original_va"]: row for row in self.data["entries"]}
        self.assertEqual("uarte_nrfx_isr_int", by_va["0x0006312c"]["upstream_alias"])
        self.assertEqual("nrfx_gpiote_irq_handler", by_va["0x00065b9c"]["upstream_alias"])
        self.assertEqual("qspi_nor_init", by_va["0x00060c00"]["upstream_alias"])
        self.assertEqual("sw_isr_entry",
                         by_va["0x0006312c"]["pointer_occurrences"][0]["class"])
        self.assertEqual("init_entry",
                         by_va["0x00060c00"]["pointer_occurrences"][0]["class"])

    def test_cmake_has_no_broad_retention_or_numeric_forcing(self):
        app_cmake = (ROOT / "recon/application/app/CMakeLists.txt").read_text()
        self.assertIn("app_address_taken_roots.cmake", app_cmake)
        self.assertRegex(app_cmake, r"option\(G1_ENABLE_ADDRESS_TAKEN_ROOTS[\s\S]*?OFF\)")
        self.assertRegex(app_cmake, r"option\(G1_ENABLE_FIXED_VERIFIED_RODATA[\s\S]*?OFF\)")
        self.assertNotIn("--no-gc-sections", self.cmake)
        self.assertNotIn("KEEP(", self.cmake)
        self.assertNotRegex(self.cmake, r"--undefined=0x")

    def test_measured_build_is_isolated_and_fail_closed(self):
        receipt = json.loads(
            (ROOT / "recon/analysis/app_address_taken_root_build.json").read_text())
        self.assertTrue(receipt["baseline"]["config"]["normal_gc"])
        self.assertFalse(receipt["baseline"]["config"]["address_taken_roots"])
        self.assertFalse(receipt["rooted"]["config"]["fixed_verified_rodata"])
        self.assertTrue(receipt["rooted"]["config"]["address_taken_roots"])
        self.assertTrue(receipt["roots"]["all_present"])
        self.assertEqual([], receipt["baseline"]["undefined_symbols"])
        self.assertEqual([], receipt["rooted"]["undefined_symbols"])
        self.assertEqual("blocked_overlap", receipt["fixed_placement_gate"]["status"])


if __name__ == "__main__":
    unittest.main()
