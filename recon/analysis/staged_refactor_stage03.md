# Stage 03 — the pipeline's `.h` blind spot, and the first structural stage

**Written incrementally as the work ran. Nothing here is committed.**

Starting point of this pass:

```
HEAD          5337623a  "Latent defect harvest: 498 argument defects fixed -- and a NEW class 303 sites wide"
              (parent 3bc67207 "R7 GATE PASSES", parent a2f3303d "P4 iter-40")
working tree  dirty (concurrent parity agent, display/sensor + lsm6dso work):
              M recon/app/src/FUN_000622a0.c, recon/verified/src/FUN_000622a0.c
              T recon/application/src/lsm6dso_init_chip.c
              M recon/named|readable_sources|symbolized|... lsm6dso_init_chip.c
              M recon/emulator/reports/*.md, scripts/capture_display_sensor_oracle.sh
              ?? Even+Realities_1.9.0.xapk, recon/emulator/reports/display_sensor_oracle_dashboard.json,
                 golden_framebuffer_dashboard_p2_render.{pgm,png,raw}, ..._crop.png
```

`driver.py status` at the start of this pass:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **stale** | 2,538 | **81** |
| 01 literal_inline | current (rel. stage 00's tree) | 2,619 | 0 |
| 02 block_dedupe | current (rel. stage 01's tree) | 2,619 | 0 |
| 99 defect_probe | stale | 2,600 | 12 |

The 81 moved inputs are commit `5337623a`'s latent-defect harvest — i.e. the
parity agent acting on Stage 02's own `DEFECTS.json`. Stage 00 must be
regenerated before anything is measured, exactly as the R7 gate record's closing
note predicted.

---

## 1. The blocking pipeline fix — `input_set.py` now enumerates `.h` fragments

Stage 02 §6 item 9 filed this as *"the highest-value pipeline fix for the next
stage, to be made before stage 03 materialises."* It is done.

### 1.1 What was wrong

`input_set.py` matched exactly one include shape:

```python
_INCLUDE_INC = re.compile(r'#\s*include\s+"([^"]+\.inc)"')
```

and resolved it **only relative to the including file**, non-transitively, and
only from `.c` seeds. Three consequences, all measured:

* **`.h` fragments were invisible.** That is how
  `recon/symbolized/app/ble_process_put_common.h` stayed outside the pipeline
  while three `.inc` fragments included it. At `a2f3303d` it declared
  `extern int debug_print();` (line 47) and `extern int log_message();`
  (line 64) — K&R-unprototyped *and returning `int`* where the authority says
  `void f(uintptr_t, ...)`.

  **Correction to what I expected to find.** Those two declarations are already
  fixed in the live tree: commit `5337623a` (the concurrent parity agent, acting
  on Stage 02's own `DEFECTS.json`) rewrote them to
  `extern void debug_print(unsigned long, ...)` /
  `extern void log_message(unsigned long, ...)`, a 2-line change. So the fix
  here did not *find* that defect — Stage 02's diagnostic stage 99 did, and it
  has been repaired upstream. What the fix does is put the file **under pipeline
  control**, and that had an immediate, measured effect: with the header in the
  input set, Stage 02's sub-batch E now withdraws both declarations in favour of
  `recon/headers/g1_log.h` (`+#include "../../headers/g1_log.h"`, two `extern`
  lines removed). Before this fix the transformer could not see the file at all,
  so the corrected-but-still-duplicated declarations would have persisted
  indefinitely.
* **`-I`-resolved includes were invisible.** 1,615 app sources spell
  `#include "g1_app_symbols.h"` and 952 net sources spell
  `#include "g1_net_symbols.h"`; neither resolves relative to the including
  file. Both files were nevertheless in the set — but only by the accident that
  they are separately listed as *pin artifacts*. Nothing in the mechanism found
  them.
* **the closure was one level deep.** `g1_net_symbols.h` includes
  `g1_net_ram_reloc.h`; nothing reached it.

### 1.2 What it does now

* quoted includes only (`#include <...>` is the toolchain search path, never
  repository content we may transform);
* both `.inc` **and** `.h`;
* resolved the way the compiler resolves them: relative to the including file
  first, then along `INCLUDE_SEARCH_DIRS`, a new explicit list of the six `-I`
  directories the two CMakeLists actually pass that can name repository content
  (`recon/application/{app,net}/src`, `recon/app/src`, `recon/headers`,
  `recon/symbols`, `recon/wiring`);
* **transitively**, to a fixed point;
* seeded from the **complete** compiled source set (retained sources +
  CMakeLists-direct TUs + generated `.rodata` TUs + pin artifacts), so it runs
  last in `derive()`, not in the middle;
* a fragment resolving into a **protected** tree (R1) is reported as
  `header_fragments_protected` and carried by reference — never transformed.
  Measured: **0** such fragments exist today, but `recon/app/src` really is on
  the app `-I` path, so the guard is load-bearing rather than decorative.

### 1.3 Measured effect on the input set

```
transformable: 2,619  ->  2,625      (+6)
quarantined (protected trees, compiled): 36  ->  36   (Δ 0)
```

The six new files, and why each was missed:

| file | includers | why it was invisible |
|---|---:|---|
| `recon/headers/g1_log.h` | 418 | `.h`, resolved relative |
| `recon/headers/g1_nrf_regs.h` | 40 | `.h`, resolved relative |
| `recon/headers/g1_ghidra_ops.h` | 9 | `.h`, resolved relative |
| `recon/headers/g1_cmsis_shim.h` | 6 | `.h`, resolved relative |
| `recon/symbolized/app/ble_process_put_common.h` | 3 (all `.inc`) | `.h`, **and** only reachable from `.inc` seeds, which were never re-scanned |
| `recon/symbols/g1_net_ram_reloc.h` | 1 (`g1_net_symbols.h`) | second level of the closure |

`unresolved_quoted_includes` is exactly **one** entry, `lsm6dso.c` — a Zephyr
driver TU textually included by our LSM6DSO glue and satisfied from
`${ZEPHYR_BASE}/drivers/sensor/lsm6dso`. It is correctly not repository content
we may transform. **There is no other quoted include in the whole compiled set
that the pipeline cannot account for.**

### 1.4 A side finding: four headers in `recon/headers/` are dead

The closure is now exhaustive, so its complement is meaningful.
`recon/headers/` holds seven files; the closure reaches four. The three it does
not reach — `g1_types.h`, `ipc_sync.h`, `zephyr_objects.h` — plus
`recon/symbols/g1_compat_types.h` are included by **no** file in the compiled
set (verified by `grep -rln` over `recon/symbolized` and `recon/application`:
zero hits). They are listed in `AGENTS.md` as project structure. They are not
compiled. Reported, not acted on — deleting files is not this pipeline's job.

---

## 2. The manifest invalidation, handled honestly rather than special-cased

Stage 02 declined this fix specifically because *"changing the input set changes
the file list for stages 00 and 01 as well, invalidating two landed manifests
and every measurement in Stage 01's report."* That is exactly what happened, and
the response was to **regenerate all three stages and diff the manifests**, not
to special-case the new files out of the older stages.

```sh
$V recon/refactor/driver.py materialize 0    # 2,625 files, 2,567 parity rows
$V recon/refactor/driver.py materialize 1    # 2,625 files, 2,567 parity rows
$V recon/refactor/driver.py materialize 2    # 2,625 files, 2,567 parity rows
```

### 2.1 Manifest diff, stage by stage

Two causes are superimposed and are separated below: **(i)** my `input_set`
fix (+6 files, identical in all three stages), and **(ii)** the parity agent's
commit `5337623a`, which moved 81 inputs.

| | stage 00 | stage 01 | stage 02 |
|---|---:|---:|---:|
| `file_count` | 2,619 → **2,625** | 2,619 → **2,625** | 2,619 → **2,625** |
| files **added** | 6 | 6 | 6 |
| files **removed** | 0 | 0 | 0 |
| same-path content changed | **81** | **81** | **80** |

The 6 added files are the same 6 in every stage — §1.3's table. **No file was
removed from any manifest**, so the fix is purely additive: every measurement in
the Stage 01 and Stage 02 reports that was taken over the 2,619 files still
refers to those same 2,619 files, now accompanied by 6 more.

`driver.py check-addresses`: **0↔1 identical, 1↔2 identical, 2,567 addresses on
every side, 0 gained, 0 lost.** Unchanged from the R7 gate record's 2,567 —
so the 81 moved inputs are body edits, not function additions or withdrawals.
`test_guard.py` / whole refactor suite: **7 / 7 PASS.**

### 2.2 What moved in the transformation output, and which cause owns it

| statistic | R7 gate record | **this pass** | owner |
|---|---:|---:|---|
| stage 01 candidates accepted / quarantined | 100 / — | 100 / 1,934 | — |
| stage 01 `sites_inlined` | 178 | **192** | (ii) parity agent |
| stage 01 `files_rewritten` | — | 43 (46 changed) | (ii) |
| A volatile spelling: sites rewritten | 3,116 | 3,116 | — |
| A `total_accessor_sites_seen` | 6,078 | **6,085** | (ii) |
| A distinct spellings before → after | 84 → 52 | 84 → 52 | — |
| B `G1_NORETURN_CALL` sites | 45 | 45 | — |
| C `G1_LOG_ROUTE` pairs seen | 409 | **411** | (ii) |
| C sites rewritten / files | 266 / 127 | **367 / 160** | (ii) |
| C refused: else branch dropped ALL args | **80** | **0** | (ii) — *fixed upstream* |
| C refused: argument count differs | 55 | **38** | (ii) |
| C refused: same arity, different text | 8 | **6** | (ii) |
| D `G1_ASSERT_FAIL` sites / files | 135 / 89 | **139 / 92** | (ii) |
| D refused: print half has zero arguments | 4 | **0** | (ii) — *fixed upstream* |
| E files converted | 1 | **47** | (i) **and** (ii) |
| E declarations withdrawn | 2 | **92** | (i) and (ii) |
| E files quarantined | 45 | **0** | (ii) — *fixed upstream* |
| E zero-argument sites found | 183 | **0** | (ii) — *fixed upstream* |
| `header_include_sites` | 241 | **277** | (i) and (ii) |
| latent defects recorded | 192 | **44** | (ii) |

**This is the clearest possible confirmation that the Stage 02 defect harvest
was real and was acted on.** Every quarantine class Stage 02 opened has gone to
zero: the 80 "else branch dropped ALL arguments" log routes, the 4
zero-argument assert expansions, the 45 files with zero-argument calls to a
variadic log entry point, all 183 of those call sites. Stage 02 quarantined
those rather than transform them; the parity agent fixed the underlying
reconstructions in the canonical trees; Stage 02's transformer, re-run
unchanged, now transforms 101 more log routes and 4 more assert pairs, and
converts 47 files instead of 1.

`latent_defects_found` falling 192 → **44** is the same story read from the
other end. The residue is 38 argument-count disagreements + 6 same-arity
disagreements = 44, exactly the two C classes that remain.

One number in the E row is mine, not the parity agent's: of the 47 files
converted, `ble_process_put_common.h` is converted **only because of the
`input_set` fix**. The other 46 became convertible when their zero-argument call
sites were repaired upstream.

### 2.3 A second input-set extension, made in the same pass and for the same reason

The move batch (§4) rewrites file paths, and **two build artifacts name sources
by path**. C6 requires a structural stage to own them in the same transaction,
so `input_set.py` gained a `build_machinery` category alongside `pin_artifacts`:

```
recon/generated/app_retained_sources.cmake
recon/generated/net_retained_sources.cmake
recon/application/app/CMakeLists.txt
recon/application/net/CMakeLists.txt
```

```
transformable: 2,625  ->  2,629      (+4, total +10 against the R7 record's 2,619)
```

Same handling: all three landed stages regenerated, **0 files removed**,
`check-addresses 1↔2` still identical at 2,567.

The app `CMakeLists.txt` is in that list for one specific reason, and it is the
sharpest edge in the whole stage:

```cmake
set_source_files_properties(
  "${CMAKE_CURRENT_LIST_DIR}/../../symbolized/app/discovery_callback.c"
  PROPERTIES COMPILE_OPTIONS "-std=gnu99")
```

`discovery_callback.c` carries a `register ... asm("r9")` body and needs GNU
C99. **CMake does not error when a `set_source_files_properties` path stops
existing** — the property silently applies to nothing, and the TU then fails
under strict C99. A move batch that did not own this file would fail in a way
that looks like a source defect. It is rewritten by the same transformer, in
the same transaction, and the manifest records the count (`1`).

---

## 3. A structural fix to the driver, forced by a compile failure

Sub-batch A's **first** build attempt failed, with 2 errors:

```
.../app/ble/spec_ble_command_hook.c:129:10: fatal error:
      ../../../headers/g1_dedupe.h: No such file or directory
.../app/sensors/power/fuel_gauge_update.c:42:10: fatal error:
      ../../../../headers/g1_dedupe.h: No such file or directory
```

Under R4 a compile failure in a stage tree is proof the transformer is wrong.
Triage: **bucket (a), and the bug was in the driver, not in my transformer.**

`recon/headers/g1_dedupe.h` is *generated* by Stage 02. It is deliberately not
in Stage 02's `MANIFEST["files"]` — staleness would otherwise hunt for a source
that never existed. But `driver.materialize` builds stage N's file list from
`prev_man["files"]`, so a generated artifact of stage N−1 was invisible to
stage N and simply did not exist in its tree. Stage 02 never noticed because
its own tree contained the header it had just written; the defect only appears
at the **third** stage in a chain, which is this one.

Fix, in `driver.py` and therefore permanent for every future stage: after the
skeleton is built, any **real** file in the previous stage's tree that its
manifest does not list is by definition that stage's generated artifact, and is
copied forward verbatim. The manifest records it:

```json
"inherited_generated_outputs": ["recon/headers/g1_dedupe.h"]     // stage 03
"inherited_generated_outputs": []                                 // stages 01, 02
```

Regenerated, rebuilt: **exit 0, 0 errors.** No hand-edit anywhere.

---

## 4. Sub-batch A — module directory materialisation

### 4.1 Scope decision: app core only, and why

**Net is not restructured.** Measured reasons, not preference:

* it is **frozen** at 225,581 B with ~1.7 kB of real device headroom;
* it is ~100 % stock — `recon/ownership/net_function_ownership.json` records
  452/452 `sdk_library` and *zero* product-owned net functions needing readable
  C, so there is no module structure to recover. The plan's own §7 says
  `net/src/stock/` is "the honest answer";
* its CMakeLists carries a **path-keyed**
  `list(FILTER G1_RETAINED_SOURCES EXCLUDE REGEX "/FUN_0102(a4c8|…)\.c$")`
  over 17 files, plus 71 explicitly-named canonical sources.

Consequence worth stating plainly: **the net image is byte-identical to Stage
02's by construction**, because not one net input changed.

### 4.2 What moved, and where

1,615 retained app sources + 6 fragments = **1,621 files moved**, into 22
directories under `recon/symbolized/app/`:

| directory | files | | directory | files |
|---|---:|---|---|---:|
| `lib/` | 482 | | `sensors/power/` | 42 |
| `unsorted/` | **177** | | `sensors/input/` | 30 |
| `core/` | 142 | | `ui/dashboard/` | 26 |
| `audio/` | 137 | | `esb/` | 24 |
| `ble/` | 105 | | `sensors/imu/` | 22 |
| `notify/` | 99 | | `analytics/` | 14 |
| `display/` | 89 | | `ui/onboarding/` | 13 |
| `storage/` | 86 | | `ui/quicknote/` | 11 |
| `gui/` | 57 | | `ui/translate/` | 8 |
| `ipc/` | 47 | | `ui/navigation/` | 5 |
| | | | `common/` | 3 |
| | | | `ui/teleprompt/` | 2 |

Directory names come from `refactor_module_map.json`'s own `directory_map` with
its `app/src/` prefix stripped — the plan's names, not invented ones.

**A correction to `refactor_module_map.json`, found by running it.**
`directory_map` has **no entry for `lib`**, although `summary.app.module_sizes`
reports `lib: 482` — the single largest group. The first materialisation
therefore dropped all 482 recovered-stock files into the quarantine directory,
which would have been a plain lie about what they are. The transformer now
supplies `lib -> lib`, which *is* the target layout named in
`production_refactor_plan.md` §2. Fixed in the transformer and regenerated; no
hand-edit.

`unsorted/` holds **177** files and is deliberately ugly: 145 `L5-residual`
rows the plan's classifier could not place, plus **32 files with no row in the
module map at all**. Those 32 are the staleness the brief warned about — the
map was generated at commit `6aa09be0` and the tree has moved since. They are
enumerated in the MANIFEST under `unmapped_to_quarantine`:
`panel_resume`, `panel_suspend`, `panel_set_brightness_level`,
`panel_render_screen_dispatch`, `projector_clear_canvas`,
`projector_flush_canvas`, 7 `screen_render_ret0_*`, `imu_fusion_{init,resume,suspend}`,
`set_imu_thread_delay`, 3 `local_*_ipc_service_recv`,
`register_ipc_service_recv_callback`, 6 `wlc{cap,stai}_record_*`,
`nfc_link_{delay_msec,ops_noop}`, `coredep_delay_cycles`,
`misc_dev_api_write_op12`, `FUN_0007c86c`. Several are obviously placeable by
name (the `panel_*`/`projector_*`/`screen_render_*` group is `display`, the
`imu_fusion_*` group is `sensors/imu`, the `*_ipc_service_recv` group is `ipc`)
— **and I did not place them**, because doing so by eye is exactly the
invention R5 forbids. They belong in the map, regenerated from evidence.

The 6 include fragments (`ble_process_put_common.h` and 5
`ble_process_put_ops_*.inc`) follow the module of the files that include them.
Measured: every one is reached from exactly one module (`ble`), so this is a
decision, not a heuristic; `ambiguous_fragments` is **empty**. Because they
move together, their relative includes of each other need no rewriting at all.

**708 `#include` depth rewrites across 464 files** (`../../headers/…` →
`../../../headers/…`, or four levels for `ui/*` and `sensors/*`). No other
include shape needed touching: `g1_app_symbols.h` (2,147 sites) is resolved from
the `-I` path and is unaffected by a move.

`app_retained_sources.cmake`: **1,615 paths rewritten, order preserved
exactly.** `CMakeLists.txt`: **1 path rewritten** (`discovery_callback.c`).

### 4.3 Gate — the byte-identical prediction held

Sub-batch A predicted a byte-identical image, on the grounds that link order
follows `G1_RETAINED_SOURCES` order (preserved exactly), and that nothing else
about a source's identity reaches the image — **`__FILE__` appears in 0 files
across all of `recon/symbolized`** (measured), and object paths live only in
debug info, which `zephyr.bin` does not carry.

| gate | result |
|---|---|
| app build | **exit 0, 0 errors**, first try after the driver fix |
| **app `zephyr.bin` vs Stage 02** | **`cmp` SILENT — BYTE-IDENTICAL** |
| net | **not rebuilt: not one net input changed; byte-identical by construction** |
| compiler warnings | **2,005 vs 2,005 — Δ 0** |
| app FLASH | 956,248 B / 982,528 B = **97.33 %** (Δ 0 vs Stage 02, at the pre-regeneration inputs) |
| app `.text` / `.data` / `.bss` | 951,288 / 4,951 / 249,251 — Δ 0 (pre-regeneration inputs) |
| app RAM | 253,765 B = 56.32 % — Δ 0 |
| `driver.py check-addresses 2 3` | **identical, 2,567 both sides, 0 gained, 0 lost** |

**A byte-identical image means sub-batch A's observable side-effect equivalence
is Stage 02's, by construction rather than by argument** — the same reasoning
Stage 02 used, and it is stronger than a behavioural capture. Every bus
transaction, every volatile access, every framebuffer byte is produced by the
same instruction stream. 1,621 files moved and the firmware did not notice.

---

## 5. Sub-batch B — module header materialisation

A directory of files is not a module. What makes it one is that the module has
**one place** where each symbol is declared. Today the same callee is re-typed
in every file that calls it — `g1_app_symbols.h` is included 2,147 times but
carries globals, not function prototypes, so every `extern` for a *function*
is per-file.

Sub-batch B generates `recon/symbolized/app/<module>/g1_<module>.h` holding
every `extern` declaration that the module's files agree on, deletes the
per-file copies, and includes the header instead.

### 5.1 Agreement is defined as *type* identity, not text identity

Grouping on raw text yielded only 100 hoists out of 714 candidate symbols,
because the corpus spells the same type many ways. Three equivalences are
folded, each provable and each already used by Stage 02 sub-batch A:

1. whitespace is not part of a type;
2. `unsigned` ≡ `unsigned int`, `signed` ≡ `signed int` (C11 6.7.2);
3. a parameter **name** is not part of a function type (C11 6.7.6.3 — prototype
   identifiers have no linkage and leave scope at the end of the declarator).

Nothing else. `int` is never merged with `unsigned int`; `uint32_t` is never
resolved to its underlying type; `__attribute__((noreturn))` keeps a
declaration **distinct** rather than being discarded. The header emits the
*most common source spelling* of the agreed group, so it reads like the code it
replaces rather than like a canonicaliser's output — a free choice, because
every spelling in a group denotes the same type by construction.

### 5.2 Measured result

| | |
|---|---:|
| module headers generated | **16** |
| declarations hoisted | **99** |
| per-file copies withdrawn | **217** |
| symbols **refused** because the module disagrees about their type | **1,014** |
| files skipped for carrying a multi-declaration line | 16 |

Per module, `declarations_hoisted` / `files`:

```
notify        10/99     ui/onboarding 10/13    lib            9/482   storage    9/86
display        8/89     sensors/power  8/42    unsorted       8/177   ble        7/104
core           7/142    audio          6/137   ipc            5/47    sensors/input 4/30
ui/quicknote   4/11     analytics      2/14    esb            1/24    sensors/imu   1/22
```

Six directories produced **no** header at all: `gui` (57 files), `common` (3),
`ui/dashboard` (26), `ui/navigation` (5), `ui/teleprompt` (2),
`ui/translate` (8). For `gui` and `ui/dashboard` that is a result, not an
absence — those modules have plenty of shared callees and agree on **none** of
them.

**99 is a small number and I am not going to dress it up.** The reason it is
small is the finding: **1,014 symbol/module pairs — 818 distinct symbols —
could not be hoisted because the module's own files disagree about the
symbol's type.** A module that cannot agree with itself about a callee's
signature is not yet a module, and consolidating its declarations by fiat would
have meant choosing a winner, i.e. inventing evidence about a shipped ABI.

### 5.3 Three transformer bugs, all found by the compiler, all fixed in the transformer

Sub-batch B needed **three** rounds. Every failure is reported; the iteration
history is the finding (README C4).

| round | compiler said | bucket | fix |
|---|---|---|---|
| 1 | `core/g1_core.h:31: error: unknown type name 'int64_t'` (×2) | **(a)** | a header must be self-contained; the generated header now includes `<stdint.h>` / `<stddef.h>`, both type-only |
| 2 | `sensors/power/mark_master_or_low_battery_flag.c:16: error: conflicting types … have 'unsigned int(void)'`, previous declaration `void(void)` | **(b) payload, (a) mechanism** | see §5.4 |
| 3 | `lib/net_buf_pool_get_727ac.c:30: error: conflicting types for 'assert_post_action'; have 'void(unsigned int, unsigned int)'`, previous `void(uintptr_t, uint32_t)` | **(a)** | see §5.5 |
| 4 | **exit 0, 0 errors** | — | — |

### 5.4 Round 2 — the compiler checking callers against a definition for the first time

`sensors/power` contains both the callers and the definition of
`mark_master_or_low_battery_flag`. Two callers declare it `void (void)`; its own
reconstructed body at `FUN_0002efc0 @ 0x0002efc0` is `unsigned int (void)`.
Nothing had ever compared them, because until this stage they were never in the
same translation unit. A module header puts them there.

The transformer fix is mechanical and is the right one: extract every top-level
**definition** in the module, canonicalise it as a declaration, and refuse to
hoist any symbol whose callers disagree with it — recording the disagreement
instead. This is the same refusal discipline Stage 02 used for the
zero-argument print half.

That check turned 568 refusals into **1,014**, and the new class is the
valuable one:

| refusal class | count |
|---|---:|
| **`declaration_disagrees_with_definition`** | **446** |
| `arity_differs` (between callers) | 274 |
| `return_type_differs` (between callers) | 175 |
| `parameter_type_differs` (between callers) | 119 |

**All 446 of the definition disagreements resolve to a definition found in
`<symbol>.c`** — i.e. the transformer's definition scanner did not fire on
anything but the file that owns the symbol, which is the accuracy check for
that scanner. Of the 446:

* **175 disagree about ARITY** — the callers' prototype and the function's own
  body do not take the same number of arguments;
* **48 of those drop *every* argument**: callers declare `f(void)` for a body
  that takes one or more.

Worked example, both files in `analytics/`, both naming `FUN_0007db50 @
0x0007db50`:

```c
/* accumulate_burial_point_duration.c -- the definition */
void accumulate_burial_point_duration(int param_1, int param_2, int param_3, int param_4)

/* exit_dashboard_burial_point.c -- the caller */
extern unsigned int accumulate_burial_point_duration(void);
...
        (void)accumulate_burial_point_duration();
```

Four register arguments the shipped call sets up, and the caller passes none.
This is **exactly** the class `code_dedupe_plan.json`'s `hard_rule` describes
and the Unicorn differential harness is structurally blind to: the harness
models callees as order-keyed oracles and compares the *callee's* side effects,
so it never observes whether the caller loaded r0–r3.

Other confirmed shapes: `flash_settings_read` declared 3-argument in two files
and 5-argument in a third *within one module*; `get_device_info` (the plan's
181-in-edge hub) declared `int(void)`, `uint8_t *(void)`, `uintptr_t(void)` and
`unsigned int(void)` in `analytics` alone; `qspi_nor_write` declared
`unsigned int(void)` against a body taking four arguments.

These are **not** transformed and **not** fixed here. R1 forbids this pipeline
writing the canonical trees, where the fix belongs. They are handed over in
`recon/refactor/stage_03_module_structure/DEFECTS.json` with the module, the
symbol, every distinct canonical type with its occurrence count, the defining
file, and the file list.

### 5.5 Round 3 — a parser bug worth naming

`extern __attribute__((noreturn)) void assert_post_action(uintptr_t, uint32_t);`
was being filed under the symbol **`__attribute__`**, because the symbol
extractor took the first identifier followed by `(`. The declaration was
therefore hoisted under a nonsense name, while the file's own, differently
typed `extern void assert_post_action(unsigned, unsigned);` was left in place —
and the two met in the same TU. Attributes are now lifted out before parsing
and appended to the canonical form, so a `noreturn` declaration stays
*distinct* from a non-`noreturn` one rather than colliding with it.

This one is worth naming because it is the failure mode C4 predicts: a
transformer bug that produces a *plausible-looking* wrong output, caught only
because an authoritative declaration refused to compile.

### 5.6 What B refuses structurally, beyond the type disagreements

* a **multi-declaration line** (several `extern`s separated by `;` on one
  source line) is skipped whole — splitting it would be a rewrite, and this
  batch only moves declarations it can read verbatim;
* a **function-pointer declarator** (`(*fp)(...)`) is never canonicalised, so
  never hoisted;
* a symbol with **only one** declaring file in the module is not hoisted —
  there is nothing to consolidate.

---

## 6. Gate ladder — measured

Built from the stage trees with the repository's own entry point. **No build
file, linker script or `tools/` module was edited outside the stage tree.**

```sh
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s3-base-app
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh net /private/tmp/g1-s3-base-net -- \
      -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s3-app
```

| gate | Stage 02 (baseline, rebuilt at these inputs) | **Stage 03 (A+B)** |
|---|---|---|
| app build | exit 0 | **exit 0, 0 errors** (round 4 of the transformer) |
| **app `zephyr.bin`** | — | **BYTE-IDENTICAL to Stage 02 — `cmp` silent** |
| **net `zephyr.bin`** | exit 0 | **not rebuilt — 0 of 970 net-related manifest entries changed; byte-identical by construction** |
| app FLASH | 956,356 B / 982,528 B = 97.34 % | **956,356 B = 97.34 % — Δ 0 B**, 26,172 B headroom |
| app `.text` / `.data` / `.bss` | 951,392 / 4,951 / 249,251 | **Δ 0 / Δ 0 / Δ 0** |
| app RAM | 253,765 B = 56.32 % | **Δ 0 B** |
| ELF symbol table (`nm -n`, every entry) | — | **0 diff lines** |
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| `--allow-multiple-definition` / `--defsym` | 0 | **0** |
| compiler warnings | 2,005 | **2,035 (Δ +30)** — see below |
| compiler errors | 0 | **0** |
| **per-object comparison** (`--strip-debug --remove-section=.comment`) | — | **2,836 / 2,837 byte-identical**; the 1 is `zephyr/lib/posix/uname.c.obj`, the known build-to-build stock churn unit. 215 basenames were ambiguous on one side and not compared. |
| `.rodata` vs `app_update.bin` | 1,325 match / 14 mismatch (Stage 02) | **inherited unchanged — the image is byte-identical, so every function of the image is** |
| `check_ram_pin_collisions.py` app | — | **627 bound OK, 0 escaping, 0 unknown inside a live object** |
| `check_ram_pin_collisions.py --core net` | — | **170 bound OK, 0 / 0** |
| `check_net_raw_literals.py` | — | **983 TUs, 0 failed to preprocess, 0 / 0 / 0 / 0 / 0** |
| `verify_net_stock_data_window.py` | — | **PROVEN** — 256/349 words equal, 93 differing all flash pointers, **0 differing for any other reason**, 0 non-stock input sections |
| `check_thread_create_stack_args.py --trials 120` | — | **10 / 10 PASS, EXIT 0** |
| `gen_retained_sources.py --check` | — | **"retained source lists are current"** |
| `driver.py check-addresses 2 3` | — | **identical, 2,567 both sides, 0 gained, 0 lost** |
| whole `recon/refactor` suite | 7 / 7 | **25 / 25 PASS** — 18 new tests added by this stage (`test_input_set.py`) |
| idempotence (`materialize 3` twice) | — | MANIFEST `36b47f94…` → `36b47f94…`; whole-tree hash `11733e5c…` → `11733e5c…` — **byte-identical** |

**The +30 warnings, measured rather than assumed.** Diffing the two builds'
warnings bucketed by `-W` flag gives **exactly one** differing bucket:

```
-Wbuiltin-declaration-mismatch    204  ->  234      (+30)
```

Every other bucket is identical, and **no new warning kind appears.** The cause
is mechanical: a hoisted `extern int memcpy();`-style declaration is now seen by
every file in its module rather than only by the file that wrote it, so GCC
reports the same pre-existing mismatch more times. The image is byte-identical,
so nothing the compiler newly complains about changed what it emitted. This is
a diagnostic-**visibility** change, and it is the module header doing exactly
what a module header is for: it made an existing disagreement louder.

### 6.1 What the byte-identical image proves, and what it does not

Stage 03 moved **1,621 files**, rewrote **708 include paths**, regenerated the
generated source list and the app `CMakeLists.txt`, generated **16 module
headers**, hoisted **99 declarations** and withdrew **217 per-file copies** —
and both cores' `zephyr.bin` are byte-identical to Stage 02's.

Under R7 that is the strongest available result: side-effect equivalence is
Stage 02's **by construction, not by argument**. Every bus transaction, every
volatile access, every ordering, every framebuffer byte is produced by the same
instruction stream. No behavioural capture could add information to that.

What it does **not** prove is Stage 02's own equivalence with the shipped
binaries at *these* inputs. See §8.

---

## 7. R8 — which of these transformations could reorder or coalesce a volatile access

Answering directly, per sub-batch:

| sub-batch | R8 exposure | what makes it safe |
|---|---|---|
| **A** module directory materialisation | **none** | it never edits inside a function body. The only in-file edit is `#include` path depth, which is outside every function and changes no token the compiler sees after preprocessing. The list order that determines section layout is preserved exactly, and it is preserved *deliberately* — a sorted or regrouped `G1_RETAINED_SOURCES` would change `.text` layout without changing one instruction. |
| **B** module header materialisation | **none, given the type-identity requirement** | a declaration emits no instruction and cannot reorder an access. The only way B could change codegen is by replacing a local declaration with a *differently typed* one — which is refused: hoisting requires every occurrence in the module, **and the definition where the module owns one**, to denote the same C type. That makes the dangerous case unrepresentable rather than merely unlikely. |

**And the argument is closed empirically, exactly as Stage 02's was:** both
cores' `zephyr.bin` are byte-identical to Stage 02's and 2,836 of 2,837
comparable objects are byte-identical. **A transformation that emits the same
instruction stream cannot have added, removed or reordered a bus transaction.**

The R8 table for the stages ahead is unchanged from Stage 02 §7, with one
addition: a **cohesive-TU merge** (many functions per `.c`, §9 item 1) is the
first transformation in this pipeline that would *not* be able to make this
claim, because merging changes archive member granularity and therefore section
layout. It needs the oracle, not a `cmp`.

---

## 8. What I did NOT do, and everything quarantined, with measured reasons

1. **I did not run the behavioural oracle, and I do not claim R7 acceptance
   from one.** Renode is owned by the concurrent agent and the brief forbids
   running it. What I claim instead is the same thing Stage 02 claimed, and it
   is stronger for this stage: **both cores' `zephyr.bin` are byte-identical to
   Stage 02's**, so Stage 03's observable behaviour *is* Stage 02's, instruction
   for instruction.

   **The outstanding gate is not mine — it is Stage 02's, at these inputs.**
   The R7 gate record was taken at HEAD `a2f3303d`. HEAD is now `5337623a`,
   which landed the 498-argument-defect harvest and moved 81 pipeline inputs,
   plus one further working-tree fix during this pass. Those are *semantic*
   changes to the reconstruction, made by the parity agent, and they are not
   covered by the R7 record. **An oracle run against the current in-tree build
   is required before Stage 03 can be considered proven** — but when it is run,
   Stage 03 needs no separate capture, because its image is byte-identical to
   the Stage 02 image that would be captured. The four framebuffer hashes to
   match remain `19b1f24a…` / `0c5cc90b…` (dashboard) and `b26c73b3…` /
   `1d617c65…` (navigation); RAM layout diffs to 0 lines and `.text` moved 0 B,
   so the probe addresses are unchanged.

2. **I did not restructure the net core** (§4.1). Frozen, ~100 % stock, no
   module structure to recover, and a path-keyed CMake filter that would have to
   be reasoned about for no benefit. Consequence: net's image is byte-identical
   by construction.

3. **I did not merge functions into cohesive translation units.** This is the
   most visible thing the brief permits and I did not do it; the reason is
   measured, not squeamish. §5 found **1,014 symbol/module pairs where a
   module's own files disagree about a symbol's type**, 446 of them disagreeing
   with the symbol's *definition*. Concatenating those files into one TU makes
   every one of those disagreements a hard compile error simultaneously —
   several hundred failures at once, in a batch whose failures could not then be
   attributed. Under R4 each would have to be triaged, and under R1 the fix
   belongs in the canonical trees, which I may not write. **The declaration
   disagreements are the blocking prerequisite for a TU merge, and finding them
   is what this stage did.** Sequencing the merge after they are repaired is the
   whole point of "most-mechanical first".

4. **I did not fix any of the 1,014 declaration disagreements.** R1: the fix is
   in `recon/{app,net}/src`, which this pipeline may never write. They are
   handed over in `DEFECTS.json` with everything a fixer needs (module, symbol,
   every canonical type with occurrence count, defining file, file list).

5. **I did not place the 32 files that have no row in
   `refactor_module_map.json`.** They are in `unsorted/`. Several are obviously
   placeable by name — but placing them by eye is invention (R5). They belong in
   a regenerated map.

6. **I did not re-derive the module map.** The brief is right that plan counts
   go stale, and two staleness facts were measured here: `directory_map` has no
   `lib` entry despite `module_sizes` reporting 482 (fixed in the transformer,
   §4.2), and 32 live compilable sources have no row at all. The map's *class*
   assignments (L4 graph 320 rows, L5 residual 145) were **not** re-derived —
   doing so needs `tools/ghidra_refgraph.py` re-run and `lib_sigmatch2.py`
   against the pinned NCS build, which is a separate evidence task.

7. **I did not introduce struct types.** `production_refactor_plan.md` budgets
   that as Batch 7 and warns it is the one batch that can grow the image; it also
   requires `_Static_assert(offsetof/sizeof)` per struct and a `cfg_verify` pass
   per touched function. It cannot ride along with a file move.

8. **I did not rename anything.** App naming is already done (4 `FUN_` files of
   1,615 retained). The remaining naming work is net — 747 of 923 — and net is
   out of scope. There was no app renaming worth doing.

9. **I did not touch any canonical tree, `tools/`, `recon/emulator/**`,
   `armemul`, any live build file, any linker script, `recon/board/**`, or the
   live `recon/headers/`.** Structurally impossible through
   `guard.check_write`; `test_guard.py` 7/7 proves both refusals. The 16
   generated module headers and the rewritten `CMakeLists.txt` /
   `app_retained_sources.cmake` exist **only inside the stage tree**.

10. **I did not regenerate the diagnostic stage 99**, and it should now be
    retired rather than repaired. `driver.py status` reports it stale (94
    inputs moved). Its purpose was to force Stage 02's sub-batch E to withdraw
    the local log externs in the files E quarantined, so the compiler would
    count the zero-argument call sites. **Stage 02 now quarantines 0 files and
    finds 0 zero-argument sites** — the parity agent fixed all 183 — so the
    probe has nothing left to measure. Its 275-error measurement stands as the
    historical record that justified the fix. I left the stage registered rather
    than deleting it, because deleting the evidence of a completed measurement
    is not an improvement; but it should not be re-materialised.

11. **I did not commit anything.**

### 8.1 Quarantine, in full

Not one entry was hand-edited.

| sub-batch | reason | count |
|---|---|---:|
| A | file has no row in `refactor_module_map.json` → `unsorted/` | **32** |
| A | map row is `needs_judgement` (L5 residual) → `unsorted/` | 145 |
| A | fragment reachable from more than one module | **0** (measured) |
| B | module's files disagree with the symbol's own **definition** | **446** |
| B | callers disagree about **arity** | 274 |
| B | callers disagree about **return type** | 175 |
| B | callers disagree about **parameter type** | 119 |
| B | declaration is on a multi-declaration source line | 16 files |
| B | function-pointer declarator — never canonicalised | — |
| B | only one declaring file in the module — nothing to consolidate | — |
| — | net core, entirely | 952 `.c` + 71 CMake-named sources |

---

## 9. Is this production-grade, or merely rearranged?

Asked directly by the brief, so answered directly.

**What a maintainer would genuinely recognise.** The app tree now has a
navigable shape: `display/`, `gui/`, `ble/`, `esb/`, `ipc/`, `audio/`,
`storage/`, `notify/`, `sensors/{imu,power,input}/`, `ui/{dashboard,navigation,
teleprompt,translate,quicknote,onboarding}/`, `analytics/`, `core/`, `common/`,
with recovered stock quarantined in `lib/` and unplaced code in an
honestly-named `unsorted/`. The build list is generated from it and the
`-std=gnu99` coupling travels with its file. Sixteen modules have a header. A
new reader can find the display code.

**What is honestly still rearrangement.** Three things:

* **the files are still one function each.** 1,621 files for ~1,100 product
  functions is not what a maintainer expects from `display/`. The merge is the
  next batch and §8 item 3 says exactly why it could not be this one;
* **the module headers are thin.** 99 declarations over 16 headers is roughly
  six declarations per module. A real module header declares the module's own
  public API; these declare its *agreed-upon callees*. The reason they are thin
  is a genuine finding, not modesty — 1,014 refusals;
* **`unsorted/` holds 177 files, 10.9 % of the app tree.** That is the plan's
  own L5 residual plus map staleness, and it is displayed rather than hidden.

**The most valuable thing this stage produced is not the directory tree.** It is
the 1,014-entry disagreement census, and in particular the 446 cases where a
module's callers disagree with the callee's own reconstructed definition, 175 of
those about arity and 48 dropping every argument. Nothing in the pipeline could
see those before, for a precise reason: they only become visible when the caller
and the callee are put in the same translation unit, and no stage before this one
put them there. Stage 02 predicted this bucket-(b) mechanism ("the compiler finds
what the parity harness structurally cannot see"); Stage 03 is where it paid out
against real ABI shapes rather than log prototypes.

So: **the structure is real and the image did not move a byte — but the tree is
one batch short of what the owner asked for, and this stage found the reason
that batch could not run yet.**

---

## 10. Concurrency, idempotence, footprint, reproduction

**Concurrency.** It happened, as the brief predicted. `driver.py status`
reported stage 00 **stale by 1 input** partway through this pass —
`recon/symbolized/app/ui_navigation_task.c`, the parity agent's G-3 navigation
work (alongside `recon/app/src/FUN_0003f410.c`). **All four stages were
regenerated, never patched**, and every transformation statistic came back
**identical** (stage 01: 100/1,934/192; stage 02: 3,116 / 45 / 367 / 139 / 47;
stage 03: 1,621 moved / 16 headers / 99 hoisted / 1,014 refused),
`check-addresses 2 3` still identical at 2,567.

**Both builds were then re-run at the regenerated inputs, and the result is
worth stating exactly**, because it is the only interesting thing the
concurrency did:

| | pre-regeneration | post-regeneration |
|---|---:|---:|
| Stage 02 baseline app `zephyr.bin` | — | **MOVED** |
| Stage 02 baseline FLASH | 956,248 B (97.33 %) | **956,356 B (97.34 %)** — Δ **+108 B** |
| Stage 02 baseline `.text` | 951,288 | **951,392** — Δ +104 B |
| **Stage 03 vs Stage 02, same inputs** | `cmp` silent | **`cmp` silent** |
| Stage 03 errors / warnings | 0 / 2,035 | **0 / 2,035** |
| `nm -u` / dup globals / symtab diff | 0 / 0 / 0 | **0 / 0 / 0** |
| `check_ram_pin_collisions` app | 627 / 0 / 0 | **627 / 0 / 0** |

The parity agent's `ui_navigation_task.c` fix grew the app image by 108 B — a
real semantic change, theirs, not this stage's. **Stage 03's own delta is 0 B
against whichever baseline it is measured on**, which is the property that
matters and the reason regenerating rather than patching is the contract. All
the §6 figures are the post-regeneration ones except the two explicitly marked
"pre-regeneration inputs".

**Idempotence, measured.** `materialize 3` twice, no other change:

```
MANIFEST.json sha256        36b47f94adb94f14…  ->  36b47f94adb94f14…
sha256 over the whole tree  11733e5c08c3f7fc…  ->  11733e5c08c3f7fc…
```

**Footprint.** Everything this pass wrote:

```
 M recon/refactor/input_set.py                       (.h closure + build_machinery)
 M recon/refactor/driver.py                          (stage 3 registry; inherited generated outputs)
 M recon/refactor/stage_0{0,1,2}_*/MANIFEST.json     (regenerated: +10 files, 81 inputs moved upstream)
 M recon/refactor/stage_01_literal_inline/QUARANTINE.json
 M recon/refactor/stage_02_block_dedupe/{DEFECTS,QUARANTINE}.json
?? recon/refactor/transforms/t03_module_structure.py (the transformer)
?? recon/refactor/test_input_set.py                  (18 new tests: include closure + canonicaliser)
 M recon/refactor/README.md                          (C2 rewritten; stage table 03/03b/03c)
?? recon/refactor/stage_03_module_structure/         (MANIFEST/PARITY_MAP/DEFECTS + tree/)
?? recon/analysis/staged_refactor_stage03.md         (this file)
```

`recon/refactor/.gitignore` already excludes `stage_*/tree/`. **No file outside
`recon/refactor/` and this report was written. Nothing committed.**

Everything else dirty in `git status` belongs to the concurrent parity agent.

### 10.1 Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py input-set            # 2,629 transformable, 36 quarantined-protected
$V recon/refactor/driver.py materialize 0
$V recon/refactor/driver.py materialize 1
$V recon/refactor/driver.py materialize 2
$V recon/refactor/driver.py materialize 3
$V recon/refactor/driver.py check-addresses 2 3  # identical, 2,567
$V -m unittest discover -s recon/refactor -p 'test_*.py'    # 7/7

./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   app /private/tmp/g1-s2-app
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s3-app
cmp /private/tmp/g1-s2-app/zephyr/zephyr.bin /private/tmp/g1-s3-app/zephyr/zephyr.bin   # SILENT

# sub-batch A alone (module move only, no module headers):
G1_STAGE03_MODULE_HEADERS=0 $V recon/refactor/driver.py materialize 3
```

### 10.2 The next batch, and what must land before it

1. **Repair the 1,014 declaration disagreements** in the canonical trees
   (`DEFECTS.json`), arity first: 175 caller/definition arity mismatches, 48 of
   which drop every argument. This is the same work the parity agent just did for
   the log entry points in `5337623a`, applied to ordinary product functions.
2. **Then** the cohesive-TU merge. It is the first pipeline transformation that
   cannot be gated on `cmp zephyr.bin` — merging changes archive member
   granularity and therefore section layout — so it needs the oracle per
   sub-batch, and it must not start while several hundred TUs would fail at once.
3. **Regenerate `refactor_module_map.json`** against the live tree: 32 missing
   rows, a missing `lib` entry in `directory_map`, and 465 rows (L4 320 + L5 145)
   whose evidence tier the plan itself marks unconfirmed.
4. **Run the oracle against the current in-tree build** (§8 item 1). The R7 gate
   record predates the 498-defect harvest; it is not evidence for these inputs.
