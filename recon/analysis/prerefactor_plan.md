# Pre-refactor passes G6 (inline small literals) and G7 (dedupe repeated code)

**Status: ANALYSIS ONLY.** Nothing in the corpus was modified by this pass. No
source, build file, linker script, `recon/emulator/**` or `tools/` logic was
touched; nothing was committed. The deliverables are three new files:

| file | contents |
|---|---|
| `recon/ownership/literal_inline_plan.json` | 5,669 candidates, one record each: address/value, current form, proposed form, classification, evidence, pins retired, batch |
| `recon/ownership/code_dedupe_plan.json` | 12 named clusters + a 205-row generic cross-file cluster appendix, each with call sites, a concrete inline/macro signature, risk and batch |
| this file | totals, application order, re-proof obligations, cross-tree propagation rules, non-goals |

**Snapshot caveat.** A parity bring-up was running concurrently and edited
`recon/application/app/src/g1_app_string_rodata.c`,
`recon/symbols/g1_app_globals.ld` and `recon/application/app/CMakeLists.txt`
during this pass. Every count below is a snapshot taken while those files were
in flux; re-run the scripts before applying a batch, and treat the pin counts
in particular as accurate to within the objects that bring-up added.

Reproduce (read-only):

```sh
# the scratchpad scripts that produced the two JSONs
#   scan_literals.py -> classify_g6c.py -> classify_num.py -> callsite_ctx.py -> emit_plans.py
#   cluster_g7b.py   -> g7_targeted.py  -> emit_g7.py
PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python <script>
```

---

## 0. The corpus is nine parallel trees, not five

The task brief named five. There are nine, and the count matters because a
defect fixed in one is not fixed in the others:

| tree | `.c` files | role |
|---|---:|---|
| `recon/app/src` | 2,141 | **canonical app**, parity-proven, `recon_kit.RECON_SRC` |
| `recon/verified/src` | 2,138 | app mirror — **3 files behind canonical today** |
| `recon/app/src_sym` | 1,059 | older symbolized app snapshot |
| `recon/verified/src_sym` | 1,059 | mirror of the above |
| `recon/symbolized/app` | 2,141 | **what the build compiles** (1,609 retained sources) |
| `recon/named` | 2,140 | readable app mirror — **1 file behind** |
| `recon/readable_sources/app/{g1,library}` | 1,156 + 959 | readable split — **29 symbolized files have no readable counterpart** |
| `recon/application/src` | 1,156 | a further readable app tree |
| `recon/net/src` | 1,177 | **canonical net** |
| `recon/symbolized/net` | 1,155 | **what the net build compiles** (923 retained) |
| `recon/net/named` | 1,124 | readable net mirror |

Two consequences that the plan encodes as rules:

1. **The build tree is `recon/symbolized/{app,net}`**, confirmed from
   `recon/generated/{app,net}_retained_sources.cmake`. An edit that only lands
   in `recon/app/src` changes nothing in the image; an edit that only lands in
   `recon/symbolized/app` is never parity-proven.
2. **The trees have already diverged in content, not only in naming.** The
   canonical app tree references **1,428** distinct `.rodata` addresses; the
   symbolized app tree references **2,706**. 1,063 of the 1,278 extra are
   in-sector (real string/data objects the symbolizer named and the canonical
   source spells differently or not at all), and 238 are out-of-sector
   addresses that the symbolizer nevertheless named `rodata_*`. **808 G6
   inline candidates have no canonical-tree site at all.** They are batch
   G6‑B3 precisely because they carry no parity obligation but do change the
   image.

---

## 1. G6 — inline small literals

### 1.1 What was scanned

Every integer literal and every `rodata_<hex>` / `ADDR_*` symbol reference in
all nine trees, comments and string bodies masked out. Region truth came from
the byte-verified oracles only:
`recon/ownership/rodata_decode_ledger{,_net}.json` (367 + N regions),
`recon/application/app/src/g1_app_string_rodata.c` (1,787 emitted string
objects), `g1_app_font_rodata.c` (5), `recon/data/*.c` (993) and
`recon/net/data/*.c`. Names for numeric constants came only from
`~/ncs251/modules/hal/nordic/nrfx/mdk/nrf5340_{application,network}.h`, the
CMSIS Cortex‑M33 SCS map, and the POSIX/Zephyr errno table.

### 1.2 Census

Raw reference counts, canonical trees:

| class | app | net |
|---|---:|---:|
| `.rodata`-sector addresses | 3,816 sites / 1,428 distinct | 355 / 103 |
| RAM addresses (`0x2000…`) | 3,706 sites / 306 distinct | 572 / 217 |
| `.text` addresses | 1,958 / 174 | 119 / 71 |
| MMIO window | 146 / 65 | 147 / 32 |
| high-word / SCS window | 559 / 87 | 206 / 50 |
| plain scalars | 15,977 / 1,502 | 9,766 / 955 |
| `ADDR_*_THUMB` function pointers | 127 distinct, 258 sites (all trees) | — |

### 1.3 Decisions

**2,978 `.rodata` reference candidates** (all trees, de-duplicated by address):

| decision | app objects | app ref-sites | net objects | net ref-sites |
|---|---:|---:|---:|---:|
| **inline** | 1,918 | 19,329 | 116 | 809 |
| ambiguous | 261 | 1,712 | 12 | 25 |
| keep-symbolic | 567 | 4,128 | 104 | 259 |

Breakdown of the decisions:

| class | decision | app | net |
|---|---|---:|---:|
| `string_literal` — byte-verified string object, byte before the VA is NUL | inline | 1,918 | 116 |
| `out_of_sector_pin` — `rodata_*` name on a `.text`/`.data` address | keep-symbolic | 253 | 54 |
| `data_object` — inside a byte-verified table/bitmap | keep-symbolic | 215 | 7 |
| `relocatable_pointer_table` — `ptr_table`/`ptr_record` region | keep-symbolic | 78 | 41 |
| `non_string_bytes` | keep-symbolic | 21 | 2 |
| `unmodelled_string` — clean string but no region owns the VA | ambiguous | 133 | 4 |
| `string_interior` — decodes, but the previous byte is not NUL (suffix sharing) | ambiguous | 68 | 4 |
| `short_object_review` — emitted object ≤ 4 B (the §10 stub hazard) | ambiguous | 60 | 4 |

**2,691 numeric-literal candidates**:

| class | app distinct / sites | net distinct / sites | decision |
|---|---:|---:|---|
| `nrf_peripheral_register` (MDK header names the base + 4-aligned offset) | 18 / 64 | 29 / 143 | inline |
| `cortex_scs_register` (CMSIS) | 4 / 8 | 7 / 17 | inline |
| `errno_negative` | 23 / 440 | 22 / 152 | **ambiguous — per-site review** |
| `float_bits` (IEEE-754 binary32) | 120 / 207 | 2 / 2 | **ambiguous — per-site review** |
| `round_power_of_two` (equals a base *and* a bit constant) | 1 / 14 | 1 / 1 | ambiguous |
| `probable_struct_offset` | 65 / 5,446 | 65 / 3,441 | keep-symbolic (production refactor) |
| `bit_mask` / `wide_mask` / `small_negative` | 67 / 996 | 29 / 605 | keep-symbolic |
| `unmapped_high_word` | 20 / 24 | 1 / 2 | keep-symbolic |
| **`unnamed_scalar` — no evidence attaches a name** | **1,336 / 9,483** | **881 / 5,756** | keep-symbolic |

**Honest note on the numeric class.** The owner's brief expected "small
numeric constants passed as raw hex" to be a large G6 category. It is not.
2,217 of 2,691 distinct numeric literals (82 %) have **no** evidence-backed
name: they are struct offsets, masks, and opcode/size constants whose meaning
lives in a struct layout or a protocol the project has not yet recovered.
Naming them would be invention, which the brief forbids. The evidence-backed
numeric inline set is **58 candidates over 232 sites** — small, and worth doing
only because it is free of risk.

**Honest note on "small arrays".** The brief expected an array class. It is
effectively empty. `rodata_decode_report.md` §4 records that **element width is
proven for exactly two app regions** (`rodata_aae20`, `rodata_f1590`); every
other numeric region is emitted as a byte-exact `unsigned char []` with
`width evidence: none`. Writing `{1, 2, 3}` for a region whose element width is
unproven would invent a layout. All 222 non-string data objects are therefore
**keep-symbolic**, and promoting them is gated on the interprocedural argument
taint that §4 already names as separate work.

### 1.4 The hard rule, and what it protects

> A reference that must remain relocatable is never inlined.

Concretely, the following are classified **keep-symbolic without exception**,
and the plan JSON carries the reason per candidate:

* the **127 `ADDR_*_THUMB` symbols** (258 sites) — every one is a function
  address + the Thumb bit, compared against a `struct bt_gatt_attr` write
  callback or stored as a work handler. Freezing them pins original-image
  `.text` addresses into a relocated build;
* **`ptr_table` / `ptr_record` regions** (78 app + 41 net references) — the
  `.rodata` decode already emits these through the `__asm__`-alias mechanism of
  `pointer_rebind.md` precisely so no raw absolute word is stored;
* **`struct device` / `init_entry` neighbourhoods** — `rodata_87b30` and the
  16 other deferred regions of `rodata_decode_report.md` §6;
* **RAM addresses** (306 app + 217 net distinct) and **`.text` addresses**
  (174 + 71) — SDK-owned objects and code, already handled by the symbolizer;
* **section boundaries** — the sector edges proven in §1 of the decode report.

### 1.5 Pins retired

`recon/symbols/g1_app_globals.ld` holds **2,605** `PROVIDE(rodata_… = …)`
lines, 2,403 of them numeric absolute; `g1_net_globals.ld` holds 224, 222
numeric. G6 retires a numeric pin when every reference to that address becomes
a literal *and* the emitted object backing the symbol is withdrawn with it.

| batch | candidates | reference sites | **numeric pins retired** | cores |
|---|---:|---:|---:|---|
| **G6‑B1** log-argument string literals | 554 | 9,251 | **554** | app |
| **G6‑B2** non-log-argument string literals | 623 | 7,935 | **614** | app 556 / net 67 |
| **G6‑B3** string heads with no canonical site | 857 | 2,952 | **856** | app 808 / net 49 |
| **G6‑B4** hardware register addresses | 58 | 232 | 0 | app 22 / net 36 |
| **G6‑B5** errno negatives (review) | 45 | 592 | 0 | app 23 / net 22 |
| **G6‑B6** IEEE-754 bit patterns (review) | 122 | 209 | 0 | app 120 / net 2 |
| **G6‑A** ambiguous work list — no edits | 275 | 1,752 | 0 | app 262 / net 13 |
| **G6‑X** keep-symbolic — no edits | 3,135 | 30,140 | 0 | app 2,055 / net 1,080 |
| **total** | **5,669** | **53,063** | **2,024** | |

**2,024 of the 2,625 numeric pins (77 %) are retirable by G6 alone** — 1,915
app and 109 net. Every one of them is currently *inert* (the symbol is defined
by an emitted object, so the `PROVIDE` never fires), which is exactly the state
`rodata_decode_report.md` §10 warns about: *"if the object is ever dropped, an
inert `PROVIDE(rodata_X = 0x…)` silently resurrects the original-image address
and the reader gets garbage again."* Retiring them converts a silent-corruption
failure mode into a link error.

### 1.6 The biggest G6 hazard: this pass can *grow* flash

Inlining does **not** free the object's bytes on its own.
`recon/application/app/g1_verified_rodata_keep.ld` contains
`KEEP(*rodata_*.c.obj(".rodata.rodata_*"))`, and
`rodata_decode_report.md` §10 measured that `--gc-sections` consequently drops
**nothing**. So an inline batch that does not also withdraw the object leaves
the old bytes in flash **and** adds the new literal:

* the 1,918 app inline candidates total **66,243 B**; the 116 net ones **3,753 B**;
* app is at **921,576 / 982,528 B = 93.80 %**, net at **~97.3 %** of its partition.

1,913 of the 1,918 app strings are textually distinct, so linker
`.rodata.str1.1` merging saves almost nothing; and 1,793 of them are referenced
from a single canonical translation unit, so the literal really is the object
moved, not copied. **Every G6 string batch must therefore be applied as one
transaction: inline the literal → delete the object from
`g1_app_string_rodata.c` / `recon/application/rodata/*.c` → delete the
`PROVIDE` → re-measure flash.** Doing the three steps in separate builds will
overflow the partition.

Note also that 125 app + 10 net strings *are* shared across canonical
translation units. For those the plan proposes a single named
`static const char g1_str_<hex>[]` in the owning module header rather than
repeated literals.

---

## 2. G7 — dedupe repeated code

### 2.1 Method

3,318 canonical files, **112,293 statements**. Comments and preprocessor lines
stripped; statements split at `;`/`{`/`}`; Ghidra temporaries
(`iVarN`/`uVarN`/`param_N`/`uStack_N`/`local_N`/`extraout_*`/`unaff_*`/`in_*`)
folded to `V`; every integer literal folded to `N`; whitespace removed. Two
keys per window: `callee_exact` (keeps `FUN_xxxxxxxx`) and `shape` (folds it to
`F`). Windows of k = 1…6.

**Clusters are ranked by distinct-file count, not by occurrence count.** The
raw occurrence ranking is dominated by two enormous files repeating one idiom
1,012 times; that is a loop, not an inline function.

### 2.2 Clusters found

205 generic cross-file clusters appear in ≥ 6 distinct files (the appendix in
the JSON). Twelve are named, specified and risk-rated. **9,935 duplicated
sites** in the canonical trees are covered by the named clusters.

| id | cluster | canonical sites | canonical files | batch | risk |
|---|---|---:|---:|---|---|
| C02 | volatile-cast memory accessors | **7,543** (4,743 app + 2,800 net) | 1,405 | G7‑B5 | **high** |
| C10 | conflicting `extern` decls of the 4 logging entry points | **1,256 declarations, 384 distinct signatures** | ~500 | G7‑B2 | **highest-priority defect** |
| C01 | Zephyr `__ASSERT` expansion (`printk` + `assert_post_action`) | **440 pairs** (320 app + 120 net) | 257 | G7‑B3 | medium |
| C09 | `((long long (*)(void))FUN_xxxx)()` cast-call | 1,012 | **2** | G7‑B7 | audit, not dedupe |
| C06 | `DEBUG_PRINT(…) else debug_print(…)` log gate | 337 | 133 | G7‑B4 | medium |
| C05 | absolute-path `#include` of the host's `cmsis_gcc.h` | 88 | 88 | G7‑B1 | none (portability defect) |
| C12 | `F(…); __builtin_unreachable();` noreturn tail | 79 | 43 | G7‑B3 | low-medium |
| C03 | CMSIS `getBasePriority`/`setBasePriority`/`isCurrentModePrivileged`/`InstructionSynchronizationBarrier` re-defined per file | 73 definitions | 22 | G7‑B1 | **lowest** |
| C04 | Ghidra `CARRY*`/`SCARRY*`/`SBORROW*` re-defined per file | 58 definitions | 11 | G7‑B1 | low |
| C07 | `__set_BASEPRI_MAX(N); __ISB();` irq-lock prologue | 48 | 45 | G7‑B4 | medium |
| C08 | net vtable-dispatch thunk | 13 | 13 | G7‑B6 | medium-high |
| C11 | trivial `T F(void){return N;}` stubs | 28 | 28 | **G7‑X** | non-goal |

### 2.3 The three highest-payoff clusters, and why two of them are dangerous

**C10 — the logging prototypes. This is the most important finding of G7 and
it is not a tidiness issue.** The four variadic logging entry points are
declared **1,256 times in 384 different ways**:

* `DEBUG_PRINT` — 299 declarations, 97 distinct signatures, return types
  `void`/`int`/`unsigned int`/`uint32_t`/`uint64_t`/`long long`;
* `debug_print` — 314 / 89, including **37 files declaring `void
  debug_print(void)` and 20 declaring `void debug_print(int, ...)`**;
* `log_message` — 375 / 119;
* `printk` — 268 / 79.

On this build (`-mfpu=fpv5-sp-d16 -mfloat-abi=hard`) a **variadic** function
passes floating-point arguments in **core** registers while a non-variadic one
passes them in **FP** registers. `void f(void)` and `void f(int, ...)` are
therefore not interchangeable declarations of the same symbol: each translation
unit is compiling against its own belief about the ABI. Unifying them **will**
change codegen in some files, so it is a re-proof event, not a cleanup.
The true signature must be read off each entry point's prologue in the
disassembly before the header is written.

**C02 — the volatile accessors: 7,543 sites, and the trap is width/signedness.**
The same access is spelled twenty ways
(`*(volatile int*)` 977, `*(volatile int *)` 282, `*(volatile unsigned*)` 156,
`*(volatile unsigned int*)` 218, `*(volatile uint*)` 29, …). Some of that is
pure spelling — `unsigned`, `unsigned int` and `uint` are the same type — and
normalising those is codegen-identical. But `int` and `unsigned int` are not,
and AGENTS.md's methodology step 1 makes width and signedness load-bearing:
*"globals → fixed absolute-address `volatile` pointers using literal-pool
VALUES (match width/signedness)"*. Folding all 977 `*(volatile int*)` sites
into a `G1_R32` that yields `uint32_t` changes the type of every comparison and
shift downstream. **Split into two sub-passes**: (a) spelling normalisation
within one type, textual and codegen-identical; (b) macro introduction per
width with a signedness audit of every consumer. There is already an in-tree
precedent for the macro form — `recon/net/src/FUN_01013650.c` defines and uses
`U8/U16/S16/U32/U64(p,o)` and is the only file that does.

**C01 — the `__ASSERT` expansion: 440 adjacent pairs across 257 files.** This
is the cluster with the cleanest payoff and it composes with G6: the three
string operands are rodata pins today, and `rodata_99cbd`
(`"ASSERTION FAIL [%s] @ %s:%d\n"`) alone has **1,843 references** across the
trees — the single most-referenced literal in the corpus. The macro can only be
written after G6‑B1 turns those into literals. The danger is that **the two
halves do not pair 1:1**: 937 app `printk`-class calls but only 662
`assert_post_action` calls, and 313 vs 268 on net. 275 app and 45 net print
calls are *not* assert expansions. Sites also differ in argument count (4 vs
5). Collapsing a 5-argument site into a 4-argument macro silently drops a
register argument — and that is exactly the class the harness cannot see.

### 2.4 The harness-blindness rule

`tools/parity/emu.py` compares the ABI return register(s), the ordered
**non-stack** memory-write trace, call count/order and fault parity. It is
**blind** to dropped register/stack arguments, wrong indirection levels, stack
writes, stack-buffer layout, wrong embedded constants and wrong loop strides —
**19 confirmed instances so far**. Every G7 cluster that touches argument
passing or stack layout (C01, C02, C07, C08, C09, C10) therefore requires a
**disassembly-level review per site**, not a green harness run. The plan JSON
repeats this on each affected cluster so it cannot be lost when a batch is
picked up in isolation.

C09 is the purest example and is deliberately **not** proposed as a dedupe:
calling `device_info_text_width_get` through a `long long (*)(void)` cast makes
the caller read `r0:r1` as a 64-bit result when the callee only defines `r0`.
The harness compares the return register of the *function under test*, not of
its stubbed callees, so 1,012 such calls are invisible to it. That is an audit,
one call at a time.

---

## 3. Recommended application order

Safest first, each step independently attributable. **Do not start while the
parity bring-up is running** — every step below changes either the canonical
sources (parity) or the symbolized sources (the image).

| # | step | why here | re-proof gate |
|---|---|---|---|
| 1 | **G7‑B1** — header extraction: C03, C04, C05 | no call site changes at all; a `static inline` definition moved verbatim into a header cannot change codegen. Also closes part of the `SCARRY4`/pseudo-op link residue AGENTS.md tracks, and removes the absolute host path from 88 files | diff all copies first (several C04 copies differ: `static inline` vs `static __attribute__((always_inline)) inline` — at `-Os` that changes whether a call is emitted, which changes the harness's call trace). Then compile + `nm` compare. No `recon_kit.prove` needed if no function body changed |
| 2 | **G6‑B4** — hardware register names (58 candidates) | textual substitution of an identical integer; codegen unchanged | compile + `cmp` of the `.o` text; still run `cfg_verify` on touched canonical functions because the edit is scripted |
| 3 | **G6‑B3** — the 857 string heads with **no canonical site** (856 pins) | touches only the symbolized/named/readable trees, so **no parity obligation at all** — but it is the single biggest pin retirement, and it exercises the withdraw-object-and-pin transaction on the lowest-risk set | `full_link.py {app,net}` → `nm -u` must be 0; read the affected `.rodata` back out of `zephyr.elf`'s PT_LOAD and byte-compare against `app_update.bin`; re-measure flash |
| 4 | **G6‑B1** — 554 log-argument string literals (554 pins) | pure `const char *` argument position; the value cannot reach anything else | `recon_kit.prove` **and** `tools/cfg_verify.py` on every canonical file touched; then the step-3 link/byte/flash gate |
| 5 | **G7‑B2** — one declaration per logging entry point (C10) | must land before any batch that rewrites a log call, or the wrong prototype gets baked in | read each entry point's prologue in the disassembly; then `prove` + `cfg_verify` on every file whose declaration changed |
| 6 | **G6‑B2** — 623 non-log string literals (614 pins) | consumers may care about pointer identity | as step 4, plus a disassembly read of every non-log consumer |
| 7 | **G7‑B3** — assert + noreturn macros (C01, C12) | depends on G6‑B1 having produced the literals | per-site argument-count check against the disassembly; `prove` + `cfg_verify` per file |
| 8 | **G7‑B4** — log gate and irq-lock prologue (C06, C07) | branch sense and the save/lock/ISB/restore quadruple must be confirmed per site | disassembly review, then `prove` + `cfg_verify` |
| 9 | **G6‑B5 / G6‑B6** — errno negatives and float bit patterns | numeric identity is not evidence; these are per-site confirmations that mostly will not fire | per-site disassembly; sites that cannot be confirmed stay as raw hex |
| 10 | **G7‑B5** — volatile accessors, sub-pass (a) spelling only | 7,543 sites; keep it textual and type-preserving | compile + `.o` byte compare (must be identical) |
| 11 | **G7‑B5** — volatile accessors, sub-pass (b) macros per width | the signedness audit is the work | `prove` + `cfg_verify` per file, plus a signedness read of every consumer |
| 12 | **G7‑B6 / G7‑B7** — net vtable thunks, cast-call audit | dropped-argument class; no batching | one site at a time, by disassembly |
| — | **G6‑A** — 275 ambiguous candidates | produces evidence, not edits; can run in parallel with anything | re-derive the region, then the candidate moves into B1/B2 or into X |

### 3.1 What must be re-proven, and how

* **Any change to a body in `recon/app/src`** → `recon_kit.prove(va, size, name,
  src, nptr, trials)` **and** `PYTHONSAFEPATH=1 .venv/bin/python
  tools/cfg_verify.py app <FUNC>`. A bare `emu.compare` pass without case
  coverage is not acceptable (AGENTS.md critical finding #1).
* **Any change to a body in `recon/net/src`** → `net_recon_kit.prove` **and**
  `tools/cfg_verify.py net <FUNC>`.
* **Any change to `recon/symbolized/{app,net}`** → `tools/full_link.py {app,net}`,
  `nm -u` = 0, 0 duplicate globals, no `--allow-multiple-definition`, and a
  byte comparison of the affected `.rodata` read back out of the linked ELF's
  PT_LOAD against `app_update.bin` / `netcore_image.bin`.
* **Any batch that withdraws a rodata object** → re-measure FLASH against the
  982,528 B (app) / 231,424 B (net) partitions in the same build.
* **Any change touching argument passing or stack layout** → disassembly-level
  review per site. The harness is blind to it (§2.4).

### 3.2 Cross-tree propagation rules

The brief notes that the layering has itself caused bugs. The rules:

1. **A literal or dedupe change is propagated to every tree that contains the
   function**, in this order: `recon/app/src` (or `recon/net/src`) → re-prove →
   `recon/verified/src` → `recon/symbolized/{app,net}` → `recon/named` /
   `recon/net/named` → `recon/readable_sources/app/{g1,library}` →
   `recon/application/src`. The canonical tree is proven first because it is
   the only tree the harness reads.
2. **The mirrors are not all in sync today** — `recon/verified/src` is 3 files
   behind `recon/app/src`, `recon/named` 1 behind, and 29 symbolized files have
   no readable counterpart. **Sync the mirrors before starting**
   (`cp -n recon/app/src/*.c recon/verified/src/`), otherwise a batch will
   appear to have been applied everywhere while three functions silently keep
   the old form.
3. **`recon/app/src_sym` and `recon/verified/src_sym` (1,059 files each) are
   older snapshots.** Either bring them into the propagation list or delete
   them; leaving a third symbolized snapshot around guarantees that a later
   pass edits the wrong one. This plan does neither — it flags it.
4. **The form differs per tree and must not be copied verbatim.** Canonical
   trees spell the reference as a raw `0x…` literal; symbolized/named/readable
   trees spell it as `rodata_<hex>` with a `/*=0xADDR*/` provenance comment.
   The G6 edit is *different text* in the two families and the plan records the
   per-tree file list for each candidate so the two can be driven separately.
5. **Retiring a pin is a three-file transaction**: the literal lands in the
   sources, the object is deleted from `g1_app_string_rodata.c` /
   `recon/application/rodata/g1_*_rodata_0N.c`, and the `PROVIDE` line is
   deleted from `recon/symbols/g1_{app,net}_globals.ld`. Deleting only the
   `PROVIDE` breaks the link; deleting only the object silently resurrects the
   original-image address (§10 of the decode report).
6. **`recon/symbols/*.h` and `*.ld` are generated.** New headers introduced by
   G7 (`g1_assert.h`, `g1_mmio.h`, `g1_cmsis_shim.h`, `g1_ghidra_ops.h`,
   `g1_log.h`) go in `recon/headers/`, never into `recon/symbols/`.

---

## 4. Non-goals — explicitly out of scope for G6 and G7

* **Struct-member accesses.** 65 app + 65 net distinct struct-offset literals
  cover 8,887 sites. Turning `*(int*)(p + 0x10)` into `p->field` is the
  production refactor and needs `recon/structs/struct_catalog_app.json`; it is
  not a literal inline.
* **Naming the 2,217 evidence-free scalars.** 9,483 app + 5,756 net sites. No
  log text, SDK header or register meaning attaches a name. Left as raw hex.
* **Typing the byte-verified blobs as arrays.** Element width is proven for two
  app regions only; the rest stay `unsigned char []` until interprocedural
  argument taint exists.
* **Collapsing the trivially-identical shipped functions (C11).** 28 distinct
  symbols share the body `return N;`. They are real symbols the link needs.
* **Merging `int` with `unsigned int` volatile accesses.** See §2.3.
* **Renaming functions, splitting modules, or changing file layout.** That is
  the module-cohesion end goal (AGENTS.md remaining plan step 6).
* **Anything in `recon/emulator/**`, `tools/`, `armemul`, or the build files.**
  A concurrent parity bring-up owns them.

---

## 5. Biggest hazards, ranked

1. **Flash.** App is at 93.80 % and net at ~97.3 % of their partitions, and
   `KEEP(*rodata_*.c.obj(...))` means `--gc-sections` drops nothing. A G6
   string batch applied without withdrawing the object in the same build
   overflows the partition. (66,243 B app + 3,753 B net at stake.)
2. **The logging prototypes (C10).** 384 distinct signatures for 4 symbols on a
   hard-float build where variadic and non-variadic disagree about where floats
   go. This is a live ABI defect, not a style problem.
3. **Harness blindness.** 19 confirmed instances of the harness passing a wrong
   reconstruction. Six of the twelve G7 clusters touch argument passing or
   stack layout and must be reviewed in disassembly.
4. **The §10 stub hazard.** 60 app + 4 net inline candidates sit on emitted
   objects ≤ 4 B. That is the exact shape that produced the font-directory bug
   (`rodata_8ac2c`, `rodata_98e3c`/`_98fbc`/`_98fe8`). They are held in G6‑A and
   must have their extent re-derived, never trusted.
5. **String-interior references.** 68 app + 4 net pins address the *tail* of a
   longer string. The shipped image shares those bytes; inlining duplicates
   them and, worse, hides that the two call sites were reading one object.
6. **Nine trees.** Three are already out of sync. Any batch applied without a
   pre-sync will leave a silent minority of functions on the old form.

---

## Pre-refactor batch G7-B1 + G6-B4 — APPLIED

The first two batches of §3 have been **applied** to the corpus. The full
record — per-file counts, the copy-diff that bounds G7-B1, the `cmp` results,
every gate, the oracle confirmation and everything deferred with its reason —
is in the sibling file:

> **`recon/analysis/prerefactor_progress.md`**

Headline, so this file is not misleading on its own:

* **Both cores' `zephyr.bin` are byte-identical to the pre-batch baseline.**
  FLASH **952,316 B app / 225,581 B net — Δ 0 B**; RAM **253,765 B / 63,380 B —
  Δ 0 B**. The ELF symbol table is identical, all 9,139 entries. Both batches
  were budgeted at 0 B and landed at 0 B.
* **All four framebuffers still byte-identical** to the committed goldens
  (dashboard `p2_render` `19b1f24a…` 2,923 px, dashboard `p1_boot`
  `0c5cc90b…` 0 px, navigation `p2_render` `b26c73b3…` 1,098 px, navigation
  `p1_boot` `1d617c65…` 656 px), confirmed by re-running both captures.
* Gates: `gen_retained_sources.py --check` clean; both builds exit 0; `nm -u`
  **0/0**; duplicate globals **0/0**; no `--allow-multiple-definition`;
  `check_ram_pin_collisions.py` **0/0** both cores; `check_net_raw_literals.py`
  **0/0**; `check_thread_create_stack_args.py` **10/10**;
  `verify_net_stock_data_window.py` **PROVEN**.

**Two corrections to this document's own analysis, found by applying it.**

1. **§2.2's C03/C04 risk rating is too optimistic.** The gate "diff every copy
   before collapsing" **fails for the majority**. 743 helper definitions form
   **43 distinct families** even after normalising spellings of the *same* type;
   only 10 of 22 helper names have a single family. Several divergences are
   semantic, not cosmetic: a 6-copy **stub family** (`getBasePriority` →
   `return 0`, `setBasePriority` → `(void)p`, `isCurrentModePrivileged` →
   `return 1`), a 6-copy `__atomic_signal_fence` barrier that emits **no**
   instruction where the dominant form emits a real `isb`, and `always_inline`
   spellings. C03 is therefore **not** "the lowest risk in G7" as a whole — the
   *conforming subset* is, and it is 25 of the 38 build-tree files. The other 13
   are deferred, individually, with the divergent helper named.
2. **§1.3's numeric census undercounts, and G6-B4 has a trap the plan does not
   name.** The live scan finds **662 sites in 282 files across nine trees** (241
   in the canonical trees) against the recorded 232; the census recorded only the
   canonical trees. More importantly, **50 sites in 29 files sit inside a
   `UINT32_C()` / `UINT64_C()` macro argument**, which token-pastes a `U` suffix
   (`c ## U`). Substituting anything there is a hard preprocessing error, not a
   silent codegen change — three net TUs failed to compile on the first attempt.
   Those 50 sites stay as raw hex. Any future G6 batch must exclude
   token-pasting contexts.

Also worth carrying forward: **one include spelling**,
`#include "../../headers/g1_<name>.h"`, resolves for the app build, the net build
*and* `tools/parity/recon.py`'s temp-directory TU (through its existing
`-I recon/{app,net}/src`, since GCC concatenates the `-I` dir with the quoted
path). New `recon/headers/` files therefore need **no** build-file or `tools/`
change — which matters because `recon/headers` is on the app build's include path
but not the net build's.
