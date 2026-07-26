"""The write guard is the mechanism that makes R1 structural rather than a
convention, so it gets a test that fails loudly if anyone widens it.

    PYTHONSAFEPATH=1 .venv/bin/python -m unittest discover -s recon/refactor -p 'test_*.py'
"""

import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import guard  # noqa: E402


class TestProtectedTrees(unittest.TestCase):
    CANONICAL = [
        "recon/app/src/FUN_00010fc8.c",
        "recon/app/src_sym/FUN_00010fc8.c",
        "recon/net/src/FUN_0102a720.c",
        "recon/verified/src/FUN_00010fc8.c",
        "recon/verified/src_sym/FUN_00010fc8.c",
        "recon/data/rodata_0x88570.c",
        "recon/net/data/anything.c",
        "recon/emulator/scripts/capture_display_sensor_oracle.sh",
        "tools/cfg_verify.py",
    ]

    def test_protected_paths_are_recognised(self):
        for rel in self.CANONICAL:
            with self.subTest(rel=rel):
                self.assertTrue(guard.is_protected(os.path.join(guard.REPO_ROOT, rel)))

    def test_unprotected_paths_are_not(self):
        for rel in ("recon/symbolized/app/get_lux_info.c",
                    "recon/symbols/g1_app_globals.ld",
                    "recon/application/app/src/g1_app_string_rodata.c",
                    "recon/refactor/stage_01_literal_inline/tree/recon/symbolized/app/x.c"):
            with self.subTest(rel=rel):
                self.assertFalse(guard.is_protected(os.path.join(guard.REPO_ROOT, rel)))

    def test_write_into_canonical_is_refused(self):
        stage = os.path.join(guard.REFACTOR_ROOT, "stage_99_probe")
        for rel in self.CANONICAL:
            with self.subTest(rel=rel):
                with self.assertRaises(guard.WriteGuardError):
                    guard.check_write(os.path.join(guard.REPO_ROOT, rel), stage)

    def test_write_outside_the_stage_is_refused(self):
        stage = os.path.join(guard.REFACTOR_ROOT, "stage_99_probe")
        for rel in ("recon/symbolized/app/get_lux_info.c",
                    "recon/symbols/g1_app_globals.ld",
                    "recon/refactor/stage_00_snapshot/tree/recon/symbolized/app/x.c",
                    "recon/refactor/README.md"):
            with self.subTest(rel=rel):
                with self.assertRaises(guard.WriteGuardError):
                    guard.check_write(os.path.join(guard.REPO_ROOT, rel), stage)

    def test_traversal_out_of_the_stage_is_refused(self):
        stage = os.path.join(guard.REFACTOR_ROOT, "stage_99_probe")
        sneaky = os.path.join(stage, "tree", "..", "..", "..",
                              "app", "src", "FUN_00010fc8.c")
        with self.assertRaises(guard.WriteGuardError):
            guard.check_write(sneaky, stage)

    def test_write_inside_the_stage_is_allowed(self):
        with tempfile.TemporaryDirectory(dir=guard.REFACTOR_ROOT) as stage:
            p = guard.guarded_write_text(
                os.path.join(stage, "tree", "recon", "symbolized", "app", "x.c"),
                stage, "int x;\n")
            self.assertTrue(os.path.exists(p))


class TestStageIsolation(unittest.TestCase):
    def test_a_stage_cannot_write_into_a_sibling_stage(self):
        a = os.path.join(guard.REFACTOR_ROOT, "stage_00_snapshot")
        b = os.path.join(guard.REFACTOR_ROOT, "stage_01_literal_inline")
        with self.assertRaises(guard.WriteGuardError):
            guard.check_write(os.path.join(b, "tree", "x.c"), a)


if __name__ == "__main__":
    unittest.main()
