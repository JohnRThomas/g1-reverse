#!/usr/bin/env python3
"""Focused fail-closed tests for nRF53 MMIO differential tracing."""

import unittest

import cfg_verify
from parity import emu


VA = 0x00050000
RTC1_COUNTER = 0x41016504


class ParityMmioTest(unittest.TestCase):
    def test_omitted_zero_valued_mmio_read_fails(self):
        original = bytes.fromhex("0168 0020 7047")  # ldr r1,[r0]; return 0
        omitted = bytes.fromhex("0020 7047")
        fixture = [[(RTC1_COUNTER, bytes(4))]]
        common = dict(
            trials=1, nptr=0, arg_overrides=[{0: RTC1_COUNTER}],
            absolute_memory_overrides=fixture,
        )
        identical = emu.compare(original, VA, len(original),
                                 original, VA, len(original), **common)
        self.assertTrue(identical["pass"], identical)
        verdict = emu.compare(original, VA, len(original),
                              omitted, VA, len(omitted), **common)
        self.assertFalse(verdict["pass"], verdict)
        before, after = verdict["detail"][0][2:4]
        self.assertEqual([("R", RTC1_COUNTER, 4, 0)], before["events"])
        self.assertEqual([], after["events"])

    def test_peripheral_reads_and_writes_share_one_ordered_trace(self):
        # ldr r1,[r0]; str r2,[r0,#4]; ldr r3,[r0,#4]; bx lr
        body = bytes.fromhex("0168 4260 4368 7047")
        runner = emu.Runner(VA, len(body), body)
        result = runner.run(
            0, [RTC1_COUNTER, 0, 0xAABBCCDD, 0], 0,
            absolute_memory_overrides=[
                (RTC1_COUNTER, (0x11223344).to_bytes(4, "little"))],
        )
        self.assertEqual([
            ("R", RTC1_COUNTER, 4, 0x11223344),
            ("W", RTC1_COUNTER + 4, 4, 0xAABBCCDD),
            ("R", RTC1_COUNTER + 4, 4, 0xAABBCCDD),
        ], result["events"])

    def test_reviewed_transition_is_traced_and_unknown_miss_faults(self):
        load = bytes.fromhex("0068 7047")
        runner = emu.Runner(VA, len(load), load)
        transitioned = runner.run(
            0, [RTC1_COUNTER, 0, 0, 0], 0,
            absolute_memory_overrides=[(RTC1_COUNTER, bytes(4))],
            absolute_read_transitions=[(RTC1_COUNTER, 1, 0xA5A55A5A)],
        )
        self.assertEqual(0xA5A55A5A, transitioned["r0"])
        self.assertEqual([("R", RTC1_COUNTER, 4, 0xA5A55A5A)],
                         transitioned["events"])
        reset = runner.run(0, [RTC1_COUNTER, 0, 0, 0], 0)
        self.assertNotIn("error", reset)
        self.assertEqual([("R", RTC1_COUNTER, 4, 0)], reset["events"])
        unknown = runner.run(0, [0x60000000, 0, 0, 0], 0)
        self.assertEqual("Invalid memory read", unknown["error"])

    def test_rtc_compare_set_retained_false_proof_is_rejected(self):
        verdict = cfg_verify.verify("net", "rtc_compare_set", trials_random=0)
        self.assertEqual("FAIL", verdict["status"], verdict)
        self.assertEqual(1, verdict["cover_cases"])
        mismatch = verdict["detail"][0]
        self.assertEqual("state", mismatch[1])
        original, candidate = mismatch[2], mismatch[3]
        self.assertIn(("R", RTC1_COUNTER, 4, 0), original["events"])
        self.assertNotIn(("R", RTC1_COUNTER, 4, 0), candidate["events"])


if __name__ == "__main__":
    unittest.main()
