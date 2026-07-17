#!/usr/bin/env python3
"""Fail-closed tests for generated CPUAPP public owners and link aliases."""

import json
import os
import sys
import unittest


ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

import apply_names
import gen_function_aliases


class AppIdentityAliasTests(unittest.TestCase):
    def test_public_owner_rename_preserves_provenance_text(self):
        source = ("/* Reconstructed old_owner @ 0x2bed0 */\n"
                  "const char *s = \"old_owner\";\n"
                  "int old_owner(void) { return 1; }\n")
        rendered = apply_names.rename_public_owner(
            source, 0x2bed0, "display_panel_is_secondary")
        self.assertIn("int display_panel_is_secondary(void)", rendered)
        self.assertIn("Reconstructed old_owner", rendered)
        self.assertIn('"old_owner"', rendered)

    def test_wrong_entry_does_not_rename(self):
        source = "/* Reconstructed old_owner @ 0x2bed0 */\nint old_owner(void);\n"
        self.assertEqual(source, apply_names.rename_public_owner(
            source, 0x2bed2, "new_owner"))

    def test_explicit_alias_requires_one_defined_owner(self):
        manifest = {"by_address": {"0x00001000": {
            "raw_name": "FUN_00001000", "name": "owner", "human": True}}}
        aliases, _ = gen_function_aliases.plan_aliases(
            manifest, {"owner"}, {"legacy"}, {"legacy": "0x00001000"})
        self.assertEqual([("legacy", "owner", "0x00001000")], aliases)
        with self.assertRaises(SystemExit):
            gen_function_aliases.plan_aliases(
                manifest, set(), {"legacy"}, {"legacy": "0x00001000"})

    def test_committed_alias_catalog_is_unique_and_known(self):
        with open(os.path.join(
                ROOT, "recon/catalogs/function_names_app.json")) as stream:
            manifest = json.load(stream)
        aliases = gen_function_aliases.load_link_aliases("app", manifest)
        self.assertEqual(29, len(aliases))
        self.assertEqual("0x00034808", aliases["can_begin_task_transition"])
        self.assertEqual("0x000431a8", aliases["get_display_atomic_state"])

    def test_display_accessor_alias_targets_the_only_retained_owner(self):
        with open(os.path.join(
                ROOT, "recon/catalogs/function_names_app.json")) as stream:
            manifest = json.load(stream)
        aliases = gen_function_aliases.load_link_aliases("app", manifest)
        address = aliases["get_display_atomic_state"]
        record = manifest["by_address"][address]
        self.assertEqual("FUN_000431a8", record["raw_name"])
        self.assertEqual("atomic_get_3_0", record["name"])
        self.assertEqual("recon/app/src/atomic_get_3_0.c", record["source"])

        planned, rejected = gen_function_aliases.plan_aliases(
            manifest, {"atomic_get_3_0"}, {"get_display_atomic_state"},
            aliases)
        self.assertIn(("get_display_atomic_state", "atomic_get_3_0",
                       "0x000431a8"), planned)
        self.assertFalse(rejected["both_defined"])

        with open(os.path.join(
                ROOT, "recon/symbols/g1_app_function_aliases.ld")) as stream:
            fragment = stream.read()
        expected = ("PROVIDE(get_display_atomic_state = atomic_get_3_0); "
                    "/* 0x000431a8 */")
        self.assertEqual(1, fragment.count(expected))
        self.assertNotIn("atomic_get_3_0 = get_display_atomic_state", fragment)


if __name__ == "__main__":
    unittest.main()
