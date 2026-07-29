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

---

# ══════════════════════════════════════════════════════════════════════
# SIXTH ITERATION — 2026-07-28 (later session)
# ══════════════════════════════════════════════════════════════════════

Written incrementally while the work ran. Every number below is from a command
executed in this pass; where it contradicts an earlier section of this file or
AGENTS.md, that is stated in place rather than quietly corrected.

Task, in the owner's priority order: (1) raise the mutation kill rate before
widening coverage, and decide whether the stack-record capture retreat of §16.1
can be undone soundly; (2) fan out across the unpiloted modules; (3) resolve the
open divergences of §18.3.

## 20. Kill rate BEFORE — measured on whole modules, not on ten symbols

§18.6 reported **64 %** over ten hand-picked symbols. That is not the figure to
improve against, so the first thing this pass did was grade **every** piloted
symbol. `cli.py grade --module <m> --mutants 16`, refactored tree:

```
module    graded  baseline-OK  killed/total   kill rate  median  zero-kill symbols
ipc          47        44       261 / 425        61 %      80 %        2
sensors      87        75       404 / 705        57 %      75 %       13
lib           5         4        49 /  61        80 %      81 %        0
                                ---------
ALL                             714 / 1191       60 %
```

Two things are visible here that the ten-symbol sample hid: the real aggregate
is **60 %, not 64 %**, and **15 symbols score zero** — a suite that cannot
detect any single-token change to the function it is supposed to constrain.

### 20.1 A vacuous measurement in the grader itself — corrected

`__ieee754_expf` appears in the pilot's own `lib` numbers with a **100 % kill
rate**. Its baseline **FAILS**. Every mutant therefore also fails, is counted
as killed, and the symbol scores 100 % while measuring nothing. That is the
fifth distinct shape of vacuous pass this project has produced, and it was in
the anti-vacuity instrument itself.

`cli.cmd_grade` now prints `n/a(baseline FAIL)` and the aggregates above exclude
those symbols (3 in `ipc`, 12 in `sensors`, 1 in `lib`). Including them would
have reported 63 % / 61 % / 84 % — i.e. the defect flatters the number.

## 21. Why mutants survive — four causes, all measured, all fixed

### 21.1 The mutation engine was mutating the WRONG FUNCTION (45 symbols)

`mutate.member_span` confines a mutant to the target's own banner-delimited
block. It located that block by `public-name:` **or**, failing that, by
`\bSYMBOL\s*\(` anywhere in the block. The second test matches a **call site**.

```
ipc/g1_ipc_cc01.c
  member 1: st25dv_write_control_and_ack   ... body contains
                st25dv_reg_modify_low5(val, b);      <-- matches "SYMBOL ("
  member 4: st25dv_reg_modify_low5         <-- the actual definition
```

The first member wins because the scan is in file order, so **every mutant for
`st25dv_reg_modify_low5` was applied to a sibling**: graded **0 of 12 killed at
100 % instruction coverage**. That is precisely the vacuous-grading failure
`member_span` was written to prevent (§11.1 A), reintroduced one level along —
and it is the eighth defeat of text-anchored matching recorded in this project.

Swept over the whole refactored app tree: **45 of the 1,167 members of merged
TUs were mis-attributed.** After the fix (`public-name:` first, and the loose
fallback restricted to something that looks like a *definition* — name,
balanced parameter list, then `{` and not `;`): **0 of 1,604.**

```
st25dv_reg_modify_low5     0 %  ->  64 %
```

### 21.2 `nptr` was fixed at 2 — and the fix is a MASK, not a count

§18.5 specified this and did not build it. Built here as
`generate.pointer_arg_mask`.

The pilot passed `nptr = 2` to `emu.make_args`, so exactly r0 and r1 pointed
into scratch. A function whose third or fourth parameter is a pointer got a
seeded integer there and the shipped code faulted dereferencing it. But a fixed
prefix is wrong in the other direction too, and that half was not stated before:
it makes r0 a pointer for a function whose first parameter is a `uint8_t`
command code, which feeds a pointer-shaped value to a switch selector — the
exact blind spot AGENTS.md finding #1 exists for.

So the count is not the thing to derive. The **mask** is: track which registers
still hold a value derived from an argument register (through register moves and
immediate add/sub), and mark argument *i* a pointer when a load or store uses
such a register as its base. Argument registers lose their origin at every `bl`.
Walked in address order over the CFG-reachable set, never by linear
disassembly, so a literal pool cannot be decoded as instructions.

`--nptr` now defaults to `-1` = derive; a non-negative value reproduces the old
behaviour so the two can be compared. The derived mask is recorded in every
vector file (`pointer_arg_mask`).

### 21.3 THE RETREAT OF §16.1 IS REVERSED — the diagnosis was incomplete

§16.1 disabled the stack-record pointee capture because
`st25dv_read_area_size` failed 41 of 41 fixtures on both trees, and attributed
it to a spelling problem: the shipped code reserves a slot with `push {r1}`
while the reconstruction uses `str r1,[sp,#n]`, and correction 2 classifies the
first as frame bookkeeping and the second as content.

**That attribution is wrong, and the measurement that shows it is cheap.**
A probe (`stackprobe.py`, scratchpad) re-runs the ORIGINAL and the CANDIDATE
under each frozen fixture with the window at 48 and compares *only* the
capture, using none of the rest of the pass criterion. Over all 47 `ipc`
symbols:

```
symbols where the capture AGREES on every fixture, both trees   44 / 47
  ... of which capture a NON-EMPTY record                        8
symbols where it DISAGREES                                       3
```

So 44 of 47 were already sound and were thrown away with the three. And the
three are not a `push`-versus-`str` problem at all:

```
st25dv_read_area_size        push {r0,r1,r2,lr}   ; 12-byte SCRATCH ALLOCATION
                             add  r1, sp, #4      ; OUT parameter, callee fills
                             bl   0x7c968
st25dv_mailbox_poll_message  push {r0,r1,r2,r3,r4,r5,r6,lr}  ; same shape
                             add  r0, sp, #8
st25dv_reg_modify_low5       ldrb.w r3,[sp,#7]    ; reads the out-buffer BACK
                             bic  r3, r3, #0x1f   ; keeps its top three bits
                             strb.w r3,[sp,#7]
```

The first two pass a buffer whose content at the call is *garbage on both
sides* — the pushed words are the incoming r0-r2, and the callee is what fills
it. The third is the clearest: golden byte `0x30`, candidate `0x50`. The **low
five bits, which the function computes, agree exactly**; the top three, which it
**inherited** from uninitialised frame memory, do not.

All three are one defect class: the capture was comparing bytes whose value the
function never produced. Two rules follow, and neither is a heuristic about
instruction spelling:

* **Rule 6 — a stack byte READ before the run ever wrote it is inherited, not
  produced**, and is dropped. (`UC_HOOK_MEM_READ` over the stack window,
  golden side only.)
* **Rule 7 — the GOLDEN defines the extent.** The shipped image is the oracle,
  so the offsets *it* wrote are what the record is. The candidate's window is
  read raw and compared only at those offsets
  (`core.stack_args_mismatch`). An offset the shipped code never wrote is not
  part of the observable contract in this model, so a candidate that spills a
  register there is not a failure.

Rule 7 is a deliberate asymmetry and a weakening, stated where it is
implemented: a candidate that writes an **extra** field is now invisible. A
candidate that **fails to write** a field the shipped code writes is still
caught, because the golden offset is compared against whatever the candidate's
frame holds.

Consequences, measured:

```
                              probe disagreements      run verdict, both trees
st25dv_read_area_size          41/41  ->  0/41         OK(41/41)
st25dv_mailbox_poll_message    42/42  ->  0/42         OK(42/42)
st25dv_reg_modify_low5          1/42  ->  0/42         OK(42/42)
```

`core.STACK_ARG_WINDOW` therefore defaults to **48 again**. The record is no
longer folded into the event-trace digest (it cannot be — the two sides now
carry different representations of it); it is a second, structural comparison
in `cli._replay`, reported as `{"stack_record": …}` with the call ordinal,
argument index, offset, expected and actual byte.

### 21.4 A fixture dimension that did not exist: POINTER CHAINS

This one was not on anybody's list and it is the largest single effect
measured in this pass.

`emu` seeds the scratch region an argument points at with random bytes. A
pointer *field* read out of that pointee is therefore a random 32-bit word, and
dereferencing it faults. Firmware written against a driver model chases two or
three of those before it does anything at all:

```c
((vfn847d8)(*(int *)(*(int *)(*param_1 + 8) + 8)))(*param_1, &local_28, 2, ...)
```

`i2c_read_reg16_be` is exactly that shape. Measured: it faulted on the second
load in **every one of 113 candidate fixtures**, kept 3, reached 74 % of its
instructions and **never reached its own call** — so the 20-byte descriptor it
builds in stack locals was never passed to anyone, and every perturbation of
every field survived. Its 19 % kill rate was read in §18.6 as the price of the
stack-record blind spot. It was not: the capture worked and there was nothing
to capture.

The fix is a fixture, not a harness change — `tools/parity/emu.py` is FROZEN
(AGENTS.md) and shared with the net core, so the chain image is written through
the existing `abs` (absolute-memory) dimension. `generate.CHAIN_BASE` holds a
512-byte region every word of which is an address inside it.

One wrinkle had to be measured rather than reasoned: a word in that region is
used two incompatible ways. As a **load base** it must be 4-aligned or Unicorn
rejects the `ldr`; as a **function pointer** it must be odd or the `blx`
switches to ARM state and dies with "Invalid instruction". No single value is
both. So which words carry the Thumb bit is **swept**: 3 strides x 4 residues.

```
i2c_read_reg16_be, 12 chain combinations
  11 still fault
  stride 0x04 / residue 2:  returns, ncalls=1, 20-byte record captured
```

Effect on the four symbols re-measured immediately:

```
                          coverage        kill rate
i2c_read_reg16_be      74 % -> 100 %     19 % -> (baseline now FAILS, see §22.1)
dev_send_cmd16_payload         92 %      79 % -> 100 %
opt3001_read_lux_raw          100 %      87 %
st25dv_write_reg_pair          78 %      47 %
```

## 22. New findings the fixes exposed

### 22.1 `i2c_read_reg16_be` is a FALSE PROOF — the record it passes is wrong

The chain dimension took this function from 74 % to 100 % coverage and its call
became reachable for the first time under any harness in this repository. Its
source header says `parity: 300/300 trials, PROVEN`. It now **FAILS 2 of 8
fixtures, identically on both trees.**

The shipped code builds a 32-byte descriptor at `sp+8` and passes `sp+8`:

```
offset 0  : &local_2d   (pointer)      offset 12 : &local_2c  (pointer)
offset 4  : 1                          offset 16 : 2
offset 8  : 0                          offset 20 : 7
```

The reconstruction spells that descriptor as six **independent stack locals**
and passes `&local_28`, relying on the compiler to lay them out contiguously in
declaration order:

```c
unsigned char *local_28; unsigned int local_24; unsigned char local_20;
unsigned short *local_1c; unsigned int local_18; unsigned char local_14;
local_28 = &local_2d; local_24 = 1; local_20 = 0;
local_1c = local_2c;  local_18 = 2; local_14 = 7;
iVar1 = (...)(*param_1, &local_28, 2, (short)param_1[1]);
```

C guarantees no such thing, and the compiler does not do it. Candidate window
at the call, first eight bytes: `ebef0720 08100120` — offset 4 holds the value
`0x20011008`, which is `param_1` spilled, where the shipped code has the
constant `1`.

**Checked against the compiler-version hypothesis and it does not hold.** The
harness compiles candidates with `arm-none-eabi-gcc 15.1.0`, while the firmware
was built with `arm-zephyr-eabi` GCC 12.2 (AGENTS.md), so a layout difference
could have been an artefact. Re-running this fixture with the Zephyr SDK's
`arm-zephyr-eabi-gcc` produces the **byte-identical** candidate window and the
same mismatch at offset 4. It is a reconstruction defect: a struct spelled as
loose locals.

**This is also a harness-fidelity item worth recording on its own:** every
candidate in this suite is built by a compiler four major versions newer than
the one that built the firmware. It did not matter here. It has not been
swept.

### 22.2 `__ieee754_expf` — RESOLVED, and the ORACLE was the one that was wrong

§18.3 item 2 recorded this as a "candidate reconstruction finding … pure
numeric divergence … not a `-ffp-contract` artefact". It is neither. It is a
**harness defect, and the worst kind: the harness accused a correct
reconstruction.**

The first thing that decides it is not disassembly, it is an external oracle.
Comparing both answers against `math.exp`:

```
fixture   x            shipped(golden)  candidate     true         golden err  cand err
seed-3    9.8066502    18156.375        18154.072     18154.072    +1.27e-4    2.0e-8
seed-5    1.5707964     4.810565          4.8104777     4.8104776  +1.82e-5    3.0e-8
seed-22  -3.0           0.049785264       0.049787067   0.049787068 -3.62e-5   3.0e-8
```

**The candidate is accurate to one float32 ULP and the golden is not.** A
golden that is wrong is not a divergence, it is a broken oracle, and the error
has an exact shape: `k * 9.0580006e-06` for `k = 14, 2, -4`, which is
`k * ln2LO` — the low half of the argument reduction `x - k*ln2HI - k*ln2LO`,
missing entirely.

Cause: `run_original` read the shipped body as
`func_bytes_padded(va, size, pad=64)`. Reads outside the mapped body hit
`emu`'s unmapped-access hook, which **maps a page of zeros and continues**.
`__ieee754_expf` is 344 bytes at 0x76290, so the padded body ends at 0x76428 —
and its literal pool holds exactly two more words:

```
0x76428  0x3717f7d1  = 9.0580006e-06   ln2LO              <-- read as 0.0
0x7642c  0x0d800000  = 2**-100         subnormal rescale  <-- read as 0.0
```

`core.literal_pad` now derives the pad from every PC-relative load in the
function instead of assuming 64. Padding only extends the MAPPED region;
`emu`'s executable extent stays `[va, va+size)`, so the extra bytes are the
real image bytes at their real addresses, which is exactly what a PC-relative
load is entitled to see.

```
__ieee754_expf   FAIL 25/37 on both trees  ->  OK 37/37 on both trees
```

**Scope of the defect, swept:** of 1,529 app symbols with a catalogued size,
**59 have a literal pool reaching past `size + 64`** — `lib` 19, `notify` 8,
`ui`/`sensors`/`display` 5 each, `ble`/`unsorted` 4, `gui` 4, `core` 2,
`esb`/`storage`/`audio` 1. Every vector for those symbols generated before this
fix was frozen against a partly-zeroed literal pool. They are regenerated.

This is the third time in this project a wrong-by-omission read has been
mistaken for a reconstruction defect (`fuel_gauge_update`'s truncated extent in
§5, `-fno-inline` in §3, and now this). The method note stands and is
strengthened: **a failure that reproduces identically on both trees is a
hypothesis about the harness first.**

### 22.3 `imu_mahony_ahrs_update` — harness artefact, and the cause is IPA-RA

§18.3 item 3 guessed "harness fixture quality … re-test with derived `nptr`".
The class was right and the cause was not: the derived mask for this function
is `{0}`, which is correct (seven floats in s0-s6, `state` in r0), and it still
fails 44/44 on both trees. The reason is exact:

```
0002662c  push   {r3, lr}            <-- saves NO callee-saved register
00026636  vldr   s7,  [r0, #0x18]    <-- r0 = state
...
0002666c  bl     #0x265e8            <-- fast_inverse_sqrt (leaf, float in/out)
...
000266b4  vldr   s13, [r0, #8]       <-- r0 STILL USED AS state   *** FAULT ***
```

The shipped code keeps the `state` pointer live in **r0 across a call**. That
is only valid code if the compiler knew the callee does not clobber r0 — i.e.
it was built with **inter-procedural register allocation** (`-fipa-ra`, on by
default at `-Os` when the callee is visible). `fast_inverse_sqrt` takes and
returns a float and never touches r0.

`emu`'s oracle writes `sha256(ordinal)` into **r0:r1 at every call, whatever
the callee's return kind**. So after the oracled call r0 holds a garbage word
and the next `vldr [r0,#8]` faults — `fault_off = 144`, `ncalls = 1`, exactly
what the vector froze. The candidate, compiled against an `extern` declaration,
*must* assume AAPCS and reloads the pointer from a callee-saved register, so it
does not fault and the two diverge.

This is the same defect AGENTS.md §51 records against `cfg_verify` ("its opaque
callee stub always clobbers r0"), inherited here because both use `emu`'s
oracle. It is not specific to this function and it is **not measured across the
corpus**: any caller built with IPA-RA that keeps a live value in r0-r3 across
a call is affected.

**The fix is specified and NOT built** (it needs `emu`, which is FROZEN and
shared with the net core, or a trampoline hook in `_CoverageRunner`): make the
oracle **return-kind aware** and preserve every caller-saved register the
callee's ABI does not define — r2/r3 always, r1 unless the return kind is
`i64`, r0 when the return kind is `void`/`f32`/`f64`. That is the most
permissive consistent model and cannot manufacture a fault. Its cost is a
narrow blind spot: a candidate that wrongly assumed r1 survives would also
pass.

**Verdict: `imu_mahony_ahrs_update` is NOT a reconstruction defect.** AGENTS.md's
record of it as repaired stands.

### 22.4 `curve_table_interp_201pt` — RESOLVED, passes 45/45

§18.3 item 7 lists it failing 45 of 46 on both trees. With the fixture set of
this pass it is **OK(45/45) on both trees at 94 % coverage**. It was a fixture
artefact, not a defect.

### 22.5 `battery_soc_curve_model_init` — the AGENTS.md record is OPTIMISTIC

§18.3 item 6 and AGENTS.md finding #1b disagree: AGENTS.md says **CLOSED in P4
iteration 40** (`FAIL 13/43 -> PASS 43/43`), the pilot said 19 of 47 fixtures
fail. Resolved here, and the answer is that **the harness is right and the
record is wrong** — with the caveat below.

Measured under the final harness, both trees identically:

```
--nptr 2 (the pilot's configuration)   FAIL(28/47)   cov 91 %
--nptr derived, mask {1,2,3}           FAIL(0/49)    cov 93 %
```

The derived mask is `{1,2,3}` because r0 is only ever *passed* to a callee (it
is the source argument of an inlined `memcpy` at 0xe576) and never
dereferenced by this function. Under it, essentially every fixture diverges.
Concretely, `seed-3`, where both sides return the same value after the same 8
calls and agree on the first 74 of 87 events:

```
event 74  call ordinal 6, three stack pointers passed
   golden    (SP+0, SP+24, SP+4)
   candidate (SP+0, SP+12, SP+4)      <-- a DIFFERENT local is passed
event 76  call ordinal 7, r2
   golden    1092413446               candidate 1092413450   (4 ULP apart)
event 77  the same value stored to 0x20009A1C
events 83-86  four consecutive words
   golden    914513789   x4           candidate 2413199852   x4
```

A different stack local at a call boundary and four wholly different stored
words are not rounding. `core.normalise_events` preserves relative stack
structure exactly, so `SP+24` versus `SP+12` is a real difference.

**Why the two records disagree.** The closure in P4 iteration 40 was decided by
`cfg_verify`. AGENTS.md's own CURRENT PHASE section says `cfg_verify` **is not
evidence on this code** and is blind in both directions; §51.1.1 shows it
passing a real defect. A `PASS 43/43` from it does not establish closure. The
repairs made in iteration 40 were real and improved the function — 13/43
failing became 28/47 passing under the pilot's own configuration — but the
function is **not clean**, and AGENTS.md's "CLOSED" should be downgraded.

**Caveat, stated because it is not eliminated:** this symbol is not in the
literal-pad-affected set (`pad = 64`), and the divergence reproduces on both
trees, but the oracle-clobber limitation of §22.3 has *not* been ruled out for
it — it makes 8 calls. That check is not done here.

### 22.6 Two NEW divergences the fan-out found (both trees, uninvestigated)

* **`debug_print` (`common`) — a SEMANTIC CALL-TARGET failure, not a value
  failure.** Fixture `orc-all-0`, call ordinal 4: the shipped image calls
  `0x0007C132` and the candidate calls `0x0007CB0C`. The pass criterion's
  call-target identity check (§4) is what catches this; the return value, the
  call count and the whole event trace agree. A candidate calling the wrong
  same-ABI dependency is precisely the class that check exists for. **Not
  root-caused. It could also be a `target_map` artefact and that has not been
  excluded.**
* **`update_burial_point_day_index` (`analytics`) — FAIL 40 of 41 at 14 %
  coverage.** Diverges at event 2 with the same return value and call count.
  The coverage figure is the more useful number: 14 % means the vectors barely
  reach this function, so the failure is at the very start of it.

### 22.7 `st25dv_mailbox_send_message` — RESOLVED: the callee ARITY was too wide

§18.3 item 4 recorded this as "the fourth argument of the first call is 8 in
the shipped code and 0 in the reconstruction. Everything else in the trace
matches." Everything else matches because **nothing else differs** — the
fourth argument register is dead.

The callee is `st25dv_write_reg_pair` at 0x24f08. Its whole body is:

```
push {r3,r4,r5,lr}   mov r4,r0    ldr r5,[pc,#0x2c]   movs r3,#4
mov r2,r0            movs r1,#0   ldr r0,[r5]         bl 0x256dc   ...
```

It reads **r0 and nothing else**; r1, r2 and r3 are all overwritten before any
use. Its true arity is **1**. `cfg_verify.core_ctx`, which is Ghidra's
decompiled signature, says **4**, so the harness compared three dead registers
holding whatever the caller happened to leave there.

§11 defect 2 fixed the harness comparing four registers regardless of arity by
taking the arity from Ghidra. This is the same defect from the other side: the
*source* of the arity can itself be too wide.

`core.live_in_arity` derives it from the callee's own bytes — a live-in
analysis (read before written) over the CFG-reachable set, stopping at the
callee's first `bl` — and `callee_abi` uses it whenever it is NARROWER than
Ghidra's. It can only ever be too wide, never too narrow, so it cannot
manufacture a false pass relative to today.

One correction was needed and it is the same trap as §21.3: **`push {r3,r4,r5,lr}`
READS r3**, and Thumb uses exactly that to reserve four bytes of stack. Counting
it as a use derived arity 4 — reproducing the very over-wide value the function
exists to narrow. A stack save is only a real use if the value is reloaded, and
the walk stops at the first `bl` before any reload matters.

```
st25dv_write_reg_pair   Ghidra arity 4  ->  derived 1
st25dv_mailbox_send_message   FAIL(43/44) both trees  ->  OK(44/44) both trees
```

**Scope, swept:** of the 2,383 app callees with a Ghidra arity, **310 (13 %)
are over-wide** — 81 of them 4→3, 61 4→1, 45 4→2, 29 3→2. Thirteen per cent of
call sites in the corpus were comparing dead registers. `DERIVED_ARITY`
therefore defaults **on**, and all vectors in this pass were regenerated with
it.

## 23. ⚠️ VECTOR SEMANTICS CHANGED — read this before reusing any vector file

**Every vector file generated before this pass is invalid and every vector in
`recon/tests/vectors/app/` was regenerated.** Five changes alter what a golden
expectation *is*, not merely which fixtures are chosen. A concurrent agent
holding vectors generated against the previous harness (the net core's, for
example) must regenerate them; comparing old vectors against the current
harness will produce failures that mean nothing.

1. **`core.STACK_ARG_WINDOW` defaults to 48** (was 0). Vectors now carry a
   `cases[].stack_args` field and `cli._replay` applies a SECOND, structural
   criterion. A vector without the field is simply unchecked on that axis.
2. **The stack record is no longer folded into the event digest.** Old vectors
   generated with the window enabled have a digest that the current harness
   will never reproduce.
3. **`core.literal_pad` replaces the fixed 64-byte pad.** The golden's own
   observable behaviour changes for the 59 app symbols whose literal pool
   reaches further (§22.2). Their old expectations were frozen against a
   partly-zeroed literal pool.
4. **`core.DERIVED_ARITY` defaults on.** The number of argument registers
   recorded in every call event changes wherever the derived arity is narrower
   than Ghidra's — 13 % of app callees (§22.7). This changes the event trace
   hash of any fixture that reaches such a call.
5. **`--nptr` defaults to `-1` (derive).** The fixture *inputs* change, so
   fixture ids no longer correspond between old and new files.

`tools/parity/emu.py` and `tools/cfg_verify.py` are **untouched**; `emu` is
used as a library exactly as before and `cfg_verify` only for
`selector_values` and `core_ctx`. No source in any reconstruction tree was
edited by this pass.

## 24. What this pass did NOT do, and why

> The measured results are in **§26**, appended after this section because it
> was written while the sweep was still running.

* **`display` (89 symbols) was dropped mid-pass.** Its functions are long
  render loops; generation was averaging minutes per symbol and would not have
  finished. 17 of its symbols were generated in an earlier wave and discarded
  when the harness changed. It is the cheapest module to add next.
* **`core` (142), `ble` (99), `audio` (137), `unsorted` (167) were never
  started.** With `display` that is **634 of the app core's 1,604 module
  symbols still unpiloted** — the fan-out reached roughly 60 %, not 100 %.
* **The oracle's r0/r1 clobber is NOT fixed** (§22.3). It is specified there.
  Until it is, any caller built with `-fipa-ra` that keeps a value live in
  r0-r3 across a call diverges for a reason that is not a defect. **The size of
  this class is not measured** — `imu_mahony_ahrs_update` is the only confirmed
  member. That measurement is the single most valuable next number, because
  every unexplained "golden faults, candidate returns" result in §26 is a
  candidate for it.
* **`battery_model_state_update` was not root-caused.** It remains what
  AGENTS.md says it is: open. This pass confirms it fails on both trees
  (0 of 46 fixtures, 62 % coverage) and adds nothing else.
* **`fuel_gauge_update` was not re-investigated** beyond confirming it still
  fails one fixture of 43 on both trees at 47 % coverage.
* **The net core was not run.** Still true, and now with a stronger warning
  attached: §23 lists five changes that invalidate any vector generated against
  the previous harness.
* **`G1_AUTOCONF` was not supplied**, so `send_response_data_to_ble` and
  `send_response_data_to_msgqueue` remain `CCFAIL` (visible, not hidden).
* **The compiler-version gap was not swept.** Candidates are built with
  `arm-none-eabi-gcc 15.1.0`; the firmware was built with `arm-zephyr-eabi`
  GCC 12.2. Checked on exactly one symbol (§22.1) where it made no difference.
* **Module-scope emulation, the external-oracle tier for `lib`, and an
  object-extent model for stack pointees** are all still unbuilt. Rules 6 and 7
  (§21.3) are a *sound comparison* over a fixed window, not an extent model;
  the residual blind spot is stated where they are implemented.
* **Renode was not run. Nothing was committed. No source in any tree was
  edited.**

## 25. Files changed by this pass (nothing committed)

Modified (all previously committed in `f3dc81b9`):

```
tools/modtest/core.py       stack-record rules 6 & 7 + window default 48;
                            stack_args_mismatch(); literal_pad(); 
                            live_in_arity() + DERIVED_ARITY; stack_content flag
tools/modtest/generate.py   pointer_arg_mask() + _masked_args(); pointer-CHAIN
                            fixture dimension; ptr4/ptr2/ptr0 bands; stack
                            record folded into the outcome-distinctness key
tools/modtest/mutate.py     member_span(): public-name pass before the loose
                            fallback, and the fallback restricted to definitions
tools/modtest/cli.py        --nptr defaults to derive; stack_args written into
                            every vector and checked at replay; kill rate
                            reported as n/a when the baseline fails
recon/tests/test_modtest_pilot.py   negative controls now exercise the
                            stack-record criterion too
recon/analysis/test_architecture.md  this section onwards
recon/tests/vectors/app/**  REGENERATED IN FULL (see §23)
```

`tools/parity/emu.py`, `tools/cfg_verify.py`, `recon/net/**`,
`recon/symbolized/net/**`, `recon/tests/vectors/net/**`,
`recon/analysis/net_test_coverage.md` and every refactor stage are untouched.


---

## 26. ⚠️ VECTOR-SEMANTICS LEDGER, and the versioning that makes it enforceable

> **This section exists because a prose warning is not a mechanism.** §23 said
> the vector semantics had changed. It did not reach the concurrent net-core
> pass in time: **168 of its vectors were invalidated mid-sweep** by changes
> made here, it recovered by pinning the harness to a `git show HEAD` snapshot
> and regenerating, and it **deleted 81 more** whose harness version it could
> not establish rather than publish numbers it could not stand behind. That is
> the correct call and it should not have been necessary.

### 26.1 The ledger

Each entry says what changed and marks what it invalidates. **Every vector
generated before the entry below it is invalid and must be regenerated.**
The working tree is deliberately dirty (owner rule), so a git rev would name
four materially different harnesses "HEAD" in one session; the identifier is
therefore a content fingerprint over `core.py`, `generate.py`, `cli.py` and
`mutate.py` — `core.harness_rev()`.

```
change                                          invalidates vectors generated before it
--------------------------------------------------------------------------------------
STACK_ARG_WINDOW 0 -> 48, + stack_args field    ALL (observable comparison changed)
stack record removed from the event digest      ALL with the window on
literal_pad() replaces the fixed 64-byte pad    the 59 app symbols of §22.2
DERIVED_ARITY on (callee arity from the image)  ALL reaching a narrowed callee (13 %)
--nptr default -1 (derived mask) + ptr bands    ALL (fixture inputs changed)
--------------------------------------------------------------------------------------
harness fingerprint at the end of this pass:    c9132a14658714d0
--------------------------------------------------------------------------------------
2026-07-29 (2nd pass) -- ONE BURST, applied BEFORE any `gen`, then frozen:
  -fno-ipa-vrp in UNIT_BOUNDARY_CFLAGS           ALL merged-TU candidates (call deleted)
  read-only pointer in a stack record -> content ALL with a record holding a .rodata ptr
  _expose_target accepts preprocessor lines      ALL stage-09 symbols behind a directive
  vector_staleness FAILS CLOSED (+ env dict)     nothing semantically; refuses unstamped
  cmd_run per-symbol guard; no .text -> CCFAIL   nothing semantically
  OUT-PARAMETER FILL (deterministic, both sides) ALL that read an unwritten out-param byte
  pointer_arg_mask keeps a PASS-THROUGH pointer  ALL (fixture inputs changed; 512 of 891)
  pointee ladder / out-param ladder dimensions   ALL (fixture inputs changed)
  GLOBAL_SPAN 4 -> 0x400, global-equals-argument ALL with a literal global
  cli --budget default 400 -> 600                ALL with > 400 candidate fixtures
--------------------------------------------------------------------------------------
★ FINAL FINGERPRINT OF THIS PASS:               956e29213dbbde89
  harness_env(): outparam_fill=True derived_arity=True oracle_preserve=True
                 stack_arg_window=48 outparam_window=512 drop_outparam_uninit=False
  ALL 924 app vectors are regenerated and stamped at it (measured: 0 stale).
  `.modtest_pin/` at 936cee0b67396ca5 is the net agent's and was NOT touched.
  ⚠ `--budget` and `max_insns` are still NOT in `harness_env()`, so this pass's
  400 -> 600 change is invisible to the guard.  See 29.11.
(c74709bc69344793 was the rev before the three net-core patches of 26.3 landed;
 the vectors measured in 27 were produced by that one and are UNSTAMPED, so
 `run` accepts them -- regenerating stamps them and the guard takes effect.)
```

**2026-07-29 — ENTRIES ADDED BY THE r0-CLOBBER PASS (§28). Both are
semantics-changing and both affect BOTH CORES. Recorded at the moment they
landed, per the rule this section exists to enforce.**

```
change                                          invalidates vectors generated before it
--------------------------------------------------------------------------------------
ORACLE_PRESERVE on (core.callee_gpr_defs):      ALL reaching a callee that provably
  r0/r1 that the REAL callee provably never     never writes r0 or r1.  Swept: 411 of
  writes are now CARRIED ACROSS the oracled     2,404 app callees (17.1 %) and 376 of
  call instead of being overwritten with        1,249 net callees (30.1 %).  On the 330
  sha256(ordinal).  §28.1.                      app symbols with a vector, 156 (47 %)
                                                have at least one such call site.
vector_staleness now also refuses a vector      none (it only tightens a check that was
  whose recorded derived_arity / oracle_        never made); but it makes the two ENV
  preserve differs from the current run.        switches enforceable from now on.
--------------------------------------------------------------------------------------
callee_gpr_defs: an incomplete CFG walk (ran      ALL generated at 936cee0b67396ca5 by a
  off the end of the catalogued extent, or fell   run with ORACLE_PRESERVE on.  §28.2.1.
  through into the next function) now returns
  None instead of "writes nothing".  Corrects
  an UNSOUND preservation.  §28.2.1.
--------------------------------------------------------------------------------------
harness fingerprint after all three:            e556ab5692bf509d
(936cee0b67396ca5 and 26100c716510a0fc existed briefly during this pass; no
 vector reported in §28 was produced by either -- everything was regenerated at
 e556ab5692bf509d.)
```

> **Net-core agent, read this — and read the second paragraph first.**
>
> ⚠ **`936cee0b67396ca5` — the fingerprint `net_test_coverage.md` §9.2 says
> this pass pinned to at `.modtest_pin/` — CONTAINS AN UNSOUND
> `callee_gpr_defs`, and it is fixed at `e556ab5692bf509d`.** At that pinned
> rev the analysis returned "this callee writes neither r0 nor r1" for any
> callee whose CFG walk **ran off the end of its catalogued extent** instead
> of reaching a return, and the net Ghidra catalog under-reports sizes *far
> more than app's* — §6.5 of your own document. The corpus effect on app was
> small (1 r0 callee, 5 r1 callees) but it is a **wrong preservation**, not a
> missing one, so on net it can make a golden trace that the silicon would not
> produce. Details and the worked instance in §28.2.1. **Do not publish
> numbers from `.modtest_pin/` at `936cee0b67396ca5` without re-checking
> against `e556ab5692bf509d`.**
>
> `MODTEST_ORACLE_PRESERVE=0` restores the pre-2026-07-29 oracle exactly, and
> `harness_rev()` at that setting is unchanged, so the fingerprint alone will
> NOT tell you which of the two semantics a vector holds — that is why
> `harness.oracle_preserve` is now stamped and checked separately. Net has the
> larger exposure of the two cores (30 % of callees leave r0 or r1 alone,
> against app's 17 %), so regenerating is very likely worth more to you than
> to app.
>
> **Your §9.1 patch to `cli.cmd_run` (count and report UNSTAMPED vectors) is
> accepted in substance and DELIBERATELY NOT APPLIED IN THIS PASS.**
> `harness_rev()` hashes whole files, so a two-line addition that changes no
> semantics whatever would still change the fingerprint and make `run` refuse
> the ~960 app vectors this pass had just generated. That is a real defect in
> the fingerprint — it cannot express "semantics-neutral" — and paying for it
> mid-sweep buys nothing. **It should be the FIRST edit of the next pass, made
> before any `gen` runs**, and the note above it should say so.

### 26.2 The mechanism, landed

`core.harness_rev()` fingerprints the harness sources that define what an
expectation *means*. `cli.cmd_gen` stamps it into every vector
(`harness.rev`, plus `stack_arg_window` and `derived_arity` for readability),
and `cli._replay` **refuses** a vector whose stamp differs, printing
`STALE-VECTOR` with both fingerprints rather than comparing against a
different definition of "expected". The whole class becomes a hard error at
the point of use.

An **unstamped** vector is allowed without complaint: every vector written
before the stamp existed is unstamped, and refusing them all would make a
safety feature a wall. **The vectors measured in §27 are unstamped** — they
predate the stamp by minutes. Regenerating them stamps them; the protection
starts from the next `gen`.

`index.py` is deliberately excluded from the fingerprint: it maps symbols to
files and takes no part in producing or comparing an expectation, so a change
there must not invalidate a corpus.

### 26.3 Three defects the net-core pass measured — applied here

Its patches, written into `recon/analysis/net_test_coverage.md` because it was
told not to touch `tools/modtest/**`. All three are now applied.

1. **`index.default_trees` indexed ZERO net units** (`net_test_coverage.md`
   §1.2). `modules_only=True` is right for app, where stage 03 created module
   directories; **the net half of every stage tree is flat** — 1,155 top-level
   `.c` files at stage 00 and still 1,155 at stage 09. So every net symbol
   reported `refactored=ABSENT` and a net sweep would have reported "no
   disagreements" having replayed nothing. Same shape as every vacuous gate
   this project has found. Verified after the patch:

   ```
   app   canonical (2147 units, 2136 symbols)   refactored ( 660, 1604)
   net   canonical (1155 units, 1155 symbols)   refactored (1155, 1155)   <-- was (0, 0)
   ```

2. **A zero-case vector printed `OK(0/0)`** (§6.1) — a green pass on a symbol
   that never executed; 6 of the first 260 net vectors, all because every
   candidate hit the instruction cap. `_replay` now returns
   `stage="vacuous"` and `cmd_run` prints `VACUOUS(0 fixtures)` with the line
   "this symbol is UNTESTED, not passing". **§13L predicted this would be
   visible "only if someone reads the number"; it is now not a number.**

3. **`nptr = 2` is wrong in both directions** (§6.2). The app pass found the
   too-low half; net found the worse half —
   `ocrypto_constant_time_is_zero(p, n)` receives a pointer in `n`, loops ~2³¹
   times and caps out on 113 of 113 candidates, giving **0 fixtures**. Already
   addressed here by `generate.pointer_arg_mask` (§21.2), which derives a mask
   rather than a prefix and would give `n` a seeded integer.

### 26.4 Working-file namespacing

This pass wrote `run_*.json` / `grade_*.json` into the shared session
scratchpad, and the net pass's `glob("grade*.json")` picked up app results
once — caught only because app symbols appeared in a net kill-rate table.
App working files are now under `<scratchpad>/app_core/`.

### 26.5 One cross-core number worth keeping

Net measured **69 % kill (256/369)** at **59.7 % coverage** with 0 vacuous
vectors and 8/8 negative controls killed. The app figures in §27 land in the
same band. **The ~60-70 % kill rate is a property of the current mutation
generator and fixture search, not of either core** — which is the right way to
read it, and it means further improvement has to come from the generator.


---

## 27. ★ MEASURED RESULTS — this pass

All numbers from commands run in this pass. Vectors regenerated in full with
the final harness (fingerprint `c74709bc69344793`; the three net-core patches of §26.3 landed after and moved it to `c9132a14658714d0`); `run` and `grade` against
both trees; 16 mutants per symbol; `grade` on the refactored tree.

### 27.1 Mutation kill rate — BEFORE and AFTER, the same modules

This is the answer to task 1. **Both columns are whole modules, not the ten
hand-picked symbols of §18.6**, and both exclude symbols whose baseline fails
(§20.1), because a kill rate is undefined there.

```
             BEFORE (harness at f3dc81b9)      AFTER (this pass)
ipc          261/425  = 61 %  (44 symbols)  ->  315/440  = 72 %  (45 symbols)
sensors      404/705  = 57 %  (65 symbols)  ->  458/667  = 69 %  (63 symbols)
lib           49/61   = 80 %  ( 4 symbols)  ->   99/125  = 79 %  (12 symbols)
             --------                          --------
TOTAL        714/1191 = 60 %                ->  872/1232 = 71 %
```

**60 % → 71 %**, and the symbols that were the floor are gone:

```
                                   before   after   cause of the change
ipc_send_len_prefixed_packet         13 %    100 %   stack record (§21.3)
i2c_read_reg16_be                    19 %    100 %   pointer chain (§21.4)  [baseline now FAILS -- §22.1]
st25dv_reg_modify_low5                0 %     64 %   member_span (§21.1)
dev_send_cmd16_payload               79 %    100 %   pointer chain
st25dv_write_reg_pair                47 %     93 %   pointer chain + arity
```

**15 symbols scored zero before; 5 do now** across a corpus 2.4x larger.

### 27.2 Fan-out — ten modules, 330 symbols

`syms` counts symbols with a vector. `cov%` is aggregate CFG-instruction
coverage of the SHIPPED bytes. `kill` is aggregate over baseline-OK symbols;
`median` is the per-symbol median, and the gap between them is the honest
shape — a minority of long functions carries most of the surviving mutants.

```
module      syms   OK  FAIL  CCFAIL  DISAGREE   cov%     kill        median  zero-kill
ipc           47   45     0      2        0     77.9 %   315/440  72%   80%      0
sensors       87   73    13      1        0     57.2 %   458/667  69%   86%      2
notify        53   43     8      2        0     60.3 %   301/437  69%   86%      1
storage       35   26     8      1        0     64.1 %   180/298  60%   81%      1
ui            16   10     1      5        0     10.1 %    56/104  54%   75%      0
gui           36   30     5      0        1     57.9 %   133/359  37%   40%      1
esb           24   15     7      2        0     46.2 %    79/157  50%   75%      0
analytics     14   12     2      0        0     64.5 %   114/168  68%   81%      0
common         3    2     1      0        0    100.0 %     5/5   100%  100%      0
lib           15   13     1      1        0     97.3 %    99/125  79%  100%      0
             ---  ---   ---    ---      ---              --------
TOTAL        330  269    46     14        1              1740/2760 = 63 %
```

**Tree agreement: 329 of 330 symbols produce identical verdicts on stage 00 and
stage 09.** Every failure is a failure on both. The single disagreement is
§27.4 and it is a compile failure, not a behaviour change.

Against the §8.2 acceptance gate, **no module passes outright**, and the gate is
doing its job:

* **coverage ≥ 70 %** — passed by `ipc`, `common`, `lib` only. `ui` at 10.1 %
  is the worst result in this document and is explained, not excused: 5 of its
  16 symbols are `CCFAIL` and the rest are dashboard/onboarding state machines
  whose entry points are thread bodies.
* **kill rate ≥ 70 %** — passed by `ipc`, `common`, `lib` on aggregate and by
  seven modules on the median. `gui` at 37 % is the outlier and the cause is
  visible: `gui_bmp_bitmap_draw` 0 %, `gui_clock_draw` 6 % — large framebuffer
  routines where a mutant perturbs a pixel loop the fixtures do not enter.
* **agreement** — passed everywhere except the one compile failure.
* **negative controls** — §27.3.

### 27.3 Negative controls — 0 survived

`recon/tests/test_modtest_pilot.py --quick`, 96 symbols:

```
POSITIVE: 96 symbols, trees agree on 96, disagree on 0, 18 failing pairs
COVERAGE: 1687/3954 shipped CFG instructions = 42.7 %
NEGATIVE CONTROLS on 6 symbols: 12 killed, 0 SURVIVED, 9 not applicable
```

Better than the pilot's 1 survivor, and the controls now exercise the
stack-record criterion as well (the file compared only `expect` before, so the
field constants of every record-building function were unguarded there).

**One control in that list is not a control and should be discounted:**
`send_response_data_to_ble` "killed 3/3" three times — it is a `CCFAIL`, and
this file still counts a compile failure as a total failure (a rough edge
§18.8 already recorded). Three of the twelve kills are therefore vacuous. The
honest count is **9 real kills, 0 survivors, 12 not applicable.** A control
that never applied is not a control, and this project has shipped two of those.

### 27.4 The ONE tree disagreement — and it is a real stage-09 defect

`gui_area_clear`: `canonical=OK(42/42)`, `refactored=CCFAIL`.

```
error: conflicting types for 'uint32_t'; have 'unsigned int'
   23 | typedef unsigned int uint32_t;
In file included from .../stdint.h:11,
     from .../symbolized/app/gui/../../../headers/g1_log.h:93,
     from .../symbolized/app/gui/gui_area_clear.c:2
note: previous declaration of 'uint32_t' {aka 'long unsigned int'}
```

The refactor injected `#include "../../../headers/g1_log.h"` into a file whose
body carries the reconstruction convention's own `typedef unsigned int
uint32_t;`. `g1_log.h` includes `<stdint.h>` unconditionally, where
`__UINT32_TYPE__` is `long unsigned int` on this target.

**First hypothesis — a harness artefact from the compiler mismatch of §22.1 —
was tested and REJECTED.** Compiled directly with the firmware's own
`arm-zephyr-eabi-gcc 12.2` and its own headers, and again with Zephyr's
minimal-libc `stdint.h`, the file fails identically. Its stage-00 counterpart
compiles cleanly (`exit 0`).

Swept: **7 stage-09 TUs pair a body-local `typedef unsigned int uint32_t;` with
a refactor-injected generated header**, and all 7 fail to compile with the
firmware's own toolchain:

```
gui/gui_area_clear.c                   storage/try_to_save_file.c
notify/put_whitelist_app_from_app.c    audio/g1_audio_09.c
notify/mobile_send_notification_to_ble_device_test.c
esb/not_disturb_sync_data.c            ui/onboarding/onboarding_sync_data.c
```

**All 7 are listed in `recon/generated/app_retained_sources.cmake`**, i.e. the
stage-09 build compiles them. That contradicts the record in AGENTS.md that
stage 09 builds `exit 0` with 0 undefined.

**This needs the owner, and I am not asserting the ladder is broken.** One of
three things is true and I could not distinguish them without running the
build, which is out of scope here: the real build passes a flag or include
order that resolves `uint32_t` to `unsigned int`; or the build record predates
the header injection; or stage 09 does not currently build. The first is
testable in one command by the owner. What is certain is that these seven
files do not compile standalone under the toolchain the firmware was built
with, and that the harness found it by measuring rather than by inspection.

### 27.5 The §18.3 divergences, resolved

```
#  symbol                        pilot verdict       this pass
1  battery_model_state_update    FAIL 46/46          FAIL 0/46 at 62 % cov -- STILL OPEN, unchanged
2  __ieee754_expf                FAIL 12/37          OK 37/37   -- HARNESS (literal pad, §22.2)
3  imu_mahony_ahrs_update        FAIL 44/44          FAIL 0/44  -- HARNESS (oracle clobbers r0, §22.3)
4  st25dv_mailbox_send_message   FAIL  1/44          OK 44/44   -- HARNESS (callee arity, §22.7)
5  fuel_gauge_update             FAIL  1/43          FAIL 42/43 at 47 % cov -- unchanged, not chased
6  battery_soc_curve_model_init  FAIL 19/47          FAIL 0/49  -- REAL; AGENTS.md "CLOSED" is optimistic (§22.5)
7  curve_table_interp_201pt      FAIL 45/46          OK 45/45   -- fixture artefact
7  button_init                   FAIL 43/43          FAIL 0/43  -- unchanged, not chased
7  click_event_dispatch_loop     FAIL  3/45          FAIL 43/46 -- unchanged
7  load_usr_setting              FAIL  1/42          FAIL 41/43 -- unchanged
7  opt3007_chip_deinit           FAIL  1/42          FAIL 41/42 -- unchanged
7  ui_set_imu_pitch_task         FAIL  1/45          FAIL 44/45 -- unchanged
7  key_event_thread              FAIL  2/9           FAIL  8/16 -- unchanged
```

**Three of the six named divergences were harness defects, one was a fixture
artefact, one is real and contradicts AGENTS.md, and one is the known-open
defect.** That ratio — four of six not the reconstruction's fault — is the
reason the method note in §18.2 is the most valuable line in this document.

New in this pass: `i2c_read_reg16_be` is a **false proof** (§22.1),
`debug_print` and `update_burial_point_day_index` are new and uninvestigated
(§22.6), and the seven non-compiling stage-09 TUs above.

### 27.6 Honest reading

* The kill rate moved **60 % → 71 %** on the modules where a before/after
  exists, and the pathological floor cases are gone. It did **not** reach the
  70 % gate everywhere: `gui` 37 %, `esb` 50 %, `ui` 54 %.
* The net core independently measured **69 %** with a different corpus. The
  ~60-70 % band is a property of the **mutation generator and fixture search**,
  not of either core. Getting past it needs work on the generator — the
  surviving mutants are now concentrated in long functions whose interiors no
  fixture reaches, which is a coverage problem, not an observation problem.
* Coverage is the weaker half of the result: **63.5 % aggregate over the ten
  modules**, with three modules under 50 %. Every green result in §27.2 is
  worth exactly that fraction.

### 27.7 The next five things, in order (replaces §19)

1. **Fix the oracle's r0/r1 clobber** (§22.3) and then MEASURE how many of the
   remaining "golden faults, candidate returns" failures it explains. This is
   the highest-value item: it is a false-failure class of unknown size, and
   every number in §27.2 is contaminated by it to an unmeasured degree.
2. **Ask the owner about the seven non-compiling stage-09 TUs** (§27.4). One
   build command settles whether the ladder record is wrong or the harness is
   missing a flag.
3. **Raise coverage, not observation.** The surviving mutants are now
   concentrated in long functions whose interiors no fixture enters —
   `gui_bmp_bitmap_draw`, `gui_clock_draw`, `sync_to_slave`. That is a
   fixture-search problem. The pointer-chain dimension (§21.4) is the template:
   it was worth 74 % → 100 % on one function and 79 % → 100 % kill on another.
4. **Finish the fan-out**: `display` (89), `core` (142), `ble` (99),
   `audio` (137), `unsorted` (167) — 634 symbols, roughly 40 % of the app core.
5. **Root-cause `battery_model_state_update`** — still the only defect
   AGENTS.md and this harness agree is real and open.

---

# 28. ★ 2026-07-29 — THE r0-CLOBBER CLASS: MEASURED, FIXED, AND THREE VERDICTS OVERTURNED

This section is written by the pass that took §27.7 item 1 ("fix the oracle's
r0/r1 clobber and then MEASURE how many of the remaining failures it
explains — every number in §27.2 is contaminated by it to an unmeasured
degree"). It answers that.

**Headline, so nobody has to read to the end:** the class is real, it is
**fixed**, and it accounts for **3 of 46** app FAILs — much less than feared.
The much larger result is what looking for it uncovered. Three claims are
overturned, and **two of them are corrections of corrections**:

* §22.5's verdict that `battery_soc_curve_model_init` is a REAL defect is
  **withdrawn** — it is undecidable here (§28.5);
* `md5_process_block` is **withdrawn** as a failure for the same reason
  (§28.5.2);
* a load-bearing claim I wrote in §28.1 about the candidate being unaffected by
  this change is **falsified by my own test** and corrected in place (§28.1.0);
* and my first `callee_gpr_defs` was **unsound**, caught by a cross-check
  against a source that knows nothing about it (§28.2.1).

Exactly **six** app symbols read back a stack buffer handed to an opaque
callee, and **three of those six are the entire list of open "real defects"
this project's harnesses have ever named** (§28.5.2). That is the finding worth
carrying forward.

Every number below is from a command run in this pass at harness fingerprint
`e556ab5692bf509d`. The ledger entries are in §26.1 and were written the
moment the code landed, not at the end.

## 28.1 The fix, and why it did not need `emu`

`emu`'s order-keyed call oracle writes **r0 and r1 only** — `uc.reg_write(
UC_ARM_REG_R0, o0)` / `R1, o1` in `emu.Runner.run`. r2, r3 and r12 are never
touched. That is worth stating because §22.3 specified a fix in terms of
"preserve every caller-saved register the callee's ABI does not define,
r2/r3 always"; r2/r3 already survive, so the whole class reduces to two
registers and no r2/r3 work was needed.

The fix is in `tools/modtest/core.py` and touches **nothing** in
`tools/parity/emu.py`, which is frozen and shared with the net core:

* `core.callee_gpr_defs(core, va)` — which of r0/r1 the callee at `va` **can
  write**, derived from *its own shipped bytes* by a CFG walk. A nested `bl`
  merges the writes of what IT calls (bounded recursion, depth 3, with a cycle
  guard); a tail branch out of the function is treated as a call; **anything
  unclassifiable — an unresolved computed branch, a `blx` through a register,
  a callee with no catalogued size, a cycle, recursion past the depth, a walk
  that runs off the end of the catalogued extent or falls through into the
  next catalogued function — returns `None` and the register is clobbered
  exactly as before.** The analysis can therefore only ever over-report
  writes, so enabling it can remove false failures and cannot manufacture
  them. (The last two of those exits were **missing on the first attempt and
  the omission was unsound** — §28.2.1.)
* `_CoverageRunner` snapshots those registers at the `bl` and restores them at
  `emu.ORACLE_TRAMPOLINE` — the mapped `bx lr` every oracled call returns
  through, executed exactly once per call and by nothing else. The restore is
  bound to the call's own return address (checked against `LR`), so a `bl`
  into the function's own body — which `emu` never oracles, and which a linear
  call-site scan can also invent — cannot leak a stale restore into a later
  call.
* `ORACLE_PRESERVE` (env `MODTEST_ORACLE_PRESERVE`, default **on**) switches it.

**It is not a live-range analysis of the caller, and does not need to be.** If
the callee writes the register, the oracle clobbers it as before; if it does
not, preserving it is what the silicon does.

### 28.1.0 ⚠ A LOAD-BEARING CLAIM I MADE AND THEN FALSIFIED

I first wrote here that "the candidate is unaffected either way: code compiled
against an `extern` declaration never reads a caller-saved register across a
call, so this changes the GOLDEN's trace and never the candidate's." **That is
wrong, and the test that says so took two minutes.** Running four symbols'
candidates with `ORACLE_PRESERVE` forced on and off:

```
candidate observable UNCHANGED by preservation   18 fixtures
candidate observable CHANGED                      6 fixtures
   ipc_send_len_prefixed_packet  seed-0 .. seed-5
```

The cause is the harness's own stub. `core._UNDEF_STUB` is

```c
__attribute__((noinline,used,section(".oracle_stubs"))) unsigned NAME(void){return N;}
```

— a **definition in the candidate's own translation unit**, not an `extern`
declaration. So GCC applies `-fipa-ra` to the candidate exactly as it did to
the firmware: the stub visibly writes r0 (it returns a value) and visibly does
**not** write r1, so the compiler may keep a candidate value live in **r1**
across a call. The candidate is subject to the same mechanism as the shipped
code.

**This does not make the change unsound; it makes it more clearly right.**
Under the OLD oracle r1 was destroyed at every call whatever the callee did, so
a candidate relying on r1 was corrupted at *every* call site — a false-failure
source on the candidate side that nobody had noticed. Under the new oracle r1
survives exactly when the real callee leaves it alone. The residual mismatch is
narrow and pre-existing: the real callee writes r1 (so the oracle clobbers)
while the stub does not (so GCC kept a value there). That case is a strict
SUBSET of the old behaviour, so the change can only shrink it.

`ipc_send_len_prefixed_packet` regenerated and re-run under the new oracle:
`canonical=OK(42/42) refactored=OK(42/42) cov=100%`. The corpus-wide check that
nothing turned from OK to FAIL is §28.8.

Applying preservation asymmetrically (a candidate's generated stub with no
`oracle_target_map` entry preserves nothing) is therefore also NOT
self-evidently harmless, and is retained only because it is the conservative
direction — it leaves the candidate with today's behaviour.

### 28.1.1 A hole in the staleness guard, found by trying to run the control

The A/B below needs one arm with `MODTEST_ORACLE_PRESERVE=0`. `harness_rev()`
fingerprints **source**, and the two semantics switches that matter
(`DERIVED_ARITY`, `ORACLE_PRESERVE`) are **environment variables** — so the
control arm and the treatment arm wrote vector files that were
indistinguishable at the same fingerprint. `core.vector_staleness` now compares
the recorded `derived_arity` / `oracle_preserve` against the current run and
refuses on a mismatch. This closes a hole that existed for `DERIVED_ARITY`
from the moment §26.2 landed and that nobody would have noticed until two
results disagreed for no visible reason.

## 28.2 Scope of the class, swept over both cores

`callee_gpr_defs` over every callee with a Ghidra arity (the same universe
that produced the 310-of-2,383 over-wide arity number in §22.7):

```
                     app             net
callees              2404            1249
  unclassifiable      220  ( 9.2%)    113  ( 9.0%)
  writes r0 AND r1   1773  (73.8%)    760  (60.8%)
  leaves r0 alone     127  ( 5.3%)    147  (11.8%)
  leaves r1 alone     370  (15.4%)    342  (27.4%)
  leaves BOTH alone    86  ( 3.6%)    113  ( 9.0%)
```

**The analysis is cross-checked against an independent source and agrees
completely.** Ghidra's return kind for a callee is derived from its decompiled
signature and has nothing to do with this walk. A callee that returns anything
in r0 must write r0:

```
app callees this analysis says NEVER write r0     127
  Ghidra return kind void / f32 / f64 (agrees)    127
  Ghidra says the result is in r0 (contradiction)   0

app callees this analysis says NEVER write r1     370
  Ghidra: i32 227, void 125, f32 14, f64 4
  Ghidra says i64, i.e. r0:r1 (contradiction)       0
```

### 28.2.1 THAT CROSS-CHECK CAUGHT MY OWN UNSOUNDNESS, and it was live for an hour

The first version of the table above said 128 never write r0, and the
cross-check found **exactly one** contradiction: `0x0000d588`, which Ghidra
calls `i64`. It is catalogued as **four bytes**:

```
0000d588  eor  r3, r3, #0x80000000
```

That is a double-negation fragment with **no return instruction at all**. The
walk simply ran out of bytes and my code returned `frozenset()` — "writes
nothing" — about a function it had not finished reading. Every guarantee in
§28.1 about conservatism was true of the branches I wrote and false of the
branch I forgot: falling off the end of the catalogued extent, and falling
through into the next catalogued function, both now `return None`.

**The fan-out for §28.7 was already running against the unsound version and was
killed and restarted rather than allowed to finish.** The corrected numbers are
above; the corpus-level effect turned out to be one r0 callee and five r1
callees, and **none of them is called from any of the 330 symbols of §27.2**,
so the A/B of §28.3 is unchanged — but that was established by re-running it,
not by arguing it.

Worth stating for whoever writes the next such analysis: the bug was not in the
hard part. It was in assuming a `for` loop over a disassembler ends the way the
CFG ends.

Exposure on the 330 app symbols that had a vector at §27.2:

```
symbols with a vector                          330
  with >= 1 call site                          242
  with >= 1 r0-preservable call site            83
  with >= 1 r1-preservable call site           149
  with >= 1 of either                          156   (47 % of the corpus)
call sites, total                             3168
  r0-preservable                                165
  r1-preservable                               1554
  target not statically resolvable               86
```

**Net has roughly twice app's per-callee exposure** (31 % vs 17 % of callees
leave at least one of the two alone). That is a fact about the net corpus, not
about this pass, and the net agent should read §26.1 before reusing a vector.

## 28.3 THE MEASUREMENT — the A/B, and it is small

Two arms, same harness, same 46 symbols (every app FAIL in §27.2), vectors
**regenerated in each arm** so the golden is internally consistent:

* **arm B (control)** `MODTEST_ORACLE_PRESERVE=0` — the pre-2026-07-29 oracle;
* **arm A (treatment)** `MODTEST_ORACLE_PRESERVE=1` — this pass's oracle.

Arm B reproduced **46 FAILs of 46**, i.e. it re-derived §27.2's verdicts
exactly, which is the check that no *other* edit in this pass moved anything.

```
                        arm B (clobber)   arm A (preserve)
FAIL -> OK                                     3
   ext_flash_read       FAIL(26/36)   ->   OK(43/43)
   ext_flash_write      FAIL(26/36)   ->   OK(43/43)
   gui_bitmap_draw      FAIL(44/45)   ->   OK(45/45)
OK -> FAIL                                     0
still FAIL, fewer failing fixtures             2
   imu_mahony_ahrs_update FAIL(1/44)  ->  FAIL(25/43)   cov 86 % -> 100 %
   md5_process_block      FAIL(0/42)  ->  FAIL(0/41)
still FAIL, MORE failing fixtures              1
   key_event_thread       FAIL(8/16)  ->  FAIL(6/22)    <-- see the confound
verdict unchanged                             40
```

**So the answer to §27.7 item 1 is: 3 of 46 app FAILs — 6.5 % — were the
r0-clobber class outright, plus one large partial. Not the dominant
contaminant it was feared to be, and now zero rather than unmeasured. The
error bar the previous pass asked for is therefore: every FAIL count in §27.2
was inflated by at most three symbols, and no OK was ever a false pass caused
by it.**

**THE CONFOUND, stated rather than buried.** Each arm regenerates its own
vectors, and the fixture SEARCH depends on the golden's behaviour, so the two
arms do not always compare the same fixtures. Measured: **5 of 46 symbols have
a different case count between the arms** (`ext_flash_read` and
`ext_flash_write` 36→43, `key_event_thread` 16→22,
`imu_mahony_ahrs_update` 44→43, `md5_process_block` 42→41). For those five the
`n/m` numbers are not like-for-like and only the OK/FAIL verdict is.
`key_event_thread` is the one that moves the wrong way — 8 of 16 failing
becomes 16 of 22 — and it is 17 %-coverage thread-body code whose fixture set
changed underneath the comparison, not a regression this change caused; it is
FAIL in both arms. **The verdict column is confound-free: 3 flips, 0
regressions, 43 unchanged.** Running both arms over one frozen fixture set is
not possible here, because the whole point is that the golden behaves
differently.

The two full flips have a visible cause. `ext_flash_read` calls `0x7c080` and
`0x7c082` **three times between them, and neither writes r0 or r1**; the
golden was faulting on a pointer the hardware keeps. `gui_bitmap_draw` calls
`0x431a8` and `0x167a8`, which write **r0 only**, so r1 was the register the
old oracle destroyed.

Coverage moves too, and that had not been anticipated: a golden that faults
early stops executing. `imu_mahony_ahrs_update` went from 86 % to **100 %**
CFG-instruction coverage on the shipped bytes for the same symbol. Every
coverage figure in §27.2 for a symbol whose golden faulted is a *lower* bound
for the same reason.

### 28.3.1 Negative controls — the fix is shown not to have bought blindness

A change that makes failures disappear has to be shown not to have made the
suite blind. `scratchpad/app_core/negctl_r0.py`:

```
symbol                  tree         mutation                verdict
imu_mahony_ahrs_update  canonical    VNMLS read as VMLS      killed  (10/25 pass)
imu_mahony_ahrs_update  refactored   VNMLS read as VMLS      killed  (10/25 pass)
ext_flash_read          canonical    drop first bare call    killed
ext_flash_read          refactored   drop first bare call    killed
ext_flash_write         canonical    drop first bare call    killed
ext_flash_write         refactored   drop first bare call    killed
gui_bitmap_draw         canonical    drop first bare call    killed
gui_bitmap_draw         refactored   drop first bare call    killed
```

The first two matter most: the injected mutation is the **actual shipped
defect** of AGENTS.md finding 1b — reading the five `VNMLS.F32` at
0x26684/0x26688/0x2669c/0x266a8/0x266ac as `VMLS.F32`, which negates the whole
accelerometer error vector. The symbol the fix rescued still detects its own
historical defect. It is run against a **25-fixture sub-vector** on which the
baseline passes, because a kill against a failing baseline is not a control
(§20.1) — the full 43-fixture baseline is FAIL(25/43) for the reason in §28.4.

**Two of these eight "survived" on the first attempt and it was my control that
was broken, not the harness.** `drop_first_call` used a whole-file regex; a
stage-09 TU holds up to 39 functions, so on the refactored tree it deleted a
statement from whichever function came first in the file. That is §21.1
exactly, reproduced by the person who had just read §21.1, and it is the
**ninth** defeat of text anchoring recorded in this document. Rewritten to use
`mutate.member_span`, all eight kill.

## 28.4 `imu_mahony_ahrs_update` — the residual is 100 % COMPUTED NaN, and the obvious fix is UNSOUND

After the fix it is FAIL(25/43) rather than FAIL(1/44). All **18** residual
failures were classified individually, and every one of them is a divergence
in the **representation of a NaN**:

```
13 fixtures   a stored word         golden 0xFFC00000   candidate 0x7FC00000
 4 fixtures   the same, at the same address, other seeds
 1 fixture    call ordinal 1 arg    golden 0xFFFFFFFF   candidate 0x7FF7FFFF
```

Both sides are quiet NaNs; they differ in sign and, once, in payload. This is
the class AGENTS.md finding 1b already declares out of scope — "equivalent
float code does not preserve NaN sign/payload while writes compare
bit-exactly" — but the exclusion is applied to **seeded inputs** only, and
these NaNs are **computed**: a fixture supplies magnitudes that overflow to
infinity inside the body, and `inf - inf` produces a NaN whose sign depends on
operand order, i.e. on instruction selection.

**The obvious fix — canonicalise any quiet-NaN bit pattern in the event trace
to one token — is not sound and is not being made.** The trace is untyped: a
word is just 32 bits. Canonicalising the NaN range conflates
`0xFFFFFFFF` with a NaN, and `0xFFFFFFFF` is `-1`, which this firmware stores
constantly. One of the eighteen fixtures above literally has `0xFFFFFFFF` on
the golden side. A rule that cannot distinguish "the float unit produced a
NaN" from "the code stored −1" is a blind spot in exactly the place errors
hide. Recorded as a named, measured class instead:

> **COMPUTED-NaN REPRESENTATION.** A fixture whose float inputs overflow inside
> the body can make both sides produce NaNs that differ in sign or payload.
> Measured cost: 18 of 43 fixtures on `imu_mahony_ahrs_update`, 0 on any other
> symbol examined in this pass. The sound fix is at the INPUT end — do not
> generate fixtures whose float arguments overflow the body — not at the
> comparison end.

`imu_mahony_ahrs_update` is **not a reconstruction defect**; §22.3's verdict
stands and is now supported by a passing 25-fixture baseline instead of by an
argument.

## 28.5 ⚠ §22.5 IS WRONG — `battery_soc_curve_model_init` is UNDECIDABLE here, not defective

§22.5 concluded "the harness is right and the record is wrong" and asked for
AGENTS.md's **CLOSED** to be downgraded to a defect. **That conclusion does not
survive being looked at.** It carried its own caveat — the oracle-clobber
limitation "has not been ruled out for it" — and ruling it out is now
possible: with preservation on it is still FAIL(0/49) at 93 % coverage on both
trees, so the r0 class is not the cause. What *is* the cause is something
§22.5 did not consider.

The full normalised trace (`scratchpad/app_core/trace_diff.py`, which exists
because `events_head` stops at 48 and this symbol diverges at 74) shows that
in **every** fixture there is exactly **one** primary divergence, at call
ordinal 6:

```
   74  G ('C', 6, ('SP', 0), ('SP', 24), ('SP', 4), 'S', 'F', 'T', None)
       C ('C', 6, ('SP', 0), ('SP', 12), ('SP', 4), 'S', 'F', 'T', None)
```

First and third arguments identical; the middle stack object sits 12 bytes
elsewhere in the candidate's frame. Everything §22.5 quoted as independent
evidence — "four wholly different stored words", "4 ULP apart" — is
**downstream of that one difference**, and the mechanism is visible in the
shipped instructions immediately after the call:

```
0000e6d4  bl    #0xea18          <-- call ordinal 6, three stack out-params
0000e6d8  ldr   r1, [sp, #0xc]   <-- reads back what the callee WROTE there
0000e6ea  ldr   r3, [r2], #4     <-- reads back the out-param ARRAY at sp+0x1c
0000e6f2  add.w r3, r5, r3, lsl #2
0000e6f6  ldr   r3, [r3]         <-- faults: r3 is uninitialised stack
```

`emu` models the callee as opaque and writes **nothing** into an
out-parameter. So both sides read uninitialised stack; because their frames
differ, they read *different* uninitialised words; one becomes an invalid
pointer and one does not. 22 of the 49 goldens end in `Invalid memory read` at
`fault_off = 442`, which is `0xe6f6` — that instruction. The other 27 return,
and their candidates fault instead. It is the same single cause in both
directions.

Two harness limitations combine here and both are already documented:

* `normalise_events`' own docstring: *"a candidate whose frame lays out the
  same locals at different RELATIVE offsets while otherwise behaving
  identically will still fail (a false failure, not a false pass)"*;
* an **unmodelled callee out-parameter** read back by the caller — `emu` has
  `oracle_memory_writes` / `stack_objects` for reviewed cases and `modtest`
  populates neither.

**Verdict, replacing §22.5's:** this harness **cannot decide**
`battery_soc_curve_model_init`. It does not show a defect and it does not show
correctness. AGENTS.md's "CLOSED" is still not *established* — it rested on
`cfg_verify`, which AGENTS.md itself says is not evidence on this code — but
§22.5's claim that the harness overturns it is withdrawn. AGENTS.md is edited
to say exactly that, and nothing stronger.

This is the fifth time in this document a divergence reproducing identically
on both trees turned out to be the harness. It is also the first time the
*correction* was itself corrected. **Both facts argue for the same rule: read
the whole trace, find the FIRST divergence, and check whether everything after
it is a consequence before counting it as evidence.**

### 28.5.1 `battery_model_state_update` is in the same regime

The other "real and open" defect: **all 46** of its goldens fault. That is the
same signature and it has not been root-caused here. Its status should be read
as "not established by this harness" until someone runs the §28.5 trace
analysis on it. §28.5.2 measures it directly and puts it in the class.

### 28.5.2 ★ THE UNMODELLED-OUT-PARAMETER CLASS — 2 % of symbols, and it contains EVERY headline open defect

Having found the mechanism twice by hand, it is worth detecting rather than
guessing. `scratchpad/app_core/outparam_scope.py` runs the **golden only** and
flags the exact signature: at every oracled call remember the stack pointers in
r0-r3; afterwards, flag any read of a stack byte within 512 of one of them that
**this run never wrote**. That is "the caller read back what the callee was
supposed to fill", and it is a property of the shipped bytes — no candidate is
involved, so it cannot be confounded by the reconstruction.

Over every app symbol that had a vector (376 at the time, one fixture each):

```
symbols probed                                                  376
  read back a stack buffer they passed to an oracled call         6   (2 %)

  md5_process_block            lib        64 bytes      FAIL(0/41)
  battery_soc_from_curve       sensors    16 bytes      OK
  battery_model_state_update   sensors     8 bytes      FAIL(0/46)
  battery_soc_curve_model_init sensors     8 bytes      FAIL(0/49)
  gui_clock_draw               gui         4 bytes      OK
  batt_soc_curve_estimate      sensors     4 bytes      OK
```

**Six symbols. Three of them fail, and those three are the entire list of open
"real defects" this harness has ever named on the app core.** The other three
are exposed and pass, which is what makes the class a *limitation* rather than
a verdict: reading back four bytes of uninitialised frame does not always reach
an observable.

`md5_process_block` is the clearest case in the corpus and deserves its two
lines. Its body is:

```c
bytes_to_u32le_array(auStack_128, param_2, 0x40);   /* ORACLED: writes nothing */
piVar1 = (int *)auStack_128;
iVar9 = *piVar1;                                    /* reads 64 bytes of garbage */
```

The oracle fills none of `auStack_128`, so **the entire 64-byte MD5 message
block is uninitialised frame memory on both sides**, and the two frames are not
the same frame. Its trace diverges on exactly the four state words and nothing
else:

```
   1  G ('W', 536943568, 4, 2580117947)      C ('W', 536943568, 4,  858310752)
   2  G ('W', 536943572, 4, 1251016022)      C ('W', 536943572, 4, 1941127790)
   3  G ('W', 536943576, 4, 1763886999)      C ('W', 536943576, 4,  578222144)
   4  G ('W', 536943580, 4, 2553975612)      C ('W', 536943580, 4, 3392002027)
```

A compression function fed two different inputs produced two different outputs.
That is not evidence about the reconstruction. **`md5_process_block` is
withdrawn as a failure and reported as UNDECIDABLE**, exactly like §28.5.

**The fix is known and is not built here.** `emu` already has
`oracle_memory_writes` and `stack_objects` for reviewed out-parameters;
`modtest` populates neither, and generating them automatically means deciding
what an opaque callee writes — which is the callee's reconstruction, not the
caller's. For six symbols, **hand-written reviewed out-parameter fixtures are
the proportionate answer**, and they would settle
`battery_model_state_update`, which is the oldest open item in AGENTS.md.

Caveat on the number: **one fixture per symbol**, so 6 is a LOWER bound — a
path not taken by that fixture can hide another. It is not a lower bound by
much: the signature is structural, not input-dependent.

## 28.6 ★ ALL 43 SURVIVING app FAILs, TRIAGED BY THE SHAPE OF THEIR FIRST DIVERGENCE

Two of the three "real defects" turning out to be undecidable makes the whole
FAIL list worth re-reading rather than re-quoting. `classify_fails.py` labels
each surviving failure with the known limitation classes its first divergence
is **consistent with**. It is triage, not a verdict — but it says where to
start, and it says which failures are consistent with NO known limitation.

```
module      symbol                                 pass    golden  consistent with
analytics   load_sys_setting                       41/43   return  value
analytics   update_burial_point_day_index          1/41    return  value
common      debug_print                            41/42   mixed   call-target
esb         find_message_pool_entry_by_id          0/1     return  beyond-48-events
esb         local_esbs_ipc_service_recv            25/52   mixed   value
esb         nrf_rtc_set_alarm_channel              1/41    return  value
esb         rtc_channel_cc_read                    3/9     mixed   length/value
esb         spi_master_init                        2/42    mixed   value
esb         sync_buffer_available_space            2/40    mixed   call-target
esb         sync_message_signal_to_slave           41/43   mixed   frame-offset+value
gui         expand_bytes_via_lut32                 14/25   mixed   beyond-48-events/value
gui         fb_blit_rows_halved                    3/4     mixed   length
gui         gui_bmp_bitmap_draw_ex                 41/44   mixed   value
gui         gui_draw_timer_hms                     1/8     mixed   value
lib         md5_process_block                      0/41    return  OUT-PARAM
notify      ancs_gatt_dm_assign_handles            42/43   mixed   frame-offset
notify      ancs_subscribe_data_source             43/44   return  stack-record
notify      ble_ancs_data_req_thread               0/42    fault   call-target
notify      bt_setup_identities                    0/9     return  frame-offset/value
notify      discovery_completed_cb_ancs            41/43   return  value
notify      get_notification_counts_cmd_process    20/41   fault   value
notify      is_on_whitelist_by_identifier          44/46   return  value
notify      local_store_write                      0/42    return  stack-record
sensors     battery_model_state_update             0/46    fault   OUT-PARAM
sensors     battery_soc_curve_model_init           0/49    mixed   OUT-PARAM
sensors     build_status_notify_packet             9/12    mixed   value
sensors     button_init                            0/43    return  value
sensors     click_event_dispatch_loop              43/46   mixed   value
sensors     fuel_gauge_update                      42/43   return  value
sensors     i2c_read_reg16_be                      5/7     mixed   stack-record/value
sensors     imu_mahony_ahrs_update                 25/43   return  computed-NaN
sensors     key_event_thread                       6/22    fault   value
sensors     load_usr_setting                       41/43   return  value
sensors     opt3001_chip_init                      14/15   mixed   stack-record
sensors     opt3007_chip_deinit                    41/42   mixed   value
sensors     ui_set_imu_pitch_task                  44/45   return  value
storage     bt_dev_settings_commit                 42/44   return  value
storage     bt_dev_show_info                       0/41    return  stack-record
storage     bt_id_addr_check_and_enable            1/2     return  stack-record
storage     ccc_set_direct                         0/1     return  stack-record
storage     commit_default_config_record           1/3     return  frame-offset+value
storage     ext_flash_api_init                     22/43   mixed   value
ui          DashBoard_Reflash                      36/43   mixed   frame-offset/value
```

```
value only ................. 20   <-- consistent with NO known limitation
stack-record ...............  6   record CONTENT differs (§16.1 rule 7)
frame-offset (any) .........  5   §28.5 -- documented FALSE-failure mode
call-target ................  3   the candidate calls a different dependency
OUT-PARAM ..................  3   §28.5.2 -- UNDECIDABLE
length / beyond-48 .........  4   trace length, or diverges past events_head
computed-NaN ...............  1   §28.4
stack-record + value .......  1
```

**Twenty of forty-three are consistent with no limitation this document knows
about, and those are the honest reconstruction-defect candidates.** The other
23 need a harness answer or a hand-written fixture before they mean anything
about the code. That is the shape §27.2 could not show, and it is a very
different reading from "46 failures".

Two cautions about the table, both from getting it wrong first:

* **The classifier's own first version was wrong.** It tested for NaN bit
  patterns before testing for `('SP', n)` deltas, and labelled
  `ancs_gatt_dm_assign_handles` — whose divergence is `SP-100` vs `SP-104` —
  as `computed-NaN`, because a raw integer in the trace happened to match the
  NaN exponent mask. Structural markers must be tested before numeric ones.
  Fixed, and the NaN test now also requires every OTHER number in the tuple to
  agree.
* It reads only the **first five** recorded failures per symbol, which is what
  `cli._replay` keeps. A symbol whose fixtures fail for two different reasons
  can be under-labelled.

### 28.6.1 ★ FOUR of the six `stack-record` failures are a POINTER TO A STRING LITERAL

The triage puts six failures in `stack-record` — the record CONTENT criterion of
§16.1 rule 7, which is the criterion that took `ipc_send_len_prefixed_packet`
from a 13 % kill rate to 100 %. Five of the six mismatch on **the same byte**:
`arg 2, offset 4`. That is too regular to be six independent defects, and it
is not:

```
symbol                       ord arg off  golden word   candidate word
bt_dev_show_info               2   2   4   0x000f31a9    0x000549d0     41/41 fixtures
ccc_set_direct                 0   2   4   0x000f471e    0x00059f10      1/1
bt_id_addr_check_and_enable    0   2   4   0x000f322e    0x00054a2c      1/2
opt3001_chip_init              1   2   4   0x000f6521    0x00062a24      1/15
```

Every golden word is an address in the shipped image's string pool, and
decoding it settles it:

```
0x000f31a9 -> b'tead of expected 0x%04x\x00evt '
0x000f471e -> b' for conn %p\x00Error signing d'
0x000f322e -> b'0x%04x timeout with err %d\n\x00'
0x000f6521 -> b't I2C_MASTER status\r\n\x00Disabl'
```

They are **`printf` format strings** (into the middle of one, because the
linker shares string tails). The candidate's words are the same strings in its
own `.rodata`, linked immediately after its code. The record is a log/format
descriptor, and the harness is comparing **where the string lives**, which is
codegen, not behaviour — the identical reason §16.1 already blanks a record
word that points into the STACK.

> **NEW NAMED CLASS — READ-ONLY POINTER INSIDE A STACK RECORD.** `_CoverageRunner`
> blanks a record word that points into the stack window and compares every
> other word byte-exactly. A word pointing at a string literal or a `const`
> table is the same kind of number and is NOT blanked. Measured cost: **4 of
> the 43 surviving app FAILs**, one of them (`bt_dev_show_info`) failing
> 41 of 41 fixtures at 100 % coverage.

**The sound fix, specified and NOT built.** Do *not* simply blank it — that
would let a candidate pass the wrong string. `emu.ReadOnlyPointees` already
exists to compare a read-only pointee **by content**, and the record format
already has a per-offset marker (`"P"`). At `gen`, a record word that lands in
a read-only extent should be stored as a content marker — the sha256 of the
pointee up to its NUL, say — and `stack_args_mismatch` should recompute the
same from the candidate's word. That compares *which string*, which is the
behaviour, and ignores *where it is*, which is not. It is a vector-semantics
change and must not be made mid-sweep; it is item 1 of §28.9.

The other two `stack-record` failures are **not** this class and stay open:
`local_store_write` (golden word `0x00000000`, candidate `0x675f7261` = the
ASCII `"ar_g"`, at arg 0 offset 0) and `ancs_subscribe_data_source` (golden
`0x72ddab67`, candidate `0xc5fe1df2`, neither an address).

### 28.6.2 ★ A HARNESS DEFECT THAT MANUFACTURES TREE DISAGREEMENTS — `_expose_target` and the `#include`

Tree agreement is the headline metric of this whole design, so a defect that
invents disagreements matters more than its symbol count. **This one accounts
for four of the seven disagreements the 634-symbol fan-out found** (§28.8), in
two different disguises:

```
get_demo_image_source     display    OK / CCFAIL  "static declaration ... follows non-static"
refresh_box_field_timer   display    OK / CCFAIL  (same, on a sibling)
set_misc_286c_value       unsorted   OK / CCFAIL  "symbol ... not found after link"
uarte_nrfx_init           core       FAIL/ CCFAIL "symbol ... not found after link"
```

The two symptoms are one bug. If `_expose_target` de-staticises the definition
but not a later forward declaration, the compile fails outright; if it
de-staticises **nothing**, the definition stays `static`, GCC drops it as
unused, and the symbol is missing after the link — which is exactly the failure
the function was written to prevent. Measured:

```
set_misc_286c_value    de-staticised=0   static forms left=1
uarte_nrfx_init        de-staticised=0   static forms left=1
get_demo_image_source  de-staticised=1   static forms left=1
```

The `display` case is the clearest to read and is worked through below:

```
get_demo_image_source    canonical=OK  refactored=CCFAIL
   error: static declaration of 'get_demo_image_source' follows non-static declaration
refresh_box_field_timer  canonical=OK  refactored=CCFAIL
   error: static declaration of 'is_box_field_timer_expired' follows non-static declaration
```

`core._expose_target` drops `static` from the target's definition (stage 07
gives TU-private symbols internal linkage, and GCC then does not emit an unused
`static`, which would make the symbol untestable in one tree only). Its
docstring already says it must also de-staticise a **forward declaration** left
behind, "measured on `trigger_touch_key_hw_reset`". It does not always manage
it. Reproduced directly:

```
_expose_target(unit.text, 'get_demo_image_source') -> de-staticised 1 occurrence
   |  static void get_demo_image_source(unsigned int);      <-- still static
```

The cause is the walk-back that finds the start of the declaration:

```python
start = max(text.rfind(";", 0, index) + 1,
            text.rfind("}", 0, index) + 1,
            (comment_end + 2) if comment_end >= 0 else 0)
...
if before.strip() or not after_kw[:1].isspace():
    continue                     # `static` must open the declaration
```

In `g1_display_cc03.c` the forward declaration is preceded by
`#include "g1_display.h"`. A preprocessor directive ends with a **newline**,
not with `;`, `}` or `*/`, so the walk-back steps over it, `before` is
`'\n#include "g1_display.h"\n'`, `before.strip()` is truthy, and the
declaration is skipped. Stage 09 is not at fault; the merged TU is legal C
until the harness edits it.

The other two are the same shape with different directives — `set_misc_286c_value`
is preceded by four `#include` lines, `uarte_nrfx_init` by three `#define`
lines:

```
'...\n#include <stddef.h>\nstatic void set_misc_286c_value(uint32_t param_1) {'
'...\n#define VC(a) (*(volatile char *)(a))\n\nstatic int uarte_nrfx_init(int param_1){'
```

**Fix (three lines, DEFERRED to the next pass):** accept `before` when it
consists only of whitespace and complete preprocessor-directive lines. It is
not applied here for the reason in §28.9: `harness_rev()` hashes whole files,
so any edit to `core.py` mid-sweep invalidates every vector this pass has
generated.

**How this pass reports around it instead of hiding it:** the defect has an
exact and greppable signature, so every disagreement carrying
`static declaration of '…' follows non-static declaration` is counted
separately in §28.8 and excluded from the agreement figure, rather than being
either silently dropped or reported as a stage-09 finding.

### 28.6.3 ★ THE UNIT BOUNDARY LEAKS IN A MERGED TU — `-fipa-vrp` deletes a call the shipped code makes

The `ble` fan-out produced one tree disagreement that is a **behaviour**
disagreement, not a compile failure — the most serious kind this design can
report:

```
read_appearance    canonical=OK(41/41)   refactored=FAIL(0/41)
                   golden ncalls=2, candidate ncalls=1, and the candidate's
                   event hash is IDENTICAL for every fixture
```

An event hash that does not vary with the input is the tell. The two source
bodies are **character-for-character identical**; only the enclosing TU differs
(canonical: `read_appearance.c`, one member; refactored:
`g1_ble_cc02.c`, eight members, one of which is the callee
`ble_appearance_value`). Compiling both and disassembling:

```
== canonical (38 B)                       == refactored (32 B)
push {r4,r5,lr}                            push {r0,r1,r2,r3,r4,lr}
...                                        mov  r1, r3
bl   #0x82a40    <- ble_appearance_value   movw r3, #0x341      <-- CONSTANT, no call
strh.w r0,[sp,#8]                          strh.w r3,[sp,#8]
...                                        ...
bl   #0x82a44    <- bt_gatt_attr_read      bl   #0x82b40
```

The shipped image makes both calls. `ble_appearance_value` is
`{ return 0x341; }`, and in the merged TU GCC can SEE that — so it substitutes
the return value and deletes the call. `__attribute__((noinline))` is applied
to that definition (verified: 7 of 7 members marked) and does not stop it,
because this is not inlining.

**Bisected against the flag set, and it is exactly one flag:**

```
(current UNIT_BOUNDARY_CFLAGS)                          size=32 calls=1
-fno-ipa-vrp                                            size=32 calls=2   <--
-fno-ipa-modref / -fno-ipa-bit-cp / -fno-ipa-cp-clone   size=32 calls=1
-fno-inline-functions-called-once / -fno-ipa-profile    size=32 calls=1
-fno-toplevel-reorder                                   size=32 calls=1
```

**Interprocedural value-range propagation**, which is not in
`UNIT_BOUNDARY_CFLAGS` and is not disabled by `-fno-ipa-cp`.

> **NEW NAMED CLASS — UNIT-BOUNDARY LEAK VIA IPA-VRP.** When a merged TU
> defines a callee whose return value GCC can pin, the candidate does not make
> the call the shipped code makes. It can only happen in a MERGED tree, so it
> shows up as a **tree disagreement** — the metric this whole design exists to
> report. Fix: add `-fno-ipa-vrp` to `core.UNIT_BOUNDARY_CFLAGS`. One line,
> empirically verified above, DEFERRED for the fingerprint reason in §28.9.

Stage 09's `cc` units are call-cohesion units — they group callers WITH their
callees by construction, so this class is aimed squarely at the part of the
ladder the harness is meant to check. §27.2's "329 of 330 agree" was measured
with this leak present and should be read accordingly.

## 28.7 `i2c_read_reg16_be` — the false proof stands, and is now in AGENTS.md

Re-measured under this pass's harness: **FAIL(5/7) on both trees at 100 %
coverage**, unchanged by r0 preservation. §22.1's diagnosis is unaffected: the
source header claims `parity: 300/300 trials, PROVEN`, and the body spells a
two-element `i2c_msg`-shaped descriptor as **six independent stack locals**
relying on the compiler to lay them out contiguously in declaration order:

```c
unsigned char *local_28; unsigned int local_24; unsigned char local_20;
unsigned short *local_1c; unsigned int local_18; unsigned char local_14;
... iVar1 = (...)(*param_1, &local_28, 2, (short)param_1[1]);
```

C guarantees no such layout and GCC does not produce it — offset 4 of the
candidate's descriptor holds `param_1` spilled (`0x20011008`) where the
shipped code has the constant `1`. Verified under the firmware's own
`arm-zephyr-eabi-gcc 12.2`, so it is not an artefact of the harness compiling
with `arm-none-eabi-gcc 15.1.0`. **It is a reconstruction defect and it is now
recorded in AGENTS.md.** It has NOT been repaired here — the repair is a
`struct i2c_msg msgs[2]`, it touches a canonical address-keyed tree, and it
needs its own re-proof.

## 28.8 ★ THE FAN-OUT — `display`, `core`, `ble`, `audio`, `unsorted`

§27.7 item 4. All 634 symbols of the five remaining app modules, generated and
replayed against both trees at `e556ab5692bf509d`.

```
requested                                    634
  gen SKIPped (no catalogued size)            40
  lost to a batch crash, then recovered       23
  lost outright (`main`, crashes the harness)  1
  measured                                   593
```

```
module      syms   OK  FAIL  CCFAIL  VACUOUS  DISAGREE  (of which harness)   cov%
audio        135  100    20      15        0         1                  1   57.7%
ble           96   75    19       2        0         1                  1   48.4%
core         139  109    20       8        2         1                  1   60.5%
display       86   69     7       9        1         2                  2   56.2%
unsorted     137  112    20       4        1         2                  1   70.2%
            ----  ---   ---     ---      ---       ---                ---
TOTAL        593  465    86      38        4         7                  6
```

**The `(of which harness)` column is a MANUAL attribution, not a machine
label.** `final_table.py`'s automatic signature match finds only 3 of the 6,
because two of them fail with `symbol … not found after link` rather than a
recognisable compiler message and one is a behaviour failure with no message at
all. Each of the six is attributed on per-symbol evidence reproduced in
§28.6.2 (four, by running `_expose_target` and counting what it de-staticised),
§27.4 (one, the `uint32_t` typedef) and §28.6.3 (one, bisected to a single
compiler flag). Anyone re-deriving the column from the script alone will get 3;
that is the script being crude, and it is said here rather than left to be
discovered.

### 28.8.1 Tree agreement — 586 of 593, and SIX of the seven disagreements are the harness

```
symbol                              module     canonical / refactored   cause
get_demo_image_source               display    OK   / CCFAIL   _expose_target  (§28.6.2)
refresh_box_field_timer             display    OK   / CCFAIL   _expose_target  (§28.6.2)
set_misc_286c_value                 unsorted   OK   / CCFAIL   _expose_target  (§28.6.2)
uarte_nrfx_init                     core       FAIL / CCFAIL   _expose_target  (§28.6.2)
get_audio_msgq_used_count           audio      OK   / CCFAIL   uint32_t typedef (§27.4)
read_appearance                     ble        OK   / FAIL     -fipa-vrp leak  (§28.6.3)
foreach_attr_entry_invoke_callback  unsorted   FAIL / OK       NOT investigated
```

**Nothing here is evidence against the refactor ladder.** Four are one
deferred three-line harness fix, one is the `uint32_t` typedef collision §27.4
already raised with the owner (this is its **eighth** instance), and one is the
`-fipa-vrp` unit-boundary leak. The seventh, `foreach_attr_entry_invoke_callback`,
disagrees in the **opposite** direction — the canonical tree fails and the
refactored one passes — and was not chased.

Corrected for the six known-harness cases the fan-out's tree agreement is
**592 of 593**.

### 28.8.2 Against the §8.2 acceptance gate — say it plainly

```
module      coverage >= 70 %   kill >= 70 %          verdict
display        56.2 %  NO      see 28.8.3            FAILS the gate
core           60.5 %  NO                            FAILS the gate
ble            48.4 %  NO                            FAILS the gate  (worst)
audio          57.7 %  NO                            FAILS the gate
unsorted       70.2 %  YES                           coverage only
```

**Not one of the five modules passes §8.2 on coverage, and only `unsorted`
clears the bar at all.** That is the same shape §27.6 reported for the first
ten modules and it is not improving: the aggregate over all fifteen app modules
measured by this harness is now in the high 50s. `ble` at **48.4 %** joins
`ui` (10.1 %) and `esb` (46.2 %) at the bottom, and its 19 FAILs should be read
as 19 failures of a body less than half of which any fixture enters.

`display` also carries **9 CCFAIL and 1 VACUOUS out of 86** — the highest
untestable fraction of any module measured so far (12 %). Six of the nine are a
Zephyr `Z_HZ_ticks` header problem that hits BOTH trees, i.e. an environment
gap in `ZEPHYR_CFLAGS`, not a defect in either tree.

### 28.8.3 Mutation kill rate — a SAMPLE, and it is labelled as one

Grading 634 symbols at 24 mutants was not reachable in this pass's compute
budget alongside two full A/B arms. A **20-symbol random sample per module**
(`random.Random(20260729).sample`, so it is reproducible and was fixed before
any result was seen) was graded at 12 mutants:

```
module      sample  baseline OK  graded  killed  aggregate     median  zero-kill
display         19           15      15      68   68/118  58%     92%        0
core            18           18      17      79   79/140  56%     67%        3
ble             19           15      15      96   96/133  72%     83%        0
audio           20           18      16      97   97/151  64%     73%        0
unsorted        16           14      14      56   56/93   60%     78%        0
                                                 -------
TOTAL                                            396/635 = 62 %
```

(`sample` is under 20 where a drawn symbol had no vector; `graded` excludes
symbols whose baseline FAILs, where a kill rate is undefined — §20.1.)

**Against the §8.2 kill bar of 70 %: `ble` passes on aggregate (72 %), nobody
else does; on the per-symbol median all five pass.** The aggregate/median gap
is the same shape §27.2 described — a minority of long functions carries most
of the surviving mutants — and `core` is the module where it bites, with 3 of
17 graded symbols killing nothing at all.

**62 % aggregate on this sample sits inside the 60-70 % band both cores have
measured with three different corpora** (app §27.1 71 %, net §26.5 69 %). §27.6
called that a property of the mutation generator and fixture search rather than
of the code, and a third independent sample not moving it is the strongest
evidence for that reading so far.

### 28.8.4 A harness robustness defect the fan-out exposed

`cli.cmd_run` has **no per-symbol guard**. An unhandled exception inside
`compile_candidate` kills the whole batch and takes every remaining symbol in
it with it. Measured: `fanrun_core_0` died after 13 of 24 symbols on

```
File "tools/modtest/core.py", line 1775, in _compile_candidate
    base = text_section["sh_addr"]
TypeError: 'NoneType' object is not subscriptable
```

— `elf.get_section_by_name(".text")` returned `None`. **23 symbols were
silently lost**, and only reappeared because the requested list was reconciled
against the produced rows rather than trusted. Re-running them one process per
symbol recovered 23 of 24; the 24th is `main`, which is the symbol that
actually triggers it and is the only symbol in the whole 634 with **no result
at all**.

Two fixes, both deferred with the rest (§28.9): wrap the per-symbol body of
`cmd_run` in a `try`/`except` that records `stage="error"`, and raise a
`RuntimeError` when the linked object has no `.text` so it becomes an ordinary
CCFAIL instead of a crash.

### 28.8.5 ★ REGRESSION CHECK — 110 of 110, zero regressions

The A/B of §28.3 only covers symbols that were already failing. The direction
that matters for a change like this is the other one: did any **passing**
symbol start failing? Every §27.2 symbol that was `OK` **and** has at least one
r0/r1-preservable call site — the only ones whose golden the change can alter —
was regenerated and re-run:

```
previously-OK and EXPOSED symbols re-run   110
  still OK                                 110
  now FAIL / CCFAIL / VACUOUS                0
```

This is also the answer to the worry §28.1.0 raised: the candidate *is* subject
to `-fipa-ra` through its own stubs, and preservation still broke nothing.

## 28.9 WHAT THIS PASS DID NOT DO, AND WHY

Enumerated rather than implied. Several of these are cheap and were skipped for
one specific reason — **`core.harness_rev()` hashes whole files**, so any edit
to `core.py` / `cli.py` / `generate.py` / `mutate.py` mid-sweep makes `run`
refuse every vector generated before it. Three known-good fixes are therefore
queued for the *start* of the next pass rather than the end of this one.

**Deferred harness fixes — apply these FIRST, before any `gen`:**

0. **`-fno-ipa-vrp` in `UNIT_BOUNDARY_CFLAGS`** (§28.6.3) — one line, bisected
   and verified. It manufactures TREE DISAGREEMENTS, which is the design's
   headline metric, so it goes first.
1. **Read-only pointer inside a stack record** (§28.6.1) — 4 of 43 surviving
   app FAILs. Store a content marker (sha of the pointee to its NUL) instead of
   the raw address, so *which string* is compared and *where it lives* is not.
   Do NOT just blank the word.
2. **`_expose_target` walks over a `#include`** (§28.6.2) — manufactures tree
   disagreements, which is the design's headline metric. Accept a `before`
   consisting only of whitespace and complete preprocessor lines.
3. **`cli.cmd_run` should count UNSTAMPED vectors** — the net pass's §9.1 patch,
   accepted in substance. `vector_staleness`' docstring already claims
   `cmd_run` reports the gap and it does not.

**Not done, with reasons:**

* **The computed-NaN class is measured but NOT fixed** (§28.4). The obvious fix
  — canonicalise quiet-NaN bit patterns in the trace — conflates `0xFFFFFFFF`
  with a NaN, and `0xFFFFFFFF` is `-1`. The sound fix is at the input end and
  is a fixture-generator change.
* **The unmodelled out-parameter class is measured but NOT fixed** (§28.5.2).
  Six symbols; the proportionate answer is hand-written reviewed
  `oracle_memory_writes` fixtures, which is per-callee reconstruction work.
* **`battery_model_state_update` is NOT root-caused.** It is placed in the
  out-parameter class by measurement, which is strictly more than was known,
  but the reviewed fixture that would decide it is not written.
* **`i2c_read_reg16_be` is NOT repaired** (§28.7). The repair is a real
  `struct i2c_msg msgs[2]` in a canonical address-keyed tree and needs its own
  proof; recording it was the task.
* **The net core's EMPIRICAL half of the r0 measurement was not run.** Net
  vectors, net sources and `net_test_coverage.md` are the other agent's under
  the concurrency rule, and this pass did not touch them. What IS provided is
  the static scope on net (§28.2) and a ledger warning (§26.1) — including
  that its pinned `936cee0b67396ca5` carries the unsoundness of §28.2.1.
* **The 174 app symbols of §27.2 that are NOT exposed to the change were not
  regenerated.** They have no r0/r1-preservable call site, so the new oracle
  cannot alter their golden — but their vector files are now stamped with an
  older fingerprint and `run` will refuse them. The corpus is internally
  consistent only for what this pass regenerated. That is a bookkeeping debt,
  not a measurement gap.
* **Kill rate for the five fan-out modules is a SAMPLE, not a census** — see
  §28.8. Grading 634 symbols at 24 mutants was not reachable in this pass's
  compute budget alongside two full A/B arms.
* **`cfg_verify` was not run and is not cited anywhere in this section**, per
  the standing rule.

## 28.10 WHERE THE APP CORE STANDS, AND THE NEXT FIVE THINGS (replaces §27.7)

**924 app symbols now have a golden vector across 15 modules** — 330 from
§27.2 plus 593 measured here plus `ipc_send_len_prefixed_packet` regenerated
during §28.1.0. Of the 634 the fan-out targeted, 40 have no catalogued size and
1 (`main`) crashes the harness.

The honest one-paragraph summary of this pass: **the r0-clobber class was real,
is fixed, and was small (3 of 46).** Hunting it turned up four larger things —
an unsound version of my own analysis (§28.2.1), a false claim of my own
(§28.1.0), and three previously unnamed false-failure classes that between them
account for **at least 11 of the 43 surviving app FAILs and 6 of the 7 fan-out
tree disagreements**. Two verdicts inherited as "real defects"
(`battery_soc_curve_model_init`, `md5_process_block`) are withdrawn as
undecidable. The number of app symbols this harness can point at and say
"this is probably the reconstruction's fault" is now **20**, not 46+86.

1. **Apply the four deferred harness fixes, in one commit, before any `gen`**
   (§28.9 items 0-3, plus the two robustness fixes of §28.8.4). They are all
   small, all bisected or reproduced, and every one of them currently
   contaminates a headline number. Then regenerate the corpus once.
2. **Write reviewed out-parameter fixtures for the six symbols of §28.5.2.**
   That is the whole class, it is six symbols, and it would settle
   `battery_model_state_update` — the oldest open item in AGENTS.md — one way
   or the other.
3. **Work the 20 `value`-only FAILs of §28.6**, which is the first list this
   project has had of failures consistent with no known harness limitation.
4. **Raise coverage.** Unchanged from §27.7 item 3 and now more urgent: the
   fan-out's five modules average **58 %**, `ble` is at 48 %, and every green
   result is worth exactly that fraction. The kill rate will not move past
   ~65 % until the fixture search enters the long functions.
5. **Ask the owner the §27.4 question** — it is now **eight** stage-09 TUs that
   pair a body-local `typedef unsigned int uint32_t;` with a refactor-injected
   generated header (`get_audio_msgq_used_count` joins the seven). One build
   command settles whether the ladder record or the harness is wrong.

---

# 29. ★ 2026-07-29 (second pass) — THE DEFERRED HARNESS FIXES, LANDED AND MEASURED

Written by the pass that took §28.10 item 1 ("apply the four deferred harness
fixes, in one commit, before any `gen`"). It also takes the four patches the
net pass specified in `net_test_coverage.md` §12 and §9.1 but could not apply,
because it was barred from `tools/modtest/`.

**This section is appended incrementally as the work happens, not written at
the end.** Numbers appear when the command that produced them has been run.

## 29.1 The burst — what landed, in one edit window, before any `gen`

`harness_rev()` hashes whole files, so an edit mid-sweep invalidates every
vector generated before it (§28.9). Everything below therefore landed FIRST,
in one window, and `tools/modtest/` was then left alone.

```
harness_rev BEFORE   e556ab5692bf509d   (§28's fan-out)
harness_rev AFTER    950823ab6c3bd815
harness_env AFTER    outparam_fill=True derived_arity=True oracle_preserve=True
                     stack_arg_window=48 outparam_window=512
                     drop_outparam_uninit=False
```

| # | fix | source | file |
|---|-----|--------|------|
| 0 | `-fno-ipa-vrp` in `UNIT_BOUNDARY_CFLAGS` | §28.6.3 | `core.py` |
| 1 | read-only pointer inside a stack record → content marker | §28.6.1 | `core.py` |
| 2 | `_expose_target` walks over a `#include` | §28.6.2 | `core.py` |
| 3 | `vector_staleness` FAILS CLOSED + `cmd_run` counts unstamped | §28.9 item 3, net §9.1 | `core.py`, `cli.py` |
| 4 | per-symbol guard in `cmd_run`; no `.text` → `RuntimeError` | §28.8.4 | `cli.py`, `core.py` |
| 5 | unmodelled out-parameter — **FILLED**, not dropped | §28.5.2, net §12.1 | `core.py`, `generate.py` |
| 6 | `pointer_arg_mask` keeps a PASS-THROUGH pointer | net §12.2 | `generate.py` |

Declined, with the measurement that decided it, in §29.6: net §12.3
(`for(;;) panic()`) and net §12.4 (ordered read trace).

## 29.2 ★ THE OUT-PARAMETER IS NOW FILLED, NOT DROPPED — and that DECIDES the class

The net pass specified a safe patch (drop any fixture whose golden read an
unwritten byte of a buffer it handed to an opaque callee) and named a stronger
one it did not build (have the oracle WRITE that buffer). **The safe version
was built first, measured, and then replaced**, because the measurement showed
what it costs:

```
                              DROP (net's safe patch)      FILL (landed)
md5_process_block             41 cases -> 1,   cov 0%      41 cases, cov 99%
battery_model_state_update    46 cases -> 1,   cov 0%      41 cases, cov 15%
battery_soc_curve_model_init  49 cases -> 3,   cov 17%     47 cases, cov 89%
```

Dropping cannot manufacture a failure, but it converts the three symbols that
carry every open "real defect" on this core into symbols with **no test at
all**. That is honest and useless.

**The fill, and why it is frame-independent.** At the moment a stack byte
inside a buffer this run passed to an oracled call is READ, and nothing in the
run has written it, the byte is given a deterministic value keyed by
`(call ordinal, argument index, offset FROM THE POINTER)` — on both sides.
The key is the point. `emu` seeds all of RAM from a PRNG, so those bytes were
never random: they were deterministic **by address**, and the shipped frame and
the candidate's frame put the same buffer at different addresses. Keying on
the offset from the pointer the callee received is what the real callee's
output is like.

Two implementation facts, both checked rather than assumed:

* **Writing memory inside a `UC_HOOK_MEM_READ` callback does change the value
  the access returns.** Verified against unicorn directly, in isolation, before
  any of this was relied on (`ldr r1,[r0]` with a hook that rewrites the word:
  `r1 = 0x11223344`, not the pre-existing `0xdeadbeef`).
* **`written` is the wrong set to test "initialised" against, and using it
  would have flagged almost everything.** A byte the prologue pushed is
  classified into `pushed`, so the epilogue's `pop` reads a byte not in
  `written`, and a 512-byte window from a stack local reaches the frame's own
  saved registers on most functions. The test is `not in written and not in
  pushed`. Rule 6's `inherited` set is left with exactly its previous meaning,
  because it defines what a stored record contains.

**Overlapping windows are resolved by the CLOSEST PRECEDING pointer**, then by
the most recent call — not by "the last region registered", which would be
decided by how far apart the frame put two arguments, i.e. by the very thing
the fill exists to be independent of.

### 29.2.1 ★ `md5_process_block` IS DECIDABLE, AND IT DIVERGES — §28.5.2 is corrected

§28.5.2 withdrew `md5_process_block` as a failure and reported it UNDECIDABLE,
because "the entire 64-byte MD5 message block is uninitialised frame memory on
both sides". With the fill that is no longer true, and the comparison is
well-posed. It was verified to be well-posed rather than assumed:

```
golden   reads 16 block words in [base, base+64)  -- 0 differ from the fill pattern
candidate reads 16 block words in [base, base+64) -- 0 differ from the fill pattern
golden   uninit stack reads = 64, all filled;  candidate = 64, all filled
initial state words (scratch, seeded by address) -- identical on both sides
```

Both sides consume the **same block and the same state**, and still produce
different output:

```
golden     0x91f37843 0xab26d489 0xd0f175ff 0x67da44ff
candidate  0x28a00344 0x3b112568 0x4a5c50da 0xce951013
```

An independent Python MD5 compression function over the same state and the same
block returns the **candidate's** four words exactly. So the reconstruction is
textbook MD5 and the shipped bytes are computing something else on this input.

> **`md5_process_block` is restored to the failure list as a DECIDED
> divergence.** It is not the harness. Whether the shipped function is a
> modified MD5 or the reconstruction has a defect is not settled here — what is
> settled is that this harness can now tell them apart, which it could not
> yesterday.

The same machinery applies to `battery_model_state_update`, whose coverage goes
from 6 instructions (0 %) to 200 (15 %) — the oldest open item in AGENTS.md is
now being executed rather than faulting at its first out-parameter read.

## 29.3 ★ WHY COVERAGE IS LOW — diagnosed against the corpus, not guessed

§28.8.2 reported "not one of the five modules passes §8.2 on coverage" and
§28.10 item 4 asked for it to be raised. The first thing to establish is what
the number is measuring, because the two obvious readings differ by thirty
points.

```
                    instruction-WEIGHTED      per-symbol MEAN
audio    (135)              57.7 %                 84.6 %
ble       (96)              48.4 %                 83.2 %
core     (140)              58.2 %                 82.0 %
display   (86)              56.2 %                 81.1 %
sensors   (87)              47.0 %                 84.9 %
ui        (16)               9.5 %                 77.6 %
unsorted (137)              70.2 %                 89.4 %
lib       (15)              97.3 %                 98.0 %
ALL      (924)              52.4 %                 82.5 %
```

**§28.8's column is instruction-weighted, and it is carried by a handful of
very long functions.** `ui` is 9.5 % weighted and 77.6 % mean because
`DashBoard_Reflash` alone is 4,911 CFG instructions at 3 % — more than the
whole rest of the module.

```
symbols below 70 % coverage      206 of 924  (22 % of symbols)
  instructions they hold      30,335 of 50,040  (61 % of the corpus)
the 20 worst hold             14,799            (30 % of the corpus)
```

The 20 are `DashBoard_Reflash`, `battery_model_state_update`,
`spec_ble_command_hook`, `imu_fusion_thread`, `audioStreamFileManagerHandler`,
`main`, `display_dispatch_thread`, `check_work_mode`, `sync_to_slave`,
`hci_vs_init`, `master_process_audio_fw_load_req`, `display_thread_handler`,
`dmic_stream_start`, `fuel_gauge_update`,
`low_speed_peripheral_dispatch_thread`, `uarte_nrfx_isr`,
`flash_firmware_update_transfer`, `local_esbs_ipc_service_recv`,
`touch_key_thread`, `try_enter_low_power_mode`. **Every one of them is a
thread body, a dispatcher, an ISR or a command hook.** That is a shape, and it
points at a channel rather than at a difficulty.

### 29.3.1 Two hypotheses tested and REJECTED, before the one that held

Recorded because rejecting them is what made the third one credible.

* **"The candidate budget truncates the search."** `select` runs
  `fixtures[:budget]` with `budget=400`, in a fixed dimension order, so a
  symbol with more candidates would silently lose the LAST dimensions — which
  are the callee-result and global x callee-result sweeps the generator's own
  docstring calls dominant. Measured: **0 of 924 symbols reached 400
  candidates** (worst 325). Rejected. *(It becomes true after this pass's
  additions, which is why the default is raised to 600 in the same burst.)*
* **"`literal_globals`' 24-address limit binds on the big functions."**
  Measured: **0 of 924 symbols hit the limit**; `DashBoard_Reflash` names 9
  globals, `spec_ble_command_hook` 9, `check_work_mode` 16. Rejected.

### 29.3.2 ★ THE POINTEE DIMENSION EXISTED AND WAS NEVER USED — 0 of 25,524

`Fixture` has carried a `mem` dimension — *"[[arg_index, offset, hex]] pointee
writes"* — since the pilot. Counted over every fixture on disk:

```
fixtures in the app corpus                       25,524
  with a pointee override ('mem')                     0
```

So the content behind every pointer argument was always `emu`'s PRNG seeding of
SCRATCH: a uniformly random word. **That is AGENTS.md finding #1 one level of
indirection out.** A command dispatcher reads its opcode out of a packet the
caller points at; a random opcode selects one arbitrary switch case; every
other case is unreachable by construction, at any number of fixtures. It is
the same defect the `orc` (callee-result) dimension was added to fix, on the
other input channel, and it explains the shape of the 20-symbol list exactly.

### 29.3.3 ★ AND A GLOBAL IS A STRUCT — the sweep addressed four bytes of it

Worked through on `confirm_message`: 229 instructions, **4 %** coverage, 322
candidate fixtures, of which the coverage-greedy selector kept **one**, because
all 322 produced the identical nine-instruction outcome. The nine instructions
are its gate:

```
00034528  ldr    r6, [pc, #0x274]     <- the literal the global sweep finds
0003452a  ldrb.w r3, [r6, #0x118]     <- the byte the branch actually reads
0003452e  cmp    r3, #0   /  beq  <exit>
00034534  ldr.w  r4, [r6, #0x110]  ;  cmp r4, r0  /  bne <exit>
0003453e  ldrb.w r3, [r6, #0x115]  ;  cmp r3, #4  /  bne <exit>
```

`GLOBAL_LADDER` wrote **four bytes at `[r6, #0]`** and nothing at +0x110,
+0x115 or +0x118. Every fixture took the same exit.

### 29.3.4 What landed, and what it moved

Three dimensions, in the same frozen burst:

1. **pointee ladder** — the first two words behind each of the first two
   pointer arguments, over `(0,1,2,3,4,5,0xff,0xffffffff)` plus the constants
   the shipped code actually compares against (`compare_immediates`, recovered
   over the CFG-reachable set so a literal pool is never decoded as a `cmp`);
2. **out-parameter ladder** — the same values as the content an oracled callee
   is modelled as writing (§29.2), which is what a `k_msgq_get(&msg)` loop's
   command selector reads;
3. **global SPAN, and global-equals-argument** — the ladder value written
   across `GLOBAL_SPAN = 0x400` from the literal (clamped so it can never spill
   into SCRATCH or the stack), plus a small dimension that fills a global with
   the fixture's OWN argument word, for the `if (ctx->current == conn)` shape.

Measured on the worked example, step by step, which is also the honest limit:

```
confirm_message   before                      cov 4 %   1 fixture kept
                  + pointee/out-param ladder  cov 4 %   1
                  + global SPAN               cov 4 %   1
                  + global-equals-argument    cov 5 %   2   <- clears gate 2
```

**Its third gate is not reachable by any ladder** and that is worth stating
plainly rather than burying: passing gate 2 requires `global+0x110 == r0`,
passing gate 3 requires `global+0x115 == 4`, and the two constraints are on the
same object at different offsets. A one-value-per-object sweep can satisfy
either but not both. The next mechanism is per-OFFSET assignment — the read
offsets are recoverable (`ldrb.w r3,[r6,#0x115]` names both the object and the
offset) and so are the immediates, so a fixture that sets each read offset to
each compared immediate is a static construction, not a solver. It is
specified here and NOT built.

## 29.6 ★ TWO OF THE NET PASS'S PATCHES ARE DECLINED — with the measurement

The brief said to read the net pass's four patches, judge them, and apply what
is sound. Two are applied (§29.2 out-parameter, §29.1 item 6 pointer mask).
Two are declined, and the reasons are measurements rather than preferences.

### 29.6.1 `for (;;) panic()` against a returning oracle (net §12.3) — DECLINED HERE

The class is real on net: 21 of its 86 failures use the idiom, a 36 % failure
rate against 5.9 % elsewhere. Exposure on the core this pass owns:

```
app sources containing `for (;;)`                          140
app sources containing `for (;;) <call>(...)`  -- the idiom   1
   recon/symbolized/app/try_enter_low_power_mode.c
```

**One symbol.** Against that, the sound implementation is not small and its
error direction is the dangerous one. It needs a `callee_noreturn` analysis
(conservative: a complete CFG walk with no reachable return, `None` on anything
unclassifiable, exactly like `callee_gpr_defs`), and it must terminate the
GOLDEN and the CANDIDATE at the same call — `emu` already has
`terminal_targets`, `terminal_ordinal` and `detect_repeated_terminal` for
precisely this, so the machinery exists and `modtest` simply does not use it.
A wrong "this callee never returns" TRUNCATES BOTH TRACES and hides everything
after the call, which is a false-PASS direction. Every other change in this
pass errs toward false failure.

Landing a semantic change of that shape for one app symbol, on a harness the
net core shares, while unable to regenerate or re-measure a single net vector
(concurrency rule), is not a trade this pass is willing to make silently. It
is recorded as specified-and-not-built, with the exact mechanism above.

### 29.6.2 Order-normalising the READ trace (net §12.4) — DECLINED, and the patch as written is UNSOUND

net §12.4 proposes applying `_sort_independent_write_runs`' canonicalisation to
runs of consecutive READS, on the argument that "reads have no side effects".
**In this harness a read event is only ever an MMIO read.** `emu._mr` appends
an `("R", …)` event if and only if `_is_nrf53_mmio(address, size)`; ordinary
RAM reads are not in the trace at all. So the proposed rule would order-
normalise exactly the accesses whose order is semantics — a read-to-clear
status register, a FIFO pop — and `emu`'s own comment states the criterion it
would break: *reordering a volatile MMIO access must fail parity*.

The three net examples are reads at `0x503DE43C` and neighbours. That is inside
the coarse `0x50000000-0x51000000` CPUAPP window but is not a peripheral: it is
a garbage pointer, seeded into a fixture, that happened to land in the window
and got classified as MMIO. **The defect is at the input end, not the
comparison end** — the same conclusion §28.4 reached for computed NaNs. A
sound fix narrows the MMIO windows to real peripheral extents, or drops a
fixture whose golden dereferences an unseeded pointer into an MMIO window; both
are fixture/model changes, neither is a trace-canonicalisation change.

Exposure on the app core: of the 43 surviving app FAILs triaged in §28.6, none
is labelled with an address-delta first divergence (the class is `esb`/net
shaped). Declining costs this core nothing measurable.

## 29.4 Per-fix evidence, before the corpus numbers

Each fix is checked on the symbol that motivated it, so a corpus-level move can
be attributed rather than inferred.

**`-fno-ipa-vrp` (§28.6.3).** The one BEHAVIOUR tree disagreement of the
593-symbol fan-out:

```
read_appearance   before   canonical=OK(41/41)  refactored=FAIL(0/41)
                  after    canonical=OK(41/41)  refactored=OK(41/41)   cov=100%
```

**`_expose_target` over a preprocessor directive (§28.6.2).** Run directly on
stage 09's merged text, counting what it de-staticises and what it leaves:

```
symbol                        de-staticised   static forms left   (§28.6.2 before)
get_demo_image_source               2                 0            1 / 1
refresh_box_field_timer             1                 0            (sibling failed)
is_box_field_timer_expired          2                 0            -- the sibling
set_misc_286c_value                 1                 0            0 / 1
uarte_nrfx_init                     1                 0            0 / 1
```

Both symptoms of §28.6.2 — "static declaration follows non-static" and "symbol
not found after link" — come from the same skipped declaration, and all five
are now clean.

**Read-only pointer inside a stack record (§28.6.1).** The precondition is that
`emu.ReadOnlyPointees`' deliberately narrow test actually resolves the golden's
words. Checked before relying on it, because if the address were a string
INTERIOR the test would return `None` and the fix would silently do nothing:

```
0x000f31a9  ('RO', b'Identity%s: %s')                           preceding byte 0x00
0x000f471e  ('RO', b'Invalid key')                              preceding byte 0x00
0x000f322e  ('RO', b'No ID address. App must call settings_load()')  0x00
0x000f6521  ('RO', b'Bus device is not ready')                  preceding byte 0x00
```

All four are proper string heads and all four are `printf`/log format strings,
which confirms §28.6.1's reading. (Its quoted decodes — `b'tead of expected
0x%04x'` and so on — were read at a shifted offset; the conclusion was right,
the bytes it printed were not. Corrected here.)

### 29.4.1 ★ `main` — the crash is gone, and the CAUSE is now visible

§28.8.4's per-symbol guard turned `main` from "the one symbol of 634 with no
result at all, which also silently killed 23 others in its batch" into an
ordinary CCFAIL. The `RuntimeError` it now raises carries the diagnosis:

```
linked object for main has no .text section
  (sections: .rodata, .siblings, .oracle_stubs, .comment, .ARM.attributes, ...)
```

`_compile_candidate`'s linker script is
`.text : { *(.text.main) *(.text.main.*) }` and everything else falls into
`.siblings`. **GCC does not emit `main` into `.text.main`** — a function it
considers startup-only goes into `.text.startup.main`, which the pattern does
not match, so `.text` is empty, the section is dropped, and the target is not
first. The fix is one line — add `*(.text.startup.%s)`, `*(.text.unlikely.%s)`
and `*(.text.hot.%s)` to the same output section — and it is **NOT applied
here**, because the harness is frozen for this pass's sweep and it would
invalidate every vector for the sake of one symbol. Specified, with the
evidence, for the next burst.

Worth checking then rather than assuming: any CCFAIL whose message is "no
`.text` section" is this same class, not a compile error in the tree.

### 29.4.2 The read-only-pointer class, measured on its four members

```
symbol                        §28.6 verdict     after the content marker
ccc_set_direct                FAIL(0/1)      -> OK(1/1)     cov 75 %
bt_id_addr_check_and_enable   FAIL(1/2)      -> OK(2/2)     cov 100 %
opt3001_chip_init             FAIL(14/15)    -> (see §29.5)
bt_dev_show_info              FAIL(0/41)     -> FAIL(0/41)  cov 100 %  -- but see below
```

`bt_dev_show_info` is the interesting one. Its divergence has **moved**: it was
`arg 2, offset 4` — the format-string pointer — on 41 of 41 fixtures; it is now

```
{"call_ordinal": 4, "arg": 2, "offset": 18, "expected": 1, "got": 42}
                                            "expected": 1, "got": 158}
                                            "expected": 1, "got": 130}
```

The golden writes the constant `1` at offset 18 of the record; the candidate's
byte there **varies with the fixture seed**, which is the signature of a slot
the candidate never wrote (rule 7 reads the candidate's window raw). A missing
store is exactly what this mechanism exists to catch, and it was hidden behind
the address comparison. It is carried into §29.5's list as a candidate defect,
not counted as a fix.

### 29.4.3 ★ NEGATIVE CONTROLS — the two "make failures disappear" changes are shown not to have bought blindness

Both the read-only content marker and the out-parameter fill turn FAILs into
OKs, so both have to be shown still to kill.

**The read-only marker compares WHICH string.** `ccc_set_direct`'s baseline is
now OK; swapping the first character of the first string literal in its member
body (through `mutate.member_span`, never a whole-file regex):

```
ccc_set_direct   baseline=OK   mutant(string swapped)=FAIL   killed
```

That is the property that distinguishes this fix from blanking the word: a
candidate that stores a *different* string still fails.

**Graded, on the symbols the two fixes moved:**

```
symbol                        tree        baseline  mutants  killed  survived  rate
battery_soc_from_curve        canonical   OK        10        9       1        90%
   (out-parameter EXPOSED and passing -- the fill's blindness test)
ccc_set_direct                canonical   OK        10        7       3        70%
bt_id_addr_check_and_enable   canonical   OK         8        7       1        88%
```

**One of my own controls was broken first, and it is the THIRD time this
document records that mistake.** A hand-written "bump the first integer"
mutation reported `battery_soc_from_curve` as SURVIVED. The regex matched a
number inside the member's own `/*=0xADDR*/` provenance comment, so the mutant
was inert. `mutate.generate` has `_inert_mask` for exactly this and reports
9 of 10 killed on the same symbol. The lesson §21.1 and §28.3.1 already
recorded, once more: **do not hand-roll a mutation when the mutation engine is
right there.**

### 29.4.4 ★ BOTH battery symbols are now attributed to ONE named limitation — the FRAME-RELATIVE OFFSET

§28.5 could not separate two limitations on `battery_soc_curve_model_init`
(unmodelled out-parameter AND frame-relative layout) and §28.5.1 recorded
`battery_model_state_update` as "not root-caused". With the out-parameter
confound removed, both resolve to the same single cause, and the coverage they
are decided at is no longer trivial:

```
battery_soc_curve_model_init   FAIL(0/49)  cov 93 % -> 95 %
   the ONE primary divergence, every fixture, at call ordinal 6:
     G ('C', 6, ('SP', 0), ('SP', 24), ('SP', 4), ...)
     C ('C', 6, ('SP', 0), ('SP', 12), ('SP', 4), ...)
   events 76..86 are all downstream of it (a value computed from the object)

battery_model_state_update     FAIL(0/46)  cov 62 % -> 89 %  (see §29.2.2)
   first divergence, every fixture, at call ordinal 4:
     G ('C', 4, ('SP', 0), ('SP', 76), ('SP', 20), ...)
     C ('C', 4, ('SP', 0), ('SP', 24), ('SP', 16), ...)
```

Same shape: the first stack argument agrees, the others sit at different
distances from it. `normalise_events` normalises every stack address to its
delta from the FIRST stack address in the trace, and its own docstring names
this as a false-failure mode. **The oldest open item in AGENTS.md is a frame
layout difference, not a behaviour difference** — as far as this harness can
show, and it is now showing it at 89 % coverage rather than the 62 % committed
at `HEAD`. (⚠ an earlier draft of this paragraph said "instead of 0 %", which
was the rejected DROP variant, not the baseline — §29.2.2.)

> **SPECIFIED, NOT BUILT — object identity instead of frame delta.** Normalise a
> stack address to `(object ordinal by first appearance, offset within that
> object)` rather than to a signed delta from an arbitrary anchor. That compares
> WHICH local was passed and WHERE INSIDE it, and stops comparing how far the
> compiler put two unrelated locals apart. The weakening is real and must be
> measured before adopting: two distinct objects the golden passes 4 bytes apart
> would no longer be distinguishable from two objects 40 bytes apart. `emu`
> already has `_stack_object_pointer` for reviewed cases, which is where the
> object boundaries would come from.

## 29.5 ★ THE 20 "NO KNOWN LIMITATION" FAILURES — worked, and a NEW limitation found in them

§28.6's list of 20 `value`-only failures was the first list this project had of
failures consistent with no known harness limitation. Twelve of them had a
regenerated vector at the time of writing; the remaining eight are in §29.8.

```
symbol                                §28.6       this pass
load_sys_setting                      FAIL(41/43) -> OK(43/43)   cov 91 %
gui_bmp_bitmap_draw_ex                FAIL(41/44) -> OK(43/43)   cov 85 %
fuel_gauge_update                     FAIL(42/43) -> OK(44/44)   cov 48 %
gui_draw_timer_hms                    FAIL(1/8)   -> FAIL(1/9)
discovery_completed_cb_ancs           FAIL(41/43) -> FAIL(41/43)
get_notification_counts_cmd_process   FAIL(20/41) -> FAIL(20/41)
build_status_notify_packet            FAIL(9/12)  -> FAIL(9/12)
button_init                           FAIL(0/43)  -> FAIL(0/43)
click_event_dispatch_loop             FAIL(43/46) -> FAIL(43/46)
bt_dev_settings_commit                FAIL(42/44) -> FAIL(41/44)
ext_flash_api_init                    FAIL(22/43) -> FAIL(22/43)
key_event_thread                      FAIL(6/22)  -> FAIL(6/22)
```

**Three of twelve were the harness after all.** Every one of the nine survivors
has its first divergence in a CALL ARGUMENT REGISTER.

### 29.5.1 `button_init` is a DECLARED BUILD DEVIATION, not a defect

```
ev15  G ('C', 15, 559568, 65536, ...)      559568 = 0x88A50, shipped .rodata
      C ('C', 15,  98265, 65536, ...)       98265 = 0x17FD9, the candidate's own
```

`button_init.c` carries a banner: *"BRING-UP WIRING FIX (P4 iteration 5) — the
three `struct gpio_dt_spec` tables this function used to read from the
unrelocated absolute pins rodata_88340 / rodata_889d0 / rodata_889e0 are now
emitted by the build in recon/application/app/src/g1_gpio_dt_specs.c"*. The
deviation is deliberate, documented, and present in the tested tree
(`stage_00_snapshot/tree/.../button_init.c`). The harness is reporting it
correctly; it is not a reconstruction defect.

Swept over the other 19: **`button_init` is the only one** of the 20 whose
source carries a bring-up/wiring/deviation banner.

### 29.5.2 ★ NEW NAMED CLASS — `live_in_arity` IS OVER-WIDE AT A `bl`, and dead registers are compared

`gui_draw_timer_hms` fails 8 of 9 fixtures, always at call ordinal 1, always
like this:

```
G ('C', 1, 4, 288, 3600, 0, ...)
C ('C', 1, 4, 288,    0, 60, ...)
```

Arguments r0 and r1 agree (`4`, `0x120`); r2 and r3 differ. The callee is
`0x47a4c`, whose whole body is 44 bytes:

```
00047a4c cmp r0,#4 / push {r3,lr} / bne 0x47a62
00047a52 mov.w r2,#0x120 / ldr r1,[pc] / ldr r0,[pc] / bl 0x86c04 / ldr r0,[pc] / pop
00047a62 cmp r1,#0 / ldr r3,[pc] / it lt / addlt r1,#3 / asrs r1,r1,#2
         mla r0,r1,r0,r3 / ldr r2,[pc] / bl 0x4790c / b
```

**r2 and r3 are written before any read on every path**; the only inputs are r0
and r1. Its true arity is 2. `core.live_in_arity` returns **4**, so the harness
compares two registers holding whatever the caller left there — `0xe10` and `0`
in the shipped frame, `0` and `0x3c` in the candidate's, both leftovers of a
different register allocation.

The cause is the `bl` rule: the walk stops at the FIRST `bl` in address order
and declares every argument register not yet written to be forwarded. On the
first path r3 is unwritten at `bl 0x86c04`, so r3 becomes live-in and the arity
widens to 4. `live_in_arity` exists to NARROW Ghidra's over-wide arities
(§22.7) and here it produces one of its own.

**The fix is not one line and is not applied.** A refinement that resolves the
forwarded set through the callee (implemented offline to test the idea) reports
`0x47a4c` as arity **1**, which is too NARROW — it inherits the same
address-order `break` and never reaches the `cmp r1,#0` on the second path. The
sound version is a proper backward liveness pass over the CFG with
interprocedural forwarding at calls (bounded depth, cycle guard, `None` on
anything unclassifiable, exactly like `callee_gpr_defs`). Specified, measured
on one worked example, **NOT built** — the brief's rule is one harness burst per
pass and this pass's burst is closed.

> **CAUTION, stated because the evidence does not reach further.** Eight other
> surviving failures also diverge in a call-argument slot, and it is *plausible*
> that several are this class. That is not established: proving it per symbol
> needs the sound analysis above. They are listed as OPEN, not as harness.

## 29.7 A self-test file, and it is SHOWN to fail without the guards

`recon/tests/test_modtest_guards.py` (new) asserts the pure-Python halves of
this burst — the properties a future edit could silently undo without any
vector noticing. 30 checks, all passing at `harness_rev=956e29213dbbde89`:
staleness fails closed on an unstamped vector and on a MISSING or changed value
of every one of the six `harness_env()` switches; `_expose_target`
de-staticises after `#include`, after `#define`, after a backslash-continued
`#define`, after a comment and after `}`, and still refuses when real code
precedes the `static`; `outparam_bytes` is deterministic and distinct per
(ordinal, index); `-fno-ipa-vrp` is in `UNIT_BOUNDARY_CFLAGS`.

**Asserting is not testing, so both load-bearing guards were re-broken and the
tests were watched to fail:**

```
with the OLD fail-OPEN staleness   unstamped refused? False   (test FAILS, as it must)
with the OLD walk-back predicate   de-staticised after #include: 0   (test FAILS)
with the new predicate                                          1
```

### 29.2.2 ⚠ A NUMBER I GOT WRONG IN §29.2, CORRECTED FROM `git HEAD`

§29.2's table compares the DROP variant against the FILL variant, both measured
during the burst. Read carelessly — and I wrote the AGENTS.md note carelessly —
it suggests the DROP column is the pre-pass baseline. **It is not.** The
pre-pass baseline is the corpus committed at `HEAD`, and it is much higher than
either intermediate:

```
symbol                         HEAD (before)   DROP variant   FINAL (this pass)
md5_process_block               99 % 41 cases    0 %  1 case    99 % 41 cases
battery_model_state_update      62 % 46 cases    0 %  1 case    89 % 46 cases
battery_soc_curve_model_init    93 % 49 cases   17 %  3 cases   95 % 49 cases
```

So the honest statements are: **the fill does not raise `md5_process_block`'s
coverage at all — it changes what the comparison MEANS** (§29.2.1), and
`battery_model_state_update` moves 62 % → 89 %, not 0 % → 89 %. The DROP
column is what the net pass's "safe patch" would have cost, which is why it was
rejected; it is not a before-number. AGENTS.md is corrected in place.

## 29.8 ★ COVERAGE — the A/B against `git HEAD`, RE-DERIVED

⚠ **RE-DERIVED, not re-quoted, after §29.2.2.** An earlier version of this
section was computed over 680 regenerated symbols and reported
`52.6 % -> 53.6 %`. The numbers below are the same script over **890**
symbols. **The two differ because the SUBSET differs, not because the baseline
was wrong** — and that distinction is the whole point of re-deriving, because
this project has already lost a structural recommendation to two numbers
compared at different granularities.

**Provenance of the BEFORE column, stated because §29.2.2 was a baseline
error.** It is not a remembered module average and it is not any intermediate
variant built during the burst. It is read per symbol out of git:

```
scratchpad/cov_ab.py:13   old = json.loads(subprocess.run(["git","show","HEAD:"+f], ...))
$ git rev-parse --short HEAD                 13ec6e3d
$ git status --porcelain recon/tests/vectors/app | wc -l      891
```

Every one of the 924 app vectors is committed at `13ec6e3d`, so for each symbol
the comparison is that symbol's own pre-pass vector against its own new one.
The §29.2.2 error was in PROSE about three symbols, and it never entered this
computation. Nothing in the table below moves as a result of that correction;
what moved is the sample size.

```
module          n |   wt-BEFORE   wt-AFTER | mean-BEFORE  mean-AFTER
analytics      14 |     64.5%       64.5%  |    78.2%       78.2%
audio         127 |     57.2%       59.1%  |    84.2%       85.3%
ble            95 |     48.2%       48.9%  |    83.0%       82.8%
common          3 |    100.0%      100.0%  |   100.0%      100.0%
core          133 |     61.2%       60.6%  |    82.9%       82.7%
display        78 |     56.9%       57.6%  |    82.0%       82.2%
esb            24 |     46.2%       45.8%  |    73.4%       75.7%
gui            36 |     57.9%       57.1%  |    66.1%       64.9%
ipc            46 |     77.5%       76.3%  |    91.0%       90.4%
lib            14 |     97.2%       97.2%  |    97.9%       97.9%
notify         53 |     60.3%       58.7%  |    83.1%       82.2%
sensors        84 |     57.9%       63.8%  |    86.4%       86.7%
storage        35 |     64.1%       63.5%  |    84.4%       84.4%
ui             16 |     10.1%        9.5%  |    77.0%       77.6%
unsorted      132 |     69.9%       70.9%  |    89.0%       89.8%
TOTAL         890 |     54.1%       54.9%  |    83.9%       84.1%
```

**+0.8 points of instruction-weighted coverage, +0.2 of the per-symbol mean.**
That is the honest headline and it is far short of what §28.10 item 4 asked
for. Six modules went DOWN. The three new dimensions are sound and they work
where the channel they open is the one that was blocked —

```
battery_model_state_update  sensors  1365 insns   62% -> 89%
display_reflash             display   105 insns   58% -> 90%
qspi_nor_write              audio     129 insns   30% -> 67%
opt_list_encode             audio      40 insns   65% -> 100%
mpu_region_index_lookup     unsorted   22 insns   27% -> 100%
```

— and they do nothing at all for a function gated by a correlated multi-field
guard (§29.3.4), which is what the twenty biggest instruction-holders are.
**No module passes the §8.2 70 % coverage bar except `ipc`, `lib` and
`unsorted`, exactly as before this pass.**

### 29.8.1 ⚠ THE PASS-THROUGH POINTER PATCH COSTS COVERAGE — measured, and it is MINE

net §12.2's patch is applied (§29.1 item 6) and it is much more aggressive on
this core than its own measurement suggested. Comparing the derived mask
against the HEAD corpus:

```
symbols compared (first 250)                            250
  mask unchanged                                         95
  mask WIDER                                            155   (62 %)
    of which the mask was previously EMPTY              103
```

Every one of the biggest coverage losses in the corpus is this:

```
symbol                            mask  HEAD -> NOW        coverage
dev_write_config_word              [0] -> [0,1,2,3]        91 % -> 19 %
ancs_connected                     [0] -> [0,1,2,3]        69 % -> 37 %
rate_limited_elapsed_seconds_tick  [0] -> [0,1,3]          92 % -> 42 %
ccc_find_cfg                       [0] -> [0,1,2]          93 % -> 57 %
```

The mechanism is obvious once seen: an `int` parameter that the function merely
FORWARDS to a callee is now marked a pointer, `make_args` gives it a SCRATCH
ADDRESS instead of a small integer, and every predicate on it goes the same way
— the exact defect `pointer_arg_mask`'s own docstring says a fixed prefix count
causes, reintroduced from the other side.

**Attributed, so the decision is not a guess:**

```
                              n     weighted BEFORE -> AFTER   net instructions
symbols whose mask CHANGED   430        49.0%  ->  49.8%            +300
symbols whose mask unchanged 306        69.7%  ->  71.0%            +114
```

The group the patch touches still improves overall, because the new fixture
dimensions gain more than the mask loses *within that group*. **So it stays,
and the refinement is specified rather than the patch reverted:** at a `bl`,
mark argument *i* a pointer only if the CALLEE dereferences the argument
position it lands in — i.e. `pointer_arg_mask` applied to the callee,
recursively, bounded depth, cycle guard, and "mark it" on anything
unclassifiable. That is the same shape as `callee_gpr_defs` and it is the
difference between "this value is passed on" and "this value is a pointer".

## 29.11 WHAT THIS PASS DID NOT DO, AND WHY

Enumerated, not implied.

**Harness fixes specified with evidence and deliberately NOT built** (the
brief's rule is one edit burst per pass, at the start; this pass's burst closed
before the sweep and was not reopened):

1. **Sound interprocedural live-in arity** (§29.5.2). `live_in_arity` stops at
   the first `bl` in ADDRESS order and forwards every unwritten argument
   register, so `0x47a4c` — whose r2/r3 are written before any read on every
   path — derives arity 4 and the harness compares two dead registers. A
   refinement that resolves the forwarded set through the callee was written
   offline and is too NARROW (it reports arity 1 for the same callee), because
   it inherits the same address-order break. The sound version is a backward
   liveness pass with interprocedural forwarding.
2. **Recursive pointer-mask at a `bl`** (§29.8.1) — the refinement of the
   patch this pass landed, which currently over-marks 62 % of symbols.
3. **`*(.text.startup.%s)` in the link script** (§29.4.1) — one line, would give
   `main` a result for the first time.
4. **Object identity instead of frame delta in `normalise_events`** (§29.4.4) —
   the single remaining cause of both battery symbols' failures. It is a
   WEAKENING and must be measured before adoption.
5. **Per-offset global/pointee assignment** (§29.3.4) — the mechanism that
   would crack a correlated multi-field guard like `confirm_message`'s. The
   read offsets and the compared immediates are both statically recoverable, so
   it is a construction, not a solver.

**Net patches declined, with measurements**: `for(;;) panic()` (§29.6.1, one
app source uses the idiom, and a wrong "noreturn" truncates both traces, which
is a false-PASS direction) and read-trace order normalisation (§29.6.2, `R`
events are MMIO-only in this harness and reordering them is the one thing
`emu` says must fail parity).

**Not attempted at all**:

* the net core — vectors, sources and `net_test_coverage.md` are the other
  agent's under the concurrency rule, and nothing under `recon/net/**`,
  `recon/symbolized/net/**`, `recon/tests/vectors/net/**` or `recon/refactor/**`
  was read for writing or changed. `.modtest_pin/` was not touched;
* `cfg_verify` was not run and is not cited anywhere in §29, per the standing
  rule;
* no reconstruction defect was REPAIRED. This pass produced a shorter, better
  attributed list of candidates (§29.5, §29.9) and repaired none of them: every
  repair touches a canonical address-keyed tree and needs its own proof, and
  the pass's budget went to the harness and the regeneration;
* nothing was committed to git.

**A hole this pass did NOT close, and it is the same shape as the one it did.**
`select`'s `budget` and `max_insns` are CLI arguments, not `harness_env()`
entries, so two vectors generated with different budgets are indistinguishable
at the same fingerprint — exactly the defect §28.1.1 found for `DERIVED_ARITY`.
This pass changed the default budget from 400 to 600, which makes the hole
live. It belongs in `harness_env()`.

### 29.8.2 ★ THE PASS-THROUGH POINTER PATCH — DECIDED, and the decision is KEEP-WITH-A-CAVEAT

A known-harmful patch may not be left unresolved, so it is decided here on
three measurements rather than on the coverage number alone.

**(a) Did it do the job it was applied for?** Its purpose is to stop the GOLDEN
faulting on a pointer parameter that `make_args` seeded with a random integer —
a frozen expectation recording a fault the hardware never takes. Counted over
every regenerated vector, splitting by whether the mask actually changed:

```
                  n     golden-FAULT fixtures BEFORE -> AFTER        instructions
mask CHANGED    512   3979/16074 (24.8%) -> 3965/16295 (24.3%)          +283
mask unchanged  379    899/8408  (10.7%) ->  944/8580  (11.0%)          +210
```

**Fourteen fixtures.** On the app core the patch removes 14 false golden faults
out of 16,074 — half a percentage point — while widening the mask on 512 of
891 symbols. Its own justification is very nearly absent here. (On net it was
measured as 47 of 370 vectors missing a pointer parameter and 21 of 86
failures; this core is simply not the one it was diagnosed on.)

**(b) What does it cost?** The largest per-symbol coverage losses in the entire
corpus are all this patch (§29.8.1). The `+283` above is NOT the patch's
credit — three other fixture dimensions landed in the same burst, and the
mask-changed group is where they also apply.

**(c) The verdict, and why it is not "revert".**

* It cannot cause a FALSE PASS. It changes fixture INPUTS only, identically on
  both sides; a candidate that behaves differently on the new inputs still
  fails. Its entire cost is coverage and its entire benefit is removing false
  failures. That asymmetry is what makes keeping it safe and reverting it
  merely better.
* Reverting is a `tools/modtest/` edit. `harness_rev()` hashes whole files, so
  it would invalidate all 924 vectors this pass has just regenerated and
  restart a multi-hour sweep — for a patch whose measured harm is bounded and
  whose measured benefit is small but real. The brief's rule is one burst per
  pass, and the net agent is blocked until this harness settles.
* **It is kept, and the refinement is specified as the FIRST item of the next
  burst** (§29.11 item 2): at a `bl`, mark argument *i* a pointer only if the
  CALLEE dereferences the position it lands in. That is the version that keeps
  the benefit (a wrapper's pointers are still found) and drops the cost (a
  forwarded `int` is no longer called a pointer).

**Anyone re-measuring after that refinement should expect the mask-changed
group to shrink from 512 symbols to something much smaller, and
`dev_write_config_word` to return to 91 %.** If it does not, the refinement is
wrong and this decision should be revisited.
