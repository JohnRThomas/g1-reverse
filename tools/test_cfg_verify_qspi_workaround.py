#!/usr/bin/env python3
"""Negative controls for qspi_workaround_apply's reviewed MMIO model."""

import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(__file__))

import cfg_verify


ROOT = os.path.dirname(os.path.dirname(__file__))
SOURCE = os.path.join(ROOT, "recon", "app", "src",
                      "qspi_workaround_apply.c")
KEY = ("app", 0x000667e0)


class QspiWorkaroundCfgVerifyTests(unittest.TestCase):
    def source(self):
        with open(SOURCE) as source_file:
            return source_file.read()

    def test_file_backed_reconstruction_passes(self):
        verdict = cfg_verify.verify("app", "qspi_workaround_apply",
                                    trials_random=0)
        self.assertEqual(verdict.get("status"), "PASS", verdict)
        self.assertEqual(verdict.get("checked"), 1, verdict)

    def test_live_r1_residual_is_required(self):
        reviewed = cfg_verify.REVIEWED_ORACLE_CASES[KEY]
        try:
            cfg_verify.REVIEWED_ORACLE_CASES[KEY] = [({}, [], {})]
            verdict = cfg_verify.verify("app", "qspi_workaround_apply",
                                        trials_random=0)
        finally:
            cfg_verify.REVIEWED_ORACLE_CASES[KEY] = reviewed
        self.assertEqual(verdict.get("status"), "FAIL", verdict)
        self.assertIn("direct-target", repr(verdict.get("detail")))

    def test_ready_transition_must_target_exact_register(self):
        reviewed = cfg_verify.ABSOLUTE_READ_TRANSITION_CASES[KEY]
        try:
            cfg_verify.ABSOLUTE_READ_TRANSITION_CASES[KEY] = [
                [(0x5002b104, 1, 1)],
            ]
            verdict = cfg_verify.verify("app", "qspi_workaround_apply",
                                        trials_random=0)
        finally:
            cfg_verify.ABSOLUTE_READ_TRANSITION_CASES[KEY] = reviewed
        self.assertEqual(verdict.get("status"), "FAIL", verdict)

    def test_missing_restore_call_fails(self):
        source = self.source()
        call = "    nrf_qspi_pins_set(&saved);"
        self.assertIn(call, source)
        verdict = cfg_verify.verify(
            "app", "qspi_workaround_apply", trials_random=0,
            source_override=source.replace(call, "    (void)saved;", 1))
        self.assertEqual(verdict.get("status"), "FAIL", verdict)

    def test_swapped_restore_target_fails_direct_identity(self):
        source = self.source()
        declaration = (
            "extern void nrf_qspi_pins_set(const struct qspi_pins *pins); "
            "/*=0x00066784*/")
        replacement = declaration + (
            "\nextern void FUN_00066850(const struct qspi_pins *pins);")
        self.assertIn(declaration, source)
        source = source.replace(declaration, replacement, 1)
        source = source.replace("nrf_qspi_pins_set(&saved);",
                                "FUN_00066850(&saved);", 1)
        verdict = cfg_verify.verify(
            "app", "qspi_workaround_apply", trials_random=0,
            source_override=source)
        self.assertEqual(verdict.get("status"), "FAIL", verdict)
        self.assertIn("direct-target", repr(verdict.get("detail")))


if __name__ == "__main__":
    unittest.main()
