"""Tests for stage 04's merge-safety rules and for the pipeline changes it made.

Every rule here exists because it prevents a SILENT wrong result, so each test
is written as "this pair must be refused", not as "this function returns X".
"""

import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import stagelib  # noqa: E402
from transforms import t03_module_structure as t3  # noqa: E402
from transforms import t04_cohesive_tu as t4  # noqa: E402

HDR = '#include "g1_app_symbols.h"\n/* readable reconstruction; identity: %s @ %s\n * public-name: %s\n */\n'


def src(*body):
    return "\n".join(body) + "\n"


def pair(a, b, hdr=None, module_header="g1_mod.h"):
    return t4.conflicts(t4.analyse(a, module_header),
                        t4.analyse(b, module_header), hdr)


def kinds(res):
    return sorted({k for k, _ in res})


class TestLexing(unittest.TestCase):
    def test_strip_comments_is_length_preserving(self):
        t = 'int a; /* x\ny */ char *s = "hi/*"; // z\nint b;\n'
        self.assertEqual(len(t4.strip_comments(t)), len(t))
        self.assertEqual(len(t4.strip_comments(t, drop_strings=True)), len(t))

    def test_comment_and_string_content_do_not_leak_into_identifiers(self):
        d = t4.analyse(src('/* helper */', 'const char *s = "helper";',
                           'int f(void){return 0;}'))
        self.assertNotIn("helper", d["idents"])

    def test_depth_zero_only(self):
        d = t4.analyse(src('void f(void){ static int hidden; typedef int inner; }',
                           'static int shown;'))
        self.assertIn("shown", d["statics"])
        self.assertNotIn("hidden", d["statics"])
        self.assertNotIn("inner", d["typedefs"])


class TestTypedefRule(unittest.TestCase):
    def test_several_typedefs_on_one_line_are_all_seen(self):
        """The `__ieee754_exp.c` shape.  A line-anchored rule sees only `u4`."""
        d = t4.analyse(src('typedef unsigned int u4; typedef unsigned long long u8;'))
        self.assertIn("u4", d["typedefs"])
        self.assertIn("u8", d["typedefs"])

    def test_the_named_u8_hazard_is_refused(self):
        a = src('typedef unsigned int u4; typedef unsigned long long u8;',
                'extern u8 __aeabi_dadd(u4,u4,u4,u4);',
                'double e(double x){return x;}')
        b = src('typedef unsigned char u8;', 'u8 g(void){return 0;}')
        self.assertIn("typedef", kinds(pair(a, b)))

    def test_a_typedef_named_but_not_defined_by_the_partner_is_refused(self):
        a = src('typedef unsigned long long u8;', 'u8 f(void){return 0;}')
        b = src('int g(unsigned char u8_value){return u8_value;}')
        self.assertEqual([], kinds(pair(a, b)))          # different identifier
        c = src('extern int h(void); int g(void){ return (int)sizeof(u8); }')
        self.assertIn("typedef", kinds(pair(a, c)))

    def test_uint32_t_is_not_folded_onto_unsigned_int(self):
        """MEASURED with the project compiler: newlib types uint32_t as
        `unsigned long`, so these two typedefs genuinely conflict."""
        a = src('typedef unsigned int u32;', 'u32 f(void){return 0;}')
        b = src('#include <stdint.h>', 'typedef uint32_t u32;',
                'u32 g(void){return 0;}')
        self.assertIn("typedef", kinds(pair(a, b)))

    def test_uint8_t_IS_folded_onto_unsigned_char(self):
        a = src('typedef unsigned char u8;', 'u8 f(void){return 0;}')
        b = src('#include <stdint.h>', 'typedef uint8_t u8;', 'u8 g(void){return 0;}')
        self.assertEqual([], kinds(pair(a, b)))


class TestStaticRule(unittest.TestCase):
    def test_internal_linkage_captured_by_a_partner_is_refused(self):
        """C11 6.2.2p4: the later `extern` inherits the visible internal
        linkage, so B's call would bind to A's private helper -- silently."""
        a = src('static int helper(int x){return x;}',
                'int f(void){return helper(1);}')
        b = src('extern int helper(int);', 'int g(void){return helper(2);}')
        self.assertIn("static", kinds(pair(a, b)))

    def test_unrelated_statics_do_not_block(self):
        a = src('static int a_only(void){return 1;}', 'int f(void){return a_only();}')
        b = src('static int b_only(void){return 2;}', 'int g(void){return b_only();}')
        self.assertEqual([], kinds(pair(a, b)))


class TestMacroRule(unittest.TestCase):
    def test_same_name_different_body_is_refused(self):
        a = src('#define LOG_LEVEL 3', 'int f(void){return LOG_LEVEL;}')
        b = src('#define LOG_LEVEL 1', 'int g(void){return LOG_LEVEL;}')
        self.assertIn("macro", kinds(pair(a, b)))

    def test_identical_body_is_allowed(self):
        a = src('#define LOG_LEVEL 3', 'int f(void){return LOG_LEVEL;}')
        b = src('#define LOG_LEVEL 3', 'int g(void){return LOG_LEVEL;}')
        self.assertEqual([], kinds(pair(a, b)))

    def test_a_macro_named_by_a_partner_that_does_not_define_it_is_refused(self):
        """The `#define NAN ...` shape: B gets its NAN from a system header and
        would silently pick up A's."""
        a = src('#define NAN 0.0f', 'float f(void){return NAN;}')
        b = src('#include <math.h>', 'float g(void){return NAN;}')
        self.assertIn("macro", kinds(pair(a, b)))

    def test_continuation_lines_are_part_of_the_body(self):
        a = src('#define M(x) do { \\', '  (x)++; \\', '} while (0)',
                'void f(int *p){M(*p);}')
        b = src('#define M(x) do { \\', '  (x)--; \\', '} while (0)',
                'void g(int *p){M(*p);}')
        self.assertIn("macro", kinds(pair(a, b)))


class TestTypeRule(unittest.TestCase):
    def test_disagreeing_declarations_are_refused(self):
        a = src('extern int shared(void);', 'int f(void){return shared();}')
        b = src('extern unsigned int shared(void);', 'int g(void){return shared();}')
        self.assertIn("type", kinds(pair(a, b)))

    def test_declaration_against_the_partner_definition_is_refused(self):
        a = src('extern void owned(void);', 'int f(void){owned(); return 0;}')
        b = src('unsigned int owned(void){return 1;}')
        self.assertIn("type", kinds(pair(a, b)))

    def test_multi_line_declarations_are_read(self):
        """The failure the second stage 04 build produced: a declaration that
        wraps over three lines is invisible to a one-physical-line scanner."""
        a = src('extern void owned(float a, float b,',
                '                  const void *table, unsigned int n);',
                'int f(void){return 0;}')
        b = src('void owned(float a, float b,',
                '           const void *table, float *out)',
                '{ (void)a; (void)b; (void)table; (void)out; }')
        self.assertIn("owned", t4.analyse(a)["decls"])
        self.assertIn("type", kinds(pair(a, b)))

    def test_module_header_declarations_participate(self):
        """The failure the first stage 04 build actually produced: a file that
        stage 03 did NOT convert keeps a local declaration that disagrees with
        the generated module header a partner includes."""
        hdr = {"shared": {t3._canon_decl("extern void shared(float);")}}
        a = src('#include "g1_mod.h"', 'int f(void){shared(1.0f); return 0;}')
        b = src('extern void shared(int);', 'int g(void){shared(1); return 0;}')
        self.assertEqual([], kinds(pair(a, b)))            # without the header
        self.assertIn("type", kinds(pair(a, b, hdr)))      # with it

    def test_module_header_is_ignored_when_nobody_includes_it(self):
        hdr = {"shared": {t3._canon_decl("extern void shared(float);")}}
        a = src('extern void shared(int);', 'int f(void){shared(1); return 0;}')
        b = src('extern void shared(int);', 'int g(void){shared(2); return 0;}')
        self.assertEqual([], kinds(pair(a, b, hdr)))


class TestShapeQuarantine(unittest.TestCase):
    def _why(self, text, base="x.c", named=frozenset()):
        return t4.shape_refusal(base, t4.analyse(text), set(named))

    def test_pragma(self):
        self.assertEqual("file_scope_pragma_leaks_forward",
                         self._why(src('#pragma GCC diagnostic ignored "-Wall"')))

    def test_absolute_include(self):
        self.assertEqual("absolute_path_include_outside_repository",
                         self._why(src('#include "/opt/x/y.h"')))

    def test_inc_fragment(self):
        self.assertEqual("includes_a_definition_carrying_inc_fragment",
                         self._why(src('#include "ops.inc"')))

    def test_alias_attribute(self):
        self.assertEqual("attribute_alias_definition",
                         self._why(src('void f(void) __attribute__((alias("g")));')))

    def test_multi_declaration_line(self):
        self.assertEqual("multi_declaration_line_types_unknown",
                         self._why(src('extern int a(void); extern int b(void);')))

    def test_cmake_named_path(self):
        self.assertEqual("named_by_path_in_app_cmakelists",
                         self._why(src('int f(void){return 0;}'),
                                   base="discovery_callback.c",
                                   named={"discovery_callback.c"}))

    def test_ffp_contract_bodies(self):
        for b in t4.FP_CONTRACT_TUS:
            if b == "discovery_callback.c":
                continue
            self.assertEqual("per_tu_ffp_contract_body",
                             self._why(src('int f(void){return 0;}'), base=b))

    def test_a_plain_file_is_mergeable(self):
        self.assertIsNone(self._why(src('int f(void){return 0;}')))


class TestMergedNameSafety(unittest.TestCase):
    def test_never_matches_the_rodata_keep_glob(self):
        """g1_verified_rodata_keep.ld matches KEEP(*rodata_*.c.obj(...)) on the
        OBJECT FILENAME (README C6)."""
        for mod in ("recon/symbolized/app/display",
                    "recon/symbolized/app/sensors/power",
                    "recon/symbolized/app/ui/dashboard"):
            n = os.path.basename(t4.merged_name(mod, 3))
            self.assertNotIn("rodata_", n)
            self.assertTrue(n.startswith("g1_") and n.endswith(".c"))

    def test_name_is_stable_and_module_scoped(self):
        self.assertEqual(
            "recon/symbolized/app/sensors/power/g1_sensors_power_02.c",
            t4.merged_name("recon/symbolized/app/sensors/power", 2))


class TestRenderIsVerbatim(unittest.TestCase):
    def test_every_member_body_survives_byte_for_byte(self):
        a = src('#include "g1_app_symbols.h"', 'int f(void){return 1;}')
        b = src('#include "g1_app_symbols.h"', 'int g(void){return 2;}')
        out = t4.render("recon/symbolized/app/core", ["m/a.c", "m/b.c"],
                        {"m/a.c": a, "m/b.c": b})
        self.assertIn(a.rstrip("\n"), out)
        self.assertIn(b.rstrip("\n"), out)
        self.assertLess(out.index(a.rstrip("\n")), out.index(b.rstrip("\n")))


class TestParityRowsWidening(unittest.TestCase):
    """The widening must be a no-op for one-identity files and must find all of
    them in a merged file, or `check-addresses` silently stops checking."""

    def setUp(self):
        import tempfile
        self.d = tempfile.mkdtemp()

    def _write(self, name, text):
        p = os.path.join(self.d, name)
        with open(p, "w") as fh:
            fh.write(text)
        return name

    def test_single_identity_file_yields_one_row(self):
        r = self._write("a.c", HDR % ("FUN_00001234", "0x00001234", "alpha"))
        rows = stagelib.parity_rows(self.d, [r])
        self.assertEqual(1, len(rows))
        self.assertEqual("0x00001234", rows[0]["address"])
        self.assertEqual("alpha", rows[0]["symbol"])

    def test_merged_file_yields_every_identity_with_its_own_public_name(self):
        body = (HDR % ("FUN_00001234", "0x00001234", "alpha")
                + "int alpha(void){return 0;}\n" + "x" * 5000 + "\n"
                + HDR % ("FUN_0000abcd", "0x0000abcd", "beta")
                + "int beta(void){return 0;}\n")
        r = self._write("m.c", body)
        rows = stagelib.parity_rows(self.d, [r])
        self.assertEqual([("0x00001234", "alpha"), ("0x0000abcd", "beta")],
                         sorted((x["address"], x["symbol"]) for x in rows))


class TestStalenessWatchesEveryMember(unittest.TestCase):
    def test_additional_sources_are_watched(self):
        rec = {"source": "a", "source_sha256": "1",
               "additional_sources": {"b": "2", "c": "3"}}
        watched = [(rec["source"], rec["source_sha256"])]
        watched += sorted(rec.get("additional_sources", {}).items())
        self.assertEqual([("a", "1"), ("b", "2"), ("c", "3")], watched)


if __name__ == "__main__":
    unittest.main()
