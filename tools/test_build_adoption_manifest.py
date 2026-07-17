#!/usr/bin/env python3
"""Fixture self-test for build_adoption_manifest.py."""

import copy
import json
import os
import sys
import tempfile
import unittest


TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import build_adoption_manifest as adoption


def write_json(root, name, value):
    path = os.path.join(root, name)
    with open(path, "w") as stream:
        json.dump(value, stream)
    return path


class AdoptionManifestTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        root = self.temp.name
        app_addresses = (0x1000, 0x1010, 0x2000, 0x2010, 0x2020,
                         0x3000, 0x3010, 0x4000)
        net_addresses = (0x01001000, 0x01002000, 0x01003000, 0x01004000,
                         0x01005000)

        def name_map(core, values):
            return {"schema": 1, "core": core,
                    "by_address": {"0x%08x" % value: {
                        "raw_name": "FUN_%08x" % value,
                        "name": "named_%08x" % value} for value in values}}

        paths = {
            "app_names": write_json(root, "app_names.json", name_map("app", app_addresses)),
            "net_names": write_json(root, "net_names.json", name_map("net", net_addresses)),
            "lc3": write_json(root, "lc3.json", {
                "upstream": {"commit": "a" * 40},
                "functions": [
                    {"address": "0x1000", "upstream_function": "lc3_public",
                     "upstream_file": "public.c", "confidence": "high",
                     "match_score": 1.0, "proof_status": "existing"},
                    {"address": "0x1010", "upstream_function": "helper",
                     "upstream_file": "public.c", "confidence": "high",
                     "match_score": 0.95, "proof_status": "existing"}],
                "tables": [{"address": "0x2000", "name": "lc3_table",
                            "upstream_file": "tables.c"}]}),
            "tinycrypt": write_json(root, "tiny.json", {
                "upstream": {"commit": "b" * 40},
                "matches": [
                    {"address": "0x2010", "symbol": "tc_public",
                     "source": "tiny.c", "linkage": "public",
                     "replacement": "direct_pinned_source", "rank_score": 1.0},
                    {"address": "0x2020", "symbol": "static_helper",
                     "source": "tiny.c", "linkage": "file_static",
                     "replacement": "compile_source_unit", "rank_score": 1.0}]}),
            "cc312": write_json(root, "cc312.json", {
                "archive_sha256": "c" * 64,
                "summary": {"start": "0x3000", "end_exclusive": "0x3020",
                            "all_sections_relocation_normalized_exact": True,
                            "gaps_or_firmware_glue_inside_span": 0},
                "members": {"member.o": ["0x3000", "0x3020", 2, 32]},
                "inventory_corrections": {"0x00003000": "archive_public"}}),
            "crypto": write_json(root, "crypto.json", {
                "functions": [
                    {"core": "app", "va": "0x4000", "component": "zephyr_bt",
                     "upstream_symbol": "bt_source", "upstream_object": "bt.c.obj",
                     "ownership": "source", "confidence": "high"},
                    {"core": "net", "va": "0x01003000",
                     "component": "softdevice_controller",
                     "upstream_symbol": "unknown helper", "ownership": "glue",
                     "confidence": "medium"}]}),
            "app_collisions": write_json(root, "app_collisions.json", {
                "functions": [
                    {"va": "0x4000", "safe_to_exclude": True,
                     "exclusion_blockers": [],
                     "signature_match": {"opcode": 1.0, "shape": 1.0,
                                         "length": 1.0},
                     "link_provenance": {"owner_input": "lib.a(bt.c.obj)"},
                     "upstream": {"symbol": "bt_source",
                                  "object": "bt.c.obj",
                                  "abi": {"return": "int", "params": []},
                                  "source": {"repository": "zephyr"}}}]}),
            "app_sdk_public": write_json(root, "app_sdk_public.json", {
                "functions": [
                    {"va": "0x00002010", "raw_symbol": "FUN_00002010",
                     "upstream_symbol": "public_runtime",
                     "upstream_member": "runtime.o",
                     "selected_link_owner": "lib.a(runtime.o)",
                     "signature_ratio": 1.0, "signature_gate": "exact_signature",
                     "abi": {"gate": "exact"},
                     "required_config": ["GCC pinned"], "safe_to_adopt": True,
                     "exclude_reconstruction": True, "blockers": []},
                    {"va": "0x00002020", "raw_symbol": "FUN_00002020",
                     "upstream_symbol": "collision",
                     "upstream_member": "collision.o",
                     "selected_link_owner": "lib.a(collision.o)",
                     "required_config": ["CONFIG_X=y"], "safe_to_adopt": False,
                     "exclude_reconstruction": False,
                     "blockers": ["identity_collision"]}]}),
            "net": write_json(root, "net.json", {
                "entries": {
                    "0x01001000": {"confidence": 0.99, "signature_match": {
                        "symbol": "sym_PRIVATE", "ratio": 1.0, "threshold": 0.9,
                        "provenance": "libsoftdevice_controller_multirole.a(member.elf)"}},
                    "0x01002000": {"confidence": 0.99, "signature_match": {
                        "symbol": "public_other_archive", "ratio": 0.99,
                        "threshold": 0.9,
                        "provenance": "libother.a(member.o)"}},
                    "0x01005000": {"confidence": 0.99, "signature_match": {
                        "symbol": "ambiguous_generic_match", "ratio": 1.0,
                        "threshold": 0.9,
                        "provenance": "NCS 2.5.1 netref object index"}}}}),
            "net_rtc": write_json(root, "net_rtc.json", {
                "upstream": {"commit": "e" * 40, "source_sha256": "f" * 64,
                             "object": "timer.c.obj"},
                "required_config": {"CONFIG_SYS_CLOCK_TICKS_PER_SEC": 32768},
                "functions": []}),
            "net_sdk_public": write_json(root, "net_sdk_public.json", {
                "upstream": {"zephyr_commit": "1" * 40},
                "required_config": {"CONFIG_ASSERT": True},
                "functions": [{
                    "va": "0x01005000", "upstream_symbol": "k_work_init",
                    "source": "kernel/work.c", "object": "libkernel.a(work.c.obj)",
                    "abi": "void k_work_init(void *, void *)",
                    "firmware_code_size": 54, "reference_code_size": 54,
                    "match": "relocation-normalized instruction-exact",
                    "match_score": 1.0, "exclude_reconstruction": True}]}),
            "net_alias_resolutions": write_json(root, "net_aliases.json", {
                "image_sha256": "2" * 64,
                "resolutions": []}),
        }
        benchmark = os.path.join(root, "sdc.md")
        with open(benchmark, "w") as stream:
            stream.write("""# benchmark
- SHA-256: `%s`
| Controller archive, exact unique identity | 2 | |
| Controller archive, exact duplicate/ambiguous identity | 1 | |
| Controller archive, high-confidence approximate unique identity | 3 | |
| Controller archive, high-confidence approximate ambiguous identity | 4 | |
| **Controller archive total** | **10** | **100** |
""" % ("d" * 64))
        paths["sdc_benchmark"] = benchmark
        paths["sdc_catalog"] = write_json(root, "sdc_catalog.json", {
            "inputs": {"archive_sha256": "d" * 64},
            "functions": [
                {"address": "0x01001000", "match_kind": "exact", "score": 1.0,
                 "best": {"symbol": "sym_PRIVATE", "identity": "archive:private"},
                 "unique_identity": True, "public_api": False,
                 "build_extraction_verified": False, "safe_to_exclude": False,
                 "exclusion_blockers": ["private_abi_unpublished"]},
                {"address": "0x01004000", "match_kind": "approximate", "score": .9,
                 "best": {"symbol": "sdc_public", "identity": "archive:public"},
                 "unique_identity": True, "public_api": True,
                 "build_extraction_verified": True, "safe_to_exclude": True,
                 "exclusion_blockers": []}]})
        paths["output"] = os.path.join(root, "out.json")
        self.paths = paths

    def tearDown(self):
        self.temp.cleanup()

    def test_deterministic_kinds_and_fail_closed_sdc(self):
        first = adoption.build(self.paths)
        second = adoption.build(self.paths)
        self.assertEqual(json.dumps(first, sort_keys=True),
                         json.dumps(second, sort_keys=True))
        rows = {(row["core"], row["va"]): row
                for core in ("app", "net")
                for row in first["cores"][core]["entries"]}
        self.assertEqual(rows[("app", "0x00001000")]["kind"], "source")
        self.assertEqual(rows[("app", "0x00001010")]["kind"], "static_helper")
        self.assertEqual(rows[("app", "0x00002000")]["kind"], "table")
        self.assertEqual(rows[("app", "0x00002020")]["kind"], "static_helper")
        self.assertEqual(rows[("app", "0x00003010")]["kind"], "archive")
        self.assertTrue(rows[("app", "0x00003010")]["exclude_reconstruction"])
        self.assertTrue(rows[("app", "0x00002010")]["exclude_reconstruction"])
        self.assertFalse(rows[("app", "0x00002020")]["exclude_reconstruction"])
        private = rows[("net", "0x01001000")]
        self.assertEqual(private["kind"], "archive")
        self.assertFalse(private["exclude_reconstruction"])
        public = rows[("net", "0x01004000")]
        self.assertTrue(public["exclude_reconstruction"])
        self.assertEqual(public["upstream_symbol"], "sdc_public")
        self.assertTrue(rows[("net", "0x01002000")]["exclude_reconstruction"])
        self.assertEqual(rows[("net", "0x01003000")]["kind"], "glue")
        self.assertFalse(rows[("net", "0x01003000")]["exclude_reconstruction"])
        self.assertTrue(rows[("net", "0x01005000")]["exclude_reconstruction"])
        self.assertEqual(rows[("net", "0x01005000")]["upstream_symbol"],
                         "k_work_init")
        self.assertFalse(first["sdc_benchmark"]["machine_exclusion_authority"])

    def test_validator_rejects_private_sdc_exclusion(self):
        data = adoption.build(self.paths)
        row = next(row for row in data["cores"]["net"]["entries"]
                   if row["va"] == "0x01001000")
        row["exclude_reconstruction"] = True
        with self.assertRaisesRegex(ValueError, "unsafe private SDC exclusion"):
            adoption.validate_manifest(data)


if __name__ == "__main__":
    unittest.main()
