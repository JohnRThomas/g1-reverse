#!/usr/bin/env python3
"""Regression test for the DEBUG_PRINT identity/ABI classification."""

import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import classify_app_link_residue


class DebugPrintIdentityTests(unittest.TestCase):
    def test_debug_print_is_a_distinct_library_wrapper(self):
        reason = classify_app_link_residue.SDK_SPELLING_OVERRIDES["DEBUG_PRINT"]
        self.assertIn("0x0007dda4", reason)
        self.assertIn("not debug_print", reason)
        self.assertIn("variadic", reason)


if __name__ == "__main__":
    unittest.main()
