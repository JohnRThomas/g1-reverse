#!/usr/bin/env python3
"""Fail-closed checks for CPUAPP SDK-inline cohesion group G."""

import hashlib
import os
import re
import subprocess
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
NCS = Path("/Users/freedomcoder/ncs251")
CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")

CANONICAL = {
    "spec_ble_command_hook.c": "9e71585ba73343354792e063aa50834eb4f3d0b0eb8d680bf6dca181a00991c5",
    "FUN_0003271c.c": "498c927567e8cb802b01dd3510c5ab45f5fbf616277e5054fa277c61f127b653",
    "FUN_00032c0c.c": "0200a6713ac73b9a49b3f7857b3d88a5c923abffbcf0e75666a9185fb5014681",
    "FUN_0003f410.c": "560138b0ac035ead00639e3292c18d72e47a1a82db95d802150173adf23aaeef",
    "ble_process_put_ops_0b_18.inc": "4d194518e1dd6abde8d4fdcccaed7db18c3c4f7794b21ea5cc097eed27393fb3",
}

RETAINED = {
    "spec_ble_command_hook.c": {"k_uptime_get_0"},
    "FUN_0003271c.c": {"k_uptime_get_4"},
    "arm_timeout_10s.c": {"k_uptime_get_4"},
    "ui_navigation_task.c": {"k_uptime_get_7"},
    "ble_process_put_req.c": {"k_uptime_get_0"},
}


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


class AppSdkInlineGroupGTest(unittest.TestCase):
    def test_canonical_sources_and_verified_mirrors_are_digest_pinned(self):
        for name, expected in CANONICAL.items():
            source = ROOT / "recon/app/src" / name
            mirror = ROOT / "recon/verified/src" / name
            self.assertEqual(expected, digest(source), name)
            self.assertEqual(expected, digest(mirror), name + " mirror")

    def test_pinned_zephyr_inline_owner_receipts(self):
        self.assertEqual(
            "f49b5b98fa64dc38fb625a477ddb2381665c5273616490910a8d077c5e39d76f",
            digest(NCS / "zephyr/include/zephyr/kernel.h"))
        self.assertEqual(
            "7630be08a9b3470ce9aa8eff5db0c7b96ccec110d6e9d7b6ec43c751d7dff4a7",
            digest(NCS / "zephyr/include/zephyr/sys/time_units.h"))

    def test_sdk_build_branch_removes_all_synthetic_uptime_references(self):
        self.assertTrue(CC.is_file())
        for name, forbidden in RETAINED.items():
            path = ROOT / "recon/symbolized/app" / name
            result = subprocess.run([
                str(CC), "-E", "-P", "-DG1_APP_SDK_INLINE_COHESION=1",
                "-I" + str(ROOT / "recon/symbols"),
                "-I" + str(ROOT / "recon/app/src"), str(path),
            ], check=True, capture_output=True, text=True)
            self.assertIn("z_impl_k_uptime_ticks", result.stdout, name)
            for symbol in forbidden:
                self.assertNotRegex(result.stdout,
                                    r"\b%s\s*\(" % re.escape(symbol), name)

    def test_inline_owner_is_local_and_cannot_collide(self):
        source_paths = [ROOT / "recon/symbolized/app" / name
                        for name in RETAINED if name != "ble_process_put_req.c"]
        source_paths.append(ROOT / "recon/symbolized/app/ble_process_put_ops_0b_18.inc")
        for path in source_paths:
            text = path.read_text(encoding="utf-8")
            definitions = re.findall(
                r"static\s+__attribute__\(\(always_inline\)\)\s+inline\s+"
                r"[^;{}]*\bg1_sdk_uptime_get_[047]\s*\(", text)
            self.assertEqual(1, len(definitions), str(path))
        linker_text = "\n".join(
            path.read_text(encoding="utf-8")
            for path in (ROOT / "recon/symbols").glob("*.ld"))
        for symbol in ("k_uptime_get_0", "k_uptime_get_4", "k_uptime_get_7"):
            self.assertNotRegex(linker_text, r"PROVIDE\s*\(\s*%s\b" % symbol)

    def test_exact_configured_time_units_formula_is_retained(self):
        for name in CANONICAL:
            text = (ROOT / "recon/app/src" / name).read_text(encoding="utf-8")
            self.assertIn("z_impl_k_uptime_ticks() * 1000u", text, name)
            self.assertIn(">> 15", text, name)


if __name__ == "__main__":
    unittest.main()
