#!/usr/bin/env python3
"""Focused fail-closed gates for retained CPUNET link-gap recovery."""

from __future__ import annotations

import hashlib
import json
import unittest
from pathlib import Path

import build_net_link_gap2_recovery_receipt as builder
import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/analysis/net_link_gap2_recovery_receipt.json"


class NetLinkGap2RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_replays_authoritative_proofs(self) -> None:
        self.assertEqual(self.receipt, builder.build_receipt())
        self.assertEqual(4, self.receipt["summary"]["function_count"])
        self.assertEqual(4, self.receipt["summary"]["cfg_pass_count"])
        self.assertEqual(0xA0, self.receipt["summary"]["total_true_executable_extent"])
        for proof in self.receipt["proofs"]:
            self.assertEqual("PASS", proof["cfg_result"]["status"])
            self.assertGreater(proof["cfg_result"]["checked"], 0)

    def test_sources_and_firmware_extents_are_hash_locked(self) -> None:
        image = (ROOT / "netcore_image.bin").read_bytes()
        for proof in self.receipt["proofs"]:
            source = ROOT / proof["source_path"]
            self.assertEqual(
                hashlib.sha256(source.read_bytes()).hexdigest(),
                proof["source_sha256"],
            )
            va = int(proof["analysis_address"], 16)
            extent = proof["true_executable_extent"]
            firmware = image[va - 0x01008000:va - 0x01008000 + extent]
            self.assertEqual(
                hashlib.sha256(firmware).hexdigest(),
                proof["firmware_extent_sha256"],
            )

    def test_true_extent_repairs_truncated_default_call(self) -> None:
        proof = next(
            row for row in self.receipt["proofs"]
            if row["analysis_address"] == "0x01016250"
        )
        self.assertEqual(0x1C, proof["catalog_executable_extent"])
        self.assertEqual(0x20, proof["true_executable_extent"])
        self.assertTrue(proof["catalog_size_injected_at_runtime"])
        self.assertEqual({"0": [0, 1, 2, 3, 4]}, proof["cfg_result"]["selectors"])

    def test_readable_bodies_preserve_raw_backmaps(self) -> None:
        for proof in self.receipt["proofs"]:
            source = (ROOT / proof["source_path"]).read_text()
            first_lines = "\n".join(source.splitlines()[:5])
            self.assertIn(proof["analysis_address"], first_lines)
            self.assertIn(proof["readable_identity"], first_lines)
            self.assertIn(proof["raw_symbol"], source)
            self.assertNotIn(".incbin", source)
            self.assertNotIn("__attribute__((naked))", source)

    def test_clamp_mutation_is_rejected(self) -> None:
        builder.install_reviewed_cases()
        source = (ROOT / "recon/net/src/FUN_01013d90.c").read_text()
        mutated = source.replace("duration = 0xa90u;", "duration = 0xa8fu;")
        result = cfg_verify.verify(
            "net", "FUN_01013d90", trials_random=1, source_override=mutated
        )
        self.assertEqual("FAIL", result["status"])

    def test_sdc_remains_retained_report_only(self) -> None:
        self.assertEqual({
            "canonical_c_only": True,
            "blobs_used": False,
            "archive_substitution_used": False,
            "sdc_retained_report_only": True,
            "shared_cfg_tool_modified": False,
        }, self.receipt["policy"])


if __name__ == "__main__":
    unittest.main()
