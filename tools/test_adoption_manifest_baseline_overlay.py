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
APP_MMIO_REPAIRS = ROOT / "recon/analysis/app_mmio_falseproof_repairs.json"
CFG_RECHECKS = ROOT / "recon/analysis/cfg_sweep_target_rechecks.json"
NET_CFG_OVERLAY = ROOT / "recon/analysis/cfg_sweep_net_recheck_overlay.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
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
        added_overlay_vas = set(current_app) - set(baseline_app)
        changed_baseline_vas = {
            va for va in baseline_app if current_app[va] != baseline_app[va]}
        overlay_vas = added_overlay_vas | changed_baseline_vas
        self.assertTrue(added_overlay_vas)
        self.assertTrue(changed_baseline_vas)
        # Later exact-stock NET overlays legitimately add public ownership
        # entries.  The proof-overlay integration must nevertheless leave all
        # SoftDevice Controller decisions exactly as pinned by the baseline.
        baseline_sdc = {
            row["va"]: (row["exclude_reconstruction"], row["decision"])
            for row in baseline["cores"]["net"]["entries"]
            if row.get("component") == "softdevice_controller"}
        current_sdc = {
            row["va"]: (row["exclude_reconstruction"], row["decision"])
            for row in current["cores"]["net"]["entries"]
            if row.get("component") == "softdevice_controller"}
        self.assertEqual(baseline_sdc, current_sdc)
        self.assertEqual(
            sum(bool(row["exclude_reconstruction"])
                for row in baseline_app.values()),
            baseline["cores"]["app"]["summary"]["exclude_reconstruction"])
        self.assertEqual(
            sum(bool(row["exclude_reconstruction"])
                for row in current_app.values()),
            current["cores"]["app"]["summary"]["exclude_reconstruction"])
        self.assertTrue(all(current_app[va].get("evidence")
                            for va in overlay_vas))
        self.assertTrue(baseline_app["0x000850dc"]["exclude_reconstruction"])
        self.assertTrue(current_app["0x000850dc"]["exclude_reconstruction"])
        self.assertEqual("nrfx_gppi_channel_endpoints_setup",
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

    def test_exact_repair_proof_overlays_are_consumed(self):
        current = adoption.build(dict(adoption.DEFAULTS))
        overlay_inputs = {row["path"]: row["sha256"]
                          for row in current["overlay_inputs"]}
        for path in (APP_MMIO_REPAIRS, CFG_RECHECKS, NET_CFG_OVERLAY):
            relative = str(path.relative_to(ROOT))
            self.assertEqual(digest(path), overlay_inputs[relative])
        bus_fault = next(
            row for row in current["cores"]["app"]["entries"]
            if row["va"] == "0x00050558")
        proof = next(
            item for item in bus_fault["evidence"]
            if item["type"] ==
            "authoritative_reconstruction_reverify_overlay")
        self.assertEqual(
            "6bf760731716d693291005c00db2f875ce4fb15ce89d93b6fca9c92ac8cbf674",
            proof["source_sha256"])
        self.assertEqual("PASS", proof["status"])

    def test_app_repair_overlay_source_hash_drift_fails_closed(self):
        changed = json.loads(CFG_RECHECKS.read_text())
        changed["rechecks"]["app:FUN_00050558"]["source_sha256"] = "0" * 64
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "cfg_rechecks.json"
            path.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["cfg_target_rechecks"] = str(path)
            with self.assertRaisesRegex(ValueError,
                                        "APP MMIO repair proof changed"):
                adoption.build(paths)

    def test_net_repair_overlay_source_hash_drift_fails_closed(self):
        changed = json.loads(NET_CFG_OVERLAY.read_text())
        row = next(item for item in changed["resolved_fail"]
                   if item["name"] == "FUN_010313ec")
        row["source_sha256"] = "0" * 64
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "net_cfg_overlay.json"
            path.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["net_cfg_recheck_overlay"] = str(path)
            with self.assertRaisesRegex(
                    ValueError, "NET CFG repaired source proof changed"):
                adoption.build(paths)

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
