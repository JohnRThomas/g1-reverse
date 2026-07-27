"""The include closure and the declaration canonicaliser are the two places
where stage 03 decides what the pipeline can SEE and what it may MERGE.  Both
had a silent-wrong failure mode before they were tested, so both get a test.

    PYTHONSAFEPATH=1 .venv/bin/python -m unittest discover -s recon/refactor -p 'test_*.py'
"""

import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import input_set  # noqa: E402
from transforms import t03_module_structure as t03  # noqa: E402


class TestIncludeClosure(unittest.TestCase):
    """R2: the input set must account for EVERY quoted include in the build."""

    @classmethod
    def setUpClass(cls):
        cls.s = input_set.derive()

    def test_header_fragments_are_enumerated(self):
        # the exact gap stage 02 s5.3 filed: a .h reachable only from an .inc
        self.assertIn("recon/symbolized/app/ble_process_put_common.h",
                      self.s.transformable)

    def test_closure_is_transitive(self):
        # g1_net_ram_reloc.h is reachable ONLY through g1_net_symbols.h
        self.assertIn("recon/symbols/g1_net_ram_reloc.h", self.s.transformable)

    def test_include_path_resolution_is_used(self):
        # 1,615 sources spell this unqualified; it resolves via -I, not relative
        self.assertIn("recon/symbols/g1_app_symbols.h", self.s.transformable)

    def test_every_quoted_include_is_accounted_for(self):
        """The property that makes the set an authority rather than a guess.

        Anything unresolved must be satisfied from the toolchain/Zephyr search
        path.  Today that is exactly one entry -- `lsm6dso.c`, a Zephyr driver
        TU textually included by our LSM6DSO glue.  If this list grows, the
        pipeline has stopped seeing something the compiler sees.
        """
        self.assertEqual(self.s.provenance["unresolved_quoted_includes"],
                         ["lsm6dso.c"])

    def test_protected_fragments_are_never_transformable(self):
        """R1 holds through the closure, not just through the seed list."""
        for rel in self.s.provenance["header_fragments_protected"]:
            self.assertNotIn(rel, self.s.transformable)
            self.assertIn(rel, self.s.quarantined_protected)

    def test_build_machinery_is_owned(self):
        """C6: a move transaction must be able to rewrite what names paths."""
        for rel in ("recon/generated/app_retained_sources.cmake",
                    "recon/application/app/CMakeLists.txt"):
            self.assertIn(rel, self.s.transformable)


class TestDeclarationCanonicalisation(unittest.TestCase):
    """Only three equivalences may be folded; everything else stays distinct."""

    def same(self, a, b):
        ca, cb = t03._canon_decl(a), t03._canon_decl(b)
        self.assertIsNotNone(ca, a)
        self.assertEqual(ca, cb, "%r vs %r" % (a, b))

    def differ(self, a, b):
        ca, cb = t03._canon_decl(a), t03._canon_decl(b)
        self.assertNotEqual(ca, cb, "%r vs %r" % (a, b))

    def test_whitespace_is_not_part_of_a_type(self):
        self.same("extern int f(int, void *);", "extern int f(int,void*);")

    def test_unsigned_is_unsigned_int(self):
        self.same("extern void f(unsigned, unsigned);",
                  "extern void f(unsigned int, unsigned int);")

    def test_parameter_names_are_not_part_of_a_type(self):
        self.same("extern int f(unsigned int a, void *b, unsigned int n);",
                  "extern int f(unsigned int, void *, unsigned int);")

    def test_int_is_never_merged_with_unsigned_int(self):
        self.differ("extern void f(int);", "extern void f(unsigned int);")

    def test_typedefs_are_never_resolved(self):
        self.differ("extern void f(uint32_t);", "extern void f(unsigned int);")

    def test_arity_difference_survives(self):
        self.differ("extern int f(uint32_t, void *, uint32_t);",
                    "extern int f(unsigned int, void *, int, unsigned int, unsigned int);")

    def test_return_type_difference_survives(self):
        self.differ("extern void *f(void *, int, uint32_t);",
                    "extern void f(void *, int, uint32_t);")

    def test_attribute_keeps_a_declaration_distinct(self):
        """The round-3 bug: noreturn must not be discarded, and must not be
        mistaken for the declared identifier."""
        a = "extern __attribute__((noreturn)) void g(uintptr_t, uint32_t);"
        b = "extern void g(uintptr_t, uint32_t);"
        self.differ(a, b)
        self.assertEqual(t03._decl_symbol(a), "g")
        self.assertEqual(t03._decl_symbol(b), "g")

    def test_function_pointer_declarators_are_refused(self):
        self.assertIsNone(
            t03._canon_decl("extern void (*fp)(int, int);"))


class TestDefinitionScan(unittest.TestCase):
    """A module header puts callers and the definition in one TU for the first
    time; the transformer must make that comparison itself (R4)."""

    SRC = (
        "#include <stdint.h>\n"
        "extern int helper(int);\n"
        "void accumulate(int param_1, int param_2)\n"
        "{\n"
        "    if (param_1) { helper(param_2); }\n"
        "}\n"
    )

    def test_definition_is_found_and_canonicalised(self):
        d = t03._definitions(self.SRC)
        self.assertIn("accumulate", d)
        self.assertEqual(d["accumulate"],
                         t03._canon_decl("extern void accumulate(int,int);"))

    def test_a_declaration_is_not_mistaken_for_a_definition(self):
        self.assertNotIn("helper", t03._definitions(self.SRC))

    def test_control_flow_is_not_mistaken_for_a_definition(self):
        self.assertNotIn("if", t03._definitions(self.SRC))


if __name__ == "__main__":
    unittest.main()
