import importlib.util
import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def load_full_link():
    spec = importlib.util.spec_from_file_location(
        "g1_full_link_for_test", ROOT / "tools/full_link.py")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    module.CORE = "net"
    module.OBJD = str(ROOT / "build/net_full_obj")
    return module


class NetFullLinkResidueIntegrationTest(unittest.TestCase):
    def test_every_nonpattern_residue_is_fail_closed_classified(self):
        module = load_full_link()
        report = module.link_and_report()
        audit = json.loads(
            (ROOT / "recon/catalogs/net_link_function_residue.json").read_text())
        expected_missing = sorted(
            row["symbol"] for row in audit["entries"]
            if row["category"] == "true_missing_reconstructed_entry")
        self.assertEqual(report["unknown"], expected_missing)
        self.assertEqual(len(report["unknown"]), 20)
        self.assertEqual(report["unknown_by_disposition"], {
            "hidden_entry_reconstruction_required": 1,
            "private_sdc_report_only": 18,
            "retained_reconstruction_required": 1,
        })
        self.assertEqual(report["reviewed_by_category"], {
            "compiler_or_ghidra_pseudo": 1,
        })


if __name__ == "__main__":
    unittest.main()
