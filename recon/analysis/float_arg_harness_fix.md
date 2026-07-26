# Float-argument blind spot in the parity harness — diagnosis, fix, corpus re-sweep

*Session of 2026-07-26. Scope: `tools/parity/emu.py`, `tools/cfg_verify.py`, and a
re-verification of every float-relevant function in both cores. Nothing is committed.*

---

## 1. What the blind spot actually was

Iteration 37 (`recon/emulator/reports/our_boot_bringup.md` §37.13) recorded that
`imu_mahony_ahrs_update` (`FUN_00026624` @ `0x26624`) shipped for weeks with **five
`VNMLS.F32` instructions reconstructed as `VMLS.F32`** — `Sd = -Sd + Sn*Sm` versus
`Sd = Sd - Sn*Sm` — and that `cfg_verify.py app FUN_00026624` returned `PASS cases=2`
on the broken body as well as the corrected one. That measurement is **reproduced here**
(broken body restored from `f334bd84^` into a scratch copy; the committed source was not
touched):

```
FIXED  : PASS cases=2 checked=2 mismatches=None      <- pre-fix harness
BROKEN : PASS cases=2 checked=2 mismatches=None      <- pre-fix harness
```

§37.13 attributed this to `emu.make_args` seeding only integer registers while a hard-float
function's arguments arrive in `s0..s6`. **That attribution is wrong, and it matters**, because
fixing the stated cause would not have fixed anything:

* `Runner.run` has seeded `s0..s15` from a PRNG since commit `5c489985`; the VFP bank was
  never undriven.
* `FUN_00026624` even had hand-written `REVIEWED_FP_CASES` entries driving `s0..s6` with
  realistic gyro/accelerometer/`dt` values.

The real causes are three, and all three are the same *shape* as CRITICAL FINDING #1 —
an input dimension the harness never varied:

1. **Float inputs were driven only by hand-written per-function cases.** There was no
   signature- or instruction-derived float coverage at all. `REVIEWED_FP_CASES` held 10
   app entries; **52 of the 61 app functions that take hard-float arguments had none**, so
   their float inputs were nothing but random words.
2. **Uniform random 32-bit words are almost never ordinary floats.** A random word has a
   uniformly random 8-bit exponent, so it is a ~1e±30 magnitude with overwhelming
   probability. The values firmware actually branches on — exactly `0.0`, `±1.0`, `±0.5`,
   sensor magnitudes — have probability ~0, exactly as uniform integers never land in a
   small switch range. Measured on a minimal body (`vcmp.f32 s0,#0` + `ite eq` versus a
   constant): **40/40 trials passed a knowingly wrong candidate** under the old seeding.
3. **A degenerate reviewed fixture.** `FUN_00026624`'s two reviewed cases pinned the
   quaternion state to the identity `q = (1,0,0,0)` and one case zeroed the accelerometer
   vector. With `q1 = q2 = q3 = 0` the intermediate terms `a` and `b` are identically zero
   and `c` only flips sign, so the five sign errors **cancel algebraically against the
   swapped `ey`/`ez` naming in the broken body**: the two implementations are bit-identical
   for *every* float argument on that state. No amount of argument variation could have
   separated them; the state fixture itself had to vary.

A fourth issue was found while fixing the above, and it is a build-contract error rather
than a coverage gap — see §3.

---

## 2. The harness fix

### 2.1 `tools/parity/emu.py`

* **`FLOAT_POOL` / `DOUBLE_POOL` / `FLOAT_BOUNDARY`** — production-plausible IEEE-754
  values: exact `0.0`, `-0.0`, `±1.0`, `±0.5`, `±2.0`, `0.25`; sensor magnitudes
  (`0.1`, `0.01`, `0.05`, `0.6`, `0.8`, `0.7071…`, `9.80665`); geometric constants
  (`π`, `π/2`, `180`, `360`, deg↔rad factors); display ranges (`100`, `255`, `1024`);
  finite magnitude extremes (`1e±6`, `1e±20`, `FLT_MIN`, `FLT_MAX`) and the smallest
  denormal. The six boundary values are over-sampled ×3 for the same reason `make_args`
  over-samples small integers.
* **`_vfp_seed_words(seed)`** replaces the uniform fill. Register *pairs* are seeded as a
  unit so `d0..d7` receive plausible binary64 values: ~25% of pairs get a pooled double,
  ~55% two pooled floats, and **~20% keep the historical uniform random words**, so the
  change is strictly additional coverage.
* **`_float_scratch_bytes(seed, size)` + `Runner.run(..., float_scratch=…)` +
  `compare(..., float_scratch_trials=…)`** — float arguments also arrive through
  *pointers* (quaternion state, filter coefficients, sample buffers), and uniform pointee
  bytes have the identical blind spot. Selected trials seed the argument-pointer region
  (`SCRATCH`, 32 KiB) with a keystream of plausible finite floats, 25% of slots left
  arbitrary. Applied before every observation hook and identically to original and
  candidate, exactly like the existing argument fixtures.

### 2.2 `tools/cfg_verify.py`

* **`float_argument_registers(rawread, va, size)`** derives the incoming AAPCS-VFP
  argument slots **from the shipped instructions**, not from a Ghidra signature: an
  `s0..s15` register read before it is written is an incoming float argument
  (`s16..s31` are callee-saved and are never argument slots). Over-reporting is harmless
  (both machines receive the identical value); under-reporting would leave a real argument
  undriven.
* **`build_float_cases(regs, doubles, …)`** enumerates one `fp_arg_overrides` dict per
  profile — `zero`, `negative-zero`, `unit`, `negative-unit`, `half`, `sensor`,
  `sensor-negated`, `unit-quaternion`, `tilted-quaternion`, `alternating-zero`, `tiny`,
  `large`, `integral`, three double-pair profiles — **plus a per-argument
  `zero-arg-sN` probe**. The probes are the float analogue of `cmp arg,#k` coverage: a
  guard like `if (ax != 0 || ay != 0 || az != 0)` selects a whole arm on *one* argument
  being exactly zero, which no all-equal profile and no random word reaches.
* **`verify()` appends the generated cases in two variants:**
  * **A — fixture-preserving:** reuses the reviewed integer/absolute/oracle state of the
    case it was cloned from and varies only the floats;
  * **B — `relaxed:` (only when reviewed absolute fixtures exist):** additionally drops
    the reviewed *absolute memory* fixture while keeping reviewed oracle results and
    argument registers, so a fixture that pins a float state object to a degenerate value
    can no longer hide a defect. This is the variant that catches `FUN_00026624`.
  Both variants run with the float pointee profile. Per-trial reviewed lists
  (`pointer_read_transitions`, `absolute_read_transitions`, primask/xpsr/exclusive-monitor
  cases, argument-relative pointee setup) are cycled so appended trials stay
  production-shaped.
* **`FLOAT_COVERAGE_EXEMPT`** — deliberately empty; it exists so a future opt-out is an
  explicit reviewable decision rather than a silent gap.
* **Float results already compare bit-exactly** and still do: `ret_kind` `f32`/`f64`
  compares `s0`/`s0:s1`, the ordered write trace compares every float store at full width,
  and float call arguments are recorded per callee float arity. **No epsilon was
  introduced anywhere.**

### 2.3 Why this cannot produce false FAILs

* Every added input is **setup applied identically to original and candidate** before any
  observation hook. A divergence therefore always means the two bodies genuinely differ on
  an input they were both given.
* A function that legitimately ignores its float arguments still passes — asserted in the
  `emu.py` self-tests for all four return kinds (`i32`/`f32`/`f64`/`void`) using two
  different encodings of "return 5".
* Non-float functions are untouched, and this is not a judgement call: generic float
  coverage is gated on `float_argument_registers` returning a non-empty set, the float
  pointee profile is applied only to those appended trials, and a function whose body
  contains **no VFP instruction at all** cannot be influenced by VFP register contents.
  Sampled confirmation: 12 randomly chosen non-VFP app functions all PASS unchanged.
* **Infinity and NaN are deliberately NOT in the generated cases or the seeding pools.**
  This is a *measured* decision, not an oversight. Algebraically identical float code does
  not preserve NaN sign/payload (`-a + b*c` via `VNMLS` versus `b*c - a` flips the sign
  bit of a propagated NaN; `inf - inf` yields the positive default NaN instead), while the
  harness compares float memory writes and float call arguments bit-exactly. Seeding them
  made the **corrected** `FUN_00026624` mismatch in nothing but the sign bit of a NaN. The
  same reasoning forced two further constraints: pointee floats are capped at `|x| ≤ 1e6`,
  and arbitrary pointee words have their exponent clamped to `2^-23 … 2^8` — a raw random
  word is a ~1e34 float three times in ten, and squaring it overflows to infinity, which
  re-creates the NaN one step later. The ~20% of register pairs that keep uniform random
  words still deliver infinities and NaNs at exactly their historical rate, so nothing that
  used to be exercised has been lost, and deliberate NaN/infinity classification coverage
  remains in the hand-reviewed `REVIEWED_FP_CASES` where libm needs it.
  An **advisory** pass is available via `CFG_VERIFY_FLOAT_EXTREMES=1` (§5).

---

## 3. A build-contract error found on the way: `-ffp-contract`

`VMLA/VMLS/VNMLA/VNMLS` multiply-accumulate with an **intermediate rounding** (two
roundings — exactly C's `a + b*c`). `VFMA/VFMS/VFNMA/VFNMS` are **fused** (one rounding).
They differ by up to 1 ULP.

The parity harness compiled every candidate with GCC's default `-ffp-contract=fast`, so
`FUN_00026624`'s candidate contained **22 `VFMA` + 4 `VFMS`** where the shipped body has
**26 unfused** MAC instructions. Comparing under the wrong contract both manufactures
spurious last-bit mismatches and hides real ones.

Census over all 2 417 catalogued app functions — 24 use MAC instructions and **not one
mixes the two forms**:

| form | count | functions |
|---|---|---|
| unfused (`vmla`/`vmls`/`vnmla`/`vnmls`) | 5 | `FUN_00026624`, `FUN_000265e8`, `FUN_00026828`, `FUN_0007cab4`, `fuel_gauge_update` |
| fused (`vfma`/`vfms`/`vfnma`/`vfnms`) | 19 | every liblc3 / libm / battery-model body |

So the G1 application translation units were built with contraction **off** and the
library modules with it **on**. `verify()` now derives the flag from the shipped bytes
(`-ffp-contract=off` when unfused MACs are present and fused ones are not) instead of
assuming one profile. **This has a consequence for the end-goal byte-match build**: those
five application bodies will not reproduce the shipped codegen unless their translation
unit is compiled `-ffp-contract=off`. `recon/application/build_cohesive.sh` does not
currently set it.

---

## 4. Discrimination proof

### 4.1 At the harness level (independent of any one function)

New self-tests in `tools/parity/emu.py`, each measured **both ways**:

| probe | old seeding | new seeding |
|---|---|---|
| `x == 0.0f` selects a different result; candidate always answers the other | **PASS (false proof)** | **FAIL**, 11/40 trials |
| `x == 1.0f`, same shape | **PASS (false proof)** | **FAIL**, 3/40 trials |
| `VMLS.F32` vs `VNMLS.F32`, `ret_kind=f32` | FAIL | FAIL |
| `*p == 0.0f` through a pointer argument | **PASS (false proof)** | **FAIL** with the float pointee profile |
| negative control: two encodings of "ignore floats, return 5", `i32`/`f32`/`f64`/`void` | PASS | **PASS** |
| negative control: identical bodies under the float pointee profile | — | **PASS** |

### 4.2 On the real defect

`FUN_00026624`, corrected body versus the `f334bd84^` broken body (scratch copy; the
committed source was never modified):

| harness | corrected body | broken body |
|---|---|---|
| pre-fix (`HEAD`) | PASS, 2 cases | **PASS, 2 cases** ← the false proof |
| fixed | **PASS, 48 cases, 48 checked** | **FAIL, 17/48 mismatches** |

The broken body now fails on `relaxed:unit`, `relaxed:negative-unit`, `relaxed:half`,
`relaxed:sensor` and `relaxed:sensor-negated` — i.e. on ordinary finite quaternion states,
with the divergence visible as different stored `q0..q3` words and a different argument to
the reciprocal-square-root helper.

Two further known-good/known-bad pairs came out of this session's own defect fixes (§6),
each measured under **both** harnesses:

| body | harness | `FUN_000869f2` (`finitef`) | `FUN_0000e340` (`battery_soc_from_curve`) |
|---|---|---|---|
| pre-fix (as committed before this work) | pre-fix (`HEAD`) | PASS, 3 cases | PASS, 2 cases |
| pre-fix | fixed | **FAIL**, 1/17 | **FAIL**, 4/16 |
| corrected | fixed | **PASS**, 17 cases, 57 checked | **PASS**, 16 cases, 56 checked |

The pre-fix row is exactly how both survived carrying the banner
`parity: 300/300 trials, PROVEN`.

---

## 5. Corpus re-sweep

**How many float functions exist.** Derived from the shipped bytes of every catalogued
function in both cores:

| core | catalogued | contain any VFP instruction | read incoming `s0..s15` |
|---|---|---|---|
| app | 2 417 | **95** | **61** |
| net | 1 252 | **0** | **0** |

The net core contains **no floating-point instructions at all** — consistent with the
nRF5340 CPUNET having no FPU. The float sweep is therefore an app-core matter entirely;
there is nothing to re-verify on net.

All **95** app functions were re-verified with the fixed harness and, separately, with a
`HEAD` copy of the harness for a baseline. The whole sweep costs ~6 CPU-minutes (351 s of
per-function verification), so it is cheap to repeat.

| | baseline (`HEAD` harness) | fixed harness |
|---|---|---|
| PASS | 87 | **92** |
| FAIL | 1 | **3** |
| compile-fail | 7 *(artifact — see note)* | 0 |
| total cover cases | 284 | **1 661** |

*Note: the 7 baseline `compile-fail` results are an artifact of running the baseline
harness copy from a scratch directory, where its relative lookup of
`recon/catalogs/function_names_app.json` fails and the readable compile symbol cannot be
resolved. They are not a real baseline difference and no improvement is claimed for them;
all 7 PASS under the current harness.*

Coverage grew from 284 to 1 661 cases (1 246 of them generated float cases), with 61
functions receiving generated float cases
(largest growth: `FUN_00021460` +98, `FUN_00016eb8` +48, `FUN_00026624` +46,
`FUN_0006ffd8` +43, `FUN_0000e53c` +42).

Split by whether the function actually takes float arguments:

| group | count | PASS | FAIL |
|---|---|---|---|
| reads incoming `s0..s15` (true hard-float ABI) | 61 | 59 | 2 — `FUN_0000c358`, `FUN_0000e53c` |
| uses VFP but takes no float argument | 34 | 33 | 1 — `FUN_0006b3c8` (pre-existing) |

### 5.1 Every NEW FAIL

Five functions that PASSed under the old harness FAIL under the fixed one.

| function | readable name | verdict | disposition |
|---|---|---|---|
| `FUN_000869f2` @ `0x869f2` | `finitef` | real defect | **FIXED + re-proven** (§6.1) |
| `FUN_0000e340` @ `0xe340` | `battery_soc_from_curve` | real defect | **FIXED + re-proven** (§6.2) |
| `FUN_00078ce0` @ `0x78ce0` | newlib `__d2b` | harness gap, not a defect | **resolved** (§6.3) |
| `FUN_0000e53c` @ `0xe53c` | `batt_soc_curve_estimate` | **real defect, OPEN** | §7.1 |
| `FUN_0000c358` @ `0xc358` | `battery_model_state_update` | **real defect, OPEN** | §7.2 |

The third pre-existing FAIL, `FUN_0006b3c8` (liblc3 `mdct.c fft`), **also fails at
baseline** — a one-sided `Invalid memory read` on a non-float trial. It is not a float
finding and is unchanged by this work.

Path relevance: three of the five sit on the **battery / fuel-gauge** path
(`battery_soc_from_curve` → `battery_model_state_update`, and `batt_soc_curve_estimate`),
one is a **libm classification primitive** used by `expf`/`ldexpf`, and one is a newlib
binary64 decomposition helper. Nothing new was found on the display, audio, brightness or
LC3 codec paths — those PASS with the new coverage.

### 5.2 Advisory pass with infinity/NaN

`CFG_VERIFY_FLOAT_EXTREMES=1` adds the `infinite` and `nan` profiles. Re-running all 95
adds exactly one function to the FAIL set: **`FUN_00026624`** fails on `infinite`, `nan`,
`relaxed:infinite`, `relaxed:nan`, and in every case the sole difference is the **sign bit
of a default NaN** passed to the reciprocal-square-root helper (`0x7FC00000` vs
`0xFFC00000`). This is the NaN-payload artefact described in §2.3, not a defect. No other
function is sensitive to infinity/NaN inputs beyond what the ordinary sweep already
reports.

---

## 6. Defects fixed this session

All three were found by the fixed harness; all were confirmed against the shipped
disassembly before any source was touched, and all were re-proven with
`cfg_verify.verify` reading the file from disk. **These are the only `recon/**` edits made
by this task**, and they are reported separately here as required.

### 6.1 `FUN_000869f2` / `finitef` — returned a constant

Shipped body:

```
869f2  vmov  r3, s0
869f6  bic   r0, r3, #0x80000000
869fa  cmp.w r0, #0x7f800000
869fe  ite   ge ; movge r0,#0 ; movlt r0,#1 ; bx lr
```

This is newlib's `finitef`: 0 for infinities and NaNs, 1 otherwise. The committed
reconstruction was

```c
int FUN_000869f2(unsigned int param_1) { (void)param_1; return 1; }
```

— an **integer** parameter (so `s0` was never even read) returning 1 unconditionally,
carrying the banner `parity: 300/300 trials, PROVEN`. Replaced with a hard-float body that
tests the exponent field. `cfg_verify` now reports `PASS cases=17 checked=57`.
Updated: `recon/app/src/`, `recon/verified/src/`, `recon/app/src_sym/`,
`recon/verified/src_sym/FUN_000869f2.c`, `recon/named/finitef.c`,
`recon/symbolized/app/finitef.c`. (Its binary64 sibling `finite` @ `0x869dc` is correct.)

### 6.2 `FUN_0000e340` / `battery_soc_from_curve` — float compare instead of a sign-bit test

Shipped body selects the SoC curve pair with

```
0e340  vmov  r3, s1
0e344  cmp   r3, #0
0e348  itete lt ...          ; 0x20002d0c/0x20002d10  vs  0x20002d14/0x20002d18
```

— a **signed integer test on the raw bits**, i.e. a sign-bit test. The reconstruction used
`if (cmpval < 0.0f)`, which differs for `-0.0` and for negative NaNs and selects the wrong
curve pair, then publishes the wrong words to `g_batt_soc_curve_val_lo/_hi`. Replaced with
a union sign-bit test. `cfg_verify` now reports `PASS cases=16 checked=56`.
Updated: `recon/app/src/`, `recon/verified/src/`, `recon/app/src_sym/`,
`recon/verified/src_sym/FUN_0000e340.c`, `recon/named/battery_soc_from_curve.c`,
`recon/symbolized/app/battery_soc_from_curve.c`,
`recon/readable_sources/app/g1/battery_soc_from_curve.c`.

### 6.3 `FUN_00078ce0` (newlib `__d2b`) — a harness normalization gap, not a defect

The generic float cases reached, for the first time, the path taken when the incoming
binary64 has an **all-zero low mantissa word** — true for `0.0`, `1.0`, `0.5`, `2.0` and
never for a uniform random double. On that path the shipped body passes `add r0,sp,#4`
while the candidate passes a differently-placed frame slot; everything else in all 18 cases
matches exactly. This is compiler frame layout, not behaviour, and the *value* the helper
produced remains proven by the following stores through the returned block pointer. Handled
with the established reviewed mechanism —
`REVIEWED_STACK_POINTER_CALLS[("app", 0x00078ce0)] = {1: {0}}` — after confirming that with
it the function PASSes with zero mismatches. **No source was changed.**

---

## 7. What remains unproven

### 7.1 `FUN_0000e53c` / `batt_soc_curve_estimate` — OPEN, real defect

FAILs on `zero`, `negative-zero`, `unit`, `negative-unit`, `half` (40/43 mismatches).
Two defects are already located precisely against the disassembly; a third is structural
and was **not** fixed, so the source was left untouched (a partial fix without a passing
re-proof would add churn without evidence):

1. `0xe924`: on the `lower >= source[0x328]` arm the shipped body sets `s18` — i.e.
   `charge_low` — to `lower`; the reconstruction instead assigns `upper = lower` and never
   updates `charge_low`. Adding `charge_low = lower;` drops the mismatch count from 40 to
   13 (measured).
2. `0xe62c`/`0xe8a6`: `vcmpe.f32 s18,s14; bmi → vmov.f32 s18,s14` is
   `if (charge_low < upper) charge_low = upper;`. The reconstruction has the assignment
   inverted (`upper = charge_low`).
3. **Remaining (structural):** at `0xe73c`/`0xe748` the shipped body special-cases
   `base == lower` and `base == upper` with **exact float equality** and uses the `r2` flag
   at `0xe794` (`cbz r2, 0xe80a`) to *skip* the spline-interpolation block entirely. The
   reconstruction always performs it, so on exact-boundary inputs it calls `FUN_000868fc`
   where the original calls `FUN_0000e938` (reported as `direct-target` at call ordinal 8).
   Reproducing that ladder faithfully — including the `0xe87a`/`0xe8ac`/`0xe8ba`
   out-of-range arms with their own coefficient sets — is the outstanding work.

### 7.2 `FUN_0000c358` / `battery_model_state_update` — OPEN, real defect

FAILs on `zero`, `negative-zero`, `half`, `sensor`, `sensor-negated` (17/23 mismatches).
The first divergence is at call ordinal 31/32, where the two bodies pass a **different
second float argument** to the same callee, and the returned `r0`/`s0` differ by an exact
factor of 5 (`0.6270036` vs `3.1350181`). 49 calls and 106 events per trial; the divergence
needs a dedicated reconstruction pass and was not attempted here.

### 7.3 Residual limits of the harness itself

* **NaN/infinity semantics are not proven.** By design (§2.3), generated cases never feed
  them, and the return comparison canonicalizes NaN payloads (pre-existing `_cf32`/`_cf64`).
  A reconstruction that mis-handles NaN/infinity in a way that only changes a NaN payload or
  sign is still invisible. Deliberate coverage requires a hand-written `REVIEWED_FP_CASES`
  entry, as libm's classification leaves already have.
* **Float reassociation is only caught where inputs make it visible.** Bit-exactness on the
  covered profiles is proven; a reordering that happens to round identically on all of them
  is not excluded.
* **`float_argument_registers` is a linear scan.** A register written on one path and read
  on another can be reported as incoming. That over-drives harmlessly, but the converse —
  an argument slot only reachable through a path the linear decode misorders — is
  theoretically possible.
* **`FUN_0006b3c8`** (liblc3 fft) remains FAIL, as it was before this work.
### 7.4 The `cfg_verify` self-test suite is already broken at `HEAD` — full audit

Running `tools/cfg_verify.py --self-test` aborts partway through, and it does so at `HEAD`
too. Because a sequential run stops at the first bad entry, the suite was audited
**exhaustively instead**: all **406** literal negative controls across its eight tables
(`negative_sources`, `directed_negative_sources`, `display_negative_sources`,
`app_random_negative_sources`, `net_negative_sources`, `net_directed_negative_sources`,
`net_random_negative_sources`, `blocker_negative_sources`) were replayed with each table's
real `trials_random`, under the **fixed** harness and under a `HEAD` copy.

**Result: 397 of 406 still bite, and every outcome is byte-for-byte identical under the two
harnesses. This work flips no control in either direction.** The nine exceptions are all
pre-existing, and they matter — *a negative control that cannot fail is worth nothing*:

| control | table | symptom |
|---|---|---|
| `lc3_tns_analyze` | `negative_sources` | opened `recon/app/src/lc3_tns_analyze.c`, which has never existed (the body is `FUN_0006ffd8.c`) — **fixed here** via `_resolve_source_path`, which is how `verify()` already resolves readable identities |
| `FUN_0100f5d8` | net directed | asserts `"(pre_shift_mix << 26)"`, removed by `d7378f46` when the body was rewritten — **aborts the whole suite** |
| `FUN_00065324` | app directed | asserts a two-argument `FUN_00065000(param_1, param_2)` call; `15ec3d1e` rewrote the body to a one-argument `FUN_00065000(domain)` — **aborts the whole suite** |
| `FUN_01019750` | net directed | vacuous: mutated source PASSes (`checked=8`) |
| `FUN_010388c8` | net random | vacuous: mutated source PASSes (`checked=4`) |
| `FUN_00081080` | app directed | vacuous: FAILs with `checked=0`, i.e. nothing was actually compared |
| `FUN_0004e604`, `FUN_0004e780`, `FUN_0004ee68`, `ancs_connected` | app random | vacuous: mutated sources PASS |

Only the first is fixed here. The rest are source-side questions in trees another agent is
actively editing, and repairing a negative control means giving it a *live* mutation, not
deleting it.

The positive evidence for this work is therefore: `tools/parity/emu.py`'s own self-tests
pass in full (including six new float probes and two new negative controls), and 397/406
`cfg_verify` negative controls behave exactly as they did before.

---

### 7.5 Concurrency note

This task committed nothing. While it ran, the concurrent header/constant session committed
`5b46bcba`, which deliberately excluded `tools/` but **swept all thirteen of this task's
`recon/` source edits into itself** — every copy of the `finitef` and
`battery_soc_from_curve` fixes (`recon/app/src`, `recon/verified/src`, both `src_sym`
mirrors, `recon/named`, `recon/symbolized/app`, `recon/readable_sources/app/g1`) now sits
in that commit under its unrelated message. They are correct and re-proven, but they are
attributed to the wrong change. The harness changes, this report and the `AGENTS.md` entry
remain uncommitted in the working tree.

---

## 8. Reproducing

```bash
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/parity/emu.py            # harness self-tests
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app FUN_00026624
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app FUN_0000e53c   # OPEN defect
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app FUN_0000c358   # OPEN defect
# advisory NaN/infinity pass
CFG_VERIFY_FLOAT_EXTREMES=1 PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app FUN_00026624
```

The float-relevant function list is regenerated by decoding every catalogued function and
recording `s0..s15` registers read before written; `cfg_verify.float_argument_registers`
is the same computation and is the authority.
