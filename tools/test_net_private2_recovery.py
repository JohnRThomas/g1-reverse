#!/usr/bin/env python3
"""Focused integrity checks for the net-private-2 reconstruction receipt."""

from __future__ import annotations

import hashlib
import json
import re
import unittest
from pathlib import Path


BASE = Path(__file__).resolve().parents[1]
RECEIPT = BASE / "recon/analysis/net_private2_recovery_receipt.json"
WORKLIST = BASE / "recon/catalogs/net_private_recovery_worklist.json"


class NetPrivate2RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.worklist = json.loads(WORKLIST.read_text())

    def test_complete_dependency_closed_shard(self) -> None:
        shard = next(
            item for item in self.worklist["shards"]
            if item["id"] == "net-private-2"
        )
        self.assertEqual(
            [item["analysis_address"] for item in self.receipt["proofs"]],
            shard["addresses"],
        )
        self.assertEqual(self.receipt["summary"]["function_count"], 16)
        self.assertEqual(
            self.receipt["summary"]["total_true_executable_extent"], 2920
        )
        corrected = next(
            item for item in self.receipt["proofs"]
            if item["analysis_address"] == "0x010231c8"
        )
        self.assertEqual(corrected["worklist_executable_extent"], 1474)
        self.assertEqual(corrected["true_executable_extent"], 1500)
        self.assertTrue(corrected["catalog_size_injected_at_runtime"])
        self.assertEqual(len(corrected["reviewed_case_labels"]), 6)
        self.assertEqual(corrected["cfg_result"]["cover_cases"], 6)
        self.assertGreaterEqual(corrected["cfg_result"]["checked"], 5)

    def test_all_cfg_proofs_pass_and_sources_match(self) -> None:
        for proof in self.receipt["proofs"]:
            with self.subTest(address=proof["analysis_address"]):
                source = BASE / proof["source_path"]
                self.assertEqual(
                    hashlib.sha256(source.read_bytes()).hexdigest(),
                    proof["source_sha256"],
                )
                first = source.read_text().splitlines()[0]
                match = re.search(r"@\s+(0x[0-9a-fA-F]+)", first)
                self.assertIsNotNone(match)
                self.assertEqual(
                    int(match.group(1), 16), int(proof["analysis_address"], 16)
                )
                self.assertEqual(proof["cfg_result"]["status"], "PASS")
                self.assertGreater(proof["cfg_result"]["checked"], 0)

    def test_readable_names_keep_raw_backmaps(self) -> None:
        by_address = {
            item["analysis_address"]: item for item in self.receipt["proofs"]
        }
        self.assertEqual(
            by_address["0x010231c8"]["primary_symbol"], "sdc_conn_window_admit"
        )
        self.assertEqual(
            by_address["0x0102583c"]["primary_symbol"],
            "controller_deferred_event_raise",
        )
        for proof in self.receipt["proofs"]:
            self.assertIn(proof["analysis_address"], proof["raw_backmap"])

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

    def test_reviewed_cases_reject_success_publication_mutation(self) -> None:
        import cfg_verify
        import build_net_private2_recovery_receipt as builder

        source = (BASE / "recon/net/src/FUN_010231c8.c").read_text()
        self.assertEqual(source.count("entry[0] = 3u;"), 1)
        mutated = source.replace("entry[0] = 3u;", "entry[0] = 7u;")
        cfg_verify.core_ctx("net")["sizes"][0x010231C8] = 1500
        builder.install_conn_window_cases()
        result = cfg_verify.verify(
            "net", "sdc_conn_window_admit", trials_random=1,
            source_override=mutated,
        )
        self.assertEqual(result["status"], "FAIL")


if __name__ == "__main__":
    unittest.main()
