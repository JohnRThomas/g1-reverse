#!/usr/bin/env python3
"""Fail-closed checks for reviewed CPUAPP tail/interior resolutions."""

import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import build_app_veneer_resolutions as subject


class AppVeneerResolutionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = subject.build()

    def test_complete_and_fail_closed(self):
        summary = self.catalog["summary"]
        self.assertEqual(119, summary["residue_symbols"])
        self.assertEqual(117, summary["unique_vas"])
        self.assertEqual(35, summary["resolved_symbols"])
        self.assertEqual(33, summary["resolved_unique_vas"])
        self.assertEqual(20, summary["materialized_symbols"])
        self.assertEqual(20, summary["materialized_unique_vas"])
        self.assertEqual(15, summary["already_strong_symbols"])
        self.assertEqual(84, summary["blocked_symbols"])

    def test_every_materialized_tail_has_exact_thumb_evidence(self):
        for row in self.catalog["entries"]:
            if row["decision"] == "materialize_reviewed_tail_alias":
                self.assertTrue(row["evidence"]["decode"].startswith("b"))
                self.assertEqual(8, len(row["evidence"]["bytes"]))
                self.assertIn(row["symbol"], subject.REVIEWED_TAILS)

    def test_ambiguous_and_ownerless_entries_are_blocked(self):
        by_symbol = {row["symbol"]: row for row in self.catalog["entries"]}
        for symbol in ("send_touch_click_event", "FUN_0002538c", "ext3cebc"):
            self.assertEqual("blocked", by_symbol[symbol]["decision"])

    def test_cfg_verified_reconstructed_entries_are_strong_owners(self):
        by_symbol = {row["symbol"]: row for row in self.catalog["entries"]}
        self.assertEqual(9, len(subject.REVIEWED_RECONSTRUCTED_ENTRIES))
        for symbol, (address, filename) in subject.REVIEWED_RECONSTRUCTED_ENTRIES.items():
            row = by_symbol[symbol]
            self.assertEqual("0x%08x" % address, row["va"])
            self.assertEqual("already_resolved_by_strong_owner", row["decision"])
            self.assertTrue(os.path.isfile(
                os.path.join(ROOT, "recon/app/src", filename)))

    def test_missing_targets_and_sdk_public_owner_are_not_promoted(self):
        by_symbol = {row["symbol"]: row for row in self.catalog["entries"]}
        for symbol in ("FUN_0008131c", "thunk_FUN_0007f7d2", "k_sem_take"):
            self.assertEqual("blocked", by_symbol[symbol]["decision"])

    def test_link_fragment_contains_only_catalog_materializations(self):
        expected = {row["symbol"] for row in self.catalog["entries"]
                    if row["decision"].startswith("materialize_")}
        rendered = subject.render_ld(self.catalog)
        actual = {line.split("(", 1)[1].split(" ", 1)[0]
                  for line in rendered.splitlines() if line.startswith("PROVIDE(")}
        self.assertEqual(expected, actual)

    def test_both_link_paths_consume_reviewed_fragment(self):
        with open(os.path.join(ROOT, "recon/application/app/CMakeLists.txt")) as stream:
            self.assertIn("g1_app_veneer_aliases.ld", stream.read())
        with open(os.path.join(ROOT, "tools/full_link.py")) as stream:
            self.assertIn("g1_%s_veneer_aliases.ld", stream.read())


if __name__ == "__main__":
    unittest.main()
