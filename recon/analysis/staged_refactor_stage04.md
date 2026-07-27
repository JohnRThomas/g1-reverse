# Stage 04 — the scoped cohesive-TU merge

**Written incrementally as the work ran. Nothing committed.**

Starting point of this pass:

```
HEAD          50929c5d  "Type-disagreement repair: 104 fixed, 255 provably-missing
                         args found, flash delta 0"
              (parents fa603c94, 8bd1b303 "P4 iter-41", dd671f22 "refactor Stage 03")
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)
```

**Ending point.** The concurrent parity agent landed `192349af` "P4 iter-42"
mid-pass, moving 4 inputs. All five stages were **regenerated, never patched**,
and both builds re-run; every figure in this report is the post-regeneration
measurement at HEAD `192349af`, and `driver.py status` reports stages 00–04 all
**current**. See §11.1.

---

## 1. First measurement: every plan number carried into this brief was stale

The brief warned that every plan-file count in this project has been stale at
least once. It was right again, and the correction is large enough to change
the shape of the stage.

`driver.py status` at the start of this pass:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **stale** | 2,403 | **226** |
| 01 literal_inline | current (rel. stage 00's tree) | 2,629 | 0 |
| 02 block_dedupe | current | 2,629 | 0 |
| 03 module_structure | current | 2,629 | 0 |
| 99 defect_probe | stale | 2,518 | 94 |

The 226 moved inputs are commit `50929c5d`'s type-disagreement repair. Stages
00 → 01 → 02 → 03 were **regenerated, never patched**, in zero transformer
rounds:

```
materialize 0   2,629 files, 2,567 parity rows
materialize 1   2,629 files, 2,567 parity rows, 100 candidates / 192 sites inlined
materialize 2   2,629 files, 2,567 parity rows, 3,116 / 45 / 367 / 139 / 47
materialize 3   2,629 files, 2,567 parity rows, 1,621 moved, 16 headers
```

**The number this stage is scoped by moved:**

| | Stage 03 report | **re-run at HEAD `50929c5d`** | Δ |
|---|---:|---:|---:|
| module headers generated | 16 | 16 | 0 |
| declarations **hoisted** | 99 | **138** | **+39** |
| per-file copies withdrawn | 217 | **293** | +76 |
| symbols **refused** (`DEFECTS.json`) | **1,014** | **902** | **−112** |

By class:

| class | Stage 03 | **now** |
|---|---:|---:|
| `declaration_disagrees_with_definition` | 446 | **372** |
| `arity_differs` | 274 | **256** |
| `return_type_differs` | 175 | **173** |
| `parameter_type_differs` | 119 | **101** |

The repair pass's own four-way split (`type_disagreement_repair.md` §8.1) said
104 FIXED. Measured against Stage 03's own agreement test re-run on the current
tree, the refusal count falls by **112**, and 39 more declarations became
hoistable. Those are the same event counted two ways and they agree to within
the noise of the eight upstream commits in between; I record the number I
measured rather than the number the document predicted.

**And the decisive measurement for this stage: NOT ONE of the 22 app modules
has zero disagreements.**

| module | files | DEFECTS entries | | module | files | DEFECTS entries |
|---|---:|---:|---|---|---:|---:|
| `lib/` | 482 | **296** | | `ipc/` | 47 | 23 |
| `core/` | 142 | 86 | | `sensors/input/` | 30 | 19 |
| `ble/` | 104 | 79 | | `ui/dashboard/` | 26 | 19 |
| `audio/` | 137 | 73 | | `ui/navigation/` | 5 | 19 |
| `notify/` | 99 | 56 | | `esb/` | 24 | 15 |
| `display/` | 89 | 50 | | `sensors/power/` | 42 | 14 |
| `storage/` | 86 | 44 | | `analytics/` | 14 | 9 |
| `gui/` | 57 | 39 | | `ui/onboarding/` | 13 | 9 |
| `unsorted/` | 177 | 29 | | `ui/translate/` | 8 | 8 |
| | | | | `sensors/imu/` | 22 | 7 |
| | | | | `ui/quicknote/` | 11 | 6 |
| | | | | `common/` | 3 | 1 |
| | | | | `ui/teleprompt/` | 2 | 1 |

So **"merge only the modules that are provably clean" selects the empty set.**
A scoped merge at *module* granularity is not available at these inputs. The
scope that IS available is finer — see §3.

*(Everything above is `driver.py status`, four `driver.py materialize` runs, and
`recon/refactor/stage_03_module_structure/DEFECTS.json` regenerated at HEAD
`50929c5d`.)*

### 1.1 Correction to the table above, made mid-run

The 902/16/138 figures are the ones the *unmodified* Stage 03 transformer
produced. Stage 03 then turned out **not to compile at these inputs** (§2), and
fixing that transformer changed its own harvest. The figures that stand for this
pass are:

| | Stage 03 report | first re-run | **after the §2 fix** |
|---|---:|---:|---:|
| module headers generated | 16 | 16 | **17** |
| declarations hoisted | 99 | 138 | **142** |
| `DEFECTS.json` entries | 1,014 | 902 | **833** |

with classes `declaration_disagrees_with_definition` **349**, `arity_differs`
**219**, `return_type_differs` **158**, `parameter_type_differs` **107**. Still
**no module with zero entries**: `lib/` 280, `core/` 81, `ble/` 71, `audio/` 63,
`notify/` 51, `display/` 50, `storage/` 42, `gui/` 34, `unsorted/` 29, `ipc/`
23, `sensors/input/` 19, `esb/` 15, `sensors/power/` 14, `ui/dashboard/` 14,
`analytics/` 9, `ui/onboarding/` 8, `ui/translate/` 8, `sensors/imu/` 7,
`ui/navigation/` 7, `ui/quicknote/` 6, `common/` 1, `ui/teleprompt/` 1.

---

## 2. Stage 03 stopped compiling, and the reason is a latent defect

The very first thing this pass built was the **baseline** — Stage 03's own tree,
regenerated at HEAD `50929c5d`. It failed:

```
core/check_work_mode.c:61:48: note: previous declaration of 'wchar_t'
        with type 'wchar_t' {aka 'short unsigned int'}
   61 | typedef unsigned short undefined2,ushort,uint2,wchar_t;
.../12.2.0/include/stddef.h:329:24: error: conflicting types for 'wchar_t';
        have 'unsigned int'
```

Under R4 that is proof the transformer is wrong, and the triage is instructive
because it is **both buckets at once**:

* **bucket (b), the payload.** `check_work_mode.c` carries a Ghidra
  `typedef unsigned short undefined2,ushort,uint2,wchar_t;` line. `wchar_t` is
  `unsigned int` on this target. That is a real reconstruction defect in a
  canonical tree, and it has been sitting there invisibly because nothing had
  ever put `<stddef.h>` into that translation unit.
* **bucket (a), the mechanism.** Stage 03's generated module header includes
  `<stdint.h>` and `<stddef.h>` to be self-contained (its own round-1 fix). The
  file became newly *eligible for a hoist* only because the parity agent's
  type-disagreement repair made two of its declarations agree — so Stage 03,
  unchanged, started injecting `<stddef.h>` into a file that redefines a
  `<stddef.h>` typedef. **Stage 03 landed green and is red at these inputs
  through no change of its own.**

The transformer fix is a refusal, not a repair: sub-batch B now excludes from the
hoist any file that itself `typedef`s a name `<stdint.h>`/`<stddef.h>` provides.
**18 files** are excluded, and they are listed in the manifest under
`files_excluded_shadowing_a_stdlib_typedef`:

```
wchar_t   : SettingStoreHandler.c, check_work_mode.c, cjson_print_value.c,
            hci_vs_init.c, l2cap_recv.c, navigation_panoramic_map_display.c,
            resource_manger_get.c, uarte_nrfx_isr.c, ui_DashBoard_task.c
uint32_t/uint16_t/uint8_t : gui_area_clear.c, mobile_send_notification_to_ble_device_test.c,
            not_disturb_sync_data.c, onboarding_sync_data.c,
            put_whitelist_app_from_app.c, sendAudioStram2Cache.c, try_to_save_file.c
uintptr_t : audioStreamFileManagerHandler.c, spec_ble_command_hook.c
```

Regenerated: **baseline build exit 0.** These 18 are handed over as defects for
the canonical trees; this pipeline may not write them (R1).

---

## 3. The measurement that decides the whole stage

If a merge cannot be scoped by module, it has to be scoped by something. The
scope this stage uses is a **maximal, order-preserving run of consecutive files
inside one module that provably cannot collide**.

*Order-preserving* is load-bearing, not tidy: archive member order follows
`G1_RETAINED_SOURCES` order and the toolchain compiles with
`-ffunction-sections`, so emitting each merged unit at exactly the position of
its members' contiguous span leaves the input-section order the linker sees
unchanged. The codegen delta is then only what the merge itself causes, not a
whole-image relayout on top of it.

### 3.0 The seven refusal rules, and what each one is defending against

Two files may share a translation unit only if none of these holds. Each is
symmetric and is evaluated against **every** file already in the run, not just
the previous one.

| rule | refuses | why it is not optional |
|---|---|---|
| `type` | a symbol declared or defined in both with more than one canonical C type, or with a declaration that cannot be canonicalised | this is the `DEFECTS.json` class, applied pairwise instead of per module |
| `dupdef` | both files define the same non-static symbol | duplicate definition |
| `static` | one file gives an identifier internal linkage and the other *names* it | **silent.** C11 6.2.2p4: a later `extern` inherits the visible prior *internal* linkage, so the second file's call binds to the first file's private helper and nothing says so |
| `typedef` | a typedef name defined by both with different types, or defined by one and named by the other | the `u8` class |
| `macro` | a macro defined by both with different bodies, or defined by one and named by the other | the `#define NAN` class: a file that merely *mentions* `NAN` is refused as a partner, so it cannot silently pick up someone else's |
| `asmname` | the same `__asm__("...")` assembler name bound to two different C identifiers | conflicting declaration |
| `includes` | the two files' **angle**-include sets differ | see §4.2 |

Quoted repository headers are not refused — they are **read**. Every quoted
include is resolved the way the compiler resolves it (relative first, then along
the five `-I` directories the app CMakeLists passes), transitively, and the
header's declarations, macros, typedefs and `static inline`s are folded into the
including file's own facts. `g1_log.h`'s `printk`, `g1_dedupe.h`'s macros and
`g1_ghidra_ops.h`'s helpers therefore participate in rules 1–6 as if the file
had written them.

### 3.0.1 A measurement the `typedef` rule could not have been written without

The obvious type foldings are **not all true on this target**. Compiled with the
project's own `arm-zephyr-eabi-gcc -mcpu=cortex-m33 -std=gnu11`:

| pair | verdict |
|---|---|
| `uint8_t` / `unsigned char` | accepted — SAME |
| `uint16_t` / `unsigned short` | accepted — SAME |
| `uint64_t` / `unsigned long long` | accepted — SAME |
| `int64_t` / `long long`, `int16_t` / `short`, `int8_t` / `signed char` | accepted — SAME |
| `size_t` / `unsigned int`, `uintptr_t` / `unsigned int` | accepted — SAME |
| **`uint32_t` / `unsigned int`** | **REJECTED — DIFFERENT** |
| **`int32_t` / `int`** | **REJECTED — DIFFERENT** |
| `uint32_t` / `unsigned long` | accepted — SAME |

newlib on `arm-zephyr-eabi` types `uint32_t` as **`unsigned long`** and `int32_t`
as **`long`**. The corpus writes `typedef uint32_t u32;` in 19 files and
`typedef unsigned int u32;` in 17 — those are *conflicting* typedefs, not two
spellings of one. Folding them the intuitive way would have produced a wrong
"these agree" verdict on the single most common typedef in the tree.

### 3.1 What blocks a merge, measured by relaxing one rule at a time

Running the partition five times over the 1,615 retained app sources, each time
switching off exactly one refusal rule:

| refusal rules in force | app TUs | files absorbed |
|---|---:|---:|
| **all six** | **590** | 1,340 |
| all but `static` | 587 | 1,344 |
| all but `typedef` | 583 | 1,350 |
| all but `macro` | 579 | 1,355 |
| **all but `type`** | **120** | **1,593** |

*(These five runs predate the §2 fix and the module-header rule of §4.2, so they
are a sensitivity measurement, not the shipped numbers; the shipped numbers are
in §5.)*

**That last row is the finding of this stage.** The three "hazard" classes the
brief names — local typedefs, macros, statics — cost between 4 and 15 files
each. The 833 declaration type disagreements cost **473 translation units**.
A fully merged app tree is 120 TUs away, and *the entire distance is the type
census*. Nothing else in the corpus is meaningfully in the way.

### 3.2 A claim I made and then had to withdraw

The transformer's first docstring said order preservation leaves "the input
section order the linker sees unchanged". **That is false, and the measurement
that disproves it is worth recording** because it changes what this stage can
claim.

The app sources link as `app/libapp.a`, and a static archive's members are pulled
**on demand** to resolve undefined symbols, not in archive order. In the
*baseline*, `__ieee754_pow.c.obj` and `nan.c.obj` are adjacent in
`app_retained_sources.cmake` and land 29 KiB apart:

```
base:  0000d5a8 T nan          00014820 T __ieee754_pow
s04:   0000d5a8 T __ieee754_pow  0000df60 T nan     (one member: g1_lib_03.c.obj)
```

Merging them into one archive member necessarily makes them adjacent. Order
preservation **bounds** the disturbance; it does not remove it. Corrected in the
transformer docstring and in the generated files' banner.

---

## 4. What the transformer does

`recon/refactor/transforms/t04_cohesive_tu.py`, registered as stage 4.

**Sub-batch selection** is by `G1_STAGE04_BATCH`, most-mechanical/least-risky
first, so a later side-effect failure localises:

* **A** — only runs in which **no member file contains the token `volatile`**.
  No member performs a volatile access at all, so no inlining decision inside
  such a TU can reorder, coalesce or drop one. R8 exposure: nil.
* **AB** (default) — every clean run.
* **off** — identity, for bisecting.

**Emission is verbatim.** Each merged unit is a banner plus every member's text
byte for byte, includes left exactly where they were. All five repository
headers are include-guarded, so a repeated inclusion is a no-op; leaving them in
place avoids any question about a header whose content depends on macros defined
before it (`g1_app_symbols.h` opens with `#ifndef bool`). **No token inside any
function body is touched by this stage.**

`app_retained_sources.cmake` is rewritten in the same transaction (C6): the first
member's line is repointed at the merged unit and the other members' lines are
deleted, so list order is preserved exactly. Merged unit names are
`g1_<module>_<NN>.c` and can never match `rodata_*` — `g1_verified_rodata_keep.ld`
matches `KEEP(*rodata_*.c.obj(...))` on the **object filename** (C6); there is a
test for it.

### 4.1 Two pipeline defects this stage had to fix first

**`stagelib.parity_rows` only ever read the first identity banner in the first
4 KiB of a file.** A merged unit carries dozens. Left alone, `check-addresses 3 4`
would have reported 1,240 functions as vanished — the integrity check silently
failing exactly where it is most needed. It now emits a row per banner, with the
`public-name:` line matched inside that banner's own window.

That widening is a **strict no-op for stages 00–03**, measured rather than
asserted: over stage 03's 2,629 manifest entries, 2,567 files carry a banner,
**2,567 banners in total, 0 files with more than one, 0 banners beyond byte
4096**. Both rules yield the same 2,567 addresses, and re-materialising 00→03
after the change confirmed 2,567 on every stage.

**`stagelib.Stage.emit` watched only one source per output.** A merged unit is
derived from N sources; without a change, an upstream defect fix landing inside
member 7 would never mark stage 04 stale — a staleness mechanism reporting
"current" while it is not. `emit` now takes `extra_sources` and records
`additional_sources`; `staleness()` checks them.

### 4.2 Rule 7 (`includes`), and why quoted headers are read rather than refused

A member's own `extern` declarations were checked by the compiler against the
headers **that file** includes, and against nothing else. Merge a file that
includes `<zephyr/kernel.h>` with one that writes its own
`extern void k_sleep(uint32_t,uint32_t);` and the authoritative declaration meets
the reconstructed one for the first time. Measured, not predicted: the second
stage 04 build failed exactly so, on `printk`, `k_sleep`, `z_impl_k_sem_take`
and `memcpy`.

Requiring the two files' **angle**-include sets to be equal makes that
unrepresentable, and the proof is one line: if A and B see the same headers, then
everything A declares locally was already compiled against B's headers and vice
versa, so only local-vs-local pairings are new — and those are rules 1–6.
`<stdint.h>`/`<stddef.h>` are exempted because they declare no function; a file
that includes one is treated as *naming* every typedef it provides, so a partner
that typedefs `uint32_t` itself is refused by the ordinary typedef rule.

**Quoted repository includes are read, not refused.** Each is resolved the way
the compiler resolves it — relative to the including file, then along the five
`-I` directories the app CMakeLists passes — transitively, and the header's
declarations, macros, typedefs, `static inline`s, struct tags and enum constants
are folded into the including file's facts. Otherwise `g1_log.h` (560 includers)
and `g1_dedupe.h` would have split every module in two. Measured cost of *not*
doing this: 882 TUs instead of 695.

### 4.3 Four more silent-hazard classes the builds forced out, in order

Each was a *transformer* bug (bucket (a)) whose payload was a real corpus shape.

| # | what the build said | the shape | the rule now |
|---|---|---|---|
| 1 | `conflicting types for 'battery_soc_curve_model_init'` | a member that stage 03 did **not** convert keeps a local declaration that disagrees with the generated **module header** another member includes | the module header's declarations participate in rule 1 whenever any member includes it |
| 2 | `conflicting types for 'battery_soc_curve_model_init'` again | the disagreeing declaration **wraps over three lines**; stage 03's scanner is `^[ \t]*extern[ \t].*;[ \t]*$` — one physical line | `extern` declarations are found at brace depth 0 and read to their terminating `;` regardless of layout |
| 3 | `redefinition of 'struct g1_i2c_msg'` | three sources define that struct **identically**; a tag may be declared repeatedly but defined once. *(A duplicate identical **typedef** is fine — measured: `c99`, `gnu99` and `gnu11` all accept it — which is why the typedef rule compares bodies and the tag rule does not.)* | rule `tag`, plus `enumconst` for enum constants |
| 4 | `conflicting types for 'is_battery_critical'` / `'thunk_FUN_00086384'` / `'cbor_decode_length_prefix'` | (a) definitions written **mid-line** after a `typedef` or an `extern`, invisible to a line-anchored scanner; (b) `#define zcbor_str_start_decode cbor_decode_length_prefix` — an object-like macro that **renames a symbol**, so the declaration the compiler sees is of a different name | definitions are found by walking back from a depth-0 `){`; identifier-to-identifier macros rename the symbol under which a declaration is recorded |

Class 4(b) is the one worth dwelling on. `#define X Y` where both are
identifiers is invisible to every name-based analysis in this project, and it
silently redirects a declaration to a different symbol. It is the same family as
the `u8` typedef: **local, legal, and only wrong when two files share a TU.**

### 4.4 The named `u8` hazard, and the parser bug that hid it

The brief names `__ieee754_exp.c`'s `typedef uint64_t u8;`. My first sweep
**did not find it**, and the reason is worth recording because it is the exact
failure mode the brief warns about: the file writes

```c
typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u8; typedef int64_t i8;
```

— four typedefs on **one physical line** — and a `^[ \t]*typedef` rule sees only
the first. The scanner is now brace-depth-aware and unanchored. With that fixed,
`HAZARDS.json` reports it without being told to:

```
u8   unsigned char        29 files   (e.g. imu_fusion_thread.c)
     unsigned long long    1 file    (__ieee754_exp.c)
```

Rule 4 refuses to put `__ieee754_exp.c` in a translation unit with any file that
so much as *names* `u8`. `lib/` is **not** excluded wholesale — 394 of its 482
files are merged — but `__ieee754_exp.c` is isolated from every `u8` user by a
rule, not by a special case.

**The corpus-wide sweep for the same shape** (`HAZARDS.json`, taken over all
1,615 retained sources *before* any header folding, so a shared header's helpers
do not show up as 300 fake collisions):

| class | count |
|---|---:|
| typedef names with **incompatible** definitions across files | **30** |
| macro names defined with **differing bodies** across files | **35** |
| `static` names used in more than one file | **17** |

The 30 incompatible typedefs are the headline. Besides `u8`, the base-type ones
are `u32` (19 files `unsigned long` vs 17 files `unsigned int` — **not** the same
type, §3.0.1), `uint` (3 spellings over 65 files), `byte`, `ulonglong`,
`undefined1`, `undefined4`, `ushort`, `code`, `code_t`; the rest are
callback typedef names (`fn_t` 8 incompatible signatures, `fnptr` 10, `codeptr`
4, `fp_t` 6 …) reused for unrelated function-pointer types in different files.
The 35 differing macros include `LOG_LEVEL` (3 bodies, 17 files), `NAN` (4
bodies, 8 files), `LOG_TAG`, `g_log_level`, `g_log_use_alt_sink` and
`log_message`.

---

## 5. What was merged

**1,615 retained app translation units → 695. 318 cohesive units absorbing
1,238 files.**

| module | merged TUs | files absorbed | largest | | module | merged TUs | files absorbed | largest |
|---|---:|---:|---:|---|---|---:|---:|---:|
| `lib/` | 101 | 370 | 12 | | `sensors/power/` | 9 | 36 | 7 |
| `audio/` | 30 | 106 | 12 | | `sensors/input/` | 9 | 26 | 6 |
| `core/` | 28 | 106 | 17 | | `gui/` | 8 | 30 | 12 |
| `unsorted/` | 23 | 160 | 20 | | `ipc/` | 8 | 43 | 11 |
| `storage/` | 22 | 71 | 12 | | `esb/` | 5 | 17 | 5 |
| `notify/` | 19 | 69 | 9 | | `sensors/imu/` | 5 | 15 | 4 |
| `display/` | 18 | 65 | 7 | | `ui/dashboard/` | 5 | 22 | 7 |
| `ble/` | 17 | 72 | 11 | | `analytics/` | 4 | 9 | 3 |
| | | | | | `ui/quicknote/` | 3 | 8 | 3 |
| | | | | | `ui/onboarding/` | 2 | 8 | 4 |
| | | | | | `ui/translate/` | 2 | 5 | 3 |

`common/`, `ui/navigation/` and `ui/teleprompt/` produced no merged unit.
Run-length histogram: 377 singletons, 116 pairs, 81 triples, … one run of 17
(`core/`) and one of 20 (`unsorted/`).
`app_retained_sources.cmake`: **318 lines repointed, 920 removed**, order
preserved exactly.

Quoted headers folded into their includers: `g1_app_symbols.h` 1,615×,
`g1_log.h` 452×, `g1_dedupe.h` 235×, `g1_ghidra_ops.h` 8×, `g1_nrf_regs.h` 7×,
`g1_cmsis_shim.h` 4×, plus the six `ble_process_put_*` fragments.
**`unresolved_quoted_includes` is empty** — every quoted include in the whole
merge-candidate set was accounted for.

---

## 6. Gate ladder — measured

Built with the repository's own entry point from the stage trees. **No build
file, linker script or `tools/` module was edited outside the stage tree.**

```sh
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4-base-app
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh     app /private/tmp/g1-s4-app
```

| gate | Stage 03 baseline, rebuilt at these inputs | **Stage 04 (sub-batch AB)** |
|---|---|---|
| app build | exit 0 (after the §2 transformer fix) | **exit 0, 0 errors** |
| app `zephyr.bin` vs baseline | — | **DIFFERS — and that is expected, see §7** |
| app FLASH | 956,356 B / 982,528 B = 97.34 % | **956,244 B = 97.32 % — Δ −112 B**, 26,284 B headroom |
| app `.text` | 492,688 | **492,576 — Δ −112 B** |
| app `.rodata` | 456,536 | **456,536 — Δ 0** |
| app `.data` / `.bss` / `.noinit` | 3,327 / 189,230 / 60,021 | **Δ 0 / Δ 0 / Δ 0** |
| app RAM | 253,765 B = 56.32 % | **253,765 B — Δ 0** |
| `.text` base | `0x0000c358` | **`0x0000c358` — unchanged** |
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| **text symbols carrying a size** (`nm -S`) | 2,935 | **2,935 — 0 added, 0 removed** |
| **functions whose size changed** | — | **9**, net −16 B (§7.1) |
| compiler warnings | 2,210 | **2,203 (Δ −7)** — exactly one bucket moved, `-Wbuiltin-declaration-mismatch` 237 → 230; **no new warning kind** |
| **per-object byte comparison** (`--strip-debug --remove-section=.comment`) | — | **1,601 uniquely matched, 1,600 byte-identical, 1 differs** — the 1 is `uname.c.obj`, the known build-to-build stock churn unit. 215 basenames ambiguous on one side and not compared. |
| **`.rodata` vs `app_update.bin`** | 1,339 objects, **1,325 match / 14 mismatch** | **1,339 objects, 1,325 match / 14 mismatch — the same 14, name for name** |
| `verify_data.py` | — | **995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)** |
| `check_ram_pin_collisions.py` app | 627 bound OK / 0 escaping / 0 unknown | **627 / 0 / 0 — identical** |
| `gen_retained_sources.py --check` | — | **"retained source lists are current"** |
| `driver.py check-addresses 3 4` | — | **identical, 2,567 both sides, 0 gained, 0 lost** |
| whole `recon/refactor` suite | 25 / 25 | **58 / 58 PASS** — 33 new tests (`test_cohesive_tu.py`) |
| idempotence (`materialize 4` twice) | — | MANIFEST `215c0c0d…` → `215c0c0d…`; whole-tree sha `8633d869…` → `8633d869…` — **byte-identical** |
| **net core** | untouched | **untouched — `git status --porcelain` over `recon/net`, `recon/symbolized/net`, `recon/application`, `recon/symbols`, `recon/headers`, `recon/generated`, `recon/board`, `recon/wiring`, `tools` is EMPTY. Not one net input changed; the 225,581 B freeze holds by construction and no net build was run.** |

### 6.1 Sub-batch A, built and measured separately

`G1_STAGE04_BATCH=A` selects only runs in which **no member contains the token
`volatile`** — 47 merged units absorbing 151 files, 1,615 → 1,511 TUs. It is a
small slice, and the reason is itself a measurement: this corpus models every
global as a `volatile` absolute-address pointer, so nearly every file contains
the token.

| gate | sub-batch A |
|---|---|
| app build | **exit 0, 0 errors** |
| app FLASH | **956,340 B = 97.33 % — Δ −16 B** |
| `.text` | **492,672 — Δ −16 B**; `.rodata` / `.data` / `.bss` / RAM **Δ 0** |
| `nm -u` / duplicate globals | **0 / 0** |
| warnings | **2,209 (Δ −1)** |
| text symbols | **0 added, 0 removed** |
| **functions whose size changed** | **2** — `k_uptime_get_3` 28 → 4 B, `__ieee754_pow` 2,480 → 2,488 B |

So a side-effect failure can be localised: A is a strict subset of AB (the
partition is identical, only the *selection* differs — `adjacencies_blocked` is
1,084 in both runs), and A's entire codegen delta is two functions.

---

## 7. R8 — the honest statement about observability

**This is the first stage in the pipeline whose image is not byte-identical, and
it could not have been.** Merging changes what the optimiser may do across
former TU boundaries. Stage 03 predicted exactly this and said the merge "needs
the oracle, not a `cmp`". It was right.

### 7.1 The delta is small, and it is enumerable

Nothing was added or removed from the symbol table (2,935 sized text symbols on
both sides; 3,115 in `nm -n` order including weak and sizeless entries), so no
function was inlined out of existence and every address in `PARITY_MAP.json`
still resolves. **Nine functions changed size, and here they all are:**

| Δ | function | before → after |
|---:|---|---|
| −24 | `k_msleep_ticks32768_c` | 28 → 4 |
| −24 | `k_uptime_get_10` | 28 → 4 |
| −24 | `k_uptime_get_3` | 28 → 4 |
| −24 | `k_uptime_get_6` | 28 → 4 |
| −24 | `k_uptime_get_8` | 28 → 4 |
| −20 | `find_cf_cfg_by_addr` | 76 → 56 |
| +8 | `__ieee754_pow` | 2,480 → 2,488 |
| +10 | `convert_to_id_on_match` | 34 → 44 |
| +106 | `close` | 76 → 182 |

Five of the nine are pure forwarding thunks that collapsed to a 4-byte tail
branch once the callee sat in the same unit. **None of the nine is a bus driver,
a display path or a sensor path.** The remaining −96 B of the −112 B `.text`
delta is alignment padding freed by those shrinks.

The containment is also proved from the other side: of the 1,601 objects present
under the same basename in both builds, **1,600 are byte-identical**. Every
object that was not merged compiled to the same bytes.

### 7.2 What is nevertheless at risk, stated plainly

* **Timing.** The pass immediately before this one proved that **+60 B of
  `.text` reordered two firmware threads on the shared I²C bus** and broke
  `twim2 p1_boot` byte-equality, and it reverted 109 otherwise-good fixes rather
  than ship "probably benign timing". This stage moves `.text` by **−112 B**.
  That is the same order of magnitude, in the opposite direction. **It must be
  assumed to perturb the same streams until an oracle run says otherwise.**
* **Layout.** `_end` is `0x2003ff45` on both sides, so the RAM probe addresses
  (`0x20040025` / `0x20040F38` / `0x20040FAA`) carry over unchanged. But
  **`runtime_info_sync` moved `0x00015c04` → `0x0001632c`**, so `$rtinfo_pc`
  **must be re-read from the ELF actually booted** — the value in every previous
  reproduction recipe is wrong for this image. And per §3.2, archive-member pull
  order changed, so a number of functions are relocated relative to the
  baseline.

### 7.3 The oracle is REQUIRED and is NOT available to me

Renode is owned by the concurrent agent and this brief forbids running it.
**I do not claim R7 acceptance for Stage 04 and I have no behavioural evidence
for it.** Unlike Stages 01–03, Stage 04 cannot borrow it either: its image is
not byte-identical to any image that has ever been captured.

What must be run, per sub-batch, A first:

```sh
# probe values MUST be re-read from the ELF actually booted:
#   arm-zephyr-eabi-nm zephyr.elf | grep -wE 'runtime_info_sync|_end'
#   device ctx = align16(_end);  +0xd5 / +0xfe8 / +0x105a
printf '$rtinfo_pc=0x0001632c\ni @/Users/freedomcoder/armemul/g1-ours-paired.resc\n' > .../ours-paired.resc
# dashboard: G1_ATT_WRITE="" ;  navigation: leave unset.  RUN NAVIGATION TWICE.
G1_APP_ELF=/private/tmp/g1-s4-app/zephyr/zephyr.elf G1_NET_ELF=<the frozen net build> \
  recon/emulator/scripts/capture_display_sensor_oracle.sh ...
```

The bar is the four shipped-firmware framebuffer hashes — `19b1f24a…` /
`0c5cc90b…` (dashboard) and `b26c73b3…` / `1d617c65…` (navigation) — plus
`spim_a` 3,645, `twim2 p1_boot` 1,089 / `7ed8ddcd…`, the `twim1 p1_boot`
per-device set, and `JBD_FRAMECOUNTER_P2` `0x0D61`. Navigation `twim2 p1_boot`
and `twim1 p1_boot` are **bistable for our rebuilt images** (R7 gate record) and
a single-run EQ/NE on them is not evidence.

**Until that run happens, Stage 04 is BUILT AND STATICALLY GATED, NOT PROVEN.**

---

## 8. What I did NOT merge, and everything quarantined, with measured reasons

### 8.1 Shape quarantine — 30 files, never paired with anything

| reason | count | files |
|---|---:|---|
| `multi_declaration_line_types_unknown` | 13 | `ui_even_ai_draw_mic_status_icon.c`, `try_enter_low_power_mode.c`, `panel_temp_calibration_init.c`, `gui_utf_draw_dark_light_split.c`, `gui_utf_draw_middle.c`, `__sfvwrite_r.c`, `cjson_parse_value.c`, `rpmsg_virtio_rx_notify.c`, `ble_ancs_data_req_thread.c`, `ble_whitelist_app.c`, `confirm_message.c`, `imu_fusion_thread.c`, +1 |
| `file_scope_pragma_leaks_forward` | 9 | `uarte_nrfx_isr.c`, `hci_vs_init.c`, `check_work_mode.c`, `resource_manger_get.c`, `cjson_print_value.c`, `l2cap_recv.c`, `ui_DashBoard_task.c`, `DashBoard_Reflash.c`, `SettingStoreHandler.c` |
| `per_tu_ffp_contract_body` | 5 | `imu_mahony_ahrs_update.c`, `fast_inverse_sqrt.c`, `orientation_get_heading_deg.c`, `quaternion_to_euler.c`, `fuel_gauge_update.c` |
| `includes_a_definition_carrying_inc_fragment` | 1 | `ble_process_put_req.c` |
| `attribute_alias_definition` | 1 | `log_message.c` |
| `named_by_path_in_app_cmakelists` | 1 | `discovery_callback.c` |

Two of these deserve the reasoning spelled out.

**`#pragma GCC diagnostic ignored` leaks forward.** It is file-scope state that
would silently *suppress* the diagnostics of every later function in a merged
unit. Diagnostics are how this project finds latent defects (README C4 bucket
(b), and §2 and §4.3 of this report are four more instances). Losing them
silently is worse than not merging. Wrapping each segment in `push`/`pop` would
restore the state — but it would also strip the pragmas `g1_log.h` applies once
through its include guard, and that is a second-order change this batch will not
take blind.

**`-ffp-contract` is a per-TU contract, and the build does not set it yet.**
AGENTS.md finding 1b: `VMLA`-family = unfused for all five G1 application float
bodies, `VFMA`-family = fused for all 19 liblc3/libm bodies, never mixed, and
"the cohesive build **must** set `-ffp-contract=off` for
`FUN_00026624/265e8/26828/7cab4/fuel_gauge_update`". Measured here: **zero
occurrences of `ffp-contract` anywhere under `recon/application` or
`recon/generated`** — the flag is not set today. Merging those five bodies would
foreclose a fix the project has already committed to, because that flag has no
finer grain than a translation unit. They are excluded. *(`FUN_0007cab4`
resolves to `discovery_callback.c`, which is excluded for the CMake-path reason
as well; both reasons apply to the same file.)*

### 8.2 Pairwise refusals — 1,084 adjacencies blocked

| rule | adjacencies blocked | worst offenders |
|---|---:|---|
| `type` | **830** | `get_device_info` 71, `memset_bytes` 46, `assert_post_action` 41, `log_msg_create_3arg` 15, `memcpy` 13, `audio_codec_reg_op_dispatch` 13, `smp_log_message` 12, `reflash_fb_data_to_lcd` 12, `k_msgq_put` 11 |
| `macro` | 117 | `g_log_level` 16, `g_log_use_alt_sink` 14, `debug_print` 11, `log_message` 6, `get_device_info` 5 |
| `includes` | 80 | `<stdbool.h>` 29, `<cmsis_gcc.h>` 21, `<zephyr/kernel.h>` 18, `<string.h>` 5, `<stdarg.h>` 3 |
| `typedef` | 29 | `uint32_t` 12, `uint8_t` 8, `wchar_t` 2, `uintptr_t` 2, `fp774_t`, `fn_t` |
| `static` | 16 | `load_u16`/`load_u32`/`store_u16`/`store_u32` 2 each, `display` 2, `ipsr`, `isb`, `rd_basepri`, `wr_basepri_max`, `fbits`, `bits` |
| `tag` | 7 | `struct adc_api_raw`, `struct device_raw`, `struct slist`, `struct slist_node`, `struct qspi_cmd`, `struct g1_i2c_msg`, `struct g1_opt_view` |
| `enumconst` | 5 | `x3c` 2, `x0c`, `x97`, `x39` |
| `asmname` | 0 | — |
| `dupdef` | 0 | — |

### 8.3 The things I chose not to do, each with the measurement behind it

1. **I did not rename colliding `static`s to raise the yield**, although the
   brief suggests it. Measured cost of the rule: re-running the partition with
   `static` switched off gives **694 TUs instead of 695 — one translation unit.**
   A whole identifier-rewriting transform, with its own failure modes, for one
   TU is not a trade worth making. The 17 colliding names are catalogued in
   `HAZARDS.json`.
2. **I did not resolve the `macro` (117) or `typedef` (29) refusals** by
   rewriting the sources. Cost: 687 and 689 TUs respectively, i.e. 8 and 6.
   Same trade.
3. **I did not merge across the `includes` boundary.** That one is worth 47 TUs
   (648 vs 695) and is the largest cheap win left, but resolving it properly
   means knowing which symbols each SDK header declares — a real evidence task,
   not a heuristic.
4. **I did not repair a single declaration disagreement.** R1: the fix belongs in
   `recon/{app,net}/src`, which this pipeline may never write. They are handed
   over, refreshed, in `stage_03_module_structure/DEFECTS.json` (**833** entries).
5. **I did not restructure the net core.** Frozen at 225,581 B, ~100 % stock, no
   module structure to recover, path-keyed CMake filter. Measured, not assumed:
   `git status --porcelain` over `recon/net`, `recon/symbolized/net`,
   `recon/application`, `recon/symbols`, `recon/headers`, `recon/generated`,
   `recon/board`, `recon/wiring` and `tools` is **empty**. No net input changed,
   so no net build was run and the freeze holds by construction.
6. **I did not run the emulator oracle** (§7.3). Renode is owned by the
   concurrent agent and the brief forbids it. I make no R7 claim.
7. **I did not hoist `#include` directives to the top of a merged unit**, which
   would have made the merged files read better. `g1_app_symbols.h` opens with
   `#ifndef bool`, so its expansion depends on the macro state at its include
   point; moving it is not provably inert and this stage does not need it.
8. **I did not regenerate `refactor_module_map.json`**, so `unsorted/` still
   holds 177 files (10.9 % of the app tree) and 32 sources still have no row.
   Same reason Stage 03 gave.
9. **I did not touch any canonical tree, `tools/`, `recon/emulator/**`,
   `armemul`, any live build file, any linker script, `recon/board/**`, or the
   live `recon/headers/`.** Structurally impossible through
   `guard.check_write`; the guard tests still pass. Everything stage 04 emits
   exists only inside `recon/refactor/stage_04_cohesive_tu/tree/`.
10. **I did not regenerate the diagnostic stage 99.** `driver.py status` reports
    it stale (308 inputs moved). Stage 03 §8 item 10 already established that it
    has nothing left to measure — the zero-argument call sites it existed to
    count are all repaired — and it should be retired rather than repaired. I
    left it registered rather than deleting the evidence of a completed
    measurement.
11. **I did not commit anything.**

---

## 9. Is this production-grade, or merely rearranged?

Asked directly by the brief, so answered directly.

**What a maintainer would genuinely recognise.** `display/` is now 18 cohesive
files plus 24 singletons instead of 89 one-function files; `ipc/` is 8 files
covering 43 of its 47 functions; `lib/` is 101 units instead of 482. The build
list is generated from it, the module headers from Stage 03 sit alongside, and
the directory tree from Stage 03 still reads. **Roughly 57 % of the app tree's
translation units are gone and 77 % of its files now live next to code they are
related to.** That is a real change in what the tree is, not a rename.

**What is honestly still rearrangement, and by how much.**

* **377 of 695 units are still single functions.** The largest merged unit holds
  20 functions; the median merged unit holds 3. A maintainer opening
  `core/g1_core_11.c` finds a handful of related functions, not a subsystem.
* **The merged files are concatenations, not compositions.** Each member keeps
  its own `#include "g1_app_symbols.h"`, its own banner comment and its own
  `extern` block; a real `display.c` would have one include block, one set of
  declarations and functions ordered by call structure. Getting there requires
  editing inside the files, which is a later stage and a different risk class.
* **`unsorted/` is still 177 files and still the second-largest directory.**

**The most valuable thing this stage produced is not the merge.** It is §3.1:
with all seven rules in force the app is **695** translation units; with only
the `type` rule relaxed it is **243**; with nothing refused at all it is **37**.
Every hazard the brief warned about — the `u8` typedef, the macros, the statics
— costs between **1 and 8 translation units each**. The 833 declaration
disagreements cost **452**. The road to a fully merged tree is one road, it is
already surveyed in `DEFECTS.json`, and nothing else is meaningfully in the way.

Set against that, this stage also found **five defect classes that no gate in
this project could see** and that would each have produced a silently wrong
image or a mass build failure: the `wchar_t`-shadowing sources (§2), multi-line
declarations, struct-tag redefinition, mid-line definitions, and
identifier-renaming macros (§4.3). Four of the five were found by a compiler
that had never been asked the question before, which is exactly the bucket-(b)
mechanism README C4 predicts.

**So: the tree is materially more cohesive than Stage 03 left it, the static
gate ladder is clean, and the codegen delta is nine nameable functions — but the
stage is not proven, because its image has never been booted.**

---

## 10. The shortest path to a fully merged, byte-identical-or-oracle-proven tree

In order, with the measured size of each step.

1. **Run the oracle on stage 04, sub-batch A first, then AB** (§7.3). Until this
   happens Stage 04 is built, not proven. Cost: two capture pairs per sub-batch
   (navigation twice — it is bistable). This is the only step that cannot be
   done without Renode, and it blocks everything after it.
2. **Repair the 833 declaration disagreements** in the canonical trees, arity
   first. `type` is worth **452 translation units** — 20× every other rule
   combined. The census is already keyed by module, symbol, every distinct
   canonical type with its occurrence count, defining file and file list. The
   top of the list is short and hub-shaped: `get_device_info` (71 blocked
   adjacencies), `memset_bytes` (46), `assert_post_action` (41), `memcpy` (13).
   Fixing those four symbols alone is worth more than every hazard rule in this
   stage.
3. **Establish which symbols the SDK angle headers declare**, so rule 7 can be
   replaced by a precise check instead of set equality. Worth **47** TUs, and it
   is a one-off evidence task (`gcc -aux-info` over the union of angle includes),
   not a heuristic.
4. **Repair the 18 sources that shadow a `<stdint.h>`/`<stddef.h>` typedef**
   (§2) and the 13 with multi-declaration lines. Both are small, mechanical,
   canonical-tree edits that unlock stage 03 hoists as well as stage 04 merges.
5. **Then re-run stage 04.** It is a pure function of its inputs; every gain
   above lands automatically. At `type` fully repaired the partition is **243**
   TUs, and with the shape quarantine also cleared it approaches the **37** that
   the rules-off upper bound measures.
6. **Only then consider composition** — one include block per module, ordered
   functions, real headers. That is the step that makes the files read like
   source rather than like a concatenation, and it is the first one that edits
   inside a file. It should not start while the tree is still 377 singletons.

A **byte-identical** merged tree is not reachable and should not be chased:
merging changes inlining opportunities and archive-member pull order by
construction (§3.2, §7). The achievable bar is the one C7 already names —
observable side-effect equivalence with the shipped binaries — and step 1 is how
this stage gets there.

---

## 11. Concurrency, footprint, reproduction

### 11.1 Concurrency — it happened, and the contract worked

Mid-pass the parity agent landed **`192349af` "P4 iter-42"**, which moved 4
pipeline inputs: `__ieee754_expf.c`, `atanf.c`, `spline_interp_3pt.c`,
`spline_interp_pair_2out.c`. **All five stages were regenerated, never patched**,
and every transformation statistic came back identical:

```
stage 00  2,629 files / 2,567 rows
stage 01  100 accepted / 1,934 quarantined / 192 sites inlined
stage 02  3,116 / 45 / 367 / 139 / 47, 44 latent defects
stage 03  1,621 moved / 17 headers / 142 hoisted / 833 refused
stage 04  1,615 -> 695 TUs / 318 merged / 1,238 absorbed / 1,084 blocked
check-addresses 0-1, 1-2, 2-3, 3-4:  all identical, 2,567 both sides
```

Both builds were re-run at the regenerated inputs, and **every figure in §6 and
§7 is the post-regeneration measurement**: baseline FLASH 956,356 B / `.text`
492,688; stage 04 FLASH 956,244 B / `.text` 492,576; warnings 2,210 vs 2,203;
`nm -u` 0/0; duplicate globals 0/0; `.rodata` 1,325 / 14 on both sides; 1,600 of
1,601 objects byte-identical; the same nine functions changed size by the same
amounts; pin gates 627 / 0 / 0; refactor suite 58/58. `driver.py status` now
reports stages 00-04 all **current**.

iter-42 moved four float bodies and changed neither build's section sizes by a
byte, which is worth recording as the concurrent agent's own containment
result rather than mine.

### 11.2 Footprint — everything this pass wrote

```
 M recon/refactor/stagelib.py                    (parity_rows widening; emit extra_sources; staleness)
 M recon/refactor/driver.py                      (stage 4 registry entry)
 M recon/refactor/transforms/t03_module_structure.py
                                                 (exclude stdlib-typedef-shadowing files from the hoist)
 M recon/refactor/README.md                      (C2 note, stage table 03b/04..07, $rtinfo_pc warning)
 M recon/refactor/stage_0{0,1,2,3}_*/MANIFEST.json, stage_0{2,3}_*/DEFECTS.json
                                                 (regenerated at iter-42)
?? recon/refactor/transforms/t04_cohesive_tu.py  (the transformer)
?? recon/refactor/test_cohesive_tu.py            (33 new tests)
?? recon/refactor/stage_04_cohesive_tu/          (MANIFEST/PARITY_MAP/QUARANTINE/HAZARDS + tree/)
?? recon/analysis/staged_refactor_stage04.md     (this file)
```

`recon/refactor/.gitignore` already excludes `stage_*/tree/`. **No file outside
`recon/refactor/` and this report was written. Nothing committed.** Everything
else dirty in `git status` belongs to the concurrent parity agent.

### 11.3 Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
for n in 0 1 2 3 4; do $V recon/refactor/driver.py materialize $n; done
$V -c "import sys;sys.path.insert(0,'recon/refactor');import driver;\
 [print(a,b,driver.check_addresses(a,b)['identical']) for a,b in ((0,1),(1,2),(2,3),(3,4))]"
$V -m unittest discover -s recon/refactor -p 'test_*.py'          # 58/58

./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s4-base-app
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh     app /private/tmp/g1-s4-app

# sub-batch A alone (only runs with no `volatile` in any member):
G1_STAGE04_BATCH=A $V recon/refactor/driver.py materialize 4
# ... and G1_STAGE04_BATCH=off for the identity transform, when bisecting.

# cost of each refusal rule, using the shipped transformer code:
$V <scratch>/s04/sensitivity.py
# cheap pre-flight before spending a full build on a parse error:
bash <scratch>/s04/preflight.sh      # syntax-only over all 695 app sources
```

