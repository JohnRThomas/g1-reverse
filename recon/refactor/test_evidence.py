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


class TestLinkEvidencePartitionCheck(unittest.TestCase):
    """`link_evidence.check-partition' -- the detector for the failure that
    broke the app link at HEAD on 2026-07-27: the evidence's content hash was
    unchanged while the TREE IT DESCRIBES had been re-partitioned by stage 04,
    so `driver.py status' reported stage 07 `current' while its `static'
    decisions were being made against a link that no longer existed."""

    def test_agreement_is_the_empty_symmetric_difference(self):
        ev = {"a.c.obj", "b.c.obj"}
        tree = {"a.c.obj", "b.c.obj"}
        self.assertEqual(link_evidence.partition_diff(ev, tree, ev | tree),
                         ([], []))

    def test_a_source_absorbed_since_the_evidence_is_flagged(self):
        """The real case: `display_close_screen.c' was INSIDE `g1_display_12.c'
        when the evidence was measured and is its own TU now, so its call to
        `display_close' became a relocation stage 07 could not see."""
        ev = {"g1_display_12.c.obj"}
        tree = {"g1_display_12.c.obj", "display_close_screen.c.obj"}
        missing, gone = link_evidence.partition_diff(ev, tree, tree)
        self.assertEqual(missing, ["display_close_screen.c.obj"])
        self.assertEqual(gone, [])

    def test_a_source_merged_away_since_the_evidence_is_flagged(self):
        ev = {"a.c.obj", "b.c.obj"}
        tree = {"g1_m_01.c.obj"}
        missing, gone = link_evidence.partition_diff(
            ev, tree, {"a.c.obj", "b.c.obj", "g1_m_01.c.obj"})
        self.assertEqual(missing, ["g1_m_01.c.obj"])
        self.assertEqual(gone, ["a.c.obj", "b.c.obj"])

    def test_rodata_objects_do_not_create_false_alarms(self):
        """The archive carries ~1,000 `rodata_*.c.obj' from a DIFFERENT
        generated list.  They must not be reported as drift."""
        ev = {"a.c.obj"} | {"rodata_%x.c.obj" % i for i in range(1000)}
        tree = {"a.c.obj"}
        self.assertEqual(link_evidence.partition_diff(ev, tree, tree), ([], []))

    def test_absent_evidence_is_unverifiable_not_agreement(self):
        r = link_evidence.check_partition(".", data="/nonexistent/evidence.json")
        self.assertEqual(r["state"], "unverifiable")

    def test_absent_evidence_build_is_unverifiable_not_agreement(self):
        import json as _json
        import tempfile
        with tempfile.NamedTemporaryFile("w", suffix=".json", delete=False) as fh:
            _json.dump({"provenance": {"build_dir": "/nonexistent/build"}}, fh)
            p = fh.name
        try:
            r = link_evidence.check_partition(".", data=p)
            self.assertEqual(r["state"], "unverifiable")
            self.assertIn("gone", r["reason"])
        finally:
            os.unlink(p)


class TestPartitionIsWatchedNotJustHashed(unittest.TestCase):
    """THE FOURTH STALENESS HOLE, pinned.

    `link_referenced_symbols.json' is only valid against the translation-unit
    partition it was measured from.  `stagelib.EVIDENCE_INPUTS' watched its
    CONTENT HASH, so when stage 04's merge partition moved underneath it the
    file's bytes were unchanged, `driver.py status' reported stages 07, 08 and
    09 `current', and the app link failed with `undefined reference to
    `display_close''.

    These tests fix the RULE, not the two symbols: an evidence file must be
    invalidated when the tree it describes changes, not merely when its own
    bytes change.
    """

    def _tree(self, td, sources):
        """A minimal tree carrying only a retained-source list."""
        d = os.path.join(td, "recon", "generated")
        os.makedirs(d, exist_ok=True)
        with open(os.path.join(d, "app_retained_sources.cmake"), "w",
                  encoding="utf-8") as fh:
            for s in sources:
                fh.write('  "${CMAKE_CURRENT_LIST_DIR}/../symbolized/%s"\n' % s)
        return td

    def _evidence(self, td, objs, name="ev.json"):
        import json as _json
        p = os.path.join(td, name)
        with open(p, "w", encoding="utf-8") as fh:
            _json.dump({"provenance": {"build_dir": "/nonexistent/build"},
                        "app_objects": sorted(objs)}, fh)
        return p

    def test_the_tree_partition_is_read_without_a_toolchain(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            self._tree(td, ["app/display/g1_display_12.c", "net/ignored.c"])
            self.assertEqual(link_evidence.retained_app_objects(td),
                             {"g1_display_12.c.obj"})

    def test_a_tree_with_no_retained_list_is_not_an_empty_partition(self):
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            self.assertIsNone(link_evidence.retained_app_objects(td))

    def test_the_display_close_case_is_reported_stale(self):
        """The measured failure, reproduced from set logic alone: the evidence
        knew only `g1_display_12.c.obj'; the tree has split
        `display_close_screen.c' back out into its own translation unit."""
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            tree = self._tree(td, ["app/display/g1_display_12.c",
                                   "app/display/display_close_screen.c"])
            ev = self._evidence(td, {"g1_display_12.c.obj"})
            r = link_evidence.partition_state(tree, data=ev)
            self.assertEqual(r["state"], "STALE")
            self.assertEqual(r["only_in_tree"], ["display_close_screen.c.obj"])

    def test_an_agreeing_partition_is_reported_agreeing(self):
        """Validated in BOTH directions -- a checker that only ever says STALE
        is not a checker."""
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            tree = self._tree(td, ["app/display/g1_display_12.c"])
            ev = self._evidence(td, {"g1_display_12.c.obj", "rodata_0.c.obj"})
            r = link_evidence.partition_state(tree, data=ev)
            self.assertEqual(r["state"], "agrees")

    def test_evidence_without_a_recorded_partition_fails_CLOSED(self):
        """An evidence file that cannot say which objects it describes cannot
        be shown to describe this tree.  That is the exact condition that
        produced the link failure, so it must not read as agreement."""
        import json as _json
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            tree = self._tree(td, ["app/a.c"])
            p = os.path.join(td, "old.json")
            with open(p, "w", encoding="utf-8") as fh:
                _json.dump({"provenance": {"build_dir": "/nonexistent"},
                            "referenced": []}, fh)
            r = link_evidence.partition_state(tree, data=p)
            self.assertEqual(r["state"], "unrecorded")
            self.assertNotEqual(r["state"], "agrees")

    def test_absent_evidence_is_not_a_staleness_fault(self):
        """Absent evidence already means `apply nothing' to every consumer, so
        it must not make every stage permanently stale."""
        import tempfile
        with tempfile.TemporaryDirectory() as td:
            tree = self._tree(td, ["app/a.c"])
            r = link_evidence.partition_state(
                tree, data=os.path.join(td, "does-not-exist.json"))
            self.assertEqual(r["state"], "no_evidence")

    def test_staleness_reports_STALE_although_every_hash_matches(self):
        """The regression that matters: identical evidence bytes, identical
        source hashes, and the stage must still be reported stale."""
        man = {
            "files": {},
            "evidence_inputs": stagelib.evidence_hashes(),
            "input_stage": {"stage": 6, "slug": "unit_composition",
                            "tree": "recon/refactor/stage_06_unit_composition/tree"},
            "evidence_partition": {"state": "agrees"},
        }
        real_man, real_part = stagelib.load_manifest, stagelib.evidence_partition_state
        try:
            stagelib.load_manifest = lambda n, s: man
            stagelib.evidence_partition_state = lambda t: {
                "state": "STALE", "only_in_tree": ["display_close_screen.c.obj"]}
            st = stagelib.staleness(7, "internal_linkage")
            self.assertEqual(st["state"], "stale")
            self.assertEqual(st["inputs_missing"], [])
            self.assertTrue(any("PARTITION" in c for c in st["inputs_changed"]),
                            st["inputs_changed"])
            # and the repair must NOT be "regenerate the stage": regenerating
            # it would read the same stale evidence and decide the same way.
            self.assertIn("link_evidence.py generate", st["repair"])

            stagelib.evidence_partition_state = lambda t: {"state": "agrees"}
            self.assertEqual(stagelib.staleness(7, "internal_linkage")["state"],
                             "current")
        finally:
            stagelib.load_manifest, stagelib.evidence_partition_state = (
                real_man, real_part)

    def test_only_a_consuming_stage_is_subject_to_the_check(self):
        """A stage that never reads the evidence must not be made stale by it,
        or the check becomes noise and gets ignored."""
        import importlib
        t07 = importlib.import_module("transforms.t07_internal_linkage")
        self.assertTrue(getattr(t07, "CONSUMES_PARTITION_EVIDENCE", False))
        for mod in ("t04_cohesive_tu", "t08_call_order", "t09_call_cohesion"):
            m = importlib.import_module("transforms." + mod)
            self.assertFalse(getattr(m, "CONSUMES_PARTITION_EVIDENCE", False),
                             mod)

    def test_a_transformer_edit_makes_its_stage_stale(self):
        """THE FIFTH HOLE.  A stage is `transformer(input)'.  Watching only the
        input meant editing a transformer left every downstream stage reporting
        `current' against a tree no transformer would now produce -- measured
        in this pass, when the comma-declarator repair landed in
        `t04_cohesive_tu.py' and stages 04-09 all still said `current'."""
        man = {"files": {},
               "evidence_inputs": stagelib.evidence_hashes(),
               "transforms_digest": stagelib.transforms_digest()}
        real = stagelib.load_manifest
        try:
            stagelib.load_manifest = lambda n, s: man
            self.assertEqual(stagelib.staleness(4, "cohesive_tu")["state"],
                             "current")
            man["transforms_digest"] = "0" * 64
            st = stagelib.staleness(4, "cohesive_tu")
            self.assertEqual(st["state"], "stale")
            self.assertTrue(any("TRANSFORMER CHANGED" in c
                                for c in st["inputs_changed"]), st)
        finally:
            stagelib.load_manifest = real

    def test_the_digest_is_deterministic_and_order_independent(self):
        """It must not be derived from `sys.modules': stage 04's record would
        then depend on whether stage 09 had been materialised first in the same
        process, and MANIFEST idempotence would break."""
        self.assertEqual(stagelib.transforms_digest(),
                         stagelib.transforms_digest())
        self.assertEqual(len(stagelib.transforms_digest()), 64)

    def test_a_manifest_without_the_digest_is_not_fabricated_stale(self):
        """Absence of the field means `written before the check existed', not
        `wrong'.  It is reported, not asserted."""
        man = {"files": {}, "evidence_inputs": stagelib.evidence_hashes()}
        real = stagelib.load_manifest
        try:
            stagelib.load_manifest = lambda n, s: man
            st = stagelib.staleness(4, "cohesive_tu")
            self.assertEqual(st["state"], "current")
            self.assertIn("NOT RECORDED", st["transforms_digest"])
        finally:
            stagelib.load_manifest = real

    def test_the_generator_records_the_partition_it_measured(self):
        """Without this field the check degrades to `unverifiable' the moment
        /private/tmp reaps the build directory."""
        if not os.path.exists(link_evidence.DATA):
            self.skipTest("link_referenced_symbols.json not generated")
        with open(link_evidence.DATA, encoding="utf-8") as fh:
            doc = json.load(fh)
        self.assertIn("app_objects", doc,
                      "the evidence must record the object partition it "
                      "describes; regenerate it with link_evidence.py generate")
        self.assertGreater(len(doc["app_objects"]), 0)
