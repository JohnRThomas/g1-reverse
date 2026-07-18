#!/usr/bin/env python3
"""Fail-closed checks for CPUAPP compiler-outlined SDK header bridges."""

from pathlib import Path
import hashlib
import json
import re
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "recon/application/app/src/g1_sdk_inline_bridges.c"
CMAKE = ROOT / "recon/application/app/CMakeLists.txt"
CANONICAL = ROOT / "recon/app/src/aging_mode_thread.c"
RECEIPT = ROOT / "recon/ownership/app_k_uptime_get_4_bridge.json"
CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")
NM = CC.with_name("arm-zephyr-eabi-nm")


class AppSdkInlineBridgeTests(unittest.TestCase):
    def test_receipt_hashes_canonical_bridge_and_pinned_sdk(self):
        receipt = json.loads(RECEIPT.read_text())
        digest = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
        self.assertEqual(receipt["canonical_caller"]["sha256"], digest(CANONICAL))
        self.assertEqual(receipt["bridge"]["sha256"], digest(SOURCE))
        kernel = Path(receipt["pinned_sdk_evidence"]["kernel_header"]["path"])
        units = Path(receipt["pinned_sdk_evidence"]["time_units_header"]["path"])
        self.assertEqual(receipt["pinned_sdk_evidence"]["kernel_header"]["sha256"],
                         digest(kernel))
        self.assertEqual(receipt["pinned_sdk_evidence"]["time_units_header"]["sha256"],
                         digest(units))

    def test_bridge_is_integration_only(self):
        self.assertIn("src/g1_sdk_inline_bridges.c", CMAKE.read_text())
        canonical = CANONICAL.read_text()
        self.assertIn("extern uint32_t k_uptime_get_4(void)", canonical)
        self.assertNotIn("G1_APP_SDK_INLINE_COHESION", canonical)
        self.assertNotIn("z_impl_k_uptime_ticks", canonical)

    def test_pinned_uptime_arithmetic_and_signature(self):
        text = SOURCE.read_text()
        self.assertRegex(text, r"uint32_t\s+k_uptime_get_4\s*\(void\)")
        self.assertIn("z_impl_k_uptime_ticks() * 1000u", text)
        self.assertIn(">> 15", text)
        self.assertIn("CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768", text)

    def test_object_has_one_bridge_and_sdk_tick_dependency(self):
        with tempfile.TemporaryDirectory() as directory:
            obj = Path(directory) / "bridge.o"
            subprocess.run([str(CC), "-c", "-Os", "-mcpu=cortex-m33", "-mthumb",
                            str(SOURCE), "-o", str(obj)], check=True)
            symbols = subprocess.run([str(NM), str(obj)], check=True,
                                     capture_output=True, text=True).stdout
        self.assertRegex(symbols, r"(?m)^[0-9a-f]+\s+T\s+k_uptime_get_4$")
        self.assertRegex(symbols, r"(?m)^\s+U\s+z_impl_k_uptime_ticks$")
        self.assertEqual(1, len(re.findall(r"\sT\s+k_uptime_get_4$", symbols,
                                          flags=re.MULTILINE)))


if __name__ == "__main__":
    unittest.main()
