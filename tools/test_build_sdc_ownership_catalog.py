#!/usr/bin/env python3
"""Unit tests for the fail-closed SDC identity classifier."""
import importlib.util
import os
import unittest

PATH = os.path.join(os.path.dirname(__file__), "build_sdc_ownership_catalog.py")
SPEC = importlib.util.spec_from_file_location("sdc_catalog", PATH)
S = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(S)


def candidate(identity, sequence):
    return {"identity": identity, "opcodes": tuple(sequence),
            "instruction_count": len(sequence), "symbol": identity,
            "symbol_binding": "STB_LOCAL", "symbol_visibility": "STV_DEFAULT"}


class ClassifierTest(unittest.TestCase):
    def test_exact_unique(self):
        seq = ("push", "mov", "cmp", "beq", "str", "pop")
        result = S.classify(S.rank_sequence(seq, [
            candidate("exact", seq),
            candidate("runner", seq[:-1] + ("bx",)),
        ]))
        self.assertTrue(result["exact_opcode_sequence"])
        self.assertTrue(result["unique_identity"])

    def test_duplicate_exact_fails_closed(self):
        seq = ("push", "mov", "cmp", "beq", "str", "pop")
        result = S.classify(S.rank_sequence(seq, [
            candidate("first", seq), candidate("second", seq)]))
        self.assertFalse(result["unique_identity"])
        self.assertEqual(2, len(result["tied_best"]))

    def test_below_threshold_is_not_owned(self):
        seq = ("push", "mov", "cmp", "beq", "str", "pop")
        self.assertIsNone(S.classify(S.rank_sequence(
            seq, [candidate("other", ("nop",) * 6)])))

    def test_length_window(self):
        seq = ("nop",) * 6
        self.assertEqual([], S.rank_sequence(seq, [candidate("long", ("nop",) * 9)]))
        self.assertEqual(1, len(S.rank_sequence(
            seq, [candidate("long", ("nop",) * 9)], tolerance=3)))


if __name__ == "__main__":
    unittest.main()
