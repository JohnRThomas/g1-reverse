#!/usr/bin/env python3
"""Regression gates for the binary-derived CPUAPP root inventory."""

import json
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class AppRootInventoryTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.data = json.loads((ROOT / "recon/catalogs/app_root_inventory.json").read_text())

    def test_vector_and_exception_roots(self):
        vectors = self.data["vectors"]
        self.assertEqual(85, vectors["word_count"])
        rows = {row["index"]: row for row in vectors["entries"]}
        self.assertEqual("0x200312f0", rows[0]["target"]["raw"])
        self.assertEqual("0x00050a98", rows[1]["target"]["va"])
        self.assertEqual("0x00067538", rows[26]["target"]["va"])
        self.assertEqual("0x00067528", rows[28]["target"]["va"])

    def test_init_order_and_exact_stock_owners(self):
        levels = {row["level"]: row for row in self.data["init_levels"]}
        self.assertEqual(17, levels["PRE_KERNEL_1"]["count"])
        self.assertEqual(1, levels["PRE_KERNEL_2"]["count"])
        self.assertEqual(28, levels["POST_KERNEL"]["count"])
        self.assertEqual(2, levels["APPLICATION"]["count"])
        names = [entry["name"] for level in self.data["init_levels"]
                 for entry in level["entries"]]
        for name in ("remoteproc_mgr_boot", "bt_rpmsg_init", "long_wq_init",
                     "mcumgr_handlers_init", "smp_init", "sync_rtc_setup"):
            self.assertIn(name, names)
        self.assertEqual(4, names.count("regulator_npm1300_init"))

    def test_device_and_isr_topology(self):
        devices = self.data["devices"]
        self.assertEqual(26, devices["count"])
        self.assertEqual(24, devices["stride"])
        self.assertIn("CONFIG_PM_DEVICE", devices["required_kconfig"])
        by_name = {row["name"]: row for row in devices["entries"]}
        self.assertIsNone(by_name["lsm6dso"]["init"])
        self.assertEqual("qspi_nor_init", by_name["qspi_nor"]["init"])
        isrs = {row["irq"]: row for row in self.data["sw_isr_table"]["non_default"]}
        self.assertEqual(11, len(isrs))
        self.assertEqual("rtc_nrf_isr", isrs[21]["name"])
        self.assertEqual("nrfx_qspi_irq_handler", isrs[43]["name"])

    def test_runtime_thread_and_static_storage_lifecycle(self):
        threads = {row["name"]: row for row in self.data["dynamic_threads"]}
        self.assertEqual("0x00019718", threads["ancs"]["entry_candidates"][0])
        self.assertEqual(0x1400, threads["ancs"]["stack_size"])
        self.assertEqual("runtime_k_thread_create", threads["display"]["lifecycle"])
        msgqs = {row["name"]: row for row in self.data["static_msgqs"]}
        self.assertEqual((204, 18), (msgqs["audio"]["message_size"],
                                    msgqs["audio"]["max_messages"]))
        self.assertTrue(all(row["lifecycle"] == "rom_static_initializer"
                            for row in msgqs.values()))

    def test_catalog_missing_thread_entries_are_exact_code_roots(self):
        threads = {row["name"]: row for row in self.data["dynamic_threads"]}
        self.assertEqual(["0x0002692c"], threads["run_main_e"]["entry_candidates"])
        self.assertEqual(["0x00027cfc"], threads["run_main_f"]["entry_candidates"])
        self.assertEqual(["0x00032420"], threads["aging_a"]["entry_candidates"])
        names = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        expected = {
            "0x0002692c": "master_display_thread",
            "0x00027cfc": "slave_display_thread",
            "0x00032420": "aging_mode_thread",
        }
        self.assertEqual(expected, {address: names["by_address"][address]["name"]
                                    for address in expected})


if __name__ == "__main__":
    unittest.main()
