#!/usr/bin/env python3
"""Regression and mutation gates for the CPUNET boot-root closure."""

import json
import unittest
from pathlib import Path

import cfg_verify
import net_recon_kit
from build_net_esb_boot_root import OUTPUT, build


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon/net/src/FUN_0102a720.c"
NET_CMAKE = ROOT / "recon/application/net/CMakeLists.txt"
STOCK_ALIASES = ROOT / "recon/application/net/src/stock_call_aliases.ld"


class NetEsbBootRootTest(unittest.TestCase):
    def test_production_root_is_live_without_wrapper_code(self):
        cmake = NET_CMAKE.read_text()
        aliases = STOCK_ALIASES.read_text()
        self.assertIn('../../net/src/FUN_0102a720.c"', cmake)
        self.assertNotIn(
            '${ZEPHYR_BASE}/samples/bluetooth/hci_rpmsg/src/main.c', cmake)
        self.assertIn("-Wl,-u,FUN_0102a720", cmake)
        self.assertIn("-Wl,-u,FUN_0102b758", cmake)
        self.assertIn("main = FUN_0102a720;", aliases)

    def test_receipt_and_extents(self):
        self.assertEqual(net_recon_kit.TRUE_SIZE_OVERRIDES[0x0102A720], 0x3E8)
        self.assertEqual(cfg_verify.TRUE_SIZE_OVERRIDES[("net", 0x0102A720)], 0x3E8)
        self.assertEqual(build(), json.loads(OUTPUT.read_text()))

    def test_directed_cfg_and_mutations(self):
        source = SOURCE.read_text()
        verdict = cfg_verify.verify("net", "FUN_0102a720", trials_random=0)
        self.assertEqual((verdict["status"], verdict["checked"]), ("PASS", 5))
        mutations = (
            ("state->role == 1 ? 0 : 1", "state->role == 1 ? 1 : 0"),
            (">= UINT64_C(10000)", ">= UINT64_C(30000)"),
            ("crossing_count > 2", "crossing_count > 3"),
        )
        for correct, wrong in mutations:
            self.assertIn(correct, source)
            mutated = source.replace(correct, wrong, 1)
            result = cfg_verify.verify(
                "net", "FUN_0102a720", trials_random=0,
                source_override=mutated)
            self.assertEqual(result["status"], "FAIL", (correct, result))


if __name__ == "__main__":
    unittest.main()
