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
        self.assertEqual(41, len(aliases))
        self.assertEqual("0x00034808", aliases["can_begin_task_transition"])
        self.assertEqual("0x000431a8", aliases["get_display_atomic_state"])

    def test_residue_spellings_have_exact_retained_identity_backmaps(self):
        expected = {
            "bt_att_chan_send": "0x00058a54",
            "bucket_idx": "0x0007de82",
            "bytes_to_chunksz": "0x0007de70",
            "compare_int_unlock": "0x00063524",
            "k_fifo_put": "0x00086502",
            "k_timer_start": "0x00075174",
            "net_buf_add": "0x0005f5d0",
            "net_buf_alloc": "0x000836de",
            "next_free_chunk": "0x0007ddec",
            "set_chunk_size": "0x0007de54",
            "svfprintf_reentrant": "0x00078d90",
            "update_cache": "0x000737d8",
        }
        with open(os.path.join(
                ROOT, "recon/catalogs/function_names_app.json")) as stream:
            manifest = json.load(stream)
        aliases = gen_function_aliases.load_link_aliases("app", manifest)
        self.assertEqual(expected, {name: aliases[name] for name in expected})
        with open(os.path.join(
                ROOT, "recon/symbols/g1_app_function_aliases.ld")) as stream:
            fragment = stream.read()
        for address in expected.values():
            owner = manifest["by_address"][address]
            source = owner["name"] + ".c"
            self.assertTrue(os.path.exists(os.path.join(
                ROOT, "recon/symbolized/app", source)), source)
        for alias, address in expected.items():
            target = manifest["by_address"][address]["name"]
            line = "PROVIDE(%s = %s); /* %s */" % (alias, target, address)
            self.assertEqual(1, fragment.count(line), line)
        with open(os.path.join(
                ROOT, "recon/analysis/app_link_residue.json")) as stream:
            residue = json.load(stream)
        unresolved = {row["symbol"] for row in residue["entries"]}
        self.assertFalse(set(expected) & unresolved)

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
