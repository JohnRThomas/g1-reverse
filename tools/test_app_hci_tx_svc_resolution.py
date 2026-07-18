import json
import os
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_hci_tx_svc_resolution.json"


class HciTxSvcResolutionTest(unittest.TestCase):
    def test_receipt_is_current(self):
        env = dict(os.environ, PYTHONSAFEPATH="1",
                   PYTHONPATH=str(ROOT / "tools"))
        subprocess.run([
            str(ROOT / ".venv/bin/python"),
            str(ROOT / "tools/build_app_hci_tx_svc_resolution.py"),
            "--check",
        ], cwd="/tmp", env=env, check=True, capture_output=True, text=True)

    def test_sites_are_in_body_not_functions(self):
        data = json.loads(RECEIPT.read_text())
        self.assertEqual("resolved_in_containing_owner", data["status"])
        self.assertEqual("hci_tx_thread", data["owner"]["name"])
        self.assertEqual(2, len(data["sites"]))
        self.assertEqual({"FUN_0005463e", "FUN_00054688"},
                         set(data["resolution"]["fake_function_entries_removed"]))
        self.assertFalse(data["policy"]["linker_aliases_emitted"])
        self.assertFalse(data["policy"]["invented_functions"])


if __name__ == "__main__":
    unittest.main()
