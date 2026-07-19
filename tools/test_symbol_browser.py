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

    def test_source_references_are_navigable(self):
        result = self.index.list_symbols("app", "", "all", 1, 100)
        detail = next(self.index.detail("app", row["address"]) for row in result["items"] if self.index.detail("app", row["address"])["data_refs"])
        reference = detail["data_refs"][0]
        target = self.index.detail("app", reference["address"])
        self.assertIsNotNone(target)
        self.assertEqual(target["address"], reference.get("owner_address") or reference["address"])

    def test_active_coordination_lock_refuses_writes(self):
        if not self.index.meta()["coordination_active"]:
            self.skipTest("naming sweep lock already released")
        before = self.module.OVERRIDES.read_bytes()
        record = self.index.list_symbols("app", "", "all", 1, 1)["items"][0]
        with self.assertRaisesRegex(ValueError, "HELD"):
            self.index.apply_rename("app", record["address"], "symbol_browser_test_name", "test")
        self.assertEqual(self.module.OVERRIDES.read_bytes(), before)

    def test_static_ui_exposes_required_controls(self):
        html = (ROOT / "tools/symbol_browser/static/index.html").read_text()
        css = (ROOT / "tools/symbol_browser/static/styles.css").read_text()
        js = (ROOT / "tools/symbol_browser/static/app.js").read_text()
        self.assertIn("GoToRef", html)
        self.assertIn("Rename symbol", html)
        self.assertIn('id="application-only" type="checkbox" checked', html)
        self.assertIn('id="close-rename" type="button"', html)
        self.assertIn('id="cancel-rename" type="button"', html)
        self.assertIn("prefers-reduced-motion", css)
        self.assertIn("data-goto", js)


if __name__ == "__main__":
    unittest.main()
