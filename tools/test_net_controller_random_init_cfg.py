"""CFG and identity regression for the controller xoroshiro64** initializer."""

import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM

import net_extract
from cfg_verify import REVIEWED_ORACLE_CASES, verify


ROOT = Path("/Users/freedomcoder/Projects/G1disasm2")
TARGET = 0x0100F5D8
EXTENT = 0x5A
RAND_POLL = 0x01009204


class NetControllerRandomInitCfgTest(unittest.TestCase):
    def test_original_extent_and_rand_poll_call_are_pinned(self):
        code = net_extract.func_bytes_padded(TARGET, EXTENT, 0)
        decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        decoder.detail = True
        instructions = list(decoder.disasm(code, TARGET))

        self.assertEqual(instructions[-1].address, 0x0100F630)
        self.assertEqual(instructions[-1].mnemonic, "pop")
        calls = [
            insn.operands[0].imm & 0xFFFFFFFF
            for insn in instructions
            if insn.mnemonic == "bl" and
            insn.operands and insn.operands[0].type == ARM_OP_IMM
        ]
        self.assertEqual(calls, [RAND_POLL])
        self.assertEqual(
            int.from_bytes(net_extract.read_analysis(0x0100F638, 4), "little"),
            0x9E3779BB,
        )

    def test_canonical_source_keeps_raw_backmap(self):
        canonical = (ROOT / "recon/net/src/FUN_0100f5d8.c").read_text()
        self.assertIn("seed both controller xoroshiro64** streams", canonical)
        self.assertIn("sdc_rand_poll @ 0x01009204", canonical)
        self.assertIn("extern void FUN_01009204", canonical)
        self.assertNotIn("extern void sys_rand_get", canonical)

    def test_stock_rand_source_layout_selects_blocking_slot(self):
        header = Path(
            "/Users/freedomcoder/ncs251/nrfxlib/softdevice_controller/include/"
            "sdc_soc.h"
        ).read_text()
        low = header.index("rand_prio_low_get")
        high = header.index("rand_prio_high_get")
        poll = header.index("rand_poll")
        self.assertLess(low, high)
        self.assertLess(high, poll)
        self.assertIn("sdc_rand_source_register", header)

    def test_directed_cfg_cases_pass_and_transition_is_live(self):
        cases = REVIEWED_ORACLE_CASES[("net", TARGET)]
        self.assertEqual(len(cases), 5)
        result = verify("net", "sdc_controller_random_init", trials_random=0)
        self.assertEqual(result["status"], "PASS", result)
        self.assertEqual(result["checked"], len(cases), result)

        source = (ROOT / "recon/net/src/FUN_0100f5d8.c").read_text()
        correct = "(second_xor << 9);"
        self.assertIn(correct, source)
        wrong = source.replace(correct, "(second_xor << 8);", 1)
        verdict = verify(
            "net", "FUN_0100f5d8", trials_random=0,
            source_override=wrong,
        )
        self.assertEqual(verdict["status"], "FAIL", verdict)


if __name__ == "__main__":
    unittest.main()
