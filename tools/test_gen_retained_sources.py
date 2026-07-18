#!/usr/bin/env python3
"""Tests for gen_retained_sources.py."""

import json
import os
import sys
import tempfile
import unittest


TOOLS = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, TOOLS)
import gen_retained_sources as retained


class RetainedSourcesTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        root = self.temp.name
        self.configs = {}
        for core, addresses in (("app", (0x1000, 0x1010, 0x1020)),
                                ("net", (0x01001000, 0x01001010))):
            source_dir = os.path.join(root, core)
            os.makedirs(source_dir)
            names = {"schema": 1, "by_name": {"readable": hex(addresses[1])}}
            names_path = os.path.join(root, core + "_names.json")
            with open(names_path, "w") as stream:
                json.dump(names, stream)
            with open(os.path.join(source_dir, "FUN_%08x.c" % addresses[0]), "w") as stream:
                stream.write("void raw(void) {}\n")
            with open(os.path.join(source_dir, "readable.c"), "w") as stream:
                stream.write("void readable(void) {}\n")
            if core == "app":
                with open(os.path.join(source_dir, "legacy.c"), "w") as stream:
                    stream.write("/* Reconstructed legacy @ 0x1020. */\n")
            self.configs[core] = {
                "source_dir": source_dir,
                "names": names_path,
                "output": os.path.join(root, core + ".cmake"),
            }
        self.manifest_path = os.path.join(root, "manifest.json")

    def tearDown(self):
        self.temp.cleanup()

    def write_manifest(self, app_rows=None, net_rows=None):
        def rows(core, values):
            result = []
            for va, exclude, component, evidence in values or []:
                result.append({"core": core, "va": hex(va),
                               "exclude_reconstruction": exclude,
                               "component": component, "evidence": evidence})
            return result
        data = {"cores": {"app": {"entries": rows("app", app_rows)},
                            "net": {"entries": rows("net", net_rows)}}}
        with open(self.manifest_path, "w") as stream:
            json.dump(data, stream)

    def test_excludes_only_true_rows_and_is_deterministic(self):
        self.write_manifest(
            app_rows=[(0x1000, True, "tinycrypt", []),
                      (0x1010, False, "tinycrypt", []),
                      (0x9990, True, "archive", [])],
            net_rows=[])
        first = retained.build(self.manifest_path, self.configs)
        second = retained.build(self.manifest_path, self.configs)
        self.assertEqual(first, second)
        app = first[self.configs["app"]["output"]]
        self.assertNotIn("FUN_00001000.c", app)
        self.assertIn("readable.c", app)
        self.assertIn("legacy.c", app)
        self.assertIn("manifest exclusions: 2; matched sources: 1", app)

    def test_report_only_sdc_is_never_excluded(self):
        evidence = [{"type": "sdc_archive_benchmark_summary",
                     "per_va_unique_identity": False}]
        self.write_manifest(net_rows=[
            (0x01001000, True, "softdevice_controller", evidence)])
        with self.assertRaisesRegex(ValueError, "report-only SDC"):
            retained.build(self.manifest_path, self.configs)

    def test_missing_and_ambiguous_source_va_fail_closed(self):
        self.write_manifest()
        bad = os.path.join(self.configs["app"]["source_dir"], "unknown.c")
        with open(bad, "w") as stream:
            stream.write("void unknown(void) {}\n")
        with self.assertRaisesRegex(ValueError, "no VA mapping"):
            retained.build(self.manifest_path, self.configs)
        os.unlink(bad)
        duplicate = os.path.join(self.configs["app"]["source_dir"], "duplicate.c")
        with open(duplicate, "w") as stream:
            stream.write("/* duplicate @ 0x1000 */\n")
        with self.assertRaisesRegex(ValueError, "ambiguous canonical VA"):
            retained.build(self.manifest_path, self.configs)

    def test_catalog_content_disagreement_fails_closed(self):
        self.write_manifest()
        raw = os.path.join(self.configs["app"]["source_dir"], "FUN_00001000.c")
        with open(raw, "w") as stream:
            stream.write("/* stale identity @ 0x1090 */\n")
        with self.assertRaisesRegex(ValueError, "catalog/content VA conflict"):
            retained.build(self.manifest_path, self.configs)

    def test_strict_symbolized_identity_and_name_validation(self):
        self.write_manifest()
        self.configs["app"]["strict_symbolized"] = True
        for filename, va, public in (("FUN_00001000.c", 0x1000, "FUN_00001000"),
                                     ("readable.c", 0x1010, "readable"),
                                     ("legacy.c", 0x1020, "legacy")):
            path = os.path.join(self.configs["app"]["source_dir"], filename)
            identity = ("tail_1010" if filename == "readable.c" else
                        "FUN_%08x" % va)
            with open(path, "w") as stream:
                stream.write("/* readable reconstruction; identity: "
                             "%s @ 0x%08x\n * public-name: %s\n */\n" %
                             (identity, va, public))
        # legacy is not in by_name, so strict symbolized mode rejects it.
        with self.assertRaisesRegex(ValueError, "absent from name catalog"):
            retained.build(self.manifest_path, self.configs)
        names_path = self.configs["app"]["names"]
        with open(names_path) as stream:
            names = json.load(stream)
        names["by_name"]["legacy"] = "0x1020"
        with open(names_path, "w") as stream:
            json.dump(names, stream)
        retained.build(self.manifest_path, self.configs)
        with open(os.path.join(self.configs["app"]["source_dir"], "readable.c"), "w") as stream:
            stream.write("/* readable reconstruction; identity: "
                         "FUN_00001020 @ 0x00001020 */\n")
        with self.assertRaisesRegex(ValueError, "filename/header conflict"):
            retained.build(self.manifest_path, self.configs)

    def test_check_mode_writes_nothing_and_detects_stale(self):
        self.write_manifest()
        outputs = retained.build(self.manifest_path, self.configs)
        with self.assertRaisesRegex(ValueError, "stale"):
            retained.update(outputs, check=True)
        retained.update(outputs)
        self.assertEqual(retained.update(outputs, check=True), [])


if __name__ == "__main__":
    unittest.main()
