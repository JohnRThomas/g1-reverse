#!/usr/bin/env python3
"""Fail-closed tests for exact NCS 2.5.1 mcumgr adoption."""

import hashlib
import json
import unittest
from pathlib import Path

from elftools.elf.elffile import ELFFile


ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / "recon/ownership/app_mcumgr_stock_atomic_adoption.json"
MANIFEST = ROOT / "recon/ownership/adoption_manifest.json"
NAMES = ROOT / "recon/catalogs/function_names_app.json"
RETAINED = ROOT / "recon/generated/app_retained_sources.cmake"
IMAGE = ROOT / "app_update.bin"


class AppMcumgrStockAtomicAdoptionTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.audit = json.loads(AUDIT.read_text())
        cls.rows = {row["va"]: row for row in cls.audit["authorizations"]}

    def test_four_source_units_are_one_atomic_group(self):
        self.assertEqual(4, len(self.audit["selected_source_units"]))
        group = set(self.rows)
        self.assertEqual(20, len(group))
        for row in self.rows.values():
            self.assertEqual(group, set(row["atomic_group"]))
            self.assertEqual(group,
                             set(row["whole_unit_closure"]["exclude_only"]))
            self.assertTrue(row["configuration_variant_exact"])
            self.assertTrue(row["instruction_exact"])
            self.assertTrue(row["relocation_masked_byte_exact"])

    def test_exact_config(self):
        required = next(iter(self.rows.values()))["required_config"]
        self.assertEqual("y", required["CONFIG_ZCBOR_STOP_ON_ERROR"])
        self.assertEqual("y", required[
            "CONFIG_MCUMGR_TRANSPORT_BT_REASSEMBLY"])
        self.assertEqual("2475", required[
            "CONFIG_MCUMGR_TRANSPORT_NETBUF_SIZE"])

    def test_every_emitted_section_is_relocation_normalized_exact(self):
        image = IMAGE.read_bytes()
        for va, row in self.rows.items():
            name = ".text." + row["identity_correction"][
                "corrected_upstream_symbol"]
            with Path(row["upstream_object"]).open("rb") as stream:
                elf = ELFFile(stream)
                section = elf.get_section_by_name(name)
                candidate = bytearray(section.data())
                reloc = elf.get_section_by_name(".rel" + name)
                offsets = ([] if reloc is None else
                           [int(item["r_offset"])
                            for item in reloc.iter_relocations()])
            firmware = bytearray(image[
                int(va, 16) - 0xC000:
                int(va, 16) - 0xC000 + len(candidate)])
            for offset in offsets:
                candidate[offset:offset + 4] = b"\0" * 4
                firmware[offset:offset + 4] = b"\0" * 4
            self.assertEqual(candidate, firmware, va)
            self.assertEqual(row["normalized_code_sha256"],
                             hashlib.sha256(firmware).hexdigest())

    def test_manifest_and_cmake_exclude_only_recovered_owners(self):
        entries = {row["va"]: row for row in
                   json.loads(MANIFEST.read_text())["cores"]["app"]["entries"]}
        retained = RETAINED.read_text()
        for va, row in self.rows.items():
            self.assertTrue(entries[va]["exclude_reconstruction"], va)
            self.assertNotIn(Path(row["reconstruction_source"]).name, retained)
        self.assertNotIn("0x00051304", entries)
        self.assertNotIn("0x000513cc", entries)
        self.assertNotIn("0x000526b4", entries)
        self.assertNotIn("0x00080be2", entries)

    def test_readable_and_raw_backmaps_are_bijective(self):
        names = json.loads(NAMES.read_text())["by_address"]
        for va, row in self.rows.items():
            record = names[va]
            self.assertEqual(row["raw_symbol"], record["raw_name"])
            self.assertEqual(row["identity_correction"][
                "corrected_readable_identity"], record["name"])
        self.assertEqual("smp_packet_free", names["0x00080ae2"]["name"])
        self.assertIn("thunk_FUN_0005f24c",
                      names["0x00080ae2"]["aliases"])

    def test_state_and_sdc_policy(self):
        self.assertEqual("0x2000a94c",
                         self.audit["state_closure"]["mgmt_group_list"])
        self.assertEqual("0x26ac",
                         self.audit["state_closure"]["net_buf_data_pkt_pool_size"])
        self.assertEqual("report_only_unchanged", self.audit["sdc_policy"])

    def test_verified_relink_removed_visible_collisions(self):
        link = self.audit["verified_relink"]
        self.assertEqual((18, 7), (link["all_collisions_before"],
                                  link["all_collisions_after"]))
        self.assertEqual({
            "mgmt_find_handler", "smp_process_request_packet",
            "smp_add_cmd_err", "smp_transport_init",
            "smp_rx_remove_invalid", "smp_free_buf",
        }, set(link["removed_mcumgr_collisions"]))
        self.assertEqual([], link["added_mcumgr_collisions"])
        self.assertEqual([], link["undefined_before"])
        self.assertEqual([], link["undefined_after"])


if __name__ == "__main__":
    unittest.main()
