#!/usr/bin/env python3
"""Canonical source and CFG gates for COLLISION-21 namespace isolation."""

import json
import re
import sys
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import cfg_verify
import recon_kit


ACQUIRE = "g1_recon_retarget_lock_acquire_recursive"
RELEASE = "g1_recon_retarget_lock_release_recursive"
HOOKS = {
    "0x000510fc": ("FUN_000510fc", ACQUIRE),
    "0x00051134": ("FUN_00051134", RELEASE),
}
DIRECT_CLOSURE = {
    "FUN_00076ad0": (1, 1),
    "FUN_00076b9c": (1, 0),
    "FUN_00076ba8": (0, 1),
    "FUN_00076bb4": (1, 0),
    "__sinit_lock_release": (0, 1),
    "FUN_00076ed4": (1, 2),
    "FUN_00077820": (1, 1),
    "FUN_000785bc": (1, 0),
    "FUN_000785c8": (0, 1),
}
ALL_SOURCES = tuple(raw for raw, _ in HOOKS.values()) + tuple(DIRECT_CLOSURE)


class RetargetRecursiveNamespaceTest(unittest.TestCase):
    def test_private_names_preserve_bijective_raw_backmaps(self):
        overrides = json.loads(
            (ROOT / "recon/catalogs/function_name_overrides.json").read_text()
        )["app"]
        for address, (raw_name, private_name) in HOOKS.items():
            with self.subTest(address=address):
                row = overrides[address]
                self.assertEqual(private_name, row["name"])
                self.assertEqual(raw_name, row["raw_name"])
                self.assertIn(address, row["evidence"])
                self.assertIn("COLLISION-21", row["evidence"])

    def test_canonical_and_verified_sources_are_identical(self):
        for source_name in ALL_SOURCES:
            canonical = ROOT / "recon/app/src" / (source_name + ".c")
            verified = ROOT / "recon/verified/src" / (source_name + ".c")
            with self.subTest(source=source_name):
                self.assertTrue(canonical.exists())
                self.assertEqual(canonical.read_bytes(), verified.read_bytes())

    def test_hooks_expose_private_source_identity_and_single_lock_abi(self):
        acquire = (ROOT / "recon/app/src/FUN_000510fc.c").read_text()
        release = (ROOT / "recon/app/src/FUN_00051134.c").read_text()
        self.assertIn("#define %s FUN_000510fc" % ACQUIRE, acquire)
        self.assertIn("void %s(uintptr_t lock)" % ACQUIRE, acquire)
        self.assertIn("#define %s FUN_00051134" % RELEASE, release)
        self.assertIn("void %s(uintptr_t lock)" % RELEASE, release)
        self.assertIn("(g1_k_timeout_t){ .ticks = -1 }", acquire)
        self.assertIn("FUN_00072558(lock)", release)
        self.assertNotIn("void __retarget_lock_acquire_recursive", acquire)
        self.assertNotIn("void __retarget_lock_release_recursive", release)

    def test_exact_six_acquire_seven_release_direct_site_closure(self):
        acquire_sites = 0
        release_sites = 0
        call_pattern = r"\b%s\s*\(" 
        for source_name, expected in DIRECT_CLOSURE.items():
            text = (ROOT / "recon/app/src" / (source_name + ".c")).read_text()
            # Extern declarations contain the same token; count only calls in
            # the body after the last declaration semicolon.
            acquire = len(re.findall(call_pattern % ACQUIRE, text)) - (
                1 if "extern void %s" % ACQUIRE in text else 0)
            release = len(re.findall(call_pattern % RELEASE, text)) - (
                1 if "extern void %s" % RELEASE in text else 0)
            with self.subTest(source=source_name):
                self.assertEqual(expected, (acquire, release))
                self.assertNotIn("__retarget_lock_acquire_recursive(", text)
                self.assertNotIn("__retarget_lock_release_recursive(", text)
            acquire_sites += acquire
            release_sites += release
        self.assertEqual((6, 7), (acquire_sites, release_sites))

    def test_true_extents_exclude_assertion_literal_pools(self):
        self.assertEqual(0x2c, cfg_verify.TRUE_SIZE_OVERRIDES[("app", 0x510fc)])
        self.assertEqual(0x24, cfg_verify.TRUE_SIZE_OVERRIDES[("app", 0x51134)])
        self.assertEqual(0x2c, recon_kit.TRUE_SIZE_OVERRIDES[0x510fc])
        self.assertEqual(0x24, recon_kit.TRUE_SIZE_OVERRIDES[0x51134])

    def test_hooks_and_complete_direct_closure_cfg_pass(self):
        for source_name in tuple(raw for raw, _ in HOOKS.values()) + tuple(DIRECT_CLOSURE):
            with self.subTest(source=source_name):
                verdict = cfg_verify.verify("app", source_name, trials_random=1)
                self.assertEqual("PASS", verdict.get("status"), verdict)
                self.assertGreater(verdict.get("checked", 0), 0, verdict)

    def test_assertions_and_private_target_identity_are_required(self):
        for raw_name in ("FUN_000510fc", "FUN_00051134"):
            path = ROOT / "recon/app/src" / (raw_name + ".c")
            source = path.read_text()
            mutated = source.replace("if (lock == 0u)", "if (0)", 1)
            verdict = cfg_verify.verify(
                "app", raw_name, trials_random=0, source_override=mutated)
            self.assertEqual("FAIL", verdict.get("status"), verdict)

        acquire = (ROOT / "recon/app/src/FUN_00076b9c.c").read_text()
        acquire = acquire.replace(
            "#define %s FUN_000510fc" % ACQUIRE,
            "#define %s FUN_00051134" % ACQUIRE, 1)
        verdict = cfg_verify.verify(
            "app", "FUN_00076b9c", trials_random=1, source_override=acquire)
        self.assertEqual("FAIL", verdict.get("status"), verdict)

        release = (ROOT / "recon/app/src/FUN_00076ba8.c").read_text()
        release = release.replace(
            "#define %s FUN_00051134" % RELEASE,
            "#define %s FUN_000510fc" % RELEASE, 1)
        verdict = cfg_verify.verify(
            "app", "FUN_00076ba8", trials_random=1, source_override=release)
        self.assertEqual("FAIL", verdict.get("status"), verdict)


if __name__ == "__main__":
    unittest.main()
