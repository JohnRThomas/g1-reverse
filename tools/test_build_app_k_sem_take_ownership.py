#!/usr/bin/env python3
"""Fail-closed tests for the CPUAPP public k_sem_take owner."""

import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import build_app_k_sem_take_ownership as subject


class AppKSemTakeOwnershipTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.catalog = subject.build()

    def test_exact_firmware_tail_and_backmap(self):
        self.assertEqual("0x0007cb48", self.catalog["wrapper_va"])
        self.assertEqual("0x00072908", self.catalog["owner_va"])
        self.assertEqual("f5f7debe", self.catalog["firmware"]["bytes"])
        self.assertEqual("b.w #0x72908", self.catalog["firmware"]["decode"])
        self.assertTrue(self.catalog["policy"]["raw_address_backmap_preserved"])

    def test_public_abi_is_tail_safe(self):
        self.assertEqual("CONFIG_USERSPACE=n", self.catalog["upstream"]["config"])
        self.assertIn("r2:r3", self.catalog["abi"]["parameter_1"])
        self.assertTrue(self.catalog["abi"]["tail_safe"])

    def test_only_retained_z_impl_owns_semantics(self):
        self.assertEqual("retained reconstruction", self.catalog["ownership"]["kind"])
        self.assertFalse(self.catalog["ownership"]["sdk_z_impl_adopted"])
        self.assertEqual(
            "z_impl_k_sem_take=g1_displaced_sdk_z_impl_k_sem_take",
            self.catalog["ownership"]["sdk_symbol_displacement"])
        self.assertEqual(6, self.catalog["references"]["count"])
        line = [line for line in subject.render_ld(self.catalog).splitlines()
                if line.startswith("PROVIDE(")][0]
        self.assertEqual("PROVIDE(k_sem_take = z_impl_k_sem_take);",
                         line.split(" /*", 1)[0])

    def test_both_app_link_paths_consume_public_alias_fragment(self):
        with open(os.path.join(ROOT, "recon/application/app/CMakeLists.txt")) as stream:
            self.assertIn("g1_app_public_sdk_aliases.ld", stream.read())
        with open(os.path.join(ROOT, "tools/full_link.py")) as stream:
            self.assertIn("g1_%s_public_sdk_aliases.ld", stream.read())


if __name__ == "__main__":
    unittest.main()
