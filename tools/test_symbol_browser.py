#!/usr/bin/env python3
"""Read-only regression tests for the G1 symbol browser."""

from __future__ import annotations

import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SERVER = ROOT / "tools/symbol_browser/server.py"


def load_server():
    spec = importlib.util.spec_from_file_location("g1_symbol_browser", SERVER)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class SymbolBrowserTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.module = load_server()
        cls.index = cls.module.INDEX

    def test_inventory_tracks_canonical_sources(self):
        meta = self.index.meta()
        for core in ("app", "net"):
            expected = len(list((ROOT / f"recon/{core}/src").glob("*.c")))
            self.assertEqual(meta["cores"][core]["total"], expected)

    def test_application_filter_hides_catalogued_libraries(self):
        manifest = json.loads((ROOT / "recon/application/application_sources.json").read_text())
        summary = manifest["summary"]
        meta = self.index.meta()["cores"]["app"]
        self.assertEqual(meta["application"], summary["included_g1_application"])
        self.assertEqual(meta["library"], summary["excluded_library"])
        visible = self.index.list_symbols("app", "", "all", 1, 10)
        complete = self.index.list_symbols("app", "", "all", 1, 10, False)
        self.assertEqual(visible["total"], summary["included_g1_application"])
        self.assertEqual(complete["total"], summary["total_cpuapp_functions"])
        self.assertEqual(self.index.list_symbols("app", "lc3_encode", "all", 1, 10)["total"], 0)
        self.assertGreater(self.index.list_symbols("app", "lc3_encode", "all", 1, 10, False)["total"], 0)

    def test_goto_by_name_raw_entry_and_interior_address(self):
        result = self.index.list_symbols("app", "", "all", 1, 10)
        record = result["items"][0]
        by_entry = self.index.detail("app", record["address"])
        by_raw = self.index.detail("app", record["raw_name"])
        interior = self.index.detail("app", hex(int(record["address"], 16) + 2))
        self.assertEqual(by_entry["kind"], "function")
        self.assertEqual(by_entry["address"], by_raw["address"])
        self.assertEqual(by_entry["address"], interior["address"])
        self.assertEqual(interior["goto_offset"], 2)

    def test_post_sweep_source_backmaps_resolve(self):
        expected = {
            "ble_work_thread": ("FUN_00021da8", "0x00021da8"),
            "brightness_level": ("FUN_00023844", "0x00023844"),
            "low_speed_peripheral_dispatch_thread": ("FUN_0002a8d8", "0x0002a8d8"),
        }
        for readable, (raw, address) in expected.items():
            self.assertEqual(self.index.detail("app", readable)["address"], address)
            self.assertEqual(self.index.detail("app", raw)["display_name"], readable)
        self.assertEqual(self.index.meta()["cores"]["app"]["unnamed"], 0)

    def test_source_references_are_navigable(self):
        result = self.index.list_symbols("app", "", "all", 1, 100)
        detail = next(self.index.detail("app", row["address"]) for row in result["items"] if self.index.detail("app", row["address"])["data_refs"])
        reference = detail["data_refs"][0]
        target = self.index.detail("app", reference["address"])
        self.assertIsNotNone(target)
        self.assertEqual(target["address"], reference.get("owner_address") or reference["address"])

    def test_verified_struct_catalog_is_searchable_and_linked(self):
        meta = self.index.meta()["structs"]
        self.assertEqual(meta["total"], 676)
        self.assertEqual(meta["g1"], 377)
        self.assertEqual(meta["library"], 299)
        self.assertEqual(meta["verified"], 676)
        self.assertEqual(meta["verification_fail"], 0)
        self.assertEqual((meta["clusters_target"], meta["clusters_covered"]), (684, 684))
        self.assertEqual(self.index.list_structs("", "all", "all", 1, 10)["total"], 676)
        self.assertEqual(self.index.list_structs("", "g1", "all", 1, 10)["total"], 377)
        self.assertEqual(self.index.list_structs("", "library", "header", 1, 100)["total"], 60)

        detail = self.index.struct_detail("settings_store")
        self.assertEqual(detail["cid"], "global_1071")
        self.assertTrue(detail["library_verified"])
        self.assertTrue(detail["verified"])
        self.assertTrue(detail["fields"])
        member = detail["members"][0]
        self.assertTrue(member["resolvable"])
        function = self.index.detail("app", member["address"])
        self.assertIn("global_1071", {row["cid"] for row in function["structs"]})

    def test_active_coordination_lock_refuses_writes(self):
        if not self.index.meta()["coordination_active"]:
            self.skipTest("naming sweep lock already released")
        before = self.module.OVERRIDES.read_bytes()
        record = self.index.list_symbols("app", "", "all", 1, 1)["items"][0]
        with self.assertRaisesRegex(ValueError, "HELD"):
            self.index.apply_rename("app", record["address"], "symbol_browser_test_name", "test")
        self.assertEqual(self.module.OVERRIDES.read_bytes(), before)

    def test_completed_coordination_note_does_not_hold_lock(self):
        coordination = self.module.COORDINATION.read_text()
        if "no locks remain" not in coordination:
            self.skipTest("coordination file currently describes active work")
        self.assertFalse(self.module.coordination_active())

    def test_static_ui_exposes_required_controls(self):
        html = (ROOT / "tools/symbol_browser/static/index.html").read_text()
        css = (ROOT / "tools/symbol_browser/static/styles.css").read_text()
        js = (ROOT / "tools/symbol_browser/static/app.js").read_text()
        self.assertIn("GoToRef", html)
        self.assertIn("Structures", html)
        self.assertIn('id="struct-layout"', html)
        self.assertIn("Rename symbol", html)
        self.assertIn('id="application-only" type="checkbox" checked', html)
        self.assertIn('id="close-rename" type="button"', html)
        self.assertIn('id="cancel-rename" type="button"', html)
        self.assertIn("prefers-reduced-motion", css)
        self.assertIn("data-goto", js)
        self.assertIn("/api/struct/", js)


if __name__ == "__main__":
    unittest.main()
