#!/usr/bin/env python3
"""Unit tests for the deterministic upstream preflight parsers."""

import os
import sys
import unittest
import json


TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import upstream_preflight as preflight


class UpstreamPreflightTest(unittest.TestCase):
    def test_project_revision_is_scoped_to_project(self):
        manifest = """manifest:
  projects:
    - name: first
      path: modules/first
      revision: abc123
    - name: second
      revision: 'v2.0'
"""
        self.assertEqual(preflight.project_revision(manifest, "first"), "abc123")
        self.assertEqual(preflight.project_revision(manifest, "second"), "v2.0")
        self.assertIsNone(preflight.project_revision(manifest, "absent"))

    def test_attribute_blocks_do_not_leak_between_members(self):
        output = """File: lib.a(hard.o)
Attribute Section: aeabi
  Tag_CPU_arch: v8-M.mainline
  Tag_ABI_VFP_args: VFP registers
File: lib.a(soft.o)
Attribute Section: aeabi
  Tag_CPU_arch: v8-M.mainline
"""
        self.assertEqual(preflight.attribute_blocks(output), [
            {"file": "lib.a(hard.o)", "Tag_CPU_arch": "v8-M.mainline",
             "Tag_ABI_VFP_args": "VFP registers"},
            {"file": "lib.a(soft.o)", "Tag_CPU_arch": "v8-M.mainline"},
        ])

    def test_text_render_is_stable_and_reports_failure_values(self):
        report = {
            "summary": {"checks": 2, "passed": 1, "failed": 1},
            "checks": [
                {"name": "good", "status": "pass", "expected": 1, "actual": 1},
                {"name": "bad", "status": "fail", "expected": "a", "actual": "b",
                 "detail": "fixture"},
            ],
        }
        self.assertEqual(
            preflight.render_text(report),
            "PASS good\nFAIL bad expected='a' actual='b' (fixture)\n"
            "SUMMARY checks=2 passed=1 failed=1",
        )

    def test_durable_catalog_separates_private_zephyr_from_public_baseline(self):
        with open(preflight.PROVENANCE_CATALOG) as stream:
            catalog = json.load(stream)
        firmware = catalog["firmware_manifest"]
        self.assertEqual(firmware["ncs_release"], "v2.5.1")
        self.assertNotEqual(firmware["zephyr_base_commit"],
                            firmware["zephyr_public_ncs_baseline"])
        self.assertIn("private_dirty", firmware["zephyr_identity_status"])
        self.assertTrue(catalog["policy"]["private_sdc_report_only"])
        self.assertEqual(
            set(catalog["prebuilt_archives"]),
            {"cc312_platform", "oberon_net", "mpsl_net",
             "softdevice_controller"})
        corrections = catalog["provenance_corrections"]
        self.assertEqual(len(corrections), 3)
        self.assertTrue(all(row["to_component"] == "open_amp"
                            for row in corrections))


if __name__ == "__main__":
    unittest.main()
