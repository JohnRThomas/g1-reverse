#!/usr/bin/env python3
"""Regression tests for ble_process_put_req's directed CFG fixture."""

from __future__ import annotations

import unittest

import cfg_verify


class BlePutCfgFixtureTest(unittest.TestCase):
    def test_missing_case_oracles_get_independent_empty_dicts(self) -> None:
        completed = cfg_verify._complete_case_oracle_overrides(
            [{}, {1: {0: 1}}], 4, "test"
        )
        self.assertEqual(completed, [{}, {1: {0: 1}}, {}, {}])
        self.assertIsNot(completed[2], completed[3])

    def test_malformed_case_oracles_fail_closed(self) -> None:
        with self.assertRaises(TypeError):
            cfg_verify._complete_case_oracle_overrides([{}, []], 2, "test")
        with self.assertRaises(ValueError):
            cfg_verify._complete_case_oracle_overrides([{}, {}], 1, "test")

    def test_response_memset_is_replayed_at_exact_target(self) -> None:
        writes = cfg_verify.REVIEWED_ORACLE_MEMORY_WRITES[
            ("app", 0x0001A75C)
        ]
        self.assertEqual(writes, {
            0: [(0, 0, bytes(16), 0x00086C78)],
        })

    def test_authoritative_directed_cases_pass(self) -> None:
        verdict = cfg_verify.verify(
            "app", "ble_process_put_req", trials_random=0
        )
        self.assertEqual(verdict["status"], "PASS")
        self.assertEqual(verdict["cover_cases"], 137)
        self.assertEqual(verdict["checked"], 137)
        self.assertEqual(
            [case[2] for case in verdict["pointer_cases"]],
            list(range(1, 0x28)),
        )


if __name__ == "__main__":
    unittest.main()
