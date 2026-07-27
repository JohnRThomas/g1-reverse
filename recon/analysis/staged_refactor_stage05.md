# Stage 04 rework + Stage 05 — written incrementally as the work ran

**Nothing committed.** Every number below comes from a command that was run.
Where a number was later superseded by a re-measurement, the earlier number is
corrected in place with a note rather than deleted.

Starting point, measured rather than inherited:

```
HEAD          ff99f0c6  "Stage 04 FAILS R7 -- and the failing half is the SAFE one;
                         dashboard spim_a root-caused"
              (parents e78474a4 "Type-disagreement repair 2", 3b8242fa "refactor Stage 04")
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)
```

`driver.py status` at the start of this pass:

| stage | state | inputs unchanged | inputs changed |
|---|---|---:|---:|
| 00 snapshot | **stale** | 1,976 | **653** |
| 01 literal_inline | current (rel. stage 00's tree) | 2,629 | 0 |
| 02 block_dedupe | current | 2,629 | 0 |
| 03 module_structure | current | 2,629 | 0 |
| 04 cohesive_tu | current | 2,629 | 0 |
| 99 defect_probe | stale | 2,304 | 308 |

The 653 moved inputs are commit `e78474a4`, the type-disagreement repair 2
(833 → 677 disagreements, flash payload byte-identical). **Stage 00 was stale
before this pass began**, so every count carried into the brief — 695 TUs, 586
TUs, 833 defects — had to be re-measured. All of them moved. That is the fourth
consecutive pass in which this has happened; it is the mechanism working.

---

## 1. Regeneration, and the two latent defects it exposed

Stages 00 → 01 → 02 → 03 → 04 were **regenerated, never patched**.

```
materialize 0   2,629 files / 2,567 parity rows / 0 transformations
materialize 1   2,629 files / 2,567 rows / 100 candidates / 192 sites inlined
materialize 2   2,629 files / 2,567 rows / 3,116 / 45 / 367 / 139 / 47
materialize 3   2,629 files / 2,567 rows / 1,621 moved
```

Stage 03's own harvest moved a long way on the repair:

| | stage 04's report (HEAD `192349af`) | **re-run at HEAD `ff99f0c6`** |
|---|---:|---:|
| module headers generated | 17 | **20** |
| declarations hoisted | 142 | **255** |
| `DEFECTS.json` entries | 833 | **664** |

Then the **stage 03 baseline did not compile**, and under R4 that is proof the
transformer is wrong. It failed twice, on two different mechanisms, and both are
bucket-(a) transformer bugs whose payload is a real corpus shape.

### 1.1 Round 1 — a module header published `k_sem_give` into a TU that gets it from Zephyr

```
unsorted/g1_unsorted.h:38:13: error: conflicting types for 'k_sem_give';
    have 'void(int)'
  .../zephyr/include/generated/syscalls/kernel.h:1110:20: note: previous
    definition of 'k_sem_give' with type 'void(struct k_sem *)'
unsorted/g1_unsorted.h:39:13: error: conflicting types for 'k_sleep'
unsorted/g1_unsorted.h:44:12: error: conflicting types for 'strlen';
    have 'int(int)'
```

`unsorted/imu_fusion_init.c` includes `<zephyr/kernel.h>` on **line 1** and the
generated module header on line 43. It never declared `k_sem_give` itself — it
acquired the reconstructed spelling from the header, which is exactly what a
module header is for.

This is the same shape as stage 04 §2's `wchar_t` failure: the concurrent
agent's repair made three declarations newly *type-identical* across
`unsorted/`, so stage 03 — unchanged — started hoisting them. **Stage 03 landed
green and is red at these inputs through no change of its own.** A transformer
whose safety depends on which declarations happen to agree this week is not
safe; it is lucky.

**The fix is an evidence task, not a heuristic**, and it is the one stage 04 §10
step 3 already named: `recon/refactor/sdk_symbols.py` compiles a probe
translation unit per angle header with the project's own flag set (lifted
verbatim from a real `build_cohesive.sh` compile command) and `-aux-info`, which
makes GCC emit one line per declaration it saw. The result is committed as
`recon/refactor/sdk_declared_symbols.json` so the transformer stays a pure
function of its inputs and needs no Zephyr build directory.

Measured: **20 headers probed, 996 identifiers.**

| | |
|---|---:|
| angle headers the app corpus includes | 15 |
| identifiers from those alone | **746** |
| standard headers probed although no corpus file includes one today | 5 (`stdio.h`, `stdlib.h`, `errno.h`, `time.h`, `assert.h`) |
| identifiers those add | **250** |
| headers needing a prelude to compile standalone | 1 — `cmsis_gcc.h` (uses `int32_t` without including `<stdint.h>`) |
| headers that would not compile standalone at all | **0** |

Per header: `zephyr/kernel.h` 467, `time.h` 497, `math.h` 197, `stdio.h` 159,
`zephyr/drivers/uart.h` 116, `stdlib.h` 93, `string.h` 61, `zephyr/device.h` 53,
`errno.h` 15, `ctype.h` 14, `inttypes.h` 10, `zephyr/devicetree.h` 7,
`assert.h` 2, and **0** each for `stdint.h`, `stddef.h`, `stdbool.h`,
`stdarg.h`, `limits.h`, `sys/types.h`, `cmsis_gcc.h`.

*Probing the five headers no corpus file includes is a deliberate choice with a
specific justification rather than "to be safe": stages 03–05 actively change
which declaration reaches which translation unit, so "no file includes
`<stdio.h>` this week" is not a property a transformer may rely on. It is not
hypothetical either — `core/g1_core.h` publishes*
`extern unsigned int snprintf(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);`
*today, and GCC already emits `'snprintf' is declared in header '<stdio.h>'` as
a note. It is one `#include` away from being the `k_sem_give` error.*

**Measured residue, stated rather than buried:** `cmsis_gcc.h` compiles with the
`<stdint.h>` prelude but contributes **0** identifiers, because its bodies are
`__STATIC_FORCEINLINE` definitions that `-aux-info` does not report (verified by
hand: the probe's `.aux` file has 122 lines, none containing `NVIC`). 46 corpus
files include it. So a hoisted declaration colliding with a CMSIS intrinsic
would still get through. No such hoist exists today — `test_size_gate.py`
asserts the property over the materialised tree — but the evidence file does not
prove it for that one header.

**The refusal, and its measured cost.** Stage 03 now refuses to hoist any symbol
in the evidence set, reporting it as a new `DEFECTS.json` class
`reconstructed_declaration_shadows_an_sdk_symbol`. It is deliberately *not*
"reconcile with the SDK prototype": rewriting a reconstructed declaration to
match a header is inventing evidence about the shipped ABI, which this
transformer refuses everywhere else.

| | |
|---|---:|
| symbols refused | **267** |
| of those, refused **necessarily** — a member of that module really does include an angle header that declares the symbol | **89** |
| refused only by the broader rule | **178** |
| hoists lost (255 → 206 before the round-2 fix) | **49** |

Modules whose members include a *declaring* angle header at all:
`app` (8 headers), `core`, `display`, `notify`, `unsorted` (`zephyr/kernel.h`),
`esb`, `input`, `lib` (`string.h` and friends). The other 15 modules include
none, which is why the precise rule is so much cheaper.

I kept the broader rule. The reason is a property, not caution: **a generated
module header must not publish a declaration of a name the C library or Zephyr
owns**, whatever a module member happens to include this week — and the 267
entries are themselves a defect list, in exactly the sense
`stage04_r7_validation.md` §8.1 established when one `DEFECTS.json` entry turned
out to freeze the device clock.

### 1.2 Round 2 — a trailing comment made a declaration invisible to the safety rule

```
ui/navigation/ui_navigation_task.c:127:13: error: conflicting types for
    'memset_bytes'; have 'void(void *, int, size_t)'
  ui/navigation/g1_navigation.h:32:13: note: previous declaration with type
    'void(void *, int, int)'
```

The offending line is

```c
extern void memset_bytes(void *, int, size_t);                /* memset */
```

Stage 03's declaration scanner is `^[ \t]*extern[ \t].*;[ \t]*$` — the
terminating `;` anchored at **end of line**. The trailing comment moves it, so
the declaration is invisible; stage 03 judged `ui/navigation` unanimous on
`(void*,int,int)`, hoisted that, and the build failed against the very
declaration the scanner could not read.

Stage 04 fixed exactly this class for *its* scanner (§4.3 item 2, multi-line
declarations) and stage 03 was never brought along. A declaration the safety
rule cannot read is a declaration the safety rule cannot protect.

**Fix:** a length- and newline-preserving comment blanker (`_blank_comments`),
so the scan runs on a comment-free view whose offsets and line numbers stay
aligned with the original and the two can be zipped line for line at withdrawal
time. Withdrawal additionally refuses to drop a line whose tail opens a comment
it does not close, which would swallow the following lines.

Effect on the harvest: hoists **206 → 218**, refusals **599 → 664** — the
scanner now sees declarations it used to miss, and some of them disagree.

### 1.3 Stage 03 after both fixes

```
materialize 3   2,629 files / 2,567 rows / 1,621 moved / 704 content-changed
                19 module headers / 218 declarations hoisted
                664 divergent + 267 sdk-shadowing = 931 DEFECTS.json entries
baseline build  exit 0, 0 errors
                FLASH 956,356 B / 982,528 B = 97.34 %   RAM 253,765 B = 56.32 %
```

---

## 2. Stage 04 reworked on the R7 evidence — sub-batch **B** is the default

The gate record's instruction is explicit: do not bisect sub-batch A looking for
a guilty file, because there is no guilty file. The measurement is that **all
eight regressions are A's** and that AB-against-A gives **0 regressions and 2
improvements**. So the stage is restructured as a transformer change: `A` and
`B` now **partition** the clean multi-member runs, and `B` is the default.

```python
volatile_free = not any(info[m]["has_volatile"] for m in members)
if batch == "A":  return volatile_free
if batch == "B":  return not volatile_free
return True                      # AB
```

**What the `volatile` token actually partitions is shape, not risk.** This
corpus models every global as a `volatile` absolute-address pointer, so a file
*without* the token is the unusual one: a pure computational leaf (libm) or a
forwarding thunk that touches no global at all. Sub-batch A is therefore
precisely the set of files whose merging lets a 28-byte thunk collapse into a
4-byte tail branch — which is exactly what its entire −16 B codegen delta was
(`k_uptime_get_3` 28 → 4 B, `__ieee754_pow` 2,480 → 2,488 B). The half selected
as low-risk on a sound R8 argument was the half most likely to change linked
size, and linked size is the carrier.

The R8 argument is not refuted by any of this. It is irrelevant.

### 2.1 The partition, measured at these inputs

Four materialisations of the same partition, differing only in selection:

| batch | app TUs | merged units | files absorbed | adjacencies blocked |
|---|---:|---:|---:|---:|
| `OFF` (identity) | 1,615 | 0 | 0 | 877 |
| **`A`** | 1,514 | 45 | 146 | 877 |
| **`B` (default)** | **697** | **249** | **1,167** | 877 |
| `AB` | 596 | 294 | 1,313 | 877 |

45 + 249 = 294 and 146 + 1,167 = 1,313 exactly, so A and B do partition AB with
nothing lost or double-counted. **B carries 918 of the 1,019 TU reduction —
90 % of the merge yield — and A carries 101.** Dropping A costs a tenth of the
yield and removes the half that carries 100 % of the measured damage.

*(These counts are lower than the brief's 695/586 for two reasons that pull in
opposite directions: the type-disagreement repair 2 unblocked merges, and §1.1's
SDK refusal removed 49 hoists which re-fragments some runs. The measured net is
above.)*


### 2.2 The honest answer to "is a B-only stage byte-comparable?" — **NO**

The brief asks this directly, so it is answered directly, with a build rather
than an argument. Four app images at one input set, all built with the
repository's own entry point, no build file or linker script edited anywhere:

| image | FLASH | Δ FLASH | `.text` | **Δ `.text`** | codegen class |
|---|---:|---:|---:|---:|---|
| stage 03 baseline | 956,356 B (97.34 %) | — | 492,688 | — | — |
| stage 04 **A** | 956,340 B | −16 | 492,676 | **−12** | size-changing |
| stage 04 **B** | 956,276 B | −80 | 492,612 | **−76** | size-changing |
| stage 04 **AB** | 956,276 B | −80 | 492,600 | **−88** | size-changing |

`.text` is additive to the byte: −12 + −76 = −88 exactly. RAM is 253,765 B on
all four (Δ 0), and `rodata`/`datas`/`bss`/`noinit` are Δ 0 on all four.

> **A B-only stage 04 is NOT size-neutral. Its `.text` delta is −76 B.**

Sub-batch A measures −12 B here and measured **−16 B** at the inputs the R7 gate
ran on (`stage04_r7_validation.md` §3.4) — the difference is the 653 moved
inputs, not a disagreement. Either way **B's delta is five to six times the
magnitude of the A delta that broke eight navigation fields.**

Dropping A removes the half that was *measured* to do damage. It does not make
the stage safe, and claiming otherwise would be exactly the reasoning the gate
record forbids. The AB-against-A comparison that showed B introducing 0
regressions measured B's **incremental** effect *on top of A* — a B-only image
is a fourth image that has never been booted, at a linked size neither A nor AB
had.

**The oracle is REQUIRED for stage 04 in this form and I cannot run it.** Renode
is owned by the concurrent agent and this brief forbids it. I make no R7 claim
for stage 04, and the stage's own `MANIFEST.json` now says so mechanically:
`"declared_codegen_class": "size-changing"`, `"oracle_required": true`.

What can be said without the oracle is the containment, and it is tight:

```
sized text symbols   2,935 -> 2,935     0 added, 0 removed
functions changed    7
    -24  app_msleep_thunk_b        28 ->   4      (forwarding thunk -> tail branch)
    -24  k_msleep_ticks32768_c     28 ->   4
    -24  k_uptime_get_6            28 ->   4
    -20  find_cf_cfg_by_addr       76 ->  56
     -4  fortify_chk_fail          32 ->  28
    +10  convert_to_id_on_match    34 ->  44
   +106  close                     76 -> 182
net from the changed functions  +20 B; the remaining -96 B is alignment padding
freed by the five shrinks
```

None of the seven is a bus driver, a display path or a sensor path — but that
was true of sub-batch A's two as well, and A still moved the OPT3001 poll train
by 100.7 ms. **Absence of a bus driver in the diff is not evidence.** The
carrier is total linked size, not which function moved.

### 2.3 What stage 04 sub-batch B produces

| | |
|---|---:|
| app translation units | 1,615 → **700** |
| merged units | **249** |
| files absorbed | **1,164** |
| shape-quarantined | 30 |
| adjacencies blocked | 878 |
| merged unit size: min / median / max | 2 / **4** / **23** |
| single-source units remaining | **451 of 700 (64 %)** |

Per module (merged units / files absorbed / largest): `lib/` 76 / 313 / 19,
`core/` 27 / 112 / 17, `audio/` 22 / 103 / 12, `notify/` 20 / 73 / 9,
`unsorted/` 16 / 148 / 23, `display/` 14 / 71 / 8, `storage/` 14 / 55 / 12,
`ble/` 13 / 69 / 13, `gui/` 8 / 32 / 13, `sensors/power/` 6 / 34 / 8,
`ipc/` 6 / 40 / 16, `sensors/input/` 6 / 26 / 6, `sensors/imu/` 5 / 15 / 4,
`esb/` 4 / 17 / 7, `ui/dashboard/` 3 / 22 / 11, `ui/onboarding/` 3 / 8 / 4,
`analytics/` 2 / 12 / 7, `ui/quicknote/` 2 / 8 / 5, `ui/translate/` 2 / 6 / 4.
`common/`, `ui/navigation/` and `ui/teleprompt/` still produce none.

---

## 3. Size-neutrality made a first-class, checkable stage property

The general lesson the brief names outlives this stage, so it is encoded rather
than written down: **any transformation that changes linked size can break
side-effect equivalence, in either direction.** Three independent measurements
now say it (+60 B, +16 B, **−16 B**), and the third is the decisive one because
it points the *other* way — shrinking is not safe either.

That was discovered at an oracle run, after a build and nine Renode captures.
It did not have to be. "Can this stage change linked size?" is a property of the
stage, declarable in advance.

**What was added.**

1. **Every stage DECLARES a codegen class** in `driver.STAGES` — a fifth field:

   | class | meaning | gate |
   |---|---|---|
   | `byte-identical` | image must be byte-identical to the input stage's | `cmp zephyr.bin` |
   | `size-neutral` | image may differ; every allocatable section size unchanged | section table |
   | `size-changing` | sections move; **an oracle run is REQUIRED** and may not be inferred, argued or borrowed | Renode |

   Stages 00–03 `byte-identical`; **04 `size-changing`**; 05 `size-neutral`.

2. **`driver.py materialize` records it in the MANIFEST**, together with
   `"oracle_required"`, so the obligation travels with the stage instead of
   living in a report.

3. **`driver.py size-gate N BASE_BUILD STAGE_BUILD`** measures the class the
   stage actually achieved, writes `SIZE_GATE.json` into the stage directory and
   exits non-zero when the stage came out **worse** than it declared. The
   verdict is deliberately asymmetric: coming out *better* passes and is
   reported (a stage that declared `size-changing` and turned out
   byte-identical needs no oracle run).

4. **`stagelib.elf_section_sizes`** parses the ELF section header table
   directly — no toolchain — so the gate and its tests run everywhere. A size
   gate that only runs where a cross-compiler is installed is a gate that does
   not run.

### 3.1 The gate's own first version was broken, and the bug is now a test

The first implementation compared `(".text", ".rodata", ".data", ".bss",
".noinit")` and reported the stage 04 image as **`size-neutral` with every
delta `+0`** — while `.text` had in fact moved by 80 bytes. The reason:

```
BASE  text=492688  rodata=456536  datas=3327  bss=189230  noinit=60021
```

**The G1 Zephyr link names those sections without a leading dot**, and carries
20 more allocatable areas besides (`device_area`, `k_sem_area`,
`log_const_area`, `sw_isr_table`, `net_buf_pool_area`, …). A gate keyed on a
name list is a gate that silently passes, which is worse than no gate.

The gate now keys on **`SHF_ALLOC` in the section header** and canonicalises the
leading dot, so no name list can go stale, a section that appears or vanishes
counts as a change, and non-allocatable sections (`.debug_*`, `.symtab`,
`.comment` — including `uname.c.obj`'s embedded build clock) are dropped before
classification. `test_size_gate.py::test_zephyr_names_its_sections_without_a_leading_dot`
pins it.

### 3.2 The measured gate results

```
driver.py size-gate 4 <stage-03 build> <stage-04-B build>
    declared size-changing -> measured size-changing   PASS   oracle_required TRUE
    deltas {'text': -76}

driver.py size-gate 5 <stage-04-B build> <stage-05 build>
    declared size-neutral  -> measured BYTE-IDENTICAL  PASS   oracle_required FALSE
    deltas {}   image_byte_identical TRUE
```

---

## 4. Stage 05 — compositions, not concatenations

Stage 04's own verdict on itself is the brief for this stage:

> The merged files are **concatenations, not compositions**. Each member keeps
> its own `#include "g1_app_symbols.h"`, its own banner comment and its own
> `extern` block; a real `display.c` would have one include block, one set of
> declarations and functions ordered by call structure.

**The sub-batch split is by codegen class, not by intuition** — which is the
whole point of §3, applied to the first stage designed after the gate:

* **`N` (default)** — provably **preprocessor-identical**. Every edit removes
  either a token sequence the preprocessor was already discarding or a
  declaration the compiler had already accepted with an identical type earlier
  in the same TU.
* **`S` (opt-in)** — internal linkage for TU-private symbols. Genuinely
  production-grade and genuinely codegen-changing. **Not applied.**

### 4.1 Sub-batch N, rule by rule

**N1 — duplicate `#include` withdrawal.** The second and later occurrences of an
identical include spelling inside one merged unit are removed; the first stays
exactly where it is.

Inertness is checked, not assumed. Angle headers rely on C11 7.1.2p4 (a standard
header may be included more than once). **Every quoted repository header is
resolved the way the compiler resolves it, read, and deduplicated only if it
carries an include guard or `#pragma once`.** Measured: all 27 distinct include
spellings across the merged units are idempotent —
`unguarded_headers_not_deduplicated` is **empty**.

This deliberately does not *move* an include. Stage 04 §8.3 item 7 declined to
hoist includes because `g1_app_symbols.h` opens with `#ifndef bool`, so its
expansion depends on the macro state at its include point. That objection
applies to moving, not to deleting a repeat — and deleting is enough, because
the first member's include block is already at the top of the file.

**N2 — duplicate file-scope declaration withdrawal.** A file-scope `extern`
whose canonical type is identical to one already seen earlier in the same unit
is removed (C11 6.7p4; only LATER copies go, so the surviving declaration still
precedes every use). A declaration that is *not* identical is never touched:
stage 04's `type` rule guarantees no such pair exists inside one unit, so a
difference here would mean the partition was wrong, and the right response is to
leave it visible for the compiler rather than hide it. That path is counted
(`N2_declarations_left_disagreeing`) and is **0** in this run.

**N3 — member banner compression.** Stage 04's three-line
rule/filename/rule separator becomes one line. **Every `identity:` provenance
banner is preserved byte for byte** — they are what `stagelib.parity_rows`
reads, and `check-addresses 4 5` is the check that they were.

### 4.2 What it did, measured

| | |
|---|---:|
| merged units seen / composed | 249 / **249** |
| duplicate `#include` directives withdrawn | **1,573** |
| duplicate file-scope declarations withdrawn | **146** |
| member banners compressed | **1,164** |
| declarations left disagreeing (would mean stage 04 was wrong) | **0** |
| headers refused as not provably idempotent | **0** |

Include consolidation, measured over the 249 merged units:

| | stage 04 | **stage 05** |
|---|---:|---:|
| `#include` directives in merged units | 2,423 | **850** |
| most in a single unit | 49 | **6** |
| separate include *blocks* per unit, worst case | **30** | **5** |
| units down to exactly ONE include block | 0 | **21** |
| units at 2 blocks | 16 | **134** |

**And the acceptance measurement: `zephyr.bin` is `cmp`-IDENTICAL between stage
04 and stage 05, on the whole 956,276-byte app image**, with
`app_update.bin`'s 956,868-byte payload identical too (only the 256-byte
MCUboot RSA-PSS signature TLV differs, as it does between any two signing runs).
The stage declared `size-neutral` and achieved `byte-identical`. **Stage 05
needs no oracle run of its own**: whatever stage 04's image does, stage 05's
image does bit for bit.

### 4.3 Sub-batch S — measured, and deliberately NOT applied

The candidate set is computed even in the sub-batch that does not take it, on
the principle that an unexercised opportunity nobody counts is an opportunity
nobody knows about.

| | |
|---|---:|
| **candidates** — defined in a merged unit, named nowhere else | **241** |
| refused: named outside the translation unit | 777 |
| refused: named by a linker fragment or `g1_app_symbols.h` | 96 |
| refused: declared by an SDK header (the §1.1 evidence, reused) | 26 |
| refused: reserved identifier the implementation may call (C11 7.1.3) | 12 |
| refused: `__asm__`-named or macro-renamed | 6 |
| **applied** | **0** |

The two evidence-driven refusals matter. The first candidate list contained
`__malloc_lock`, `_sbrk_r`, `_fstat_r`, `_puts_r` — newlib callbacks that
**newlib** calls and that no scan of our own sources can see. Four of them are
caught by the SDK evidence set; the rest are caught by the C11 7.1.3 rule that a
file-scope identifier beginning with an underscore belongs to the
implementation.

**That residue is exactly why S is not applied.** A source-text reference scan
cannot see a call from a library or from a vector table, so sub-batch S must be
gated by a real link (README C6) *and* by an oracle run, and this pass can do
neither. It is implemented, measured and left off.

---

## 5. Gate ladder — measured at the final inputs

**A correction to §1, made after the fact and against my own numbers.** The
concurrent parity agent landed the `errno_wrapped_tick_call` third-argument fix
**mid-pass** — the very defect `stage04_r7_validation.md` §8 predicted and handed
over. `driver.py status` reported one moved input
(`stage_02_.../errno_wrapped_tick_call.c`), so stages 03, 04 and 05 were
**regenerated, never patched**, and every image was rebuilt. The final stage 03
harvest is therefore **19 module headers / 218 hoisted / 663 divergent + 267
sdk-shadowing**, not the 20/255/664 §1 recorded before the two transformer
fixes and the concurrent landing. §1's numbers are left in place as the record
of what the *unmodified* transformer produced.

The fix is present in every image measured below — verified in the linked ELF,
not taken on report:

```
00079d34 <errno_wrapped_tick_call>:
   79d4a:  movs  r2, #0          <-- param_3 = 0, the ACCUMULATE arm
   79d4c:  mov   r1, r2
   79d4e:  bl    44df8 <rate_limited_elapsed_seconds_tick>
```

which is the shipped image's `0x7d1ec` sequence instruction for instruction.

| gate | stage 03 baseline | **stage 04 (B)** | **stage 05 (N)** |
|---|---|---|---|
| app build | exit 0 | **exit 0** | **exit 0** |
| app FLASH | 956,356 B / 97.34 % | **956,276 B / 97.33 % (Δ −80)** | **956,276 B (Δ 0)** |
| app RAM | 253,765 B / 56.32 % | **Δ 0** | **Δ 0** |
| `.text` | 492,688 | **492,612 (Δ −76)** | **492,612 (Δ 0)** |
| `rodata` / `datas` / `bss` / `noinit` | 456,536 / 3,327 / 189,230 / 60,021 | **Δ 0 each** | **Δ 0 each** |
| `zephyr.bin` vs previous stage | — | DIFFERS (expected) | **`cmp` IDENTICAL, 956,276 B** |
| `app_update.bin` payload vs previous stage | — | — | **956,868 B IDENTICAL** (only the 256 B RSA-PSS TLV differs) |
| `nm -u` undefined | **0** | **0** | **0** |
| duplicate global definitions | **0** | **0** | **0** |
| sized text symbols (`nm -S`, T/t/W/w entries) | 3,013 | **3,013** | **3,013** |
| ...of which DISTINCT names | 2,935 | **2,935 — 0 added, 0 removed** | **2,935** |
| functions whose size changed | — | **7** (§2.2) | **0** |
| build-log lines containing `warning:` | 2,987 | **2,975 (Δ −12)** | **2,975 (Δ 0)** | 

*(The warning figure counts log LINES matching `warning:`, which is a different metric from the per-diagnostic counts earlier reports quote (2,174 / 2,203). Only the deltas are comparable within this table.)*

| **`driver.py size-gate`** | — | **declared `size-changing` → measured `size-changing`, PASS, `oracle_required` TRUE** | **declared `size-neutral` → measured `byte-identical`, PASS, `oracle_required` FALSE** |
| `driver.py check-addresses` 0-1, 1-2, 2-3, 3-4, **4-5** | **all identical, 2,567 both sides on every pair** | | |
| `tools/verify_data.py` | **995 / 995 byte-exact, 56,279 / 56,279 B (100.00 %)** | | |
| `check_ram_pin_collisions` (on the stage 05 ELF) | **627 bound OK / 0 escaping / 0 unknown inside a live object** (20 raw-literal pins outside the RAM region and 3 abs symbols not in the linker scripts — both unchanged) | | |
| `check_thread_create_stack_args --trials 120` | **10 / 10 PASS, exit 0** | | |
| `gen_retained_sources.py --check` | **"retained source lists are current"** | | |
| **refactor test suite** | **105 / 105 PASS** (was 58 / 58 — **47 new tests**) | | |
| idempotence, stage 04 | MANIFEST `522c7ae8…` → `522c7ae8…`, whole tree `46121635…` → `46121635…` — **byte-identical** | | |
| idempotence, stage 05 | MANIFEST `213f9954…` → `213f9954…`, whole tree `258d6711…` → `258d6711…` — **byte-identical** | | |
| `driver.py status` | **stages 00–05 all current**, 0 inputs changed | | |

**Net core: untouched, and measured rather than assumed.**
`git status --porcelain` over `recon/net`, `recon/symbolized/net`,
`recon/application`, `recon/symbols`, `recon/headers`, `recon/generated`,
`recon/board`, `recon/wiring` and `tools` is **empty**. No net input changed, so
no net build was run and the 225,581 B freeze holds by construction.
`check_net_raw_literals` and `verify_net_stock_data_window` need a net ELF and
were therefore **not run** — building one would have been the only way to run
them and there was nothing to rebuild. That is recorded as not-run, not as
passed.

---

## 6. Is this production-grade, or merely rearranged?

Asked directly by the brief, so answered directly, and the answer is different
in the two halves.

**Stage 05's composition step: yes, and it is provable.** A merged unit is no
longer a file that says `#include "g1_app_symbols.h"` twenty times. Include
directives inside merged units fall **2,423 → 850**; the worst unit falls from
**49 includes in 30 separate blocks to 6 in at most 5**; 21 units are down to a
single include block and 134 to two. 146 duplicated declarations are gone. And
the whole thing is `cmp`-identical at the image level, so it is the rare
refactor that a maintainer can take with no risk argument at all. A reviewer
opening `display/g1_display_01.c` now reads one include block, then the
functions.

**Stage 04's merge: materially better than the last pass, and still not there.**
1,615 → 700 translation units, 249 cohesive units absorbing 1,164 files, median
merged unit 4 members (up from 3), largest 23 (up from 20). But **451 of 700
units — 64 % — are still a single source file**, which is *worse* than the AB
run's 54 %, because dropping sub-batch A is dropping merges. That is the price
of the R7 evidence and it is the right price, but it should be stated as a
regression in cohesion, not hidden inside a better safety story.

**What a maintainer would still object to, unchanged from stage 04 §9:**

* `unsorted/` is still 148 absorbed files across 16 units and the module map has
  not been regenerated.
* Functions inside a merged unit are still in *link* order, not call order.
  Reordering them changes `.text` layout, so under §3's rule it is a
  `size-changing` transformation and needs the oracle. It was not attempted.
* No merged unit has a header of its own describing *its* interface; the module
  header from stage 03 is still module-wide.
* 241 symbols that are private to one translation unit are still global.

**And the honest headline: stage 04 is still not proven.** Its image has never
been booted in any form — A, B or AB. Stage 05 inherits that exactly, no better
and no worse, because its image is byte-identical to stage 04's.

The most valuable thing this pass produced is not either stage. It is §3: the
project now *declares* whether a stage can move linked size, records the
obligation in the stage's own manifest, and has a command that measures whether
the declaration held — so the next stage that would have been caught by an
oracle run is caught by a build instead. The Stage 04 gate cost nine Renode
captures to learn something a `size -A` could have predicted.

---

## 7. What I did NOT do, and everything quarantined, with measured reasons

1. **I did not run the emulator oracle.** Renode is owned by the concurrent
   agent and this brief forbids it. **Stage 04 sub-batch B is `size-changing`
   at −76 B of `.text` and an oracle run is REQUIRED before it is landed.** I
   make no R7 claim for it. Stage 05 needs no oracle of its own — its image is
   `cmp`-identical to stage 04's — but it inherits stage 04's unproven status
   entirely.
2. **I did not bisect sub-batch A.** The gate record forbids it and gives the
   reason: there is no guilty file, the mechanism is linked size. I acted on the
   measurement instead, by making B the default.
3. **I did not apply sub-batch S (internal linkage).** 241 candidates measured,
   0 applied (§4.3). It needs a real link gate *and* an oracle run, and a
   source-text reference scan structurally cannot see a call from newlib or from
   a vector table — the `_sbrk_r` / `__malloc_lock` class. Two evidence-driven
   refusals (SDK-declared, C11 7.1.3 reserved) catch 38 of them; I do not claim
   they catch all.
4. **I did not move module-private declarations out of the module header into
   the merged unit that now owns all their users.** It is codegen-neutral and it
   is the obvious next composition step; I ran out of pass, not out of
   justification. The measurement that sizes it has not been taken.
5. **I did not reorder functions by call structure** inside a merged unit — the
   thing that would most make these files read like source. It changes `.text`
   layout, so under §3 it is `size-changing` and cannot be validated here.
6. **I did not hoist a first-occurrence include to the top of its unit.** Only
   repeats are deleted. That is why 228 of 249 units still have 2–5 include
   blocks rather than 1: a later member legitimately introduces a header no
   earlier member had. Moving it would need a proof that no `#define`/`#undef`
   between the top of the file and its original position affects it.
7. **I did not repair a single declaration disagreement.** R1: the fix belongs
   in the canonical trees, which this pipeline may never write. They are handed
   over, refreshed, in `stage_03_module_structure/DEFECTS.json` — **663
   divergent-spelling entries plus 267 new
   `reconstructed_declaration_shadows_an_sdk_symbol` entries**. The latter class
   is new evidence and should be read the way §8.1 of the stage 04 gate report
   taught: `extern int strlen(int a);` in a module header is not a merge
   blocker, it is a wrong prototype.
8. **The `cmsis_gcc.h` gap in the SDK evidence is open.** It contributes 0
   identifiers because `-aux-info` does not report `__STATIC_FORCEINLINE`
   bodies, and 46 corpus files include it. No hoist collides with a CMSIS name
   today (asserted by a test over the materialised tree), but the evidence file
   does not prove it.
9. **The 18 sources that shadow a `<stdint.h>`/`<stddef.h>` typedef and the 15
   with multi-declaration lines are still excluded from the hoist**, unrepaired,
   for the same R1 reason.
10. **I did not restructure the net core**, and no net gate that needs a net ELF
    was run (§5).
11. **I did not regenerate `refactor_module_map.json`**, so `unsorted/` is still
    the third-largest directory.
12. **I did not regenerate stage 99.** It is the retired diagnostic; `status`
    reports it stale with 781 inputs moved. `test_size_gate.py` permits exactly
    one manifest to lack the new codegen-class field and only while its stage is
    reported stale — so the gap is visible rather than exempted.
13. **`cfg_verify` was not run and is not cited.** Every number here comes from
    a build, a `cmp`, an ELF section table, a `nm`, or a test run.
14. **Nothing was committed.** The tree is left dirty.

### Shape quarantine, stage 04 — 30 files, unchanged from stage 04's own list

13 `multi_declaration_line_types_unknown`, 9 `file_scope_pragma_leaks_forward`,
5 `per_tu_ffp_contract_body`, 1 `includes_a_definition_carrying_inc_fragment`,
1 `attribute_alias_definition`, 1 `named_by_path_in_app_cmakelists`.

### Pairwise refusals, stage 04 — 878 adjacencies blocked

Unchanged in shape from stage 04's census; the `type` rule still dominates.

---

## 8. Footprint — everything this pass wrote

```
 M recon/refactor/driver.py
        stage registry gains a fifth field (declared codegen class); stage 5
        registered; `size-gate` subcommand; manifest records
        declared_codegen_class + oracle_required
 M recon/refactor/stagelib.py
        CODEGEN_CLASSES / elf_section_sizes(alloc_only) / classify_codegen /
        size_deltas / size_gate -- keyed on SHF_ALLOC, not a section-name list
 M recon/refactor/transforms/t03_module_structure.py
        _blank_comments + _COMMENT_TAIL (a declaration with a trailing comment
        is now visible to the safety rule); refuse to hoist any symbol the SDK
        angle headers declare
 M recon/refactor/transforms/t04_cohesive_tu.py
        sub-batch B added; A and B now PARTITION the clean runs; DEFAULT_BATCH
        = "B"; batch value validated; docstring records the R7 evidence
 M recon/refactor/stage_0{0,1,2,3,4}_*/MANIFEST.json, stage_03/DEFECTS.json,
   stage_04/{QUARANTINE,HAZARDS}.json                        (regenerated)
?? recon/refactor/sdk_symbols.py                 (the evidence generator)
?? recon/refactor/sdk_declared_symbols.json      (996 identifiers, 20 headers)
?? recon/refactor/transforms/t05_cohesive_composition.py
?? recon/refactor/test_size_gate.py              (25 tests)
?? recon/refactor/test_composition.py            (22 tests)
?? recon/refactor/stage_05_cohesive_composition/ (MANIFEST/PARITY_MAP/QUARANTINE + tree/)
?? recon/refactor/stage_0{4,5}_*/SIZE_GATE.json
?? recon/analysis/staged_refactor_stage05.md     (this file)
```

`recon/refactor/.gitignore` already excludes `stage_*/tree/`. **No canonical
tree, no `recon/symbols`, no `recon/application`, no `tools/` module, no
emulator report, no linker script, no `recon/board/**` and nothing under
`~/Projects/armemul` was written** — structurally enforced by
`guard.check_write`, whose refusal tests still pass. Everything else dirty in
`git status` belongs to the concurrent parity agent.

## 9. Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"

$V recon/refactor/driver.py status                  # expect 00-05 current
for n in 0 1 2 3 4 5; do $V recon/refactor/driver.py materialize $n; done
for a in 0 1 2 3 4; do $V recon/refactor/driver.py check-addresses $a $((a+1)); done
$V -m unittest discover -s recon/refactor -p 'test_*.py'          # 105/105

# the SDK declared-symbol evidence (needs one successful build for its -I set)
$V recon/refactor/sdk_symbols.py generate \
   --command-file <a gcc line lifted from a build log> --build <that build dir>

# the four images
./recon/refactor/stage_03_module_structure/tree/recon/application/build_cohesive.sh   app /private/tmp/g1-s5-f-base
./recon/refactor/stage_04_cohesive_tu/tree/recon/application/build_cohesive.sh        app /private/tmp/g1-s5-f-s04
./recon/refactor/stage_05_cohesive_composition/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s5-f-s05
# sub-batch comparison:  G1_STAGE04_BATCH={A,B,AB,OFF} $V driver.py materialize 4

# the new gate
$V recon/refactor/driver.py size-gate 4 /private/tmp/g1-s5-f-base /private/tmp/g1-s5-f-s04
$V recon/refactor/driver.py size-gate 5 /private/tmp/g1-s5-f-s04  /private/tmp/g1-s5-f-s05
cmp /private/tmp/g1-s5-f-s04/zephyr/zephyr.bin /private/tmp/g1-s5-f-s05/zephyr/zephyr.bin
```

## 10. THE ONE THING THE NEXT PASS MUST DO

**Run the oracle on stage 04 sub-batch B.** It is `size-changing` at −76 B, it
has never been booted, and −12 B of the same kind broke eight navigation fields
the in-tree build reproduces byte-exactly. The capture recipe is in the README's
Stage 04 gate record, with one change that will bite: **`$rtinfo_pc` must be
re-read from this image's own ELF** — there are now four different values across
base/A/B/AB and none of them is in any recorded recipe.

If it passes, stage 05 lands with it for free: its `zephyr.bin` is
`cmp`-identical.
