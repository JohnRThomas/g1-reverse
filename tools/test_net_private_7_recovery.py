import importlib.util
import json
import re
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location(
    "net_private_7", ROOT / "tools/build_net_private_7_receipt.py")
BUILDER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BUILDER)
RECEIPT = ROOT / "recon/ownership/net_private_7_recovery.json"


class NetPrivate7RecoveryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuilds_via_authoritative_cfg_verify(self):
        self.assertEqual(BUILDER.build(), self.receipt)

    def test_complete_worklist_shard_and_true_extents(self):
        self.assertEqual(13, self.receipt["summary"]["function_count"])
        self.assertEqual(1000, self.receipt["summary"]["total_true_executable_extent"])
        self.assertEqual(2, self.receipt["summary"]["catalog_missed_extent_injections"])

    def test_every_function_passes_substantive_cfg_verification(self):
        for row in self.receipt["functions"]:
            self.assertEqual("PASS", row["cfg_verify"]["status"])
            self.assertGreaterEqual(row["cfg_verify"]["checked"], 80)

    def test_sources_preserve_raw_backmaps_and_are_not_blobs(self):
        for row in self.receipt["functions"]:
            source = (ROOT / row["source"]).read_text()
            address = re.search(r"@\s+(0x[0-9a-fA-F]+)", source.splitlines()[0])
            self.assertIsNotNone(address)
            self.assertEqual(int(row["analysis_address"], 16),
                             int(address.group(1), 16))
            self.assertIn(row["raw_backmap"], source)
            self.assertNotIn(".byte", source)
            self.assertNotIn('__asm__(".inst', source)

    def test_scope_policy_is_fail_closed(self):
        policy = self.receipt["policy"]
        self.assertTrue(policy["canonical_readable_c_only"])
        self.assertTrue(policy["archive_or_blob_substitution_forbidden"])
        self.assertTrue(policy["shared_generated_or_name_outputs_untouched"])


if __name__ == "__main__":
    unittest.main()
