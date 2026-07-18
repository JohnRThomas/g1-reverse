#!/usr/bin/env python3
"""Fail closed when the canonical CPUAPP corpus and verified mirror drift."""

import os
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CANONICAL = os.path.join(ROOT, "recon/app/src")
VERIFIED = os.path.join(ROOT, "recon/verified/src")


def c_sources(directory):
    return {name for name in os.listdir(directory) if name.endswith(".c")}


class AppVerifiedMirrorTests(unittest.TestCase):
    def test_complete_byte_identical_mirror(self):
        canonical = c_sources(CANONICAL)
        verified = c_sources(VERIFIED)
        self.assertEqual(canonical, verified)
        differing = []
        for name in sorted(canonical):
            with open(os.path.join(CANONICAL, name), "rb") as stream:
                canonical_bytes = stream.read()
            with open(os.path.join(VERIFIED, name), "rb") as stream:
                verified_bytes = stream.read()
            if canonical_bytes != verified_bytes:
                differing.append(name)
        self.assertEqual([], differing)


if __name__ == "__main__":
    unittest.main()
