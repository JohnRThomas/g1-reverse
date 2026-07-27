# The phase-tolerant stream criterion — design, derivation, and the re-run gate

**Written incrementally as the work ran. Nothing committed. Every number below
comes from a command that was actually run; where a claim is later corrected it
is corrected in place with a note rather than deleted.**

The owner chose the **phase-tolerant criterion** over (i) re-baselining the two
`p1_boot` streams and (ii) abandoning the cohesive merge, on the stated ground
that it **keeps both streams gated** rather than exempting them. That constraint
is what this design is built around.

---

## 0. Inputs, and a concurrency note taken at the start

```
HEAD                     3d3ee155  "Stage 04-B FAILS R7: there is NO LANDING
                                    BETWEEN THE SLOTS -- size compensation refuted"
working tree at start    clean except ?? Even+Realities_1.9.0.xapk
driver.py status         stages 00-08 ALL CURRENT (2,629 / 2,631 / 1,716
                         inputs unchanged, 0 changed); 99 stale (retired probe)
stage trees on disk      materialised 11:48-12:26 by the stage04b pass
```

Everything measured in this report was taken at **those** inputs.

**At 13:02:49 the concurrent parity agent rewrote 130+ `recon/symbolized/app/*.c`
files** (`bt_enable.c`, `imu_fusion_thread.c`, … — `ls -lT` timestamps) plus
`recon/app/src/FUN_00012db0.c`, `recon/named/`, `recon/readable_sources/`, and
added `recon/analysis/type_disagreement_repair_3.md`. `driver.py status` now
reports **stage 00 stale on 104 inputs**.

My four builds completed at **12:55:23 (stage 01), ~12:57 (stage 02), ~12:59
(stage 06) and 13:01:46 (stage 07)** — all before 13:02:49 — and the base /
stage 03 / stage 04 / stage 05 builds are the stage04b pass's, from the same
tree state. **No build in this report read a moving input**, and every image
compared here derives from one consistent input set. The stages must be
regenerated before the next measurement; that is the staleness mechanism
working, not a defect (README "Staleness and repair").

Reused, verbatim and unmodified, from the stage04b pass's scratch:

| artifact | what |
|---|---|
| `/private/tmp/g1_ship_seed_q1` | seeded **shipped** navigation capture |
| `/private/tmp/g1_ship_seed_dash_d1` | seeded **shipped** dashboard capture |
| `/private/tmp/g1_s4b_{base_nav1,base_dash}` | in-tree base |
| `/private/tmp/g1_s4b_s03_nav1` | stage 03 |
| `/private/tmp/g1_s4b_{s04_nav1,s04_nav2,s04_dash}` | stage 04-B |
| `/private/tmp/g1-s4b-{base,s03,s04,s05}` | the four builds |

New in this pass: builds `/private/tmp/g1-pt-s0{1,2,6,7}` and captures
`/private/tmp/g1_pt_s07_{nav1,dash,nav2}`.

### 0.1 Which images actually need a capture — measured, not assumed

```
cmp g1-pt-s01/zephyr/zephyr.bin  g1-pt-s02/zephyr/zephyr.bin   -> IDENTICAL
cmp g1-pt-s02/zephyr/zephyr.bin  g1-s4b-s03/zephyr/zephyr.bin  -> IDENTICAL   956,356 B
cmp g1-pt-s06/zephyr/zephyr.bin  g1-s4b-s05/zephyr/zephyr.bin  -> IDENTICAL   956,276 B
cmp g1-s4b-s04/zephyr/zephyr.bin g1-s4b-s05/zephyr/zephyr.bin  -> IDENTICAL   (stage04b pass)
```

| image | FLASH | `runtime_info_sync` | `_end` |
|---|---:|---|---|
| in-tree base | 956,480 B | `0x00015c04` | `0x2003ff45` |
| **stage 01 = stage 02 = stage 03** | **956,356 B** | `0x00015c04` | `0x2003ff45` |
| **stage 04-B = stage 05 = stage 06** | **956,276 B** | `0x00016c14` | `0x2003ff45` |
| **stage 07** | **955,996 B** | `0x00016c14` | `0x2003ff45` |

So **three distinct images** cover stages 01–07, and the stage04b pass's
captures already cover two of them. Only stage 07 needed new Renode runs.
`$rtinfo_pc` for stage 07 is `0x00016c14` — the **same** fifth value as stage
04-B, not a sixth; re-read from the ELF, not assumed.

`driver.py size-gate`, run at these builds:

| stage | declared | measured | `text` Δ | `rodata` Δ | `oracle_required` |
|---|---|---|---:|---:|---|
| 06 unit_composition | `byte-identical` | **byte-identical** | 0 | 0 | false |
| 07 internal_linkage | `size-changing` | size-changing | **−276** | **−8** | **true** |

---

## 1. What the existing criterion actually measures — and does not

`cmp3.py`'s 69 fields all come from
`peripherals/<bus>/phases/<phase>/{transaction_count,stream_sha256}` and its
per-device children. Reading the code rather than the prose:

* `i2c_canonical_line(t)` is `DEV|DIR|PAYLOAD`. **There is no timestamp in it.**
* the only place time enters is the **phase split** — the capture script cuts
  every trace at `RunFor 6` and again at `RunFor 14`.

So the strict criterion is **phase-blind on content and phase-brittle at the
wall**: a train may slide arbitrarily far in time and score EQ, right up to the
moment one burst crosses the 6 s boundary, at which point *both* phases' counts
and *both* phases' hashes change at once. That is precisely the failure mode
the stage04b gate recorded.

A phase-tolerant criterion is therefore not only a relaxation. Replacing the
wall anchor with a train anchor **removes** a sensitivity that was never
intentional, and adding an explicit phase bound **adds** a check that does not
exist today.

---

## 2. The criterion

Implemented in **`recon/emulator/scripts/phase_tolerant_compare.py`**, fed by an
**additive** block `peripherals/<bus>/whole_run_trains` that
`build_display_sensor_oracle.py` now writes. Every pre-existing oracle field is
untouched (proved in §5).

### 2.1 Decomposition

**Burst** — a maximal run of consecutive transactions on one `(bus, device)`
separated by at most `BURST_GAP_NS = 5 ms`.

5 ms is a constant, but its **validity is asserted per capture** rather than
assumed (C7c: never key a rule on an unchecked constant). Measured gap
distribution, shipped navigation capture, whole run:

| stream | max intra-burst gap | min inter-burst gap | separated |
|---|---:|---:|---|
| `spim_a` jbd_display | 4,270,000 ns | 5,290,000 ns | yes |
| `twim1` npm1300 | 2,330,000 ns | 5,062,990 ns | yes |
| `twim1` opt3001 | 790,000 ns | 49,642,120 ns | yes |
| `twim1` st25dv_system_port | 4,150,000 ns | 6,220,000 ns | yes |
| `twim1` st25dv_nfc_eeprom | 3,141,880 ns | 5,190,000 ns | yes |
| `twim2` lsm6dso | 4,350,000 ns | 5,591,850 ns | yes |

The valley is **narrow** — 1.0 ms on `spim_a`, 0.9 ms on `twim1` npm1300 — so
`gap_separation.separated` is published per device per capture and a comparer
that sees `false` must not trust the segmentation.

**Train** — the bursts sharing one key, in time order. The key is the burst's
**register programme**: every *write* payload verbatim, every *read* reduced to
`(selected register, payload length)`.

The rationale is structural, not a threshold: **a write payload is the firmware
talking; a read payload is the model talking.** Keying on writes is what makes
train membership stable when a modelled sensor value crosses a threshold at a
slightly different virtual time. Measured justification — per-register read
variability over the shipped navigation run:

```
npm1300 reg=0x03  reads=190  distinct=8      <- charger state machine
npm1300 reg=0x04  reads=7    distinct=3
lsm6dso reg=0x28  reads=549  distinct=59     <- the modelled gesture waveform
lsm6dso reg=0x22  reads=549  distinct=1
opt3001 reg=0x00  reads=46   distinct=1
opt3001 reg=0x01  reads=3    distinct=3
```

Keying on the full content puts the `npm1300 0x03` bursts into **different
trains depending on when the charger state changed**, which is exactly the
instability that made the first attempt at this measurement produce a δ of
−3,706 ms on a population-equal train (recorded below in §3.1 as a rejected
approach).

### 2.2 The gates

| | gate | what it catches |
|---|---|---|
| **P1** | the **set of train keys** must be identical | a changed register, a changed write payload, a changed read length, a burst whose shape changed, a transaction added inside a burst |
| **P2** | per-train burst **populations** must be equal, or differ only by bursts the **observation wall clipped** — checked by extrapolating the train's *own measured median period* across the 20 s wall and requiring the extra/missing burst to land within the bound of the predicted time | a burst genuinely added or dropped anywhere except at the wall |
| **P3** | `\|starts_ns[i]^ours − starts_ns[i]^shipped\| ≤ Δ` for every burst whose correspondence is unambiguous | a train displaced by more than Δ |
| **P4** | **cadence, gated THROUGH P3** | a period error `e` accumulates; after `⌈Δ/e⌉` bursts `\|δ\|` exceeds Δ. On the 45-burst OPT3001 poll train this catches a period error above `Δ/44` = **3.3 ms on a 350.3 ms period, 0.94 %** |
| **P5** | an **order inversion** between two bursts more than Δ apart in the shipped run is a failure | a reordering that is not a bounded phase shift |

**Unambiguity (P3's applicability), stated structurally.** Burst *i*'s
i-th-to-i-th match is unambiguous iff `|δ_i|` is less than **half the local
period** around burst *i* in the shipped train (the smaller of the gaps to its
neighbours). Above that, burst *i* in one run is nearer to burst *i±1* of the
other and the correspondence carries no information. Bursts failing this test
are reported as `????` and their **phase is not gated** — their content (P1)
and population (P2) still are. This is not a tolerance; it is the point at
which the measurement stops existing.

**Why P5 is the teeth.** Ordering is enforced *through time*, not through
index. Two bursts may swap only if a shift within Δ explains it. The
LSM6DSO regression the stage04b pass decoded — a periodic ODR-reconfiguration
block crossing a poll pair — is admitted **only because both bursts stay within
Δ of their shipped counterparts**; a swap between bursts 9.9 s apart is
reported as `P5 order`, and in fact **the in-tree base fails P5 on `twim1`
npm1300 for exactly that reason** (§4.1), which is a pre-existing defect the
strict criterion never surfaced.

---

## 3. Deriving the bound — measurement first, verdict afterwards

**The rule was fixed before any stage was compared:**

> Δ = the maximum `|δ|` over **phase-measurable** trains between the **shipped
> firmware** and **our in-tree build**, over **both** stimuli and **every**
> traced bus.

**Why this population and not another.** The criterion's job is to separate
refactor damage from what the project's own accepted baseline already contains.
A bound *below* the baseline's own disagreement is not a stricter gate — it is a
**blind** gate: every stream becomes a pre-existing failure and the three-way
comparison stops discriminating. That is not an argument about convenience; it
is checked in §4.4, where at the alternative bound the *base itself* fails the
streams under test.

### 3.1 Two derivations that were tried and rejected, with their numbers

**(a) The codegen noise floor.** `base ↔ stage 03` is a −4 B `.text` / −124 B
`.rodata` relink that the stage04b gate measured as bit-identical on all 69
fields. Max `|δ|`: **1.226 ms** (npm1300), 0.182 ms (opt3001), 0.120 ms
(lsm6dso). Iteration 43's +2 B relink gave 0. **Rejected:** at Δ = 1.3 ms the
in-tree base fails the phase gate on every stream, including all four it
currently passes.

**(b) A scheduler-quantum derivation.** §4 of `stage04b_r7_validation.md` shows
the displacement is quantised at ≈100.5 ms, which would be a principled bound
*if the quantum could be tied to a mechanism*. It cannot, on the evidence
available: `CONFIG_SYS_CLOCK_TICKS_PER_SEC=32768` (30.5 µs, read from
`/private/tmp/g1-s4b-base/zephyr/.config`), the BLE virtual central's connection
interval is 30 ms with `SweepDwell 4` = 120 ms
(`armemul/models/BLE_VirtualCentral.cs:372`, `:69`), and a scan of **every**
traced peripheral's burst cadence in the shipped capture finds
**no ≈100.5 ms period anywhere**:

```
spim_a       66.6 ms x149     twim1:0x45   350.3 ms x28
twim1:0x6B   20.1 x137, 200.0 x61          twim2:0x6B  38.1 x236, 10.1 x194, 80.1 x107
```

**Rejected: I could not measure the mechanism, so I will not derive a bound
from it.** (This also retires my own first guess that the quantum was a Zephyr
system tick.)

**(c) Train identity by full burst content.** Rejected on measurement: it puts
`npm1300` bursts into different trains as the charger state register steps, and
produced `dphase −3,706.60 ms … +7,498.63 ms` on population-equal trains between
**shipped and the in-tree base**. Replaced by the register-programme key (§2.1).

### 3.2 The derivation, as run

```
$ phase_tolerant_compare.py derive-bound \
    rep_ship_nav/display_sensor_oracle.json  rep_base_nav1/display_sensor_oracle.json \
    rep_ship_dash/..._dashboard.json         rep_base_dash/..._dashboard.json
```

| pair | stream | measurable trains | ambiguous | max `\|δ\|` |
|---|---|---:|---:|---:|
| **navigation** | `spim_a` jbd_display | 26 | 2 | **145.440 ms** |
| | `twim1` npm1300 | 9 | 3 | 45.870 ms |
| | `twim1` opt3001 | 3 | 0 | 10.930 ms |
| | `twim1` st25dv_nfc_eeprom | 4 | 0 | 28.260 ms |
| | `twim1` st25dv_system_port | 2 | 1 | 28.260 ms |
| | `twim2` lsm6dso | 4 | 1 | 8.790 ms |
| **dashboard** | `spim_a` jbd_display | 9 | 2 | 7.810 ms |
| | `twim1` npm1300 | 9 | 3 | 28.260 ms |
| | `twim1` opt3001 | 3 | 0 | 7.810 ms |
| | `twim1` st25dv_nfc_eeprom | 4 | 0 | 28.260 ms |
| | `twim1` st25dv_system_port | 2 | 1 | 28.260 ms |
| | `twim2` lsm6dso | 4 | 1 | 7.800 ms |

> ### **Δ = 145.440 ms**

### 3.3 The train that sets it, inspected rather than trusted

The bound comes from the navigation display animation. Four `n=4`/`n=5` trains
of 22-transaction pixel-window bursts, **minimum period 2,265.1 ms**, so
`|δ| = 145 ms` is 6 % of a period and the correspondence is forced, not chosen:

```
train 02042420FF00000000000000000000|00|02042820FF...   (n=4, burstlen 22)
  shipped 5.620470  7.885550  10.150620  12.588180
  ours    5.583150  7.848230  10.113330  12.442740
  delta   -37.320   -37.320    -37.290   -145.440  ms
```

Three cycles in lock-step at −37.32 ms, then one **slip of −108.15 ms**. Two
sibling trains give −145.04 ms, one −96.16 ms, one `n=5` gives −75.10 then
−61.82 ms. It is a *step*, not a drift.

**This is the strongest available evidence that a displacement of this size is
not a behavioural difference**, because on this very stream:

* whole-run `spim_a` is **3,645 == 3,645** transactions, exact on shipped and on
  our build (`stage04b_r7_validation.md` §3.6);
* **all four framebuffers are byte-identical to the committed goldens**, 153,600
  B each, `cmp` exit 0.

A 145 ms slip in the display transaction stream changes **not one pixel**.

**The objection I have to state against my own number.** `spim_a` navigation is
*also* a known open gap (`sensor_parity_status.md` §41: our `NAVIGATION_ACTIVE`
transition is 110 ms early, and one animation frame differs — it is the `P1
content` failure in §4.1). Deriving a tolerance partly from a stream that is
itself unresolved is uncomfortable. It is not circular — the slip measured here
occurs between 10.15 s and 12.5 s, six seconds after the `NAVIGATION_ACTIVE`
transition, and is a different event — but a reader who rejects `spim_a` as a
source would derive **Δ = 45.87 ms** from `twim1` npm1300 instead. **§4.4
reports the gate at that bound too, so the verdict's sensitivity to this choice
is visible rather than hidden.**

Δ is used **exactly as measured**, 145.440 ms, not rounded up. The in-tree base
therefore sits *exactly at* the bound with zero headroom, by construction.

---

## 4. The gate, re-run

### 4.1 Stages 01, 02, 03 — the criterion must not flip a passing stage

Image byte-identical across all three; capture `g1_s4b_s03_nav1`.

```
=== phase-tolerant three-way, bound 145.440 ms : shipped | base | S01_03 ===
-- BOTH_PASS : 4
   twim1 opt3001_ambient_light      base=PASS  S01_03=PASS   10.930 -> 10.930 ms
   twim1 st25dv_nfc_eeprom          base=PASS  S01_03=PASS   28.260 -> 28.260 ms
   twim1 st25dv_system_port         base=PASS  S01_03=PASS   28.260 -> 28.260 ms
   twim2 lsm6dso_imu                base=PASS  S01_03=PASS   10.620 -> 10.590 ms
-- PRE_EXISTING_SAME : 2
   spim_a jbd_display   base profile {'P1 content':2,'P2 population':1}  == stage
   twim1  npm1300       base profile {'P3 phase':1,'P5 order':1}         == stage
-- PRE_EXISTING_WORSE : 0
-- REGRESSION : 0
REFACTOR REGRESSIONS: 0   PRE-EXISTING-BUT-WORSE: 0
```

**PASS.** No previously-passing stream flips. Two streams fail on **both** the
base and the stage, identically:

* `spim_a` — `P1 content` ×2 (one shipped animation-frame train absent from
  ours, one present only in ours) plus `P2 population 33 → 34`. This is the
  §41 one-extra-frame residue, and the criterion **still fails it** — content,
  not phase.
* `twim1` npm1300 — `P3 phase` ×1 and **`P5 order`: two bursts 9,904.330 ms
  apart in the shipped run swapped order.** That is a pre-existing ordering
  defect in our build that the strict per-phase hash never isolated, because
  the merged `twim1` bus hash was already NE for other reasons.

### 4.2 Stage 04-B (= stage 05 = stage 06)

```
=== NAVIGATION, bound 145.440 ms : shipped | base | S04B ===
-- BOTH_PASS : 4
   twim1 opt3001_ambient_light   base=PASS   10.930 ms   S04B=PASS   93.750 ms
   twim1 st25dv_nfc_eeprom       base=PASS   28.260 ms   S04B=PASS   28.590 ms
   twim1 st25dv_system_port      base=PASS   28.260 ms   S04B=PASS   28.590 ms
   twim2 lsm6dso_imu             base=PASS   10.620 ms   S04B=PASS   91.720 ms
-- PRE_EXISTING_WORSE : 2
   spim_a jbd_display   base {'P1 content':2,'P2 population':1}      max|d| 145.440
                        S04B {'P1 content':2,'P3 phase':21,'P2 population':1}
                                                                     max|d| 245.780
                        WORSE THAN BASE: P3 phase 0 -> 21
   twim1  npm1300       base {'P3 phase':1,'P5 order':1}   max|d| 1198.549
                        S04B {'P2 population':3}           max|d|   92.690
                        WORSE THAN BASE: P2 population 0 -> 3
-- REGRESSION : 0
REFACTOR REGRESSIONS: 0   PRE-EXISTING-BUT-WORSE: 2

=== DASHBOARD, bound 145.440 ms ===
-- BOTH_PASS : 4        -- PRE_EXISTING_SAME : 2
-- PRE_EXISTING_WORSE : 0   -- REGRESSION : 0
REFACTOR REGRESSIONS: 0   PRE-EXISTING-BUT-WORSE: 0
```

**The eight fields that failed the strict gate are exactly the phase effects the
new criterion admits.** `twim1 opt3001` and `twim2 lsm6dso` — the two streams
whose strict `p1_boot` counts and hashes moved — **PASS on both stimuli**, with
their content, population, cadence and order all gated and their measured
displacement (93.750 ms and 91.720 ms) inside Δ.

**But stage 04-B is not clean.** On navigation it makes the *already-failing*
`spim_a` stream worse: **21 new `P3 phase` failures**, the animation trains
moving from a peak `|δ|` of 145.440 ms to **245.780 ms**. The increase is
**+100.34 ms** — the same ≈100.5 ms slot step §4 of the stage04b report
identified, now measured on a third stream. Because the baseline sits exactly
at Δ on this stream, any further displacement in the same direction fails it.

The `twim1` npm1300 line is flagged `WORSE` by the tool's category rule but is
**not straightforwardly worse**: the stage loses the base's `P3 phase` and
`P5 order` failures (max `|δ|` 1,198.549 → 92.690 ms) and gains three
`P2 population` failures at the 20 s wall. It is *differently* wrong. Recorded
as measured; I am not going to call it an improvement either.

### 4.3 Stage 07 — internal linkage, `.text` −276 B

Three fresh seeded captures (`G1_SEED=305419896`, `$rtinfo_pc=0x00016c14`
re-read from the ELF): navigation ×2 and dashboard.

**The acceptance bar holds.** All four framebuffers `cmp`-identical to the
committed goldens, 153,600 B each, exit 0:
`golden_framebuffer_p1_boot`, `golden_framebuffer_p2_render`,
`golden_framebuffer_dashboard_p1_boot`, `golden_framebuffer_dashboard_p2_render`.

**Strict criterion (`cmp3.py`, 69 fields per stimulus):**

| | navigation | dashboard |
|---|---:|---:|
| EQ to shipped on both | 48 | 52 |
| pre-existing gap, identical | 0 | 3 |
| pre-existing gap, different value | 8 | 6 |
| **regression** | **9** | **4** |
| improvement | **4** | **4** |

Stage 07 reproduces stage 04-B's eight and adds `counters/JBD_FRAMECOUNTER_P2`
`0x0D61` → `0x0D76` on navigation; on the dashboard it breaks
`twim2/p2_render` count `1206` → **`1202`** and its `sha_regprog`. But it also
**closes three long-standing gaps outright**:

```
counters/ESB_MASTER_FRAMES   ship 0x175   base 0x176   S07 0x175   == shipped
counters/ESB_ACKS            ship 0x175   base 0x176   S07 0x175   == shipped   (both stimuli)
counters/JBD_FRAMECOUNTER_P2 ship 0x2E65  base 0x2EA3  S07 0x2E65  == shipped   (dashboard)
spim_a/p2_render/count       ship 12225   base 12289   S07 12225   == shipped   (dashboard)
```

The `ESB_MASTER_FRAMES`/`ESB_ACKS` `+1` is iteration 43 §43.11's open item and
`stage04b_r7_validation.md` §6 item 7 left it "unchanged and untouched, with its
falsification test unrun". **A −276 B relink closes it.** That is consistent
with iteration 43's own diagnosis that it is a boot-phase effect, and it is
reported, not celebrated: the same mechanism that closes it is the one that
moves everything else.

**Phase-tolerant criterion, Δ = 145.440 ms:**

```
NAVIGATION   BOTH_PASS 4   PRE_EXISTING_SAME 0   PRE_EXISTING_WORSE 2   REGRESSION 0
DASHBOARD    BOTH_PASS 4   PRE_EXISTING_SAME 2   PRE_EXISTING_WORSE 0   REGRESSION 0
```

The dashboard `twim2/p2_render` count drop is resolved by the criterion exactly
as designed, and this is the clean worked example of what it is for:

```
twim2 lsm6dso_imu   PASS/INDETERMINATE-PHASE   max|d| = 14.070 ms
  note  P2 6B|W|28|6B|R|28|n6|6B|W|22|6B|R|22|n6:
        wall-clipped: 1 burst(s) pushed past 20.000 s
```

1,206 − 1,202 = 4 transactions = **one 4-transaction poll burst**, and the
train's own median period predicts it lands beyond 20.000 s. Not a lost poll —
a poll the observation window no longer contains.

Navigation's two `PRE_EXISTING_WORSE`:

* `spim_a` — `P3 phase` 0 → **21**, peak `|δ|` 145.440 → **281.670 ms**. Worse
  than stage 04-B's 245.780 ms, in the same direction.
* `twim1` npm1300 — `P0 segmentation` ×1 and `P2 population` ×4. The `P0` is a
  **criterion artifact, not a firmware difference**, and §6.8 below records it
  with its measurement.

#### 4.3.1 The §9 prediction — 5 of 6 confirmed, 1 falsified

`stage04b_r7_validation.md` §9 predicted, in advance, what a stage-07 capture
must show if the two-slot model is right:

| prediction | measured | |
|---|---|---|
| `twim1 p1_boot` **373** | **373** | ✔ |
| OPT3001 `p1_boot` **35** | **35** | ✔ |
| OPT3001 sha **`b759ccc5…`** | **`b759ccc5…`** | ✔ |
| merged `twim1 p1_boot` sha **`4f49068a…`** | **`47a3cad0…`** | ✘ **falsified** |
| `twim2 p1_boot` 1,089 sha **`03537cda890a2b7d…`** | **`03537cda890a2b7d…`** | ✔ |
| `twim2 p1_boot` `regprog` **`6d3c4072…`** | **`6d3c4072…`** | ✔ |
| OPT3001 poll #13 at **≈4.2036 s**, not ≈4.3042 s | **4.200620 s** | ✔ |
| all four framebuffers byte-identical | byte-identical | ✔ |

**The two-slot model survives**: at −276 B, four times stage 04-B's delta, the
train lands in the *earlier* slot, not a third one. The full bracket:

| image | `text` Δ vs in-tree | OPT3001 poll #13 | polls in `p1_boot` |
|---|---:|---|---:|
| shipped | — | 4.295524 s | 17 (33) |
| in-tree base | 0 | 4.304162 s | 17 (33) |
| stage 01 = 02 = 03 | −4 | 4.304192 s | 17 (33) |
| stage 04-B = 05 = 06 | −80 | 4.203640 s | **18 (35)** |
| **stage 07** | **−356** | **4.200620 s** | **18 (35)** |

**One quantitative correction to §4 of that report.** It says three images
spanning −16 B to −92 B land in the earlier slot "**within 0.5 ms of each
other**". Stage 07 lands **3.02 ms** from stage 04-B — same slot, six times that
spread. The slot is real; the 0.5 ms tightness was a property of the three
images measured, not of the mechanism.

**The falsified item is the one that should have been falsified.** The merged
`twim1` bus sha hashes the *interleaving* of OPT3001, nPM1300 and two ST25DV
ports — three independent firmware threads sharing one bus. Every per-device
sha is exactly as predicted; only the cross-device interleaving differs, and
the oracle's own `determinism_verification` block has flagged that merged hash
as unstable since it was written. The prediction should not have included it.

### 4.4 Sensitivity of the verdict to the bound

The alternative derivation of §3.1 — reject `spim_a` as a source, take
Δ = 45.870 ms from `twim1` npm1300 — changes the answer, so it is reported
rather than buried:

| stage, navigation | Δ = 145.440 ms | Δ = 45.870 ms |
|---|---|---|
| 01 / 02 / 03 | 0 regressions, **0 worse** | 0 regressions, **1 worse** |
| 04-B / 05 / 06 | **0 regressions**, 2 worse | **2 regressions**, 2 worse |
| 07 | **0 regressions**, 2 worse | **2 regressions**, 2 worse |

At Δ = 45.870 ms the two regressions are `twim1 opt3001` (`P3` 91.730 ms and a
`P2` extra burst at 19.981110 s that the wall extrapolation then cannot explain)
and `twim2 lsm6dso` (`P3` 91.720 ms, `P5` order) — i.e. **exactly the two
streams the owner asked to keep gated**, failing again.

And the tighter bound **flips a stage that is measurably a no-op**:

```
S01_03  twim1 npm1300   base {'P3 phase':1,'P5 order':1}
                        S01_03 {'P3 phase':2,'P5 order':1}
        WORSE: P3 phase 1 -> 2
        FAIL  P3 phase: |delta| 45.930 ms > bound on 4/64 bursts
```

45.930 versus a bound of 45.870 — **60 microseconds**, on an image whose only
difference from the base is a −4 B / −124 B relink. That is the "blind gate"
failure mode of §3 made concrete: a bound set at or below the baseline's own
disagreement has no headroom and reports the noise floor.

**I am reporting the outcome at the bound I derived, and the outcome at the one
I rejected, and I am not choosing between them on the basis of which admits
stage 04.** The rule was fixed first; Δ = 145.440 ms follows from it.

---

## 5. The stale shipped navigation oracle — regenerated

`recon/emulator/reports/display_sensor_oracle.json` was regenerated from the
seeded shipped capture `/private/tmp/g1_ship_seed_q1`; the dashboard oracle from
`/private/tmp/g1_ship_seed_dash_d1`. The committed files were saved first to
`/private/tmp/g1-pt/old_reports/`.

**The four golden framebuffers are byte-identical after regeneration**
(`cmp` exit 0, all four) — the regeneration touched no pixel.

### 5.1 Navigation: 8 measured differences, every one attributed

| field | committed | regenerated | cause |
|---|---|---|---|
| `counters/RADIO_TX` | `0x230` | **`0x232`** | **staleness** — the file predates `emulation SetSeed` (iteration 41); the radio frame count is seed-dependent |
| `counters/VC_DATA_EVENTS` | `0x215` | **`0x212`** | **staleness** — same seed cause |
| `counters/SCREEN_ID_ctx_d5` | *absent* | `0x0A` | **staleness** — the counter was added to the capture script afterwards |
| `peripherals/radio_esb/ble_radio_transmitted_frames` | `0x230` | `0x232` | same field as `RADIO_TX` |
| `twim1/p1_boot/stream_sha256` | `ef6fcb11…` | **`33cbd8c1…`** | **staleness** — the merged `twim1` bus interleaving is exactly what the seed pins |
| `twim1/p2_render/stream_sha256` | `f418e5ba…` | `329565e4…` | same |
| `saadc/whole_run/stream_sha256` | `660cdf3b…` | `ebf06b30…` | **script change** — iteration 42's RAM-pointer canonicalisation |
| `jbd_journal_tail` (40 entries) | — | — | **staleness** — the last 40 journal lines carry sequence numbers and timestamps that the seed moves |

Plus **20 fields the committed file does not carry at all**, none of them mine:

* 8 `saadc/whole_run/pointer_*` and `stream_sha256_raw_pointers` — iteration 42's
  pointer canonicalisation, published so the strict value stays measurable;
* 12 `twim2/**/{stream_sha256_regprog, analogue_sample_*}` — iteration 42's
  analogue-sample canonicalisation.

And **357 fields from this pass's `whole_run_trains` block**.
**0 fields were removed.**

Confirmation that comparing against the committed file would have hidden
failures: `twim1/p1_boot/stream_sha256` and `counters/RADIO_TX` are two of the
eight strict stage-04-B regressions, and both were *already* different in the
committed file.

### 5.2 Dashboard: purely additive, as predicted

```
REMOVED-only-in-OLD: 0   ADDED-only-in-NEW: 444   CHANGED: 0
  of ADDED, from the new phase-tolerant block: 444 ; other: 0
```

**0 of 69 fields changed**, confirming the stage04b pass's claim that the
dashboard oracle was current, and confirming that the oracle-builder change is
**strictly additive**: no existing field moved on either oracle.

**No criterion text was retired**, so there is no `WITHDRAWN_annotations` block
to write. `parity_criteria` (G-1…G-6, S-*) and `determinism_verification` are
carried through byte for byte; the new criterion is published alongside them as
`peripherals/<bus>/whole_run_trains/criterion`.

---

## 6. What the criterion stops catching

Published so the residue stays measurable. Each item names the field that keeps
it inspectable.

1. **The absolute placement of a periodic train in wall time, up to 145.440 ms.**
   A wrong sleep constant, a dropped tick, or a thread-priority inversion whose
   whole effect is a displacement below Δ is now invisible to P1–P5. This is the
   class `stage04b_r7_validation.md` §4.3 named, and it is real: iteration 43's
   frozen clock was found by a stream comparison, not by pixels.
   *Kept measurable by:* the strict `phases/<phase>/{transaction_count,
   stream_sha256}` fields, unchanged; and by the per-stream `max|delta|` the
   comparer prints for **every** stream including passing ones.
2. **Read payload bytes are not part of the train key.** A read payload is model
   output, so the key uses `(register, length)` instead. A defect that makes the
   model return different values *without* changing any firmware write is not a
   P1 failure.
   *Kept measurable by:* `stream_sha256` (reads included) and, for the IMU,
   `analogue_sample_payloads` / `stream_sha256_regprog`.
3. **Burst counts at the observation wall.** P2 admits a burst that the 20 s wall
   clipped, when the train's own median period predicts it back within Δ. A
   genuine extra poll that happens to occur in the last Δ of the run is
   therefore admissible.
   *Kept measurable by:* the strict per-phase `transaction_count`, and by the
   `note` lines the comparer prints for every wall-explained population change.
4. **Phase on trains whose correspondence is ambiguous.** On the LSM6DSO poll
   train the minimum local period is 10.100 ms while `|δ|` reaches 9.25 ms
   (navigation) and 13.88 ms (dashboard), so **part of the largest stream in the
   oracle has no phase gate at all**. Content and population are still gated.
   *Kept measurable by:* the `????` lines, which print how many bursts of how
   many were excluded and the largest excluded `|δ|`.
5. **Ordering among bursts closer together than Δ.** P5 admits any permutation
   inside a 145.440 ms window. Two device transactions 100 ms apart may swap.
   *Kept measurable by:* `worst_admissible_inversion_ms`, and the strict
   `stream_sha256`, which is order-sensitive to the transaction.
6. **`npm1300` phase is not evidence.** Its trains carry a charger state
   register that steps during the run; three trains per stimulus are reported
   ambiguous with `|δ|` up to 7,497.653 ms. Treat `twim1 npm1300` P3 results as
   indeterminate.
7. **Everything outside the traced buses.** `counters/RADIO_TX`, `ESB_*`,
   `saadc`, `pdm0`, `gpiote*` have no train decomposition and are **not** covered
   by this criterion at all — they remain gated strictly by `cmp3.py`. Note that
   `RADIO_TX` — one of the eight strict stage-04-B regressions — is therefore
   **not** absorbed by the phase-tolerant criterion; it is simply outside it.
8. **A shared bus can merge two independent bursts, and that is a FALSE
   POSITIVE, not a miss.** Measured on stage 07, navigation, `twim1` npm1300:

   ```
   shipped   3.906360  6B|W|080001   (the previous 070401 is > 5 ms earlier)
   stage 07  3.808650  6B|W|070401
             3.811750  6B|W|080001   gap 3.100 ms  -> ONE burst
   ```

   The `080001…` init burst moved −94.7 ms (the familiar slot step) and a
   `070401` from the 200 ms-periodic train happened to land 3.100 ms ahead of
   it, inside `BURST_GAP_NS`. The two segment as one, producing a train that
   exists as no firmware programme on either side. `gap_separation.separated`
   is `true` on every capture in this pass, so the assertion does **not** catch
   it — the collision is between *different devices' trains on one device's
   stream*, not a violation of the intra/inter void.

   The comparer now names it `P0 segmentation` (a train appears only in ours
   and its key *begins* with another train's key) so it is visible rather than
   miscounted as `P1 content`. **It is still reported as a failure** — I did not
   make it pass. The proper repair is to calibrate the burst gap per device from
   the shipped reference (shipped `twim1` npm1300 max intra-burst gap is
   2,330,000 ns, which would have split it); that is not done and is filed in §8.

**The strict values are not replaced.** `cmp3.py`'s 69 fields are still computed
and still reported (§4.2 and §4.3 quote them for stages 04-B and 07), exactly as
iteration 42 published `stream_sha256_raw_pointers` and
`analogue_sample_payloads` next to the canonicalised ones.

---

## 7. VERDICT

**Determinism, re-verified at this pass's images.** `diff -r` of the
regenerated oracle directories for stage 07 navigation run 1 vs run 2:
**no output**. A single seeded run is evidence.

| stage | image | codegen class | strict `cmp3` | **phase-tolerant, Δ = 145.440 ms** |
|---|---|---|---|---|
| **01** literal_inline | 956,356 B | byte-identical | *(covered by stage 03's image)* | **PASS** — 0 regressions, 0 worse |
| **02** block_dedupe | = 01 | byte-identical | *(same image)* | **PASS** — 0 regressions, 0 worse |
| **03** module_structure | = 01 | byte-identical | 0 regressions | **PASS** — 0 regressions, 0 worse |
| **04-B** cohesive_tu | 956,276 B | size-changing, `text` −76 | **8 regressions nav, 1 dash** | **PASS on every gated stream** — 0 regressions both stimuli; **2 pre-existing-but-worse on navigation** |
| **05** cohesive_composition | = 04-B | measured byte-identical | *(same image)* | inherits stage 04-B exactly |
| **06** unit_composition | = 04-B | measured byte-identical | *(same image)* | inherits stage 04-B exactly |
| **07** internal_linkage | 955,996 B | size-changing, `text` −276 / `rodata` −8 | 9 regressions nav / 4 dash, **4 improvements each** | **PASS on every gated stream** — 0 regressions both stimuli; **2 pre-existing-but-worse on navigation** |

**All four acceptance framebuffers are byte-identical to the committed goldens
on every image measured** — base, stage 03, stage 04-B, stage 07 — 153,600 B
each, `cmp` exit 0.

### 7.1 For stages 04-B, 05, 06: is the residue phase, or something real?

The eight strict navigation regressions, resolved:

| strict field | cause under the phase-tolerant criterion |
|---|---|
| `twim1 p1_boot` count 371 → 373 | **phase** — the 6 s wall; whole-run OPT3001 45 → 46 bursts, the extra one wall-clipped at 19.98 s |
| `twim1 p1_boot` OPT3001 count 33 → 35 | **phase** — same burst |
| `twim1 p1_boot` OPT3001 sha | **phase** — same burst, content identical |
| `twim1 p1_boot` merged-bus sha | **phase** — cross-device interleaving on a shared bus, flagged unstable by the oracle's own `determinism_verification` |
| `twim2 p1_boot` sha | **phase** — the ODR-reconfiguration burst crossing one poll burst; both within Δ, so admissible under P5 |
| `twim2 p1_boot` `regprog` sha | **phase** — same |
| `twim2 p1_boot` LSM6DSO sha | **phase** — same |
| `counters/RADIO_TX` `0x232` → `0x234`/`0x235` | **NOT COVERED.** Outside the criterion entirely (§6.7). Still an open, strictly-gated difference |

And what is **not** phase, on navigation only:

* `spim_a` display animation: `P3 phase` 0 → **21** failures, peak `|δ|`
  145.440 → **245.780 ms** (stage 04-B) / **281.670 ms** (stage 07). Beyond Δ,
  in a stream that already fails `P1 content` for the §41 one-extra-frame
  residue. The framebuffers are unaffected, but this is measured damage on top
  of an existing gap and the criterion says so.

### 7.2 For stage 07: three closures and one new content difference

Stage 07 is the only stage in the ladder that **moves fields toward shipped**:
`ESB_MASTER_FRAMES`/`ESB_ACKS` `0x176` → `0x175`, the dashboard
`JBD_FRAMECOUNTER_P2` `0x2EA3` → `0x2E65` and `spim_a p2_render` `12,289` →
`12,225` — all three now **exactly shipped**. Against that, navigation
`JBD_FRAMECOUNTER_P2` `0x0D61` → `0x0D76` is a new strict regression the
phase-tolerant criterion does not cover (a counter, not a stream), and the
`twim1` npm1300 `P0 segmentation` artifact is a criterion defect (§6.8), not a
firmware one.

**`"oracle_required": true` is discharged for stages 04 and 07** in the sense
that the oracle was run and the result is reported. Whether these stages LAND
is the owner's decision, and the honest statement of the evidence is: they pass
the criterion the owner chose on every stream it gates, and they measurably
worsen one navigation stream that was already failing.

---

## 8. What I did NOT close, and why

1. **The burst-gap threshold is a constant, not calibrated from the reference.**
   §6.8 measures the false positive this produces on a shared bus. The repair is
   to derive the per-device threshold from the shipped capture's own maximum
   intra-burst gap and re-segment ours with it. Not done: it changes the shape
   of the oracle block (the shipped reference would have to be an input to the
   builder), and I would rather ship a criterion with a *named, measured* false
   positive than one whose segmentation rule I changed and did not re-validate.
2. **`RADIO_TX`, `ESB_*`, `VC_DATA_EVENTS`, `saadc`, `pdm0`, `gpiote*` are not
   covered.** They have no train decomposition. `RADIO_TX` is one of the eight
   stage-04-B strict regressions and it stays strictly gated and failing.
3. **The ≈100.5 ms quantum is still unexplained.** §3.1(b) rules out the Zephyr
   system tick (32,768 Hz), the BLE connection interval (30 ms) and the sweep
   dwell (120 ms), and finds no ≈100.5 ms cadence on any traced peripheral. A
   mechanism would give a *better* bound than the one derived here.
4. **The `spim_a` navigation `P1 content` failure is untouched.** One animation
   frame train exists in shipped and not in ours and vice versa, on the base and
   on every stage. This is `sensor_parity_status.md` §41's one-extra-frame
   residue. The criterion fails it, correctly, and I did not fix it.
5. **The `twim1` npm1300 `P5 order` failure on the BASE is new information and
   unchased.** "Two bursts 9,904.330 ms apart in the shipped run swapped order"
   — a pre-existing ordering defect in our build that no strict field isolated,
   because the merged `twim1` hash was already NE. It deserves a look.
6. **`npm1300` phase is indeterminate** (§6.6) — three trains per stimulus with
   `|δ|` up to 7,497.653 ms are excluded as ambiguous. Its content and
   population are gated; its phase is not evidence either way.
7. **Part of the LSM6DSO poll train has no phase gate** (§6.4). On stage 07
   navigation, **199 of 547** bursts are excluded as ambiguous; on the dashboard
   **432 of 545**. The exclusion is honest (the local period is 10.100 ms and
   `|δ|` reaches 5.770 ms) but it means the largest stream in the oracle is
   phase-gated only in part.
8. **Stage 08 was not gated.** `call_order` is a measured no-op — its tree is
   byte-for-byte stage 07's — so its image is stage 07's and it inherits stage
   07's verdict; but I did not build it to confirm that, and its
   `SIZE_GATE.json` is still absent.
9. **The net core was not touched.** No net input moved, no net build was run,
   the frozen `g1-i30e-net` image was booted in all three new captures.
   `check_net_raw_literals` and `verify_net_stock_data_window` need a net ELF
   and were **not run** — recorded as not-run, not as passed.
10. **Stages are now stale** (§0): the concurrent parity agent moved 104 inputs
    at 13:02:49, after every build here completed. Regenerate before the next
    measurement.
11. **`cfg_verify` was not run and is not cited.** Every number in this report
    comes from a build, a `cmp`, an ELF symbol table, a seeded Renode capture or
    a JSON diff.
12. **Nothing was committed.** The tree is left dirty.

---

## 9. Footprint — everything this pass wrote

```
 M recon/emulator/scripts/build_display_sensor_oracle.py     (additive: the
       whole_run_trains block + BURST_GAP_NS/OBSERVATION_WALL_NS/train helpers;
       no existing field's value changed -- proved by the dashboard diff, 0/69)
 M recon/emulator/reports/display_sensor_oracle.json         (REGENERATED from
       the seeded shipped navigation capture; 8 stale fields corrected, 20
       iteration-42 fields gained, 357 new train fields, 0 removed)
 M recon/emulator/reports/display_sensor_oracle_dashboard.json (REGENERATED;
       0 fields changed, 444 train fields added)
 M recon/refactor/stage_06_unit_composition/SIZE_GATE.json   (measured)
 M recon/refactor/stage_07_internal_linkage/SIZE_GATE.json   (measured)
 M recon/refactor/README.md                                  (R7 gate record)
?? recon/emulator/scripts/phase_tolerant_compare.py          (new)
?? recon/analysis/phase_tolerant_criterion.md                (this file)
```

The four `golden_framebuffer_*.raw/pgm/png` were rewritten by the regeneration
and are **byte-identical** to the committed ones (`cmp` exit 0, all four).

**Not written:** no canonical tree, no `recon/symbols`, no `recon/application`,
no `tools/` module, no linker script, no `recon/board/**`, nothing under
`~/Projects/armemul`, and no stage tree. Every `.resc` this pass generated lives
in `/private/tmp/g1-pt/`.

The 130+ modified `recon/symbolized/app/*.c`, `recon/app/src/FUN_00012db0.c`,
`recon/named/`, `recon/readable_sources/`, `recon/verified/` and
`?? recon/analysis/type_disagreement_repair_3.md` that `git status` shows are
**the concurrent parity agent's, not mine.**

---

## 10. Reproducing

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

# builds (stage 03's, 04's and 05's are the stage04b pass's and were reused)
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh app /private/tmp/g1-pt-s01
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh    app /private/tmp/g1-pt-s02
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh app /private/tmp/g1-pt-s06
./recon/refactor/stage_07_internal_linkage/tree/recon/application/build_cohesive.sh app /private/tmp/g1-pt-s07
cmp /private/tmp/g1-pt-s01/zephyr/zephyr.bin /private/tmp/g1-s4b-s03/zephyr/zephyr.bin   # IDENTICAL
cmp /private/tmp/g1-pt-s06/zephyr/zephyr.bin /private/tmp/g1-s4b-s05/zephyr/zephyr.bin   # IDENTICAL
$V recon/refactor/driver.py size-gate 6 /private/tmp/g1-s4b-s05 /private/tmp/g1-pt-s06
$V recon/refactor/driver.py size-gate 7 /private/tmp/g1-pt-s06  /private/tmp/g1-pt-s07

# captures -- ALWAYS seeded; $rtinfo_pc re-read from the ELF actually booted
arm-zephyr-eabi-nm /private/tmp/g1-pt-s07/zephyr/zephyr.elf | grep -wE 'runtime_info_sync|_end'
bash /private/tmp/g1-pt/cap.sh s07_nav1 /private/tmp/g1-pt-s07 0x00016c14 nav
bash /private/tmp/g1-pt/cap.sh s07_dash /private/tmp/g1-pt-s07 0x00016c14 dash
bash /private/tmp/g1-pt/cap.sh s07_nav2 /private/tmp/g1-pt-s07 0x00016c14 nav   # determinism

# oracles (the train block is written automatically)
$V recon/emulator/scripts/build_display_sensor_oracle.py            <cap> <rep>
$V recon/emulator/scripts/build_display_sensor_oracle.py --screen=dashboard <cap> <rep>

# THE BOUND -- derived, printed, before any stage is compared
$V recon/emulator/scripts/phase_tolerant_compare.py derive-bound \
   <rep_ship_nav>/display_sensor_oracle.json  <rep_base_nav>/display_sensor_oracle.json \
   <rep_ship_dash>/..._dashboard.json         <rep_base_dash>/..._dashboard.json

# THE GATE
$V recon/emulator/scripts/phase_tolerant_compare.py compare --bound-ms=145.44 \
   <shipped.json> <base.json> <stage.json> LABEL
# the strict criterion, still run and still reported:
$V /private/tmp/g1-s4r7/cmp3.py <shipped.json> <base.json> <stage.json> LABEL
```

**The shipped reference is now the committed
`recon/emulator/reports/display_sensor_oracle.json`** — regenerated in this pass,
so §3.1 of `stage04b_r7_validation.md` no longer applies and the file may be
used directly.

---

## 11. The static ladder, re-run at the stage 07 image

| gate | value |
|---|---|
| **all four framebuffers vs the regenerated committed goldens** | **byte-identical on every image**: base, stage 03, stage 04-B, stage 07, both stimuli — `cmp` exit 0, 7 report directories × 2 phases |
| app build | exit 0 |
| FLASH (stage 07) | **955,996 B / 982,528 B = 97.30 %** (in-tree base 956,480 B / 97.35 %) |
| `nm -u` undefined | **0** |
| duplicate **global** definitions | **0** (20 lowercase duplicates are file-local statics, which is what stage 07 creates by design) |
| `check_ram_pin_collisions --core app` (stage 07 ELF) | **596 bound OK / 0 escaping / 0 unknown inside a live object**; 20 raw-literal pins outside the RAM region, 3 abs symbols not in the linker scripts — both unchanged. *(596, not the stage-05 figure of 627, because stage 07 makes 137 symbols `static`.)* |
| `tools/verify_data.py` | **995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)** |
| `check_thread_create_stack_args --trials 120` | **10 / 10 PASS, exit 0** |
| `recon/refactor` test suite | **139 / 139 PASS** |
| net core | **untouched** — frozen `g1-i30e-net`, `zephyr.bin` **225,581 B**, booted in all three new captures. `check_net_raw_literals` and `verify_net_stock_data_window` need a net ELF and were **not run** — recorded as not-run, not as passed. |
