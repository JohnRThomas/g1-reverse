# Stage 04 sub-batch **B** + Stage 05 — the R7 oracle run

**Written incrementally as the work ran. Nothing committed. Every number below
comes from a command that was actually run; where a claim is later corrected it
is corrected in place with a note rather than deleted.**

Inputs of this pass:

```
HEAD at start fc11c2c8  "P4 iter-43: the frozen-clock fix lands -- 7 screen regions
                         restored, prediction OVERSHOOTS by +64"
              (parent ddab9a5d "Stage 04 reworked + Stage 05 composition")
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)

HEAD at end   348c2f4e  "Stages 06-08: all five Stage-05 open items closed"
              -- the CONCURRENT agent's commit, landed 12:32:38 while this pass
              was writing up.  `git diff --stat fc11c2c8 348c2f4e` over
              recon/symbolized, recon/application, recon/symbols, recon/headers
              and recon/generated is EMPTY, so **not one pipeline input moved**
              and every measurement below stands at the inputs it names.  That
              commit did sweep up my regenerated MANIFEST/SIZE_GATE files, since
              I never commit.
```

The obligation this pass discharges (or fails to) is stated mechanically in the
stage's own manifest — `"declared_codegen_class": "size-changing"`,
`"oracle_required": true` — and in prose in `recon/refactor/README.md`'s Stage 04
gate record and `recon/analysis/staged_refactor_stage05.md` §10.

---

## 1. Regeneration against current HEAD

`driver.py status` **before** anything was regenerated:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **stale** | 2,626 | **3** |
| 01 literal_inline | current | 2,629 | 0 |
| 02 block_dedupe | current | 2,629 | 0 |
| 03 module_structure | current | 2,629 | 0 |
| 04 cohesive_tu | current | 2,629 | 0 |
| 05 cohesive_composition | current | 1,714 | 0 |
| 99 defect_probe | stale | 1,831 | 781 |

The three moved inputs are exactly iteration 43's §43.13 repair — the four
`memcpy` calls with a missing length constant:

```
recon/symbolized/app/clear_timeout_message.c
recon/symbolized/app/confirm_message.c
recon/symbolized/app/post_notification_cmd_process.c
```

Iteration 43's *other* fix (`errno_wrapped_tick_call.c`, the frozen clock) had
already landed mid-pass during the stage-05 pass and was already absorbed, which
is why only three inputs moved rather than four.

Stages 00 → 05 were **regenerated, never patched**.

### 1.1 What moved in the transformation output: **nothing**

| transformer | stage 05 report (HEAD `ddab9a5d` inputs) | **re-run at HEAD `fc11c2c8`** |
|---|---|---|
| 00 snapshot | 2,629 files / 2,567 parity rows | **2,629 / 2,567** |
| 01 literal_inline | 100 candidates / 192 sites | **100 / 192** (43 files rewritten) |
| 02 block_dedupe | 3,116 / 45 / 367 / 139 / 47 | **3,116 / 45 / 367 / 139 / 47** |
| 03 module_structure | 1,621 moved / 19 headers / 218 hoisted / 663 divergent | **1,621 / 19 / 218 / 663** |
| 04 cohesive_tu (`B`) | 1,615 → 700 TUs, 249 merged, 1,164 absorbed, 30 quarantined, 878 blocked | **identical, field for field** |
| 05 cohesive_composition (`N`) | 1,573 includes / 146 decls / 1,164 banners / 241 `S` candidates | **identical, field for field** |

`DEFECTS.json` is **940** entries (299 `declaration_disagrees_with_definition`,
277 `reconstructed_declaration_shadows_an_sdk_symbol`, 170 `arity_differs`,
132 `return_type_differs`, 62 `parameter_type_differs`) — up from the 663 + 267 =
930 the stage-05 report recorded, because iteration 43 changed three files'
declarations.

So the iteration-43 repairs **do not perturb the merge partition at all**: the
same 249 units absorb the same 1,164 files. What did change is where two of the
repaired functions live, and one of those is worth stating:

* `errno_wrapped_tick_call.c` is now **absorbed into the merged unit
  `ble/g1_ble_12.c` together with `rate_limited_elapsed_seconds_tick` itself**
  (verified in the stage 04 and stage 05 trees at lines 347/360 and 322/335).
  Before iteration 43 the stage-04 `type` refusal rule kept those two files
  apart — that refusal is exactly what
  `stage04_r7_validation.md` §8.1 identified as the reason the compiler was
  never allowed to see the contradiction. The defect is repaired, the refusal
  lapsed, and the two files are now one translation unit.
* `post_notification_cmd_process.c` → `notify/g1_notify_10.c`.
* `clear_timeout_message.c` and `confirm_message.c` remain single-source TUs in
  `notify/`; their `0x1b4` `memcpy` lengths are present in the stage trees.

`driver.py status` after regeneration: **stages 00–05 all current, 0 inputs
changed**. Stage 99 left stale (781 inputs) — it is the retired diagnostic probe,
as stages 03/04/05 all recorded.

`check-addresses` 0-1, 1-2, 2-3, 3-4, **4-5**: all `"identical": true`,
**2,567** addresses on both sides of every pair.
`recon/refactor` test suite: **105 / 105 PASS**.

### 1.2 An integrity anomaly in `materialize`, reported because it was real

The first `materialize 4` of this pass produced a tree that was **missing merged
unit files it had recorded in its own manifest**. It reported
`"files": 1714` but `"parity_rows": 2473` — 94 rows short of the 2,567 every
other stage produces — and `materialize 5` then died on the first missing file:

```
FileNotFoundError: recon/refactor/stage_04_cohesive_tu/tree/
                   recon/symbolized/app/analytics/g1_analytics_01.c
```

`ls` of that directory at the time showed only the stage-03 module header
`g1_analytics.h`; the four `.c` files the manifest listed were absent. Re-running
`materialize 4` then `materialize 5` unmodified produced `parity_rows: 2567`,
the files present, and a clean stage 05. **It did not reproduce**, so I cannot
name the mechanism and I am not going to invent one.

Two things about it are worth recording anyway:

1. `check-addresses 3 4` **would** have caught it (2,567 vs 2,473 → not
   identical), but `materialize` does not run that check itself, so the only
   reason the corruption surfaced at all is that the *next* stage happened to
   crash on it. A stage that is the last in the chain would have been built and
   captured silently short by 94 functions.
2. Everything measured below was taken from the **second**, verified
   materialisation, whose `parity_rows` is 2,567 and whose `check-addresses`
   chain is identical end to end.

---

## 2. Builds — four images, and a FIFTH `$rtinfo_pc`

Built with the repository's own entry point. No build file, linker script or
`tools/` module was edited to build any of them.

```sh
./recon/application/build_cohesive.sh                                                   app /private/tmp/g1-s4b-base
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh      app /private/tmp/g1-s4b-s03
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh           app /private/tmp/g1-s4b-s04
./recon/refactor/stage_05_cohesive_composition/tree/recon/application/build_cohesive.sh  app /private/tmp/g1-s4b-s05
```

| image | build | `zephyr.bin` | FLASH | RAM | `_end` | **`runtime_info_sync`** |
|---|---|---:|---:|---:|---|---|
| **in-tree HEAD** (`base`) | exit 0 | 956,480 B | 956,480 B 97.35 % | 253,765 B | `0x2003ff45` | **`0x00015c04`** |
| stage 03 (the size-gate base) | exit 0 | 956,356 B | 97.34 % | 253,765 B | `0x2003ff45` | `0x00015c04` |
| **stage 04 sub-batch `B`** | exit 0 | **956,276 B** | 97.33 % | 253,765 B | `0x2003ff45` | **`0x00016c14`** |
| **stage 05 (`N`)** | exit 0 | **956,276 B** | 97.33 % | 253,765 B | `0x2003ff45` | **`0x00016c14`** |

**`$rtinfo_pc` for the stage 04-B image is `0x00016c14` — a FIFTH distinct
value**, after `0x00015c04` (in-tree), `0x00015c0c` (sub-batch A) and
`0x0001632c` (sub-batch AB). It appears in no recorded recipe. `_end` is
`0x2003ff45` on all four, so the three RAM probes
`0x20040025 / 0x20040F38 / 0x20040FAA` carry over unchanged.

### 2.1 The two identities that decide what has to be captured

```
cmp g1-s4b-base/zephyr/zephyr.bin  g1-i43b-app/zephyr/zephyr.bin   -> IDENTICAL
cmp g1-s4b-s04/zephyr/zephyr.bin   g1-s4b-s05/zephyr/zephyr.bin    -> IDENTICAL (956,276 B)
```

The first says my `base` **is** iteration 43's final accepted image, so the
baseline this pass measures is iteration 43's state and not an older one. The
second is the stage-05 claim, **re-verified after regeneration rather than
assumed** — one capture of the stage 04 image therefore covers stage 05 exactly.

### 2.2 `driver.py size-gate`, declared versus achieved

```
size-gate 4  <stage-03 build> <stage-04-B build>
    declared size-changing -> measured size-changing   PASS   oracle_required TRUE
    section_deltas {text: -76, rodata: 0, datas: 0, bss: 0, noinit: 0}
    28 allocatable sections both sides; every other one delta 0

size-gate 5  <stage-04-B build> <stage-05 build>
    declared size-neutral  -> measured BYTE-IDENTICAL   PASS   oracle_required FALSE
    section_deltas all 0    image_byte_identical TRUE
```

Both `SIZE_GATE.json` files were rewritten in the stage directories. The `.text`
delta reproduces the stage-05 report's **−76 B** for sub-batch B exactly, at
these newer inputs.

### 2.3 Two transient integrity failures I could not reproduce, reported anyway

**(a) `materialize 4` — §1.2 above.**

**(b) The first `stage 04` build failed and the second, from a byte-identical
tree, succeeded.** The first `build_cohesive.sh` on the stage-04 tree exited 1
with

```
symbolized/app/unsorted/discovery_callback.c:71:41: error: expected '=', ',',
    ';', 'asm' or '__attribute__' before 'asm'
symbolized/app/unsorted/discovery_callback.c:98:303: error: 'uVar9' undeclared
```

and the failing command line carries **`-std=c99`**, i.e. exactly the C2 hazard
the README describes: the `set_source_files_properties` `-std=gnu99` flag for
that one file had not been applied. But the flag is not missing. `CMakeLists.txt`
is **sha-identical across the stage 03, 04 and 05 trees**
(`24c028ff…`) and all three spell the post-stage-03 path
`.../symbolized/app/unsorted/discovery_callback.c`; the source file is
sha-identical across all three trees (`278d0864…`); stage 03 and stage 05 built
that same file from that same list with no error, in the same batch, minutes
either side. Deleting the build directory and rebuilding stage 04 unchanged
gave exit 0 and FLASH 956,276 B.

**CORRECTION, made after the fact — I DO have a cause, and it is not mine.**
I first wrote here that I had no explanation. That was wrong, and the evidence
appeared later in the pass: **a concurrent agent was editing
`recon/refactor/` transformer sources while I was materialising and building.**
`ls -lT` timestamps against my own timeline:

```
recon/refactor/transforms/t03_module_structure.py   modified 11:56:15
recon/refactor/stagelib.py                          modified 12:03:03
recon/refactor/sdk_symbols.py                       modified 12:04:33
recon/refactor/driver.py                            modified 12:04:46
recon/refactor/transforms/t06,t07,t08_*.py          new, 12:06 - 12:19
recon/refactor/stage_0{6,7,8}_*/                    new, 12:22
```

against my own: `materialize 0..5` ran 11:48–11:53, the four builds ran
11:53–12:01, the captures 12:01–12:31. **`t03_module_structure.py` was rewritten
at 11:56:15 — inside the stage-03/stage-04 build window, and the stage-04 build
that failed was the one running at that moment.** The first `materialize 4/5`
anomaly at ~11:49 sits in the same live-edit window. That is a mechanism, and it
is a far better one than "unexplained": the pipeline's C1 guard protects the
*canonical* trees from the pipeline, and nothing protects the *pipeline* from a
second writer.

The `recon/refactor` test suite was **not** the cause — no `test_*.py` calls
`materialize` or writes outside a temporary directory — and I retract nothing
about that check, only about the conclusion I drew from it.

**What this costs, and what it does not.** It does not invalidate the
measurements: after the concurrent edits I re-materialised stages 4 and 5 and
got **byte-identical** manifests and whole trees (`a43e42af…` / `be8bbf1c…`,
`d8f7e1fa…` / `deaef122…`), and I rebuilt stages 03 and 04 from the trees as
they now stand and compared `zephyr.bin` against the images I captured — see
§2.4. What it does cost is the C4 rule's force: **a stage compile failure is
only proof the transformer is wrong if nobody else is writing the transformer at
the same time.** Anyone acting on that rule should check `git status` and file
mtimes before concluding it.

### 2.4 Re-verification after the concurrent edits — both images reproduce

Because §2.3 established that a second writer was active in `recon/refactor/`
during the build window, the two stage images this pass draws conclusions from
were **rebuilt from the trees as they stand after those edits** and compared:

```
./recon/refactor/stage_04_cohesive_tu/tree/.../build_cohesive.sh      app /private/tmp/g1-s4b-s04v   exit 0
./recon/refactor/stage_03_module_structure/tree/.../build_cohesive.sh app /private/tmp/g1-s4b-s03v   exit 0
cmp g1-s4b-s04/zephyr/zephyr.bin  g1-s4b-s04v/zephyr/zephyr.bin   ->  IDENTICAL
cmp g1-s4b-s03/zephyr/zephyr.bin  g1-s4b-s03v/zephyr/zephyr.bin   ->  IDENTICAL
```

Together with the byte-identical re-materialisation of stages 4 and 5, this
closes the question: **the images captured in §3 are exactly what the stage
trees produce at the end of this pass.** The concurrency cost a diagnosis and
two rebuilds, not a result.

*(Six of the seven `recon/refactor/**` files `git status` shows as modified —
`driver.py`, `stagelib.py`, `sdk_symbols.py`, `sdk_declared_symbols.json`,
`t03_module_structure.py`, and the new `stage_0{6,7,8}_*` /
`t0{6,7,8}_*.py` / `link_evidence.py` / `staged_refactor_stage06.md` —
**are the concurrent agent's, not mine.** My footprint is §7.)*

---

## 3. The oracle run — five seeded captures, two images, both stimuli

Every capture used `recon/emulator/scripts/capture_display_sensor_oracle.sh`
**unmodified**, with `G1_SEED=305419896` (the script's own default), `G1_HOOKS=0`,
`G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025`, the
frozen net image `g1-i30e-net`, and a `$rtinfo_pc` re-read from the ELF actually
booted.

| capture | image | stimulus | `$rtinfo_pc` |
|---|---|---|---|
| `s04_nav1`, `s04_nav2`, `s04_dash` | **stage 04 sub-batch B** (= stage 05) | nav ×2, dash | **`0x00016c14`** |
| `base_nav1`, `base_dash` | in-tree HEAD `fc11c2c8` | nav, dash | `0x00015c04` |

### 3.1 A correction that had to be made before anything could be compared:
### the committed NAVIGATION shipped oracle is STALE

`recon/emulator/reports/display_sensor_oracle.json` — the committed navigation
oracle — **differs from a regeneration of the seeded shipped navigation capture
in 8 of 69 measured fields**:

| field | committed | regenerated from `g1_ship_seed_q1` |
|---|---|---|
| `counters/RADIO_TX` | `0x230` | **`0x232`** |
| `counters/VC_DATA_EVENTS` | `0x215` | **`0x212`** |
| `counters/SCREEN_ID_ctx_d5` | *absent* | `0x0A` |
| `saadc/whole_run/stream_sha256` | `660cdf3b…` | `ebf06b30…` (iteration 42's pointer canonicalisation) |
| `twim1/p1_boot/stream_sha256` | `ef6fcb11…` | **`33cbd8c1…`** |
| `twim1/p2_render/stream_sha256` | `f418e5ba…` | `329565e4…` |
| `twim2/p1_boot/stream_sha256_regprog` | *absent* | `5e4a55c6…` |
| `twim2/p2_render/stream_sha256_regprog` | *absent* | `72854f7c…` |

The **dashboard** oracle is current — regenerating it from
`g1_ship_seed_dash_d1` gives **0 of 69** fields different, because iteration 42
regenerated it. Navigation was never regenerated after the seed landed.

This is not cosmetic. Comparing against the committed file would have scored
`twim1/p1_boot/sha` and `RADIO_TX` as *pre-existing gaps* rather than as
regressions, i.e. it would have hidden two of the eight failures below. **Every
number in this section is measured against the regeneration from the seeded
shipped capture**, which is what the Stage 04 A/AB gate also used.

### 3.2 THE ACCEPTANCE BAR — all four framebuffers byte-identical

`cmp` against the committed goldens, 153,600 B each, exit 0 every time, on both
the in-tree base and stage 04-B:

| | shipped golden | in-tree base | **stage 04-B (= stage 05)** |
|---|---|---|---|
| navigation `p1_boot` | `1d617c65…` 656 px | IDENTICAL | **IDENTICAL** |
| navigation `p2_render` | `b26c73b3…` 1,098 px | IDENTICAL | **IDENTICAL** |
| dashboard `p1_boot` | `0c5cc90b…` 0 px | IDENTICAL | **IDENTICAL** |
| dashboard `p2_render` | `19b1f24a…` 2,923 px | IDENTICAL | **IDENTICAL** |

`SCREEN_ID` `0x0A` / `0x06`, `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02` — equal to
shipped on both images, both stimuli.

### 3.3 Three-way field comparison — **STAGE 04 SUB-BATCH B FAILS R7**

69 measured fields per stimulus. A field that differs on **both** the in-tree
build and the stage build is a pre-existing gap and is not charged to the
refactor.

| | **navigation** | **dashboard** |
|---|---:|---:|
| EQ to shipped on both base and stage | 49 | 55 |
| pre-existing gap, identical on both | 3 | 10 |
| pre-existing gap, different value | 7 | 1 |
| **REFACTOR REGRESSION** (base EQ, stage NE) | **8** | **1** |
| refactor improvement (base NE, stage EQ) | 2 | 2 |

### 3.4 THE FINDING — sub-batch B breaks the SAME EIGHT FIELDS as sub-batch A

| field | shipped | in-tree base | **stage 04-B** | sub-batch A (2026-07-27) | sub-batch AB |
|---|---|---|---|---|---|
| `twim1 p1_boot` count | 371 | 371 EQ | **373** | 373 | 373 |
| `twim1 p1_boot` OPT3001 count | 33 | 33 EQ | **35** | 35 | 35 |
| `twim1 p1_boot` OPT3001 sha | `ef88ae8b…` | EQ | **`b759ccc5…`** | `b759ccc5…` | `b759ccc5…` |
| `twim1 p1_boot` merged-bus sha | `33cbd8c1…` | EQ | **`4f49068a…`** | `4f49068a…` | `4f49068a…` |
| `twim2 p1_boot` sha | `7ed8ddcd0c0d420d…` | EQ | **`03537cda890a2b7d…`** | `03537cda…` | `03537cda…` |
| `twim2 p1_boot` LSM6DSO sha | same | EQ | same | same | same |
| `twim2 p1_boot` `regprog` sha | `5e4a55c6…` | EQ | **`6d3c4072…`** | `6d3c4072…` | `6d3c4072…` |
| `counters/RADIO_TX` navigation | `0x232` | `0x232` EQ | **`0x234`** | `0x233` | `0x234` |
| `counters/RADIO_TX` dashboard | `0x232` | `0x232` EQ | **`0x235`** | `0x233` | `0x234` |

**Every hash is byte-for-byte the value sub-batch A produced.** Not the same
*kind* of failure — the same failure, to the digit.

The two improvements are also the same ones: on both stimuli, `twim2 p2_render`
goes from NE to byte-equal with shipped
(navigation `334912…` → `191ba08b9fa130…` == shipped;
dashboard `b774cb…` → `fbc6ec681e02d0…` == shipped). As the A/AB report said,
this is luck rather than repair — the same phase mechanism happening to land
right — and it is not counted as progress.

### 3.5 Decoded transaction by transaction — the same two re-phasings

`difflib` over the oracle's own canonical per-device streams, base vs stage 04-B:

```
OPT3001, twim1 p1_boot
  EQUAL   base[0:33] == stage[0:33]     (33)
  INSERT  base[33:33] stage[33:35]
      +  opt3001_ambient_light  45|W|00
      +  opt3001_ambient_light  45|R|0000

LSM6DSO, twim2 p1_boot   (1,089 -> 1,089)
  EQUAL   base[0:99]     == stage[0:99]        (99)
  DELETE  base[99:103]                          -- 6B|W|28 / 6B|R|… / 6B|W|22 / 6B|R|…
  EQUAL   base[103:1089] == stage[99:1085]     (986)
  INSERT                    stage[1085:1089]   -- the same four, at the tail
```

Character for character the §3.5 decode of sub-batch A. And the poll-train
phase, measured from `twim1.p1.trace` ticks:

| image | OPT3001 polls in `p1_boot` | steady-state period | poll #13 | last poll |
|---|---:|---|---|---|
| shipped | 17 (33 transactions) | 0.350250 s | 4.295530 s | 5.696592 s |
| in-tree base | 17 (33) | 0.350310 s | 4.304170 s **+8.64 ms** | 5.705322 s |
| **stage 04-B** | **18 (35)** | 0.350310 s | **4.203650 s −100.52 ms vs base** | **5.955170 s** |

The *period* is unchanged (identical to base, 0.350310 s); the train's **phase**
moves −100.52 ms and one extra poll fits inside the 6 s wall. Sub-batch A moved
it −100.7 ms. Two different sub-batches, two different linked sizes, the same
displacement to within 0.2 ms.

### 3.6 What holds

* Every field iteration 43 made byte-exact on the **dashboard** is unchanged:
  `spim_a p2_render` 12,289, `JBD_FRAMECOUNTER_P2` `0x2EA3`,
  `twim1 p2_render` 584 with nPM1300 514 — **bit-identical between base and
  stage 04-B**, so the merge neither helps nor hurts the iteration-43 residue.
* navigation `spim_a` whole run 3,645 (`p1`+`p2` = 808 + 2,837 on the stage,
  786 + 2,859 on base, 764 + 2,881 shipped — the split is the known §42.10
  non-defect, the total is exact on all three).
* navigation `twim1 p2_render` 599 with all four per-device streams EQ;
  `JBD_FRAMECOUNTER_P2` `0x0D61`.
* Every pre-existing gap is unchanged or moves toward shipped. Stage 04-B makes
  none of them worse.

### 3.7 Codegen delta, for the record

| | `text` | `rodata` | `datas` | `bss` | `noinit` |
|---|---:|---:|---:|---:|---:|
| in-tree base | 492,692 | 456,660 | 3,327 | 189,230 | 60,021 |
| stage 03 | 492,688 | 456,536 | 3,327 | 189,230 | 60,021 |
| **stage 04-B / stage 05** | **492,612** | 456,536 | 3,327 | 189,230 | 60,021 |
| **Δ stage 04-B vs stage 03** | **−76** | 0 | 0 | 0 | 0 |
| Δ stage 04-B vs in-tree base | −80 | −124 | 0 | 0 | 0 |

### 3.8 Determinism, re-verified at this pass's images

```
stage04-B  nav1 vs nav2   diff -r over the regenerated oracle directories -> NO OUTPUT
```

Run 1 and run 2 of the stage 04-B image under the navigation stimulus produce a
**byte-identical** regenerated oracle directory, including all eight framebuffer
artifacts. A single seeded run is evidence; the eight regressions cannot be
excused as jitter.

---

## 4. WHY it fails — the displacement is QUANTISED, not proportional

This is the part that changes the recommendation, and it is measured rather than
argued. The OPT3001 poll train's first steady-state poll, read straight from
`twim1.p1.trace` ticks, across **every image on this machine**:

| image | `.text` Δ vs in-tree | OPT3001 poll #13 | polls in `p1_boot` | whole-run OPT3001 |
|---|---:|---|---:|---:|
| **shipped firmware** | — | **4.295530 s** | 17 (33 tx) | 113 |
| in-tree base (= `g1-i43b-app`) | 0 | **4.304170 s** | 17 (33) | 113 |
| iteration 43's own capture `g1_i43_b_nav1` | 0 | 4.304170 s | 17 (33) | 113 |
| **stage 03** | **−4** (rodata −124) | **4.304200 s** | 17 (33) | 113 |
| stage 04 **A** (2026-07-27 pass) | −16 | **4.203950 s** | **18 (35)** | 115 |
| **stage 04 B** (this pass) | **−80** | **4.203650 s** | **18 (35)** | **115** |
| stage 04 **AB** (2026-07-27 pass) | −92 | **4.203460 s** | **18 (35)** | 115 |

There are **exactly two slots**: `4.3042 s` and `4.2036 s`, **100.5 ms apart**.
Three images whose `.text` deltas span −16 B to −92 B — a factor of six — land
in the *earlier* slot **within 0.5 ms of each other**. Stage 03 at −4 B stays in
the base slot within 0.03 ms.

**The displacement is not a function of how much the image shrank.** It is a
threshold: either a perturbation leaves the periodic thread in its slot, or it
moves it one whole step of ≈100.5 ms.

### 4.1 The LSM6DSO regression is the SAME 100.5 ms step — correcting §3.5

The `twim2 p1_boot` diff is **not** "a poll pair rotating to the tail"; that is
`difflib` aligning a repeating pattern, and §3.5 reports its output rather than
its meaning. The first *actually* differing canonical line is index **967**, and
only 18 of 1,089 lines differ, all between 967 and 984. What moved is a periodic
**ODR-reconfiguration block** (`0180 / 46 / R / 0100 / 10 / R / 1020 / …`):

```
base        poll pair 3.889460 s   then the reconfig block at 3.944430 s
stage 04-B  reconfig block 3.843920 s   then the poll pair at 3.889190 s
                                    3.944430 - 3.843920 = -100.51 ms
```

**−100.51 ms — the same step, to 10 µs, as the OPT3001 train.** Both navigation
regressions are one phenomenon: a periodic dispatch thread's phase steps by one
≈100.5 ms slot. The stream is otherwise identical: 1,089 transactions in
`p1_boot` and **2,289 whole-run on every image including shipped**.

### 4.2 The margin, and why it decides the question

The OPT3001 steady-state period is 350.31 ms and `p1_boot` ends at 6.000 s.

| image | last `p1_boot` poll | next poll would be | **margin before an 18th poll appears** |
|---|---|---|---:|
| **shipped** | 5.696592 s | 6.046843 s | **46.8 ms** |
| in-tree base | 5.705322 s | 6.055632 s | **55.6 ms** |
| stage 04-B | 5.955170 s (the 18th) | 6.305480 s | overshot by 44.8 ms |

**The shipped firmware itself is 46.8 ms away from producing 35 transactions
instead of 33** — 0.78 % of the 6-second phase. The in-tree build has 55.6 ms of
margin. The smallest displacement any perturbation produced is **100.5 ms**.

> **The step is larger than the margin. There is no landing between the two
> slots.**

### 4.3 So: (a), (b), or a third option?

**(a) A size-compensating measure is REFUTED by measurement, not judged
unattractive.** For a pad to restore `twim1 p1_boot == 371` it would have to put
the dispatch thread back inside the base slot, and the observable moves in
≈100.5 ms steps while the tolerance is 55.6 ms. Three images at −16, −80 and
−92 B all land in the same alternative slot, so the displacement cannot be
titrated by choosing how many bytes to give back. The only "compensation" that
demonstrably works is the one stages 01–03 already have: an image that is
**byte-identical** — which for a merge stage means not merging.

**(a′) A corollary: the A/AB gate record's recommendation 1 is refuted too.**
That record recommends fixing the boot-path timing gap first (our build is
+3.45 ms late to the first bus transaction; iteration 43 root-caused it to
`g1_ram_arena` over-zeroing, §43.10, worth −2.40 ms). It would not help: the gap
is 3.45 ms and the slot step is 100.5 ms, a factor of 29. Closing the *whole*
boot-lateness gap moves the train by under 4 % of one step and cannot change
which slot a merged image lands in. Iteration 43 showed the same thing from the
other side: a **+2 B** relink that shifted 1,000 text symbols and changed 64 SPI
transactions left all 69 navigation fields bit-identical (§43.7). Being inside
the slot is what matters, not being close to shipped.

**(b) Accepting that bus phase is not part of the equivalence bar is what the
evidence supports** — and it can now be stated with a number instead of a shrug:

* the failing navigation streams are **content-identical**. Whole-run LSM6DSO is
  2,289 on shipped and on every one of our images; OPT3001 differs by exactly
  one extra poll in 20 s (113 → 115); the OPT3001 poll *period* is identical to
  30 ns; the LSM6DSO block that moved is the same block with the same payload.
* the criterion they fail is not "does the firmware do the same thing" but "does
  a periodic thread's phase fall on the same side of the harness's 6 s phase
  wall", and the shipped firmware's own margin on that question is **46.8 ms in
  6,000 ms**.
* `RADIO_TX` (`0x232` → `0x234` navigation, `0x235` dashboard) is the same
  family: 2–3 extra radio frames in a 20 s window, on an image whose
  `ESB_MASTER_FRAMES` +1 is already documented (iteration 43 §43.11) as a
  boot-phase effect awaiting an equal boot phase.

**What I will NOT do, and did not do:** widen a tolerance so these go green. No
oracle file was edited, no criterion was relaxed, no tolerance was added, and
the nine regressions are recorded above at their measured values. Option (b) is
a decision about what the acceptance bar *is*; it is the owner's to take, not a
gate-file edit for a pipeline agent to slip in.

**The third option the evidence actually points at is a criterion, not a
policy: re-baseline these two `p1_boot` streams on the DECODED difference.**
Every comparison in this project hashes an ordered transaction stream. For these
two the honest criterion the data supports is *(i)* the per-device multiset and
its order **within a poll train**, *(ii)* the poll period, and *(iii)* an
explicit phase tolerance. Stage 04-B satisfies (i) and (ii) exactly and fails
only (iii). **The residue such a criterion would fail to catch is real and must
be published with it**: a defect that changes *when* a sensor is sampled without
changing *what* is exchanged — a wrong sleep constant, a dropped tick, a thread
priority inversion — is exactly a 100 ms-class phase move, and is exactly what
it would stop detecting. Iteration 43's frozen clock was found by a stream
comparison, not by pixels; weakening stream comparison has a precedent for a
cost.

I am not implementing that. I am recording that it is the only one of the three
that both admits stage 04 and keeps a stated, falsifiable bar.

---

## 5. VERDICT

### Stage 04 sub-batch **B** — **FAILS R7**

Eight navigation fields and one dashboard counter that the in-tree build
reproduces byte-exactly against the shipped firmware are broken:
`twim1 p1_boot` (371 → **373**, OPT3001 33 → **35** plus its sha and the
merged-bus sha), `twim2 p1_boot` (1,089 transactions in a different order,
`7ed8ddcd0c0d420d…` → **`03537cda890a2b7d…`**, including the `regprog`
canonicalisation), and `counters/RADIO_TX` (`0x232` → **`0x234`** navigation,
**`0x235`** dashboard).

**They are the same eight fields, with the same hashes, that sub-batch A broke.**
The rework that made B the default — taken on the measurement that 100 % of the
damage was A's and that AB-against-A gave 0 regressions — does not survive
contact with a B-only image. It could not have: AB-against-A measured B's
*incremental* effect on top of A, in a run where A had already moved the thread
into the other slot. B on its own moves it into the same slot by itself.

### Stage 05 — **inherits the failure exactly**

`cmp` of `zephyr.bin` between the stage 04-B and stage 05 builds is **identical,
956,276 B** (re-verified at these inputs, not assumed), and `size-gate 5`
measures `byte-identical` with every allocatable section delta 0. Stage 05's
composition work is sound and costs nothing observable; it is blocked solely by
stage 04.

### What holds

* **All four acceptance framebuffers byte-identical to the committed goldens**
  on both stimuli — `1d617c65…` 656 px, `b26c73b3…` 1,098 px, `0c5cc90b…`
  all-zero, `19b1f24a…` 2,923 px, 153,600 B each, `cmp` exit 0.
* `SCREEN_ID` `0x0A`/`0x06`, `DISPLAY_ON` `0x01`, `ESB_SYNC` `0x02` — EQ to
  shipped on every image.
* Navigation `spim_a` whole run 3,645; `twim1 p2_render` 599 with all four
  per-device streams EQ; `JBD_FRAMECOUNTER_P2` `0x0D61`.
* Every dashboard number iteration 43 moved is **bit-identical between base and
  stage 04-B**: `spim_a p2_render` 12,289, `JBD_FRAMECOUNTER_P2` `0x2EA3`,
  `twim1 p2_render` 584 / nPM1300 514.
* **Stage 03 is clean at these inputs** — 0 regressions, 0 improvements and 0
  gaps-that-moved: bit-identical to the in-tree build on all 69 navigation
  fields at `.text` −4 B / `.rodata` −124 B. That is a new measurement this pass
  and it is what brackets the threshold.

### Static ladder, at these inputs

| gate | in-tree base | stage 04-B | stage 05 |
|---|---|---|---|
| app build | exit 0 | exit 0 | exit 0 |
| FLASH | 956,480 B 97.35 % | **956,276 B 97.33 %** | **956,276 B** |
| RAM | 253,765 B 56.32 % | Δ 0 | Δ 0 |
| `nm -u` undefined | 0 | **0** | **0** |
| duplicate global definitions | 0 | **0** | **0** |
| sized text symbols / distinct names | 3,013 / 2,935 | **3,013 / 2,935** | **3,013 / 2,935** |
| build-log lines with `warning:` | 2,987 | **2,975 (Δ −12)** | **2,975 (Δ 0)** |
| `size-gate` | — | declared `size-changing` → measured `size-changing`, **PASS**, `oracle_required` TRUE | declared `size-neutral` → measured **`byte-identical`**, PASS, `oracle_required` FALSE |

| whole-pipeline gate | result |
|---|---|
| `driver.py status` | stages **00–05 current**, 0 inputs changed (99 stale, retired probe) |
| `check-addresses` 0-1, 1-2, 2-3, 3-4, 4-5 | all `identical: true`, **2,567** both sides |
| `recon/refactor` test suite | **105 / 105 PASS** |
| idempotence, stage 04 | `MANIFEST.json` `a43e42af…` → `a43e42af…`, whole tree `be8bbf1c…` → `be8bbf1c…` |
| idempotence, stage 05 | `MANIFEST.json` `d8f7e1fa…` → `d8f7e1fa…`, whole tree `deaef122…` → `deaef122…` |
| `tools/verify_data.py` | **995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)** |
| `gen_retained_sources.py --check` | "retained source lists are current" |
| `check_ram_pin_collisions --core app` (stage 05 ELF) | **627 bound OK / 0 escaping / 0 unknown inside a live object** (20 raw-literal pins outside the RAM region, 3 abs symbols not in the linker scripts — both unchanged) |
| `check_thread_create_stack_args --trials 120` | **10 / 10 PASS, exit 0** |

**Net core untouched.** No net input moved, no net build was run, the frozen
`g1-i30e-net` image was booted in all six captures. `check_net_raw_literals` and
`verify_net_stock_data_window` need a net ELF and were therefore **not run** —
recorded as not-run, not as passed.

**`cfg_verify` was not run and is not cited.** Every number in this report comes
from a build, a `cmp`, an ELF section table, an `nm`, a seeded Renode capture or
a test run.

---

## 6. What I did NOT close, and why

1. **Stage 04 is still not landable, and I did not make it landable.** Sub-batch
   B fails the same eight fields as A. The `MANIFEST.json` obligation
   `"oracle_required": true` is **not discharged as satisfied** — the oracle was
   run and the stage failed it. I did not flip the field: it is an accurate
   statement of the gate, and flipping it would say the opposite of what was
   measured.
2. **I did not bisect sub-batch B**, for the reason the README gives and which
   §4 now supports with numbers: there is no guilty unit, and the observable is
   quantised, so a bisection would find whichever unit happens to sit at the
   threshold rather than a defect.
3. **I did not decide between option (b) and the third option in §4.3.** Both
   are changes to the acceptance bar and belong to the owner. I edited no oracle
   file, widened no tolerance and added none.
4. **I did not regenerate the stale committed navigation oracle**
   (`recon/emulator/reports/display_sensor_oracle.json`, §3.1 — 8 of 69 fields
   differ from a seeded regeneration). It is within my remit and it is a real
   defect in the gate files, but regenerating a *gate* in the same pass that
   reports a *failure measured against that gate* is exactly the move that
   should not be made by the agent doing the reporting. The evidence and the
   command are in §8; it is a two-minute job for whoever owns the decision.
5. **The two transient integrity failures (§1.2, §2.3) are explained but not
   fixed.** A concurrent agent was rewriting `recon/refactor/` transformer
   sources during my materialise/build window. I did not add the guard that
   would make this visible — `materialize` still does not assert its own
   `parity_rows` against `check-addresses`, which is the check that would have
   caught the 2,473-row tree without waiting for the next stage to crash. I
   deliberately did not add it: `driver.py` was being actively edited by the
   other agent while I worked, and two writers is what caused the problem in the
   first place. It is filed in the README record instead.
6. **The +3.45 ms boot lateness and the `g1_ram_arena` over-zeroing are
   untouched.** §4.3(a′) shows closing them would not change this verdict, which
   is a reason to *deprioritise* them for the merge question — not a reason to
   consider them closed. They remain iteration 43 §43.15 item 2.
7. **`ESB_MASTER_FRAMES` / `ESB_ACKS` `0x176` vs `0x175`** unchanged and
   untouched, as iteration 43 left it, with its falsification test unrun.
8. **Sub-batch S (internal linkage, 241 candidates) is still not applied**, and
   sub-batch A is measured but not default.
9. **Stage 99 left stale** (781 inputs). Retired diagnostic probe.
10. **Nothing was committed.** The tree is left dirty.

---

## 7. Footprint — everything this pass wrote

```
 M recon/refactor/stage_0{0,1,2,3,4,5}_*/MANIFEST.json     (regenerated)
 M recon/refactor/stage_03_module_structure/DEFECTS.json   (regenerated, 930 -> 940)
 M recon/refactor/stage_0*_*/PARITY_MAP.json               (regenerated)
 M recon/refactor/stage_04_cohesive_tu/{QUARANTINE,HAZARDS}.json
 M recon/refactor/stage_04_cohesive_tu/SIZE_GATE.json      (re-measured, text -76 B)
 M recon/refactor/stage_05_cohesive_composition/SIZE_GATE.json
 M recon/refactor/README.md                 (Stage 04-B R7 gate record appended)
?? recon/analysis/stage04b_r7_validation.md                (this file)
```

**I committed nothing.** But the concurrent agent's commit `348c2f4e`
(12:32:38) swept up everything of mine that was dirty at that moment — the
regenerated MANIFEST/DEFECTS/SIZE_GATE files and the bulk of the README gate
record. At the end of the pass `git status` is therefore
`M recon/refactor/README.md` (my two later corrections) plus
`?? recon/analysis/stage04b_r7_validation.md`, and the rest of my footprint is
inside someone else's commit. Recorded rather than tidied.

`recon/refactor/.gitignore` excludes `stage_*/tree/`, so the regenerated trees do
not appear in `git status`. **No canonical tree, no `recon/symbols`, no
`recon/application`, no `tools/` module, no emulator script, no emulator report,
no linker script, no `recon/board/**` and nothing under `~/Projects/armemul` was
written.** Every `.resc` this pass generated lives in `/private/tmp/g1-s4b/`.

---

## 8. Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
for n in 0 1 2 3 4 5; do $V recon/refactor/driver.py materialize $n; done   # parity_rows MUST be 2567 every time
for a in 0 1 2 3 4; do $V recon/refactor/driver.py check-addresses $a $((a+1)); done
$V -m unittest discover -s recon/refactor -p 'test_*.py'                    # 105/105

./recon/application/build_cohesive.sh                                                  app /private/tmp/g1-s4b-base
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh     app /private/tmp/g1-s4b-s03
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh          app /private/tmp/g1-s4b-s04
./recon/refactor/stage_05_cohesive_composition/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4b-s05
$V recon/refactor/driver.py size-gate 4 /private/tmp/g1-s4b-s03 /private/tmp/g1-s4b-s04
$V recon/refactor/driver.py size-gate 5 /private/tmp/g1-s4b-s04 /private/tmp/g1-s4b-s05
cmp /private/tmp/g1-s4b-s04/zephyr/zephyr.bin /private/tmp/g1-s4b-s05/zephyr/zephyr.bin

# $rtinfo_pc PER IMAGE -- base/s03 0x00015c04, stage04-B and stage05 0x00016c14 (a FIFTH value)
arm-zephyr-eabi-nm zephyr.elf | grep -wE 'runtime_info_sync|_end'
bash /private/tmp/g1-s4b/cap.sh s04_nav1  /private/tmp/g1-s4b-s04  0x00016c14 nav
bash /private/tmp/g1-s4b/cap.sh s04_dash  /private/tmp/g1-s4b-s04  0x00016c14 dash
bash /private/tmp/g1-s4b/cap.sh base_nav1 /private/tmp/g1-s4b-base 0x00015c04 nav
bash /private/tmp/g1-s4b/cap.sh base_dash /private/tmp/g1-s4b-base 0x00015c04 dash
bash /private/tmp/g1-s4b/cap.sh s04_nav2  /private/tmp/g1-s4b-s04  0x00016c14 nav   # determinism
bash /private/tmp/g1-s4b/cap.sh s03_nav1  /private/tmp/g1-s4b-s03  0x00015c04 nav   # the threshold bracket

# THE SHIPPED REFERENCE MUST BE REGENERATED FROM THE SEEDED SHIPPED CAPTURE (see 3.1):
$V recon/emulator/scripts/build_display_sensor_oracle.py                    /private/tmp/g1_ship_seed_q1      /private/tmp/g1-s4b/rep_ship_nav
$V recon/emulator/scripts/build_display_sensor_oracle.py --screen=dashboard /private/tmp/g1_ship_seed_dash_d1 /private/tmp/g1-s4b/rep_ship_dash
$V /private/tmp/g1-s4r7/cmp3.py   <rep_ship>/*.json <rep_base>/*.json <rep_s04>/*.json LABEL
$V /private/tmp/g1-s4r7/devdiff.py <capA> <capB> twim1 p1_boot opt3001_ambient_light
```

---

## 9. A falsifiable prediction for stages 06–08, which landed during this pass

The concurrent agent committed stages **06 unit_composition**, **07
internal_linkage** and **08 call_order** at `348c2f4e`, after every measurement
above was taken. Their own `SIZE_GATE.json` files say:

| stage | declared | measured | `text` Δ | `oracle_required` |
|---|---|---|---:|---|
| 06 unit_composition | `byte-identical` | **`byte-identical`** | 0 | false |
| 07 internal_linkage | `size-changing` | `size-changing` | **−276** | **true** |
| 08 call_order | `size-changing` | *(no `SIZE_GATE.json` yet)* | — | **true** |

**Stage 06 inherits this verdict exactly** — its image is byte-identical to
stage 05's, which is byte-identical to stage 04-B's, which is the image that
failed above. It needs no capture of its own and it is not landable while stage
04 is not.

**Prediction for stage 07, stated in advance so it can be falsified.** §4 says
the observable moves in ≈100.5 ms steps with a 55.6 ms margin, and that any
perturbation past the threshold lands in the same alternative slot regardless of
magnitude (−16, −80 and −92 B all did). Stage 07 is −276 B. So when it is
captured under the seeded navigation stimulus it should show:

* `twim1 p1_boot` **373**, OPT3001 **35**, sha **`b759ccc5…`**, merged-bus sha
  **`4f49068a…`**;
* `twim2 p1_boot` 1,089 transactions with sha **`03537cda890a2b7d…`** and
  `regprog` **`6d3c4072…`**;
* OPT3001 poll #13 at **≈4.2036 s**, not ≈4.3042 s;
* all four framebuffers **byte-identical**.

If stage 07 instead lands back at ≈4.3042 s with `twim1 p1_boot == 371`, §4's
two-slot model is wrong and a size-compensating measure is back on the table.
Either outcome is worth the one capture it costs.
