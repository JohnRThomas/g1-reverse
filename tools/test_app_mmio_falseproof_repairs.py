#!/usr/bin/env python3
"""Fail-closed checks for the two repaired CPUAPP ordered-MMIO false proofs."""

import hashlib
import json
import unittest
from pathlib import Path

import cfg_verify


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/analysis/app_mmio_falseproof_repairs.json"


class AppMmioFalseproofRepairsTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_is_exact_and_mirrors_are_synchronized(self):
        self.assertEqual("g1.app-mmio-falseproof-repairs.v1",
                         self.receipt["schema"])
        self.assertEqual({"0x00050558", "0x00066050"},
                         {row["va"] for row in self.receipt["repairs"]})
        for row in self.receipt["repairs"]:
            canonical = ROOT / row["canonical_source"]
            mirror = ROOT / row["verified_mirror"]
            self.assertEqual(canonical.read_bytes(), mirror.read_bytes())
            self.assertEqual(
                row["source_sha256"],
                hashlib.sha256(canonical.read_bytes()).hexdigest(),
            )

    def test_canonical_sources_pass_authoritative_cfg_verification(self):
        for row in self.receipt["repairs"]:
            # One deterministic baseline trial is required for a straight-line
            # function such as FUN_00066050, which has no CFG selector cases.
            verdict = cfg_verify.verify("app", row["raw_symbol"],
                                        trials_random=1)
            self.assertEqual("PASS", verdict["status"], verdict)
            self.assertEqual(row["cfg_verify"]["cases"],
                             verdict["cover_cases"])

    def test_bfar_after_cfsr_regression_is_rejected(self):
        path = ROOT / "recon/app/src/FUN_00050558.c"
        source = path.read_text()
        ordered = (
            "        fault_address = *scb_bfar;\n"
            "        if ((int32_t)(*scb_cfsr << 0x10) < 0) {"
        )
        regressed = (
            "        if ((int32_t)(*scb_cfsr << 0x10) < 0) {\n"
            "            fault_address = *scb_bfar;"
        )
        self.assertIn(ordered, source)
        verdict = cfg_verify.verify(
            "app", "FUN_00050558", trials_random=0,
            source_override=source.replace(ordered, regressed),
        )
        self.assertEqual("FAIL", verdict["status"], verdict)

    def test_grouped_pdm_event_writes_regression_is_rejected(self):
        path = ROOT / "recon/app/src/FUN_00066050.c"
        source = path.read_text()
        ordered = (
            "    *pdm_events_started = 0;\n"
            "    uint32_t events_started = *pdm_events_started;\n"
            "    *pdm_events_stopped = 0;\n"
            "    uint32_t events_stopped = *pdm_events_stopped;"
        )
        regressed = (
            "    *pdm_events_started = 0;\n"
            "    *pdm_events_stopped = 0;\n"
            "    uint32_t events_started = *pdm_events_started;\n"
            "    uint32_t events_stopped = *pdm_events_stopped;"
        )
        self.assertIn(ordered, source)
        verdict = cfg_verify.verify(
            "app", "FUN_00066050", trials_random=0,
            source_override=source.replace(ordered, regressed),
        )
        self.assertEqual("FAIL", verdict["status"], verdict)


if __name__ == "__main__":
    unittest.main()
