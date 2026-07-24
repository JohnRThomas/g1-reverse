# Our-build boot bring-up vs golden trace (P4 iteration 1)

**Moment of truth.** The firmware *rebuilt from the reconstructed sources* was
loaded into Renode and traced against the shipped-image golden oracle
(`golden_boot_trace.md` / `.json`). This is an honest report of exactly how far
it boots and where it first diverges.

## TL;DR

- **Milestone tier reached: E3 in full, and it *enters* E4** (CPUNET released &
  executing + rpmsg/IPC endpoint bring-up begins) — then the **app core hard-faults**.
- **First hard divergence:** `blx r3` in **`log_msg_process`** (our `0x42a4a`,
  app instr **4707994** of 4707995) branches to **PC=0x10B168B4** (QSPI XIP
  window) → `CPU abort: Trying to execute code outside RAM or ROM`.
- **Root cause / classification:** an **absolute DATA-pointer literal not
  relocated**. `log_msg_process` iterates the Zephyr `_log_backend_list`
  section using two symbols pinned to the *original-image* addresses
  `0x882a0`/`0x882b0`, but our relocated build places that section at
  `0x80640`/`0x80650`. It therefore walks foreign memory, loads a garbage
  `log_backend_api*`, and calls through a corrupt `api->process` pointer.
- **Next fix:** in `recon/symbols/g1_app_globals.ld` rebind the two
  `log_msg_process` bound-symbols to the linker-provided
  `_log_backend_list_start` / `_log_backend_list_end` instead of the pinned
  absolutes (same idea as `pointer_rebind.md`, applied to these two DATA
  section-boundary symbols). At least 4 sibling functions carry the same class
  of latent unrelocated pointer (see §5) and should be swept together.

---

## 1. Loader setup

New additive loader **`armemul/g1-ours.resc`** (shipped-image `g1.resc` /
`golden_trace.resc` untouched). It mirrors the golden determinism environment
exactly and `LoadELF`s our two builds:

| aspect | value |
|--------|-------|
| model set / load order | identical to `g1.resc` (all `models/*.cs`) |
| core scheduling | serial — `MasterTimeSource.ExecuteInSerial = True` |
| global quantum | `0.000010` s |
| CC312 RNG seed | `0x5340CC3105340CC3` |
| FICR/UICR + QSPI ext-store seed | loaded (same binaries as `g1.resc`) |
| app image | `LoadELF /private/tmp/g1-ours-app/zephyr/zephyr.elf` → cpuapp; VTOR/PC/SP set from `0xC200` |
| net image | `LoadELF /private/tmp/g1-ours-net/zephyr/zephyr.elf` → cpunet; VTOR/PC/SP set from `0x01008800` |
| net flash enlargement | net LMA ends `0x01040279` (> stock `0x40000`). Renode **rejects** redeclaring the registered `flash_net`, so the loader **adds a contiguous 0x1000 tail region** `flash_net_tail @ 0x01040000` via `LoadPlatformDescriptionFromString` (additive; `platforms/nrf5340.repl` untouched). Net flash effectively `0x41000`. |

Builds (both exit 0, undefined=0):
`recon/application/build_cohesive.sh app /private/tmp/g1-ours-app` and
`... net /private/tmp/g1-ours-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF`.
App LOAD `0xC200..0xa4074`; net LOAD `0x01008800..0x0103f90c` + rodata to `0x01040279`.

**Deliberately omitted:** `g1.resc`'s `cpuapp AddHook 0x19308/0x16268` device-info
seeds. They are pinned to *original-image* PCs (wrong in our relocated build) and
only affect BLE naming / ESB pairing (beyond E4); the golden trace is autonomous
(stimulus-free) boot regardless.

Trace/analyze mirrors golden, with **one necessary change**: PC→name resolution
uses **our ELF's own `nm` table** (`scratchpad/analyze_ours.py`), not the
original catalog — our build relocates every function, so the original
`function_names_app.json` addresses would mis-map. Symbol *names* still match
golden, so the event lists are directly comparable by name. Our per-core event
JSON saved beside the golden: `recon/emulator/reports/our_boot_trace_{app,net}.json`.

---

## 2. How far it boots (milestone tier + instruction counts)

App core executed **4,707,995** instructions before the abort; **466** unique
functions entered. Milestone evidence (our first-entry instr index):

| tier | golden marker | our build | our first_i |
|------|---------------|:---------:|-------------|
| **E1** reset→kernel | reset vector, region_init, k_sem_init | **reached** | `z_arm_reset` 0; `region_init` 80,111; `z_impl_k_sem_init` 80,492 |
| **E2** device / SYS_INIT | clock init, **`nrf_cc3xx_platform_init`** | **reached (past CC312 blocker)** | `nrfx_clock_init` 81,126; `nrf_cc3xx_platform_init` 83,071 |
| **E3** main + threads | `z_impl_k_thread_create`, `main` | **reached** | `z_impl_k_thread_create` 613,974; **`main` 4,667,207** |
| **E4** "it lives" | net released, IPC, display, `bt_start`, ADV_IND | **entered, not completed** | CPUNET **released & executing** (`clock_app: Network core released`; net core ran from its reset vector, 85k instr); **`ipc_service_open_instance` 4,668,358** (rpmsg endpoint bring-up begins). **NOT reached:** `ipc_service_send`, `spi_read_id` (display), `bt_start`, first ADV_IND. |
| **E5** | steady state | no | — |

So the rebuild clears **E1–E3 outright** and satisfies the **first E4 sub-condition
(CPUNET released & executing)** plus the start of IPC endpoint registration,
then faults ~40.8k instructions into `main()`'s bring-up.

---

## 3. First divergence (precise)

- **Where:** `log_msg_process` (recon `FUN_0004d334`), our address `0x00042a4a`,
  instruction **4,707,994** (0-based; last executed).
- **Faulting instruction:** `42a4a: blx r3` — a call through
  `log_backend->api->process`.
- **Actual next PC:** `0x10B168B4` (r3 = `0x10B168B5`, odd/Thumb). This is the
  QSPI **XIP window** (base `0x10000000`, offset `0xB168B4`). Renode:
  `qspi: XIP read ... while disabled` then
  `cpuapp: CPU abort [PC=0x10B168B4]: Trying to execute code outside RAM or ROM`.
- **Expected next (golden):** a valid `log_backend_uart_api.process` call
  (golden reaches E5, so its `log_msg_process` iterates the real backend list
  and continues normally).
- **Fault type:** hard CPU abort (prefetch/execute from unmapped/XIP space),
  caused by dereferencing a garbage `log_backend` entry.

### Provenance (exact)

`log_msg_process` loads its iteration bounds from its constant pool:

```
429f4: ldr r9, [pc,#216]  ; = 0x000882b0   (end bound)
429f8: ldr r4, [pc,#184]  ; = 0x000882a0   (start bound)
 ...
42a42: ldr r3, [r4,#0]    ; r3 = backend->api   (backend @ 0x882a0 = FOREIGN memory)
42a44: ldr r3, [r3,#12]   ; r3 = api->process   (garbage)
42a4a: blx r3             ; -> 0x10B168B4  FAULT
```

In our ELF `nm`: the real log-backend section is **`log_backend_area @ 0x80640`**
(`_log_backend_list_start = 0x80640`, `_log_backend_list_end = 0x80650`, one
entry `log_backend_uart`, api `log_backend_uart_api @ 0x896c4` — all valid). But
the two symbols `log_msg_process` uses are **absolute pins to the original image**:

```
recon/symbols/g1_app_globals.ld:177  PROVIDE(rodata_882a0 = 0x000882a0);
recon/symbols/g1_app_globals.ld:178  PROVIDE(__settings_handler_static_list_start = 0x000882b0);
nm:  000882a0 A rodata_882a0
     000882b0 A __settings_handler_static_list_start
```

`0x882a0` in *our* relocated build lands inside the generic `rodata` section
(`0x806d0..0x8a074`), not the backend list, so `*(0x882a0)` is arbitrary rodata
read as a `log_backend_api*`.

The reconstructed source names them literally
(`recon/symbolized/app/log_msg_process.c:31-32`):

```c
int *piVar1 = (int*)&__settings_handler_static_list_start; /*=0x882b0*/  // should be _log_backend_list_end
int *piVar5 = (int*)&rodata_882a0;                         /*=0x882a0*/  // should be _log_backend_list_start
```

The symbolizer mislabeled the original `_log_backend_list_start/end` boundary
(0x882a0/0x882b0) as `rodata_882a0` / `__settings_handler_static_list_start`
(the adjacent settings-handler section began at the same 0x882b0 in the original
layout), and both got pinned as absolutes rather than bound to the real Zephyr
section-boundary symbols.

---

## 4. Classification of the first divergence

**Absolute DATA-pointer literal not relocated** (task category 3), boot-critical
variant. Not a recon defect (the function's *logic* is parity-proven 300/300 and
correct); not a missing thread root; not a Kconfig/DT mismatch; not an emulator
gap. It is a symbol-binding/relocation error: two data section-boundary symbols
were fixed to original-image addresses instead of following the linker.

Boot-critical because Zephyr logging (`CONFIG_LOG`) runs extremely early —
`log_msg_process` is invoked from the log-processing path during `main()`'s
bring-up, right after CPUNET release and the first rpmsg endpoint open.

---

## 5. The next few divergences (same class, cheap to note)

Immediately before the fatal `blx`, four functions performed **reads through
garbage pointers** that Renode logged as "read from non-existing peripheral"
(returned 0, so **non-fatal** this run, but each is the same unrelocated-absolute
defect and will need fixing):

| PC (ours) | function | garbage address read |
|-----------|----------|----------------------|
| `0x4b9c4` | `ipc_service_open_instance` | `0xC016CBE4` (via `[r0+8]` in the ipc config) |
| `0x4295c` | `serialization_register_endpoint` | `0xC016CBF0` |
| `0xd36c`  | `strlen` | `0x29287325` (bad string arg) |
| `0x77fc6` | `get_skip` (mpsc_pbuf) | `0x800333DB` |

These sit on the rpmsg/IPC endpoint-registration path (E4 IPC bring-up) and are
consistent with the residual unresolved-pointer set (`pointer_rebind.md`: 24 app
literals kept unrelocated, incl. rpmsg/ipc endpoint callbacks). They are latent
now only because the log fault kills the core first.

---

## 6. Concrete next fix (drives P4 iteration 2)

1. **Rebind the two `log_msg_process` bounds** in `recon/symbols/g1_app_globals.ld`:
   replace the absolute `PROVIDE(rodata_882a0 = 0x882a0)` /
   `PROVIDE(__settings_handler_static_list_start = 0x882b0)` **as used by
   log_msg_process** with references to the linker-provided
   `_log_backend_list_start` / `_log_backend_list_end` (the real
   `log_backend_area` section symbols, already present at 0x80640/0x80650). Same
   mechanism as the function-pointer rebind in `pointer_rebind.md`, applied to
   these DATA section-boundary symbols. (Care: `rodata_882a0` and
   `__settings_handler_static_list_start` may be referenced by other TUs — bind
   the *log_msg_process* iteration specifically to the log-backend section symbols;
   if the settings-handler section start is genuinely needed elsewhere, use the
   real `__settings_handler_static_list_start` linker symbol there too, not the
   0x882b0 pin.)
2. **Rebuild app**, reload `g1-ours.resc`, re-trace, and confirm
   `log_msg_process` iterates `0x80640..0x80650` and returns normally.
3. **Sweep the §5 cluster** (rpmsg/ipc endpoint pointers) the same way so the
   next E4 step (`ipc_service_send`, then display `spi_read_id`, then `bt_start`
   + first ADV_IND) can be reached. Re-evaluate the net core, which was released
   and began booting but only ran ~85k instructions before the app abort halted
   forward progress.

Acceptance target unchanged: reach E4 (`bt_start` / first ADV_IND / display init)
on our build, matching the golden markers.

---

## Regenerate

```sh
# build (both cores)
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-ours-app
recon/application/build_cohesive.sh net /private/tmp/g1-ours-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# trace in Renode
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain -e 'i @/tmp/g1_ours/trace_ours.resc' > /tmp/g1_ours/ours_run.out 2>&1
# analyze (our-ELF nm symbol map)  [script + nm maps in the session scratchpad]
S=<scratchpad>
PYTHONSAFEPATH=1 .venv/bin/python $S/analyze_ours.py $S/app_nm.txt /tmp/g1_ours/trace_app.log recon/emulator/reports/our_boot_trace_app.json
PYTHONSAFEPATH=1 .venv/bin/python $S/analyze_ours.py $S/net_nm.txt /tmp/g1_ours/trace_net.log recon/emulator/reports/our_boot_trace_net.json
```

`g1-ours.resc` and `/tmp/g1_ours/trace_ours.resc` are the loader and trace
driver; `analyze_ours.py` + the two `*_nm.txt` maps live in the session
scratchpad. Nothing committed; `armemul` changes are additive only
(`g1-ours.resc` + the in-script tail-region override).

---

# Iteration 2 — log-backend iterable-section rebind

Applied the §6 fix, rebuilt, re-booted, re-traced. **The QSPI-XIP log fault is
resolved.** But the re-trace also corrects iteration 1's own diagnosis: the
`log_msg_process` abort was a *secondary* fault inside the fatal-error logging
path. The **true first divergence is an earlier kernel OOPS** (instr ~4,702,339)
that iteration 1's log double-fault had masked. The milestone tier is therefore
**unchanged** from iteration 1 — this iteration removed the masking fault and
exposed the real blocker; it did not advance the boot.

## 1. Pins rebound (in `recon/symbols/g1_app_globals.ld`)

Two pins — and *only* two; a full sweep (below) found no others of this class.
Both were mislabeled by the symbolizer as generic `rodata` / settings symbols but
are in fact the Zephyr **log-backend iterable-section boundaries**:

| pin (name) | was (absolute, original-image) | now (linker section symbol) | resolves to (our build) |
|---|---|---|---|
| `rodata_882a0` | `0x000882a0` | `_log_backend_list_start` | **0x00080640** |
| `__settings_handler_static_list_start` | `0x000882b0` | `_log_backend_list_end` | **0x00080650** |

**Why one value serves two consumers.** `__settings_handler_static_list_start`
is referenced with a *double meaning*: as the log-backend-list **end** (7 log
functions) and as the settings-handler-list **start** (3 settings functions). In
the shipped image both were `0x882b0` because the two iterable sections are
adjacent (log-backend list ends exactly where the settings-handler list begins).
That adjacency is **preserved by the linker in our relocated build**:
`_log_backend_list_end == _settings_handler_static_list_start == 0x80650` (nm
confirms). So binding the pin to `_log_backend_list_end` is simultaneously the
correct settings-handler-list start. No source edit and no symbol split needed.

## 2. Sweep of the same class (systematic, not one-off)

Searched every `PROVIDE(...)` in `g1_app_globals.ld` and every reconstructed app
source for Zephyr iterable-section boundary pins. Findings:

- The **only** iterable-section boundary pins referenced by reconstructed code
  are the two above (`__settings_handler_static_list_start` appears in 16 sites;
  `rodata_882a0` in the 7 log functions). No other `_*_list_start/end`,
  `__*_start/end`, `_bt_*_static_list_*`, `__device_*`, `__init_*`,
  `_net_buf_pool_list_*`, `_static_thread_data_*`, `_shell_*` boundary pin is
  wired into reconstructed code — those sections are iterated by **stock SDK
  code**, which already uses the linker's real symbols.
- The `g_*_list_head/tail/next` and `log_backend_count` pins are **RAM runtime
  globals at `0x2000xxxx`** (linked-list heads, counters) — genuine absolute
  pins, correctly left untouched.
- **One residual latent defect, NOT a linker pin, left in place (out of scope):**
  the settings-handler-list **end** is a hard-coded integer literal `0x00088328`
  inside the reconstructed `settings_register.c` / `settings_parse_and_lookup.c`
  sources (the original `_settings_handler_static_list_end`; ours is `0x806c8`).
  It is in canonical recon C, not the linker script, so it is not fixed here.
  It only bites if a settings iteration runs; the boot faults earlier (§5), so it
  stays latent this round. Flagged for a source-level pass.

## 3. Rebuild status

`build_cohesive.sh app /private/tmp/g1-ours-app` → exit 0. **0 undefined, 0
duplicate** symbols. FLASH **626384 / 982528 B = 63.75%** (unchanged — the rebind
adds no code). Verification in the linked ELF:

```
nm:   00080640 R rodata_882a0                          (= _log_backend_list_start)
      00080650 R __settings_handler_static_list_start  (= _log_backend_list_end = _settings_handler_static_list_start)
log_msg_process constant pool (was 0x882a0 / 0x882b0):
      42ab4: .word 0x00080640   ; start  (loaded into r4)
      42ad0: .word 0x00080650   ; end    (loaded into r9)
```

## 4. Log fault resolved (confirmed on hardware-model)

Re-booted via the unmodified `g1-ours.resc` / `trace_ours.resc`. `log_msg_process`
now iterates the **correct** range `0x80640..0x80650` (one entry,
`log_backend_uart`). Renode log for iteration 1 vs 2:

```
iter-1:  qspi: XIP read at offset 0xB168B4 while disabled; returning 0
         cpuapp: CPU abort [PC=0x10B168B4]: Trying to execute code outside RAM or ROM   <-- GONE
iter-2:  (no QSPI-XIP read, no 0x10B168B4 abort)
```

`log_msg_process` runs to completion; the whole fatal-error logging path now
flushes and reaches `nrf_cc3xx_platform_abort` (instr 4,708,476 — never reached
in iter-1), after which both cores halt (`PC does not lay in memory ...`), which
is the platform's fatal/reset hook, not a code abort.

## 5. New milestone tier + the corrected first divergence

**Milestone tier: unchanged — E1–E3 complete, E4 *entered* not completed**
(CPUNET released — `clock_app: Network core released`, net ran 85,000 instr of
early `.data`/`.bss` init; app IPC endpoint open begun: `ipc_service_open_instance`
@4,668,358). **NOT reached:** `settings_subsys_init`, `ipc_service_send`,
`spi_read_id` (display), `bt_enable`, `bt_start`, first ADV_IND — same as iter-1.
App executed **4,708,483** instr (iter-1: 4,707,995; +488 = the now-completed
panic-log flush).

**Corrected first divergence — a kernel OOPS golden never takes** (present in
iter-1 too, at identical indices; masked there by the log double-fault):

| step | our instr | function |
|---|---|---|
| assertion tripped | **4,702,339** | `assert_post_action` → `z_arm_svc` |
| kernel oops | 4,702,351 | `_oops` → `z_do_kernel_oops` (4,702,353) |
| arch fatal | 4,702,356 | `z_arm_fatal_error` → `z_fatal_error` (4,707,306) |
| fatal logging (now completes) | 4,707,946 | `fatal_log_and_reset` → `log_panic` → `log_msg_process` (fixed) |
| platform abort / halt | 4,708,476 | `nrf_cc3xx_platform_abort` → cores halt |

**Golden comparison (the proof it is a divergence):** in the golden app trace
(1117 functions, reaches E5), the **entire oops/fatal chain is absent** —
`assert_post_action`, `_oops`, `z_do_kernel_oops`, `z_arm_fatal_error`, `panic`,
`fatal_log_and_reset` are all MISSING. Golden also **never enters the runtime
deferred-log packaging path** (`z_log_vprintk`, `z_impl_z_log_msg_runtime_vcreate`,
`cbvprintf_package` all MISSING in golden) — whereas our build enters all three
just before the assert. (Golden's lone `z_fatal_error`/`nrf_cc3xx_platform_abort`
hits at first_i 367/104 are early-boot enclosing-symbol misattributions, not real
calls.)

Immediately before the assert, our trace runs (relocated addrs, our-ELF nm):
`main → register_ipc_service_context → check_sw0_status → log_message →
z_log_vprintk → z_impl_z_log_msg_runtime_vcreate → cbvprintf_package → …`. During
packaging, `strlen`/`get_skip` read garbage — notably `strlen(0x29287325)`;
`0x29287325` little-endian is the ASCII bytes `25 73 28 29 = "%s()"`, i.e. the
packager is consuming **format-string bytes as a `%s` argument pointer** — a
format/vararg misalignment. The §5 rpmsg/IPC reads
(`0xC016CBE4`/`0xC016CBF0` via `ipc_service_open_instance` /
`serialization_register_endpoint`) recur on the same early-main path.

## 6. Classification of the new divergence

Ranked, with confidence. **Not** a recon-logic defect (the functions are
parity-proven) and **not** the data-section-boundary class fixed this iteration
(that pin is now correct).

1. **(highest-leverage) LOG configuration / mode mismatch — config class
   (→ Kconfig/overlay).** Golden's app never uses the runtime deferred-vprintk
   packaging path at all; ours does, and that is where it dies. Strongly suggests
   our `recon/application/app/prj.conf` enables a fuller/deferred `CONFIG_LOG_*`
   mode (or a higher default level / `LOG_PRINTK`) than the shipped image, so a
   debug `log_message` that golden compiles out or routes to a no-op is instead
   runtime-packaged — and the packaging is what trips. Also explains why our
   `check_sw0_status` debug branch runs ~35k instr into `main()` while golden only
   reaches `check_sw0_status` at steady state (12.3M).
2. **(contributing) Absolute rodata *format-string / constant* pins not
   relocated — same meta-class as this iteration's fix, different subset.** The
   format string (`rodata_a18cd`) and its arg (`rodata_a19af`) are absolute pins
   to *original* rodata; in the relocated image the packager reads mismatched
   bytes (the `"%s()"` evidence). Unlike the log-backend boundary, these are
   **interior rodata offsets, not section boundaries**, so they cannot be rebound
   to a linker symbol — the structural remedy is to have the reconstructed sources
   **emit their own string constants** (let the compiler place+relocate them)
   rather than pin to original addresses. This is the residual DATA-pin tail.
3. **(contributing) rpmsg/IPC endpoint unresolved-pointer cluster** — the §5
   pointers from `pointer_rebind.md`'s residual 24 app literals (incl. the 7
   unreconstructed IPC/rpmsg callbacks), still reading `0xC016CBE4`/`0xC016CBF0`
   on this same path.

## 7. Recommended next fix (drives iteration 3)

1. **Diff the app LOG Kconfig against the shipped image** (`CONFIG_LOG_MODE_*`,
   `CONFIG_LOG_DEFAULT_LEVEL`, `CONFIG_LOG_PRINTK`, and `g_log_level` init). This
   is the single highest-value lead: golden never runs runtime `cbvprintf_package`.
   Aligning the log mode likely removes the early `check_sw0_status` debug-log path
   (and the packaging assert) outright.
2. If the log statement is legitimately present, address the **absolute rodata
   format-string pins** structurally (emit strings from the reconstructed source).
3. **Sweep the §5 rpmsg/IPC endpoint pointer cluster** per `pointer_rebind.md`.
4. Also carry the latent **settings-list-end `0x88328` literal** (§2) into the
   source-level rodata-pin pass.

Acceptance target unchanged: reach E4 (`bt_start` / first ADV_IND / display init).

## Regenerate (iteration 2)

Same commands as above; the app ELF is rebuilt in place at
`/private/tmp/g1-ours-app`. The two rebound pins are the only source change
(`recon/symbols/g1_app_globals.ld`). Nothing committed.

---

# Iteration 3 — console char-out callback (NOT a logging-config divergence)

Applied a fix, rebuilt (0 undefined / 0 duplicate), re-booted via the unmodified
`g1-ours.resc` / `trace_ours.resc`, re-traced. **The kernel OOPS / runtime
deferred-log packaging path is gone.** The app now advances *past* the old
assert (instr 4,702,339) and executes the console-log path correctly; a **new,
later first divergence** appears — a **usage fault** on the `pt_nfc_eeprom_link`
path (instr **4,703,842**).

## 1. Verdict: config vs reconstruction

**It was a RECONSTRUCTION / WIRING defect, not a logging-configuration
divergence. Iteration 2's leading hypothesis (§6.1 "LOG mode mismatch") is
FALSIFIED, with proof.** No `prj.conf` change was made or needed.

The reconstructed log path never routes through Zephyr runtime packaging on its
own. Disassembly of *our* build:

- `log_message` / `DEBUG_PRINT` (@0x75e3c) → `vprintf` (@0x4291c) → `z_cbvprintf_impl`.
  It does **not** reference `z_log_vprintk` / `z_impl_z_log_msg_runtime_vcreate` /
  `cbvprintf_package`. (`recon/named/log_message.c`, `recon/symbolized/app/vprintf.c`.)
- The runtime-packaging path (`z_log_vprintk`→`runtime_vcreate`→`cbvprintf_package`)
  is only reachable from `printk` (@0x77992, via `CONFIG_LOG_PRINTK=y`) — **not**
  from `vprintf`.

So our build did not "enter the runtime path because of a LOG Kconfig". It
**executed garbage** that happened to wander through `vprintk`/`z_log_vprintk`.

### The real mechanism (confirmed by disasm + image bytes)

`recon/symbolized/app/vprintf.c` passed the pinned symbol `rodata_4b1b5`
(`PROVIDE(rodata_4b1b5 = 0x0004b1b5)` in `g1_app_globals.ld`) as the **per-char
output callback** to `z_cbvprintf_impl`. In the *shipped* image, `0x4b1b4` is a
tiny **char-out trampoline** (verified by reading original image bytes):

```
4b1b4:  ldr r3,[pc,#4]   ; = 0x200027c8   (firmware stdout-hook global)
4b1b6:  ldr r3,[r3,#0]   ; = installed worker (console_out @0x608ec)
4b1b8:  bx  r3
4b1bc:  .word 0x200027c8
```

i.e. `vprintf → z_cbvprintf_impl → trampoline → *(0x200027c8) = console_out`
(`'\n'→"\r\n"`, `uart_poll_out` on the chosen console UART). Golden confirms the
exact shape: app `log_message` x198 → `vprintf` x198 → `z_cbvprintf_impl` →
`lseek` x4168 (the trampoline, folded into the `lseek` symbol) → `uart_poll_out`
x28767. **Golden never runs runtime packaging from this path — it just prints to
UART.**

In *our relocated* build the literal `0x4b1b5` is **not relocated** (it is the
original absolute), and `0x4b1b4` now lands **inside an unrelated function
(`rtc_cb`)**. So `z_cbvprintf_impl` calls through garbage → the code there
stumbles into `vprintk`/`z_log_vprintk`/`z_impl_z_log_msg_runtime_vcreate` →
`cbvprintf_package(strlen 0x29287325="%s()")` → `assert_post_action` → `_oops`
→ `z_arm_fatal_error`. **The "%s()" and the whole runtime-packaging chain were a
red herring: symptoms of executing `rtc_cb` bytes, not a LOG config.**

Second, coupled defect: the trampoline (@0x4b1b4), its char-out worker
(`console_out` @0x608ec) and its installer (the UART-console `SYS_INIT` @0x608c4)
are **all folded inside `clock_control_nrf_on_blocking` (0x60788)** in the
catalog and were never split out / reconstructed. So even a correct trampoline
would read `0x200027c8` = **NULL** (its setter `set_g_misc_val_27c8` is
dead-code-eliminated; a whole-image scan finds only 2 references to `0x200027c8`
— the trampoline read and that DCE'd setter, whose single caller @0x608c4 is
unreconstructed).

## 2. The change (one file, relocatable, DT-correct)

`recon/symbolized/app/vprintf.c` — replaced the unrelocated absolute callback
`rodata_4b1b5` with a relocatable char-out bound to the chosen console UART,
reproducing the shipped image's observable output path (`console_out →
uart_poll_out`) without the runtime-swappable hook indirection:

```c
static int g1_vprintf_char_out(int c, void *ctx) {
    const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    if (c == '\n') uart_poll_out(dev, '\r');
    uart_poll_out(dev, (unsigned char)c);
    return c;
}
/* vprintf: z_cbvprintf_impl(&g1_vprintf_char_out, 0, fmt, ap, ...) */
```

The compiled `g1_vprintf_char_out` (@0x428f4) is byte-for-byte the same shape as
Zephyr's own `console_out` (dev→api→`poll_out`, `'\n'→"\r\n"`). Only the
**build/wiring TU** (`symbolized/app/vprintf.c`, the file actually in
`recon/generated/app_retained_sources.cmake`) was touched; the byte-parity
reconstruction in `recon/app/src/FUN_0004b1cc.c` and the pinned `rodata_4b1b5`
in `g1_app_globals.ld` are left as-is (documented, not deleted). **No `prj.conf`
/ Kconfig change.**

## 3. Rebuild status

`build_cohesive.sh app /private/tmp/g1-ours-app` → **exit 0, 0 undefined, 0
duplicate**. FLASH **626432 / 982528 B = 63.76%**. `nm`: `vprintf` @0x4291c now
loads callback `0x000428f5` = `g1_vprintf_char_out` (valid Thumb function ptr),
no absolute pin.

## 4. OOPS resolved (confirmed on the hardware-model)

Re-boot via the unmodified `g1-ours.resc`. The log path now runs cleanly:

```
check_sw0_status → log_message → vprintf → z_cbvprintf_impl
  → g1_vprintf_char_out → uarte_nrfx_poll_out (→ k_is_in_isr, is_tx_ready,
    pm_device_state_get)   [~2000 instr of real per-char console output]
```

No `assert_post_action`, no `_oops`, no `z_log_vprintk` / `runtime_vcreate` /
`cbvprintf_package`, no QSPI-XIP abort. The console UART output path is now
identical in behavior to golden (`… → uart_poll_out`).

## 5. New milestone tier + instruction counts

**Milestone tier: still E4 *entered*, not completed** — but qualitatively
further than iter-1/2:

- **Console/UART logging now works end-to-end** (golden-equivalent) — a real E4
  capability that was previously fatal.
- **Net core advanced 85k → ~248k instr** (released, running its RTC/timer ISR
  loop; alive, no fault).
- App reaches **new code never executed before**: `pt_nfc_eeprom_link_start` /
  `pt_nfc_eeprom_link_init` (@4,703,825/4,703,828).
- **Still NOT reached:** `ipc_service_send`, display `spi_read_id`, `bt_enable`,
  `bt_start`, first ADV_IND.

Honest note on instruction counts: the trace ran to the 0.15 s budget
(**14,999,144** app instr) but real forward progress is **~1,500 app
instructions past iter-2's assert** — after the usage fault (§6) the app spins in
the fatal handler `drop_item_locked` for ~10.3M instr (log-mpsc drop loop, i.e.
panic spin, **not** boot progress). Golden app total is 12,629,795 instr and
reaches E1–E5 with **no** `z_arm_usage_fault` / `_oops`.

## 6. New first divergence (precise) + classification

**Usage fault (Cortex-M) at instr 4,703,842.** Chain (relocated addrs, our-ELF nm):

```
main → register_ipc_service_context → check_sw0_status  (log path completes OK)
check_sw0_status tail-calls (ldmia sp!,{r3,r4,r5,lr}; b.w) →
  pt_nfc_eeprom_link_start (0x2be9c) → pt_nfc_eeprom_link_init (0x2bdb4)
    [runs only 8 instr, early-returns -1] → back to link_start @0x2bea4
  0x2beae: pop {r3,pc}   → z_arm_usage_fault (0x4e7b0)   ← FAULT
    → z_arm_fault → usage_fault.constprop.0 → z_arm_fatal_error → z_fatal_error
    → spins in drop_item_locked
```

- **Faulting instruction:** `pop {r3,pc}` at 0x2beae (return from
  `pt_nfc_eeprom_link_start`). The popped return PC triggers a usage fault —
  overwhelmingly **INVSTATE** (return address with the Thumb bit clear), the
  natural cause for a `pop {…,pc}` fault. *To confirm in iter-4: read the stacked
  return word at the fault.*
- **Expected (golden):** golden runs `pt_nfc_eeprom_link_start` (x2, 9 instr) and
  `pt_nfc_eeprom_link_init` (x2, **33 instr**) with **no fault**, and reaches E5.
- **Key data divergence:** our `pt_nfc_eeprom_link_init` runs only **8 instr** and
  early-returns `-1` because its config struct **`g_pt_nfc_link_cfg_static`
  @0x20002408** (an absolute RAM pin) is **all-zero / unpopulated** — its first
  word is 0, so the first `if (cfg->fn == NULL) return -1;` check trips. Golden's
  33-instr run means the struct's 4 function pointers are populated there.
- **Fault classification:** **reconstruction / wiring defect**, same meta-class as
  this iteration's fix (unrelocated pointer *or* an unreconstructed installer /
  ordering) — **not** a Kconfig/DT mismatch, **not** a recon-logic defect (the
  functions are parity-proven), **not** an emulator gap. Two candidate root causes
  (iter-4 to disambiguate): (a) the NFC-eeprom-link vtable installer /`SYS_INIT`
  that populates `g_pt_nfc_link_cfg_static` is unreconstructed or ordered *after*
  `link_start` (the exact "folded/DCE'd installer" pattern just fixed for the
  console hook), and/or (b) a corrupted / non-Thumb stacked return address in the
  `register_ipc_service_context → check_sw0_status → link_start` tail-call chain
  (note our `register_ipc_service_context` runs 1× here vs golden's 59× / broader
  interleaving — the early-main control flow may itself be arriving on a divergent
  path).

## 7. Recommended next fix (drives iteration 4)

1. **Confirm the fault mode:** at instr 4,703,842 read SP + the stacked return
   word popped by `0x2beae`; verify bit0 == 0 (INVSTATE) and identify the bad
   return target.
2. **Ground-truth `g_pt_nfc_link_cfg_static` (0x20002408):** find who writes its
   4 function pointers in the original image (BL/store scan), check whether that
   installer is reconstructed and registered, and whether it runs **before**
   `pt_nfc_eeprom_link_start` — same technique that found the missing console-hook
   installer this iteration.
3. **Check the early-`main()` control flow** vs golden around
   `register_ipc_service_context` / `check_sw0_status` (ours reaches this cluster
   ~4.70M in one pass; golden interleaves `register_ipc_service_context` 59× across
   5–12M) to ensure `link_start` is not being reached on a divergent path.

Acceptance target unchanged: reach E4 completion (`bt_start` / first ADV_IND /
display init) on our build.

## Regenerate (iteration 3)

Same commands as iterations 1–2 (build `app`, boot `g1-ours.resc` via
`/tmp/g1_ours/trace_ours.resc`, analyze with `analyze_ours.py` + `app_nm.txt`).
The only source change is `recon/symbolized/app/vprintf.c`. Nothing committed.

---

## Systematic sweep (code-pointer + section pins)

Targeted sweep of the **"absolute flash pointer used as a code pointer, not
relocated"** defect class (the iteration-3 `vprintf`/`rodata_4b1b5` archetype),
so the Renode boot stops hitting these one at a time.

### 0. The enumeration net had to be corrected first

A previous pass enumerated candidates as *"FLASH-range pin whose address falls
inside a reconstructed function's extent"* and found ~11, all interior. **That
net is wrong**, and the proof is the archetype itself: `rodata_4b1b5` (0x4b1b5,
the console char-out trampoline that iteration 3 fixed) is **not** inside any
`app_funcs.json.gz` extent — it sits in the *gap* between `FUN_0004b17c`
(ends 0x4b1b0) and `FUN_0004b1c0`. Ghidra simply never catalogued it. A net that
misses the one confirmed positive cannot be used to clear the class.

The correct discriminator is **discriminator #1 from the task: bit0 set**.
Re-enumerating `PROVIDE(<name> = 0x...)` in `recon/symbols/g1_app_globals.ld`:

| population | count | verdict |
|---|---:|---|
| numeric pins total | 3343 | — |
| FLASH-range (0xC200..0xA4074) | 1121 | — |
| RAM `0x2000xxxx` | 738 | left literal (kept per task) |
| in the **code** region 0xC358..0x879A6, **odd** (Thumb) | **83** | **the candidate set** |
| in the code region, **even** | 34 | data (see §3) |
| "inside a function extent" (the old net) | 11 | 3 of them are in the 83; the rest are data |

All 11 of the old net's candidates were re-checked and are accounted for below.

### 1. Per-candidate evidence and verdict (83 odd code-region pins)

Three discriminators were applied to every candidate:
**(a)** disassemble the **original image bytes** at `addr & ~1` (`tools/extract.py` +
capstone); **(b)** how the pin is **used** in `recon/symbolized/app` (callback /
thread entry / `blx` argument vs. numeric compare); **(c)** a new
**byte-prologue matcher**: read 16 original bytes at the pin and compare against
the first bytes of every function symbol in our linked ELF, to *name* the target.

Result: **80 of 83 are genuine unrelocated Thumb code pointers** (each decodes as
a real function prologue at the exact address, and each is used as a callback,
thread entry, `k_work`/`k_timer`/`z_add_timeout` handler, or `foreach` visitor).
This is a much larger surface than iteration 1–3 assumed, and it is a **separate
channel of the same defect that `pointer_rebind.md` fixed for the
`ADDR_*_THUMB` macros** — the `rodata_<odd-addr>` linker pins were never swept.

| verdict | n | meaning |
|---|---:|---|
| **DATA → left literal** | 3 | not a pointer at all |
| **code-pointer → REBOUND** | 9 | a symbol in our build was positively identified |
| **code-pointer → BLOCKED (SDK-static)** | 28 | target named with certainty, but it is `static`/local in its SDK library, so no honest `&sym` binding exists |
| **code-pointer → DEFERRED (unreconstructed)** | 43 | target is a Ghidra-uncatalogued, unreconstructed function; nothing to bind to |

**DATA (3) — left literal.** Positive evidence they are constants, not addresses:

| pin | evidence |
|---|---|
| `rodata_fc09` 0xfc09 | used as `bt_hci_cmd_send_sync(0xfc09, …)` — an **HCI opcode** (OGF 0x3f vendor, OCF 0x09). Bytes at 0xfc08 decode mid-instruction. |
| `rodata_ff41` 0xff41 | used as `if (0xff41 < param_2 - 0xa4)` — numeric magnitude compare. |
| `rodata_1274f` 0x1274f | used as `if (uVar9 - 0x2a30 <= 0x1274f)` — numeric magnitude compare. |

**REBOUND (9).** Each has a *positive* identification, not proximity:

| pin | → target | evidence that decided it |
|---|---|---|
| `rodata_2692d` | `master_display_thread` | `function_names_app.json` durable map gives entry **0x2692c** exactly; prologue `push {r3,r4,r5,r6,r7,lr}`; used as the `z_impl_k_thread_create` *entry* argument in `run_main_dispatch_thread` |
| `rodata_27cfd` | `slave_display_thread` | durable map entry **0x27cfc** exactly (Ghidra's `app_funcs` has an off-by-2 at 0x27cfe); same thread-entry use site |
| `rodata_32421` | `aging_mode_thread` | durable map entry **0x32420** exactly; `z_impl_k_thread_create` entry arg in `start_aging_mode_thread` |
| `rodata_75005` | `z_timer_expiration_handler` | **24 leading bytes byte-identical** to our build's `z_timer_expiration_handler`; use site is the `z_add_timeout` handler arg inside `z_impl_k_timer_start` — semantically the same function |
| `rodata_86661` | `z_thread_timeout` | 8-byte function, byte-identical modulo the `b.w` relocation (`movs r1,#1; subs r0,#0x18; b.w z_sched_wake_thread`), **and** the function immediately following it is byte-identical in both images (`z_unpend_all`); use site is `z_add_timeout(thread+0x18, …)` in `z_impl_k_thread_create` / `pend_locked` / `z_init_static_threads` |
| `rodata_85f8d` | `zcbor_uint32_decode` | **32/32 leading bytes identical** modulo `b.w` relocs; zcbor decoder fn-ptr in `img_mgmt_upload` |
| `rodata_85f93` | `zcbor_size_decode` | 32/32 identical; +6 byte offset preserved in both images |
| `rodata_85f97` | `zcbor_bstr_decode` | 32/32 identical; +10 byte offset preserved in both images |
| `rodata_86f35` | `__sread` | 10 leading bytes identical modulo the `bl` reloc, **plus** an independent hit in `recon/catalogs/app_toolchain_exact_matches.json`: newlib `lib_a-stdio.o .text.__sread`, normalized-code SHA match, `firmware_hits: ["0x00086f34"]`; use site is a `FILE` op fn-ptr in `newlib_stdio_init_stream` |

**Rejected matches (discipline check).** Two byte-prologue hits were *not* taken:
`rodata_46d8d` → `panel_on` (10 bytes agree, then codegen diverges; the durable
map places `panel_on` at **0x46dd8**, not 0x46d8c — a shared `*_init` prologue,
false positive) and `rodata_4b1b5` → `mutex_init` (only 8 bytes; 0x4b1b4 is
already known from iteration 3 to be the char-out trampoline, already fixed at
source level in `symbolized/app/vprintf.c`).

**BLOCKED — SDK-static targets (28).** The byte-prologue matcher named these with
16/16-byte agreement, so the *identification* is solid, but each target is `t`
(local) in its Zephyr/newlib/open-amp library and no external `&sym` can bind to
it (identical constraint to `pointer_rebind.md`'s "17 stock functions defined
static"): `clock_event_handler` (`nrfx_clock_init` handler), `work_queue_main`,
`work_timeout`, `slice_timeout`, `mbox_callback`, `mbox_callback_process`,
`virtio_notify_cb`, `rpmsg_virtio_hold_rx_buffer`, `l2cap_rtx_timeout`,
`l2cap_alloc_frag`, `l2cap_rx_process`, `prep_write_cb`, `found_attr`,
`match_uuid`, `gatt_write_rsp`, `gatt_find_type_encode`, `remove_peer_from_attr`,
`convert_to_id_on_match`, `ccc_save`, `sc_process`, `smp_ident_sent`,
`keys_add_id`, `adv_pause_enabled`, `clock_started_callback`, `out_func`,
`transition_complete`, `rtc_cb`, `find_flash_total_size`.
The semantic agreement between each matched name and its use site (e.g.
`work_queue_main` ← `k_work_queue_start`'s `k_thread_create` entry;
`clock_event_handler` ← `nrfx_clock_init`'s argument) is itself strong
confirmation that the whole 80-pin class is real.

**DEFERRED — unreconstructed targets (43).** The address decodes as a clean
function entry in the original image but that function is **not in
`app_funcs.json.gz`, not in the durable name map, and has no reconstruction**
anywhere in `recon/` — so there is no symbol to bind to. Rebinding these requires
*reconstructing* the target, not editing a pin. This group contains the current
boot blocker (§4).

### 2. Iterable-section sub-class — re-confirmed, nothing new

Re-swept `g1_app_globals.ld` for `_*_list_start/end`, `__device_*`, `__init_*`,
`_settings_handler_*`, `_bt_*_static_list_*`, `_net_buf_pool_list_*`, `_log_*`,
`_shell_*`, `_k_*_list_*`, `_static_thread_data_*`. **Exactly the two pins
iteration 2 already rebound exist** (`rodata_882a0` → `_log_backend_list_start`,
`__settings_handler_static_list_start` → `_log_backend_list_end`); every other
such section is iterated by stock SDK code using the linker's own symbols. No
change. Iteration 2's conclusion holds.

### 3. Even code-region pins and other flash pins — data, left alone

The 34 even pins inside the code region are page/size constants and rodata table
bases (0xf000, 0x10000, 0x28000, 0x30000, 0x40000, 0x50100 …) or land in the
trailing data of a **data-inflated** Ghidra function (AGENTS.md CRITICAL FINDING
#2) — e.g. `rodata_1f400` at +19620 inside `ble_process_put_req` (242 B of code +
25 KB of trailing table). None are code pointers; all left literal. The named
non-`rodata_*` flash pins are LC3 codec tables, font tables and `struct device`
instances — data, out of this class (the four `*_dev` pins are a separate
unrelocated-**data**-pointer residue, noted not fixed).

### 4. Rebuild status

`recon/application/build_cohesive.sh app /private/tmp/g1-sweep-app` → **exit 0,
0 undefined (`nm -u`), 0 duplicate global definitions.**
FLASH **626432 / 982528 B = 63.76%** — *bit-identical to iteration 3*; a pin
rebind emits no code.

The rebind was done in `recon/symbols/g1_app_globals.ld` only, using the
linker-script form (same mechanism as iteration 2's section rebind, with the
Thumb bit made explicit as `pointer_rebind.md` requires):

```ld
PROVIDE(rodata_2692d = master_display_thread | 1);
```

Verification in the linked ELF (`readelf` — note `nm` *masks* bit0 on `FUNC`
symbols, `readelf` does not):

```
readelf:  000220a5 FUNC GLOBAL ABS rodata_2692d      (= master_display_thread|1)
          0007f459 FUNC GLOBAL ABS rodata_86661      (= z_thread_timeout|1)
objdump:  25a78: .word 0x000220a5    <- run_main_dispatch_thread's k_thread_create entry
          25aa4: .word 0x0002328d    <- slave_display_thread|1
          2c3e8: .word 0x0002bf1d    <- aging_mode_thread|1
          46830/6d4d8/6d5e0/6f418/6fc70: .word 0x0007f459   <- z_thread_timeout|1 (5 z_add_timeout sites)
```
and the old absolutes `0x0002692d / 0x00027cfd / 0x00032421 / 0x00086661` no
longer appear as literals anywhere in `.text`.

4 of the 9 rebinds materialise in this build; the other 5
(`rodata_75005`, `rodata_85f8d/93/97`, `rodata_86f35`) are referenced only from
TUs that are **not in `app_retained_sources.cmake`** (`z_impl_k_timer_start.c`,
`img_mgmt_upload.c`, `newlib_stdio_init_stream.c` — the SDK provides those), so
`PROVIDE` correctly does not emit them. They are corrected for the day those TUs
are retained. No source file, no `prj.conf`, no `tools/` change.

### 5. Boot result: **no regression, and no advance** (honest)

Re-booted the unmodified `armemul/g1-ours.resc` (via an additive
`/tmp/g1_sweep/trace_sweep.resc` that only overrides `$app_elf`) and re-traced
both cores with the same 0.15 s / 10 µs-quantum / seeded-RNG environment.

| metric | iteration 3 | this sweep |
|---|---|---|
| app instructions executed | 14,999,144 (budget) | **14,999,144** |
| app unique functions | 465 | **465** |
| net instructions | 248,823 | **248,823** |
| net unique functions | 357 | **357** |
| first divergence (app instr) | 4,703,842 | **4,703,842** |

A name-by-name diff of the two app traces gives **0 differences in `first_i` for
all 462 shared functions** (the 3 name deltas are enclosing-symbol aliasing
between the two analyzers at identical addresses). Milestone tier is unchanged:
**E1–E3 complete, E4 entered not completed** (CPUNET released and running,
console UART logging working, `ipc_service_open_instance` reached; still not
reached: `ipc_service_send`, `spi_read_id`, `bt_enable`, `bt_start`, ADV_IND).

This is the expected outcome and it is worth stating plainly: none of the 9
rebound pointers is *invoked* before the fault. The display/aging threads are
spawned by `run_main_dispatch_thread`, which the boot never reaches, and no
thread timeout expires before the panic. The rebinds are **latent correctness
fixes** (each one was a live landmine — `z_thread_timeout` in particular is armed
from 5 sites starting at instr 613,974), not a boot advance.

### 6. New first divergence — precisely identified, and it is *this* class

The re-trace did produce a decisive result: it **corrects iteration 3's
diagnosis** of the first divergence, and pins it on a DEFERRED pin from §1.

Iteration 3 reported the fault as `pop {r3,pc}` in `pt_nfc_eeprom_link_start`,
blamed on `g_pt_nfc_link_cfg_static` being unpopulated, reached by a tail-call
from `check_sw0_status`. The instruction-level trace shows that is a *symptom*.
The actual chain (our relocated addresses):

```
4701815  main+0x27c
4701823  register_ipc_service_context+0x0     ; ctx[0x60]=global_ipc_service_send|1  (correctly relocated)
                                              ; ctx[0x64]=0x00025ae9                 (RAW, unrelocated)
4701839  main+0x298                           ; builds 4 IPC-service records at ctx+0x6e4/0x6f0/0x6fc/0x708
4701848  0x00025ae8   <-- blx *(ctx+0x778) == the unrelocated pin rodata_25ae9
                          in OUR image 0x25ae8 is arbitrary code at check_sw0_status+0x38
4701850  log_message -> vprintf -> ... -> uarte_nrfx_poll_out   (~2000 instr of real console output)
4703823  check_sw0_status+0x3e:  ldmia.w sp!,{r3,r4,r5,lr}      ; pops a frame that was never pushed
4703825  b.w pt_nfc_eeprom_link_start          ; entered with a corrupt lr
4703836  pt_nfc_eeprom_link_start+0x8
4703842  z_arm_usage_fault                     <-- FAULT (pop {r3,pc} with the corrupt return word)
         -> z_arm_fault -> usage_fault.constprop.0 -> z_arm_fatal_error -> spins in drop_item_locked
```

Ground truth for the call site (`objdump` on our ELF):

```
main:      15c0a: ldr.w r2,[r4,#0x778] ; 15c0e: blx r2         <- call_hook(context,0x778,0x6e4)
register_ipc_service_context:
           21a58: ldr r3,[pc,#52] ; 21a5a: orr.w r3,r3,#1 ; 21a5e: str r3,[r0,#0x60]   (relocated OK)
           21a60: ldr r3,[pc,#48] ; 21a62: str r3,[r0,#0x64]                            (NO orr — raw pin)
           21a94: .word 0x00025ae9      <- rodata_25ae9, the unrelocated absolute
```

**Classification: absolute flash pointer used as a code pointer, not relocated —
i.e. exactly the class of this sweep — sub-case "target unreconstructed".**
`rodata_25ae9` is the original-image entry 0x25ae8 of the **IPC-service
registrar**: `push {r0,r1,r4,lr}; …; ldr r1,[r3,#4]; cmp r1,#0x15; …; str.w r0,[r3,r4,lsl #2]` —
it appends a service record to a ≤22-entry table and logs on overflow. It lives
in the Ghidra gap 0x25AD2..0x25B78, immediately before its already-reconstructed
sibling `global_ipc_service_send` (0x25b78, correctly bound via
`ADDR_global_ipc_service_send_THUMB`). It has **no catalog entry and no
reconstruction**, so it cannot be rebound — it must be reconstructed.

It is a genuine divergence from golden: golden runs
`register_ipc_service_context` **59×** and `global_ipc_service_send` **24×** and
reaches E5, and only reaches `check_sw0_status` at steady state (instr
12,310,559); ours enters `check_sw0_status`'s *middle* at 4,701,848 on the first
pass. `pt_nfc_eeprom_link_start` is never legitimately called on our path at all
— golden calls it at 7,273,973 with `pt_nfc_eeprom_link_init` running its full
33 instructions. The iteration-3 observation that `g_pt_nfc_link_cfg_static`
(0x20002408) is all-zero is real but **incidental** (it is a separate, still-open
defect: a `.data` RAM pin whose initialiser was lost), not the cause of the fault.

### 7. Next fix (drives iteration 5)

1. **Reconstruct the IPC-service registrar at original 0x25AE8** (the target of
   `rodata_25ae9`) and rebind the pin to it. This is the single blocking defect;
   everything after it in `main()` (the four IPC-service registrations, then
   `spi_master_install_ops`, then the display/`bt_enable` bring-up) is gated on it.
2. **The same cluster, same gap:** `main()` also stores three *unrelocated*
   IPC-service handlers into those records — `rodata_162ed` (ctx+0x6ec),
   `rodata_16bf1` (ctx+0x6f8), `rodata_7c00d` (ctx+0x710) — all DEFERRED in §1,
   all unreconstructed, all in the same Ghidra gaps. Only the fourth
   (`ADDR_local_esbs_ipc_service_recv_THUMB`) is reconstructed. Reconstruct the
   three; they will be dispatched immediately after the registrar starts working.
3. **The 28 SDK-static BLOCKED pins** need a different remedy from a linker pin:
   either an SDK-side alias/export, or the iteration-3 pattern of replacing the
   pinned callback in the *wiring TU* with a compiler-emitted equivalent (as done
   for `g1_vprintf_char_out`). `clock_event_handler`, `work_queue_main`,
   `work_timeout`, `slice_timeout` and the three rpmsg/mbox ones are the
   boot-relevant ones.
4. Then re-check `g_pt_nfc_link_cfg_static` (0x20002408) as its own defect —
   a `.data` RAM pin whose original initialiser (4 function pointers) is not
   reproduced by our build.

Acceptance target unchanged: reach E4 completion (`bt_start` / first ADV_IND /
display init).

### Regenerate (this sweep)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-sweep-app
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_sweep/trace_sweep.resc' > /tmp/g1_sweep/run.out 2>&1
# trace_sweep.resc = $app_elf/$net_elf override + 'i @g1-ours.resc' + the iteration-1
# tracing macro (additive; g1-ours.resc itself untouched).
```

Only `recon/symbols/g1_app_globals.ld` was changed (9 `PROVIDE` rebinds +
their evidence comments). Nothing committed.

---

## Iteration 4 — reconstruct the IPC-service registrar (original 0x25AE8) and rebind its pin

The sweep's §7.1 blocker is **fixed**. The registrar was reconstructed from the
original image bytes, parity-proven, wired into the build and bound to the pin.
The boot **advances onto golden's own call sequence** (four IPC-service
registrations → `spi_master_install_ops` → `button_init`) and then hits a
**new, different first divergence**: a Zephyr `gpio_pin_configure`
"Unsupported pin" `__ASSERT` inside `button_init`, caused by an **unrelocated
absolute rodata DATA table** (`rodata_88340`, a 9-entry `gpio_dt_spec` array).
Milestone tier is unchanged (**E1–E3 complete, E4 entered, not completed**).

### 1. The function: `register_ipc_service_recv_callback` @ original 0x25AE8

**Extent derived from the image** (it is uncatalogued — Ghidra gap
0x25AD2..0x25B78). 0x25AD4..0x25AE7 is the *preceding* function's literal pool;
the function proper is:

| region | bytes | content |
|---|---|---|
| code | `0x25AE8..0x25B53` | **0x6C = 108 B**, `push {r0,r1,r4,lr}` … `pop {r4,pc}` |
| literal pool | `0x25B54..0x25B6B` | 6 words (0x20007a84, 0x2000230c, 0x20007554, 0x9f6a3, 0x9f512, 0x9f540) |
| (separate) | `0x25B6C..0x25B77` | a 12-B `ldr r0,[pc,#4]; b.w` stub — **not** part of this function |
| (separate) | `0x25B78` | `global_ipc_service_send` (already reconstructed, size 182) |

**The name is self-evidenced**, not guessed: the function passes its own name as
the `%s()` argument of its log lines — the literal 0x9f6a3 is the string
`"register_ipc_service_recv_callback"`, used with the two formats
`"%s(): ipc_service_register(%d,%s) %d,SUCCESS\n"` (0x9f512) and
`"%s(): ipc_service_register(%d,%s) %d,total must < %d\n"` (0x9f540).

**What it does.** `tbl = *g_ipc0_endpoint` (0x20007a84 — the context pointer that
`register_ipc_service_context` stores there); `n = tbl[1]`. If `n <= 21` it
appends: `tbl[n+2] = record; tbl[1] = n+1;` and returns 0 (logging at
`g_log_level > 2`). If `n > 21` it returns −1 and logs the overflow at
`g_log_level > 0` (max 22 entries). Both log sites pick `log_message`
(0x7dda4) or `debug_print` (0x19c70) on `g_log_use_alt_sink` (0x20007554) — the
identical sink-selection shape as its sibling `global_ipc_service_send`.

**Proof status — what was actually run:**

- `recon_kit.prove(0x25ae8, 0x6c, 'register_ipc_service_recv_callback', …, trials=300)`
  → **`pass: true`, `cfg_status: PASS`, `checked: 300`, `mismatches: null`**.
  Source auto-saved to `recon/app/src/register_ipc_service_recv_callback.c`
  (mirrored into `recon/verified/src/`).
- `tools/cfg_verify.py app register_ipc_service_recv_callback` →
  **`PASS cases=0 sel={}`**.
- **Catalog note (disclosed):** `recon_kit.info`/`cfg_verify` resolve a function's
  identity and size from the scratchpad catalogs, and this function was never
  catalogued. One record was therefore appended to
  `<scratchpad>/app_funcs.json` and `<scratchpad>/classified.json`
  (entry 0x25ae8, size 0x6c, class APPLICATION); originals backed up as
  `*.json.i4bak`. **No `tools/` logic was changed.**
- **Honest coverage caveat + what was done about it.** `cases=0` means
  cfg_verify found **no argument-derived selectors**: every branch in this
  function keys off *absolute globals* (`tbl[1]`, `g_log_level`,
  `g_log_use_alt_sink`), which the generic fixture leaves as PRNG garbage.
  Mutation probes confirmed the 300-trial fixture reaches only the
  success/no-log arm (mutating the store index, the count update or the return
  value FAILs; mutating the overflow bound, the log thresholds, the sinks or the
  log arguments still PASSes). A **directed fixture harness** was therefore run
  on top (`emu.compare` with `absolute_memory_overrides` seeding the table
  pointer, `count ∈ {0,1,20,21,22,23,100,−1}`, `g_log_level ∈ {−1,0,1,2,3,7}`,
  `g_log_use_alt_sink ∈ {0,1}` — 96 cases, `candidate_direct_target_map` +
  `call_stack_arity_by_target` enabled so call targets and stack varargs are
  compared): **96/96 PASS**, with the original observed taking all four arms
  (r0=0 no-log ×40, r0=0 +1 log call ×20, r0=−1 no-log ×12, r0=−1 +1 log call
  ×24). Under that harness **every** mutant above FAILs (bound, both log
  thresholds, both sink selections, both format strings, the name argument, the
  `%d` count argument, the trailing `22` stack argument) while the unmutated
  control PASSes. Driver: `<scratchpad>/directed.py`.

### 2. Pin rebound

| pin | was | now |
|---|---|---|
| `rodata_25ae9` (`g1_app_globals.ld:42`) | `0x00025ae9` (raw original address) | `register_ipc_service_recv_callback \| 1` |

Because a `PROVIDE` expression is **not** a `--gc-sections` root, the ld rebind
alone linked but left `rodata_25ae9 = 0x00000001` (target discarded — verified in
the first build attempt). The binding was therefore additionally expressed
through the `pointer_rebind.md` `__asm__`-alias mechanism so the reference is a
real `R_ARM_ABS32`:

```c
/* recon/symbols/g1_app_symbols.h */
extern const unsigned char __g1_fp_register_ipc_service_recv_callback[]
    __asm__("register_ipc_service_recv_callback");
#define ADDR_register_ipc_service_recv_callback_THUMB \
    (((unsigned long)&__g1_fp_register_ipc_service_recv_callback) | 1u)
```

and `recon/symbolized/app/register_ipc_service_context.c` now stores
`ADDR_register_ipc_service_recv_callback_THUMB` into `ctx[0x64]` instead of
`&rodata_25ae9` (the sibling slot `ctx[0x60]` already used this mechanism). The
`g1_app_globals.ld` rebind is kept as the documented binding for any other
consumer of `rodata_25ae9`.

Three absolute-rodata string pins used by the new function were added
(`rodata_9f512`, `rodata_9f540`, `rodata_9f6a3`) in `g1_app_globals.ld` +
`g1_app_symbols.h`, following the same convention every other reconstructed log
site uses (this is the still-open interior-rodata-pin class of iteration 2 §2;
harmless here because `g_log_level <= 1` on this boot path, so neither log fires
— confirmed in the trace, the registrar runs 17 instructions per call).

Build visibility: `recon/symbolized/app/register_ipc_service_recv_callback.c`
added to `recon/generated/app_retained_sources.cmake` next to
`global_ipc_service_send.c`.

### 3. Rebuild status

`recon/application/build_cohesive.sh app /private/tmp/g1-i4-app` → **exit 0,
`nm -u` = 0 undefined, 0 duplicate global definitions.**
FLASH **626576 / 982528 B = 63.77 %** (iteration 3 / sweep: 626432 B = 63.76 %;
+144 B = the new 0x94-byte function). Relocation-correctness in the linked ELF:

```
nm:      0002196c T register_ipc_service_recv_callback
         00021ae8 T register_ipc_service_context
objdump: 21af4: ldr r3,[pc,#52]; 21af6: orr.w r3,r3,#1; 21afa: str r3,[r0,#0x64]
         21b2c: .word 0x0002196d      <- register_ipc_service_recv_callback|1
```

(the old raw literal `0x00025ae9` no longer appears), and the compiled body is
shape-for-shape the original: `push {r0,r1,r4,lr}; ldr…; cmp r1,#21; bgt;
adds r4,r1,#2; str.w r0,[r3,r4,lsl #2]; str r1,[r3,#4]; …; pop {r4,pc}`.

### 4. Boot result — advance, with no regression

Re-booted the **unmodified** `armemul/g1-ours.resc` through an additive
`/tmp/g1_i4/trace_i4.resc` (only `$app_elf` overridden), same
0.15 s / 10 µs-quantum / seeded-RNG / serial-scheduling environment; both cores
traced; PCs resolved through our own ELF's `nm`.

**No regression — the whole earlier prefix is instruction-identical:**

| marker | iter 1–3 / sweep | iteration 4 |
|---|---:|---:|
| `region_init` | 80,111 | **80,111** |
| `z_impl_k_sem_init` | 80,492 | **80,492** |
| `nrfx_clock_init` | 81,126 | **81,126** |
| `nrf_cc3xx_platform_init` | 83,071 | **83,071** |
| `z_impl_k_thread_create` | 613,974 | **613,974** |
| `main` | 4,667,207 | **4,667,207** |
| `ipc_service_open_instance` (E4 entry) | 4,668,358 | **4,668,358** |

**New forward progress (all of it new code, and all of it on golden's path):**

| our instr | function | golden instr | note |
|---:|---|---:|---|
| 4,701,823 | `register_ipc_service_context` ×1 | 5,176,674 | now stores a **valid** ctx[0x64] |
| 4,701,849 / 890 / 910 / 930 | **`register_ipc_service_recv_callback` ×4** | (folded into a neighbour in golden's catalog) | the four IPC-service registrations; 17 instr each = success arm, returns 0 |
| 4,701,955 | **`spi_master_install_ops`** | 5,181,308 | never reached before |
| 4,701,966 | **`button_init`** | 5,181,325 | never reached before |
| 4,702,055 | **`gpio_pin_configure_17688`** | 5,181,325+ | never reached before |

Golden's ordering `register_ipc_service_context → spi_master_install_ops →
button_init → gpio_pin_configure` is now reproduced exactly. Unique app
functions 465 → **472**. Iteration 3's `check_sw0_status` /
`pt_nfc_eeprom_link_start` / `pt_nfc_eeprom_link_init` / `z_arm_usage_fault` /
`z_arm_fault` are **all gone** — that whole garbage-execution chain was the
symptom of the unrelocated pin and no longer exists.

**Honest note on the numbers.** The raw "first divergence" index moved *earlier*
(4,703,842 → **4,703,517**) and total executed app instructions fell
(14,999,144 → **4,709,377**). Neither is a regression:

- iteration 3 burned ~2,000 instructions executing garbage inside
  `check_sw0_status` (a full console-log flush golden never runs there) before
  faulting, so its index was inflated by work that was never legitimate;
- iteration 3's 14.999 M was the 0.15 s budget spent **spinning in the fatal
  handler** (`drop_item_locked`), not boot progress. This run's fatal path
  completes and issues `SYSRESETREQ` (`fatal_log_and_reset` →
  `nrf_cc3xx_platform_abort`, instr 4,709,370), after which both cores halt, so
  the run simply ends earlier.
- Net core consequently got less virtual time: **86,000** instr (sweep: 248,823).
  This is an artifact of the app resetting instead of spinning, not a net
  regression — the net core was released and executing normally in both runs.

**Milestone tier: unchanged — E1–E3 complete, E4 entered, not completed.**
Still NOT reached: `ipc_service_send`, `settings_subsys_init`, `spi_read_id`
(display), `bt_enable`, `bt_start`, first ADV_IND.

### 5. New first divergence (precise) + classification

**Kernel OOPS from a Zephyr `gpio_pin_configure` `__ASSERT`, at instr 4,703,517.**

```
4,701,966  button_init+0x0
4,702,055  gpio_pin_configure_17688+0x0      ; gpio_pin_configure_dt(&spec[0], flags)
           ... 31 instr, takes the "Unsupported pin" arm ...
4,702,086  printk  (assert banner)  -> z_log_vprintk -> z_impl_z_log_msg_runtime_vcreate
4,702,834  gpio_pin_configure_17688+0x58     ; second printk of the same assert
4,703,514  gpio_pin_configure_17688+0x5e
4,703,517  assert_post_action  -> z_arm_svc -> _oops -> z_do_kernel_oops
           -> z_arm_fatal_error -> z_fatal_error -> fatal_log_and_reset
           -> nrf_cc3xx_platform_abort -> SYSRESETREQ -> cores halt
```

The failing check is the second `__ASSERT` in `gpio_pin_configure`
(`ldr r3,[r5,#4]; ldr r3,[r3]; ldr r3,[r3]; lsl.w r5,#1,pin; tst r3,r5; bne`),
i.e. `(cfg->port_pin_mask & BIT(pin)) != 0` — **"Unsupported pin"**.

**Root cause (proved by reading both images).** `button_init` copies a 9-entry
`struct gpio_dt_spec` table out of the **absolute pin `rodata_88340`**
(`PROVIDE(rodata_88340 = 0x00088340)`) and feeds each entry to
`gpio_pin_configure_dt`. In the **original** image 0x88340 is exactly that table:

```
spec[0..8] port=0x00087b60 (= g_gpio0_dev) pin = 26,25,28,27,24,19,21,23,30  flags=0
```

In **our relocated** ELF the same address is occupied by a *different* verified
rodata table (`nm`: `00088340 R rodata_15f40`), so `button_init` reads:

```
spec[0] port=0x00087cf8 pin=12  flags=0x0023
spec[1] port=0x20007554 pin=62  flags=0x099c     <- a RAM global as a device*
spec[2] port=0x00099329 pin=69  flags=0x0993
spec[3] port=0x00087d10 pin=252 flags=0x0069
...
```

Pins 62/69/252/165 are outside any 32-bit port mask, and the `port` words are
not devices — hence the assert.

**Classification: absolute DATA pin not relocated — the *data-table* sibling of
the code-pointer class fixed in iterations 3–4.** Not a recon-logic defect
(`button_init` is parity-proven and its algorithm is right), not a Kconfig/DT
mismatch (our overlay's gpio0 is present and fine), not an emulator gap. Two
coupled pins are involved and **both** were already flagged and left unfixed by
the sweep (§3: "the four `*_dev` pins are a separate unrelocated-**data**-pointer
residue, noted not fixed") — they are now boot-critical:

| pin | pinned to (original) | correct symbol in our build |
|---|---|---|
| `rodata_88340` | 0x00088340 (gpio_dt_spec[9] table) | *no linker symbol exists* — table must be emitted from source |
| `g_gpio0_dev` | 0x00087b60 | `__device_dts_ord_12` @ **0x00080080** (gpio@842500) |
| `g_gpio1_dev` | 0x00087b48 | `__device_dts_ord_22` @ **0x00080068** (gpio@842800) |

Golden comparison (the proof it is a divergence): in the golden app trace
(1117 functions, E1–E5), `button_init` @5,181,316 and `gpio_pin_configure_17688`
@5,181,325 run with **no** `assert_post_action`, **no** `printk`, **no** `_oops`,
and boot continues to `spi_read_id` @7,273,380 and `bt_start` @7,641,560.

### 6. Status of the sweep's §7.2 cluster (the three sibling IPC handlers)

`rodata_162ed`, `rodata_16bf1`, `rodata_7c00d` are still unrelocated raw pins
stored by `main` into the four service records (`main.c:274/278/284`). They did
**not** block this boot and were therefore **not** reconstructed, per scope:
the registrar only *stores the record pointer* into the table
(`tbl[n+2] = record`) — it never calls the handler. All four registrations
returned 0 and the handlers are only dispatched on an actual IPC receive, which
the boot does not reach. They remain the correct follow-up once IPC traffic
starts (they are `DEFERRED`/unreconstructed targets in the same Ghidra gaps).

### 7. Recommended next fix (drives iteration 5)

1. **Rebind the two GPIO device pins** in `g1_app_globals.ld`:
   `PROVIDE(g_gpio0_dev = __device_dts_ord_12);`
   `PROVIDE(g_gpio1_dev = __device_dts_ord_22);`
   (verified addresses 0x80080 / 0x80068 in this build; ords come from
   `zephyr/include/generated/devicetree_generated.h`,
   gpio@842500 → 12, gpio@842800 → 22).
2. **`rodata_88340` cannot be rebound** — it is an *interior data table* whose
   own first words are device pointers. Emit it from the wiring TU
   (`recon/symbolized/app/button_init.c`) as a real
   `static const struct gpio_dt_spec g1_button_gpios[9]` built from
   `DEVICE_DT_GET(DT_NODELABEL(gpio0))` with the recovered pins
   `26,25,28,27,24,19,21,23,30` (flags 0) — the iteration-3
   `g1_vprintf_char_out` pattern. Keep the parity-proven
   `recon/app/src/button_init.c` untouched.
3. **Sweep the same class systematically**: enumerate every *even* flash pin in
   `g1_app_globals.ld` that a reconstructed source dereferences as a **struct /
   table / device pointer** (the sweep's §3 dismissed the 34 even code-region
   pins as "data, left alone" — correct as code pointers, but this iteration
   shows the data ones are equally fatal). `rodata_88340`, the four `*_dev`
   pins, and `g_pt_nfc_link_cfg_static` (0x20002408, still-unpopulated `.data`)
   are the known members.
4. Then re-run and expect the next stop to be further into `button_init` /
   `nfc_gpo_init` or at the display `spi_read_id` bring-up.

Acceptance target unchanged: reach E4 completion (`bt_start` / first ADV_IND /
display init).

### Regenerate (iteration 4)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i4-app
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i4/trace_i4.resc' > /tmp/g1_i4/run.out 2>&1
# trace_i4.resc = $app_elf/$net_elf override + 'i @g1-ours.resc' + the iteration-1
# tracing macro (additive; g1-ours.resc itself untouched).
# analyze: <scratchpad>/analyze.py <nm> <trace> <out.json>
```

Files changed: `recon/app/src/register_ipc_service_recv_callback.c` (new, proven)
+ its `recon/verified/src/` mirror, `recon/symbolized/app/register_ipc_service_recv_callback.c`
(new), `recon/symbolized/app/register_ipc_service_context.c` (one store),
`recon/symbols/g1_app_globals.ld` (1 rebind + 3 string pins),
`recon/symbols/g1_app_symbols.h` (1 alias + 1 macro + 3 externs),
`recon/generated/app_retained_sources.cmake` (1 entry).
Scratchpad catalogs gained one record each (backed up). No `tools/` change, no
`prj.conf`/Kconfig change, `armemul` additive only. Nothing committed.

---

## Iteration 5 — absolute DATA pins (devices + gpio_dt_spec tables)

Iteration 4's blocker is **fixed** and the boot advances a long way: the app core
now completes `button_init`, runs `settings_subsys_init`, reaches
`flash_settings_read`, and — for the **first time in this bring-up** — **never
faults at all**: no `assert_post_action`, no `_oops`, no `z_arm_fatal_error`, no
`SYSRESETREQ`. It ends the run **alive and idling** in a retry/sleep loop.
App unique functions **472 → 601**; app instructions **4,709,377 → 5,067,675**
(same 0.15 s budget). Milestone tier still **E1–E3 complete, E4 entered, not
completed** (no `spi_read_id`, `bt_enable`, `bt_start`, ADV_IND yet).

Final artifacts: build `/private/tmp/g1-i5d-app`, trace `/tmp/g1_i5e/`.

### 1. Device pins rebound (with evidence)

Identification method (per pin, not by proximity): read the **original** device
object out of `app_update.bin`, follow word0 to its **C name string**, and match
that exact string against the device object at `__device_dts_ord_<N>` in **our
linked ELF**. Ordinals were re-derived from *this build's*
`zephyr/include/generated/devicetree_generated.h` and confirmed by `nm`/`readelf`
(they are **not** the iteration-4 numbers taken on faith — 12 and 22 happened to
still be right; the rest are new).

| pin | original addr | name string (both images) | rebound to | our addr |
|---|---|---|---|---|
| `g_gpio0_dev` | 0x87b60 | `gpio@842500` | `__device_dts_ord_12` | 0x80084 |
| `g_gpio1_dev` | 0x87b48 | `gpio@842800` | `__device_dts_ord_22` | 0x8006c |
| `entropy_dev` | 0x87b90 | `crypto@50844000` | `__device_dts_ord_86` | 0x800b4 |
| `g_watchdog_device` | 0x87cc8 | `watchdog` (nPM1300) | `__device_dts_ord_148` | 0x801ec |
| `rodata_87bf0` | 0x87bf0 | `mx25r6435f@0` | `__device_dts_ord_160` | 0x80114 |
| `rodata_87cb0` | 0x87cb0 | `regulators` (nPM1300) | `__device_dts_ord_149` | 0x801d4 |
| `rodata_87d58` | 0x87d58 | `lsm6dso@6b` | `__device_dts_ord_155` | 0x8027c |
| `rodata_87d70` | 0x87d70 | `charger` (nPM1300) | `__device_dts_ord_146` | 0x80294 |

All eight resolve in the linked ELF (`readelf -sW`) and each target's name string
was re-read from our own ELF image to confirm the match. The original and our
`struct device` / `gpio_driver_config` layouts are identical (verified:
`config[0] = port_pin_mask` = 0xffffffff for gpio0, 0xffff for gpio1 in **both**
images), so the rebind is layout-safe.

`entropy_dev`, `g_watchdog_device`, `rodata_87cb0/87d58/87d70` are **latent** on
this boot (their consumers — `sys_rand32_get`, `init_watchdog`,
`lsm6dso_init_chip`, `fuel_gauge_*` — are not reached yet); they are corrected
and caused no regression. `g_gpio0/1_dev` and `rodata_87bf0` are live.

**One rebind REVERTED after measurement.** `rodata_87c08` = the `ipc0` device
(original name string `"ipc0"`, our `__device_dts_ord_29`) — the identification
is unambiguous and the pin is genuinely wrong, but with it applied the boot
**regresses**: the real OpenAMP/rpmsg instance gets opened, `main()` then blocks
waiting for the endpoint bind (`serialization_register_endpoint` slips
4,668,377 → 4,705,055), the app drops into `idle`/`arch_cpu_idle` forever and
**never reaches** `register_ipc_service_context`, `spi_master_install_ops`,
`button_init` or `settings_subsys_init` (**521** unique fns / **4,738,510**
instr, vs 557 / 5,061,646 with the pin left absolute). Per the no-regression
gate it is reverted, with the measurement and the re-apply condition recorded in
`g1_app_globals.ld`. The real blocker there is the **CPUNET rpmsg handshake**,
not the pin.

### 2. The `gpio_dt_spec` tables — re-emitted, not rebound

`rodata_88340` / `rodata_889d0` / `rodata_889e0` cannot be rebound to any linker
symbol: their *contents* embed absolute `struct device *` words. They are now
emitted by the build in a new wiring TU
**`recon/symbolized/app/g1_gpio_dt_specs.c`** (added to
`recon/generated/app_retained_sources.cmake`), transcribed from the shipped
image with `tools/extract.py`:

```
0x88340: 9 x { 0x87b60 (gpio0), pin, dt_flags 0 }
         pins = 26, 25, 28, 27, 24, 19, 21, 30, 23
0x889d0: { 0x87b48 (gpio1), pin  9, dt_flags 0x0011 }   /* ACTIVE_LOW|PULL_UP */
0x889e0: { 0x87b48 (gpio1), pin 10, dt_flags 0x0011 }
```

**Correction to iteration 4 §5:** the last two pins of the 9-entry table are
`30, 23`, not `23, 30`. Cross-checked two ways — the image bytes at
0x88370/0x88378, and `button_init`'s own interleaved
`gpio_pin_set_checked(gpio0, 0x1e=30, 1)` / `(gpio0, 0x17=23, 0)` after
`spec[7]` / `spec[8]`.

Layout is `{ const struct device *port; u8 pin; /*pad*/ u16 dt_flags; }`
(8 B/entry), matching Zephyr's `struct gpio_dt_spec` exactly; the tables are
built with `DEVICE_DT_GET(DT_NODELABEL(gpio0|gpio1))` so both the table address
and the embedded device pointers relocate. Verified in the linked ELF: all nine
entries have `port = 0x80084` whose name reads back as `"gpio@842500"`.
`g1_app_globals.ld` binds the recovered pin names to these definitions, which is
what fixes the *other* consumer (`nfc_field_event_signal_sem` uses
`rodata_889d0`) with no source edit; `readelf` shows
`rodata_889d0 = 0x80a48 = g1_gpio1_pin9_spec`. The canonical
`recon/app/src/button_init.c` is untouched.

The build TU had to be separate: including `<zephyr/drivers/gpio.h>` inside
`button_init.c` collides with its recovered `gpio_pin_configure` /
`z_device_is_ready` externs.

### 3. Two NON-pin defects found on the way — same "lost information at a call" family

Fixing the pins alone would **not** have advanced the boot. Two reconstruction
defects sit directly on the `button_init` path; both were proved by
disassembling the **original** bytes and comparing with **our** codegen, and both
were fixed in the build/wiring TUs only (canonical `recon/app/src` untouched).

**(a) One pointer level too many** — `gpio_pin_configure_17688.c` (0x17688) and
`gpio_pin_configure.c` (0x17858). Both wrote
`enabled = **(volatile uint32_t ***)(dev + 4)` (and the same for
`output = ...(dev + 16)`), so `*enabled` was a **third** load. The original does
two:

```
orig 0x176a0: ldrd r7,r6,[r0,#4]   ; r7 = dev->config
orig 0x17706: ldr  r3,[r7]         ; r3 = cfg->port_pin_mask
orig 0x1770a: tst  r4,r3           ;  == Zephyr __ASSERT(cfg->port_pin_mask & BIT(pin))
ours 0x16194: ldr  r3,[r3,#0]      ; mask
ours 0x1619a: ldr  r3,[r3,#0]      ; <-- EXTRA: dereferences 0xffffffff
```

With the *wrong* device this was invisible; with the *correct* one it would have
dereferenced the port-pin mask value. Same for `data->invert`. The sibling
recon of `gpio_pin_set_checked` / `gpio_pin_get_checked` /
`gpio_pin_get_raw_checked` / `gpio_pin_configure_dt` uses the correct depth —
which is itself the cross-check that the two above are wrong.

**(b) Arguments dropped at an indirect/extern call.** Ghidra's
`(*UNRECOVERED_JUMPTABLE)()` / `(*api)()` idiom compiles to a call with
*whatever* is in r0–r2. In the ORIGINAL codegen those registers happened to hold
the right values; in ours they do not:

| site | original passes | ours passed |
|---|---|---|
| `gpio_pin_configure_17688` tail call `api->pin_configure` | r0=dev, r1=pin, r2=combined flags | r0=**spec**, r1=flags, r2=? |
| `gpio_pin_set_checked` tail call `api->port_{set,clear}_bits_raw` | r0=port, r1=**BIT(pin)** | r0=port, r1=**pin** |
| `z_tick_sleep` → `unready_thread` (`extern void unready_thread(void)`) | r0=`_current` (`ldr r0,[r7,#8]` @0x74786) | r0=**&sched_spinlock** |

All three now pass their arguments explicitly. `add_thread_to_wait_queue.c`
carried the same `unready_thread()` no-arg form and was fixed the same way (it
is currently gc'd out of the image).

The `z_tick_sleep` one was the *measured* blocker after the pin fix: calling
`unready_thread(&sched_spinlock)` left the sleeping thread in the ready cache
(`update_cache(0)`), `z_swap` returned to it immediately, and the following
`__ASSERT(!_THREAD_SUSPENDED)` (sched.c:1458) tripped a kernel OOPS.

### 4. Bounded sweep of the class (evidence per pin, deferrals stated)

`g1_app_globals.ld` has **3336** numeric pins, **648** of them even and in the
FLASH range — far too many to blanket-rebind, and a blanket rebind would be
wrong anyway (most are scalars or strings). The sweep was bounded two ways:
**(i)** the pin must be referenced by a function that the emulator **actually
executed**, and **(ii)** the original bytes at the pin must **start with a
pointer** (flash 0xC200..0xFAB8D or RAM 0x2000xxxx) rather than ASCII or a
scalar. That leaves **18** candidates (66 pins pass (i) alone; 48 of those are
string constants). Re-run against the *new* (iteration-5) executed set, which is
how `rodata_87bf0` was found — it was invisible in the iteration-4 trace because
`flash_settings_read` was never reached.

**Fixed (12):** the 8 device pins of §1 (one later reverted) + the 3
`gpio_dt_spec` tables of §2 + `rodata_87c08` (reverted).

**Deferred, with reasons:**

| pin(s) | what the bytes are | why deferred |
|---|---|---|
| `rodata_88058`, `88070`, `88128`, `88188`, `881a8`, `881b0`, `881b8`, `881d8`, `881e0`, `88258` | arrays of `{const char *name; u32 level}` = Zephyr `struct log_source_const_data` (`log_const_area`); names decode to `"bt_gatt"`, `"cbprintf_package"`, `"fatal_error"`, `"flash_nrf"`, `"fs_nvs"`, `"ipc_service"`, `"log"`, `"LSM6DSO"` | passed as the *source* argument of `z_log_msg_runtime_create` / `log_msg_create_3arg`, only dereferenced when a backend formats the message. Fixing them needs per-module `LOG_MODULE_REGISTER` emission + a name→section-entry map, not a pin rebind. No observed boot impact — the log path runs and flushes to UART this iteration. |
| `rodata_87fc8` | `_static_thread_data` iterable-section bound | `z_init_static_threads` uses it as **both** start and end (`piVar2 = piVar6 = 0x87fc8`), so the iteration is empty and the value is never dereferenced. **Correct as-is**; a rebind would be a behaviour change, not a fix. |
| `rodata_88058` / `88070` (second role) | `_bt_gatt_service_static` list bounds in `bt_gatt_service_init` / `bt_gatt_foreach_attr_type` | same iterable-section sub-class; BT is not reached, and the correct remedy is the linker's own `_bt_gatt_service_static_list_{start,end}`, which needs the BT service tables to exist first. |
| `rodata_10000`, `30000`, `40000`, `40002`, `40202` | 0x10000 = `GPIO_INPUT`, 0x30000 = `GPIO_INPUT\|GPIO_OUTPUT`, others are size/page constants | **scalars, not addresses** — used as the `flags`/size argument. Correctly literal. |
| ~48 `rodata_99xxx/9axxx/9fxxx/…` | printf/log format and name strings (`"%s()"`, `"button_..."`, assert texts) | interior rodata offsets, the still-open class from iteration 2 §2. Not struct/table pointers; the structural remedy is source-level string emission. |
| the other 630 even FLASH pins | not referenced by any executed function | outside the bounded sweep; re-run the sweep against each new trace (that is how `rodata_87bf0` surfaced). |

### 5. Rebuild status

`recon/application/build_cohesive.sh app /private/tmp/g1-i5d-app` → **exit 0,
`nm -u` = 0 undefined, 0 duplicate global definitions.**
FLASH **626680 / 982528 B = 63.78 %** (iteration 4: 626576 B = 63.77 %; +104 B =
the emitted gpio_dt_spec tables + the explicit call arguments). RAM 75573 B =
16.77 %. No `--allow-multiple-definition`, no weak/numeric root, no `prj.conf` /
Kconfig / devicetree change, no `tools/` change.

### 6. Boot result — no regression, large advance

Re-booted the **unmodified** `armemul/g1-ours.resc` through an additive
`/tmp/g1_i5e/trace_i5e.resc` (only `$app_elf` / trace paths overridden), same
0.15 s / 10 µs-quantum / seeded-RNG / serial-scheduling environment.

**(a) No regression — the whole iteration-4 prefix is instruction-identical:**

| marker | iteration 4 | iteration 5 |
|---|---:|---:|
| `region_init` | 80,111 | **80,111** |
| `nrf_cc3xx_platform_init` | 83,071 | **83,071** |
| `z_impl_k_thread_create` | 613,974 | **613,974** |
| `main` | 4,667,207 | **4,667,207** |
| `ipc_service_open_instance` | 4,668,358 | **4,668,358** |
| `register_ipc_service_context` | 4,701,823 | **4,701,823** |
| `register_ipc_service_recv_callback` ×4 | 4,701,849 | **4,701,849** |
| `spi_master_install_ops` | 4,701,955 | **4,701,955** |
| `button_init` | 4,701,966 | **4,701,966** |

**(b) New forward progress — all of it on golden's own path:**

| our instr | function | golden instr | note |
|---:|---|---:|---|
| 4,703,554 | `gpio_pin_set_checked` | 5,182,831 | never reached before |
| 4,705,405 | `gpio_pin_configure` | 5,184,663 | never reached before |
| 4,706,414 | `gpio_pin_get_checked` | 5,194,087 | never reached before |
| 4,706,571 | `gpio_pin_get_raw_checked` | — | `button_init` now runs to completion |
| 4,706,727 | `ext_flash_api_init` | — | |
| **4,706,769** | **`settings_subsys_init`** | 5,244,168 | listed "NOT reached" in iterations 1–4 |
| 4,974,017 | `flash_settings_read` | 5,503,072 | |
| 4,979,326 | `z_tick_sleep` (`k_sleep`) | 5,568,434 | |
| 5,058,012 | `idle` / `arch_cpu_idle` | — | the idle thread runs for the first time |
| 5,058,113 | `nrfx_ipc_irq_handler` → `mbox_dispatcher` → `mbox_callback` | — | **the CPUNET → CPUAPP IPC interrupt is received and dispatched** |
| 5,058,760 | `z_timer_expiration_handler` | — | timer/timeout subsystem live |
| 5,061,160 | `z_thread_timeout` → `z_sched_wake_thread` | — | the sweep's `rodata_86661` rebind fires for real |

Golden's function ordering `register_ipc_service_context → spi_master_install_ops
→ button_init → gpio_pin_* → settings_subsys_init → flash_settings_read →
k_sleep/z_tick_sleep` is reproduced exactly.

| metric | iter 4 | **iter 5** |
|---|---:|---:|
| app instructions (0.15 s) | 4,709,377 | **5,067,675** |
| app unique functions | 472 | **601** |
| net instructions | 86,000 | **250,075** |
| net unique functions | — | **371** |
| app faults (`assert_post_action`/`_oops`/fatal) | yes | **none** |
| ends by | `SYSRESETREQ`, both cores halted | **alive, idling** |

`grep -iE "abort|fault|halted|SYSRESETREQ"` on the Renode log is **empty** for
the app core — the first fault-free run of this bring-up.

### 7. New first divergence (precise) + classification

**Not a fault — a liveness stall.** At **4,974,017** `main → …
init_analytics_settings → load_sys_setting → flash_settings_read` runs

```c
if (!z_device_is_ready(<mx25r6435f@0>)) { log_message(...); result = -1; }
...
if (retry == 10) return result;
k_sleep(0x0ccd /* 3277 ms */); ++retry;
```

`z_device_is_ready` returns **false**, so it enters a **10 × 3.277 s** retry
loop — 32.7 s of virtual time. Confirmed by extending the budget to 0.6 s: the
app gains only ~17.6 k instructions per 0.2 s (pure tick/idle) and the PC stays
at `arch_cpu_idle`. Golden enters `flash_settings_read` **once** and returns 0.

**Root cause, proved from both images (and it is NOT a pin).** The
`rodata_87bf0` rebind of §1 is applied and verified
(`rodata_87bf0 = 0x80114 = __device_dts_ord_160`, name `"mx25r6435f@0"`), and the
trace is byte-identical with and without it — because the *real* device also
reports not-ready. `z_device_is_ready` checks `state->initialized &&
state->init_res == 0`; `qspi_nor_init` runs at 617,144, gets through
`nrfx_qspi_init` / `exit_dpd` / `qspi_rdsr`, and returns an error. Comparing the
`qspi_nor_config` object in both images:

```
ORIGINAL (app_update.bin @0x8b66c) +0x2c: 00 00 00 02   size = 0x02000000 = 32 MiB
                                   +0x30: c2 25 39      jedec-id  (MX25U25635F)
OURS     (zephyr.elf  @0x89fd8)    +0x2c: 00 00 80 00   size = 0x00800000 =  8 MiB
                                   +0x30: c2 28 17      jedec-id  (MX25R6435F)
```

`recon/board/g1_board.overlay:113-119` declares `mx25r6435f@0` with
`jedec-id = [c2 28 17]`. The shipped firmware expects **`c2 25 39`, 32 MiB** —
which is exactly what Renode's `models/Macronix_MX25U.cs` reports
(`manufacturerId = 0xC2, memoryType = 0x25, memoryDensity = 0x39`, capacity
0x2000000). So the driver's RDID check fails, `qspi_nor_init` returns `-ENODEV`,
and every external-flash consumer (settings, analytics, quick-note) degrades to
retry loops.

**Classification: recovered-devicetree (board-evidence) error** — a *third*
class, distinct from the code-pointer pins (iterations 3–4) and the data pins
(this iteration). Not a recon-logic defect, not an emulator gap (the Renode model
matches the shipped image), not a linker/relocation problem.

### 8. Recommended next fix (drives iteration 6)

1. **Correct the external-NOR node in `recon/board/g1_board.overlay`**: the part
   is a **MX25U25635F** — `jedec-id = [c2 25 39]`, `size = <0x10000000>` (bits,
   32 MiB) — not an MX25R6435F. Evidence is the shipped `qspi_nor_config` bytes
   above; the Renode model already agrees. This should let `qspi_nor_init`
   succeed, `flash_settings_read` return 0 on the first try, and `main()` proceed
   past the settings/analytics load toward `spi_read_id` (golden 7,273,380) and
   `bt_start` (golden 7,641,560). *(Deliberately not done here: it is a
   devicetree/config change, outside this iteration's scope.)*
2. **Then re-apply `PROVIDE(rodata_87c08 = __device_dts_ord_29)`** together with
   work on the **CPUNET rpmsg/IPC bind**. The pin is right; today it just moves
   the stall earlier. The app already receives the net core's IPC interrupt
   (`nrfx_ipc_irq_handler → mbox_dispatcher → mbox_callback` @5,058,113), so the
   remaining gap is the rpmsg endpoint handshake, not the mailbox.
3. **Sweep for more dropped-argument call sites** (§3b). Both instances found
   were `Ghidra (*UNRECOVERED_JUMPTABLE)()` / `extern f(void)` forms that only
   worked by register accident in the original codegen. A grep for
   `UNRECOVERED_JUMPTABLE` / zero-argument externs in `recon/symbolized/app`,
   cross-checked against the original disassembly's live registers at each `bl`,
   would clear the class before it costs another iteration. **These pass parity
   today**, so `tools/parity` cannot see them — worth a note in AGENTS.md.
4. Re-run the §4 bounded sweep against the *new* trace each iteration: each
   advance exposes device pins that were previously unreachable
   (`rodata_87bf0` was invisible until this run).

Acceptance target unchanged: reach E4 completion (`bt_start` / first ADV_IND /
display init).

### Regenerate (iteration 5)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i5d-app
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i5e/trace_i5e.resc' > /tmp/g1_i5e/run.out 2>&1
# trace_i5e.resc = $app_elf/$net_elf override + 'i @g1-ours.resc' + the iteration-1
# tracing macro (additive; g1-ours.resc itself untouched).
# analyze: <scratchpad>/analyze.py <app_nm.txt> <trace_app.log> <out.json>
```

Files changed: `recon/symbols/g1_app_globals.ld` (8 device-pin rebinds + 1
documented revert + 3 table bindings), `recon/symbolized/app/g1_gpio_dt_specs.c`
(new), `recon/symbolized/app/button_init.c`,
`recon/symbolized/app/gpio_pin_configure_17688.c`,
`recon/symbolized/app/gpio_pin_configure.c`,
`recon/symbolized/app/gpio_pin_set_checked.c`,
`recon/symbolized/app/z_tick_sleep.c`,
`recon/symbolized/app/add_thread_to_wait_queue.c`,
`recon/generated/app_retained_sources.cmake` (1 entry).
No `recon/app/src` change, no `tools/` change, no `prj.conf`/Kconfig/devicetree
change, `armemul` additive only. Nothing committed.

## Iteration 6 — external-NOR devicetree + the first RAM-pin collision + the CPUNET rpmsg backend

Three independent defects were found and fixed; one change was measured to
regress and was reverted. Net result on the **app core**: the settings store on
external QSPI NOR now really mounts and reads, `main()` runs the whole
settings/analytics load and reaches `runtime_info_sync` →
`global_ipc_service_send`, **fault-free**, **612** unique functions (iteration 5:
601). Net result on the **net core**: the OpenAMP/rpmsg backend comes up for the
first time (`open` → `ipc_static_vrings_init` → `ipc_rpmsg_init` →
`rpmsg_init_vdev`), and — when the app-side pin is also applied — completes
`rpmsg_create_ept` → `rpmsg_send_ns_message` → `mbox_nrf_send` → `ipc_service_send`,
which the app receives and decodes.

Milestone tier is still **E1–E3 complete, E4 entered, NOT completed**. No
`spi_read_id` (golden 7,273,380), no `bt_enable`/`bt_start` (golden 7,641,560),
no ADV_IND. **E4 did not complete.**

Final artifacts: app build `/private/tmp/g1-i6f-app`, net build
`/private/tmp/g1-i6d-net`, trace `/tmp/g1_i6final/`.

### 1. Task 1 — the external QSPI NOR node, corrected field by field

Reference layout: NCS 2.5.1 `struct qspi_nor_config`
(`zephyr/drivers/flash/nrf_qspi_nor.c:47`) = `nrfx_qspi_config_t nrfx_cfg;
uint32_t size; uint8_t id[3]; const struct pinctrl_dev_config *pcfg;`. The
build uses **short enums** (arm-eabi default), which is what puts `size` at
+0x2c and `id` at +0x30 — confirmed by the shipped object itself and by
`qspi_nor_init`'s own `ldrb r3,[r6,#29]` / `ldrb r8,[r6,#28]` reading writeoc /
readoc at +0x1d / +0x1c.

Shipped object: `app_update.bin` VA **0x8b66c** (file offset 0x7f66c), reached
from the `struct device` at 0x87bf0 (`name -> 0xf5d6b = "mx25r6435f@0"`,
`config = 0x0008b66c`). Ours: `qspi_nor_dev_config` @0x89fd8.

| off | field | shipped | ours (iter 5) | verdict / evidence |
|---|---|---|---|---|
| +0x00 | `xip_offset` | 0 | 0 | same |
| +0x04..0x1b | `pins` (6 × u32) | all 0 | all 0 | same (both skip GPIO/PSEL cfg) |
| +0x1c | `prot_if.readoc` | `04` | `04` | same — `NRF_QSPI_READOC_READ4IO` ⇒ `readoc = "read4io"` **kept** |
| +0x1d | `prot_if.writeoc` | `03` | `03` | same — `NRF_QSPI_WRITEOC_PP4IO` ⇒ `writeoc = "pp4io"` **kept** |
| +0x1e | `prot_if.addrmode` | `00` | `00` | same — 24-bit ⇒ `address-size-32` absent. **Kept even though the part is 32 MiB** (the shipped firmware really does use 24-bit + bank addressing) |
| +0x1f | `prot_if.dpmconfig` | `00` | `00` | same (this NCS never sets it) |
| +0x20 | `phy_if.sck_delay` | `00` | `00` | same — `sck-delay` default 0 **kept** |
| +0x21 | `phy_if.dpmen` | `00` | `00` | same |
| +0x22 | `phy_if.spi_mode` | `00` | `00` | same — MODE0 ⇒ no `cpol`/`cpha` **kept** |
| +0x23 | `phy_if.sck_freq` | **`00`** | **`05`** | **CHANGED → `sck-frequency = <96000000>`** |
| +0x24 | `timeout` | 0 | 0 | same |
| +0x28 | `irq_priority` | `00` | `00` | same |
| +0x29 | `skip_gpio_cfg` | `01` | `01` | same |
| +0x2a | `skip_psel_cfg` | `01` | `01` | same |
| +0x2c | `size` (bytes) | **`0x02000000`** | **`0x00800000`** | **CHANGED → `size = <268435456>`** (bits; 32 MiB) |
| +0x30 | `id[3]` | **`c2 25 39`** | **`c2 28 17`** | **CHANGED → `jedec-id = [c2 25 39]`** |
| +0x34 | `pcfg` | 0x0008b6a4 | 0x00089fd8-relative | relocated pointer; expected to differ |

**After the fix the object byte-matches the shipped one over 0x00..0x33** (only
`pcfg`, a relocated pointer, differs). Verified by re-reading both images.

**`sck-frequency` evidence (the field iteration 5 did not notice).**
`sck_freq = 0 = NRF_QSPI_FREQ_DIV1` alone is ambiguous — the driver's nRF53
ladder produces it for both the "≥ 96 MHz" and the "≥ 48 MHz" branches. The
tie-break is `BASE_CLOCK_DIV`, which the same function writes to
`HFCLK192MCTRL`. In the shipped `qspi_nor_init` (0x60c00, the DEVICE_DT_INST
init entry — the `struct init_entry` at VA 0x87a74 is `{0x00060c01, 0x00087bf0}`,
with `qspi_nrfx_configure` inlined):

```
60c22:  mov.w r4, #0x50005000     ; NRF_CLOCK (secure)
60c26:  movs  r3, #0
60c2e:  str.w r3, [r4, #0x5b8]    ; HFCLK192MCTRL = 0 = NRF_CLOCK_HFCLK_DIV_1
60c34:  bl    0x66994             ; nrfx_qspi_init
60c38:  movs  r3, #2
60c3a:  str.w r3, [r4, #0x5b8]    ; restore NRF_CLOCK_HFCLK_DIV_4 (=2)
```

`HFCLK192MCTRL` is at offset 0x5B8 (`nrf5340_application.h:1513`) and the
restore value 2 = `NRF_CLOCK_HFCLK_DIV_4` confirms the decode. Only the
`INST_0_SCK_FREQUENCY >= NRF_QSPI_BASE_CLOCK_FREQ` (96 MHz) branch yields the
pair (`BASE_CLOCK_DIV = DIV_1`, `INST_0_SCK_CFG = FREQ_DIV1`): the ≥48 MHz
branch would write `DIV_2` (=1) and the ≥32 MHz branch would give
`sck_freq = 3`. Any value ≥ 96000000 reproduces the bytes; **96000000** is the
canonical choice. Our previous 8 MHz gave `DIV_ROUND_UP(48e6, 8e6) - 1 = 5`.

**Properties that are NOT expressible in the config bytes — checked in code
instead, all already correct and left unchanged:**

* `has-dpd` — `dpmconfig`/`dpmen` are 0 in **both** images because this NCS
  version never sets them from `has-dpd`; the property is compile-time only.
  The shipped `qspi_nor_init` really calls `exit_dpd` at 0x8397e (which emits
  cinstr **0xAB**), so `has-dpd` is present. ✔
* `t-exit-dpd = <35000>` — `exit_dpd` @0x8397e does `movs r0,#35; bl 0x86384`
  (`k_busy_wait(35 µs)`); the driver computes `DIV_ROUND_UP(t_exit_dpd, 1000)`,
  so 35000 ns is right. ✔
* `t-enter-dpd = <10000>` — `enter_dpd` (inlined in `qspi_nor_pm_action`
  @0x60b48) emits cinstr **0xB9** then `movs r0,#10; bl 0x86384`. ✔
* `quad-enable-requirements` — the shipped code does `sr_num = 1` and
  `eor.w r2,r2,#0x40` (= BIT(6)) ⇒ **S1B6**, the binding default. ✔

**Node name kept, label corrected.** The node NAME must stay `mx25r6435f@0`:
that literal string is the Zephyr device name in the shipped image (device
object 0x87bf0 → name pointer 0xf5d6b → `"mx25r6435f@0"`) and every recovered
consumer resolves it. Only the misleading DT **label** was renamed
`mx25r64 → extflash` (2 references, both in the overlay), with a comment
recording the part's real identity (MX25U256 family).

Independent corroboration for 32 MiB: Renode's `models/Macronix_MX25U.cs`
(`C2/25/39`, capacity 0x2000000) and `armemul/docs/g1-qspi-layout.md`, the
region map of a ~31 MiB dump taken off the actual glasses.

### 2. Effect of the DT fix — and the fault it unmasked

With the node corrected, `qspi_nor_init` succeeds, `z_device_is_ready` returns
true, and `flash_settings_read` returns on the **first** try instead of looping
10 × 3.277 s. The boot immediately advanced into a large body of new code — and
**faulted**, for a reason that had nothing to do with the devicetree.

**First run after the DT fix** (build `/private/tmp/g1-i6-app`, trace `/tmp/g1_i6/`):
`z_arm_usage_fault` @5,009,759 → `z_arm_fatal_error` → `z_fatal_error` →
`fatal_log_and_reset` → **SYSRESETREQ** @t≈0.055 s.

Root cause, proved with two Renode probes:

* A write-watchpoint on 0x20007550 caught exactly two writers:
  `WROTE_PC_SLOT pc=0x0004e0bc val=0x00077a8e` (`arch_new_thread+0x18`, correct)
  and `WROTE_PC_SLOT pc=0x00017aea val=0x00000001` (**`debug_print+0x4a`**).
* A hook on `z_arm_pendsv`'s exception return (0x4e078) caught the consequence:
  `BADSWITCH th=0x20003420 psp=0x20007538 stackedpc=0x00000001`.

`debug_print` @0x17aa0 ends with `ldr r3,[pc,#20]` → literal `0x20007550`,
`str r2,[r3]` — the recovered global `g_ring_log_pending`, pinned at its
ORIGINAL absolute address. In OUR build 0x20007550 is inside
`logging_stack` (0x20006d58 + 2048 = 0x20007558) — specifically inside the log
thread's *initial exception frame* at PSP 0x20007538, at the stacked-PC slot.
The next switch to the log thread resumed at PC = 1, slid the whole
0x0000..0xC200 MCUboot window (24,832 halfword-zero instructions = exactly
0xC200 bytes), hit `_vector_table`, and usage-faulted.

**Classification: a FOURTH class — absolute RAM-pin collision.** Distinct from
the code-pointer pins (iterations 3–4), the flash data pins (iteration 5) and
the recovered-devicetree error (§1). Not a recon-logic defect (the pin is a
faithful transcription), not an emulator gap.

**Fix (bounded, group 1 only).** New wiring TU
`recon/symbolized/app/g1_app_ram_relocs.c` gives real linker-allocated storage
to the five pins that span 0x20007514..0x20007558, i.e. the whole overlap with
`logging_stack`: `g_bonded_count` (u32), `g_ancs_conn` (u32),
`g_debug_msg_pipe` (`struct k_msgq`; 52 B in the original — the gap to the next
pin — and `debug_log_queue_init` does `k_msgq_alloc_init(&it, 200, 0x14)`),
`g_ring_log_pending` (u32), `g_log_use_alt_sink` (u32).
`g1_app_globals.ld` rebinds the five pin names to those definitions; the
canonical `recon/app/src` bodies take `&name`, so no source change was needed.

Side effect worth recording: `g_log_use_alt_sink` now reads its own
zero-initialised storage instead of log-stack garbage, so the `DEBUG_PRINT`
alternative sink is (correctly) not selected and `debug_print` / `enqueue_debug`
/ `vsnprintf_impl` are no longer executed on this boot. That is a **fidelity
improvement**, not a loss: in the original those globals are zero-initialised too.

### 3. How big is this class? (measured, not estimated)

A sweep (`ramsweep.py`, scratchpad) cross-referenced every `PROVIDE(x = 0x2000….)`
in `g1_app_globals.ld` against every sized RAM symbol in our linked ELF, and
attributed each pin to the functions whose literal pools reference it:

* **738** RAM pins total.
* **561** of them land INSIDE a sized object of our build.
* **66** of those are referenced by a function that this boot actually executed.

**A structural "reserve the original's RAM" fix is NOT available**: the pins
span **0x20000000 … 0x2007fc70**, i.e. essentially the entire 512 KiB SRAM, so
Zephyr cannot be relocated out of the way. The class has to be retired pin by
pin (or by reproducing the original RAM layout outright, which is the
byte-match endgame). Notable still-colliding groups, all currently latent
because the object they sit in is unused so far:

| pins | our object they land in |
|---|---|
| `g_ipc_send_fail_cnt`, `g_serialization_ipc_ept`, `g_serialization_ipc_ready`, `g_ipc0_endpoint`, `g_ext_flash_mutex`, `g_ext_flash_dev` | `smp_work_queue_stack` (0x20007558, 2048 B) |
| `g_curr_tick_lo/hi`, `device_info`, `g_button_irq_cb*`, `g_ble_conn_ctx_ptr`, `g_ambient_light_sensor_ready` | `mbox_stack` (0x20006958, 1024 B) |
| `g_boot_uptime_s`, `log_backend_count`, `log_buffered_cnt`, `g_current_thread_ptr`, `g_sched_ready_runq`, `g_errno`, … | `z_main_stack` (0x20008d48, 16384 B) |
| `g_debug_msg_scratch_buf` (200 B memcpy target), `g_change_work_mode_busy`, `g_runtime_mode_flag`, … | `kheap__system_heap` (0x2000d148, 16384 B) |
| `g_log_level`, `g_t_init`, `g_serialization_ipc_ept_ctx` | `fdtable` (0x20002218, 640 B) |

Each iteration should re-run this sweep against the new trace and fix the group
that the new code path actually touches — the same bounded discipline as
iteration 5 §4.

### 4. Task 2 — the CPUNET rpmsg bind

**Net-side defect A — the `ipc0` device pin was unrelocated on the net core too.**
Captured the net UART for the first time
(`sysbus.uart_net CreateFileBackend`); it printed

```
*** Booting nRF Connect SDK v2.5.1 ***
[00:00:00.000,579] <err> ipc_service: Invalid backend configuration
```

That string is `ipc_service.c`'s `!backend` path, i.e. `instance->api == NULL`.
Traced to `FUN_0102ac0c`, which passes the literal **0x0103bfac** to both
`ipc_service_open_instance` and `ipc_service_register_endpoint`. In the shipped
`netcore_image.bin` that VA is a `struct device` whose word0 (0x0103cf12) is
the C string **`"ipc0"`** and whose api is 0x0103c8a8. In our net build the same
address is plain text (`nm`: `0103bf82 t ept_cb`). Our net DT has
`DT_N_S_ipc_S_ipc0_ORD = 22`; `__device_dts_ord_22` @0x0103d500 reads back name
`"ipc0"`, api 0x0103dd08.

A linker `PROVIDE` could **not** fix this one — unlike the app side, the net
sources embed the address as a *numeric literal*, so `rodata_103bfac` was never
referenced and the PROVIDE was dropped. The fix therefore uses the files' own
established `G1_COHESIVE_BUILD` mechanism (already present in both TUs for
`g1_ipc0_endpoint_config` / `g1_hci_endpoint_config`): a guarded macro
`G1_IPC0_DEVICE` / `C_0102b07c_DEV` resolving to
`DEVICE_DT_GET(DT_NODELABEL(ipc0))` in the cohesive build and to the original
literal otherwise, applied in `recon/net/src/FUN_0102ac0c.c` and
`recon/net/src/FUN_0102afbc.c`. Parity builds are unaffected. Verified in
codegen: the literal pool word became `0x0103d500`.
`recon/symbols/g1_net_globals.ld` also carries the documented
`PROVIDE(rodata_103bfac = __device_dts_ord_22)` for any symbolic consumer.

**Net-side defect B — an argument dropped at an indirect call (iteration 5 §3b
class), PROVEN.** With defect A fixed the `-EIO` disappeared but the net core
went from 250,075 to **10,375,000** instructions, spinning in
`optimal_num_desc()` inside the static-vrings `open()`. A Renode hook at
`open+0xa` gave the answer directly:

```
NET_OPEN_A instance=0x01030ee5 cfg=0x05468123 lr=0x0102ea7f
```

`instance` was **`open` itself** (`0x01030ee4|1`), so `conf = *(u32*)(inst+4)`
was garbage, `conf->shm_size` read 0, and `available = 0 - 4 = 0xFFFFFFFC` made
the `while (available > shm_size(n, buf)) n++;` loop effectively unbounded.
`lr` points into `FUN_0102ac0c` right after its `bl FUN_0102d558`, so the
culprit is `FUN_0102d558` — the recovered `ipc_service_open_instance`:

```c
r3 = **(volatile int32_t **)(param_1 + 8);      /* backend->open_instance */
if (r3 != 0) { fnptr_t f = (fnptr_t)r3; return f(); }   /* <-- no argument */
```

The ORIGINAL (netcore_image.bin, analysis VA 0x0102d558) tail-calls with r0
never touched since entry:

```
102d57a: ldr r3,[r0,#8]              ; backend = instance->api
102d598: ldr r3,[r3,#0]              ; backend->open_instance
102d59a: cbz r3, 0102d5a4
102d59c: add sp,#28 / ldr.w lr,[sp],#4
102d5a2: bx  r3                      ; r0 STILL = instance
```

Fixed in `recon/symbolized/net/FUN_0102d558.c` (the TU the net build actually
compiles, per `recon/generated/net_retained_sources.cmake:771`) and mirrored in
`recon/net/src/FUN_0102d558.c`: `typedef int32_t (*fnptr_t)(int32_t)` and
`return f(param_1);`. Our codegen is now `ldr r0,[r3,#0]; … bx r0` with r0
preserved — structurally identical to the original's tail call.
`tools/parity` cannot see this defect (callees are modelled as order-keyed
oracles that ignore arguments), which is exactly the iteration 5 §3(b) note.

**What the net core does now.** With both net fixes and (temporarily) the app
pin applied — build `/private/tmp/g1-i6d-net`, trace `/tmp/g1_i6k/` — the net
core reproduces golden's own ordering for the first time:

| net function | ours | golden |
|---|---:|---:|
| `open` (backend) | 198,636 | (inlined/absent) |
| `ipc_static_vrings_init` | 199,800 | 111,106 |
| `metal_device_open` | 200,215 | — |
| `ipc_rpmsg_init` | 205,100 | 139,129 |
| `rpmsg_init_vdev` | 205,123 | — |
| `ipc_service_register_endpoint` | 206,931 | 140,407 |
| `rpmsg_create_ept` | 207,166 | 140,642 |
| `rpmsg_send_ns_message` | 207,561 | 141,037 |
| `ipc_virtio_notify` → `mbox_nrf_send` | 208,365 / 208,379 | — |
| `ipc_service_send` | 212,706 | — |

The net UART's `<err> ipc_service` line is gone, and the app **receives** the
announcement: `nrfx_ipc_irq_handler` → `mbox_callback` → `k_work_submit_to_queue`
→ `work_queue_main` → `mbox_callback_process` → `virtqueue_notification` →
`rpmsg_virtio_rx_callback` → `virtqueue_get_buffer` → `rpmsg_virtio_ns_callback`
→ `ns_bind_cb`. The vring transport works in **both** directions.

**But the bind still does not complete, and the app pin was REVERTED again.**
`bound_cb` is never reached. A hook on the app's `register_ept` shows why:

```
APP_REGEPT  cfg=0x00089748  nameptr=0x0004bc05  name=<binary garbage>
APP_NSBIND  name='ipc0'
```

The net announces `"ipc0"`, but the app's own `struct ipc_ept_cfg` is at the
**unrelocated** absolute rodata address 0x00089748, so `cfg->name` reads
0x0004bc05 — a code address inside `open()` — instead of a string.
`get_ept_slot_with_name()` therefore never matches and `bound_cb()` never fires,
so `serialization_init`'s `k_sem_take` blocks forever and `main()` never reaches
`register_ipc_service_context` / `button_init` / `settings_subsys_init`
(**4,720,087** instr / **525** unique fns, vs **5,042,715** / **612** with the
pin left absolute). Per the no-regression gate `rodata_87c08` is pinned back to
`0x00087c08`, with the re-apply condition recorded in `g1_app_globals.ld`.

The three **net-side** changes are kept: they are proven correct, and with the
app pin reverted the app trace is **byte-identical** to the run without them
(same 5,042,715 instructions, identical first-instruction map).

### 5. Rebuild status

| build | result |
|---|---|
| `build_cohesive.sh app /private/tmp/g1-i6f-app` | exit 0, `nm -u` = **0** undefined, **0** duplicate globals. FLASH **626680 / 982528 B = 63.78 %** (unchanged vs iteration 5), RAM **75645 B = 16.79 %** (+72 B = the five relocated RAM globals) |
| `build_cohesive.sh net /private/tmp/g1-i6d-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF` | exit 0, **0** undefined, **0** duplicate. FLASH **227961 B = 98.50 %**, RAM **54076 B = 82.51 %** (identical to the previous net build; the net image layout did not move) |

No `--allow-multiple-definition`, no weak/numeric root, no Kconfig/`prj.conf`
change, no `tools/` change. `armemul` used additively only (an extra `.resc`
under `/tmp`; `g1-ours.resc` and the models untouched).

### 6. Boot result — before/after, both cores

Same environment as iteration 5 (0.15 s, 10 µs global quantum, seeded CC3xx
RNG, serial core scheduling, unmodified `g1-ours.resc`).

| metric | iteration 5 | **iteration 6** |
|---|---:|---:|
| app instructions (0.15 s) | 5,067,675 | **5,042,715** |
| app unique functions | 601 | **612** |
| app faults (`assert_post_action`/`_oops`/fatal/SYSRESETREQ) | none | **none** |
| app ends | alive, idling in a 10 × 3.277 s retry loop | **alive, idling; settings loaded, blocked on main's IPC reply semaphore** |
| net instructions | 250,075 | **10,375,000** |
| net unique functions | 371 | **332** |

**No regression on the app.** The whole iteration-5 prefix is reproduced and
extended; `button_init` (4,701,826), `gpio_pin_*`, `ext_flash_api_init`
(4,706,587) and `settings_subsys_init` (4,706,676) are all still reached, and
`flash_settings_read` (4,973,924) now **returns 0 on the first call**.
The app instruction count is slightly *lower* than iteration 5 (5,042,715 vs
5,067,675) purely because the 32.7 s retry/sleep loop is gone — the 25 k
"missing" instructions were tick/idle spin. Unique functions went **up**, 601 →
612: 20 genuinely new ones, 9 lost, and all 9 lost ones
(`z_tick_sleep`, `wait_for_event`, `get_uptime_ms`, `dlist_unlink_node`,
`sched_switch_handle_timeout`, `sched_thread_should_preempt`,
`g1_vprintf_char_out`, `z_thread_timeout`, `z_sched_wake_thread`) are the retry
loop's own machinery.

**New app forward progress — and it follows golden's order exactly:**

| function | ours | golden | note |
|---|---:|---:|---|
| `z_impl_flash_get_page_count` / `qspi_nor_pages_layout` | 4,706,627 | — | flash-map layout now queryable |
| `settings_register` | 4,973,065 | — | |
| `init_analytics_settings` | 4,973,376 | 5,502,525 | |
| `load_sys_setting` | 4,973,379 | 5,502,528 | |
| `flash_settings_read` | 4,973,924 | 5,503,072 | **returns 0 first try** |
| `ext_flash_read` | 4,973,958 | 5,503,106 | never reached before |
| `qspi_nor_read` → `nrfx_qspi_read` | 4,974,036 / 4,974,713 | — / 5,503,849 | **real QSPI transfer** |
| `qspi_xfer` → `nrfx_qspi_irq_handler` → `qspi_handler` | 4,974,715 … 4,974,846 | — | DMA completion IRQ serviced |
| `load_usr_setting` | 4,975,864 | 5,510,520 | |
| `set_test_mode` | 4,977,934 | 5,518,204 | |
| `is_battery_critical` | 4,977,980 | — | |
| `load_burial_point` | 4,977,997 | 5,520,837 | |
| `sys_rand32_get` → `entropy_cc3xx_rng_get_entropy` | 4,981,143 / 4,981,174 | 5,524,043 | CC312 entropy consumed by app code |
| `reset_countdown_timer_default` | 4,981,973 | — | |
| `runtime_info_sync` | 4,981,993 | 5,533,805 | |
| `global_ipc_service_send` | 4,982,013 | 5,533,821 | |

Golden's chain
`settings_subsys_init → init_analytics_settings → load_sys_setting →
flash_settings_read → ext_flash_read → nrfx_qspi_read → load_usr_setting →
set_test_mode → load_burial_point → sys_rand32_get → runtime_info_sync →
global_ipc_service_send` is reproduced **function-for-function, in order**.

**Net core, honest accounting.** 19 genuinely new functions — the entire
OpenAMP/libmetal/rpmsg backend (`open`, `ipc_static_vrings_init`, `metal_init`,
`metal_device_open`, `virtqueue_allocate`, `ipc_rpmsg_init`, `rpmsg_init_vdev`,
`ipc_virtio_get_status`, …) — none of which had ever executed. 58 functions that
iteration 5 reached are **not** reached now, and they are all downstream of a
wait that is *correct*: the net core is `ROLE_REMOTE` and, with the app-side pin
reverted, the app never sets `VIRTIO_CONFIG_STATUS_DRIVER_OK` in
`sram0_shared`, so `rpmsg_init_vdev_with_config` busy-polls
`ipc_virtio_get_status` (624,949 iterations = the 10.4 M instruction count).
Deferred that way: the net log thread and its UART output, `idle`,
`z_impl_k_sleep`, `z_impl_k_timer_start`, and four recovered net functions
(`FUN_0102acb4`, `FUN_0102ab50`, `FUN_0102a620`, `FUN_0102abac`). This is the
remote behaving as designed; it resolves the moment the app opens its side
(§7 step 1). It was kept rather than reverted because reverting restores a state
where the net's `ipc_service` silently fails with `-EIO`.

### 7. New first divergence + classification + next fix

**Divergence (app):** at **4,982,013** `main → runtime_info_sync →
global_ipc_service_send` sends the runtime-info message and `main` then does
`k_sem_take(&ctx[8], K_FOREVER)` (`mutex_lock_syscall_handler(context + 8, …, -1, -1)`
in `recon/symbolized/app/main.c`). The semaphore is only given by the IPC reply
path, which cannot run because the app's rpmsg endpoint is not bound. The app
drops to `idle`/`arch_cpu_idle` (5,039,635) and stays there, still servicing
`nrfx_ipc_irq_handler` → `mbox_dispatcher` → `mbox_callback` (5,039,736).

**Classification: unrelocated absolute rodata pin (iteration-5 data-pin class),
`struct ipc_ept_cfg` at 0x00089748.** Not a fault, not an emulator gap — the
transport is proven working in both directions.

**Next fixes, in order:**

1. **Emit a relocated `ipc_ept_cfg` for 0x00089748.** Its contents embed a
   `const char *name` and callback pointers, so — exactly like the
   `gpio_dt_spec` tables of iteration 5 §2 — it must be *emitted* by the build
   (new wiring TU + `PROVIDE(rodata_89748 = …)`), not merely rebound. Transcribe
   the shipped bytes with `tools/extract.py`; the name must come out `"ipc0"` to
   match what the net core announces. **Then re-apply
   `PROVIDE(rodata_87c08 = __device_dts_ord_29)`** — the pin itself is right and
   everything downstream of it is now proven ready. Expected result: `bound_cb`
   on both sides, `ipc_service_send` on the app, `main` unblocks, and the boot
   should run on toward `spi_read_id` (golden 7,273,380) and `bt_start`
   (golden 7,641,560), i.e. **E4 completion**.
2. **Re-run the §3 RAM-pin sweep against the new trace** and fix the group the
   newly-reached code touches. The `smp_work_queue_stack` group
   (`g_serialization_ipc_ept`, `g_serialization_ipc_ready`, `g_ipc0_endpoint`,
   `g_ext_flash_dev`, `g_ext_flash_mutex`, `g_ipc_send_fail_cnt`) is the most
   likely next casualty, because step 1 puts exactly those objects into use.
3. **Sweep the dropped-argument class on the net core** the same way iteration 5
   §8.3 proposed for the app. `FUN_0102d558` was found only because it happened
   to be on the critical path; every recovered `(*fn)()` / zero-argument
   `extern` in `recon/{net,symbolized/net}` should be cross-checked against the
   original's live registers at the call. `tools/parity` is blind to this class.
4. Long term: the RAM-pin class (561 colliding pins) cannot be retired by
   relocation — the original occupies the whole SRAM. It goes away only as the
   RAM layout itself is reproduced.

### Regenerate (iteration 6)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i6f-app
recon/application/build_cohesive.sh net /private/tmp/g1-i6d-net -- \
  -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i6final/trace.resc' > /tmp/g1_i6final/run.out 2>&1
# trace.resc = $app_elf/$net_elf override + 'i @g1-ours.resc' + the tracing macro
# + `sysbus.uart_net CreateFileBackend` (additive; g1-ours.resc untouched).
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
# RAM-pin sweep: <scratchpad>/ramsweep.py
```

Files changed:
`recon/board/g1_board.overlay` (QSPI NOR node: jedec-id, size, sck-frequency,
label + per-field evidence comments),
`recon/symbolized/app/g1_app_ram_relocs.c` (new),
`recon/generated/app_retained_sources.cmake` (1 entry),
`recon/symbols/g1_app_globals.ld` (5 RAM-pin rebinds + the `rodata_87c08`
re-apply-then-revert record),
`recon/symbols/g1_net_globals.ld` (`rodata_103bfac` rebind + evidence),
`recon/net/src/FUN_0102ac0c.c`, `recon/net/src/FUN_0102afbc.c` (guarded
`G1_COHESIVE_BUILD` ipc0-device macro; parity path unchanged),
`recon/symbolized/net/FUN_0102d558.c` + `recon/net/src/FUN_0102d558.c`
(dropped-argument defect fix, proven against the original bytes).
No `recon/app/src` change, no `tools/` change, no Kconfig/`prj.conf` change,
`armemul` additive only. Nothing committed.

---

## Iteration 7 — the app's `ipc_ept_cfg` (Step A) + library-displacement Batch 0 (Step B)

**Headline.** The rpmsg endpoint **binds**. `bound_cb` fires on both cores, the
app's `main()` unblocks, and for the first time the app **sends and receives**
over IPC: `runtime_info_sync → global_ipc_service_send → ipc_service_send →`
(net replies) `→ ept_cb → ipc0_ept_recv`. App unique functions **612 → 681**;
the CPUNET core stops busy-polling (10,375,000 → 255,064 instructions) and
gains **91** unique functions.

Milestone tier: **E1–E3 complete, E4 advanced but NOT completed.** The app-side
E4 marker `ipc_service_send` is reached (5,034,609); `spi_read_id`,
`bt_enable`/`bt_start` and ADV_IND are still not.

Final artifacts: app `/private/tmp/g1-i7e-app`, net `/private/tmp/g1-i7c-net`,
trace `/tmp/g1_i7e/`. (Step-A-only app build: `/private/tmp/g1-i7b-app`, trace
`/tmp/g1_i7d/`.)

| metric | iteration 6 | **iteration 7 (Step A)** | **iteration 7 (Step A+B, final)** |
|---|---:|---:|---:|
| app instructions (0.15 s budget) | 5,042,715 | 5,044,404 | **5,045,044** |
| app unique functions | 612 | 672 | **681** |
| net instructions | 10,375,000 | 255,064 | **255,064** |
| net unique functions | 332 | 423 | **423** |
| app FLASH | 626,680 B (63.78 %) | 627,368 B (63.85 %) | **628,380 B (63.96 %)** |
| app RAM | 75,645 B (16.79 %) | 75,757 B (16.81 %) | **75,757 B (16.81 %)** |
| net FLASH / RAM | 227,961 B / 54,076 B | 228,009 B / 54,140 B | **228,009 B / 54,140 B** |

All builds: `nm -u` = **0** undefined, **0** duplicate globals. No
`--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig/`prj.conf` change; `armemul` used additively only
(an extra `.resc` under `/tmp`; `g1-ours.resc` and the models untouched).

---

### Step A — the app's `ipc_ept_cfg`, and why iteration 6's diagnosis was wrong

#### A.1 Correction: there is no `ipc_ept_cfg` at 0x00089748

Iteration 6 §7 concluded that the app's `struct ipc_ept_cfg` sits at the
unrelocated pin **0x00089748**. That is **wrong**, and it was checked this
iteration before acting on it. The bytes at VA 0x89748 in `app_update.bin`
(file offset 0x7d748, VA→offset delta 0xC000, the same delta that reproduces
iteration 6's own QSPI-config table at 0x8b66c) are

```
89748: 89 7a 09 3b  3b 80 14 3b  17 04 28 3b  81 e5 3a 3b   ...
```

i.e. a run of small IEEE-754 floats — part of the **LC3 SNS analysis tables**
(`recon/symbolized/app/lc3_sns_analyze.c`). No `rodata_89748` pin exists in
`g1_app_globals.ld` and no recovered source references that address. 0x89748
was simply the stale value our codegen happened to leave in **r2** at the call.

#### A.2 The real defect: a dropped argument in `serialization_register_endpoint`

`serialization_init` (0x25c54) calls

```c
serialization_register_endpoint(&rodata_87c08,             /* instance */
                                &g_serialization_ipc_ept,  /* ept      */
                                &g_serialization_ipc_ept_ctx); /* cfg  */
```

which is Zephyr's `ipc_service_register_endpoint(instance, ept, cfg)`.
The ORIGINAL tail call (`app_update.bin`, VA 0x4cbec) keeps **r2 untouched
since entry**:

```
4cc34: str.w r0, [r1], #4        ; ept->instance = instance; r1 = &ept->token
4cc38: ldr   r3, [r4, #12]       ; backend->register_endpoint
4cc3a: add   sp, #28
4cc3c: ldmia.w sp!, {r4, r5, lr}
4cc40: bx    r3                  ; r0=instance  r1=&ept->token  r2=cfg
```

Ghidra's decompilation carries the marker
`/* WARNING: Could not recover jumptable at 0x0004cc40. Too many branches */
/* WARNING: Treating indirect jump as call */` and emits
`(**(code **)(iVar2 + 0xc))(param_1, param_2 + 1)` — **two** arguments. The
reconstruction transcribed that faithfully, so `cfg` was never passed and the
callee read whatever was in r2.

Fixed in `recon/symbolized/app/serialization_register_endpoint.c` (the build
input) and mirrored into the canonical `recon/app/src/FUN_0004cbec.c` +
`recon/verified/src/FUN_0004cbec.c`.
**Re-verified:** `cfg_verify.py app FUN_0004cbec` → `PASS cases=6`;
`recon_kit.prove(0x4cbec, 86, 'FUN_0004cbec', …, trials=300)` →
`pass=True, checked=306`. Note that both the before and after versions pass —
`tools/parity`/`cfg_verify` model callees as order-keyed oracles that ignore
arguments, exactly the blind spot recorded in iteration 5 §3(b) and iteration 6
§4 (net `FUN_0102d558`).

#### A.3 The real `ipc_ept_cfg`: `g_serialization_ipc_ept_ctx` @ 0x200023dc

The third argument is the RAM pin `g_serialization_ipc_ept_ctx` (0x200023dc),
a `.data` object that no recovered code ever writes.

**The app `.data` load base was derived and then PROVEN.** Hypothesis
L = 0xf6d64 → RAM 0x20000000 (image ends at 0xfab8d, so `.data` length 0x3e29).
Proof: at L + 0x39c8 = flash **0xfa72c** the bytes are

```
+0x00 0x200039c8   wait_q.head      -> itself
+0x04 0x200039c8   wait_q.tail      -> itself
+0x08 0x00000000   count = 0
+0x0c 0x00000001   limit = 1
+0x10 0x200039d8   poll_events.head -> itself   (CONFIG_POLL=y)
+0x14 0x200039d8   poll_events.tail -> itself
```

— a self-consistent `struct k_sem` whose two self-referential list heads can
only be correct if the load base is exactly 0xf6d64. That object is
`g_serialization_ipc_mutex` (0x200039c8), i.e.
`K_SEM_DEFINE(g_serialization_ipc_mutex, 0, 1)`.

With that mapping, `g_serialization_ipc_ept_ctx` loads from flash **0xf9140**:

| off | field | value | decode |
|---|---|---|---|
| +0x00 | `.name` | `0x0009f71c` | the C string **`"ipc0"`** |
| +0x04 | `.prio` | `0x00000000` | 0 |
| +0x08 | `.cb.bound` | `0x00025b6d` | function @0x25b6c |
| +0x0c | `.cb.received` | `0x00025a49` | **`ipc0_ept_recv`** @0x25a48 (durable map) |
| +0x10 | `.cb.error` | `0x00000000` | NULL |
| +0x14 | `.priv` | `0x00000000` | NULL |

Corroboration for each field:

* 0x9f71c is the **only** `"ipc0"` string in `app_update.bin`, and the only
  other pointer to it is the `struct device` at 0x87c08 (= the `ipc0` device,
  our `__device_dts_ord_29`) — so this record announces exactly the name the
  CPUNET core sends in its rpmsg name-service message.
* 0x25a48 is the catalogued `ipc0_ept_recv`.
* 0x25b6c is an **8-byte uncatalogued function** in the Ghidra gap
  0x25b6c..0x25b78. Disassembled from the image it is
  `ldr r0,[pc,#4] ; literal 0x200039c8` + `b.w 0x72880` (= `k_sem_give`), i.e.
  `bound(priv) { k_sem_give(&g_serialization_ipc_mutex); }` — precisely the
  semaphore `serialization_init` then `k_sem_take`s.

#### A.4 Every operand of the call was also mis-placed (RAM-pin collisions)

Measured with `readelf -sW` on the iteration-6 ELF:

| pin | original VA | our build's object at that VA |
|---|---|---|
| `g_serialization_ipc_ept_ctx` | 0x200023dc | `fdtable` (0x20002218, 640 B) |
| `g_serialization_ipc_mutex` | 0x200039c8 | `posix_thread_pool` (0x20003938, 1240 B) |
| `g_ipc_send_fail_cnt` | 0x20007a74 | `smp_work_queue_stack` (0x200075a0, 2048 B) |
| `g_serialization_ipc_ept` | 0x20007a78 | `smp_work_queue_stack` |
| `g_serialization_ipc_ready` | 0x20007a80 | `smp_work_queue_stack` |
| `g_ipc0_endpoint` | 0x20007a84 | `smp_work_queue_stack` |

All six are now **emitted** by a new wiring TU
`recon/application/app/src/g1_ipc_serialization_objects.c` (real
`struct ipc_ept_cfg` with `.name = "ipc0"`, a `K_SEM_DEFINE(…,0,1)`, a
`struct ipc_ept`, and three scalars), and `g1_app_globals.ld` rebinds the six
pin names onto them. The `bound` callback is re-emitted as
`g1_ipc0_ept_bound` (the 8-byte original had to be re-emitted, not pinned,
because its literal must relocate with the semaphore); `received` goes through
a one-line adapter onto the recovered `ipc0_ept_recv`. Verified in the linked
ELF: `.name → "ipc0"`, `bound = 0x000496e5`, `received = 0x00077557`, and the
semaphore's `.data` image is `{self, self, 0, 1, self+0x10, self+0x10}` —
field-for-field the shipped shape.

`PROVIDE(rodata_87c08 = __device_dts_ord_29)` was then **re-applied**.

#### A.5 First measurement: a REGRESSION, root-caused and fixed

Build `/private/tmp/g1-i7a-app` (trace `/tmp/g1_i7a/`) **regressed**:
**4,675,530** instructions / **444** unique fns, kernel `_oops` at 4,669,670 →
`z_fatal_error` → SYSRESETREQ. The assert is `work_queue_main`'s
`__ASSERT(handler != NULL)`.

Cause: **the 64 bytes of RAM this iteration added shifted every object by
0x30–0x40**, and a *latent* RAM-pin collision became fatal.
`app_event_manager_submit` (0x4f770) submits the `k_work` pinned at
**0x20002838**, which lands inside nrfx_gpiote's `.data.m_cb` (0x200027ec,
0x7c B). It moved from `m_cb+0x30` to `m_cb+0x4c`, and the handler word
stopped reading a nonzero value. In iterations 5–6 the same collision was
invisible only because the garbage flags word made `k_work_submit` believe the
item was already queued.

The shipped image has that `k_work` in `.data` (load image flash 0xf959c):
`{ .node.next = 0, .handler = 0x0004f5b1, .queue = 0, .flags = 0 }`, and
0x4f5b0 is the catalogued `app_event_manager_process_events`. It is now emitted
by `g1_app_ram_relocs.c` (group 2) together with `g_notify_pending_lock` /
`g_notify_pending_slist` (both of which land inside `z_main_stack`) and
`g_notify_pending_flags_bitmap`. Emitting the handler also pulls the
previously garbage-collected `app_event_manager_process_events` into the link —
the event manager runs for the first time.

**Structural note (important for later iterations): any change to the app's RAM
footprint re-shuffles which absolute RAM pins collide with which objects.** The
561-pin collision set measured in iteration 6 §3 is not stable across builds;
each iteration has to re-measure.

#### A.6 The endpoint binds

Build `/private/tmp/g1-i7b-app` + the iteration-6 net (`/private/tmp/g1-i6d-net`),
trace `/tmp/g1_i7b/`:

| app function | ours | iteration 6 |
|---|---:|---:|
| `serialization_init` | 4,670,170 | 4,668,211 |
| `open` (rpmsg backend) | 4,670,186 | — |
| `ipc_static_vrings_init` | 4,671,350 | — |
| `ipc_rpmsg_init` | 4,676,781 | — |
| `serialization_register_endpoint` | 4,706,874 | 4,668,237 |
| `register_ept` → `get_ept_slot_with_name` | 4,706,887 / 4,706,973 | — |
| `ns_bind_cb` | 4,717,667 | — |
| `rpmsg_create_ept` | 4,717,930 | — |
| **`bound_cb`** | **4,718,338** | — |
| **`g1_ipc0_ept_bound`** (k_sem_give) | **4,719,132** | — |
| `register_ipc_service_context` | 4,753,574 | 4,701,683 |
| `button_init` | 4,753,717 | 4,701,826 |
| `settings_subsys_init` | 4,758,567 | 4,706,676 |

`bound_cb` fires and `main()` unblocks — the Step A goal. The run was still
truncated, because the **CPUNET** core now reached code it had never executed
and took a kernel panic that reset the whole emulated machine.

#### A.7 Two CPUNET defects, both the same class, both fixed

**(a) The net's two endpoint bind semaphores were pins into a live pool.**
The net UART printed
`ASSERTION FAIL @ WEST_TOPDIR/zephyr/kernel/sched.c:722` (that is
`__ASSERT_NO_MSG(thread->base.pended_on)` in `pended_on_thread`), with
`lr = unpend_thread_no_timeout+0x1e`, reached from
`bound_cb → FUN_0102ac00 → FUN_01036824` (the recovered `k_sem_give`) on the
semaphore pinned at **0x21000914**, which in our net build is inside
`hci_cmd_pool` (0x210008fc, 52 B).

The net `.data` load base was derived the same way and is
**flash 0x0103ed24 → RAM 0x21000000**, length 0xc3c, ending exactly at the
image end 0x0103f960. The two records read

```
0x21000914 -> { 0x21000914, 0x21000914, 0, 1, 0x21000924, 0x21000924 }
0x2100092c -> { 0x2100092c, 0x2100092c, 0, 1, 0x2100093c, 0x2100093c }
```

i.e. `K_SEM_DEFINE(…, 0, 1)` for the `ipc0` and the `nrf_bt_hci` endpoints.
Both are now emitted in `recon/application/net/src/g1_product_endpoints.c`,
together with the endpoint handle `0x210045f8` and its ready flag `0x21004600`
(both of which land inside **`sdc_mempool`**, the SoftDevice Controller heap).
The five recovered TUs that used those literals switch to them through the
file-local `G1_COHESIVE_BUILD` guard already established in that tree, so the
parity path is byte-identical.

**(b) The CPUNET `_kernel` pin — the actual blocker.** With a *correct*
semaphore the take really blocked, and the next assert was
`spinlock.h:273` (`k_spin_release`'s `__ASSERT(z_spin_unlock_valid(l),
"Not my spinlock")`) at `lr = z_pend_curr+0x36`.

Root cause: the recovered spinlock validators `FUN_0103610c`
(`z_spin_lock_valid`), `FUN_01036144` (`z_spin_lock_set_owner`),
`FUN_01036128` (`z_spin_unlock_valid`) and `FUN_01037130` read the kernel
structure at the hard-coded address **0x21004b28** — `_kernel` in the *shipped*
image. Our net build puts `_kernel` at 0x210083d0, and 0x21004b28 is inside
`sdc_mempool`. The recovered validators therefore stamped a garbage
`thread_cpu` owner into every spinlock they took, and the SDK's own
`k_spin_release` (reached through `z_pend_curr`) compared it against the real
`_current`. Both read `+8` (`cpus[0].current`) and `+0x10` (`cpus[0].id`) —
verified identical in our build's `z_spin_lock_set_owner`
(`ldrb r2,[r3,#16]; ldr r3,[r3,#8]; orrs r3,r2; str r3,[r0]`).

Those four TUs now resolve the base to `&_kernel` under `G1_COHESIVE_BUILD`
(literal preserved otherwise). `cfg_verify.py net` re-run on all four:
`FUN_01036144 PASS`, `FUN_0103610c PASS`, `FUN_01036128 PASS`,
`FUN_01037130 PASS cases=4`.

**This is a bounded fix, not the whole class.** `0x21004b28` still appears in
**20 further** `recon/symbolized/net` TUs (and its neighbours 0x21004b30 /
0x21004b40 / 0x21004b4c / 0x21004b5c / 0x21004b68 / 0x21004b70 … appear ~130
times in total). Only the four ownership validators were converted, because
they are the ones that must agree with SDK code. The rest is the natural
scope of iteration 8.

#### A.8 Step A result — no machine reset, full IPC round trip

Build `/private/tmp/g1-i7b-app` + `/private/tmp/g1-i7c-net`, trace `/tmp/g1_i7d/`:
app **5,044,404** instructions / **672** unique (baseline 5,042,715 / 612).
The whole OpenAMP/libmetal/rpmsg stack now executes on the app core
(`open`, `ipc_static_vrings_init`, `metal_*`, `virtqueue_*`, `rpmsg_*`,
`register_ept`, `ns_bind_cb`, `bound_cb`, `advertise_ept`, `ipc_virtio_notify`,
`mbox_nrf_send`), and so does the reply path:

| app function | ours | iteration 6 |
|---|---:|---:|
| `flash_settings_read` | 5,026,495 | 4,973,924 |
| `load_usr_setting` / `set_test_mode` / `load_burial_point` | 5,028,443 / 5,030,513 / 5,030,576 | 4,975,864 / 4,977,934 / 4,977,997 |
| `sys_rand32_get` | 5,033,722 | 4,981,143 |
| `runtime_info_sync` | 5,034,564 | 4,981,993 |
| `global_ipc_service_send` | 5,034,584 | 4,982,013 |
| **`ipc_service_send`** (E4 marker) | **5,034,609** | — |
| `ept_cb` → `g1_ipc0_ept_received` → `ipc0_ept_recv` | 5,036,942 … 5,036,954 | — |

#### A.9 New first divergence (precise) + classification

At **5,036,946** `ipc0_ept_recv` dispatches the reply to the handler stored in
the IPC-service table and jumps to raw **0x162ec** — the unrelocated pin
`rodata_162ed`, installed by `main()`:

```c
B8 (context, 0x6e4) = 1;
W32(context, 0x6e8) = &rodata_998da;      /* service name string   */
W32(context, 0x6ec) = &rodata_162ed;      /* handler, UNRELOCATED  */
...
W32(context, 0x6f8) = &rodata_16bf1;      /* handler, UNRELOCATED  */
W32(context, 0x704) = ADDR_local_esbs_ipc_service_recv_THUMB;  /* already fixed */
W32(context, 0x710) = &rodata_7c00d;      /* handler, UNRELOCATED  */
```

**Classification: the iteration-3/4 code-pointer-pin class.** Three of the four
registered IPC service handlers are still original-image Thumb literals
(0x162ed, 0x16bf1, 0x7c00d); only 0x15961 was rebound (iteration 4). None of
the three has a catalogued entry — 0x162ec and 0x16bf0 sit in uncatalogued
Ghidra gaps, and 0x7c00c is a 4-byte `movs r0,#0; bx lr` stub between
`clear_status_byte_cb` (0x7c004) and `FUN_0007c010`. **Next fix: reconstruct
those three and rebind them, exactly as iteration 4 did for 0x25ae8.**

Honest accounting of the 28 functions the baseline reached and this run does
not: they are all log-formatting/`log_dropped` machinery (`print_formatted`,
`encode_uint`, `snprintk`, `vsnprintk`, `dropped_notify`, …) and RTC/DPPI
teardown (`rtc_nrf_isr`, `sys_clock_announce`, `z_time_slice`,
`nrfx_dppi_channel_free`, …) that ran during the baseline's long idle tail.
This run spends the same instruction budget doing the IPC round trip instead.
97 functions are new.

---

### Step B — library-displacement Batch 0 (goal G2, first batch)

#### B.1 Prerequisite: the sanctioned generator could not run

`tools/gen_retained_sources.py --check` failed before any Batch-0 work:

```
error: missing symbolized identity header for .../recon/symbolized/app/g1_app_ram_relocs.c
error: symbolized filename absent from name catalog: .../recon/symbolized/app/register_ipc_service_recv_callback.c
```

Iterations 4–6 had hand-edited the *generated* `app_retained_sources.cmake`.
Two structural fixes, no `tools/` change:

1. The two hand-written wiring TUs (`g1_gpio_dt_specs.c`, `g1_app_ram_relocs.c`)
   are **not** recovered functions and have no VA, so they were moved out of
   `recon/symbolized/app` into `recon/application/app/src/` (the sanctioned
   place, alongside `g1_lsm6dso_device.c` / `g1_sdk_inline_bridges.c`) and are
   listed explicitly in `recon/application/app/CMakeLists.txt`.
2. `register_ipc_service_recv_callback` (0x25ae8, reconstructed in iteration 4)
   was missing from `recon/catalogs/function_names_app.json` because Ghidra
   never catalogued that gap. The durable entry was added (with its
   `recon/named/` readable mirror). `tools/validate_name_maps.py` previously
   reported this as `app unexpected generated identity 0x00025ae8` + `app …
   has 1 extra identities`; both errors are now gone (the two remaining errors
   are pre-existing net-side ones for 0x0102a720).

`gen_retained_sources.py --check` now reports `retained source lists are
current`, and the generated file is authored solely by the generator again.

#### B.2 Rows added

Four `exclude_reconstruction: true` rows were added to
`recon/ownership/adoption_manifest.json` (`cores.app.entries`, schema-conform,
each carrying the candidate's three evidence records plus a
`library_displacement_candidate` record):

| va | raw_symbol | current_symbol | upstream identity |
|---|---|---|---|
| `0x00017688` | `FUN_00017688` | `gpio_pin_configure_17688` | `gpio_pin_configure_dt` |
| `0x000177c4` | `FUN_000177c4` | `gpio_pin_get_raw_checked` | `gpio_pin_get_raw` |
| `0x00017858` | `FUN_00017858` | `gpio_pin_configure` | **`gpio_pin_interrupt_configure_dt`** |
| `0x00017980` | `FUN_00017980` | `gpio_pin_get_checked` | `gpio_pin_get` (gpio0) |

App manifest summary 567 → **571** entries, 553 → **557** exclusions.
Regenerated list: retained 1707 → **1704**, exclusions 553 → **557**, matched
sources 408 → **412**.

**Correction to the candidate record for 0x17858.** The JSON maps it to
`gpio_pin_configure`; the recovered body dispatches `api + 0x18`
(`pin_interrupt_configure`, not `pin_configure` at `api + 0`), masks
`0x1600000` = `GPIO_INT_{DISABLE,ENABLE,EDGE}` and `0x6000000` =
`GPIO_INT_{LOW_0,HIGH_1}`, and flips the trigger when
`GPIO_INT_LEVELS_LOGICAL` (0x800000) disagrees with `data->invert`. That is
`gpio_pin_interrupt_configure_dt`.

#### B.3 What happened to the callers

As the report predicted, a header `static inline` has **no external symbol to
bind**, so excluding the four TUs left the recovered callers (`button_init`,
`read_sw0_pin`, `nfc_field_event_signal_sem`) with undefined references. They
were wired to the real Zephyr API through a new bridge TU
**`recon/application/app/src/g1_gpio_header_bridges.c`**, which includes
`<zephyr/drivers/gpio.h>` and re-expresses each historical identity as a
one-line call into the genuine inline:

```c
int gpio_pin_configure_17688(const struct gpio_dt_spec *s, gpio_flags_t f)
{ return gpio_pin_configure_dt(s, f); }

int g1_gpio_pin_interrupt_configure_bridge(const struct gpio_dt_spec *s,
                                           gpio_flags_t f)
        __asm__("gpio_pin_configure");          /* pointer_rebind.md mechanism */

int gpio_pin_get_raw_checked(const struct device *p, gpio_pin_t pin)
{ return gpio_pin_get_raw(p, pin); }

int gpio_pin_get_checked(gpio_pin_t pin)
{ return gpio_pin_get(DEVICE_DT_GET(DT_NODELABEL(gpio0)), pin); }
```

The `gpio_pin_configure` identity collides with gpio.h's own inline of that
name, so it is attached with an `__asm__` label — the same conflict-free
mechanism `pointer_rebind.md` uses for function-pointer aliases. **No recovered
caller was edited**: their loose `unsigned int` prototypes are ABI-compatible
on AAPCS. `gpio_pin_get_checked`'s reconstruction carried two extra junk
arguments that the original never used; `button_init` already calls it with one.

#### B.4 Verification and boot result

Rebuild `/private/tmp/g1-i7e-app`: **exit 0, 0 undefined, 0 duplicate**;
FLASH 628,380 B (63.96 %, +1,012 B — the real inlines carry more `__ASSERT`
text), RAM unchanged at 75,757 B, so **no RAM re-shuffle**. `nm` confirms all
four identities are defined and now backed by the header bodies.

Boot (trace `/tmp/g1_i7e/`, same net build): **5,045,044** instructions /
**681** unique functions — **no regression** vs Step A (5,044,404 / 672), and
the four displaced identities execute at the same points on the `button_init`
path, in golden's order:

| function | Step B | Step A | iteration 6 |
|---|---:|---:|---:|
| `button_init` | 4,753,856 | 4,753,856 | 4,701,826 |
| `gpio_pin_configure_17688` | 4,753,945 | 4,753,945 | 4,701,915 |
| `gpio_pin_set_checked` (not displaced) | 4,755,464 | 4,755,444 | 4,703,414 |
| `gpio_pin_configure` (→ interrupt cfg) | 4,757,335 | 4,757,295 | 4,705,265 |
| `gpio_pin_get_checked` | 4,758,352 | 4,758,304 | 4,706,274 |
| `gpio_pin_get_raw_checked` | 4,758,481 | 4,758,461 | 4,706,431 |

**Behaviour change, and it is the payoff.** The A.9 divergence is unchanged in
cause but its *symptom* improved. `ipc0_ept_recv` still jumps to the
unrelocated 0x162ec; in the Step-B layout that address lands inside
`button_init`, which falls through into `gpio_pin_set_checked` and then
`gpio_pin_configure_17688`. With the **real** gpio.h body in place the
`__ASSERT` catches the bogus arguments and the kernel takes a clean
`assert_print` → `assert_post_action` → `_oops` at 5,038,881, instead of Step
A's silent `z_arm_usage_fault` at 5,036,983. `z_arm_usage_fault` /
`z_arm_fault` / `usage_fault.constprop.0` disappear from the trace and nine
logging/fatal functions appear. That is exactly the "library stability +
correct typing" the displacement goal exists to buy: the upstream body detects
the corruption the reconstruction silently accepted.

---

### Regenerate (iteration 7)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
recon/application/build_cohesive.sh app /private/tmp/g1-i7e-app
recon/application/build_cohesive.sh net /private/tmp/g1-i7c-net -- \
  -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i7e/trace.resc' > /tmp/g1_i7e/run.out 2>&1
# trace.resc = $app_elf/$net_elf override + 'i @g1-ours.resc' + tracing macro
# + `sysbus.uart_net CreateFileBackend` + `sysbus.uart0 CreateFileBackend`
# (additive; g1-ours.resc untouched).
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
```

Files changed:
`recon/symbolized/app/serialization_register_endpoint.c`,
`recon/app/src/FUN_0004cbec.c`, `recon/verified/src/FUN_0004cbec.c`
(dropped-argument fix, proven against the original bytes),
`recon/application/app/src/g1_ipc_serialization_objects.c` (new),
`recon/application/app/src/g1_gpio_header_bridges.c` (new),
`recon/application/app/src/g1_app_ram_relocs.c` (moved from
`recon/symbolized/app/`, + group 2),
`recon/application/app/src/g1_gpio_dt_specs.c` (moved from
`recon/symbolized/app/`),
`recon/application/app/CMakeLists.txt` (4 wiring TUs listed explicitly),
`recon/symbols/g1_app_globals.ld` (`rodata_87c08` re-applied + 10 RAM-pin
rebinds with evidence),
`recon/symbolized/app/button_init.c` (comment path only),
`recon/application/net/src/g1_product_endpoints.c` (2 semaphores + ept + flag),
`recon/net/src/FUN_0102ac00.c`, `FUN_0102ac0c.c`, `FUN_0102ace8.c`,
`FUN_0102abac.c`, `FUN_0102acf4.c` (guarded relocation of the net IPC objects),
`recon/{symbolized/net,net/src}/FUN_0103610c.c`, `FUN_01036128.c`,
`FUN_01036144.c`, `FUN_01037130.c` (guarded `_kernel` base),
`recon/catalogs/function_names_app.json` + `recon/named/register_ipc_service_recv_callback.c`
(0x25ae8 durable entry),
`recon/ownership/adoption_manifest.json` (4 Batch-0 exclusions),
`recon/generated/app_retained_sources.cmake` (regenerated by the sanctioned
generator only).
No `tools/` change, no Kconfig/`prj.conf`/devicetree change, `armemul` additive
only. Nothing committed.
