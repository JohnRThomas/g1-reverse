# Type-disagreement repair, pass 3 — size-neutral repairs only, gated per object

**Status: COMPLETE.** Written incrementally as the work ran. Nothing committed.

Renode belongs to a concurrent agent this pass. **No framebuffer, no sensor
stream and no boot capture was run or is claimed.** The only gate available is
a per-object one, and it is used as a *filter*, not as a post-hoc
justification: an edit that moves an allocatable byte is reverted and recorded
as quarantined with its measured `.text` delta, never argued around. §2 defines
the gate and why it differs from pass 2's; §2.1 and §5.1 record the negative and
positive controls that prove each new probe actually bites.

Result in one line: **51 ledger entries closed, `app_update.bin` payload
byte-identical to HEAD's (957,072 of 957,328 bytes, `cmp -n 957072` exit 0),
FLASH 956,480 B Δ 0, and two calibration bugs found in the inherited oracles —
one of which was about to inject a real ABI defect into working code.**

---

## 0. Starting point, measured

```
HEAD          3d3ee155  "Stage 04-B FAILS R7: there is NO LANDING BETWEEN THE SLOTS
                         -- size compensation refuted"
working tree  clean except `?? Even+Realities_1.9.0.xapk` (not mine)
```

> The `gitStatus` snapshot carried into this brief again listed a different
> history (`6aa09be0 G5: decode the .rodata sector` at the tip, ten modified
> files). That is **not** this checkout — the same discrepancy pass 2 recorded.
> `git log --oneline` gives `3d3ee155`; `git status --porcelain` gives exactly
> one line. Every number below is against `3d3ee155`.

Pass 2's work and iteration 43's are both **already committed** (`e78474a4`,
`fc11c2c8`), so this pass starts from a tree that contains them.

### 0.1 `DEFECTS.json`, re-run

The brief said the count has moved repeatedly (1,014 → 833 → 930 → 940 → 949).
At HEAD it is **949**, and the composition has changed: two classes exist that
did not exist for pass 2.

| class | entries at HEAD |
|---|---:|
| `reconstructed_declaration_shadows_an_sdk_symbol` | 299 |
| `declaration_disagrees_with_definition` | 296 |
| `arity_differs` | 163 |
| `return_type_differs` | 131 |
| `parameter_type_differs` | 59 |
| `reconstructed_declaration_shadows_an_sdk_macro` | 1 |
| **total** | **949** |

Stage 03's own agreement test (`td/remeasure.py`, unmodified from pass 1) on the
live `recon/symbolized/app` tree:

```
STILL disagreeing: 721  {decl_vs_def 296, arity 163, return_type 131,
                         param_type 56, shadows_sdk_symbol 75}
now AGREEING     : 228  {shadows_sdk_symbol 224, param_type 3, shadows_sdk_macro 1}
```

**That 228 is not 228 fixes.** 225 of the 228 are the two new `shadows_*`
classes, and `remeasure.py` applies the wrong criterion to them: those entries
carry a **single** spelling (`{"extern int memcmp(const void*,const void*,unsigned long);": 1}`),
so a test for "do the spellings in this entry's files agree" is vacuously true.
The shadow classes are counted separately below and not credited as fixed.

**Baseline for this pass: 949 entries, 721 still disagreeing under Stage 03's
criterion.**

### 0.2 Baseline build

`recon/application/build_cohesive.sh app /private/tmp/g1-td3-base`, from
scratch, exit 0.

```
FLASH  956,480 B / 982,528 B   97.35 %      RAM 253,765 B / 440 KB  56.32 %
app_update.bin 957,328 B
```

Matches the acceptance figure in the brief (~956,480 B / 97.35 %) exactly.

---

## 1. The oracles, re-validated at HEAD

Re-swept: **2,377 functions, 13,713 call sites, 4 s** — and every one of the
2,377 callee records is **byte-identical to pass 2's sweep** (`json` compare,
0 differing records). The four published validation cases reproduce:

| function | oracle at HEAD | independent fact |
|---|---|---|
| `get_dashboard_sum_time` (`FUN_0004a960`) | `in_regs=[]`, `ret_r0_expl` **and** `ret_r1_expl` | declared `long long f(void)` |
| `get_current_burial_point_type` (`FUN_0007dac0`) | `in_regs=[]`, `ret_r0_expl`, not `ret_r1_expl` | `unsigned int f(void)` |
| `gui_utf_draw_align_right` (`FUN_00044ec4`) | `in_regs=[1,2,3]`, `in_stack=[0,4,…,28]` ⇒ 12 | definition has 12 parameters |
| `debug_print` (`FUN_00019c70`) | `varargs` save area at 0 | `void f(uintptr_t, ...)` |

The four known calibration bugs also reproduce unchanged: `__aeabi_uldivmod`
still reports the spurious `in_stack=[4,8,12]`; the three self-clearing idiom
functions are still exactly `FUN_0004ff00`, `FUN_0004ff38`, `FUN_0007e2ec`;
the tail-call thunk finder still returns **94**; `z_spin_unlock_valid` still
reports the scratch `ret_r1_expl`.

### 1.1 CALIBRATION BUG 6 — the missing-argument selector counts COMMAS, not ABI SLOTS

This is new, it is mine, and it invalidates part of a number this brief carried
in as settled.

`constargs.py` (iteration 43) decides a call site is short with

```python
if src['nargs'] >= lb: continue          # nargs = source commas + 1
```

`nargs` is the number of comma-separated argument *expressions*; `lb` is the
number of core registers r0..r3 the callee reads before writing. **Those are
not the same quantity.** Under AAPCS on this target (`-mfpu=fpv5-sp-d16`, so
`double` is *not* a VFP type) a `long long`, a `double`, or an 8-byte struct
argument occupies **two** core registers, 8-byte aligned. One source argument
can fill r2 *and* r3.

Three worked examples, read out of the tree:

```c
/* recon/symbolized/app/ble_ancs_data_req_thread.c */
extern void z_impl_k_sem_take(void*,int64_t);
   z_impl_k_sem_take(c+0x200,-1LL);      /* line 45 */
   z_impl_k_sem_take(c+0x1e8,0x8000LL);  /* line 47 */

/* recon/symbolized/app/dev_reg_modify_bits.c */
typedef struct { long long ticks; } g1_k_timeout_t;
extern int k_mutex_lock(unsigned int mutex, g1_k_timeout_t timeout);
   k_mutex_lock(mutex, (g1_k_timeout_t){ .ticks = -1 });   /* line 51 */
```

The selector reported all three as "missing r2 and r3, and the image proves the
constants are `-1,-1` / `0x8000,0` / `-1,-1`". Those constants are exactly the
two halves of the 64-bit argument **the source already passes**. Nothing is
missing. Had they been "repaired" by appending two more arguments, the result
would have been a genuine ABI defect injected into working code — the precise
failure mode the four-way split exists to prevent.

Corrected census, counting core-register slots from the local declaration in the
very file that makes the call (`td3/slotaudit.py`, `td3/shortcalls.py`; a
64-bit-payload struct typedef declared *inside* the file is resolved to `D`):

| population | comma-count criterion | slot-aware, first cut | false alarms removed |
|---|---:|---:|---:|
| corpus-wide missing-argument sites | **361** over 190 symbols | 347 over 186 symbols | 14 |
| iteration 43's paired sites | 295 | 287 | 8 |
| iteration 43's 56 constant-proven sites | 56 | 52 | 4 |

**These are not the final numbers** — my own slot counter still had a bug at
this point (§1.2), and the corrected census is in the table there. Recorded in
this order because that is the order in which it was found.

### 1.2 CALIBRATION BUG 7 — `long long` read as a parameter NAMED `long`

Found by reading a diff my own tool had just written, not by trusting a sweep.
The parameter-type splitter treats the trailing identifier of a declarator as
the parameter *name*:

```c
/* recon/symbolized/app/settings_load_subtree_direct.c */
extern int k_mutex_lock(void *, long long);
  k_mutex_lock(&g_settings_lock, -1LL);      /* line 40 */
```

`param_types("long long")` matched `(.*?)\s*\b(\w+)$` and returned type
`"long"`, parameter name `"long"` — one 32-bit slot instead of two. The site
was therefore still counted as "missing r2 and r3", and the applier duly wrote

```c
extern int k_mutex_lock(void *, long long,int,int);
  k_mutex_lock(&g_settings_lock, -1LL, -1, -1);
```

which passes `K_FOREVER` twice. Rule adopted: **the trailing identifier is a
parameter name only if it is not itself a type keyword** (`long int char short
unsigned signed double float void _Bool`). The edit above was reverted before
any build.

Corrected census after both calibration fixes:

| population | comma-count | slot-aware | false alarms |
|---|---:|---:|---:|
| corpus-wide missing-argument sites | **361** / 190 symbols | **345** / 185 symbols | 16 |
| iteration 43's paired sites | 295 | 286 | 9 |
| iteration 43's 56 constant-proven sites | 56 | **51** | **5** |

The 16 corpus-wide false alarms: `z_impl_k_sem_take` ×4, `k_mutex_lock` ×4,
`u64_sub` ×2, and one each of `dcmp_negate_rhs`, `__truncdfsf2`, `k_msgq_get`,
`__floatdisf`, `FUN_0007e624`, `z_add_timeout`.

---

## 2. The gate this pass uses, and why it is different from pass 2's

Pass 2 required **whole-object byte identity**. That is stricter than the
question actually being asked, and it costs real repairs: `.debug_info`,
`.debug_str` and `.debug_abbrev` record type *spellings*, so a declaration
respelt from `unsigned long` to `size_t` — ABI-identical, zero codegen effect —
changes the object and would be reverted.

Only **allocatable** sections reach flash. This pass therefore gates on

> **GATE A — every allocatable section's bytes are identical**
> (`.text*`, `.rodata*`, `.data*`, `.ARM.exidx*`, `.init_array*`, `.bss*`,
> extracted with `objcopy -O binary` and compared by SHA-256), with
> **GATE B — whole object identical** reported alongside.

Gate A ⇒ the linked image is byte-identical, which is exactly pass 2's claim,
reached without rejecting DWARF-only differences.

### 2.1 The screen, and its negative control

`td3/screen.py` recompiles ONE file with the exact command line the cohesive
build recorded in `compile_commands.json` and compares against that build's
object. Cost ≈ 1 s per candidate instead of one full build.

* **Determinism check:** recompiling unmodified `confirm_message.c`,
  `DashBoard_Reflash.c`, `key_event_thread.c`, `process_task_sync_event.c`
  reproduces the baseline object **byte for byte**.
* **Negative control (required — degenerate fixtures have burned this project
  four times):** changing one constant in `process_task_sync_event.c`
  (`sync_to_slave(uVar5, 0xd, 0)` → `… , 1)`) yields
  `base 10820 B sha fd91d1764ed1 / new 10820 B sha 47206f4f111c` —
  **same size, different bytes.** A size-only test would have missed it. The
  screen bites.

### 2.2 A defect in my own gate, found by the build

`screen.entry(path) is None` was read as "not a build input, therefore zero
flash risk". **That is false for `.inc` files**: they are build inputs through
`#include`. Four of them (`ble_process_put_ops_09_10.inc`, `…_0b_18`,
`…_19_20`, `…_21_27`) were edited in §4 and slipped the gate, and the first
full build **failed**:

```
ble_process_put_ops_09_10.inc:23:14: error: conflicting types for 'memcpy';
  have 'void *(void *, const void *, size_t)'
ble_process_put_common.h:61:12: note: previous declaration with type 'int()'
```

All four were reverted; `ble_process_put_req.c` then gates **B** (whole object
identical). Rule adopted: a file that is not a `compile_commands.json` entry is
only ungated if nothing `#include`s it — checked, and in this tree the *only*
included non-header sources are those five `ble_process_put_ops_*.inc` files.

---

## 3. Repair track 1 — the 51 constant-argument sites: NONE is free, measured

The brief carried these in as "56 recorded, ranked, unapplied". §1.1 reduces
them to 51. All 51 were applied file by file and screened.

```
KEPT (gate A or B)                                0 files
QUARANTINED (allocatable bytes changed)          15 files, 47 sites
NOT A BUILD INPUT (ungated, zero flash effect)    3 files,  5 sites
COMPILE ERROR                                     1 file, 12 sites
```

**Not one of the 51 sites is free.** Measured `.text` deltas, per object:

| file | sites | callee(s) | `.text` | Δ |
|---|---:|---|---|---:|
| `key_event_thread.c` | 9 | `k_msleep`, `display_inputEvent`, `display_DelayClose`, `device_info_set_mode`, `change_work_mode_to`, `reset_esb_sync_state` | 2128 → 2152 | **+24** |
| `process_task_sync_event.c` | 6 | `sync_to_slave` | 568 → 580 | **+12** |
| `fuel_gauge_update.c` | 1 | `sync_to_slave` | 1436 → 1444 | +8 |
| `gpio_nrfx_pin_configure.c` | 2 | `gpiote_in_init` | 392 → 400 | +8 |
| `ui_teleprompter_task.c` | 3 | `k_mutex_lock`, `sync_to_slave` | 3192 → 3200 | +8 |
| `low_speed_peripheral_dispatch_thread.c` | 3 | `sync_to_slave`, `esb_send_command_and_wait_ack` | 1028 → 1032 | +4 |
| `prepare_quick_note_mode.c` | 1 | `send_event` | 44 → 46 | +2 |
| `display_dispatch_thread.c` | 2 | `sync_to_slave` | 2456 → 2456 | **0** |
| `hci_le_generate_dhkey.c` | 1 | `z_log_msg_runtime_create` | 164 → 164 | **0** |
| `l2cap_recv.c` | 1 | `bt_conn_create_pdu` | 1144 → 1144 | **0** |
| `local_esbs_ipc_service_recv.c` | 1 | `update_persist_task_status` | 1064 → 1064 | **0** |
| `pow.c` | 1 | `__divdf3` | 452 → 452 | **0** |
| `process_for_new_message_come_on.c` | 1 | `sync_to_slave` | 668 → 668 | **0** |
| `process_pt_data.c` | 1 | `set_pending_state_flag` | 532 → 532 | **0** |
| `rpmsg_virtqueue_channel_init.c` | 1 | `z_impl_k_sem_init` | 516 → 516 | **0** |
| **total** | **33** | | | **+66 B** |

**+66 B for the whole class.** Iteration 42 measured that **+16 B** collapses the
dashboard and Stage 04-B proved there is no landing between the OPT3001 slots
(step 100.5 ms, margin 55.6 ms). +66 B is not a marginal call.

### 3.1 The 9 sites that ARE size-neutral — the recommended first batch

The eight zero-delta files pass the finer test iteration 43 used:

```
display_dispatch_thread.c   hci_le_generate_dhkey.c   l2cap_recv.c
local_esbs_ipc_service_recv.c   pow.c   process_for_new_message_come_on.c
process_pt_data.c   rpmsg_virtqueue_channel_init.c
      nm -S: functions changing size ......... 0   (all eight)
      .text total delta ...................... 0   (all eight)
      allocatable bytes ...................... DIFFER (all eight)
```

Same shape as iteration 43's `memcpy` repair (427 image bytes changed, `.text`
delta 0, `nm -S` zero functions changed size), which a full seeded capture on
both stimuli then proved byte-identical.

**They were NOT landed.** Two of them (`display_dispatch_thread.c`) sit on the
display path the framebuffer gate measures, and the repair *changes what the
callee receives* — from whatever the compiler left in r3 to the shipped `0`.
That is a behavioural change, correct in direction and unmeasurable here.
Landing an unmeasurable behavioural change to reach a source-fidelity number is
exactly the trade this project has refused four times. They are recorded, with
the evidence a Renode-owning pass needs to land them in one capture.

### 3.2 Two further facts the class produced

* `pow.c:60` is not a missing argument but a **wrong-width** one:
  `extern uint64_t __divdf3(uint32_t,uint32_t); … __divdf3(0,0)` where
  `__divdf3` takes two `double`s. On `-mfpu=fpv5-sp-d16` a `double` travels in
  a core register pair, so the shipped code sets r0..r3 and ours sets r0,r1.
  The site computes `0.0/0.0` to raise `EDOM` (`errno = 0x21`); today the
  numerator is 0 and the denominator is whatever is in r2:r3.
* The repair is **not per-site independent**. Widening
  `extern int sync_to_slave(char *, int, int);` in `process_for_new_task.c`
  broke a *thirteenth* call at line 1296 that the constant selector never
  admitted (`too few arguments to function 'sync_to_slave'`). A declaration
  cannot be widened without repairing every call in that file.

---

## 4. Repair track 2 — the `u8` typedef collision, CLOSED for zero flash bytes

The brief calls this "the highest-risk item": inside `__ieee754_exp.c` the name
`u8` means `uint64_t`, while `recon/headers/g1_types.h` and 40-odd other files
mean `uint8_t`, so merging `lib/` into one translation unit would silently
truncate every soft-double helper return to 8 bits — and it is **not** a compile
error.

Swept: **exactly one file in the corpus defines `u8` as a 64-bit type**
(`grep -ln 'typedef[^;]*\(uint64_t\|unsigned long long\|int64_t\)[^;]*\bu8\b'`
over all 2,153 sources → `__ieee754_exp.c`), and one defines `i8` as `int64_t`
(the same file). So the repair is a single atomic rename, not a corpus-wide one.

```
recon/symbolized/app/__ieee754_exp.c:22
-  typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u8; typedef int64_t i8;
+  typedef uint32_t u4; typedef int32_t i4; typedef uint64_t u64; typedef int64_t i64;
   … 16 uses of `u8`, 2 of `i8` renamed
```

Gate:

```
whole object   17712 B sha d3de8726522e  ->  17716 B sha d0e3752e5e0e   (GATE B fails)
allocatable    0d3c35a46acc34a8 / 752 B  ->  0d3c35a46acc34a8 / 752 B   (GATE A PASSES)
```

The object grows 4 bytes **entirely in `.debug_str`** — the typedef's name. Not
one allocatable byte moves. This is precisely the repair pass 2's whole-object
gate would have thrown away.

Mirrored to `recon/app/src/FUN_00012db0.c`, `recon/verified/src/FUN_00012db0.c`,
`recon/named/__ieee754_exp.c`,
`recon/readable_sources/app/library/__ieee754_exp.c`.

**Item 6 of pass 2's "what I did NOT close" is closed.** The remaining 29
incompatible typedefs in Stage 04's `HAZARDS.json` are function-pointer
typedefs (`fp_t`, `fn_t`, `codeptr`, `callback_t`, …) whose per-file meanings
genuinely differ; they are not touched here.

---

## 5. Repair track 3 — the shadow class, measured for the first time

`reconstructed_declaration_shadows_an_sdk_symbol` (299) plus
`…_an_sdk_macro` (1) is **31.6 % of the whole ledger** and no pass has examined
it. Stage 03's agreement test *cannot*: those entries carry a single spelling,
so "do the spellings agree" is vacuously true and it reports 224 of them as
already fixed.

The real question is the merge hazard: when the file joins a TU in which the
SDK's own declaration is visible, do the two declarations conflict? C accepts a
compatible redeclaration and rejects an incompatible one, so the compiler
answers it exactly. `td3/shadowprobe.py` compiles

```
<21 Zephyr/newlib headers>
<our declaration>
```

with the cohesive build's real flags.

### 5.1 The probe was degenerate on the first run, and the control caught it

First run: **0 conflicts of 284**. The positive control — replace our
declaration with one that cannot be compatible with anything
(`extern struct g1_probe_tag_never { int a; } SYM(int,char,double,void*,long long);`)
— returned **0 bites of 110**. A probe that never fires on a deliberate
mutation proves nothing.

Cause: the error filter tested for the literal `' error: '`, and the build
passes `-fdiagnostics-color=always`, so the text is
`\x1b[01;31m\x1b[Kerror: \x1b[m\x1b[K`. Stripping ANSI before matching fixed
it. **Re-run of the control: 23 of 23 symbols bite.** Only then were the
results used.

### 5.2 What the class actually is

```
shadow entries                                        300
distinct (symbol, spelling) probes                    284
CONFLICT with the SDK's own declaration               258   (91 %)
compatible                                             26   (23 symbols,
                                                             every one
                                                             positive-control
                                                             verified)
```

Top conflicting symbols: `assert_post_action` ×17, `memcpy` ×14,
`z_impl_k_sem_take` ×12, `memcmp` ×8, `z_spin_unlock_valid` ×8,
`z_impl_k_sem_init` ×7, `strcpy` ×7, `k_mutex_lock` ×7, `snprintf` ×6,
`atomic_set_bit` ×6, `atomic_test_bit` ×6.

**The class is overwhelmingly real, and it was being scored as 75 % fixed.**

### 5.3 The repair — adopt the SDK's own prototype, read out of GCC

The conflicting-declaration error prints the authoritative prototype:

```
note: previous declaration of 'free' with type 'void(void *)'
```

`td3/sdktypes.py` harvests it for every shadowed symbol (**83 of 110
recovered**; the other 27 are `static inline`s or macros, for which GCC reports
a *definition*, not a declaration, and the repair is a deletion rather than a
respelling — not attempted). `td3/applysdk.py` replaces our declaration with
it and gates each file.

```
files edited                     327
  GATE A (allocatable identical) 111
  GATE B (object identical)        4
  FAIL  (ABI genuinely differs)   20   -> reverted
  compile error                  188   -> reverted
  not a build input                4   -> kept, syntax-checked standalone
skips: no SDK prototype recovered 93   compatible already 21
       declarator not isolated     7
```

The 188 compile errors are files whose bodies have no declaration of the SDK's
parameter types in scope (`struct _reent`, `FILE`, `k_timeout_t`); pulling the
header in is a different repair with a different risk profile and was not done.

**115 files now carry the SDK's exact prototype and not one allocatable byte
moved.**

### 5.4 Shadow class, before and after — on the criterion that means something

Both measured with the same probe, the "before" read out of `git show HEAD:`:

```
                        entries   CONFLICT   clean
before (HEAD)             300        273       27
after  (this pass)        300        236       64
                                    -----
entries closed                        37
```

Per (entry, file) pair: **668 of 714 conflicting → 525 of 714**, i.e. **143
declaration sites** stopped conflicting with the SDK.

---

## 6. Repair track 4 — declaration canonicalisation, rounds 1 and 2

Pass 2's canonicaliser (`canon3.py`, image-arbitrated, unchanged) re-run at HEAD
with the frozen set **cleared**, so every file pass 2 reverted for a
whole-object difference is a candidate again under Gate A.

| round | targets | canonical chosen | files edited | GATE A | GATE B | FAIL | compile error | not built |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 | 727 | 591 | 210 | **53** | 0 | 114 | 23 | 20 |
| 2 (frozen-spelling rule) | 727 | 580 | 123 | **57** | 2 | 40 | 7 | 17 |

Round 3 was not run: pass 2 measured round 3 at +3 entries and the sequence was
already flattening. 184 files are frozen.

Stage 03's agreement test after each step:

```
baseline                       STILL 721
after canonicalisation r1      STILL 714
after canonicalisation r2      STILL 712
after the SDK-prototype pass   STILL 714   <- see below
final                          STILL 714
```

The two-entry rise at the SDK step is real and is not hidden: adopting the
SDK's prototype in one file of a shadow entry can *introduce* a spelling
difference against a sibling file that keeps ours. It is a move from "both
files wrong the same way" to "one file right"; the shadow measurement in §5.4 is
the one that counts for that class.

Non-shadow classes only, where Stage 03's criterion is the right one:

```
baseline   decl_vs_def 296 + arity 163 + return 131 + param 56  =  646
final      decl_vs_def 294 + arity 163 + return 123 + param 55  =  635
                                                                  ---
                                                             11 closed
```

---

## 7. Gate ladder — the authoritative clean build

`recon/application/build_cohesive.sh app /private/tmp/g1-td3-final`, from
scratch, against `/private/tmp/g1-td3-base` built from HEAD before any edit.

| gate | required | measured |
|---|---|---|
| app build | links | **exit 0** |
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| pin gates, app | 0/0 | **627 bound OK, 0 escaping, 0 unknown inside a live object** (20 raw literal pins outside the RAM region, 3 abs symbols not in the linker scripts — both unchanged from baseline) |
| pin gates, net | 0/0 | **0 escaping, 0 unknown inside a live object** — run on the FROZEN `/private/tmp/g1-i30e-net/zephyr/zephyr.elf`, `zephyr.bin` **225,581 B**, not rebuilt: no net input was touched |
| `check_thread_create_stack_args --trials 120` | 10/10 | **10/10, EXIT=0** |
| `verify_data.py` | 995/995 | **995/995 files, 56,279/56,279 B, 100.00 %** |
| app FLASH | 956,480 B / 97.35 % | **956,480 B / 97.35 % — Δ 0** |
| flash headroom | 26,048 B | **26,048 B — Δ 0** |
| app RAM | 253,765 B | **253,765 B — Δ 0** |
| every allocatable section size | unchanged | **`size -A` diff is EMPTY except `.debug_info/.debug_abbrev/.debug_line/.debug_str/.debug_loc` and the total** |
| **`app_update.bin` payload** | — | **`cmp -n 957072` exits 0 — 957,072 of 957,328 bytes IDENTICAL** (the 256-byte tail is the randomised RSA-PSS signature TLV) |
| per-object byte comparison (debug stripped) | — | **2,837 uniquely matched, 2,835 identical, 2 differ, 215 ambiguous** |

### 7.1 The two residual objects, explained to the byte

* **`uname.c.obj`** — the stock SDK unit already recorded as differing
  build-to-build (`prerefactor_progress.md` §0/§4, Stage 02 §4): it embeds a
  build clock. `--gc-sections` removes it from the image, which is why the
  payload is nevertheless identical.
* **`ui_new_message_task.c.obj`** — a GCC-internal switch table renumbered.
  `size -A` diff: `.rodata.CSWTCH.12` → `.rodata.CSWTCH.14`, **4 bytes in
  both**; `objdump -dr` diff is exactly one line, the relocation's section
  *name*: `17c: R_ARM_ABS32 .rodata.CSWTCH.12` → `… .CSWTCH.14`. Contents,
  instructions and relocation type are identical, the section is merged by
  name-independent placement, and the linked payload is byte-identical.
  Gate A on this file: **PASS** (`4a6d6798ec3c67e1:392` both sides).

### 7.2 The gate I CANNOT run, stated as outstanding

**The four framebuffers were NOT captured and are NOT claimed.**
`navigation p1_boot` / `navigation p2_render` / `dashboard p1_boot` /
`dashboard p2_render`, the `twim1`/`twim2`/`spim_a`/`saadc` streams,
`JBD_FRAMECOUNTER_P2`, `DISPLAY_ON`, `ESB_SYNC`, `SCREEN_ID`, `RADIO_TX` — none
of them was re-measured. Renode belongs to a concurrent agent and I did not
touch it, `~/Projects/armemul`, or any `.resc`.

What can be said, and only this: **the linked flash payload is byte-identical to
the payload whose framebuffers were last captured** (iteration 43's
`g1-i43b-app`, which is what HEAD builds), so re-running the oracle must
reproduce them bit for bit unless the emulator is nondeterministic. That is an
inference from byte-equality, not a measurement, and it is recorded as one.

---

## 8. The four-way split, measured

`td3/split.py`, patched for calibration bugs 6 and 7. *FIXED* is measured by
re-running Stage 03's own agreement test, not by counting edits.

| class | entries | FIXED | CONFIRMED REAL | FALSE ALARM | UNSETTLED |
|---|---:|---:|---:|---:|---:|
| `arity_differs` | 163 | 0 | 68 | 0 | 95 |
| `declaration_disagrees_with_definition` | 296 | 2 | 17 | 90 | 187 |
| `parameter_type_differs` | 59 | 4 | 9 | 37 | 9 |
| `return_type_differs` | 131 | 8 | 16 | 40 | 67 |
| `reconstructed_declaration_shadows_an_sdk_symbol` | 299 | (see below) | 44 | 10 | 25 |
| `reconstructed_declaration_shadows_an_sdk_macro` | 1 | 1 | 0 | 0 | 0 |
| **total** | **949** | **14 + 37** | **154** | **177** | **383** |

* **FIXED = 14 on the four spelling classes** (Stage 03's criterion), **plus 37
  shadow entries** on the SDK-conflict criterion of §5.4. The "220 FIXED" the
  raw script prints for the shadow class is the vacuous-agreement artifact of
  §0.1 and is **not** claimed.
* **CONFIRMED REAL = 154** — the image proves a defect: a call site fills fewer
  core-register slots than the callee's prologue reads (slot-aware, thunk- and
  idiom-corrected), or a definition declares fewer slots than the image proves.
* **FALSE ALARM = 177 (18.7 %)** — every remaining spelling maps to the same
  AAPCS signature, so no call site can emit wrong code. Prior passes ran 20–26 %.
  Canonicalising a false alarm is the safe repair; changing the *code* to
  "fix" one injects a defect.
* **UNSETTLED = 383** — ABI-real, not settled here.

### 8.1 Short definitions — the count moved again, and against my interest

Slot-aware, the definitions declaring fewer slots than the image proves are
read are **2**: `main_dispatch_thread_tick` (7 vs 8) and `slave_display_thread`.
Pass 2's other survivor, `z_impl_k_timer_start`, no longer trips the test
because its definition now spells the `k_timeout_t` parameter as a 64-bit type,
which fills the two slots the automated test was missing.

`slave_display_thread` is the one pass 2 **refuted on other grounds**: it is a
`k_thread_entry_t`, the kernel passes exactly three arguments in r0–r2 and r3 is
undefined at entry, so "argument 4" cannot exist. The automated test cannot see
that and still flags it. Pass 2's refutation stands; **the honest count of
short definitions is 1**, `main_dispatch_thread_tick`.

---

## 9. Stage 07's dead functions — asked, and the first answer was wrong

The brief asks whether any of the 120 provably-dead functions are dead because a
caller lost an argument or a whole call. The image answers directly: count the
shipped `bl` sites targeting each function, and count the calls in our tree.

```
image functions with at least one shipped call site       1,897
our tree calls them not at all                              216   (465 sites)
our tree calls them fewer times than the image              263
  ... of the 216, those whose shipped CALLERS are files we
      reconstructed (i.e. the loss would be ours)             64   (115 sites)
```

**64 was wrong.** Two confounders, both found by opening the files rather than
believing the sweep:

* **per-file aliases.** `display_dispatch_thread.c` calls `FUN_00026850` under
  its own local name `display_mutex_unlock`; the catalogue name is
  `ui_state_mutex_unlock`. Same address, different spelling.
* **calls inside macro bodies.** `run_main_dispatch_thread.c:70` calls
  `main_dispatch_thread_tick` from inside a `#define`, and the call scanner
  blanks preprocessor lines, so it sees none of them.

Recounted with each file's own `NAME <= FUN_xxxxxxxx @ 0xADDR` provenance block
resolving aliases by address, and scanning the raw body rather than the
preprocessor-blanked text:

```
lost callees BEFORE alias/macro-aware recount   64   (115 sites)
lost callees AFTER                              12   ( 29 sites)
```

The 12: `CC_PalMutexCreate` (10), `nrfx_qspi_init` (3), `ver_str` (2),
`FUN_00059afc` (2), `nrfx_qspi_cinstr_xfer` (2), `nrfx_qspi_mem_busy_check` (2),
`nrfx_qspi_erase` (2), `FUN_0007def6` (2), `SettingStoreHandler` (1),
`audioStreamFileManagerHandler` (1), `close` (1), `nrfx_qspi_chip_erase` (1).
Six of the twelve are `nrfx_qspi_*`, where the build uses the SDK's own driver
rather than ours, so the "missing" call is in an SDK object. **This is a lead,
not a defect list**, and it is recorded as one: nothing was changed on its
account.

---

## 10. Footprint — every file this pass wrote

| tree | files changed | how |
|---|---:|---|
| `recon/symbolized/app` | **235** | the gated tree; every one passes GATE A |
| `recon/named` | 222 | mirrored, verbatim, anchored |
| `recon/readable_sources/app/g1` | 115 | mirrored |
| `recon/readable_sources/app/library` | 59 | mirrored |
| `recon/app/src` | 14 | mirrored via the catalogue's `FUN_%08x` name |
| `recon/verified/src` | 12 | mirrored |
| `recon/app/src_sym` | 7 | mirrored |
| `recon/verified/src_sym` | 7 | mirrored |
| `recon/analysis/type_disagreement_repair_3.md` | this file | new |

Mirroring is **verbatim text substitution into the corresponding file only**
(same basename, or the `FUN_%08x` the catalogue gives), and the pre-edit text
must occur **exactly once**: 291 line hunks, 273+131+70+15+12+7+7 = 515 applied,
**627 not found and 4 ambiguous, all skipped and counted, none guessed**.

### 10.1 A hazard checked and cleared

`recon/app/src` is not purely documentation — **2 of its files are compiled**
(`FUN_0007f772.c`, `FUN_0007f79e.c`, per `compile_commands.json`). Neither is in
the 14 files the mirror touched, so the build is unaffected by the mirroring.
Checked explicitly rather than assumed, because the mirror ran *after* the final
gated build.

**Not written:** `recon/refactor/` (`git status --porcelain recon/refactor` = **0
lines**), `recon/net/**`, `recon/symbolized/net`, `recon/headers`,
`recon/symbols`, `recon/application`, `recon/board`, `recon/generated`,
`recon/wiring`, any linker script, `tools/`, `~/Projects/armemul`, any `.resc`.
**The net image is FROZEN by construction at 225,581 B**: no net source, header,
symbol or build input was touched and no net build was run.

---

## 11. What I did NOT close, and why

1. **898 of 949 ledger entries remain open** (14 closed on Stage 03's criterion,
   37 shadow entries on the SDK-conflict criterion). 383 are ABI-real and
   unsettled, 177 are false alarms that still need canonicalising for the merge
   but cannot be canonicalised without moving allocatable bytes, 154 are
   confirmed-real defects with per-site image evidence and no free repair.

2. **All 51 constant-argument sites are quarantined, and this is now MEASURED
   rather than argued** (§3): the class costs **+66 B** of `.text`, and no
   member of it is free. The 9 sites in 8 files that are size-neutral at
   function granularity (§3.1) are the recommended first batch for a pass that
   owns Renode — one seeded capture on both stimuli decides all nine.

3. **The other 294 image-proven missing-argument sites** (345 slot-aware, minus
   the 51 constant-proven) are untouched: their value would have to be invented.

4. **`main_dispatch_thread_tick` (7 slots vs 8)** is identified, not repaired.

5. **The 303 invented-argument sites** are untouched. Pass 1's R8 triage (287
   inert / 21 volatile / 0 call) stands; deleting ~287 argument setups moves
   `.text` in the shrinking direction by far more than the +16 B that already
   broke the dashboard.

6. **188 shadow files could not adopt the SDK prototype** because the SDK's
   parameter types are not in scope (`struct _reent`, `FILE`, `k_timeout_t`).
   Adding the header is a different repair — GCC treats several of these
   symbols as builtins once the header is visible, which can change codegen —
   and it needs its own gated pass.

7. **27 of the 110 shadowed symbols have no recoverable SDK prototype**: they
   are `static inline`s or macros, for which GCC reports a *definition*. The
   repair there is to delete our declaration and include the header, not to
   respell it.

8. **The 29 remaining incompatible typedefs** in `HAZARDS.json` are
   function-pointer typedefs with genuinely different per-file meanings; only
   the `u8`/`i8` collision (the one that was silent and wrong) is closed.

9. **The 12 lost-call leads** (§9) were investigated to the point of a
   defensible number and no further; nothing was changed on their account.

10. **`cfg_verify` was not run and is not cited anywhere in this report.** It is
    structurally blind to this defect class — it seeds r0..r3 regardless of
    declared arity — so a green sweep would be evidence of nothing. The
    per-object Gate A and the byte-identical `app_update.bin` payload are the
    evidence. **No new `cfg_verify` fixture was added**, so the "does it fail on
    a real mutation" obligation does not arise for it; the obligation *did*
    arise for the two new probes in this pass, and both were controlled (§2.1,
    §5.1).

11. **The framebuffers and every emulator-derived hold criterion are
    OUTSTANDING, not claimed** (§7.2).

12. **Nothing was committed.** The tree is left dirty.

---

## 12. Reproducing

```sh
cd /Users/freedomcoder/Projects/G1disasm2
V="PYTHONSAFEPATH=1 .venv/bin/python"
T=<scratchpad>/td3          # td/ and td2/ are the earlier passes' toolkits, reused

# baseline
recon/application/build_cohesive.sh app /private/tmp/g1-td3-base

# oracles (4 s over the whole app image) -- identical to pass 2's records
$V $T/sweep.py app $T/image_app.json      # 2,377 functions, 13,713 sites
$V $T/scan.py recon/symbolized/app $T/symb_app.json
$V $T/table.py ; $V $T/thunks.py app $T/thunks.json $T/image_app.json   # 94, 3

# calibration bugs 6 and 7
$V $T/slotaudit.py hits ; $V $T/slotaudit.py rows ; $V $T/shortcalls.py

# the per-object screen and its negative control
$V $T/screen.py recon/symbolized/app/<file>.c
$V $T/gate.py   <files.json> <gate.json>          # GATE A / GATE B

# track 1 -- constant arguments (all quarantined)
$V $T/applyconst.py ; $V $T/measure_quarantine.py ; $V $T/nmcheck.py ; $V $T/textcmp.py

# track 3 -- the shadow class
$V $T/shadowprobe.py ; $V $T/sdktypes.py ; $V $T/applysdk.py
$V $T/shadowremeasure.py

# track 4 -- canonicalisation
CANON3_ALL=1 $V $T/canon3.py plan $T/plan1.json ; $V $T/canon3.py apply $T/plan1.json

# mirrors, then the decisive measurements
$V $T/mirror.py
recon/application/build_cohesive.sh app /private/tmp/g1-td3-final
cmp -n 957072 /private/tmp/g1-td3-{base,final}/zephyr/app_update.bin
$V /tmp/objcmp.py /private/tmp/g1-td3-base /private/tmp/g1-td3-final
$V tools/verify_data.py
$V recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
$V recon/emulator/scripts/check_ram_pin_collisions.py /private/tmp/g1-td3-final/zephyr/zephyr.elf
$V recon/emulator/scripts/check_ram_pin_collisions.py /private/tmp/g1-i30e-net/zephyr/zephyr.elf
$V $T/remeasure.py        # Stage 03's agreement test:  721 -> 714
$V $T/split.py            # the four-way split
$V $T/lostcalls.py        # the dead-function lead
```

**Nothing was committed. The tree is left dirty.**

### 12.1 Final consistency check

`ninja -n` in `/private/tmp/g1-td3-final` after the mirroring reports **0
pending object rebuilds** — confirming directly that none of the 436 mirrored
files in `recon/named`, `recon/readable_sources`, `recon/app/src*` or
`recon/verified/src*` is a build input, so the gated build above is the build
this tree produces.
