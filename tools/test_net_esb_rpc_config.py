#!/usr/bin/env python3
"""Fail-closed evidence gate for the shipped CPUNET ESB/nRF-RPC config."""

import struct
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
IMAGE = ROOT / "netcore_image.bin"
CONFIG = ROOT / "recon/application/net/prj.conf"

RUNTIME_BASE = 0x01008800
LOG_CONST_START = 0x337EC
LOG_CONST_COUNT = 32
STATIC_TIMESLOT_THREAD_START = 0x337C0
TIMESLOT_CALLBACK_LITERAL = 0x238E4
INIT_TABLE_START = 0x33664
MISSING_STOCK_INIT_ROWS = {
    0x3366C: 0x010302C1,  # pthread_barrier_pool_init
    0x33674: 0x01030311,  # pthread_cond_pool_init
    0x3367C: 0x01030349,  # pthread_mutex_pool_init
    0x33684: 0x01030385,  # posix_thread_pool_init
    0x3369C: 0x0103669D,  # init_mem_slab_module
    0x3372C: 0x01034935,  # check_ext_api_requests
}
EXPECTED_MODULES = [
    "NRFX_DPPI", "NRFX_GPIOTE", "NRFX_TIMER", "NRF_RPC",
    "NRF_RPC_CBOR", "NRF_RPC_OS", "app_esb", "bt_hci_raw", "bt_rpa",
    "bt_sdc_crypto", "bt_sdc_ecdh", "bt_sdc_hci_driver",
    "cbprintf_package", "clock_control", "esb", "fatal_error",
    "hci_rpmsg", "ipc_service", "log", "log_mgmt", "log_uart",
    "mbox_nrfx_ipc", "mpsl_init", "mpu", "net_buf", "net_buf_simple",
    "nrf_rpc_ipc", "os", "soc", "sync_rtc", "timeslot",
    "uart_nrfx_uarte",
]


def original_log_modules():
    image = IMAGE.read_bytes()
    rows = []
    for index in range(LOG_CONST_COUNT):
        offset = LOG_CONST_START + index * 8
        name_pointer, level = struct.unpack_from("<II", image, offset)
        string_offset = name_pointer - RUNTIME_BASE
        if not 0 <= string_offset < len(image):
            raise AssertionError(f"log module pointer out of range: {name_pointer:#x}")
        end = image.find(b"\0", string_offset)
        if end < 0:
            raise AssertionError(f"unterminated log module at {name_pointer:#x}")
        rows.append((image[string_offset:end].decode("ascii"), level))
    return rows


class NetEsbRpcConfigTest(unittest.TestCase):
    def test_original_iterable_table_proves_all_32_modules(self):
        rows = original_log_modules()
        self.assertEqual(EXPECTED_MODULES, [name for name, _ in rows])
        self.assertEqual([0, 0, 0], [level for _, level in rows[:3]])
        self.assertTrue(all(level == 3 for _, level in rows[3:]))

    def test_original_timeslot_owner_is_a_static_product_thread(self):
        image = IMAGE.read_bytes()
        static_thread = struct.unpack_from(
            "<11I", image, STATIC_TIMESLOT_THREAD_START
        )
        self.assertEqual(
            (
                0x21001ED0,  # struct k_thread
                0x21007940,  # 0x400-byte stack
                0x400,
                0x0102C011,  # runtime Thumb entry; analysis VA 0x0102b810
                0,
                0,
                0,
                0xFFFFFFF0,  # cooperative priority -16
                0,
                0,
                0x0103D252,  # "mpsl_nonpreemptible_thread_id"
            ),
            static_thread,
        )
        self.assertEqual(
            0x0102C145,
            struct.unpack_from("<I", image, TIMESLOT_CALLBACK_LITERAL)[0],
            "worker must pass the custom runtime Thumb callback at analysis VA 0x0102b944",
        )

        name_offset = static_thread[-1] - RUNTIME_BASE
        name_end = image.index(b"\0", name_offset)
        self.assertEqual(
            b"mpsl_nonpreemptible_thread_id", image[name_offset:name_end]
        )

    def test_original_init_table_proves_posix_fw_info_and_slab_owners(self):
        image = IMAGE.read_bytes()
        self.assertEqual(0, (0x33734 - INIT_TABLE_START) % 8)
        self.assertEqual(26, (0x33734 - INIT_TABLE_START) // 8)
        for offset, function_pointer in MISSING_STOCK_INIT_ROWS.items():
            self.assertEqual(
                (function_pointer, 0),
                struct.unpack_from("<II", image, offset),
                f"original init record at file offset {offset:#x}",
            )

    def test_canonical_config_selects_proven_stock_owners(self):
        assignments = {
            line.split("=", 1)[0]: line.split("=", 1)[1]
            for line in CONFIG.read_text().splitlines()
            if line.startswith("CONFIG_") and "=" in line
        }
        for symbol in (
            "CONFIG_DYNAMIC_INTERRUPTS",
            "CONFIG_DYNAMIC_DIRECT_INTERRUPTS",
            "CONFIG_ESB",
            "CONFIG_ESB_DYNAMIC_INTERRUPTS",
            "CONFIG_NRF_RPC",
            "CONFIG_POSIX_API",
            "CONFIG_FW_INFO",
        ):
            self.assertEqual("y", assignments.get(symbol), symbol)
        self.assertEqual(
            "1",
            assignments.get("CONFIG_MPSL_TIMESLOT_SESSION_COUNT"),
            "the shipped custom timeslot worker opens one MPSL session",
        )

    def test_private_sdc_policy_is_not_replaced_by_config_selection(self):
        text = (ROOT / "recon/application/net/CMakeLists.txt").read_text()
        self.assertIn("G1_PRIVATE_REPORT_ONLY_SOURCES", text)
        self.assertNotIn("--undefined=FUN_", text)


if __name__ == "__main__":
    unittest.main()
