#!/usr/bin/env python3
"""Fail-closed parity and provenance gates for four retained CPUNET gaps."""

import hashlib
import json
import unittest
from pathlib import Path

import cfg_verify
from parity import emu


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_link_gap_recovery.json"


class NetLinkGapRecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_authoritative_cfg_verify_remains_green(self):
        for row in self.receipt["functions"]:
            with self.subTest(symbol=row["raw_symbol"]):
                verdict = cfg_verify.verify("net", row["raw_symbol"])
                self.assertEqual("PASS", verdict["status"])
                self.assertGreaterEqual(verdict["checked"],
                                        row["ordinary_cfg_checked"])

    def test_directed_production_shaped_cases_remain_green(self):
        state_cases = dict(cfg_verify.REVIEWED_STATE_CASES)
        oracle_cases = dict(cfg_verify.REVIEWED_ORACLE_CASES)
        nptr_counts = dict(cfg_verify.REVIEWED_NPTR_COUNTS)
        target_arities = dict(cfg_verify.REVIEWED_TARGET_CALL_ARITIES)
        scratch = emu.SCRATCH

        cfg_verify.REVIEWED_STATE_CASES[("net", 0x0100f7e0)] = [
            ({0: value}, []) for value in
            (0, 10, 11, 15, 16, 32, 33, 39, 40, 46, 47, 48, 0xffffffff)
        ]
        cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0100f7e0)] = 0

        def finish_case(state):
            owner, connection = scratch + 0x3000, scratch + 0x3400
            owner_image = bytearray(16)
            owner_image[4:8] = connection.to_bytes(4, "little")
            connection_image = bytearray(0x220)
            connection_image[0:2] = (0x1234).to_bytes(2, "little")
            connection_image[0x64] = state
            return ({0: owner}, [(owner, bytes(owner_image)),
                                  (connection, bytes(connection_image))])

        cfg_verify.REVIEWED_STATE_CASES[("net", 0x0100fae4)] = [
            finish_case(state) for state in (1, 0, 2)
        ]
        cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0100fae4)] = 1

        def timing_case(local0, local1, peer0, peer1, valid, time0, time1):
            connection = scratch + 0x4000
            timing = scratch + 0x4200
            peer = scratch + 0x4300
            connection_image = bytearray(0x80)
            connection_image[0x6e] = local0
            connection_image[0x6f] = local1
            timing_image = bytearray(16)
            timing_image[2:4] = (0x1111).to_bytes(2, "little")
            timing_image[4:6] = time0.to_bytes(2, "little")
            timing_image[6:8] = (0x2222).to_bytes(2, "little")
            timing_image[8:10] = time1.to_bytes(2, "little")
            peer_image = bytes((peer0, peer1, 0, 0))
            return ({0: connection, 1: timing, 2: peer, 3: valid},
                    [(connection, bytes(connection_image)),
                     (timing, bytes(timing_image)), (peer, peer_image)])

        cfg_verify.REVIEWED_STATE_CASES[("net", 0x0100f110)] = [
            timing_case(0x0c, 0x0c, 0, 0, 0, 1, 2),
            timing_case(0, 0, 0x0c, 0x0c, 1, 1, 2),
            timing_case(0, 0x0c, 0, 0, 0, 0x2000, 2),
            timing_case(0, 0, 0, 0, 1, 0x2000, 0x3000),
        ]
        cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x0100f110)] = 3

        def packet_case(address, results):
            return ({0: address, 1: 0x89abcdef},
                    [(address, bytes(64))], results)

        cfg_verify.REVIEWED_ORACLE_CASES[("net", 0x01009224)] = [
            packet_case(scratch + 0x5000, {0: {0: 2}}),
            packet_case(scratch + 0x5100, {0: {0: 8}}),
            packet_case(scratch + 0x5200, {0: {0: 3}}),
            packet_case(scratch + 0x5005,
                        {0: {0: 4}, 1: {0: 0}, 2: {0: 1}}),
            packet_case(scratch + 0x5021,
                        {0: {0: 4}, 1: {0: 0}, 2: {0: 1}}),
            packet_case(scratch + 0x5040,
                        {0: {0: 4}, 1: {0: 1}, 2: {0: 1}}),
        ]
        cfg_verify.REVIEWED_NPTR_COUNTS[("net", 0x01009224)] = 1
        cfg_verify.REVIEWED_TARGET_CALL_ARITIES[("net", 0x01009224)] = {
            0x0100ec88: 1, 0x01025fd4: 2, 0x0102602e: 2,
            0x0102609e: 2, 0x01026122: 2, 0x010267fe: 2,
            0x01026842: 2, 0x01008d00: 2,
        }

        try:
            for row in self.receipt["functions"]:
                with self.subTest(symbol=row["raw_symbol"]):
                    verdict = cfg_verify.verify(
                        "net", row["raw_symbol"], trials_random=0)
                    self.assertEqual("PASS", verdict["status"])
                    self.assertEqual(row["directed_cases"],
                                     verdict["checked"])
        finally:
            cfg_verify.REVIEWED_STATE_CASES.clear()
            cfg_verify.REVIEWED_STATE_CASES.update(state_cases)
            cfg_verify.REVIEWED_ORACLE_CASES.clear()
            cfg_verify.REVIEWED_ORACLE_CASES.update(oracle_cases)
            cfg_verify.REVIEWED_NPTR_COUNTS.clear()
            cfg_verify.REVIEWED_NPTR_COUNTS.update(nptr_counts)
            cfg_verify.REVIEWED_TARGET_CALL_ARITIES.clear()
            cfg_verify.REVIEWED_TARGET_CALL_ARITIES.update(target_arities)

    def test_sources_and_policy_are_fail_closed(self):
        self.assertEqual(4, self.receipt["summary"]["function_count"])
        self.assertEqual(386, self.receipt["summary"]
                         ["total_true_executable_extent"])
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_readable_c_only"])
        self.assertTrue(policy["archive_or_blob_substitution_forbidden"])
        self.assertEqual("report_only_unchanged", policy["private_sdc_mpsl"])
        for row in self.receipt["functions"]:
            source = ROOT / row["source"]
            data = source.read_bytes()
            text = data.decode()
            self.assertEqual(row["source_sha256"],
                             hashlib.sha256(data).hexdigest())
            self.assertIn(row["raw_symbol"], text)
            self.assertIn(row["analysis_address"], text)
            self.assertNotIn(".incbin", text)
            self.assertNotIn(".byte", text)


if __name__ == "__main__":
    unittest.main()
