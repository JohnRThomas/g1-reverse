#!/usr/bin/env python3
"""Regression guards for the cohesive CPUNET timeslot owner."""

import pathlib
import unittest

ROOT = pathlib.Path(__file__).resolve().parents[1]


class NetTimeslotOwnerTest(unittest.TestCase):
    def test_exact_static_owner(self):
        source = (ROOT / "recon/application/net/src/timeslot_owner.c").read_text()
        self.assertIn("LOG_MODULE_REGISTER(timeslot, 3)", source)
        self.assertIn("K_MSGQ_DEFINE(g1_timeslot_api_msgq, 1, 4, 4)", source)
        self.assertIn(".distance_us = 50000", source)
        self.assertIn(".length_us = 5000", source)
        self.assertIn(".timeout_us = 1000000", source)
        self.assertIn("K_THREAD_DEFINE(mpsl_nonpreemptible_thread_id, 0x400", source)
        self.assertIn("-16, 0, 0", source)

    def test_relocations_are_cohesive_only(self):
        worker = (ROOT / "recon/net/src/FUN_0102b810.c").read_text()
        producer = (ROOT / "recon/net/src/FUN_0102b900.c").read_text()
        for text in (worker, producer):
            self.assertIn("#ifdef G1_COHESIVE_BUILD", text)
            self.assertIn("/*=0x210008e0*/", text)
            self.assertIn("#else", text)
        self.assertIn("/*=0x210005d8*/", worker)
        self.assertIn("/*=0x210005b8*/", worker)
        self.assertIn("/*=0x0102c145 runtime Thumb*/", worker)

    def test_cmake_has_no_forced_timeslot_retention(self):
        cmake = (ROOT / "recon/application/net/CMakeLists.txt").read_text()
        self.assertIn("G1_TIMESLOT_OWNER_SOURCES", cmake)
        self.assertIn("G1_COHESIVE_BUILD=1", cmake)
        self.assertNotIn("-u,FUN_0102b810", cmake)
        self.assertNotIn("-u,FUN_0102b944", cmake)
        self.assertNotIn("KEEP(*timeslot", cmake)


if __name__ == "__main__":
    unittest.main()
