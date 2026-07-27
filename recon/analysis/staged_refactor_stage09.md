# Stage 09 — grouping by CALL COHESION instead of link adjacency

**Written incrementally while the work was done.** Every number below comes from
a command that was run, and the command is given. Where I corrected my own
earlier claim inside this pass, the correction is left in place rather than
tidied away.

Date: 2026-07-27. Repository HEAD at the start of this pass: `da19df1a`
("Consolidated verdict: stages 00-03 defensible, 04-08 ARE NOT"). Nothing here
is committed.

---

## 0. The one-paragraph answer

Stage 09 is built, registered, tested (46 new tests, suite **203/203**), and
materialised: **742 → 659 app translation units, 55 call-cohesive merged units,
138 units absorbed**, and the number of intra-module call edges that now live
inside a single translation unit goes from stage 04's **11** to **85**. It is
declared `size-changing` with `oracle_required: true` and **no oracle run has
been done for it**; the ladder beneath it fails R7 at the corrected
segmentation, so it could not have been proven this pass in any case.

Three things this pass found that were not known when it started:

1. **§11.2's numbers were stale.** The live tree has **742** retained app TUs,
   not 705; **493** single-source (66.4 %), not 454; **1,224** intra-module
   call edges, not 1,216. Call-cohesion is worth **83** absorbed files, not
   100; the no-adjacency ceiling is **512**, not 523. §1 below.
2. **The recurring defect class has a sixth instance**, and stage 09's first
   build found it: a file-scope `extern` statement with a *comma-separated
   declarator list* declares several symbols that **every refusal rule in this
   pipeline is structurally blind to**. §3.
3. **The ladder does not link at HEAD, from stage 07 upward — and this is not
   stage 09's doing.** Stage 08's own tree, built at HEAD, fails with the same
   single undefined reference. The cause is that stage 07's link evidence
   describes a *different translation-unit partition* from the one its input
   tree now has. §4. This is the most serious finding in this report.

And one thing about stage 09 itself that I got wrong in this report before I
measured it: **the single-source share barely moves** — 66.4 % → **66.3 %**,
because 82 of the 138 absorbed members were already stage 04 merged units. This
stage improves the *quality* of the grouping (35× the call edges per unit), not
the *fraction* of the tree that is grouped. §8 item 2.

---

## 1. §11.2's numbers, re-measured — and they had moved again

The brief said to verify §11.2's counts before relying on them. They had moved.

**Method.** A standalone re-measurement using stage 04's *own* analyser,
*own* header folding and *own* seven refusal rules, so the numbers are
comparable with the ones the verdict publishes:

```sh
S=<scratchpad>
PYTHONSAFEPATH=1 .venv/bin/python $S/measure_11_1.py \
    recon/refactor/stage_08_call_order/tree
```

| | verdict §11.1 (15:24) | **measured here (15:30)** |
|---|---:|---:|
| retained app translation units | 705 | **742** |
| single-source | 454 (64.4 %) | **493 (66.4 %)** |
| intra-module call edges between distinct TUs | 1,216 | **1,224** |
| call-cohesion: groups / absorbed / TUs after | 75 / 100 / 605 | **55 / 83 / 659** |
| no-adjacency ceiling: groups / absorbed / TUs after | 105 / 523 / 182 | **103 / 512 / 230** |

**Why they moved.** A concurrent agent regenerated the entire ladder between
15:27:58 and 15:28:48 on 2026-07-27 (MANIFEST mtimes), which is *after* the
consolidated verdict was written (15:24). Stage 04's own manifest at HEAD now
reports:

```
merge_candidates                1615
translation_units_after          742      (README still says 700; §11.1 said 705)
merged_tus                       249
files_absorbed                  1122      (README says 1,164)
shape_quarantined                 30
```

So this is the third independent confirmation of the project's own warning that
**every plan-file count has been stale at least once**. The README's stage 04
row (`1,615 → 700 TUs … 1,164 files absorbed`) is stale too; the current
numbers are 742 and 1,122.

**What did NOT move:** the shape-quarantine census (30 files, 6 reasons,
identical breakdown) and the hazard census (29 incompatible local typedefs, 35
macro names with differing bodies, 17 statics in more than one file).

**The ratio the stage exists for survives the correction intact.** 1,224 call
edges between distinct units against 11 inside all 249 merged units is 111:1.
Stage 04 groups on an axis that is very nearly orthogonal to call structure.

---

## 2. What stage 09 is

`recon/refactor/transforms/t09_call_cohesion.py`, registered in
`driver.STAGES` as stage 9, slug `call_cohesion`, input stage 08, app core
only, declared **`size-changing`** / **`oracle_required: true`**.

**Grouping.** Within one module directory, over the retained app source list:

* a **call edge** joins A and B when A names an identifier B *defines* with
  external linkage — the same relation stage 08 used *inside* a unit, so the
  two measurements are directly comparable;
* candidates are visited in generated-source-list order and placed **first-fit**
  into an existing group of the same module, accepted only when the candidate
  has a call edge to at least one member already there **and** `t04.conflicts`
  finds nothing against **every** member already there;
* otherwise it opens a new group.

First-fit is a **lower bound** on "connected components of the intra-module
call graph": a component whose members pairwise conflict is split rather than
forced together. That direction is deliberate — the refusal rules win over the
grouping ambition, never the reverse. There is a test for exactly that
(`test_a_pairwise_conflict_wins_over_a_call_edge`).

**Sub-batches**, `G1_STAGE09_BATCH`:

| | |
|---|---|
| `C` (default) | call cohesion — a call edge is required |
| `M` | module-wide ceiling — the edge requirement is dropped. This is §11.1's "no-adjacency ceiling". It absorbs far more and is **not** the default, because what it produces is a module *bucket*, not a cohesive unit. |
| `OFF` | identity transform, for bisecting |

**Shape quarantine.** Stage 04's, re-evaluated against the text each file
actually has at this stage rather than carried forward as a list — plus one
rule stage 04 does not have (§3).

**Emission.** At the position of the earliest member in the generated source
list; members' text verbatim; the §2.3 forward-declaration block for every
struct/union tag the unit names; `recon/generated/app_retained_sources.cmake`
rewritten in the same transaction (C6); unit names `g1_<module>_ccNN.c`, a
namespace disjoint from stage 04's `g1_<module>_NN.c` and provably never
matching `rodata_*` (`g1_verified_rodata_keep.ld` matches on the object
filename — README C6). All four properties have tests.

**Why the declaration cannot be weakened.** Stage 04 merged *adjacent* files,
so a merged unit sat where its members already sat. Stage 09 merges files that
were **not** adjacent, so every member after the first moves from its own
position in the archive to the group's position. The layout disturbance is
strictly larger than stage 04's, and stage 04's was −76 B of `.text` that moved
the OPT3001 poll train a whole 100.5 ms slot and broke eight navigation fields.

### 2.1 Measured result, sub-batch `C`

```sh
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize 9
```

```
translation_units            742 -> 659
merged_units                  55
units_absorbed               138
shape_quarantined             31
intra_module_call_edges     1224
call_edges_now_inside_one_unit  85        (stage 04/08: 11)
placements_blocked          1548
parity_rows                 2567
```

`driver.py check-addresses 8 9` → **identical, 2,567 addresses on both sides,
`only_in_a` and `only_in_b` empty.** No function was dropped or duplicated.

Pairwise refusals, by rule (`stage_09_call_cohesion/QUARANTINE.json`):

```
type       1192      includes     78      static     11
macro       224      typedef      38      tag         1
enumconst     4                            total   1548
```

`no_call_edge_refusals` = **31,606** candidate/group pairs skipped purely for
want of a call edge. That number is the *price of cohesion*: it is what
sub-batch `M` would additionally consider, and it is why `M` reaches 512
absorbed against `C`'s 83.

Groups of length one: **573**.

---

## 3. The sixth instance of the recurring defect class

**Found by a compile failure, not predicted.** The first stage 09 build
(`/private/tmp/g1-s09-build.log`) produced exactly one compile error:

```
recon/symbolized/app/core/g1_core_cc01.c:414:16:
    error: conflicting types for 'k_sleep'; have 'int32_t()'
  414 | extern int32_t k_sleep(k_timeout_t);
note: previous declaration of 'k_sleep' with type 'void(int, int)'
   86 | extern void update_box_presence_flag(void*,void*),
              init_config_fields_default9(void*),k_sleep(int,int),
              st25dv_build_and_write_ndef_records(void*,void*,void*),
              set_time_mark(void);
```

**One `;`, one `extern`, five declarations.** Stage 04 has a shape rule whose
stated intent is precisely this case — *"a multi-declaration source line;
stage 03 already refuses to read those declarations, so their types are
UNKNOWN, and an unknown type cannot be proven not to collide"* — and its
implementation is

```python
d["multi_decl_line"] = any(line.count(";") > 1 or line.count("extern") > 1 ...)
```

which reads a comma-separated declarator list as **one** declaration. Worse,
`t03._decl_symbol` returns the identifier before the *first* `(`, so
`analyse()['decls']` records `update_box_presence_flag` and nothing else: the
declaration of `k_sleep(int,int)` is invisible to refusal rules 1 and 2. Two
tests assert both halves of that blindness so the finding cannot silently
evaporate (`test_stage_04_shape_rule_is_blind_to_it`,
`test_stage_04_records_only_the_first_declarator`).

**Triage: (a) transformer bug AND (b) latent reconstruction defect.**

* (a) The shape rule cannot see what it was written to see. Fixed in stage 09
  by `multi_declarator_externs()`, which finds file-scope `extern` statements
  whose declarator list has a top-level comma (parenthesis/bracket groups are
  blanked first, so a parameter-list comma cannot be mistaken for a separator)
  and shape-quarantines the file. **Fail closed**, deliberately: decomposing
  the list into one canonical declaration per declarator would be strictly
  better — the rules would then *see* the types instead of refusing to look —
  but `_decl_symbol` misreads a function-pointer declarator (`extern int
  (*f)(void), g;` yields `int`), and a decomposition that is wrong is worse
  than a refusal that is total. This is stated in the code, not just here.
* (b) `k_sleep(int,int)` against `int32_t k_sleep(k_timeout_t)` is a genuine
  type disagreement in the canonical corpus — the `DEFECTS.json` class. R1
  makes repairing it the parity agent's work, not this pipeline's.

**Measured cost of the fail-closed rule: 1 file.**

```
files carrying a multi-declarator extern statement
  stage 03 tree       2 of 1,615
  stage 08 tree       2 of   742
newly shape-quarantined by stage 09         1
  (g1_core_01.c)
already quarantined by stage 04's existing rule   1
  (ble_ancs_data_req_thread.c -- it also has a >1-`;` line)
```

Stage 09's shape quarantine is therefore 31 files, 7 reasons, against stage
04's 30 / 6. Merged-unit yield is unchanged at 55 / 138.

### 3.1 The exact patch for stage 04 — written, deliberately NOT applied

`g1_core_01.c` is a **stage 04 merged unit**: stage 04 produced a translation
unit containing a declaration none of its rules could read. It happened not to
collide *inside that unit*. The blind spot is real and it did fire.

The patch, for whoever next owns `t04_cohesive_tu.py`:

```python
# transforms/t04_cohesive_tu.py, in analyse(), replacing the existing
# d["multi_decl_line"] assignment:

    d["multi_decl_line"] = any(
        line.count(";") > 1 or line.count("extern") > 1
        for line in (m.group(0) for m in t3._DECL_LINE.finditer(code))
    ) or bool(t9.multi_declarator_externs(text))
```

(or, without the import, by inlining `multi_declarator_externs`'s body — it is
20 lines and depends only on `strip_comments` and `_depths`, both already in
`t04`.)

**I did not apply it.** Changing `t04.analyse` regenerates stage 04's tree,
and a concurrent agent is re-gating stages 04 and 07 right now — the whole
ladder was regenerated at 15:28 while this pass was reading it. Landing a
transformer change under a running gate is exactly the failure the pipeline's
staleness machinery exists to prevent. The measured exposure is 1 file, so the
cost of deferring is bounded and stated.

---

## 4. THE LADDER DOES NOT LINK AT HEAD — and stage 09 is not the cause

### 4.1 What happened

After the shape rule above, stage 09 **compiled first try, zero compile
errors**, and then failed at the link with exactly one message:

```
recon/symbolized/app/display/display_close_screen.c:39:
    undefined reference to `display_close'
collect2: error: ld returned 1 exit status
```

Before charging that to stage 09, I built **stage 08's own tree** at the same
HEAD:

```sh
./recon/refactor/stage_08_call_order/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s09x-s08
```

```
exit=1
recon/symbolized/app/display/display_close_screen.c:39:
    undefined reference to `display_close'
```

**Byte-identical failure.** Stage 09 adds **zero** new compile errors and
**zero** new link errors over its own input. The failure is inherited.

### 4.2 The root cause, traced

`display_close` is `static` in `display/g1_display_12.c`. It became static at
**stage 07**, and stage 07 decides internal linkage from *link evidence*:

```
recon/refactor/link_referenced_symbols.json
  provenance.build_dir = /private/tmp/g1-s6-base
  referenced_count     = 5420
  'display_close'  in referenced                → False
  'display_close'  in app_defined               → True
```

So on the evidence, nothing outside `display_close`'s own object referenced it,
and `static` was correct. But `display/display_close_screen.c` — a **separate
translation unit in the current tree** — calls `display_close(loc, 2)`.

The evidence build resolves the contradiction:

```sh
arm-zephyr-eabi-nm -A /private/tmp/g1-s6-base/app/libapp.a | grep -w display_close
  …/libapp.a:g1_display_12.c.obj:00000000 T display_close
# and there is NO member named display_close_screen.c.obj at all
```

In the build the evidence was measured from, **`display_close_screen.c` was a
member of `g1_display_12.c`** — the same object — so the call generated no
undefined symbol and the evidence was right. In the current tree,
`g1_display_12.c` has members `display_reflash.c` and `display_close.c` only,
and `display_close_screen.c` is its own translation unit. **Stage 04's
partition moved underneath stage 07's evidence.**

Secondary confirmation of the same drift, from the stale build directories the
consolidated verdict's size gates were measured in:

```sh
arm-zephyr-eabi-nm -A /private/tmp/g1-cons-s08/app/libapp.a | grep -w display_close_screen
  …/libapp.a:g1_display_12.c.obj:00000000 T display_close_screen
```

— i.e. `/private/tmp/g1-cons-s08` was built from a stage 08 tree in which
`display_close_screen` was still inside `g1_display_12.c`. Every SIZE_GATE.json
on disk was measured against `g1-cons-s0N`, so **all eight of them describe a
ladder that no longer exists.**

### 4.3 Why the staleness mechanism did not catch it

`stagelib.EVIDENCE_INPUTS` watches the **content hash** of
`link_referenced_symbols.json`. The file did not change; the *tree it describes*
did. `driver.py status` therefore reports stage 07 as **current** while its
evidence describes a different object partition — the single failure mode the
project's own comment says a staleness mechanism must not have ("it reports
'current' while it is not").

This is the same defect class as everything else in this report: a comparison
that cannot see the difference that matters. Here the comparison is a hash of a
JSON file, and the semantic difference is *which objects exist*.

### 4.4 The repair — two parts

1. **Operational, and prescribed by the pipeline's own contract.**
   `link_evidence.py`'s docstring already says: *"a source change that starts
   calling a symbol from a new place invalidates it. That is why the consumer
   is a STAGE, regenerated from its inputs."* So:

   ```sh
   ./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
       app /private/tmp/g1-s06-base
   PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py generate \
       --build /private/tmp/g1-s06-base
   for n in 7 8 9; do
     PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/driver.py materialize $n
   done
   ```

   **I did not run the `generate` step.** It rewrites a shared evidence input
   and would mark stages 03–09 stale for the concurrent agent mid-gate. The
   measurement of what it would change is in §4.5.

2. **Structural, so it can never again be silent.** The evidence must be
   checkable against the tree that consumes it. Implemented in this pass as an
   additive subcommand — it changes no stage's output and invalidates nothing:

   ```sh
   PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py check-partition \
       recon/refactor/stage_06_unit_composition/tree
   ```

   It compares the object basenames in the evidence build's `app/libapp.a`
   against the source basenames in the consuming tree's
   `recon/generated/app_retained_sources.cmake` and reports the symmetric
   difference. See §5.

### 4.5 What regenerating the evidence would change — MEASURED, not run

Built stage 06's tree at HEAD (it builds and **links** cleanly, `exit=0`,
0 errors) and generated evidence from it **into the scratchpad, never over the
shared file**:

```sh
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s09x-s06          # exit=0
# link_evidence.generate('/private/tmp/g1-s09x-s06', DEFAULT_NM) -> scratch JSON
```

| | committed evidence | fresh from HEAD's stage 06 |
|---|---:|---:|
| `referenced` | 5,420 | **5,422** |
| symbols only in the fresh set | — | **2**: `_puts_r`, `display_close` |
| symbols only in the committed set | 0 | — |
| `app_defined` | 3,742 | 3,742 |
| of stage 07's **133** applied candidates, now referenced | — | **1: `display_close`** |

So the repair is exactly one symbol wide. Stage 07 would apply 132 instead of
133, and the link error disappears. `_puts_r` is the second drifted symbol and
is **not** one of stage 07's candidates, so it costs nothing today — but it is
the newlib-callback family the evidence mechanism exists for, and it drifted
for the same reason.

`link_evidence.py check-partition` on stage 06's tree names both:

```
state                                             STALE
evidence_build                          /private/tmp/g1-s6-base
retained sources with no object in the evidence        59
objects in the evidence no longer retained              9
  … including display_close_screen.c.obj and _puts_r.c.obj in the first list,
    and pixelto4bithex_for_flash.c.obj in the second
```

and against the fresh evidence it reports **`agrees`, 0 and 0** — so the check
is validated in both directions, not just the failing one.

### 4.6 A source-level corroboration, independent of the linker

Over every retained app TU in each tree, every file-scope `static` name that
another retained TU *names*:

| tree | such names | of which are real cross-TU function references |
|---|---:|---|
| stage 08 | 17 | `display_close`, `pixelto4bithex_for_flash` |
| **stage 09** | **17** | the same two |

The other 15 (`bits`, `fp`, `dbg`, `B`, `F`, `eq`, `ipsr`, `isb`,
`rd_basepri`, …) are local-variable names in unrelated files — the scan is
name-level and says so. The point is the equality: **stage 09's cross-TU
`static` exposure is identical to its input's.** It creates none.

`pixelto4bithex_for_flash` does not reach the linker as an error because
`--gc-sections` deletes its only caller; `check-partition` shows it was its own
object when the evidence was measured and is inside a merged unit now, so it is
the same drift with a luckier outcome.

---

## 5. `link_evidence.py check-partition` — what this pass shipped

Additive: a new subcommand and one new pure function. It changes no stage's
output, no existing function's behaviour, and no evidence file, so it
invalidates nothing and marks nothing stale.

```sh
PYTHONSAFEPATH=1 .venv/bin/python recon/refactor/link_evidence.py \
    check-partition recon/refactor/stage_06_unit_composition/tree
```

* `partition_diff(ev_objs, tree_objs, present_sources)` is the pure set logic
  and has six unit tests that need **no toolchain** — the same argument
  `stagelib.elf_section_sizes` makes when it parses ELF by hand ("a gate that
  only runs where a cross-compiler is installed is a gate that does not run").
* The soundness direction is *every retained source of this tree must have an
  object of that name in the evidence archive*. A retained source with no
  object then did not exist as a translation unit then, so any reference to its
  symbols was intra-object and invisible to `nm`.
* The reverse direction is reported for diagnosis, filtered to objects whose
  source still exists under `recon/symbolized/app/`, so the ~1,000
  `rodata_*.c.obj` members of a different generated list cannot create false
  alarms. There is a test for that filter.
* `archive_members` uses `nm -A`, not `ar t`: measured on this host, `ar t`
  renders these archives' extended long-name table unusably (`/`, `//`, `/0`).
* An absent evidence file or an absent evidence build returns
  `"state": "unverifiable"` — **an absent build is not evidence of agreement.**

**Run it against the tree the consuming stage READS** (stage 07 reads stage
06's). Running it against stage 09's own tree reports `STALE 55` — correctly,
because stage 09's 55 merged units do not exist in a stage 06 build — but
stage 09 does not consume the evidence, so that is not a finding about stage 09.

---

## 6. The §13 items that do not need the emulator

### 6.1 `gap_separation.separated` is vacuous — CONFIRMED, and now calibrated

The verdict's §6.2 says the predicate cannot fail. Re-derived from the source
rather than taken on trust (`recon/emulator/scripts/build_display_sensor_oracle.py`,
lines 585-634):

```python
for i in range(1, len(ticks)):
    g = ticks[i] - ticks[i - 1]
    if g > gap_ns:  ...  min_inter = min(min_inter, g)      # every min_inter >  gap_ns
    else:                max_intra = max(max_intra, g)      # every max_intra <= gap_ns
...
"separated": (max_intra is None or min_inter is None
              or (max_intra <= BURST_GAP_NS < min_inter)),
```

`_train_block` calls `split_bursts(ticks)` with the default, so `gap_ns` **is**
`BURST_GAP_NS` on every path. Both conjuncts are therefore true by
construction. It is a tautology, not a check. Measured across the 42
`gap_separation` blocks in the ten oracles under `/private/tmp/g1-pt/rep_*`:
`separated` is `True` **42 of 42**.

**What this pass adds is the calibration the verdict's suggested repair
lacked.** Re-derived the oracle from RAW captures at two thresholds using a
scratch copy of the script (`G1_BURST_GAP_NS`, never the shared file), over
`g1_ship_seed_q1`, `g1_s4b_base_nav1`, `g1_ship_seed_dash_d1`, and computed the
real void ratio `min_inter / max_intra` per device:

| device | ratio at **5.000 ms** (shipped) | ratio at **0.790 ms** |
|---|---:|---:|
| `opt3001_ambient_light` | 62.84 – 73.03 | 62.84 – 73.03 |
| `st25dv_nfc_eeprom` | **1.65 – 1.68** | 102.96 – 102.98 |
| `st25dv_system_port` | **1.50 – 1.51** | 102.93 – 102.98 |
| `lsm6dso_imu` | **1.05 – 1.29** | 39.55 – 48.50 |
| `jbd_display` | **1.24 – 1.33** | 4.27 – 4.34 |
| `npm1300_charger_fuelgauge` | **2.17 – 2.41** | **1.50 – 1.59** |

At the shipped 5 ms threshold **five of six devices have no bimodal void at
all** — `lsm6dso_imu`'s largest intra-burst gap and smallest inter-burst gap are
within **5 %** of each other. The field advertises "the gap distribution is
bimodal"; the data says it is bimodal for exactly one device. At 0.790 ms five
of six become strongly bimodal and only `npm1300_charger_fuelgauge` does not —
and `npm1300` is precisely the device whose train-membership swap blew the
ambiguity rule's Δ to 7,498.630 ms (§6 of the verdict). The two independent
findings agree on which stream is genuinely mis-segmented.

**The exact patch** — for whoever owns `build_display_sensor_oracle.py`; I did
not edit it (R1, and it is another agent's file):

```python
#: A burst gap threshold is only meaningful if the gap distribution has a VOID
#: around it.  `max_intra <= BURST_GAP_NS < min_inter' is true BY CONSTRUCTION
#: -- split_bursts defines max_intra as the largest gap <= the threshold and
#: min_inter as the smallest gap > it -- so it can never fail and never has.
#: This is falsifiable: require the void to be at least K-fold.
#:
#: K = 4 is calibrated, not chosen: at the shipped 5 ms threshold it fires on
#: 5 of the 6 devices (ratios 1.05 - 2.41), and at 0.790 ms it fires on 1
#: (npm1300, 1.50) -- the same train the phase criterion independently shows is
#: mis-assigned.  A check that fires on the threshold known to mis-segment and
#: clears the one known to segment well is doing its job.
SEPARATION_RATIO = 4.0

        "gap_separation": {
            "burst_gap_ns": BURST_GAP_NS,
            "max_intra_burst_gap_ns": max_intra,
            "min_inter_burst_gap_ns": min_inter,
            "separation_ratio": (None if not max_intra or not min_inter
                                 else min_inter / max_intra),
            "separation_ratio_required": SEPARATION_RATIO,
            "separated": (max_intra is None or min_inter is None
                          or min_inter >= SEPARATION_RATIO * max_intra),
        },
```

Note the consequence, stated plainly so it is not a surprise: **applying this
patch turns `separated` False on 5 of 6 devices in every currently committed
oracle.** That is the correct outcome — it is the check finally reporting what
was always true — but it means the field's consumers must be looked at in the
same transaction. That is why it is a patch in a report and not a silent edit
to someone else's file.

### 6.2 Stage 01's declared class, and the whole declared-vs-measured triple

`driver.STAGES` row 1 **is** corrected — it declares `size-changing` and
carries the reason inline. Audited every stage on disk:

| stage | declared (registry) | declared (SIZE_GATE) | measured | pass | deltas |
|---|---|---|---|---|---|
| 1 | `size-changing` | `size-changing` | `size-changing` | ✔ | `text` −4, `rodata` −124 |
| 2 | `byte-identical` | `byte-identical` | `byte-identical` | ✔ | — |
| 3 | `byte-identical` | `byte-identical` | `byte-identical` | ✔ | — |
| 4 | `size-changing` | `size-changing` | `size-changing` | ✔ | `text` −76 |
| 5 | `size-neutral` | `size-neutral` | `byte-identical` | ✔ (better) | — |
| 6 | `byte-identical` | `byte-identical` | `byte-identical` | ✔ | — |
| 7 | `size-changing` | `size-changing` | `size-changing` | ✔ | `text` −276, `rodata` −8 |
| 8 | `size-changing` | `size-changing` | `byte-identical` | ✔ (better) | — |
| 9 | `size-changing` | *(not measurable — no linked image)* | — | — | — |

**Every declared class matches the registry and no stage came out worse than it
declared.** This is now a test, not a table:
`test_call_cohesion.TestRegistry.test_every_size_gate_on_disk_agrees_with_the_registry`
walks `driver.STAGES`, opens every `SIZE_GATE.json` that exists, and asserts
the declared class equals the registry's and the measured rank does not exceed
it. Stage 01's error could not recur silently.

**But a caveat that belongs with the table, not below it:** every one of those
eight gates was measured against `/private/tmp/g1-cons-s0N`, and §4.2 shows
those builds were made from a **different ladder** (their `g1_display_12.c.obj`
still contains `display_close_screen`). The declared-vs-measured *contract* is
sound and now tested; the *numbers* in the right-hand columns are stale and
have to be re-measured after the evidence repair. Stages 0-9 have no size gate
that describes the tree at HEAD.

### 6.3 The equal-population ambiguity rule — left OFF, band documented

`criterion_probe.py` ships it behind `G1_EQUAL_POP_RULE`, default off, with
tests. Nothing in this pass changes that, and nothing in this pass shows it
can be turned on. What this pass adds is *why* the band exists, from the
independent direction:

| burst gap | Δ, original rule | Δ, equal-population rule | devices with a ≥4× void |
|---:|---:|---:|---:|
| 0.700 – 2.300 ms | 145.440 ms | **145.440 ms** | (0.790 ms measured) **5 of 6** |
| 2.400 – 5.000 ms | 145.440 ms | **7,498.630 ms** | (5.000 ms measured) **1 of 6** |

The rule is free exactly where the segmentation is bimodal and explodes exactly
where it is not, and the blow-up is contributed by `npm1300`, which is the one
device still un-bimodal at 0.790 ms. **The rule is not the problem and the
threshold is not independently choosable: the two are one change**, which is
what §6.1 of the verdict said and what §6.1 above now corroborates from the gap
histograms rather than from Δ. It stays off. The condition under which it may
be turned on is now stateable as a measurement on the capture itself
(`separation_ratio >= 4` on every gated device) rather than as a Δ that happens
to come out unchanged.

---

## 7. Gates — what passed, what is outstanding

| gate | result |
|---|---|
| stage tree compiles first try | **PASS after one transformer round.** Round 1 failed with 1 compile error (§3); round 2 compiled with **0** compile errors. R4 honoured: the repair was a transformer change, never a hand-edit. |
| build links | **FAIL — INHERITED.** One undefined reference, `display_close`. Stage 08's tree at the same HEAD fails with the byte-identical message (§4.1). Stage 09 adds zero. |
| `nm -u` 0 | **NOT RUN** — needs a linked ELF. |
| 0 duplicate globals | **NOT RUN** as a link check; the transformer's rule 2 (`dupdef`) refuses the source-level case structurally and has a test. |
| per-object comparison | **RUN, and it is clean:** over the **1,630** objects common to the stage 08 and stage 09 archives, **1,630 have identical allocatable size and 0 differ**. Whole-archive allocatable total **891,578 → 891,514 B, −64 B**, all of it inside the 138 objects replaced by 55 merged ones. (Raw `sha256` of the objects differs everywhere because the build path is embedded — that comparison measures the directory name, not the code.) |
| `check_ram_pin_collisions` | **NOT RUN** — needs an ELF. |
| `check_net_raw_literals`, `verify_net_stock_data_window` | **NOT RUN** — net core untouched, and both need a net ELF. Recorded as not-run, not as passed. |
| `check_thread_create_stack_args` | **NOT RUN** — needs an ELF. |
| `driver.py check-addresses 8 9` | **PASS — identical, 2,567 on both sides**, `only_in_a` / `only_in_b` empty. |
| `driver.py size-gate 9` | **NOT RUN** — there is no stage 09 image to measure. |
| test suite | **PASS 203/203** (was 157/157; +40 stage 09, +6 partition check). |
| idempotence | **PASS** — `materialize 9` twice gives a byte-identical tree (`fdb1e1df…`, 1,693 real files) and a byte-identical MANIFEST (`68c28cf4…`). |
| net image FROZEN 225,581 B | **NOT RE-MEASURED.** The net core was not touched and no net input moved; I did not build it and I do not claim it. |
| R7 / oracle | **OUTSTANDING.** Declared `size-changing`, `oracle_required: true`, **no capture taken**. Renode is held by the concurrent agent and I did not run it. |

---

## 8. The maintainer question, answered directly

> **Would a maintainer opening a stage-09 unit find functions that belong
> together?**

**Yes for the 55 units this stage created, and the improvement is measurable
rather than asserted — but "call each other" is not the same as "belong
together", 55 units out of 659 is not a restructured tree, and the fraction of
the tree that is one function per file is essentially unchanged (66.4 % →
66.3 %, §8 item 2).**

The measurement. Call edges that now live inside one translation unit:

| | edges inside a unit | units |
|---|---:|---:|
| stage 04 / 08 (link adjacency) | **11** | 249 |
| **stage 09 (call cohesion)** | **85** | 55 |

A stage 04 unit averages **0.044** internal call edges. A stage 09 unit averages
**1.55** — **35× denser** — and by construction every stage 09 unit has at
least one, because a member could only join by having one. Group sizes:

```
1 member  573      (untouched)
2          39
3           9
4           4
5           2
7           1
```

Read one and judge. `display/g1_display_cc01.c`:

```
 *   power_down_panel.c        g1_display_08.c -> delay_ms.c
 *   g1_display_08.c           g1_display_08.c -> net_pkt_write_be16.c
 *   net_pkt_write_be16.c      g1_display_08.c -> power_down_panel.c
 *   delay_ms.c                net_pkt_write_be16.c -> g1_display_15.c
 *   g1_display_15.c
```

That reads as a panel power-down path with the two helpers it uses. A stage 04
unit's banner, by contrast, can only say its members "were CONSECUTIVE in that
list".

**Now the honest qualifications.**

1. **`delay_ms` and `net_pkt_write_be16` are generic leaves.** Cohesion by call
   edge pulls a utility into whichever unit calls it, which is right when it has
   one caller and wrong when it is a library primitive that happens to have been
   filed under `display/`. The grouping has no notion of *fan-in*; a rule that
   refused to absorb a member whose module-wide fan-in exceeds some N would be
   the obvious next refinement, and it is not implemented.
2. **573 of 659 units are still groups of one, and the single-source share
   barely moves.** I wrote "about 61 %" here first and then measured it, and I
   was wrong: of the 138 absorbed members, only **56** were single-source (the
   other 82 were already stage 04 merged units), so the share goes

   ```
   493 / 742 = 66.4 %   ->   437 / 659 = 66.3 %
   ```

   **0.1 of a percentage point.** The reviewer objection "64 % of translation
   units are still one function each" is **not answered by this stage at all**.
   What stage 09 improves is the *quality* of the grouping (edges per unit,
   35×), not the *fraction* of the tree that is grouped. Anyone who wants the
   fraction moved wants sub-batch `M`, or wants stage 03b's type census
   repaired so that the 1,192 `type` refusals stop blocking placements.
3. **The unit is merged, not composed.** Each member keeps its own include
   block, so a stage 09 unit can carry an `#include` after code — exactly the
   shape stage 04 produced and stage 05 then compressed. Re-running stage 05's
   composition over a stage 09 tree is the natural follow-on and is deliberately
   not folded in here.
4. **The ceiling is not the answer either.** Sub-batch `M` reaches 512 absorbed
   against `C`'s 83 — six times the yield — but what it produces is a module
   bucket. `M` answers "how much does adjacency cost?"; it does not answer this
   question. That is why it exists and why it is not the default.
5. **1,139 of the 1,224 intra-module call edges still cross a unit boundary.**
   The refusal rules blocked **1,548** placements — `type` 1,192 of them — and
   those are the `DEFECTS.json` declaration disagreements. **The single biggest
   constraint on cohesion is not the grouping algorithm; it is that the corpus
   declares the same symbol with different types in different files.** Until
   stage 03b's census is repaired upstream, no grouping strategy can do much
   better.

So: better, honestly measured, and not finished.

---

## 9. What I did NOT do, and everything quarantined

**Not done, with the reason:**

1. **No Renode, no oracle, no capture.** The concurrent agent owns it. Stage 09
   declares `size-changing` / `oracle_required: true` and that obligation is
   **outstanding**. I make no behavioural claim about stage 09 at all.
2. **I did not regenerate `link_referenced_symbols.json`**, although §4.5
   measures exactly what it would change (2 symbols, 1 stage 07 candidate). It
   is a shared evidence input and rewriting it marks stages 03-09 stale for an
   agent who is mid-gate. The command is in §4.4.
3. **I did not change `t04_cohesive_tu.py`**, although §3.1 contains the exact
   patch and the blind spot is real and fired. Same reason: the ladder was being
   regenerated while this pass ran, and the measured exposure is 1 file.
4. **I did not edit `build_display_sensor_oracle.py`** (R1, another agent's
   file). §6.1 has the patch and, new in this pass, the calibration for its
   constant.
5. **I did not turn the equal-population ambiguity rule on** (§6.3). It stays
   off-by-default and tested.
6. **The net core was not touched, not built and not measured.** The frozen
   225,581 B was not re-verified. `check_net_raw_literals` and
   `verify_net_stock_data_window` are recorded **NOT RUN**.
7. **`cfg_verify` was not run and is not cited.** Every number here comes from a
   build, an `nm`, an ELF section table, a JSON diff, or a re-derivation over a
   capture directory already on disk.
8. **The 638 divergent declaration symbols were not repaired** — R1 makes that
   the parity agent's work. §8 item 5 measures what they cost this stage.
9. **Stage 99** was left stale, as every prior pass has.
10. **Nothing was committed.**
11. **No size gate for stage 09**, because there is no linked image to measure.
    And the eight size gates that do exist describe a ladder that no longer
    exists (§6.2) — I did not re-measure them, because doing so means rebuilding
    a nine-image ladder whose stage 07 does not link.

**Quarantined by stage 09, with measured reasons**
(`stage_09_call_cohesion/QUARANTINE.json`):

```
shape refusals                                          31 files, 7 reasons
    multi_declaration_line_types_unknown                13
    file_scope_pragma_leaks_forward                      9
    per_tu_ffp_contract_body                             5
    multi_declarator_extern_statement_types_unknown      1   <- new this stage
    attribute_alias_definition                           1
    includes_a_definition_carrying_inc_fragment          1
    named_by_path_in_app_cmakelists                      1

pairwise placements blocked                          1,548, over 7 rules
    type 1,192   macro 224   includes 78   typedef 38
    static 11    enumconst 4   tag 1

candidate/group pairs skipped for want of a call edge   31,606
groups of length one                                       573
```

**Per module** (units / members absorbed / largest):

```
lib 18/48/7   core 6/13/3   storage 5/11/3   audio 4/12/4   ble 4/9/3
gui 4/8/2     display 3/12/5  ipc 3/6/2      notify 3/8/4
sensors/input 2/4/2   unsorted 2/4/2   ui/dashboard 1/3/3
```

Ten of the 22 app module directories yielded no call-cohesive group at all.

---

## 10. Reproducing this report

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

# stage 09
$V recon/refactor/driver.py materialize 9
$V recon/refactor/driver.py check-addresses 8 9
$V -m unittest discover -s recon/refactor -p 'test_*.py'        # 203/203
./recon/refactor/stage_09_call_cohesion/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s09-app

# the link failure is upstream -- stage 08 fails identically
./recon/refactor/stage_08_call_order/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s09x-s08

# the evidence drift, and what repairing it would change
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh \
    app /private/tmp/g1-s09x-s06
$V recon/refactor/link_evidence.py check-partition \
    recon/refactor/stage_06_unit_composition/tree           # STALE, 59 / 9
#   link_evidence.generate('/private/tmp/g1-s09x-s06', DEFAULT_NM) into scratch,
#   then diff `referenced` against the committed file        -> +2, -0

# the gap_separation calibration, from RAW captures already on disk (no Renode)
sed 's/^BURST_GAP_NS = 5_000_000  /BURST_GAP_NS = int(__import__("os").environ.get("G1_BURST_GAP_NS", 5_000_000))  /' \
    recon/emulator/scripts/build_display_sensor_oracle.py > $S/bdso2.py
for T in 5000000 790000; do
  G1_BURST_GAP_NS=$T $V $S/bdso2.py /private/tmp/g1_ship_seed_q1   $S/sep/ship_nav_$T
  G1_BURST_GAP_NS=$T $V $S/bdso2.py /private/tmp/g1_s4b_base_nav1  $S/sep/base_nav_$T
  G1_BURST_GAP_NS=$T $V $S/bdso2.py --screen=dashboard \
      /private/tmp/g1_ship_seed_dash_d1 $S/sep/ship_dash_$T
done
#   then min_inter/max_intra per device from each display_sensor_oracle.json
```

## 11. Footprint — everything this pass wrote

```
recon/refactor/transforms/t09_call_cohesion.py     NEW   the stage
recon/refactor/test_call_cohesion.py               NEW   40 tests
recon/refactor/driver.py                           +14   stage 9 registry row
recon/refactor/link_evidence.py                   +140   check-partition
recon/refactor/test_evidence.py                    +55   6 tests
recon/refactor/stage_09_call_cohesion/             NEW   materialised stage
recon/refactor/README.md                            mod  gate record
recon/analysis/staged_refactor_stage09.md          NEW   this report
```

No canonical tree, no `recon/symbols`, no `recon/application`, no `tools/`, no
emulator report and no other stage directory was written to. `guard.py` enforces
the first four structurally; the rest is `git status`.
