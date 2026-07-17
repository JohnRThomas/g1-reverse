import hashlib
import json
import unittest
from pathlib import Path

from capstone import Cs, CS_ARCH_ARM, CS_MODE_MCLASS, CS_MODE_THUMB
from capstone.arm import ARM_OP_IMM, ARM_REG_PC, ARM_REG_R1


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
CATALOG = ROOT / "recon/catalogs/net_packet_airtime_abi.json"
BASE = 0x01008000
TARGET = 0x010109EC
CALLERS = {
    0x01011D14: 0xBE,
    0x010122B4: 0x46,
    0x01012438: 0x204,
}
EXPECTED_CALLS = {0x01011D70, 0x010122E4, 0x0101262C}


def decoder():
    md = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
    md.detail = True
    return md


def decode(blob, address, size):
    start = address - BASE
    return list(decoder().disasm(blob[start:start + size], address))


def direct_calls_to(blob, target):
    """Scan every Thumb halfword, including code after embedded data islands."""
    md = decoder()
    found = set()
    for offset in range(0, len(blob) - 3, 2):
        insn = next(md.disasm(blob[offset:offset + 4], BASE + offset,
                              count=1), None)
        if (insn is not None and insn.size == 4 and insn.mnemonic == "bl" and
                branch_target(insn) == target):
            found.add(insn.address)
    return found


def branch_target(insn):
    if not insn.operands or insn.operands[0].type != ARM_OP_IMM:
        return None
    return insn.operands[0].imm & 0xFFFFFFFF


def is_return(insn):
    if insn.mnemonic == "bx" and insn.op_str == "lr":
        return True
    return insn.mnemonic.startswith("pop") and "pc" in insn.op_str


def r1_is_dead_after(insns, call_address):
    """Prove every post-call path returns or overwrites r1 before reading it."""
    by_address = {insn.address: insn for insn in insns}
    call = by_address[call_address]
    work = [call.address + call.size]
    seen = set()
    while work:
        address = work.pop()
        if address in seen:
            continue
        seen.add(address)
        insn = by_address.get(address)
        if insn is None:
            return False
        if is_return(insn):
            continue
        reads, writes = insn.regs_access()
        if ARM_REG_R1 in reads:
            return False
        if ARM_REG_R1 in writes:
            continue
        if insn.mnemonic in ("bl", "blx"):
            # An intervening call may consume any AAPCS argument register.
            return False
        target = branch_target(insn) if insn.mnemonic.startswith("b") else None
        conditional = insn.mnemonic not in ("b", "b.w")
        if target is not None:
            work.append(target)
        if target is None or conditional:
            work.append(insn.address + insn.size)
    return True


class NetPacketAirtimeAbiTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.blob = IMAGE.read_bytes()
        cls.report = json.loads(CATALOG.read_text())

    def test_catalog_pins_scalar_abi_and_backmap(self):
        self.assertEqual(hashlib.sha256(self.blob).hexdigest(),
                         self.report["image_sha256"])
        self.assertEqual(self.report["address"], "0x010109ec")
        self.assertEqual(self.report["extent"], "0x540")
        self.assertEqual(self.report["return_kind"], "i32")
        self.assertEqual(
            self.report["backmap"]["controller_packet_airtime_compute"],
            "FUN_010109ec",
        )

    def test_original_has_exactly_the_reviewed_direct_calls(self):
        # Whole-image halfword scanning makes the guard fail closed if a
        # previously unknown caller appears outside the reviewed functions.
        self.assertEqual(direct_calls_to(self.blob, TARGET), EXPECTED_CALLS)
        self.assertEqual(
            {int(row["callsite"], 16) for row in self.report["callers"]},
            EXPECTED_CALLS,
        )

    def test_r1_is_dead_on_every_post_call_path(self):
        all_insns = {
            insn.address: insn
            for address, size in CALLERS.items()
            for insn in decode(self.blob, address, size)
        }
        # Each analysis receives the complete union because FUN_01012438's
        # call branches backward within its own body after returning.
        insns = list(all_insns.values())
        for callsite in EXPECTED_CALLS:
            with self.subTest(callsite=hex(callsite)):
                self.assertTrue(r1_is_dead_after(insns, callsite))

    def test_reconstruction_and_verifier_do_not_claim_a_pair(self):
        source = (ROOT / "recon/net/src/FUN_010109ec.c").read_text()
        verifier = (ROOT / "tools/cfg_verify.py").read_text()
        self.assertIn("uint32_t FUN_010109ec(", source)
        self.assertNotIn("uint64_t FUN_010109ec(", source)
        self.assertIn('(\"net\", 0x010109ec): \"i32\"', verifier)
        self.assertNotIn('(\"net\", 0x010109ec): \"i64\"', verifier)


if __name__ == "__main__":
    unittest.main()
