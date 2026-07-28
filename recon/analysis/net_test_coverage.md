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
