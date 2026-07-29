# G1 Firmware Reconstruction — Agent Entrypoint

**Read this first.** This repo reconstructs the Even Realities **G1 smart-glasses firmware**
(Nordic nRF5340 dual-core) from the shipped binaries back into buildable, human-readable
NCS/Zephyr C, **proving each function byte/semantics-faithful** to the original. This is a
legitimate recovery of the owner's own device firmware (sources were lost).

The device = smart glasses with 2 projectors (L/R), each on a control board, both BLE
devices synchronising via Nordic's protocol (ESB). Two CPUs:
- **app core** (CPUAPP, Cortex-M33) — application logic. Image `app_update.bin`, link base **0xC200**.
- **net core** (CPUNET) — BLE controller + ESB radio + glue. Image `netcore_image.bin`. **Two coordinate spaces** (see `tools/net_address_space.py`, `recon/catalogs/net_address_spaces.json`): **analysis base 0x01008000** (Ghidra import — function identities, CFG positions, `off = va - 0x01008000` for image bytes) vs **true runtime/link base 0x01008800** (linked execution addresses + stored absolute flash pointers). Delta **0x800**. The image is position-DEPENDENT: it only runs loaded at 0x01008800. Proven by two oracles — the reset vector and the SVCall handler (its vector 0x0102f4c1 lands on the canonical `z_arm_svc` prologue at file offset 0x26cc0 only at base 0x01008800). Net Zephyr build pins this with `CONFIG_FLASH_LOAD_OFFSET=0x8800`; never fall back to the board default 0x01000000.
Separate CPUs/flash/RAM; they share only `sram0_shared` (OpenAMP/rpmsg IPC). **Net core cannot
share structs/functions with app core.**

---

## ⚠️ ENVIRONMENT — non-negotiable

- **`PYTHONSAFEPATH=1` on EVERY python call.** A local `struct.py` shadows the stdlib; without
  this, imports break. Use `/Users/freedomcoder/Projects/G1disasm2/.venv/bin/python`.
- Zephyr toolchain: `/Users/freedomcoder/zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/` (gcc/as/ld/nm).
- Ghidra needs **JDK 21**: `JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home`.
- Firmware build config (confirmed): **NCS v2.5.1, Zephyr 3.4.99, arm-zephyr-eabi GCC 12.2,
  newlib-nano, `-Os` hard-float** (`-mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard`).
  Reference build at `~/ncs251/refapp` (board `nrf5340dk_nrf5340_cpuapp`).
- **Scratchpad** (analysis artifacts, ledgers, JSON) lives OUTSIDE the repo at:
  `/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/<session>/scratchpad` — the
  active one is `bf259b2e-0c97-4e04-ae79-84a08ccae34e`. If the session dir changed, find the
  newest under `/private/tmp/claude-501/-Users-freedomcoder-Projects-G1disasm2/`. Key files there:
  `classified.json` (app funcs+class+size), `net_funcs.json`, `app_funcs.json`, `refgraph_{app,net}.json`
  (Ghidra call/data-ref graph), `symbol_map*.json`, `global_names_*.json`, `suspect_proofs.json`,
  `reverify_*_L*.json` (CFG-sweep results), `*_ledger_*.json` (proof ledgers).
- Persistent memory (loads each session): `/Users/freedomcoder/.claude/projects/-Users-freedomcoder-Projects-G1disasm2/memory/`
  — `g1-parity-pipeline.md` has the deepest state.

---

## THE END GOAL

One cohesive, buildable NCS 2.5.1 **dual-core Zephyr project** assembled from the recovered
functions + headers + data + wiring, that **links with all raw addresses resolved** and whose
build **byte-matches the original image** in a build comparison. `.rodata`/`.data` byte-match is
the achievable, meaningful gate (already 100% on data tables); `.text` gets as close as codegen
allows (parity proves *semantics*, not identical codegen — ~80-90% expected, not 100%). Anything
that cannot be reconstructed ships as a **byte-exact blob** (last resort). **Nothing suspicious
or unverified may be left uninspected.**

---

## METHODOLOGY — how a function is "proven"

1. **Reconstruct** C from Ghidra decomp + annotated Thumb disasm. Convention that makes parity
   exact: globals → fixed absolute-address `volatile` pointers using literal-pool VALUES (match
   width/signedness); callees → `extern` (modeled as identical order-keyed oracles), same order.
2. **Prove** via `tools/parity/emu.py` — a **Unicorn Cortex-M33 differential harness**. It runs
   original vs recompiled candidate over N trials and compares the **side-effect trace**: ABI
   return reg(s) + ordered non-stack memory-write trace + call count/order + fault parity. Pass
   ⇒ auto-saves the `.c`.
3. **Verify with control-flow coverage** — see the CRITICAL finding below.

Reconstruction saves to `recon/app/src/` (app, `recon_kit.RECON_SRC`) and `recon/net/src/` (net,
`net_recon_kit`). `recon/verified/src/` is the app "verified" mirror (keep it synced to app/src:
`cp -n recon/app/src/*.c recon/verified/src/`).

---

## 🔑 CRITICAL FINDINGS

### 1. Harness false proofs (FIXED) — the big one
`emu.make_args` originally seeded non-pointer args with **random 32-bit values**. Any function
that dispatches on a **small-range argument** (switch/enum/opcode/flag: `cmp r1,#8; bhi; tbh
[pc,r1]`) had its real cases **never exercised** — only the default path. A trivially-wrong
reconstruction could pass 300/300. Confirmed on `FUN_01013650` (net).
- **Fix 1 (landed):** `make_args` now mixes small/boundary values (~45%) into non-pointer args.
- **Fix 2 — THE authoritative verifier (`tools/cfg_verify.py`):** derive branch/switch-case
  inputs *from the original CFG* (taint-track which arg each selector derives from; read tbb/tbh
  table sizes; cmp boundaries; cbz/cbnz) and drive **every** case via `emu.compare(..., arg_overrides=)`.
  Coverage is a property of the CFG, not luck. **This is "control-flow with side-effect
  comparison" made sound** (pure CFG graph-iso fails because codegen differs; we instead use the
  CFG to pick inputs, then compare side effects). Self-tests hold; catches false proofs that
  survive biased fuzzing. **All re-verification and redo must use `cfg_verify.verify(core, name)`.**

### 1b. FLOAT-argument false proofs (FIXED) — same shape as #1, different domain
The VFP bank was the *second* input dimension the harness never varied. `s0..s15` were
seeded, but only with **uniform random words** — which, read as binary32, are ~1e±30
magnitudes essentially always, so the values firmware branches on (**exactly 0.0, ±1.0,
±0.5, sensor magnitudes**) had probability ~0, exactly as uniform integers never land in a
small switch range. Float inputs were otherwise driven only by hand-written per-function
`REVIEWED_FP_CASES`; **52 of the 61 app functions taking float args had none**. Measured: a
body returning a different result iff `x == 0.0f` passed 40/40 trials against a candidate
that always answered the other way. `imu_mahony_ahrs_update` (`FUN_00026624`) shipped five
`VNMLS`→`VMLS` sign inversions and returned `PASS cases=2` **on the broken body too** — its
reviewed fixture pinned the identity quaternion `q=(1,0,0,0)`, which makes the sign errors
cancel algebraically for *every* argument (a **degenerate fixture** hides a defect no matter
how the arguments vary).
- **Fix (landed):** `emu` seeds `s0..s15` from a pooled realistic float/double generator
  (boundary values over-sampled, ~20% still uniform random) and can seed the argument-pointer
  region with plausible floats (`float_scratch_trials`); `cfg_verify.float_argument_registers`
  derives the incoming VFP slots **from the shipped instructions** and
  `build_float_cases` drives every float function through exact-value profiles plus a
  per-argument `zero-arg-sN` probe — including a `relaxed:` variant that drops a reviewed
  absolute fixture so a degenerate state cannot hide anything. Broken `FUN_00026624` now
  FAILs 17/48; corrected PASSes 48/48.
- **NaN/infinity are deliberately excluded** from generated inputs: equivalent float code
  does not preserve NaN sign/payload while writes compare bit-exactly, so seeding them fails
  *correct* reconstructions. Opt in with `CFG_VERIFY_FLOAT_EXTREMES=1` (advisory only).
- **`-ffp-contract` is a per-TU build contract recovered from the image:** `VMLA`-family =
  unfused (contract off, all 5 G1 application float bodies), `VFMA`-family = fused (all 19
  liblc3/libm bodies), never mixed. `cfg_verify` now derives it. **The cohesive build must
  set `-ffp-contract=off` for `FUN_00026624/265e8/26828/7cab4/fuel_gauge_update`** or their
  codegen cannot byte-match.
- **Net core has ZERO floating-point instructions** (CPUNET has no FPU) — this class is
  app-core only.
- **`cfg_verify --self-test` is ALREADY BROKEN at HEAD** and cannot run to completion: 2 of
  its 406 negative controls assert strings that source rewrites removed (`FUN_0100f5d8`,
  `FUN_00065324`) and 7 more are vacuous (mutated source PASSes / `checked=0`). Audited
  exhaustively under both harnesses — 397/406 bite and every outcome is identical, so this
  work flips none of them. Details + the list: `float_arg_harness_fix.md` §7.4.
- Sweep + open items: `recon/analysis/float_arg_harness_fix.md`. Fixed defects: `finitef`
  (`FUN_000869f2`, was `return 1`), `battery_soc_from_curve` (`FUN_0000e340`, float compare
  where the image does a sign-bit test). `FUN_0000e53c` `battery_soc_curve_model_init`
  — repairs landed in P4 iteration 40 (a 16-byte-short catalogued extent, the temperature
  break-point selection, and the range test / slope sign / two table indices of the output
  interpolation — `recon/emulator/reports/our_boot_bringup.md` §40.10). ⚠ **NOT "CLOSED".
  Downgraded 2026-07-29 to `NOT ESTABLISHED`.** Its closure was decided by `cfg_verify`,
  which this same file says is not evidence on this code. The independent `modtest` harness
  cannot decide it either: its single primary divergence is a stack-frame relative offset at
  one call, and the fault that follows comes from reading back an out-parameter `emu` never
  models — both are documented harness limitations, not observations about the code
  (`recon/analysis/test_architecture.md` §28.5). **No evidence of a defect and no proof of
  correctness. It needs a real oracle, not another green harness run.**
  **STILL OPEN, and in the SAME undecided regime — all 46 of its golden runs fault:**
  `FUN_0000c358` `battery_model_state_update` (§28.5.1). ⚠ **Measured 2026-07-29: exactly
  SIX app symbols read back a stack buffer they passed to an emulated (opaque) callee, which
  `emu` never fills — and THREE of the six are the only open "real defects" this project's
  harnesses have named** (`battery_model_state_update`, `battery_soc_curve_model_init`,
  `md5_process_block`; the other three are exposed and pass). For six symbols the
  proportionate fix is hand-written reviewed out-parameter fixtures
  (`emu.oracle_memory_writes` / `stack_objects`, which `modtest` does not populate). Until
  then **none of the three is evidence of a reconstruction defect.**
  `recon/analysis/test_architecture.md` §28.5.2.

### 2. Ghidra data-inflation — many "huge" functions are small code + a trailing DATA table
Ghidra folds a trailing rodata table into the function symbol. CFG-reachable analysis (BFS from
entry, follow branches/jump-tables, stop at ret) vs declared size reveals e.g. `ble_process_put_req`
25616B → **242B code** + 25KB data; `imu_fusion_thread` 2268→86; `FUN_0006c778` 10232→1002.
~24 app + 8 net functions inflated. **Fix:** reconstruct only the true code extent, split the
trailing bytes into a byte-exact rodata file. CAVEAT: CFG-reachable is a LOWER bound — jump-table
functions look inflated because CFG stops at the computed branch; RESOLVE the table before
truncating. `truesize.py` only EXTENDS (won't catch over-reports).

### 3. Two source dirs — canonical is `recon/app/src` (live recon_kit output, currently 1735).
`recon/verified/src` is a mirror. Keep synced.

---

## PROJECT STRUCTURE

```
recon/
  app/src/          1735 proven app .c (LIVE, recon_kit output)      [canonical]
  verified/src/     app "verified" mirror (sync from app/src)
  net/src/          698 proven net .c
  net/data/         net rodata tables split off inflated funcs
  named/            app funcs renamed to human names (1209+)
  symbolized/{app,net}/  address->symbol substituted, compilable sources (100% compile)
  symbols/          g1_{app,net}_symbols.h, *_globals.ld (PROVIDE pins), *_aliases.ld
  data/             993 byte-verified app rodata tables (100% byte-match)
  modules/          20 app subsystems (headers/README/wiring) — for module-cohesion end goal
  headers/          g1_types.h, ipc_sync.h, zephyr_objects.h
  board/            g1_board.overlay, pins_gpio.md, pins_buses.md, prj.conf
  wiring/           app_objects.c (K_*_DEFINE), GAPS.md
  deferred/         functions that cannot be parity-proven (byte-exact source kept)
  blobs/{app,net}/  byte-exact .S blobs (LAST RESORT), from make_blobs.py
  refactor/         *** THE STAGED REFACTOR LADDER *** driver.py + transforms/t00..t09,
                    one stage_NN_*/ dir each (tree/ + MANIFEST/QUARANTINE/SIZE_GATE json).
                    README.md ends with the AUTHORITATIVE R7 gate record.
  emulator/         Renode boot-parity harness: scripts/ (capture + oracle build +
                    slot_quantised_compare.py, the FROZEN criterion), reports/
                    our_boot_bringup.md (the running log) and the golden framebuffers.
tools/
  parity/emu.py         FROZEN harness (Unicorn diff). make_args fixed; arg_overrides added.
  parity/recon.py       compile+link candidate at real VA with stub callees
  recon_kit.py          app: info(va), prove(va,size,name,src,nptr,trials); RECON_SRC=recon/app/src
  net_recon_kit.py      net mirror (base 0x01008000, net_extract bytes)
  extract.py            app image byte/literal reads (base 0xC200)
  net_extract.py        net image reads (off = va - 0x01008000)
  cfg_verify.py         *** CFG-directed side-effect verifier -- NOT evidence on the ladder ***
  modtest/              golden-vector regression suite oracled by the SHIPPED image
                        (gen | run | grade | index).  Vectors: recon/tests/vectors/<core>/.
                        Design + all measured results: recon/analysis/test_architecture.md
                        (app, newest section last -- §28 as of 2026-07-29) and
                        recon/analysis/net_test_coverage.md (net).
                        Vectors carry a HARNESS FINGERPRINT and `run` refuses a stale one;
                        `MODTEST_ORACLE_PRESERVE` / `MODTEST_DERIVED_ARITY` are stamped too.
                        App coverage as of 2026-07-29: 923 symbols across 15 modules.
  reverify.py           corpus sweep (sweeplist/batch modes) -> uses cfg_verify
  build_symbol_map.py   address->symbol map (both cores)
  symbolize.py          write symbolized sources + headers (comment/string-aware substitution!)
  gen_linker.py         PROVIDE(name=0xADDR) pin fragments
  full_link.py          phase-4 driver: compile all + partial link + categorize undefined
  make_blobs.py         byte-exact .S blobs (last resort)
  truesize.py           extend Ghidra under-reported sizes (does NOT catch over-reports)
  worklist.py           remaining()==0 means all targets have a reconstruction
  *_flow.wf.js          Workflow scripts (Fable/Sonnet agent waves)
```

---

## CURRENT PHASE (2026-07-28) — EMULATOR BOOT-PARITY + THE STAGED REFACTOR LADDER

**Read this before the older CURRENT STATE section below**, which is a snapshot
of the *reconstruction* workstream as of 2026-07-11 and is not maintained.

The project's active front is the **staged refactor ladder** in
`recon/refactor/` (stages 00–09) and its **R7 behavioural gate**, run on Renode
against the shipped firmware's own captured bus traces.

* **Authoritative ladder record:** the `★ R7 GATE RECORD — ITERATION 53` section
  at the **end of `recon/refactor/README.md`**. It states, for all ten stages in
  one place, what the stage does, its codegen class, how it is proven and what
  it quarantines. **Every R7 verdict above it in that file is superseded.**
* **Working notes / full measurements:** `recon/emulator/reports/our_boot_bringup.md`,
  newest section last (§53 as of 2026-07-28).
* **Status as of iteration 53:** stages **00–09 all `current`**, all ten build
  and link (`exit 0`, 0 undefined), **all ten match the four shipped golden
  framebuffers 4/4**, and the ladder is green end to end — **eight of its ten
  steps decided by `cmp`** (byte-identical images or byte-identical 20 s
  captures) and **two by the gate, both at `D = 0.000 ms`** on all six streams
  of both stimuli. The cumulative `stage 00 → stage 09` comparison is also
  `D = 0.000 ms`. App flash 956,840 B / 97.39 %; net `zephyr.bin` **FROZEN at
  225,581 B** and not rebuilt.
* **The criterion is FROZEN: `W = 100.513 ms`, `R = 1.160 ms`**
  (`recon/emulator/scripts/slot_quantised_compare.py`). Do not retune it. Note
  `W` is **not** the BLE connection interval — that is 30 ms
  (`CONNECT_IND Interval = 0x0018`); `W` ≈ 3.35 of them. That observation does
  **not** license changing `W`, which was derived from shipped-vs-shipped.
* **The pipeline carries exactly ONE named quarantine**, in stage 07:
  `serialization_ipc_ept_register` (`transforms/t07_internal_linkage.py`,
  `MEASURED_EXCLUSIONS`). It is **empirical, not a rule, and not a defect fix** —
  an owner decision recorded with its measurement. Do not generalise it into a
  predicate; the two candidate predicates are both measurably wrong (§52.5).
* **`cfg_verify` is NOT evidence on this code.** §51 showed it is blind in both
  directions here — it PASSes a real defect and FAILs its repair, because its
  opaque callee stub always clobbers `r0`. Never cite a green `cfg_verify` as
  proof in the ladder/parity workstream. (It remains useful as a *diagnostic*
  for the reconstruction workstream below.)
* **Owner rule, still binding:** never apply refactoring transforms to the
  canonical address-keyed trees (`recon/app/src`, `recon/verified/src`,
  `recon/net/src`, …). **Defect repairs** there are legitimate and have been
  made (iterations 39–45, 49–51). A stale stage is **REGENERATED**
  (`driver.py materialize N`), never hand-patched.
* **Still open, carried forward:** `battery_model_state_update` (`FUN_0000c358`)
  is an unrepaired float-path defect; five console lines still differ from the
  shipped firmware in the base build (listed in §51.9 item 1); the cross-TU
  `int`/`void` return-type sweep (§51.9 item 3) has never been run; stage 99 is
  a diagnostic and is permanently stale.

---

## CURRENT STATE — reconstruction workstream (snapshot 2026-07-11, NOT maintained)

- **App: 1735 reconstructions; Net: 698.** `worklist.remaining()`==0 both (every target has a `.c`).
- **Symbolization + naming complete:** address→symbol maps both cores; app 589/589 globals named;
  net 267/269. Symbolized trees **100% compile** (2388/2388). Provenance `/*=0xADDR*/` kept at each site.
- **Data byte-match 100%** (839 rodata tables, 43239 bytes).
- **Partial link succeeds** (full_link.py); undefined = pinned globals + library + Ghidra pseudo-ops
  (SCARRY4/EPILOGUE/__impl) + the unproven residue. Zero surprise application gaps.
- **Harness false-proof fix + CFG verifier landed and committed.**
- ⚠ **NEW FALSE PROOF, 2026-07-29 — `i2c_read_reg16_be` (`FUN_000847d8`, `recon/symbolized/app/
  i2c_read_reg16_be.c`).** Its own header claims `parity: 300/300 trials, PROVEN`; it **FAILs
  5 of 7 golden fixtures on BOTH trees at 100 % coverage** under `tools/modtest`. The shipped
  code builds a two-element `i2c_msg`-shaped descriptor on the stack and passes its address;
  the reconstruction spells that descriptor as **six independent stack locals** and relies on
  the compiler laying them out contiguously in declaration order. C guarantees no such thing
  and GCC does not do it — offset 4 of the candidate's descriptor holds `param_1` spilled
  (`0x20011008`) where the image has the constant `1`. **Verified under the firmware's own
  `arm-zephyr-eabi-gcc 12.2`**, so it is not an artefact of the harness compiling with a newer
  compiler. NOT repaired; the repair is a real `struct i2c_msg msgs[2]` and needs its own
  proof. `recon/analysis/test_architecture.md` §22.1, §28.6. **A `parity: N/N PROVEN` banner
  in a reconstruction header is not evidence that survives contact with a fixture that
  actually reaches the call.**
- **IN PROGRESS — CFG sweep is PARTIAL:** `cfg_sweep_fails.json` (repo root) holds **40 confirmed
  false proofs so far (24 app + 16 net)** but only ~44% of suspects were checked before the shards
  ended (~409/919 app, ~266/540 net). **Next session step 1: re-run the CFG sweep to completion**
  (`for i in 0..7: PYTHONSAFEPATH=1 .venv/bin/python tools/reverify.py sweeplist app|net i 8`,
  then aggregate `reverify_{app,net}_L*.json` FAIL arrays) — the full list will be larger than 40.
  Known fails incl. `FUN_01013650`,`FUN_0101ba58`,`FUN_0101a38c` (net), `FUN_00018334`,`FUN_0004f1d0`
  (app) — the last two were "redone" overnight but STILL fail under proper case coverage.

---

## REMAINING PLAN (in order)

> **Items 5 and 6 are substantially DONE and have moved on.** The dual-core
> project links (`nm -u` 0 on both cores), builds, boots on Renode and matches
> the four shipped golden framebuffers; module cohesion is delivered by the
> staged refactor ladder (stages 03–09), not by a Fable sweep. See the CURRENT
> PHASE section at the top. Items 1–4 below belong to the reconstruction
> workstream and are unaudited by this pass.

1. **Finish CFG sweep** → authoritative false-proof list (`reverify_{app,net}_L*.json`, FAIL arrays).
2. **Redo every CFG-FAIL** with Fable agents (`tools/reverify_redo_flow.wf.js` pattern; agents
   re-verify with `cfg_verify` before saving). This also covers the app functions the 2:50 limit
   cut off. For data-inflated ones: reconstruct true code only, split data (see finding #2).
3. **Huge/irreducible functions:** first check inflation (finding #2) and whether they break down;
   Fable until only genuinely-huge remain. **Blob (make_blobs.py) ONLY as last resort.**
4. **Structs/data-pointers:** after function updates, update `recon/symbols/*.h`, `recon/headers/`
   so global/struct/pointer decls match the reconstructed accesses.
5. **Full link (`full_link.py app`/`net`):** regenerate symbol map + symbolize + gen_linker +
   aliases first; resolve all raw addresses; remaining undefined must be genuine SDK library
   symbols only. Fix incompatibilities (type reconciliation, `__impl` aliases, stub pseudo-ops).
6. **END GOAL — build comparison + module cohesion:** a Fable-agent sweep reconstructs cohesive
   modules from the fully-linkable functions + headers into one NCS 2.5.1 dual-core project; build
   it and byte-compare `.text`/`.rodata`/`.data` + section map vs `app_update.bin`/`netcore_image.bin`.

**Cost note:** the user is cost-sensitive AND there is a rolling ~5-hour usage limit that halts ALL
sessions (a limit halt stranded work overnight; a permission dialog also blocked all night — avoid
tools that pop approval prompts if unattended). **Compute (full_link, cfg sweep, byte-match) is
FREE on the agent budget; reserve the budget for Fable reconstruction/module waves.** Commit each
milestone to git locally. If approaching the limit, pause and defer the expensive Fable work.

---

## RESUME CHECKLIST

```bash
cd /Users/freedomcoder/Projects/G1disasm2
git log --oneline | head            # milestones
# authoritative fail list from the last CFG sweep:
PYTHONSAFEPATH=1 .venv/bin/python -c "import json,glob; \
 [print(c, sum((json.load(open(f)).get('FAIL',[]) for f in glob.glob('<SCRATCH>/reverify_%s_L*.json'%c)),[])) for c in ('app','net')]"
# re-verify ONE function authoritatively:
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py <app|net> <FUNC_NAME>
# reconstruct+prove one function: recon_kit.prove / net_recon_kit.prove (see NET_PLAYBOOK.md)
# full link probe:
PYTHONSAFEPATH=1 .venv/bin/python tools/full_link.py app
```
Verify EVERYTHING with `cfg_verify`; do not trust a bare `pass:True` from a raw `emu.compare`
without case coverage. Do not leave any FAIL or `deferred/`/`blob` unexplained.
