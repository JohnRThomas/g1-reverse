#!/usr/bin/env python3
"""Fail-closed regression for the finite FUN_010089f8 CFG timeout."""

import hashlib
import json
from pathlib import Path
import unittest

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon/net/src/FUN_010089f8.c"
RECEIPT = ROOT / "recon/analysis/cfg_timeout_net_FUN_010089f8.json"
BASELINE = ROOT / "recon/analysis/cfg_sweep_net_baseline_lanes.json"
FINAL = ROOT / "recon/analysis/cfg_sweep_net_final_lanes.json"
KEY = ("net", 0x010089F8)

P256 = (1 << 256) - (1 << 224) + (1 << 192) + (1 << 96) - 1
P256_GX = int(
    "6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",
    16,
)
P256_GY = int(
    "4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5",
    16,
)
BOUNDED_FIELD_ELEMENT = int(
    "9e56f50919667ed08c15d7b3d4d3c09d2a6c4cfe37a5b37ec8c7f2d94ef923ab",
    16,
) % P256


def _limbs(value):
    return value.to_bytes(32, "little")


def _directed_cases():
    vectors = (
        (0, 0, False),
        (1, 1, False),
        (P256 - 1, P256 - 1, False),
        (P256_GX, P256_GY, False),
        (BOUNDED_FIELD_ELEMENT, P256_GX, False),
        ((1 << 256) - 1, (1 << 256) - 1, False),
        (P256_GX, P256_GY, True),
    )
    cases = []
    for left_value, right_value, alias_left in vectors:
        out = emu.SCRATCH + 0x100
        left = out if alias_left else emu.SCRATCH + 0x200
        right = emu.SCRATCH + 0x300
        memory = [
            (out, bytes(32)),
            (left, _limbs(left_value)),
            (right, _limbs(right_value)),
        ]
        cases.append(({0: out, 1: left, 2: right}, memory))
    return cases


def _with_directed_cases(source_override=None, count=None):
    old = cfg_verify.REVIEWED_STATE_CASES.get(KEY)
    cases = _directed_cases()
    if count is not None:
        cases = cases[:count]
    cfg_verify.REVIEWED_STATE_CASES[KEY] = cases
    try:
        return cfg_verify.verify(
            "net",
            "FUN_010089f8",
            trials_random=0,
            source_override=source_override,
        )
    finally:
        if old is None:
            del cfg_verify.REVIEWED_STATE_CASES[KEY]
        else:
            cfg_verify.REVIEWED_STATE_CASES[KEY] = old


class TimeoutClassificationTest(unittest.TestCase):
    def test_receipt_is_bound_to_the_timed_out_source(self):
        receipt = json.loads(RECEIPT.read_text())
        digest = hashlib.sha256(SOURCE.read_bytes()).hexdigest()
        self.assertEqual("finite_slow_verification_path", receipt["classification"])
        self.assertEqual("PASS", receipt["authoritative_status"])
        self.assertFalse(receipt["source_defect"])
        self.assertEqual(receipt["source_sha256"], digest)

        baseline = json.loads(BASELINE.read_text())["lanes"]["5"]["receipt"]
        final = json.loads(FINAL.read_text())["lanes"]["5"]["receipt"]
        self.assertIn("FUN_010089f8", baseline["PASS"])
        self.assertIn("FUN_010089f8", final["timeout"])
        self.assertEqual(digest, baseline["_source_hashes"]["FUN_010089f8"])
        self.assertEqual(digest, final["_source_hashes"]["FUN_010089f8"])

    def test_seven_production_shaped_cases_pass_full_return(self):
        verdict = _with_directed_cases()
        self.assertEqual("PASS", verdict["status"], verdict)
        self.assertEqual(7, verdict["checked"])
        self.assertEqual(7, verdict["cover_cases"])

    def test_result_corruption_is_rejected(self):
        source = SOURCE.read_text()
        corrupt = source.replace(
            "result[i] = remainder[i];",
            "result[i] = remainder[i] ^ 1u;",
        )
        self.assertNotEqual(source, corrupt)
        verdict = _with_directed_cases(source_override=corrupt, count=1)
        self.assertEqual("FAIL", verdict["status"], verdict)
        self.assertEqual(1, verdict["checked"])
        self.assertEqual(1, verdict["mismatches"])


if __name__ == "__main__":
    unittest.main()
