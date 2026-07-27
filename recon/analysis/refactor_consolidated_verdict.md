# The staged refactor, consolidated — one document, one baseline

**Purpose.** Until now, answering "is the staged refactor proven?" required
reading seven reports written at three different HEADs against three different
baselines. This document regenerates the whole ladder at ONE head, re-measures
every gate, states the verdict per stage in one table, and enumerates what is
still outstanding.

Everything below is a number from a command run in this pass, at:

```
HEAD            e7f35727  "Type-disagreement repair 4: 89 shadow entries closed,
                           zephyr.bin BYTE-IDENTICAL"
working tree    clean except the unrelated untracked Even+Realities_1.9.0.xapk
date            2026-07-27
```

Written incrementally as the work ran. Where this pass contradicts an earlier
report — including its own earlier paragraphs — the correction is made in place
and labelled.

---

## 0. What this pass was asked to do, and what it did

| task | outcome |
|---|---|
| 1. Regenerate + re-verify the ladder at HEAD | **done** — and it found that **stage 04 no longer compiles** (§2) and that the **payload identity has broken**, invalidating half the captures (§3.2) |
| 2a. Stage 08 `SIZE_GATE.json` | **done** (§3) — and stages 01, 02, 03 had none either; **stage 01's, run for the first time, FAILED and its declared class was wrong** (§3.4) |
| 2b. Burst-gap threshold | **measured, NOT adopted** (§5) — but it **flips stages 04-B/05/06/07 from PASS to FAIL** at every threshold that leaves Δ unchanged, so the published verdict must change regardless |
| 2c. Ambiguity rule (§8 item 7) | **implemented, off by default** (§6) — the "closable at zero cost" claim is **FALSE** at the shipped burst gap: Δ would go 145.440 → **7,498.630 ms** |
| 2d. `RADIO_TX` component field | **ADOPTED** (§7) — zero captures, zero oracle change, and the base does **not** hold `RADIO_TX` |
| 3. One consolidated verdict, in the README gate record | **done** — §9 here, and the README's `★ CONSOLIDATED GATE RECORD` |
| 4. Improved grouping as a new stage | **measured and specified, NOT built** (§11) — 1,216 call edges vs stage 08's 11, ceiling 705 → 182 TUs; not landed because the oracle is unavailable and the ladder it would sit on fails R7 |

**Δ was NOT tuned.** It re-derives to exactly **145.440 ms** — the published
value — at every burst-gap threshold and under both ambiguity rules in the band
this pass reports. Every criterion change measured here makes stages *fail*;
none makes one pass.

---

## 1. The ladder regenerated at HEAD `e7f35727`

`driver.py status` before anything: **stage 00 stale on 177 inputs**
(2,454 unchanged of 2,631), stages 01–08 reported *current* because they are
compared against stage 00's tree, which had not yet been regenerated. Stage 99
(the retired diagnostic probe) stale on 824 — expected, it is not in the ladder.

Regenerated **00 → 08 in order, never patched, zero transformer rounds** (every
`materialize` exited 0 on its first invocation; no transformer was edited in
this pass):

```
for n in 0 1 2 3 4 5 6 7 8; do driver.py materialize $n; done      # all exit 0
```

### 1.1 Harvest, and what moved since iteration 44's regeneration

Iteration 44 (`our_boot_bringup.md` §44.1) regenerated the same ladder at HEAD
`49caeb66`. Two repair passes have landed since (`0ce1fda4` iter-44,
`e7f35727` type-disagreement repair 4). Field-by-field:

| stage | field | iter 44 @ `49caeb66` | **this pass @ `e7f35727`** |
|---|---|---:|---:|
| 00 | files copied / parity rows | 2,629 / 2,567 | **2,629 / 2,567** (unchanged) |
| 01 | rodata objects withdrawn / bytes / PROVIDE pins retired | 100 / 3,997 / 100 | **100 / 3,997 / 100** (unchanged) |
| 01 | candidates accepted / sites inlined / files rewritten | — | 100 / 192 / 43 |
| 02 | `E` declarations withdrawn / latent defects / files changed | 92 / 44 / 739 | **92 / 44 / 739** (unchanged) |
| 03 | files changed | 709 | **712** (+3) |
| 03 | declarations hoisted | 220 | **222** (+2) |
| 03 | divergent declaration symbols | 639 | **638** (−1) |
| 03 | module headers | 19 | **19** |
| 04 | TUs | — | **1,615 → 705** |
| 04 | merged units / files absorbed | — | **244 / 1,154** |
| 04 | refusals typedef / macro / static | 29 / 35 / 17 | **29 / 35 / 17** (unchanged) |
| 05 | duplicate includes withdrawn | 1,578 | **1,596** (+18) |
| 05 | duplicate declarations withdrawn | 146 | **152** (+6) |
| 05 | member banners compressed | 1,158 | **1,154** (−4) |
| 06 | merged units | 247 | **244** (−3) |
| 06 | declarations demoted | 4 | **4** |
| 06 | late includes hoisted / seen | 248 / 282 | **268 / 305** |
| 07 | definitions given internal linkage | 135 | **135** |
| 07 | in-unit externs made `static` | 18 | **19** (+1) |
| 08 | units reordered / member blocks moved | 0 / 0 | **0 / 0** |
| 08 | units refused (preproc / file-scope static) | 59 / 70 | **59 / 70** |

**Reading of the movement.** The type-disagreement repair pass closed 89 shadow
entries; that is visible as stage 03's `divergent_declaration_symbols` 639 → 638
and two more declarations becoming hoistable, and it propagates to stage 05's
duplicate-include and duplicate-declaration counts. **Stage 04's merged-unit
count fell 247 → 244** — the repair made three previously-mergeable adjacencies
collide, or three units shrank below the merge floor. That is a *reduction* in
stage 04's yield, and it is the only number in the table moving in the
unhelpful direction.

### 1.2 Integrity, after regeneration

```
driver.py status                      stages 0..8 ALL current  (0 inputs changed)
                                      stage 99 stale on 860 (retired probe, not in the ladder)
check-addresses 0-1 1-2 2-3 3-4 4-5 5-6 6-7 7-8
                                      identical: True, count 2567 == 2567, only_in_a 0, only_in_b 0
                                      -- ALL EIGHT PAIRS
refactor test suite                   139 / 139 PASS
stage 07 tree  vs  stage 08 tree      diff -rq  -> NO DIFFERENCES, 1,739 files each
```

Stage 08 remains a **measured no-op at the file level**: its tree is byte-for-byte
stage 07's after regeneration at this HEAD, exactly as its own report claimed.

---

## 2. The ladder BUILT at HEAD — and stage 04 does NOT compile

Nine app builds were run with the repository's own entry point, one per stage
plus the in-tree base, each into its own clean directory:

```
./recon/application/build_cohesive.sh app /private/tmp/g1-cons-base
./recon/refactor/stage_NN_*/tree/recon/application/build_cohesive.sh app /private/tmp/g1-cons-sNN
```

### 2.1 **STAGE 04 FAILS TO COMPILE at HEAD `e7f35727`.** This is new.

```
recon/symbolized/app/lib/g1_lib_03.c:659:14: error: conflicting types for
    'z_device_is_ready'; have '_Bool(const struct device *)'
  note: previous declaration of 'z_device_is_ready' with type
    '_Bool(const struct device *)'                       <- line 580
recon/symbolized/app/lib/g1_lib_03.c:845:14: error: conflicting types ... (same)
FATAL ERROR: command exited with status 1
```

**The two "conflicting" declarations are character-for-character identical.**
Three members of the merged unit `lib/g1_lib_03.c` each carry

```c
extern _Bool z_device_is_ready(const struct device *);
```

and **no file-scope declaration of `struct device` exists anywhere in the unit**.
GCC says so on the line above each error:

```
659:45: warning: 'struct device' declared inside parameter list will not be
        visible outside of this definition or declaration
```

A struct tag whose first appearance is inside a parameter list has
**parameter-list scope**. Each of the three declarations therefore introduces
its *own* incomplete `struct device`, the three prototypes have three
incompatible types, and the second and third are rejected.

**Triage, per README C4.**

* **(a) transformer bug — this one.** Stage 04's `type` refusal rule compares
  declaration **text**. Identical text does not imply identical type: it is
  exactly the C7c failure shape in a new dress, and this is its **fifth**
  occurrence in the project. The rule is sound for every symbol whose parameter
  types are complete at file scope and silently wrong for any that names a tag
  the unit never declares.
* **(b) latent reconstruction defect, exposed in the same unit.** The third
  member defines its own `struct device_raw { … }` and calls
  `z_device_is_ready(device)` with a `const struct device_raw *`
  (`-Wincompatible-pointer-types` at line 852); the first member passes
  `(const void *)&rodata_87bf0`, the second `(const void *)flash_device`. Three
  members, three different notions of what that argument is. The compiler found
  it because a merge finally put them in one TU — the same mechanism that found
  the frozen-clock defect at the Stage 04 gate.

**No transformer was being edited while this ran** (`ls -lT` on
`recon/refactor/transforms/*` and `recon/refactor/*.py`: newest mtime
12:21:29, every build started after 14:20), so the second-writer explanation
that applied to the stage04b pass does not apply here. The failure is real and
reproducible.

### 2.2 What this refutes

`our_boot_bringup.md` §44.9 item 6 says the stage ladder was not re-gated, and
justifies reusing the stage captures like this:

> stages 04-B/05/06/07 build from inputs whose payload is byte-identical to the
> ones the phase-tolerant pass measured, and that pass's captures are therefore
> still current. **I did not verify this by rebuilding a stage** — it is an
> inference from the base payload identity, and it is stated as one.

**The inference is false at this HEAD.** Base payload identity does not imply
stage payload identity, because the transformers' *inputs* moved even where the
base's *output* did not: stage 04's merged-unit count moved 247 → 244 (§1.1) and
its tree no longer compiles. An honestly-labelled inference turned out to be
wrong, which is the value of labelling it.

### 2.3 The repair, as a transformer change (never a hand-patch)

`recon/refactor/transforms/t04_cohesive_tu.py` gained
`incomplete_tag_forwards()` + `blank_attributes()`, and `render()` now emits, in
the merged unit's preamble, a **file-scope forward declaration for every
`struct`/`union` tag the unit names**:

```c
/* File-scope forward declarations for every struct/union tag this unit names.
 * Without them a tag whose only appearance in a member is inside a parameter
 * list has PARAMETER-LIST scope, so two textually IDENTICAL declarations in two
 * members declare two different incomplete types and the second is a
 * conflicting redeclaration (C11 6.2.1p7).  Incomplete-type forward
 * declarations emit no code. */
struct device;
```

Design decisions, and why:

* **Emitting is unconditional**, not conditional on "is this tag already
  declared?" A conditional form has to reason about ORDER (a member that names
  the tag *before* the member that defines it is still broken) and about scope
  (a function-local `struct X { … }` is not a file-scope declaration). Each is a
  place for the rule to silently stop covering something. A repeated or
  redundant forward declaration of an incomplete struct is valid C and emits no
  code, so the unconditional form is sound and cheaper to audit.
* **The rule keys on a structural property** — "the unit names this tag" — not
  on a list of tag names (C7c).
* **`__attribute__((…))` is blanked by counting parentheses**, not by a regular
  expression. The corpus writes `struct __attribute__((packed))
  user_settings_record` (3 sites), and a scanner that takes the token after
  `struct` would have read `__attribute__` as the tag. The nesting is arbitrary
  (`__attribute__((__aligned__(4)))`). *This was caught by a test I wrote before
  looking at the corpus, then confirmed against it.*
* `enum` is deliberately **not** forward-declared: `enum E;` is invalid ISO C.

**Measured after regeneration:** **207 forward declarations across 107 of the
249 merged units** (counted inside the generated block, at the closing input
generation).  *Correcting my own earlier figure in this document: an initial
`grep '^struct \|^union '` gave "341 across 100 units", but that expression also
counts every pre-existing file-scope `struct`/`union` line in the members.  The
block-accurate count is 207 / 107.* `check-addresses` 3-4, 4-5, 5-6, 6-7, 7-8 all identical at
**2,567**. Refactor suite **145/145** (6 new tests:
`IncompleteTagForwardsTest`).

---

## 4. The three criterion improvements — method

All three were measured **without Renode**. Every raw capture from the
stage04b and phase-tolerant passes survives in `/private/tmp` (`g1_ship_seed_q1`,
`g1_ship_seed_dash_d1`, `g1_s4b_base_nav1`, `g1_s4b_base_dash`,
`g1_s4b_s03_nav1`, `g1_s4b_s04_nav1/nav2/dash`, `g1_pt_s07_nav1/nav2/dash`), and
`build_display_sensor_oracle.py` is a pure function of a capture directory. So
the oracle can be **re-derived at any burst-gap threshold** from the traces
already on disk, and the comparer re-run over the result.

**Fidelity check first.** A copy of the builder with `BURST_GAP_NS` read from
the environment, run at the default 5 ms over `g1_ship_seed_q1`, reproduces
`/private/tmp/g1-pt/rep_ship_nav/display_sensor_oracle.json` with **0 of 546
fields changed** (the 4 fields present only in the committed file are the
`images/cpuapp|cpunet` `file`/`sha256` provenance pair). The re-derivation is
therefore the same measurement, not a similar one.

`recon/emulator/scripts/` belongs to the concurrent agent, so **nothing there
was edited**. The variants live in `recon/refactor/criterion_probe.py` (§8) and
their working copies in this pass's scratch.

---

## 5. The burst-gap threshold — measured, and it CHANGES THE LADDER'S VERDICT

`our_boot_bringup.md` §44.3.4 swept the threshold on **navigation only** and
concluded `spim_a` navigation "passes cleanly at T = 2.580 ms". This pass swept
28 thresholds on **both stimuli**, re-deriving Δ at each.

### 5.1 The sweep (shipped vs the in-tree base, Δ held at the published 145.440 ms)

| T (ms) | Δ **re-derived** | navigation failures | dashboard failures |
|---:|---:|---|---|
| 0.020 | 145.440 | `spim_a` P1×2 P2×1; `npm1300` P1×5 P0×1 | `spim_a` P5×1; `npm1300` P1×5 P0×1 |
| 0.100 | **10,815.160** | `npm1300` P1×3; `lsm6dso` P1×2 | `spim_a` P5×1; `npm1300` P1×2 P0×1 P2×2; `lsm6dso` P1×2 |
| 0.500 | **10,815.160** | `npm1300` P1×3 P2×3 | `spim_a` P5×1; `npm1300` P1×2 P2×1 |
| 0.600 / 0.650 | **10,815.160** | `npm1300` P1×3 P2×3 | `spim_a` P5×1; `npm1300` P1×2 P2×1 |
| **0.700** | **145.440** | `npm1300` **P2×3** | `spim_a` **P5×1** |
| 0.750 | 145.440 | `npm1300` P2×3; **`opt3001` P1×1 P0×1 P2×1** | `spim_a` P5×1 |
| **0.790** | **145.440** | `npm1300` **P2×3** | `spim_a` **P5×1** |
| **0.800** | **145.440** | `npm1300` **P2×3** | `spim_a` **P5×1** |
| 0.850 … 0.950 | 145.440 | `npm1300` P1×3 P2×3 | `spim_a` P5×1; `npm1300` P1×3 |
| 1.100 | 145.440 | `npm1300` P1×3 P2×3; `st25dv_sys` P1×2 P0×1 | + `st25dv_sys` P1×2 P0×1 |
| 2.300 | 145.440 | `npm1300` P2×3 | `spim_a` P1×3 P5×1 |
| 2.400 / 2.500 / **2.580** | 145.440 | `npm1300` **P3×1 P5×1** | `spim_a` P1×3; `npm1300` P2×3 |
| **5.000 (published)** | 145.440 | **`spim_a` P1×2 P2×1; `npm1300` P3×1 P5×1** | **`spim_a` P1×1 P2×1; `npm1300` P2×3** |
| 6.000 | **10,802.600** | `spim_a` P1×2 P2×1; `npm1300` P1×2 P3×1 P2×1 P5×1 | `spim_a` P1×1 P2×1; `npm1300` P1×2 P2×4 |
| 8.000 | 145.440 | `spim_a` P1×2 P2×1; `npm1300` P3×1 P5×1 | `spim_a` P1×1 P2×1; `npm1300` P2×3 |
| 10.000 | 145.440 | `spim_a` P1×2 P2×1; `npm1300` P2×3 | `spim_a` P1×7 P2×1; `npm1300` P3×2 P5×1 |

**Two corrections to §44.3.4.**

1. **T = 2.580 ms is not the answer.** It is clean on navigation, as §44.3.4
   measured — but on the **dashboard** it *introduces* `spim_a` `P1 content ×3`.
   §44.3.4's sweep never ran the dashboard.
2. The cleanest thresholds are **0.700, 0.790 and 0.800 ms**, where the base
   fails exactly one stream per stimulus, and — decisively — **Δ re-derives to
   exactly 145.440 ms, the published bound, unchanged.**

### 5.2 What is left failing at T = 0.790 ms, and whether it is real

```
navigation  twim1 npm1300   P2 population 5 -> 6   extra burst at 18.827820 s
                            P2 population 145 -> 144 missing at 19.054650 s
                            P2 population 10 -> 9    missing at 17.573143 s
dashboard   spim_a          P5 order: two bursts 146.570 ms apart swapped
```

The navigation three are **exactly** the failures §44.3.4 predicted at
T = 0.790 ms, and §43.9/§43.10 already root-caused them to the +3.45 ms boot
lateness at the 20 s observation wall. They are a **genuine residue**, correctly
reported. The dashboard one is an order inversion **1.130 ms above the bound**
(146.570 vs 145.440) — i.e. the base sits on the bound's knife-edge here too,
which is what "the bound is not rounded up" buys.

### 5.3 The decisive measurement — the ladder, re-gated at each threshold

| stage | stimulus | **T = 5.000 ms (published)** | **T = 0.790 ms** |
|---|---|---|---|
| 03 | nav | 0 REG, 0 PEW | 0 REG, 0 PEW |
| **04-B** | nav ×2 | 0 REG, **2 PEW** | **1 REGRESSION** (`spim_a` P3×24), 1 improvement (`npm1300`) |
| 04-B | dash | 0 REG, 0 PEW | 0 REG, 0 PEW |
| **07** | nav ×2 | 0 REG, **2 PEW** | **1 REGRESSION** (`spim_a` P3×22 + P2×1), 1 PEW |
| 07 | dash | 0 REG, 0 PEW | **1 REGRESSION** (`npm1300`) |

And the number that drives it, `spim_a` navigation, shipped vs each image:

| image | `spim_a` nav peak displacement | verdict at T = 5.000 | verdict at T = 0.790 |
|---|---:|---|---|
| in-tree base | **145.440 ms** | FAIL `{P1 content: 2, P2 population: 1}` | **PASS** |
| stage 03 | **145.380 ms** | FAIL `{P1 content: 2, P2 population: 1}` | **PASS** |
| stage 04-B | **245.780 ms** | FAIL `{P1×2, P3×22, P2×1}` | **FAIL `{P3 phase: 24}`** |
| stage 07 | **281.670 ms** | FAIL `{P1×2, P3×22, P2×1}` | **FAIL `{P3: 22, P2: 1}`** |

> **The published criterion scored stages 04-B/05/06/07 as "PASS on every gated
> stream, 0 regressions" only because the BASE was failing the same stream for
> an unrelated segmentation reason.** Remove the segmentation artifact — without
> touching Δ, which re-derives to the same 145.440 ms — and the stage's 22–24
> `P3 phase` failures on `spim_a` become what they are: a **regression**.

This is **robust across the whole clean band**: at T = 0.700, 0.790, 0.800 and
2.300 ms the verdict is the same (`spim_a` navigation REGRESSION on 04-B and
07). Only the published 5.000 ms hides it.

**Which ambiguity rule the counts come from.** The P3 burst counts above are
with the §6 equal-population rule ON. With the shipped rule they are 22 (stage
04-B) and 21 + one `P2 population` (stage 07). *The verdict — REGRESSION — is
identical under both rules at every threshold in the band;* only the count of
failing bursts moves, which is the signature of a strengthening.

The peak-|δ| numbers themselves were already published — the criterion report's
"What is not phase, and is charged" paragraph states 145.440 → 245.780 →
281.670 ms. **What was wrong was the bucket, not the measurement.** It was
booked as *pre-existing-but-worse* rather than *regression* because the
comparer's `worse_than()` compares fail-profile CATEGORIES, and the base already
had a non-empty profile on that stream.

### 5.4 Verdict on this improvement — measured, and NOT applied to the shared script

**The measurement is decisive; the constant is not.** Reasons not to hard-code
0.790 ms into `phase_tolerant_compare.py` / `build_display_sensor_oracle.py` in
this pass:

* The clean band is **non-monotonic**: T = 0.750 ms sits *between* two clean
  thresholds and introduces an `opt3001` `P0 segmentation`. A criterion constant
  standing on a non-monotonic knife-edge is C7c wearing a different hat.
* A structural derivation was attempted and does **not** select a workable
  value. Counting *composite* trains (a train key that is the concatenation of
  two other train keys — the arithmetic §44.3.1/§44.3.2 used, `141 = 108+1+32`
  and `308,735 = 719+1+308,015`) minimises at T ≈ 0.100 ms, where Δ explodes to
  10,815.160 ms. Composites never reach zero anywhere usable: `npm1300` carries
  2 on **both** the shipped and our captures at every T from 0.500 to 10 ms.
* Those files belong to the concurrent agent (§4).

**What must change regardless of the constant** is the README's published
verdict for stages 04-B/05/06/07, because it is true only at one threshold and
false at every other threshold that leaves Δ unchanged. §10 does that.

---

## 6. The ambiguity rule (§8 item 7) — "closable at zero cost" is **FALSE** as stated

`our_boot_bringup.md` §44.7.1 argues that when two trains have **equal burst
populations**, `starts_ns` is sorted on both sides, so `i ↔ i` is the unique
order-preserving bijection and the ambiguity exclusion carries no information.
The argument is correct. Its conclusion — *"Dropping the exclusion on this
stream closes the hole and changes no verdict on any image measured… the next
pass can land it in one step"* — is not, and §44.7.1 measured only
`twim2 lsm6dso`.

**Implemented and measured** (`G1_EQUAL_POP_RULE=1`: drop the exclusion when
`len(starts_ours) == len(starts_shipped)`, retain it otherwise, since an unequal
population makes the common-prefix pairing a genuine choice):

```
Δ derivation, shipped vs in-tree base, both stimuli, at the SHIPPED 5 ms gap
  ORIGINAL rule            DERIVED PHASE BOUND = 145.440 ms
  EQUAL-POPULATION rule    DERIVED PHASE BOUND = 7,498.630 ms
```

The blow-up comes from `twim1 npm1300` navigation, from a train with **n = 6 on
both sides** — equal populations — whose `max|δ|` is 7,498.630 ms. §44.7.1
attributed the multi-second `npm1300`/`spim_a` values to "the segmentation
artifact" and expected the equal-population guard to exclude them. It does not:
the §44.3.1 train-membership swap moves one burst between two trains **while
both keep their populations (9 and 6)**. `i ↔ i` really is the unique
order-preserving bijection there — it is the *train assignment* that is wrong,
not the correspondence.

> **Landing §44.7.1's change "in one step" at the shipped 5 ms burst gap would
> have moved Δ from 145.440 ms to 7,498.630 ms — a 51× widening that gates
> essentially nothing.** Correcting my predecessor's claim: it is not zero-cost,
> and the cost is invisible if you measure it on `twim2 lsm6dso` alone.

### 6.1 It becomes free once the segmentation is fixed — the two changes are COUPLED

| burst gap | Δ, ORIGINAL rule | Δ, EQUAL-POPULATION rule |
|---:|---:|---:|
| 0.700 ms | 145.440 | **145.440** |
| **0.790 ms** | 145.440 | **145.440** |
| 0.800 ms | 145.440 | **145.440** |
| 2.300 ms | 145.440 | **145.440** |
| 2.400 ms | 145.440 | 7,498.630 |
| 5.000 ms | 145.440 | **7,498.630** |

At any threshold in the clean band the rule is genuinely free — **Δ re-derives
to 145.440 ms unchanged** — and it does what §8 item 7 asked. Measured on the
base at T = 0.790 ms, `twim2 lsm6dso`:

```
ORIGINAL rule    navigation  PASS/INDETERMINATE-PHASE  max|d|=10.620 ms  200 of 548 bursts excluded
                 dashboard   PASS/INDETERMINATE-PHASE  max|d|=13.670 ms  200 of 546 bursts excluded
EQUAL-POP rule   navigation  PASS                      max|d|=10.620 ms  0 excluded
                 dashboard   PASS                      max|d|=13.670 ms  0 excluded
```

`max|δ|` is **identical** either way — the excluded bursts never carried a
larger displacement — and both values sit inside Δ by an order of magnitude.
The largest stream in the oracle stops being phase-gated only in part.

**Ladder effect: none.** At T = 0.790 ms the rule changes only the *counts*
(`spim_a` stage 04-B `P3 phase` 22 → 24, stage 07 21 → 22, stage 03 `npm1300`
P3 1 → 3) and flips **no stage's verdict** at either threshold. That is the
correct signature for a strengthening: it makes an existing failure bigger and
creates no new pass.

### 6.2 A vacuous assertion found while doing this

`build_display_sensor_oracle.py` publishes, per device,

```python
"separated": (max_intra is None or min_inter is None
              or (max_intra <= BURST_GAP_NS < min_inter)),
```

advertised as the per-capture bimodality check that makes a mis-segmenting
capture "reported rather than silently mis-segmented". But `split_bursts`
*defines* `max_intra` as the largest gap `<= gap_ns` and `min_inter` as the
smallest gap `> gap_ns`. **The predicate is therefore true by construction, for
every capture and every threshold.** Measured: `separated` is `True` for all six
devices on all four reference captures at T = 0.020 ms through 10.000 ms
inclusive — including thresholds that demonstrably mis-segment.

This is the C7c family again — a gate that cannot fail. It belongs to the
concurrent agent's file, so it is **reported, not edited**. A test that would
bite: assert the gap histogram has a *void* around the threshold, e.g.
`min_inter / max_intra >= K` for a declared `K`, which is falsifiable.

---

## 7. The `RADIO_TX` component field — APPLIED, and it costs nothing

`our_boot_bringup.md` §44.4 proved `RADIO_TX = ESB_MASTER_FRAMES +
BLE_link_layer_TX` exactly, from four instrumented captures, and named the
missing field. It declined to add it because "it changes the oracle's field
set, which is a criterion change".

**No capture and no oracle change are needed.** The oracle already publishes
both `counters/RADIO_TX` and `counters/ESB_MASTER_FRAMES`, so the component is
arithmetic on fields that already exist:

```
BLE_link_TX  :=  RADIO_TX  -  ESB_MASTER_FRAMES
```

Evaluated over the committed report directories of the two prior passes — no
Renode, no new field, no re-derivation of Δ (`RADIO_TX` is a counter and sits
outside the phase criterion entirely, §8 item 7 of the criterion report):

| stimulus | image | `RADIO_TX` | **ESB** | **BLE** |
|---|---|---:|---:|---:|
| navigation | **shipped** | 562 | **373** | **189** |
| navigation | in-tree base | 562 | 374 ✗ | 188 ✗ |
| navigation | stage 03 | 562 | 374 ✗ | 188 ✗ |
| navigation | stage 04-B (×2 runs) | 564 | 374 ✗ | 190 ✗ |
| navigation | stage 07 (×2 runs) | 560 | **373 ✓** | 187 ✗ |
| dashboard | **shipped** | 562 | **373** | **189** |
| dashboard | in-tree base | 562 | 374 ✗ | 188 ✗ |
| dashboard | stage 04-B | 565 | 374 ✗ | 191 ✗ |
| dashboard | stage 07 | 561 | **373 ✓** | 188 ✗ |

This reproduces §44.4's instrumented navigation table **exactly** (562/373/189,
562/374/188, 564/374/190, 560/373/187) from ordinary oracle fields, and extends
it to the dashboard, which §44.4 did not measure.

**What it changes, stated as verdicts:**

1. **The in-tree base does NOT hold `RADIO_TX`.** Every record since §43.11 has
   listed `RADIO_TX 0x232` as a criterion our base meets. It is `374 + 188`
   against shipped's `373 + 189` — **both halves wrong by one, in opposite
   directions**. Under the component field the base fails **two** fields on both
   stimuli. That is a strictly harder bar, adopted here.
2. **Stage 04-B's `RADIO_TX` "regression" is not a regression.** `ESB` 374 → 374
   (unchanged, still wrong), `BLE` 188 → 190 (still wrong by one — *magnitude*
   unchanged on ESB, |δ| 1 → 1 on BLE with the sign flipped). Under the summed
   counter it read `0x232 → 0x234`, an unambiguous-looking +2.
3. **Stage 07 CLOSES the ESB half outright** — `ESB 373 == shipped` on both
   stimuli — and worsens the BLE half from |δ| 1 to |δ| 2 (navigation) while
   leaving it at |δ| 1 (dashboard). Under the summed counter this read as
   `0x232 → 0x230`, a regression on a criterion the base "passed".

> A single summed counter scored the base EQ while both of its components were
> wrong, and scored the stage that **fixed one component** as a regression.
> This is the sharpest example in the project of C7c's cousin: **a gate on a
> derived aggregate is a gate that can pass for the wrong reason.**

The component is implemented in `recon/refactor/criterion_probe.py` (§8) with
tests, so it can be recomputed from any pair of oracle JSONs.

---

## 3. Size gates — stage 08's was missing; so were stages 00–03's

`our_boot_bringup.md` §44.9 item 7 records "Stage 08 still has no
`SIZE_GATE.json`". It was worse than that: **only stages 04, 05, 06 and 07 had
one.** Every stage now has its class measured against its own predecessor's
build (`driver.py size-gate N <build N-1> <build N>`), not against the in-tree
build.

| stage | declared | **measured** | `zephyr.bin` | allocatable deltas |
|---|---|---|---:|---|
| 01 | `byte-identical` | see §3.1 | 956,356 B | vs stage 00 |
| 02 | `byte-identical` | **`byte-identical`** | 956,356 B | all 0 |
| 03 | `byte-identical` | **`byte-identical`** | 956,356 B | all 0 |
| 04 | `size-changing` | **`size-changing`** | 956,276 B | `text` **−76** |
| 05 | `size-neutral` | **`byte-identical`** (better than declared) | 956,276 B | all 0 |
| 06 | `byte-identical` | **`byte-identical`** | 956,276 B | all 0 |
| 07 | `size-changing` | **`size-changing`** | 955,996 B | `text` **−276**, `rodata` **−8** |
| **08** | `size-changing` | **`byte-identical`** (better than declared) | 955,996 B | `text/rodata/datas/bss/noinit` all **0**, 28 == 28 allocatable sections |

**`recon/refactor/stage_08_call_order/SIZE_GATE.json` now exists**, records
`"pass": true`, `"image_byte_identical": true`, `"oracle_required": false` with
the reason *"Linked size did not move; every previously captured behavioural
measurement carries over by construction, not by argument."* That is the right
outcome for a stage whose tree is byte-for-byte its predecessor's, and it is now
a measurement in the stage directory instead of a claim in a report.

### 3.1 The image ladder, re-measured at HEAD

| image | `zephyr.bin` | `text` | `runtime_info_sync` | `cmp` chain |
|---|---:|---:|---|---|
| in-tree base | **956,496** | **492,696** | `0x00015c04` | — |
| stage 01 | 956,356 | 492,688 | `0x00015c04` | differs from base |
| stage 02 | 956,356 | 492,688 | `0x00015c04` | **== stage 01** |
| stage 03 | 956,356 | 492,688 | `0x00015c04` | **== stage 02** |
| stage 04-B | 956,276 | 492,612 | `0x00016c14` | differs from 03 |
| stage 05 | 956,276 | 492,612 | `0x00016c14` | **== stage 04** |
| stage 06 | 956,276 | 492,612 | `0x00016c14` | **== stage 05** |
| stage 07 | 955,996 | 492,336 | `0x00016c14` | differs from 06 |
| stage 08 | 955,996 | 492,336 | `0x00016c14` | **== stage 07** |

The three-image structure the earlier records describe (01=02=03, 04=05=06,
07=08) **reproduces exactly at HEAD**, and `$rtinfo_pc` still takes only two
distinct values across the eight stages.

### 3.2 **THE PAYLOAD IDENTITY HAS BROKEN. Half the existing captures are INVALID.**

Iteration 44 §44.1 established that the in-tree `zephyr.bin` had been
byte-identical across several repair passes, and §44.9 item 6 leaned on that to
carry every stage capture forward without rebuilding. **Re-measured here, it no
longer holds.**

```
cmp  g1-cons-base/zephyr/zephyr.bin   g1-i44-base/zephyr/zephyr.bin      -> DIFFER
cmp -n 957072  g1-cons-base/zephyr/app_update.bin  g1-i44-base/...       -> differ at char 13
zephyr.bin   956,480 B  ->  956,496 B                                    (+16 B)
size -A      text 492,692 -> 492,696                                     (+4 B)
             every other allocatable section delta 0; the rest is .debug_*
nm           runtime_info_sync 0x00015c04, _end 0x2003ff45               (both UNMOVED)
```

The commit at HEAD is titled *"…zephyr.bin BYTE-IDENTICAL"*, and its own final
build directory `/private/tmp/g1-td4-final` is 956,480 B. **The tree that got
committed is not the tree that build measured**: `ls -lT` shows the app sources
last written at **14:17:18**, five minutes *after* the 14:12:00 commit and two
minutes before my build, while `git status` reports them clean. So the claim was
true of the build it was made on and is not true of HEAD.

**Which existing captures survive, measured by `cmp` against the images the
earlier passes actually booted:**

| stage image | vs prior pass's build | captures |
|---|---|---|
| stage 01 (= 02 = 03) | `cmp` **IDENTICAL** to `g1-pt-s01`; stage 03 `cmp` **IDENTICAL** to `g1-s4b-s03` | **STILL VALID** |
| stage 04-B (= 05 = 06) | **DIFFERS** from `g1-s4b-s04` (same 956,276 B, different bytes) | **INVALID** |
| stage 07 (= 08) | **DIFFERS** from `g1-pt-s07` (same 955,996 B, different bytes) | **INVALID** |
| **in-tree base** | **DIFFERS** from `g1-i44-base` / `g1-s4b-base` | **INVALID** — and this is the reference every three-way comparison uses |

The forward declarations §2.3 adds are incomplete-type declarations that emit no
code, and the pre-fix and post-fix builds of stages 05–08 report identical FLASH
(956,276 / 956,276 / 955,996 / 955,996 B), so the byte differences are
attributable to the upstream repair passes rather than to my transformer change.
**I cannot prove that by `cmp`**, because the pre-fix stage 04 tree does not
compile at all and its 05–08 build directories were overwritten by the rebuild.
Stated as an attribution, not a measurement.

> **Consequence: at HEAD `e7f35727` the ladder has NO valid behavioural evidence
> from stage 04 onward, and no valid base reference at all.** Renode is held by
> the concurrent agent for this pass, so the captures could not be retaken. Every
> R7 verdict in §9 for stages 04–08 is therefore reported as **carried from the
> phase-tolerant pass's images, which are no longer the images the tree
> produces.** That is a weaker claim than any previous report has made, and it is
> the correct one.

### 3.3 The build IS deterministic — and stage 00 is faithful to ITS inputs

A first reading of the base rebuild said "not reproducible". **That was wrong,
and here is the measurement that corrects it:**

```
g1-cons-base   (14:19)   956,496 B
g1-cons-base2  (15:2x)   956,496 B   cmp vs base   -> differ  (389 bytes)
g1-cons-base3  (15:4x)   956,496 B   cmp vs base2  -> IDENTICAL
```

Two builds with no input movement between them are byte-identical. The
base↔base2 difference is the concurrent agent's landing — `driver.py status`
names it precisely: **stage 00 stale on 50 inputs**, all
`recon/symbolized/app/*.c`.

**And the snapshot mechanism itself is validated, by the controlled test the
README specifies.** Regenerating stage 00 at the *current* inputs and building
both:

```
g1-cons-s00b  (stage 00 tree, current inputs)   956,496 B
g1-cons-base4 (in-tree,       current inputs)   956,496 B
cmp                                             -> IDENTICAL
```

**At one input generation, stage 00's tree builds byte-identically to the live
repository.** The `FORCE_REAL_DIRS` / symlink mechanism is sound; the earlier
956,480-vs-956,496 gap was two different input generations, nothing else.

And the snapshot stage is faithful to the input set it captured:

```
cmp  g1-cons-s00/zephyr/zephyr.bin  g1-i44-base/zephyr/zephyr.bin    -> IDENTICAL
cmp  g1-cons-s00/zephyr/zephyr.bin  g1-s4b-base/zephyr/zephyr.bin    -> IDENTICAL
cmp  g1-cons-s00/zephyr/zephyr.bin  g1-td4-final/zephyr/zephyr.bin   -> IDENTICAL
                                                    all three at 956,480 B
```

**Stage 00's image is byte-identical to the base image of all three preceding
passes.** So iteration 44's payload-identity claim was true *for the inputs it
measured*, and §3.2's finding is narrower than it first looked: it is not that
the payload drifted under those passes, it is that **a further change landed
after them**, worth `text` +4 B / `zephyr.bin` +16 B, and it is in HEAD.

The consequence for capture validity in §3.2 is unchanged, because the stage
04-B and stage 07 images this tree now produces still differ byte-for-byte from
the ones the earlier passes booted.

### 3.4 A size gate that had never been run — and stage 01's declared class was WRONG

Running `size-gate 1` for the first time (base = **stage 00's** build, not the
in-tree build — the class is declared against the stage's own predecessor):

```
declared_codegen_class   byte-identical
measured_codegen_class   size-changing        text -4 B,  rodata -124 B
pass                     FALSE
```

Stage 01 withdraws **100 backing `.rodata` objects worth 3,997 B**, retires 100
`PROVIDE` pins and deletes 100 `extern` declarations. It cannot be
byte-identical, its own harvest says so, and it has been declared
`byte-identical` since it was written **because no size gate was ever run for
it.** C7b added the mechanism after stage 04; nobody went back.

`driver.STAGES` row 1 is corrected to **`size-changing`**, with the reason in
the row itself. `size-gate 1` then passes as declared, and records
`"oracle_required": true`.

**The behavioural obligation happens to be discharged for this image** — the
phase-tolerant pass captured stages 01/02/03, and §3.2 measured stage 01's image
`cmp`-identical to the one it booted — **but it was discharged by accident, not
by the declaration.** Had stage 01 ever changed size differently, nothing would
have asked for a capture.

`test_size_gate.Registry` caught the manifest lagging the corrected row
immediately, which is the mechanism working.

### 3.5 Idempotence, re-verified after every change in this pass

```
stage trees 01..08, hashed file-by-file (content + symlink targets), then
`materialize 1..8` re-run and re-hashed:
                                    ALL EIGHT TREES BYTE-IDEMPOTENT
check-addresses 0-1 … 7-8           identical, 2,567 == 2,567, all eight pairs
refactor test suite                 157 / 157 PASS  (139 at the start of this
                                    pass; +6 IncompleteTagForwardsTest,
                                    +12 test_criterion_probe)
```

---

## 8. `recon/refactor/criterion_probe.py` — what this pass shipped

The measured criterion work lives in **`recon/refactor/criterion_probe.py`**
(and `recon/refactor/test_criterion_probe.py`, 12 tests), not in the emulator
scripts, because those belong to the concurrent agent (§4).

* `radio_tx_components(oracle)` → `{RADIO_TX, ESB_MASTER_FRAMES, BLE_link_TX}`.
  **ADOPTED** — it needs no capture and no oracle field.
* `compare_radio_tx(shipped, ours)` → per-component verdict plus a
  `"cancellation"` flag that fires exactly when the SUM agrees while both
  components disagree. Pinned by
  `test_THE_CANCELLATION_the_base_sum_agrees_while_both_halves_are_wrong`.
* `measurable_mask(..., equal_population_rule=)` — the §6 ambiguity rule,
  **implemented and off by default**, with a test asserting that the
  unequal-population half of the exclusion is *retained* (dropping that half is
  what moves the bound to 7,498.630 ms).
* CLI: `criterion_probe.py radio-tx SHIPPED.json OURS.json …`, exit 1 when any
  component differs.

The burst-gap sweep is a measurement over 28 thresholds × 11 capture
directories; it is reproduced in §10 rather than shipped as a tool, because
this pass does **not** recommend adopting a constant (§5.4).

---

## 9. THE CONSOLIDATED VERDICT — one table, one baseline

Read the columns as: **class** = declared → measured (`SIZE_GATE.json`, this
pass); **strict** = the wall-anchored `cmp3` verdict from the pass that captured
that image; **phase (5 ms)** = the published phase-tolerant verdict; **phase
(corrected)** = the same criterion with the segmentation artifact removed
(§5.3), Δ **unchanged at 145.440 ms**.

| # | transforms | class declared → measured | strict `cmp3` | phase, 5 ms | **phase, corrected** | outstanding |
|---|---|---|---|---|---|---|
| **00** | verbatim snapshot | `byte-identical` → *(identity; image `cmp`-identical to three prior passes' base)* | n/a | n/a | n/a | stale on 50 inputs at close of pass |
| **01** | 100 rodata string literals inlined, 192 sites, backing object + `PROVIDE` pin + `extern` withdrawn | ~~`byte-identical`~~ → **`size-changing`** (`text` −4, `rodata` −124) | **0 regressions** | **PASS** | **PASS** | class was WRONG and ungated until this pass (§3.4); oracle obligation discharged only by accident |
| **02** | 3,116 volatile-accessor spellings; 45 noreturn, 367 log-route, 139 assert sites; 92 declarations withdrawn | `byte-identical` → **`byte-identical`** | **0 regressions** | **PASS** | **PASS** | 44 latent defects found and filed, not repaired |
| **03** | 1,621 sources into 22 module dirs; 19 module headers; 222 declarations hoisted | `byte-identical` → **`byte-identical`** | **0 regressions** | **PASS** | **PASS** | **638 divergent declaration symbols** still open (`DEFECTS.json`) — the stage-03b work |
| **04** | cohesive TU merge, sub-batch B: 1,615 → 705 TUs, 244 merged units, 1,154 files absorbed | `size-changing` → **`size-changing`** (`text` −76) | **8 regressions** nav, 1 dash | PASS (0 REG, 2 pre-existing-worse) | **FAIL — 1 REGRESSION**: `spim_a` navigation, 24 bursts over Δ, peak \|δ\| **245.780 ms** vs Δ 145.440 | oracle REQUIRED; **capture INVALID at HEAD** (§3.2). 454 of 705 TUs still single-source |
| **05** | composition: 1,596 duplicate includes, 152 duplicate declarations withdrawn, 1,154 banners | `size-neutral` → **`byte-identical`** (better) | inherits 04 | inherits 04 | **inherits 04's FAIL** | none of its own; sub-batch `S` opt-in, not applied |
| **06** | 4 module-header declarations demoted; 268 of 305 late includes hoisted | `byte-identical` → **`byte-identical`** | inherits 04 | inherits 04 | **inherits 04's FAIL** | none of its own |
| **07** | internal linkage from link evidence: 135 definitions `static`, 19 in-unit externs | `size-changing` → **`size-changing`** (`text` −276, `rodata` −8) | 9 regressions nav / 4 dash, **4 improvements each** | PASS (0 REG, 2 pre-existing-worse) | **FAIL — 1 REGRESSION**: `spim_a` navigation, 22 bursts, peak \|δ\| **281.670 ms**; a second on `twim1 npm1300` at some thresholds | oracle REQUIRED; **capture INVALID at HEAD**. 120 recovered functions provably dead |
| **08** | stable topological sort of member blocks, callee before caller | `size-changing` → **`byte-identical`** (better) | inherits 07 | inherits 07 | **inherits 07's FAIL** | **`SIZE_GATE.json` now written** (§3); 0 units reordered — 11 internal call edges in 244 units |

### 9.1 Counters, under the component field (§7)

| image | `ESB_MASTER_FRAMES` | `BLE_link_TX` | old summed verdict |
|---|---|---|---|
| shipped | 373 | 189 | — |
| in-tree base | **374 ✗** | **188 ✗** | recorded as **EQ** — a cancellation |
| stage 04-B | 374 ✗ | 190 ✗ | recorded as a regression `0x232→0x234` |
| stage 07 | **373 ✓** | 187 ✗ (nav) / 188 ✗ (dash) | recorded as a regression `0x232→0x230` |

### 9.2 Static ladder, at this pass's inputs

```
app builds 00..08                      9 of 9 exit 0  (stage 04 only AFTER the fix, section 2)
nm -u, all nine images                 0 / 0 / 0 / 0 / 0 / 0 / 0 / 0 / 0
duplicate GLOBAL definitions           0 on every image
check_ram_pin_collisions --core app    596 bound OK / 0 escaping / 0 unknown inside a live object
                                       (20 raw-literal pins outside the RAM region, 3 abs symbols
                                        not in the linker scripts -- both unchanged;
                                        bound pins 627 -> 596 since iteration 44, upstream)
check_thread_create_stack_args -t 120  10 / 10 PASS, exit 0
tools/verify_data.py                   995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)
refactor test suite                    157 / 157 PASS
driver.py check-addresses, 8 pairs     identical, 2,567
stage trees 01..08 idempotence         byte-idempotent, all eight
net core                               NOT BUILT AND NOT TOUCHED this pass -- see section 12
```

### 9.3 So: is the staged refactor defensible as production-grade work?

**Stages 00–03: yes.** Mechanically derived, byte-idempotent, address-set
identical, gated by a real build, and behaviourally validated against the
shipped binaries on an image this tree still produces. Stage 01's *declaration*
was wrong and is now corrected and gated.

**Stages 04–08: no, and less so than the README currently says.** Three separate
things have to be true and only the first is:

1. the transformation is mechanical, idempotent and address-preserving — **true,
   re-verified here**;
2. it passes the acceptance criterion — **false**: the phase-tolerant PASS
   depended on a segmentation artifact that was masking the damage, and at every
   threshold that leaves Δ unchanged the `spim_a` navigation train is a
   **regression** (§5.3);
3. the evidence corresponds to the tree — **false at HEAD**: the stage 04-B and
   stage 07 images this tree produces are not the images that were captured
   (§3.2).

**And stage 04 did not compile at all at HEAD until this pass fixed the
transformer** (§2), which no report would have caught, because no pass since
`stage04b` had rebuilt it.

---

## 10. Reproducing everything in this document

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

# --- 1. the ladder
for n in 0 1 2 3 4 5 6 7 8; do $V recon/refactor/driver.py materialize $n; done
$V recon/refactor/driver.py status
for a in 0 1 2 3 4 5 6 7; do $V recon/refactor/driver.py check-addresses $a $((a+1)); done
$V -m unittest discover -s recon/refactor -p 'test_*.py'          # 157/157

# --- 2. nine builds, each with the repository's own entry point
./recon/application/build_cohesive.sh app /private/tmp/g1-cons-base
for n in 00_snapshot 01_literal_inline 02_block_dedupe 03_module_structure \
         04_cohesive_tu 05_cohesive_composition 06_unit_composition \
         07_internal_linkage 08_call_order; do
  ./recon/refactor/stage_$n/tree/recon/application/build_cohesive.sh \
      app /private/tmp/g1-cons-s${n%%_*}
done

# --- 3. size gates: the base of stage N is stage N-1's build, never the in-tree build
$V recon/refactor/driver.py size-gate 1 /private/tmp/g1-cons-s00 /private/tmp/g1-cons-s01
$V recon/refactor/driver.py size-gate 8 /private/tmp/g1-cons-s07 /private/tmp/g1-cons-s08

# --- 4. RADIO_TX components -- no Renode, no oracle change
$V recon/refactor/criterion_probe.py radio-tx \
   /private/tmp/g1-pt/rep_ship_nav/display_sensor_oracle.json \
   /private/tmp/g1-pt/rep_base_nav1/display_sensor_oracle.json \
   /private/tmp/g1-pt/rep_s04_nav1/display_sensor_oracle.json \
   /private/tmp/g1-pt/rep_s07_nav1/display_sensor_oracle.json

# --- 5. the burst-gap sweep, from the RAW captures already on disk (no Renode)
#     a copy of build_display_sensor_oracle.py with BURST_GAP_NS read from the
#     environment; verified to reproduce the committed oracle at 5 ms with
#     0 of 546 fields changed.
sed 's/^BURST_GAP_NS = 5_000_000  /BURST_GAP_NS = int(__import__("os").environ.get("G1_BURST_GAP_NS", 5_000_000))  /' \
    recon/emulator/scripts/build_display_sensor_oracle.py > $S/bdso2.py
G1_BURST_GAP_NS=790000 $V $S/bdso2.py                     /private/tmp/g1_ship_seed_q1  $S/T790/ship_nav
G1_BURST_GAP_NS=790000 $V $S/bdso2.py --screen=dashboard  /private/tmp/g1_ship_seed_dash_d1 $S/T790/ship_dash
#   ... likewise g1_s4b_base_nav1, g1_s4b_base_dash, g1_s4b_s03_nav1,
#       g1_s4b_s04_nav1/nav2/dash, g1_pt_s07_nav1/nav2/dash
$V $S/ptc2.py derive-bound  $S/T790/ship_nav/...json $S/T790/base_nav/...json \
                            $S/T790/ship_dash/...json $S/T790/base_dash/...json
G1_EQUAL_POP_RULE=1 $V $S/ptc2.py compare --bound-ms=145.440 \
    <shipped> <base> <stage> LABEL
```

`ptc2.py` is `recon/emulator/scripts/phase_tolerant_compare.py` with the
equal-population rule of §6 added behind `G1_EQUAL_POP_RULE`; the same rule is
shipped, tested and off-by-default in `recon/refactor/criterion_probe.py`.

---

## 11. The remaining structural work — MEASURED, SPECIFIED, and deliberately NOT LANDED

### 11.1 The measurement

Stage 04's own verdict was that most units are still single-source and that it
merges by link-order adjacency. Re-measured at HEAD on stage 08's tree, using
stage 04's **own** analyser and **own** pairwise refusal rules:

```
retained app translation units                              705
  merged units                                              251
  single-source                                             454   (64.4 %)
intra-module call edges between DISTINCT retained TUs      1,216
  (stage 08 measured 11 call edges INSIDE the 244 merged units)
```

> **1,216 against 11.** The call structure is not missing — 99 % of it falls
> between units that stage 04 never considered merging, because they are not
> adjacent in the generated source list. The grouping really is the problem, and
> the ratio quantifies it.

Two groupings simulated under the unchanged refusal rules (first-fit greedy
inside each module directory, so both are lower bounds):

| grouping | groups | TUs absorbed | 705 → |
|---|---:|---:|---:|
| **call-cohesion** (merge only units joined by a call edge) | 75 | 100 | **605** |
| **no-adjacency ceiling** (any pairwise-clean units in a module) | 105 | 523 | **182** |

Dropping adjacency is worth **523 translation units** — more than four times
stage 04's entire remaining yield — and call-cohesion alone is worth 100.

### 11.2 The specification, ready to build

**Stage 09 `call_cohesion`**, input stage 08, app core only.

* **Grouping:** connected components of the intra-module call graph (`file A` →
  `file B` when A names a symbol B defines), restricted to one module directory,
  grown greedily and **checked pairwise against every member already in the
  group** with `t04.conflicts` — the same seven rules, unchanged.
* **Shape quarantine:** inherit stage 04's, unchanged (`#pragma`, absolute
  include, `.inc` fragment, `alias` attribute, multi-declaration line, the
  CMake-named `discovery_callback.c`, the five `-ffp-contract` float bodies).
* **Emission:** at the position of the **earliest** member in the generated
  source list, so archive-order disturbance is bounded exactly as stage 04
  bounds it; `render()` with the §2.3 forward-declaration block.
* **Build machinery in the same transaction (C6):**
  `recon/generated/app_retained_sources.cmake`, and the merged names must never
  match `rodata_*` (`g1_verified_rodata_keep.ld` matches on the object
  filename).
* **Declared class: `size-changing`, `oracle_required: true`.** A merge of this
  size cannot be size-neutral; stage 04's −76 B moved the OPT3001 train a whole
  100.5 ms slot.

### 11.3 Why it was NOT landed in this pass

Not for lack of a design or of measurements — both are above. Three reasons,
in order:

1. **The oracle is unavailable to me.** Renode is held by the concurrent agent
   for the whole of this pass. A stage declared `oracle_required` that is landed
   without a capture adds unprovable surface; the project already has two
   (stages 04 and 07) and §3.2 has just invalidated the evidence for both.
2. **The ladder it would sit on currently FAILS R7 from stage 04 onward**
   (§5.3, §9.3). Piling a 523-TU merge on top of a failing stage makes the
   eventual bisection strictly harder, which is the exact thing this pipeline's
   stage ordering exists to prevent.
3. **Stage 04 did not compile at HEAD** and had to be repaired first (§2). The
   budget this pass had for new construction went into that repair, its tests,
   and re-verifying the ladder around it — which was the stated first priority.

**I am not claiming an oracle I cannot run, and I am not claiming a stage I did
not build.** What is claimed is the measurement: 1,216 call edges, 454
single-source units, a 523-TU ceiling, all reproducible from
`recon/refactor/transforms/t04_cohesive_tu.py`'s own analyser.

---

## 12. What I did NOT do, and everything quarantined

**Not done, with the reason:**

1. **No Renode capture, at all.** The concurrent agent owns it for this pass.
   Every behavioural verdict here is either (a) recomputed from raw capture
   directories already on disk, or (b) carried from an earlier pass and
   **labelled invalid where the image no longer matches** (§3.2). No new
   behavioural claim is made.
2. **The burst-gap constant was NOT changed** in
   `recon/emulator/scripts/*` (§5.4) — the file is another agent's, the clean
   band is non-monotonic, and no structural derivation selects a value.
3. **The equal-population ambiguity rule was NOT switched on** in the shared
   comparer (§6) — it is unsafe at the shipped 5 ms gap and the two changes are
   coupled. It is shipped off-by-default and tested in `criterion_probe.py`.
4. **`gap_separation.separated` was NOT repaired** (§6.2) although it is proven
   vacuous — another agent's file.
5. **Stage 09 was NOT built** (§11.3).
6. **The net core was not built and not touched.** No net input moved.
   `check_net_raw_literals` and `verify_net_stock_data_window` need a net ELF and
   were **NOT RUN** — recorded as not-run, not as passed. The frozen net image
   (225,581 B) was not re-verified in this pass.
7. **`cfg_verify` was not run and is not cited.** Every number here comes from a
   build, a `cmp`, an ELF section table or symbol table, a JSON diff, or a
   re-derivation over an existing capture directory.
8. **The 638 divergent declaration symbols (stage 03 `DEFECTS.json`) were not
   repaired** — R1 makes that the parity agent's work — and the
   `z_device_is_ready` / `struct device_raw` disagreement §2.1 exposed was
   **reported, not fixed**, for the same reason.
9. **Stage 99** (the retired diagnostic probe) was left stale on 860 inputs, as
   every prior pass has.
10. **Nothing was committed.** The tree is left dirty.

**Quarantined, with measured reasons (stage 04, sub-batch B, at HEAD):**

```
shape_refusals                              30 files, 6 reasons
pairwise adjacencies blocked               862, over 7 rules
runs of length one                         309
clean runs not selected by sub-batch B      46
silent hazards found by the refusal rules:
    typedef names with incompatible definitions   29
    macro names with differing bodies             35
    static names used in more than one file       17
stage 08 units refused
    member block carries a preprocessor directive 59
    member block declares a file-scope static     70
quarantined-protected build inputs (carried by reference, C2)  36
```

## 13. What a reviewer would still object to

Honestly, and in the order I would raise them:

1. **"Your stage 04–08 evidence does not correspond to your tree."** Correct,
   and §3.2 says so. It is the single largest hole and it needs three Renode
   captures per image to close.
2. **"You changed the criterion's segmentation until the base passed."** The
   fair version of this. My defence is narrow: Δ is *derived*, not chosen, and
   it re-derives to **exactly 145.440 ms** at four different thresholds
   including the one I report; the change makes stages FAIL, never pass; and I
   declined to adopt a constant precisely because the selection would otherwise
   be tuned. But the choice of *which* threshold to report is mine, and a
   reviewer is entitled to ask for a structural derivation. §5.4 says I tried
   one and it does not select a usable value.
3. **"Stage 01's class was wrong for the whole life of the pipeline and nobody
   noticed."** Also correct (§3.4). It says the C7b mechanism was added
   forward-only and never back-filled, which is a process finding, not a
   one-stage finding.
4. **"You added 341 declarations to stage 04's trees and cannot prove they cost
   nothing."** I can prove the FLASH size is unchanged and that incomplete-type
   declarations emit no code; I cannot `cmp` against the pre-fix image because
   the pre-fix tree does not compile (§3.2). That is a genuinely weaker claim
   than this project's usual bar.
5. **"64 % of translation units are still one function each."** Yes — §11
   measures the ceiling at 182 TUs and specifies the stage, and does not build
   it.
6. **"Your `RADIO_TX` component is a subtraction, not a measurement."** It is a
   subtraction — of two fields the oracle publishes — and it reproduces §44.4's
   four instrumented captures exactly on navigation, then extends to the
   dashboard, which was never instrumented. A reviewer wanting the p1/p2 split
   still needs the instrumented capture.
7. **"The net core has not been looked at in three passes."** True (§12 item 6).

---

## 14. Two costs of the stage-04 repair, and the closing input generation

### 14.1 The forward-declaration block reduces stage 06's yield

Every merged unit now opens with a declaration block before its first member,
and stage 06's include-hoisting rule keys on "the unit's **first include
block**". Measured, same inputs, before and after the §2.3 change:

| stage | field | before the fix | **after** |
|---|---|---:|---:|
| 06 | `H_late_includes_seen` | 305 | **153** |
| 06 | `H_includes_hoisted` | 268 | **142** |
| 06 | `files_changed` | 149 | **86** |
| 08 | `units_already_in_call_order` | 115 | **87** |
| 08 | refused: preprocessor directive | 59 | **109** |
| 08 | refused: file-scope static | 70 | **48** |

Stages 05 and 07 are **unchanged field for field**, and stage 06 still measures
`byte-identical`, so **nothing observable was paid** — but 126 fewer includes are
hoisted, which is a real loss of composition depth. The clean follow-up is to
teach stage 06 that the generated forward-declaration block is part of the
unit's preamble rather than a barrier. **Not done**, and named here rather than
left for someone to rediscover as an unexplained regression.

### 14.2 Closing state — the inputs moved again

The concurrent agent landed **50 further inputs** during this pass. The ladder
was regenerated once more at the close (00→08, all exit 0, `status` **0
changed** on stages 0–8; stage 99 stale on 863, as always):

| stage | field | measured generation (§1, built) | **closing generation** |
|---|---|---:|---:|
| 04 | translation units | 1,615 → **705** | 1,615 → **742** |
| 04 | merged units / files absorbed | 244 / 1,154 | **249 / 1,122** |
| 04 | adjacencies blocked | 862 | **893** |
| 05 | duplicate includes / declarations withdrawn | 1,596 / 152 | **1,526 / 143** |
| 06 | late includes hoisted / seen | 142 / 153 | **146 / 157** |
| 07 | definitions given internal linkage | 135 | **133** |
| 08 | units reordered | 0 | **0** |
| 00/03 | files, parity rows, hoists, divergent symbols | unchanged | unchanged |

**The newest landing REDUCES stage 04's merge yield again**: 705 → 742 retained
TUs, 1,154 → 1,122 files absorbed, 862 → 893 adjacencies blocked. Two
consecutive repair passes have now each made the merge *less* effective (247 →
244 → 249 units but fewer files inside them). Worth watching: the declaration
repairs are closing type disagreements *and* creating new pairwise collisions.

**Everything built and measured in §2, §3, §5 and §9 is at the measured
generation**, which is the one stage 00 captured and which is `cmp`-identical to
the base image of the three preceding passes. The closing generation was not
built. Stated so the two are never conflated.

---

## 15. Footprint — everything this pass wrote

```
 M recon/refactor/transforms/t04_cohesive_tu.py   incomplete_tag_forwards() +
       blank_attributes() + the render() preamble block  (section 2.3)
 M recon/refactor/test_cohesive_tu.py             +6 IncompleteTagForwardsTest
 M recon/refactor/driver.py                       STAGES row 1 class corrected
                                                  byte-identical -> size-changing
 M recon/refactor/README.md                       the CONSOLIDATED GATE RECORD,
                                                  and the stage-01 table row
 M recon/refactor/stage_*/{MANIFEST,PARITY_MAP,QUARANTINE,DEFECTS}.json
                                                  regenerated, never hand-edited
 M recon/refactor/stage_*/tree/**                 regenerated
 M recon/refactor/stage_0{4,5,6,7}/SIZE_GATE.json re-measured
?? recon/refactor/stage_08_call_order/SIZE_GATE.json   NEW -- the section 3 gap
?? recon/refactor/stage_0{1,2,3}/SIZE_GATE.json        NEW
?? recon/refactor/criterion_probe.py                   NEW (section 8)
?? recon/refactor/test_criterion_probe.py              NEW, 12 tests
?? recon/analysis/refactor_consolidated_verdict.md     this file
```

**Not written:** no canonical tree (`recon/app/src`, `recon/net/src`,
`recon/verified`, `recon/named`, `recon/readable_sources`, `recon/symbolized`),
no `recon/symbols`, no `recon/application`, no `tools/` module, no
`recon/emulator/**` — **not the scripts and not the reports** — no linker
script, no board file, nothing under `~/Projects/armemul`. Everything temporary
is under this session's scratch and `/private/tmp/g1-cons-*`.

The modified `recon/emulator/reports/our_boot_bringup.md` and the ~50 modified
`recon/symbolized/app/*.c` that `git status` shows are **the concurrent parity
agent's, not mine.**

**Nothing was committed.**
