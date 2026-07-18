import json
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_settings_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
STATE = ROOT / "recon/symbols/g1_app_sdk_state.ld"


class SettingsStockAdoptionTest(unittest.TestCase):
    def setUp(self):
        self.receipt = json.loads(RECEIPT.read_text())
        self.group = set(self.receipt["atomic_group"])
        self.entries = {row["va"]: row for row in
                        json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}

    def test_exact_atomic_group_is_excluded(self):
        self.assertEqual(12, len(self.group))
        self.assertTrue(all(self.entries[va]["exclude_reconstruction"]
                            for va in self.group))
        self.assertTrue(all(row["instruction_exact"] and
                            row["relocation_masked_byte_exact"]
                            for row in self.receipt["authorizations"]))

    def test_sources_are_not_retained(self):
        text = RETAINED.read_text()
        for row in self.receipt["authorizations"]:
            self.assertNotIn(Path(row["reconstruction_source"]).name, text)

    def test_private_state_is_pinned(self):
        text = STATE.read_text()
        for symbol, address in self.receipt["private_state_pins"].items():
            self.assertIn("%s = %s;" % (symbol, address), text)

    def test_expected_link_contract(self):
        delta = self.receipt["expected_link_delta"]
        self.assertEqual((28, 22), (delta["before"], delta["after"]))
        self.assertEqual([], delta["added"])
        self.assertEqual(["FUN_0005463e", "FUN_00054688"],
                         delta["unresolved"])


if __name__ == "__main__":
    unittest.main()
