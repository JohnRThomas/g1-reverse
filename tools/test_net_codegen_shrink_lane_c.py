import json
import unittest
from pathlib import Path

import build_net_codegen_shrink_lane_c as builder


class NetCodegenShrinkLaneCTest(unittest.TestCase):
    def test_receipt_replays(self):
        expected = json.loads(builder.OUTPUT.read_text())
        self.assertEqual(expected, builder.build_receipt())

    def test_policy_and_exact_delta(self):
        receipt = json.loads(builder.OUTPUT.read_text())
        self.assertEqual(-44, receipt["summary"]["production_function_bytes_delta"])
        self.assertTrue(receipt["policy"]["sdc_functions_retained_report_only"])
        self.assertFalse(receipt["policy"]["automatic_sdc_removal"])
        self.assertFalse(receipt["policy"]["archive_or_stock_substitution"])
        self.assertEqual(
            {"FUN_010225ac", "FUN_0102524c"},
            {row["raw_symbol"] for row in receipt["reviewed_without_change"]},
        )


if __name__ == "__main__":
    unittest.main()
