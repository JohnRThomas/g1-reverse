# Boot-path correctness defects (P1 ∩ P0)

CFG sweep (`cfg_fails_{app,net}.json`, reverify.py sweeplist ×16 shards, verified
context) intersected with the golden boot-path function set (`golden_boot_trace.json`:
1117 app + 739 net functions that execute during the shipped images' boot to E5).

## Full sweep result
- **app**: 2115 checked, 2087 PASS, **17 FAIL**, 11 timeout, 0 other.
- **net**: 1142 checked, 1126 PASS, **1 FAIL**, 0 timeout, 15 other(inconclusive).

Only defects that (a) execute on the boot path AND (b) are actually compiled into
our build (`generated/app_retained_sources.cmake` / `recon/net/src`) can break our
rebuild's boot. That intersection is small:

## Boot-path defects that affect our build (6)

| core | function | verdict | compiled? | ownership | resolution |
|------|----------|---------|:--:|-----------|------------|
| app | `region_init` @0x00050bf0 | FAIL (40 mism.) | yes | **STOCK** Zephyr `arch/arm/core/mpu/arm_mpu.c` (writes MPU_RNR/RBAR/RLAR 0xe000ed98/9c/a0) | **displace to SDK** — do not hand-fix; build should use Zephyr's arm_mpu.c. FAIL = imperfect recon of a stock fn, harmless once displaced. |
| app | `now_has_persist_task` | timeout (inconclusive) | yes | Even app (persist-task logic) | re-verify with budget; if genuinely wrong, redo via prove() to PASS |
| app | `update_persist_task_status_to_idle` | timeout (inconclusive) | yes | Even app | re-verify; redo if wrong |
| net | `FUN_01011664` | other (inconclusive) | yes | TBD | re-verify; classify + resolve |
| net | `FUN_01025734` | other (inconclusive) | yes | TBD | re-verify; classify + resolve |
| net | `FUN_0102665c` | other (inconclusive) | yes | TBD | re-verify; classify + resolve |

## Off-boot-path FAILs (matter for full correctness/byte-match, NOT for E4 boot-parity)
- app (16): FUN_000165b4, FUN_00033c18, FUN_000440ec, FUN_0004db04, FUN_0004de68,
  FUN_00050c54, FUN_00057484, FUN_00057db0, FUN_0005c0bc, FUN_000639d4, FUN_0006b3c8,
  FUN_00079278, FUN_00087184, SettingStoreHandler, ancs_disconnected,
  send_response_data_to_msgqueue.
- net (1): FUN_01016250.

These are deferred until after E4 boot-parity (they don't execute before steady state
in the original; if our build diverges into one, it resurfaces in P4 differential
bring-up).

## Note
`region_init` being FAIL + compiled is the archetype: several boot functions are
stock code the ownership pass hasn't displaced yet. Triage every boot-path defect by
ownership FIRST — a stock FAIL is displaced, not reconstructed.

## Resolution

All 6 defects triaged to a definitive verdict. Verification used the authoritative
`tools/cfg_verify.py` (`cfg_verify.verify(core, name)`); for functions whose bodies sit
behind a spin-lock or that are absent from the Ghidra catalog, verification was driven
with the tool's own reviewer-metadata machinery (`REVIEWED_STATE_CASES`,
`REVIEWED_CALL_ARITIES_BY_FORMAT`, injected size) so the real branches are exercised.

| core | function | definitive verdict | ownership | action |
|------|----------|--------------------|-----------|--------|
| app | `region_init` @0x00050bf0 | **FAIL** (40 mism., struct-layout only) | **STOCK** Zephyr | displacement recommended (below) |
| app | `now_has_persist_task` @0x0002be64 | **was FAIL → now PASS** (4/4 cases) | **Even app** | fixed + proven, saved |
| app | `update_persist_task_status_to_idle` @0x0002c0e8 | **was FAIL → now PASS** (5/5 cases) | **Even app** | fixed + proven, saved |
| net | `FUN_01011664` @0x01011664 | **PASS** | net (catalog-missing) | false alarm — already correct |
| net | `FUN_01025734` @0x01025734 | **PASS** | net (catalog-missing) | false alarm — already correct |
| net | `FUN_0102665c` @0x0102665c | **PASS** | net (catalog-missing) | false alarm — already correct |

### 1. app `region_init` @0x00050bf0 — STOCK, displace to SDK
Confirmed stock Zephyr, not Even code. The shipped disassembly (`ldrb r4,[r1,#8]`;
`and r2,r4,#0x1f`; `lsr r4,r4,#5`; `ldr r3,[r1,#0xc]`; writes RNR/RBAR/RLAR via
0xe000ed00 base) is **bit-for-bit** the SDK's `region_init` in
`~/ncs251/zephyr/arch/arm/core/aarch32/mpu/arm_mpu_v8_internal.h`, using the SDK's
`struct arm_mpu_region {uint32_t base; const char *name; arm_mpu_region_attr_t attr;}`
(attr at **offset 8**) and packed `struct arm_mpu_region_attr {uint8_t rbar:5;
uint8_t mair_idx:3; uint32_t r_limit;}`. The 40 CFG mismatches come **only** from the
hand-recon's wrong struct layout (omits `name` → attr at offset 4; splits rbar/mair_idx
into a uint32 + a uint8 instead of one packed byte); the register-write arithmetic is
identical. Displace, do not hand-fix.
- **SDK source unit to compile:** `zephyr/arch/arm/core/aarch32/mpu/arm_mpu.c`
  (built with `CONFIG_ARM_MPU=y` for the M33; `region_init` is a `static` inline in the
  included `arm_mpu_v8_internal.h`, so no separate object is produced).
- **Retained-sources entry to remove:** `recon/symbolized/app/region_init.c`
  (line 694 of `recon/generated/app_retained_sources.cmake`).
- **How (owner action, not done here):** that cmake is generated from
  `recon/ownership/adoption_manifest.json`; there is currently **no** manifest row for
  0x00050bf0. Add one — `{core:"app", va:"0x00050bf0", raw_symbol:"FUN_00050bf0",
  current_symbol:"region_init", kind:"sdk", component:"app_sdk", upstream_symbol:
  "region_init", upstream_unit:".../zephyr/arch/arm/core/aarch32/mpu/arm_mpu.c",
  exclude_reconstruction:true}` — then regenerate. (Manifest/build wiring intentionally
  left unedited per task scope.)

### 2. app `now_has_persist_task` @0x0002be64 — Even app, was WRONG, FIXED + PROVEN
The prior "300/300 PROVEN" was **vacuous**: the function opens with
`while (*0x20018d9c) signal_persist_task_event();`, and the harness seeds RAM randomly,
so the lock byte was ~never 0 — every trial spun to the instruction cap and the body was
never executed (bare CLI reports FAIL, `checked=0`). Driving the body (lock seeded free)
exposed a genuine defect: the two logging calls were reconstructed as `DEBUG_PRINT()` /
`FUN_00019c70()` with **no arguments**, and the first branch targeted an unresolved
`DEBUG_PRINT` instead of `log_message` @0x7dda4. Ground truth (disasm) is
`log_message(0xa2566,0xa267b,uVar3,param_2,*(u8*)(p1+0xd5))` for `*0x20007554==0` else
`debug_print(...)` @0x19c70, same args. Rewrote faithfully (correct targets
`FUN_0007dda4`/`FUN_00019c70`, full arg lists). **Proven PASS, 4/4 CFG state cases**
(cover the `status<=1` early return, the `0x2000230c<=3` skip, and both log branches).
Saved to `recon/app/src/now_has_persist_task.c` (+ `recon/verified/src` mirror).

### 3. app `update_persist_task_status_to_idle` @0x0002c0e8 — Even app, was WRONG, FIXED + PROVEN
Same masking: identical spin-lock prologue made the old proof vacuous (CLI FAIL,
`checked=0`). Body-driven verification showed control flow, return, memory writes,
`display_close_screen` @0x49858 call and the `type==0x10` branch were all correct; the
sole defect was the log branch calling unresolved `DEBUG_PRINT(0xa25d9,0xa2625)` instead
of `log_message` @0x7dda4. Corrected to `FUN_0007dda4(0xa25d9,0xa2625)` (and confirmed
the else branch `FUN_00019c70(0xa25d9,0xa2625,0)` @0x19c70). **Proven PASS, 5/5 CFG state
cases** (outer-false skip; log_message branch; `display_close_screen`+debug_print branch;
`0x10` field-copy branch; `type==1` no-log branch). The variadic log helpers required the
per-callsite format arities `(0x7dda4,0xa25d9)->2`, `(0x19c70,0xa25d9)->3` (the original
leaves scratch garbage in r2/r3, which are not arguments). Saved to
`recon/app/src/update_persist_task_status_to_idle.c` (+ `recon/verified/src` mirror).

### 4-6. net `FUN_01011664` / `FUN_01025734` / `FUN_0102665c` — PASS, false alarms
"other/inconclusive" only because these three addresses are **absent from the Ghidra
catalog** (`net_funcs.json`) — they fall in address gaps Ghidra never marked as function
entries, so `cfg_verify` returned `nosize`. Supplying the true extents from the source
headers (0xba / 0x20 / 0x20) and re-running `cfg_verify.verify('net', …)` gives a clean
**PASS** for all three. No defect; reconstructions are already correct, no change made.

### Verifier-metadata caveat (honest note)
Defects #2/#3 are corrected and proven **through `cfg_verify`**, but the *bare CLI*
`cfg_verify.py app <name>` will still report FAIL until two reviewer-metadata entries are
added to `tools/cfg_verify.py`: a `REVIEWED_STATE_CASES[("app",0x2be64/0x2c0e8)]` entry
seeding `0x20018d9c=0` (so the body past the spin-lock runs), and for 0x2c0e8 a
`REVIEWED_CALL_ARITIES_BY_FORMAT[("app",0x2c0e8)]` entry for the variadic log arities.
These are verifier-side coverage metadata, **not** code defects, and were left unadded per
the "do not modify tools/" constraint. The exact case tuples used to prove both functions
are in this session's scratchpad (`test_updidle.py` and the now_has case list). Likewise,
the build compiles `recon/symbolized/app/*.c`, so `symbolize.py` must be re-run to
propagate the two corrected sources into the symbolized tree before a rebuild.
