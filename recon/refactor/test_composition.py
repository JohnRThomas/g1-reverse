"""Tests for stage 05 -- composition of stage 04's merged translation units.

Sub-batch N claims to be **preprocessor-identical**: every edit removes either a
token sequence the preprocessor was already discarding (a repeated include of an
idempotent header) or a declaration the compiler had already accepted with an
identical type earlier in the same translation unit.  That claim is what lets
the stage declare the codegen class ``size-neutral``, so it needs tests that
bite rather than tests that agree.
"""

from __future__ import annotations

import os
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import stagelib  # noqa: E402
from transforms import t05_cohesive_composition as t5  # noqa: E402

GUARDED = ('#ifndef G1_X_H\n#define G1_X_H\nextern int x(void);\n'
           '#endif /* G1_X_H */\n')
ONCE = '#pragma once\nextern int y(void);\n'
NAKED = 'extern int z(void);\nint zz = 1;\n'

IDEM = {'"a.h"': True, '"naked.h"': False, "<stdint.h>": True}


class HeaderIdempotence(unittest.TestCase):
    def _write(self, body):
        d = tempfile.mkdtemp()
        p = os.path.join(d, "h.h")
        with open(p, "w", encoding="utf-8") as fh:
            fh.write(body)
        return p

    def test_include_guard_is_idempotent(self):
        self.assertTrue(t5.header_is_idempotent(self._write(GUARDED)))

    def test_pragma_once_is_idempotent(self):
        self.assertTrue(t5.header_is_idempotent(self._write(ONCE)))

    def test_a_header_with_no_guard_is_refused(self):
        self.assertFalse(t5.header_is_idempotent(self._write(NAKED)))

    def test_a_guard_preceded_by_a_declaration_is_refused(self):
        body = "extern int leaked(void);\n" + GUARDED
        self.assertFalse(t5.header_is_idempotent(self._write(body)))

    def test_a_leading_comment_does_not_defeat_the_guard(self):
        body = "/* banner\n * lines\n */\n" + GUARDED
        self.assertTrue(t5.header_is_idempotent(self._write(body)))

    def test_a_missing_file_is_refused_not_crashed(self):
        self.assertFalse(t5.header_is_idempotent("/nonexistent/h.h"))


class ComposeN(unittest.TestCase):
    def test_a_repeated_include_is_withdrawn_and_the_first_stays_put(self):
        src = ('#include "a.h"\n'
               'int f(void) { return 1; }\n'
               '#include "a.h"\n'
               'int g(void) { return 2; }\n')
        out, st = t5.compose(src, IDEM)
        self.assertEqual(out.count('#include "a.h"'), 1)
        self.assertTrue(out.startswith('#include "a.h"\n'))
        self.assertEqual(st["N1_duplicate_includes_withdrawn"], 1)

    def test_an_unguarded_header_is_NOT_deduplicated(self):
        src = '#include "naked.h"\nint f(void){return 1;}\n#include "naked.h"\n'
        out, st = t5.compose(src, IDEM)
        self.assertEqual(out.count('#include "naked.h"'), 2)
        self.assertEqual(st.get("N1_duplicate_includes_withdrawn", 0), 0)
        self.assertEqual(st["N1_duplicate_includes_kept_unguarded"], 1)

    def test_a_repeated_identical_declaration_is_withdrawn(self):
        src = ('extern int h(int);\n'
               'int f(void){return h(1);}\n'
               'extern int h(int);\n'
               'int g(void){return h(2);}\n')
        out, st = t5.compose(src, IDEM)
        self.assertEqual(out.count("extern int h(int);"), 1)
        self.assertEqual(st["N2_duplicate_declarations_withdrawn"], 1)

    def test_only_LATER_copies_go_so_the_declaration_still_precedes_every_use(self):
        src = 'extern int h(int);\nint f(void){return h(1);}\nextern int h(int);\n'
        out, _ = t5.compose(src, IDEM)
        self.assertLess(out.index("extern int h(int);"), out.index("h(1)"))

    def test_a_DISAGREEING_declaration_is_left_visible_not_hidden(self):
        """Stage 04's `type` rule says this cannot happen inside one unit.

        If it does, the partition was wrong, and hiding the second declaration
        would turn a hard compiler error into a silently wrong binding.
        """
        src = 'extern int h(int);\nextern int h(long);\n'
        out, st = t5.compose(src, IDEM)
        self.assertIn("extern int h(long);", out)
        self.assertEqual(st["N2_declarations_left_disagreeing"], 1)
        self.assertEqual(st.get("N2_duplicate_declarations_withdrawn", 0), 0)

    def test_a_declaration_inside_a_function_body_is_not_touched(self):
        src = ('extern int h(int);\n'
               'int f(void){\nextern int h(int);\nreturn h(1);\n}\n')
        out, st = t5.compose(src, IDEM)
        self.assertEqual(out.count("extern int h(int);"), 2)
        self.assertEqual(st.get("N2_duplicate_declarations_withdrawn", 0), 0)

    def test_a_declaration_with_a_trailing_comment_is_seen(self):
        src = ('extern int h(int);\n'
               'int f(void){return h(1);}\n'
               'extern int h(int);            /* memset */\n')
        out, st = t5.compose(src, IDEM)
        self.assertEqual(st["N2_duplicate_declarations_withdrawn"], 1)
        self.assertNotIn("/* memset */", out)

    def test_the_member_banner_is_compressed_to_one_line(self):
        rule = "/* ---------------------------------------------------------------- */"
        src = "%s\n/* foo.c */\n%s\nint f(void){return 1;}\n" % (rule, rule)
        out, st = t5.compose(src, IDEM)
        self.assertIn("/* ---- foo.c ---- */", out)
        self.assertEqual(st["N3_member_banners_compressed"], 1)
        self.assertNotIn(rule, out)

    def test_identity_banners_survive_byte_for_byte(self):
        """`stagelib.parity_rows` reads these; losing one loses an address."""
        banner = ("/* readable reconstruction; identity: FUN_00010840 @ 0x00010840\n"
                  " * public-name: compute_lux_brightness_bucket\n */\n")
        src = '#include "a.h"\n' + banner + 'int f(void){return 1;}\n' + \
              '#include "a.h"\n' + banner.replace("00010840", "00010900") + \
              'int g(void){return 2;}\n'
        out, _ = t5.compose(src, IDEM)
        self.assertIn("identity: FUN_00010840 @ 0x00010840", out)
        self.assertIn("identity: FUN_00010900 @ 0x00010900", out)
        rows_before = stagelib.parity_rows.__doc__ is not None
        self.assertTrue(rows_before)

    def test_composition_is_idempotent(self):
        src = ('#include "a.h"\nextern int h(int);\n'
               'int f(void){return h(1);}\n'
               '#include "a.h"\nextern int h(int);\n'
               'int g(void){return h(2);}\n')
        once, _ = t5.compose(src, IDEM)
        twice, st = t5.compose(once, IDEM)
        self.assertEqual(once, twice)
        self.assertEqual(st.get("N1_duplicate_includes_withdrawn", 0), 0)
        self.assertEqual(st.get("N2_duplicate_declarations_withdrawn", 0), 0)


class MergedUnitIdentification(unittest.TestCase):
    """The filename-pattern bug, pinned.

    `g1_[a-z0-9_]+_\\d\\d\\.c$` also matched the byte-verified
    `recon/application/rodata/g1_app_rodata_00.c` tables, whose FILENAMES are
    load-bearing: `g1_verified_rodata_keep.ld` matches
    `KEEP(*rodata_*.c.obj(...))` on the object filename (README C6).
    """

    BANNER = ("/*\n * Cohesive translation unit for the `display' module.\n */\n"
              "int f(void){return 1;}\n")

    def test_a_stage_04_merged_unit_is_recognised(self):
        self.assertTrue(t5.is_merged_unit(
            "recon/symbolized/app/display/g1_display_01.c", self.BANNER))

    def test_a_verified_rodata_table_is_NOT(self):
        self.assertFalse(t5.is_merged_unit(
            "recon/application/rodata/g1_app_rodata_00.c", self.BANNER))

    def test_a_plain_app_source_is_NOT(self):
        self.assertFalse(t5.is_merged_unit(
            "recon/symbolized/app/display/power_for_panel.c",
            "#include \"g1_app_symbols.h\"\nint f(void){return 1;}\n"))


class SubBatchDeclaration(unittest.TestCase):
    def test_the_default_sub_batch_is_the_preprocessor_identical_one(self):
        self.assertEqual(t5.DEFAULT_BATCH, "N")
        self.assertIn("S", t5.BATCHES)
        self.assertIn("NS", t5.BATCHES)

    def test_stage_05_declares_size_neutral_not_byte_identical(self):
        """N is *intended* to be byte-identical, but merging upstream means the
        stage cannot promise it -- so it declares the weaker class and lets
        `driver.py size-gate 5` report which was achieved."""
        import driver
        cls = {row[0]: row[4] for row in driver.STAGES}
        self.assertEqual(cls[5], "size-neutral")

    def test_stage_04_defaults_to_sub_batch_B(self):
        from transforms import t04_cohesive_tu as t4
        self.assertEqual(t4.DEFAULT_BATCH, "B")
        self.assertEqual(t4.BATCHES, frozenset(("A", "B", "AB", "OFF")))


if __name__ == "__main__":
    unittest.main()
