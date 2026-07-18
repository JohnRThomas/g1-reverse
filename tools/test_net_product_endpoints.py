#!/usr/bin/env python3
"""Regression guards for cohesive CPUNET endpoint ownership."""

import pathlib
import unittest


ROOT = pathlib.Path(__file__).resolve().parents[1]


class NetProductEndpointsTest(unittest.TestCase):
    def test_exact_endpoint_objects(self):
        source = (ROOT / "recon/application/net/src/g1_product_endpoints.c").read_text()
        self.assertIn('.name = "ipc0"', source)
        self.assertIn('.name = "nrf_bt_hci"', source)
        self.assertIn("FUN_0102ab14", source)
        self.assertIn(".bound = FUN_0102ac00", source)
        self.assertIn("FUN_0102adf0", source)
        self.assertIn(".bound = FUN_0102ace8", source)

    def test_canonical_sources_replace_symbolized_copies(self):
        cmake = (ROOT / "recon/application/net/CMakeLists.txt").read_text()
        self.assertIn("G1_PRODUCT_ENDPOINT_SOURCES", cmake)
        self.assertIn("g1_product_endpoints.c", cmake)
        for name in ("a4c8", "ab14", "ab50", "abac", "ac00", "ac0c",
                     "acb4", "ace8", "acf4", "adac", "adf0", "afbc",
                     "b15c", "b1c8", "b2ac"):
            self.assertIn(name, cmake)
        self.assertNotIn("-u,FUN_0102ab14", cmake)
        self.assertNotIn("KEEP(*g1_product", cmake)

    def test_default_raw_backmaps_remain(self):
        for name in ("FUN_0102a720.c", "FUN_0102ac0c.c", "FUN_0102acb4.c",
                     "FUN_0102afbc.c", "FUN_0102b2ac.c"):
            source = (ROOT / "recon/net/src" / name).read_text()
            self.assertIn("#ifdef G1_COHESIVE_BUILD", source)
            self.assertIn("#else", source)
            self.assertIn("/*=0x", source)


if __name__ == "__main__":
    unittest.main()
