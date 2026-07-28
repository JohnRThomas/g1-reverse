# The phase bound, re-derived so that it does not depend on our own build's error

**Written incrementally as the work ran.** Every number comes from a command
actually run in this pass, or is re-derived here from a capture on disk; where a
number is inherited it says so and it is re-computed rather than quoted. Where a
claim of mine is later shown wrong it is corrected in place with a note.

Nothing is committed. `recon/refactor/` is not touched (concurrent agent owns it).

---

## 0. The two defects this pass is answering

**Defect A — the bound is a function of our own error.** The published rule is

> Δ = max `|δ|` over phase-measurable trains between the **shipped firmware** and
> **our in-tree base**, over both stimuli and every traced bus.

Iteration 45 landed a genuine firmware repair; iteration 46 re-derived Δ by the
same rule and got **262.200 ms** instead of **145.440 ms** — an 80 % widening
caused entirely by the base moving. Provenance is confirmed: shipped versus the
*pre-i45* base still gives exactly 145.440 ms. A gate that widens when the
firmware improves cannot detect a regression.

**Defect B — the gate is flippable by inert bytes.** 204 bytes of unreferenced,
`retain`-kept, zero-filled `.rodata`, moving **zero** `.text` addresses, shift the
navigation cluster by a whole slot (+101.010 ms) on stage 04 and by nothing
(+0.120 ms) on the base. The pad costs ~1 ms of boot-path time; a slot boundary
is crossed only when the image already sits within ~1 ms of one.

A third defect falls out of iteration 46 §46.6 and drives the redesign:
**`max|δ|` is not a displacement.** On `spim_a` navigation the distribution of
per-burst δ is ~154 ms wide *at zero slot offset*. The published maxima decompose
as `−37.3 ms structural offset + k×100.5 ms + a within-train spread up to ~108 ms`,
and the third term dominates. Δ was derived from, and stages were gated on, a
statistic that is mostly not displacement.

---

## 1. THE RULE, FIXED BEFORE ANY MEASUREMENT

Stated here in full, before a single number below it was computed, so that no
result in this report can be read as tuning. Deviations from this statement, if
any, are recorded in §9 with their reason.

### 1.1 Statistic: median, not maximum

For a stream `(bus, device)` and an image pair `(shipped, ours)`, take the
per-burst displacements `δ_i` over the trains common to both, using the
criterion's existing decomposition (`phase_tolerant_compare.blocks` /
`trains_by_key`) — **no second segmentation rule is introduced.** Then

* `D = median(δ)` — the stream's **displacement**;
* `S = P95(δ) − P5(δ)` — the stream's **spread**, i.e. everything `D` does not
  explain.

`max|δ|` is still computed and still published, as a separate field, so the
strict residue stays measurable.

### 1.2 Decomposition against the stimulus lattice

`W` = the width of one DUT BLE connection-event response slot, **a property of
the stimulus and the emulated link**, measured independently of any bound (§3).

```
k = round(D / W)          the integer slot index
r = D − k·W               the sub-slot residual
```

### 1.3 The gates

| | gate | rationale |
|---|---|---|
| **Q1** | `\|r\| ≤ R` on every gated stream | a displacement that is an exact number of stimulus slots is stimulus-driven and carries no information about the refactor; everything the lattice does **not** explain is ours |
| **Q2** | `k` is **reported, never gated** | its value is decided by which side of a connection-event boundary the link landed on, which §46.9/§46.10 proved is reachable by semantics-free bytes |
| **Q3** | `S ≤ Σ` | a cadence/drift error changes the shape of the distribution even when the median is clean; `Q1` alone would not see it |
| **Q4** | P1 content, P2 population, P5 order | unchanged from the published criterion |
| **Q5** | `slot_edge_margin` is computed and **published for every image**; below `M` the stream's verdict is **`METASTABLE`**, not PASS and not FAIL | a gate that a 204-byte inert pad can flip must say so out loud rather than silently pass or fail |

### 1.4 Where the constants come from — and where they may NOT come from

`W`, `R`, `Σ`, `M` are **forbidden** from being derived from "how far our build
sits from shipped". Admissible sources, in order of preference:

1. **shipped vs shipped across different emulator seeds** — contains no build of
   ours at all;
2. **the measured dispersion of `W` itself** across independent one-slot moves —
   the lattice's own width is not a constant, and a residual smaller than that
   dispersion is indistinguishable from "exactly one slot";
3. **the measured cost of a semantics-free perturbation** (the 204-byte pad),
   for `M` only — the criterion must be insensitive to at least the smallest
   perturbation known to flip `k`.

`R = max(source 1, source 2)`, published with both components separately so the
choice is visible. `Σ` from source 1. `M` from source 3.

**Under this rule, improving the firmware cannot loosen the gate**: a repair
moves `D`, `k` and the boot offset — all of them *measured outputs* — and moves
none of `W`, `R`, `Σ`, `M`.

### 1.5 What this rule is expected to stop catching (predicted in advance)

* Any displacement that is an exact integer number of stimulus slots, of any
  size. Under the old rule a 2-slot move failed and a 1-slot move passed, for no
  reason connected to the firmware.
* Kept measurable by: `k` published per stream per image, `max_abs_delta_ms`
  published unchanged, and the strict `cmp3.py` fields untouched.

---

*(measurements follow; sections are appended as they are produced)*

---

## 2. The control that decides the whole question: SHIPPED vs SHIPPED

Six new seeded Renode captures of the **shipped** firmware were taken in this
pass (`/private/tmp/g1-i47/shipcap.sh`), four navigation and two dashboard, at
four emulator seeds. Nothing of our build appears anywhere in this section.

```
seed A  305419896   (the project's standard seed; a re-run of the reference)
seed B  2596069104
seed C  1732584193
seed D  13579
```

### 2.1 The determinism control — exact

`g1_i47_shipA_nav` versus the project's reference shipped capture
`g1_ship_seed_q1` (taken a day earlier, different host load, fresh Renode):

```
spim_a.p1.trace  spim_a.p2.trace  twim1.p1  twim1.p2  twim2.p1  twim2.p2   IDENTICAL
fb_p1_boot.ppm   fb_p2_render.ppm                                          IDENTICAL
```

and through the oracle and the new statistic, every field on every stream is
**0.000 ms** — `D`, `S`, `min`, `max`, `k`, `r`, `max|δ|`. The measurement is
exact and the capture is a function of (image, seed).

### 2.2 **The published Δ is not a measurement of our build. It is the emulator's stimulus noise floor.**

The published derivation rule, applied verbatim by
`phase_tolerant_compare.py derive-bound` — but to a pair that contains **no
build of ours at all**, shipped-seed-A against shipped-seed-C, over both
stimuli:

```
DERIVED PHASE BOUND (max over every pair): 141.170 ms
```

against the same rule's answer for shipped versus our pre-i45 base, **145.440 ms**.

> **Δ = 145.440 ms is reproduced to within 3 % by changing nothing but the
> emulator seed on the shipped firmware.** The quantity the project has been
> gating stages against was believed to encode "how far our build sits from
> shipped". Measured against a pure-stimulus control it is, to within a few
> percent, the noise floor of the stimulus. That is a stronger statement than
> Defect A: the bound was not merely *contaminated* by our build's error, it was
> never dominated by it.

### 2.3 The published criterion FAILS the shipped firmware against itself

`phase_tolerant_compare.py pair --bound-ms=145.44`, shipped-seed-A as the
reference, shipped at another seed as "ours":

| pair | streams failing (of 6) | what |
|---|---:|---|
| seed A → seed A (control) | **0** | every field 0.000 |
| seed A → **seed B** | **2** | `spim_a` `P2 population 34→35`; `npm1300` `P2 population` ×3 |
| seed A → **seed C** | **1** | `npm1300` `P5 order: two bursts 9904.330 ms apart swapped` |
| seed A → seed D | 0 | — |

### 2.4 Two named "genuine firmware residues" are FALSIFIED by this control

**(a) The three `npm1300` P2 population failures.** The consolidated verdict
§5.2 recorded them as *"a genuine residue, correctly reported"*, root-caused by
§43.9/§43.10 to "the +3.45 ms boot lateness at the 20 s observation wall".
Iteration 46 §46.5.1 charged them to stage 03 as its single REGRESSION.
Side by side at T = 0.790 ms, all re-run in this pass:

| run | extra burst | missing burst | missing burst |
|---|---|---|---|
| our pre-i45 base | 18.827820 s | 19.054650 s | 17.573143 s |
| our stage 03 | 18.827753 s | 19.054650 s | 17.573143 s |
| **shipped firmware, seed B** | **18.824460 s** | **19.054650 s** | **17.573143 s** |

Two of the three are the **same timestamp to the microsecond**; the third is
3.3 ms away. They are produced by the shipped firmware compared against itself.
**They are not a firmware residue and they are not evidence about any stage.**
They are a property of an `npm1300` train that straddles the 20 s wall, which
any perturbation — including a pure seed change — moves.

**(b) The `npm1300 P5 order` failure on the base.** The criterion report §4.1
called it *"a pre-existing ordering defect in our build that the strict
per-phase hash never isolated"*, and §8 item 5 said *"it deserves a look"*.
Shipped seed A vs shipped seed C reports, verbatim:

```
FAIL  P5 order: two bursts 9904.330 ms apart in the shipped run swapped order
```

— the **identical 9904.330 ms**. It is not a defect in our build. It is what
`P5` does to this stream under any perturbation.

### 2.5 Seed variance, quantified

Per-stream displacement `D = median(δ)` and residual `r`, shipped vs shipped:

| pair | max \|D\| | on | max \|r\| | max \|δ\| |
|---|---:|---|---:|---:|
| A → A | **0.000** | — | 0.000 | 0.000 |
| A → B | 1.130 | `spim_a` | 1.130 | 2,547.150 |
| A → C | **67.388** | `st25dv_nfc` | 50.107 | 7,569.950 |
| A → D | 2.190 | `spim_a` | 2.190 | 102.480 |
| B → C | 66.340 | `st25dv_nfc` | 50.002 | 7,568.917 |
| C → D | 66.340 | `st25dv_nfc` | 50.110 | 7,568.916 |
| A → B (dash) | 1.010 | `st25dv_nfc` | 1.010 | 1.650 |
| A → C (dash) | 36.070 | `opt3001` | 36.070 | 74.310 |

Seed C also changes **content**: `spim_a` `p2_render` is 2,881 transactions at
seeds A/C/D and **2,903** at seed B. So the seed moves counts as well as phase.

Two things follow, and they point in opposite directions — both are reported:

* **the stimulus noise floor is tens of milliseconds**, `max|D| = 67.388 ms`,
  `max|r| = 50.110 ms`. Any claim that a 30–70 ms displacement is refactor
  damage is a claim the emulator cannot support across seeds;
* but the seed does **not** move the display cluster by a slot (`k = 0` on
  `spim_a` for every seed pair), and seed noise is **incoherent** — at seed C,
  `spim_a` +9.700, `opt3001` +50.107, `npm1300` +50.049, `st25dv` +67.388,
  `lsm6dso` 0.000, all different. Every slot move measured on our images is
  **coherent**: the startup-cluster devices move together by the same amount and
  the free-running devices do not move at all.

---

## 3. The constants, every one of them measured

`<scratch>/i47/constants.py`, run at T = 0.790 ms over the captures on disk.

### 3.1 `W` — the slot width

A hop counts as a **clean one-slot hop** iff both slot-locked devices
(`spim_a jbd_display`, `twim1 opt3001`) move by 90–110 ms **and agree with each
other within 1 ms**. Five such hops exist among the images on disk:

| pair | `spim_a` \|D\| | `opt3001` \|D\| |
|---|---:|---:|
| HEAD base → stage 03 | 99.950 | 100.026 |
| stage 03 → stage 04 | 100.340 | 100.465 |
| HEAD base → stage 04 + pad | 100.590 | 100.571 |
| stage 04 → stage 04 + pad | 101.010 | 101.010 |
| pre-i45 base → old stage 04-B | 100.470 | 100.694 |

> ### **W = 100.513 ms**  (10 measurements; min 99.950, max 101.010, range 1.060)

Our images appear here only as **probes** of the link: what is being measured is
the spacing of the emulated DUT's answered connection-event windows, and it
comes out the same whichever pair of images is used to jump between two of them.
Independent corroboration from the stimulus model: `BLE_VirtualCentral.cs:372`
sets the connection interval to `{0x18, 0x00}` = 24 × 1.25 ms = **30 ms**, and
`W / 30 ms = 3.35` — the "≈1 answered response in 3⅓ connection events" that
§44.5 measured. The mechanism is still not derived from first principles (§9).

**`R_slot` = 0.563 ms** — the largest deviation of an observed hop from `W`.
The lattice's own spacing is not constant, so a residual below this is
indistinguishable from "exactly one slot".

### 3.2 `R_pad` — what a provably semantics-free change costs

The 204-byte inert `.rodata` pad from iteration 46 §46.4 (unreferenced,
unexecutable, `SHF_GNU_RETAIN`, **0 `.text` addresses moved**), over four image
pairs and both stimuli:

| pair | max \|r\| | k observed |
|---|---:|---|
| base → base + pad, navigation | **1.160** | 0 |
| stage 04 → stage 04 + pad, navigation | 1.100 | 0 and **+1** |
| base → base + pad, dashboard | 1.010 | 0 |
| stage 04 → stage 04 + pad, dashboard | 0.979 | 0 |

> ### **R_pad = 1.160 ms** (`twim1 opt3001`, base → base + pad, navigation)

Note the second row: the pad moves `spim_a` and `opt3001` by a **whole slot**
(k = +1) on stage 04 and the residual is still ≤ 1.100 ms. That is the
knife-edge, decomposed — the slot move goes into `k`, which is not gated, and
what is left in `r` is a millisecond.

> ### **R = max(R_slot, R_pad) = 1.160 ms**

### 3.3 `R_seed` — the stimulus noise floor, NOT a gate

Largest `|r|` the shipped firmware produces against itself across seeds:
**50.110 ms**; largest `|D|`: **67.388 ms**. Used only as an annotation: a Q1
failure below it is real at a fixed seed but is not reproducible as a claim
about the firmware across stimulus realisations, and the tool says so.

### 3.4 `Σ` — the spread ceilings, and an honest note that Q3 is weak

Per-device `P95 − P5` ceilings from the seed pairs only:

| device | Σ (ms) |
|---|---:|
| `spim_a` jbd_display | 68.240 |
| `twim1` npm1300 | 1,069.469 |
| `twim1` opt3001 | 37.387 |
| `twim1` st25dv_nfc | 76.299 |
| `twim1` st25dv_system_port | 76.260 |
| `twim2` lsm6dso | 34.393 |

**Q3 as calibrated catches nothing in the current ladder**, and I am not going
to tighten it to make it look useful. The reason it cannot be tightened is
measured: the **inert 204-byte pad alone** produces `S = 32.968 ms` on `spim_a`
navigation with individual bursts moving as far as **−82.850 ms**, while the
median moves 0.120 ms. Per-burst phase on `spim_a` navigation carries ±83 ms of
variation attributable to bytes no instruction reads. Any Σ that admits the
inert pad admits everything the ladder currently does. Published so it stays
measurable; §9 records it as not closed.

---

## 4. Two deviations from §1, both against my own interest

**(a) The refactor gate is computed on the DIRECT `base → stage` pairing, not on
the difference of two shipped-relative statistics.** §1 did not say which.
Measured reason: `median(X−Z) ≠ median(X−Y) − median(Y−Z)` on distributions this
wide. `twim1 st25dv_nfc`, base → stage 03: via shipped-relative medians it is
**+5.680 ms** (base −1.740, stage 03 +3.940); paired directly it is
**−0.060 ms**. The indirect arithmetic would have failed a stage the direct
measurement clears, so the choice was made *against* the flattering answer being
the reason.

**(b) Q5 as specified in §1 cannot be implemented.** `slot_edge_margin` is
**not computable from the oracle's observables.** §1 assumed the boot-path
offset `b` (readable on a free-running stream) would predict which side of a
window boundary the trigger lands on. It does not:

```
HEAD base   lsm6dso median delta vs shipped = 6.749 ms   spim_a k = -1
stage 03    lsm6dso median delta vs shipped = 6.750 ms   spim_a k =  0
```

**One microsecond of boot offset apart, opposite slots.** The trigger is the
GATT-ack path through the net core and the BLE model; the app's free-running
peripheral cadence does not measure it. So the lattice cannot be fitted and the
margin cannot be computed. What replaces Q5 is in §5.4.

---

## 5. THE GATE, RUN

Implemented in **`recon/emulator/scripts/slot_quantised_compare.py`** (new).
Run over iteration 46's captures — which are one internally consistent set from
one ladder generation, all seeded `G1_SEED=305419896`, `$rtinfo_pc` re-read per
ELF. No stage tree was materialised or rebuilt in this pass (`recon/refactor/`
belongs to the concurrent agent).

**Inherited, not measured here:** the image identities `stage 01 = 02 = 03` and
`stage 04 = 05 = 06` are iteration 46 §46.11's `cmp` chain. Five captures cover
seven images *because that chain holds*; I did not re-run the `cmp`s, because I
did not rebuild the images.

### 5.1 Navigation, T = 0.790 ms, W = 100.513 ms, R = 1.160 ms

| pair | max \|r\| | on | k (spim_a / opt3001) | **Q1/Q3** |
|---|---:|---|---|---|
| base → **stage 01 = 02 = 03** | 0.563 | `spim_a` | +1 / +1 | **PASS** |
| base → **stage 04 = 05 = 06** | 0.520 | `st25dv_nfc` | 0 / 0 | **PASS** |
| base → *stage 04 + inert pad* | 0.791 | `lsm6dso` | +1 / +1 | **PASS** |
| base → *base + inert pad* | 1.160 | `opt3001` | 0 / 0 | **PASS** |
| pre-i45 base → **old stage 04-B** | 0.580 | `st25dv_nfc` | −1 / −1 | **PASS** |
| pre-i45 base → **old stage 07** | **30.881** | `npm1300` | *not a slot* | **FAIL, 5 of 6 streams** |

### 5.2 Dashboard, same constants

| pair | max \|r\| | **Q1/Q3** |
|---|---:|---|
| base → stage 03 | 0.092 | **PASS** |
| base → stage 04 | 0.510 | **PASS** |
| base → stage 04 + pad | 0.519 | **PASS** |
| base → base + pad | 1.010 | **PASS** |

### 5.3 **The burst-gap threshold stops being load-bearing**

Every verdict above was re-run at **T = 5.000 ms** as well. The Q1/Q3 outcome is
**identical at both thresholds on both stimuli** — 0 failures for every stage
except stage 07, which fails the same 5 of 6 streams at both. The consolidated
verdict's §5.3 (*"the published criterion scored stages 04-B/05/06/07 as PASS
only because the base was failing the same stream for an unrelated segmentation
reason"*, and the whole non-monotonic clean-band problem of §5.4) **does not
arise under this rule.** The threshold still matters for P1/P2/P5, where the
segmentation is the measurement; it no longer decides a phase verdict.

### 5.4 What replaces Q5 — `SLOT MOVED`, and the probe that is required

`k` differing between base and stage is printed as `<== SLOT MOVED`, with:

> Every SLOT-SENSITIVE strict field on this bus (`p1_boot` `transaction_count`
> and `stream_sha256`, `RADIO_TX`'s BLE component, `JBD_FRAMECOUNTER`) is
> slot-attributable and is NOT evidence of a regression or an improvement.

This is computable, and it retro-explains the ladder's strict results without
any new hypothesis:

* stage 03's **eight strict `cmp3` "improvements"** (§46.5.2) — `k` moves
  −1 → 0 on `spim_a` and `opt3001`. Slot-attributable. Not eight repairs.
* stage 04 + pad's **seven strict "improvements"** (§46.9.1) — same `k` move,
  produced by 204 inert bytes. Slot-attributable.
* old stage 04-B's **eight strict "regressions"** — `k` moves 0 → −1.
  Slot-attributable. Not eight regressions.

`slot_edge_margin` itself is **not published, because it is not measurable**
(§4b). The only instrument known to decide metastability is the one iteration 46
built: **rebuild the same sources with an inert pad and re-measure `k`.** Its
cost is one build plus two captures per image, and this report states it as a
requirement for any image whose `k` differs from the base's — not as something
already discharged.

---

## 6. Does the new rule flip a previously-passing stage? Yes — ONE — and here is why that is not a bug in the rule

The discipline is: *a rule change that flips a previously-passing stage is a bug
in the rule until proven otherwise.* One stage flips.

| stage | published criterion (Δ 145.440, T 5.000 ms) | published criterion (Δ 145.440, T 0.790 ms) | **slot-quantised rule** |
|---|---|---|---|
| 01 / 02 / 03 | PASS | PASS *(iteration 46: 1 REGRESSION)* | **PASS** |
| 04 / 05 / 06 (HEAD) | PASS | PASS *(iteration 46)* | **PASS** |
| 04-B / 05 / 06 (old) | PASS, 2 pre-existing-worse | **REGRESSION** (consolidation §5.3) | **PASS** |
| **07 (old)** | **PASS**, 2 pre-existing-worse | **REGRESSION** (consolidation §5.3) | **FAIL** |

So stage 07 flips **only against the T = 5.000 ms reading**, which is the single
threshold the consolidation showed hides the failure. Against the clean band it
agrees with the consolidation. The evidence that the failure is real:

1. **It is not a slot.** `spim_a` moves −119.510 ms = **−1.189 slots**;
   `opt3001` −104.614 = −1.041. Every other slot move in the project has both
   devices inside 1 ms of an integer. Residuals: −18.997 ms and −4.101 ms,
   16× and 3.5× the bound.
2. **+31.250 ms lands identically on three independent `twim1` devices**
   (`npm1300`, `st25dv_nfc_eeprom`, `st25dv_system_port`) — coherent, and not a
   multiple or fraction of `W`. Iteration 46 §46.6.3 raised this as a hypothesis
   (one 30 ms BLE connection interval) with its falsification test stated and
   **unrun**; the new rule makes it a *failure* rather than an aside.
3. **Seed noise does not look like this.** At seed C the shipped firmware moves
   `spim_a` +9.700, `opt3001` +50.107, `npm1300` +50.049, `st25dv` +67.388,
   `lsm6dso` 0.000 — five different numbers. Stage 07 moves three independent
   devices by *the same* 31.250 ms. The magnitude is below `R_seed` and the tool
   labels it `BELOW-STIMULUS-NOISE`, honestly; the coherence is what says it is
   not noise, and that is stated as an observation, not encoded as a gate.
4. **Stage 07 does not link at HEAD anyway** (§46.3, stage 09 §4) — the images
   this verdict is computed on are the pre-i45 ones.

**Everything else that previously passed still passes**, including both inert-pad
images and both old-ladder stages. No previously-passing stage flips for a reason
the rule cannot defend.

---

## 7. Task 3 — the burst-gap and ambiguity findings, closed or explained

### 7.1 `gap_separation.separated` was vacuous — **FIXED**

`recon/emulator/scripts/build_display_sensor_oracle.py` now publishes the
falsifiable K-fold void test from `staged_refactor_stage09.md` §6.1, with
`SEPARATION_RATIO = 4.0`, and keeps the tautology's value as
`separated_by_construction_LEGACY` so the old field stays measurable.

Regenerated from the shipped navigation capture and diffed field-by-field
against the **HEAD** script run from the same directory on the same capture:

```
REMOVED: 0   ADDED: 18   CHANGED: 5
  the 18 added are separation_ratio / separation_ratio_required /
      separated_by_construction_LEGACY, x 6 devices
  the 5 changed are EXACTLY the `separated` booleans
golden_framebuffer_p1_boot.raw / p2_render.raw   cmp exit 0  (byte-identical)
```

Measured values, shipped navigation:

| device | ratio @ 5.000 ms | `separated` | ratio @ 0.790 ms | `separated` |
|---|---:|---|---:|---|
| `spim_a` jbd_display | **1.24** | **false** | 4.27 | true |
| `twim1` npm1300 | **2.17** | **false** | **1.50** | **false** |
| `twim1` opt3001 | 62.84 | true | 62.84 | true |
| `twim1` st25dv_system_port | **1.50** | **false** | 102.97 | true |
| `twim1` st25dv_nfc_eeprom | **1.65** | **false** | 102.98 | true |
| `twim2` lsm6dso | **1.29** | **false** | 39.55 | true |

Exactly stage 09 §6.1's calibration: **5 of 6 fail at the shipped threshold, 1 of
6 at 0.790 ms, and the holdout is `npm1300`** — the same device the phase
criterion independently shows is mis-assigned. The consequence stage 09 warned
about is real and is accepted: `separated` is now `false` on most devices in
every regenerated oracle. **No consumer branches on it** — verified by grep
across `*.py`/`*.sh`/`*.js`: it is published and never read.

### 7.2 The burst gap is now sweepable from the repository — **FIXED**

`BURST_GAP_NS` reads `G1_BURST_GAP_NS` (default unchanged at 5 ms). Four
separate passes have swept this threshold, and **every one of them did it with a
private copy of the script**, which is why none of their numbers is reproducible
from the repository. Verified equivalence: the shared script at
`G1_BURST_GAP_NS=790000` reproduces iteration 46's sweep copy **exactly** — same
train count, same burst count, same `key_sha256` list and same `starts_ns` list
on all six devices.

**The threshold constant itself is NOT changed**, and the consolidation's §5.4
reasons for not changing it still stand (the clean band is non-monotonic).
§5.3 above is the new argument: under the slot-quantised rule the verdict is the
same at 0.790 ms and at 5.000 ms, so the constant is no longer load-bearing for
a phase verdict and there is nothing to be gained by standing it on a knife-edge.

### 7.3 The `P0 segmentation` SPLIT direction — **FIXED**

`phase_tolerant_compare.py` had a category for the *merge* direction only, so a
burst that segments into two under a tighter gap was charged as `P1 content`
(iteration 46 §46.9.1, §46.13 item 5). Both directions are now named. The exact
case §46.9.1 measured, re-run:

```
P0 segmentation: a shipped train is absent from ours and its key BEGINS with
   another train's key -- one burst split in two under burst_gap_ns
   (n=2) 6B|W|040A02|6B|W|040F|6B|R|04|n1|6B|W|040F02|6B|W|040201
P0 segmentation: a train appears only in ours and another train's key BEGINS
   with it (n=2) 6B|W|040A02
P1 content: train present only in ours (n=2) 6B|W|040F|6B|R|04|n1|...
```

**Limitation, stated rather than hidden:** the prefix heuristic catches the
shipped train and the *leading* half; the trailing half is not a prefix of
anything and is still charged as `P1 content`. It is **still a FAIL** either way
— naming an artifact does not make it pass.

**Regression-checked against HEAD's own script**, over 14 navigation and 12
dashboard image/threshold combinations:

```
per-stream verdict / max|d| / measurable, HEAD vs patched   0 differences
three-way REGRESSION and PRE-EXISTING-BUT-WORSE buckets     0 differences
```

My first version of this check was wrong and said "DIFFER" on five rows: it was
comparing the failure DETAIL lines, whose labels are exactly what the patch
changes. Corrected in place. The change is a relabel; it moves no verdict and no
bucket, including the `worse_than()` category counting that the relabel could in
principle have disturbed.

#### 7.3.1 A finding that fell out of that regression check

Running the **published** three-way comparer on the inert-pad images:

| three-way (shipped \| base \| image) | T = 0.790 ms | T = 5.000 ms |
|---|---|---|
| base \| **base + 204 B inert pad** | **1 REGRESSION**, 1 pre-existing-worse | **1 REGRESSION**, 1 pre-existing-worse |
| base \| stage 04 + pad | 1 REGRESSION, 0 | 0, 0 |

**The published criterion charges 204 bytes of `.rodata` that no instruction
reads with a refactor REGRESSION, on the in-tree base, at both thresholds.**
That is Defect B stated as sharply as it can be stated, and it is a *different*
demonstration from iteration 46's — §46.10's control showed the pad moved
nothing on the base by a slot; this shows the gate fails it anyway. Under the
slot-quantised rule the same image is `max|r| = 1.160 ms`, **PASS**.

### 7.4 The ambiguity rule — **MOOT under the new rule, and the 7,498 ms cannot recur**

`G1_EQUAL_POP_RULE` exists because the published criterion *excludes* bursts
whose `i ↔ i` correspondence is ambiguous, and turning the exclusion off at the
5 ms gap blew Δ from 145.440 ms to **7,498.630 ms**. The slot-quantised rule has
**no exclusion**: it uses every burst and takes a *median*, so there is nothing
to switch on or off, and a single mis-assigned `npm1300` burst cannot move the
bound. Measured directly: `npm1300` carries `max|δ| = 2,547.852 ms` on the
base → stage 03 pairing and its displacement `D` is **−0.272 ms**. The outlier
that broke the old rule is absorbed, and it is still visible, because
`max_abs_delta_ms` is printed on every row.

**Correcting iteration 44's claim once more, from a third direction:** §44.7.1
said the exclusion was closable at zero cost; the consolidation showed it costs
51× at the shipped gap; this pass shows the exclusion should not have existed —
it was a patch on a statistic (`max`) that could not survive one bad burst.

---

## 8. What the new rule STOPS catching

Published so the residue stays measurable, in the pattern iteration 42 used for
`stream_sha256_raw_pointers` and `analogue_sample_payloads`. Each item names the
field that keeps it inspectable.

1. **A displacement that is an exact integer number of stimulus slots, of any
   size.** `k = ±3` is admitted as readily as `k = ±1`. Under the old rule a
   1-slot move passed and a 2-slot move failed, for no reason connected to the
   firmware; this rule stops pretending the difference is meaningful. If the
   number of slots is *itself* evidence of something, this rule will not say so.
   *Kept measurable by:* `k` printed per stream per image, and the `SLOT MOVED`
   annotation whenever it differs from the base's.
2. **Anything below 1.160 ms.** That is the measured floor of the instrument, not
   a choice: 204 bytes of data no instruction reads move `twim1 opt3001` by
   1.160 ms. A real 1 ms timing defect is now invisible to Q1.
   *Kept measurable by:* the strict `cmp3.py` fields, unchanged, and the `D`
   column printed for every stream including passing ones.
3. **Everything the median hides.** `D` is deliberately robust: `npm1300` carries
   `max|δ| = 2,547.852 ms` on a pairing whose `D` is −0.272 ms. A defect that
   moves a handful of bursts a long way and leaves the bulk alone passes Q1.
   *Kept measurable by:* `max_abs_delta_ms` and `S` printed on every row, and
   Q4's P1/P2/P5, which are unchanged and still content/population/order gates.
4. **Per-burst phase on `spim_a` navigation, entirely.** Measured here: the inert
   pad alone moves individual `spim_a` bursts by up to **−82.850 ms** while the
   median moves 0.120 ms. That stream's per-burst phase is not a measurement of
   anything and Q3 cannot be calibrated to make it one.
   *Kept measurable by:* `S` and `min`/`max`, and the four acceptance
   framebuffers, which are the gate that did not move once across five images
   spanning 956,292–956,700 bytes and two slot assignments.
5. **Everything outside the traced buses.** `RADIO_TX`, `ESB_*`,
   `VC_DATA_EVENTS`, `saadc`, `pdm0`, `gpiote*` have no train decomposition and
   are not covered — unchanged from the published criterion. What is new is that
   `RADIO_TX`'s BLE component is now *annotated* as slot-attributable whenever
   `k` moves, instead of being counted as an independent regression.
6. **Anything the emulator's own stimulus noise reaches.** `R_seed = 50.110 ms`
   is a floor on what any claim about the firmware can survive a change of seed.
   The rule does not raise `R` to it — it gates at 1.160 ms and *labels* failures
   below 50.110 ms, so the residue is visible rather than absorbed.

**The strict values are not replaced.** `cmp3.py`'s 69 fields are still computed
and still reported. `phase_tolerant_compare.py` still runs and still publishes
`max|δ|` and Δ; the slot rule is published alongside it, not instead of it.

---

## 9. WHAT I DID NOT CLOSE, AND WHY

1. **No image was built and no stage tree was materialised.** Every verdict in
   §5 and §6 is computed on **iteration 46's captures** — one internally
   consistent set, seeded, `$rtinfo_pc` per ELF, but taken at HEAD `da19df1a`.
   `recon/refactor/` belongs to the concurrent agent and `git status` shows it
   is being actively repaired right now (`link_evidence.py`,
   `link_referenced_symbols.json`, `t07_internal_linkage.py`, every `MANIFEST`
   and `SIZE_GATE`). **Stages 07 and 08 could not be built at all at that HEAD**
   (§46.3), so the stage-07 verdict in §6 is computed on the *pre-i45* stage-07
   image. **If the concurrent agent's repair makes stage 07 link, it must be
   re-captured and re-gated before §6's row means anything about the current
   stage 07.** That is the single largest open item in this report.
2. **The mechanism behind `W` is still not derived.** `W = 100.513 ms` is
   measured, and `W / 30 ms = 3.35` matches §44.5's "1 answered response in 3⅓
   connection events", but the "3⅓" is not derived and §44.5's own falsification
   test (`SweepDwell 4 → 8`) is **still unrun**, for the fifth pass running. So
   is §46.6.3's test for the +31.250 ms second quantum (halve the modelled
   connection interval; it must halve while `W` does not). Both need a
   `~/Projects/armemul` change; this pass made none.
3. **Q3 is calibrated but weak** (§3.4). It catches nothing in the current
   ladder and I did not tighten it, because the inert pad alone produces a
   33 ms spread on `spim_a` navigation.
4. **`slot_edge_margin` is not measurable** (§4b) and therefore not published.
   Metastability can only be decided by the inert-pad probe, and this report
   requires it rather than discharging it: **no image in the ladder except the
   base and stage 04 has been probed.**
5. **The committed oracles were NOT regenerated.**
   `recon/emulator/reports/display_sensor_oracle{,_dashboard}.json` still carry
   the tautology's `separated: true` and lack `separation_ratio`. Regenerating
   them is one command per stimulus (§11) and I did not run it, because it
   rewrites committed reference files and four golden framebuffers in a pass
   whose own measurements are already taken. It should be the next pass's first
   action, and the diff is predicted in advance: **0 fields removed, 18 added,
   5 `separated` booleans flipped to `false`, framebuffers byte-identical.**
6. **The `P0 segmentation` split heuristic catches the leading half only**
   (§7.3). The trailing half is still charged `P1 content`.
7. **Only four seeds.** `R_seed = 50.110 ms` and `Σ` are the maxima over four
   seeds, two stimuli — an empirical floor, not a bound. More seeds can only
   raise them, and raising them makes the *annotation* wider, never the gate.
8. **The `spim_a` navigation `P1 content` failure is untouched.** One animation
   frame train exists in shipped and not in ours and vice versa, on every image.
   Q4 still fails it, correctly. This pass did not look at it.
9. **The −37.3 ms navigation / −29.0 ms dashboard structural offsets our builds
   carry against shipped on every image are still unexplained.** They are now
   *isolated* — they are exactly what `r` measures against shipped once `k` is
   removed, and they are stable to within 0.75 ms across seven images including
   both pads — which makes them a much sharper target than before. Not chased.
10. **The net core was not built and not touched.** `check_net_raw_literals` and
    `verify_net_stock_data_window` were **NOT RUN**. The frozen net image is
    byte-for-byte as found: `225,581 B`.
11. **`cfg_verify` was not run and is not cited anywhere.** Every number here
    comes from a seeded Renode capture, an oracle JSON, a `cmp`, or a grep.
12. **`battery_model_state_update` (`FUN_0000c358`)** — still the open float
    defect `AGENTS.md` §1b names. Untouched.
13. **Nothing was committed.** The tree is left dirty.

### 9.1 Gates re-run in this pass (only those needing no build)

| gate | result |
|---|---|
| `tools/verify_data.py` | **995 / 995 files, 56,279 / 56,279 B, 100.00 %** |
| net core | **UNTOUCHED — `g1-i30e-net/zephyr/zephyr.bin` 225,581 B**, booted in all six new captures |
| shipped capture determinism | **every trace and both framebuffers byte-identical** to the day-old reference (§2.1) |
| golden framebuffers through the patched oracle builder | **byte-identical**, `cmp` exit 0 (§7.1) |
| `nm -u`, duplicate globals, pin gates, `check_thread_create_stack_args` | **NOT RUN** — they need a linked ELF and this pass built nothing |

---

## 10. Footprint

```
 M recon/emulator/scripts/build_display_sensor_oracle.py
       G1_BURST_GAP_NS env override (default UNCHANGED at 5 ms);
       SEPARATION_RATIO = 4.0 replacing the tautological `separated`;
       separation_ratio / separation_ratio_required /
       separated_by_construction_LEGACY published; comment block corrected.
       Proved 0-fields-removed against HEAD on the same capture.
 M recon/emulator/scripts/phase_tolerant_compare.py
       P0 segmentation now covers the SPLIT direction as well as the merge.
       Regression-checked: no verdict and no `streams failing` count moved.
?? recon/emulator/scripts/slot_quantised_compare.py    (new -- the rule)
?? recon/analysis/criterion_bound_redesign.md          (this file)
```

**Not written:** `recon/refactor/**` (the concurrent agent's — every change
`git status` shows there is theirs), any stage tree, any committed oracle JSON,
any golden framebuffer, `recon/symbolized/**`, `recon/app/src`, `recon/net/**`,
`recon/symbols`, `recon/headers`, `recon/application`, `recon/board`, `tools/`,
any linker script, and nothing under `~/Projects/armemul`.

Outside the repository:

```
/private/tmp/g1-i47/shipcap.sh, queue1.sh, sw*.sh, seed*.sh, gate.sh, reg.sh,
                    oraclediff.sh, mko.sh, inv.sh, g1-seed-*.resc
/private/tmp/g1_i47_{shipA_nav,shipB_nav,shipC_nav,shipD_nav,
                     shipB_dash,shipC_dash}          six new SHIPPED captures
/private/tmp/g1-i47/{o_head,o_head2,o_new,o_790}     oracle-diff working set
<scratchpad>/i47/{slotwise.py,constants.py}
<scratchpad>/i47/T{790000,5000000}/**                the six new oracles
```

---

## 11. Reproducing

```sh
cd /Users/freedomcoder/Projects/G1disasm2
V="env PYTHONSAFEPATH=1 .venv/bin/python"
S=<scratchpad>

# 1. the control that decides everything: SHIPPED at four seeds
bash /private/tmp/g1-i47/shipcap.sh shipA_nav  305419896  nav      # == the reference
bash /private/tmp/g1-i47/shipcap.sh shipB_nav  2596069104 nav
bash /private/tmp/g1-i47/shipcap.sh shipC_nav  1732584193 nav
bash /private/tmp/g1-i47/shipcap.sh shipD_nav  13579      nav
bash /private/tmp/g1-i47/shipcap.sh shipB_dash 2596069104 dash
bash /private/tmp/g1-i47/shipcap.sh shipC_dash 1732584193 dash
# WAIT for renode to EXIT before building an oracle (iteration 46 section 46.8)
bash /private/tmp/g1-i47/mko.sh 790000 shipA_nav:/private/tmp/g1_i47_shipA_nav:nav ...

# 2. the published rule applied to a pair containing NO build of ours
$V recon/emulator/scripts/phase_tolerant_compare.py derive-bound \
   $S/i46/T790000/ship_nav/display_sensor_oracle.json \
   $S/i47/T790000/shipC_nav/display_sensor_oracle.json \
   $S/i46/T790000/ship_dash/display_sensor_oracle_dashboard.json \
   $S/i47/T790000/shipC_dash/display_sensor_oracle_dashboard.json
#   -> DERIVED PHASE BOUND 141.170 ms   (vs 145.440 ms against our own base)

# 3. the constants
$V $S/i47/constants.py 790000

# 4. THE GATE
$V recon/emulator/scripts/slot_quantised_compare.py gate \
   BASE.json STAGE.json SHIPPED.json LABEL
#   defaults W=100.513 R=1.160 seed-floor=50.110, all three overridable
bash /private/tmp/g1-i47/gate.sh          # the whole ladder, T=0.790 ms
T=5000000 bash /private/tmp/g1-i47/gate.sh # ... and at 5.000 ms: same verdicts

# 5. the oracle-builder patch, proved additive
bash /private/tmp/g1-i47/oraclediff.sh
# and the threshold, now sweepable from the repository:
G1_BURST_GAP_NS=790000 $V recon/emulator/scripts/build_display_sensor_oracle.py CAP OUT
```

---

## 12. The one-paragraph answer

The bound was never a measurement of our build: applied to the shipped firmware
against **itself** at a different emulator seed, the published derivation rule
returns **141.170 ms** against its published **145.440 ms**. Replacing it, the
displacement is measured as a **median** rather than a maximum and decomposed
against the stimulus lattice `W = 100.513 ms`; the integer slot count `k` is
reported and never gated, and the gate is the **sub-slot residual** against
`R = 1.160 ms` — the larger of the lattice's own dispersion (0.563 ms) and the
cost of 204 bytes of inert `.rodata` (1.160 ms). Nothing in `W`, `R`, `Σ` or the
seed floor comes from how far our build sits from shipped, so **a firmware
repair can no longer widen the gate**, and the 204-byte pad that flipped the old
gate now moves `r` by 0.120–1.160 ms and flips nothing. Re-gated on iteration 46's captures: stages 01–06
and both inert-pad images **PASS at both burst-gap thresholds on both stimuli**
— where the published criterion charges the base-plus-inert-pad image with a
REGRESSION at both thresholds —
old stage 07 **FAILS on 5 of 6 streams** with a −119.510 ms display move that is
1.189 slots and a +31.250 ms move landing identically on three independent
`twim1` devices — a real, coherent, non-lattice change. Two claims the project
carried as firmware findings — the three `npm1300` `P2 population` failures and
the `npm1300` `P5 order` inversion — **reproduce shipped-against-shipped at a
different seed, to the microsecond, and are hereby withdrawn as evidence.**
