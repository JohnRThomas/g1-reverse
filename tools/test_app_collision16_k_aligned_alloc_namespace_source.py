#!/usr/bin/env python3
"""Canonical-only namespace guards for COLLISION-16."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
OWNER = "g1_recon_k_aligned_alloc_asserting"


@unittest.skip("superseded by the public exact-owner adoption")
class KAlignedAllocNamespaceSourceTest(unittest.TestCase):
    def test_owner_canonical_and_verified_are_identical_and_namespaced(self):
        canonical = ROOT / "recon/app/src/FUN_000758cc.c"
        verified = ROOT / "recon/verified/src/FUN_000758cc.c"
        self.assertEqual(canonical.read_bytes(), verified.read_bytes())
        text = canonical.read_text()
        self.assertIn("Raw backmap: FUN_000758cc@0x000758cc", text)
        self.assertIn("void *" + OWNER + "(size_t alignment, size_t size)", text)
        self.assertNotIn("void *k_aligned_alloc(", text)
        self.assertIn("0x200037d8u", text)

    def test_sole_caller_uses_namespace_and_preserves_raw_owner_backmap(self):
        canonical = ROOT / "recon/app/src/FUN_000868c2.c"
        verified = ROOT / "recon/verified/src/FUN_000868c2.c"
        self.assertEqual(canonical.read_bytes(), verified.read_bytes())
        text = canonical.read_text()
        self.assertIn("void *malloc_impl(size_t size)", text)
        self.assertIn("FUN_000868c2@0x000868c2", text)
        self.assertIn(OWNER + "(4u, size)", text)
        self.assertIn("FUN_000758cc@0x000758cc", text)
        self.assertNotIn("return FUN_000758cc", text)

    def test_durable_override_is_namespaced_with_raw_identity(self):
        overrides = json.loads((ROOT /
            "recon/catalogs/function_name_overrides.json").read_text())
        row = overrides["app"]["0x000758cc"]
        self.assertEqual(OWNER, row["name"])
        self.assertEqual("FUN_000758cc", row["raw_name"])
        self.assertIn("assertion/logging", row["evidence"])

    def test_cfg_and_reconstruction_extents_remain_reviewed(self):
        cfg = (ROOT / "tools/cfg_verify.py").read_text()
        recon = (ROOT / "tools/recon_kit.py").read_text()
        marker = "0x000758cc): 0x4e,  # " + OWNER
        self.assertIn(marker, cfg)
        self.assertIn("0x000758cc: 0x4e,  # " + OWNER, recon)


if __name__ == "__main__":
    unittest.main()
