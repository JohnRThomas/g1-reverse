#!/usr/bin/env python3
"""Focused integrity checks for the net-private-3 reconstruction receipt."""

from __future__ import annotations

import hashlib
import json
import re
import unittest
from pathlib import Path


BASE = Path(__file__).resolve().parents[1]
RECEIPT = BASE / "recon/analysis/net_private3_recovery_receipt.json"
WORKLIST = BASE / "recon/catalogs/net_private_recovery_worklist.json"


class NetPrivate3RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.worklist = json.loads(WORKLIST.read_text())

    def test_complete_dependency_closed_shard(self) -> None:
        shard = next(
            item for item in self.worklist["shards"]
            if item["id"] == "net-private-3"
        )
        self.assertEqual(
            [item["analysis_address"] for item in self.receipt["proofs"]],
            shard["addresses"],
        )
        self.assertEqual(self.receipt["summary"]["function_count"], 13)
        self.assertEqual(
            self.receipt["summary"]["total_true_executable_extent"], 1000
        )

    def test_all_cfg_proofs_pass_and_sources_match(self) -> None:
        for proof in self.receipt["proofs"]:
            with self.subTest(address=proof["analysis_address"]):
                source = BASE / proof["source_path"]
                digest = hashlib.sha256(source.read_bytes()).hexdigest()
                self.assertEqual(digest, proof["source_sha256"])
                first = source.read_text().splitlines()[0]
                match = re.search(r"@\s+(0x[0-9a-fA-F]+)", first)
                self.assertIsNotNone(match)
                self.assertEqual(int(match.group(1), 16), int(proof["analysis_address"], 16))
                self.assertEqual(proof["cfg_result"]["status"], "PASS")
                self.assertGreater(proof["cfg_result"]["checked"], 0)

    def test_no_blob_or_archive_substitution(self) -> None:
        self.assertEqual(
            self.receipt["policy"],
            {
                "archive_substitution_used": False,
                "blobs_used": False,
                "canonical_c_only": True,
                "shared_cfg_tool_modified": False,
            },
        )


if __name__ == "__main__":
    unittest.main()
