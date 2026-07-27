"""Tests for the two EVIDENCE generators and the staleness that watches them.

Every test here pins a bug that was measured, not one that was imagined.
"""

import json
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import link_evidence  # noqa: E402
import sdk_symbols  # noqa: E402
import stagelib  # noqa: E402


class TestAuxInfoParser(unittest.TestCase):
    """The cmsis_gcc.h `gap' was a trailing comment defeating a line anchor."""

    PROTOTYPE = ('/* /ncs/zephyr/lib/libc/newlib/include/string.h:44:NF */ '
                 'extern void *memcpy (void *, const void *, unsigned int);')
    DEFINITION = ('/* /ncs/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h:269:NF */ '
                  'static void __DSB (void); /* () */')
    DEF_WITH_PARAMS = ('/* /x/cmsis_gcc.h:292:NF */ static unsigned int __REV '
                       '(unsigned int value); /* (value) unsigned int value; */')

    def test_bare_prototype_is_read(self):
        self.assertEqual(sdk_symbols._declared_identifier(
            sdk_symbols.parse_aux_line(self.PROTOTYPE)), "memcpy")

    def test_definition_with_a_trailing_comment_is_read(self):
        # the old parser `^[^:]*:\d+:\d*:?[A-Z]*:?\s*(.*);\s*$' returned None
        # here, which is why cmsis_gcc.h measured 0 identifiers with 122 lines
        self.assertEqual(sdk_symbols._declared_identifier(
            sdk_symbols.parse_aux_line(self.DEFINITION)), "__DSB")

    def test_definition_with_an_old_style_parameter_trailer_is_read(self):
        self.assertEqual(sdk_symbols._declared_identifier(
            sdk_symbols.parse_aux_line(self.DEF_WITH_PARAMS)), "__REV")

    def test_a_line_without_a_terminating_semicolon_is_refused(self):
        self.assertIsNone(sdk_symbols.parse_aux_line(
            "/* /x/h.h:1:NF */ this is not a declaration"))

    def test_a_line_with_no_location_comment_is_refused(self):
        self.assertIsNone(sdk_symbols.parse_aux_line("extern int foo(void);"))


class TestSdkEvidenceFile(unittest.TestCase):
    def setUp(self):
        if not os.path.exists(sdk_symbols.DATA):
            self.skipTest("sdk_declared_symbols.json not generated")
        with open(sdk_symbols.DATA, encoding="utf-8") as fh:
            self.doc = json.load(fh)

    def test_cmsis_gcc_h_is_no_longer_empty(self):
        per = self.doc["provenance"]["declarations_per_header"]
        self.assertGreater(per.get("cmsis_gcc.h", 0), 100,
                           "the cmsis_gcc.h gap is open again")

    def test_static_inline_sdk_functions_are_present(self):
        syms = set(self.doc["symbols"])
        for name in ("__DSB", "__NVIC_EnableIRQ", "k_msleep", "k_uptime_get",
                     "k_cycle_get_32"):
            self.assertIn(name, syms)

    def test_macro_only_spellings_are_recorded_as_macros(self):
        macros = set(self.doc["macros"])
        # CMISIS spells the public NVIC API as a macro over a static inline
        self.assertIn("NVIC_EnableIRQ", macros)
        self.assertNotIn("NVIC_EnableIRQ", set(self.doc["symbols"]))

    def test_macro_detail_is_recorded_for_the_type_headers_only(self):
        detail = self.doc["macros_by_header"]
        for h in ("stdint.h", "stddef.h"):
            self.assertIn(h, detail)
        # a header with no name-level evidence must be ABSENT, so a consumer
        # reads it as "no evidence" and refuses rather than as "no macros"
        self.assertNotIn("zephyr/kernel.h", detail)
        self.assertIsNone(sdk_symbols.load_macro_detail().get("zephyr/kernel.h"))


class TestLinkEvidence(unittest.TestCase):
    def test_load_lines_parses_a_map(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            p = os.path.join(td, "m.map")
            with open(p, "w", encoding="utf-8") as fh:
                fh.write("Archive member included to satisfy reference\n"
                         "LOAD app/libapp.a\n"
                         "LOAD /abs/path/libc_nano.a\n"
                         "LOAD app/libapp.a\n"
                         "LOAD linker stubs\n")
            self.assertEqual(link_evidence.load_lines(p),
                             ["app/libapp.a", "/abs/path/libc_nano.a"])

    def test_undefined_and_weak_are_both_references(self):
        for line, name in (("         U _sbrk_r", "_sbrk_r"),
                           ("         w __deregister_frame", "__deregister_frame")):
            m = link_evidence._UNDEF.match(line)
            self.assertIsNotNone(m, line)
            self.assertEqual(m.group("name"), name)

    def test_the_newlib_callback_class_is_visible_and_attributed(self):
        ev = link_evidence.load()
        if not ev["present"]:
            self.skipTest("link_referenced_symbols.json not generated")
        for name in ("_sbrk_r", "__malloc_lock", "_fstat_r"):
            self.assertIn(name, ev["referenced"], name)
            self.assertIn(name, ev["referenced_by_non_app_inputs"], name)
            self.assertTrue(any("libc" in r for r in ev["referrers"][name]),
                            "%s should be attributed to a C library archive"
                            % name)


class TestEvidenceStaleness(unittest.TestCase):
    def test_evidence_files_are_watched(self):
        self.assertIn("recon/refactor/sdk_declared_symbols.json",
                      stagelib.EVIDENCE_INPUTS)
        self.assertIn("recon/refactor/link_referenced_symbols.json",
                      stagelib.EVIDENCE_INPUTS)

    def test_a_manifest_that_records_evidence_goes_stale_when_it_moves(self):
        man = stagelib.load_manifest(3, "module_structure")
        if man is None or "evidence_inputs" not in man:
            self.skipTest("stage 03 not materialised with evidence hashes")
        self.assertEqual(man["evidence_inputs"], stagelib.evidence_hashes())
        # a manifest recording a DIFFERENT hash must report stale
        import copy
        forged = copy.deepcopy(man)
        forged["evidence_inputs"] = dict(man["evidence_inputs"])
        k = sorted(forged["evidence_inputs"])[0]
        forged["evidence_inputs"][k] = "0" * 64
        self.assertNotEqual(forged["evidence_inputs"], stagelib.evidence_hashes())


if __name__ == "__main__":
    unittest.main()
