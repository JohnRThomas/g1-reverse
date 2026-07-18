#!/usr/bin/env python3
"""Fail-closed checks for the canonical SDC event-publication bridge."""

import hashlib
import json
import unittest
from pathlib import Path

import cfg_verify
import net_recon_kit


BASE = Path(__file__).resolve().parents[1]
SOURCE = BASE / "recon/net/src/FUN_0101b4f4.c"
RECEIPT = BASE / "recon/ownership/net_sdc_event_publish_recovery.json"


class NetSdcEventPublishRecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())
        cls.function = cls.receipt["function"]

    def test_identity_extent_and_bytes_are_pinned(self):
        self.assertEqual(self.function["analysis_address"], "0x0101b4f4")
        self.assertEqual(self.function["true_executable_extent"], 88)
        self.assertEqual(net_recon_kit.TRUE_SIZE_OVERRIDES[0x0101B4F4], 0x58)
        self.assertEqual(
            cfg_verify.TRUE_SIZE_OVERRIDES[("net", 0x0101B4F4)], 0x58
        )
        self.assertEqual(
            hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            self.function["source_sha256"],
        )
        firmware = (BASE / "netcore_image.bin").read_bytes()
        start = 0x0101B4F4 - 0x01008000
        image = firmware[start:start + 0x58]
        self.assertEqual(
            hashlib.sha256(image).hexdigest(),
            self.function["firmware_extent_sha256"],
        )

    def test_cfg_cases_pass_and_semantic_mutation_fails(self):
        verdict = cfg_verify.verify("net", "FUN_0101b4f4", trials_random=0)
        self.assertEqual(verdict["status"], "PASS", verdict)
        self.assertEqual(verdict["cover_cases"], 5)
        self.assertEqual(verdict["checked"], 5)

        source = SOURCE.read_text()
        self.assertEqual(source.count("state[2] = 1u;"), 1)
        negative = cfg_verify.verify(
            "net", "FUN_0101b4f4", trials_random=0,
            source_override=source.replace("state[2] = 1u;",
                                           "state[2] = 0u;", 1),
        )
        self.assertEqual(negative["status"], "FAIL", negative)
        self.assertGreater(negative.get("mismatches", 0), 0)

    def test_single_owner_is_generated_and_old_bridge_is_removed(self):
        closure = (BASE / "recon/application/net/src/cfg_boundary_lowerings.c")
        self.assertNotIn("void sdc_event_publish", closure.read_text())
        names = json.loads(
            (BASE / "recon/catalogs/function_names_net.json").read_text()
        )
        self.assertEqual(names["by_name"]["sdc_event_publish"], "0x0101b4f4")
        symbolized = BASE / "recon/symbolized/net/sdc_event_publish.c"
        self.assertTrue(symbolized.is_file())
        self.assertIn("identity: FUN_0101b4f4 @ 0x0101b4f4",
                      symbolized.read_text())
        retained = (BASE / "recon/generated/net_retained_sources.cmake").read_text()
        self.assertEqual(retained.count("/sdc_event_publish.c\""), 1)

    def test_sdc_policy_stays_report_only(self):
        self.assertEqual(self.receipt["policy"], {
            "archive_substitution_used": False,
            "blobs_used": False,
            "canonical_readable_c_only": True,
            "sdc_ownership_report_only": True,
            "automatic_sdc_removal": False,
        })

    def test_runtime_link_probe_has_one_resolved_owner(self):
        probe = self.receipt["cohesive_link_probe"]
        self.assertEqual(probe["flash_origin"], "0x01008800")
        self.assertEqual(probe["compiled_reconstruction_objects"], "1130/1130")
        self.assertEqual(probe["sdc_event_publish_strong_owners"], 1)
        self.assertEqual(
            probe["sdc_event_publish_unresolved_after_archive_resolution"], 0
        )
        self.assertEqual(probe["undefined_reference_diagnostics"], 0)
        self.assertEqual(probe["full_link_unknown_symbols"], 0)
        self.assertEqual(probe["terminal_status"], "FLASH overflow only")


if __name__ == "__main__":
    unittest.main()
