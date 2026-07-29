# Net core (CPUNET) on the modtest golden-vector harness

**Status:** written incrementally during the pass, 2026-07-28. Every number
below comes from a command run in this pass unless it is explicitly flagged as
inherited. Nothing is committed; §7 lists exactly what changed on disk.

**Scope discipline.** This pass owns the NET core only. `tools/modtest/**` was
NOT edited (a concurrent agent owns it); the one net-blocking harness defect
found is written out as an exact patch in §1.2 for that owner to apply. No net
source tree was restructured.

---

## Summary

```
HARNESS ON NET          works, after ONE blocking one-line defect (§1.2, patch given)
SYMBOLS COVERED         233 vectors, 5,527 fixtures, oracled by netcore_image.bin
                        sha256 ec4e4b60...7ca4 (225,632 B)
INSTRUCTION COVERAGE    8,721 / 14,598 shipped CFG instructions = 59.7 %
                        median per symbol 0.96 ; 113 at 100 % ; 0 vacuous
MUTATION KILL RATE      256 / 369 = 69 %  (37 usable symbols of 53 graded)
                        per-symbol median 71 %
NEGATIVE CONTROLS       8 killed, 0 survived, 13 not applicable
TREE AGREEMENT          233 / 233 agree, 0 disagreements
                        79 / 79 agree on the stage-02-CHANGED subset -- the only
                        part of net where the two trees differ at all
FAILING SYMBOLS         46, identically on BOTH trees, so none is a refactor
                        regression.  Includes FUN_01013650, which AGENTS.md
                        already lists as a known net false proof -- re-found here
                        from the shipped image with no prior knowledge.

RECOVERED vs STOCK      923 retained (ours) / 232 stock, NOT "232 recovered" (§0.2)
MODULARIZATION          RECOMMEND: not yet.  Name the 604 unnamed retained
                        functions first, then cut by SUBSYSTEM (49.4 % intra-module
                        call edges) rather than by link order (25.5 %).  §5.6

Neither the >= 70 % coverage bar nor the >= 70 % kill-rate bar of
test_architecture.md §8.2 is met (59.7 % and 69 %).  Reported as failures of the
gate, not rounded up.
```

---

## 0. Three inherited claims this pass had to correct

Each of these was in the brief this pass started from, and each is wrong.
The commands that establish the correction are given.

### 0.1 "952 of 1,155 net files are real transformed files; stages 01 and 02 DID run on net"

**Wrong. Stage 01 did not touch net at all, and stage 02 touched 134 files.**

```
$ prev=recon/refactor/stage_00_snapshot/tree/recon/symbolized/net
$ for s in 01_literal_inline 02_block_dedupe 03_module_structure 04_cohesive_tu \
           05_cohesive_composition 06_unit_composition 07_internal_linkage \
           08_call_order 09_call_cohesion; do
      cur=recon/refactor/stage_$s/tree/recon/symbolized/net
      echo "stage_$s: $(diff -rq $prev $cur | wc -l)"; prev=$cur; done

stage_01_literal_inline:      0
stage_02_block_dedupe:      134
stage_03_module_structure:    0
stage_04_cohesive_tu:         0
stage_05_cohesive_composition:0
stage_06_unit_composition:    0
stage_07_internal_linkage:    0
stage_08_call_order:          0
stage_09_call_cohesion:       0
```

So **1,021 of the 1,155 net files are byte-identical from stage 00 to stage 09**,
and the entire net delta across the whole ten-stage ladder is 134 files produced
by one stage. `recon/symbolized/net` (the live tree) is byte-identical to the
stage-00 snapshot (`diff -rq` → 0).

That stage 01 skipped net is corroborated in the harness itself:
`tools/parity/emu.py` line ~288 — *"Net literal inlining is deferred anyway, so
net keeps exact address comparison"* — and in `recon/refactor/driver.py`, whose
descriptions for stages 3–7 and 9 all say **"app core only … The net core is
frozen and is not touched."**

The "952" could not be reproduced under any comparison tried here. For the
record, the adjacent counts that do exist: 1,155 net sources all carry a
`readable reconstruction` banner (0 without), and **600** carry a `parity`
note.

### 0.2 "matched sources: 232 — so only ~232 of net is recovered sources"

**Backwards.** `tools/gen_retained_sources.py::build` computes
`matched = excluded.intersection(source_index)`. The "matched sources" figure in
the header of `recon/generated/net_retained_sources.cmake` is the number of
**manifest EXCLUSIONS that matched a source file** — i.e. the count of net
sources the build *drops* in favour of a byte-exact upstream archive member.

Re-derived from `recon/ownership/adoption_manifest.json` in this pass:

```
manifest net rows                                   677
  rows with exclude_reconstruction: true            312
symbolized/net source files                       1,155
  excluded  (stock, adopted upstream byte-exact)     232
  retained  (COMPILED FROM OUR RECONSTRUCTION)       923
exclusion rows with no matching source file           80
source files with no manifest row at all             676
```

So the number of net sources that are ours to reason about is **923, not 232**.

### 0.3 "net has ESB / radio / crypto / controller subsystems to modularise"

Partly. There is **no ESB function** in the net tree — no symbol carries an
`esb` name. ESB appears only as *data*: 49 of the 1,155 files reference an
`esb`-named global (`g_net_esb_own_addr`, `g_esb_sync_response_packet`, …).
An ESB module boundary therefore has to be recovered from data affinity, not
from names. See §5.

---

## 1. Does the harness work on net? (deliverable 1)

### 1.1 What is genuinely core-parametric — verified, not assumed

Checked by reading the code and then by running it:

* `core.core_ctx("net")` reads `netcore_image.bin` via `net_extract` and takes
  sizes/entries from `net_funcs.json` — both analysis-space (0x01008000);
* `emu.NET_CODE_BASE` (0x01000000) is mapped as a 0x40000 flash window, which
  contains the analysis window;
* `core.PIN_FRAGMENTS` already filters `g1_app_*` out when `core == "net"` and
  keeps `g1_net_globals.ld`;
* `cli._ret_kind` dispatches to `net_recon_kit._ret_kind`;
* `emu._firmware_readonly_extent` already knows the CPUNET dual address space
  and resolves stored flash pointers through `net_extract.read_runtime`
  (**runtime** base 0x01008800), while function identity stays analysis-space.
  It also *disables* read-only content equivalence for net
  (`RODATA_EQUIVALENCE_CORES = ("app",)`) precisely because the two windows
  overlap numerically — a deliberate fail-closed choice, and the right one.

**The dual address space did not break vector generation.** Every VA that
crosses this harness is an analysis address; the runtime space is touched only
inside `emu`, by code that already carries the distinction. This driver performs
no conversion at all, which is the only way to be certain it cannot get one
wrong.

First net symbol ever run through the harness:

```
$ tools/modtest/cli.py gen net ocrypto_constant_time_equal --budget 200
GEN  ocrypto_constant_time_equal  va=0x01008810 size=38 cases=2 cov=12/12 (100%) globals=0
$ tools/modtest/cli.py run net ocrypto_constant_time_equal
ocrypto_constant_time_equal  canonical=OK(2/2)  refactored=ABSENT  cov=100%
```

### 1.2 ★ ONE NET-BLOCKING HARNESS DEFECT — patch required, NOT applied here

`refactored=ABSENT` above is the defect. `index.default_trees` builds the
stage-09 tree with `modules_only=True`:

```
$ PYTHONSAFEPATH=1 .venv/bin/python tools/modtest/index.py net
canonical    units= 1155 symbols= 1155 merged_units=   0 dup_symbols=0
refactored   units=    0 symbols=    0 merged_units=   0 dup_symbols=0
```

`modules_only=True` is correct for app, where stage 03 created module
directories. The **net half of every stage tree is flat** — 1,155 top-level
`.c` files at stage 00 and still 1,155 at stage 09, zero module directories — so
the filter discards the entire tree and every net symbol reports `ABSENT`.
That is silent: `cmd_run` prints `ABSENT` and moves on, so a net sweep would
report "no disagreements" while never having replayed a single refactored file.

**Required patch** (`tools/modtest/index.py`, in `default_trees`). Not applied
in this pass because a concurrent agent owns that file:

```python
 def default_trees(core="app"):
+    # The net half of every stage tree is FLAT: stage 03 created module
+    # directories for app only, so `modules_only=True` indexes ZERO net units
+    # and every net symbol silently reports ABSENT.  Measured 2026-07-28:
+    # net stage 09 has 1,155 top-level .c files and 0 module directories.
+    refactored_modules_only = (core != "net")
     return {
         "canonical": build(
             os.path.join(REPO, "recon/refactor/stage_00_snapshot/tree"),
             core=core, name="canonical(stage00)", modules_only=False),
         "refactored": build(
             os.path.join(REPO, "recon/refactor/stage_09_call_cohesion/tree"),
-            core=core, name="refactored(stage09)", modules_only=True),
+            core=core, name="refactored(stage09)",
+            modules_only=refactored_modules_only),
     }
```

Until that lands, `recon/tests/net_modtest.py` (new, this pass) supplies the
same two trees indexed flat, plus a net subsystem bucketing so vectors are filed
under something more useful than `unsorted`. It calls `cli.cmd_gen` /
`cmd_run` / `cmd_grade` unchanged, so results are produced by the same code path
the app pilot used.

```
$ PYTHONSAFEPATH=1 .venv/bin/python recon/tests/net_modtest.py index
canonical(stage_00_snapshot)   units= 1155 symbols= 1155
refactored(stage_09_call_cohesion) units= 1155 symbols= 1155
```

---

## 2. Recovered vs stock, by evidence (deliverable 2)

Derived in this pass from `recon/ownership/adoption_manifest.json`
(`recon/tests/net_modtest.py census`), not inherited.

```
net symbols indexed                                  1,155
STOCK   (manifest exclude_reconstruction: true)        232
RETAINED(compiled from our reconstruction)             923
```

**Stock — 232 files, not ours to restructure**, by manifest component:

```
zephyr_os_kernel_stock                61     openamp_rpmsg                 4
zephyr_kernel_private_stock           57     zephyr_nrf_rtc_timer          3
nrf_subsys                            49     zephyr_bluetooth_host_stock   2
net_sdk_or_glue                       32     mpsl                          2
hal_nordic_nrfx                        8     (9 further components)        1 each
net_sdk_public                         6
```

**Retained — 923 files**, by manifest component:

```
<no manifest row>                    676
softdevice_controller                167
net_sdk_or_glue                       79
zephyr_ipc_rpmsg_variant               1
```

Two things about that table matter and are easy to miss:

1. **`softdevice_controller` is RETAINED, not excluded.** 167 SDC sources are
   compiled from our reconstruction rather than adopted upstream, because the
   shipped SDC archive is obfuscated and its per-VA identity is not unique —
   `gen_retained_sources._report_only_sdc` actively *refuses* an SDC exclusion
   that rests on that evidence. So the largest single recovered block in net is
   Nordic's closed BLE controller, recovered by us because it cannot be dropped
   in from a package.
2. **676 retained files have no manifest row at all** — no exclusion decision
   was ever recorded for them, and `recon/ownership/net_function_ownership.json`
   (452 entries, all `sdk_library`) covers **zero** of them. They are the
   genuinely un-adjudicated remainder.

Subsystem buckets this pass assigned (name evidence first, then manifest
component):

```
unsorted    604      thunk        14
stock       232      radio         4
sdc         132      ipc           2
controller  104      mpsl          2
glue         59      crypto        2
```

Only **176 of the 923 retained symbols carry a recovered human name**
(`controller_*` 104, `sdc_*` 45, `thunk_*` 14, `radio_*` 4, and one each of a
few others). The other 747 are still `FUN_0100xxxx`.

Size distribution of the 923 retained (from `net_funcs.json`):
**median 40 B, mean 118 B, p90 272 B, max 5,332 B**, and 31 have no catalogued
size at all (those cannot be vectored — `cli.cmd_gen` skips them by design).

The same split measured in BYTES rather than files, which is the fairer way to
read "how much of net is ours":

```
catalogued net functions                1,252   147,725 B
  with a symbolized source              1,155   130,903 B  = 58.0 % of the 225,632 B image
    retained                              923   109,639 B  = 83.8 % of that
    stock                                 232    21,264 B
```
Net functions are much smaller than app's, which matters for §5.

---

## 3. What was vectored, and the honesty caveat on "tree agreement"

### 3.1 The symbol set

298 symbols selected in this pass, plus a second batch of 90 (§3.2):

* **all 176 retained symbols that carry a recovered human name** (`controller_*`,
  `sdc_*`, `radio_*`, `schedule_*`, `rtc_*`, `mpsl_*`, `ocrypto_*`, `ipc_*`,
  `thunk_*`) — these are the recovered subset the brief asks to prioritise;
* plus a **size-stratified sample of 132 `FUN_*` retained symbols**, 22 from
  each of six size bands (0–32, 32–64, 64–128, 128–256, 256–512, 512+ bytes),
  so the suite is not accidentally a suite of tiny leaves.

The oracle is the shipped image, confirmed rather than assumed: every vector
file carries `oracle.image_sha256 =
ec4e4b60f3efa5c830084c9dd3ca516f70cfeb81620306e2ebd8a2af158f7ca4`, and

```
$ shasum -a 256 netcore_image.bin
ec4e4b60f3efa5c830084c9dd3ca516f70cfeb81620306e2ebd8a2af158f7ca4  netcore_image.bin  (225,632 B)
```

**What actually landed after the harness-version incident of §6.4:** 233
vectors, covering **69 of the 176 named** retained symbols and **79 of the 132
stage-02-changed** retained symbols. 81 further vectors were generated but
deleted because their harness version could not be pinned.

### 3.2 ★ Why a naive "the trees agree" result on net would be near-vacuous

Because only stage 02 touched net (§0.1), **the stage-00 and stage-09 source
files are byte-identical for 1,021 of 1,155 net symbols.** For those symbols,
`canonical == refactored` is not a measurement — it is `diff` returning 0, run
through an emulator.

```
$ diff -rq stage_00.../symbolized/net stage_09.../symbolized/net | wc -l
134           # 133 retained + 1 stock
```

Of the first 298-symbol batch, only **42** are among those 134. A second batch
was therefore generated covering the **90** remaining stage-02-changed retained
symbols that have a catalogued size, so that the agreement claim is made on as
much of the real delta as possible rather than on a tautology.

**Any agreement figure in §4 is reported twice: over all symbols, and over the
stage-02-changed subset, which is the only part where disagreement is
possible at all.**

---

## 4. Results — coverage, agreement, kill rate

All numbers below come from the **233 vectors that survived the harness-version
pin** (§6.4). 81 further vectors were generated during the pass but by a
harness version this pass could not pin, and were **deleted rather than
reported** — a vector whose expectation came from an unknown code version is
worse than no vector.

### 4.1 ★ Measured instruction coverage of the SHIPPED net bytes

```
symbols                                233
fixtures                             5,527
aggregate CFG-instruction coverage   8,721 / 14,598 = 59.7 %
median per-symbol coverage                            0.96
symbols at 100 %                                       113
symbols below 50 %                                      34
symbols with ZERO fixtures (vacuous)                     0
```

Per subsystem bucket:

```
bucket        symbols  covered/total     pct   median  at 100%
controller        52    1,324 / 2,121   62.4 %   1.00     28
sdc               25      895 / 1,273   70.3 %   0.98     11
glue              13      433 /   665   65.1 %   0.81      4
radio              1       27 /    28   96.4 %   0.96      0
thunk              2        2 /     2  100.0 %   1.00      2
ipc                1       17 /   146   11.6 %   0.12      0
unsorted         139    6,023 / 10,363  58.1 %   0.94     68
```

Restricted to the **69 symbols carrying a recovered human name**, coverage is
**58.2 %**; restricted to the **79 stage-02-changed** symbols — the only ones
where the two trees can differ at all — it is **52.6 %**.

The shape matches the app pilot's: a median at or near 100 % with the mean
dragged down by a minority of long, call-heavy or loop-bound bodies. The
fifteen worst, with their reasons visible in the fixture count:

```
FUN_0102411c                     6/227    3 %   676 B, 1 fixture survived
FUN_010187e0                    22/365    6 % 1,048 B, 41 fixtures
FUN_01021b7c                     8/130    6 %   364 B, 1 fixture
FUN_0101f994                    13/200    6 %   528 B, 7 fixtures
FUN_0101ad38                    13/114   11 %   280 B, 1 fixture
ipc_rpmsg_static_vrings_open    17/146   12 %   408 B (catalogued 18 B -- §6.5)
FUN_01022a84                    39/310   13 %   944 B, 1 fixture
FUN_0101c6d0                   124/802   15 % 3,380 B, 6 fixtures
sdc_llcp_handle_control_opcode  58/302   19 %   996 B, 5 fixtures
```

Fixture-search accounting over the whole set:

```
candidates evaluated              32,700
kept as fixtures                   5,527
dropped: instruction cap             453
dropped: extent dispute                0
harness errors                         0
unresolved indirect branches          27, over 18 symbols
```

**Aggregate coverage is 59.7 %, which does NOT meet the ≥ 70 % bar of
test_architecture.md §8.2.** It is comparable to the app pilot's `sensors`
(55.5 %) and below its `ipc` (75.5 %). The named reasons are the same ones §1
of that document lists, plus one that is worse on net: 15 % of retained net
functions have no caller at all (§5.0), so a large part of this core is
ISR/callback-entered and is only reachable synthetically.

### 4.2 ★ Tree agreement — all 233 symbols, on both trees

```
symbols replayed on BOTH stage-00 and stage-09 net trees   233
  canonical and refactored produce the SAME verdict        233
  DISAGREEMENTS                                              0

  both trees OK                                            187
  both trees FAIL (same fixture count, same first event)    46
  CCFAIL / ABSENT                                            0
```

And the figure that is not a tautology:

```
stage-02-CHANGED symbols (the only ones whose source differs
between the two trees)                                      79
  agree                                                     79
  disagree                                                   0
```

For the other **154**, the stage-00 and stage-09 source files are **byte
identical** (`filecmp.cmp(..., shallow=False)` over the whole net half: 1,021
identical, 134 differing), so their agreement is definitional rather than
measured. Both numbers are reported because reporting only the 233 would be
generous to the point of being misleading.

**Conclusion: on the covered fraction, the ladder's stage 00 → stage 09
changed no observable net behaviour** — and on net that ladder is a single
transform (stage 02, block dedupe) touching 134 files, of which this pass
constrains 79.

No CCFAILs occurred on net: unlike the app core (§18.4 of
test_architecture.md), no net TU needed the build's generated `autoconf.h`.

### 4.3 Symbols that FAIL — identically on both trees, so not refactor regressions

46 of 233. Because each reproduces on the canonical tree, none is a stage-02
regression; each is a property of the reconstruction, of the fixture, or of the
harness. **None is root-caused here** (§8).

```
bucket        FAILs        changed / unchanged
unsorted        34              20 / 26
controller       8
sdc              2
glue             2
```

One of them is worth naming, because it is the closest thing to an independent
validation of the oracle available:

> **`FUN_01013650` — FAIL 5/52 at 100 % coverage.** AGENTS.md lists this
> function by name as a known CFG-sweep false proof (*"Known fails incl.
> `FUN_01013650`, `FUN_0101ba58`, `FUN_0101a38c` (net)"*). This harness
> re-found it from the shipped image with no prior knowledge, exactly as the
> app pilot independently re-found `battery_model_state_update`. The other two
> named net fails were not in this pass's symbol sample.

The rest, with the caveat that a large share look like the `nptr` fixture-quality
class of §6.2 and §18.5 (golden faults on a garbage pointer, candidate does
not):

```
FUN_01008a28  0/41 cov=100%   FUN_010195f8  0/42 cov= 91%   FUN_01010834  0/42 cov=100%
FUN_0101b7e4  0/46 cov=100%   FUN_01012438  0/43 cov= 23%   FUN_010196e0  0/42 cov= 31%
FUN_010212ec  0/43 cov= 51%   FUN_0100aff4  0/41 cov= 28%   FUN_01013650  5/52 cov=100%
controller_timing_state_reset       41/42 cov=100%
controller_procedure_generation_advance 2/8 cov=100%
controller_handle_slot_find          1/9 cov= 91%
controller_radio_request_configure   1/44 cov= 80%
controller_timing_request_submit     1/30 cov= 59%
controller_timing_snapshot_build     1/13 cov= 21%
controller_packet_duration_lookup    0/42 cov= 29%
controller_packet_payload_length_set 2/3  cov= 53%
FUN_01026acc (sdc) 2/4 cov=97%   FUN_01027302 (sdc) 1/5 cov=91%
FUN_01027974 (glue) 4/41 cov=100%   FUN_0102ff94 (glue) 42/43 cov=81%
… and 24 further `unsorted` symbols, all listed in the run logs
```

### 4.4 ★ Mutation kill rate — the anti-vacuity measurement

53 net symbols graded, 16 mutants each, against the **refactored** tree; every
mutant compiled from an in-memory override, nothing written to any tree.

```
symbols graded                                     53
  baseline FAIL -- excluded from the rate           9   (a mutant of a
                                                        already-failing body
                                                        proves nothing)
  zero valid mutants -- rate n/a (see §6.3)          7   (all 4-6 byte bodies)
  usable                                            37

killed     256
survived   113
invalid     34   (did not compile; not counted either way)
--------------------------------
** KILL RATE  256 / 369 = 69 % **
per-symbol median 71 % ; >= 70 %: 19 of 37 ; < 50 %: 6
```

69 % is just under the ≥ 70 % bar of test_architecture.md §8.2, and above the
app pilot's 64 %. The distribution is the honest picture:

```
14 %  FUN_01019ef8          (7 mutants; 73 % coverage)
33 %  FUN_0102fa4c          at 100 % coverage -- constants the trace cannot see
38 %  FUN_0102a278          at 100 % coverage
40 %  controller_indexed_status_byte_get
42 %  FUN_0100d688          survivors are four large hex constants
...
100 % controller_procedure_slot_reserve (14/14), controller_status_defaults_reset (9/9),
      FUN_0100d14c (16/16), FUN_0100ebf4 (16/16), FUN_01012970, sdc_buffer_payload_get, ...
```

The survivors cluster on **constant perturbation inside a value the event trace
never observes** — the same shape as the app pilot's stack-record blind spot
(§16.1 of test_architecture.md), which is disabled in the pinned harness.

### 4.5 Negative controls — the suite is SHOWN to fail

`recon/tests/test_modtest_net.py --shard 0/14 --probe 10` (new this pass):

```
POSITIVE: 17 symbols, trees agree on 17, disagree on 0, absent-from-one 0
COVERAGE: 1,033 / 1,747 shipped CFG instructions = 59.1 %
NEGATIVE CONTROLS on 7 symbols:  8 killed, 0 SURVIVED, 13 not applicable
  killed  FUN_0100d14c                             drop-call, flip-comparison
  killed  FUN_010108b8                             drop-call, flip-comparison
  killed  FUN_01026acc                             drop-call
  killed  FUN_0103494c                             flip-comparison
  killed  controller_buffer_is_zero                return-constant, flip-comparison
  n/a     FUN_0100a954, controller_procedure_generation_advance  (all three)
```

**Zero survivors.** `n/a` is printed rather than skipped: 13 of 21
(symbol, control) pairs had no applicable site — `FUN_0100a954` is a 6-byte body
with no return expression, no call and no comparison, which is the same
population as the zero-mutant symbols of §6.3. A control that never applied is
not a control, and this file says so on its own output.

---

## 5. Is net modularization worth doing? — measured, then recommended

### 5.0 One more limit that shapes the answer: 15 % of net has no caller

134 of the 923 retained functions (**15 %**) have **no direct caller anywhere in
the shipped image** — they are ISR handlers, callback-table entries,
init-section entries and indirect-only targets. 75 of them have callees, i.e.
they are real entry points into a chain. `recon/analysis/test_architecture.md`
§1 limit 1 applies to every one of them: *"Interrupts do not exist … no NVIC,
no exception entry, no context switch."* The named ones are the ones you would
most want covered:

```
controller_radio_event1_dispatch      controller_radio_idle_state_finish
controller_radio_transition_apply     controller_handle_update_state_apply
sdc_conn_event_process                sdc_event_publish
sdc_ext_adv_event_complete            sdc_llcp_process_rx_control_pdu
ipc_rpmsg_static_vrings_open          g1_ipc_rpmsg_register_ept
```

They can still be vectored — the harness calls them directly — but their
production entry conditions are not modelled, so their fixtures are synthetic
in a way an application function's are not.

### 5.1 The structure that exists today

923 retained net sources, **one function per file, zero module directories**,
at every stage of the ladder. `recon/refactor/driver.py` says so explicitly for
stages 3, 4, 5, 6, 7 and 9 — *"app core only … The net core is frozen and is
not touched."*

Call graph recovered in this pass by disassembling the **shipped image** (not
our sources) and following direct `bl`/`blx` into catalogued entries:

```
catalogued net functions                 1,252   (147,725 B)
  with a symbolized source                1,155  (130,903 B = 58.0 % of the image)
    retained (ours)                         923  (109,639 B = 83.8 % of that)
    stock    (adopted upstream)             232  ( 21,264 B)

call edges between source-backed functions        2,262
  both ends retained                              1,529
  crossing retained <-> stock                       412  (18.2 %)
```

### 5.2 Natural module boundaries — by call cohesion, there are none

Undirected connected components of the call graph, over the 923 retained
functions only:

```
components   152
sizes        661, 26, 23, 16, 9, 7, 5, 4, 4, 4, 4, 3, ...
singletons   126
```

**One component holds 661 of 923 functions (72 %).** Its bucket mix is
`unsorted 388 / sdc 126 / controller 89 / glue 46 / thunk 6 / radio 4 / mpsl 2`
— it is not a subsystem, it is the whole controller. There is no call-cohesion
seam to cut along. 98 retained functions have no call edge to or from any
source-backed function at all, and 371 more are pure leaves.

Data affinity is no better. Grouping by shared named global (hub globals
touched by >40 functions excluded, or everything joins everything):

```
components 680, of which 630 are singletons; largest 27, then 19, 16, 15, 15, 14
```

The largest data clusters are real and recognisable —
`g_net_ble_conn_create_ctx` + `g_net_pending_work_list` (27 functions),
`g_net_radio_addr_match_tbl` (19), `g_net_radio_drv_ctx` + `g_ll_conn_*` (15),
and a 14-function cluster around `g_esb_sync_response_packet` /
`g_net_ipc_msg_type` — but they cover a small minority of the tree.

### 5.3 How good would a net partition be? — measured against app's own modules

The right yard-stick is not "is it perfect" but "is it better than the
modularization that already shipped on the app core". Metric: the fraction of
call edges that stay *inside* a module.

```
partition                                     edges   intra-partition
APP, stage-09's 15 shipped modules            8,981       24.4 %
  excluding `unsorted`                        8,735       24.9 %
  excluding `unsorted` and `lib`              6,283       24.4 %

NET, manifest component                       1,529       62.9 %   <-- inflated
  excluding the `<no manifest row>` catch-all   135       41.5 %
NET, subsystem name bucket                    1,529       51.8 %   <-- inflated
  excluding the `unsorted` catch-all            255       49.4 %
NET, link-order 16-way slice                  1,529       25.5 %
```

The two "inflated" rows have to be read with their correction. 906 of net's
1,529 retained edges (59.3 %) are *inside the `<no manifest row>` catch-all* —
so the 62.9 % headline is mostly one giant bucket calling itself, which is the
same degenerate-measurement shape this project has been burned by before. The
honest figures are **41.5 %** and **49.4 %**.

Even so: **49.4 % is twice the 24.4 % that app's shipped modules achieve**, and
that app figure is robust to removing both of its catch-alls. So a
subsystem-named net partition would be a *better* cut than the app precedent —
but only over the part of the tree it can name.

### 5.4 The blocker is naming, not moving

```
retained sources                               923
  carrying a recovered human name              176   (controller 104, sdc 45,
                                                      thunk 14, radio 4, …)
  still FUN_0100xxxx                           747
```

The 49.4 % figure above is computed over the 255 edges whose **both** endpoints
are named. The other 604 retained functions have no name, no manifest row, and
no entry in `recon/ownership/net_function_ownership.json`; every one of them
would land in `unsorted`. `recon/analysis/test_architecture.md` §3 already
describes what that produces on the app core: *"`unsorted` is a module in name
only: 50 TUs and 167 functions with no shared responsibility."* On net it would
be 604.

**Moving 604 unnamed files into a directory called `unsorted` is a rename, not
a modularization.** The prerequisite for a net module cut is naming, and naming
needs the same evidence pipeline that produced the 176 names that exist.

### 5.5 What it would cost

* **Mechanically it is feasible.** In address order the 1,155 net sources form
  106 same-ownership runs — **53 contiguous retained runs, median 3 functions,
  longest 511**. A stage-03-style link-order move would work on the long run.
  The hard constraint is that manifest exclusions are per-VA and map 1:1 to a
  file, so **a merged TU may never mix a retained function with a stock one**;
  the 53-run structure is what makes that satisfiable.
* **Build-authority churn.** `recon/generated/net_retained_sources.cmake` names
  every source by path, so any move or merge regenerates it.
  `recon/refactor/input_set.py` already owns that file (`build_machinery`
  category, added in stage 03), so the machinery exists.
* **Size.** The three size-changing app stages moved `.text` by **−76 B**
  (stage 04 cohesive TU), **−192 B** (stage 07 internal linkage) and **+8 B**
  (stage 09 call cohesion) — from each stage's own `SIZE_GATE.json`. Those are
  **app-core measurements** (`base_elf` is the app `zephyr.elf`) and are not
  net evidence, but they are the only precedent for what this transform family
  costs, and the direction was *negative* for both merge stages. Net's real
  device headroom is **~1,747 B** (usable region 227,328 B; the build inherited
  from the brief is 225,581 B — **inherited, not re-measured in this pass**;
  note `recon/application/net/FLASH_DIVERGENCE.md` still records an older
  227,961 B build that overflowed, so that document is stale).
* **Test cost.** §4's coverage is what licenses a restructuring. Extending the
  vector set from ~390 symbols to the full 892 vectorable retained symbols is
  roughly 3× the generation time reported in §6.

### 5.6 ★ RECOMMENDATION

**Do not modularize net now. Do two smaller things first, in this order.**

1. **Name the 604 unnamed retained functions, or as many as the evidence
   supports.** This is the actual blocker (§5.4) and it is also what makes the
   remaining 747 `FUN_*` sources reviewable at all. Nothing about module
   boundaries can be decided before it, because 65 % of the tree has no
   evidence attached to it today.
2. **Then cut modules by the SUBSYSTEM partition, not by link order.**
   Measured: subsystem 49.4 % vs link-order 25.5 % intra-module edges. Stage
   03's link-order move is the *wrong* transform for net; it would score at
   app's level (24–25 %) when a 2× better cut is available. Expect roughly
   8–12 modules: `sdc`, `controller`, `radio`, `schedule`, `rtc`, `ipc`,
   `mpsl`, `crypto`, `glue`, plus whatever naming turns the 604 into.

**A correction that this recommendation depends on.** `recon/analysis/
staged_refactor_stage03.md` §4.1 justifies excluding net with *"it is ~100 %
stock — `recon/ownership/net_function_ownership.json` records 452/452
`sdk_library` and zero product-owned net functions"*. That file's own
`summary.apparent_missing_entries` is **451**: it is an audit of functions that
appeared *missing from the corpus*, not a census of net. Measured overlap with
the source tree:

```
net_function_ownership.json entries                     452
  that have a symbolized source file                    285
    of which stock (manifest-excluded)                   50
    of which retained                                   235
  with no source file at all                            167
retained sources it says NOTHING about                  688  (923 - 235)
```

So "452/452 sdk_library" is true of that audit's scope and says nothing about
**688 of the 923 retained net sources**. The exclusion of net from the ladder
rests on a generalisation the evidence does not carry. That does not by itself
make modularization right — §5.2–§5.4 are the reasons it is still premature —
but the stated reason for the exclusion should be corrected.

The other stated reason in §4.1 — the flash budget — is real but weak under the
new goal, and the app precedent (§5.5) puts the expected cost at under 200
bytes against ~1,747 B of headroom.

---

## 6. Harness findings specific to net (beyond the blocking one in §1.2)

These are reported, with exact patches where a patch is short, for the owner of
`tools/modtest/**`. **None was applied in this pass.**

### 6.1 ★ A zero-case vector reports `OK(0/0)` — a green result on nothing

`generate.select` correctly drops a fixture whose golden run hit the
instruction cap (`search.dropped_instruction_cap`; test_architecture.md §11
defect 7). When **every** candidate is dropped the vector file is written with
`cases: []` and `coverage.ratio: 0.0`, and `cli._replay` then iterates an empty
list, finds no failures and returns `ok=True`. `cmd_run` prints:

```
ocrypto_constant_time_is_zero   canonical=OK(0/0)  refactored=OK(0/0)  cov=0%
```

That is a **PASS on a symbol that was never executed**. §13L of
test_architecture.md predicted the visibility of this ("only if someone reads
the number"); on net it is not hypothetical.

```
measured: 6 of the first 260 net vectors have cases == 0, all six because
          100 % of candidates hit the instruction cap
```

Suggested patch (`tools/modtest/cli.py`, in `_replay`), so the suite cannot be
green on an empty fixture set:

```python
     failures = []
     covered = set()
+    if not record["cases"]:
+        # A vector set with no surviving fixture proves nothing.  Returning
+        # ok=True here prints OK(0/0), which is a PASS on a symbol that was
+        # never executed.  Measured on net: 6 of 260 vectors, all from
+        # search.dropped_instruction_cap == candidates.
+        return False, {"stage": "vacuous", "failures": [], "n_failures": 0,
+                       "cases": 0, "candidate_insns": 0}
     for case in record["cases"]:
```

### 6.2 `nptr = 2` is wrong in BOTH directions, and net shows the other one

test_architecture.md §18.5 records that `nptr = 2` is too LOW for a function
with three or more pointer parameters. Net exhibits the converse and it is
worse, because it destroys the fixture set entirely rather than biasing it.

`ocrypto_constant_time_is_zero(unsigned char *p, int n)` has two parameters;
`nptr = 2` makes **`n` a pointer value** — a large address — and its
`do { n--; } while (n != 0)` loop then runs ~2³¹ iterations and hits the
200,000-instruction cap on all 113 candidates. Its three-argument sibling
`ocrypto_constant_time_equal(p1, p2, n)` gets `n` as a seeded integer under the
same `nptr = 2` and reaches **12/12 = 100 % coverage with 2 fixtures**. Same
code shape, opposite outcome, decided entirely by where the arity boundary
falls.

Cheap fix, and it needs no new machinery: sweep `nptr` and keep the best result.
A `--nptr 1` regeneration of the six affected symbols was started but did not
finish inside this pass (§8), so the *fix* is measured only on the one symbol
pair above; the *defect* is measured on all six (6 of 260 vectors at the time,
100 % of candidates capped).

### 6.3 The mutation engine produces ZERO mutants for a one-line body

`mutate.generate` has five mutant classes; four need a constant, an operator or
a relational, and the fifth (`del:`) needs a line that *ends in `;`* and does
not start a definition. A large number of net sources are a single-statement
accessor written on one line:

```c
void FUN_010093ac(uint32_t value){*(volatile uint32_t*)((unsigned long)&g_21000b78) /*=0x21000b78*/=value;}
```

That file has no live constant (the only hex is inside a `/*= */` comment, and
`_inert_mask` correctly excludes it), no operator, and the single line ends in
`}` — so **`generate` returns 0 mutants** and `cmd_grade` prints
`kill_rate=n/a`. Measured over the symbols vectored in this pass:

```
symbols with vectors             226
  zero mutants                    20   (9 %) -- every one is <= 6 bytes of code
mutant-count histogram            0:20  1:10  2:6  3:3  4:6  5:9  6:2  7:4
                                  8:7  9:7  10:7  11:1  12:8  13:5  14:3  15:1  16:127
net sources whose non-comment body is <= 2 lines:  117 / 1155
```

`n/a` is honest and is not a false green, but 9 % of the suite has no
anti-vacuity evidence at all. A sixth mutant class — replace the right-hand
side of a single assignment with `0`, which is exactly what the
`return-constant` negative control does — would cover it.

### 6.4 ★ CONCURRENCY HAZARD — the harness changed under a running sweep

Recorded because it invalidated measurements mid-pass and would have produced
findings that are pure artefact.

`tools/modtest/**` is owned by a concurrent agent. It was clean at HEAD
(commit `f3dc81b9`) when this pass's first generation batch started at 21:59.
It was then edited **four times while that batch was still running**:

```
core.py      22:04:16      +191 lines
cli.py       22:07:17       +30
mutate.py    22:12:39       +35
generate.py  22:21:35      +215
```

The decisive one: `core.STACK_ARG_WINDOW` was flipped **0 → 48**, i.e. the
stack-record capture that test_architecture.md §16.1 disabled was re-enabled.
That changes what `observable_key` contains. A vector generated before the
edit and replayed after it compares two different things, and every such
symbol would have failed **identically on both trees** — the exact signature
this project reads as a harness defect, except here it would have been a
version skew.

```
vectors written after 22:04:16 : 168 of 314
```

**Handled, not worked around.** `recon/tests/net_modtest.py` now resolves the
harness through `MODTEST_DIR` and this pass pinned it to a snapshot of HEAD
(`git show HEAD:tools/modtest/*.py`), verified:

```
core file: .../.modtest_pin/modtest/core.py    STACK_ARG_WINDOW = 0
VECTOR_DIR = <repo>/recon/tests/vectors
```

All 168 post-edit vectors were **regenerated under the pin**, so the whole
vector set comes from one harness version — the one
`recon/analysis/test_architecture.md` §18 documents.

The snapshot could not simply live in the scratchpad: `core.py` does
`sys.path.insert(0, dirname(dirname(__file__)))` to reach `extract`,
`net_extract` and `parity.emu`, which put the scratchpad on `sys.path`, where a
stray `dis.py` shadows the stdlib module and breaks `capstone` — the same class
of failure as the `struct.py` shadow AGENTS.md warns about. The pin therefore
lives at `<repo>/.modtest_pin/` (symlinks to `tools/*` plus the snapshot), so
`REPO` still resolves to the repository and vectors are still written to
`recon/tests/vectors`. **It is a temporary artefact of this pass and is
deleted at the end** (§8).

### 6.5 The net Ghidra catalog under-reports sizes far more than app's

`core.true_extent` extended the catalogued size on **62 of 314** vectored net
symbols. The largest extensions are big enough to deserve review on their own:

```
FUN_0102f080                    320 ->  908   (+588)
ipc_rpmsg_static_vrings_open     18 ->  408   (+390)   <-- 22x
FUN_0101c6d0                   3040 -> 3380   (+340)
FUN_01010ff0                    110 ->  402   (+292)
FUN_0101b230                    570 ->  796   (+226)
```

`true_extent` only ever extends and never crosses the next catalogued entry, so
these are bounded and fail-safe. But an 18-byte catalogued function whose own
CFG reaches 408 bytes is either a catalog defect or a shared tail block, and
`ipc_rpmsg_static_vrings_open` is exactly the symbol that then measures 17/146
= 12 % coverage. Not investigated in this pass.

### 6.6 What did NOT break on net, checked rather than assumed

* **The dual address space.** No conversion is performed anywhere in the net
  path; analysis addresses go in and `emu` resolves stored runtime pointers
  itself. Read-only content equivalence is *disabled* for net by
  `emu.RODATA_EQUIVALENCE_CORES`, so net compares pointer addresses exactly —
  stricter, not looser.
* **Linker pins.** All **460** net pins from `g1_net_globals.ld` resolve.
  431 are rewritten by `linker_pins`'s transitive-closure loop, because their
  right-hand side names a `g1_net_ram_blk_*` object defined in
  `recon/application/net/src/g1_net_ram_relocs.c`, which the harness does not
  link; the fallback rebinds them to the address comment in
  `g1_net_symbols.h`, which is the original absolute address — correct for
  emulation, where the golden side runs at original addresses.
  **Checked for a value change: 0 numeric pins changed value.** (The
  closure loop's `re.findall(r'[A-Za-z_$][\w$]*', expression)` does extract
  `x1011869` from `0x01011869`; on this data it is harmless — the resulting
  rewrite is leading-zero stripping only — but it is a latent text-anchoring
  trap of the family this project keeps finding.)

---

---

## 7. Files changed (nothing committed)

New, untracked, all written by this pass:

```
recon/tests/net_modtest.py            net driver: flat-indexed stage trees,
                                      subsystem bucketing, harness version pin
recon/tests/test_modtest_net.py       net positive/agreement/negative-control suite
recon/tests/vectors/net/**/*.json     golden vectors (see §4 for the count)
recon/analysis/net_test_coverage.md   this file
```

Modified: **none.** No source in any tree was edited. `tools/modtest/**` was
not touched by this pass — the two patches it needs are written out in §1.2 and
§6.1 for its owner. `recon/symbolized/net`, `recon/net/src`, the refactor
stage trees, `recon/symbols/*` and every ownership manifest are unchanged.

Temporary, and **removed at the end of the pass**: `<repo>/.modtest_pin/`
(symlinks to `tools/*` plus a `git show HEAD` snapshot of `tools/modtest`),
which existed only to pin the harness version against concurrent edits (§6.4).
To reproduce any number in this file, recreate it and export
`G1_MODTEST_DIR=<repo>/.modtest_pin/modtest`:

```bash
rm -rf .modtest_pin && mkdir -p .modtest_pin
for f in tools/*; do ln -s "$PWD/$f" ".modtest_pin/$(basename $f)"; done
rm -f .modtest_pin/modtest && mkdir -p .modtest_pin/modtest
for f in __init__ index core generate mutate cli; do
    git show f3dc81b9:tools/modtest/$f.py > .modtest_pin/modtest/$f.py; done
```

It must live under the repo root, not in the scratchpad: `core.py` puts its own
parent directory on `sys.path` to reach `extract` / `net_extract` /
`parity.emu`, and it derives `REPO` (hence `VECTOR_DIR`) from the grandparent.

**One measured determinism check**, because a version pin is worthless if
generation is not reproducible: `controller_byte_popcount`, generated by a
pre-edit process, regenerates **byte-identical** under the pin.

Everything else `git status` shows is the **concurrent app-core agent**, not
this pass. For the record, so the two are not confused:

```
NOT MINE:  tools/modtest/{cli,core,generate,mutate}.py       (modified)
           recon/analysis/test_architecture.md               (modified)
           recon/tests/test_modtest_pilot.py                 (modified)
           recon/tests/vectors/app/**                        (modified + new)
```

At the start of the session `git status` showed
`recon/refactor/transforms/t04_cohesive_tu.py` and `t09_call_cohesion.py`
modified; during the session they became clean and the modtest files became
modified instead.

One thing worth flagging to that agent: **it is writing its own working files
into this session's scratchpad** (`grade_analytics.json`, `grade_before_ipc.json`,
`grade_before_sensors.json`, `grade_ui.json`, `grade_common.json`,
`grade_before_lib.json` all appeared in
`/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/4d7b7032-…/scratchpad`).
That is how `g1_paths` resolves "the newest session directory", and it means a
naive `glob("grade*.json")` in either agent's aggregation picks up the other's
results. It did here, once, and was caught because app symbol names
(`lsm6dso_init_chip`, `i2c_read_reg16_be`) appeared in a net kill-rate table.
Every number in §4.4 is computed from an explicit file list, not a glob.

---

## 8. What this pass did NOT do, and why

* **Did not edit `tools/modtest/**`.** Owned by a concurrent agent. The one
  net-BLOCKING defect (§1.2) and one soundness defect (§6.1) are written out as
  exact patches instead. The workaround driver produces identical results
  because it calls `cli.cmd_gen` / `cmd_run` / `cmd_grade` unchanged.
* **Did not restructure any net source tree.** Explicitly out of scope for this
  pass; §5 is a recommendation with numbers, not an execution.
* **Did not vector all 923 retained symbols.** 388 were selected (§3.1) and
  **233 landed**; 81 were deleted for harness-version inconsistency (§6.4) and
  the rest did not finish generating. Generation is the expensive step and the
  machine was shared with the app-core fleet — 20 Python processes on 10 cores
  for most of the pass. Concretely still un-vectored: 107 of the 176 named
  retained symbols and 53 of the 132 stage-02-changed ones.
* **Did not finish the `--nptr 1` regeneration** of the six instruction-capped
  symbols (§6.2). The defect is measured; the fix is demonstrated on one
  symbol pair (`ocrypto_constant_time_is_zero` vs `..._equal`), not on all six.
* **Did not root-cause the 46 identical-on-both-trees failures** (§4.3),
  including `FUN_01013650`, which AGENTS.md already knows about.
* **Did not run the negative controls on more than 7 symbols.** The suite
  (`test_modtest_net.py`) replays every record before it reaches the controls,
  and under the shared machine that bounded the probe.
* **Did not vector the 232 stock symbols.** By design: they are adopted
  byte-exact from upstream archives and are not ours to restructure, so
  constraining them buys nothing.
* **Did not investigate the 62 `true_extent` extensions** (§6.5), including the
  22× extension of `ipc_rpmsg_static_vrings_open`.
* **Did not root-cause any per-symbol failure** in §4.4. Each is reported with
  its fixture and first divergent event; chasing them is separate work, and
  §8.4a of test_architecture.md is explicit that a fleet agent must never edit
  a source to make a test pass.
* **Did not build the net image.** Nothing in this pass changes a net source,
  so a build would verify nothing about it. The flash figures in §5.5 are
  therefore **inherited and flagged as such**, and
  `recon/application/net/FLASH_DIVERGENCE.md` is noted as stale (it records a
  227,961 B build; the brief and `staged_refactor_stage03.md` §4.1 both say
  225,581 B).
* **Did not run Renode.** Prohibited for this pass, and irrelevant: the whole
  point of this harness is that it is not the 30 µs-sensitive gate.
* **Did not cite `cfg_verify`.** It is blind in both directions on this code
  (AGENTS.md). The harness uses two of its helper functions and nothing else.
* **Did not commit.** The tree is left dirty; §7 lists exactly what changed.

---
---

# PASS 2 — 2026-07-29

**Everything from here down is a second pass.** Sections 0–8 above are the
first pass and are left verbatim; where this pass contradicts one of its
numbers or claims, it says so by section number. Nothing is committed.

Scope discipline is unchanged: this pass owns the NET core, does **not** edit
`tools/modtest/**`, and writes any needed harness patch into this document.

```
VECTORS                 376 (was 233), ALL stamped harness 936cee0b67396ca5,
                        8,415 fixtures, oracled by netcore_image.bin
                        sha256 ec4e4b60...7ca4 (225,632 B)
TASK 2 -- COMPLETE      166 / 166 vectorable NAMED symbols   (was  69)
                        132 / 132 stage-02-CHANGED symbols   (was  79)
COVERAGE                12,436 / 21,148 shipped CFG instructions = 58.8 %
                        (below the >= 70 % bar; reported as a gate failure)
TREE AGREEMENT          376 / 376 agree, 0 disagreements
                        132 / 132 agree on the ONLY part of net the ladder
                        touches -- so the stage 00 -> 09 claim now rests on
                        net's whole delta, not on 59 % of it
FAILURES                86 (76 FAIL + 10 VACUOUS), all identical on BOTH trees
TASK 1 -- ROOT CAUSES   57 of 86 attributed to four mechanisms, each shown by
                        experiment: an oracle that never writes a callee's
                        OUT-PARAMETER (§12.1), a derived pointer mask that
                        misses PASS-THROUGH pointers on 47 of 370 vectors
                        (§12.2), the `for(;;) panic()` idiom against a
                        returning oracle (§12.3), and an ordered READ trace
                        that over-constrains C evaluation order (§12.4).
                        27 remain without an established cause.
DEFECT FOUND + REPAIRED controller_duration_to_units: `sdiv` modelled as
                        unsigned division.  10/43 golden fixtures failed
                        before, 0 after.  Applied to the canonical trees.
KILL RATE (new vectors) 530 / 908 = 58 % over 88 usable symbols, median 71 %
TASK 3 -- NAMING        490 of 892 retained functions given a subsystem with
                        recorded evidence; 24 mechanically nameable.  The
                        measurement OVERTURNS §5.6: at equal module count a
                        link-order cut scores 30.2 % against the evidence-based
                        subsystem cut's 28.1 %, and the HYBRID beats both at
                        34.6 %.  §5.3's "49.4 %" compared partitions of
                        different granularity.
```

## 9. The harness changed under this pass too — what that forced

### 9.1 ★ The brief's expectation was wrong: NOT ONE inherited vector is stale

The brief for this pass said the harness now stamps vectors at `gen` and
`run` refuses a mismatched one, so *"expect some [inherited vectors] to be
rejected as stale"*. Measured over all 233 inherited net vectors:

```
$ PYTHONSAFEPATH=1 .venv/bin/python -c "
import json,glob,collections
c=collections.Counter()
for f in glob.glob('recon/tests/vectors/net/**/*.json',recursive=True):
    c[json.dumps(json.load(open(f)).get('harness'),sort_keys=True)]+=1
print(c)"
Counter({'null': 233})
```

**All 233 are UNSTAMPED**, and `core.vector_staleness` returns `None` — i.e.
*replay permitted, no complaint* — for exactly that case:

```python
    stamped = harness.get("rev")
    if stamped is None:
        return None
```

So zero would have been rejected. They would have been **silently replayed**
against a harness that has since changed in four ways that each redefine the
stored expectation:

```
STACK_ARG_WINDOW      0  ->  48     (stack-record capture re-enabled)
DERIVED_ARITY        --  ->  True   (callee arity derived from the callee's bytes)
ORACLE_PRESERVE      --  ->  True   (r0/r1 preserved across a call the callee never writes)
literal_pad          64  ->  derived (golden body mapped to cover its literal pool)
```

That is the same failure mode §6.4 documented, one layer down: the stamp
closes the *changed-stamp* hole and leaves the *no-stamp* hole open, and every
vector this project has on disk today for the net core is in the second
category. The docstring of `vector_staleness` says *"`cli.cmd_run` reports the
count so the gap is visible"* — **it does not**; `grep -n "unstamped" tools/modtest/cli.py`
returns nothing.

**Suggested patch, for the owner of `tools/modtest/**` — NOT applied here.**
Two lines in `cli.cmd_run`, so the gap is at least counted where the docstring
already claims it is:

```python
 def cmd_run(args, trees):
     rows = []
+    unstamped = 0
     for symbol in args.symbols:
         ...
         except FileNotFoundError:
             print("SKIP %-40s no vectors (run `gen` first)" % symbol)
             continue
+        if not (record.get("harness") or {}).get("rev"):
+            unstamped += 1
         ...
+    if unstamped:
+        print("NOTE %d of %d vectors are UNSTAMPED: they were frozen by an "
+              "unknown harness version and are replayed on trust "
+              "(core.vector_staleness permits them)." % (unstamped, len(rows)))
```

This pass did not rely on the mechanism either way: it **regenerated all 233**
rather than reinterpreting them, which is what the brief asked for.

### 9.2 ★ `tools/modtest/**` was edited twice more, mid-sweep, again

Recorded because it cost this pass a full generation run.

```
tools/modtest/core.py   modified 05:38  (sweep started 05:34)
tools/modtest/core.py   modified 05:44
tools/modtest/cli.py    modified 05:44
```

A running `gen` process has already imported the harness, so its *behaviour* is
frozen at import time — but `core.harness_rev()` is computed lazily from the
files **on disk**, so the stamp a long-running process writes is whichever
content it happened to hash first. The two are only guaranteed to agree if
nobody edits the files. They were edited.

**Handled the same way §6.4 did, because there is no other correct option.**
The 214 vectors produced by the first sweep were discarded, a snapshot of the
harness was taken at `.modtest_pin/`, and everything below was generated *and*
replayed under it:

```
$ shasum -a 256 .modtest_pin/modtest/core.py
c0a8f84e5817f1f529ff32b6aee2877a0da20a6314b734b2c661810b7b5790b3
$ ... harness_rev()                936cee0b67396ca5
    STACK_ARG_WINDOW = 48   DERIVED_ARITY = True   ORACLE_PRESERVE = True
```

`recon/tests/net_modtest.py` already resolves the harness through
`G1_MODTEST_DIR`; this pass changed its stale comment (the pin is no longer a
substitute for the stamp, it is a defence against the *unstamped* hole plus
concurrent edits) and changed its `--nptr` default from `2` to `-1`, the
derived pointer-argument mask that landed in `generate.pointer_arg_mask` after
the previous pass. That is the §6.2 fix, adopted rather than re-implemented.

**The pin means the vectors this pass leaves on disk are stamped
`936cee0b67396ca5`.** When `tools/modtest` settles, they will read
`STALE-VECTOR` against it and must be regenerated — which is the mechanism
working, not a defect.

---

## 10. Naming and subsystem attribution — the §5.4/§5.6 blocker, measured

The previous pass's recommendation was: *name the 604 unnamed retained
functions first, then cut modules by SUBSYSTEM (49.4 % intra-module edges)
rather than by link order (25.5 %)*. This pass built the evidence pipeline for
that, ran it, and **the recommendation does not survive its own metric.**

### 10.1 The evidence available, counted

Derived from the shipped image plus catalogs derived from it
(`netcore_image.bin`, `recon/catalogs/refgraph_net.json.gz`,
`recon/symbols/g1_net_symbols.h`, and the nRF5340 **network-core** register map
parsed out of `~/ncs251/modules/hal/nordic/nrfx/mdk/nrf5340_network.h` — 25
peripheral bases, 912 named registers; `RADIO->PACKETPTR` resolves to
0x41008504, which is the check that the parse is right).

```
retained net functions with a catalogued size          892
  already carrying a recovered human name              166
  UNNAMED                                              726

unnamed functions that reference ...
  a NET peripheral register block (MMIO)                66
  a descriptive named global                           286   (41 more reference
                                                              only address-derived
                                                              names like g_21000b78,
                                                              which carry no information)
  a string constant                                     47
  a named direct caller or callee                      308
  NOTHING of the above                                 254
```

Corrections to §2/§5.4 while here: the retained-and-named count is **166 with a
catalogued size**, not 176 (10 named symbols have no catalogued size and cannot
be vectored or sized), and the unnamed retained population is **747** of which
**726** have a size — not 604. 604 was the count of the `unsorted` *bucket*,
which is a different thing.

### 10.2 ★ The MMIO evidence is sound — checked, not assumed

`constants()` walks a function's declared extent linearly, so a literal pool
inside the body decodes as junk instructions and could manufacture a peripheral
hit. Every hit was therefore cross-checked against an **independent
derivation**: the reconstructed source for the same function (written from
Ghidra's decompilation), which must name an address on the same 4 KB peripheral
page or the `G1_NRF_<PERIPH>_NS_BASE` macro.

```
A1 MMIO hits checked against the reconstructed source   102
  witnessed                                             102   (100 %)
  no witness                                              0
```

Two rounds of that check were themselves wrong before this one was right — the
first looked only for the bare base address (`0x4100c000`) and reported 32
false positives; the second added the macro spelling and still reported 8,
because `FUN_010251ec` spells its TIMER0 register as `0x4100c140`, the CC[0]
address, not the base. Page-granular matching finds all 102. **The two failed
checks were the check's defect, not the evidence's** — which is the same trap
as anchoring a pattern at end of line, and is recorded here because it nearly
produced a "the MMIO evidence is 69 % junk" claim.

### 10.3 ★ A hold-out test says the RECOVERED NAMES are the unreliable part

The attribution rules are only worth something if they reproduce the subsystem
of functions whose subsystem is already known. So each of the 148 named
functions with a name-implied subsystem was held out in turn and re-derived
from the others:

```
A1  MMIO                    0 / 4    correct
A2  global-name prefix      5 / 12
A2b global co-occurrence    4 / 5
A3  unanimous neighbours   40 / 67
no prediction possible         60
```

A1 scoring 0/4 looked like a refutation. It is not: all four disagreements are
cases where the **name** is wrong, not the rule.

```
sdc_ecb_run_blocking          touches ECB    -- the name says ECB too; the
                                                "gold" label sdc is the error
sdc_llcp_stop_rx_timeout      touches RADIO  -- 22 bytes, and its whole body is
                                                RADIO->INTENCLR &= ~0x40 plus a
                                                store to RADIO+0x560.  It is a
                                                radio interrupt-disable, not LLCP.
sdc_llcp_note_unsupported_pdu touches RADIO
sdc_llcp_release_rx_context   touches AAR
```

`sdc_llcp_stop_rx_timeout`, disassembled from the shipped bytes:

```
010208b0  ldr    r3, [pc, #0x14]     ; 0x41008000  = RADIO
010208b4  ldr.w  r2, [r3, #0x200]    ; RADIO->INTENCLR region
010208b8  bic    r2, r2, #0x40
010208bc  str.w  r2, [r3, #0x200]
010208c0  str.w  r1, [r3, #0x560]
```

So the hold-out measures the **labels**, not the rules, and the label source is
the existing `function_names_net.json`. That matters well beyond this section:
**§5.3's "subsystem 49.4 %" figure is computed over those same labels.**

### 10.4 ★ The measured comparison — and §5.6's recommendation is overturned

Attribution assigned, by evidence class, over the 892 retained-with-size:

```
A0  name-implied (accepted as given)          148
A1  MMIO, witnessed                            56
A2  descriptive global name prefix             80
A2b global ownership learned from A0/A1/A2     32
A3  every attributed neighbour agrees         174
    ambiguous (evidence names >1 subsystem)     10
    STILL UNATTRIBUTED                         384
```

Intra-module call-edge fraction, over the 1,597 call edges between
source-backed retained net functions. **Two denominators, because the
difference is where 49.4 % came from:** `covered` counts only edges the
partition places both ends of; `all` is what a real module cut must live with,
because an unplaced function still lands somewhere.

```
partition                                    all-edges      covered-edges
names only                                    64/1597   4.0 %   64/120   53.3 %
A0+A1+A2+A2b                                 168/1597  10.5 %  168/413   40.7 %
A0+A1+A2+A2b+A3                              449/1597  28.1 %  449/706   63.6 %
RANDOM control, same class sizes             158/1597   9.9 %  158/706   22.4 %

link-order slice, 10 modules                 483/1597  30.2 %   (places everything)
link-order slice, 16 modules                 418/1597  26.2 %
HYBRID: attribution, link-order for the rest 552/1597  34.6 %
```

Three things follow, and the first two contradict §5.6.

1. **Intra-module fraction is dominated by module SIZE.** The same link-order
   cut scores 44.2 % at 5 modules, 30.2 % at 10, 24.0 % at 20 and 13.7 % at 60.
   Comparing a partition at one granularity against a partition at another —
   which is what "subsystem 49.4 % vs link-order 25.5 %" does — measures
   granularity. At **equal module count** the evidence-based subsystem cut
   (28.1 %) is *slightly worse* than the address-order cut (30.2 %).
2. **Link order is therefore NOT the wrong transform for net.** It is the right
   *fallback*: address order is the original translation-unit and archive-member
   order, which is why it captures 30 % of call edges with no semantic input at
   all.
3. **The attribution is still real signal, and it is worth having.** Against a
   random partition with the identical class-size distribution it scores
   63.6 % vs 22.4 % on the edges it covers, and the hybrid — evidence-based
   subsystem where there is evidence, link-order slice for the 384 that have
   none — beats **both** components: 34.6 % against 30.2 % and 28.1 %.

**Revised recommendation, replacing §5.6:** if net is modularized, do it as a
**link-order cut overridden by the evidence-based attribution**, at roughly ten
modules, and do not gate it on naming the remaining 726 functions. Naming
remains worth doing for reviewability; it is not the blocker §5.4 said it was,
because attribution does not need a name.

### 10.5 What could actually be NAMED, by evidence class

Attribution is not a name. On names, this pass is deliberately conservative —
"a well-evidenced 200 beats a speculative 604", and most of the 726 do not
support a name from the image alone.

```
TRIVIAL ACCESSORS -- whole shipped body is one PC-relative load of a named
global's address, one load or one store with a constant displacement, and a
return.  Name derived mechanically from the global's recovered name, the
access width and the direction, all read from the shipped instruction.
                                                        24 functions
                                                        (22 distinct names;
                                                         2 collisions to resolve)
```

Everything else this pass looked at needs a body-level reading to name honestly,
which is the work the existing 166 names represent and is not something this
pass can do at scale without inventing. **Reported as 24 mechanically nameable,
not as 200.** The 24 are listed with their evidence in the pass artefacts (§13);
they are NOT applied, because renaming a symbolized net source changes the
identity every vector in `recon/tests/vectors/net` is keyed by and the build's
`recon/generated/net_retained_sources.cmake` path list, and neither is worth
churning for 24 accessors mid-pass.

One further correction they surface: two of the 24 would be named from globals
whose recovered name begins with a digit (`g_154_critical_section_nest_cnt`),
which is not a legal C identifier stem. That is a latent defect in the global
name catalog, not in the naming rule.

---

## 11. Results — this pass's vector set

All 376 vectors were generated AND replayed under the pinned harness of §9.2
(`936cee0b67396ca5`, `STACK_ARG_WINDOW=48`, `DERIVED_ARITY=1`,
`ORACLE_PRESERVE=1`, derived pointer-argument mask). Every vector on disk
carries that stamp; there is no unstamped vector left in
`recon/tests/vectors/net`.

### 11.1 ★ Task 2 is complete: every vectorable named and changed symbol

```
                                            previous pass    this pass
retained net symbols with a catalogued size       892            892
  carrying a recovered name                       166            166
    VECTORED                                       69            166   (100 %)
  touched by stage 02 (the only net delta)         132            132
    VECTORED                                       79            132   (100 %)
unnamed symbols also vectored                       -            210
TOTAL VECTORS                                     233            376
fixtures                                        5,527          8,415
```

The previous pass's "107 of the 176 named are un-vectored" is corrected to
**97 of 166**: 10 of the 176 named symbols have no catalogued size, so
`cli.cmd_gen` skips them by design and they were never vectorable. All 97 are
now vectored, as are the 53 remaining stage-02-changed symbols.

### 11.2 Coverage of the shipped net bytes

```
symbols                                376
fixtures                             8,415
aggregate CFG-instruction coverage  12,436 / 21,148 = 58.8 %
symbols at 100 %                       204
symbols below 50 %                      58
symbols with ZERO fixtures (VACUOUS)    10   <- now REPORTED as VACUOUS,
                                                 not as OK(0/0) (§6.1 patch landed)
coverage over the 166 NAMED symbols   4,156 / 6,980 = 59.5 %
coverage over the 132 CHANGED symbols 4,448 / 8,782 = 50.6 %
```

**58.8 % still does not meet the ≥ 70 % bar** of test_architecture.md §8.2, and
it is essentially unchanged from the previous pass's 59.7 % on 60 % as many
symbols. Reported as a failure of the gate.

### 11.3 ★ Tree agreement — 376/376, and the non-vacuous part is now 132

```
replayed on BOTH stage-00 and stage-09 net trees        376
  same verdict                                          376
  DISAGREEMENTS                                           0

  both OK                                               290
  both FAIL (identical failure)                          76
  both VACUOUS                                           10
  CCFAIL / ABSENT                                         0

stage-02-CHANGED symbols -- the only net files whose
source differs between the two trees at all             132
  agree                                                 132
  disagree                                                0
```

The previous pass constrained **79** of the 133 changed retained files; this
pass constrains **132 of 132 vectorable** (one of the 134 changed files is
stock and one has no catalogued size). Within the covered instruction set,
**the ladder's stage 00 → stage 09 changes no observable net behaviour, and
that statement now rests on the whole of net's actual delta rather than on 59 %
of it.**

### 11.4 The vacuous ten, and why the §6.2 `nptr` story was the wrong diagnosis

```
sdc_assertion_fail                        controller_work_duplicate_enqueue_assert
sdc_conn_timing_fault                     controller_packet_build_next
sdc_ecb_run_blocking                      schedule_phase_offset_get
FUN_0100b6b4  FUN_01021108  FUN_01031820  FUN_01035edc
```

All ten fail for one reason — **100 % of candidate fixtures hit the
200,000-instruction cap** — and the reason for THAT is not the pointer-argument
mask. Five of the ten are the `for (;;) <panic>` idiom (§12.3); the shipped
`sdc_assertion_fail` never returns, so under an oracle that DOES return the
body loops forever. `sdc_ecb_run_blocking` polls an ECB hardware flag that no
emulated peripheral ever sets.

**The `--nptr 1` demonstration the brief asked for cannot be performed as
specified, because the symptom no longer reproduces.** The previous pass named
one pair; re-measured under the current harness:

```
$ net_modtest.py gen ocrypto_constant_time_is_zero ocrypto_constant_time_equal --nptr 2
GEN  ocrypto_constant_time_is_zero   cases=2  cov=8/8 (100%)
GEN  ocrypto_constant_time_equal     cases=3  cov=12/12 (100%)
$ ...                                                       --nptr -1
GEN  ocrypto_constant_time_is_zero   cases=3  cov=8/8 (100%)
GEN  ocrypto_constant_time_equal     cases=3  cov=12/12 (100%)
```

`ocrypto_constant_time_is_zero` produced **zero** fixtures at `nptr = 2` in the
previous pass and produces two now, at 100 % coverage, under the same
`nptr = 2`. Something in `generate.py` — rewritten by its owner after that pass
(+215 lines) — closed it. Derived `nptr` is still the better setting (3
fixtures vs 2) and is now this driver's default, but **it is not what fixed the
class, and the other five symbols of that six were never identified in the
record, so there is nothing to re-measure them against.** Stated rather than
quietly dropped.

---

## 12. ★ TASK 1 — root-causing the failures

The inherited number was 46 of 233. On this pass's larger set it is **86 of
376** (76 FAIL + 10 VACUOUS), and **all 86 fail identically on both trees**, so
none is a stage-02 regression. What follows classifies them by mechanism, and
every class is demonstrated on at least one member with an experiment, not
inferred from its shape.

```
class                              n    what it is
------------------------------- ----   ---------------------------------------
F-GOLDEN-FAULTS                   20    shipped bytes fault, candidate returns
F-EVENTS                          17    trace differs mid-run
F-EVENT-COUNT                     10    trace lengths differ
F-VACUOUS                         10    no fixture survived (§11.4)
F-ADDR-DELTA                       7    same event, different address
F-RETURN-ONLY                      7    IDENTICAL trace, different return value
F-CALLS                            5    different number of calls
F-CAND-FAULTS                      3    candidate faults, shipped bytes do not
F-STACK                            3    stack-record mismatch
F-CAND-RUNAWAY                     2    candidate never returns
F-VALUE                            2    same address, different value
```

### 12.1 ★ ORACLE DEFECT — an oracled call never writes its OUT-PARAMETER

`emu`'s order-keyed call oracle writes r0 and r1 and nothing else. A callee
whose job is to fill a caller-supplied buffer therefore writes **nothing**, and
the caller then reads a stack slot no instruction in the run ever wrote. Golden
and candidate lay their locals out differently, so they read different garbage
— and the divergence is invisible in the event trace, because the stack is
excluded from it.

`radio_slot_margin_get` is the clean instance: golden and candidate produce the
**same events hash** `e298e620…` and the same 3 calls, and differ only in the
return value, 348 (0x15c) vs 338 (0x152) — exactly this function's
`active_margin` vs `idle_margin` pair. Decisive experiment, compiling the
canonical source with the two locals forced to a constant and changing nothing
else:

```
$ probe_uninit.py radio_slot_margin_get
as-is      ok=False failures=1  expected=[[348]] got=[[338]]
locals=0   ok=False failures=3  expected=[[348],[324],[339]] got=[[338],[314],[329]]
locals=1   ok=True  failures=0
```

**Forcing the two locals to 1 makes the reconstruction pass all three golden
fixtures.** The value that decides the answer is supplied by neither the
fixture nor the code; the comparison is ill-posed. `radio_transition_overhead_get`
(217 vs 207) and `FUN_01012c14` (161 vs 151) are the same function shape and
the same 0xd9/0xcf and 0x89/0x7f constant pairs.

Population bound: **27 of the 86 failing symbols pass `&local` to a callee**,
which is the precondition for this class.

**Patch, for the owner of `tools/modtest/**` — not applied here.** The safe
version cannot manufacture anything, because it only DROPS fixtures:

```python
# core.py, in the golden run: track writes, and reject a fixture whose golden
# read a byte of its own stack frame that nothing in the run wrote.
#
#   uninitialised = golden_stack_reads - golden_stack_writes - fixture_seeded
#   if uninitialised: drop the fixture (search.dropped_uninitialised_stack)
#
# A stronger version -- have the call oracle write sha256(ordinal) bytes
# through any argument register that points into the stack/scratch arena, on
# BOTH sides -- makes the fixture usable instead of dropping it, and is the
# exact counterpart of the r0/r1 preservation already landed in
# `oracle_preserve_map`: there the oracle clobbered too much, here it writes
# too little.
```

### 12.2 ★ FIXTURE DEFECT — the derived pointer mask misses PASS-THROUGH pointers

`generate.pointer_arg_mask` marks argument *i* a pointer when a load or store
uses a register still derived from it, and **clears every argument register's
origin at a `bl`**. A function that only hands its pointers to callees — a
wrapper — therefore reports an EMPTY mask, `make_args` seeds those registers
with random integers, and the shipped bytes fault dereferencing them. The
frozen golden then records a fault the hardware never takes.

Audited against the reconstructed signatures, which are an independent
derivation (Ghidra decompilation plus review) rather than a restatement of the
same instructions:

```
vectors audited                                                 370
  derived mask agrees with the signature                        300
  derived mask MISSES at least one pointer parameter             47   (12.7 %)
  derived mask has an EXTRA entry the signature does not         24
```

**12.7 % is the same order as the app core's "Ghidra callee arities over-wide
on 310 of 2,383 callees (13 %)", in the opposite direction and by a different
mechanism.** 21 of the 86 failures are among the 47.

Decisive experiment on `FUN_01008a28`, whose signature is
`void f(uint32_t out[8], const uint32_t value[8])` and whose derived mask is
`[]`:

```
derived mask  []   golden = FAULT "Invalid memory write", candidate returns  -> FAIL 0/42
--nptr 2           golden = RETURN, 11 events, 3 calls                       -> golden no longer faults
```

The docstring's conservatism argument — *"the analysis can only ever say this
register IS written too often, never too rarely"* — is about `callee_gpr_defs`,
and does not transfer: for the POINTER mask the unsafe direction is
under-marking, and it is under-marking on one vector in eight.

**Patch, for the owner — not applied here.** Do not clear an argument
register's origin at a `bl` when it is still in an argument position: a value
in r0–r3 at a call site is being PASSED, and if the callee dereferences it the
caller's argument is a pointer. Conservative form:

```python
        if head in ("bl", "blx"):
            for name in _ARG_REGS:
+               # A value still sitting in an argument register AT the call is
+               # being passed on.  A wrapper never dereferences its own
+               # pointer arguments, so clearing here reports an empty mask and
+               # make_args then seeds a pointer parameter with a random int.
+               # Measured: 47 of 370 net vectors, 21 of 86 net failures.
+               if origin.get(name) is not None:
+                   mask.add(origin[name])
                origin.pop(name, None)
            continue
```

### 12.3 ★ IDIOM — `for (;;) panic()` against an oracle that returns

The net reconstruction spells a noreturn platform panic as

```c
static __attribute__((always_inline, noreturn)) inline void
panic(uint32_t domain, uint32_t reason) { for (;;) sdc_assertion_fail(domain, reason); }
```

with the comment *"Repeating the platform call if a test double returns
preserves that contract"*. Against `emu`, whose oracle **does** return, that
loop runs until the instruction cap while the shipped bytes simply fall
through. `FUN_01013650` — the one net failure AGENTS.md already names — is
exactly this: `ncalls 8` golden vs **33,331** candidate.

```
failing symbols using the idiom            21 of 86
net sources using the idiom overall        58 of 1,155
  so: 21/58 = 36 % of idiom users fail, against 65/1,097 = 5.9 % of the rest
```

This is not a reconstruction defect — on silicon the callee never returns and
both forms are equivalent — and it is not a harness defect either, exactly.
It is an interaction, and the cheap fix belongs to the harness: treat a call to
a target that never returns in the shipped image as terminating the golden and
the candidate alike. The harness already computes enough of the callee's CFG
(`callee_gpr_defs` walks it) to know which targets have no reachable return.

### 12.4 ★ HARNESS — the ordered READ trace over-constrains C evaluation order

`sdc_buffer_elapsed_units_get` fails 2 of 8 fixtures with

```
seed-9   golden ('R', 1346232380, 2, 0)   candidate ('R', 1346232382, 2, 0)
seed-33  golden ('R', 1076094354, 2, 0)   candidate ('R', 1076094356, 2, 0)
```

— a two-byte delta on the FIRST event. Its reconstruction reads
`*(uint16_t*)(state+6)` and `*(uint16_t*)(state+8)`, and the shipped
disassembly reads `[r3,#6]` then `[r3,#8]`; the offsets are identical and the
source matches the image instruction for instruction. **The two reads are
unsequenced in C**, so the compiler is free to emit them in either order, and
the harness's ordered read trace calls that a divergence. `sdc_buffer_accumulate`
(+10) and `controller_packed_cursor_advance` (+24) are the same thing at other
offsets.

`core._sort_independent_write_runs` already exists for the write side. The read
side has no counterpart. **Patch: apply the same independent-run
canonicalisation to consecutive reads that are not separated by a write, a call
or a fault** — reads have no side effects, so reordering them within such a run
cannot lose information.

### 12.5 ★ RECONSTRUCTION DEFECT, FOUND AND REPAIRED — signed vs unsigned divide

`controller_duration_to_units` (`FUN_0100d538`) failed **10 of 43** fixtures,
always by exactly one: 5661/5660, 23841/23840, 8272/8271, 46409/46408,
51848/51847.

```
0100d548  cmp   r0, r3
0100d54c  bls   #0x100d574        <- UNSIGNED compare guards the divide
0100d54e  subs  r0, r0, r1
0100d550  sdiv  r0, r0, r2        <- SIGNED divide
```

The guard is unsigned, so `duration - base` may exceed 0x7fffffff, and the
shipped code then truncates a NEGATIVE quotient toward zero. The
reconstruction divided two `uint32_t`, which floors instead — the two differ by
one on exactly those inputs. Repair:

```c
        return ((uint32_t)((int32_t)(duration - base) / (int32_t)divisor)) & 0xffffu;
```

Verified against the shipped bytes, compiled from an in-memory override so no
tree was written during the test:

```
as-is        ok=False failures=10 / 43 cases
sdiv-repair  ok=True  failures=0  / 43 cases
```

**Applied** to `recon/symbolized/net/controller_duration_to_units.c` and
`recon/net/src/FUN_0100d538.c` — the canonical address-keyed trees, where
defect repairs are legitimate (AGENTS.md). The stage trees were NOT touched:
a stale stage is REGENERATED with `driver.py materialize`, never hand-patched,
and that is the owner's call. **Until it is regenerated, `net_modtest.py run
controller_duration_to_units` will still report FAIL, because it replays the
stage trees.**

Systematic sweep for the same class, over every retained net function whose
shipped bytes contain a divide:

```
functions whose shipped bytes divide            31
  sdiv only                                      6
  udiv only                                     25
  both                                           0
SUSPECT (sdiv in the image, no signed type anywhere in the C)   2
   controller_handle_slot_find_from   0x0102741e
   controller_handle_slot_find        0x01027470
```

Both suspects are in the failing set. Neither was confirmed: in both, the
dividend is a slot index in 0..256 and the divisor a zero-extended byte, so
signed and unsigned agree on every value they can take, and the failure must
have another cause. **The class is bounded at one confirmed instance, not
generalised from it.**

### 12.6 ★ A RECONSTRUCTION that cannot be right — `FUN_01008a28`

Once §12.2's fixture defect is removed with `--nptr 2`, the golden runs cleanly
(11 events, 3 calls) and the CANDIDATE is the side that fails: 0 events,
`returned: false`. The shipped body is 48 bytes:

```
01008a28  push.w {r0, r4, r5, r6, r7, r8, sb, sl, fp, lr}
01008a2e  bl     #0x1008670
01008a3e  bl     #0x1008940
01008a46  bl     #0x1008940
01008a50  stm.w  r8, {r0, r1, r2, r3, r4, r5, r6, r7}
```

— a wrapper around three helpers with a **non-standard in-register ABI** (a
256-bit value carried in r0–r7), which is Oberon's hand-written P-256
assembly. Our reconstruction is a from-scratch C re-implementation of modular
squaring with all three helpers `static inline`, so it makes **zero** calls and
runs a 512-iteration bit loop. It is semantically plausible and structurally
unrelated to the shipped function.

`0x01008a28` has **no row in `recon/ownership/adoption_manifest.json`** (it is
one of the 676 retained net files with no adjudication at all), yet it sits in
the same Oberon block as `ocrypto_constant_time_equal`, which AGENTS.md records
as adopted byte-exact from `liboberon_3.0.13.a`. **Recommendation: adjudicate
0x01008a28 and its neighbours 0x01008670 / 0x01008940 for byte-exact adoption
rather than reconstruction.** Not done here — adoption decisions are a manifest
change, outside this pass's ownership.

### 12.7 Accounting — what is and is not explained

```
failing symbols                                          86
  pass &local to a callee            (§12.1 precondition) 27
  derived pointer mask misses a pointer      (§12.2)      21
  use the for(;;) panic idiom                (§12.3)      21
  first divergence is an address delta       (§12.4)       7
  union of the four                                       57
  NOT explained by any of them                            29
```

The 29 are listed in the pass artefacts. Two of them are named above
(`controller_duration_to_units`, repaired; `FUN_01008a28`, structural), leaving
**27 net failures with no established cause**. That is the honest residue, and
it is smaller than the 46 this pass inherited *entirely* un-triaged.

**No failure found in this pass is a stage-02 regression.** All 86 reproduce
identically on the canonical tree.

---

## 13. Mutation kill rate on the NEW vectors — the anti-vacuity check

The 143 symbols this pass vectored for the first time have no inherited
kill-rate evidence, so the 111 of them whose baseline PASSES were graded, 16
mutants each, against the refactored tree, every mutant compiled from an
in-memory override.

```
symbols graded                                    111
  baseline FAIL -- excluded by construction          0   (the list was built
                                                          from the passing set)
  zero valid mutants -- rate n/a                    23   (§6.3 class, unchanged)
  usable                                            88

killed    530
survived  378
invalid    85   (did not compile; counted neither way)
--------------------------------------------------
** KILL RATE  530 / 908 = 58 % **
per-symbol median 71 % ; >= 70 %: 45 of 88 ; < 50 %: 23
```

**58 % is below the previous pass's 69 % and below the ≥ 70 % bar**, which is
expected and is the point of measuring it: the previous 69 % was over 37 usable
symbols chosen from the named/sampled set, and this is over 88 symbols drawn
from the part of net nobody had tested before. The median is the same (71 %);
the mean is dragged down by a longer tail.

Three vector sets kill **nothing** and are reported as such rather than counted
as coverage:

```
  0 %  FUN_0102ed18                        0 / 16
  0 %  sdc_llcp_handle_unknown_response    0 / 16
  0 %  sdc_hci_event_suppressed            0 /  2
```

A vector set with a 0 % kill rate is a vacuous pass in everything but name.
Those three, plus the 23 with no valid mutant at all, are 26 of 111 symbols
(23 %) with no anti-vacuity evidence.

---

## 14. Files changed by this pass (nothing committed)

```
MODIFIED
  recon/analysis/net_test_coverage.md          sections 9-15 appended
  recon/tests/net_modtest.py                   --nptr default 2 -> -1 (derived);
                                               harness-pin comment corrected
  recon/symbolized/net/controller_duration_to_units.c    DEFECT REPAIR §12.5
  recon/net/src/FUN_0100d538.c                          the same repair
  recon/tests/vectors/net/**                   ALL 376 regenerated + stamped

NEW
  recon/analysis/net_subsystem_attribution.json  490 functions with subsystem +
                                                 evidence class, 24 accessor
                                                 name proposals, and the
                                                 partition metrics of §10.4

TEMPORARY, in the repo root, NOT deleted
  .modtest_pin/                                a COPY of tools/modtest taken at
                                               05:45 plus symlinks to tools/*,
                                               harness_rev 936cee0b67396ca5
```

**`.modtest_pin/` is deliberately left in place.** `tools/modtest/core.py`
changed again at 06:01, so the pinned content no longer exists anywhere else
and deleting the pin would make every number above irreproducible. Delete it
once `tools/modtest` settles, then regenerate — the vectors will correctly
report `STALE-VECTOR` at that point. To reproduce anything here meanwhile:

```bash
export G1_MODTEST_DIR=$PWD/.modtest_pin/modtest
PYTHONSAFEPATH=1 .venv/bin/python recon/tests/net_modtest.py run <symbol>
```

**Not touched:** `tools/modtest/**` (four patches written out instead, §9.1,
§12.1, §12.2, §12.4), `recon/refactor/**` (including the stage trees — see the
§12.5 caveat), `recon/symbolized/app/**`, `recon/app/src/**`, app vectors,
`AGENTS.md`, and every ownership manifest.

Working files live in a net-namespaced scratchpad subdirectory
(`<scratch>/netpass2/`) precisely because §7 recorded the concurrent agent
writing `grade*.json` into the shared scratchpad root; every aggregate in this
document is computed from an explicit `run_all.<i>.json` / `grade_net2.<i>.json`
file list, never a glob.

---

## 15. What this pass did NOT do, and why

* **Did not edit `tools/modtest/**`.** Four patches are written out instead:
  the unstamped-vector counter (§9.1), the out-parameter oracle (§12.1), the
  pass-through pointer mask (§12.2) and the read-order canonicalisation
  (§12.4). Its owner was actively editing it throughout — three edits landed
  inside this pass's sweeps.
* **Did not regenerate the refactor stage trees**, so the §12.5 repair is not
  yet visible to `net_modtest.py run`. `driver.py materialize` is the owner's
  call and `recon/refactor/**` is out of this pass's ownership.
* **Did not root-cause 27 of the 86 failures.** §12.7 lists the accounting;
  the 29 unexplained minus the two named there. Every one of them is
  reproducible with the pinned harness and its first divergent event is
  recorded in the run JSON.
* **Did not repair `FUN_01008a28`.** It needs an in-register 256-bit ABI
  reconstruction, and the right answer is probably byte-exact adoption from
  `liboberon_3.0.13.a` — a manifest decision, not a source edit (§12.6).
* **Did not apply the 24 accessor names** (§10.5). Renaming a symbolized net
  source changes the identity every vector is keyed by and the path list in
  `recon/generated/net_retained_sources.cmake`; not worth churning mid-pass for
  24 accessors, and two of the 24 need a global-name catalog fix first.
* **Did not vector the remaining 516 unnamed retained symbols**, nor the 31
  with no catalogued size, nor the 232 stock symbols (by design — stock is
  adopted byte-exact and is not ours to restructure).
* **Did not grade the 233 inherited symbols again.** The 111 graded here are
  the ones with no prior evidence; regrading the rest would re-measure what §4.4
  already measured, at ~25 minutes of machine time per 40 symbols.
* **Did not build the net image.** The §12.5 repair changes one expression in
  one function and does not change any interface; a build would be the right
  check before it is relied on, and it is left for the owner because the net
  build is FROZEN at 225,581 B and rebuilding it is a decision, not a test.
* **Did not run Renode**, and did not cite `cfg_verify` (AGENTS.md: it is blind
  in both directions on this code).
* **Did not commit.**
