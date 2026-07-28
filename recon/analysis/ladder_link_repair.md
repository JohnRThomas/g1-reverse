# Ladder link repair — the stale-evidence staleness hole, and the comma declarator

**Written incrementally while the work was done.** Every number comes from a
command that was actually run, and the command is given. Where I corrected my
own earlier claim inside this pass, the correction is left in place rather than
tidied away.

Date: 2026-07-28. Repository HEAD at the start of this pass: `6fd3427f`
("P4 iter-46: repaired stage 04 PASSES -- and a 204-byte inert pad flips the
gate"). **Nothing here is committed.**

**I cannot run the oracle.** Renode is owned by a concurrent agent and I did not
touch it. No behavioural claim about any stage is made anywhere in this report.
Where a stage is `size-changing` / `oracle_required: true`, that obligation is
recorded as **OUTSTANDING**, never as discharged.

---

## 0. Baseline, measured before anything was changed

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py status
$V -m unittest discover -s recon/refactor -p 'test_*.py'
$V recon/refactor/link_evidence.py check-partition \
    recon/refactor/stage_06_unit_composition/tree
```

| | |
|---|---|
| test suite, with the uncommitted t04/t09 edits in place | **203/203 OK** |
| `driver.py status`, stages 00-09 | **every one `current`** |
| `driver.py status`, stage 99 | `stale` (863 changed inputs — as every prior pass left it) |
| `check-partition` on stage 06's tree | **`STALE`, 59 retained sources with no object in the evidence, 9 objects no longer retained** |

Those first two rows together **are** the bug: the pipeline's own staleness
report says stages 07, 08 and 09 are current, and the third row says the
evidence stage 07 reads describes a different translation-unit partition from
the tree it reads it against. `display_close_screen.c.obj` and `_puts_r.c.obj`
are both in the `only_in_tree` list, exactly as `staged_refactor_stage09.md`
§4.5 reported.

**Confirmed independently, not taken on trust.** (sections below, filled in as
the work proceeds)

---

## 1. The uncommitted transformer edits — FINISHED, not reverted

`git diff` at session start showed two modified files:

* `transforms/t04_cohesive_tu.py` **+83 lines**: `_blank_groups`,
  `multi_declarator_externs`, the `d["multi_declarator_extern"]` analysis key,
  and the `shape_refusal` arm returning
  `multi_declarator_extern_statement_types_unknown`.
* `transforms/t09_call_cohesion.py` **-78/+7 lines**: the two functions deleted
  and re-bound as aliases onto `t4._blank_groups` / `t4.multi_declarator_externs`.

**Decision: finish it.** Reasons, in order of weight:

1. It is the §3.1 patch the brief asked for, landed in the place §3.1 says it
   belongs (stage 04, where the blind spot lives), and it is the *stronger* of
   the two forms §3.1 offers — a distinct analysis key and a distinct
   quarantine reason, so `QUARANTINE.json` names *which* shape fired, rather
   than OR-ing into `multi_decl_line` and losing that.
2. The de-duplication is complete in the direction that matters: stage 09 now
   has **no copy** of the logic, only aliases, so the two cannot drift. Stage
   09's 40 tests — the record of how the sixth instance was found — go on
   exercising the same code the merge now uses.
3. It was already green: **203/203 with the edits in place**, measured above
   before I changed anything.

What was *not* finished by the previous agent, and is finished here: nothing in
the transformers. The edits are self-consistent as they stand. What was missing
was everything downstream — the stages were never regenerated against them, and
`driver.py status` could not tell (§0).

### 1.1 What the patch actually cost, measured

`driver.py materialize 4` before and after. The "before" column is the live
tree at session start (which `staged_refactor_stage09.md` §1 measured
independently and reported as 742/1,122/30):

| stage 04 | README's row | live at session start | **after the patch** |
|---|---:|---:|---:|
| `translation_units_after` | 700 | 742 | **743** |
| `merged_tus` | 249 | 249 | **249** |
| `files_absorbed` | 1,164 | 1,122 | **1,121** |
| `shape_quarantined` | — | 30 | **31** |
| `adjacencies_blocked` | — | — | **893** |

One more file quarantined, one fewer absorbed, one more translation unit. The
new quarantine reason appears in `stage_04_cohesive_tu/QUARANTINE.json` as
`multi_declarator_extern_statement_types_unknown`. **The measured exposure
§3.1 predicted (1 file) is exactly what it cost.** The README's row is wrong in
both figures and is corrected in §6.

The other two files carrying a comma-declarator `extern` were already
quarantined by the pre-existing `multi_decl_line` rule, so the rule's total
reach is 2 files of 1,615 at stage 03 — unchanged from §3's census.

---

## 2. The staleness hole — the part that matters more than the two symbols

### 2.1 The bug, restated precisely

`link_referenced_symbols.json` answers **"which symbols does something outside
their own OBJECT reference?"**. That answer is only meaningful relative to a
particular partition of sources into objects. `stagelib.EVIDENCE_INPUTS`
watched the file's **content hash**. The file's bytes did not change; the
partition did. So `status` said `current` and the link said
`undefined reference to 'display_close'`.

This is the **fourth** staleness hole in this pipeline, and all four have one
shape: *something correlated with the input was watched instead of the input.*

| # | watched | actual input | how it surfaced |
|---|---|---|---|
| 1 | the first member of a merged unit | all members | recorded pre-emptively in `stagelib.emit`'s docstring |
| 2 | `input_set` (which never lists the evidence files) | the evidence too | regenerating SDK evidence moved stage 03's harvest 218→215 hoists while `status` said current |
| 3 | — | — | (the `EVIDENCE_INPUTS` list that closed #2) |
| 4 | **the evidence file's hash** | **the partition the evidence describes** | **this pass: the app link failed from stage 07 upward** |

The rule that follows, and the one I implemented to: **watch the thing the
consumer's correctness actually depends on.**

### 2.2 The fix, in four parts

**(a) The evidence records the partition it was measured from.**
`link_evidence.generate()` now writes `app_objects` — the sorted object
basenames of the evidence build's `app/libapp.a` — into the evidence JSON
itself. Measured: **1,769 objects**.

This is not a convenience. Before it, the only way to recover the partition was
to `nm` the build directory recorded in `provenance.build_dir` — and that
directory lives in `/private/tmp`, which the OS reaps. Once it is gone the
checker's only honest answer is `"unverifiable"`, i.e. **the check silently
stops checking**, which is the same failure one level up. A recorded set never
evaporates and needs no cross-compiler to read.

**(b) A toolchain-free state function.** `link_evidence.partition_state(tree)`
compares that recorded set against the tree's own
`recon/generated/app_retained_sources.cmake`. Two text files inside the
repository; no ELF, no `nm`, no build. States: `agrees`, `STALE`,
`unrecorded` (evidence predating (a) — **fails closed**), `no_evidence` (not a
staleness fault: absent evidence already means "apply nothing" to every
consumer), `unverifiable` (tree has no retained source list).

**(c) `stagelib.staleness` consults it.** A transformer that reads
partition-dependent evidence sets `CONSUMES_PARTITION_EVIDENCE = True`
(`t07_internal_linkage.py` does; t04, t08, t09 deliberately do not, and there
is a test asserting exactly that, so the check cannot degrade into noise that
gets ignored). `driver.py materialize` then records the agreement in the
MANIFEST, and `staleness()` **re-derives it on every `status`** against the
stage's recorded input tree.

**(d) The repair line is corrected.** When the partition disagrees,
`status`'s `repair` field no longer says "materialize the stage" — regenerating
it would read the same stale evidence and make the same wrong decision. It now
prints the three-command sequence: rebuild the input tree → regenerate the
evidence → materialize. There is a test asserting the repair text names
`link_evidence.py generate`.

`check_partition` (the existing subcommand) was also changed to prefer the
recorded partition, so it keeps working after the build directory is reaped;
it reports which source it used in a new `partition_source` field.

### 2.3 The detector, exercised in both directions LIVE

```sh
$V -c "import link_evidence as le; le.partition_state(<tree>)"
```

| tree / evidence | state | tree objs | evidence objs | missing |
|---|---|---:|---:|---:|
| stage 06 tree, **repaired** evidence | `agrees` | 743 | 1,769 | 0 |
| stage 04 tree, repaired evidence | `agrees` | 743 | 1,769 | 0 |
| stage 09 tree, repaired evidence | **`STALE`** | 660 | 1,769 | **55** |
| stage 06 tree, **pre-repair** evidence | **`unrecorded`** | — | — | — |

The stage 09 row is the check working, not a fault: stage 09's 55 merged units
did not exist in the stage 06 build, and stage 09 does not consume the
evidence. The stage 06 row against the old evidence is the fail-closed path.

`check-partition` on stage 06's tree, before and after:

```
BEFORE   state STALE   59 retained sources with no object   /  9 objects no longer retained
AFTER    state agrees   0                                   /  0     (partition_source: recorded in the evidence)
```

### 2.4 Tests

`test_evidence.py` gains **9 tests** in a new class,
`TestPartitionIsWatchedNotJustHashed`. Suite **203 → 212, all passing**. The
load-bearing one is
`test_staleness_reports_STALE_although_every_hash_matches`: identical evidence
bytes, identical source hashes, and the stage must still come out `stale` —
with the repair naming `link_evidence.py generate` rather than `materialize`.
It also asserts the other direction (`agrees` → `current`), because a checker
that only ever says STALE is not a checker.

`test_the_generator_records_the_partition_it_measured` **failed on the
committed evidence file** when I first ran it, which is the honest way round:
the test was written before the evidence was regenerated and it caught the old
format.

---

## 3. The evidence regeneration, and the two symbols

Stage 06's tree at the repaired stage 04 partition builds and **links** cleanly:

```sh
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-lr-s06
```

```
exit=0    compile errors: 0    FLASH 956,292 B (97.33 %)    RAM 253,765 B (56.32 %)
```

Evidence regenerated from it. The diff against the committed file:

| | committed (`/private/tmp/g1-s6-base`) | **regenerated (`/private/tmp/g1-lr-s06`)** |
|---|---:|---:|
| `referenced` | 5,420 | **5,422** |
| only in the new set | — | **2: `_puts_r`, `display_close`** |
| only in the old set | — | **0** |
| `app_defined` | 3,742 | 3,742 |
| `app_objects` recorded | *(field absent)* | **1,769** |

**Exactly the two symbols §4.5 predicted, and no others** — and note this was
re-derived at the *new* 743-TU partition, not the 742-TU one §4.5 measured, so
the prediction survived a partition change of its own.

Stage 07's applied candidates: **133 → 132.** `display_close` is no longer a
candidate and no longer becomes `static`.

---

## 4. Regeneration and integrity

Stages were regenerated **00 → 09 in order** after the evidence was final —
never patched. `driver.py status`:

```
  0 snapshot              current    6 unit_composition     current
  1 literal_inline        current    7 internal_linkage     current   partition=agrees
  2 block_dedupe          current    8 call_order           current
  3 module_structure      current    9 call_cohesion        current
  4 cohesive_tu           current   99 defect_probe         stale  (as every prior pass left it)
  5 cohesive_composition  current
```

**Idempotence — proven over the whole ladder, not one stage.** Every stage tree
was fingerprinted (sha256 over `(relpath, sha256(bytes))` of every real file,
symlinks excluded), then all ten stages re-materialised, then fingerprinted
again:

```
ALL TEN TREES BYTE-IDENTICAL
```

All ten `PARITY_MAP.json` files are byte-identical too. Only the MANIFESTs of
stages 00-06 changed, and only because they record the new evidence hash.

Two things worth recording from the fingerprints:

* **stage 07 and stage 08 have the byte-identical tree** (`9f6901de…`, 1,777
  real files). Stage 08 reports `units_reordered: 0`, `files_changed: 0` — it
  is a measured no-op on this input, as the README already says.
* stage 09's tree is 1,694 real files against 1,777.

`driver.py check-addresses` on **every consecutive pair**:

```
0->1 1->2 2->3 3->4 4->5 5->6 6->7 7->8 8->9
identical=True everywhere, count_a = count_b = 2,567, only_in_a = only_in_b = 0
```

**2,567 addresses carried unchanged through all nine transitions.** No function
was dropped or duplicated anywhere in the ladder.

---

## 5. A FIFTH staleness hole, found while closing the fourth — and closed

I hit it myself, in this pass, which is the only reason it is in this report.

**A stage is `transformer(input)`. Staleness watched the input and the evidence
and never the transformer.** I applied the comma-declarator repair to
`t04_cohesive_tu.py`, ran `driver.py status`, and it reported stages 04 through
09 **`current`** — while stage 04's tree still held the 742-unit partition the
*unpatched* rule produced. Nothing but my remembering to type `materialize`
stood between that and a gate measured against a tree no transformer would now
produce. It is the same family as the other four: something correlated with the
input was watched instead of the input.

**Closed.** `stagelib.transforms_digest()` is one sha256 over every `*.py` in
`recon/refactor/transforms/`; `driver.py materialize` records it as
`transforms_digest` in the MANIFEST; `staleness()` compares it and reports
`recon/refactor/transforms/ (TRANSFORMER CHANGED)` among `inputs_changed`.

Three design choices, each for a stated reason:

* **Whole directory, not the imported closure.** Deriving it from `sys.modules`
  after the import would make stage 04's record depend on whether stage 09 had
  been materialised first in the same process — that breaks MANIFEST
  idempotence. There is a test for determinism. Transformers also import each
  other heavily (t05-t09 all use `t04.conflicts`), so the true closure is
  nearly the whole directory anyway. It over-refuses; over-refusing costs one
  regeneration of a pipeline this pass proves byte-idempotent.
* **An absent field is not a stale.** A manifest written before the digest
  existed reports `transforms_digest: "NOT RECORDED -- regenerate to start
  watching"` and stays `current`. Fabricating a stale would have made the
  ladder permanently red for a reason that is not a fault.
* **What it still does not cover, stated rather than implied:**
  `stagelib.py`, `driver.py`, `input_set.py` and the evidence generators are
  **not** in the digest. A change to those can still move a stage's output
  without marking it stale. **That is a smaller hole, not no hole**, and I am
  leaving it open rather than pretending otherwise.

Three tests, suite **212 → 215**.

---

## 6. What the comma-declarator repair changed about WHERE the rule fires

Worth recording because it is better than §3.1 predicted, and I did not expect
it.

Stage 09 saw the defect in `g1_core_cc01.c`, and traced it back to
`g1_core_01.c` — a **stage 04 merged unit**. Landing the rule in stage 04 makes
it fire one stage earlier, on the **source file** that actually carries the
declaration:

```
stage 04 QUARANTINE.json, new rule fires on:  box_placement_animation_step.c
```

So the repair is not "quarantine the merged unit that turned out to contain a
bad declaration" — it is "refuse to merge the file that carries one **in the
first place**". Verified structurally rather than by inspection:

```
box_placement_animation_step.c is its own TU in app_retained_sources.cmake   1 occurrence
stage 04 units carrying BOTH `k_sleep(int,int)' and `k_sleep(k_timeout_t)'   0
```

The collision stage 09 tripped over cannot form at stage 04 any more.

**Shape quarantine census, stage 04 (31 files, 7 reasons)** — identical at
stage 09:

```
multi_declaration_line_types_unknown              13
file_scope_pragma_leaks_forward                    9
per_tu_ffp_contract_body                           5
attribute_alias_definition                         1
includes_a_definition_carrying_inc_fragment        1
multi_declarator_extern_statement_types_unknown    1   <- new, in stage 04 now
named_by_path_in_app_cmakelists                    1
```

---

## 7. THE LADDER LINKS — all ten stages, measured

Ten builds, one per stage, each into its own directory, driven by
`/private/tmp/g1-lr-buildall.sh`:

```
### stage 0 exit=0 compile_errors=0 link_undef=0     ### stage 5 exit=0 compile_errors=0 link_undef=0
### stage 1 exit=0 compile_errors=0 link_undef=0     ### stage 6 exit=0 compile_errors=0 link_undef=0
### stage 2 exit=0 compile_errors=0 link_undef=0     ### stage 7 exit=0 compile_errors=0 link_undef=0
### stage 3 exit=0 compile_errors=0 link_undef=0     ### stage 8 exit=0 compile_errors=0 link_undef=0
### stage 4 exit=0 compile_errors=0 link_undef=0     ### stage 9 exit=0 compile_errors=0 link_undef=0
```

**10 of 10 build. 10 of 10 link. Zero compile errors. Zero undefined
references.** Stages 07, 08 and 09 previously failed with
`undefined reference to 'display_close'`; they do not now.

**Transformer rounds: zero.** No transformer needed a second round in this
pass — the one transformer change (the comma-declarator rule) was written by
the previous agent and compiled first try. Nothing was hand-edited in any
stage tree.

Per-image link hygiene:

| stage | `nm -u` | duplicate globals | `zephyr.bin` | sha256 (12) |
|---|---:|---:|---:|---|
| 00 | 0 | 0 | 956,496 | `2c510a78366b` |
| 01 | 0 | 0 | 956,356 | `a868a9fba012` |
| 02 | 0 | 0 | 956,356 | `a868a9fba012` |
| 03 | 0 | 0 | 956,356 | `a868a9fba012` |
| 04 | 0 | 0 | 956,292 | `3345b40a4662` |
| 05 | 0 | 0 | 956,292 | `3345b40a4662` |
| 06 | 0 | 0 | 956,292 | `3345b40a4662` |
| 07 | 0 | 0 | 956,076 | `b369a08c7162` |
| 08 | 0 | 0 | 956,076 | `b369a08c7162` |
| 09 | 0 | 0 | 956,092 | `bfa3bfae1d94` |

The image hashes independently confirm the size gates: 01=02=03, 04=05=06,
07=08, and 09 alone.

### 7.1 Size gates — all nine, re-measured

`driver.py size-gate N /private/tmp/g1-lr-s0(N-1) /private/tmp/g1-lr-s0N`:

| stage | declared | **measured** | pass | oracle required | nonzero deltas |
|---|---|---|---|---|---|
| 1 | `size-changing` | `size-changing` | ✔ | **yes** | `text` −4, `rodata` −124 |
| 2 | `byte-identical` | `byte-identical` | ✔ | no | — |
| 3 | `byte-identical` | `byte-identical` | ✔ | no | — |
| 4 | `size-changing` | `size-changing` | ✔ | **yes** | `text` −76 |
| 5 | `size-neutral` | `byte-identical` *(better)* | ✔ | no | — |
| 6 | `byte-identical` | `byte-identical` | ✔ | no | — |
| 7 | `size-changing` | `size-changing` | ✔ | **yes** | `text` −200, `rodata` −8 |
| 8 | `size-changing` | `byte-identical` *(better)* | ✔ | no | — |
| 9 | `size-changing` | `size-changing` | ✔ | **yes** | `text` **+8** |

**All nine PASS. No stage came out worse than it declared.**

Two things that moved and should not be glossed:

* **Stage 07 is `.text` −200, not −276.** The README and the consolidated
  verdict both say −276. That number was measured at a different partition and
  with 133 candidates; at 743 TUs and 132 candidates it is **−200**. This is
  the fourth generation of this figure (−276, −276, and 135/137 candidates in
  earlier records). I have corrected the README row.
* **Stage 09 has a size gate for the first time.** `staged_refactor_stage09.md`
  §7 recorded it NOT RUN because stage 09 had no linked image. It has one now:
  **`.text` +8 B**, `size-changing`, PASS.

**All eight pre-existing `SIZE_GATE.json` files described a ladder that no
longer existed** (§6.2 of the stage 09 report: they were measured against
`/private/tmp/g1-cons-s0N`). All nine are now re-measured against
`/private/tmp/g1-lr-s0N`, built from the trees currently on disk, and written
into the stage directories.

### 7.2 The transformer digest, exercised live

Not just unit-tested — driven against the real ladder:

```
append one comment line to transforms/t04_cohesive_tu.py
  -> driver.py status: stages 0-9 ALL STALE
revert it
  -> driver.py status: stages 0-9 ALL CURRENT
```

Both directions, on the live pipeline.

---

## 8. HONEST STATE OF EVERY STAGE

**Read the last column first.** `builds` and `links` are facts about a
toolchain. `oracle` is a fact about behaviour, and I could not measure a single
one of them.

| stage | builds | links | `nm -u` | declared | measured | size gate | **oracle** |
|---|---|---|---|---|---|---|---|
| 00 | ✔ | ✔ | 0 | `byte-identical` | *(identity)* | n/a | n/a |
| 01 | ✔ | ✔ | 0 | `size-changing` | `size-changing` | ✔ PASS | **OUTSTANDING — NOT RUN** |
| 02 | ✔ | ✔ | 0 | `byte-identical` | `byte-identical` | ✔ PASS | not required |
| 03 | ✔ | ✔ | 0 | `byte-identical` | `byte-identical` | ✔ PASS | not required |
| 04 | ✔ | ✔ | 0 | `size-changing` | `size-changing` | ✔ PASS | **OUTSTANDING — NOT RUN** |
| 05 | ✔ | ✔ | 0 | `size-neutral` | `byte-identical` | ✔ PASS (better) | not required *(inherits 04)* |
| 06 | ✔ | ✔ | 0 | `byte-identical` | `byte-identical` | ✔ PASS | not required *(inherits 04)* |
| 07 | ✔ | ✔ | 0 | `size-changing` | `size-changing` | ✔ PASS | **OUTSTANDING — NOT RUN** |
| 08 | ✔ | ✔ | 0 | `size-changing` | `byte-identical` | ✔ PASS (better) | not required *(inherits 07)* |
| 09 | ✔ | ✔ | 0 | `size-changing` | `size-changing` | ✔ PASS | **OUTSTANDING — NOT RUN** |

**I CANNOT RUN THE ORACLE and I did not run it.** Renode is held by a
concurrent agent. I make **no behavioural claim about any stage**. Four stages
(01, 04, 07, 09) declare `oracle_required: true` and all four obligations are
open. Linking is not equivalence: a `.text` delta of **+8 B** — stage 09's — is
exactly the order this project has three times measured to re-phase the boot
path and break byte-equality of a peripheral bus stream, *in either direction*.

The R7 verdicts in the consolidated record (stages 04-08 FAIL under the
corrected segmentation) stand **unchanged and un-re-tested by this pass**, and
they were measured on **different images** from the ten tabulated in §7 — so
they cannot simply be carried across either.

---

## 9. WHAT I DID NOT CLOSE, and why

1. **The oracle, for all four `size-changing` stages.** Renode belongs to a
   concurrent agent. Stated as OUTSTANDING everywhere, never as discharged.
2. **The R7 verdict.** Not re-derived. The consolidated verdict's FAIL for
   stages 04-08 is neither confirmed nor refuted here, and the images have
   moved underneath it.
3. **The net core.** Not built, not touched, not measured. The frozen
   225,581 B was **not** re-verified and I do not claim it.
   `check_net_raw_literals` and `verify_net_stock_data_window`: **NOT RUN.**
4. **`check_ram_pin_collisions`, `check_thread_create_stack_args`,
   `tools/verify_data.py`, `cfg_verify`.** Not run. Every number in this
   report comes from a build, an `nm`, an ELF section table, a JSON diff, or
   the pipeline's own driver.
5. **The remaining staleness surface.** `stagelib.py`, `driver.py`,
   `input_set.py` and the evidence *generators* are still not watched by
   anything. A change to those can move a stage's output while `status` says
   `current`. **Smaller hole, not no hole** — §5.
6. **`_puts_r`.** It is the second symbol that drifted and it is now in the
   evidence's `referenced` set, so nothing is broken by it today. But it is
   the newlib-callback family the evidence mechanism exists for, and it
   drifted for the same reason `display_close` did. Nobody has audited whether
   other members of that family are one partition move away from the same
   fate.
7. **The 638 divergent declaration symbols** (`DEFECTS.json`) — R1 makes that
   the parity agent's work. They are still the single largest constraint on
   grouping: 1,545 pairwise placements blocked at stage 09, `type` refusals the
   bulk of them.
8. **`build_display_sensor_oracle.py` / the `gap_separation` tautology / the
   equal-population rule.** Untouched; another agent's files. The patches and
   calibration remain in `staged_refactor_stage09.md` §6.
9. **Stage 99** left stale, as every prior pass has.
10. **Decomposing a comma-declarator list** into one declaration per declarator
    — which would let the rules *see* the types instead of refusing to look —
    is still not attempted, for the reason the code states: `_decl_symbol`
    misreads a function-pointer declarator, and a wrong decomposition is worse
    than a total refusal.
11. **Nothing was committed.** The tree is dirty; §10 says exactly how.

---

## 10. FOOTPRINT — everything this pass wrote

```
recon/refactor/link_evidence.py             mod   app_objects recorded; retained_app_objects,
                                                  evidence_app_objects, partition_state;
                                                  check_partition prefers the recorded set
recon/refactor/stagelib.py                  mod   PARTITION_DEPENDENT_EVIDENCE,
                                                  evidence_partition_state, TRANSFORMS_DIR,
                                                  transforms_digest; staleness consults both
                                                  and rewrites the repair line
recon/refactor/driver.py                    mod   records transforms_digest + evidence_partition
recon/refactor/transforms/t04_cohesive_tu.py mod  (FINISHED the previous agent's edit)
recon/refactor/transforms/t09_call_cohesion.py mod (FINISHED: aliases, no second copy)
recon/refactor/transforms/t07_internal_linkage.py mod  CONSUMES_PARTITION_EVIDENCE = True
recon/refactor/test_evidence.py             +12 tests  (203 -> 215)
recon/refactor/link_referenced_symbols.json REGENERATED from /private/tmp/g1-lr-s06
recon/refactor/stage_0*/MANIFEST.json       regenerated (all 10)
recon/refactor/stage_0*/PARITY_MAP.json     regenerated (all 10)
recon/refactor/stage_0*/QUARANTINE.json     regenerated (04, 05, 07, 09)
recon/refactor/stage_0*/SIZE_GATE.json      re-measured (01-09; 09 for the FIRST time)
recon/refactor/stage_0*/tree/               regenerated (all 10) -- gitignored
recon/refactor/README.md                    mod   rows 04/07/09 corrected from measurement;
                                                  new gate record appended
recon/analysis/ladder_link_repair.md        NEW   this report
```

No canonical tree, no `recon/symbols`, no `recon/application`, no `tools/`, no
emulator script or report, and no net-core file was written by me. `guard.py`
enforces the first several structurally; the rest is `git status`.

**NOT MINE — the concurrent agent was writing to this tree while this pass
ran.** `git status` at the close also shows:

```
 M recon/emulator/scripts/build_display_sensor_oracle.py
 M recon/emulator/scripts/phase_tolerant_compare.py
?? recon/emulator/scripts/slot_quantised_compare.py
?? recon/analysis/criterion_bound_redesign.md
?? Even+Realities_1.9.0.xapk                       (pre-existing, unrelated)
```

**I did not touch any of those files.** They were absent from a `git status`
taken mid-pass and present at the close, which dates them to the concurrent
agent, not to me. I record them so that whoever reviews this dirty tree does
not attribute them here — and note the practical consequence: `.../scripts/`
moved *underneath* this pass, so if any of my measurements had depended on the
oracle scripts they would now be suspect. None do; every number here comes from
a build, an `nm`, an ELF section table, a JSON diff, or `driver.py`.

## 11. Reproducing this report

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

# 1. the ladder, up to the tree the evidence must be measured from
for n in 4 5 6; do $V recon/refactor/driver.py materialize $n; done
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-lr-s06                                   # exit 0, links
$V recon/refactor/link_evidence.py generate --build /private/tmp/g1-lr-s06

# 2. the rest of the ladder, then the whole thing again for idempotence
for n in 7 8 9; do $V recon/refactor/driver.py materialize $n; done
for n in 0 1 2 3 4 5 6 7 8 9; do $V recon/refactor/driver.py materialize $n; done

# 3. the gates
$V recon/refactor/driver.py status
$V recon/refactor/link_evidence.py check-partition \
    recon/refactor/stage_06_unit_composition/tree                # agrees, 0 / 0
$V -m unittest discover -s recon/refactor -p 'test_*.py'         # 215/215
for n in 0..9; do build stage n -> /private/tmp/g1-lr-s0$n; done # /private/tmp/g1-lr-buildall.sh
for n in 1..9; do $V recon/refactor/driver.py size-gate $n \
    /private/tmp/g1-lr-s0$((n-1)) /private/tmp/g1-lr-s0$n; done
for pair in 0-1 ... 8-9; do $V recon/refactor/driver.py check-addresses $a $b; done
```


