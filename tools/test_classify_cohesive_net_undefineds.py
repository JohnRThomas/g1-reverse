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

    def test_link_surface_is_closed(self):
        self.assertEqual(self.report["summary"]["undefined_symbols"], 0)
        self.assertEqual(self.report["summary"]["link_reference_relocations"], 0)
        self.assertEqual(self.report["entries"], [])

    def test_private_archive_policy_remains_non_mutating(self):
        self.assertTrue(self.report["policy"]["private_sdc_mpsl_report_only"])
        self.assertFalse(
            self.report["policy"]["automatic_private_archive_alias_or_removal"]
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
