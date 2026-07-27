"""Tests for stages 06, 07 and 08.

Each test that pins a bug names the build failure it was found by.
"""

import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from transforms import t06_unit_composition as t6  # noqa: E402
from transforms import t07_internal_linkage as t7  # noqa: E402
from transforms import t08_call_order as t8  # noqa: E402
from transforms import t03_module_structure as t3  # noqa: E402


class TestTopIncludeBlock(unittest.TestCase):
    def _end(self, text):
        return t6.top_include_block_end(t3._blank_comments(text).split("\n"))

    def test_leading_run_of_includes(self):
        self.assertEqual(self._end('#include "a.h"\n#include <b.h>\nint x;\n'), 2)

    def test_comments_and_blanks_do_not_end_the_block(self):
        self.assertEqual(
            self._end('/* banner */\n\n#include "a.h"\n\n/* c */\n#include <b.h>\n'
                      'int x;\n'), 6)

    def test_a_unit_with_no_leading_include_has_no_block(self):
        self.assertEqual(self._end("int x;\n#include <b.h>\n"), 0)


class TestIncludeHoisting(unittest.TestCase):
    """H moves a directive only under two checks; both are exercised."""

    def _run(self, body, spelling_macros):
        text = {"recon/symbolized/app/m/u.c": body}
        orig = dict(text)

        def fake_angle(spell):
            v = spelling_macros.get(spell)
            return None if v is None else set(v)

        saved = t6.angle_macro_names
        t6.angle_macro_names = fake_angle
        try:
            out = t6.hoist_includes("/nonexistent", list(text), text, [])
        finally:
            t6.angle_macro_names = saved
        return text["recon/symbolized/app/m/u.c"], out, orig

    def test_a_late_include_is_hoisted_when_nothing_blocks_it(self):
        body = ('#include <stdint.h>\nint a(void){return 0;}\n'
                '#include <stddef.h>\nint b(void){return 0;}\n')
        new, out, _ = self._run(body, {"<stdint.h>": [], "<stddef.h>": ["NULL"]})
        self.assertEqual(out["totals"]["H_includes_hoisted"], 1)
        self.assertLess(new.index("#include <stddef.h>"), new.index("int a(void)"))

    def test_an_intervening_define_refuses_the_hoist(self):
        body = ('#include <stdint.h>\n#define K 1\nint a(void){return K;}\n'
                '#include <stddef.h>\n')
        new, out, orig = self._run(body, {"<stdint.h>": [], "<stddef.h>": []})
        self.assertEqual(out["refused"]["intervening_preprocessor_directive"], 1)
        self.assertEqual(new, orig["recon/symbolized/app/m/u.c"])

    def test_intervening_code_naming_a_macro_of_the_header_refuses(self):
        body = ('#include <stdint.h>\nint a(void){int NULL_ish=0; return NULL;}\n'
                '#include <stddef.h>\n')
        new, out, orig = self._run(body, {"<stdint.h>": [], "<stddef.h>": ["NULL"]})
        self.assertEqual(
            out["refused"]["intervening_code_names_a_macro_of_the_header"], 1)
        self.assertEqual(new, orig["recon/symbolized/app/m/u.c"])

    def test_no_macro_evidence_means_refuse_not_allow(self):
        body = ('#include <stdint.h>\nint a(void){return 0;}\n'
                '#include <zephyr/kernel.h>\n')
        new, out, orig = self._run(body, {"<stdint.h>": []})   # kernel.h absent
        self.assertEqual(out["refused"]["no_macro_evidence_for_this_header"], 1)
        self.assertEqual(new, orig["recon/symbolized/app/m/u.c"])


class TestDefinitionStart(unittest.TestCase):
    """Regression: `error: duplicate 'static'' in ble/g1_ble_02.c.

    The walk back to the start of a definition accepted a `}' only when the
    depth BEFORE it was 0.  The depth before a function body's closing brace is
    1, so `}' was never a boundary, the walk ran back over whole function
    bodies, and three candidates in one unit resolved to the SAME definition.
    """

    BODY = ('extern int helper(int);\n'
            'void first(int a){ if(a){ a++; } }\n'
            'void second(int b){ b--; }\n'
            'unsigned third(void){ return 0; }\n')

    def test_each_definition_resolves_to_its_own_start(self):
        offs = {n: t7.definition_start(self.BODY, n)
                for n in ("first", "second", "third")}
        self.assertEqual(len(set(offs.values())), 3, offs)
        self.assertTrue(self.BODY[offs["first"]:].startswith("void first"))
        self.assertTrue(self.BODY[offs["second"]:].startswith("void second"))
        self.assertTrue(self.BODY[offs["third"]:].startswith("unsigned third"))

    def test_a_definition_after_a_preprocessor_line_starts_after_it(self):
        body = '#include <stdint.h>\nint only(void){ return 1; }\n'
        off = t7.definition_start(body, "only")
        self.assertTrue(body[off:].startswith("int only"))

    def test_an_unresolvable_span_is_refused_rather_than_guessed(self):
        self.assertIsNone(t7.definition_start("int a(void){return 0;}", "nope"))


class TestBuildPins(unittest.TestCase):
    """Regression: the link failed on a symbol a linker fragment named."""

    def test_foreach_in_lists_gc_roots_are_resolved(self):
        texts = {
            "recon/generated/app_gc_roots.cmake":
                "set(G1_RECOVERED_GC_ROOTS\n  main\n  ble_work_thread\n)\n",
            "recon/application/app/CMakeLists.txt":
                'foreach(_g1_root IN LISTS G1_RECOVERED_GC_ROOTS)\n'
                '  zephyr_ld_options("-Wl,--undefined=${_g1_root}")\n'
                'endforeach()\n',
        }
        got = t7._cmake_forced_symbols(texts)
        self.assertIn("main", got)
        self.assertIn("ble_work_thread", got)

    def test_a_literal_foreach_list_is_resolved(self):
        texts = {"c.txt": 'foreach(_r __sprintf_chk sprintf fprintf)\n'
                          '  zephyr_ld_options("-Wl,--undefined=${_r}")\n'
                          'endforeach()\n'}
        got = t7._cmake_forced_symbols(texts)
        self.assertEqual(got, {"__sprintf_chk", "sprintf", "fprintf"})

    def test_a_literal_undefined_flag_is_resolved(self):
        self.assertIn("main", t7._cmake_forced_symbols({"x": "-Wl,--undefined=main"}))

    def test_linker_fragments_are_discovered_not_listed(self):
        tree = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                            "stage_06_unit_composition", "tree")
        if not os.path.isdir(tree):
            self.skipTest("stage 06 not materialised")
        names, sources = t7.pinned_by_the_build(tree)
        ld = [s for s in sources if s.endswith(".ld")]
        self.assertGreaterEqual(len(ld), 15,
                                "a hard-coded 3-file list is back: %s" % ld)
        self.assertIn("wait_touch_key_release_or_timeout", names)


class TestCallOrder(unittest.TestCase):
    UNIT = ('/*\n * Cohesive translation unit\n */\n'
            '/* ---- a.c ---- */\n'
            '#include "g1_app_symbols.h"\n'
            'void a(void){ b(); }\n'
            '/* ---- b.c ---- */\n'
            'void b(void){ }\n')

    def test_the_unit_include_block_is_lifted_out_of_the_first_member(self):
        pre, members = t8.split_members(self.UNIT)
        self.assertIn('#include "g1_app_symbols.h"', "\n".join(pre))
        self.assertEqual([n for n, _ in members], ["a.c", "b.c"])
        self.assertNotIn("#include", "\n".join(members[0][1]))

    def test_a_callee_defined_after_its_caller_is_moved_before_it(self):
        new, info = t8.reorder(self.UNIT)
        self.assertEqual(info.get("blocks_moved"), 2, info)
        self.assertLess(new.index("---- b.c ----"), new.index("---- a.c ----"))

    def test_a_member_carrying_a_directive_refuses(self):
        unit = self.UNIT.replace("void b(void){ }", "#define Q 1\nvoid b(void){ }")
        new, info = t8.reorder(unit)
        self.assertEqual(info["refused"],
                         "member_block_carries_a_preprocessor_directive")
        self.assertEqual(new, unit)

    def test_a_member_with_a_file_scope_static_refuses(self):
        unit = self.UNIT.replace("void b(void){ }", "static void b(void){ }")
        new, info = t8.reorder(unit)
        self.assertEqual(info["refused"],
                         "member_block_declares_a_file_scope_static")
        self.assertEqual(new, unit)

    def test_a_cycle_is_left_alone(self):
        unit = ('/*\n * Cohesive translation unit\n */\n'
                '/* ---- a.c ---- */\nvoid a(void){ b(); }\n'
                '/* ---- b.c ---- */\nvoid b(void){ a(); }\n')
        new, info = t8.reorder(unit)
        self.assertEqual(info["refused"], "call_graph_has_a_cycle")
        self.assertEqual(new, unit)

    def test_unrelated_members_keep_their_original_order(self):
        unit = ('/*\n * Cohesive translation unit\n */\n'
                '/* ---- a.c ---- */\nvoid a(void){ }\n'
                '/* ---- b.c ---- */\nvoid b(void){ }\n')
        new, info = t8.reorder(unit)
        self.assertTrue(info.get("unchanged"))
        self.assertEqual(new, unit)


if __name__ == "__main__":
    unittest.main()
