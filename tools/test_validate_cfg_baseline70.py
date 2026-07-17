import copy
import json
import unittest

import validate_cfg_baseline70 as validator


class ValidateCfgBaseline70Test(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = json.loads(validator.CATALOG.read_text())

    def test_committed_catalog_is_closed_and_sources_exist(self):
        self.assertEqual(
            validator.validate(self.data),
            {
                "historical_entries": 70,
                "authoritative_cfg_pass": 69,
                "owned_interior": 1,
                "unresolved": 0,
            },
        )

    def test_missing_pass_is_fail_closed(self):
        data = copy.deepcopy(self.data)
        data["authoritative_cfg_pass_0157de4"].pop()
        with self.assertRaisesRegex(validator.CatalogError, "unresolved baseline"):
            validator.validate(data, check_sources=False)

    def test_exception_requires_owner_pass_receipt(self):
        data = copy.deepcopy(self.data)
        del data["verification_receipts"]["0157de4"]["net:FUN_010333b4"]
        with self.assertRaisesRegex(validator.CatalogError, "no PASS receipt"):
            validator.validate(data, check_sources=False)

    def test_summary_cannot_hide_unresolved_state(self):
        data = copy.deepcopy(self.data)
        data["resolution_summary"]["unresolved"] = 1
        with self.assertRaisesRegex(validator.CatalogError, "resolution_summary.unresolved"):
            validator.validate(data, check_sources=False)


if __name__ == "__main__":
    unittest.main()
