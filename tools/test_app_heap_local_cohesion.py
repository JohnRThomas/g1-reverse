#!/usr/bin/env python3
"""Build/collision guards for CPUAPP's retained Zephyr heap.c locals."""

import hashlib
import subprocess
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/") / \
    "arm-zephyr-eabi-gcc"
NM = CC.with_name("arm-zephyr-eabi-nm")
CANONICAL = {
    "alloc": ROOT / "recon/app/src/FUN_0007df24.c",
    "free": ROOT / "recon/app/src/free_chunk.c",
}
MIRRORS = {
    "alloc": ROOT / "recon/verified/src/FUN_0007df24.c",
    "free": ROOT / "recon/verified/src/free_chunk.c",
}
SYMBOLIZED = {
    "alloc": ROOT / "recon/symbolized/app/alloc_chunk.c",
    "free": ROOT / "recon/symbolized/app/free_chunk.c",
}
LOCAL_RESIDUE = {"FUN_0007def6", "free_list_remove_bidx", "merge_chunks"}


def compile_object(source, cohesive):
    output = Path(tempfile.mkdtemp(prefix="g1_heap_cohesion_")) / \
        (source.stem + ".o")
    command = [
        str(CC), "-c", "-std=gnu11", "-Os", "-ffreestanding",
        "-mcpu=cortex-m33", "-mthumb", "-mfpu=fpv5-sp-d16",
        "-mfloat-abi=hard", "-I" + str(ROOT / "recon/symbols"),
    ]
    if cohesive:
        command.append("-DG1_APP_SDK_INLINE_COHESION=1")
    command.extend([str(source), "-o", str(output)])
    subprocess.run(command, check=True, capture_output=True, text=True)
    return output


def symbols(path, flag):
    result = subprocess.run([str(NM), flag, str(path)], check=True,
                            capture_output=True, text=True)
    return {line.split()[-1] for line in result.stdout.splitlines()
            if line.split()}


class AppHeapLocalCohesionTest(unittest.TestCase):
    def test_canonical_and_verified_sources_are_identical(self):
        for key in CANONICAL:
            self.assertEqual(
                hashlib.sha256(CANONICAL[key].read_bytes()).digest(),
                hashlib.sha256(MIRRORS[key].read_bytes()).digest(), key)

    def test_parity_mode_preserves_historical_oracle_boundaries(self):
        alloc_undefined = symbols(compile_object(CANONICAL["alloc"], False),
                                  "-u")
        free_undefined = symbols(compile_object(CANONICAL["free"], False),
                                 "-u")
        self.assertIn("free_list_remove_bidx", alloc_undefined)
        self.assertIn("FUN_0007def6", free_undefined)
        self.assertIn("FUN_0007dfe6", free_undefined)

    def test_cohesive_objects_remove_only_heap_local_residue(self):
        for tree in (CANONICAL, SYMBOLIZED):
            undefined = set()
            globals_ = set()
            for source in tree.values():
                obj = compile_object(source, True)
                undefined.update(symbols(obj, "-u"))
                globals_.update(symbols(obj, "-g"))
            self.assertTrue(LOCAL_RESIDUE.isdisjoint(undefined), tree)
            self.assertTrue(LOCAL_RESIDUE.isdisjoint(globals_), tree)

    def test_no_standalone_or_weak_helper_owner(self):
        source_dir = ROOT / "recon/app/src"
        forbidden_files = {
            "FUN_0007def6.c", "free_list_remove.c",
            "free_list_remove_bidx.c", "merge_chunks.c",
        }
        self.assertTrue(forbidden_files.isdisjoint(
            {path.name for path in source_dir.glob("*.c")}))
        for path in list(CANONICAL.values()) + list(MIRRORS.values()):
            text = path.read_text()
            self.assertIn("G1_APP_SDK_INLINE_COHESION", text)
            self.assertNotIn("__attribute__((weak))", text)

    def test_integration_shell_enables_scoped_cohesion(self):
        cmake = (ROOT / "recon/application/app/CMakeLists.txt").read_text()
        self.assertIn(
            "target_compile_definitions(app PRIVATE "
            "G1_APP_SDK_INLINE_COHESION=1)", cmake)


if __name__ == "__main__":
    unittest.main()
