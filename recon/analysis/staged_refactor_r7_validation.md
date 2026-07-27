# Staged refactor — R7 (observable side-effect equivalence) validation pass

**Status: IN PROGRESS.** Written incrementally as the work runs so a mid-run
process failure cannot lose it. Nothing here is committed.

## 0. Starting state, measured

```
$ git rev-parse HEAD
a2f3303decfbacbb9ecfa6e430b0a415d94c466d   "P4 iter-40: ADC hits the oracle EXACTLY (998/998) -- six WLC NDEF ops recovered"

$ git status --porcelain
?? Even+Realities_1.9.0.xapk           <- unrelated, untracked archive
```

The working tree was **clean** at HEAD apart from that one untracked archive
when this pass started. (The session brief's `gitStatus` snapshot listed a dozen
modified files and a different commit list; that snapshot is stale — those edits
are *in* commit `a2f3303d`.)

**CORRECTION, written after the fact rather than left to stand.** At **04:19:48**
the concurrent parity agent began landing a large batch (807 files under
`recon/app/src`, 802 under `recon/verified/src`, 77 under `recon/symbolized`,
69 `recon/named`, 68 `recon/readable_sources`, plus
`recon/analysis/latent_defect_harvest.md`), which moved **75** of this
pipeline's inputs and made stage 00 stale again. **Every build and every
our-build capture in this report finished before that:** app builds at 04:03:00
and 04:04:01, the last of the six our-build Renode captures at 04:15:48. The one
thing that ran afterwards is the *shipped-firmware* navigation capture (04:21:00),
which boots `app_update.bin` / `netcore_image.bin` and reads none of our sources.

So nothing here was measured against a moving input — but the stages are stale
again as of the end of this pass, and the repair is the usual
`materialize 0 && 1 && 2` plus a re-run of the ladder. That is the mechanism
working, not a problem.

`armemul` (the Renode platform repo) checked before anything ran:

```
$ cd ~/Projects/armemul && git status --porcelain
 M models/NRF5340_SPIM.cs        <- the opt-in TraceFile hook, 3 mentions   PRESENT
 M models/NRF5340_TWIM.cs        <- the opt-in TraceFile hook, 2 mentions   PRESENT
?? g1-ours.resc  ?? g1-ours-paired.resc                                      PRESENT
```

Both uncommitted capture hooks and both `-ours` machine scripts survive. The
oracle capture is therefore runnable.

## 1. Staleness BEFORE regeneration

`driver.py status` at HEAD:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---|
| 00 snapshot | **stale** | 2,600 | **12** |
| 01 literal_inline | current (vs its own recorded stage-00 input) | 2,612 | 0 |
| 02 block_dedupe | current (vs its own recorded stage-01 input) | 2,612 | 0 |
| 99 defect_probe | current | 2,612 | 0 |

The 12 moved inputs are exactly iteration 39/40's landing:

```
recon/symbolized/app/battery_soc_curve_model_init.c     (i39/i40 fix 3 + §40.10)
recon/symbolized/app/event_record_init.c                (i40 rebind)
recon/symbolized/app/fill_record_type8.c                (i40 rebind)
recon/symbolized/app/invoke_optional_op_offset12.c      (i40 dropped-arg fix)
recon/symbolized/app/opt_list_encode.c                  (i40)
recon/symbolized/app/opt_node_serialize.c               (i40)
recon/symbolized/app/opt_node_serialize_7c5ba.c         (i40)
recon/symbolized/app/opt_node_total_len.c               (i40)
recon/symbolized/app/opt_node_value_len.c               (i40)
recon/symbolized/app/serialization_read_or_copy.c       (i40)
recon/symbols/g1_app_globals.ld                         (6 code pins deleted, 5 added)
recon/symbols/g1_app_symbols.h                          (6 externs, 6 ADDR_*_THUMB, 5 globals)
```

So the prediction in the brief holds: **both landed stages were materialised
before iterations 39/40 and are stale.** Stages 01 and 02 report "current" only
because staleness is computed against the recorded predecessor tree, which has
not been regenerated yet; regenerating 00 cascades.

*(sections appended as work proceeds)*

---

## 2. Regeneration — stages 00 → 01 → 02 against current HEAD

Regenerated, never hand-patched, in order:

```
$ driver.py materialize 0   {"files": 2619, "parity_rows": 2567, "files_copied": 2619, "transformations": 0}
$ driver.py materialize 1   {"files": 2619, "parity_rows": 2567,
                             "candidates_accepted": 100, "candidates_quarantined": 1934,
                             "sites_inlined": 178, "files_rewritten": 43, "files_changed_total": 46,
                             "rodata_objects_withdrawn": 100, "object_bytes_withdrawn": 3997,
                             "provide_pins_retired": 100, "extern_declarations_removed": 100}
$ driver.py materialize 2   {"files": 2619, "parity_rows": 2567,
                             "A_volatile_spelling_sites": 3116, "A_files": 584,
                             "A_spellings_before_after": [84, 52],
                             "B_noreturn_sites": 45, "C_log_route_sites": 266,
                             "C_log_route_pairs_seen": 409, "D_assert_fail_sites": 135,
                             "E_files_converted": 1, "E_declarations_withdrawn": 2,
                             "E_files_quarantined": 45,
                             "latent_defects_found": 192, "files_changed_total": 714}
```

**Rounds needed: ZERO.** No transformer change was required; both regenerations
ran first-try. There was therefore no compile failure to triage into bucket (a)
or bucket (b) *at the materialize step*; the build-step triage is §3.

### 2.1 Staleness AFTER regeneration

`driver.py status` → stages **00, 01, 02 all `"current"`**,
`inputs_unchanged: 2619`, `inputs_changed: []`.

*Correction to a claim I nearly made:* stage **99** (`defect_probe`) reports
`"stale"` with the same 12 inputs, because it is a *diagnostic* tree derived
from stage 01 and I deliberately did not regenerate it — it is expected not to
compile and is not part of the acceptance ladder. Stated so the `status` output
is not misread as a failure of this pass.

`driver.py check-addresses 0 1` and `1 2`: **identical, 2,567 addresses on both
sides, 0 gained, 0 lost** (was 2,561 — exactly +6, iteration 40's six recovered
WLC NDEF op functions).

`python -m unittest discover -s recon/refactor -p 'test_*.py'` → **7/7 OK**.

### 2.2 Did the site counts change now that i39/i40 added new sources? **No — and that is a measured result, not an oversight.**

The brief predicted the counts should move. They did not, and the reason is
precise. Comparing the new `MANIFEST.json` against the committed one
(`git show HEAD:…`) the ONLY differences are:

| key | old | new |
|---|---:|---:|
| `file_count` (all three stages) | 2,612 | **2,619** |
| `input_provenance.retained_sources.app` | 1,609 | **1,615** |
| stage 02 `A_volatile_spelling.total_accessor_sites_seen` | 6,069 | **6,078** |

Everything else — every stage-01 candidate/site/withdrawal figure, every
stage-02 sub-batch rewrite count, and the entire `QUARANTINE.json` and
`DEFECTS.json` of both stages (`git status` shows them **unmodified**) — is
byte-identical.

The +7 files are the six new symbolized WLC sources plus the new wiring TU
`recon/application/app/src/g1_wlc_ndef_type_records.c`; the +6 parity rows are
the six new function addresses. So the new code **is** in the input set — this
is not a case of the pipeline failing to see it.

Why it contributes 0 rewrites, verified per file rather than assumed:

| file (all 16 confirmed present in the stage tree) | `rodata_*` refs | `__builtin_unreachable` | `assert_post_action` | volatile-cast spellings |
|---|---:|---:|---:|---|
| `wlccap_record_value_len` / `wlcstai_record_value_len` | 0 | 0 | 0 | none |
| `wlccap_record_next_fragment` | 0 | 0 | 0 | `*(volatile unsigned char *)`×2, `*(volatile unsigned int *)`×3 |
| `wlcstai_record_next_fragment` | 0 | 0 | 0 | `*(volatile unsigned int *)`×4 |
| `wlccap_record_encode` / `wlcstai_record_encode` | 0 | 0 | 0 | none |
| `battery_soc_curve_model_init` | 0 | 0 | 0 | `*(volatile float *)`×6 |
| `event_record_init`, `fill_record_type8` | 1 each | 0 | 0 | none |
| `invoke_optional_op_offset12`, `opt_list_encode`, `opt_node_serialize*`, `opt_node_total_len`, `opt_node_value_len` | 0 | 0 | 0 | 1 (canonical) |
| `serialization_read_or_copy` | 0 | 0 | 0 | `*(volatile int*)`×2, `*(volatile unsigned int*)`×1 — **non-canonical** |

The nine new accessor sites (5 + 4) are exactly the `6,069 → 6,078` delta, and
**all nine are already in the canonical spelling**, so sub-batch A sees them and
correctly rewrites none. `serialization_read_or_copy` is the one changed file
stage 02 does rewrite — 3 whitespace normalisations — and it was already being
rewritten before i40 changed its body, so its contribution to the 3,116 is
unchanged.

The two `rodata_*` references in `event_record_init` / `fill_record_type8` are
i40's *rebinds* (numeric pins replaced by named symbols); neither is a stage-01
inline candidate (they are data-object references, not string arguments in an
accepted callee's argument position).

**Conclusion:** stages 01 and 02 are semantically unchanged by the i39/i40
landing. The regeneration was still mandatory — the stage trees now carry the
i39/i40 *content* of the 10 edited files and the 7 new ones, which is what the
build and the oracle actually exercise.

---

## 3. Builds and the non-emulator gate ladder

Five builds, all with the repository's / stage tree's own entry point, **no
build file, linker script or `tools/` module edited anywhere**:

```sh
./recon/application/build_cohesive.sh                                          app /private/tmp/g1-r7-base-app
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh app /private/tmp/g1-r7-s1-app
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   app /private/tmp/g1-r7-s2-app
./recon/application/build_cohesive.sh                                          net /private/tmp/g1-r7-base-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   net /private/tmp/g1-r7-s2-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

**All five exited 0, first try.** No compile failure at any point in this pass,
so the bucket-(a)/bucket-(b) triage is empty for this regeneration — there was
nothing to triage. (The buckets are not vacuous in general: stage 02's own pass
produced one bucket-(a) failure with a bucket-(b) payload. This pass simply
re-ran an already-correct transformer over inputs it already handled.)

### 3.1 The baseline is the in-tree build, and it is provably the iteration-40 reference

```
$ cmp /private/tmp/g1-r7-base-app/zephyr/zephyr.bin /private/tmp/g1-i40d-app/zephyr/zephyr.bin
(silent)
```

My freshly built in-tree app image is **byte-identical to `g1-i40d-app`**, the
build iteration 40 measured. So iteration 40's oracle captures are a valid
"current in-tree build" reference, and my own fresh base captures are directly
comparable to them.

Likewise `cmp /private/tmp/g1-r7-base-net/zephyr/zephyr.bin
/private/tmp/g1-i30e-net/zephyr/zephyr.bin` is **silent** — the net image is
unchanged since iteration 30, as claimed.

### 3.2 Gate ladder — every number from a command actually run

| gate | in-tree base | **Stage 01** | **Stage 02** |
|---|---|---|---|
| app build | exit 0 | exit 0 | **exit 0** |
| net build | exit 0 | — | **exit 0** |
| app FLASH | 955,048 B / 982,528 B = 97.20 % | 954,912 B = 97.19 % | **954,912 B = 97.19 % — Δ −136 B vs base** |
| app `.text` / `.data` / `.bss` | 950,080 / 4,951 / 249,251 | 949,956 / 4,951 / 249,251 | **949,956 / 4,951 / 249,251 — Δ −124 / 0 / 0** |
| app RAM | 253,765 B = 56.32 % | 253,765 B | **253,765 B — Δ 0 B** |
| app RAM layout (`nm -n`, every `0x2…` symbol) vs base | — | — | **0 diff lines** |
| `_end` | `0x2003ff45` | — | **`0x2003ff45` — unchanged** |
| `runtime_info_sync` | `0x00015bc8` | — | **`0x00015bc8` — unchanged** |
| **app `zephyr.bin` S1 vs S2** | — | — | **BYTE-IDENTICAL (`cmp` silent)** |
| **app ELF symbol table S1 vs S2 (`nm -n`, all)** | — | — | **0 diff lines** |
| app `app_update.bin` S1 vs S2 | — | — | differs in exactly **256 bytes** — the trailing MCUboot RSA-PSS signature |
| net FLASH / RAM | 225,581 B = 97.48 % / 63,380 B = 96.71 % | — | **225,581 B / 63,380 B — Δ 0 B, the frozen values** |
| **net `zephyr.bin` base vs S2** | — | — | **BYTE-IDENTICAL** |
| net ELF symbol table base vs S2 | — | — | **0 diff lines** |
| `nm -u` undefined | app 0 / net 0 | app 0 | **app 0 / net 0** |
| duplicate global definitions | 0 / 0 | — | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` in the link | 0 | — | **0** |
| compiler warnings | 1,887 app / 1,066 net | 1,887 | **1,887 / 1,066 — Δ 0** |
| compiler errors | 0 / 0 | 0 | **0 / 0** |
| `.rodata` read out of the linked ELF's PT_LOAD vs `app_update.bin` | **1,424 match / 14 mismatch** | — | **1,325 match / 14 mismatch — the SAME 14, name for name** |
| `check_ram_pin_collisions.py` app | — | — | **627 bound OK, 0 escaping, 0 raw-literal-in-a-live-object, 0 unknown-inside-a-live-object** |
| `check_ram_pin_collisions.py --core net` | — | — | **170 bound OK, 0 / 0 / 0** |
| `check_net_raw_literals.py` | — | — | **983 TUs, 0 failed to preprocess, 0 / 0 / 0 / 0 / 0** |
| `verify_net_stock_data_window.py` | — | — | **PROVEN** — 256/349 words equal, **93 differing words all flash pointers, 0 differing for any other reason**, 72 map input sections, **0 non-stock input sections** |
| `check_thread_create_stack_args.py --trials 120` | — | — | **10 / 10 PASS, EXIT 0** |
| `gen_retained_sources.py --check` | — | — | **"retained source lists are current"** |
| `driver.py check-addresses 0 1` / `1 2` | — | — | **identical, 2,567 addresses both sides, 0 gained, 0 lost** |
| `unittest discover -s recon/refactor` | — | — | **7 / 7 PASS** |

The **−136 B** whole-image delta is 12 B larger than Stage 01's previously
reported −124 B. `.text` moved by exactly −124 B in both; the extra 12 B is
image-layout padding, not code. The direction and the mechanism
(`g1_app_string_rodata.c` withdrawal minus `.rodata.str1.1` growth) are
unchanged.

### 3.3 Per-object comparison — nothing outside the transformed set moved

`--strip-debug --remove-section=.comment`, matched by basename with the
build-relative `CMakeFiles` suffix as tiebreaker:

| comparison | identical | differing | unmatched by path |
|---|---:|---:|---|
| **Stage 01 vs Stage 02** | **3,130** | **2** | 3 (`main.c.obj`, `sqrtf.c.obj`, `strtol.c.obj` — the multi-copy basename class) |
| **base vs Stage 02** | **3,086** | **46** | the same 3 |

The 2 differing in S1-vs-S2 are `open-amp/.../remoteproc_virtio.c.obj` and
`zephyr/lib/posix/uname.c.obj` — the two stock SDK units already recorded in
`prerefactor_progress.md` §0/§4 as differing build-to-build regardless of any
change. **Every one of Stage 02's 714 rewritten files produced a byte-identical
object.**

The 46 in base-vs-S2 decompose exactly:

* **43** are exactly the stage-01 rewritten translation units (the stage-01
  changed-file list is 46 entries = 43 rewrites + `g1_app_string_rodata.c` +
  `g1_app_globals.ld` + `g1_app_symbols.h`; `main.c.obj` falls into the
  unmatched multi-copy class, and `g1_app_string_rodata.c.obj` — the withdrawal
  — is one of the 43 counted here);
* **`isr_tables.c.obj`** — link-generated from the final ELF, so it necessarily
  moves when the image shifts by −124 B. Address relocation, not a semantic
  change;
* **`remoteproc_virtio.c.obj`, `uname.c.obj`** — the two stock churn units.

Nothing else in either build moved.

---

## 4. THE MAIN EVENT — the display/sensor oracle against the Stage 02 build

### 4.1 What was run, exactly

Seven Renode captures, all through the repository's own
`recon/emulator/scripts/capture_display_sensor_oracle.sh`, with the
iteration-40 recipe re-derived from the ELFs actually booted:

```sh
# probe addresses, RE-READ from each ELF (they happen to coincide, but the rule is to re-read):
#   base:     _end 0x2003ff45   runtime_info_sync 0x00015bc8
#   stage 02: _end 0x2003ff45   runtime_info_sync 0x00015bc8      <- unchanged
#   => device ctx 0x2003ff50;  +0xd5 = 0x20040025, +0xfe8 = 0x20040F38, +0x105a = 0x20040FAA
printf '$rtinfo_pc=0x00015bc8\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-r7/ours-paired.resc

F=$(mktemp -u); mkfifo $F; sleep 100000 > $F & W=$!         # the ConsoleIOSource workaround
G1_ATT_WRITE=""  \                                          # "" = dashboard; unset = navigation
G1_RESC=/private/tmp/g1-r7/ours-paired.resc \
G1_APP_ELF=/private/tmp/g1-r7-s2-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-r7-base-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_r7_s2_dash < $F
kill $W; rm -f $F
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_r7_s2_dash /private/tmp/g1-r7/rep-s2_dash
```

| capture | image | stimulus | outdir |
|---|---|---|---|
| `s2-dash` | stage 02 | dashboard (`G1_ATT_WRITE=""`) | `/private/tmp/g1_r7_s2_dash` |
| `s2-dash-r2` | stage 02 | dashboard | `…_dash_r2` — determinism double-run |
| `s2-nav` | stage 02 | navigation | `/private/tmp/g1_r7_s2_nav` |
| `s2-nav-r2` | stage 02 | navigation | `…_nav_r2` — determinism double-run |
| `base-dash` | in-tree | dashboard | `/private/tmp/g1_r7_base_dash` |
| `base-nav` | in-tree | navigation | `/private/tmp/g1_r7_base_nav` |
| `base-nav-r2` | in-tree | navigation | `…_nav_r2` — determinism double-run |

The net ELF is a non-variable: `base-net`, `s2-net` and `g1-i30e-net` are all
**byte-identical**, so exactly one net image was booted in all seven runs.

### 4.2 Determinism, verified before any conclusion was drawn

Stage 02 / dashboard, two full end-to-end runs diffed field by field:

**Bit-identical across the two runs:** both framebuffer sha256; `spim_a`
`p1_boot` AND `p2_render` stream hashes; `spim_b`; `twim1` merged bus AND every
per-device stream, both phases; `twim2` both phases; `pdm0` / `saadc` /
`gpiote0` / `gpiote1` whole-run; and every counter including
`SCREEN_ID_ctx_d5`, `DISPLAY_ON_ctx_fe8`, `ESB_SYNC_ctx_105a`,
`ESB_MASTER_FRAMES` (0x176), `ESB_ACKS`, `JBD_FRAMECOUNTER_P1/P2`,
`VC_DATA_EVENTS`, `VTIME_P1/P2`.

**The single exception is `RADIO_TX` (0x230 vs 0x234)** — already on the
oracle's documented "do not gate on these" list (§2.1 of
`display_sensor_parity.md`).

So every EQ/NE verdict below is about the image, not about run jitter.

### 4.3 DASHBOARD — result

**Every gated stream is `in-tree == stage 02`. Zero differences of any kind.**

| criterion | shipped | in-tree | **Stage 02** | verdict |
|---|---|---|---|---|
| **D-1** `framebuffer p2_render` | `19b1f24a09f97a8d…`, 2,923 lit px | same | **same — raw 153,600 B byte-identical to in-tree** | **PASS** |
| **D-2** `framebuffer p1_boot` | `0c5cc90b079d0d9c…`, 0 lit px | same | **same, byte-identical** | **PASS** |
| **D-3** `spim_a p1_boot` | 34 txns, sha | 34, EQ | **34, EQ** | **PASS** |
| **D-5** `SCREEN_ID_ctx_d5` | `0x06` | `0x06` | **`0x06`** | **PASS** |
| **D-6** `DISPLAY_ON_ctx_fe8` / `ESB_SYNC_ctx_105a` | `0x01` / `0x02` | same | **same** | **PASS** |
| **D-7** `spim_b` both phases | 0 txns | 0 | **0, EQ** | **PASS** |
| `twim1 p1_boot` whole bus | 346 | 346, EQ | **346, EQ** | PASS |
| `twim1 p1_boot` nPM1300 / OPT3001 / ST25DV 0x53 / 0x57 | 285 / 14 / 25 / 22 | all EQ | **all EQ** | PASS |
| `twim2 p1_boot` (LSM6DSO) | 1,075 | 1,075, EQ | **1,075, EQ** | PASS |
| `pdm0` / `gpiote0` / `gpiote1` whole-run | 2 / 25 / 0 | all EQ | **all EQ** | PASS |
| `saadc` whole-run | 998 accesses | 998, **sha NE** | **998, sha NE — identical to in-tree** | pre-existing (§40.13 item 2) |
| `twim1 p2_render` | 584 | 572, NE | **572, NE — identical to in-tree** | pre-existing (§40.13 item 3) |
| `twim2 p2_render` | 1,206 | 1,206, NE | **1,206, NE — and NE vs in-tree** | pre-existing (§40.13 item 4) + phase, see §4.5 |
| `spim_a p2_render` | 12,225 | 9,212, NE | **9,212, NE — identical to in-tree** | not a gate (§8.3: shipped `p2_render` is itself unstable) |

**Not one dashboard stream that the in-tree build matches is broken by the
refactor.** The four all-important acceptance framebuffers on this stimulus —
`19b1f24a…` 2,923 px and `0c5cc90b…` all-zero — are reproduced byte-for-byte.

### 4.4 NAVIGATION — result, and the one apparent regression, which is NOT one

The four navigation acceptance framebuffers are reproduced exactly by **both**
builds:

| criterion | shipped | in-tree | **Stage 02** | verdict |
|---|---|---|---|---|
| **G-1** `framebuffer p2_render` | `b26c73b37d441fc8…`, 1,098 lit px | same | **same — raw 153,600 B byte-identical to in-tree** | **PASS** |
| **G-2** `framebuffer p1_boot` | `1d617c65a688f10e…`, 656 lit px | same | **same, byte-identical** | **PASS** |
| **G-6** `spim_b` both phases | 0 txns | 0, EQ | **0, EQ** | **PASS** |
| **S-ESB** | `ESB_SYNC 0x02`, `DISPLAY_ON 0x01`, PTX > 0 | `0x02` / `0x01` / 0x176 | **`0x02` / `0x01` / 0x176** | **PASS** |
| `S-PMIC p1_boot` | 291 | 291, EQ | **291, EQ** | PASS |
| `S-NFC 0x53 / 0x57 p1_boot` | 25 / 22 | EQ / EQ | **EQ / EQ** | PASS |
| `S-ALS p1_boot` | 33 | 33, EQ | **33, EQ** | PASS |
| `S-MIC` / `S-KEYS` (`pdm0`, `gpiote0/1`) | 2 / 25 / 0 | EQ | **EQ** | PASS |
| `S-ADC` | 998 accesses | 998, sha NE | **998, sha NE — identical stream to in-tree** | pre-existing |
| **G-3** `spim_a p1_boot` / `p2_render` | 764 / 2,881 | 126 / 109, NE | **126 / 109, NE — stream byte-identical to in-tree** | pre-existing, §5 |
| `S-IMU p2_render` | 1,200 | 1,200, NE | **1,200, NE** | pre-existing (§40.13 item 4) |
| `twim1 p2_render` merged | 599 | 588, NE | **588, NE** | pre-existing; merged bus is excluded from the gate anyway |
| **`S-IMU p1_boot`** | 1,089 | 1,089, **EQ** | 1,089, **NE** | **looks like a regression — it is not; see below** |

On the first pass this read as *the* finding: the LSM6DSO boot stream matches the
shipped firmware byte-for-byte on the in-tree build and does not on the Stage 02
build, with identical transaction counts (1,089 == 1,089).

The payload-level diff is tiny and very specific. Stripping `seq=` and `tick=`,
the two 1,089-line traces differ by **8 lines out of 2,178**: exactly one
4-transaction accelerometer/gyro poll pair
(`W 28`,`R 000000000000`,`W 22`,`R 000000000000`) sits **before** a periodic
ODR-reconfiguration block in one and **after** it in the other. Nothing else —
no payload byte, no transaction, no count.

```
in-tree : … poll@3.8896s   RECONFIG@3.9446s   poll@3.9697s …
stage 02: … poll@3.8094s   RECONFIG@3.8943s   poll@3.8946s …
```

### 4.5 Falsifying it: the navigation `twim2` stream is not reproducible for EITHER build

Rather than explain the flip away, I measured it. Both images were captured a
**second** time under the navigation stimulus and each run was compared against
the shipped oracle:

| stream (navigation) | shipped | base run 1 | base run 2 | **S02 run 1** | **S02 run 2** |
|---|---:|---|---|---|---|
| `twim2 p1_boot` (LSM6DSO) | 1,089 | 1,089 **EQ** | 1,089 **NE** | 1,089 **NE** | 1,089 **EQ** |
| `twim1 p1_boot` merged bus | 371 | 371 **EQ** | **373 NE** | 371 **NE** | 371 **EQ** |
| `twim1 p1_boot` OPT3001 | 33 | 33 **EQ** | **35 NE** | 33 **EQ** | 33 **EQ** |
| `twim1 p1_boot` nPM1300 | 291 | 291 EQ | 291 EQ | 291 EQ | 291 EQ |
| `twim1 p1_boot` ST25DV 0x53 / 0x57 | 25 / 22 | EQ | EQ | EQ | EQ |
| `spim_a p1_boot` / `p2_render` | 764 / 2,881 | 126 / 109 NE | 126 / 109 NE | 126 / 109 NE | 126 / 109 NE |
| framebuffer `p1_boot` / `p2_render` | `1d617c65…` / `b26c73b3…` | MATCH | MATCH | MATCH | MATCH |

**Each image produces both outcomes across two runs of itself.** The in-tree
build matched the shipped LSM6DSO boot stream on run 1 and missed it on run 2;
the Stage 02 build missed it on run 1 and **matched it on run 2**. The same
image also produced 33 and then 35 OPT3001 boot transactions.

So the §4.4 flip is **run-to-run non-determinism of the navigation capture for
our rebuilt images**, not an effect of the refactor. Under the R7 bar there is
**no navigation regression**: every gated stream that the in-tree build can
match, the Stage 02 build also matches, and the ones neither matches are the
already-catalogued pre-existing gaps.

Three things make this the right reading rather than a convenient one:

1. **It is symmetric.** A refactor defect cannot make the *unmodified* in-tree
   image fail the same gate on its second run.
2. **The mechanism is visible in the trace.** Only the *position* of one poll
   pair relative to a periodic reconfiguration moved; every payload byte is
   identical, every count is identical. That is interleaving, not content.
3. **The instruction stream is provably unchanged.** Disassembling both linked
   ELFs end to end gives **179,900 vs 179,899 entries**, and the *only*
   difference in the whole mnemonic histogram is **one `.word`** — a literal-pool
   data word, not an instruction. Section sizes: `.text` 0x780f8 → 0x780f4
   (**−4 B**, that one word), `.rodata` 0x6f5cc → 0x6f554 (**−120 B**, the
   string merge). `.text` still starts at `0x0000c358`. There is no code path
   that Stage 02 executes differently; only the *addresses* of code after that
   literal pool move by 4 bytes, which is enough to shift Renode's
   translation-block boundaries and hence the virtual-time phase by tens of
   microseconds early in the run.

**Correction to the harness documentation, and to iteration 40.**
`display_sensor_parity.md` §2.1 lists `twim2` stream hashes and every `twim1`
per-device hash as *bit-identical across runs*. That was measured on the
**shipped** images and it does not transfer to ours: under the navigation
stimulus our builds' `twim2 p1_boot` and `twim1 p1_boot` OPT3001 streams are
bistable. Consequently `our_boot_bringup.md` **§40.13 item 5** — which recorded
a navigation `p1_boot` OPT3001 `33 → 35` and nPM1300 `EQ → NE` shift between
`g1-i40b` and `g1-i40d` and attributed it to "doing real NDEF work shifts the
sampling phase" — is at least partly **run jitter, not an image effect**: the
identical `g1-i40d` image reproduced both 33/EQ and 35/NE here. (Two runs per
image is a small sample; what it establishes is bistability, not a rate. The
nPM1300 boot stream stayed EQ in all four navigation runs.)

**Practical consequence for the gate:** navigation `twim2 p1_boot` and the
merged/OPT3001 `twim1 p1_boot` must be treated as *multi-run* criteria for our
rebuilt images — "matched in at least one of N deterministic runs" — or the
capture must be made reproducible first. A single-run EQ/NE on those streams is
not evidence about a code change in either direction. The framebuffers, the
`spim_a` streams, `saadc`, `pdm0`, `gpiote*`, nPM1300 and both ST25DV ports were
stable across every run and remain hard gates.

---

## 5. G-3 — ROOT CAUSE FOUND, proven from the shipped bytes

`G-3` (navigation `spim_a` 126 vs 764 and 109 vs 2,881, with byte-identical
framebuffers) was the last open screen-level gap. It is now closed as a
**diagnosis**: a single dropped `if (event == 0 && NAVIGATION_ACTIVE == 1)`
branch in `ui_navigation_task`, which in the shipped firmware advances an
**animated** bitmap at 15 Hz.

The stage-02 and in-tree builds emit **byte-identical** navigation `spim_a`
streams, so none of this is refactor-related; it is a pre-existing
reconstruction defect that this pass localised while the oracle was available.

### 5.1 The gap is one shape, not a diffuse deficit

Opcode histogram, navigation `p1_boot`, shipped vs ours:

```
0x01  2/2   0x06  4/4   0x31  4/4   0x36  2/2   0x46  4/4   0x66  2/2
0x71  2/2   0x73  2/2   0x99  2/2   0x9F  1/1   0xA3  4/4   0xA9  2/2
0xB9  1/1   0xC0 10/10          <- every panel command matches EXACTLY
0x02  673 / 64            0x97   49 / 20        <- the entire gap
```

Pixel-window shapes, `(x, pixel bytes) -> count`:

| shape | p1 shipped | p1 ours | p2 shipped | p2 ours |
|---|---:|---:|---:|---:|
| `x=0`, 61440 / 30720 (full-panel clear bands) | 6 / 3 | **6 / 3** | 2 / 1 | **2 / 1** |
| `x=178`, 213 B | 55 | **55** | — | — |
| `x=120`, 240 B | — | — | 82 | **82** |
| `x=32`, **10 B** (20 px) | — | — | 21 | **21** |
| **`x=32`, 9 B (18 px)** | **609** | **0** | **2,646** | **0** |

609 + 2,646 = **3,255** of the 3,410 missing transactions, and the remaining
29 + 126 = **155** are the `0x97` refresh that terminates each group. Our build
emits **zero** 9-pixel-byte windows and every pixel-content hash we do emit
already exists in the shipped stream (`ours-not-in-shipped = 0`, both phases).

### 5.2 It is one 18×21 px cell, repainted at exactly 15 Hz for exactly 10.43 s

Grouping the shipped stream (`0x02` runs terminated by `0x97`):

```
p1_boot  blits per refresh: 3,0×8,3,0×8,3,55, then 21,21,21,…  (29 times)
ours     blits per refresh: 3,0×8,3,0×8,3,55                    <- identical prefix, then nothing
p2_render blits per refresh: 21 ×126, then 3,21,82
ours                        :               3,21,82             <- identical tail only
```

Every one of the 155 groups is **21 blits at `x=32`, rows 265…285 inclusive,
9 pixel bytes each, then one `0x97`**. Measured from the shipped trace ticks:

```
155 groups, first 4.09145 s, last 14.52391 s, span 10.43246 s
inter-group interval: 66,620,000 ns exactly on 143 of 150 intervals
                      (4 × 66.61 ms, 1 × 66.63, 2 sub-ms outliers, 4 stalls 83–150 ms)
=> 15.01 Hz
```

Per-row content over the 126 `p2_render` frames shows an **animation, not a
static repaint**: row 285 is one constant value all 126 times; rows 283/284
carry `ff83adfb` 97 times and `3e7077fd` 29; rows 265/266 carry `3e7077fd` 90
and `20532bca` 36; rows 271/272 cycle **11 distinct** contents. The proportion
of the "filled" value rises monotonically from the top row to the bottom — the
signature of a cell whose content advances frame by frame.

Our build's only `x=32` group is **20 px wide (10 bytes), emitted once**, in the
final burst — a different, static draw.

### 5.3 Where the two streams part company, to the millisecond

```
SHIPPED p1: 764 txns, 0.1017 s … 5.9569 s   (animating continuously from 4.0915 s)
OURS    p1: 126 txns, 0.1081 s … 3.9384 s   (silent after the 2nd panel init)
SHIPPED p2: 2,881 txns, 6.0234 s … 14.5346 s (animation to 14.5240, then the final burst)
OURS    p2:   109 txns, 14.4337 s … 14.4407 s (the final burst ONLY, ~100 ms early)
```

Both builds draw the same final screen and the framebuffers are byte-identical.
The entire difference is the 10.43 s of animation in between — and 10.43 s is
**exactly** `ui_navigation_task`'s own countdown: `SYNC_RETRIES = 10`,
decremented once per `>1001 ms` in `sync_timeout`, then `exit_navigation`.

### 5.4 The defect, read off the shipped Thumb

`ui_navigation_task` = `FUN_0003f410`, extent **0x3f410 … 0x3fd44** (next
catalogued function `draw_template_translate_screen` @ `0x0003fd44`), 0x934 B.
Decoding every `BL` inside that extent:

| callee | shipped sites inside the extent | our reconstruction |
|---|---|---|
| `gui_reset_dynamic_bitmap_frame_state` @0x43308 | `0x3f50c` | 1 call ✓ |
| `gui_bmp_bitmap_draw` @0x43484 | `0x3f5d2` | 1 call ✓ |
| `gui_bitmps_merge_draw` @0x43bd8 | `0x3f938` | 1 call ✓ |
| **`gui_bmp_dynamic_bitmap_draw` @0x4334c** | **`0x3fc2e`** | **declared `extern`, called ZERO times** |

(The other `BL`s to these callees that a naive scan finds — `0x3ff5e`,
`0x3fde4`, `0x4023e`, `0x40344` — lie in `draw_template_translate_screen` /
`ui_translate_task` and are correctly excluded by the extent.)

The missing block, disassembled from `app_update.bin`:

```
3fbee:  cmp    r5, #0             ; r5 = event
3fbf0:  bne.w  0x3f4b4            ;   -> not the periodic tick
3fbf4:  ldrb   r3, [r4, #6]       ; r4+6 = g_20004bbe = NAVIGATION_ACTIVE
3fbf6:  cmp    r3, #1
3fbf8:  bne.w  0x3f57c
3fbfc:  ldr    r3, [r7, #0]       ; g_log_level
3fbfe:  cmp    r3, #2
3fc00:  ble.n  0x3fc14
3fc02..3fc10:                     ; the routed log call
3fc14:  bl     0x7d3ee            ; device_info_text_width_get   -> r5
3fc1a:  bl     0x7d446            ; device_info_text_height_get_clamped -> r0
3fc1e:  movs   r3, #0
3fc20:  add.w  r2, r0, #0x3a
3fc24:  mov    r1, r5
3fc26:  movs   r0, #8             ; <-- bitmap id 8
3fc28:  strd   r3, r3, [sp, #4]
3fc2c:  str    r3, [sp, #0]
3fc2e:  bl     0x4334c            ; gui_bmp_dynamic_bitmap_draw(8, w, h+0x3a, 0,0,0)
3fc32:  bl     0x167a8            ; get_device_info  (fall-through, reconstructed)
```

i.e. **`case 0` (NAVIGATION INIT / waiting) is missing its `event == 0` arm:**

```c
if (event == 0u && NAVIGATION_ACTIVE == 1u) {
    if (LOG_LEVEL > 2) LOG_CALL(…);
    int w = device_info_text_width_get();
    int h = device_info_text_height_get_clamped();
    gui_bmp_dynamic_bitmap_draw(8, w, h + 0x3a, 0, 0, 0);   /* ANIMATED */
}
```

The reconstruction's `case 0` has **no `event == 0` arm at all**; it falls
straight through to the `master_enabled` test and returns.

Three corroborations that this is the right block and not a coincidence:

1. **The argument shape is the animated twin of a call we did reconstruct.**
   Our `exit_navigation:` correctly emits
   `gui_bmp_bitmap_draw(0x3f, w, h + 0x3a, 0, 0)` — the *static* renderer,
   bitmap **0x3f**, at site `0x3f5d2`. The missing call is the *dynamic*
   renderer, bitmap **8**, with the identical `(w, h + 0x3a, 0, 0, …)` layout.
2. **`gui_reset_dynamic_bitmap_frame_state()` is already in our `case 0`**, at
   `0x3f50c`, immediately before `draw_locale_adjusted_label()` — the firmware
   *resets the animation frame counter* on entering the waiting state, and then
   never advances it in our build. A reset with no advance is exactly a
   one-frame animation.
3. **The window matches the state machine.** The animation runs from the moment
   `NAVIGATION_ACTIVE` becomes 1 (4.0915 s) to `exit_navigation` (14.5240 s) —
   10.43 s = the `SYNC_RETRIES = 10` × `>1001 ms` countdown, which our build
   also executes (its final burst lands at 14.4337 s).

### 5.5 What this predicts, and what it does not

Restoring the branch should turn `spim_a` navigation `p1_boot` 126 → 764 and
`p2_render` 109 → 2,881, and should turn both `stream_sha256` into candidates
for G-3 PASS. It should **not** change any framebuffer — the final frame is
already byte-identical, which is why the defect survived every pixel gate.

**I did not apply the fix.** `recon/symbolized/app/ui_navigation_task.c`,
`recon/named/`, `recon/app/src/FUN_0003f410.c` and `recon/verified/src/` are the
canonical trees, owned by the concurrent parity agent and R1-protected from this
pipeline. The fix also needs the `gui_bmp_dynamic_bitmap_draw` prototype (6 args
including three stack words) read off its own prologue, and a `cfg_verify` run,
which is that agent's workflow. Everything needed is above: the extent, the
exact `BL` site, the register set-up, the guard conditions and the two globals.

**Related counts NOT closed** (both pre-existing, both identical between the
in-tree and Stage 02 builds, so neither is refactor-related):
`saadc` whole-run stream sha (998 == 998 accesses, different register stream);
dashboard `twim1 p2_render` 572 vs 584 with nPM1300 513 vs 514; `twim2
p2_render` on both stimuli. I did not investigate them — the oracle time went to
G-3, which was the named target.

---

## 6. What I did NOT close, and why

1. **The `saadc` register-stream sha** (998 == 998 accesses, stream differs).
   Pre-existing since iteration 40; identical between the in-tree and Stage 02
   builds. Not investigated — out of scope for an R7 refactor gate, and the
   oracle budget went to G-3.
2. **Dashboard `twim1 p2_render` 572 vs 584 / nPM1300 513 vs 514**, and
   **`twim2 p2_render`** on both stimuli. Same status: pre-existing, identical
   in both builds.
3. **The G-3 fix itself.** Diagnosed to a single `BL` site (§5.4); not applied,
   because the file lives in an R1-protected canonical tree owned by the
   concurrent parity agent.
4. **Stage 99** (`defect_probe`) was left stale. It is a diagnostic tree that is
   *expected* not to compile; regenerating it would have cost a build and proved
   nothing about R7.
5. **`cfg_verify` / the `reverify` sweep** were not run. Under C7 they are
   diagnostics, and neither stage changes a canonical body, so no canonical
   function owes a re-proof. `check_thread_create_stack_args` — which *does*
   drive the parity harness over canonical bodies — was run: 10/10.
6. **The navigation capture was not made deterministic.** §4.5 shows it is not,
   for our images. Making it so (or making the harness gate on N runs) is the
   single highest-value follow-up for the emulator side, because until then a
   navigation `twim2`/`twim1` `p1_boot` EQ/NE reading cannot be used as evidence
   about any change — this pass, iteration 40's §40.13 item 5, and any future
   iteration alike.
7. **I did not commit anything**, and did not touch any canonical tree, `tools/`,
   `armemul`, any build file, any linker script, or `recon/board/**`.

## 7. Footprint — everything this pass changed

```
 M recon/refactor/stage_00_snapshot/{MANIFEST,PARITY_MAP}.json      regenerated
 M recon/refactor/stage_01_literal_inline/{MANIFEST,PARITY_MAP}.json regenerated
 M recon/refactor/stage_02_block_dedupe/{MANIFEST,PARITY_MAP}.json   regenerated
 M recon/refactor/README.md                                          + the R7 GATE RECORD section
?? recon/analysis/staged_refactor_r7_validation.md                   this file
```

`QUARANTINE.json` and `DEFECTS.json` of both stages are **unmodified** — the
regeneration reproduced them byte for byte. `stage_*/tree/` is `.gitignore`d.
Build outputs and captures live under `/private/tmp/g1-r7*` and
`/private/tmp/g1_r7_*`, outside the repository.

Re-checked at the end of the pass. `git status` at that moment shows ~1,800
modified files under `recon/{app,verified,symbolized,named,readable_sources}` —
**none of them are mine.** They are the concurrent parity agent's batch that
landed at 04:19:48 (see the correction in §0); the write guard makes it
structurally impossible for this pipeline to have written any of them, and every
measurement above predates them. From this pass the *only* changed paths are the
six regenerated stage JSONs, `recon/refactor/README.md`, and this file.

`~/Projects/armemul` still carries exactly what it carried at the start — the
two uncommitted `TraceFile` hooks in `models/NRF5340_{SPIM,TWIM}.cs` and the two
untracked `g1-ours*.resc` files. Nothing there was written.

**Stage staleness at the end of the pass:** stage 00 `stale`, 75 inputs moved
(2,544 unchanged); stages 01 and 02 `current` against their recorded
predecessors, i.e. the trees that were built and captured are internally
consistent snapshots. Repair before the next measurement:
`materialize 0 && materialize 1 && materialize 2`, then re-run §3 and §4.
