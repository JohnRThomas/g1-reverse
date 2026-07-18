#!/usr/bin/env python3
"""Fail-closed identity, retention, and namespace gates for COLLISION-09."""

import hashlib
import json
import re
import subprocess
import sys
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import extract
from parity import emu, recon

BUILD = Path("/private/tmp/g1-app-residue-current-0718")
PINNED = Path("/private/tmp/g1_cpuapp_shell_build_0717j")
GPPI_OBJECT = (PINNED / "modules/hal_nordic/nrfx/CMakeFiles/"
               "modules__hal_nordic__nrfx.dir/Users/freedomcoder/ncs251/"
               "modules/hal/nordic/nrfx/helpers/nrfx_gppi_dppi.c.obj")
BASELINE_SHA256 = "8012a14b16b6ddd0671cebe93b875629a861c19586e6cb842212c41ed2fcbbbc"
NAMES = {
    "0x00064f48": "g1_recon_nrfx_gppi_event_endpoint_setup",
    "0x00064f78": "g1_recon_nrfx_gppi_task_endpoint_setup",
    "0x00064fa8": "g1_recon_nrfx_gppi_event_endpoint_clear",
    "0x00064fd4": "g1_recon_nrfx_gppi_task_endpoint_clear",
    "0x000850dc": "g1_recon_nrfx_gppi_channel_endpoints_setup",
}


class GppiNamespaceTest(unittest.TestCase):
    def test_durable_names_mirrors_and_generated_owners(self):
        catalog = json.loads((ROOT / "recon/catalogs/function_names_app.json").read_text())
        retained = (ROOT / "recon/generated/app_retained_sources.cmake").read_text()
        for va, name in NAMES.items():
            row = catalog["by_address"][va]
            self.assertEqual("FUN_%08x" % int(va, 16), row["raw_name"])
            self.assertEqual(name, row["name"])
            self.assertEqual(va, catalog["by_name"][name])
            raw = row["raw_name"] + ".c"
            self.assertEqual((ROOT / "recon/app/src" / raw).read_bytes(),
                             (ROOT / "recon/verified/src" / raw).read_bytes())
            self.assertTrue((ROOT / "recon/named" / (name + ".c")).exists())
            self.assertTrue((ROOT / "recon/symbolized/app" / (name + ".c")).exists())
            self.assertIn("/" + name + ".c", retained)

    def test_false_net_buf_adoption_is_revoked_without_baseline_mutation(self):
        baseline_path = ROOT / "recon/ownership/adoption_manifest_baseline.json"
        self.assertEqual(BASELINE_SHA256,
                         hashlib.sha256(baseline_path.read_bytes()).hexdigest())
        baseline = json.loads(baseline_path.read_text())
        current = json.loads((ROOT / "recon/ownership/adoption_manifest.json").read_text())
        b = {row["va"]: row for row in baseline["cores"]["app"]["entries"]}["0x000850dc"]
        c = {row["va"]: row for row in current["cores"]["app"]["entries"]}["0x000850dc"]
        self.assertEqual("net_buf_simple_push_mem", b["current_symbol"])
        self.assertTrue(b["exclude_reconstruction"])
        self.assertEqual(NAMES["0x000850dc"], c["current_symbol"])
        self.assertFalse(c["exclude_reconstruction"])
        self.assertTrue(any(e.get("type") ==
                            "explicit_fail_closed_retention_override"
                            for e in c["evidence"]))

    def test_complete_caller_closure_targets_namespaces(self):
        ipc = (ROOT / "recon/app/src/FUN_0004c278.c").read_text()
        self.assertIn("g1_recon_nrfx_gppi_task_endpoint_clear(param_1, uVar1)", ipc)
        self.assertIn("g1_recon_nrfx_gppi_task_endpoint_setup(param_1, uVar1)", ipc)
        callback = (ROOT / "recon/app/src/FUN_0004c418.c").read_text()
        self.assertIn("g1_recon_nrfx_gppi_event_endpoint_setup(id, state)", callback)
        uarte = (ROOT / "recon/app/src/FUN_00062d9c.c").read_text()
        self.assertIn("g1_recon_nrfx_gppi_channel_endpoints_setup(", uarte)
        wrapper = (ROOT / "recon/app/src/FUN_000850dc.c").read_text()
        self.assertIn("g1_recon_nrfx_gppi_event_endpoint_setup(channel, event_endpoint)", wrapper)
        self.assertIn("g1_recon_nrfx_gppi_task_endpoint_setup(channel, task_endpoint)", wrapper)

    def test_pinned_configured_sdk_omits_assertion_paths(self):
        expected = {
            "nrfx_gppi_task_endpoint_setup":
                (10, "1d5d7f64b303530a449b191c0dc05528b9b3ce9f2b674f766aa9b51836df392c"),
            "nrfx_gppi_task_endpoint_clear":
                (8, "6da6e0257ca5060b31d04537fc940426e2925a98bbc4ff5c9d8eb516440200cc"),
            "nrfx_gppi_channel_endpoints_setup":
                (14, "d6aa15e751d47c82f881193732004701e3c81d6733118e5a7e0be3579348279d"),
        }
        with GPPI_OBJECT.open("rb") as stream:
            elf = ELFFile(stream)
            for symbol, (size, digest) in expected.items():
                code = elf.get_section_by_name(".text." + symbol).data()
                self.assertEqual(size, len(code))
                self.assertEqual(digest, hashlib.sha256(code).hexdigest())

    def test_assertion_removal_mutation_is_rejected_on_null_endpoint(self):
        mutation = ("void mutated(unsigned channel, int endpoint) {"
                    "*(volatile unsigned *)(endpoint + 0x80) = "
                    "channel | 0x80000000u; }")
        compiled, error = recon.compile_func(mutation, "mutated", 0x00064f78)
        self.assertIsNone(error, error)
        candidate, tail, candidate_size, candidate_va = compiled
        result = emu.compare(
            extract.func_bytes_padded(0x00064f78, 34, 64),
            0x00064f78, 34, candidate + tail, candidate_va, candidate_size,
            trials=1, nptr=0, arg_overrides=[{0: 3, 1: 0}],
            candidate_direct_target_map=dict(recon.LAST_DIRECT_TARGET_MAP))
        self.assertFalse(result["pass"])
        self.assertEqual(1, result["mismatches"])

    def test_normal_link_delta_is_exact_and_unresolved_is_unchanged(self):
        run = subprocess.run(
            ["cmake", "--build", str(BUILD), "-j8"],
            capture_output=True, text=True)
        output = run.stdout + "\n" + run.stderr
        collisions = set(re.findall(
            r"multiple definition of [`']([^'`]+)", output))
        undefined = set(re.findall(r"undefined reference to [`']([^'`]+)", output))
        self.assertEqual(82, len(collisions))
        self.assertNotIn("nrfx_gppi_task_endpoint_setup", collisions)
        self.assertNotIn("nrfx_gppi_task_endpoint_clear", collisions)
        self.assertFalse(set(NAMES.values()) & collisions)
        self.assertEqual({"FUN_0005463e", "FUN_00054688",
                          "g_2000b154", "rodata_f5d9e", "rodata_f5dbd"},
                         undefined)


if __name__ == "__main__":
    unittest.main()
