#!/usr/bin/env python3
import json
import unittest
from pathlib import Path

from validate_cohesive_net_undefineds import ROOT, REPORT, validate


class CohesiveNetUndefinedClassificationTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.report = json.loads(REPORT.read_text())
        cls.by_symbol = {row["symbol"]: row for row in cls.report["entries"]}

    def test_full_report_invariants(self):
        validate(self.report)

    def test_private_archive_policy_is_non_mutating(self):
        mpsl = self.by_symbol["FUN_01021940"]
        self.assertEqual(mpsl["category"], "private_sdc_mpsl_report_only")
        self.assertTrue(mpsl["manifest_policy_conflict"])
        self.assertFalse(mpsl["provider"]["safe_to_auto_resolve"])
        sdc = self.by_symbol["FUN_0100f86c"]
        self.assertEqual(sdc["provider"]["family"], "softdevice_controller")
        self.assertFalse(sdc["provider"]["safe_to_auto_resolve"])

    def test_known_stock_and_anomalous_providers(self):
        self.assertEqual(
            self.by_symbol["FUN_01025d38"]["provider"]["symbol"],
            "__udivmoddi4",
        )
        self.assertEqual(
            self.by_symbol["FUN_0102a244"]["provider"]["symbol"], "strcmp"
        )
        self.assertEqual(
            self.by_symbol["spin_lock"]["resolution_kind"],
            "existing_readable_alias_not_linked",
        )
        self.assertEqual(
            self.by_symbol["FUN_0102d25c"]["provider"]["status"],
            "no_valid_provider",
        )

    def test_input_catalogs_are_declared(self):
        names = {Path(row["path"]).name for row in self.report["inputs"]}
        self.assertIn("refgraph_net.json.gz", names)
        self.assertIn("net_address_spaces.json", names)
        self.assertIn("adoption_manifest.json", names)
        self.assertIn("net_sdc_archive_ownership.json", names)

    def test_firmware_selects_released_ncs_manifest(self):
        provenance = self.report["archive_version_discrimination"][
            "firmware_release_provenance"
        ]
        self.assertEqual(provenance["ncs_release"], "v2.5.1")
        self.assertEqual(
            provenance["embedded_banner"],
            "*** Booting nRF Connect SDK v2.5.1 ***",
        )
        self.assertEqual(provenance["image_offset"], "0x363c4")
        self.assertEqual(
            provenance["released_component_revisions"]["nrfxlib"], "v2.5.1"
        )


if __name__ == "__main__":
    unittest.main()
