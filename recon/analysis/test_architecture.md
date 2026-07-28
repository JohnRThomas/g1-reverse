# Test architecture for the G1 reconstruction — design, harness, pilot

**Status:** architecture-and-pilot pass, 2026-07-28. Written incrementally; the
numbers below were produced by commands run in this pass, not inherited.
Nothing is committed. `git status` at the end lists exactly what changed.

**What this replaces.** The R7 behavioural gate (Renode, slot-quantised bus
traces, `W = 100.513 ms` / `R = 1.160 ms`) is not the acceptance criterion for
code-quality work any more. Iterations 46–53 established why: making one
function `static` — semantically identical, both forms disassembled and shown
to be the same program — moves its own I²C traffic by 30 µs, and by 1.7 s that
shift crosses a 30 ms BLE connection-event boundary and fails the gate. Under
that constraint no restructuring is possible. The gate remains valid for what
it measures; it is simply the wrong instrument for "did this refactor change
behaviour".

---

## 0. Measured starting state

Every number here comes from a command run in this pass.

```
tools/modtest/index.py app
  canonical  (stage 00 snapshot, flat)   units=2147  symbols=2136  merged=0
  refactored (stage 09, modular)         units= 660  symbols=1604  merged=222
```

Module census of the refactored tree (`recon/refactor/stage_09_call_cohesion/
tree/recon/symbolized/app`), counted by provenance banner:

```
module TUs: 660   single-function TUs: 438   = 66.4 %
functions per TU: 437x1, 70x2, 42x3, 30x4, 15x5, 15x6, ... 1x24, 1x25, 1x39

  analytics  TUs=  4 single=  2 ( 50%) funcs=  14
  audio      TUs= 63 single= 41 ( 65%) funcs= 137
  ble        TUs= 40 single= 28 ( 70%) funcs=  99
  common     TUs=  3 single=  3 (100%) funcs=   3
  core       TUs= 52 single= 31 ( 60%) funcs= 142
  display    TUs= 26 single= 15 ( 58%) funcs=  89
  esb        TUs= 12 single=  8 ( 67%) funcs=  24
  gui        TUs= 29 single= 20 ( 69%) funcs=  57
  ipc        TUs= 11 single=  4 ( 36%) funcs=  47
  lib        TUs=217 single=149 ( 69%) funcs= 482
  notify     TUs= 45 single= 28 ( 62%) funcs=  99
  sensors    TUs= 35 single= 19 ( 54%) funcs=  94
  storage    TUs= 39 single= 29 ( 74%) funcs=  85
  ui         TUs= 34 single= 24 ( 71%) funcs=  65
  unsorted   TUs= 50 single= 37 ( 74%) funcs= 167
```

This confirms the owner's 66 % figure at a different snapshot (the owner's
"493 of 742" and this pass's "438 of 660" are the same ratio at different
stage-09 regenerations). It **corrects** the `unsorted` figure: at stage 09
`unsorted` is **50 TUs / 167 functions**, not 177 files — the 177 belongs to an
earlier stage. `ipc` is the most-merged module (36 % single) and `storage` /
`unsorted` the least (74 %).

Also worth stating plainly, because it shapes the plan: the stage-09 tree still
carries **2,147 flat top-level `.c` files** alongside the 660 module TUs. Those
are the pre-stage-03 copies of sources the build does not compile (the retained
sources list, not the directory, is the build authority). Any tooling that
globs the directory instead of the module subtrees will silently test the wrong
files. `tools/modtest/index.py` refuses to index them for the refactored tree
(`modules_only=True`).

---

## 1. The central decision: the oracle is the shipped image

A test whose expected value comes from our own reconstruction proves
self-consistency and nothing else. The one non-circular source of truth
available is `app_update.bin` / `netcore_image.bin` — the owner's shipped
firmware.

`tools/parity/emu.py` already emulates a single function's *original bytes* at
its real VA under Unicorn. **That capability is the test-vector generator.**
The change of shape is small but decisive:

| | today (`emu.compare`) | this harness |
|---|---|---|
| what runs | original **and** candidate, simultaneously | original **once**, at generation time |
| expectation | implicit, transient | **frozen to JSON**, reviewable, diffable |
| bound to | one source path | a **symbol**, resolved per tree |
| reports | pass/fail | pass/fail **+ measured coverage + mutation kill rate** |

Concretely, `recon/tests/vectors/<core>/<module>/<symbol>.json` holds, for one
function: its original VA and size, its ABI return kind, the sha256 of the
image the expectations came from, the list of globals its literal pool names,
the measured coverage, and one record per fixture containing the complete input
state and the expected observable key.

### How far this can be pushed — measured, not assumed

* **Per-function: proven, and it works on both trees.** Section 4.
* **Whole-module entry points: partially.** `emu.Runner` accepts
  `internal_code_regions` — additional original byte ranges that count as part
  of the unit rather than as oracled calls. That is the mechanism for widening
  the oracle boundary from a function to a module: map every intra-module
  callee's original bytes as internal, and only cross-module calls get oracled.
  Section 6 reports what this actually buys and where it stops.
* **Hard limits, in order of how quickly they bite:**
  1. **Interrupts do not exist.** Unicorn is driven by `emu_start`; there is no
     NVIC, no exception entry, no context switch. Any behaviour that depends on
     an ISR firing is unreachable. This excludes the ESB radio callbacks, the
     RTC/timer expiry paths, and every `k_work` deferred body reached only from
     an ISR.
  2. **Time does not pass.** There is no clock. `k_uptime_get`, `k_busy_wait`,
     `k_sleep` are oracled calls returning a fixed hash; a loop that waits for a
     timer to advance never terminates and hits the instruction cap.
  3. **No RTOS.** `k_sem_take`, `k_mutex_lock`, `k_msgq_put` are oracled. Their
     *side effects on kernel objects* are not modelled, so anything whose
     correctness is "the second thread saw it" is out of scope by construction.
  4. **DMA does not exist.** A SPIM/TWIM transfer started by writing `TASKS_START`
     never deposits bytes in the RX buffer. `emu` can be told to advance one
     absolute word at one read ordinal (`absolute_read_transitions`), which
     models an EVENTS register becoming set, but not a buffer filling.
  5. **MMIO reads return reset state (zero) unless a fixture says otherwise.**
     This is a deliberate fail-closed choice in `emu` (`NRF53_MMIO_WINDOWS`):
     an omitted peripheral read is *not* silently equal to a read returning
     zero, because reads are recorded as ordered events.
  6. **Timing is not modelled at all** — which is the point. The thing that
     made the R7 gate unusable for restructuring is exactly the thing this
     harness does not look at.

---

## 2. Where tests run, and why not the alternatives

**Primary: Unicorn-driven, against the shipped image, host-side.**

Rejected alternatives, with the reason:

* **Host-native build with hardware mocked.** The expectation would have to be
  written by hand or taken from our own code — circular. It also cannot run
  most of this corpus: the reconstruction convention (AGENTS.md §METHODOLOGY)
  expresses globals as fixed absolute-address `volatile` pointers using the
  literal-pool VALUES, e.g. `*(volatile int32_t *)0x2000230c`. On a host those
  addresses segfault. Making them portable would mean rewriting the very
  sources under test.
* **Zephyr `native_sim` / `unit_testing`.** Same circularity problem, plus it
  needs each module to have a buildable dependency closure with Zephyr headers
  — the modules were formed by link-order adjacency and call cohesion, not by
  design, so no such closure exists (section 3). It is the right target *later*,
  for modules that have been genuinely redesigned rather than merged.
* **On-target under Renode.** This is the R7 gate. It is end-to-end, it is
  slow, and it is timing-sensitive to 30 µs — the property that makes
  restructuring impossible. Keep it as a release check, not as a unit suite.
* **Unicorn-driven — chosen.** The expectation is non-circular; nRF5340 MMIO
  and Zephyr kernel calls need no mocks because they are *uniformly oracled on
  both sides*; the same vector file drives both trees; and coverage is
  measurable on the shipped bytes rather than on our own.

A second, complementary tier is worth having and is **not** built here: for
`lib/` functions that are recovered newlib/libm/liblc3 code, an *external*
specification oracle exists (the upstream implementation). That is genuinely
independent evidence and would catch what emulation cannot. Noted in section 8.

---

## 3. The unit boundary, and how dependencies are faked

**The unit is one function, in both trees.** This is forced, not chosen: the
golden expectation is produced by emulating the shipped bytes of exactly one
function, and every control transfer that leaves those bytes is oracled. For
the candidate to be comparable, the same set of transfers must leave it.

**Dependencies are not mocked — they are oracled.** Every external call returns
`sha256(call_ordinal)` in r0:r1. Both sides see the identical value at their
k-th call, and the call itself is recorded as an ordered event carrying its
AAPCS argument registers. This is why no Zephyr or nRF driver mock is needed,
and it is also the honest statement of the limit: the harness proves *what the
function computes and what it asks its dependencies to do*, never *what the
dependencies then do*.

Two boundary problems had to be solved, and both were measured rather than
predicted:

1. **A merged TU inlines its siblings.** A stage-09 unit holds up to 39
   functions; at `-Os` GCC inlines a single-caller `static` sibling, so the
   candidate would perform inline what the shipped function does with a `bl`.
2. **`-fno-inline` is not the fix, and this is the interesting one.** Measured
   on `__ieee754_asinf`: the reconstruction spells its bit-casts as
   `static inline float F(uint32_t)`, which are *notation*, not functions.
   `-fno-inline` turned all sixteen of them into real calls — golden
   `ncalls=0`, candidate `ncalls=16`, **FAIL 0/5 on BOTH trees**. A harness
   artefact that would have read as a reconstruction defect.

The landed answer (`tools/modtest/core.py:UNIT_BOUNDARY_CFLAGS`) disables the
*size/call-count heuristics* that pull a `static` sibling in
(`-fno-inline-functions -fno-inline-small-functions
-fno-inline-functions-called-once -fno-partial-inlining -fno-ipa-icf
-fno-ipa-sra -fno-ipa-cp`) while leaving `-finline` alone, which is what
honours the `inline` keyword. Placement is then made explicit rather than
inherited: `-ffunction-sections` plus a link script that puts
`*(.text.<symbol>)` first at the original VA, `.rodata` next, and every sibling
after that — so the executable extent handed to the emulator is exactly the
target function, and a merged unit's siblings are external boundaries, oracled
exactly as the shipped image's `bl` to them is.

**On the ugliness of the boundaries — stated plainly.** These modules were
formed by link-order adjacency (stage 03) and call cohesion (stage 09), not by
design. `unsorted` is a module in name only: 50 TUs and 167 functions with no
shared responsibility, and 32 of its files have no module-map row at all.
`lib/` is 482 functions of recovered newlib, libm, liblc3, nrfx and Bluetooth
host code that happen not to belong to an application subsystem. `sensors` is
three genuinely different things (`imu`, `input`, `power`) that only stage 09's
submodule split keeps apart. A test suite cannot fix that, and it should not
pretend to: what it *can* do is make a later re-cut of the boundaries safe,
which is the actual point.

---

## 4. The pass criterion, stated exactly

`tools/modtest/core.py:observable_key`. Two candidate runs of the same fixture
agree when these are equal:

* the **ABI return value**, and only the registers the ABI defines as the
  result — `void` compares nothing, `i32` compares r0, `i64` compares r0:r1,
  `f32` compares s0 with NaN payload canonicalised, `f64` compares s0:s1;
* whether the function **returned** at all (or faulted, and then: same fault
  class and same trace prefix);
* the **number of external calls**;
* the **sha256 of the complete ordered event trace** — every nRF5340 MMIO read
  (address, width, value), every non-stack memory write (address, width,
  value), and every external call with its AAPCS argument registers, in order;
* **semantic call-target identity**: wherever the compiler exposed a callee
  whose original VA is known, the ordinal-matched original call must have gone
  to that same VA. Without this a candidate could call the wrong same-ABI
  dependency and still match the trace.

Deliberately **not** compared: instruction count, cycle count, code size, stack
traffic, register allocation, the text offset at which a fault occurred, and
NaN payloads. Those are codegen, not behaviour. Stack writes are excluded
because register spill layout is not observable; pointers into read-only flash
compare by their *content* when they are complete printable NUL-terminated
strings, so an inlined literal is not a false failure.

---

## 5. The harness

`tools/modtest/` (new, uncommitted). Run everything as
`PYTHONSAFEPATH=1 .venv/bin/python tools/modtest/cli.py <cmd> app [symbols…]`.

```
index.py     symbol -> (tree, TU, original VA), by PROVENANCE BANNER not path
core.py      golden/candidate execution, the pass criterion, compilation,
             true extent, coverage instrumentation
generate.py  coverage-guided fixture search over 7 input dimensions
mutate.py    source mutation engine (the anti-vacuity control)
cli.py       gen / run / grade / index
```

Vectors live in `recon/tests/vectors/<core>/<module>/<symbol>.json`.

### The seven fixture dimensions, and why each exists

| # | dimension | why it is there |
|---|---|---|
| 1 | seeded argument vectors (`emu.make_args`) | already boundary-biased by AGENTS.md #1 |
| 2 | CFG-recovered per-argument selector values | reuses `cfg_verify.selector_values` |
| 3 | the **whole** `emu.FLOAT_POOL` swept through s0 | AGENTS.md #1b; eight samples of a 66-entry pool visit most branch domains exactly once |
| 4 | **absolute memory** — every global the literal pool names, over a value ladder | the dimension `cfg_verify` structurally lacks (§51.1.1) |
| 5 | **callee return values** — all-calls and one-call-at-a-time | see below; the largest single effect measured in this pass |
| 6 | global × callee-result **combinations** | a predicate needing both operands set |
| 7 | architectural mode (thread / handler), when the body reads IPSR | |

**Dimension 5 is the finding.** `emu`'s oracle returns `sha256(ordinal)` — a
large arbitrary word — so every `== 0`, `< 0` or small-enum test on a callee
result goes exactly ONE way for every fixture. This is AGENTS.md finding #1 one
level out: the blind spot moves from the argument bank to the *return* bank.
Measured, on the same code, before and after adding it:

```
                                 coverage before   after
fuel_gauge_update  (1,064 B)        20/319   6 %   ->  see below
opt3001_read_lux_raw                12/17   71 %   ->  17/17  100 %
mark_master_or_low_battery_flag      6/14   43 %   ->  13/14   93 %
opt3007_get_max_lux                 18/53   34 %   ->  44/53   83 %
```

**Dimension 6** then took `fuel_gauge_update` from 39/338 (12 %) to
**160/338 (47 %)**: its live predicate compares a 64-bit uptime (a callee
result) against a stored timestamp (a global), and no one-dimensional fixture
can make that comparison go both ways.

### Four harness defects found and fixed during the pilot

Each was found because a test failed identically on BOTH trees, which is the
signature of a harness artefact rather than a refactor regression.

1. **`-fno-inline` destroys the reconstruction's notation.** The obvious way to
   stop a merged TU inlining its siblings turns `static inline float F(uint32_t)`
   bit-casts into real calls: golden `ncalls=0`, candidate `ncalls=16`,
   `__ieee754_asinf` FAIL 0/5 on both trees. Replaced by heuristic-only
   inlining suppression (`core.UNIT_BOUNDARY_CFLAGS`).
2. **Missing per-callee ABI arity.** Without `call_arity_by_target`, `emu`
   compares four argument registers at every call site whatever the callee's
   real arity, so caller scratch in r1–r3 fails a correct candidate. All 42
   `opt3001_read_lux_raw` cases failed at event 0 on this alone.
3. **Missing linker pins.** The symbolized trees spell a global by NAME;
   `recon/symbols/g1_app_globals.ld` is what binds `g_opt3007_chip_ready` to
   0x20018da1. Without the fragment the name is undefined, the harness's own
   stub generator turns it into a *function*, and a fixture that drives the
   global has no effect at all. Also needed: the transitive closure of pin
   expressions, and a fallback to the `/* @0x… */` address comment in
   `g1_app_symbols.h` for pins whose right-hand side is defined in an
   integration TU the harness does not link (`g1_log_use_alt_sink`) — without
   which `opt3007_get_max_lux` and `fuel_gauge_update` did not LINK.
4. **`mnemonic.startswith("bl")` also matches `blt`.** Twice, in two different
   walkers. `blt`/`bls`/`ble` are conditional branches; treating them as calls
   made the CFG walker fall through instead of following the branch. Effects:
   the coverage denominator was deflated, and `true_extent` stopped one
   instruction short of `fuel_gauge_update`'s own tail block at 0x10FBE — so
   the golden run recorded **60 phantom "calls"** to a block that is part of
   the function, and the reconstruction (which spells it inline) "failed".
   That one is worth restating: **a text-pattern bug in the harness
   manufactured a reconstruction defect that does not exist.** It is the sixth
   defeat of prefix/text-anchored parsing recorded in this project.

### Three equivalences the pass criterion applies, each measured

* **read-only pointee content** (inherited from `emu`): a pointer to an
  immutable NUL-terminated printable string compares by its bytes, not by its
  flash address, so an inlined literal is not a false failure.
* **stack-frame origin** (`core.normalise_events`): a pointer to a stack local
  is recorded as its signed delta from the first stack address in the trace.
  Measured on `fuel_gauge_update`: original passes (0x2007EF3C, +4, +8) at call
  ordinal 2, candidate passes (0x2007EF48, +4, +8) — same record, different
  frame origin. Relative structure is preserved exactly, so passing a different
  local, or the same two in the opposite order, still fails.
* **independent write order** (`core._sort_independent_write_runs`): a maximal
  run of writes to *distinct*, *non-MMIO* addresses with no intervening call or
  MMIO access is order-normalised. Measured: the shipped code stores 0x20007B70
  then 0x20007B74; the reconstruction stores them in the opposite order. Only
  calls and MMIO observe anything in this model, so between two of them the
  order of two different RAM stores is instruction scheduling. A wrong value, a
  wrong address, a missing or extra write all still change the multiset.

### One class of fixture is DROPPED rather than failed

`generate.tail_branch_entries`: when the shipped function *branches* (not
`bl`s) to an address that the Ghidra catalog registers as a separate function
entry, the catalog's function boundary and the reconstruction's disagree, and
no fixture reaching that block can decide anything. Such fixtures are dropped,
and the count and the disputed targets are written into the vector file
(`search.dropped_extent_dispute`, `search.extent_dispute_targets`). A suite
that emits a false FAIL is worse than one that emits none, because it invites a
"fix" to correct code.

---

## 6. Module-scope testing: what it buys, and where it stops

**Evaluated, and the answer is "not yet, and here is the concrete blocker."**

`emu.Runner(internal_code_regions=…)` accepts additional original byte ranges
that count as part of the unit rather than as oracled calls. Widening the
oracle boundary from a function to a module is therefore mechanically possible:
take the module's call graph, mark every intra-module callee's original bytes
internal, and let only cross-module calls be oracled.

What that would buy is real — an intra-module call chain would be exercised end
to end instead of oracled at the first hop. What stops it, in order:

1. **The instruction cap.** `emu` defaults to 200,000 instructions per trial.
   A single application entry point that runs a real intra-module chain reaches
   that easily; `ipc_rpmsg_backend_register` (404 bytes) already only reaches
   26 of 145 CFG instructions because five of its fixtures terminate early.
2. **A module entry point is usually a thread body or a callback**, i.e. it is
   entered from an ISR or from the scheduler, neither of which exists here.
   `key_event_thread`, `imu_fusion_thread`, `click_event_dispatch_loop`,
   `ipc0_ept_recv` are all in this class.
3. **Intra-module calls are not the interesting boundary anyway.** The modules
   were cut by link adjacency and call cohesion, so "inside the module" and
   "inside one logical operation" are not the same set. Making the ipc module's
   internal calls concrete does not make the *protocol* concrete, because the
   peer is the net core across rpmsg.

The pragmatic conclusion recorded here: **per-function golden vectors,
aggregated per module, are the unit of work.** Module-scope emulation is a
worthwhile second phase for the handful of modules with a synchronous,
non-threaded entry point (`storage`, parts of `lib`), and it should be attempted
only after per-function coverage is banked, because it needs the same fixtures.

---

## 7. Pilot results  — ⚠️ SUPERSEDED BY §18

> These numbers were produced with a harness that still had SEVEN defects in
> it (§11, §14, §16, §17).  They are kept because the sequence is the evidence
> that each defect was found by measurement rather than by inspection.  **The
> authoritative results are §18.**

Three modules of deliberately different character. Every number below is from a
command run in this pass. `canonical` = stage 00 (flat, one function per file),
`refactored` = stage 09 (modular, merged TUs).

### 7.1 `lib` — pure, leaf, hard-float

```
symbol             va          size  cases  coverage        canonical      refactored
__ieee754_asinf    0x00075f88   396    34   107/107  100%   OK(34/34)      OK(34/34)
```

### 7.2 `sensors` — hardware-dependent (I²C, ambient-light, fuel gauge)

```
symbol                            size  cases  coverage       canonical     refactored
opt3001_read_lux_raw                46     3    17/17  100%   OK(3/3)       OK(3/3)
opt3007_get_max_lux                140    43    44/53   83%   OK(43/43)     OK(43/43)
mark_master_or_low_battery_flag     32     3    13/14   93%   OK(3/3)       OK(3/3)
i2c_read_reg16_be                   74     3    23/31   74%   OK(3/3)       OK(3/3)
array_max_skip_nan_a                96    44    32/32  100%   OK(44/44)     OK(44/44)
array_max_skip_nan_b                98    44    33/33  100%   OK(44/44)     OK(44/44)
floorf                               6    30     2/2   100%   OK(30/30)     OK(30/30)
fuel_gauge_update                 1196    43   160/338  47%   FAIL(42/43)   FAIL(42/43)
```

### 7.3 `ipc` — stateful/protocol, and the most-merged module (36 % single-function)

All 47 symbols. Aggregate **885 / 1194 CFG instructions = 74.1 %**; median
per-symbol coverage **91 %**; **21 of 47 at 100 %**.

Lowest coverage, which is where the honest reading is:

```
ipc_rpmsg_backend_register     26/145   18%   (404 B, 5 fixtures survive to the end)
st25dv_mailbox_poll_message    16/69    23%   (poll loop; needs a peripheral EVENT)
pt_comm_transport_write        21/23    91%   (but only 14 fixtures)
ipc0_ept_recv                  35/51    69%
send_response_data_to_msgqueue 29/49    59%
```

### 7.4 AGREEMENT: the two trees agree on every symbol tested

**On all 56 symbols across the three modules, `canonical` and `refactored`
produced byte-identical observable keys on every fixture.** Where a test fails,
it fails identically on both. That is the pilot's principal result about the
refactor: on the code these vectors cover, **stages 00 → 09 changed no
observable behaviour**, and that conclusion now rests on an oracle taken from
the shipped image rather than on a 30 µs-sensitive Renode capture.

It is worth being precise about what that does and does not say. It says the
refactor is behaviour-preserving *on the covered fraction*. `ipc` is 74 %
covered, so 26 % of its shipped instructions are not spoken for by any of this.

### 7.5 DIVERGENCE: `fuel_gauge_update`, one fixture, on BOTH trees

This is the pilot's one live finding, and because it reproduces identically on
the canonical tree it is **not** a refactor regression — it is a property of the
reconstruction itself.

```
fixture   combo-2-0   all 7 literal-pool globals = 0xffffffff,
                      all callee returns = 0
expected  return, ncalls=21, r0=1056964608 (0.5f)
actual    return, ncalls=21, r0=1056964608 (0.5f)   -- identical
diverges  call ordinal 13, target 0x0000d848 = __extendsfdf2 (soft float->double)
            shipped     r0 = 0x38D5B3F3  =  1.0193735e-4
            candidate   r0 = 0x8781____  = -2.0114315e-34
```

Everything else in the trace matches, including the return value and all 21
calls. `-ffp-contract=off` **is** correctly derived and applied for this body
(it is one of the five unfused application bodies named in AGENTS.md #1b), so
the difference is not a contraction artefact. The two writes at 0x20007B70 /
0x20007B74 that also differed were an ordering difference and are now
normalised away (§5); this one is a **value** difference in a float that the
reconstruction feeds to a soft-float helper.

Status: **candidate reconstruction defect, not yet root-caused.** It is
adjacent to the known-open float-path defect `battery_model_state_update`
(`FUN_0000c358`, AGENTS.md "STILL OPEN"), and `fuel_gauge_update` is in the same
battery/fuel-gauge chain — but that adjacency is a lead, not a conclusion, and
this pass did not chase it. The fixture is extreme (all globals 0xffffffff)
and it is possible that no production state reaches it. What is certain is that
under an input state both programs accept, they compute different numbers.

---

## 8. The module-by-module plan a fleet can execute

### 8.1 The loop, per module

```bash
V="PYTHONSAFEPATH=1 /Users/freedomcoder/Projects/G1disasm2/.venv/bin/python"
$V tools/modtest/cli.py gen   app --module <m> --budget 700    # golden vectors
$V tools/modtest/cli.py run   app --module <m>                 # both trees
$V tools/modtest/cli.py grade app --module <m> --mutants 24    # kill rate
$V recon/tests/test_modtest_pilot.py                           # + negative controls
```

`gen` writes `recon/tests/vectors/app/<module>/<symbol>.json`. Those files are
the deliverable: they are reviewable, they are diffable, and they carry the
sha256 of the image the expectations came from, so a regenerated vector against
a different image is visible rather than silent.

### 8.2 Acceptance for a module

A module is **done** when all four hold, and each is a number in the run log,
not a judgement:

1. `run` reports `canonical == refactored` on every symbol (agreement), and
   every disagreement is either root-caused to a real behaviour change or the
   refactor is reverted;
2. aggregate CFG-instruction coverage **≥ 70 %**, with every symbol below 50 %
   individually listed and explained (a poll loop, an ISR path, a DMA
   completion — the reasons in §1 are legitimate; "we did not try" is not);
3. mutation kill rate **≥ 70 %** on the module, with every survivor either shown
   to be an equivalent mutant (as two of `__ieee754_asinf`'s were, measured over
   200,000 inputs) or converted into a new fixture;
4. `recon/tests/test_modtest_pilot.py` reports **0 survived negative controls**
   on that module's symbols.

Nothing here asks for byte identity, image size, or a Renode capture.

### 8.3 Ordering, and the expected difficulty per module

Ordered so that the harness is exercised on easy code first and the hard cases
arrive with the fixture library already built. Function counts are measured
(§0); the difficulty column is a prediction and should be corrected in place as
each module lands.

| order | module | funcs | expected coverage | why |
|---|---|---:|---|---|
| 1 | `lib` | 482 | **high (85–100 %)** | newlib/libm/liblc3/nrfx leaves; pure, argument-driven. Also the one module where an EXTERNAL oracle exists (§9). Split into 4–6 fleet shards. |
| 2 | `sensors` | 94 | high for `power`, medium for `imu`, low for `input` | `input` is thread/ISR-driven |
| 3 | `storage` | 85 | medium-high | flash/settings; synchronous, argument-driven; a good second candidate for module-scope emulation |
| 4 | `ipc` | 47 | **74 % measured** | done in this pass; the template for the protocol modules |
| 5 | `analytics` | 14 | high | small, arithmetic |
| 6 | `esb` | 24 | low-medium | radio; most entry points are ISR callbacks |
| 7 | `display` / `gui` / `ui` | 89 / 57 / 65 | medium | framebuffer writes are ordinary memory writes and compare well; the render loops are long and will hit the instruction cap |
| 8 | `audio` | 137 | medium | codec kernels are pure (good); the PDM/DMA paths are not reachable |
| 9 | `notify` | 99 | medium | ANCS/notification state machines; heavy callee-result dependence, so dimension 5 matters most here |
| 10 | `core` | 142 | medium-low | scheduler/threads; much of it is unreachable without an RTOS |
| 11 | `ble` | 99 | low-medium | host stack; deep call chains, oracled at the first hop |
| 12 | `unsorted` | 167 | unknown | **do this LAST and use the result to re-cut it.** 50 TUs with no shared responsibility and 32 files with no module-map row. Once every other module has vectors, the symbols that remain here can be assigned by measured call affinity rather than by link adjacency — and the vectors make that re-cut safe, which is the whole point of building them. |

Net core (`recon/symbolized/net`) is untouched by this pass. The harness is
core-parametric (`core_ctx("net")`, `NET_CODE_BASE`, `net_extract`) and should
work, but **it has not been run once on net** and must not be assumed to.

### 8.4 What a fleet agent must NOT do

* **Never edit a source to make a test pass.** A divergence is a finding. Route
  it to a human with the fixture id and the first divergent event.
* **Never regenerate a vector to make a test pass.** Regenerating changes the
  expectation, which is the one thing that must not move. If a vector is
  genuinely wrong (a harness bug — four were found in this pass), fix the
  harness and regenerate *everything*, and say so.
* **Never report a pass without its coverage number.** A green run at 5 %
  coverage licenses restructuring it cannot see, which is worse than no suite.
* **Never cite `cfg_verify`.** It is blind in both directions on this code
  (our_boot_bringup.md §51.1.1, §51.4). This harness *uses* two of its
  functions — `selector_values` for fixture dimension 2 and `core_ctx` for
  callee ABI — and that is the only role it has here.

---

## 9. What this suite will NOT catch — the honest complement

> §9E is superseded twice: by §13E′ (capture built) and then by §16.1 (capture
> disabled by default, so §9E is back in force at full width).

Coverage of the pilot is **885/1194 = 74.1 %** for `ipc` and **100 %** for the
two `lib`/`sensors` leaves that reached it. The complement of those numbers is
this list. Everything here is a defect class that can exist in the tree and
pass every test in this suite.

**A. Everything outside the covered fraction.** 26 % of `ipc`'s shipped
instructions, 53 % of `fuel_gauge_update`'s, 82 % of
`ipc_rpmsg_backend_register`'s. Concretely unreached: peripheral poll loops
waiting for an EVENTS register (`st25dv_mailbox_poll_message`, 23 %), error
branches behind a callee that no oracle value produces, and the second half of
long initialisers.

**B. Anything that needs a second execution context.**
* interrupt handlers, and every path only an ISR reaches;
* thread bodies, `k_work` handlers, and everything about scheduling;
* races, priority inversion, lock ordering, re-entrancy — a suite that runs one
  function on one core with no preemption cannot see any of it;
* the two cores talking to each other. `ipc` is tested as *what the app core
  writes*, never as *what the net core then does*.

**C. Anything that needs time or DMA.** Timeout behaviour, retry backoff,
watchdog interaction, a SPIM/TWIM transfer actually delivering bytes. The
harness models "the driver was asked to start a transfer", never "the transfer
completed".

**D. Callee behaviour.** Every dependency is an order-keyed oracle. If the
reconstruction calls the *right* function with the *right* arguments in the
*right* order, this suite is satisfied — even if the callee itself is wrong.
Callees are covered only by their own vectors, and only to their own coverage
fraction.

**E. A defect that shifts the single stack pointer a function passes.**
Measured, in this pass. `core.normalise_events` anchors stack addresses on the
first one seen; when a function passes exactly one stack pointer, moving it
moves the anchor with it and the delta stays 0. A `+ 2` changed to `- 2` on
`(char*)&uStack_c + 2` in `opt3001_read_lux_raw` **survived** the mutation
grading for this reason. The fix is to capture pointee CONTENT at call
boundaries (`emu` has the machinery, `stack_objects`, but only for
hand-reviewed sites); it is not built.

**F. Numeric defects below the observable precision.** Measured: of five 1-ULP
perturbations of `__ieee754_asinf`'s polynomial coefficients, over 300,000
float32 inputs drawn from the branch's reachable domain, the result differs on
**0**, **1**, **24**, **518** and **5,358** of them. The first is an equivalent
mutant that no test can kill; the next three need 10²–10⁵ fixtures. A 1-ULP
coefficient error in a polynomial kernel is effectively invisible to any
fixture-count-bounded suite. **The right instrument for this class is an
external oracle** — comparing `lib`'s recovered newlib/libm bodies against the
upstream implementation — which is independent evidence and is not built here.

**G. Build-level and link-level properties.** Section sizes, symbol placement,
duplicate globals, pin correctness, whether the image still fits, whether it
links at all. Those are what `full_link.py`, the pin gates and the size gates
are for, and this suite replaces none of them.

**H. Timing.** Entirely, deliberately. If a restructuring shifts I²C traffic by
30 µs, this suite is silent — which is the point, and also means it cannot
replace the R7 gate for a release decision.

**I. Whether the reconstruction is the RIGHT program.** The oracle is the
shipped image's *behaviour under emulation*. A place where our Unicorn model
and real silicon disagree — an unmodelled MMIO side effect, an errata, a
cache/write-buffer effect — is invisible to both sides equally.

**J. Anything about code QUALITY.** This suite says a restructuring did not
change behaviour. It says nothing about whether the restructuring was an
improvement. 438 of 660 module TUs are still single-function; no test can tell
you that is bad.

---

## 10. What was NOT done in this pass, and why

* **No net-core run.** The harness is core-parametric but has never been
  executed with `core="net"`. Do not assume it works.
* **19 modules not piloted.** By design — this was an architecture-and-pilot
  pass. `lib` was sampled at ONE symbol, not swept.
* **Module-scope (multi-function) emulation not built.** Evaluated and
  deferred, with reasons, in §6.
* **The `fuel_gauge_update` divergence not root-caused.** Reported with its
  evidence in §7.5; chasing it is a separate piece of work.
* **No external-oracle tier for `lib`.** Identified in §9F as the right
  instrument for the one defect class emulation cannot reach; not built.
* **Pointee-content capture at call boundaries not built.** This is the fix for
  blind spot §9E and is the single highest-value next increment to the harness.
* **`cfg_verify --self-test` not run.** It is already broken at HEAD (AGENTS.md)
  and this work does not touch its assertions.
* **Renode not run.** Explicitly out of scope for this phase.
* **Nothing committed.** The tree is left dirty; §11 lists exactly what changed.

---

## 11. Second iteration: what the `ipc` sweep found, and the fifth harness defect

Running all 47 `ipc` symbols against both trees produced **three tree
disagreements**. All three were investigated. **Two were harness defects and
one was a testability difference; none was a behaviour change.** This is worth
recording as a method note: a disagreement is a hypothesis, not a result, and
the first thing to test is the harness.

**5. The candidate's own `.rodata` was shadowed by the shipped image.** The
candidate is linked at the ORIGINAL VA, so its `.rodata` lands a few hundred
bytes into the shipped flash image's address space. `emu.Runner` consults the
shipped image FIRST when resolving a read-only pointee by content — correct for
its differential use, wrong here — so an inlined C string literal resolved to
whatever the shipped image happens to hold at that address:

```
ipc0_ept_recv            golden ('RO', b'%s(): NOT MATCH(cmd=%x)! ipc_receiver_index: %d, …')
                      candidate ('RO', b'Tu')
global_ipc_service_send  golden ('RO', b'global_ipc_service_send')
                      candidate ('RO', b' Tu')
```

`b'Tu'` is stub code bytes. Fixed by giving the candidate an own-tail extent
that is consulted **before** the image (`core.run_candidate`).

**6. Stage 07's `static` makes a symbol un-emittable in isolation.** A `static`
function that no other member of its TU calls is simply not emitted by GCC, so
`ipc_rpmsg_backend_register` was *untestable* in the refactored tree and
testable in the canonical one — a difference in testability that reads as a
difference in behaviour. Fixed by `core._expose_target`, which drops `static`
from the target function's own definition only, anchored on the definition
(`static … <symbol> ( … ) {`) so a declaration, a static variable, or a
sibling's `static` is never touched, applied at most once, with the count
returned so a silent no-match is visible. Linkage is not part of the pass
criterion (§4); the body, the constants and the calls are untouched.

**7. A golden vector must not freeze a capped run.** `ipc_rpmsg_backend_register`
produced a golden with `ncalls = 25000, returned = false` — an unbounded loop
truncated at the instruction budget. Any candidate whose loop costs a different
number of instructions per iteration fails that (the candidate reached 22,222),
and it means nothing. `emu.compare` already calls such a trial inconclusive;
`generate.select` now drops them and records the count
(`search.dropped_instruction_cap`).

### 11.1 The measurement that changed the design: mutation grading of merged TUs

Grading the first ten symbols produced two results at **0 % kill rate with
100 % coverage** — the exact failure mode this design exists to prevent. Two
separate causes, both found and both fixed:

**A. Mutants were landing in SIBLING functions.** A stage-09 unit holds up to
39 functions and the mutation engine was mutating the whole file, so most
mutants perturbed code the target's vectors cannot constrain and were counted
as survivors. `mutate.member_span` now confines mutants to the target's own
block, delimited by provenance banners.

```
                              before   after
ipc_read_u16_field             0/16    13/16   87%
dev_send_cmd16_payload         3/16    11/16   79%
st25dv_write_reg_pair          0/16     7/15   47%
```

**B. Stack-local records passed by pointer were completely invisible.** This is
the important one. A great deal of this firmware builds a small record in a
stack local and passes its address:

```c
struct {...} local_20;  local_20.a = 2; … local_20.e = 7;
ipc_transport_ops_dispatch(param_1, &local_20, 2, param_2);
```

`emu` records the call's argument *registers*, so the trace contains the
pointer; `normalise_events` then replaces it with a frame-origin-independent
offset. **Nothing observed what was in the record.** `ipc_send_len_prefixed_packet`
had 100 % instruction coverage, 41 fixtures, and a **13 %** kill rate: every
perturbation of every field constant survived.

Built, rather than merely documented: `core._CoverageRunner` now captures, at
every `bl`/`blx` inside the unit, the bytes of `[ptr, ptr+48)` **that the run
actually wrote**, for each of r0–r3 that points into the stack window, keyed by
offset from the pointer. Content keyed by offset is independent of frame
layout, of field store order and of store width; excluding bytes the run never
wrote keeps uninitialised frame padding — the one thing that legitimately
differs between two compilations — out of the comparison.

Three corrections were needed to make it sound, each measured:

* **a record may hold a pointer to another stack local** (`local_20.p = &local_24`),
  whose raw value is frame layout. Those aligned words are blanked. Without
  this, `ipc_send_len_prefixed_packet` failed 41/41 on **both** trees;
* **the pre-computed call-site set comes from a linear disassembly** and can
  misalign inside a literal pool; the instruction at the PC is now re-checked
  before anything is recorded;
* **a capture is only COMMITTED when control actually leaves the unit.** A run
  that builds a record and then faults before the call has passed it to nobody.
  `i2c_read_reg16_be` faults on a vtable load; the shipped code faults before
  filling the record and the reconstruction fills it first, with identical fault
  class and identical event traces. Uncommitted, this failed 2 of 3 fixtures on
  both trees.

Result: `ipc_send_len_prefixed_packet` **13 % → 100 %** kill rate,
`i2c_read_reg16_be` **19 % → 100 %**, both still passing on both trees.

**This supersedes blind spot §9E**: the pointee-content capture that section
described as "not built" is now built. What remains invisible is narrower and
is restated in §13.

---

## 12. Cost

Measured on this machine, single process:

* `gen` is the expensive step: it runs ~110–210 candidate fixtures of the
  ORIGINAL per symbol. Roughly 15–60 s per symbol depending on size and call
  count. It is done ONCE per symbol and the result is frozen to JSON.
* `run` was originally recompiling the candidate translation unit for **every
  fixture** — 47 symbols × ~40 fixtures × 2 trees = 3,760 compiles for one
  module. A compile cache keyed on (tree, symbol, VA, flags, mutant digest)
  reduces that to 2 compiles per symbol. This matters more than anything else
  in the harness for fleet throughput.
* `grade` compiles once per mutant (16–40 per symbol) and is the second-most
  expensive step; run it per module, not per commit.

All of it is CPU-only, needs no hardware, no Renode, and parallelises by
symbol, so a fleet can shard a module by symbol with no shared state — the
vector files are the only output and they never collide.

---

## 13. Blind spots, restated after the pointee-content work

§9 was written before §11. These supersede §9E and refine §9A–D; everything
else in §9 stands unchanged.

**E′ (replaces E).** Stack-record CONTENT is now compared. What is still
invisible in a stack record:

* **a pointer field aimed at the wrong stack object.** Words holding a stack
  address are blanked, because their raw value is frame layout. A record whose
  `p` field points at the wrong local passes.
* **bytes beyond 48 from the pointer** (`core.STACK_ARG_WINDOW`). A larger
  record is compared only in its first 48 bytes.
* **fields the run never writes.** If both the shipped code and the
  reconstruction leave a field uninitialised, agreeing to leave it
  uninitialised is all that is checked — which is correct, but it means a
  "should have initialised this" defect is invisible.
* **records reached only through r4–r11 or the stack**, not r0–r3. Only the
  four AAPCS register arguments are scanned.

**A′.** The coverage denominator is CFG-reachable instructions of the shipped
function, unioned with everything any fixture actually executed. It cannot be
inflated by an incomplete static walk, but a `tbb`/`tbh` whose table no fixture
indexes into contributes nothing to either side of the ratio, so a switch case
that is never reached is also never counted as missing. `search.unresolved_indirect`
in each vector file is the count of branch targets the walker could not resolve
and is the honest flag for this.

**D′.** Callee behaviour remains unobserved (§9D) — but the *arguments* a callee
receives are now observed much more strongly: registers, stack-passed words,
read-only string content, and (new) the content of stack records they point to.
What is still unobserved is what the callee then does.

**K (new).** Anything that depends on the ORDER of two stores to different RAM
locations. `core._sort_independent_write_runs` normalises those runs away. The
conditions are strict — no intervening call or MMIO access, all addresses
distinct, none in an MMIO window — so a wrong value, a wrong address, a missing
or an extra write all still fail. But if two RAM locations are genuinely
order-sensitive because something outside this model observes them (a DMA
engine reading a descriptor, the other core reading shared SRAM), that ordering
is not checked.

**L (new).** Fixtures dropped by `search.dropped_extent_dispute` and
`search.dropped_instruction_cap` are not tested at all. Both counts are written
into every vector file. A symbol whose entire fixture set was dropped shows
`cases = 0` and coverage 0 %, which is visible — but only if someone reads the
number, which is why §8.2 makes coverage a gate rather than a footnote.

---

## 14. Third iteration: making the pointee capture sound, and two performance defects

### 14.1 The pointee window was unsound, and the fix is instruction-classified

The first cut of the stack-record capture (§11.1 B) took a fixed 48-byte window
from the pointer. That window **runs past the object into the frame's own saved
registers**, whose position relative to a local differs between the shipped code
and any recompilation. Measured, immediately, on the very next full sweep:

```
ipc_read_u16_field   `unsigned short local_14` -- a TWO-byte local
  golden    offsets 0..19 written: (0,0)(1,0)(2,1)(3,32)(4,4)(5,0)…(16,1)(18,31)
  candidate offsets 0..17 written: (0,0)(1,0)(2,4)(3,0)(4,0)…(14,1)(16,31)
  verdict   42 of 43 fixtures FAILED, identically on BOTH trees
```

Offsets 2..19 are r4–r7/lr in the shipped frame and a different arrangement in
the candidate's. So a fixed window is not sound at any size — even four bytes
fails here, because the saved-register region begins at offset 2.

**The fix classifies the STORE, not the address.** A stack byte written by
`push` / `vpush` / `stmdb sp!` is frame bookkeeping and is never pointee
content; the write hook now reads the PC, disassembles the instruction
performing the store, and excludes those bytes. After it:

```
ipc_read_u16_field            golden [(2, ((0,0),(1,0)))]   candidate identical
ipc_send_len_prefixed_packet  golden 20-byte record         candidate identical
                              (the P-blanked pointer word, then 2,0,0,0,0,…,7)
i2c_read_reg16_be             golden []                     candidate []
```

The 2-byte local is captured as exactly two bytes and the 20-byte record as
exactly twenty. This is the version the pilot numbers below were produced with.

It is worth being explicit that this was found by the suite failing, not by
inspection, and that the signature — **identical failure on both trees** — is
what identified it as a harness defect rather than a refactor regression, for
the seventh time in this pass.

### 14.2 Two performance defects, both order-of-magnitude

* **Catastrophic regex backtracking.** `_expose_target`'s first spelling was
  `static\s+((?:\w+|\*|\s)*?\bNAME\s*\(`. On a merged TU that backtracks
  catastrophically: **154 seconds for one symbol** of `g1_ipc_06.c`, so its ten
  members cost 25 minutes of pure regex. Replaced by a linear scan: **0.000 s**,
  and the whole compile+link is now 0.11 s. Roughly 1,400×.
* **A per-instruction Python callback.** The coverage hook was registered over
  the whole body and fired once per emulated instruction — more expensive than
  the emulation it observes. Coverage is only needed while GENERATING vectors
  (it is measured on the shipped bytes), so replay now sets
  `track_coverage=False`, and the stack-record hooks are registered
  **per call site** (`begin=site, end=site`) instead of over the body.

Neither is a correctness issue, but both are the difference between a fleet
being able to run this and not.

---

## 15. Files changed (nothing committed)

New, untracked:

```
tools/modtest/__init__.py
tools/modtest/index.py       symbol -> (tree, TU, original VA), by provenance banner
tools/modtest/core.py        oracle, pass criterion, compilation, extent, coverage,
                             stack-record capture
tools/modtest/generate.py    coverage-guided fixture search (7 dimensions)
tools/modtest/mutate.py      mutation engine + member-span confinement
tools/modtest/cli.py         gen / run / grade / index
recon/tests/test_modtest_pilot.py    executable pilot suite + negative controls
recon/tests/vectors/app/{ipc,sensors,lib}/*.json   golden vectors
recon/analysis/test_architecture.md  this file
```

Modified: **none.** No source in any tree was edited; the mutation engine
compiles from an in-memory override and never writes to the repository.
`tools/parity/emu.py`, `tools/cfg_verify.py` and every refactor stage are
untouched — `emu` is used as a library (its `Runner`, `make_args`,
`FLOAT_POOL`, `ReadOnlyPointees`, `_bytes_extent`, `_firmware_readonly_extent`)
and `cfg_verify` for exactly two functions (`selector_values`, `core_ctx`).

One observation about the working tree, reported because it is a change I did
not make: at the start of this session `git status` showed
`recon/refactor/transforms/t04_cohesive_tu.py` and `t09_call_cohesion.py` as
modified. They are clean now, and nothing in this pass touched them.

---

## 16. Fourth iteration, and the retreat that has to be recorded

Running the full sweep again with the sound pointee capture produced **five
more classes**, all of which failed identically on both trees:

**8. A STORED FUNCTION POINTER is the candidate's stub address.**
`register_ipc_service_context` writes `0x25B39` — a Thumb function address —
into a global; the candidate wrote its own stub's address, and all 42 fixtures
failed. `emu` already resolves this identity for *call targets*
(`oracle_target_map`); the same map is now applied to values appearing anywhere
in the candidate's event trace, preserving the Thumb bit.

**9. A merged TU's SIBLINGS are defined, so they were missing from that map.**
`register_ipc_service_context` then passed on the canonical tree (where the
callee is an `extern` stub) and still failed 42/42 on the refactored one (where
it is a sibling in `g1_ipc_cc03.c`). Fixed by mapping every banner-named
`STT_FUNC` in the linked object back to its original VA.

**10. Zephyr headers.** Two `ipc` TUs `#include <zephyr/sys_clock.h>`. Adding
`~/ncs251/zephyr/include` and `~/ncs251/nrf/include` gets further but then needs
the build's generated `autoconf.h` (`CONFIG_SYS_CLOCK_TICKS_PER_SEC`). That file
is **build-specific**, and force-including a foreign build's copy would change
the codegen of inline Zephyr helpers and could manufacture divergences. It is
therefore **opt-in** (`G1_AUTOCONF=<path>`), and without it those TUs report
`CCFAIL`, which is visible and honest. No G1-specific `autoconf.h` exists on
this machine, so `send_response_data_to_ble` and `send_response_data_to_msgqueue`
are untested here.

### 16.1 THE RETREAT: the stack-record capture is now OFF by default

Correction to §11.1 and §13. The capture is real, it works, and it closes a
large blind spot — and I could not make it sound within this pass. The fifth
correction is the one that stopped it:

> The shipped code may reserve a stack slot with `push {r1}` while the
> reconstruction uses `str r1,[sp,#n]`. Correction 2 (§14.1) classifies the
> first as frame bookkeeping and the second as content, so
> `st25dv_read_area_size` captured **nothing** on the golden side and four
> bytes on the candidate's — **41 of 41 fixtures failed, identically on both
> trees, with byte-identical event traces.**

Both `push` and `str` are legitimate spellings of "put this value in a stack
slot"; distinguishing frame bookkeeping from object content by the store
instruction is a heuristic, and this is where it breaks. A sound capture needs
an object-extent model (which bytes belong to the pointee), which
`emu.stack_objects` provides only for hand-reviewed sites.

So `core.STACK_ARG_WINDOW` defaults to **0**. Enable with
`MODTEST_STACK_ARG_WINDOW=48`. The machinery, all four corrections and this
measurement stay in the tree for whoever builds the extent model. **Blind spot
§9E/§13E′ is therefore back in force**, at its full width:

> The CONTENT of a stack-local record passed by pointer is not compared.
> Measured cost: `ipc_send_len_prefixed_packet` — 100 % instruction coverage,
> 41 fixtures, **13 %** mutation kill rate. Every field-constant perturbation
> survives. This is the largest known hole in the suite and the highest-value
> next piece of work.

The principle this follows is the one stated in §5 and it is worth repeating,
because it is the reason for the retreat rather than a workaround: **a suite
that emits a false FAIL is worse than one with a known blind spot, because it
invites a "fix" to correct code.**

---

## 17. Fifth iteration: the inline-suppression rule was too broad

**11.** `UNIT_BOUNDARY_CFLAGS` originally suppressed inlining wholesale
(`-fno-inline-functions -fno-inline-small-functions
-fno-inline-functions-called-once`). That also stops the compiler inlining a
**file-local helper with no provenance banner** — which is *spelling*, not a
shipped function — so the candidate called helpers the shipped body has inline.
Measured: `__ieee754_atan2f` golden `ncalls = 0`, candidate `ncalls = 5`,
**FAIL 0/48 on both trees**; `__ieee754_expf` 25/37.

The precise rule is a property of the SOURCE, not of a compiler flag:

* a **banner-named** function is a separate function in the shipped image and
  must remain a call boundary → `__attribute__((noinline))`, injected by
  `core._mark_members_noinline`;
* an **unbannered** file-local helper is notation and may inline freely.

Only the interprocedural transforms that would merge or reshape a banner-named
function stay as flags (`-fno-ipa-icf -fno-ipa-sra -fno-ipa-cp
-fno-partial-inlining`). `__ieee754_atan2f`: **0/48 → 48/48** on both trees.

Two text-surgery defects had to be fixed to make that injection safe, and both
are the same family of error this project keeps finding:

* **`if (getNewsIndex(a)) {` satisfies "name ( … ) {".** Taking the FIRST `)`
  rather than the matching one identified an `if` condition as a definition and
  injected an attribute into the middle of another function's body, breaking
  the whole TU. Fixed with a balanced-paren scan plus a check that the text
  before the name is a return type rather than a statement opener.
* **`text.rfind("*/") + 1` points BETWEEN the two characters of the comment
  terminator**, producing `*__attribute__((noinline)) /`. It needs `+ 2`. The
  same off-by-one existed in `_expose_target`. That is the **seventh** defeat
  of character-level text anchoring recorded in this project, and the second in
  this pass.

---

## 18. ★ FINAL PILOT RESULTS — this section supersedes §7

Everything in §7 was measured with a harness that had seven defects in it.
These are the numbers from the final harness, run in one pass at the end of
this session. **139 symbols across three modules of deliberately different
character.**

### 18.1 Coverage of the SHIPPED instructions

```
module    symbols  covered/total CFG instructions   median   at 100%   fixtures
lib             5      420 / 448  = 93.8 %            0.98      2/5        165
ipc            47      901 / 1194 = 75.5 %            1.00     29/47      1,603
sensors        87    3,518 / 6,334 = 55.5 %           1.00     48/87      2,831
```

The median is 100 % in both large modules and the mean is dragged down by a
minority of long, call-heavy or poll-loop functions — which is the shape you
would expect and is exactly why the median and the aggregate are both reported.
`sensors` is the lowest because it contains the thread bodies
(`key_event_thread` 17 %, `imu_fusion_thread`), the long init sequences
(`lsm6dso_init_chip` 10 %) and the EKF (`fuel_gauge_update` 47 %).

### 18.2 Tree agreement — the pilot's principal result

**On all 139 symbols, `canonical` (stage 00) and `refactored` (stage 09)
produced identical verdicts.** Every symbol that passes, passes on both; every
symbol that fails, fails on both with the same fixture set and the same first
divergent event; every symbol that fails to compile, fails on both.

```
                    ipc      sensors    lib
both trees OK        44          75       5
both trees FAIL       1          11       1
both trees CCFAIL     2           1       0
trees DISAGREE        0           0       0
```

Within the covered fraction, **stages 00 → 09 changed no observable behaviour**
— and that conclusion now rests on an oracle taken from the shipped image
rather than on a 30 µs-sensitive Renode capture. That is the answer to the
question the owner asked.

Three tree disagreements appeared during the pass and **all three were harness
defects** (§11): the candidate's own `.rodata` shadowed by the shipped image,
stage 07's `static` making a symbol un-emittable, and a golden vector frozen
from a capped run. This is the method note worth carrying forward: **a
disagreement is a hypothesis, and the first thing to test is the harness.**

### 18.3 Candidate reconstruction findings — present on BOTH trees

Because they reproduce on the canonical tree, none of these is a refactor
regression; each is a property of the reconstruction itself. **None is
root-caused here.**

1. **`battery_model_state_update` (`FUN_0000c358`) — FAIL 46/46 fixtures,
   67 % coverage.** This is the defect AGENTS.md lists as *"STILL OPEN (real,
   previously invisible)"*. **The harness found it independently, from the
   shipped image, with no prior knowledge**, and it is the strongest available
   evidence that the oracle works.
2. **`__ieee754_expf` — 12 of 37 fixtures.** Pure numeric divergence: zero
   calls, zero side effects, return value differs by ~1.4 × 10⁻⁴ relative
   (e.g. `0x468E1BC0` vs `0x468E1739`). Not a `-ffp-contract` artefact — the
   contract is derived from the shipped instructions and the three other libm
   bodies pass under the identical setting.
3. **`imu_mahony_ahrs_update` — 44/44.** Careful here: AGENTS.md records this
   function as REPAIRED and passing `cfg_verify` 48/48. The divergence is on
   fixtures where the ORIGINAL faults on an invalid pointer and the candidate
   does not — see the fixture-quality limitation in §18.5. **Treat as harness
   fixture quality until re-tested with derived `nptr`, not as a defect.**
4. **`st25dv_mailbox_send_message` — 1 of 44 (`glob-0-0`).** With
   `g_st25dv_dev+0x10` zeroed, the fourth argument of the first call is `8` in
   the shipped code and `0` in the reconstruction. Everything else in the trace
   matches.
5. **`fuel_gauge_update` — 1 of 43 (`combo-2-0`).** With all seven literal-pool
   globals `0xffffffff` and all callees returning 0, the float handed to
   `__extendsfdf2` at call ordinal 13 is `1.0193735e-4` in the shipped code and
   `-2.0114315e-34` in the reconstruction. Return value and all 21 calls match.
6. **`battery_soc_curve_model_init` — 19 of 47.** AGENTS.md records this as
   CLOSED in P4 iteration 40. Either it regressed or this harness reaches
   inputs `cfg_verify` does not. **Needs checking before anything is concluded.**
7. Also failing on both trees, uninvestigated: `button_init` (43/43),
   `click_event_dispatch_loop` (3/45), `curve_table_interp_201pt` (1/46),
   `load_usr_setting` (1/42), `opt3007_chip_deinit` (1/42),
   `ui_set_imu_pitch_task` (1/45), `key_event_thread` (2/9).

### 18.4 Symbols that cannot be compiled in isolation (3 of 139)

`send_response_data_to_ble`, `send_response_data_to_msgqueue`,
`SlaveDoubleClickEventInject` include Zephyr headers that need the build's
generated `autoconf.h`. It is build-specific and no G1 copy exists on this
machine; supplying a foreign one would change inline Zephyr helper codegen.
Opt in with `G1_AUTOCONF=<path>`. Until then they are **untested**, and the
`CCFAIL` says so rather than hiding it.

### 18.5 A fixture-quality limitation found at the end, not fixed

`generate.candidate_fixtures` passes `nptr = 2` — the first two argument
registers point into scratch, the rest are seeded integers. A function with
**three or more pointer parameters** therefore receives garbage in the later
ones, and the shipped code faults dereferencing them while the reconstruction
may not. That is what `imu_mahony_ahrs_update`'s 44/44 looks like, and it
probably accounts for some of §18.3 item 7.

**The fix is specified and not built:** derive the pointer-argument count per
function (`cfg_verify.pointer_control_inputs` already recovers pointer slots
from the shipped instructions), or simply add `nptr = 0..4` variants to the
fixture set. It needs a full vector regeneration, which did not fit in this
session. A fleet should do this FIRST, before authoring any more modules.

### 18.6 Mutation kill rate — the anti-vacuity measurement

`cli.py grade`, 10 symbols, 16 mutants each, against the refactored tree.
Every mutant is compiled from an in-memory override; nothing is written to the
repository.

```
symbol                            killed survived invalid  kill rate
array_max_skip_nan_a                 14      2       0        88 %
opt3001_read_lux_raw                 13      2       1        87 %
ipc_read_u16_field                   13      2       1        87 %
mark_master_or_low_battery_flag       6      1       0        86 %
dev_send_cmd16_payload               11      3       2        79 %
getNewsIndex                          6      2       3        75 %
__ieee754_asinf                      12      4       0        75 %
st25dv_write_reg_pair                 7      8       1        47 %
i2c_read_reg16_be                     3     13       0        19 %
ipc_send_len_prefixed_packet          2     13       1        13 %
                                    ---    ---     ---
                                     87     50       9        64 % overall
```

The distribution is the honest picture, and the two ends of it are both
informative:

* the **75–88 % band** is what the suite achieves on ordinary code, and the
  survivors there are mostly measurable equivalents — for `__ieee754_asinf`,
  two of the four survivors change the function's float32 result on **0** and
  **1** of 300,000 inputs drawn from the branch's reachable domain, so no test
  can kill them;
* the **13–19 % floor** is `ipc_send_len_prefixed_packet` and
  `i2c_read_reg16_be`, and it is **entirely** the stack-record blind spot of
  §16.1: both build a record in a stack local and pass its address, and every
  field-constant perturbation survives. This is the concrete price of the
  retreat, stated as a number.

### 18.7 Negative controls — the suite is shown to fail, not asserted to

`recon/tests/test_modtest_pilot.py --quick`, 32 symbols:

```
POSITIVE: 32 symbols, trees agree on 32, disagree on 0
COVERAGE: 564/960 shipped CFG instructions = 58.8 %
NEGATIVE CONTROLS on 6 symbols: 12 killed, 1 survived, 5 not applicable
  killed  ipc_read_u16_field         return-constant, flip-comparison
  killed  ipc_transport_ops_dispatch return-constant, drop-call
  killed  send_response_data_to_ble  return-constant, drop-call, flip-comparison
  killed  serial_data_read_dispatch  return-constant, flip-comparison
  killed  __fpclassifyf              return-constant, flip-comparison
  killed  dump_template_gyro_info    flip-comparison
  SURVIVED dump_template_gyro_info   drop-call
```

"Not applicable" is printed rather than silently skipped, because a control
that never applied is not a control — this project has shipped two of those.
The one survivor is recorded as a blind spot, not rounded away.

Two known rough edges in this file, both cosmetic: it counts a `CCFAIL` as a
total failure (so `send_response_data_to_ble` shows as FAIL 3/3 rather than
"cannot compile"), and it re-runs vectors the `cli.py run` command already
covers.

### 18.8 Summary against the acceptance criteria of §8.2

| module | agreement | coverage ≥ 70 % | kill rate ≥ 70 % | neg. controls |
|---|---|---|---|---|
| `lib` (5 sampled) | ✅ 5/5 | ✅ 93.8 % | ✅ 75 % (asinf) | ✅ |
| `ipc` | ✅ 47/47 | ✅ 75.5 % | ⚠️ 13–87 %, mixed | ✅ 0 survived on ipc symbols |
| `sensors` | ✅ 87/87 | ❌ 55.5 % | ⚠️ 19–88 %, mixed | not run |

**No module passes §8.2 outright**, and that is the correct outcome for a pilot:
the gate is real rather than decorative. `ipc` is closest and fails only on the
kill-rate spread caused by the stack-record blind spot. `sensors` fails on
coverage, for reasons that are named per symbol (threads, long init sequences,
poll loops) rather than hand-waved.

---

## 19. The next five things, in order

1. **Derive `nptr` per function** (§18.5). Cheapest fix with the largest effect
   on false failures. Do this before authoring any more modules; it needs a
   vector regeneration.
2. **An object-extent model for stack pointees** (§16.1). Removes the largest
   real blind spot and would take `ipc_send_len_prefixed_packet` from 13 % to
   100 %. The four corrections already made are in the tree and documented; the
   missing piece is knowing where the object ends.
3. **Investigate the six candidate findings** in §18.3, starting with
   `battery_soc_curve_model_init` (AGENTS.md says CLOSED; this says 19/47 fail)
   because that one is either a regression or a coverage gain, and both matter.
4. **Point `G1_AUTOCONF` at the real build** so the three Zephyr-including TUs
   become testable.
5. **Run the harness once on the net core.** It is core-parametric and has
   never been executed with `core="net"`.
