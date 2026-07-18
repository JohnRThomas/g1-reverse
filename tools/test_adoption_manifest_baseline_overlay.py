#!/usr/bin/env python3
"""Migration and fail-closed tests for the pinned adoption baseline overlay."""

import copy
import hashlib
import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build_adoption_manifest as adoption


ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "recon/ownership/adoption_manifest_baseline.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
RETENTIONS = ROOT / "recon/ownership/app_collision_retention_overrides.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
OVERLAY_VAS = {"0x00052fbc", "0x000680f8", "0x00070ee4", "0x00071560",
               "0x0006615c", "0x000661dc", "0x00066214", "0x00066270",
               "0x00066300", "0x000503d8", "0x00050558", "0x000506ac",
               "0x000507d4", "0x00071b2c", "0x000758cc", "0x000864e8",
               "0x00071c20", "0x00071cf4", "0x00072040", "0x0007205c",
               "0x00072078"}
CHANGED_BASELINE_VAS = {"0x00070ee4", "0x0006615c", "0x000661dc",
                        "0x00066214", "0x00066270", "0x00066300",
                        "0x000503d8", "0x00050558", "0x000506ac",
                        "0x000507d4", "0x000850dc", "0x000864e8",
                        "0x00071c20", "0x00071cf4"}
ADDED_OVERLAY_VAS = OVERLAY_VAS - CHANGED_BASELINE_VAS


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


class AdoptionBaselineOverlayTest(unittest.TestCase):
    def test_pinned_baseline_and_overlay_are_exact(self):
        baseline = json.loads(BASELINE.read_text())
        current = json.loads(MANIFEST.read_text())
        self.assertEqual(adoption.BASELINE_PROVENANCE["sha256"],
                         digest(BASELINE))
        self.assertEqual(adoption.BASELINE_PROVENANCE,
                         current["baseline_provenance"])
        baseline_app = {row["va"]: row for row in
                        baseline["cores"]["app"]["entries"]}
        current_app = {row["va"]: row for row in
                       current["cores"]["app"]["entries"]}
        self.assertEqual(ADDED_OVERLAY_VAS,
                         set(current_app) - set(baseline_app))
        self.assertEqual(CHANGED_BASELINE_VAS,
                         {va for va in baseline_app
                          if current_app[va] != baseline_app[va]})
        self.assertEqual(baseline["cores"]["net"], current["cores"]["net"])
        self.assertEqual(260, baseline["cores"]["app"]["summary"][
            "exclude_reconstruction"])
        self.assertEqual(280, current["cores"]["app"]["summary"][
            "exclude_reconstruction"])
        self.assertTrue(all(current_app[va]["exclude_reconstruction"]
                            for va in OVERLAY_VAS))
        self.assertTrue(baseline_app["0x000850dc"]["exclude_reconstruction"])
        self.assertFalse(current_app["0x000850dc"]["exclude_reconstruction"])
        self.assertEqual("g1_recon_nrfx_gppi_channel_endpoints_setup",
                         current_app["0x000850dc"]["current_symbol"])
        retained = RETAINED.read_text()
        self.assertNotIn("/bt_settings_delete.c", retained)
        self.assertNotIn("/metal_bus_unregister.c", retained)
        self.assertNotIn("/rpmsg_init_vdev.c", retained)
        self.assertNotIn("/virtqueue_free.c", retained)
        for symbol in ("nrfx_pdm_init", "nrfx_pdm_uninit", "nrfx_pdm_start",
                       "nrfx_pdm_buffer_set", "nrfx_pdm_stop"):
            self.assertNotIn("/%s.c" % symbol, retained)
        for symbol in ("arm_mem_manage_fault_helper", "arm_bus_fault_helper",
                       "arm_usage_fault_helper", "z_arm_fault"):
            self.assertNotIn("/%s.c" % symbol, retained)

    def test_production_build_is_deterministic(self):
        paths = dict(adoption.DEFAULTS)
        first = adoption.build(paths)
        second = adoption.build(paths)
        self.assertEqual(first, second)
        self.assertEqual(json.loads(MANIFEST.read_text()), first)

    def test_changed_collision_receipt_fails_closed(self):
        catalog = json.loads(AUTH.read_text())
        changed = copy.deepcopy(catalog)
        row = next(item for item in changed["authorizations"]
                   if item["va"] == "0x00071560")
        row["collision_receipt_sha256"] = "0" * 64
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "authorizations.json"
            path.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["app_collision_authorizations"] = str(path)
            with self.assertRaisesRegex(ValueError,
                                        "collision receipt digest mismatch"):
                adoption.build(paths)


if __name__ == "__main__":
    unittest.main()
