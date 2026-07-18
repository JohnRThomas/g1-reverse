#!/usr/bin/env python3
"""Regression gates for the three Ghidra-missed CPUAPP thread entries."""

import hashlib
import json
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import extract


class AppMissingThreadRootsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads((ROOT / "recon/ownership/app_missing_thread_roots_recovery.json").read_text())
        cls.names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        cls.roots = json.loads((ROOT / "recon/catalogs/app_gc_roots.json").read_text())

    def test_exact_firmware_extents(self):
        for row in self.receipt["entries"]:
            address = int(row["address"], 16)
            body = extract.read(address, row["extent"])
            self.assertEqual(row["entry_bytes"], body[:8].hex())
            self.assertEqual(row["firmware_sha256"], hashlib.sha256(body).hexdigest())

    def test_durable_readable_backmaps(self):
        for row in self.receipt["entries"]:
            record = self.names["by_address"][row["address"]]
            self.assertEqual(row["name"], record["name"])
            self.assertTrue((ROOT / row["source"]).is_file())

    def test_complete_named_gc_graph(self):
        self.assertTrue(self.receipt["summary"]["complete_root_graph"])
        self.assertTrue(self.roots["summary"]["complete_root_graph"])
        self.assertEqual([], self.roots["unresolved_addresses"])
        resolved = {row["address"]: row["symbol"] for row in self.roots["roots"]
                    if row["resolved"]}
        for row in self.receipt["entries"]:
            self.assertEqual(row["name"], resolved[row["address"]])


if __name__ == "__main__":
    unittest.main()
