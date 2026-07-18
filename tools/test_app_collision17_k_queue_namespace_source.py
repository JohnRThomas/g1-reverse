#!/usr/bin/env python3
"""Canonical source/back-map checks for COLLISION-17 implementation."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RAW = "FUN_000864e8"
READABLE = "g1_recon_z_impl_k_queue_init"
CALLERS = (
    "FUN_000526f4", "FUN_00052760", "FUN_00054a44",
    "FUN_00056704", "FUN_00057358", "FUN_000574ec",
    "FUN_00057874", "FUN_000579d0", "FUN_00058930",
    "FUN_00059690",
)


@unittest.skip("superseded by the public exact-owner adoption")
class AppCollision17QueueNamespaceSourceTest(unittest.TestCase):
    def test_durable_name_preserves_raw_address_backmap(self):
        overrides = json.loads((ROOT /
            "recon/catalogs/function_name_overrides.json").read_text())["app"]
        row = overrides["0x000864e8"]
        self.assertEqual(READABLE, row["name"])
        self.assertEqual(RAW, row["raw_name"])
        self.assertIn("28-byte", row["evidence"])
        self.assertIn("0x000864e8", row["evidence"])

    def test_owner_and_all_caller_mirrors_are_exact(self):
        for raw_name in (*CALLERS, RAW):
            canonical = ROOT / "recon/app/src" / f"{raw_name}.c"
            mirror = ROOT / "recon/verified/src" / f"{raw_name}.c"
            with self.subTest(raw_name=raw_name):
                self.assertEqual(canonical.read_bytes(), mirror.read_bytes())

    def test_exact_eleven_sites_use_readable_unary_owner(self):
        total = 0
        macro = f"#define {READABLE} {RAW}"
        for raw_name in CALLERS:
            source = (ROOT / "recon/app/src" / f"{raw_name}.c").read_text()
            with self.subTest(raw_name=raw_name):
                self.assertIn(macro, source)
                self.assertIn(f"extern void {READABLE}", source)
                self.assertNotIn(f"extern void {RAW}", source)
                self.assertNotIn(f"extern int {RAW}", source)
                calls = source.count(f"{READABLE}(") - 1  # extern declaration
                self.assertGreaterEqual(calls, 1)
                total += calls
        self.assertEqual(11, total)

    def test_owner_emits_raw_symbol_with_readable_body(self):
        owner = (ROOT / f"recon/app/src/{RAW}.c").read_text()
        self.assertIn(f"#define {READABLE} {RAW}", owner)
        self.assertIn(f"void {READABLE}(int *param_1)", owner)
        self.assertIn("four-byte spinlock at +8", owner)
        self.assertEqual(7, owner.count("*(volatile unsigned int *)"))

    def test_cfg_and_reconstruction_extent_arity_are_pinned(self):
        cfg = (ROOT / "tools/cfg_verify.py").read_text()
        recon = (ROOT / "tools/recon_kit.py").read_text()
        self.assertIn('(\"app\", 0x000864e8): 1', cfg)
        self.assertIn('(\"app\", 0x000864e8): 0x1a', cfg)
        self.assertIn('0x000864e8: 0x1a', recon)
        for caller in CALLERS:
            address = "0x" + caller.removeprefix("FUN_")
            self.assertIn(address, cfg)


if __name__ == "__main__":
    unittest.main()
