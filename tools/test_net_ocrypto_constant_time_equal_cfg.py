"""Exact-owner and CFG checks for net Oberon constant-time primitives."""

import gzip
import hashlib
import io
import json
import subprocess
import unittest
from pathlib import Path

import net_extract
from cfg_verify import BOUNDED_RANDOM_ARGS, verify
from elftools.elf.elffile import ELFFile


ROOT = Path("/Users/freedomcoder/Projects/G1disasm2")
EQUAL_VA = 0x01008810
ZERO_VA = 0x01008838
STOCK_ARCHIVE = Path(
    "/Users/freedomcoder/ncs251/nrfxlib/crypto/nrf_oberon/lib/"
    "cortex-m33+nodsp/soft-float/liboberon_3.0.13.a"
)
STOCK_MEMBER = "ocrypto_constant_time.s.obj"
AR = Path(
    "/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
    "arm-zephyr-eabi-ar"
)
RECEIPT = ROOT / "recon/ownership/net_oberon_constant_time_exact.json"


class OcryptoConstantTimeEqualCfgTest(unittest.TestCase):
    def test_reviewed_length_domain_is_nonzero_and_covers_live_call(self):
        self.assertEqual(
            BOUNDED_RANDOM_ARGS[("net", EQUAL_VA)][2], (1, 2, 3, 32))
        self.assertEqual(
            BOUNDED_RANDOM_ARGS[("net", ZERO_VA)][1], (1, 2, 3, 32))

        with gzip.open(ROOT / "recon/catalogs/refgraph_net.json.gz", "rt") as stream:
            graph = json.load(stream)["functions"]
        self.assertEqual(graph["0x1008810"]["callers"], ["0x1038d38"])
        self.assertEqual(graph["0x1008838"]["callers"], ["0x1038dbc"])

        # ocrypto_curve_p256_from64bytes compares its two 32-byte results.
        caller = net_extract.func_bytes_padded(0x01038D38, 90, 0)
        self.assertIn(bytes.fromhex("20226946"), caller)
        self.assertIn(bytes.fromhex("cff742fd"), caller)

    def test_pinned_oberon_owner_is_available(self):
        self.assertTrue(STOCK_ARCHIVE.is_file())
        header = Path(
            "/Users/freedomcoder/ncs251/nrfxlib/crypto/nrf_oberon/include/"
            "ocrypto_constant_time.h"
        ).read_text()
        self.assertIn("length > 0", header)
        self.assertIn("ocrypto_constant_time_equal", header)
        self.assertIn("ocrypto_constant_time_is_zero", header)

    def test_pinned_archive_member_is_byte_exact_for_complete_unit(self):
        receipt = json.loads(RECEIPT.read_text())
        self.assertEqual(
            receipt["upstream"]["archive_sha256"],
            hashlib.sha256(STOCK_ARCHIVE.read_bytes()).hexdigest())
        member = subprocess.check_output(
            [str(AR), "p", str(STOCK_ARCHIVE), STOCK_MEMBER])
        self.assertEqual(
            receipt["upstream"]["member_sha256"],
            hashlib.sha256(member).hexdigest())
        elf = ELFFile(io.BytesIO(member))
        text = elf.get_section_by_name(".text").data()
        self.assertEqual(receipt["exact_text"]["size"], len(text))
        self.assertEqual(text, net_extract.read_analysis(EQUAL_VA, len(text)))

        self.assertEqual(
            ["FUN_01008810", "FUN_01008838"],
            [row["raw_symbol"]
             for row in receipt["exact_text"]["functions"][:2]])
        self.assertEqual("report_only_unchanged",
                         receipt["policy"]["sdc_policy"])

    def test_cfg_verify_completes_with_checked_trials(self):
        for name in ("FUN_01008810", "FUN_01008838"):
            verdict = verify("net", name, trials_random=4)
            self.assertEqual(verdict["status"], "PASS", verdict)
            self.assertGreater(verdict["checked"], 0, verdict)

    def test_return_semantics_are_live(self):
        source = (ROOT / "recon/net/src/FUN_01008810.c").read_text()
        correct = "uVar1 = uVar1 | (*param_1 ^ *param_2);"
        self.assertIn(correct, source)
        verdict = verify(
            "net", "FUN_01008810", trials_random=4,
            source_override=source.replace(
                correct, "uVar1 = uVar1 ^ (*param_1 ^ *param_2);", 1),
        )
        self.assertEqual(verdict["status"], "FAIL", verdict)

        zero_source = (ROOT / "recon/net/src/FUN_01008838.c").read_text()
        zero_correct = "uVar1 |= *param_1;"
        self.assertIn(zero_correct, zero_source)
        zero_verdict = verify(
            "net", "FUN_01008838", trials_random=4,
            source_override=zero_source.replace(
                zero_correct, "uVar1 ^= *param_1;", 1),
        )
        self.assertEqual(zero_verdict["status"], "FAIL", zero_verdict)


if __name__ == "__main__":
    unittest.main()
