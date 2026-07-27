"""Tests for stage 09, the call-cohesion grouping transformer.

Every rule this stage adds or reuses is exercised here, and so is the defect
that the first stage 09 build found: a file-scope ``extern`` statement with a
comma-separated declarator list, which declares several symbols that every
refusal rule in the pipeline was structurally blind to.
"""

from __future__ import annotations

import json
import os
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import driver  # noqa: E402
import stagelib  # noqa: E402
from transforms import t04_cohesive_tu as t4  # noqa: E402
from transforms import t09_call_cohesion as t9  # noqa: E402


class TestMultiDeclaratorExterns(unittest.TestCase):
    """The rule the first stage 09 build failure produced."""

    #: verbatim from `recon/symbolized/app/core/...` via stage 04's
    #: `g1_core_01.c`; the declaration of `k_sleep(int,int)` inside it is what
    #: collided with `extern int32_t k_sleep(k_timeout_t);` in another member.
    REAL = ('extern void update_box_presence_flag(void*,void*),'
            'init_config_fields_default9(void*),k_sleep(int,int),'
            'st25dv_build_and_write_ndef_records(void*,void*,void*),'
            'set_time_mark(void);\n')

    def test_finds_the_real_corpus_statement(self):
        self.assertEqual(len(t9.multi_declarator_externs(self.REAL)), 1)

    def test_stage_04_shape_rule_is_blind_to_it(self):
        """The measurement that makes this a stage 04 finding, not just a fix."""
        d = t4.analyse(self.REAL)
        self.assertFalse(d["multi_decl_line"],
                         "if this ever becomes True, stage 04 has been repaired "
                         "and t09's own rule is redundant rather than additive")

    def test_stage_04_records_only_the_first_declarator(self):
        d = t4.analyse(self.REAL)
        self.assertIn("update_box_presence_flag", d["decls"])
        for hidden in ("k_sleep", "set_time_mark",
                       "st25dv_build_and_write_ndef_records"):
            self.assertNotIn(hidden, d["decls"])

    def test_a_parameter_list_comma_is_not_a_declarator_separator(self):
        self.assertEqual(
            t9.multi_declarator_externs('extern void f(int, char *, long);\n'), [])

    def test_an_array_bound_comma_is_not_a_declarator_separator(self):
        self.assertEqual(
            t9.multi_declarator_externs('extern int t[(1,2)];\n'), [])

    def test_two_objects_on_one_statement_are_found(self):
        self.assertEqual(len(t9.multi_declarator_externs('extern int a, b;\n')), 1)

    def test_block_scope_extern_is_ignored(self):
        src = 'void f(void){ extern int a, b; (void)a; }\n'
        self.assertEqual(t9.multi_declarator_externs(src), [])

    def test_a_comma_inside_a_comment_does_not_fire(self):
        self.assertEqual(
            t9.multi_declarator_externs('extern int a; /* a, b */\n'), [])

    def test_a_comma_inside_a_string_does_not_fire(self):
        self.assertEqual(
            t9.multi_declarator_externs('extern const char *s;\n'
                                        'const char *t = "a, b";\n'), [])

    def test_blank_groups_is_length_preserving(self):
        s = 'extern void f(int, char), g;'
        self.assertEqual(len(t9._blank_groups(s)), len(s))


class TestShapeRefusal(unittest.TestCase):

    def test_inherits_stage_04s_reasons(self):
        d = t4.analyse('#pragma GCC diagnostic ignored "-Wall"\nint f(void){return 0;}\n')
        self.assertEqual(
            t9.shape_refusal("x.c", d, '#pragma GCC diagnostic ignored "-Wall"\n',
                             set()),
            "file_scope_pragma_leaks_forward")

    def test_adds_the_multi_declarator_reason(self):
        src = TestMultiDeclaratorExterns.REAL
        self.assertEqual(t9.shape_refusal("x.c", t4.analyse(src), src, set()),
                         "multi_declarator_extern_statement_types_unknown")

    def test_a_clean_file_is_not_refused(self):
        src = 'extern int g(void);\nint f(void){return g();}\n'
        self.assertIsNone(t9.shape_refusal("x.c", t4.analyse(src), src, set()))

    def test_the_five_fp_contract_bodies_are_still_refused(self):
        for base in t4.FP_CONTRACT_TUS:
            self.assertEqual(t9.shape_refusal(base, t4.analyse("int f(void){return 0;}\n"),
                                              "int f(void){return 0;}\n", set()),
                             "per_tu_ffp_contract_body")


class TestMergedName(unittest.TestCase):

    def test_never_matches_the_rodata_keep_pattern(self):
        for mod in ("display", "sensors/power", "lib"):
            nm = t9.merged_name(t4.APP_SRC + mod, 3)
            self.assertFalse(os.path.basename(nm).startswith("rodata_"))

    def test_namespace_is_disjoint_from_stage_04s(self):
        mod = t4.APP_SRC + "display"
        s4 = {os.path.basename(t4.merged_name(mod, i)) for i in range(1, 40)}
        s9 = {os.path.basename(t9.merged_name(mod, i)) for i in range(1, 40)}
        self.assertEqual(s4 & s9, set())

    def test_emitted_inside_the_members_own_module_directory(self):
        self.assertEqual(os.path.dirname(t9.merged_name(t4.APP_SRC + "sensors/power", 1)),
                         t4.APP_SRC + "sensors/power")


class TestCallGraph(unittest.TestCase):

    def _facts(self, files):
        return {p: t4.analyse(t) for p, t in files.items()}

    def test_edge_when_one_file_names_what_another_defines(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return b(); }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 1; }\n"}
        edges, adj = t9.call_graph(sorted(files), self._facts(files), files)
        self.assertIn((t4.APP_SRC + "m/a.c", t4.APP_SRC + "m/b.c"), edges)
        self.assertIn(t4.APP_SRC + "m/a.c", adj[t4.APP_SRC + "m/b.c"])

    def test_no_self_edge(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return a(); }\n"}
        edges, _ = t9.call_graph(sorted(files), self._facts(files), files)
        self.assertEqual(edges, set())

    def test_cross_module_edges_are_excluded(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return b(); }\n",
                 t4.APP_SRC + "n/b.c": "int b(void){ return 1; }\n"}
        edges, _ = t9.call_graph(sorted(files), self._facts(files), files)
        self.assertEqual(edges, set())

    def test_a_name_only_in_a_comment_or_string_is_not_an_edge(self):
        files = {t4.APP_SRC + "m/a.c": 'int a(void){ /* b */ return 0; }\n'
                                       'const char *s = "b";\n',
                 t4.APP_SRC + "m/b.c": "int b(void){ return 1; }\n"}
        edges, _ = t9.call_graph(sorted(files), self._facts(files), files)
        self.assertEqual(edges, set())


class TestGrouping(unittest.TestCase):

    def _run(self, files, require_edge=True):
        info = {p: t4.analyse(t) for p, t in files.items()}
        order = sorted(files)
        _edges, adj = t9.call_graph(order, info, files)
        return t9.group_module(order, info, adj, None, require_edge)

    def test_call_cohesion_groups_a_caller_with_its_callee(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return b(); }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 1; }\n"}
        self.assertEqual([len(g) for g in self._run(files)], [2])

    def test_call_cohesion_refuses_unrelated_files(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return 1; }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 2; }\n"}
        self.assertEqual([len(g) for g in self._run(files)], [1, 1])

    def test_the_module_ceiling_batch_groups_them_anyway(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return 1; }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 2; }\n"}
        self.assertEqual([len(g) for g in self._run(files, require_edge=False)], [2])

    def test_a_pairwise_conflict_wins_over_a_call_edge(self):
        """Cohesion never overrides a refusal rule -- rule 4, `typedef'."""
        files = {t4.APP_SRC + "m/a.c": "typedef unsigned long long u8;\n"
                                       "int a(void){ return b(); }\n",
                 t4.APP_SRC + "m/b.c": "typedef unsigned char u8;\n"
                                       "int b(void){ return 1; }\n"}
        self.assertEqual([len(g) for g in self._run(files)], [1, 1])

    def test_a_dupdef_is_refused(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return b(); }\n"
                                       "int dup(void){ return 0; }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 1; }\n"
                                       "int dup(void){ return 0; }\n"}
        self.assertEqual([len(g) for g in self._run(files)], [1, 1])

    def test_the_group_keeps_its_earliest_member_first(self):
        """Emission position is the earliest member's, so first-fit must too."""
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return 1; }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return a(); }\n",
                 t4.APP_SRC + "m/c.c": "int c(void){ return a(); }\n"}
        groups = self._run(files)
        self.assertEqual(groups[0][0], t4.APP_SRC + "m/a.c")

    def test_grouping_is_deterministic(self):
        files = {t4.APP_SRC + "m/a.c": "int a(void){ return b(); }\n",
                 t4.APP_SRC + "m/b.c": "int b(void){ return 1; }\n",
                 t4.APP_SRC + "m/c.c": "int c(void){ return b(); }\n"}
        self.assertEqual(self._run(files), self._run(files))


class TestRender(unittest.TestCase):

    def setUp(self):
        self.mod = t4.APP_SRC + "m"
        self.text = {
            self.mod + "/a.c": "/* identity: FUN_1 @ 0x1 */\nint a(void){ return b(); }\n",
            self.mod + "/b.c": "/* identity: FUN_2 @ 0x2 */\nint b(void){ return 1; }\n",
        }
        self.members = [self.mod + "/a.c", self.mod + "/b.c"]
        self.edges = {(self.mod + "/a.c", self.mod + "/b.c")}
        self.out = t9.render(self.mod, self.members, self.text, self.edges)

    def test_every_member_body_is_reproduced_verbatim(self):
        for m in self.members:
            self.assertIn(self.text[m].rstrip("\n"), self.out)

    def test_every_identity_banner_survives(self):
        self.assertIn("identity: FUN_1 @ 0x1", self.out)
        self.assertIn("identity: FUN_2 @ 0x2", self.out)

    def test_the_banner_names_the_members_and_the_edges(self):
        self.assertIn(" *   a.c", self.out)
        self.assertIn(" *   b.c", self.out)
        self.assertIn("a.c -> b.c", self.out)

    def test_tag_forward_declarations_are_emitted(self):
        text = {self.mod + "/a.c": "extern int f(const struct device *);\n",
                self.mod + "/b.c": "extern int g(const struct device *);\n"}
        out = t9.render(self.mod, sorted(text), text, set())
        self.assertIn("struct device;", out)

    def test_render_is_deterministic(self):
        self.assertEqual(
            self.out, t9.render(self.mod, self.members, self.text, self.edges))


class TestRegistry(unittest.TestCase):

    def test_stage_09_is_registered_and_declares_size_changing(self):
        row = [r for r in driver.STAGES if r[0] == 9]
        self.assertEqual(len(row), 1)
        self.assertEqual(row[0][1], "call_cohesion")
        self.assertEqual(row[0][3], "t09_call_cohesion")
        self.assertEqual(row[0][4], "size-changing")

    def test_every_registered_stage_declares_a_known_class(self):
        for row in driver.STAGES:
            self.assertIn(row[4], stagelib.CODEGEN_CLASSES, row[1])

    def test_every_size_gate_on_disk_agrees_with_the_registry(self):
        """§13 item 3: stage 01's declared class was wrong for the pipeline's
        whole life.  This makes the declared/measured/registry triple a test."""
        declared = {r[0]: r[4] for r in driver.STAGES}
        checked = 0
        for n, slug, _d, _m, _c in driver.STAGES:
            p = os.path.join(HERE, "stage_%02d_%s" % (n, slug), "SIZE_GATE.json")
            if not os.path.exists(p):
                continue
            with open(p, encoding="utf-8") as fh:
                g = json.load(fh)
            self.assertEqual(g["declared_codegen_class"], declared[n], slug)
            self.assertLessEqual(stagelib.CODEGEN_RANK[g["measured_codegen_class"]],
                                 stagelib.CODEGEN_RANK[declared[n]], slug)
            self.assertTrue(g["pass"], slug)
            checked += 1
        self.assertGreater(checked, 0, "no SIZE_GATE.json found at all")


class TestMaterialisedStage(unittest.TestCase):
    """Assertions about the stage tree, skipped when it has not been built."""

    @classmethod
    def setUpClass(cls):
        cls.man = stagelib.load_manifest(9, "call_cohesion")
        if cls.man is None:
            raise unittest.SkipTest("stage 09 has not been materialized")

    def test_manifest_declares_the_class_and_the_oracle_obligation(self):
        self.assertEqual(self.man["declared_codegen_class"], "size-changing")
        self.assertTrue(self.man["oracle_required"])

    def test_address_set_is_identical_to_stage_08(self):
        if stagelib.load_manifest(8, "call_order") is None:
            self.skipTest("stage 08 has not been materialized")
        r = driver.check_addresses(8, 9)
        self.assertTrue(r["identical"], (r["only_in_a"], r["only_in_b"]))

    def test_no_merged_unit_is_named_rodata(self):
        for p in self.man["sub_batches"].get("merged_translation_units", []) or \
                self.man.get("merged_translation_units", []):
            self.assertFalse(os.path.basename(p).startswith("rodata_"), p)

    def test_every_merged_unit_records_all_its_members(self):
        for p in self.man.get("merged_translation_units", []):
            rec = self.man["files"][p]
            members = rec["transformations"]["merged_from"]
            self.assertGreaterEqual(len(members), 2, p)
            # member 1 is `source`; members 2..n must be watched by staleness
            self.assertEqual(len(rec.get("additional_sources", {})),
                             len(members) - 1, p)


if __name__ == "__main__":
    unittest.main()
