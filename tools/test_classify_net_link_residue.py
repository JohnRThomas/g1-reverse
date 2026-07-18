import json
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PYTHON = ROOT / ".venv/bin/python"


class NetLinkResidueTest(unittest.TestCase):
    def test_generated_catalog_is_complete_and_partitioned(self):
        with tempfile.TemporaryDirectory() as temp:
            output = Path(temp) / "report.json"
            markdown = Path(temp) / "report.md"
            subprocess.run(
                [
                    str(PYTHON), str(ROOT / "tools/classify_net_link_residue.py"),
                    "--json", str(output), "--markdown", str(markdown),
                ],
                cwd="/tmp", check=True, capture_output=True, text=True,
                env={"PYTHONSAFEPATH": "1"},
            )
            generated = json.loads(output.read_text())
            committed = json.loads(
                (ROOT / "recon/catalogs/net_link_function_residue.json").read_text()
            )
            self.assertEqual(generated, committed)
            total = generated["summary"]["classified_residue"]
            self.assertEqual(
                sum(generated["summary"]["by_category"].values()), total
            )
            self.assertEqual(len(generated["entries"]), total)
            self.assertEqual(
                len({entry["symbol"] for entry in generated["entries"]}), total
            )

    def test_high_risk_policy_examples(self):
        report = json.loads(
            (ROOT / "recon/catalogs/net_link_function_residue.json").read_text()
        )
        by_symbol = {entry["symbol"]: entry for entry in report["entries"]}
        self.assertNotIn("controller_default_bounds_build", by_symbol)
        self.assertNotIn("controller_timing_defaults_apply", by_symbol)
        self.assertEqual(
            by_symbol["rtc_compare_event_clear"]["category"],
            "sdk_or_config_symbol",
        )
        self.assertEqual(
            by_symbol["FUN_shadow_default"]["category"],
            "compiler_or_ghidra_pseudo",
        )
        # These previously reported integration residues have been resolved;
        # the refreshed catalog must not silently reintroduce them.
        self.assertNotIn("g_21000ea7", by_symbol)
        self.assertNotIn("FUN_01008fc0", by_symbol)
        self.assertNotIn("controller_assert", by_symbol)

    def test_all_former_missing_entries_have_exact_recovery_closure(self):
        report = json.loads(
            (ROOT / "recon/catalogs/net_link_function_residue.json").read_text()
        )
        missing = [
            entry for entry in report["entries"]
            if entry["category"] == "true_missing_reconstructed_entry"
        ]
        self.assertEqual(missing, [])
        self.assertEqual(report["summary"]["actionable_net_reconstruction_count"], 0)
        self.assertEqual(report["summary"]["expected_unknown_count"], 0)
        self.assertEqual(len(report["recovered_link_gaps"]), 20)
        self.assertEqual(len(report["recovered_descendants"]), 13)
        recovered = report["recovered_link_gaps"] + report["recovered_descendants"]
        self.assertEqual(len({row["symbol"] for row in recovered}), 33)
        self.assertTrue(all(row["cfg_status"] == "PASS" for row in recovered))
        self.assertTrue(all(len(row["source_sha256"]) == 64 for row in recovered))
        self.assertTrue(all(len(row["receipt_sha256"]) == 64 for row in recovered))


if __name__ == "__main__":
    unittest.main()
