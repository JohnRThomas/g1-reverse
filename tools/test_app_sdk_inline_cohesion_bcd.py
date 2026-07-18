#!/usr/bin/env python3
"""Fail-closed checks for CPUAPP SDK inline-cohesion groups B/C/D."""

import os
import subprocess
import tempfile
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
       "arm-zephyr-eabi-gcc")
NM = ("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/"
      "arm-zephyr-eabi-nm")
SOURCES = {
    "bt_id_add.c": {"FUN_00080fd2"},
    "log_output_dropped_process.c": {"buffer_write"},
    "compare_set.c": {"compare_int_lock", "event_clear"},
}
FLAGS = [
    "-Os", "-std=gnu11", "-mcpu=cortex-m33", "-mthumb",
    "-mfpu=fpv5-sp-d16", "-mfloat-abi=hard",
    "-I" + os.path.join(ROOT, "recon/symbols"),
]


def compile_source(source, output, cohesive):
    command = [GCC] + FLAGS
    if cohesive:
        command.append("-DG1_APP_SDK_INLINE_COHESION=1")
    command += ["-c", source, "-o", output]
    subprocess.run(command, check=True, capture_output=True, text=True)


def symbols(path):
    result = subprocess.run([NM, "-a", path], check=True,
                            capture_output=True, text=True).stdout
    defined = set()
    undefined = set()
    for line in result.splitlines():
        fields = line.split()
        if len(fields) == 2 and fields[0] == "U":
            undefined.add(fields[1])
        elif len(fields) >= 3:
            defined.add(fields[-1])
    return defined, undefined


class AppSdkInlineCohesionBcdTests(unittest.TestCase):
    def test_parity_path_keeps_original_oracle_boundaries(self):
        with tempfile.TemporaryDirectory() as temporary:
            for filename, expected in SOURCES.items():
                source = os.path.join(ROOT, "recon/symbolized/app", filename)
                output = os.path.join(temporary, filename + ".o")
                compile_source(source, output, cohesive=False)
                _, undefined = symbols(output)
                self.assertTrue(expected <= undefined, filename)

    def test_cohesive_path_has_no_local_helper_residue_or_export(self):
        all_helpers = set().union(*SOURCES.values())
        with tempfile.TemporaryDirectory() as temporary:
            for filename in SOURCES:
                source = os.path.join(ROOT, "recon/symbolized/app", filename)
                output = os.path.join(temporary, filename + ".o")
                compile_source(source, output, cohesive=True)
                defined, undefined = symbols(output)
                self.assertFalse(all_helpers & undefined, filename)
                self.assertFalse(all_helpers & defined, filename)
                self.assertFalse({name for name in defined
                                  if name.startswith("g1_")}, filename)

    def test_sources_pin_reviewed_receipts_and_shared_gate(self):
        expected = {
            "FUN_00054ea8.c": "receipt 781199a9",
            "FUN_0004de68.c": "receipt c6f068f2",
            "compare_set.c": "receipt baa02453",
        }
        for filename, receipt in expected.items():
            path = os.path.join(ROOT, "recon/app/src", filename)
            with open(path, encoding="utf-8") as stream:
                source = stream.read()
            self.assertIn("G1_APP_SDK_INLINE_COHESION", source, filename)
            self.assertIn(receipt, source, filename)


if __name__ == "__main__":
    unittest.main()
