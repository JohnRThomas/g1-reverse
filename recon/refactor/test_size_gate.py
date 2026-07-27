"""Tests for the codegen-size class -- a first-class, checkable stage property.

WHY THIS FILE EXISTS.  Stage 04 was gated behaviourally and failed: eight
navigation fields that the in-tree build reproduces byte-exactly against the
shipped firmware broke, and the carrier was **-16 B of `.text`** re-phasing the
boot path by -100.7 ms.  That is the third independent measurement in this
project of the same effect (+60 B, +16 B, -16 B), and the third one is the
important one because it points the OTHER WAY: shrinking the image is not safe
either.

The failure was discovered at an oracle run, after a build and nine Renode
captures.  It did not have to be.  "Can this stage change linked size?" is a
property of the stage and is declarable in advance, so it now IS declared, in
the driver's stage registry, and ``driver.py size-gate`` measures whether the
declaration held.  These tests are what make that declaration binding rather
than a comment.
"""

from __future__ import annotations

import json
import os
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import driver  # noqa: E402
import stagelib  # noqa: E402


def _elf32(sections: list[tuple[str, int]], alloc: bool = True) -> bytes:
    """A minimal but genuine little-endian ELF32 with the given section sizes.

    Built by hand rather than by compiling something, so the test needs no
    toolchain and asserts against a byte layout it fully specifies.
    """
    names = [""] + [n for n, _ in sections] + [".shstrtab"]
    strtab = b"".join(n.encode() + b"\0" for n in names)
    offs, cur = {}, 0
    for n in names:
        offs[n] = cur
        cur += len(n) + 1

    shnum = len(sections) + 2                 # null + sections + .shstrtab
    ehsize, shentsize = 52, 40
    strtab_off = ehsize
    shoff = strtab_off + len(strtab)

    eh = bytearray(ehsize)
    eh[0:4] = b"\x7fELF"
    eh[4] = 1                                  # ELFCLASS32
    eh[5] = 1                                  # ELFDATA2LSB
    eh[6] = 1
    struct.pack_into("<HHI", eh, 16, 2, 40, 1)          # e_type, e_machine, e_version
    struct.pack_into("<III", eh, 24, 0, 0, shoff)       # entry, phoff, shoff
    struct.pack_into("<IHHHHHH", eh, 36, 0, ehsize, 0, 0, shentsize, shnum,
                     shnum - 1)

    def sh(name, size, off=0, flags=0):
        b = bytearray(shentsize)
        struct.pack_into("<IIIIII", b, 0, offs[name], 1, flags, 0, off, size)
        return bytes(b)

    hdrs = [sh("", 0)]
    hdrs += [sh(n, s, flags=stagelib.SHF_ALLOC if alloc else 0)
             for n, s in sections]
    hdrs.append(sh(".shstrtab", len(strtab), strtab_off))
    return bytes(eh) + strtab + b"".join(hdrs)


class ElfSectionSizes(unittest.TestCase):
    def test_reads_sizes_without_a_toolchain(self):
        blob = _elf32([(".text", 492576), (".rodata", 456536), (".bss", 189230)])
        with tempfile.TemporaryDirectory() as td:
            p = os.path.join(td, "a.elf")
            with open(p, "wb") as fh:
                fh.write(blob)
            got = stagelib.elf_section_sizes(p)
        self.assertEqual(got[".text"], 492576)
        self.assertEqual(got[".rodata"], 456536)
        self.assertEqual(got[".bss"], 189230)

    def test_rejects_a_non_elf(self):
        with tempfile.TemporaryDirectory() as td:
            p = os.path.join(td, "a.elf")
            with open(p, "wb") as fh:
                fh.write(b"not an elf at all")
            with self.assertRaises(ValueError):
                stagelib.elf_section_sizes(p)

    def test_matches_the_toolchain_on_a_real_elf_when_one_exists(self):
        """If a real build is lying around, cross-check against `size -A`."""
        import glob
        import subprocess
        cands = sorted(glob.glob("/private/tmp/g1-*/zephyr/zephyr.elf"))
        sz = os.path.expanduser(
            "~/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-size")
        if not cands or not os.path.exists(sz):
            self.skipTest("no built ELF and/or no toolchain available")
        elf = cands[0]
        mine = stagelib.elf_section_sizes(elf)
        out = subprocess.run([sz, "-A", elf], capture_output=True, text=True).stdout
        checked = 0
        for line in out.splitlines():
            parts = line.split()
            if len(parts) >= 2 and parts[0].startswith("."):
                try:
                    theirs = int(parts[1])
                except ValueError:
                    continue
                if parts[0] in mine:
                    self.assertEqual(mine[parts[0]], theirs, parts[0])
                    checked += 1
        self.assertGreater(checked, 3)


class Classification(unittest.TestCase):
    BASE = {".text": 1000, ".rodata": 500, ".data": 10, ".bss": 20, ".noinit": 30}

    def test_identical_image_is_byte_identical(self):
        self.assertEqual(
            stagelib.classify_codegen(self.BASE, dict(self.BASE), True),
            "byte-identical")

    def test_same_sizes_different_image_is_size_neutral(self):
        self.assertEqual(
            stagelib.classify_codegen(self.BASE, dict(self.BASE), False),
            "size-neutral")

    def test_a_sixteen_byte_shrink_is_size_changing(self):
        """The exact shape that broke Stage 04: -16 B, in the SHRINK direction."""
        stage = dict(self.BASE, **{".text": self.BASE[".text"] - 16})
        self.assertEqual(stagelib.classify_codegen(self.BASE, stage, False),
                         "size-changing")

    def test_bss_alone_is_enough(self):
        stage = dict(self.BASE, **{".bss": self.BASE[".bss"] + 4})
        self.assertEqual(stagelib.classify_codegen(self.BASE, stage, False),
                         "size-changing")

    def test_non_alloc_sections_never_reach_the_classifier(self):
        """`.debug_*`, `.symtab` and `.comment` carry no SHF_ALLOC, so
        `elf_section_sizes(alloc_only=True)` drops them before classification.
        `uname.c.obj`'s embedded build clock must not fail a size gate."""
        blob = _elf32([("text", 100)], alloc=True)
        with tempfile.TemporaryDirectory() as td:
            p = os.path.join(td, "a.elf")
            with open(p, "wb") as fh:
                fh.write(blob)
            self.assertEqual(sorted(stagelib.elf_section_sizes(p, alloc_only=True)),
                             ["text"])
            raw = stagelib.elf_section_sizes(p)
        self.assertIn(".shstrtab", raw)

    def test_zephyr_names_its_sections_without_a_leading_dot(self):
        """The bug this gate shipped with, pinned as a test.

        The G1 Zephyr link emits `text`/`rodata`/`datas`/`bss`/`noinit` with NO
        leading dot, plus 20 more allocatable areas.  A gate keyed on a
        `(".text", ...)` name list reported every delta as +0 and passed a
        stage whose `.text` had moved by 80 bytes.  Keying on SHF_ALLOC and
        canonicalising the dot is what makes that unrepresentable.
        """
        blob = _elf32([("text", 492688), ("rodata", 456536), ("datas", 3327),
                       ("bss", 189230), ("noinit", 60021), ("k_sem_area", 96)])
        with tempfile.TemporaryDirectory() as td:
            p = os.path.join(td, "a.elf")
            with open(p, "wb") as fh:
                fh.write(blob)
            got = stagelib.elf_section_sizes(p, alloc_only=True)
        self.assertEqual(got["text"], 492688)
        self.assertEqual(got["datas"], 3327)
        self.assertEqual(got["k_sem_area"], 96)
        moved = dict(got, text=got["text"] - 80)
        self.assertEqual(stagelib.classify_codegen(got, moved, False),
                         "size-changing")

    def test_deltas_are_signed(self):
        stage = dict(self.BASE, **{".text": 984})
        d = stagelib.size_deltas(self.BASE, stage)
        self.assertEqual(d[".text"], -16)

    def test_a_section_that_appears_or_vanishes_is_a_change(self):
        stage = dict(self.BASE)
        stage["k_sem_area"] = 96
        self.assertEqual(stagelib.classify_codegen(self.BASE, stage, False),
                         "size-changing")


class Verdict(unittest.TestCase):
    def _gate(self, declared, base_sections, stage_sections, same_bin):
        with tempfile.TemporaryDirectory() as td:
            be = os.path.join(td, "b.elf")
            se = os.path.join(td, "s.elf")
            bb = os.path.join(td, "b.bin")
            sb = os.path.join(td, "s.bin")
            with open(be, "wb") as fh:
                fh.write(_elf32(list(base_sections.items())))
            with open(se, "wb") as fh:
                fh.write(_elf32(list(stage_sections.items())))
            with open(bb, "wb") as fh:
                fh.write(b"IMAGE")
            with open(sb, "wb") as fh:
                fh.write(b"IMAGE" if same_bin else b"OTHER")
            return stagelib.size_gate(declared, be, se, bb, sb)

    B = {"text": 1000, "rodata": 500}

    def test_a_byte_identical_claim_FAILS_when_text_moves(self):
        r = self._gate("byte-identical", self.B, {"text": 984, "rodata": 500},
                       False)
        self.assertFalse(r["pass"])
        self.assertEqual(r["measured_codegen_class"], "size-changing")
        self.assertEqual(r["section_deltas"]["text"], -16)

    def test_a_byte_identical_claim_FAILS_on_a_size_neutral_result(self):
        r = self._gate("byte-identical", self.B, dict(self.B), False)
        self.assertFalse(r["pass"])
        self.assertEqual(r["measured_codegen_class"], "size-neutral")

    def test_a_size_changing_claim_passes_when_it_comes_out_better(self):
        r = self._gate("size-changing", self.B, dict(self.B), True)
        self.assertTrue(r["pass"])
        self.assertEqual(r["measured_codegen_class"], "byte-identical")
        self.assertFalse(r["oracle_required"])

    def test_size_changing_measured_demands_the_oracle(self):
        r = self._gate("size-changing", self.B, {"text": 984, "rodata": 500},
                       False)
        self.assertTrue(r["pass"])
        self.assertTrue(r["oracle_required"])
        self.assertIn("-16 B", r["why_oracle_required"])

    def test_an_unknown_declared_class_is_refused(self):
        with self.assertRaises(ValueError):
            stagelib.size_gate("probably-fine", "/nonexistent", "/nonexistent")


class Registry(unittest.TestCase):
    def test_every_stage_declares_a_valid_class(self):
        self.assertTrue(driver.STAGES)
        for row in driver.STAGES:
            self.assertEqual(len(row), 5, row[1])
            self.assertIn(row[4], stagelib.CODEGEN_CLASSES, row[1])

    def test_the_merge_stage_may_not_claim_byte_identity(self):
        """Stage 04 concatenates translation units.

        That changes archive-member granularity and cross-TU inlining by
        construction (stage report §3.2 measured `__ieee754_pow` and `nan`
        moving 29 KiB), so no future edit may quietly relabel it as gateable on
        `cmp zephyr.bin`.
        """
        cls = {row[0]: row[4] for row in driver.STAGES}
        self.assertEqual(cls[4], "size-changing")

    def test_status_reports_the_declared_class(self):
        for row in driver.status():
            self.assertIn("declared_codegen_class", row)

    def test_a_materialised_manifest_records_the_class_and_the_obligation(self):
        """Every CURRENT stage's manifest carries its declared class.

        A stage whose manifest predates the property is allowed to lack it on
        exactly one condition: that `status` reports it **stale**, so the gap is
        visible and the documented repair (regenerate) applies.  Silently
        exempting a stage would be the same mistake the size gate itself made
        when it keyed on a section-name list.
        """
        state = {row["stage"]: row["state"] for row in driver.status()}
        checked, exempt = 0, []
        for row in driver.STAGES:
            man = stagelib.load_manifest(row[0], row[1])
            if man is None:
                continue
            if man.get("declared_codegen_class") is None:
                self.assertEqual(state.get(row[0]), "stale", row[1])
                exempt.append(row[1])
                continue
            checked += 1
            self.assertEqual(man.get("declared_codegen_class"), row[4], row[1])
            self.assertEqual(man.get("oracle_required"),
                             row[4] == "size-changing", row[1])
        self.assertGreater(checked, 0)
        # the only stage expected here is the retired diagnostic probe
        self.assertTrue(set(exempt) <= {"defect_probe"}, exempt)

    def test_the_size_gate_writes_into_the_stage_directory_only(self):
        """The gate's own output is subject to the same write guard (R1)."""
        import guard
        st = stagelib.Stage(4, "cohesive_tu", "")
        guard.check_write(os.path.join(st.dir, "SIZE_GATE.json"), st.dir)
        with self.assertRaises(guard.WriteGuardError):
            guard.check_write(
                os.path.join(guard.REPO_ROOT, "recon", "app", "src",
                             "SIZE_GATE.json"), st.dir)


class SdkEvidence(unittest.TestCase):
    """The SDK declared-symbol evidence, and the refusal it powers.

    Stage 03 published `extern void k_sem_give(int);` into a module header that
    `unsorted/imu_fusion_init.c` includes -- a file whose line 1 is
    `#include <zephyr/kernel.h>`.  The build stopped with `conflicting types`.
    The evidence file is what makes that unrepresentable.
    """

    def test_the_evidence_file_exists_and_covers_the_three_measured_failures(self):
        import sdk_symbols
        syms = sdk_symbols.load()
        if not syms:
            self.skipTest("sdk_declared_symbols.json has not been generated")
        for s in ("k_sem_give", "k_sleep", "strlen"):
            self.assertIn(s, syms)

    def test_absent_evidence_degrades_to_the_previous_behaviour(self):
        import sdk_symbols
        saved = sdk_symbols._cache
        try:
            sdk_symbols._cache = None
            real = sdk_symbols.DATA
            sdk_symbols.DATA = "/nonexistent/sdk_declared_symbols.json"
            try:
                self.assertEqual(sdk_symbols.load(), set())
            finally:
                sdk_symbols.DATA = real
        finally:
            sdk_symbols._cache = saved

    def test_stage_03_records_whether_it_had_the_evidence(self):
        man = stagelib.load_manifest(3, "module_structure")
        if man is None:
            self.skipTest("stage 03 not materialised")
        b = man["sub_batches"]["B_module_headers"]
        self.assertIn("sdk_evidence_present", b)
        self.assertIn("symbols_refused_shadowing_an_sdk_symbol", b)

    def test_no_generated_module_header_declares_an_sdk_symbol(self):
        """The property, asserted against the materialised tree itself."""
        import re
        import sdk_symbols
        syms = sdk_symbols.load()
        st = stagelib.Stage(3, "module_structure", "")
        root = os.path.join(st.tree, "recon", "symbolized", "app")
        if not syms or not os.path.isdir(root):
            self.skipTest("no evidence and/or stage 03 not materialised")
        decl = re.compile(r'^\s*extern\b[^;]*?\b([A-Za-z_]\w*)\s*\(', re.M)
        offenders = []
        for dp, _dirs, names in os.walk(root):
            for n in names:
                if not (n.startswith("g1_") and n.endswith(".h")):
                    continue
                with open(os.path.join(dp, n), encoding="utf-8",
                          errors="surrogateescape") as fh:
                    for m in decl.finditer(fh.read()):
                        if m.group(1) in syms:
                            offenders.append("%s: %s" % (n, m.group(1)))
        self.assertEqual(offenders, [])


if __name__ == "__main__":
    unittest.main()
