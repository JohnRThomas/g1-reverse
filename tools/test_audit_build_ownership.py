#!/usr/bin/env python3
"""Fixture tests for audit_build_ownership.py."""

import json
import os
import sys
import tempfile
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parent
sys.path.insert(0, str(TOOLS))
import audit_build_ownership as ownership


def entry(va, raw, current, upstream, unit, kind="source"):
    return {"core": "app", "va": va, "raw_symbol": raw,
            "current_symbol": current, "upstream_symbol": upstream,
            "upstream_unit": unit, "kind": kind, "component": "fixture",
            "exclude_reconstruction": True,
            "decision": "adopt_upstream_exclude_reconstruction", "evidence": [{}]}


class OwnershipAuditTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        root = Path(self.temp.name)
        self.root = root
        self.manifest = {"cores": {"app": {"entries": [
            entry("0x00001000", "FUN_00001000", "tc_aes", "tc_aes", "aes.c.obj"),
            entry("0x00002000", "FUN_00002000", "cc_init", "cc_init", "right.o", "archive"),
            entry("0x00003000", "FUN_00003000", "missing", "missing", "missing.c"),
        ]}, "net": {"entries": []}}}
        (root / "compile_commands.json").write_text(json.dumps([
            {"directory": str(root), "file": str(root / "recon/app/src/aes.c"),
             "arguments": ["cc", "-c", "a.c", "-o", "recon.o"]},
            {"directory": str(root), "file": "/ncs/modules/crypto/aes.c",
             "arguments": ["cc", "-c", "a.c", "-o", "upstream.o"]},
        ]))
        (root / "symbols.nm").write_text(
            "%s/recon.o:00001000 00000010 T tc_aes\n"
            "%s/upstream.o:00002000 00000010 T tc_aes\n"
            "/sdk/libcrypto.a(wrong.o):00003000 00000010 T cc_init\n"
            "%s/recon.o:00004000 00000010 T FUN_00004000\n"
            "%s/recon.o: U FUN_00009999\n" % (root, root, root, root))

    def tearDown(self):
        self.temp.cleanup()

    def test_collisions_missing_wrong_owner_and_raw_residue(self):
        mapping, warnings = ownership.read_compile_commands(self.root / "compile_commands.json")
        self.assertFalse(warnings)
        defs, undef = ownership.parse_nm((self.root / "symbols.nm").read_text(), mapping, "fixture")
        report = ownership.audit(self.manifest, "app", defs, undef, True)
        self.assertEqual(report["status"], "fail")
        self.assertEqual(report["summary"]["collisions"], 1)
        self.assertEqual(report["summary"]["excluded_reconstructions_present"], 1)
        self.assertEqual(report["summary"]["excluded_owners_missing"], 1)
        self.assertEqual(report["summary"]["wrong_owners"], 1)
        self.assertEqual(report["raw_undefined_symbols"], ["FUN_00009999"])
        self.assertEqual(report["summary"]["raw_defined_symbols"], 1)

    def test_no_artifacts_is_unavailable_not_failure(self):
        report = ownership.audit(self.manifest, "app", [], set(), False)
        self.assertEqual(report["status"], "unavailable")
        self.assertEqual(report["summary"]["violations"], 0)
        self.assertEqual(report["summary"]["excluded_owners_missing"], 0)

    def test_partial_evidence_does_not_claim_pass(self):
        report = ownership.audit(self.manifest, "app", [], set(), True, False)
        self.assertEqual(report["status"], "partial")
        self.assertFalse(report["evidence_complete"])

    def test_map_parser_retains_archive_member(self):
        text = """ .text.cc_init  0x00001000 0x10 /sdk/lib.a(right.o)\n+                0x00001000 cc_init\n+"""
        defs = ownership.parse_map(text, {}, "fixture.map")
        self.assertTrue(any(item.symbol == "cc_init" and "right.o" in item.origin for item in defs))

    def test_merged_elf_owner_is_inconclusive(self):
        defs, undef = ownership.parse_nm(
            "/build/zephyr.elf:00001000 00000010 T tc_aes\n", {}, "elf")
        report = ownership.audit(self.manifest, "app", defs, undef, True, True)
        row = next(item for item in report["inconclusive_owners"]
                   if item["va"] == "0x00001000")
        self.assertIn("no object provenance", row["reason"])
        self.assertFalse(any(item["va"] == "0x00001000"
                             for item in report["excluded_owners_missing"]))


if __name__ == "__main__":
    unittest.main()
