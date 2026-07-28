"""Controls for `recon/emulator/scripts/check_app_flash_literals.py`.

This project has had FOUR degenerate fixtures pass vacuously and SIX scanners
beaten by text-anchored parsing, so these tests are written to DISCRIMINATE,
not to be green:

  * every positive control is paired with a negative control that differs in
    exactly one respect, so a scanner that flagged (or ignored) everything
    would fail at least one of the pair;
  * `test_controls_are_not_degenerate` asserts, on the same fixture text, that
    the positive control's value and the negative control's value receive
    OPPOSITE verdicts -- a fixture where both agree cannot pass;
  * the specific defeats that beat prior scanners in this repository are each
    an explicit case: a trailing `/* ... */` comment, a comma-separated
    declarator list, a value hidden in a string body, an alternative spelling
    of the same number, and a longer number that merely starts with it.
"""
import json
import os
import shutil
import sys
import tempfile
import unittest

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
sys.path.insert(0, os.path.join(REPO, "recon", "emulator", "scripts"))
import check_app_flash_literals as C  # noqa: E402

LO, HI = C.image_window()
DATA_LO = C.APP_TEXT_END

# a real, measured-live defect (boot_cost_per_byte.md + iteration 49 section 49)
BAD = 0x00099919
# a value in the same window that is only ever COMPARED, never dereferenced --
# the class iteration 5 established with the retained-block validity magic
MAGIC = 0x000C0FFE

# the eight raw flash literals iteration 49 measured LIVE as format pointers in
# a 20 s G1_SEED=305419896 capture of both stimuli.  They must not come back.
LIVE_EIGHT = [0x993C9, 0x9943C, 0x99476, 0x994D3, 0x99919, 0x9FA78, 0x9FF38,
              0xA00D0]
REPAIRED_TREES = ["recon/named", "recon/symbolized/app",
                  "recon/readable_sources/app/g1"]


def classes(src):
    """{value: set(classes)} for one snippet of C."""
    out = {}
    for u in C.classify_uses(C.ctokenize(src), LO, HI):
        if C.in_scope(u, LO, HI, DATA_LO):
            out.setdefault(u["value"], set()).add(u["class"])
    return out


class TokenizerCannotBeTextAnchored(unittest.TestCase):
    def test_value_in_a_block_comment_is_not_a_token(self):
        self.assertNotIn(BAD, classes("int f(void){ /* 0x00099919 */ return 0; }"))

    def test_value_in_a_line_comment_is_not_a_token(self):
        self.assertNotIn(BAD, classes("int f(void){ // 0x00099919\n return 0; }"))

    def test_value_in_a_string_body_is_not_a_token(self):
        self.assertNotIn(BAD, classes('const char *s = "addr 0x00099919 here";'))

    def test_value_in_a_char_constant_is_not_a_token(self):
        self.assertNotIn(BAD, classes("char c = '\\x99'; /* 0x00099919 */"))

    def test_trailing_comment_after_the_literal_does_not_hide_it(self):
        # the exact shape that beat a prior scanner: a trailing `/* memset */`
        got = classes("void f(void){ log_message(0x00099919, 0); /* memset */ }")
        self.assertIn(BAD, got)

    def test_all_spellings_of_the_same_value_are_found(self):
        for spelling in ("0x00099919", "0x99919", "0x99919UL", "0X99919u",
                         "0x00099919ul", "629017"):
            with self.subTest(spelling=spelling):
                self.assertIn(BAD, classes("void f(void){ g(%s); }" % spelling),
                              "%s not seen" % spelling)

    def test_a_longer_number_starting_with_the_value_is_a_different_number(self):
        self.assertNotIn(BAD, classes("void f(void){ g(0x999190); }"))
        self.assertNotIn(BAD, classes("void f(void){ g(0x000999190); }"))

    def test_comma_declarator_list_does_not_hide_the_second_declarator(self):
        got = classes("int *a = (int *)0x99919, *b = (int *)0x9943c;")
        self.assertEqual(got.get(0x99919), {"pointer"})
        self.assertEqual(got.get(0x9943C), {"pointer"})

    def test_a_macro_body_is_scored(self):
        got = classes("#define FMT 0x00099919\nvoid f(void){ g(FMT); }")
        self.assertIn(BAD, got)


class UseClassification(unittest.TestCase):
    def test_call_argument_is_not_assumed_benign(self):
        self.assertEqual(classes("void f(void){ log_message(0x00099919, 0); }")[BAD],
                         {"unknown"})

    def test_pointer_cast_is_a_dereference(self):
        self.assertEqual(classes("void f(void){ p = (unsigned char *)0x00099919; }")[BAD],
                         {"pointer"})

    def test_pointer_cast_over_an_offset_expression_is_a_dereference(self):
        got = classes("void f(void){ x = *(volatile uint8_t *)(0x00099919 + i); }")
        self.assertEqual(got[BAD], {"pointer"})

    def test_comparison_is_a_magic_value(self):
        self.assertEqual(classes("void f(void){ if (x == 0x000c0ffe) g(); }")[MAGIC],
                         {"magic"})
        self.assertEqual(classes("void f(void){ if (0x000c0ffe != x) g(); }")[MAGIC],
                         {"magic"})

    def test_switch_case_label_is_a_magic_value(self):
        got = classes("void f(void){ switch (x) { case 0x000c0ffe: g(); } }")
        self.assertEqual(got[MAGIC], {"magic"})

    def test_the_same_magic_value_dereferenced_is_NOT_magic(self):
        # proves the magic verdict comes from the USE and not from the value
        got = classes("void f(void){ y = *(volatile int *)0x000c0ffe; }")
        self.assertEqual(got[MAGIC], {"pointer"})

    def test_code_window_mask_is_out_of_scope_but_code_window_deref_is_not(self):
        mask = "void f(void){ x = y & 0xfff7; }"
        deref = "void f(void){ x = *(volatile int *)0xfff7; }"
        self.assertNotIn(0xFFF7, classes(mask))
        self.assertEqual(classes(deref).get(0xFFF7), {"pointer"})

    def test_a_multiplication_is_not_mistaken_for_a_pointer_cast(self):
        got = classes("void f(void){ x = (a * b) * 0x000c0ffe; }")
        self.assertEqual(got[MAGIC], {"unknown"})


class GateVerdict(unittest.TestCase):
    """End-to-end: the process exit status, through a real tree on disk."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix="g1-flashlit-")
        self.tree = os.path.join(self.dir, "recon", "src")
        os.makedirs(self.tree)
        self.ledger = os.path.join(self.dir, "ledger.json")
        self.set_ledger({})

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def write(self, name, text):
        with open(os.path.join(self.tree, name), "w") as fh:
            fh.write(text)

    def run_gate(self):
        return C.main(["--tree", self.tree, "--ledger", self.ledger,
                       "--max-print", "0", "--quiet"])

    def set_ledger(self, entries):
        with open(self.ledger, "w") as fh:
            json.dump({"entries": entries}, fh)

    # ---- the two controls the brief requires -----------------------------
    def test_POSITIVE_control_known_bad_literal_is_caught(self):
        self.write("bad.c",
                   "void f(void){ log_message(0x00099919, 0x00099b4c); }\n")
        self.assertEqual(self.run_gate(), 1)

    def test_NEGATIVE_control_legitimate_magic_comparison_is_not_flagged(self):
        self.write("ok.c",
                   "int f(int x){ return x == 0x000c0ffe; }\n")
        self.assertEqual(self.run_gate(), 0)

    def test_controls_are_not_degenerate(self):
        """Both controls in ONE file: the gate must fail, and it must fail
        because of the bad literal and not because of the magic one."""
        self.write("both.c",
                   "int f(int x){ if (x == 0x000c0ffe) log_message(0x00099919, 0);"
                   " return 0; }\n")
        self.assertEqual(self.run_gate(), 1)
        # now ledger ONLY the bad literal -> the magic one must not fail it
        self.set_ledger({hex(BAD): {"disposition": "dead_at_seed",
                                    "reason": "control"}})
        self.assertEqual(self.run_gate(), 0)
        # and ledger ONLY the magic literal -> still fails on the bad one
        self.set_ledger({hex(MAGIC): {"disposition": "magic",
                                      "reason": "control"}})
        self.assertEqual(self.run_gate(), 1)

    # ---- fail-closed ------------------------------------------------------
    def test_unclassifiable_value_fails_closed(self):
        self.write("u.c", "unsigned long t[] = { 0x000a0000UL };\n")
        self.assertEqual(self.run_gate(), 1)

    def test_ledger_entry_without_a_reason_does_not_cover(self):
        self.write("bad.c", "void f(void){ log_message(0x00099919, 0); }\n")
        self.set_ledger({hex(BAD): {"disposition": "dead_at_seed", "reason": ""}})
        self.assertEqual(self.run_gate(), 1)

    def test_ledger_cannot_wave_through_a_dereference_without_pointer_reviewed(self):
        self.write("bad.c", "void f(void){ p = (unsigned char *)0x00099919; }\n")
        self.set_ledger({hex(BAD): {"disposition": "dead_at_seed",
                                    "reason": "not called at this seed"}})
        self.assertEqual(self.run_gate(), 1)
        self.set_ledger({hex(BAD): {"disposition": "pointer_reviewed",
                                    "reason": "reviewed: table base, tracked"}})
        self.assertEqual(self.run_gate(), 0)

    def test_a_clean_tree_passes(self):
        self.write("clean.c",
                   'void f(void){ log_message((unsigned long)"%s(): Master!'
                   '------\\n", 0); }\n')
        self.assertEqual(self.run_gate(), 0)


class RepairedTreesStayRepaired(unittest.TestCase):
    """Regression guard for the iteration-49 repair itself."""

    def test_the_eight_measured_live_literals_are_gone(self):
        for tree in REPAIRED_TREES:
            root = os.path.join(REPO, tree)
            if not os.path.isdir(root):
                self.skipTest("%s absent" % tree)
            found = {u["value"] for u in C.scan_tree(root, LO, HI)
                     if u["value"] in LIVE_EIGHT}
            self.assertEqual(found, set(),
                             "%s still names %s raw" %
                             (tree, sorted(hex(v) for v in found)))


if __name__ == "__main__":
    unittest.main()
