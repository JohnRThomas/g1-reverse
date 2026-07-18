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
        self.assertEqual(
            by_symbol["controller_default_bounds_build"]["category"],
            "true_missing_reconstructed_entry",
        )
        self.assertEqual(
            by_symbol["controller_default_bounds_build"]["va"],
            "0x010282fc",
        )
        self.assertEqual(
            by_symbol["controller_default_bounds_build"]["closeout_disposition"],
            "private_sdc_report_only",
        )
        self.assertEqual(
            by_symbol["controller_timing_defaults_apply"]["category"],
            "true_missing_reconstructed_entry",
        )
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

    def test_all_true_missing_entries_have_non_actionable_closeout(self):
        report = json.loads(
            (ROOT / "recon/catalogs/net_link_function_residue.json").read_text()
        )
        missing = [
            entry for entry in report["entries"]
            if entry["category"] == "true_missing_reconstructed_entry"
        ]
        self.assertTrue(missing)
        self.assertTrue(all(entry["closeout_disposition"] for entry in missing))
        self.assertTrue(all(entry["closeout_actionable"] is False for entry in missing))
        self.assertEqual(
            report["summary"]["actionable_net_reconstruction_count"], 0
        )
        explicit = {
            "FUN_0100ef08": "private_sdc_report_only",
            "FUN_01011664": "private_sdc_report_only",
            "FUN_01018df8": "private_sdc_report_only",
            "FUN_0101d890": "private_sdc_report_only",
            "FUN_0102665c": "private_sdc_report_only",
            "FUN_010292ec": "private_sdc_report_only",
            "FUN_0102a1e0": "private_sdc_report_only",
            "controller_entry_links_release": "private_sdc_report_only",
            "controller_timing_defaults_apply": "private_sdc_report_only",
            "sdc_conn_event_process": "private_sdc_report_only",
            "FUN_0102fa84": "blocked_c_unexpressible",
            "FUN_0102d25c": "anomalous_non_executable_target",
            "controller_default_bounds_build": "private_sdc_report_only",
        }
        by_symbol = {entry["symbol"]: entry for entry in missing}
        self.assertEqual(
            {symbol: by_symbol[symbol]["closeout_disposition"]
             for symbol in explicit},
            explicit,
        )


if __name__ == "__main__":
    unittest.main()
