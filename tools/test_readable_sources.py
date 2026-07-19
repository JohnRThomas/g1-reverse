#!/usr/bin/env python3
"""Regression tests for the generated fully named CPUAPP tree."""

from __future__ import annotations

import importlib.util
import json
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILDER = ROOT / "tools" / "build_readable_sources.py"
OUTPUT = ROOT / "recon" / "readable_sources" / "app"
CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")


def load_builder():
    spec = importlib.util.spec_from_file_location("g1_build_readable_sources", BUILDER)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class ReadableSourceTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.builder = load_builder()
        cls.manifest = json.loads((OUTPUT / "manifest.json").read_text())

    def test_complete_named_inventory(self):
        summary = self.manifest["summary"]
        self.assertEqual(summary["sources"], 2115)
        self.assertEqual(summary["g1_sources"], 1156)
        self.assertEqual(summary["library_sources"], 959)
        self.assertEqual(summary["recovered_layouts"], 676)
        self.assertEqual(summary["raw_function_filenames"], 0)
        self.assertEqual(summary["support_files"], 6)
        self.assertEqual(summary["layout_bindings_attached"], 891)
        self.assertEqual(summary["layout_bindings_without_body"], 175)
        outputs = [ROOT / row["output"] for row in self.manifest["sources"]]
        self.assertEqual(len(outputs), len(set(outputs)))
        self.assertTrue(all(path.is_file() for path in outputs))
        self.assertFalse(any(path.name.startswith("FUN_") for path in outputs))

    def test_code_has_no_raw_function_tokens(self):
        for row in self.manifest["sources"]:
            text = (ROOT / row["output"]).read_text(errors="replace")
            self.assertFalse(
                self.builder.RAW_FUNCTION.search(self.builder.code_only(text)),
                row["output"],
            )
            self.assertFalse(
                self.builder.RAW_ADDRESS_SYMBOL.search(self.builder.code_only(text)),
                row["output"],
            )

    def test_all_structs_are_bound_and_declared(self):
        header = (OUTPUT / "include" / "g1_recovered_layouts.h").read_text()
        catalog = json.loads((ROOT / "recon/structs/struct_catalog_app.json").read_text())["structs"]
        for row in catalog:
            self.assertIn("struct " + self.builder.layout_type(row), header)
        self.assertEqual(
            sum(len(row["structure_bindings"]) for row in self.manifest["sources"]) +
            len(self.manifest["unattached_structure_bindings"]),
            sum(len(row["members"]) for row in catalog),
        )

    def test_layout_header_compiles(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / "check.c"
            source.write_text('#include "g1_recovered_layouts.h"\nint main(void) { return 0; }\n')
            result = subprocess.run(
                [str(CC), "-fsyntax-only", "-std=gnu11", "-mcpu=cortex-m33", "-mthumb",
                 "-I" + str(OUTPUT / "include"), str(source)],
                capture_output=True,
                text=True,
            )
            self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
