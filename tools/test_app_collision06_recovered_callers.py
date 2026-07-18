#!/usr/bin/env python3
"""Authoritative closure tests for COLLISION-06 recovered callers."""

import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import cfg_verify


class AppCollision06RecoveredCallersTest(unittest.TestCase):
    def test_canonical_and_verified_mirrors_are_identical(self):
        for symbol in ("FUN_0006125c", "FUN_00061310"):
            canonical = ROOT / "recon/app/src" / (symbol + ".c")
            mirror = ROOT / "recon/verified/src" / (symbol + ".c")
            self.assertEqual(canonical.read_bytes(), mirror.read_bytes())

    def test_erase_caller_has_complete_reviewed_cfg_coverage(self):
        verdict = cfg_verify.verify("app", "FUN_0006125c", trials_random=0)
        self.assertEqual(verdict.get("status"), "PASS", verdict)
        self.assertEqual(verdict.get("cover_cases"), 4, verdict)

    def test_word_write_caller_has_complete_reviewed_cfg_coverage(self):
        verdict = cfg_verify.verify("app", "FUN_00061310", trials_random=0)
        self.assertEqual(verdict.get("status"), "PASS", verdict)
        self.assertEqual(verdict.get("cover_cases"), 4, verdict)

    def test_erase_target_identity_is_required(self):
        path = ROOT / "recon/app/src/FUN_0006125c.c"
        source = path.read_text()
        mutated = source.replace("FUN_00065f1c(address);",
                                 "FUN_00072880(address);", 1)
        verdict = cfg_verify.verify("app", "FUN_0006125c", trials_random=0,
                                    source_override=mutated)
        self.assertEqual(verdict.get("status"), "FAIL", verdict)

    def test_word_write_target_identity_is_required(self):
        path = ROOT / "recon/app/src/FUN_00061310.c"
        source = path.read_text()
        mutated = source.replace(
            "FUN_00065f80(address + offset, source[offset / 4]);",
            "FUN_00072880(address + offset);", 1)
        verdict = cfg_verify.verify("app", "FUN_00061310", trials_random=0,
                                    source_override=mutated)
        self.assertEqual(verdict.get("status"), "FAIL", verdict)


if __name__ == "__main__":
    unittest.main()
