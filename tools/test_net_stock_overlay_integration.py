#!/usr/bin/env python3
"""Fail-closed checks for the combined CPUNET stock-owner overlays."""

import unittest

import build_adoption_manifest as adoption


class NetStockOverlayIntegrationTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        result = adoption.build(dict(adoption.DEFAULTS))
        cls.rows = {row["va"]: row
                    for row in result["cores"]["net"]["entries"]}

    def test_corrected_and_public_owners_are_selected(self):
        expected = {
            "0x0100823c": "__aeabi_uldivmod",
            "0x01025d38": "__udivmoddi4",
            "0x0102a244": "strcmp",
            "0x0102d25c": "arch_busy_wait",
            "0x0102eb2c": "arch_irq_enable",
            "0x0102fa84": "__chk_fail",
            "0x010353ec": "virtqueue_add_consumed_buffer",
            "0x01038fa4": "ocrypto_mod_p256_to_bytes",
            "0x0103a056": "ipc_static_vrings_shm_size",
            "0x0103ab0e": "metal_io_block_write",
            "0x0103ac50": "virtqueue_get_available_buffer",
            "0x0103b0e8": "z_impl_k_busy_wait",
            "0x0103b304": "sys_timepoint_calc",
            "0x0103b34c": "sys_timepoint_timeout",
            "0x0103b53a": "__memcpy_chk",
            "0x0103b5c4": "strnlen",
            "0x0103b614": "__aeabi_memcpy4",
            "0x0103b62e": "memset",
        }
        for va, symbol in expected.items():
            with self.subTest(va=va):
                self.assertEqual(self.rows[va]["upstream_symbol"], symbol)
                self.assertTrue(self.rows[va]["exclude_reconstruction"])

    def test_wrong_oberon_identity_is_not_retained(self):
        row = self.rows["0x01038fa4"]
        self.assertNotEqual(row["upstream_symbol"],
                            "ocrypto_mod_p256_from_bytes")
        evidence = row["evidence"][-1]
        self.assertEqual(evidence["rejected_identity"],
                         "ocrypto_mod_p256_from_bytes")

    def test_private_sdc_policy_remains_fail_closed(self):
        private_sdc = [row for row in self.rows.values()
                       if row.get("component") == "softdevice_controller" and
                       not any(item.get("public_api") is True
                               for item in row.get("evidence", []))]
        self.assertTrue(private_sdc)
        self.assertTrue(all(not row["exclude_reconstruction"]
                            for row in private_sdc))


if __name__ == "__main__":
    unittest.main()
