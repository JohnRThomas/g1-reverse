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
            by_symbol["FUN_0100938c"]["category"],
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
        self.assertEqual(
            by_symbol["g_21000ea7"]["category"],
            "data_or_global_alias_gap",
        )
        # These previously reported integration residues have been resolved;
        # the refreshed catalog must not silently reintroduce them.
        self.assertNotIn("FUN_01008fc0", by_symbol)
        self.assertNotIn("controller_assert", by_symbol)


if __name__ == "__main__":
    unittest.main()
