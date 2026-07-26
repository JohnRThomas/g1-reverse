# `recon/refactor/` — staged, mechanical refactor pipeline, and Stage 01

**Status: IN PROGRESS.** This file is written incrementally as the work runs, so
that a mid-run process failure cannot lose it. Sections appear in the order they
were measured. Nothing here is committed.

Starting point of this pass:

```
HEAD          7b5bf7cb  "G7-B2: one authoritative log prototype -- 2,420 declarations, 6 real defects fixed"
working tree  dirty (concurrent parity agent):
              M recon/app/src/FUN_0002ea28.c, recon/verified/src/FUN_0002ea28.c (+ _sym mirrors)
              M recon/symbolized/app/fuel_gauge_sample_init_timestamp.c
              M recon/symbols/g1_app_globals.ld, recon/symbols/g1_app_symbols.h
              M recon/generated/app_verified_data_sources.cmake
              M tools/cfg_verify.py
              ?? recon/data/rodata_0x88a50.c
```

A second agent is landing reconstruction defect fixes concurrently. Every number
below is a measurement taken at a recorded moment against a recorded content
hash; the stage MANIFESTs pin those hashes so a stage can be told stale and
regenerated rather than reconciled by hand.

---

## 1. Where Stage 01 actually starts — the population, measured

The owner's calibration is that `recon/ownership/literal_inline_plan.json` holds
5,669 candidates of which the **inlinable population is 2,092**, and that part of
it is already applied. Both halves confirmed against the live files:

```
$ literal_inline_plan.json totals
  rodata_reference_candidates 2978   numeric_literal_candidates 2691
  inline 2092    keep_symbolic 3135    ambiguous 442
```

2,092 = G6-B1 554 + G6-B2 623 + G6-B3 857 + G6-B4 58, exactly.

**What is already applied** (committed history, `prerefactor_progress.md`):
G6-B4 (58, as `G1_*` register macros), G6-B3 (796 of 857) and G6-B1 (548 of 554)
landed in `recon/symbolized/*` — 8,780 reference sites, 1,344 numeric `PROVIDE`
pins retired. Stage 01 therefore does **not** start from zero and must not
re-apply them.

**Measured remaining population.** Every `rodata_<hex>` token still referenced
from the authoritative compilable input set (the 1,609 app + 923 net entries of
`recon/generated/*_retained_sources.cmake`, plus the 5 `.inc` files those
sources `#include`), comments and string bodies masked:

| | distinct `rodata_*` symbols | sites |
|---|---:|---:|
| still referenced in the build tree | **1,122** | **2,443** |

Cross-referenced against the plan's batches:

| batch | candidates | still referenced in the build tree | sites |
|---|---:|---:|---:|
| G6-B1 log-argument strings | 554 | **1** | 1 |
| G6-B2 non-log strings | 623 | **506** (465 app / 41 net) | **1,233** |
| G6-B3 no-canonical-site strings | 857 | **38** | 48 |
| G6-B4 register addresses | 58 | 0 (applied as macros) | 0 |
| G6-B5 / G6-B6 (numeric, review) | 45 / 122 | 0 (no pin symbol) | 0 |
| G6-A ambiguous | 275 | 126 | 200 |
| G6-X keep-symbolic | 3,135 | 449 | 959 |

So the honest Stage 01 target is **~545 candidates over ~1,282 sites**
(G6-B2 506 + G6-B3 residue 38 + G6-B1 residue 1), not 2,092 and certainly not
5,669. The rest of the 2,092 is either already applied or is a `keep_symbolic`/
`ambiguous` class that Stage 01 must not touch.

*Reconciliation with the transformer's own final census (3.7).* The transformer
considered **2,034** candidates — the 2,092 `classification: inline` population
minus the 58 G6-B4 register-address candidates, which carry no `pin_symbol` and
are therefore not a withdraw-transaction at all (they were applied as `G1_*`
macros in a previous pass). Of those 2,034, **544** have a live reference in the
compilable tree. The 545 above counted one extra candidate whose only remaining
occurrence is inside the transaction's own artifacts.

*(sections below are appended as the work proceeds)*

---

## 2. `recon/refactor/` — the pipeline

```
recon/refactor/
  README.md                      the contract
  guard.py                       the write guard (R1) -- the single choke point
  input_set.py                   authoritative derivation of the COMPILABLE input set (R2)
  stagelib.py                    materialisation, MANIFEST/PARITY_MAP, staleness, address sets
  driver.py                      status | materialize N | check-addresses A B | input-set
  test_guard.py                  proves the guard refuses both classes of illegal write
  transforms/t00_snapshot.py     identity transform
  transforms/t01_literal_inline.py
  stage_00_snapshot/  { MANIFEST.json, PARITY_MAP.json, tree/ }
  stage_01_literal_inline/ { MANIFEST.json, PARITY_MAP.json, QUARANTINE.json, tree/ }
```

### 2.1 The write guard is structural, not a convention

`guard.check_write(path, stage_dir)` is the only way anything in the pipeline
writes. It refuses on **two independent conditions**:

1. `path` inside a protected evidence tree — `recon/app/src`, `recon/app/src_sym`,
   `recon/net/src`, `recon/verified/src`, `recon/verified/src_sym`, `recon/data`,
   `recon/net/data`, `recon/emulator`, `tools`;
2. `path` outside the stage's own directory.

So a transformer cannot touch canonical evidence *and* cannot escape its stage
even by accident. `test_guard.py` asserts both refusals plus the positive case.

### 2.2 The input set, derived from the generated lists and not from a glob

```
$ driver.py input-set
 transformable             2612
 quarantined_protected       36    (compiled, but inside a protected tree)
 provenance:
   retained_sources        {app: 1609, net: 923}   <- recon/generated/*_retained_sources.cmake
   inc_fragments              5    <- #include'd by retained sources
   cmakelists_direct       {app: 29, net: 71}      <- spelled inline in the two CMakeLists
   rodata_tus                17    <- recon/application/rodata/*.c
   pin_artifacts              4    <- g1_{app,net}_globals.ld, g1_{app,net}_symbols.h
```

The 36 **quarantined protected** entries matter and were not obvious: the app
CMakeLists compiles 2 sources straight out of `recon/app/src`
(`FUN_0007f772.c`, `FUN_0007f79e.c`) and the net CMakeLists compiles 34 out of
`recon/net/src`. They are build inputs that live in an R1-protected tree, so the
pipeline carries them **by reference** and can never rewrite them.

The 4 pin artifacts are in the transformable set because the inline transaction
is not complete without them (see 3.1).

### 2.3 How a stage is built — and the proof that the mechanism is sound

A stage's `tree/` is a **complete buildable repository root**: transformed files
are real files; everything else the build needs is a *relative* symlink back into
the repository. `build_cohesive.sh` is invoked from inside the stage tree exactly
as it is invoked from the repo, so **no build file, linker script or `tools/`
logic is edited to build a stage.**

One subtlety is load-bearing and is enforced in `driver.FORCE_REAL_DIRS`: every
directory from which a relative `..` traversal starts must be a *real* directory
in the stage tree. `recon/generated/*.cmake` names its sources as
`${CMAKE_CURRENT_LIST_DIR}/../symbolized/app/<name>.c`, and the symbolized
sources `#include "../../headers/g1_log.h"`. If `recon/generated` or
`recon/symbolized` were symlinks, the OS's *physical* `..` resolution would
escape the stage and silently compile the **live** repository — a silent-wrong
failure, not a loud one. Ten directories are forced real for this reason.

**Measured proof that the mechanism is neutral** — the same commit, built twice:

```
./recon/application/build_cohesive.sh                       app /private/tmp/g1-rf-base-app
./recon/refactor/stage_00_snapshot/tree/recon/application/build_cohesive.sh app /private/tmp/g1-rf-s0-app

cmp .../g1-rf-base-app/zephyr/zephyr.bin .../g1-rf-s0-app/zephyr/zephyr.bin   -> no difference
size: text 949488  data 4951  bss 249251   -- identical
FLASH 954,444 B / 982,528 B = 97.14 %      -- identical
RAM   253,765 B / 440 KB    = 56.32 %      -- identical
```

Both builds exited 0. `driver.py status` afterwards reports stage 00
`"state": "current", "inputs_unchanged": 2612` — i.e. the concurrent agent did
not move an input underneath the comparison, so the two builds really are of the
same content.

### 2.4 Correction to the flash figure in the brief

The brief states the app image is **948,812 B (96.57 %)** with ~33 KB headroom.
Measured at this pass's HEAD (`7b5bf7cb` + the concurrent working tree) the app
image is **954,444 B (97.14 %)**, i.e. **+5,632 B** and **28,084 B of headroom**.
The growth is the concurrent parity agent's, not this pass's; it is stated here
because Stage 01's budget is measured against the *current* number, not the
brief's.

---

## 3. Stage 01 — literal inlining

### 3.1 What the transformation is, exactly

For a byte-verified `.rodata` string object it performs the **four-part
transaction** in one regeneration — three parts from `prerefactor_plan.md` §3.2
rule 5, plus the fourth the link requires (found by the G6-B3 batch):

1. every reference site `((unsigned long)&rodata_X) /*=0xVA*/`
   → `((unsigned long)"…") /*=0xVA*/` (provenance comment kept; the per-file
   header line is annotated `[INLINED -- refactor stage 01]`);
2. the emitted object is deleted from `recon/application/app/src/g1_app_string_rodata.c`;
3. `PROVIDE(rodata_X = 0xVA);` is deleted from `recon/symbols/g1_app_globals.ld`;
4. `extern const unsigned char rodata_X[];` is deleted from
   `recon/symbols/g1_app_symbols.h`.

Doing 1 without 2 **grows** flash. Doing 2 without 3 silently resurrects the
original-image address at every remaining reader. Doing 3 without 1 is a **link
error** — which is the point: after the transaction a missed reference site
cannot be silent. This is why the pin/declaration artifacts are in the
transformable input set at all.

### 3.2 The acceptance rule (mechanical, conservative, and stated)

Under R7 the only thing inlining changes observably is the **pointer value**
handed to the consumer; the **bytes** are identical by construction (copied out
of the byte-verified object and re-checked against `app_update.bin`). A pointer
value is unobservable outside the chip unless it is compared, or stored and later
compared. So:

* a candidate is applied only if **every** live reference resolves — through at
  most one level of `#define` or local-assignment indirection — to an argument
  position of an **accepted** callee;
* a callee is accepted if it is a logging entry point whose ABI was read off the
  shipped disassembly (`recon/headers/g1_log.h`: `log_message`, `DEBUG_PRINT`,
  `debug_print`, `printk`), a C-library string/format function
  (`printf`/`snprintf`/`snprintk`/`strcmp`/`strncmp`/`strstr`/…), **or** a
  function-like macro *defined in the same file* whose body only calls accepted
  callees — that last clause is resolved mechanically and is what let `LOG_IF`,
  `DBGT`, `DBG2`, `DBG4` and `DISPLAY_LOG_2` through on evidence rather than on
  a hard-coded list;
* the byte evidence is **re-derived, never trusted from the plan**: object body
  length == declared length; object > 4 B (the `rodata_decode_report.md` §10 stub
  hazard); exactly one NUL-terminated string (no string pools); object bytes
  equal `app_update.bin` at the VA read through `tools/extract.py`; byte before
  the VA is NUL so the VA is a string **head**, not an interior;
* `UINT32_C()`/`UINT64_C()` token-paste contexts are refused by construction;
* everything else is **quarantined**, untransformed, listed in
  `stage_01_literal_inline/QUARANTINE.json` with its reason.

### 3.3 Result

```
$ driver.py materialize 1
 candidates_accepted        100
 candidates_quarantined    1934
 sites_inlined              178
 files_rewritten             43
 rodata_objects_withdrawn   100      object_bytes_withdrawn 3997
 provide_pins_retired       100      extern_declarations_removed 100
```

All 100 are G6-B2 (the non-log-argument string batch — the one the previous pass
never started, and the only inline batch with meaningful population left).
Accepted consumers, measured: `log_message` 63, `debug_print` 51, `LOG_IF` 19,
`strncmp` 7, `DBG4` 3, `printf` 3, `strcmp` 2, `DBG2` 2, `DBGT` 2, `snprintf` 2,
`snprintk` 1, `DISPLAY_LOG_2` 1, `printk` 1.

### 3.4 First-try compile status — the measurement, not the checkbox

**The Stage 01 tree compiled and linked clean on the first build, first try:
0 errors, 0 new warnings, `nm -u` 0.** The transformer needed **two rounds**, and
both rounds are reported because the iteration history is the finding:

| round | change | outcome | bucket |
|---|---|---|---|
| 1 | first transformer | **0 candidates accepted, 0 sites** — every candidate quarantined as "referenced outside the canonical spelling". The transformer was counting the object *definition* in `g1_app_string_rodata.c` and the *extern declaration* in `g1_app_symbols.h` as foreign references, i.e. it was tripping over the very three files its own transaction rewrites. | **(a) transformer bug** — caught by the materialize step, before any compile |
| 2 | exclude the three transaction files from the foreign-spelling scan | 100 accepted, 178 sites; **build exit 0 first try** | — |

**Compile-failure triage: zero failures, therefore zero bucket-(a) and zero
bucket-(b) findings.** I looked for bucket (b) deliberately and did not find it,
and the honest reason is structural rather than lucky: this transformation
substitutes one `unsigned long`-typed expression for another of identical type
in argument position. It introduces **no new authoritative declaration**, so it
has no mechanism for exposing a latent reconstruction defect. That is precisely
the property that makes it a good *first* stage, and it also means Stage 01
contributes nothing to the G7-B2-style defect harvest. The stages that will
produce bucket-(b) findings are the ones that introduce a type or a prototype
(the MMIO accessor macros of stage 04 and the struct typing of stage 07).

### 3.5 Gate ladder — measured

Built from the stage tree with the repository's own entry point and **no build
file, linker script or `tools/` module edited**:

```
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh app /private/tmp/g1-rf-s1-app
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh net /private/tmp/g1-rf-s1-net -- \
      -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

| gate | baseline (stage 00 == in-tree) | Stage 01 |
|---|---|---|
| app build | exit 0 | **exit 0, first try** |
| net build | exit 0 | **exit 0** |
| app FLASH | 954,460 B / 982,528 B = 97.14 % | **954,336 B = 97.13 % — Δ −124 B** |
| app `.text` | 949,496 | **949,368 — Δ −128 B** |
| app `.data` / `.bss` | 4,951 / 249,251 | **Δ 0 / Δ 0** |
| app RAM | 253,765 B = 56.32 % | **Δ 0 B** |
| app RAM *layout* (`nm -n`, every `0x2…` symbol) | — | **0 diff lines** |
| net FLASH / RAM | — | **225,581 B = 97.48 % / 63,380 B — the frozen values, untouched** |
| `nm -u` undefined | 0 / 0 | **0 / 0** |
| duplicate global definitions | 0 / 0 | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` | 0 | **0** |
| compiler warnings | 1,887 app / 1,066 net | **1,887 / 1,066 — Δ 0** |
| compiler errors | 0 | **0** |
| `gen_retained_sources.py --check` | clean | **clean** |
| `check_ram_pin_collisions.py` app | — | **624 bound OK, 0 escaping, 0 unknown inside a live object** |
| `check_ram_pin_collisions.py --core net` | — | **170 bound OK, 0 / 0** |
| `check_net_raw_literals.py` | — | **0 / 0 / 0 / 0 / 0** |
| `verify_net_stock_data_window.py` | — | **PROVEN** — 93 differing words all flash pointers, **0 differing for any other reason**, 0 non-stock input sections |
| `check_thread_create_stack_args.py --trials 120` | — | **10 / 10 PASS** |
| `driver.py check-addresses 0 1` | — | **identical, 2,561 addresses both sides, 0 gained, 0 lost** |
| `test_guard.py` | — | **7 / 7 PASS** |

**Re-measured after a concurrent input moved.** Midway through the pass the
parity agent edited `recon/symbolized/app/battery_soc_curve_model_init.c`.
`driver.py status` flagged stage 00 stale; both stages were **regenerated** (not
patched) and **both the baseline and the Stage 01 app image were rebuilt from
scratch** so the delta is measured on one input state. The transformation output
is bit-for-bit the same across that regeneration — 100 candidates, 178 sites,
3,997 B, 43 files rewritten — and the whole-image delta is unchanged at −124 B;
only the absolute baseline moved, by the +16 B that edit cost. The figures in the
table above are the **re-measured** ones (`/private/tmp/g1-rf-b2-app` vs
`/private/tmp/g1-rf-s2-app`). The net figures are from the earlier net build,
which stays valid because that edit touched no net input.

**`.rodata` read back out of the linked ELF's PT_LOAD and byte-compared with
`app_update.bin`:**

| | match | mismatch |
|---|---:|---:|
| baseline | 1,424 | 14 |
| Stage 01 | **1,325** | **14 — the same 14** |

The match count falls by exactly 99, which is the number of withdrawn objects
that were actually live in the link (one of the 100, `rodata_a71cd`, had already
been dropped by `--gc-sections` in the baseline). **No object that survived
changed a byte.** The 14 mismatches are the pre-existing, documented
"byte-exact *modulo relocation*" class — the eight localized-string pointer
tables `rodata_8a3e0…8ab18`, `rodata_87d58`, and the five `rodata_0x27cc0`-class
records — identical to the baseline's 14, name for name.

**Per-object comparison, every `.c.obj` of both builds, `--strip-debug
--remove-section=.comment`:** 3,043 objects compared by basename,
**2,999 byte-identical, 44 differing.** 43 of the 44 are exactly the files the
transformer rewrote, the 44th is `g1_app_string_rodata.c.obj` (the withdrawal),
and one further unit — `uname.c.obj` — differs for the reason
`prerefactor_progress.md` §4 already recorded: it is a stock unit that differs
build-to-build regardless of any change. **Nothing outside the transformed set
moved.**

### 3.6 The flash finding, stated plainly

The pre-refactor plan projected that inlining strings is where the flash win is
(66,243 B of app strings at stake). **Stage 01 measures −124 B for 3,997 B of
objects withdrawn.** The reason is arithmetic, not a defect: the transaction
*moves* the bytes rather than deleting them — the object leaves
`g1_app_string_rodata.c` and comes back as a `.rodata.str1.1` literal in each
consuming TU. The saving is only the linker's string merging where two TUs share
a literal. Anyone budgeting a future string batch on a byte-per-object basis will
be wrong by two orders of magnitude; budget it at **≈0 B and gate on the
measurement**, which is what this stage does.

### 3.7 Quarantined — everything left untransformed, and why

`stage_01_literal_inline/QUARANTINE.json`, 1,934 entries. **Not one of them was
hand-edited.**

| quarantine reason | candidates | live sites |
|---|---:|---:|
| no live reference in the compilable tree — already applied by G6-B1/B3/B4, or never compiled | 1,490 | 0 |
| **unproven consumer context** | **310** | **863** |
| net core is frozen | 73 | 164 |
| no emitted object in `g1_app_string_rodata.c` — nothing to withdraw, so inlining would only grow flash | 60 | 66 |
| referenced outside the canonical `((unsigned long)&SYM)` spelling | 1 | 2 |

The 310 unproven-consumer candidates break down as (a candidate may appear in
more than one row):

| why the consumer is unproven | candidates |
|---|---:|
| assigned to a local, then used in a non-call position (`x = y`, a `case` arm, a struct initialiser) | 154 |
| stored / initialised with no callee at all | 79 |
| `#define` body whose macro is used in a non-call position | 25 |
| refused callee `assert_post_action` (documented argument-shape suspicion) | 21 |
| callee not proven to read the value as bytes — `trigger_screen_state_change` 18, `sllist_find_by_name_ci` 11, `task_wait_ticks` 9, `emit` 7, `gui_utf_draw` 6, `log_value`/`vdprintf_to_fd`/`cjson_add_bool_to_object`/`cjson_add_string_to_object`/`LOG_ACTION` 4 each, and a long tail | 78 |

**Net is quarantined wholesale and that is a deliberate correctness decision, not
timidity.** There is no net rodata object to withdraw:
`recon/application/rodata/g1_net_rodata_0*.c` is not wired into
`recon/application/net/CMakeLists.txt`, so the transaction has no "withdraw"
half and inlining on net is *pure growth* against ~1.7 kB of real device
headroom. Independently, commit `6c69eaa8`'s `.rodata` pointee equivalence class
in `tools/parity/emu.py` is deliberately DISABLED for net because net's analysis
and runtime address windows overlap numerically; nothing here enables it.
**The highest-value net follow-up is to wire the net rodata objects first** —
that turns the 73 quarantined net candidates from a growth into a shrink.

---

## 4. What I did NOT do, and why

1. **I did not run the behavioural oracle.** The brief forbids running Renode
   (another agent owns it), and the display/sensor oracle is a Renode capture.
   **So Stage 01 is NOT yet proven against the R7 acceptance bar.** What is
   proven is everything below it: compile, link, `nm -u` 0, per-object
   equivalence outside the transformed set, byte-identical surviving `.rodata`
   against the shipped image, unchanged RAM layout, and the four defect gates.
   The oracle run is the one outstanding gate and it should be the first thing
   done on this stage tree:
   `recon/emulator/scripts/capture_display_sensor_oracle.sh` +
   `build_display_sensor_oracle.py` against `/private/tmp/g1-rf-s1-app`, with the
   §37 recipe (`G1_HOOKS=0`, `$rtinfo_pc` re-read from *this* ELF,
   `G1_CTX_FE8`/`G1_CTX_105A`/`G1_SCREEN_ID` re-derived from `_end` in this ELF).
   The four framebuffer hashes to match are
   `19b1f24a…` / `0c5cc90b…` (dashboard) and `b26c73b3…` / `1d617c65…`
   (navigation). RAM layout diffing to 0 lines means the probe addresses from
   iteration 38 remain valid for this build.
2. **I did not touch any canonical tree** — structurally impossible through the
   guard, and confirmed: `git status` shows no `recon/{app,net,verified}/**`
   change from this pass.
3. **I did not touch `tools/`, `recon/emulator/**`, `armemul`, any build file,
   any linker script in the live tree, or `recon/board/**`.** The stage tree
   carries its own copies of `g1_app_globals.ld` and `g1_app_symbols.h`; the
   live ones are untouched.
4. **I did not apply the numeric-literal batches G6-B5 (errno) or G6-B6
   (IEEE-754 bit patterns).** They carry no `pin_symbol`, so they are not a
   transaction, and the plan itself classifies them as *per-site review* —
   "numeric identity is not evidence". They are not automatable under R5 and are
   not in Stage 01.
5. **I did not touch the "small arrays" class.** It is effectively empty:
   `rodata_decode_report.md` §4 proves element width for exactly two app regions,
   so writing `{1, 2, 3}` for any other region would invent a layout.
6. **I did not build stages 02+.** The ordering is recorded in
   `recon/refactor/README.md`; Stage 01 is the one landed.
7. **I did not run the full `reverify` sweep or `cfg_verify`.** Under R7 they are
   diagnostics, and Stage 01 changes no canonical body, so no canonical function
   owes a re-proof. (`check_thread_create_stack_args`, which *does* drive the
   parity harness over canonical bodies, was run anyway: 10/10.)
8. **I committed nothing.**

---

## 5. The three questions, answered directly

### 5.1 Does anything in this layout make a whole-firmware side-effect comparison harder?

**No — it makes it easier, with one caveat worth knowing.**

Each stage tree is a *complete, self-contained, buildable repository root* that
produces the real firmware artifacts with the repository's own entry point and no
build-file edits. A harness can therefore stand up stage N and the shipped image
side by side without any special casing, and can bisect across stages using the
same command. `PARITY_MAP.json` gives address → stage-file traceability for
localising a failure, and `check-addresses A B` catches a dropped or duplicated
function *before* the oracle runs.

The caveat: object-file **paths** differ between a stage build and an in-tree
build (CMake embeds the absolute source path in the object path). That is a
comparison nuisance for per-object diffs — they must be matched by basename, and
`main.c.obj` in particular collides with MCUboot's `main.c.obj`, which briefly
produced a false "identical" reading in my own measurement until I resolved the
path. It is **not** an image-level nuisance: the stage-00 `zephyr.bin` is
byte-identical to the in-tree build, which proves no source path leaks into
loaded content via `__FILE__` or assert text.

### 5.2 What final artifact does the refactored build produce, and how is it loaded?

Building `stage_NN/tree/recon/application/build_cohesive.sh app <dir>` produces,
under `<dir>/zephyr/`:

| artifact | what it is |
|---|---|
| `zephyr.elf` | the linked app-core image with full symbols — the input to `nm`, the emulator and every gate script |
| `zephyr.bin` / `zephyr.hex` | the raw app-core image |
| **`app_update.bin`** | the **MCUboot-signed update image — directly comparable to the shipped `app_update.bin`** |
| `net_core_app_update.bin` | the same for the net core |
| `merged.hex`, `merged_domains.hex` | flashable images (app+MCUboot; both domains) |

For a side-effect comparison under identical conditions, load
`<dir>/zephyr/zephyr.elf` into the Renode machine exactly as
`recon/emulator/scripts/capture_display_sensor_oracle.sh` already does for the
in-tree build — the stage build is the same kind of artifact in the same layout,
so the capture script needs the build directory changed and nothing else. Two
values must be **re-read from the ELF actually booted** rather than copied:
`$rtinfo_pc` (`runtime_info_sync`) and the `G1_CTX_*` / `G1_SCREEN_ID` probe
addresses derived from `_end`. For Stage 01 they happen to be unchanged (RAM
layout diffs to 0 lines and `.text` moved by only −128 B), but re-reading them is
the rule, not an optimisation.

### 5.3 Which transformations fall under R8?

R8 is *anything that reorders or coalesces volatile MMIO accesses, or changes the
number or order of bus transactions.*

**Stage 01: none.** It substitutes one `unsigned long`-valued expression for
another of identical type in argument position. It introduces no sequence point,
removes none, touches no `volatile` access, and changes no control flow. The
per-object evidence supports this directly: 2,999 of 3,043 objects are
byte-identical and the 44 that differ are exactly the transformed set.

Stage 01's own residual risk is a *different* class from R8 and is worth naming
so it is not confused with it: **pointer identity**. Two references to one string
used to be one address; after inlining they are two `.rodata.str1.1` copies
unless GCC merges them (it does within a TU, and there is no LTO, so it does not
across TUs). That is observable only if the firmware compares two such pointers
for equality. The acceptance rule of §3.2 excludes it by refusing every site
where the value is stored rather than consumed — which is why 154 + 79 + 25 = 258
candidates are quarantined.

**Where R8 will bite in later stages, flagged now:**

| stage | transformation | R8 exposure | conservative default |
|---|---|---|---|
| 02 | volatile-accessor **spelling** normalisation within one type | none — the type is identical, so no access is added, removed or reordered | gate on a byte-identical `.o`; any difference means it was not a spelling change |
| 03 | `__ASSERT` / noreturn macro extraction | none directly; but collapsing a 5-argument site into a 4-argument macro silently drops a register argument, which the parity harness cannot see | per-site argument-count check against the disassembly; refuse any site whose arity does not match |
| 04 | **MMIO accessor macros per width** | **direct.** Folding `*(volatile int*)` and `*(volatile unsigned*)` into one macro changes signedness downstream, and any macro that evaluates its argument more than once, or that a compiler may fold, changes the number of bus transactions | one macro per width **and** per signedness; single evaluation; `volatile` preserved verbatim; per-file `.o` comparison and an oracle run before the batch is accepted |
| 04 | irq-lock prologue (`__set_BASEPRI_MAX(N); __ISB();`) extraction | **direct** — the save/lock/ISB/restore quadruple is an ordering contract, and `__atomic_signal_fence` emits *no instruction* where the dominant form emits a real `isb` (the G7-B1 finding) | never collapse across the two families; keep the divergent copies separate |
| 06 | module materialisation / file moves | none, but `KEEP(*rodata_*.c.obj(".rodata.rodata_*"))` ties flash occupancy to **filenames** — moving into a subdirectory is safe (`*` absorbs the path), renaming across that boundary is not | freeze `rodata_*` filenames; regenerate the KEEP list explicitly and gate on a byte-identical image |
| 07 | struct typing | indirect — a wrong field width changes access width, which for a `volatile` field changes the bus transaction | per-struct batches with `_Static_assert(offsetof/sizeof)` in the shipped header, `.o` comparison, oracle after each |

---

## 6. Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py materialize 0
$V recon/refactor/driver.py materialize 1
$V recon/refactor/driver.py check-addresses 0 1
$V -m unittest discover -s recon/refactor -p 'test_*.py'
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh app /private/tmp/g1-rf-s1-app
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh net /private/tmp/g1-rf-s1-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

`driver.py status` will report stage 00 stale as soon as the concurrent parity
agent touches an input. That is the mechanism working: regenerate both stages and
re-run the ladder. **Never hand-patch a stage tree.**

---

## 7. Idempotency, concurrency and repository footprint

**Idempotency, measured.** `driver.py materialize 1` run twice, no other change:

```
MANIFEST.json sha256          75e04a11ba2b8f38…  ->  75e04a11ba2b8f38…
sha256 over the whole tree/   b0d33c15514de52f…  ->  b0d33c15514de52f…
```

Byte-identical. The transformers are pure functions of their input bytes.

**Concurrency.** The parity agent landed further changes while this pass ran
(`fuel_gauge_update.c`, `fuel_gauge_sample_init_timestamp.c`, `FUN_0002ea28.c`,
`recon/data/rodata_0x88a50.c` and a `g1_app_globals.ld` / `g1_app_symbols.h`
edit). `driver.py status` reports both stages `"current"` at the end of the pass,
because the snapshot was taken after those edits landed —
`recon/symbolized/app/fuel_gauge_update.c` hashes to `5b5f5a5a6bacae93…` both in
the tree and in the stage-00 MANIFEST. Nothing this pass measured was taken
against a moving input. When the agent's *next* edit lands, `status` will say
`stale` and name the file; the repair is `materialize 0` then `materialize 1`,
then re-run the ladder. **No file this pass wrote is outside `recon/refactor/`
and `recon/analysis/staged_refactor_stage01.md`.**

**The repository's own `tools/` test corpus is unaffected by construction, and
I checked rather than assumed.** No `tools/test_*.py` uses `os.walk`, `rglob` or
`glob.glob` over `recon/**` (measured: zero matches), and the four non-test tools
that do `os.walk` walk a *build* directory or an upstream NCS root, never
`recon/`. So `recon/refactor/` cannot be picked up as a duplicate source or a
duplicate identity by anything in the corpus. A full
`python -m unittest discover -s tools -p 'test_*.py'` run was started as a
courtesy check; the corpus takes far longer than this pass had left and its
result is not reported here. Note that AGENTS.md already records
`cfg_verify --self-test` as broken at HEAD for reasons predating this work, so a
green corpus was not the baseline in any case.

**Footprint.** Each stage tree is ~17 MB / ~2,600 real files / ~1,800 relative
symlinks. `recon/refactor/.gitignore` therefore ignores `stage_*/tree/` and keeps
`MANIFEST.json`, `PARITY_MAP.json` and `QUARANTINE.json` — the evidence that a
stage produced what it claims — under version control. Every stage is
regenerable from the committed manifests plus the driver.
