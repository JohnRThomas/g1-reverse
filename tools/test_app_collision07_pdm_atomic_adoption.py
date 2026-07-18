#!/usr/bin/env python3
"""Fail-closed checks for the atomic nrfx PDM source-unit adoption."""

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
AUTH = ROOT / "recon/ownership/app_collision_adoption_authorizations.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
PRJ = ROOT / "recon/application/app/prj.conf"
AUDIT = ROOT / "recon/catalogs/app_collision07_pdm_atomic.json"
PDM_VAS = {
    "0x0006615c", "0x000661dc", "0x00066214", "0x00066270", "0x00066300",
}
PDM_SYMBOLS = {
    "nrfx_pdm_init", "nrfx_pdm_uninit", "nrfx_pdm_start",
    "nrfx_pdm_buffer_set", "nrfx_pdm_stop",
}


class PdmAtomicAdoptionTest(unittest.TestCase):
    def setUp(self):
        self.auth = json.loads(AUTH.read_text())
        self.rows = [row for row in self.auth["authorizations"]
                     if row.get("batch") == "COLLISION-07"]

    def test_five_exact_rows_are_one_atomic_unit(self):
        self.assertEqual(PDM_VAS, {row["va"] for row in self.rows})
        self.assertEqual(PDM_SYMBOLS, {row["symbol"] for row in self.rows})
        for row in self.rows:
            self.assertTrue(row["configuration_variant_exact"])
            self.assertTrue(row["instruction_exact"])
            self.assertEqual(18, row["cfg_verify_cases"])
            self.assertEqual(PDM_VAS, set(row["atomic_group"]))
            self.assertEqual(PDM_VAS, set(row["whole_unit_closure"]["exclude_only"]))
            self.assertEqual([], row["whole_unit_closure"]["new_undefined_symbols"])
            self.assertEqual(row["firmware_code_size"], row["upstream_code_size"])

    def test_configuration_and_artifact_receipts_are_current(self):
        text = PRJ.read_text()
        self.assertIn("CONFIG_ASSERT=y", text)
        self.assertIn("CONFIG_ASSERT_LEVEL=2", text)
        self.assertIn("# CONFIG_SPIN_VALIDATE is not set", text)
        for row in self.rows:
            config = Path(row["configured_build"])
            obj = Path(row["upstream_object"])
            self.assertEqual(row["configured_build_sha256"],
                             hashlib.sha256(config.read_bytes()).hexdigest())
            self.assertEqual(row["upstream_object_sha256"],
                             hashlib.sha256(obj.read_bytes()).hexdigest())
            values = adoption._kconfig_values(config)
            self.assertEqual(row["required_config"],
                             {key: values.get(key)
                              for key in row["required_config"]})

    def test_manifest_and_retained_list_exclude_exact_public_owners(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        self.assertTrue(all(entries[va]["exclude_reconstruction"] for va in PDM_VAS))
        retained = RETAINED.read_text()
        for symbol in PDM_SYMBOLS:
            self.assertNotIn("/%s.c" % symbol, retained)
        for va in PDM_VAS:
            self.assertTrue((ROOT / "recon/app/src" / ("FUN_%s.c" % va[2:])).exists())

    def test_link_delta_is_exact_and_unresolved_set_is_stable(self):
        delta = json.loads(AUDIT.read_text())["link_delta"]
        self.assertEqual((96, 91),
                         (delta["before_unique_collisions"],
                          delta["after_unique_collisions"]))
        self.assertEqual(PDM_SYMBOLS, set(delta["removed"]))
        self.assertEqual([], delta["added"])
        self.assertEqual(delta["unresolved_before"], delta["unresolved_after"])

    def test_missing_atomic_peer_fails_closed(self):
        changed = copy.deepcopy(self.auth)
        changed["authorizations"] = [row for row in changed["authorizations"]
                                      if row.get("va") != "0x00066300"]
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "authorizations.json"
            path.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["app_collision_authorizations"] = str(path)
            with self.assertRaisesRegex(ValueError, "incomplete atomic authorization"):
                adoption.build(paths)

    def test_assertion_config_mutation_fails_closed(self):
        changed = copy.deepcopy(self.auth)
        with tempfile.TemporaryDirectory() as temp:
            config = Path(temp) / ".config"
            config.write_text("# CONFIG_ASSERT is not set\nCONFIG_ASSERT_LEVEL=2\n"
                              "# CONFIG_SPIN_VALIDATE is not set\n")
            digest = hashlib.sha256(config.read_bytes()).hexdigest()
            for row in changed["authorizations"]:
                if row.get("batch") == "COLLISION-07":
                    row["configured_build"] = str(config)
                    row["configured_build_sha256"] = digest
            auth = Path(temp) / "authorizations.json"
            auth.write_text(json.dumps(changed))
            paths = dict(adoption.DEFAULTS)
            paths["app_collision_authorizations"] = str(auth)
            with self.assertRaisesRegex(ValueError, "required config mismatch"):
                adoption.build(paths)


if __name__ == "__main__":
    unittest.main()
