"""Fail-closed checks for the corrected CPUNET Oberon serializer owner."""

import importlib.util
import gzip
import json
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB

import net_extract


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/net_oberon_mod_p256_to_bytes_exact.json"
OVERRIDES = ROOT / "recon/catalogs/function_name_overrides.json"
_SPEC = importlib.util.spec_from_file_location(
    "build_net_oberon_mod_p256_to_bytes",
    ROOT / "tools/build_net_oberon_mod_p256_to_bytes.py")
builder = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(builder)


class NetOberonModP256ToBytesTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_receipt_rebuilds_from_pinned_archive(self):
        self.assertEqual(builder.build(), self.receipt)
        self.assertEqual([], self.receipt["upstream"]["relocation_offsets"])
        self.assertEqual(52, self.receipt["upstream"]["section_size"])
        self.assertEqual("complete-section-byte-exact",
                         self.receipt["firmware_proof"]["match"])

    def test_prior_from_bytes_identity_is_rejected_by_exact_bytes(self):
        rejected = self.receipt["rejected_identity"]
        self.assertEqual("ocrypto_mod_p256_from_bytes", rejected["symbol"])
        self.assertEqual("0x01038f70", rejected["actual_analysis_va"])
        self.assertNotEqual(rejected["section_sha256"],
                            self.receipt["upstream"]["section_sha256"])

        code = list(Cs(CS_ARCH_ARM, CS_MODE_THUMB).disasm(
            net_extract.read_analysis(0x01038FA4, 52), 0x01038FA4))
        loads = [ins.op_str for ins in code if ins.mnemonic == "ldr"]
        stores = [ins.op_str for ins in code if ins.mnemonic == "str"]
        self.assertEqual("r3, [r1, #0x1c]", loads[0])
        self.assertEqual("r3, [r0]", stores[0])
        self.assertEqual("r3, [r1]", loads[-1])
        self.assertEqual("r3, [r0, #0x1c]", stores[-1])

    def test_callers_and_abi_are_serialization_shaped(self):
        callers = self.receipt["firmware_proof"]["code_callers"]
        self.assertEqual(["0x01038d9c", "0x01038da0"],
                         [row["va"] for row in callers])
        self.assertIn("output[32]", self.receipt["identity"]["abi"])
        self.assertEqual(bytes.fromhex("00f002b9"),
                         net_extract.read_analysis(0x01038D9C, 4))
        caller = net_extract.read_analysis(0x01038DA0, 28)
        self.assertIn(bytes.fromhex("00f0fdf8"), caller)
        self.assertIn(bytes.fromhex("00f0f5b8"), caller)
        relocations = self.receipt["firmware_proof"][
            "archive_call_relocations"]
        self.assertEqual([0, 6, 22], [row["offset"] for row in relocations])
        self.assertTrue(all(row["target"] == "ocrypto_mod_p256_to_bytes"
                            for row in relocations))

        with gzip.open(ROOT / "recon/catalogs/refgraph_net.json.gz", "rt") as stream:
            graph = json.load(stream)["functions"]
        self.assertEqual(["0x1038da0"], graph["0x1038fa4"]["callers"])

    def test_version_claim_stops_at_archive_family(self):
        version = self.receipt["version_precision"]
        self.assertIn("v2.4.0", version["archive_blob_identical_tags"])
        self.assertIn("v2.5.3", version["archive_blob_identical_tags"])
        self.assertIn("cannot distinguish", version["limitation"])
        self.assertEqual("NCS/nrfxlib v2.5.1",
                         self.receipt["upstream"]["manifest_pin"])

    def test_durable_name_preserves_raw_identity_and_sdc_policy(self):
        override = json.loads(OVERRIDES.read_text())["net"]["0x01038fa4"]
        self.assertEqual("ocrypto_mod_p256_to_bytes", override["name"])
        self.assertIn("FUN_01038fa4", override["evidence"])
        self.assertTrue(self.receipt["policy"]["raw_backmap_preserved"])
        self.assertEqual("report_only_unchanged",
                         self.receipt["policy"]["sdc_policy"])


if __name__ == "__main__":
    unittest.main()
