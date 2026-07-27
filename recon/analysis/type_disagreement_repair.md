# Type-disagreement repair — acting on the Stage 03 `DEFECTS.json` work list

**Status: IN PROGRESS.** Written incrementally as the work runs. Nothing committed.

Inputs:

* `recon/refactor/stage_03_module_structure/DEFECTS.json` — 1,014 entries
* `recon/analysis/staged_refactor_stage03.md` §5, §8.3 (why they block the TU merge)
* `recon/analysis/latent_defect_harvest.md` (the method this pass inherits)

The compiler said WHERE the reconstruction disagrees with itself. It cannot say
which side is right. **The arbiter is the shipped image.**

---

## 0. The work list, re-measured

`DEFECTS.json` is keyed by (module, symbol). Read that way it is 1,014 entries:

| class | entries |
|---|---:|
| `declaration_disagrees_with_definition` | 446 |
| `arity_differs` | 274 |
| `return_type_differs` | 175 |
| `parameter_type_differs` | 119 |
| **total** | **1,014** |

But a symbol's type is a property of the *symbol*, not of the module, and 818
distinct symbols carry those 1,014 entries (`get_device_info` appears in 20
modules, `memset_bytes` in 19, `memcpy` in 13). Corpus-wide, the declaration
population is much larger than the per-module view suggests — in
`recon/symbolized/app` (the tree the cohesive build compiles, 2,153 files):

```
extern function declarations : 6236
function definitions         : 2450
distinct symbols declared    : 2077
distinct symbols defined     : 2416
memcpy       : 99 declarations, 1 definition
memset_bytes : 182 declarations, 1 definition
```

### 0.1 The first split that matters: which disagreements are ABI-observable

Stage 03 defined agreement as **type identity** (§5.1). On this target
(`arm-zephyr-eabi`, AAPCS, hard-float, 32-bit) type identity is far stricter
than *code* identity: `int`, `unsigned int`, `uint32_t`, `uintptr_t`, `void *`,
`char *` and an enum all pass in exactly one core register and generate
byte-identical caller and callee code. So a "disagreement" is either

* **cosmetic** — every spelling maps to the same ABI signature, and the fix
  cannot move a single byte of `.text`; or
* **ABI-real** — the spellings disagree about *arity*, about a 64-bit vs 32-bit
  slot, about a VFP slot, or about whether a value comes back at all.

`scratchpad/td/abi.py` maps a prototype onto its ABI signature. The categories
are `V` void, `W` one 32-bit core word (every full-width scalar **and every
pointer**), `D` a 64-bit core pair, `F`/`G` a single/double VFP slot, and — this
distinction is load-bearing — `b`/`B`/`h`/`H`/`L` for the **narrow** integers
(`int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `_Bool`). Narrow types are *not*
interchangeable with `W`: declaring a parameter `unsigned char` makes the caller
emit `uxtb` before the call, so swapping `int` for `unsigned char` is an
observable codegen change, not spelling. Applied to all 1,014 entries — every
type string parsed, 0 unparsed:

| | entries |
|---|---:|
| cosmetic — identical ABI signature | **310** |
| cosmetic — differ only in `void` vs 32-bit return, or an unknown typedef assumed 32-bit | **110** |
| **ABI-real disagreement** | **594** |

and by class:

| class | ABI-real | cosmetic |
|---|---:|---:|
| `arity_differs` | 274 | 0 |
| `declaration_disagrees_with_definition` | 234 | 212 |
| `return_type_differs` | 71 | 104 |
| `parameter_type_differs` | **15** | **104** |

**The `parameter_type_differs` class is 87 % spelling noise** — 104 of 119
entries are `int` vs `unsigned int` vs `void *` on a 32-bit register. Those
still have to be canonicalised before a TU merge (the compiler rejects them
regardless), but they are not defects in the reconstruction, and correcting them
must move zero bytes. That prediction is testable per object and is used as a
gate below.

### 0.2 A landmine the TU merge would have hit, found while calibrating this

`recon/symbolized/app/__ieee754_exp.c:22` carries a **file-local typedef that
redefines a global one to a different width**:

```c
typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u8; typedef int64_t i8;
```

`recon/headers/g1_types.h:35` declares `typedef uint8_t u8;`. Inside
`__ieee754_exp.c`, `u8` means **uint64_t**; everywhere else in the corpus it
means **uint8_t**. Its seven `extern u8 __aeabi_dadd(u4,u4,u4,u4);`-style
declarations are correct *in that file* and would become 8-bit-return
declarations of the double-precision helpers the moment the file is
concatenated into a module TU. Merging `lib/` without dealing with this is a
silent 64-bit-to-8-bit truncation of every soft-double helper result, not a
compile error. Recorded here; see §7 for what was done about it.

*(Numbers above from `scratchpad/td/abi.py` + `scan.py`; commands in §9.)*

---

## 1. The image oracles this pass adds

`latent_defect_harvest.md` built two oracles for the *logging* entry points
(gate-pair detection, format-string arity). Neither generalises: the symbols in
`DEFECTS.json` are ordinary functions with no format string. This pass adds two
new ones, both read straight off `app_update.bin`, and both swept over the whole
image in 3 s.

### 1.1 The CALLEE oracle — `scratchpad/td/callee.py`

An abstract interpretation over each function's CFG carrying the set of
registers already **defined**, meeting by intersection at joins. It yields, per
function:

* `in_regs` — which of r0..r3 are **read before being written** on some path
  from the entry. A register read before it is written can only be an incoming
  argument. This is an **exact lower bound on arity** that needs no caller and
  no format string. (An argument the body ignores stays invisible, so it is a
  lower bound, never an upper one.)
* `in_stack` — loads of `[sp,#N]` with `N >= frame`, i.e. incoming arguments 5,
  6, … `frame` is the sum of the entry block's `push`/`vpush`/`sub sp`, and the
  function is skipped when `sp` is later written in a way the tool cannot track.
* `in_vfp` — `s0..s15` / `d0..d7` read before written (hard-float arguments).
* `ret_r0_expl` / `ret_r1_expl` — r0 (and r1, i.e. a 64-bit return) written on
  **every** returning path by a **non-call** instruction. The `_expl` qualifier
  is load-bearing: after any `bl` the callee's own result sits in r0, so "r0 is
  defined at the return" is true of a `void` function that merely ends in a
  call. Only an explicit write is evidence of a return value.
* `varargs` — the AAPCS variadic register-save area in the prologue.

Two calibration bugs were found and fixed while validating it, both of which
had produced absurd arities (`nrfx_clock_stop` arity 192):

1. **Interleaved prologues.** GCC emits `push {…}; mov r6,r1; sub sp,#0x2dc`.
   Stopping the frame scan at the first non-`push` gave `frame = 0x24` instead
   of `0x300`, and every local access then looked like an incoming stack
   argument. Fixed by accumulating every `sp` adjustment in the entry block up
   to the first control transfer, and by handling `sub.w`/`subw`.
2. **Ghidra data-inflation (AGENTS.md finding #2).** `in_stack` was scanning all
   declared bytes, including the trailing rodata / the next function's body that
   Ghidra folded into the symbol. Restricted to **CFG-reachable** addresses.

Validation, on functions whose prototype is independently known:

| function | oracle | independent fact |
|---|---|---|
| `get_dashboard_sum_time` `FUN_0004a960` | `in_regs=[]`, `ret_r0_expl` **and** `ret_r1_expl` | declared `long long f(void)` — 64-bit return |
| `get_current_burial_point_type` `FUN_0007dac0` | `in_regs=[]`, `ret_r0_expl`, not `ret_r1_expl` | `unsigned char f(void)` |
| `gui_utf_draw_align_right` `FUN_00044ec4` | `in_regs=[1,2,3]`, `in_stack=[0,4,…,28]` ⇒ arity **12** | definition has exactly **12** parameters |
| `debug_print` `FUN_00019c70` | `varargs` register-save area detected | `void f(const char *, ...)` |

### 1.2 The CALLER oracle

`callsite.analyse_site` from the previous harvest, run over **every** `bl` with
an immediate target rather than only the logging ones: **13,713 call sites** in
`app_update.bin`, each with the backward-CFG-resolved definer of r0..r3 and the
`[sp,#N]` stores in the same window.

The caller side is deliberately used only as *corroboration*. §2 of
`latent_defect_harvest.md` proved it is noisy in one direction — a live
caller-saved register at the `bl` looks like an argument. Measured again here on
`get_current_burial_point_type`, whose callee oracle proves arity 0: four of its
six shipped call sites nonetheless have r0 **and** r3 written in the window.
**The callee oracle is the arbiter; the caller oracle is not.**

---

## 2. What the image says about the definitions themselves

Before touching a declaration: are the **definitions** — the parity-proven
bodies, the things Stage 03 measured the declarations against — right?

1,971 symbols have both a definition in `recon/symbolized/app` and an identity
in the image. Comparing the definition's AAPCS **core-register slot count**
(computed by `slots.py`: a `long long` takes two 8-byte-aligned words; under the
hard-float PCS a non-variadic `float`/`double` parameter takes a VFP slot and
**no** core register) against the image lower bound:

```
definition slots == image lower bound      1521
definition slots >  image lower bound       439   (arguments the body ignores;
                                                   invisible to the oracle)
definition slots <  image lower bound         6   <-- IMPOSSIBLE unless wrong
variadic definitions                          5
```

**Six definitions declare fewer parameters than the shipped body provably
reads.** These are real defects that no pass so far could see — `cfg_verify`
seeds r0..r3 regardless of the declared arity, so a dropped parameter changes
nothing it compares:

| symbol | definition | image lower bound | evidence |
|---|---:|---:|---|
| `lc3_sns_analyze` | 7 | 13 | r0-r3 + `[sp,#32]` |
| `batt_soc_curve_estimate` | 2 | 6 | r0,r1 + `[sp,#4]` |
| `z_impl_k_timer_start` | 3 | 6 | r0,r2,r3 + `[sp,#0]`,`[sp,#4]` |
| `lc3_sns_spectral_shaping` | 6 | 8 | r0-r3 + `[sp,#8]`,`[sp,#12]` |
| `lc3_tns_analyze` | 6 | 7 | r0-r3 + `[sp,#4]`,`[sp,#8]` |
| `main_dispatch_thread_tick` | 7 | 8 | `[sp,#0..12]` |

The four apparent **VFP** shortfalls (`__ieee754_expf`, `lc3_bwdet_run`,
`lc3_energy_compute`, `lc3_tns_analyze`) are **tool false alarms and are not
claimed**: their "incoming" slots are s13/s14/s15, and AAPCS-VFP allocates float
arguments from **s0 upward**, so a read of s14 before a write is scratch use on
a path the abstract interpretation orders pessimistically, not an argument.
Only a contiguous prefix from s0 is evidence; every one of the four has that
prefix already matching its declaration.

---

## 3. `arity_differs` is not a declaration problem — it is 255 missing arguments

All 274 `arity_differs` entries are ABI-real by construction. The question the
compiler cannot answer is whether the *declarations* merely disagree or whether
the **calls** are actually wrong. Counting the arguments each C call passes
(`calls.py`, comment/string/preprocessor aware, declaration and definition
parameter lists masked out) over `recon/symbolized/app` — 19,311 calls in 2,153
files — and comparing against the image, for the 818 `DEFECTS.json` symbols:

```
call sites matching the image lower bound exactly                 6200
call sites passing MORE than the lower bound                      1359
call sites passing FEWER, proven by the callee's REGISTER reads     255
call sites passing FEWER, proven only via the stack-argument bound    33
```

The **255** are a hard result: the callee's prologue reads `r_k` before writing
it, and the source passes fewer than `k+1` arguments. No frame arithmetic and
no caller heuristics are involved. They span **127 symbols**; the worst are
`strlen` (11 sites), `esb_send_command_and_wait_ack` (11), `memset_bytes` (9),
`k_mutex_lock` (6), `memcpy` (5).

Representative, with the shipped instructions:

```c
/* bt_set_name_internal.c:25 */   unsigned uVar1 = strlen();
/* app_msleep_thunk_a.c:17  */   __aeabi_uldivmod(param_1*0x8000+999, param_1>>0x11, 1000, 0);
                                 k_sleep();          /* k_sleep reads r0,r1 */
```

This is the **register-passthrough** shape: the value is already in the right
register — as the enclosing function's own incoming argument, or as the
immediately preceding call's return — so Ghidra had no C-level expression to
attach and emitted none. It is invisible to `cfg_verify` for the same structural
reason as the dropped log arguments: the harness seeds r0..r3 whatever the
declared arity is.

### 3.1 Where the missing value comes from — measured, not assumed

Of the 255, **141** are *unambiguous*: exactly one source call to that symbol in
that file **and** exactly one `bl` to that target in the shipped body, so the
source site and the machine site correspond with no ordering judgement. (The
rest: 46 have no `bl` in the image — `.inc` fragments and tail-called sites; 25
are in files with more than one definition; 34 have equal but >1 counts, which
would need the source-order/address-order matching that
`latent_defect_harvest.md` §6.1 refused to guess at.)

For those 141 sites, walking each missing register backwards to its origin:

```
missing register slots, total                     165
  written by a real instruction in the window      48
  UNDEFINED, walk reaches the FUNCTION ENTRY       82   <- the enclosing
                                                        function's own argument
  UNDEFINED, walk stops at a preceding `bl`        31   <- the previous call's
                                                        return value
  mixed / depth-limited                             4
```

### 3.2 What was repaired — 53 sites, no value invented

A site was repaired only when **all** of these hold, which is a strictly
mechanical rule:

1. the callee's prologue reads `r0..r(k-1)` before writing them (image proof of
   arity ≥ k);
2. the source call passes **zero** arguments;
3. the site is unambiguous in the sense of §3.1;
4. **every** one of `r0..r(k-1)` traces back to the function **entry** still
   undefined — so the value passed is literally the enclosing function's own
   incoming argument *k*;
5. the enclosing function's own parameters occupy one core register each (no
   64-bit, no float), so parameter *i* is register *i*.

**53 sites qualify.** The restored argument list is the enclosing function's own
first *k* parameters, by name. Nothing is invented and nothing is guessed:

```c
/* att_cfm_sent  FUN_00082346 @ 0x82346 */
00082346  push  {r4, lr}
00082348  mov   r4, r1          ; r0, r1 still hold att_cfm_sent's own args
0008234a  cbnz  r2, #0x82350
0008234c  bl    #0x822ae        ; att_optional_sent_cb_dispatch(r0, r1)
```
`FUN_000822ae`'s own oracle says `in_regs=[1]` ⇒ arity ≥ 2, and the walk from
`0x8234c` reaches the entry with r0 and r1 undefined. Repair:
`att_optional_sent_cb_dispatch(param_1, param_2);`

Note that this repair is expected to be **codegen-neutral or codegen-improving**:
the shipped code emits *no* instruction at `0x8234c` to set up r0/r1 because
they are already in place, and so should ours. What it does change is that the
enclosing function must now keep `param_1` live in r0 across the call — which is
exactly what the shipped register allocation does and what our zero-argument
version did not require.

Applied by `scratchpad/td/apply_entry_args.py` across seven trees, keyed by
**function VA** rather than by name, so each tree gets the spelling it uses
(`FUN_000822ae` in `recon/app/src`, `att_optional_sent_cb_dispatch` in
`recon/named` / `recon/symbolized/app`):

| tree | files changed | absent |
|---|---:|---:|
| `recon/app/src` | 53 | 0 |
| `recon/verified/src` | 53 | 0 |
| `recon/named` | 53 | 0 |
| `recon/symbolized/app` | 53 | 0 |
| `recon/app/src_sym` | 33 | 20 |
| `recon/verified/src_sym` | 33 | 20 |
| `recon/readable_sources/app/g1` | 32 | 21 |
| **total** | **310 files** | |

The declaration in each edited file is bumped to the corpus-convention
`unsigned long` slot spelling at the same time, so the file stays internally
consistent.

### 3.3 Gate for §3.2, measured — 53 image-proven arguments restored, zero bytes moved

Baseline `/private/tmp/g1-td-base` (clean build of the tree as found, 07-27
05:49). Repair build `/private/tmp/g1-td-p2a`.

| gate | baseline | after the 53 restorations |
|---|---|---|
| app build | exit 0 | **exit 0, 0 errors** |
| `nm -u` undefined | 0 | **0** |
| app FLASH | 956,480 B / 97.35 % | **956,480 B / 97.35 % — Δ 0** |
| `text` | 492,688 | **492,688 — Δ 0** |
| `rodata` | 456,660 | **456,660 — Δ 0** |
| `datas` | 3,327 | **3,327 — Δ 0** |
| `bss` | 189,230 | **189,230 — Δ 0** |
| **per-object byte comparison** | — | **2,837 uniquely matched, 2,835 identical, 2 differ** |

45 of the 53 repaired `recon/symbolized/app` files are in the retained build
set. **44 of those 45 produced a byte-identical object.** The two differing
objects are:

* `bt_gatt_store_cf.c.obj` — 5,284 → 5,296 B in the *object*, while total
  `text` moved 0 B: a register-allocation shuffle inside one function, which is
  precisely what "the value must now stay live in r0 across the call" means.
* `uname.c.obj` — the stock SDK unit already recorded in
  `prerefactor_progress.md` §0/§4 and Stage 02 §4 as differing build-to-build
  regardless of any change. Not attributable to this pass.

This is the strongest form the containment proof can take here: **53 call sites
gained an argument the shipped image proves is passed, and the flash image did
not grow by one byte** — because the argument was already in the register and
neither compiler needed an instruction to put it there.

One compile error was produced and fixed on the way, and it is worth recording
because it was a bug in *my* transform, not in the reconstruction: the first
version rewrote a declaration by matching its whitespace-normalised text, so
`extern int  conn_auth_cb_get_or_init(void);` (two spaces) was silently not
rewritten while its call site was, giving `too many arguments to function`.
Fixed by rewriting through byte **spans**; the same span-based pass repaired
9 declarations across the 310 edited files.

---

## 4. R8 triage of the INVENTED-argument sites

`latent_defect_harvest.md` §2 found 303 log call sites in `recon/symbolized/app`
passing MORE arguments than the format string consumes, and §6.2 deliberately
left every one of them alone because *some are volatile reads* — deleting a
volatile read changes the number of bus transactions, which is an R8 decision
and not a blanket rule.

Re-measured on the current tree with the same format-arity oracle, and this
time each **surplus argument expression** is classified:

| tree | INERT | VOLATILE | CALL |
|---|---:|---:|---:|
| `recon/symbolized/app` | 287 | **21** | 0 |
| `recon/named` | 220 | 10 | 0 |
| `recon/readable_sources/app/g1` | 153 | 21 | 0 |
| `recon/app/src` / `recon/verified/src` | 108 each | 6 each | 0 |
| `recon/app/src_sym` / `recon/verified/src_sym` | 37 each | 2 each | 0 |
| **total across trees** | **950** | **68** | **0** |

* **VOLATILE** — the surplus expression contains a `volatile` dereference, so
  removing it removes a load from the emitted code. `display_reflash_handler.c`
  is the canonical example the harvest named: the fourth argument is literally
  `*alternate_log`, the log-sink gate load.
* **CALL** — none. No surplus argument is a function call, so the "unknown side
  effect" worry does not arise anywhere in this population.
* **INERT** — a constant, a local, or a plain (non-volatile) memory read.

**In `recon/symbolized/app`, 287 of 308 surplus arguments are provably inert and
21 are volatile reads.** The split is now measured rather than assumed, which is
what §6.2 asked the next pass to establish. What was *done* with it is in §6.

---

## 5. Pass 1 — declaration canonicalisation, and what it refused

The blocking prerequisite Stage 03 named is that a module's files must agree
about a symbol's type *as a type*, not merely as an ABI. `unsigned long` and
`unsigned int` are both one core register and identical codegen, but they are
**different types** to the compiler, so canonicalising onto an invented
convention spelling would not remove a single `conflicting types` error at merge
time. **The canonical spelling is therefore the symbol's own DEFINITION**, with
parameter names stripped.

`scratchpad/td/canon.py` decides, for each of the 818 `DEFECTS.json` symbols:

| outcome | symbols |
|---|---:|
| **canonicalised from the definition** | **147** |
| refused — the declarations disagree about the ABI itself (arity / 64-bit / VFP slot) | 593 |
| refused — `void` definition vs a value-returning declaration | 68 |
| refused — the canonical text would not compile in every tree (§5.2) | 10 |

### 5.1 The `void`-vs-value refusal, 68 symbols — why it is a refusal and not a fix

Rewriting `extern int f(void);` to `extern void f(void);` is not a declaration
repair: some caller **assigns** the result, so the change is a compile error
that can only be resolved by editing that caller's *body*. Which side is right
is a per-function reconstruction question of exactly the shape
`exit_dashboard_burial_point` was (G7-B2: the body was `unsigned int` and
returned the value of a `void` logging call). These 68 are reported as
**unsettled**, not as fixed.

### 5.2 Three transform bugs, all caught by the compiler, all in my tooling

Recorded because each one produced a *wrong* declaration, and two of them were
ABI-wrong, not merely ugly:

1. **`unsigned long` invented for a symbol with no definition.** The fallback
   branch emitted `extern unsigned long f(...)` for the 10 symbols that have no
   definition in the tree. For `thunk_FUN_00071678` — which every one of its 9
   declarations spells as a **pointer** (`int *` / `uint32_t *` / `void *`) and
   whose call sites write `*thunk_FUN_00071678() = 0x22;` — that is a compile
   error, and for `__floatdidf` it was worse: it silently narrowed a
   `unsigned long long` return (r0:r1) to `unsigned long` (r0), **an ABI
   regression the compiler would not have flagged**. Fixed by taking those 10
   canonical texts from the most common spelling at `HEAD` instead of inventing
   one.
2. **A parameter-name stripper that ate type names.** `^(.*?[\w\*])\s*(\w+)$`
   is non-greedy, so `uint32_t` split into `u` + `int32_t` and the declaration
   became `f(u)`. Written into 177 files before it was caught; corrected in the
   same run.
3. **Typedefs that do not exist in every translation unit.** Copying the
   definition's prototype verbatim moved `uint32_t`, `size_t` and finally the
   project type `bt_addr_le_wire_t` into files that include none of the headers
   declaring them. Base-C typedefs are now normalised (`uint32_t` →
   `unsigned int`, `uint64_t` → `unsigned long long`, …); the 10 symbols whose
   prototype contains a genuine `struct`/project type are **refused outright**
   and restored to their `HEAD` text, because rewriting `struct
   notification_message *` into anything else is invention.

### 5.3 What Pass 1 changed

Applied across seven trees, keyed by function VA. (These are the figures from
the final, reproducible run of `apply_all.py` on a clean `HEAD`, after
`dev_api_call_slot0` was withdrawn from the canonical set — see §7.1. The
exploratory run quoted slightly higher numbers before that withdrawal.)

| tree | declarations rewritten |
|---|---:|
| `recon/symbolized/app` | 252 |
| `recon/app/src` | 252 |
| `recon/verified/src` | 252 |
| `recon/named` | 251 |
| `recon/readable_sources/app/g1` | 157 |
| `recon/app/src_sym` / `recon/verified/src_sym` | 57 each |
| refused as ABI-incompatible | 4 |

| gate | baseline | **Pass 1 + Pass 2A** |
|---|---|---|
| app build | exit 0 | **exit 0, 0 errors** |
| `nm -u` undefined | 0 | **0** |
| app FLASH | 956,480 B / 97.35 % | **956,480 B / 97.35 % — Δ 0** |
| flash headroom | 26,048 B | **26,048 B** |
| `text` | 492,688 | **492,692 — +4 B** |
| `rodata` / `datas` / `bss` | 456,660 / 3,327 / 189,230 | **unchanged, Δ 0** |
| app RAM | 253,765 B | **253,765 B — Δ 0** |
| **per-object byte comparison vs baseline** | — | **2,837 uniquely matched, 2,827 identical, 10 differ** |

The ten differing objects, and why each differs:

| object | Δ `.text` | cause |
|---|---:|---|
| `ble_conn_le_prepare_and_connect.c.obj` | −4 | `int`→`unsigned int` return, `u8 *`→`unsigned char *` |
| `bt_gatt_store_cf.c.obj` | 0 | the §3.2 argument restoration (register allocation) |
| `cjson_parse_with_opts.c.obj` | +4 | `int`→`unsigned int` return of `cjson_parse_value` |
| `opt_record_decode.c.obj` | 0 | `int`→`unsigned int` return |
| `request_ancs_attr_ext.c.obj` | +4 | `unsigned`→`const unsigned char *` parameters |
| `st25dv_build_and_write_ndef_records.c.obj` | −4 | six `void *`→typed-pointer parameters |
| `timing_channel_dispatch.c.obj` | −2 | `int`→`unsigned int *` first parameter |
| `ui_refalsh_warp.c.obj` | 0 | `int`→`unsigned long` return |
| `update_box_field_debounce.c.obj` | 0 | `int`→`unsigned int` return |
| `uname.c.obj` | 0 | stock SDK unit, differs build-to-build regardless |

**Honest caveat, stated as a limitation rather than glossed:** `int` versus
`unsigned int` is codegen-identical *at the call* but is **not** semantically
inert in the *caller's expression* — `if (f() < 0)` folds to false if `f` is
declared unsigned. In all nine attributable cases above the result is used only
in an `== 0` / `!= 0` test or assigned to an explicitly-typed local, which is
why the deltas are ±4 B of register shuffling rather than a disappearing branch;
`update_box_field_debounce.c` was disassembled to confirm this (44 B before and
after, a `blt`→`bge` inversion with the two return paths reordered, same
comparison signedness). But the canonical side is the **parity-proven
definition**, so where the two disagree the definition is the better evidence.

---

## 6. Behavioural gate — Renode, seeded, navigation profile

Run against `/private/tmp/g1-td-p1/zephyr/zephyr.elf` (Pass 1 + Pass 2A) and the
**unchanged** net image `/private/tmp/g1-i30e-net`, with
`ORACLE_EMULATION_SEED: 305419896` printed by the capture (the determinism
requirement from iteration 41). `runtime_info_sync` = `0x00015c0c` and
`_end` = `0x2003ff45` are **identical to iteration 41's**, so the probe
addresses `0x20040025 / 0x20040F38 / 0x20040FAA` carry over unchanged and were
re-derived rather than assumed.

| gate | required | measured |
|---|---|---|
| navigation `p1_boot` framebuffer | `1d617c65…`, 656 px | **`1d617c65a688f10e…`, 656 px — `cmp` vs `golden_framebuffer_p1_boot.raw`: NO DIFFERENCE** |
| navigation `p2_render` framebuffer | `b26c73b3…`, 1,098 px | **`b26c73b37d441fc8…`, 1,098 px — `cmp` vs `golden_framebuffer_p2_render.raw`: NO DIFFERENCE** |
| navigation `spim_a` whole run | 3,645 == shipped | **786 + 2,859 = 3,645** (shipped 764 + 2,881 = 3,645) |
| `twim2 p1_boot` LSM6DSO | 1,089 / `7ed8ddcd0c0d…` EQ | **1,089 / `7ed8ddcd0c0d420db885bde4…` — EQ** |
| whole `twim1 p1_boot` per-device set | EQ | **npm1300 291 EQ, opt3001 33 EQ, st25dv_nfc 25 EQ, st25dv_sys 22 EQ** |
| `JBD_FRAMECOUNTER_P2` | 0x0D61 EQ | **0x00000D61 — EQ** |
| `DISPLAY_ON_ctx_fe8` / `ESB_SYNC_ctx_105a` | 0x01 / 0x02 | **0x01 / 0x02** |

`ESB_MASTER_FRAMES` is **0x176** against the shipped 0x175 — one frame more.
The oracle's own `determinism_verification` block lists `RADIO_TX` /
`VC_DATA_EVENTS` / ESB announce responses as `NOT_stable_across_runs` (±~2
frames of `NRF5340_RADIO` model cadence), so this is inside the documented
tolerance and the boolean gate — ESB sync reaching 2 — holds. I record the
number rather than hiding it.

---

---

## 7. Pass 1b — attempted, MEASURED, and WITHDRAWN

Pass 1 refuses a symbol outright when **any** declaration of it anywhere in the
corpus disagrees about the ABI. That throws away the safe rewrites with the
unsafe ones: `delay_scaled_busy_wait` is `void(int)` in one file and
`void(unsigned int)` in another — identical codegen — but was refused because a
third file spells it variadic. Pass 1b (`scratchpad/td/canon2.py`) moved the
decision from the **symbol** to the **declaration**, keeping every safety test
per-declaration (same arity, same 64-bit/VFP slots, same parameter narrowness;
a value return is never rewritten to `void`).

It worked, and it more than doubled the resolved count:

```
canonical prototypes built            734 symbols
declarations rewritten (symbolized/app)      1,294
declarations REFUSED as ABI-incompatible     9,277
DEFECTS.json entries resolved:  104  ->  213
app build exit 0, nm -u 0, FLASH 956,544 B (+64 B), text +60 B
all FOUR framebuffers still byte-identical
```

**And it regressed a named iteration-41 gate, so it was withdrawn.**

| iteration-41 gate | Pass 1 | Pass 1b |
|---|---|---|
| `twim2 p1_boot` LSM6DSO stream | `7ed8ddcd0c0d…` **EQ** | `03537cda890a…` **NE** |
| `twim1 p1_boot` `opt3001_ambient_light` | 33 / **EQ** | 35 / **NE** |

The cause is measured, not guessed. Stripping the tick column from the traces:

* **twim2** differs in **36 lines out of 1,089**, and the difference is a pure
  **permutation**: an 18-transaction window in which the accel/gyro output-
  register block (`W 0x28`/`R×6`, `W 0x22`/`R×6`) moves from *before* to *after*
  a four-transaction config block. The multiset of transactions is identical.
* **twim1** differs only in the interleaving of device `0x6B` (nPM1300) against
  `0x45` (OPT3001) — exactly the case the oracle's own
  `determinism_verification.NOT_stable_across_runs` block names ("three
  independent firmware threads sharing one bus … diff twim1 PER DEVICE").

So Pass 1b's +60 B of `.text` shifted instruction timing enough to reorder two
firmware threads on a shared I²C bus. That is not a semantic defect — but
`twim2 p1_boot` had been byte-EQ under Pass 1 and the acceptance bar names it,
and **"probably benign timing" is not a standard this project accepts**. The
whole of Pass 1b was reverted.

**What was given up, stated plainly: 109 further `DEFECTS.json` entries that
Pass 1b did resolve.** They are recoverable — `canon2.py` and `canon2.json` are
kept — but landing them needs either a `.text`-neutral way to apply them or an
explicit decision that a reordered-but-identical I²C transaction multiset is an
acceptable gate outcome. That decision is not mine to take unilaterally.

### 7.1 One more regression Pass 1 itself caused, found and fixed

`check_thread_create_stack_args` dropped to **9/10**: canonicalising
`dev_api_call_slot0` onto its definition's `unsigned int` third parameter made
`imu_fusion_init`'s harness fixture fail to compile, because that call site
passes a `void *`. The symbol was removed from the canonical set and its nine
declarations restored to `HEAD`; the gate is **10/10** again. The canonical set
is therefore **146 symbols**, and `canon_final.json` records exactly that, so
the pass reproduces.

---

## 8. Final state — every gate, measured

The tree was reset to `HEAD` (`fa603c94` — the concurrent agent committed twice
during this pass; its new baseline build is **byte-identical** to the one taken
at the start, so every measurement above still stands) and the whole pass
re-applied from one script, `scratchpad/td/apply_all.py`:

```
step 1  PASS 2A   53 entry-sourced arguments restored, 310 files, 7 trees
step 2            18 declarations made consistent with their own call sites
step 3  PASS 1    252 declarations canonicalised in recon/symbolized/app
                  (252 / 251 / 157 / 57 / 57 in the other trees), 4 refused
```

**The resulting image is byte-identical (`cmp`, exit 0) to the image whose four
framebuffers and sensor streams were captured in §6**, so those results are
carried over as measurements of *this* tree, not merely of a similar one.

| gate | required | measured |
|---|---|---|
| app build | links | **exit 0, 0 errors** |
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| pin gates, app | 0/0 | **627 bound OK, 0 escaping, 0 unknown inside a live object** |
| `check_thread_create_stack_args --trials 120` | 10/10 | **10/10 PASS** |
| `verify_data.py` | 995/995 | **995/995 byte-exact, 56,279/56,279 B (100.00 %)** |
| app FLASH | 956,480 B / 97.35 % | **956,480 B / 97.35 % — Δ 0** |
| flash headroom | 26,048 B | **26,048 B — Δ 0** |
| `text` / `rodata` / `datas` / `bss` | — | **492,692 (+4) / 456,660 / 3,327 / 189,230 (Δ 0)** |
| app RAM | 253,765 B | **253,765 B — Δ 0** |
| net FLASH | FROZEN 225,581 B | **untouched — no net source, header, symbol or build input modified** |
| per-object byte comparison | — | **2,837 uniquely matched, 2,827 identical, 10 differ** |
| dashboard `p2_render` | `19b1f24a…`, 2,923 px | **`19b1f24a09f97a8d…`, 2,923 px — `cmp` vs golden: NO DIFFERENCE** |
| dashboard `p1_boot` | all-zero | **all 153,600 bytes zero (`0c5cc90b079d0d9c…`)** |
| navigation `p2_render` | `b26c73b3…`, 1,098 px | **`b26c73b37d441fc8…`, 1,098 px — NO DIFFERENCE** |
| navigation `p1_boot` | `1d617c65…`, 656 px | **`1d617c65a688f10e…`, 656 px — NO DIFFERENCE** |
| navigation `spim_a` whole run | 3,645 | **786 + 2,859 = 3,645** |
| `twim2 p1_boot` LSM6DSO | 1,089 / `7ed8ddcd0c0d…` EQ | **1,089 / `7ed8ddcd0c0d420db885bde4…` — EQ** |
| whole `twim1 p1_boot` per-device set | EQ | **npm1300 291 / opt3001 33 / st25dv_nfc 25 / st25dv_sys 22 — all EQ** |
| `JBD_FRAMECOUNTER_P2` | 0x0D61 EQ | **0x00000D61 — EQ** |
| `ESB_MASTER_FRAMES` | — | 0x176 vs shipped 0x175 (inside the oracle's own documented ±2 radio-cadence tolerance; `ESB_SYNC` still reaches 2) |

### 8.1 The four-way split, final

| class | FIXED | CONFIRMED REAL, not fixed | FALSE ALARM | UNSETTLED |
|---|---:|---:|---:|---:|
| `arity_differs` | 0 | **117** | 0 | 157 |
| `declaration_disagrees_with_definition` | 62 | 41 | 141 | 202 |
| `parameter_type_differs` | 28 | 28 | 49 | 14 |
| `return_type_differs` | 14 | 31 | 73 | 57 |
| **total (1,014)** | **104** | **217** | **263** | **430** |

*FIXED* is measured by **re-running Stage 03's own agreement test** on the
current tree (`remeasure.py`: identical type-identity criterion, identical
per-module file sets) — not by counting edits. *CONFIRMED REAL* means the image
proves a defect for that symbol (a call site passing fewer arguments than the
callee's prologue reads, §3, or a short definition, §2). *FALSE ALARM* means
every spelling maps to the same ABI signature, so **no call site emits wrong
code** — the entry exists only because the agreement criterion is type
identity. *UNSETTLED* is an ABI-real disagreement this pass did not settle.

Note that the 53 argument restorations of §3.2 appear under `arity_differs` as
**0 FIXED**: restoring the argument at one call site does not make the other
files in that module agree about the symbol's arity. The repair is real and
image-proven; the *entry* stays open until every declaration and every call site
of that symbol is brought to the same arity.

---

## 9. What I did NOT close, and why

1. **910 of 1,014 entries remain open.** 430 are ABI-real disagreements this
   pass did not settle; 263 are false alarms that still need canonicalising for
   the merge; 217 are confirmed-real defects with per-site image evidence but no
   repair. The largest single block is `arity_differs` (274 entries, 0 closed).

2. **202 of the 255 register-proven missing-argument call sites are not
   repaired.** The repaired 53 are exactly those where the value is the
   enclosing function's own incoming argument and the source/machine match is
   unambiguous. The rest break down as: 48 register slots written by a real
   instruction in the window (the argument is an expression that must be
   *reconstructed*, not merely named); 31 whose value is the immediately
   preceding call's return, which needs a new local and therefore a `cfg_verify`
   re-proof of the enclosing function; 46 with no `bl` in the image (`.inc`
   fragments, tail calls); 25 in files with more than one definition; 34 where
   the source-order/address-order match is ambiguous — the same refusal
   `latent_defect_harvest.md` §6.1 made for `key_event_thread`. **A wrong
   argument is worse than a missing one**; that principle decided every one of
   these.

3. **The 6 short DEFINITIONS (§2) are identified but not repaired.**
   `lc3_sns_analyze` (7 vs 13), `batt_soc_curve_estimate` (2 vs 6),
   `z_impl_k_timer_start` (3 vs 6), `lc3_sns_spectral_shaping` (6 vs 8),
   `lc3_tns_analyze` (6 vs 7), `main_dispatch_thread_tick` (7 vs 8). Adding a
   parameter to a definition changes the function's own body contract and
   requires a `cfg_verify` re-proof per function plus a matching repair at every
   call site. That is a reconstruction task, not a declaration task.

4. **The 303 INVENTED-argument sites are triaged (§4) but not corrected.**
   The split is now measured — 287 inert / 21 volatile / 0 call in
   `recon/symbolized/app` — which is what `latent_defect_harvest.md` §6.2 asked
   the next pass to establish. Correcting even the 287 inert ones **deletes**
   argument-setup instructions and therefore moves `.text` in the opposite
   direction from every other change here; Pass 1b (§7) has just demonstrated
   that a 60-byte `.text` move is enough to reorder two firmware threads on a
   shared I²C bus and break a byte-equality gate. Deleting ~287 argument setups
   is a much larger move than 60 bytes. It needs its own pass, its own baseline,
   and its own capture — not a ride-along.

5. **The 36 zero-argument sites in `key_event_thread.c` are untouched.** Both
   gate halves are empty, there is no donor branch, and source order does not
   follow address order in a 2,702-byte function. Nothing in this pass's oracles
   changes that: the callee oracle gives the *arity* of `log_message`/
   `debug_print` (variadic — it gives nothing), and the format-string oracle
   needs a format string, which is exactly what is missing. They remain behind
   the two `__asm__`-renamed placeholders, which are still byte-identical to the
   baseline.

6. **`__ieee754_exp.c`'s local `u8` redefinition (§0.2) is recorded, not
   fixed.** Renaming the file-local typedefs is trivial; deciding it is safe is
   not, because every one of that file's declarations and its own body read `u8`
   as 64-bit. It must be done as one atomic rename with a `cfg_verify` re-proof,
   and it must be done **before** `lib/` is merged into a TU, or the merge
   silently truncates every soft-double helper result to 8 bits. This is the
   single highest-risk item this pass found and did not close.

7. **The net core was not modified.** Measured, not assumed:
   `git status --porcelain recon/net recon/symbolized/net recon/readable_sources/net`
   is empty, and no shared input (`recon/headers`, `recon/symbols`,
   `recon/application`, `recon/board`, `recon/generated`, `recon/wiring`)
   changed. The 225,581 B freeze holds by construction; no net build was needed
   and none was run. `DEFECTS.json` is app-only (Stage 03 §4.1).

8. **`recon/refactor/` was not modified** — `git status --porcelain
   recon/refactor/` is empty. The work list was read, never written.

9. **`cfg_verify` was not re-swept.** It is structurally blind to this entire
   defect class (that is the premise of the work), so a green sweep would prove
   nothing about these changes. The per-object byte comparison and the four
   framebuffers are the stronger evidence and are what was run.

10. **Nothing was committed.** The tree is left dirty.

---

## 10. Reproducing

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
T=<scratchpad>/td

# image oracles (3 s over the whole app image)
$V $T/sweep.py app $T/image_app.json      # 2,377 functions, 13,713 call sites
$V $T/scan.py  recon/symbolized/app $T/symb_app.json   # 6,236 decls, 2,450 defns
$V $T/calls.py recon/symbolized/app $T/calls_app.json  # 19,311 calls
$V $T/table.py                                          # per-symbol table

# the single applier (from a clean HEAD)
$V $T/apply_all.py            # DRY RUN;  --apply to write

# gates
recon/application/build_cohesive.sh app /private/tmp/g1-td-final2
$V tools/verify_data.py
$V recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
$V recon/emulator/scripts/check_ram_pin_collisions.py /private/tmp/g1-td-final2/zephyr/zephyr.elf
$V /tmp/objcmp.py /private/tmp/g1-td-base2 /private/tmp/g1-td-final2
$V $T/remeasure.py            # Stage 03's own agreement test, re-run

# behavioural oracle (SEEDED; the seed is printed as ORACLE_EMULATION_SEED)
printf '$rtinfo_pc=0x00015c0c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-td-cap/ours-paired.resc
bash -c 'F=$(mktemp -u); mkfifo $F; sleep 100000 > $F & W=$!
G1_RESC=/private/tmp/g1-td-cap/ours-paired.resc \
G1_APP_ELF=/private/tmp/g1-td-final2/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_td_nav < $F
kill $W; rm -f $F'      # dashboard: same, with G1_ATT_WRITE=""
$V recon/emulator/scripts/build_display_sensor_oracle.py /private/tmp/g1_td_nav /private/tmp/g1-td-cap/rep-nav
cmp /private/tmp/g1-td-cap/rep-nav/golden_framebuffer_p1_boot.raw \
    recon/emulator/reports/golden_framebuffer_p1_boot.raw
```

**Nothing was committed. The tree is left dirty.**
