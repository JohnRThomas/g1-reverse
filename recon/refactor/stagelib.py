"""Stage materialisation, MANIFEST/PARITY_MAP emission and staleness.

Contract (see README.md):

  stage_00  = verbatim snapshot of the compilable input set
  stage_N   = transformer_N(stage_N-1)          for N >= 1

A stage directory is:

  recon/refactor/stage_NN_<slug>/
    MANIFEST.json      per file: source path, source SHA-256, output SHA-256,
                       transformations applied with site counts
    PARITY_MAP.json    original address <-> canonical name <-> stage file path
                       <-> symbol name   (traceability + integrity, R7)
    tree/              a BUILDABLE root: the transformed files are real files,
                       everything else the build needs is a relative symlink
                       back into the repository

Staleness: a stage is stale iff any input's content hash differs from the hash
recorded in its MANIFEST.  The repair is ALWAYS ``driver.py materialize`` -- a
stage tree is never hand-patched, because reproducibility is what lets a stage
be regenerated when the concurrent parity agent lands a defect fix upstream.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from guard import REPO_ROOT, WriteGuardError, check_write, is_protected  # noqa: E402

REFACTOR_DIR = os.path.join(REPO_ROOT, "recon", "refactor")

_IDENTITY = re.compile(
    r"identity:\s*(?P<raw>[A-Za-z_][A-Za-z_0-9]*)\s*@\s*(?P<va>0x[0-9a-fA-F]+)"
)
_PUBLIC = re.compile(r"^\s*\*\s*public-name:\s*(?P<name>\S+)\s*$", re.M)


def sha256_file(path: str) -> str:
    h = hashlib.sha256()
    with open(path, "rb") as fh:
        for chunk in iter(lambda: fh.read(1 << 16), b""):
            h.update(chunk)
    return h.hexdigest()


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def stage_dir(number: int, slug: str) -> str:
    return os.path.join(REFACTOR_DIR, "stage_%02d_%s" % (number, slug))


def _relsym(target_abs: str, link_abs: str) -> str:
    return os.path.relpath(target_abs, os.path.dirname(link_abs))


class Stage:
    """One materialised stage."""

    def __init__(self, number: int, slug: str, description: str):
        self.number = number
        self.slug = slug
        self.description = description
        self.dir = stage_dir(number, slug)
        self.tree = os.path.join(self.dir, "tree")
        self.files: dict[str, dict] = {}

    # -- writing -------------------------------------------------------
    def emit(self, relpath: str, data: bytes, source_abs: str,
             source_sha: str, transforms: dict,
             extra_sources: list[tuple[str, str]] | None = None) -> None:
        """Write one materialised file into the stage tree.

        ``extra_sources`` is a list of ``(absolute path, sha256)`` for the
        FURTHER inputs an output was derived from.  Stage 04 merges N sources
        into one translation unit; without this, staleness would watch only the
        first member and an upstream defect fix landing inside member 7 would
        never mark the stage stale -- the single most dangerous failure mode a
        staleness mechanism can have, because it reports "current" while it is
        not.
        """
        out = os.path.join(self.tree, relpath)
        check_write(out, self.dir)
        os.makedirs(os.path.dirname(out), exist_ok=True)
        if os.path.islink(out):
            os.unlink(out)
        with open(out, "wb") as fh:
            fh.write(data)
        rec = {
            "source": os.path.relpath(source_abs, REPO_ROOT).replace(os.sep, "/"),
            "source_sha256": source_sha,
            "output_sha256": sha256_bytes(data),
            "bytes": len(data),
            "transformations": transforms,
        }
        if extra_sources:
            rec["additional_sources"] = {
                os.path.relpath(p, REPO_ROOT).replace(os.sep, "/"): s
                for p, s in extra_sources}
        self.files[relpath] = rec

    # -- manifests -----------------------------------------------------
    def write_manifest(self, extra: dict) -> str:
        doc = {
            "schema": "g1.refactor.stage-manifest/1",
            "stage": self.number,
            "slug": self.slug,
            "description": self.description,
            "input_stage": extra.pop("input_stage", None),
            "generated_by": "recon/refactor/driver.py",
            "reproduce": "PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize %d"
                         % self.number,
            "repair_policy": "A stale or failing stage is REGENERATED, never hand-edited. "
                             "A compile failure in a stage tree is proof the transformer is "
                             "wrong, not a task to hand-fix.",
            "file_count": len(self.files),
            "files": self.files,
        }
        doc.update(extra)
        path = os.path.join(self.dir, "MANIFEST.json")
        check_write(path, self.dir)
        with open(path, "w", encoding="utf-8") as fh:
            json.dump(doc, fh, indent=1, sort_keys=False)
            fh.write("\n")
        return path

    def write_parity_map(self, rows: list[dict], extra: dict | None = None) -> str:
        doc = {
            "schema": "g1.refactor.parity-map/1",
            "stage": self.number,
            "slug": self.slug,
            "purpose": "Traceability and an integrity check, NOT the thing being proven. "
                       "The acceptance bar is observable side-effect equivalence with the "
                       "SHIPPED binaries (R7); this map exists so that when equivalence "
                       "fails, an original address can be walked to the stage file that "
                       "now carries it.",
            "row_count": len(rows),
            "rows": rows,
        }
        if extra:
            doc.update(extra)
        path = os.path.join(self.dir, "PARITY_MAP.json")
        check_write(path, self.dir)
        with open(path, "w", encoding="utf-8") as fh:
            json.dump(doc, fh, indent=1)
            fh.write("\n")
        return path


def parity_rows(tree_root: str, relpaths: list[str]) -> list[dict]:
    """Extract (original address, canonical raw name, stage path, symbol) rows.

    EVERY ``identity:`` banner in the file yields a row, not just the first one
    in the first 4 KiB.  Stage 04 merges many one-function files into one
    cohesive translation unit, so a stage file legitimately carries dozens of
    identities; the earlier "first banner in the first 4096 bytes" rule would
    have reported 1,340 functions as vanished and made ``check-addresses``
    meaningless exactly where it is most needed.

    This widening is a **strict no-op for stages 00-03**, and that is measured
    rather than assumed: over stage 03's 2,629 manifest entries, 2,567 files
    carry an identity banner, **2,567** banners in total, **0** files carry more
    than one, and **0** banners sit beyond byte 4096.  Both rules therefore
    yield the same 2,567 addresses on those stages.
    """
    rows = []
    for rp in relpaths:
        ap = os.path.join(tree_root, rp)
        if not ap.endswith((".c", ".inc")) or not os.path.exists(ap):
            continue
        with open(ap, encoding="utf-8", errors="replace") as fh:
            body = fh.read()
        hits = list(_IDENTITY.finditer(body))
        for i, m in enumerate(hits):
            # the public-name line belongs to the banner it FOLLOWS, so the
            # search window ends at the next identity banner.
            end = hits[i + 1].start() if i + 1 < len(hits) else len(body)
            pm = _PUBLIC.search(body, m.end(), end)
            rows.append({
                "address": m.group("va").lower(),
                "canonical_name": m.group("raw"),
                "symbol": pm.group("name") if pm else m.group("raw"),
                "stage_path": rp,
            })
    rows.sort(key=lambda r: (r["address"], r["stage_path"]))
    return rows


def load_manifest(number: int, slug: str) -> dict | None:
    p = os.path.join(stage_dir(number, slug), "MANIFEST.json")
    if not os.path.exists(p):
        return None
    with open(p, encoding="utf-8") as fh:
        return json.load(fh)


#: Files a TRANSFORMER reads that are not part of the transformed input set.
#:
#: ``recon/refactor/sdk_declared_symbols.json`` and
#: ``link_referenced_symbols.json`` are evidence a transformer consults to
#: decide what it may do.  They live inside the pipeline, so ``input_set``
#: never lists them, so before this list ``driver.py status`` reported a stage
#: as **current** after its evidence had been regenerated underneath it -- the
#: single failure mode a staleness mechanism must not have, and the one this
#: pipeline has already been bitten by from the other direction (README: "a
#: staleness mechanism that watched only the first member would report
#: 'current' while an upstream defect fix sat unnoticed inside member 7").
#:
#: Measured when it was added: regenerating the SDK evidence changed stage 03's
#: harvest (218 -> 215 hoists, 267 -> 300 refusals) while ``status`` went on
#: reporting stages 03, 04 and 05 as current.
EVIDENCE_INPUTS = (
    "recon/refactor/sdk_declared_symbols.json",
    "recon/refactor/link_referenced_symbols.json",
)


def evidence_hashes() -> dict[str, str]:
    out: dict[str, str] = {}
    for rel in EVIDENCE_INPUTS:
        p = os.path.join(REPO_ROOT, rel)
        out[rel] = sha256_file(p) if os.path.exists(p) else "(absent)"
    return out


#: EVIDENCE WHOSE VALIDITY IS A PROPERTY OF A TREE, NOT OF ITS OWN BYTES.
#:
#: ``link_referenced_symbols.json`` answers "which symbols does something
#: outside their own OBJECT reference?".  That answer is only meaningful
#: relative to a particular partition of sources into objects.  Stage 04's
#: merge partition moved on 2026-07-27 while the evidence file's bytes did not,
#: `display_close_screen.c` stopped being a member of `g1_display_12.c` and
#: became its own translation unit, its call to `display_close` turned from an
#: intra-object reference (invisible to ``nm``) into a relocation, stage 07
#: read the frozen evidence, made `display_close` ``static``, and the app link
#: failed from stage 07 upward -- while ``driver.py status`` reported stages
#: 07, 08 and 09 **current** throughout.
#:
#: THE HASH WAS NOT THE THING TO WATCH.  This is the FOURTH staleness hole in
#: this pipeline and every one of them has the same shape: something was
#: watched that is *correlated* with the input rather than *being* the input
#: (the first member of a merged unit rather than all members; an input set
#: that did not list the evidence at all; an evidence hash rather than the
#: partition the evidence describes).  The rule that follows from all four:
#: **watch the thing the consumer's correctness actually depends on.**
PARTITION_DEPENDENT_EVIDENCE = ("recon/refactor/link_referenced_symbols.json",)

#: THE FIFTH HOLE, same family, found while closing the fourth.
#:
#: A stage is ``transformer(input)``.  Staleness watched the INPUT and the
#: EVIDENCE and never the TRANSFORMER, so editing a transformer left every
#: downstream stage reporting ``current`` while its tree was the output of code
#: that no longer exists.  Measured in this pass: the comma-declarator repair
#: was applied to ``t04_cohesive_tu.py`` and ``driver.py status`` went on
#: reporting stages 04-09 ``current``, with stage 04's tree still carrying the
#: 742-unit partition the unpatched rule produced.  Nothing but an agent
#: remembering to regenerate stood between that and a gate measured against a
#: tree no transformer would now produce.
#:
#: The digest is over the WHOLE ``transforms/`` directory rather than the
#: modules a given stage imports.  Deliberately:
#:
#:   * it is deterministic and invocation-order independent -- deriving it from
#:     ``sys.modules`` after the import would make stage 04's record depend on
#:     whether stage 09 had been materialised first in the same process, which
#:     would break MANIFEST idempotence;
#:   * transformers import each other heavily (t05-t09 all use ``t04.conflicts``
#:     and ``t03._decl_symbol``), so the true dependency closure is nearly the
#:     whole directory anyway;
#:   * it OVER-refuses, which is the safe direction: the cost of a spurious
#:     stale is one regeneration of a pipeline this pass proves byte-idempotent.
#:
#: WHAT IT STILL DOES NOT COVER, stated rather than implied: ``stagelib.py``,
#: ``driver.py``, ``input_set.py`` and the evidence generators are not in the
#: digest.  A change to those can still move a stage's output without marking
#: it stale.  That is a smaller hole than the one this closes, not no hole.
TRANSFORMS_DIR = os.path.join(REFACTOR_DIR, "transforms")


def transforms_digest() -> str:
    """One hash over every transformer source file."""
    h = hashlib.sha256()
    if not os.path.isdir(TRANSFORMS_DIR):
        return "(absent)"
    for name in sorted(os.listdir(TRANSFORMS_DIR)):
        if not name.endswith(".py"):
            continue
        h.update(name.encode())
        h.update(sha256_file(os.path.join(TRANSFORMS_DIR, name)).encode())
    return h.hexdigest()


def evidence_partition_state(tree_root: str) -> dict:
    """Does the recorded link evidence still describe ``tree_root``'s partition?

    Delegates to ``link_evidence.partition_state``, which compares the
    evidence's own recorded ``app_objects`` against the tree's generated
    retained-source list.  Both are text files inside the repository, so this
    costs a read and runs on every ``status`` -- deliberately, because a check
    that needs a cross-compiler and a surviving ``/private/tmp`` build is a
    check that does not run.
    """
    import link_evidence                       # local: avoids an import cycle
    return link_evidence.partition_state(tree_root)


def staleness(number: int, slug: str) -> dict:
    """A stage is stale iff an input content hash changed, **or** the evidence
    it consumed no longer describes its input tree's object partition.

    The second clause is not a refinement of the first: the evidence file's
    hash can be unchanged while the answer it encodes has become wrong.  See
    ``PARTITION_DEPENDENT_EVIDENCE``.
    """
    man = load_manifest(number, slug)
    if man is None:
        return {"stage": number, "state": "absent"}
    changed, missing, ok = [], [], 0
    recorded = man.get("evidence_inputs")
    if recorded is not None:
        now = evidence_hashes()
        for rel, sha in sorted(recorded.items()):
            if now.get(rel) != sha:
                changed.append(rel)
            else:
                ok += 1

    #: the transformer that produced this tree (see TRANSFORMS_DIR above).
    #: Absent from a manifest written before the digest existed, and absence
    #: must not fabricate a stale: the tree may be perfectly current.  It is
    #: reported instead, so it is visible rather than silent.
    tdigest = man.get("transforms_digest")
    if tdigest is not None and tdigest != transforms_digest():
        changed.append("recon/refactor/transforms/ (TRANSFORMER CHANGED)")

    #: only stages that CONSUME partition-dependent evidence record this key,
    #: so a stage that never reads the evidence is never made stale by it.
    partition = None
    if man.get("evidence_partition") is not None:
        ist = man.get("input_stage") or {}
        rel_tree = ist.get("tree")
        if not rel_tree:
            partition = {"state": "unverifiable",
                         "reason": "manifest records no input tree"}
        else:
            partition = evidence_partition_state(
                os.path.join(REPO_ROOT, rel_tree))
        if partition["state"] not in ("agrees", "no_evidence"):
            changed.append(
                "recon/refactor/link_referenced_symbols.json"
                " (PARTITION: %s)" % partition["state"])
    for rel, rec in man["files"].items():
        watched = [(rec["source"], rec["source_sha256"])]
        watched += sorted(rec.get("additional_sources", {}).items())
        for relsrc, sha in watched:
            src = os.path.join(REPO_ROOT, relsrc)
            if not os.path.exists(src):
                missing.append(relsrc)
                continue
            if sha256_file(src) != sha:
                changed.append(relsrc)
            else:
                ok += 1
    out = {
        "stage": number,
        "slug": slug,
        "state": "stale" if (changed or missing) else "current",
        "inputs_unchanged": ok,
        "inputs_changed": sorted(changed),
        "inputs_missing": sorted(missing),
        "repair": "PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize %d"
                  % number,
    }
    if tdigest is None:
        out["transforms_digest"] = "NOT RECORDED -- regenerate to start watching"
    if partition is not None:
        out["evidence_partition"] = partition
        if partition["state"] not in ("agrees", "no_evidence"):
            # REGENERATING THE STAGE WOULD NOT FIX THIS.  The stage would read
            # the same stale evidence and make the same wrong decision.  The
            # repair is upstream of the stage, so it is stated upstream of the
            # stage's own repair line.
            out["repair"] = (
                "The link evidence no longer describes this stage's input "
                "tree.  Regenerating the stage would reproduce the same wrong "
                "decisions.  Rebuild the input tree, regenerate the evidence, "
                "THEN materialize:\n"
                "  ./%s/recon/application/build_cohesive.sh app <BUILD>\n"
                "  PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/"
                "link_evidence.py generate --build <BUILD>\n"
                "  PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py "
                "materialize %d" % ((man.get("input_stage") or {}).get("tree",
                                                                       "<input tree>"),
                                    number))
    return out


# ------------------------------------------------------- codegen size class
#
# A FIRST-CLASS, CHECKABLE STAGE PROPERTY -- added after the Stage 04 R7 gate.
#
# Three independent measurements in this project now say the same thing:
#
#   * +60 B of `.text` reordered two firmware threads on the shared I2C bus and
#     broke `twim2 p1_boot` byte-equality (type_disagreement_repair.md, pass 1b);
#   * +16 B collapsed the dashboard (iteration 42);
#   * **-16 B** moved the OPT3001 poll train's phase by -100.7 ms and gained it
#     one extra poll inside the 6 s wall, breaking eight navigation fields the
#     in-tree build reproduces byte-exactly (stage04_r7_validation.md §3.5).
#
# The third is the decisive one because it points the other way: the damage is
# not "bigger image, slower boot".  **Any transformation that changes linked
# size can break observable side-effect equivalence, in either direction.**
#
# That was discovered at the gate, after a build and nine Renode captures.  It
# should not have been: whether a stage can change linked size is a property of
# the stage, declarable in advance and checkable mechanically.  So every stage
# now DECLARES a codegen class, the driver records it in the MANIFEST, and
# ``driver.py size-gate`` measures the class actually achieved and refuses a
# stage that came out worse than it declared.
#
#: ordered weakest-claim-last.  A stage may come out BETTER than it declared
#: (that is information); it may never come out worse (that is a broken claim).
CODEGEN_CLASSES = ("byte-identical", "size-neutral", "size-changing")
CODEGEN_RANK = {c: i for i, c in enumerate(CODEGEN_CLASSES)}

#: What decides ``size-neutral`` is **every section carrying SHF_ALLOC**, not a
#: list of section names.
#:
#: The first version of this gate compared ``(".text", ".rodata", ".data",
#: ".bss", ".noinit")`` and reported the Stage 04 image as ``size-neutral`` with
#: every delta ``+0`` -- because the G1 Zephyr link names those sections
#: **without a leading dot**: ``text`` 492,688, ``rodata`` 456,536, ``datas``
#: 3,327, ``bss`` 189,230, ``noinit`` 60,021, plus 20 more allocatable areas
#: (``device_area``, ``k_sem_area``, ``log_const_area``, ...).  A gate keyed on
#: a name list is a gate that silently passes, which is worse than no gate.  The
#: ALLOC flag is in the section header and cannot go stale.
SHF_ALLOC = 0x2

#: reported first in the delta table when present, purely for readability.
PREFERRED_SECTION_ORDER = ("text", "rodata", "data", "datas", "bss", "noinit")


def _canon_section(name: str) -> str:
    return name[1:] if name.startswith(".") else name


def elf_section_sizes(path: str, alloc_only: bool = False) -> dict[str, int]:
    """Section name -> size, parsed from the ELF section header table.

    Parsed here rather than shelled out to ``arm-zephyr-eabi-size`` so the gate
    and its tests need no toolchain: a size gate that only runs where a
    cross-compiler is installed is a gate that does not run.

    ``alloc_only`` keeps just the sections whose header carries ``SHF_ALLOC``
    -- the ones that occupy the device's flash or RAM and can therefore move a
    bus transaction -- and canonicalises the name by dropping a leading dot, so
    ``.text`` and Zephyr's ``text`` are the same key.
    """
    import struct as _struct                      # local: a repo-root struct.py
    with open(path, "rb") as fh:                  # shadows the stdlib module,
        data = fh.read()                          # hence PYTHONSAFEPATH=1
    if data[:4] != b"\x7fELF":
        raise ValueError("not an ELF file: %s" % path)
    is64 = data[4] == 2
    end = "<" if data[5] == 1 else ">"
    if is64:
        shoff, = _struct.unpack_from(end + "Q", data, 0x28)
        shentsize, shnum, shstrndx = _struct.unpack_from(end + "HHH", data, 0x3A)
        name_off, flag_off, size_off = 0x00, 0x08, 0x20
        szfmt = end + "Q"
        flagfmt = end + "Q"
    else:
        shoff, = _struct.unpack_from(end + "I", data, 0x20)
        shentsize, shnum, shstrndx = _struct.unpack_from(end + "HHH", data, 0x2E)
        name_off, flag_off, size_off = 0x00, 0x08, 0x14
        szfmt = end + "I"
        flagfmt = end + "I"

    def hdr(i):
        return shoff + i * shentsize

    strtab_off, = _struct.unpack_from(end + ("Q" if is64 else "I"),
                                      data, hdr(shstrndx) + (0x18 if is64 else 0x10))
    strtab_sz, = _struct.unpack_from(szfmt, data, hdr(shstrndx) + size_off)
    strtab = data[strtab_off:strtab_off + strtab_sz]

    out: dict[str, int] = {}
    for i in range(shnum):
        base = hdr(i)
        nm_idx, = _struct.unpack_from(end + "I", data, base + name_off)
        flags, = _struct.unpack_from(flagfmt, data, base + flag_off)
        sz, = _struct.unpack_from(szfmt, data, base + size_off)
        j = strtab.find(b"\0", nm_idx)
        name = strtab[nm_idx:j if j >= 0 else None].decode("utf-8", "replace")
        if not name:
            continue
        if alloc_only:
            if not (flags & SHF_ALLOC):
                continue
            name = _canon_section(name)
        out[name] = out.get(name, 0) + sz
    return out


def classify_codegen(base_sizes: dict[str, int], stage_sizes: dict[str, int],
                     image_identical: bool) -> str:
    """The codegen class a stage ACTUALLY achieved.

    ``base_sizes``/``stage_sizes`` are ALLOC-only section maps.  A section that
    exists on one side and not the other counts as a change: appearing or
    vanishing is exactly as observable as growing.
    """
    if image_identical:
        return "byte-identical"
    for s in set(base_sizes) | set(stage_sizes):
        if base_sizes.get(s, 0) != stage_sizes.get(s, 0):
            return "size-changing"
    return "size-neutral"


def size_deltas(base_sizes: dict[str, int], stage_sizes: dict[str, int]
                ) -> dict[str, int]:
    """Signed per-section deltas.  Unchanged sections are omitted; the
    preferred sections are always reported so the table reads the same way
    every time."""
    keys = set(base_sizes) | set(stage_sizes)
    out = {s: stage_sizes.get(s, 0) - base_sizes.get(s, 0) for s in keys}
    ordered = [s for s in PREFERRED_SECTION_ORDER if s in out]
    ordered += sorted(s for s in out
                      if s not in PREFERRED_SECTION_ORDER and out[s])
    return {s: out[s] for s in ordered}


def size_gate(declared: str, base_elf: str, stage_elf: str,
              base_bin: str | None = None, stage_bin: str | None = None) -> dict:
    """Measure the achieved codegen class and judge it against the declared one.

    The verdict is deliberately asymmetric.  Coming out BETTER than declared
    passes and is reported (a stage that declared ``size-changing`` and turned
    out byte-identical needs no oracle run).  Coming out WORSE fails: the stage
    made a claim about observability that its own image refutes.
    """
    if declared not in CODEGEN_RANK:
        raise ValueError("unknown codegen class %r" % declared)
    bs = elf_section_sizes(base_elf, alloc_only=True)
    ss = elf_section_sizes(stage_elf, alloc_only=True)
    identical = False
    if base_bin and stage_bin and os.path.exists(base_bin) and os.path.exists(stage_bin):
        with open(base_bin, "rb") as a, open(stage_bin, "rb") as b:
            identical = a.read() == b.read()
    measured = classify_codegen(bs, ss, identical)
    ok = CODEGEN_RANK[measured] <= CODEGEN_RANK[declared]
    return {
        "schema": "g1.refactor.size-gate/1",
        "declared_codegen_class": declared,
        "measured_codegen_class": measured,
        "pass": ok,
        "image_byte_identical": identical,
        "section_deltas": size_deltas(bs, ss),
        "alloc_section_count": [len(bs), len(ss)],
        "base_sections": dict(sorted(bs.items())),
        "stage_sections": dict(sorted(ss.items())),
        "oracle_required": measured == "size-changing",
        "why_oracle_required":
            "Linked size moved.  Three independent measurements in this project "
            "(+60 B, +16 B, -16 B) show a size change of this order re-phases the "
            "boot path and can break byte-equality of a peripheral bus stream in "
            "EITHER direction.  R7 acceptance cannot be inferred; it must be "
            "captured." if measured == "size-changing" else
            "Linked size did not move; every previously captured behavioural "
            "measurement carries over by construction, not by argument.",
        "base_elf": base_elf,
        "stage_elf": stage_elf,
    }


def address_set(number: int, slug: str) -> set[str]:
    p = os.path.join(stage_dir(number, slug), "PARITY_MAP.json")
    if not os.path.exists(p):
        return set()
    with open(p, encoding="utf-8") as fh:
        doc = json.load(fh)
    return {r["address"] for r in doc["rows"]}
