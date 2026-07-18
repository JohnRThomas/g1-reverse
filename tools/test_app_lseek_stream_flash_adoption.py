#!/usr/bin/env python3
"""Fail-closed gates for fdtable and progressive stream-flash adoption."""

import importlib.util
import json
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_lseek_stream_flash_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
SPEC = importlib.util.spec_from_file_location(
    "build_app_lseek_stream_flash_adoption",
    ROOT / "tools/build_app_lseek_stream_flash_adoption.py")
builder = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(builder)


class AppLseekStreamFlashAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.rows = {row["va"]: row for row in cls.receipt["authorizations"]}
        manifest = json.loads(MANIFEST.read_text())
        cls.manifest = {row["va"]: row for row in manifest["cores"]["app"]["entries"]}

    def test_receipt_is_deterministic_and_exact(self):
        self.assertEqual(self.receipt, builder.build())
        expected = set(builder.FDTABLE_GROUP + builder.FLASH_GROUP)
        self.assertEqual(expected, set(self.rows))
        for row in self.rows.values():
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["configuration_variant_exact"])
            self.assertGreater(row["cfg_verify_cases"], 0)
            self.assertEqual(row["upstream_symbol_size"],
                             row["firmware_code_size"] + row["literal_pool_tail_size"])
            self.assertTrue(row["whole_unit_closure"]["raw_aliases_preserved"])

    def test_atomic_groups_are_complete(self):
        for va in builder.FDTABLE_GROUP:
            self.assertEqual(set(builder.FDTABLE_GROUP),
                             set(self.rows[va]["atomic_group"]))
        for va in builder.FLASH_GROUP:
            row = self.rows[va]
            self.assertEqual(set(builder.FLASH_GROUP), set(row["atomic_group"]))
            self.assertEqual(set(builder.FLASH_GROUP),
                             set(row["whole_unit_closure"]["exclude_only"]))
        self.assertEqual({"0x0004b130", "0x0004e0f8", "0x0007f070"},
                         {row["va"] for row in self.receipt["hidden_exact_source_sections"]})

    def test_fdtable_data_layout_and_owner_are_exact(self):
        table = self.receipt["stock_data_objects"]["fdtable"]
        self.assertEqual("0x20002548", table["firmware_address"])
        self.assertEqual((16, 0x28, 0x280),
                         (table["entry_count"], table["entry_size"],
                          table["size"]))
        self.assertEqual({"g_fdtable_entries": 0,
                          "g_fdtable_refcount_field": 8},
                         table["field_aliases"])
        state = (ROOT / "recon/symbols/g1_app_sdk_state.ld").read_text()
        self.assertIn("g_fdtable_entries = fdtable;", state)
        self.assertIn("g_fdtable_refcount_field = fdtable + 8;", state)
        cmake = (ROOT / "recon/application/app/CMakeLists.txt").read_text()
        self.assertIn("--globalize-symbol=fdtable", cmake)

    def test_cohesive_probe_has_one_shared_stock_owner(self):
        probe = self.receipt["cohesive_link_probe"]
        self.assertEqual(0x330, probe["remaining_section_layout_delta"])
        self.assertEqual("pending_whole_image_section_convergence",
                         probe["absolute_placement_status"])
        nm = "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm"
        symbols = subprocess.check_output(
            [nm, "-a", "-S", probe["elf"]], text=True)
        rows = [line.split() for line in symbols.splitlines()]
        by_name = {row[-1]: row for row in rows if row}
        self.assertEqual("20002218", by_name["fdtable"][0])
        self.assertEqual(by_name["fdtable"][0],
                         by_name["g_fdtable_entries"][0])
        self.assertEqual("20002220", by_name["g_fdtable_refcount_field"][0])
        for displaced in ("fd_table_lookup", "fdtable_entry_unref",
                          "fd_table_dispatch_op1", "fd_table_dispatch_op2"):
            self.assertNotIn(displaced, by_name)

    def test_config_and_source_units_are_pinned(self):
        self.assertEqual({"CONFIG_IMG_ERASE_PROGRESSIVELY": "y"},
                         self.receipt["required_project_config"])
        sources = {row["upstream_source"] for row in self.rows.values()}
        self.assertEqual({
            "zephyr/lib/os/fdtable.c",
            "zephyr/subsys/storage/stream/stream_flash.c",
            "zephyr/subsys/dfu/img_util/flash_img.c",
        }, sources)
        for row in self.rows.values():
            if row["va"] not in builder.FDTABLE_GROUP:
                self.assertEqual("y", row["required_config"][
                    "CONFIG_IMG_ERASE_PROGRESSIVELY"])
                self.assertEqual("y", row["required_config"][
                    "CONFIG_STREAM_FLASH_ERASE"])

    def test_manifest_and_retained_list_apply_exact_exclusions(self):
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(self.manifest[va]["exclude_reconstruction"], va)
            source_name = Path(row["reconstruction_source"]).name
            raw = row["raw_symbol"]
            current = self.manifest[va]["current_symbol"]
            self.assertNotIn("/" + source_name, retained)
            self.assertNotIn("/" + raw + ".c", retained)
            self.assertNotIn("/" + current + ".c", retained)
        self.assertIn("/serialization_copy_fields_0c_10.c", retained)

    def test_external_caller_uses_stock_public_flash_img_api(self):
        names = json.loads((ROOT /
            "recon/catalogs/function_names_app.json").read_text())
        caller_name = names["by_address"]["0x00051870"]["name"]
        source = (ROOT / "recon/symbolized/app" /
                  (caller_name + ".c")).read_text()
        self.assertIn("flash_img_init_id", source)
        self.assertIn("flash_img_buffered_write", source)
        self.assertNotIn("extern int FUN_0007f150", source)
        self.assertNotIn("extern int FUN_0007f110", source)
        self.assertIn("FUN_0007f150 @ 0x0007f150", source)
        self.assertIn("FUN_0007f110 @ 0x0007f110", source)

    def test_dead_helpers_and_sdc_policy_remain_fail_closed(self):
        self.assertEqual({"stream_flash_bytes_written", "flash_img_bytes_written",
                          "flash_img_init"},
                         set(self.receipt["dead_sdk_helpers_must_gc"]))
        self.assertEqual("retained_unchanged", self.receipt["pthread_attr_getstack"])
        self.assertEqual("report_only_unchanged", self.receipt["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
