#!/usr/bin/env python3
"""Fail-closed checks for the CPUNET Nordic RTC timer adoption."""

import json
import unittest
from pathlib import Path

import build_net_rtc_timer_atomic_adoption as receipt


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/catalogs/net_rtc_timer_ownership.json"


class NetRtcTimerAtomicAdoptionTest(unittest.TestCase):
    def test_configured_sections_calls_and_state_are_exact(self):
        current = json.loads(AUDIT.read_text())
        self.assertEqual(current, receipt.build())
        sizes = {row["symbol"]: row["size"]
                 for row in current["section_matches"]}
        self.assertEqual(0x124, sizes["compare_set"])
        self.assertEqual(0xF4, sizes["rtc_nrf_isr"])
        self.assertTrue(all(row["match"] ==
                            "relocation-masked-byte-exact"
                            for row in current["section_matches"]))
        self.assertEqual({
            "0x01031248", "0x010312d0", "0x010313a8",
            "0x010313ec", "0x010315f0", "0x0103a6ae",
        }, {row["va"] for row in current["functions"]})

    def test_version_boundary_is_precise_and_not_overclaimed(self):
        current = json.loads(AUDIT.read_text())
        rows = current["version_precision"]["candidate_matrix"]
        by_ncs = {row["ncs_tag"]: row for row in rows}
        self.assertEqual("source_incompatible", by_ncs["v2.4.1"]["verdict"])
        self.assertFalse(by_ncs["v2.4.1"]["same_source_as_pinned"])
        self.assertEqual("body_compatible_not_patch_discriminating",
                         by_ncs["v2.5.1"]["verdict"])
        self.assertTrue(by_ncs["v2.5.1"]["same_source_as_pinned"])
        self.assertTrue(by_ncs["v2.6.1"]["same_source_as_pinned"])
        self.assertIn("does not independently distinguish",
                      current["version_precision"]["strongest_local_boundary"])
        self.assertIn("lacks exact-alarm argument and -EINVAL paths",
                      by_ncs["v2.4.1"]["source_discriminators"])
        self.assertEqual({
            "COUNTER_HALF_SPAN_plus_one": "0x00800001",
            "RTC1_register_base": "0x41016000",
            "COUNTER_HALF_SPAN_minus_MIN_CYCLES": "0x007ffffd",
        }, current["binary_discriminators"]["compare_set_constants"])
        self.assertEqual(16, current["binary_discriminators"]
                         ["cc_data_layout"]["stride"])

    def test_truncated_final_0x24_bytes_are_explicitly_proved(self):
        current = json.loads(AUDIT.read_text())
        extent = current["extent_correction"]
        self.assertEqual(0x100, extent["ghidra_declared_size"])
        self.assertEqual(0x124, extent["true_elf_section_size"])
        self.assertEqual(0x24, extent["omitted_tail_size"])
        image = (ROOT / "netcore_image.bin").read_bytes()
        start = 0x010313EC - 0x01008000 + 0x100
        tail = image[start:start + 0x24]
        self.assertEqual(tail.hex(), extent["omitted_tail_hex"])
        self.assertEqual([0x114, 0x120], [
            row["offset"] for row in extent["omitted_tail_relocations"]
        ])
        self.assertIn("0x41016504", extent["old_harness_blind_spot"])
        self.assertIn("full configured-section comparison",
                      extent["old_harness_blind_spot"])

    def test_receipt_authorizes_the_complete_static_closure(self):
        current = json.loads(AUDIT.read_text())
        wanted = {
            "0x01031248", "0x010312d0", "0x010313a8",
            "0x010313ec", "0x010315f0", "0x0103a6ae",
        }
        entries = {row["va"]: row for row in current["functions"]}
        self.assertEqual(wanted, set(entries))
        self.assertTrue(all(row["exclude_reconstruction"]
                            for row in entries.values()))

    def test_sdc_policy_remains_report_only(self):
        current = json.loads(AUDIT.read_text())
        self.assertEqual("report_only_unchanged",
                         current["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
