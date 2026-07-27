# Stage 04 — R7 behavioural validation (the oracle run the stage report could not do)

**Written incrementally as the work ran. Nothing committed.**

Inputs of this pass:

```
HEAD          3b8242fa  "refactor Stage 04: cohesive TU merge -- 1,615 app TUs -> 695,
                         1,600/1,601 objects byte-identical"
              (parents 192349af "P4 iter-42", 50929c5d, dd671f22)
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)
```

`driver.py status` at the start of this pass:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **current** | 2,629 | 0 |
| 01 literal_inline | current | 2,629 | 0 |
| 02 block_dedupe | current | 2,629 | 0 |
| 03 module_structure | current | 2,629 | 0 |
| 04 cohesive_tu | **current** | 2,629 | 0 |
| 99 defect_probe | stale | 2,304 | 308 |

Stages 00–04 are current at HEAD `3b8242fa`, so nothing needed regenerating
before the first build; the materialised stage-04 tree on disk is the **AB**
sub-batch (`MANIFEST.json → sub_batches.sub_batch = "AB"`, 1,615 → 695 TUs,
318 merged units, 1,238 files absorbed, 30 shape-quarantined). Stage 99 is the
retired diagnostic probe and was left stale, as stages 03 and 04 both recorded.

---

## Running log

*(sections are appended as each measurement completes)*

---

## 1. Builds — three images, and the `$rtinfo_pc` trap is real

Three app images were built with the repository's own entry point. No build
file, linker script or `tools/` module was edited to build any of them.

```sh
./recon/application/build_cohesive.sh                                       app /private/tmp/g1-s4r7-base-app
G1_STAGE04_BATCH=A  driver.py materialize 4
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-A-app
                    driver.py materialize 4        # back to AB
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-AB-app
```

| image | build | FLASH | RAM | `_end` | **`runtime_info_sync`** |
|---|---|---:|---:|---|---|
| **in-tree HEAD** (`base`) | exit 0 | 956,480 B 97.35 % | 253,765 B | `0x2003ff45` | **`0x00015c04`** |
| **stage 04 sub-batch A** | exit 0 | 956,340 B 97.33 % (Δ −140) | 253,765 B | `0x2003ff45` | **`0x00015c0c`** |
| **stage 04 sub-batch AB** | exit 0 | 956,244 B 97.32 % (Δ −236) | 253,765 B | `0x2003ff45` | **`0x0001632c`** |

**All three `runtime_info_sync` addresses are different, and none of them is the
value in any recorded recipe.** The stage-04 report warned about
`0x00015c04 → 0x0001632c`; it did not know that sub-batch **A** has a third
value, `0x00015c0c`. Every capture below used the value re-read from the ELF it
actually booted. `_end` is `0x2003ff45` on all three, so the RAM probes
`0x20040025 / 0x20040F38 / 0x20040FAA` (ctx = align16(`_end`) = `0x2003ff50`,
+0xd5 / +0xfe8 / +0x105a) carry over unchanged, exactly as predicted.

Two cross-checks that the images are the ones the previous passes measured:

```
cmp g1-s4r7-base-app/zephyr/zephyr.bin  g1-i42d-app/zephyr/zephyr.bin   -> IDENTICAL
cmp g1-s4r7-AB-app/zephyr/zephyr.bin    g1-s4-app/zephyr/zephyr.bin     -> IDENTICAL
```

So the in-tree build at HEAD `3b8242fa` is byte-identical to iteration 42's
accepted `g1-i42d-app`, and my stage-04 AB build is byte-identical to the one
the stage-04 report measured statically. Nothing drifted between the passes.

Re-materialising stage 04 back to AB after the A build reproduced
`MANIFEST.json` sha `d0e66ecd…` exactly — the batch switch is a clean round
trip, and `git status` is clean over `recon/refactor/`.

*(Note the FLASH deltas are quoted against the **in-tree** build here, not
against the stage-03 tree. The stage-04 report's Δ −112 B is stage 04 vs stage
03; stages 01–03 account for the other −124 B. Both are true; they answer
different questions.)*

---

## 2. TASK 2 — the dashboard oracle is regenerated, and the schema is now in the tool

`build_display_sensor_oracle.py` emitted the navigation schema unconditionally,
which is why iteration 42 correctly refused to overwrite
`display_sensor_oracle_dashboard.json` (§42.10 item 8). It now takes
`--screen=dashboard|navigation` (default `navigation`), driven by a
`SCREEN_PROFILES` table holding the per-screen schema id, output filename,
framebuffer prefix, prose, stimulus and phase descriptions, plus a dashboard
`screen` block.

**The navigation path is a strict no-op, measured rather than asserted.** The
pre-change script was copied into the same directory (so its `repo` root
resolves identically) and both were run over the same seeded shipped navigation
capture into two scratch report dirs:

```
diff -r noop_pre noop_post   ->  no output, exit 0
```

The whole report directory — `display_sensor_oracle.json` and all eight golden
framebuffer artifacts — is byte-identical. Navigation cannot have been
disturbed by this change.

### 2.1 What changed in the regenerated dashboard oracle

Regenerated from the seeded shipped capture `/private/tmp/g1_ship_seed_dash_d1`
(`G1_ATT_WRITE="" G1_SEED=305419896`). Comparing 74 measured fields (counters,
firmware events, both framebuffers, every bus/phase transaction count and
stream sha, every twim1 per-device sub-stream, all four register-access
peripherals) between the recorded file and the regenerated one:

**74 fields compared, 6 changed.**

| field | recorded | regenerated | cause |
|---|---|---|---|
| `counters/VC_DATA_EVENTS` | `0x00000214` | **`0x00000213`** | **seed** |
| `twim1/p2_render/transaction_count` | 584 | **597** | **seed** |
| `twim1/p2_render/dev:npm1300/transaction_count` | 514 | **527** | **seed** |
| `twim1/p2_render/stream_sha256` | `0f99cbdf…` | `8188ba1c…` | consequence of the above |
| `twim1/p2_render/dev:npm1300/stream_sha256` | `595d8bc1…` | `10548822…` | consequence of the above |
| `saadc/whole_run/stream_sha256` | `660cdf3b…` | `ebf06b30…` | **NOT the seed** — iteration 42's pointer canonicalisation |

That last row is worth separating out, because charging it to the seed would be
wrong. The regenerated file carries **both** hashes, and the old value is
preserved exactly:

```
saadc/whole_run/stream_sha256                = ebf06b3002209e68…   (index-canonical)
saadc/whole_run/stream_sha256_raw_pointers   = 660cdf3bff15837e…   (== the recorded value)
```

So the seed fix moved **three** criteria — exactly the three iteration 42
predicted (`twim1 p2_render` 584→597, nPM1300 514→527, and `VC_DATA_EVENTS`),
with the two dependent stream hashes making six changed fields in total.

**Two numbers the seed fix did NOT move**, and this matters because iteration 42
listed the first of them as a correction:

* `spim_a p2_render` transaction_count is **12,225 in both** the recorded
  (unseeded run 1) and the seeded file. The recorded *annotation* was wrong, not
  the recorded *value* — run 1 happened to land on the seeded number and run 2
  did not.
* `JBD_FRAMECOUNTER_P2` is **`0x00002E65` in both**, same reason.

Both framebuffers reproduce byte-for-byte:
`p1_boot 0c5cc90b… ` (0 lit px, all-zero) and
`p2_render 19b1f24a… ` (2,923 lit px, bbox (78,211)-(564,338) 487×128), and
`cmp` against the committed
`recon/emulator/reports/golden_framebuffer_dashboard_p2_render.raw` is exit 0.
The four `screen/observed_firmware_events` numbers, which the recorded file
carried hand-derived, are now **measured from `run.out`** and reproduce the
recorded values exactly: `DashBoard_Reflash` 136, `notify_display_mode
screen=6` ×8, `display_START` actions `[0, 1]` in order, `ui_navigation_task` 0.

**Determinism re-verified end to end at the oracle level**: regenerating from
the second seeded shipped capture (`_d2`) and `diff -r`-ing the two report
directories gives no output. The dashboard oracle is byte-reproducible.

### 2.2 Every criterion preserved — and two exemptions withdrawn

D-1 … D-7, the `note`, the three `S-D-*` sensor criteria, the whole `screen`
block and its evidence list are all preserved. D-1/D-2/D-3 now carry values
**formatted from the capture in hand** rather than copied, so a regenerated file
cannot silently keep a stale hash.

The one change of substance is the bullet that used to read:

> NOT A GATE (measured non-deterministic …): `peripherals/spim_a/phases/p2_render/stream_sha256`, its `transaction_count`, and `counters/JBD_FRAMECOUNTER_P2`. Compare `lit_pixels` / bbox / framebuffer sha instead.

That exemption was derived from two **unseeded** runs. It is replaced by two new
gates:

* **D-8** — `spim_a p2_render transaction_count == 12,225` and its
  `stream_sha256` must match.
* **D-9** — `counters/JBD_FRAMECOUNTER_P2 == 0x00002E65`.

and the old text is not deleted but **moved into a new
`determinism_verification/WITHDRAWN_annotations` block**, each entry stating
what it used to claim and why it is withdrawn, so the record of the mistake
stays auditable. `twim2 p2_render` and the radio counters
(`RADIO_TX`/`VC_DATA_EVENTS`/`ESB_*`) are withdrawn from the *determinism*
block on the same evidence — seeded, they are identical across two shipped runs.
Withdrawing them as determinism claims does **not** by itself forbid a
comparison tolerance against a differently-linked image; it removes the false
justification "run-to-run noise", which was never true once the seed is pinned.

**What the surviving exemption fails to catch**, stated explicitly and recorded
in the JSON as `what_this_now_FAILS_to_catch`: the only remaining
`NOT_stable_across_runs` entry is the **merged `twim1` bus stream**, excused
because three independent firmware threads arbitrate one bus. It is covered by
the four per-device sub-streams — but the per-device split by construction drops
the **relative order of transactions belonging to different devices**. A defect
that reorders OPT3001 against nPM1300 without changing either device's own
stream is invisible to this oracle. That residue is measurable: the merged
`stream_sha256` is still emitted, it is simply not gated.


---

## 3. TASK 1 — the oracle run. Nine seeded captures, three images, both stimuli

Every capture used `recon/emulator/scripts/capture_display_sensor_oracle.sh`
unmodified, with `G1_SEED=305419896` (the script's own default, emitted as
`emulation SetSeed` before platform creation), `G1_HOOKS=0`,
`G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025`, the
frozen net image `g1-i30e-net`, and a `$rtinfo_pc` re-read from that image's own
ELF. Navigation was run **twice** per image, per the R7 gate record.

| capture | image | stimulus | `$rtinfo_pc` |
|---|---|---|---|
| `base_nav1`, `base_nav2`, `base_dash` | in-tree HEAD | nav ×2, dash | `0x00015c04` |
| `A_nav1`, `A_nav2`, `A_dash` | stage 04 **A** | nav ×2, dash | `0x00015c0c` |
| `AB_nav1`, `AB_nav2`, `AB_dash` | stage 04 **AB** | nav ×2, dash | `0x0001632c` |

Shipped-firmware references: the seeded captures `g1_ship_seed_q1`/`_q2`
(navigation) and `g1_ship_seed_dash_d1`/`_d2` (dashboard) taken in iteration 42.

### 3.1 A correction to the R7 gate record: the navigation "bistability" is gone

The R7 gate record instructs that navigation `twim2 p1_boot` and `twim1 p1_boot`
be treated as **multi-run criteria** because "each image produces both
outcomes". That measurement was taken at HEAD `a2f3303d`, **before** the seeding
discipline landed in iterations 41/42, so its two runs drew different net-core
RNG streams.

Measured here, with the seed pinned, run 1 vs run 2 of the same image:

```
SHIPPED   q1 vs q2      whole regenerated oracle dir  BYTE-IDENTICAL
in-tree   nav1 vs nav2  whole regenerated oracle dir  BYTE-IDENTICAL
stage04 A nav1 vs nav2  whole regenerated oracle dir  BYTE-IDENTICAL
stage04 AB nav1 vs nav2 whole regenerated oracle dir  BYTE-IDENTICAL
```

**Navigation is deterministic per image once the seed is pinned.** The
bistability was the unseeded RNG, exactly as iteration 41 found for the other
streams. This matters for what follows: a single seeded run of `twim2 p1_boot`
**is** evidence now, and a difference on it cannot be excused as bistability.
The R7 gate record's instruction is superseded, and its "one apparent regression
was investigated and disproved" paragraph rested on unseeded double-runs.

### 3.2 THE ACCEPTANCE BAR — all twelve framebuffers byte-identical

`cmp` against the committed goldens, 153,600 B each, exit 0 every time:

| | in-tree base | **stage 04 A** | **stage 04 AB** |
|---|---|---|---|
| navigation `p1_boot` `1d617c65…` 656 px | IDENTICAL | **IDENTICAL** | **IDENTICAL** |
| navigation `p2_render` `b26c73b3…` 1,098 px | IDENTICAL | **IDENTICAL** | **IDENTICAL** |
| dashboard `p1_boot` `0c5cc90b…` all-zero | IDENTICAL | **IDENTICAL** | **IDENTICAL** |
| dashboard `p2_render` `19b1f24a…` 2,923 px | IDENTICAL | **IDENTICAL** | **IDENTICAL** |

**The pixel bar is not disturbed by the merge, on either sub-batch, on either
screen.** The honest-stimulus counters go with it: `SCREEN_ID` `0x0A`
(navigation) / `0x06` (dashboard), `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02` — all
equal to shipped on all three images.

### 3.3 Three-way field comparison

69 measured fields per stimulus (counters, both framebuffers, every bus/phase
transaction count and stream sha, every `twim1` per-device sub-stream, the
`regprog` canonical hashes, and all four register-access peripherals). A field
that differs on **both** the in-tree build and the stage build is a pre-existing
gap and is not charged to the refactor.

| | **navigation, A** | **navigation, AB** | **dashboard, A** | **dashboard, AB** |
|---|---:|---:|---:|---:|
| EQ to shipped on both ours and base | 49 | 49 | 55 | 55 |
| pre-existing gap, identical on both | 2 | 2 | 12 | 10 |
| pre-existing gap, different value | 10 | 8 | 1 | 1 |
| **REFACTOR REGRESSION** (base EQ, stage NE) | **8** | **8** | **1** | **1** |
| refactor improvement (base NE, stage EQ) | 0 | **2** | 0 | **2** |

### 3.4 THE FINDING — stage 04 breaks navigation `p1_boot`, and it is sub-batch A

The eight navigation regressions are **identical between sub-batch A and
sub-batch AB**, field for field, value for value:

| field | shipped | in-tree base | **stage 04 A** | **stage 04 AB** |
|---|---|---|---|---|
| `twim1 p1_boot` count | 371 | 371 EQ | **373** | **373** |
| `twim1 p1_boot` OPT3001 count | 33 | 33 EQ | **35** | **35** |
| `twim1 p1_boot` OPT3001 sha | `ef88ae8b…` | EQ | **`b759ccc5…`** | **`b759ccc5…`** |
| `twim1 p1_boot` merged-bus sha | `33cbd8c1…` | EQ | `4f49068a…` | `4f49068a…` |
| **`twim2 p1_boot` sha** | **`7ed8ddcd0c0d420d…`** | **EQ** | **`03537cda890a2b7d…`** | **`03537cda890a2b7d…`** |
| `twim2 p1_boot` LSM6DSO sha | same | EQ | same as above | same as above |
| `twim2 p1_boot` `regprog` sha | `5e4a55c6…` | EQ | `6d3c4072…` | `6d3c4072…` |
| `counters/RADIO_TX` | `0x232` | `0x232` EQ | **`0x233`** | **`0x234`** |

Running the same comparator with **sub-batch A as the baseline and AB as the
stage** gives **0 regressions and 2 improvements**. So:

> **Every side-effect regression stage 04 introduces is caused by sub-batch A.
> Sub-batch B — 271 further merged units absorbing 1,087 more files — adds not
> one new divergence, and repairs two.**

That is the opposite of what the risk ordering predicted. Sub-batch A was
selected as the low-risk half precisely because **no member file contains the
token `volatile`**, so no inlining decision inside a merged A unit can reorder,
coalesce or drop a volatile access. The R8 reasoning was sound and it is still
sound — *the regression is not a volatile-access reordering*. It is timing, and
timing does not care which half of the batch moved the code.

Sub-batch A's entire codegen delta is **−16 B of `.text` and two functions**:
`k_uptime_get_3` 28 → 4 B (a forwarding thunk collapsing to a tail branch) and
`__ieee754_pow` 2,480 → 2,488 B. That is what moved the boot path.

### 3.5 What the two regressions actually are, decoded transaction by transaction

Neither is a content divergence. Both are pure re-phasings, and saying so
precisely is the point — but neither is therefore harmless, because C7 gates on
the ordered stream.

**(a) OPT3001, `twim1 p1_boot`, 33 → 35.** `difflib` over the canonical
per-device stream:

```
EQUAL   base[0:33] == stage[0:33]     (33)
INSERT  base[33:33] stage[33:35]
    +  opt3001_ambient_light  45|W|00
    +  opt3001_ambient_light  45|R|0000
```

The first 33 transactions are identical and in order; stage 04 performs **one
extra ambient-light poll** before the 6 s phase wall. The poll *period* is
unchanged to 30 ns — 0.350250–0.350316 s on all three images — but the train's
**phase** moved:

```
poll #14 (the first steady-state poll after the conversion-enable burst)
   shipped   4.295524 s
   in-tree   4.304162 s     +8.6 ms  vs shipped
   stage 04  4.203454 s    -92.1 ms  vs shipped,  -100.7 ms vs the in-tree build
```

so where shipped and in-tree stop at 5.696590 / 5.705320 s, stage 04 fits one
more at 5.954830 s. `p2_render` OPT3001 is 80 on all three, so this is a genuine
extra poll over the 20 s run, not a transaction moving across the wall.

**(b) LSM6DSO, `twim2 p1_boot`, 1,089 → 1,089 with a different sha.** Same tool:

```
EQUAL   base[0:99]     == stage[0:99]        (99)
DELETE  base[99:103]                          -- 6B|W|28 / 6B|R|.. / 6B|W|22 / 6B|R|..
EQUAL   base[103:1089] == stage[99:1085]     (986)
INSERT                    stage[1085:1089]   -- the same four, at the tail
```

**One 4-transaction IMU poll pair rotates from index 99 to the end.** The
multiset of transactions is identical; only the position changes. This is the
exact shape the R7 gate record described and dismissed as bistability — and
§3.1 shows it is not bistability, it is a stable, reproducible consequence of
the −16 B.

**(c) `RADIO_TX` `0x232 → 0x233` (A) / `0x234` (AB)**, on both stimuli. +1 and
+2 BLE radio frames. `ESB_MASTER_FRAMES`/`ESB_ACKS` stay at the pre-existing
`0x176` vs `0x175`.

### 3.6 Iteration 42's wins, re-measured — one of four is broken

| iteration-42 criterion | shipped | in-tree | **A** | **AB** | verdict |
|---|---|---|---|---|---|
| navigation `spim_a` whole run | 3,645 | 3,645 | **3,645** | **3,645** | **HOLDS** |
| navigation `twim1 p2_render` 599, all four per-device sha | 599 | 599 EQ | **599 EQ** | **599 EQ** | **HOLDS** |
| navigation `twim2 p1_boot` 1,089 / `7ed8ddcd0c0d…` | EQ | EQ | 1,089 / `03537cda…` | 1,089 / `03537cda…` | **BROKEN** |
| navigation `JBD_FRAMECOUNTER_P2` `0x0D61` | `0x0D61` | `0x0D61` | **`0x0D61`** | **`0x0D61`** | **HOLDS** |

And the dashboard criteria iteration 42 had just made byte-exact all survive:
`twim2 p1_boot` 1,075 `f182314b…`, `twim1 p1_boot` 346 `0a8ed850…`,
`spim_a p1_boot` 34 `f91505ab…`, ST25DV `p2_render` 7 / 4, OPT3001 `p2_render`
59 `4e016ae0…`, `saadc` 998 `ebf06b30…` (both stimuli), and both `twim2
p2_render` `regprog` hashes — every one EQ on A and AB.

### 3.7 The two improvements, reported without celebration

On **both** stimuli, sub-batch B (present in AB, absent from A) takes
`twim2 p2_render` from NE to **byte-equal with shipped**:

```
navigation  ship 191ba08b9fa130…  base 334912551045a4…  A 8b3c69f98c0ac5…  AB 191ba08b9fa130…  EQ
dashboard   ship fbc6ec681e02d0…  base b774cbaa03ad15…  A b774cbaa03ad15…  AB fbc6ec681e02d0…  EQ
```

This closes iteration 42's "3 of 1,200 accel payloads differ" residue outright —
the *raw* stream sha now matches, not just the `regprog` canonicalisation. It is
the same mechanism as the regression, running the other way: the merge moved the
boot path by a different amount and this time the IMU sample phase landed on the
shipped one. **It is luck, not repair**, and it should not be counted as
progress; if anything it is further evidence that these three streams are
carried by boot-path phase rather than by firmware logic.

### 3.8 What is pre-existing and therefore not chargeable to the refactor

Identical on the in-tree build and the stage build, both differing from shipped:
`ESB_MASTER_FRAMES`/`ESB_ACKS` `0x176` vs `0x175`; and on the dashboard,
`spim_a p2_render` 9,212 vs 12,225, `JBD_FRAMECOUNTER_P2` `0x22D7` vs `0x2E65`,
`twim1 p2_render` 583 vs 597 with nPM1300 513 vs 527, `ESB_ANNOUNCE_RESP`
`0x165` vs `0x162`. Stage 04 makes **none** of these worse — the dashboard
repaint deficit and the nPM1300 tail are bit-for-bit what the in-tree build
produces.

Pre-existing but *different in value* on the stage build (a gap that moved
rather than a gap that appeared): navigation `spim_a` p1/p2 **split** 764/2,881
shipped, 786/2,859 in-tree, **808/2,837** stage 04 — whole run 3,645 on all
three; `JBD_FRAMECOUNTER_P1` `0x2A1` / `0x2B6` / `0x2CB`; `VC_DATA_EVENTS`
`0x212` / `0x216` / `0x217`–`0x218`; `ESB_ANNOUNCE_RESP` `0x15B` / `0x15E` /
`0x15D`; and the merged `twim1 p2_render` bus sha (per-device EQ throughout, so
this is only the excused three-thread interleaving).

---

## 4. TASK 3 — the remaining dashboard gaps

### 4.1 Dashboard `spim_a p2_render` 9,212 vs 12,225 — **ROOT-CAUSED AND CLOSED (diagnosis)**

This was the largest unexplained display gap and it is now fully decomposed, from
the traces alone plus two cheap Renode probes.

**Step 1 — the deficit is not diffuse; it is seven named screen regions.**
Grouping every `0x02` pixel-window burst by the panel region it touches (burst =
maximal run of `0x02` between panel commands):

| region (panel coords) | windows/burst | **shipped** | **ours (base, A, AB — identical)** |
|---|---:|---|---|
| x=78, y=259..292 (clock digits) | 34 | 132× T=0.0686 s | 129× T=0.0688 s |
| x=78, y=207..234 (date line) | 28 | 132× T=0.0686 s | 129× T=0.0688 s |
| x=0, y=175..374 (content block) | 200 | 4× | 4× |
| x=0, y=0..384 (full-screen clear) | 3 | 2× | 2× |
| **x=244, y=211..339 (vertical divider)** | 129 | **7× T=1.2003 s** | **ABSENT** |
| **x=564, y=211..339 (vertical divider)** | 129 | **7× T=1.2003 s** | **ABSENT** |
| **x=312, y=247..274 ("Hold Right TouchBar")** | 28 | **7×** | **ABSENT** |
| **x=326, y=274..301 ("to Add QuickNote")** | 28 | **7×** | **ABSENT** |
| **x=78, y=316..342** | 27 | **7×** | **ABSENT** |
| **x=256, y=209..235 (note glyph)** | 27 | **7×** | **ABSENT** |
| **x=174, y=316..343 (Bluetooth glyph)** | 28 | **11×** (4 boot + 7 periodic) | **4× (boot only)** |

The deficits sum to `903 + 903 + 196 + 196 + 189 + 189 + 196 + 102 + 84 =`
**2,958**, and `12,225 − 9,212 = 2,958` — exact, with nothing left over. The
per-opcode histogram agrees independently: `0x97` (panel refresh) 331 vs 276,
Δ = 55 = the 55 missing bursts; every other opcode count is identical.

**Step 2 — the gate.** All seven absent regions are drawn in ONE branch of
`DashBoard_Reflash`, below `if (param_3 == 1) { … } else if (param_3 != 4)
{ return; }`
(`recon/named/DashBoard_Reflash.c:1422`,
`recon/symbolized/app/DashBoard_Reflash.c:1429`, and the three sibling layout
variants at named lines 649 / 1749 / 2430). The clock and date are drawn
*above* that gate, which is exactly why they still repaint. `param_3 == 1` only
arrives via a `DISPLAY_MESSAGE_START` on `g_display_msgq`, whose only runtime
producer is `notify_display_mode` inside `display_dispatch_thread`, which fires
only when `memory_compare_bytes(display + 0xef, *(ctx + 0xfec), 0x6a)` differs.

**Step 3 — measured, not inferred.** A Renode hook on `DashBoard_Reflash`
logging `r2` (`param_3`), one run per image, seeded, dashboard stimulus:

```
shipped   (hook @0x3727c)    136 calls   125x param_3=0   11x param_3=1
our build (hook @0x325b0)    133 calls   129x param_3=0    4x param_3=1
```

11 − 4 = **7**, matching the seven absent repaints region for region. Our four
`param_3 == 1` calls are all in the boot burst; **after boot our firmware never
performs a full dashboard redraw at all.**

**Step 4 — the actual defect.** A second probe reads the payload the memcmp
watches — `*(uint32_t *)*(uint32_t *)(device_ctx + 0xfec)`, a unix timestamp — at
every `DashBoard_Reflash` call:

```
SHIPPED   1704067208, 1704067210, 1704067211, 1704067212,
          1704067213, 1704067214, 1704067216, 1704067217     <- it TICKS
OURS      1704067200 … 1704067200, every single call         <- FROZEN
```

**Our firmware's system clock never advances.** It sits on the 2024-01-01
00:00:00Z epoch base for the entire 20 s run. Nothing in the 106-byte payload
ever changes, so the memcmp never differs, `notify_display_mode` never fires
after boot, `param_3 == 1` never arrives, and the seven static regions are
never repainted.

That also disposes of the "1.2003 s period" as a red herring: there is no 1.2 s
timer anywhere in the dashboard path (grepped for `1200`, `0x4b0`, the matching
tick counts and a `% 17`/`% 18` frame modulo — nothing). The shipped repaints
land on the *second boundary*, quantised onto the 200.01 ms
`low_speed_peripheral_dispatch_thread` grid, and the shipped timestamp list is
correspondingly non-uniform (…208, 210, 211, 212, 213, 214, 216, 217 — 209 and
215 are missing because two edges fell in the same grid slot).

**Consequences worth stating plainly:**

* This single defect accounts for the **whole** dashboard `spim_a p2_render`
  gap (2,958 of 2,958 windows) and for `JBD_FRAMECOUNTER_P2` `0x22D7` vs
  `0x2E65`.
* It is **not** a stage-04 effect. base, A and AB are bit-identical on every
  one of these regions; the merge neither caused nor worsened it.
* It is a **user-visible functional bug on real hardware**, not an emulator
  artifact: a dashboard whose clock never advances.
* The framebuffer is byte-identical *despite* the defect only because the
  static elements are painted correctly during boot and nothing ever erases
  them. The pixel gate could not have caught this. It took the transaction
  stream — which is precisely the argument for C7 gating on bus traffic and not
  only on pixels, and precisely why the bogus `NOT_stable_across_runs`
  annotation on this stream was so expensive: it hid a real firmware defect for
  eight iterations.

A follow-up investigation to localise the frozen clock to a source line
(`low_speed_peripheral_dispatch_thread` / `errno_wrapped_tick_call` and whatever
should advance the epoch) is running; whatever it finds, the diagnosis above
stands on the two probe runs.

### 4.2 Dashboard nPM1300 −14 — re-measured; the period is confirmed and it is NOT codegen-carried

Timing every `W 070401` fuel-gauge poll in `twim1.p2.trace`:

| image | polls in p2 | first | last | inter-burst pause: min / median / max | last five pauses |
|---|---:|---|---|---|---|
| **shipped** | 68 | 6.0735 | 19.7960 | 0.4012 / 0.4093 / 0.5001 | 0.4012 0.4012 0.4012 0.4516 0.4015 |
| in-tree base | 67 | 6.0774 | 19.8800 | 0.4085 / 0.4501 / 0.5001 | 0.4522 0.4492 0.4480 0.4993 0.4517 |
| stage 04 A | 67 | 6.0774 | 19.8789 | 0.4085 / 0.4492 / 0.5001 | 0.4524 0.4492 0.4480 0.4992 0.4489 |
| stage 04 AB | 67 | 6.0768 | 19.8784 | 0.4086 / 0.4500 / 0.4993 | 0.4523 0.4492 0.4480 0.4993 0.4490 |

Iteration 42's characterisation is confirmed exactly: the shipped pause
**settles to 0.4012–0.4015 s** at the tail while ours stays at
**0.4480–0.4524 s** — a constant **+48 to +50 ms per cycle**, one scheduling
tick. The accumulated drift puts our last poll group at 19.878 s instead of
19.796 s, so its 14 transactions are cut by the 20 s wall. That is the whole
−14.

**New information from this pass:** the figure is **identical to within 1 ms
across all three of our images** (0.4501 / 0.4492 / 0.4500 median), while their
`.text` differs by 236 B and their boot times differ by 0.47 ms. The pause is
therefore **a computed sleep length, not a codegen-carried timing artifact**,
and the place to look is whatever computes the nPM1300 poll thread's
inter-burst sleep — not the bus, not the transaction contents (iteration 42
already refuted the ST25DV-occupancy hypothesis). **Not closed.**

### 4.3 The 6.4 ms boot lateness — re-measured, and it splits in two

First transaction on each bus, `p1_boot`, identical on both stimuli:

| image | `twim1` (nPM1300) | `twim2` (LSM6DSO) | `spim_a` (panel) |
|---|---|---|---|
| **shipped** | 0.049940 | 0.073300 | 0.101700 |
| in-tree base | 0.053390 **+3.45 ms** | 0.079690 **+6.39 ms** | 0.108070 **+6.37 ms** |
| stage 04 A | 0.053390 **+3.45 ms** | 0.079590 **+6.29 ms** | 0.107980 **+6.28 ms** |
| stage 04 AB | 0.053390 **+3.45 ms** | 0.079220 **+5.92 ms** | 0.107620 **+5.92 ms** |

**The `twim1` figure is +3.45 ms on all three images, to the 10 ns resolution of
the trace.** It does not move when `.text` moves by 236 B. The `twim2` and
`spim_a` figures do move (+6.39 → +5.92 ms).

So the lateness has **two components, and they should be attacked separately**:

1. a **fixed +3.45 ms** accrued before the first nPM1300 transaction at ~50 ms —
   invariant under codegen, therefore not an instruction-count effect. It is
   something taking a fixed extra amount of time in early init (a poll loop
   bound, a delay constant, a clock-ready wait), and it is the *same* class of
   suspect as §4.2's +50 ms.
2. a **further ~2.9 ms** accrued between the first `twim1` and the first `twim2`
   transaction — this is the part that tracks codegen, moving −0.47 ms for
   stage 04's −236 B (≈ 2 µs per byte of `.text`).

That refines §42.10 item 3 from "invariant across six builds, moves in
60–240 µs steps" into a split where only the smaller half is codegen-carried.
**Not closed**, but the search is now bounded to the interval before the first
nPM1300 transaction.

### 4.4 ESB counters +1 — measured, left open deliberately

`ESB_MASTER_FRAMES` and `ESB_ACKS` are `0x176` on all three of our images
against the shipped `0x175`, on both stimuli — a stable +1, unchanged by
stage 04. `RADIO_TX` is `0x232` shipped and in-tree, `0x233` on A and `0x234`
on AB, so the merge does move that one by +1/+2.

I did not close this. The +1 sits inside the documented ±2 tolerance, and the
honest reason not to spend on it is that §4.1 just showed what a mis-set
tolerance costs: the effort is better spent on the frozen clock and on §4.2/§4.3,
which are firmware defects with a measured mechanism. What I will not do is
*widen* anything to make `RADIO_TX` green — it is recorded above as a stage-04
regression at its measured value.

---

## 5. Static ladder, re-run at these inputs

| gate | in-tree base | stage 04 A | stage 04 AB |
|---|---|---|---|
| app build | exit 0 | exit 0 | exit 0 |
| `nm -u` undefined | 0 | 0 | 0 |
| duplicate global definitions | 0 | 0 | 0 |
| sized text symbols (`nm -S`) | 2,997 | **2,997** | **2,997** |
| compiler warnings | 2,174 | 2,209 | 2,203 |
| `driver.py check-addresses` 0-1, 1-2, 2-3, 3-4 | — | identical, 2,567 both sides on every pair | |
| `recon/refactor` test suite | — | **58 / 58 PASS** | |
| stage 04 batch round trip | — | `MANIFEST.json` sha `d0e66ecd…` before A, `d0e66ecd…` after restoring AB — byte-identical | |

Net core untouched: no net input changed, no net build was run, the frozen
`g1-i30e-net` image was booted in all nine captures.

---

## 6. VERDICT

### Stage 04 sub-batch A — **FAILS R7**

Eight fields that the in-tree build reproduces byte-exactly against the shipped
firmware are broken by sub-batch A on the navigation stimulus:
`twim1 p1_boot` (371 → 373, OPT3001 33 → 35 plus its sha and the merged-bus
sha), `twim2 p1_boot` (1,089 transactions in a different order,
`7ed8ddcd0c0d420d…` → `03537cda890a2b7d…`, including the `regprog`
canonicalisation), and `counters/RADIO_TX` (`0x232` → `0x233`).

The failure is **stable and reproducible at the pinned seed** (run 1 and run 2
of every image produced byte-identical oracle directories), so it cannot be
excused as the bistability the R7 gate record recorded — §3.1 shows that
bistability was itself an unseeded-capture artifact.

Both regressions decode to pure **re-phasings**, not content divergences: the
OPT3001 poll train moves 100.7 ms earlier and gains one poll inside the 6 s
window (the first 33 transactions are identical and in order); one 4-transaction
LSM6DSO poll pair rotates from index 99 to the tail of an otherwise identical
1,089-transaction stream. But C7 gates the ordered stream, and the ordered
stream changed.

Sub-batch A's entire codegen delta is **−16 B of `.text` and two functions**
(`k_uptime_get_3` 28 → 4 B, `__ieee754_pow` 2,480 → 2,488 B). Sixteen bytes
moved two firmware threads far enough to break byte-equality on two buses.

### Stage 04 sub-batch AB — **FAILS R7, with exactly the same eight fields and no others**

Comparing AB **against A** rather than against the in-tree build gives **0
regressions and 2 improvements**. Sub-batch B — 271 further merged units
absorbing 1,087 more files, `.text` −96 B beyond A — introduces **not one new
divergence**, and takes `twim2 p2_render` to byte-equality with the shipped
firmware on both stimuli.

**So the risk ordering was inverted.** The half selected as low-risk on a sound
R8 argument (no member contains the token `volatile`, so no merged unit can
reorder a volatile access) carries 100 % of the damage, and the half that
carries all the volatile exposure carries none of it. The R8 argument was not
wrong — the failure is not a volatile reordering. It is timing, and timing is
insensitive to which half of the batch moved.

### What holds

* **All twelve framebuffers byte-identical to the shipped goldens** — the four
  acceptance hashes on both sub-batches and on the in-tree build.
* `SCREEN_ID` / `DISPLAY_ON` / `ESB_SYNC` equal to shipped everywhere.
* Three of iteration 42's four "do not regress" criteria: navigation `spim_a`
  whole run 3,645, navigation `twim1 p2_render` 599 with all four per-device
  streams EQ, `JBD_FRAMECOUNTER_P2` `0x0D61`.
* Every dashboard criterion iteration 42 had just made byte-exact.
* Every pre-existing gap is unchanged — stage 04 makes none of them worse.

### Recommendation

**Do not land stage 04 in this form.** The right next move is not to bisect
sub-batch A's 47 merged units for "the bad one" — there is no bad one; the
mechanism is the linked size of the boot path, and any merge that changes it
will reproduce this. The two options that actually address it:

1. **Fix the boot-path timing gap first (§4.3).** Our build is +3.45 ms /
   +6.4 ms late to the first bus transaction, and the fixed +3.45 ms half is not
   codegen-carried. While a 16 B change can flip a gate, no merge stage can be
   validated. Iteration 42 said the same thing from the other side.
2. Or **accept the merge and re-baseline** these two `p1_boot` streams
   explicitly, with the decoded diffs in §3.5 as the record of exactly what was
   given up. That is a real decision with a real cost and it is not mine to
   take — but it must be taken deliberately, not by widening a tolerance.

Stage 04 remains **BUILT, STATICALLY GATED, ORACLE-RUN — AND FAILING** on eight
navigation fields and one dashboard counter.

---

## 7. What I did NOT close, and why

1. **Sub-batch A's eight regressions are diagnosed, not fixed.** The mechanism
   is measured (a −100.7 ms phase shift of the ALS poll train; a one-position
   rotation of an IMU poll pair) but no fix is proposed, because the cause is the
   linked size of the boot path and not any individual merged unit. Bisecting A's
   47 units would find a unit whose removal happens to restore the phase, which
   is not the same as finding a defect.
2. **The frozen system clock (§4.1) is diagnosed to the payload word, not to a
   source line.** I proved `*(uint32_t *)*(uint32_t *)(device_ctx + 0xfec)` never
   advances in our build and that this alone accounts for all 2,958 missing
   dashboard pixel windows and for `JBD_FRAMECOUNTER_P2`. Localising the writer
   to a line and repairing it belongs to the canonical trees, which this pass may
   not touch (a concurrent agent owns them).
3. **The nPM1300 +48–50 ms poll pause (§4.2) is not root-caused.** New this pass:
   it is identical across all three of our images, so it is a computed sleep
   length rather than a codegen artifact. The computing function is not
   identified.
4. **The boot lateness (§4.3) is not closed**, but it is now split into a fixed,
   non-codegen-carried +3.45 ms before the first nPM1300 transaction and a
   codegen-carried ~2.9 ms after it. Only the second half moves with `.text`.
5. **`ESB_MASTER_FRAMES`/`ESB_ACKS` +1 not investigated.** Recorded at its
   measured value; no tolerance widened.
6. **`spim_a` navigation p1/p2 split** 764/2,881 vs 786/2,859 vs 808/2,837 —
   whole run 3,645 on all three, so the split is left as the known non-defect
   §42.10 item 5 records, now with a stage-04 value.
7. **`cfg_verify` was not run and is not cited.** No claim in this report rests
   on it; every number comes from a build, a `cmp`, a seeded Renode capture or a
   Renode PC hook.
8. **Stage 99 left stale.** Retired diagnostic, as stages 03 and 04 both
   recorded.
9. **Nothing committed.** The tree is left dirty.

### Footprint — everything this pass wrote

```
 M recon/emulator/scripts/build_display_sensor_oracle.py
        --screen=dashboard|navigation via SCREEN_PROFILES; dashboard determinism/
        criteria/screen blocks derived from the capture; navigation path proved a
        strict no-op by diff -r against the pre-change script
 M recon/emulator/reports/display_sensor_oracle_dashboard.json
        regenerated from the SEEDED shipped capture; 6 of 74 measured fields moved
        (3 by the seed, 1 by iteration 42's pointer canonicalisation, 2 dependent
        hashes); D-1..D-7 preserved, D-8/D-9 added, the bogus non-determinism
        exemption moved into WITHDRAWN_annotations
 M recon/refactor/README.md
        stage-04 table row; the bistability instruction superseded; the Stage 04
        R7 gate record appended
?? recon/emulator/reports/golden_framebuffer_dashboard_p1_boot.{raw,pgm,png}
        new — D-2 gates on this frame and no golden existed for it
?? recon/analysis/stage04_r7_validation.md   (this file)
```

`golden_framebuffer_dashboard_p2_render.{raw,pgm,png,crop.png}` were rewritten
and are byte-identical to the committed files, so they do not appear as
modified. **No canonical tree, no `recon/refactor/` transform, no linker script,
no build file, no `recon/board/**`, no `tools/` module and nothing under
`~/Projects/armemul` was touched** — the probe hooks of §4.1 live in throwaway
`.resc` files under `/private/tmp/g1-s4r7/probe/`.

### Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py status
./recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-base-app
G1_STAGE04_BATCH=A $V recon/refactor/driver.py materialize 4
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-A-app
$V recon/refactor/driver.py materialize 4
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4r7-AB-app

# nine seeded captures; $rtinfo_pc re-read PER IMAGE (0x15c04 / 0x15c0c / 0x1632c)
bash /private/tmp/g1-s4r7/cap.sh base_nav1 /private/tmp/g1-s4r7-base-app 0x00015c04 nav
# ... base_nav2 base_dash A_nav1 A_nav2 A_dash AB_nav1 AB_nav2 AB_dash

$V recon/emulator/scripts/build_display_sensor_oracle.py                    <cap> <rep>
$V recon/emulator/scripts/build_display_sensor_oracle.py --screen=dashboard <cap> <rep>
$V /private/tmp/g1-s4r7/cmp3.py <ship.json> <base.json> <stage.json> LABEL

# the analyses of section 4
$V /private/tmp/g1-s4r7/regions.py <ship>/spim_a.p2.trace <ours>/spim_a.p2.trace
$V /private/tmp/g1-s4r7/devdiff.py <capA> <capB> twim1 p1_boot opt3001_ambient_light
# the two probes that root-caused the dashboard gap:
#   ours    hook @0x000325b0 (DashBoard_Reflash), payload ptr @0x20040F3C
#   shipped hook @0x0003727c (DashBoard_Reflash), payload ptr @0x2005413C
#   see /private/tmp/g1-s4r7/probe/{ours,ship}-{dashprobe,ts}.resc
```

---

## 8. ADDENDUM — the frozen clock is pinned to ONE MISSING ARGUMENT, and it was already in `DEFECTS.json`

§4.1 left the frozen system clock diagnosed to the payload word. A follow-up
investigation localised it to a single line, and I re-verified the two
load-bearing disassemblies myself against my own freshly-built ELF and the
shipped image rather than taking them on report.

**The defect.** `recon/symbolized/app/errno_wrapped_tick_call.c` (the file the
build actually compiles — `app_retained_sources.cmake:1165`) declares and calls
its callee with **two** arguments where the shipped code passes **three**:

```c
extern void rate_limited_elapsed_seconds_tick(unsigned int, unsigned int);   /* line 12 */
  rate_limited_elapsed_seconds_tick(param_2, 0);                             /* line 25 */
```

**Shipped**, `0x0007d1d6` via `tools/extract.py`, disassembled:

```
7d1e6:  f8d4 2fec   ldr.w r2, [r4, #0xfec]
7d1ea:  6013        str   r3, [r2, #0]
7d1ec:  2200        movs  r2, #0          <-- param_3 = 0   (ACCUMULATE)
7d1ee:  4611        mov   r1, r2          <-- param_2 = 0
7d1f0:  f7cd f93c   bl    0x4a46c
```

**Ours**, `errno_wrapped_tick_call` at `0x00079d38` in
`/private/tmp/g1-s4r7-base-app/zephyr/zephyr.elf`:

```
79d48:  f8d4 2fec   ldr.w r2, [r4, #0xfec]
79d4c:  6013        str   r3, [r2, #0]
79d4e:  2100        movs  r1, #0          <-- only r1 zeroed
79d50:  f7cb f854   bl    44dfc <rate_limited_elapsed_seconds_tick>
```

`movs r2, #0` is simply **absent**. Every other instruction of the function
matches the shipped image one for one. On the dominant path `r2` still holds the
payload pointer loaded two instructions earlier, which is never zero.

**Why that freezes the clock.** `rate_limited_elapsed_seconds_tick`
(`FUN_0004a46c`, itself byte-faithful in our build) branches on `param_3`:
`param_3 == 0` is the ACCUMULATE arm, which contains the **only**
`*param_1 += elapsed_seconds` in the whole image; any non-zero `param_3` takes
the RESET-ONLY arm, which just restamps `g_progress_tick_ms[param_2]` and never
touches the timestamp. Our build takes the reset arm on every pass. Hence
1704067200, forever.

The arity is not in doubt: every *other* caller in the tree already uses the
three-argument form — `recon/symbolized/app/master_process_audio_fw_load_req.c:96,826`
(`(int*, int, int)`, called `(…, 0, 1)`) and
`recon/symbolized/app/ble_process_put_ops_01_08.inc:106` (`(config, 0, 1)`).
`errno_wrapped_tick_call` is the only site with the truncated prototype, and it
is the only one that needs `param_3 == 0`.

### 8.1 The part that should change how `DEFECTS.json` is read

This defect **is already in stage 03's census**, verbatim:

```json
{"module_dir": "recon/symbolized/app/ble",
 "symbol": "rate_limited_elapsed_seconds_tick",
 "class": "declaration_disagrees_with_definition",
 "distinct_types": 2,
 "types": {"extern void rate_limited_elapsed_seconds_tick(unsigned int,unsigned int);": 1,
           "extern void rate_limited_elapsed_seconds_tick(int*,int,int);": 1},
 "definition_file": "rate_limited_elapsed_seconds_tick.c",
 "files": ["errno_wrapped_tick_call.c"]}
```

It has been sitting in `recon/refactor/stage_03_module_structure/DEFECTS.json`
since stage 03, filed as a **merge blocker** — one of the 833 entries stage 04
§10 step 2 treats as "worth 452 translation units". Stage 04's `type` refusal
rule dutifully refused to put those two files in one translation unit, which is
correct and which is also exactly why the compiler was never allowed to see the
contradiction and shout.

**So the 833 entries are not a refactor obstacle. They are a defect list**, and
this is the proof: one entry, chosen by nothing but where the trace led,
freezes the device clock, suppresses every post-boot dashboard redraw, and costs
2,958 SPI transactions and `JBD_FRAMECOUNTER_P2`. Repairing them "arity first",
which §10 step 2 already recommends for merge yield, should be re-prioritised as
a **defect hunt** — with the highest-value order being the entries whose
`class` is `arity_differs` or `declaration_disagrees_with_definition` against
the symbol's own definition, since those are the ones that can silently pass a
garbage register.

The banner on the defective file still reads `parity: 300/300 trials, PROVEN`.
It is the iteration-39 failure mode again: the harness constrained the function
*body* but left `r2` unconstrained at the outgoing `bl`, so a caller-side
argument slot that is never planted is invisible to it. `cfg_verify` has the
same blind spot here and was not consulted.

One adjacent hazard, flagged but not chased:
`recon/symbolized/app/ble_process_put_common.h:52` declares
`extern int rate_limited_elapsed_seconds_tick();` with an **empty parameter
list**, which suppresses arity checking in every TU that includes it. It is not
what let this bug through (`errno_wrapped_tick_call.c` carries its own local
prototype) but the same class could hide behind it elsewhere.

### 8.2 Handed over, not fixed

The repair belongs in the canonical trees, which this pass may not write — a
concurrent agent owns them. The one-line fix is
`rate_limited_elapsed_seconds_tick(param_2, 0, 0);` with a three-argument
prototype, in `recon/symbolized/app/errno_wrapped_tick_call.c` (lines 12 and 25)
and its mirrors `recon/named/errno_wrapped_tick_call.c` (11, 24),
`recon/app/src/FUN_0007d1d6.c` (3, 16), `recon/app/src_sym/`,
`recon/verified/src{,_sym}/FUN_0007d1d6.c`,
`recon/readable_sources/app/g1/errno_wrapped_tick_call.c` and
`recon/application/src/errno_wrapped_tick_call.c`.

**Predicted effect, stated in advance so it can be falsified:** `DashBoard_Reflash`
should be called with `param_3 == 1` **11** times instead of 4 under the seeded
dashboard stimulus, `spim_a p2_render` should go from 9,212 to **12,225**, and
`JBD_FRAMECOUNTER_P2` from `0x22D7` to **`0x2E65`**. The dashboard framebuffer
should stay byte-identical. If those three numbers do not all move together, the
diagnosis is wrong.
