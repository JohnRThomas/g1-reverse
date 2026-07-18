#!/usr/bin/env python3
"""Integration gates for the combined logging collision milestone."""

import json
import re
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


class LoggingCollisionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads((
            ROOT / "recon/ownership/app_collision32_33_logging.json").read_text())
        cls.names = json.loads((
            ROOT / "recon/catalogs/function_names_app.json").read_text())
        cls.retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()

    def test_corrected_and_namespaced_identities(self):
        expected = {
            "0x0004db04": "log_output_process",
            "0x0004de68": "log_output_dropped_process",
            "0x0004def8": "g1_recon_log_backend_uart_panic",
            "0x0004d578": "g1_recon_z_log_msg_free",
            "0x0004d588": "g1_recon_z_log_msg_pending",
            "0x0004d678": "g1_recon_z_impl_log_panic",
        }
        for va, name in expected.items():
            self.assertEqual(name, self.names["by_address"][va]["name"])
            self.assertEqual(va, self.names["by_name"][name])

    def test_exact_sdk_closure_is_excluded(self):
        for name in ("print_formatted", "newline_print", "log_output_process",
                     "log_output_dropped_process", "log_backend_uart_dropped"):
            self.assertNotIn("/" + name + ".c", self.retained)
        self.assertIn("/g1_recon_log_backend_uart_panic.c", self.retained)

    def test_log_core_callers_target_namespaces(self):
        process = (ROOT / "recon/app/src/FUN_0004d594.c").read_text()
        self.assertIn("g1_recon_z_log_msg_free(item)", process)
        self.assertIn("return g1_recon_z_log_msg_pending()", process)
        fatal = (ROOT / "recon/app/src/FUN_00063b7c.c").read_text()
        self.assertIn("g1_recon_z_impl_log_panic()", fatal)

    def test_mpsc_names_remain_stable(self):
        by_address = self.names["by_address"]
        self.assertEqual("g1_recon_z_log_msg_alloc",
                         by_address["0x0004d55c"]["name"])
        self.assertEqual("g1_recon_z_log_msg_commit",
                         by_address["0x0004d8b8"]["name"])

    def test_exact_receipts_and_link_delta(self):
        self.assertTrue(all(row["instruction_exact"]
                            for row in self.audit["authorizations"]))
        link = self.audit["verified_normal_link"]
        self.assertEqual((15, 10), (link["before"], link["after"]))
        self.assertEqual([], link["added"])
        self.assertEqual(["FUN_0005463e", "FUN_00054688"],
                         link["unresolved"])

    def test_normal_link_has_exact_remaining_residue(self):
        run = subprocess.run(
            ["cmake", "--build", self.audit["verified_normal_link"]["build"],
             "-j8"], capture_output=True, text=True)
        output = run.stdout + "\n" + run.stderr
        collisions = set(re.findall(
            r"multiple definition of [`']([^'`]+)", output))
        undefined = set(re.findall(
            r"undefined reference to [`']([^'`]+)", output))
        self.assertEqual(set(self.audit["verified_normal_link"]["collisions"]),
                         collisions)
        self.assertEqual(set(self.audit["verified_normal_link"]["unresolved"]),
                         undefined)


if __name__ == "__main__":
    unittest.main()
