# Stage 02 — repeated code blocks → inlinable functions and macros

**Status: COMPLETE for this pass, one gate outstanding (§7).** Written
incrementally as the work ran. **Nothing here is committed.**

Starting point of this pass:

```
HEAD          21659e1b  "refactor: staged pipeline under recon/refactor/ + Stage 01 literal inline"
working tree  dirty (concurrent parity agent, battery/fuel-gauge defect fixes):
              M recon/app/src/{FUN_0000e53c,FUN_0002ea28,fuel_gauge_update}.c  (+ _sym / verified mirrors)
              M recon/symbolized/app/{battery_soc_curve_model_init,fuel_gauge_sample_init_timestamp,fuel_gauge_update}.c
              M recon/symbols/g1_app_globals.ld, recon/symbols/g1_app_symbols.h
              M recon/generated/app_verified_data_sources.cmake
              M tools/cfg_verify.py
              ?? recon/data/rodata_0x88a50.c
```

**Headline.** Stage 02 collapses **3,562 duplicated sites** across **714 files**
into five macro families, and the resulting firmware is **byte-identical to
Stage 01 on both cores** — `cmp` silent on `zephyr.bin`, 3,426/3,428 app and
1,168/1,170 net object files byte-identical, ELF symbol tables identical to the
line. And it produced the bucket-(b) harvest Stage 01 structurally could not:
**192 candidate latent reconstruction defects**, of which the compiler
independently confirmed **273 hard errors in 44 translation units** when the
authoritative prototype was forced in.

---

## 1. The population, re-measured against the LIVE compilable tree

Stage 01's lesson was that plan-file counts are stale relative to what is
actually live (it measured 544 live candidates where the plan said 2,092). Every
figure below was re-derived by scanning the **2,610 `.c`/`.inc`/`.h` entries of
`driver.py input-set`'s 2,612-file transformable set** (the authority is
`recon/generated/{app,net}_retained_sources.cmake`, never a glob), with comments
and string bodies masked by the same lexer Stage 01 uses
(`transforms/t01_literal_inline.mask`).

`recon/ownership/code_dedupe_plan.json` counts its clusters over the **canonical**
trees `recon/app/src` (2,141 files) + `recon/net/src` (1,177). Those are R1
evidence and are *not* what the build compiles. The delta below is that
difference plus the 677 app / 312 net manifest exclusions the retained-source
lists encode.

| cluster | plan / brief says | **live in the compilable tree** | files |
|---|---:|---:|---:|
| C02 volatile-cast accessors | 7,543 sites / 1,405 files (brief) | **6,069 sites, 84 spellings** | **1,095** |
| C01 print-half + `assert_post_action` adjacent pair | 440 pairs / 257 files | **146 pairs** (115 app / 31 net) | **96** |
| C01 loose `assert_post_action(` | 662 app / 268 net | **321** (243 app / 78 net) | — |
| C06 log-level gate | 337 sites / 133 files | **409 if/else pairs** (see §1.1) | **161** |
| C12 `expr; __builtin_unreachable();` | 79 sites / 43 files | **48 sites** (2 app / 46 net) | **26** |
| C07 `__set_BASEPRI_MAX(N); __ISB();` | 48 sites / 45 files | **15 sites** (11 app / 4 net) | **14** |
| C09 `((long long (*)(void))F)()` cast-call | 1,012 sites / 2 files | **1,012 sites / 2 files** | 2 |
| zero-argument `debug_print()` | 140 (brief) | **230 source occurrences / 45 files**; **273 TU-level call sites** measured by the compiler (§5.3) | 44 TUs |

### 1.1 Corrections to the brief, stated plainly

* the brief's **~7,543 volatile-cast sites across ~1,405 files** is a
  canonical-tree figure. Live in the compilable tree: **6,069 sites in 1,095
  files**, in **84 distinct spellings**.
* the brief's **~440 assert pairs** is likewise canonical. Live: **146**.
* the brief's **~337 log-gate patterns**: the plan's normalised shape
  (`if (*(volatile int*)N == N) { DEBUG_PRINT(N,N); } else { debug_print(N,N); }`)
  matches **zero** live sites, because symbolization rewrote `DEBUG_PRINT` to
  `log_message` and the gate global to a named pointer. Under the live spelling
  there are **409** such if/else pairs in **161** files — *more* than the plan
  says, not fewer. Only **266** of them have identical argument lists in the two
  branches; the other **143** are the defect harvest (§5.1).
* the brief's **140 zero-argument `debug_print()` sites** is an undercount on
  both counts. There are **230** literal source occurrences in 45 files, and the
  compiler measures **273** actual call sites once macro expansion is accounted
  for — `key_event_thread.c` alone hides **36** behind a one-line `LOG()` macro
  that a text scan sees as 2.
* the brief's app flash figure **954,460 B / 97.14 %** did not reproduce.
  Measured at this pass's inputs: **954,336 B / 982,528 B = 97.13 %**, i.e. the
  Stage 01 number, and **28,192 B of headroom**. Net reproduced exactly:
  **225,581 B / 97.48 %**.

---

## 2. What Stage 02 is, exactly

`recon/refactor/transforms/t02_block_dedupe.py`, registered as stage 2 in
`driver.py`. Five sub-batches, **ordered most-mechanical / least-risky first**
so that if observable side-effect equivalence later breaks, the sub-batch that
broke it is identifiable. Each is separately accounted for in `MANIFEST.json`
under `sub_batches`.

| | sub-batch | what it does | sites | files |
|---|---|---|---:|---:|
| **A** | volatile-accessor **spelling** normalisation | `*(volatile T*)` / `*(volatile T *)` → one spelling; `unsigned` → `unsigned int` | **3,116** | **584** |
| **B** | `G1_NORETURN_CALL` | `expr; __builtin_unreachable();` → one macro (C12) | **45** | 25 |
| **C** | `G1_LOG_ROUTE` | the log-sink route if/else → one macro (C06) | **266** | 127 |
| **D** | `G1_ASSERT_FAIL` / `G1_NET_ASSERT_FAIL` | the `__ASSERT` expansion pair → one macro (C01) | **135** | 92 |
| **E** | log-prototype convergence | withdraw per-file `extern` log declarations in favour of `recon/headers/g1_log.h` (C10 residue) | 2 decls | 1 |
| | **total** | | **3,562 rewrites + 2 withdrawals** | **714** |

The one new file the transformer generates is `recon/headers/g1_dedupe.h`, which
lives **inside the stage tree only**; the live `recon/headers/` is untouched.

### 2.1 Sub-batch A — same C type only, never a merge

Only two classes of respelling are applied, and both are provably
type-preserving:

1. **whitespace.** `*(volatile int*)` and `*(volatile int *)` differ by a space,
   and whitespace is not part of a type.
2. **`unsigned` → `unsigned int`, `signed` → `signed int`.** C11 6.7.2 makes
   these designate the *same type*.

Nothing else is merged. `int` is **never** folded into `unsigned int` — the plan
flags that as the trap (977 canonical `*(volatile int*)` sites whose signedness
is load-bearing for every downstream comparison and shift), and no typedef is
resolved: `u32`, `uint32_t`, `unsigned int` and `uint` stay three or four
distinct spellings here. Collapsing them is stage 04's job, with the signedness
audit the plan demands.

**Measured effect: 84 spellings → 52.** Top of the canonical set afterwards:

```
 1194  *(volatile int *)            712  *(volatile unsigned char *)
  752  *(volatile unsigned int *)   519  *(volatile uint8_t *)
  727  *(volatile uint32_t *)       294  *(volatile u8 *)
```

The 32 spellings that disappeared are exactly the whitespace twins plus
`unsigned`/`signed`. 2,953 of the 6,069 sites were already canonical and were
left alone.

### 2.2 Sub-batch C — why the macro takes the condition, not a gate value

The plan proposes `G1_LOG(gate, ...)` with the compared value baked in, and
flags the risk as *"only ONE of the two branches is taken at runtime, so a
swapped branch is invisible to any test that never flips the gate; confirm the
sense of the comparison per site from the disassembly."*

`G1_LOG_ROUTE(cond, ...)` takes **the whole condition, verbatim**:

```c
#define G1_LOG_ROUTE(cond, ...)        \
    do {                               \
        if (cond) {                    \
            log_message(__VA_ARGS__);  \
        } else {                       \
            debug_print(__VA_ARGS__);  \
        }                              \
    } while (0)
```

The transform never parses the condition, so it **cannot** invert a sense. That
turns a per-site disassembly review of 266 sites into a structural property.
The expansion is token-identical to the block it replaces, which is why the gate
is a byte-identical `.o` rather than an argument.

It is applied **only** where the two branches spell their argument lists
identically (266 of 409). The other 143 are §5.1.

### 2.3 Sub-batch D — parenthesised packs, because the halves do not pair 1:1

The plan's dominant hazard for C01 is that *"collapsing a 5-argument site into a
4-argument macro silently drops a register argument"*, which the Unicorn
differential harness is structurally blind to (19 confirmed instances,
`code_dedupe_plan.json` `hard_rule`). Measured live, **nine** distinct
(print-arity, post-arity) shapes exist:

```
printk(4)+post(2)  60    printk(1)+post(2)  25    printk(2)+post(2)  13
printk(5)+post(2)  11    printk(3)+post(2)   1    printk(8)+post(2)   1
assert_print(3)+post(2) 23   assert_print(5)+post(2) 1   printk(0)+post(0) 4
```

So the macro takes **parenthesised argument packs**, pasted verbatim:

```c
#define G1_ASSERT_FAIL(print_pack, post_pack)   \
    do { printk print_pack; assert_post_action post_pack; } while (0)
```

A pack macro cannot change an arity it never enumerates. All eight non-degenerate
shapes survive unchanged and are recorded in the MANIFEST as
`shapes_preserved`. The ninth — `printk(0)+post(0)`, 4 sites — is **refused**
and filed as a defect (§5.2): a zero-argument print half is not duplication, it
is a dropped-argument reconstruction.

The honest caveat: `G1_ASSERT_FAIL((fmt, cond, file, line), (file, line));` is
not more *readable* than the two statements it replaces. Its value is that the
idiom now has one name and one definition site, and that a later batch which
*does* recover the true `__ASSERT(cond)` shape has exactly one place to change.

### 2.4 Sub-batch E — the authoritative log prototype, and where it cannot reach

G7-B2 consolidated 2,420 declarations onto `recon/headers/g1_log.h`. It did not
reach everywhere. Measured live in the compilable tree, **250 `extern`
declarations of five logging/assert entry points survive in 172 files, in 86
distinct signature spellings**:

| entry point | decls | files | distinct spellings | most common |
|---|---:|---:|---:|---|
| `assert_post_action` | 129 | 129 | **41** | `(int,int)` 15, `(uint32_t, uint32_t)` 11, `(unsigned,unsigned)` 8 |
| `debug_print` | 43 | 43 | 2 | **`(void)` 39**, `()` 4 |
| `log_message` | 43 | 43 | 24 | `(int,...)` 8, `()` 5, `(unsigned int message, unsigned int function)` 4 |
| `assert_print` | 31 | 31 | 17 | `(const void*, const void*, uint32_t)` 4, 5-arg forms 2 |
| `printk` | 4 | 4 | 2 | `(void)` 3, `(int,...)` 1 |

Sub-batch E withdraws a file's `extern` for `debug_print`/`log_message`/
`DEBUG_PRINT`/`printk` and includes `g1_log.h` instead — **but only when every
call site in that file is compatible with the authoritative prototype**
`void f(uintptr_t format, ...)`, i.e. has at least one argument. **45 of the 46
files fail that test**, so 45 are quarantined and **1** is converted (2
declarations withdrawn). That is a deliberately small number: the quarantined 45
are the finding, not a failure to transform. See §5.3.

`assert_post_action` and `assert_print` are **not** touched at all — there is no
authoritative header for them yet, and writing one requires reading their
prologues off the shipped image, which is a separate evidence task (§6, item 4).

---

## 3. First-try compile status — the measurement, not the checkbox

The transformer needed **two rounds**. Both are reported, because the iteration
history is the finding.

| round | change | outcome | bucket |
|---|---|---|---|
| 1 | first transformer | app build **FAILED**, 1 error: `g1_dedupe.h:72: too few arguments to function 'printk'`, from `app_event_alloc.c` | **(a) transformer bug, with a (b) payload** |
| 2 | sub-batch E's compatibility scan moved onto the PRE-TRANSFORM text; sub-batch D refuses a zero-argument print half | app **exit 0**, net **exit 0**, **0 errors**, warnings Δ 0 | — |

**The round-1 bug, and why it matters.** Sub-batch D ran before E and folded
`printk(); assert_post_action();` in `app_event_alloc.c` into
`G1_ASSERT_FAIL((), ())`. E then scanned for `printk(` call sites, found none —
the call was now inside a macro invocation — concluded the file was compatible,
withdrew its `extern void printk(void);` and included `g1_log.h`. The macro then
expanded `printk ()` against the authoritative variadic prototype and the
compiler rejected it.

That is a genuine ordering bug in *my* transformer (bucket (a)), and the fix is
in the transformer, not the tree: E's compatibility scan now runs over a
pre-transform snapshot (`orig_masked`), and D refuses any pair whose print half
has zero arguments. But the *content* of the failure is bucket (b): those four
sites really are a zero-argument reconstruction of a 4-or-5-argument shipped
call, and they now appear in `DEFECTS.json` as
`zero_argument_assert_expansion`. **The compiler found in one build what a text
scan of `printk(` had already found but a text scan of the transformed tree
could not.**

**Compile-failure triage across the whole pass: 1 failure, bucket (a), fixed in
the transformer, regenerated. Zero hand-edits at any scale.**

---

## 4. Gate ladder — measured

Built from the stage trees with the repository's own entry point, **no build
file, linker script or `tools/` module edited anywhere**:

```sh
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s1-app
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   app /private/tmp/g1-s2-app
./recon/refactor/stage_01_literal_inline/tree/recon/application/build_cohesive.sh net /private/tmp/g1-s1-net -- \
      -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh   net /private/tmp/g1-s2-net -- \
      -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
```

| gate | Stage 01 (baseline, rebuilt this pass) | **Stage 02** |
|---|---|---|
| app build | exit 0 | **exit 0, first try after the round-2 transformer** |
| net build | exit 0 | **exit 0, first try** |
| **app `zephyr.bin`** | — | **BYTE-IDENTICAL to Stage 01 (`cmp` silent)** |
| **net `zephyr.bin`** | — | **BYTE-IDENTICAL to Stage 01 (`cmp` silent)** |
| app `app_update.bin` | — | identical for **954,928 of 955,184 B**; the trailing **256 B differ — the MCUboot RSA-PSS signature, which is randomised by construction**. Every byte of image and of the SHA-256 TLV before it is identical. |
| app FLASH | 954,336 B / 982,528 B = 97.13 % | **954,336 B = 97.13 % — Δ 0 B** |
| app `.text` / `.data` / `.bss` | 949,368 / 4,951 / 249,251 | **Δ 0 / Δ 0 / Δ 0** |
| app RAM | 253,765 B = 56.32 % | **Δ 0 B** |
| net FLASH / RAM | 225,581 B = 97.48 % / 63,380 B = 96.71 % | **Δ 0 B / Δ 0 B — the frozen values, untouched** |
| net `.text` / `.data` / `.bss` | 222,629 / 2,950 / 60,468 | **Δ 0 / Δ 0 / Δ 0** |
| ELF symbol table (`nm -n`, every entry) | app 7,903 / net 3,966 | **0 diff lines / 0 diff lines** |
| RAM layout (`nm -n`, every `0x2…` symbol) | — | **0 diff lines, both cores** |
| `nm -u` undefined | 0 / 0 | **0 / 0** |
| duplicate global definitions (`nm --defined-only --extern-only`) | 0 / 0 | **0 / 0** |
| `--allow-multiple-definition` / `--defsym` | 0 | **0** |
| compiler warnings | 1,887 app / 1,066 net | **1,887 / 1,066 — Δ 0** |
| compiler errors | 0 / 0 | **0 / 0** |
| **per-object comparison** (`--strip-debug --remove-section=.comment`, matched by build-relative path) | — | app **3,426 / 3,428 byte-identical**; net **1,168 / 1,170** |
| `.rodata` read out of the linked ELF's PT_LOAD vs `app_update.bin` | 1,325 match / 14 mismatch | **1,325 / 14 — the same 14, name for name** |
| `check_ram_pin_collisions.py` app | — | **624 bound OK, 0 escaping, 0 unknown inside a live object** |
| `check_ram_pin_collisions.py --core net` | — | **170 bound OK, 0 / 0** |
| `check_net_raw_literals.py` | — | **983 TUs, 0 failed to preprocess, 0 / 0 / 0 / 0 / 0** |
| `verify_net_stock_data_window.py` | — | **PROVEN** — 93 differing words all flash pointers, **0 differing for any other reason**, 0 non-stock input sections |
| `check_thread_create_stack_args.py --trials 120` | — | **10 / 10 PASS** |
| `gen_retained_sources.py --check` | clean | **clean** |
| `driver.py check-addresses 1 2` | — | **identical, 2,561 addresses both sides, 0 gained, 0 lost** |
| `test_guard.py` (whole `recon/refactor` suite) | — | **7 / 7 PASS** |
| idempotence (`materialize 2` twice) | — | MANIFEST `61767d0b…` → `61767d0b…`; whole-tree hash `72cd4d7a…` → `72cd4d7a…` — **byte-identical** |

**The two differing objects on each core are the same two on both**:
`open-amp/.../remoteproc_virtio.c.obj` and `zephyr/lib/posix/uname.c.obj` —
stock SDK units this stage does not touch, already recorded in
`prerefactor_progress.md` §0/§4 as differing build-to-build regardless of any
change. Three app objects were unmatched by basename+path (the
`main.c.obj` / MCUboot collision class Stage 01 §5.1 already documented).

### 4.1 What the byte-identical image actually proves

Every one of the 714 files Stage 02 rewrote produced a **byte-identical object
file**, and both linked images are byte-identical to Stage 01's. Under R7 the
acceptance bar is observable side-effect equivalence with the shipped binaries;
a byte-identical image means Stage 02's side-effect equivalence is **exactly
Stage 01's, by construction, not by argument.** Every bus transaction, every
volatile access, every ordering, every framebuffer byte is the same instruction
stream. That is a stronger result than any behavioural capture could give, and
it is the reason the gate for this stage was chosen to be the `.o` and not the
oracle.

It also retires, empirically, the plan's per-site disassembly review demands for
C06 and C01: a transformation that emits the same instructions cannot have
swapped a branch sense or dropped a register argument.

---

## 5. The bucket-(b) harvest — 192 candidate latent defects

`recon/refactor/stage_02_block_dedupe/DEFECTS.json`, **192 entries over 63
distinct files, implicating 330 call sites**. Stage 01 found zero and explained
correctly why: it introduced no new authoritative declaration, so it had no
mechanism to expose one. Stage 02 does, three separate ways.

| class | entries | what it is |
|---|---:|---|
| `log_route_branch_disagreement` | **143** | the two branches of one log gate disagree about the argument list |
| `zero_argument_call_to_variadic_log_entry_point` | **45** files / **183** source sites | a call with no arguments to an entry point whose shipped prologue reads one fixed argument then a `va_list` |
| `zero_argument_assert_expansion` | **4** | `printk(); assert_post_action();` where the shipped expansion passes 4–5 register arguments |

### 5.1 The log-route disagreement — 143 sites, 40 files

Of the 409 live log-gate if/else pairs:

| | sites |
|---|---:|
| identical argument lists — **transformed** | **266** |
| **else branch dropped ALL arguments** | **80** |
| argument counts differ (2↔3, 2↔1, 3↔1, 5↔4, 8↔4, 11↔1, 7↔5, 5↔3, …) | **55** |
| same arity, different argument text | **8** |

The shape is unmistakable. From `global_system_suspend.c`:

```c
if (*(volatile int *)&g_log_use_alt_sink == 0) {
    log_message("%s(): begin.\n", "global_system_suspend", param_3, 0U);
} else {
    debug_print();                       /* <- four arguments gone */
}
```

Both branches are the *same log line* routed to a different sink. The `if` half
knows the format string and three arguments; the `else` half knows nothing. Only
one branch runs on any given boot, so a differential harness that never flips the
sink global cannot see it — which is exactly the blind spot
`code_dedupe_plan.json`'s `hard_rule` describes. The `11 vs 1` case
(`spec_ble_command_hook.c`) drops ten.

These are **not** transformed. They are quarantined with the full snippet, the
per-branch arity and the line number, so a disassembly-level fix in the canonical
tree (which this pipeline may never write — R1) has everything it needs.

### 5.2 The zero-argument assert expansion — 4 sites

`app_event_alloc.c` and three others contain

```c
extern void printk(void);
extern void assert_post_action(void);
...
printk();
assert_post_action();
```

against a cluster whose shipped app shape is
`printk("ASSERTION FAIL [%s] @ %s:%d\n", #cond, file, line)`. Four or five
register arguments, none of them reconstructed. This is the *only* one of the
nine C01 shapes sub-batch D refuses.

### 5.3 The zero-argument log calls — measured by the compiler, not predicted

Static prediction from the transformer: **183 zero-argument source sites in 45
files**, each held up only by that file's own `extern void debug_print(void);`.

To turn the prediction into a measurement, `driver.py` gained a **diagnostic
stage 99** — the same transformer run with `G1_STAGE02_FORCE_LOG_HEADER=1`,
which withdraws the local extern in the quarantined files too. **That tree is
expected not to compile; its errors are the measurement.** It withdrew 90
declarations across 46 files, and:

```
$ ninja -k 0                                       # keep going past the first failure
275 errors, 44 failing translation units
    223  error: too few arguments to function 'debug_print'
     44  error: too few arguments to function 'log_message'
      6  error: too few arguments to function 'printk'
      1  error: conflicting types for 'debug_print';  previous declaration 'int()'
      1  error: conflicting types for 'log_message';  previous declaration 'int()'
```

**273 hard call-site errors in 44 translation units.** The compiler's number is
higher than the text scan's 183 because macro expansion multiplies sites:
`key_event_thread.c` defines

```c
#define LOG() do { if (SINK==0) log_message(); else debug_print(); } while (0)
```

and uses it **36 times**. A text scan sees two calls; the compiler sees
seventy-two errors. Worst files:

```
 72  key_event_thread.c            41  ble_process_put_ops_09_10.inc   25  proxy_thread_handler.c
 14  ble_process_put_ops_19_20.inc 12  imu_fusion_thread.c            10  check_work_mode.c
 10  button_init.c                  8  ble_process_put_ops_21_27.inc   7  navigation_overview_map_display.c
  7  init_watchdog.c                6  ble_process_put_ops_0b_18.inc   5  gui_utf_draw_truncate.c
```

The two `conflicting types` errors are a **separate, new finding**:
`recon/symbolized/app/ble_process_put_common.h` declares

```c
extern int log_message();
extern int debug_print();
```

— K&R-unprototyped **and returning `int`**, where the authority (read off the
shipped prologue, `g1_log.h`) says `void … (uintptr_t, ...)`. That header is
**not in the pipeline's input set at all**, which is itself a gap: `input_set.py`
enumerates the `.inc` fragments retained sources include but **not the `.h`
fragments**. See §6 item 6.

### 5.4 What these defects are, and are not

They are **not** proof of a behavioural bug. They are places where the recovered
C disagrees with itself about how many arguments an entry point takes, in a
direction the Unicorn differential harness is structurally blind to (dropped
register arguments — 19 confirmed instances already). Each one needs a
disassembly-level read of the `bl` site to recover the true arity, exactly as
G7-B2 did for the prototypes. That work belongs in the **canonical** trees, which
this pipeline may never write (R1), so it is handed over rather than done here.

---

## 6. What I did NOT do, and everything quarantined, with measured reasons

1. **I did not run the behavioural oracle.** Renode is owned by another agent and
   the brief forbids running it, so the display/sensor capture was not run.
   **I therefore do not claim R7 acceptance from a behavioural capture.** What I
   claim instead is stronger for this particular stage and is fully measured:
   both `zephyr.bin` are **byte-identical to Stage 01's**, so Stage 02's
   observable behaviour is Stage 01's, instruction for instruction. The
   outstanding gate is Stage 01's own oracle run (its report §4 item 1), which
   Stage 02 inherits unchanged. When it is run, the four framebuffer hashes to
   match are `19b1f24a…` / `0c5cc90b…` (dashboard) and `b26c73b3…` / `1d617c65…`
   (navigation), and because RAM layout diffs to 0 lines and `.text` moved 0 B,
   the iteration-38 probe addresses remain valid.
2. **I did not touch any canonical tree.** Structurally impossible through
   `guard.check_write`; confirmed by `git status` (no `recon/{app,net,verified}/**`
   change from this pass).
3. **I did not touch `tools/`, `recon/emulator/**`, `armemul`, any build file,
   any linker script, `recon/board/**`, or the live `recon/headers/`.** The new
   `g1_dedupe.h` exists only inside the stage trees.
4. **I did not write an authoritative header for `assert_post_action` /
   `assert_print`.** They are declared 129 + 31 times in 41 + 17 distinct
   spellings and are the single largest remaining prototype inconsistency, but
   fixing them requires reading their prologues off the shipped image. A first
   read of `FUN_0007e2ec` @ `0x0007e2ec` shows
   `eors r0,r0; msr BASEPRI,r0; mov.w r0,#4; svc #2; bx lr` — it **zeroes r0
   before reading anything**, i.e. it consumes no argument, which would make the
   185 live two-argument call sites the *invented*-argument mirror of §5. That is
   a strong hint, not evidence: whether the shipped `bl` sites set up r0/r1 has
   to be read at the call sites, and 5 of the 129 declarations additionally
   carry `__attribute__((noreturn))` while the body ends in `bx lr`. **Not
   automatable under R5 without that read; explicitly deferred.**
5. **I did not touch cluster C07 (irq-lock prologue).** Live population is
   **15 sites in 14 files**, and the plan's risk is exact: *"folding a save-less
   site into the saving inline ADDS a register read the original never made, and
   that extra read is invisible to the harness."* Under R8 that is a change to
   the number of bus transactions. Conservative default: **untouched**. Fifteen
   sites do not justify it.
6. **I did not touch cluster C09 (the 1,012 cast-calls).** The plan is explicit
   that it is *"NOT a dedupe"* — it is a per-call disassembly audit of a
   `long long (*)(void)` cast that makes the caller read r0:r1 for a callee that
   only defines r0. Batching it is forbidden by the plan and it is not a
   duplication transform.
7. **I did not touch cluster C11 (constant-returning stubs).** Explicit non-goal:
   they are distinct shipped symbols that happen to share a body.
8. **I did not touch cluster C08 (13 net vtable thunks).** `code fn` is a Ghidra
   pseudo-type and the dispatched targets' real signatures are unknown; the plan
   requires reading all 13 prologues first. Net is also frozen at ~1.7 kB of real
   headroom.
9. **I did not extend `input_set.py` to enumerate `.h` fragments.** §5.3 shows it
   should: `ble_process_put_common.h` carries two wrong declarations and is
   invisible to the pipeline. I left it alone deliberately — changing the input
   set changes the file list for stages 00 and 01 as well, invalidating two
   landed manifests and every measurement in Stage 01's report. It is filed as
   the highest-value pipeline fix for the next stage, to be made *before* stage
   03 materialises.
10. **I did not commit anything.**

### 6.1 Quarantine, in full

`recon/refactor/stage_02_block_dedupe/QUARANTINE.json`. **Not one entry was
hand-edited.**

| sub-batch | reason | count |
|---|---|---:|
| C | else branch dropped ALL arguments | 80 |
| C | argument count differs between the branches | 55 |
| C | same arity, different argument text | 8 |
| D | print half has zero arguments | 4 |
| B | not in statement position (`__asm__ volatile` tail in `bt_hci_core_recv_event.c`) | 2 |
| B | call head is not a plain identifier (`FUN_010256dc.c`) | 1 |
| E | file has a zero-argument call to a variadic log entry point | 45 files |

Refusals B/C/D also silently skip any site inside a **line-continued macro body**
(where a `do { } while (0)` would swallow the continuation) and any site not in
statement position (where the added `;` would terminate an enclosing unbraced
`if`). Those two structural guards are why the tree compiles.

---

## 7. R8 — which of these transformations could reorder or coalesce a volatile access

R8 is *anything that reorders or coalesces volatile MMIO accesses, or changes the
number or order of bus transactions.* Answering directly, per sub-batch:

| sub-batch | R8 exposure | what makes it safe |
|---|---|---|
| **A** volatile spelling | **none** | whitespace is not part of a type, and `unsigned` ≡ `unsigned int` (C11 6.7.2). No access is added, removed, widened, re-signed or reordered. No typedef is resolved and `int` is never merged with `unsigned int` — that is stage 04. |
| **B** `G1_NORETURN_CALL` | **none** | the expansion is the same token sequence in the same order. |
| **C** `G1_LOG_ROUTE` | **the one to watch, and the only real one in this stage** | **122 of the 266 conditions are themselves a volatile read** (`*(volatile int *)&g_log_use_alt_sink == 0` and its `unsigned int` / `uint32_t` spellings). The macro expands `cond` **exactly once**, in the same syntactic position — a macro that mentioned it twice would double a real bus transaction. Single evaluation is asserted in the header comment as a maintenance contract, and is *proved* by the byte-identical `.o`. |
| **D** `G1_ASSERT_FAIL` | **none** | both packs are pasted verbatim; the sequence point between the two calls is the `;` inside the macro body. |
| **E** prototype convergence | **none directly** | a declaration emits no instruction. It *can* change codegen where the local declaration was wrong — that is the point of the batch — but it cannot reorder an access. On this stage it changed one file and the image did not move. |

**And the whole argument is closed empirically:** both cores' `zephyr.bin` are
byte-identical to Stage 01's, and 4,594 of 4,598 object files are byte-identical
(the 4 exceptions being two stock SDK units per core that differ build-to-build
regardless). **No bus transaction can have been added, removed or reordered by a
transformation that emits the same instruction stream.**

The pointer-identity residual Stage 01 named does not recur here: Stage 02
introduces no new object and merges no literal.

**Where R8 still bites, updated for the stages ahead:**

| stage | transformation | R8 exposure | conservative default |
|---|---|---|---|
| 03 | `assert_post_action` / `assert_print` authoritative prototype | none directly, but it decides 160 declarations at once and will change codegen wherever the local one was wrong | read both prologues AND a sample of `bl` sites; per-object `.o` comparison; oracle before acceptance |
| 04 | MMIO accessor macros per width | **direct** — folding `*(volatile int*)` and `*(volatile unsigned*)` into one macro changes signedness downstream; a macro evaluating its argument twice changes the number of bus transactions | one macro per width **and** per signedness; single evaluation; `volatile` verbatim; `.o` comparison and an oracle run per batch. Sub-batch A has already reduced 84 spellings to 52, which is the prerequisite. |
| 04 | irq-lock prologue (C07) | **direct** — save/lock/ISB/restore is an ordering contract and `__atomic_signal_fence` emits no instruction where the dominant form emits a real `isb` (G7-B1) | never collapse across the two families; only 15 live sites, so leaving them is cheap |
| 06 | module materialisation | none, but `KEEP(*rodata_*.c.obj(".rodata.rodata_*"))` ties flash occupancy to filenames | freeze `rodata_*` filenames; regenerate the KEEP list; gate on a byte-identical image |
| 07 | struct typing | indirect — a wrong field width changes access width, and for a `volatile` field that changes the bus transaction | per-struct batches with `_Static_assert(offsetof/sizeof)`; `.o` comparison; oracle after each |

---

## 8. Concurrency, idempotence and repository footprint

**Concurrency.** `driver.py status` reports all four stages `"current"`,
`inputs_unchanged: 2612`, `inputs_changed: []` at both the start and the end of
this pass. The parity agent's battery/fuel-gauge fixes were already in the tree
when stage 00 was snapshotted (Stage 01's pass), and it landed nothing further
while this pass ran. **Nothing measured here was taken against a moving input.**
If it lands one now, `status` will say `stale` and name the file; the repair is
`materialize 0 && materialize 1 && materialize 2` and re-running §4. **Never a
hand patch.**

**Idempotence, measured.** `materialize 2` twice, no other change:

```
MANIFEST.json sha256      61767d0b06119056…  ->  61767d0b06119056…
sha256 over the whole tree 72cd4d7aee8db392…  ->  72cd4d7aee8db392…
```

**Footprint.** Everything this pass wrote:

```
 M recon/refactor/driver.py                          (stage registry: 2 and 99)
?? recon/refactor/transforms/t02_block_dedupe.py     (the transformer)
?? recon/refactor/stage_02_block_dedupe/             (MANIFEST/PARITY_MAP/QUARANTINE/DEFECTS + tree/)
?? recon/refactor/stage_99_defect_probe/             (the diagnostic tree; expected not to compile)
?? recon/analysis/staged_refactor_stage02.md         (this file)
```

`recon/refactor/.gitignore` already excludes `stage_*/tree/`, so the two new
stage directories contribute four JSON files each, not 17 MB each. **No file
outside `recon/refactor/` and this report was written.** Nothing committed.

---

## 9. Reproducing this pass

```sh
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V recon/refactor/driver.py materialize 0
$V recon/refactor/driver.py materialize 1
$V recon/refactor/driver.py materialize 2
$V recon/refactor/driver.py check-addresses 1 2
$V -m unittest discover -s recon/refactor -p 'test_*.py'

./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s2-app
./recon/refactor/stage_02_block_dedupe/tree/recon/application/build_cohesive.sh net /private/tmp/g1-s2-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
cmp /private/tmp/g1-s1-app/zephyr/zephyr.bin /private/tmp/g1-s2-app/zephyr/zephyr.bin   # silent
cmp /private/tmp/g1-s1-net/zephyr/zephyr.bin /private/tmp/g1-s2-net/zephyr/zephyr.bin   # silent

# the defect probe -- EXPECTED TO FAIL; its errors are the measurement
G1_STAGE02_FORCE_LOG_HEADER=1 $V recon/refactor/driver.py materialize 99
./recon/refactor/stage_99_defect_probe/tree/recon/application/build_cohesive.sh app /private/tmp/g1-s99-app
(cd /private/tmp/g1-s99-app && ninja -k 0)     # 275 errors, 44 failing TUs
```
