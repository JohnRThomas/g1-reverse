#!/usr/bin/env python3
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build_app_sdk_batch15_ownership as ownership


class TestBatch15(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = ownership.build()
        cls.rows = {row["symbol"]: row for row in cls.data["functions"]}

    def test_scope(self):
        self.assertEqual(8, self.data["summary"]["item_count"])
        self.assertEqual(7, self.data["summary"]["reconstructed_function_count"])
        self.assertEqual(8, self.data["summary"]["reference_count_before"])

    def test_fail_closed(self):
        self.assertTrue(self.data["policy"]["fail_closed"])
        self.assertIn("fake strtoll_internal body", self.data["policy"]["forbid"])
        self.assertTrue(self.data["identity_evidence"]["strtoll_rejected"])

    def test_backmaps_and_mirrors(self):
        for name, row in self.rows.items():
            with open(os.path.join(ownership.ROOT, row["source"]), encoding="utf-8") as stream:
                source = stream.read()
            self.assertIn(row["va"], source)
            if name == "strtoll_internal":
                self.assertIn("/*=0x00013f58*/", source)
                self.assertNotIn("strtoll_internal", source)
            else:
                self.assertIn("FUN_%08x" % int(row["va"], 16), source)

    def test_reviewed_case_counts(self):
        self.assertEqual(1, self.rows["nvmc_word_write"]["cfg_cases"])
        self.assertEqual(3, self.rows["process_queue"]["cfg_cases"])
        self.assertEqual(2, self.rows["remove_timeout"]["cfg_cases"])
        self.assertEqual(5, self.rows["sys_slist_find_and_remove"]["cfg_cases"])
        self.assertEqual(5, self.rows["sys_slist_find_and_remove_2"]["cfg_cases"])

    def test_strtoll_archive_rejected_by_identity(self):
        evidence = self.data["identity_evidence"]
        self.assertEqual("newlib-nano _strtod_l", evidence["correct_owner"])
        self.assertNotEqual(evidence["firmware_target_prefix"],
                            evidence["lib_a_strtoll_prefix"])


if __name__ == "__main__":
    unittest.main()
