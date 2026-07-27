# Stages 06 / 07 / 08 — closing the Stage 05 §7 NOT-DONE list

**Written incrementally as the work ran. Nothing committed.** Every number below
comes from a command that was run. Where a number is superseded by a
re-measurement it is corrected in place with a note rather than deleted.

The brief is `recon/analysis/staged_refactor_stage05.md` §7, items 1–6:

1. sub-batch S (internal linkage) — implemented, measured, **not applied**,
   because a source-text scan cannot see newlib calling `_sbrk_r`;
2. module-private declaration demotion — not attempted;
3. include **hoisting** — stage 05 only deleted repeats;
4. call-order function reordering — not attempted, `size-changing` by default;
5. the `cmsis_gcc.h` gap in the SDK evidence — open.

All five are now done, and three of them turned out to be a different problem
from the one they were filed as. Headline first:

| | |
|---|---|
| **item 5 — `cmsis_gcc.h`** | not a GCC limitation. **A line-anchored regex in our own `sdk_symbols.py` defeated by a trailing comment** — the *third* time that exact failure mode has bitten this pipeline. Evidence **996 → 1,406** declared identifiers, **0 lost**, plus a new **27,838**-name macro census. Image `cmp`-IDENTICAL. |
| **item 1 — internal linkage** | source-text scan replaced by **link evidence** (`nm --undefined-only` over all 66 inputs of the app link, archives scanned whole). It names `_sbrk_r`'s referrer — and it shows the source scan was **wrong on 58 of its 240 candidates, 24 %**. 137 symbols made `static`, gated by a **real link** (README C6) which caught a hazard no `nm` evidence could: `.text` **−276 B**, `oracle_required`. |
| **items 2+3 — demotion + hoisting** | stage 06, declared `byte-identical`, **measured byte-identical**: `zephyr.bin` `cmp`-identical at 956,276 B. Units with exactly ONE include block **21 → 112**. |
| **item 4 — call-order reordering** | implemented, and it is a **measured no-op**. The 249 merged units contain **11 internal call edges in total**, all already callee-before-caller. Stage 08's tree is byte-for-byte stage 07's. |
| **suite** | **105 → 139** (34 new tests) |

---

## 0. Starting point, measured rather than inherited

```
HEAD          fc11c2c8  "P4 iter-43: the frozen-clock fix lands -- 7 screen regions
                         restored, prediction OVERSHOOTS by +64"
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)
```

`driver.py status` at the start of this pass:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **stale** | 2,626 | **3** |
| 01 literal_inline | current | 2,629 | 0 |
| 02 block_dedupe | current | 2,629 | 0 |
| 03 module_structure | current | 2,629 | 0 |
| 04 cohesive_tu | current | 2,629 | 0 |
| 05 cohesive_composition | current | 1,714 | 0 |
| 99 defect_probe | stale | 1,831 | 781 |

The 3 moved inputs are iteration 43. Stages 00 → 05 were **regenerated, never
patched** — the sixth consecutive pass in which that has been required, and it
worked again in **zero transformer rounds**:

```
materialize 0   2,629 files / 2,567 parity rows
materialize 1   2,629 / 2,567 / 100 candidates / 192 sites
materialize 2   2,629 / 2,567
materialize 3   2,629 / 2,567 / 1,621 moved / 704 content-changed
                19 module headers / 218 hoisted / 663 divergent
materialize 4   1,714 / 2,567 / 1,615 -> 700 TUs / 249 merged / 1,164 absorbed
                30 shape-quarantined / 878 adjacencies blocked
materialize 5   1,714 / 2,567 / 249 units composed
                1,573 includes + 146 declarations withdrawn / 1,164 banners
                internal_linkage_candidates 241
```

Every field is bit-for-bit the stage 05 report's final numbers. The three moved
files touched no hoistable declaration.

**Baseline image** (stage 05 at these inputs), built with the repository's own
entry point, no build file edited:

```
FLASH 956,276 B / 982,528 B = 97.33 %      RAM 253,765 B = 56.32 %
text 492,612  rodata 456,536  datas 3,327  bss 189,230  noinit 60,021
28 allocatable sections
```

identical to the stage 05 report's figures, so iteration 43 moved the sources
and not the image.

---

## 1. Item 5 — the `cmsis_gcc.h` gap was OUR bug, not GCC's

### 1.1 What the stage 05 report said, and why it was wrong

> `cmsis_gcc.h` compiles with the `<stdint.h>` prelude but contributes **0**
> identifiers, because its bodies are `__STATIC_FORCEINLINE` definitions that
> `-aux-info` does not report (verified by hand: the probe's `.aux` file has 122
> lines, none containing `NVIC`).

The observation was exact and the attribution was wrong. `-aux-info` reports
those bodies perfectly well. Re-running the probe:

```
$ head -3 probe.aux
/* compiled from: . */
/* .../cmsis_gcc.h:258:NF */ static void __ISB (void); /* () */
/* .../cmsis_gcc.h:269:NF */ static void __DSB (void); /* () */
```

The parser was

```python
_AUX = re.compile(r'^[^:]*:\d+:\d*:?[A-Z]*:?\s*(?P<decl>.*);\s*$')
```

— **the terminating `;` anchored at end of line.** `-aux-info` appends a
trailing `/* (params) */` comment to every line that is a *definition* rather
than a bare prototype, which moves the `;` off the end, so **every definition
line in every header was silently dropped**. Definitions are exactly the
`static __inline` bodies. `NVIC` was absent for an unrelated reason: CMSIS
declares `__NVIC_EnableIRQ` and `#define`s `NVIC_EnableIRQ` onto it, and the
declaration lives in `core_cm33.h`, not `cmsis_gcc.h`.

**This is the third time a line-anchored scan has been defeated by a trailing
comment in this pipeline** (stage 03's `memset_bytes` declaration, stage 04's
multi-line declarations, now this). The replacement is structural: take the text
after the location comment, strip trailing comments, require a `;`.

### 1.2 Measured effect — a strict superset

| header | old | **new** | Δ |
|---|---:|---:|---:|
| `cmsis_gcc.h` | 0 | **121** | **+121** |
| `zephyr/kernel.h` | 467 | **857** | +390 |
| `time.h` | 497 | **888** | +391 |
| `zephyr/drivers/uart.h` | 116 | **226** | +110 |
| `zephyr/device.h` | 53 | **151** | +98 |
| `zephyr/devicetree.h` | 7 | **99** | +92 |
| `stdio.h` | 159 | **162** | +3 |
| `math.h` / `string.h` / `stdlib.h` / `ctype.h` / `errno.h` / `inttypes.h` / `assert.h` | 197 / 61 / 93 / 14 / 15 / 10 / 2 | unchanged | 0 |
| **total identifiers** | **996** | **1,406** | **+410, 0 LOST** |

`k_msleep`, `k_uptime_get`, `k_cycle_get_32`, `sys_clock_hw_cycles_per_sec`,
`__get_PSP`, `__DSB`, the whole `ARM_MPU_*` family and 121 CMSIS intrinsics were
all missing from the evidence the whole time. The gap was never confined to
`cmsis_gcc.h`; it was every `static inline` in every SDK header.

### 1.3 The residue the fix exposed, and its own closure: MACROS

`-aux-info` reports declarations and structurally cannot see a macro. That is
not hypothetical — it is precisely the `NVIC_EnableIRQ` case above. So a second
evidence axis was added: `gcc -dM -E` per header, minus the compiler's built-in
macro table and minus any prelude's own macros.

| | |
|---|---:|
| macro names measured | **27,838** |
| ...of which also a declared identifier | 27 |
| `zephyr/kernel.h` / `time.h` (devicetree-inflated) | 27,532 / 27,626 |
| `cmsis_gcc.h` | 37 |

Per-header macro *name* lists are recorded only for the C standard type/limit
headers (`stdint.h`, `stddef.h`, `stdbool.h`, `stdarg.h`, `limits.h`,
`inttypes.h`, `sys/types.h` — 822 names). Writing the devicetree table into a
committed evidence file would add megabytes to answer a question nothing asks;
the only angle headers that need name-level answers are the two that appear late
in a merged unit (§3.2). **A header with no name-level evidence is refused, not
assumed empty.**

### 1.4 What it cost the transformer, and what it caught

Stage 03 now refuses to hoist any symbol the SDK declares **or names as a
macro**:

| | stage 05 | **this pass** |
|---|---:|---:|
| declarations hoisted | 218 | **215** |
| refused, shadows an SDK **symbol** | 267 | **299** |
| refused, shadows an SDK **macro** | — | **1** (`k_fifo_put`) |
| refused, divergent spelling | 663 | **649** |
| `DEFECTS.json` entries | 930 | **949** |

`k_fifo_put` is the macro case working: Zephyr spells it
`#define k_fifo_put(fifo, data)` over `k_queue_append`, so a hoisted
`extern … k_fifo_put(…)` would have been rewritten by the preprocessor into a
declaration of a different symbol. No declaration-level evidence could see it.

### 1.5 And the whole thing is free

```
./stage_05_.../build_cohesive.sh app /private/tmp/g1-s6-evfix     exit 0
FLASH 956,276 B (97.33 %)   RAM 253,765 B   text 492,612 (Δ 0 on every section)
cmp /private/tmp/g1-s6-base/zephyr/zephyr.bin \
    /private/tmp/g1-s6-evfix/zephyr/zephyr.bin      -> IDENTICAL
```

**Correcting the SDK evidence, which moved 3 hoists and 33 refusals, produced a
byte-identical image.** A declaration emits nothing; this is the empirical proof
of that rather than the argument for it.

### 1.6 A staleness hole the fix exposed, now closed

`sdk_declared_symbols.json` lives under `recon/refactor/`, so `input_set` never
listed it, so `driver.py status` reported stages 03/04/05 as **current** while
their evidence had been regenerated underneath them. That is the one failure a
staleness mechanism must not have, and this pipeline had already been bitten by
its mirror image (README: a mechanism watching only the first member of a merged
unit "would report *current* while an upstream defect fix sat unnoticed inside
member 7").

`stagelib.EVIDENCE_INPUTS` now lists the two evidence files, `materialize`
records their hashes in every MANIFEST, and `staleness()` checks them.
`test_evidence.py` pins it.

---

## 2. Item 1 — internal linkage, decided by the LINK

### 2.1 The evidence

`recon/refactor/link_evidence.py`. `zephyr/zephyr.map` records the app link's
inputs as `LOAD` lines; each is run through `nm --undefined-only`. **Archives
are scanned whole**, including members this link did not pull in — a member that
is unused today is still evidence about what references a symbol, and
over-refusing costs a candidate while under-refusing costs an image.

```
link inputs                          66
symbols referenced by a relocation   5,420
  ...by a NON-app input              2,497
symbols defined by app/libapp.a      3,742
```

The question stage 05 could not answer, answered with a referrer:

```
_sbrk_r        referenced   by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a
__malloc_lock  referenced   by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a
_fstat_r       referenced   by  .../lib/thumb/v8-m.main+fp/hard/libc_nano.a
_puts_r        NOT referenced by anything
```

### 2.2 The source-text scan was not merely incomplete — it was wrong at 24 %

Both rules run over the same 1,158 external-linkage definitions of the 249
merged units:

| | |
|---|---:|
| source-scan candidates (stage 05's rule, re-measured here) | **240** |
| link-evidence candidates (relocation rule only) | **191** |
| both agree | 182 |
| **source scan says private, a relocation says otherwise** | **58** |
| link evidence says private, the heuristics refused | 9 |

The 58 are not newlib callbacks. They are ordinary firmware functions —
`bt_ancs_data_source_handler`, `flash_ops_thread`, `gatt_ccc_write`,
`mic_transm_thread`, `ble_work_thread`, `att_send_with_retry`,
`pairing_complete`, `l2cap_chan_disconnected_cb`, `adc_context_request_sampling`,
`draw_template_translate_screen`, … — reached through a table, a
`K_THREAD_DEFINE` in a hand-written integration TU, or a callback struct the
identifier scan does not follow. Applying stage 05's measured-but-unapplied set
would have made 58 symbols `static` that something calls.

*(The stage 05 report's figure was 241 candidates; 240 here, the one-symbol
difference being iteration 43's three moved sources.)*

### 2.3 The rule, and the belts that were kept

`static` iff: no relocation references it; not named by a linker fragment or by
`g1_app_symbols.h`; not `__asm__`-named or macro-renamed; not SDK-declared and
not an SDK macro; not a reserved identifier (C11 7.1.3); and — added after a
build failure, §2.4 — not already `static`.

The last three are belts over the link evidence and their cost is measured, not
assumed: keeping the C11 7.1.3 rule costs exactly one symbol (`_puts_r`) and
keeping the SDK rule costs four (`fmaxf`, `fminf`, `gpio_pin_configure_dt`,
`sys_dlist_init` — our tree defines external-linkage bodies for names the SDK
also publishes as `static inline`).

### 2.4 Two transformer bugs, both found by a build, both triaged (a)

**R4 bucket (a), round 1 — `error: duplicate 'static'`** in `ble/g1_ble_02.c`
and `notify/g1_notify_02.c`.

The walk back from a definition's parameter list to the start of its declaration
accepted a `}` as a boundary only when `depth[j-1] == 0`. `depth` is the depth
*before* a character, and the depth before a function body's closing brace is 1,
never 0 — so a `}` was **never** a boundary, the walk ran backwards over whole
function bodies, and three candidates in one unit all resolved to the start of
the same earlier definition. One function got two `static` keywords and two
others silently kept external linkage. The fix keys on the depth *after* the
brace, and the rewritten walk now asserts an invariant — the span between the
boundary and the parameter list must contain no `;{}#()` — so the same class of
error is caught at materialise time rather than at the build. `definition_start`
is deliberately structural, not line-anchored, for the reason §1.1 gives.

**R4 bucket (a), round 2 — the link failed:**

```
ld.bfd: zephyr/linker_zephyr_pre0.cmd:313: undefined symbol
        `wait_touch_key_release_or_timeout' referenced in expression
```

from `recon/symbols/g1_app_function_aliases.ld`:
`PROVIDE(prepare_new_task = wait_touch_key_release_or_timeout);`

The pinned-symbol rule named **three** linker fragments. The repository has
**eighteen**. This is the same shape as the first size gate keying on a list of
section names (README C7b) and as C6's rename wave: a rule keyed on a
hand-maintained list of filenames stops covering the thing it was written for,
silently. Linker fragments are now **discovered** by walking
`recon/{symbols,application,generated,board,wiring}`.

The same round exposed a second invisible reference class. The app CMakeLists
forces 20 gc-roots onto the link, but never writes the flag literally:

```cmake
foreach(_g1_root IN LISTS G1_RECOVERED_GC_ROOTS)
  zephyr_ld_options("-Wl,--undefined=${_g1_root}")
endforeach()
```

with the names in the generated `recon/generated/app_gc_roots.cmake`. A regex for
`--undefined=NAME` would have found **zero** of them. The resolver follows the
indirection structurally (literal names, `foreach(VAR a b c)`, and
`foreach(VAR IN LISTS L)` through the `set(L …)` that defines it) and recovers
**112** forced symbols across 8 CMake files.

**Both of these are exactly why README C6 requires a real link as the gate for
this transformation class: a linker-script expression and a `--undefined=` flag
name a symbol with no relocation anywhere, so no amount of `nm` evidence can see
them.** The link is the only oracle that can, and it was.

### 2.5 The three candidate sets, in order

| rule | candidates |
|---|---:|
| source-text scan (stage 05, unapplied) | 240 |
| + link evidence replaces the reference test | 191 |
| + SDK / reserved / already-static belts | 172 |
| + **all 18 linker fragments discovered** | 158 |
| + **`--undefined=` gc-roots resolved** | **137 — applied** |

Refusals of the final rule, over 1,158 definitions:

```
referenced_by_a_relocation                             795
named_by_a_linker_fragment_or_the_symbols_header       197
asm_named_or_macro_renamed                               4
declared_by_an_sdk_header                                4
```

Applying it also rewrote **18** in-unit `extern` declarations of those symbols to
`static` (C11 6.2.2p7 makes a `static` definition after a non-`static`
declaration a hard error) and **0** module-header declarations — the module
headers publish no symbol that became private.

### 2.6 The build, and what it changed

```
build exit 0, first try after the two transformer fixes
FLASH 955,996 B (97.30 %)   Δ −280 B      RAM 253,765 B   Δ 0

driver.py size-gate 7 <stage-06 build> <stage-07 build>
  declared size-changing -> measured size-changing   PASS   oracle_required TRUE
  section deltas  { text: -276, rodata: -8, datas: 0, bss: 0, noinit: 0 }
```

| | stage 06 | **stage 07** |
|---|---|---|
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| distinct sized text symbols | 2,935 | **2,922 (−13)** |
| build-log `warning:` lines | 2,975 | **3,092 (+117)** |
| `-Wunused-function` diagnostics | 2 | **120** |
| `check_ram_pin_collisions` bound OK / escaping / unknown-in-live-object | 627 / 0 / 0 | **596 / 0 / 0** |

**The +118 unused-function warnings are the most valuable output of this stage
and they are not noise.** Giving a symbol internal linkage lets the compiler see
that nothing calls it. **120 distinct recovered functions are now provably
dead** — `bt_conn_tx_process`, `bt_gatt_service_init`, `bt_smp_ah`,
`boot_write_image_trailer_magic`, `clock_control_nrf_init`,
`cbor_map_decode_fields`, `att_prepare_write_req`, … Only 13 leave the image,
because `--gc-sections` had already dropped the rest; what is new is that we now
have their **names**. This is README C4 bucket (b) again: the compiler finds what
the parity harness structurally cannot (the harness constrains a body, not
whether anything reaches it). The full list is in the stage 07 build log.

The RAM-pin count moving 627 → 596 is the same effect seen from the linker: 31
absolute RAM symbols are no longer emitted because the only code referencing them
was dead. `bound_pins_escaping_their_owner` and `unknown_inside_a_live_object`
stay at **0**, which is the property that matters.

---

## 3. Items 2 and 3 — stage 06, declared `byte-identical` and measured so

### 3.1 D — module-private declaration demotion

Stage 03 hoisted a declaration into `g1_<module>.h` when two or more of the
module's files agreed on its type. Stage 04 then merged most of those files, so
a declaration that needed to be module-wide when it had eleven users may now have
one. D moves such a declaration into that single unit, at the exact point where
the header was included (so declare-before-use holds by construction), and
deletes outright a hoisted declaration with no user left.

| | |
|---|---:|
| generated module headers | 19 |
| declarations they publish | 215 |
| **demoted into their only user** | **4** |
| withdrawn as having no user at all | **0** |
| kept — more than one user | **211** |

**The measurement is the finding, and it is a negative one: 211 of 215 hoisted
declarations still have two or more users after the merge.** The module headers
are not over-publishing. Stage 03's ≥2-user hoist rule and stage 04's
consecutive-run merge simply do not overlap much — which is the same fact §4
below measures from the other direction.

### 3.2 H — include hoisting, under two checks

Stage 05 deliberately never *moved* an include, leaving 158 of 249 units with a
directive after their first block — **285 in total**, measured:
`<stdint.h>` 88, `"…/g1_dedupe.h"` 62, `"…/g1_log.h"` 56, `"g1_lib.h"` 22,
`<stddef.h>` 8, and 49 others, all quoted repository headers.

Hoisting is permitted only when both hold:

1. **no preprocessor directive other than `#include`** between the unit's first
   include block and the directive's own position — which guarantees the include
   is not inside a conditional and that no `#define`/`#undef` is being reordered
   against it;
2. **no identifier in the code being jumped over is a macro of that header.**
   For a quoted repository header the macro set is computed transitively; for an
   angle header it comes from §1.3's measured evidence, and **a header with no
   name-level evidence is refused**.

| | |
|---|---:|
| late includes seen | **285** |
| **hoisted** | **251** |
| refused — intervening directive (`define` 24, `define\|else\|endif\|ifdef` 2, `undef` 2, `ifdef` 1) | **29** |
| refused — intervening code names a macro of the header (`g1_lib.h` 3, `g1_log.h` 1, `g1_display.h` 1) | **5** |

Those 5 are the check earning its place: three units jump over code that names a
macro `g1_lib.h` defines, and moving the include above it would have changed what
that code means without changing what it looks like.

### 3.3 Result

| | stage 05 | **stage 06** |
|---|---:|---:|
| `#include` directives inside merged units | 848 | 848 (H moves, never deletes) |
| worst unit | 6 | 6 |
| units at exactly **1** include block | **21** | **112** |
| units at 2 blocks | 135 | 123 |
| units at 3 blocks | 77 | **13** |
| units at 4 blocks | 13 | **1** |
| units at 5 blocks | 3 | **0** |

*(848 rather than the stage 05 report's 850: this count is taken on the
comment-stripped view, and iteration 43 moved three sources. Only the deltas
within this table are comparable.)*

```
build exit 0
FLASH 956,276 B (97.33 %)   RAM 253,765 B
cmp stage05/zephyr.bin stage06/zephyr.bin   -> IDENTICAL

driver.py size-gate 6 <stage-05 build> <stage-06 build>
  declared byte-identical -> measured BYTE-IDENTICAL   PASS   oracle_required FALSE
  deltas { text: 0, rodata: 0, datas: 0, bss: 0, noinit: 0 }   28/28 alloc sections
```

**Stage 06 needs no oracle of its own: its image is the same bits as stage 05's.**

---

## 4. Item 4 — call-order reordering is a measured NO-OP, and that is the finding

Stage 08 orders each merged unit's member blocks by a stable topological sort of
the unit's own call graph (callee before caller), refusing a unit whose member
blocks carry a preprocessor directive, declare a file-scope `static`, or whose
call graph is cyclic.

It was declared `size-changing` **on principle** — reordering moves every
function after the first change point even at an identical byte total, and the
Stage 04 gate established that it is layout, not size, that re-phases a bus
stream. That declaration was not weakened by any measurement.

```
merged units seen                                 249
units refused: member block carries a directive    60
units refused: member block declares a static      71
units in call order already                       118
units reordered                                     0
member blocks moved                                 0
files changed                                       0
```

Instrumented over the 118 reorderable units, to say *why* rather than report a
zero:

| | |
|---|---:|
| internal call edges, all 118 units combined | **11** |
| units with at least one internal call edge | **9** |
| of those, already callee-before-caller everywhere | **9** |
| edges pointing backwards | **0** |

**Stage 04's merge groups sources that are adjacent in link order, and adjacency
in link order is not call relatedness: 249 cohesive units contain eleven internal
call edges between them.** There is nothing to reorder. Stage 08's tree hash is
`d69a5df6…` — byte-for-byte identical to stage 07's — so the stage was not built
and needs no oracle.

The honest consequence: **call-order is not what stands between these files and
readable source; the grouping is.** A merge keyed on call structure rather than
on consecutive retained-source runs would produce units that have an order worth
sorting. That is a stage-04 change, not a stage-08 one, and it is `size-changing`
in the way stage 04 already is.

---

## 5. Gate ladder — measured at the final inputs

| gate | stage 05 baseline | **stage 06 (DH)** | **stage 07 (S)** | **stage 08 (R)** |
|---|---|---|---|---|
| app build | exit 0 | **exit 0** | **exit 0** | not built — tree identical to stage 07 |
| app FLASH | 956,276 B / 97.33 % | **956,276 B (Δ 0)** | **955,996 B / 97.30 % (Δ −280)** | — |
| app RAM | 253,765 B / 56.32 % | **Δ 0** | **Δ 0** | — |
| `text` | 492,612 | **Δ 0** | **492,336 (Δ −276)** | — |
| `rodata` / `datas` / `bss` / `noinit` | 456,536 / 3,327 / 189,230 / 60,021 | **Δ 0 each** | **−8 / 0 / 0 / 0** | — |
| `zephyr.bin` vs previous stage | — | **`cmp` IDENTICAL, 956,276 B** | DIFFERS (declared) | — |
| `nm -u` undefined | 0 | **0** | **0** | — |
| duplicate global definitions | 0 | **0** | **0** | — |
| distinct sized text symbols | 2,935 | **2,935** | **2,922** | — |
| `warning:` log lines | 2,975 | **2,975 (Δ 0)** | **3,092 (+117, §2.6)** | — |
| **`driver.py size-gate`** | — | **declared `byte-identical` → measured `byte-identical`, PASS, `oracle_required` FALSE** | **declared `size-changing` → measured `size-changing`, PASS, `oracle_required` TRUE** | — |

Applying to every stage of this pass:

| | |
|---|---|
| `driver.py check-addresses` 4-5, 5-6, 6-7, 7-8 | **all identical, 2,567 addresses both sides on every pair** |
| `tools/verify_data.py` | **995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)** |
| `check_ram_pin_collisions` (stage 06 ELF) | **627 bound OK / 0 escaping / 0 raw-literal-in-a-live-object / 0 unknown-inside-a-live-object** |
| `check_ram_pin_collisions` (stage 07 ELF) | **596 / 0 / 0 / 0** (31 fewer absolute RAM symbols emitted — §2.6) |
| `check_thread_create_stack_args --trials 120` | **10 / 10 PASS, exit 0** |
| `gen_retained_sources.py --check` | **"retained source lists are current"** |
| **refactor test suite** | **139 / 139 PASS** (was 105 — **34 new tests**) |
| idempotence, stage 06 | MANIFEST `8e3e1090…` → `8e3e1090…`, tree `a7607d11…` → `a7607d11…` — **byte-identical** |
| idempotence, stage 07 | MANIFEST `0936795a…` → `0936795a…`, tree `d69a5df6…` → `d69a5df6…` — **byte-identical** |
| idempotence, stage 08 | MANIFEST `a23a10b3…` → `a23a10b3…`, tree `d69a5df6…` → `d69a5df6…` — **byte-identical, and equal to stage 07's** |
| `driver.py status` | **stages 00–08 all current**, 0 inputs changed (99 left stale, the retired probe) |

**Net core: untouched.** No net input changed and no net build was run, so
`check_net_raw_literals` and `verify_net_stock_data_window` — both of which need
a net ELF — are recorded as **NOT RUN**, not as passed. The 225,581 B freeze
holds by construction.

**The per-object `.rodata` vs `app_update.bin` comparison (1,325 / 14 in earlier
reports) was NOT RUN**: the script that produced it lived in a previous pass's
scratch directory and is not in the repository. `verify_data.py` — the data gate
AGENTS.md names — was run and is 100 %.

### 5.1 The new tests, and what each pins

`test_evidence.py` (17) and `test_unit_composition.py` (17). Every one pins a
bug that was **measured**, not imagined:

* the `-aux-info` parser reads a definition line carrying a trailing
  `/* (params) */` (§1.1) and refuses a line with no terminating `;`;
* `cmsis_gcc.h` contributes > 100 identifiers, `__DSB` / `k_msleep` /
  `__NVIC_EnableIRQ` are present, `NVIC_EnableIRQ` is present as a **macro** and
  absent as a symbol;
* per-header macro detail exists for `stdint.h`/`stddef.h` and is **absent** for
  `zephyr/kernel.h`, so a consumer must read it as "no evidence";
* `nm`'s `U` and `w` are both references; `_sbrk_r`/`__malloc_lock`/`_fstat_r`
  are attributed to a C library archive;
* the evidence files are watched by staleness;
* `top_include_block_end`, and hoisting refusing on an intervening `#define`, on
  a macro collision, and on a header with no macro evidence;
* `definition_start` resolving three definitions in one unit to three distinct
  offsets (the `duplicate 'static'` regression, §2.4);
* `foreach(VAR IN LISTS …)` gc-root resolution, and that ≥ 15 linker fragments
  are **discovered** — the test fails if the 3-file list comes back;
* stage 08 lifting the unit include block out of the first member, moving a
  callee before its caller, and refusing on a directive, a `static`, or a cycle.

---

## 6. The thing that changed underneath this pass: **Stage 04-B FAILED its R7 gate**

The concurrent agent ran the oracle on stage 04 sub-batch B while this pass was
running, and wrote `recon/analysis/stage04b_r7_validation.md`. Its verdict is not
mine and is cited, not claimed:

> **STAGE 04 SUB-BATCH B FAILS R7** — 8 refactor regressions on navigation, 1 on
> dashboard, at HEAD `fc11c2c8`. Every regressed hash is byte-for-byte the value
> **sub-batch A** produced: `twim1 p1_boot` 371 → 373, OPT3001 33 → 35, the
> merged-bus sha, `twim2 p1_boot` sha, `regprog` sha, `counters/RADIO_TX`
> `0x232` → `0x234`. The OPT3001 poll *period* is unchanged (0.350310 s,
> identical to base) and the train's **phase** moves **−100.52 ms**, against
> sub-batch A's −100.7 ms — two different sub-batches, two different linked
> sizes, the same displacement to within 0.2 ms. All four acceptance
> framebuffers remain `cmp`-identical to the goldens on both images.

That single paragraph resets what this pass can claim.

* **Stage 05 and stage 06 are `cmp`-identical to stage 04-B's image.** They do
  not merely *inherit an unproven status* — they inherit a **measured failure**,
  exactly and completely. Nothing in this pass makes it better or worse.
* **Stage 07 is a fifth linked size that has never been booted** (−280 B from a
  base that is already −76 B from stage 03). Given a mechanism that produced the
  same −100 ms displacement from −12 B and from −76 B, there is no honest reason
  to expect −280 B to land anywhere in particular. Its manifest says
  `"oracle_required": true` and I make **no R7 claim** for it.
* **Stage 08 requires nothing**, being byte-for-byte stage 07.

---

## 7. Is this production-grade — and what is still in the way?

**Answered directly, because the brief asks directly.**

**What genuinely improved.** The two evidence files are now the kind of artifact
this project should have had from the start: a question about the SDK or about
the link is answered by running the compiler or the linker and recording the
answer, not by a regex over source text. Both replaced a heuristic that was
measurably wrong — one by 410 identifiers, the other by 58 of 240 candidates —
and both were themselves caught being wrong by a build. The composition depth is
real: 112 of 249 units now have exactly one include block against 21, and 137
symbols that had no business being global are `static`. And 120 dead functions
have names for the first time.

**What is still not production-grade, unchanged and honestly stated.**

* **451 of 700 translation units are still a single source file.** The merge is
  by consecutive link-order runs, which §4 measured to be nearly orthogonal to
  call structure: 11 internal call edges across 249 units. These are cohesive
  *files*, not cohesive *modules*.
* **`unsorted/` is still 148 absorbed files across 16 units** and
  `refactor_module_map.json` has not been regenerated.
* **No merged unit has a header of its own** describing its interface.
* **949 `DEFECTS.json` entries** — 649 divergent declarations, 299 SDK-symbol
  shadows, 1 SDK-macro shadow — are catalogued and unrepaired. R1 puts that work
  in the canonical trees, which this pipeline may never write. The Stage 04 gate
  established these are candidate **firmware defects**, not merely merge
  blockers; one of them froze the device clock for a whole run.
* **The net core is untouched.**

### Is any of it blocked on something other than the oracle?

**Yes — and after §6 the oracle is no longer the blocker at all.** It has been
run. It said no.

The blocker is now a **decision**, and it has been costed twice:

1. **Fix the boot-path timing gap.** Our build is +3.45 ms / +6.4 ms late to the
   first bus transaction (`stage04_r7_validation.md` §4.3, which also shows the
   +3.45 ms half is *not* codegen-carried). While that gap exists, any change to
   linked size in either direction lands the OPT3001 poll train and the LSM6DSO
   poll pair in a different place inside the 6 s capture window, and every
   size-changing stage fails the same two `p1_boot` streams for the same reason.
   This is not a refactor problem; it is a reconstruction problem the refactor
   keeps re-discovering.
2. **Or deliberately re-baseline those two `p1_boot` streams**, with the decoded
   diffs as the record of what was given up — not by widening a tolerance. The
   decodes now exist for three independent sub-batches (A, AB, B) and agree to
   0.2 ms, which is as strong a case as such a re-baseline could ask for.

Until one of those happens, **no size-changing stage can ever pass R7**, and the
pipeline can only land stages that are `cmp`-identical at the image level. Stage
06 is one such stage and it landed. Stage 07 cannot be, by construction — the
whole point of `static` is to change codegen.

Two smaller things are blocked on nothing at all:

* **Regenerating `refactor_module_map.json`** so `unsorted/` stops being the
  third-largest module. Pure metadata; no image effect.
* **Repairing the 949 declaration disagreements** in the canonical trees. Owned
  by the parity agent (R1), needs no oracle, and §8.1 of the Stage 04 gate report
  showed the payoff is defect repair, not merge yield.

---

## 8. What I did NOT do, and everything quarantined, with measured reasons

1. **I did not run the emulator oracle.** Renode is owned by the concurrent
   agent and this brief forbids it. **Stage 07 is `size-changing` at −280 B of
   `.text` and an oracle run is REQUIRED before it is landed.** I make no R7
   claim for it. Stages 06 and 08 need no oracle — 06's image is `cmp`-identical
   to stage 05's and 08's tree is byte-for-byte stage 07's.
2. **I did not build stage 08.** Its tree hash equals stage 07's exactly
   (`d69a5df6…`, measured), so a build would produce stage 07's image by
   construction. Recorded as not-built, not as passed.
3. **I did not attempt a call-structure-driven MERGE** (as opposed to a
   reordering). §4 shows that is where the yield is, but it is a change to
   stage 04's partition, it is `size-changing`, and it would need the oracle that
   §6 has just shown stage 04 cannot currently pass.
4. **I did not repair a single declaration disagreement.** R1. They are handed
   over refreshed in `stage_03_module_structure/DEFECTS.json`: **649**
   divergent-spelling, **299** `reconstructed_declaration_shadows_an_sdk_symbol`
   (up from 267 — the §1.2 evidence fix made 32 more visible), **1**
   `reconstructed_declaration_shadows_an_sdk_macro` (`k_fifo_put`).
5. **I did not act on the 120 dead functions** stage 07 exposed. They are a
   defect list for the parity agent, not a deletion this pipeline may make: a
   function the shipped image contains and ours never calls is evidence about a
   missing call site, and deleting it would destroy that evidence. The names are
   in the stage 07 build log (`-Wunused-function`).
6. **I did not restructure the net core** and ran no net gate that needs a net
   ELF (§5).
7. **I did not regenerate `refactor_module_map.json`.**
8. **I did not regenerate stage 99**, the retired diagnostic; `status` reports it
   stale with 781 inputs moved.
9. **`cfg_verify` was not run and is not cited.** Every number here comes from a
   build, a `cmp`, an ELF section table, an `nm`, a `-aux-info`/`-dM` probe, or a
   test run.
10. **I did not run the per-object `.rodata` vs `app_update.bin` comparison**
    (§5): the script is not in the repository.
11. **The macro evidence is name-level for 7 headers only** (§1.3). The other 13
    are recorded by count. A hoist decision needing a name-level answer for one
    of those 13 is **refused**, which is the correct failure direction, but it is
    a limit and not a proof.
12. **The link evidence describes one build.** It is regenerated from a build
    directory and its provenance records which one
    (`/private/tmp/g1-s6-base`). A source change that starts calling a symbol
    from a new place invalidates it — which is why it is watched by
    `stagelib.EVIDENCE_INPUTS` (§1.6) and why the stage must be regenerated, not
    patched, when it moves.
13. **Nothing was committed.** The tree is left dirty.

### Quarantine, stage 06 — 34 directives and 211 declarations

| | |
|---|---:|
| includes refused, intervening preprocessor directive | 29 |
| includes refused, intervening code names a macro of the header | 5 |
| declarations kept in the module header, more than one user | 211 |

### Quarantine, stage 07 — 1,021 definitions left with external linkage

```
referenced_by_a_relocation                             795
named_by_a_linker_fragment_or_the_symbols_header       197
asm_named_or_macro_renamed                               4
declared_by_an_sdk_header                                4
```

### Quarantine, stage 08 — 131 units, and 118 with nothing to do

```
member_block_carries_a_preprocessor_directive           60
member_block_declares_a_file_scope_static               71
(reorderable, but already in call order)               118
```

### Inherited unchanged

Stage 04's 30 shape-quarantined files and 878 blocked adjacencies; stage 05's
0 unguarded headers and 0 disagreeing declarations; stage 03's 18 stdlib-typedef
shadowing files and 15 multi-declaration-line files.

---

## 9. Footprint — everything this pass wrote

```
 M recon/refactor/sdk_symbols.py
        structural -aux-info parser (the trailing-comment fix, §1.1);
        probe_macros / MACRO_DETAIL_HEADERS / load_macros / load_macro_detail
 M recon/refactor/sdk_declared_symbols.json     996 -> 1,406 symbols, + 27,838 macros
 M recon/refactor/stagelib.py
        EVIDENCE_INPUTS / evidence_hashes(); staleness now watches them
 M recon/refactor/driver.py
        stages 06/07/08 registered with their declared codegen classes;
        materialize records evidence_inputs in every MANIFEST
 M recon/refactor/transforms/t03_module_structure.py
        refuse to hoist a symbol that is an SDK MACRO, as a distinct defect class
 M recon/refactor/stage_0{0..5}_*/MANIFEST.json, stage_03/DEFECTS.json,
   stage_05/QUARANTINE.json                                        (regenerated)
?? recon/refactor/link_evidence.py               (the link evidence generator)
?? recon/refactor/link_referenced_symbols.json   (5,420 referenced symbols, 66 inputs)
?? recon/refactor/transforms/t06_unit_composition.py
?? recon/refactor/transforms/t07_internal_linkage.py
?? recon/refactor/transforms/t08_call_order.py
?? recon/refactor/test_evidence.py               (17 tests)
?? recon/refactor/test_unit_composition.py       (17 tests)
?? recon/refactor/stage_0{6,7,8}_*/             (MANIFEST/PARITY_MAP/QUARANTINE + tree/)
?? recon/refactor/stage_0{6,7}_*/SIZE_GATE.json
?? recon/analysis/staged_refactor_stage06.md     (this file)
```

`recon/refactor/.gitignore` already excludes `stage_*/tree/`. **No canonical
tree, no `recon/symbols`, no `recon/application`, no `tools/` module, no emulator
report, no linker script and nothing under `~/Projects/armemul` was written** —
structurally enforced by `guard.check_write`, whose refusal tests still pass.
`stage_04/SIZE_GATE.json` and `stage_05/SIZE_GATE.json` are dirty in
`git status` and are **the concurrent agent's**, not mine (they record its own
build directories, `/private/tmp/g1-s4b-*`); so is
`recon/analysis/stage04b_r7_validation.md`.

**Concurrency note.** The concurrent agent regenerated stages 00–05 for its own
gate run during this pass. The regeneration is deterministic and my stage 06/07/08
idempotence checks re-derived from the on-disk stage 05 tree and reproduced their
manifests byte-identically, so nothing here was measured against a moving input.
If that agent regenerates stage 03 with the pre-fix SDK evidence, stages 03–08
must be **regenerated, never patched** — 03's harvest is 215 hoists at the
corrected evidence and 218 at the old.

---

## 10. Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

$V recon/refactor/driver.py status                     # expect 00-08 current
for n in 0 1 2 3 4 5 6 7 8; do $V recon/refactor/driver.py materialize $n; done
for a in 0 1 2 3 4 5 6 7; do $V recon/refactor/driver.py check-addresses $a $((a+1)); done
$V -m unittest discover -s recon/refactor -p 'test_*.py'        # 139/139

# the two evidence files (each needs ONE successful build for its -I set / map)
$V recon/refactor/sdk_symbols.py generate \
   --command-file <a gcc line from build/compile_commands.json> --build <that build>
$V recon/refactor/link_evidence.py generate --build <that build>

# the four images
./recon/refactor/stage_05_cohesive_composition/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s6-base
./recon/refactor/stage_06_unit_composition/tree/recon/application/build_cohesive.sh      app /private/tmp/g1-s6-s06
./recon/refactor/stage_07_internal_linkage/tree/recon/application/build_cohesive.sh      app /private/tmp/g1-s6-s07
# stage 08 is byte-for-byte stage 07; comparing tree hashes is the check.

$V recon/refactor/driver.py size-gate 6 /private/tmp/g1-s6-base /private/tmp/g1-s6-s06
$V recon/refactor/driver.py size-gate 7 /private/tmp/g1-s6-s06  /private/tmp/g1-s6-s07
cmp /private/tmp/g1-s6-base/zephyr/zephyr.bin /private/tmp/g1-s6-s06/zephyr/zephyr.bin

# sub-batches:  G1_STAGE06_BATCH={D,H,DH,OFF}  G1_STAGE07_BATCH={S,OFF}
#               G1_STAGE08_BATCH={R,OFF}
```

## 11. THE ONE THING THE NEXT PASS MUST DO

**Not another stage.** Stage 04 has now failed R7 twice, from two different
sub-batches, at two different linked sizes, with the same −100 ms displacement
of the same OPT3001 poll train. Landing a sixth composition stage on top of a
merge that cannot pass its gate adds polish to a tree that is not accepted.

Close the **boot-path timing gap** — our build is +3.45 ms / +6.4 ms late to the
first bus transaction, and `stage04_r7_validation.md` §4.3 already showed the
+3.45 ms half is not codegen-carried, which means it is findable — **or** take
the decision to re-baseline navigation `twim1 p1_boot` and `twim2 p1_boot`
against the three independent decoded diffs that now agree to 0.2 ms. Until one
of those happens, every `size-changing` stage this pipeline produces is
pre-failed, and stage 07's 137 `static` symbols, its −280 B and its 120 dead
functions sit behind the same wall as stage 04's merge.
