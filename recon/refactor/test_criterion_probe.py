"""Tests for `criterion_probe.py` -- the measured criterion improvements.

The RADIO_TX numbers pinned here are the MEASURED ones from
`our_boot_bringup.md` 44.4 (four instrumented Renode captures) and from this
pass's re-derivation over the committed report directories.  If a future
capture moves them, this file is the place that says so.
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import criterion_probe as cp  # noqa: E402


def oracle(radio_tx, esb):
    return {"counters": {"RADIO_TX": "0x%016X" % radio_tx,
                         "ESB_MASTER_FRAMES": "0x%08X" % esb}}


class RadioTxComponentsTest(unittest.TestCase):

    def test_components_are_the_measured_shipped_values(self):
        c = cp.radio_tx_components(oracle(0x232, 0x175))
        self.assertEqual((c["RADIO_TX"], c["ESB_MASTER_FRAMES"], c["BLE_link_TX"]),
                         (562, 373, 189))

    def test_the_two_counters_are_parsed_at_DIFFERENT_widths(self):
        # the oracle really does spell them 16 and 8 hex digits wide; a parser
        # that keyed on width would read one of them wrong.
        c = cp.radio_tx_components(
            {"counters": {"RADIO_TX": "0x0000000000000232",
                          "ESB_MASTER_FRAMES": "0x00000175"}})
        self.assertEqual(c["BLE_link_TX"], 189)

    def test_missing_counter_is_reported_not_guessed(self):
        c = cp.radio_tx_components({"counters": {"RADIO_TX": "0x232"}})
        self.assertFalse(c["available"])
        self.assertIn("ESB_MASTER_FRAMES", c["why"])

    def test_THE_CANCELLATION_the_base_sum_agrees_while_both_halves_are_wrong(self):
        """The finding that motivates the field.

        in-tree base navigation: RADIO_TX 562 == shipped 562, but 374+188
        against 373+189.
        """
        r = cp.compare_radio_tx(oracle(0x232, 0x175), oracle(0x232, 374))
        self.assertEqual(r["sum_verdict"], "EQ")
        self.assertEqual(r["verdict"], "NE")
        self.assertTrue(r["cancellation"])
        self.assertEqual(r["fields"]["ESB_MASTER_FRAMES"]["delta"], +1)
        self.assertEqual(r["fields"]["BLE_link_TX"]["delta"], -1)

    def test_stage_07_closes_the_ESB_half_and_the_sum_calls_it_a_regression(self):
        """stage 07 navigation: 560 = 373 + 187."""
        r = cp.compare_radio_tx(oracle(0x232, 0x175), oracle(560, 373))
        self.assertEqual(r["sum_verdict"], "NE")          # 562 -> 560
        self.assertEqual(r["fields"]["ESB_MASTER_FRAMES"]["verdict"], "EQ")
        self.assertEqual(r["fields"]["BLE_link_TX"]["delta"], -2)
        self.assertFalse(r["cancellation"])

    def test_stage_04B_navigation_is_374_plus_190(self):
        r = cp.compare_radio_tx(oracle(0x232, 0x175), oracle(564, 374))
        self.assertEqual(r["fields"]["ESB_MASTER_FRAMES"]["delta"], +1)
        self.assertEqual(r["fields"]["BLE_link_TX"]["delta"], +1)

    def test_an_exactly_matching_image_is_EQ_on_both_components(self):
        r = cp.compare_radio_tx(oracle(0x232, 0x175), oracle(0x232, 0x175))
        self.assertEqual(r["verdict"], "EQ")
        self.assertFalse(r["cancellation"])


class EqualPopulationRuleTest(unittest.TestCase):

    def test_default_rule_excludes_a_burst_past_half_the_local_period(self):
        starts = [0, 100, 200, 300]
        deltas = [0, 0, 80, 0]           # 80 > 100/2
        self.assertEqual(cp.measurable_mask(starts, deltas),
                         [True, True, False, True])

    def test_equal_populations_drop_the_exclusion_when_the_rule_is_ON(self):
        starts = [0, 100, 200, 300]
        deltas = [0, 0, 80, 0]
        self.assertEqual(
            cp.measurable_mask(starts, deltas, equal_population=True,
                               equal_population_rule=True),
            [True, True, True, True])

    def test_UNEQUAL_populations_keep_the_exclusion_even_with_the_rule_ON(self):
        """The half that is not optional.

        Dropping the exclusion for unequal populations is what moves the derived
        bound to 7,498.630 ms on `twim1 npm1300`.
        """
        starts = [0, 100, 200, 300]
        deltas = [0, 0, 80, 0]
        self.assertEqual(
            cp.measurable_mask(starts, deltas, equal_population=False,
                               equal_population_rule=True),
            [True, True, False, True])

    def test_the_rule_is_off_by_default_so_it_cannot_widen_anything_silently(self):
        starts = [0, 100, 200, 300]
        deltas = [0, 0, 80, 0]
        self.assertEqual(cp.measurable_mask(starts, deltas, equal_population=True),
                         [True, True, False, True])

    def test_a_single_burst_train_is_measurable(self):
        self.assertEqual(cp.measurable_mask([0], [5]), [True])


if __name__ == "__main__":
    unittest.main()
