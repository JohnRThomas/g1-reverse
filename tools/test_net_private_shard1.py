#!/usr/bin/env python3
"""Regression gates for the private CPUNET shard-1 reconstruction."""

import json
import unittest

import verify_net_private_shard1 as shard


class NetPrivateShard1Test(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(shard.OUTPUT.read_text())

    def test_receipt_regenerates_with_authoritative_cfg(self):
        self.assertEqual(self.receipt, shard.verify())
        self.assertEqual("cfg_verified", self.receipt["status"])
        proof = self.receipt["cfg_verification"]
        self.assertEqual("PASS", proof["generic_status"])
        self.assertEqual("PASS", proof["reviewed_status"])
        self.assertEqual(121, proof["total_checked"])

    def test_reviewed_cases_cover_every_dispatch_family(self):
        counts = self.receipt["cfg_verification"]["reviewed_case_counts"]
        self.assertEqual({
            "argument_and_global_flag_cases": 29,
            "c6_tbb_cases": 13,
            "nested_phy_cases": 32,
            "event_callback_cases": 2,
            "packet_table_callback_cases": 1,
        }, counts)
        self.assertEqual(77, sum(counts.values()))

    def test_reviewed_extent_partitions_code_and_embedded_data(self):
        end = shard.VA + shard.SIZE
        intervals = list(shard.BODY_RANGES) + list(shard.DISPATCH_TABLE_ISLANDS)
        intervals += [(start, stop) for start, stop in shard.LITERAL_ISLANDS
                      if start < end]
        cursor = shard.VA
        for start, stop in sorted(intervals):
            self.assertEqual(cursor, start)
            self.assertLess(start, stop)
            cursor = stop
        self.assertEqual(end, cursor)

    def test_call_and_state_closure_is_exact(self):
        closure = self.receipt["call_state_closure"]
        self.assertEqual(sum(shard.EXPECTED_DIRECT_CALLS.values()),
                         closure["direct_callsite_count"])
        self.assertEqual(7, len(closure["indirect_callsites"]))
        self.assertEqual("FUN_0100a984@0x0100a984",
                         closure["terminal_tail_target"])
        self.assertEqual(20, closure["event_callback_stack_record_bytes"])

    def test_source_preserves_raw_backmap_and_signed_abi_fixes(self):
        source = shard.SOURCE.read_text()
        self.assertIn("FUN_01014b18 @ 0x01014b18", source.splitlines()[0])
        self.assertIn("sdc_conn_event_process", source.splitlines()[0])
        self.assertIn("int8_t cVar7", source)
        self.assertIn("FUN_01013e98(iVar18,1);", source)
        self.assertIn(
            "FUN_0100d3c0(iVar18 + 0xa8,1,*(undefined1 *)(iVar18 + 199),1)",
            source)
        self.assertNotIn(".incbin", source)
        self.assertNotIn("__attribute__((naked))", source)


if __name__ == "__main__":
    unittest.main()
