#!/usr/bin/env python3
"""Regression tests for the CPUNET dual address-space contract."""

import json
import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import build_net_address_space_receipt as receipt_builder
import net_extract
from net_address_space import (
    ANALYSIS_BASE,
    ANALYSIS_TO_RUNTIME_DELTA,
    RUNTIME_BASE,
    AddressSpaceError,
    AmbiguousAddressSpaceError,
    AnalysisAddress,
    RuntimeAddress,
    analysis_to_runtime,
    classify_untyped_flash_address,
    runtime_to_analysis,
)


class NetAddressSpaceTests(unittest.TestCase):
    def test_typed_round_trip_and_thumb_bit(self):
        analysis = AnalysisAddress(0x0100823d)
        runtime = analysis_to_runtime(analysis)
        self.assertEqual(0x01008a3d, runtime.value)
        self.assertEqual(analysis, runtime_to_analysis(runtime))
        self.assertEqual(analysis.value & 1, runtime.value & 1)
        self.assertEqual(0x23d, analysis.to_offset())
        self.assertEqual(0x23d, runtime.to_offset())

    def test_boundaries_and_untyped_overlap_refusal(self):
        self.assertEqual(ANALYSIS_BASE, AnalysisAddress(ANALYSIS_BASE).value)
        self.assertEqual(RUNTIME_BASE, RuntimeAddress(RUNTIME_BASE).value)
        with self.assertRaises(AddressSpaceError):
            AnalysisAddress(ANALYSIS_BASE - 1)
        with self.assertRaises(AddressSpaceError):
            RuntimeAddress(RUNTIME_BASE - 1)
        with self.assertRaises(TypeError):
            analysis_to_runtime(0x0100823c)
        with self.assertRaises(AmbiguousAddressSpaceError):
            classify_untyped_flash_address(0x01010000)

    def test_analysis_read_remains_parity_compatible(self):
        self.assertEqual(net_extract.read_analysis(0x0100823c, 16),
                         net_extract.read(0x0100823c, 16))
        self.assertEqual(net_extract.read_analysis(0x0100823c, 16),
                         net_extract.func_bytes(0x0100823c, 16))

    def test_reset_vector_runtime_to_analysis_oracle(self):
        reset_thumb = net_extract.read_u32_runtime(RUNTIME_BASE + 4)
        self.assertEqual(0x0102fc8d, reset_thumb)
        reset_analysis = RuntimeAddress(reset_thumb & ~1).to_analysis()
        self.assertEqual(0x0102f48c, reset_analysis.value)
        self.assertEqual(bytes.fromhex("002080f31488"),
                         net_extract.read_analysis(reset_analysis.value, 6))

    def test_runtime_string_and_table_oracles(self):
        self.assertTrue(net_extract.read_runtime(0x0103d2a7, 16).startswith(
            b"ASSERTION FAIL @"))
        self.assertFalse(net_extract.read_analysis(0x0103d2a7, 16).startswith(
            b"ASSERTION FAIL @"))
        self.assertEqual(
            bytes.fromhex("0c0802170d0101020909010106020918"),
            net_extract.read_runtime(0x0103c190, 16))

    def test_receipt_is_deterministic_and_explicit(self):
        first = receipt_builder.build()
        second = receipt_builder.build()
        self.assertEqual(first, second)
        self.assertEqual("0x01008000", first["coordinate_spaces"]["analysis"]["base"])
        self.assertEqual("0x01008800", first["coordinate_spaces"]["runtime"]["base"])
        self.assertEqual("0x800", first["coordinate_spaces"]["analysis_to_runtime_delta"])
        self.assertEqual(1288, first["summary"]["function_identities"])
        self.assertEqual(28, first["summary"]["analysis_runtime_numeric_overlaps"])
        self.assertGreaterEqual(
            first["summary"]["runtime_function_pointer_references"], 50)
        for record in first["functions"]:
            analysis = int(record["analysis_address"], 16)
            runtime = int(record["runtime_address"], 16)
            self.assertEqual(ANALYSIS_TO_RUNTIME_DELTA, runtime - analysis)

    def test_checked_in_receipt_matches_builder(self):
        with open(receipt_builder.OUTPUT) as stream:
            checked_in = json.load(stream)
        self.assertEqual(receipt_builder.build(), checked_in)


if __name__ == "__main__":
    unittest.main()
