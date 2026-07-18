#!/usr/bin/env python3
"""Regression tests for COLLISION-05 nrfx_gpiote_init."""

import json
import os
import sys
import unittest
from pathlib import Path

TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_app_collision_05_nrfx_gpiote_init as audit


class NrfxGpioteInitCollisionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = audit.build()

    def test_fails_closed(self):
        self.assertEqual(self.data["decision"], "retain_reconstruction")
        self.assertEqual(self.data["authorization"], "denied_not_semantics_exact")
        self.assertFalse(self.data["exclude_reconstruction"])

    def test_normalized_identity_fails(self):
        match = self.data["evidence"]["signature_match"]
        self.assertFalse(match["normalized_exact"])
        self.assertLess(match["opcode"], 0.9)
        self.assertLess(match["shape"], 0.7)

    def test_event_call_sequence_differs(self):
        ev = self.data["evidence"]
        self.assertIn("0x655ec", ev["firmware"]["calls"])
        self.assertEqual(ev["configured_sdk"]["call_relocations"],
                         ["memset", "arch_irq_enable"])
        probe = ev["forced_uninitialized_state_probe"]
        self.assertEqual(probe["result"], "FAIL")
        self.assertEqual(probe["first_divergence"]["firmware_target"], "0x000655ec")

    def test_private_state_is_split(self):
        state = self.data["evidence"]["global_access_mismatch"]
        self.assertEqual(state["firmware_m_cb"], "0x20002bc0")
        self.assertEqual(state["sdk_local_m_cb"], "0x2000050c")
        self.assertTrue(state["split_state_risk"])

    def test_no_authorization_or_exclusion_exists(self):
        authorizations = json.loads(audit.AUTH.read_text())["authorizations"]
        self.assertNotIn("nrfx_gpiote_init",
                         {row["symbol"] for row in authorizations})
        retained = audit.RETAINED.read_text()
        self.assertIn("g1_recon_nrfx_gpiote_init.c", retained)
        self.assertNotIn("/nrfx_gpiote_init.c\"", retained)

    def test_namespace_is_address_backed_and_caller_closed(self):
        isolation = self.data["namespace_isolation"]
        self.assertEqual(isolation["status"], "implemented")
        self.assertEqual(isolation["firmware_owner"],
                         "g1_recon_nrfx_gpiote_init")
        self.assertEqual(isolation["sdk_owner"], "nrfx_gpiote_init")
        self.assertEqual(isolation["recovered_direct_callers"], [])
        self.assertFalse(isolation["overlay_changed"])
        self.assertEqual(isolation["collision_delta"], -1)
        self.assertEqual(isolation["new_collision_symbols"], [])
        self.assertEqual(isolation["new_undefined_symbols"], [])
        self.assertEqual(isolation["nm"], {
            "app_public_owner_count": 0,
            "app_namespaced_owner_count": 1,
            "sdk_public_owner_count": 1,
        })
        self.assertTrue(isolation["map_contains_both_distinct_owners"])

    def test_catalog_is_current(self):
        expected = json.dumps(self.data, indent=1, sort_keys=True) + "\n"
        self.assertEqual(Path(audit.OUT_JSON).read_text(), expected)


if __name__ == "__main__":
    unittest.main()
