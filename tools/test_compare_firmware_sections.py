#!/usr/bin/env python3
"""Tests for the fail-closed whole-image section comparator."""

import json
import os
import struct
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

import compare_firmware_sections as comparison


CC = Path("/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc")


class FirmwareSectionComparisonTests(unittest.TestCase):
    def make_fixture(self, directory):
        directory = Path(directory)
        source = directory / "fixture.c"
        source.write_text(
            "__attribute__((section(\".fixture_text\"))) "
            "int fixture_add(int x) { return x + 3; }\n"
            "__attribute__((section(\".fixture_rodata\"))) "
            "const unsigned char fixture_rodata[4] = {1,2,3,4};\n"
            "__attribute__((section(\".fixture_data\"))) "
            "unsigned char fixture_data[4] = {5,6,7,8};\n")
        script = directory / "fixture.ld"
        script.write_text(
            "SECTIONS {\n"
            " . = 0x1000; text : { *(.fixture_text) }\n"
            " . = ALIGN(4); rodata : { *(.fixture_rodata) }\n"
            " . = 0x20000000; datas : AT(0x1100) { *(.fixture_data) }\n"
            " /DISCARD/ : { *(.comment) *(.ARM.attributes) }\n"
            "}\n")
        elf = directory / "fixture.elf"
        subprocess.run([
            str(CC), "-nostdlib", "-Os", "-mcpu=cortex-m33", "-mthumb",
            "-Wl,--build-id=none", "-Wl,-T," + str(script), str(source),
            "-o", str(elf)], check=True, capture_output=True)
        payload = bytearray(0x200)
        with elf.open("rb") as stream:
            parsed = comparison.ELFFile(stream)
            for section, _vma, lma, _flags in comparison.loadable_sections(parsed):
                offset = lma - 0x1000
                payload[offset:offset + len(section.data())] = section.data()
        return elf, bytes(payload)

    def test_mcuboot_payload_slicing(self):
        with tempfile.TemporaryDirectory() as temporary:
            path = Path(temporary) / "update.bin"
            payload = b"payload"
            header = bytearray(0x20)
            struct.pack_into("<IIHHII", header, 0, comparison.MCUBOOT_MAGIC,
                             0, len(header), 0, len(payload), 0)
            path.write_bytes(header + payload + b"tlv")
            selected, receipt = comparison.load_payload(path)
            self.assertEqual(payload, selected)
            self.assertEqual("mcuboot", receipt["format"])
            self.assertEqual(3, receipt["trailing_bytes"])

    def test_net_runtime_lma_and_initialized_data(self):
        with tempfile.TemporaryDirectory() as temporary:
            elf, payload = self.make_fixture(temporary)
            firmware = Path(temporary) / "net.bin"
            firmware.write_bytes(payload)
            report = comparison.compare(
                "net", elf, firmware, runtime_base=0x1000,
                analysis_base=0x0800)
            rows = {row["name"]: row for row in report["sections"]}
            self.assertEqual("0x00001100", rows["datas"]["lma"])
            self.assertEqual("0x00000900", rows["datas"]["analysis_lma"])
            self.assertEqual("data_initializer", rows["datas"]["category"])
            self.assertTrue(report["gates"]["structural_pass"])
            self.assertTrue(report["gates"]["non_executable_exact_pass"])

    def test_zephyr_vector_section_is_an_exact_gate_not_text_score(self):
        self.assertEqual(
            "vectors",
            comparison.classify_section(
                "rom_start", comparison.SHF_ALLOC | comparison.SHF_EXECINSTR,
                0x1000, 0x1000))
        self.assertEqual(
            "immutable",
            comparison.classify_section(
                ".ARM.exidx", comparison.SHF_ALLOC, 0x1100, 0x1100))

    def test_strict_data_detects_one_byte_change(self):
        with tempfile.TemporaryDirectory() as temporary:
            elf, payload = self.make_fixture(temporary)
            payload = bytearray(payload)
            payload[0x100] ^= 0x80
            firmware = Path(temporary) / "net.bin"
            firmware.write_bytes(payload)
            report = comparison.compare(
                "net", elf, firmware, runtime_base=0x1000,
                analysis_base=0x0800)
            data = next(row for row in report["sections"]
                        if row["name"] == "datas")
            self.assertFalse(data["byte_exact"])
            self.assertEqual("0x00001100", data["first_difference"])
            self.assertFalse(report["gates"]["non_executable_exact_pass"])

    def test_out_of_range_is_structural_failure(self):
        with tempfile.TemporaryDirectory() as temporary:
            elf, payload = self.make_fixture(temporary)
            firmware = Path(temporary) / "short.bin"
            firmware.write_bytes(payload[:0x80])
            report = comparison.compare(
                "net", elf, firmware, runtime_base=0x1000,
                analysis_base=0x0800)
            self.assertFalse(report["gates"]["structural_pass"])
            self.assertIn("datas", report["summary"]["out_of_range_sections"])

    def test_wrong_link_base_fails_even_if_sections_overlap_payload_window(self):
        with tempfile.TemporaryDirectory() as temporary:
            elf, payload = self.make_fixture(temporary)
            firmware = Path(temporary) / "wide.bin"
            firmware.write_bytes(b"\0" * 0x100 + payload)
            report = comparison.compare(
                "net", elf, firmware, runtime_base=0x0F00,
                analysis_base=0x0700)
            self.assertFalse(report["gates"]["load_base_matches_runtime"])
            self.assertFalse(report["gates"]["structural_pass"])


if __name__ == "__main__":
    unittest.main()
