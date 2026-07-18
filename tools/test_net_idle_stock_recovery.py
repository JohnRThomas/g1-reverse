import os
import sys
import unittest

BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(BASE, "tools"))

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB

import cfg_verify
import net_extract
from parity import recon


class NetIdleStockRecoveryTest(unittest.TestCase):
    def test_nrf53_idle_prepare_uses_real_exclusive_monitor(self):
        source_path = os.path.join(BASE, "recon", "net", "src",
                                   "FUN_0102d0c4.c")
        source = open(source_path).read()
        self.assertIn("z_arm_on_enter_cpu_idle_prepare", source)
        self.assertIn("(void)__LDREXB(CPU_IDLE_PREPARE_MONITOR_DUMMY);", source)
        self.assertEqual(source.count("__DMB();"), 3)

        body = source[source.index("*/") + 2:]
        compiled, error = recon.compile_func(body, "FUN_0102d0c4", 0x0102d0c4)
        self.assertIsNone(error, error)
        code, _tail, size, va = compiled
        md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        mnemonics = [ins.mnemonic for ins in md.disasm(code[:size], va)]
        self.assertEqual(mnemonics.count("ldrexb"), 1)
        self.assertGreaterEqual(mnemonics.count("dmb"), 3)
        self.assertEqual(net_extract.read(0x0102d0c6, 6),
                         bytes.fromhex("354bd3e84f3f"))

    def test_idle_prepare_proves_every_reviewed_mmio_arm(self):
        verdict = cfg_verify.verify("net", "FUN_0102d0c4", trials_random=0)
        self.assertEqual(verdict["status"], "PASS", verdict)
        self.assertEqual(verdict["cover_cases"], 9, verdict)

        source_path = os.path.join(BASE, "recon", "net", "src",
                                   "FUN_0102d0c4.c")
        source = open(source_path).read()
        wrong = source.replace("pretick_cc_to_counter < 3u",
                               "pretick_cc_to_counter < 1u", 1)
        self.assertNotEqual(source, wrong)
        negative = cfg_verify.verify("net", "FUN_0102d0c4", trials_random=0,
                                     source_override=wrong)
        self.assertEqual(negative["status"], "FAIL", negative)
        self.assertGreater(negative.get("checked", 0), 0, negative)

    def test_arch_cpu_idle_stock_sequence_and_wfi_contract(self):
        source_path = os.path.join(BASE, "recon", "net", "src",
                                   "FUN_0102e9bc.c")
        source = open(source_path).read()
        self.assertIn("arch/arm/core/aarch32/cpu_idle.S:arch_cpu_idle", source)
        self.assertNotIn("__get_CONTROL", source)
        self.assertIn("__WFI();", source)

        body = source[source.index("*/") + 2:]
        compiled, error = recon.compile_func(body, "FUN_0102e9bc", 0x0102e9bc)
        self.assertIsNone(error, error)
        code, _tail, size, _va = compiled
        self.assertEqual(code[:size].count(bytes.fromhex("30bf")), 1)
        self.assertEqual(net_extract.read(0x0102e9e0, 4),
                         bytes.fromhex("30bf00bf"))
        self.assertEqual(set(recon.LAST_DIRECT_TARGET_MAP.values()),
                         {0x0102d0c4, 0x0102d1c0})

        verdict = cfg_verify.verify("net", "FUN_0102e9bc", trials_random=0)
        self.assertEqual(verdict["status"], "PASS", verdict)


if __name__ == "__main__":
    unittest.main()
