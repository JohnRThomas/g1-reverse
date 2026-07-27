# Latent defect harvest — acting on the Stage 02 bucket-(b) findings

**Status: IN PROGRESS.** Written incrementally as the work runs. Nothing committed.

Input documents:

* `recon/analysis/staged_refactor_stage02.md` (the harvest report)
* `recon/refactor/stage_02_block_dedupe/DEFECTS.json` — 192 entries
* `recon/refactor/stage_99_defect_probe/` — the diagnostic compile (275 errors / 44 TUs)

The compiler said WHERE the reconstruction disagrees with itself. It cannot say
which side is right. **The arbiter is the shipped image**, and every claim below
is a read of `app_update.bin` / `netcore_image.bin`.

---

## 0. Method — how a call site is settled

`callsite.py` (scratchpad) disassembles the enclosing function with capstone
(Thumb, M-class) and, for each `bl` whose target is a logging entry point, walks
**backwards over the CFG** — linear fallthrough plus every branch that targets
the block — recording the last writer of r0..r3 and every store to `[sp,#N]`,
stopping each path at a preceding `bl` (an AAPCS clobber boundary).

The entry points, from `recon/headers/g1_log.h` (itself read off the shipped
prologues, G7-B2):

| symbol | VA | sink |
|---|---|---|
| `debug_print` | `0x00019c70` | ring buffer (`vsnprintf_impl`) |
| `log_message` / `DEBUG_PRINT` | `0x0007dda4` | console (`vprintf`) |
| `printk` (app) | `0x0007e2fa` | console |
| `printk` (net) | `0x01039722` | net console |

All three take **exactly one fixed argument in r0, then `...`**.

### 0.1 The first site, in full — why the harvest is real

`SendDashboardLockInfoToApp` = `FUN_00025e2c` @ `0x25e2c`. The reconstruction
(`recon/symbolized/app/SendDashboardLockInfoToApp.c:28-32`) reads

```c
if (*(volatile int *)&g_log_use_alt_sink == 0) {
    log_message("%s(): send dashboard lock info to app ,status = %d\n \n",
                "SendDashboardLockInfoToApp", 1);
} else {
    debug_print();
}
```

The shipped instructions:

```
00025e74  ldr   r3, [pc, #0x48]     ; &g_log_use_alt_sink
00025e76  movs  r2, #1              ; <-- ARG 3
00025e78  ldr   r3, [r3]            ; gate value
00025e7a  ldr   r1, [pc, #0x48]     ; <-- ARG 2  "SendDashboardLockInfoToApp"
00025e7c  ldr   r0, [pc, #0x48]     ; <-- ARG 1  format
00025e7e  cbz   r3, #0x25ea8        ; gate == 0 -> log_message
00025e80  bl    #0x19c70            ; debug_print(r0, r1, r2)
...
00025ea8  bl    #0x7dda4            ; log_message(r0, r1, r2)   <- SAME r0,r1,r2
00025eac  b     #0x25e84
```

**The argument setup happens ONCE, before the gate branch, and both `bl` sites
consume it.** The `if` half of the reconstruction is right; the `else` half
dropped all three. This is a confirmed real defect, and it also establishes the
structural fact that decides the whole `log_route_branch_disagreement` class:
in a gate pair the two calls **cannot** take different argument lists, because
there is only one argument setup.

(Note the gate sense is also confirmed: `cbz r3` — gate `== 0` goes to
`log_message`, non-zero falls through to `debug_print` — exactly what the
reconstruction spells.)

### 0.2 The arity oracle — the format string, not the register scan

`r0` is a pointer into `.rodata`. Resolving the `ldr r0,[pc,#imm]` literal and
reading the C string gives the **exact** argument count, because a variadic
`printf`-family sink consumes exactly what its conversions name. `fmt_words()`
counts 32-bit argument words with the hard-float variadic rules (a `double`
consumes two words, 8-byte aligned; `%ll` likewise). **Shipped arity = 1 +
`fmt_words(format)`.**

This is strictly better than counting `r0..r3` writes, which is noisy: at
`0x25e78` above, `r3` is written by the *gate load* `ldr r3,[r3]`, not by
argument setup. The format string is unambiguous.

Measured over the whole app image:

```
functions containing a logging bl : 566
logging call sites                : 2470
format string resolved            : 2420   (98.0 %)
arity histogram (1 = format only) :
   1:244  2:896  3:535  4:624  5:57  6:25  7:9  8:11  9:9
  10:2   11:2   13:2   14:2  15:2   unresolved:50
```

(`g1_log.h` records 2,526 `bl` sites; this pass sees 2,470 because it only
scans functions present in `recon/catalogs/app_funcs.json.gz` and only `bl`
with an immediate target.)

---

## 1. The structural fact that decides the whole 143-site class

**In a log gate pair the two branches CANNOT take different arguments, because
the shipped code sets the arguments up ONCE, before the gate branch.**

This is not an inference from one example. Detecting gate pairs directly in the
image — two `bl` sites in one function, with *different* targets, whose backward
CFG walks resolve to the **same** `r0`-defining instruction — gives:

```
gate pairs found in app_update.bin                        : 618
  identical arity AND identical r0..r3 definition set     : 617
  differing                                               :   1
```

The single "differing" pair is `FUN_0003b824` @ `0x3bac8` / `0x3bb68`, and it is
**a false alarm in my own tool, not in the image**: the second site's backward
walk crosses `0x3bb50..0x3bb66`, which is a **literal pool** that capstone
decodes as instructions (`str r6,[sp,#0x2b0]` / `movs r2,r1` alternating — the
low and high halfwords of pool words). The bogus `movs r2, r1` is what
contributed the extra `r2`. Both sites have arity 2 from the format string and
the same `r0`/`r1` setup. **Corrected: 618 / 618.**

Consequence: for a `log_route_branch_disagreement`, the fix is not a judgement
call about which half "looks better". The two halves must be made **textually
identical**, and the arity oracle says which of the two is the surviving one.

### 1.1 Corrections to the Stage 02 population, measured

Stage 02's gate-pair detector required the **braced** form
`if (...) { A(...); } else { B(...); }`. A large part of the live corpus is
**brace-less** (`init_watchdog.c`: `if (*g50==0) log_message(f,n); else debug_print();`).
Re-scanning with a detector that keys on the text *between* two consecutive log
calls (`; [}] else [{]`, any whitespace) and then filtering to **cross-sink**
pairs (one call to a console sink, one to the ring sink — the structural
signature of a log route) gives, on `recon/symbolized/app`:

| | Stage 02 | this pass |
|---|---:|---:|
| log-gate if/else pairs | 409 | **854** |
| of which the two branches disagree | 143 | **318** |
| zero-argument log call sites (source) | 230 | **244** |

The cross-sink filter matters: an unfiltered "consecutive calls with `else`
between them" scan also catches **genuine business logic**, e.g.
`discovery_completed_cb_gatt.c:34` is `if (attr_cnt < 2) log_message("GATT
Service could not be found…"); else { log_message("…succeeded"); … }` — two
*different* messages on a real condition, both to the **same** sink. Four such
same-sink pairs exist and are correctly excluded. **Stage 02's 143 was an
undercount of the same real class, not a different class.**

---

## 2. A THIRD defect class the compiler could not flag: INVENTED arguments

The arity oracle applied to every source site (not just the disagreeing ones)
shows the dropped-argument class has a **larger mirror image**. On
`recon/symbolized/app`, 2,885 sites:

```
MATCH  (source arity == shipped arity)      1328
too MANY  (+1:148 +2:63 +3:68 +4:19 +5:4 +6:1)   303   <- INVENTED arguments
too FEW   (-1:43 -2:2 -3:4 -4:1)                  50   <- dropped, non-zero
zero-argument                                    244   <- dropped, total
unresolved (format not a literal in the source)  960
```

The mechanism is visible at `display_reflash_handler` = `FUN_00048e28`:

```
00048e54  ldr  r1, [pc, #0x174]     ; "display_reflash_handler"
00048e56  ldr  r3, [r6]             ; <-- THE GATE VALUE, not an argument
00048e58  ldr  r0, [pc, #0x174]     ; "%s(): !!!!!!…!!\n"   (1 conversion)
00048e5c  bl   #0x19c70             ; debug_print(r0, r1)     -- arity 2
```

`r2` is never written; `r3` holds the log-sink gate. The reconstruction
(`display_reflash_handler.c:41-45`) writes **four** arguments in each branch:

```c
log_message(fmt, "display_reflash_handler", payload, 0);
debug_print (fmt, "display_reflash_handler", payload, *alternate_log);
```

`payload` and the trailing `0` / `*alternate_log` are **decompiler artifacts** —
r2 and r3 were live scratch at the call, and `*alternate_log` is literally the
gate load being read as a fourth argument. Ghidra had no prototype, so it
emitted every live caller-saved register as an argument.

This class was invisible to Stage 02 because a call with *too many* arguments
compiles cleanly against `void f(uintptr_t, ...)` — only *too few* is an error.
It is invisible to the parity harness for the same reason as the dropped kind.
**It is reported here but NOT blanket-corrected** — see §6.

### 2.1 Validating the arity oracle against the register evidence

Over all 2,299 sites whose format-derived arity is ≤ 4 (so the whole argument
list is in registers):

```
all format-required argument registers are set : 2296  (99.87 %)
   with 0 extra registers written : 1009
   with 1 extra (the gate load in r3) : 1135
   with 2 extra : 142      with 3 extra : 10
missing an argument register :  3
```

The three "missing" are `FUN_00018300`, `FUN_00018894`, `FUN_000188b0` — small
functions that receive the value **already in r1/r2 from their own caller** and
only load r0 before the `bl`. The backward walk starts at the function entry
and cannot see an incoming register argument, so these are **tool false alarms,
not defects**.

---

## 3. `assert_post_action` — Stage 02's hypothesis is REFUTED

Stage 02 §6 item 4 read `FUN_0007e2ec` @ `0x7e2ec`:

```
0007e2ec  eors   r0, r0          ; r0 = 0
0007e2ee  msr    basepri, r0
0007e2f2  mov.w  r0, #4          ; K_ERR_KERNEL_PANIC
0007e2f6  svc    #2
0007e2f8  bx     lr
```

and inferred that because the body *zeroes r0 before reading anything*, "the
185 live two-argument call sites [may be] the *invented*-argument mirror of §5".
It correctly called this "a strong hint, not evidence" and deferred it pending a
read of the `bl` sites. **That read now exists, and the hint was wrong.**

Every single shipped call site sets up exactly r0 and r1:

```
assert_post_action app  @ 0x0007e2ec : 253 sites, ALL regs=[0,1]
assert_post_action net  @ 0x01039bb0 : 100 sites, ALL regs=[0,1]
assert_print/report net @ 0x01039bbe : 202 sites, regs=[0,1,2] x119, [0,1,2,3] x83
```

and r0/r1 resolve to a **file path and a line number**:

```
FUN_00017688 @0x176c0  r0 -> "WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h"  r1 = #974
FUN_00026418 @0x264fe  r0 -> "../src/spim_spis/spim.c"                           r1 = #104
```

So the caller-side ABI is `assert_post_action(const char *file, unsigned line)`
— exactly what the 185 two-argument reconstructions already spell. The callee
happens to discard both, which is why the body opens with `eors r0,r0`; that is
a property of the *implementation*, not of the call contract.

**Verdict: FALSE ALARM. 353 app+net call sites confirmed correct as written.
Do NOT change them, and do NOT write a `void assert_post_action(void)`
prototype** — that would delete two real argument-setup instructions per site.

*Caveat recorded:* net literal-pool words are stored in the **runtime** space
(base `0x01008800`) while `net_extract` indexes the **analysis** space (base
`0x01008000`). Reading a stored net pointer without subtracting the 0x800 delta
returns a plausible-looking but wrong string — this pass observed exactly that
(`'purious interrupt (IRQ '`). The net r0 strings above are therefore NOT
claimed; only the **register counts**, which need no address translation, are.

---

## 4. The 4 zero-argument assert expansions — fully recovered

All four are Zephyr's `__ASSERT` expansion, recovered literal by literal:

| site | reconstruction | shipped |
|---|---|---|
| `app_event_alloc.c:25` `FUN_0004f564` | `printk(); assert_post_action();` | `printk("ASSERTION FAIL [%s] @ %s:%d\n", "0", "WEST_TOPDIR/nrf/subsys/app_event_manager/app_event_manager.c", 123); assert_post_action("…app_event_manager.c", 123);` |
| `conn_tx_send_to_driver.c:106` `FUN_000560cc` | same | cond `"*pending_no_cb > 0"`, file `"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c"`, line 627 |
| `safe_memmove_or_die.c:24` `FUN_00055ba0` | `printk(); printk(); assert_post_action();` | cond `"((psrc < pdst && (psrc + length) <= pdst) \|\| (psrc > pdst && (pdst + length) <= psrc))"`, file `"WEST_TOPDIR/zephyr/include/zephyr/sys/byteorder.h"`, line 533, **plus** a second `printk("\tSource and destination buffers must not overlap\n")` |
| `safe_memmove_or_die.c:40` | same | the same assertion, second occurrence |

The shipped shape is therefore

```c
printk("ASSERTION FAIL [%s] @ %s:%d\n", #cond, __FILE__, __LINE__);
printk("\t" msg "\n");                     /* only when __ASSERT carries a message */
assert_post_action(__FILE__, __LINE__);
```

**Verdict: 4/4 CONFIRMED REAL DEFECTS**, and every argument is now known.

---

## 5. What was changed, and the four-way split per class

All transforms are scripted (scratchpad `fix_pairs.py`, `fix_decls.py`,
`fix_asserts.py`, `fix_imu.py`). **No file was hand-edited at any scale.**

### 5.1 The four-way split the brief asked for

| class | compiler flagged | shipped disassembly CONFIRMED a real defect | FALSE ALARM (reconstruction was right) | could NOT settle |
|---|---:|---:|---:|---:|
| `log_route_branch_disagreement` | 143 (Stage 02) — **re-measured live: 318** | **250** fixed | **4** (same-sink pairs: genuine business logic, not a log route) | **68** |
| `zero_argument_call_to_variadic_log_entry_point` | 45 files / 183 sites; 273 TU call sites | **244 source sites → 0 remaining** | 0 | **36** source sites in `key_event_thread.c` (72 TU call sites) — **contained, see §6.1** |
| `zero_argument_assert_expansion` | 4 | **4** | 0 | 0 |
| `assert_post_action` prototype (Stage 02 §6 item 4, deferred) | 160 decls / 58 spellings; 185 call sites suspected of *inventing* arguments | 0 | **353** call sites (253 app + 100 net) — **the suspicion was wrong**, see §3 | 0 |
| **INVENTED arguments** (new, §2) | 0 — a compiler cannot see too *many* arguments | **303** identified with per-site evidence | — | **303 not corrected** (deliberate, §6.2) |

### 5.2 Edits applied, by transform

| transform | what it does | edits | trees |
|---|---|---:|---:|
| `fix_pairs.py` | restore the argument list a gate branch dropped, copying the surviving branch verbatim | **1,345** | 7 |
| `fix_decls.py` | normalise every local declaration onto `void NAME(unsigned long, ...)` | **2,667** | 7 |
| `fix_asserts.py` | the four `__ASSERT` expansions, every literal read off the image | **26** | 7 |
| `fix_imu.py` | the six `imu_fusion_thread` pairs with no donor branch | **60** (12 sites × 5 trees) | 5 |
| `erase_audio_buffer` | the two pairs with no donor branch | **28** | 7 |
| `key_event_thread` containment | explicit, greppable, NOT a fix (§6.1) | 5 | 5 |
| first-argument string-literal wrap | `"fmt"` → `((unsigned long)"fmt")`, corpus convention | **810** | 3 |
| first-argument `(void*)` cast | `(void*)0x…` → `(unsigned long)0x…` | **174** | 7 |

`fix_decls` is what makes both stage-99 `conflicting types` errors go away:
`ble_process_put_common.h`'s `extern int log_message();` /
`extern int debug_print();` are now the authoritative variadic prototype, as are
the same K&R declarations in the five `ble_process_put_ops_*.inc` fragments.

### 5.3 Residual population, measured

`recon/{app/src, verified/src, symbolized/app}` — the three complete app trees,
and `symbolized/app` is the one the cohesive build compiles:

| | before | after |
|---|---:|---:|
| zero-argument log call sites | **244** | **0** |
| log-sink gate pairs | 858 | 899 |
| pairs whose branches still disagree | 318 | **68** |
| pairs with BOTH halves empty | 9 | **0** |
| solo zero-argument calls | 12 | **0** |
| **net core, every tree** | **0** | **0** |

---

## 6. What I did NOT close, and why

### 6.1 `key_event_thread.c` — 36 sites, CONTAINED but NOT FIXED

`key_event_thread` (`FUN_0002955c` @ `0x2955c`) defines

```c
#define LOG() do { if (SINK==0) log_message(); else debug_print(); } while (0)
```

and uses it **36 times** — 72 of the compiler's 275 errors, the single worst
file. Unlike every other site in this pass, **both halves are empty**, so there
is no donor branch: each of the 36 is a distinct log statement with its own
format string and arguments, and recovering them means matching 36 source sites
to the shipped `bl`/`b.w` sites in a 2,702-byte function whose source order does
**not** follow address order (proved in `imu_fusion_thread`, §6.4 of
`fix_imu.py`'s docstring). A wrong match writes a **wrong format string**, which
is worse than leaving the site empty.

So it is contained, explicitly and greppably: the authoritative variadic
prototypes stay correct, and only this file's own placeholder calls go through

```c
extern void g1_log_message_argless(void) __asm__("log_message");
extern void g1_debug_print_argless(void) __asm__("debug_print");
```

with a block comment naming this report. The emitted object is **byte-identical
to the baseline** (§7), so the containment costs nothing and changes nothing.

### 6.2 The 303 INVENTED-argument sites — identified, NOT corrected

Deliberate. Correcting them means *deleting* arguments, and three things make
that a separate pass:

1. it would move flash in the opposite direction and make this pass's growth
   measurement uninterpretable;
2. some invented arguments are **volatile reads** (`*alternate_log` at
   `display_reflash_handler.c:45` is literally the log-gate load). Deleting a
   volatile read is an R8 change to the number of bus transactions, and needs
   its own per-site argument, not a blanket rule;
3. the format-derived arity is what the **callee consumes**; a caller is allowed
   to pass more. §2.1 shows the register evidence agrees with the format oracle
   for 2,296/2,299 sites, but "agrees" there means *the required registers are
   set*, which does not by itself prove the extra ones are not deliberate.

The evidence is complete and machine-readable in the scratchpad
(`evidence_app.json`: 2,470 sites, format string, arity, per-register defining
instruction), so the next pass starts with the measurement already done.

### 6.3 68 gate pairs still disagreeing

| reason | pairs (per full tree) |
|---|---:|
| arity unresolvable — the format is a **variable**, not a literal (`log_message(uVar6, …)`), so neither the provenance VA nor the string is available, and neither branch's list is a prefix of the other's | ~49 |
| neither branch's count equals the format-derived arity (the invented-argument class, §6.2, showing up inside a pair) | ~19 |

Both need per-site disassembly matching within the enclosing function, the same
work `key_event_thread` needs.

### 6.4 The `_sym` mirrors

`recon/app/src_sym` and `recon/verified/src_sym` (1,059 files each) still carry
**53 zero-argument sites in ~25 files**. These trees are **not in the build**
(`grep src_sym recon/generated/app_retained_sources.cmake` → nothing) and are
partial, older mirrors; their copies of the affected functions differ from the
canonical ones, so `fix_pairs` found no donor. Listed in the scratchpad
(`sites_final.json`). `recon/readable_sources/app/g1` has 2 left, same cause.

### 6.5 Not run / not touched

* **Renode was NOT run** — another agent owns it, per the brief.
* **The net core was not modified at all.** Measured, not assumed:
  `git status --porcelain | grep -E 'recon/(net|symbolized/net|readable_sources/net)/'`
  returns **nothing**, and no shared input (`recon/headers`, `recon/symbols`,
  `recon/application`, `recon/board`, `recon/generated`) changed either. The net
  freeze at 225,581 B is intact **by construction**; no net build was needed and
  none was run.
* **`recon/refactor/` was not modified.** One file inside
  `stage_99_defect_probe/tree/` was touched by a recursive glob and was
  **reverted to its zero-argument state**; `git status --porcelain recon/refactor/`
  is clean.
* Four JSON files (`recon/viewer_sweep/{reference_semantics,string_assets_report}.json`,
  `recon/ownership/literal_inline_plan.json`, `recon/viewer_assets/catalog.json`)
  were corrupted by an over-broad escape fix and **reverted with `git checkout`**;
  confirmed clean.
* **The concurrent parity agent's in-flight files were not disturbed.** Four of
  the nine files already dirty at the start of this pass
  (`recon/{app,verified}/src/FUN_000622a0.c`,
  `recon/{symbolized/app,named,readable_sources/app/g1}/lsm6dso_init_chip.c`)
  received exactly one additional change each, and only in two of them: the
  declaration normalisation `extern void DEBUG_PRINT(int fmt, ...);` →
  `extern void DEBUG_PRINT(unsigned long, ...);`. That is ABI-identical
  (`int` and `unsigned long` are both 32-bit in r0 here) and touches no line of
  their actual work.
* `cfg_verify` was not re-swept over the corpus. It is **structurally blind to
  this entire defect class** (that is the premise of the whole harvest), so a
  green sweep would have proved nothing about these changes. The per-object byte
  comparison in §7 is the stronger evidence and is what was run instead.

---

## 7. Gates — measured

Baseline is `/private/tmp/g1-i40d-app`, the **live-tree** iteration-40 build
(07-27 03:41, `zephyr.bin` = 955,048 B — the figure the brief quotes).

> Correction to my own earlier working assumption: I first compared against
> `/private/tmp/g1-s1-app`. That is **not** a valid baseline — it is built from
> the Stage 01 *transform tree*, whose literal-inlining rewrites move string
> references, and it showed 40 differing objects that had nothing to do with
> this work. Against the correct live-tree baseline the number is 1.

| gate | baseline | **this pass** |
|---|---|---|
| app build | exit 0 | **exit 0, 0 errors** |
| `nm -u` undefined | 0 | **0** |
| duplicate global definitions | 0 | **0** |
| app FLASH | 955,048 B / 97.20 % | **956,368 B / 97.34 % — +1,320 B** |
| app `.text` | 950,080 | **951,412 — +1,332 B** |
| app `.data` | 4,951 | **4,951 — Δ 0** |
| app `.bss` | 249,251 | **249,251 — Δ 0** |
| app RAM | 253,765 B | **253,765 B — Δ 0** |
| **flash headroom** | 27,480 B | **26,160 B** |
| `verify_data.py` | 995/995 | **995 / 995 byte-exact, 56,279 / 56,279 bytes (100.00 %)** |
| `check_thread_create_stack_args.py --trials 120` | 10/10 | **10 / 10 PASS** |
| `check_ram_pin_collisions.py` (app) | — | **627 bound OK, 0 escaping, 0 unknown inside a live object** |
| net FLASH | 225,581 B | **UNCHANGED — zero net inputs modified (§6.5)** |
| compiler warnings (app) | — | 2,005 (see below) |
| **per-object byte comparison** | — | **2,766 / 2,837 byte-identical; 71 differ** |
| **four framebuffers** | — | **NOT RUN** |

### 7.1 The per-object result — this is the containment proof

Objects matched uniquely by basename between the two builds, compared after
`--strip-debug --remove-section=.comment`:

```
uniquely matched : 2837
byte-identical   : 2766
differing        :   71
   of which traceable to a source this pass edited : 70
   not traceable                                   :  1  -> uname.c.obj
```

`uname.c.obj` is one of the two stock SDK units already recorded in
`prerefactor_progress.md` §0/§4 and Stage 02 §4 as **differing build-to-build
regardless of any change**.

Four sources that this pass edited produced a **byte-identical** object:
`key_event_thread` (the containment of §6.1 — codegen-neutral, as intended),
`img_mgmt_upload_inspect`, `switch_to_dfu_mode`, `ui_DashBoard_task` (declaration
normalisation only).

**So every byte that moved is inside one of the 70 translation units whose log or
assert argument list was corrected. Nothing else in the image moved.**

Two independent cross-checks that the *cosmetic* parts of this pass are
codegen-neutral: the 810 string-literal wraps and the 174 `(void*)` cast
rewrites both left `.text` at exactly 951,412 B across rebuilds.

### 7.2 The framebuffer gate — NOT RUN, and what can honestly be said instead

**I did not run the four-framebuffer comparison. Renode is owned by another
agent and the brief forbids running it. I make no claim about it.**

What *is* measured, and what it does and does not support:

* the change is confined to **70 translation units** (§7.1), all of them log or
  assert argument lists;
* `.data`, `.bss` and RAM moved **0 bytes**, and `check_ram_pin_collisions`
  reports 0 escaping and 0 unknown-inside-a-live-object, so **no RAM object moved
  and no probe address from iteration 38 is invalidated**;
* **`.text` moved +1,332 B, so code addresses DID shift.** Any oracle comparison
  that pins a `.text` address must be re-derived. This is the honest caveat and
  it is the reason the framebuffer gate cannot be inferred rather than run.

On whether the corrected code *executes* in the traced window: every restored
argument list sits behind a two-level gate — an outer `if (g_log_level > N)` and
an inner `if (g_log_use_alt_sink == 0)`. I did **not** establish the boot-time
value of `g_log_level`, so **I do not claim these branches are dead in the
traced window.** What the shipped image does prove (§1, 618/618) is that the
restored arguments are exactly the ones the original loads at those `bl` sites,
so where a branch *does* execute, the reconstruction is now closer to the
original, not further away.

### 7.3 Warnings

App warnings are **2,005**, against Stage 02's measured 1,887 on the Stage tree
(+118, and note that is a cross-tree comparison, not a like-for-like one).
The movement is one class: `-Wint-conversion`, now **289**, from log call sites
whose first argument is still a bare `char *` where the authoritative prototype
says `unsigned long`. This is the diagnostic `g1_log.h` explicitly predicts, it
is a no-op conversion on this 32-bit target, and 810 + 174 = 984 of these sites
were converted to the corpus `((unsigned long)…)` spelling **with `.text` moving
0 bytes**, which is the proof that the remainder are cosmetic too. They are left
because the residue is in argument positions this pass did not otherwise touch.

---

## 8. Reproducing

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
S=<scratchpad>

$V $S/evidence.py app          # 566 functions / 2470 sites / 2420 formats resolved
$V $S/arity.py                 # 850 format VAs, 0 with more than one arity
$V $S/logscan2.py $S/sites.json
$V $S/fix_pairs.py             # DRY RUN; --apply to write
$V $S/fix_decls.py             # ditto
$V $S/fix_asserts.py --apply
$V $S/fix_imu.py --apply

./recon/application/build_cohesive.sh app /private/tmp/g1-defect-app
$V tools/verify_data.py
$V recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
$V recon/emulator/scripts/check_ram_pin_collisions.py /private/tmp/g1-defect-app/zephyr/zephyr.elf
```

**Nothing was committed. The tree is left dirty.**
