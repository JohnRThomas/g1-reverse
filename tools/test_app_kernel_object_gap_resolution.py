#!/usr/bin/env python3
"""Fail-closed checks for the WS2 classic-kernel-object gap resolution."""

import json
import struct
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
RECEIPT = ROOT / "recon/ownership/app_kernel_object_gap_resolution.json"


def source(name: str) -> str:
    return (ROOT / "recon/app/src" / name).read_text()


class KernelObjectGapResolutionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.receipt = json.loads(RECEIPT.read_text())

    def test_all_ws2_candidates_are_resolved_once(self):
        expected = {
            "0x20004df0", "0x20002c30", "0x20006448", "0x20009fc0",
            "0x2000cc24", "0x20002144", "0x20006380", "0x20002000",
        }
        rows = self.receipt["objects"]
        self.assertEqual(expected, {row["address"] for row in rows})
        self.assertEqual(len(expected), len(rows))
        self.assertEqual("all_eight_ws2_type_guesses_rejected",
                         self.receipt["verdict"])

    def test_raw_bt_gatt_init_distinguishes_work_from_flags(self):
        image = (ROOT / "app_update.bin").read_bytes()

        def u32(va: int) -> int:
            off = va - 0xC200 + 512
            return struct.unpack_from("<I", image, off)[0]

        # Literal pool used by raw bt_gatt_init @0x5a954.  The three init
        # operands are 0x63a0, 0x6418 and 0x6350; 0x6448 is loaded only for
        # atomic_set_bit(SC_INDICATE_PENDING).
        self.assertEqual(0x200063A0, u32(0x5A9B8))
        self.assertEqual(0x20006418, u32(0x5A9C0))
        self.assertEqual(0x20006448, u32(0x5A9C4))
        self.assertEqual(0x20006350, u32(0x5A9CC))

        init = source("FUN_0005a954.c")
        self.assertIn("FUN_000732d4((void *)0x200063a0U", init)
        self.assertIn("FUN_000732d4((void *)0x20006418U", init)
        self.assertIn("FUN_000732d4((void *)0x20006350U", init)
        self.assertNotIn("FUN_000732d4((void *)0x20006448U", init)
        self.assertIn("FUN_000826e0((volatile uint32_t *)0x20006448U", init)

    def test_non_kernel_types_are_supported_by_recovered_accesses(self):
        clock = source("FUN_0004a4b4.c") + source("FUN_0004a4d0.c")
        for address in ("0x20004df0", "0x20004df4", "0x20004df8", "0x20004dfc"):
            self.assertIn(address, clock)

        gpiote = source("FUN_000659cc.c") + source("FUN_000659d8.c")
        self.assertIn("FUN_00064ef8(0x20002c30", gpiote)
        self.assertIn("FUN_00064eb8(0x20002c30", gpiote)

        uptime = source("FUN_0003629c.c")
        self.assertIn("volatile unsigned int*)0x20009fc0", uptime)

        errno_users = "".join(source(name) for name in (
            "FUN_000778f4.c", "FUN_00077e4c.c", "FUN_00078570.c",
            "FUN_00078598.c"))
        self.assertGreaterEqual(errno_users.count("0x2000cc24"), 4)

    def test_bt_dev_queue_and_db_hash_are_not_standalone_kernel_objects(self):
        rx = source("FUN_00053530.c") + source("FUN_000536b8.c")
        self.assertIn("FUN_0005f074(0x20002144", rx)  # net_buf_slist_put
        self.assertIn("FUN_0005f148(0x20002144", rx)  # net_buf_slist_get
        self.assertIn("0x20002980", rx)               # separate rx_work

        bt_dev = source("FUN_00052f68.c") + source("FUN_000549ec.c")
        self.assertIn("0x20002000UL + 7", bt_dev)

        db_hash = source("FUN_0005a250.c") + source("FUN_0005aba8.c")
        self.assertIn("0x20006380UL, 0x10", db_hash)
        self.assertIn("0x20006380,frame.work", db_hash)


if __name__ == "__main__":
    unittest.main()
