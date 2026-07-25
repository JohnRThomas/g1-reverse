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

---

## Iteration 8 — the three remaining IPC-service handlers (Step A) + library-displacement Batch 1 (Step B)

**Headline.** The three unrelocated IPC-service handler pointers are gone.
`0x162ec`, `0x16bf0` and `0x7c00c` were reconstructed from the image, proven,
and rebound, and the app's IPC receive path now runs **real Even handler code**
instead of jumping into whatever our layout happened to put at the raw
address. Iteration 7's kernel `_oops` at 5,038,881 is **gone**: the whole
`assert_print → assert_post_action → _oops → z_fatal_error →
nrf_cc3xx_platform_abort → SYSRESETREQ` chain disappears from the trace and the
app completes its init and settles in the kernel idle loop.

Step B displaced **52** leaf libc / lib-os / zcbor / arch reconstructions onto
their genuine upstream bodies, clean, with **FLASH −2,252 B** and no trace
regression.

Milestone tier: **E1–E3 complete, E4 advanced further than any previous
iteration but still NOT completed.** `spi_read_id`, `bt_enable`/`bt_start` and
the first ADV_IND are still not reached — the new blocker is on the **CPUNET**
core (§A.7).

Final artifacts: app `/private/tmp/g1-i8b-app` (Step-A-only:
`/private/tmp/g1-i8a-app`), net unchanged `/private/tmp/g1-i7c-net`.
Traces `/tmp/g1_i8a/`, `/tmp/g1_i8b/` (0.15 s, comparable to the baseline) and
`/tmp/g1_i8a_long/`, `/tmp/g1_i8b_long/` (3.0 s, comparable to golden).

| metric | iteration 7 (baseline) | **iter 8 Step A** | **iter 8 Step A+B (final)** |
|---|---:|---:|---:|
| app instructions @0.15 s | 5,045,044 | 5,041,477 | **5,041,553** |
| app unique functions @0.15 s | 681 | 671 | **672** |
| app instructions @3.0 s | — (machine reset at 0.15 s) | 5,151,848 | **5,149,911** |
| app unique functions @3.0 s | — | 680 | **681** |
| net instructions @0.15 s | 255,064 (cut short by the reset) | 10,091,064 | **10,091,064** |
| net unique functions | 423 | 435 | **435** |
| app FLASH | 628,380 B (63.96 %) | 629,932 B (64.11 %) | **627,680 B (63.88 %)** |
| app RAM | 75,757 B (16.81 %) | 75,757 B (16.81 %) | **75,757 B (16.81 %)** |
| net FLASH / RAM | 228,009 B / 54,140 B | unchanged (net not rebuilt) | unchanged |

Both app builds: `nm -u` = **0** undefined, **0** duplicate globals. No
`--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig/`prj.conf`/devicetree change; `armemul` used
additively only (extra `.resc` files under `/tmp`; `g1-ours.resc` and the
models untouched). Nothing committed.

**Honest note on "fewer instructions / fewer unique functions".** At 0.15 s the
Step-A run executes 3,567 *fewer* app instructions and 10 fewer unique
functions than the baseline. Every one of the 24 functions the baseline reached
and this run does not is fatal-path machinery that only ran *because* of the
crash: `assert_print`, `vprintk`, `assert_post_action`, `z_arm_svc`, `_oops`,
`z_do_kernel_oops`, `z_arm_fatal_error`, `z_fatal_error`, `k_current_get`,
`z_log_msg_runtime_create`, `is_ptr`, `g1_recon_z_log_msg_alloc`,
`log_msg_finalize_commit`, `z_log_dropped`, `fatal_log_and_reset`,
`g1_recon_z_impl_log_panic`, `log_msg_process`, `log_msg_commit`, `panic`,
`log_process`, `nrf_cc3xx_platform_abort`, `z_impl_k_timer_stop`,
`z_unpend1_no_timeout`. Nothing legitimate was lost. Given the same 3.0 s
budget golden gets, the run reaches 681 unique functions — the baseline's count
— without any of the fatal chain.

---

### Step A — reconstruct and rebind the three IPC-service handlers

#### A.1 What the three pins actually are

`main()` registers four named IPC services into the context record at +0x6e4;
each record is `{ id : u8, name : char*, handler : code* }`. Iteration 4 bound
only one of the four handlers. The other three were raw image literals:

| service id | name string | handler pin | identity |
|---|---|---|---|
| 1 | `"cpuapp-hw-id"` (0x998da) | `rodata_162ed` | **`local_ipc_service_recv`** @0x162ec |
| 6 | `"cpunet-esbm-cpu-sync"` (0x998e7) | `rodata_16bf1` | **`local_esbm_ipc_service_recv`** @0x16bf0 |
| 4 | `"cpunet-esbs"` (0x998fc) | (already bound, iteration 4) | `local_esbs_ipc_service_recv` @0x15960 |
| 5 | `"cpunet-esbs-ctrl"` (0x99908) | `rodata_7c00d` | **`local_esbs_ctrl_ipc_service_recv`** @0x7c00c |

`ipc0_ept_recv` dispatches `handler(context, data + 1, length - 1)`, so the
handler's `packet[0]` is a sub-command.

**Both names are self-evidenced, not guessed** — exactly the 0x25ae8 pattern:
every log line in 0x162ec passes the string at 0x00099b56,
`"local_ipc_service_recv"`, as its `"%s()"` argument, and every log line in
0x16bf0 passes 0x00099b6d, `"local_esbm_ipc_service_recv"`.

#### A.2 Extents derived from the image (all three are Ghidra gaps)

| VA | Ghidra gap | code extent | literal pool | size |
|---|---|---|---|---|
| 0x162ec | 0x162d8..0x1655c | **0x162ec..0x16520** | 0x16520..0x1655c | **0x234 = 564 B** |
| 0x16bf0 | 0x16bc4..0x16eb8 | **0x16bf0..0x16e88** | 0x16e88..0x16eb8 | **0x298 = 664 B** |
| 0x7c00c | 0x7c00c..0x7c010 | **0x7c00c..0x7c010** | — | **4 B** |

0x162d8..0x162eb and 0x16bc4..0x16bef are the *preceding* functions' literal
pools (`runtime_info_sync`'s and `change_work_mode_to`'s respectively), decoded
word-by-word to confirm they are data, not code. 0x7c00c is a 4-byte
`movs r0,#0; bx lr` stub sitting between `FUN_0007c004` and the
`thunk_FUN_00072880` veneer, preceded by an alignment `nop`.

`local_ipc_service_recv` is a 13-entry `tbh` switch on `packet[0] - 1`
(commands 1,2,3,4,6,7,13 + default) over the "cpuapp-hw-id" protocol: uptime
reporting, a `sys_reboot` watchdog when the cpunet sync package arrives later
than 10,001 ms, BT MAC/ESB-master-address mirroring into the context at
+0xfda/+0xfe0, a `bt_ready` notification, a 32-byte device-name `strncpy`, and
the `IPC_RESP_CPUNET_ESB_PACKAGES` counters at 0x200069e8..0x200069f4.
`local_esbm_ipc_service_recv` is a 12-entry `tbh` switch on
`packet[0] & 0x3f` (commands 4..15) over the ESB-master sync protocol: a
sequence-dedup on `packet[0x15]`, a 22-byte snapshot of the packet into
context+0x6cc with the previous snapshot preserved at +0xfcf/+0xfe0, shutdown
and work-mode transitions, two 0xda-byte message-payload copies, and the
onboarding / not-disturb display sync.

#### A.3 Proof status — what was actually run

All three were saved by `recon_kit.prove(...)` (auto-save on pass) into
`recon/app/src/`, mirrored into `recon/verified/src/`, and re-checked with the
CLI verifier:

| function | `recon_kit.prove` | `cfg_verify.py app <name>` |
|---|---|---|
| `local_ipc_service_recv` | `pass=True cfg_status=PASS checked=310` | **`PASS cases=13`** |
| `local_esbm_ipc_service_recv` | `pass=True cfg_status=PASS checked=312` | **`PASS cases=12`** |
| `local_esbs_ctrl_ipc_service_recv` | `pass=True cfg_status=PASS checked=300` | `PASS cases=0` |

`cases=13` / `cases=12` are exactly the two `tbh` table sizes: cfg_verify drove
**every** switch case from the original's own jump table.

**Catalog note (disclosed).** `recon_kit.info` / `cfg_verify` resolve identity
and size from the scratchpad catalogs, and none of the three was catalogued.
One record per function was appended to `<scratchpad>/app_funcs.json` and
`<scratchpad>/classified.json` (originals backed up as `*.json.i8bak`), exactly
as iteration 4 did for 0x25ae8. **No `tools/` logic was changed.**

#### A.4 Heeding the harness blind spot — directed fixtures + mutation controls

`prove` + `cfg_verify` model callees as **order-keyed oracles that ignore their
arguments** (iteration 5 §3b, iteration 7 §A.2). A separate directed harness
(`<scratchpad>/directed8.py`) therefore re-ran all three with

* `candidate_direct_target_map` — the **call target** is compared,
* `call_arity_by_target` — **r0..r3** are compared at every call,
* `call_stack_arity_by_format` — the **stack varargs** are compared at the two
  log sites that pass them (formats 0x99638 and 0x996b3, two words each; the
  other sites pass none, and the words at `[sp]` there are just the incoming
  r0/r1/r2 the prologue pushed),
* `absolute_memory_overrides` — `g_log_level`, `g_log_use_alt_sink` and
  `device_info` are driven explicitly instead of left as PRNG garbage,
* `arg_overrides` — a real packet buffer per switch case.

Results: `local_ipc_service_recv` **256 cases, PASS** (240 compared; the 16
that exercise the case-2 reboot arm are inconclusive because the shipped code
has *no return path* there — it falls through into its out-of-line log blocks
and loops, so both sides hit the instruction cap. Re-running the same 256 cases
with `sys_reboot` as a `terminal_target` compares that arm too: **256/256
PASS**). `local_esbm_ipc_service_recv` **240 cases, PASS**.
`local_esbs_ctrl_ipc_service_recv` **16 cases, PASS**.

Two further oracle-pinned fixtures close the two coverage holes the mutation
run exposed (below): `h1_boundary` pins `uptime_ticks_get`'s return so the
`0x2711` millisecond bound is straddled exactly (72 cases, PASS), and
`h2_payload` pins `get_message_entry` / `pt_queue_get_free_slot` to a seeded
object so both 0xda-byte payload copies are actually reached (48 cases, PASS).

**Mutation controls (`<scratchpad>/mutate8.py`).** 13 deliberate defects were
injected one at a time; every one must be rejected. First run: **10 of 13
rejected, 3 survived** — and the three survivors were real fixture gaps, not
false alarms:

| surviving mutant | why it survived | fix |
|---|---|---|
| reboot bound `0x2711 → 0x2710` | the uptime oracle returns a pseudorandom 64-bit tick count, so the exact boundary is never produced | `h1_boundary` |
| case-11 payload `0xda → 0xd9` | `get_message_entry`'s pseudorandom return never survives the `entry[0xe]`/`entry[0xd]` gates, so the copy is never reached | `h2_payload` |
| case-12 destination loses the `+0xda` bias | same | `h2_payload` |

With the two new fixtures **all 13 mutants FAIL and both unmutated controls
PASS**. The other ten (dropped stack varargs, flipped sink polarity, swapped
store target, off-by-one `strncpy` length, shifted log-level guards, 22→21-byte
mirror copy, wrong flag mask, wrong pending-state constant, wrong sentinel)
were rejected from the start.

#### A.5 Rebinding the three pins

A bare linker `PROVIDE` is not a `--gc-sections` root (iteration 4 proved it
links as `0x00000001` when the target is discarded), so each pin is bound
through the `pointer_rebind.md` `__asm__`-alias mechanism:

```c
/* recon/symbols/g1_app_symbols.h */
extern const unsigned char __g1_fp_local_ipc_service_recv[]
    __asm__("local_ipc_service_recv");
#define ADDR_local_ipc_service_recv_THUMB \
    (((unsigned long)&__g1_fp_local_ipc_service_recv) | 1u)
```

and `recon/symbolized/app/main.c` stores `ADDR_<name>_THUMB` into ctx+0x6ec /
+0x6f8 / +0x710 instead of `&rodata_162ed` / `&rodata_16bf1` / `&rodata_7c00d`.
The `g1_app_globals.ld` entries are kept as the documented binding
(`PROVIDE(rodata_162ed = local_ipc_service_recv | 1);` and siblings).

Verified in the linked ELF (`/private/tmp/g1-i8a-app`):

```
nm:      00015354 T local_ipc_service_recv
         00015bf0 T local_esbm_ipc_service_recv
         00075102 T local_esbs_ctrl_ipc_service_recv
objdump: 1624c: .word 0x00015355      <- local_ipc_service_recv | 1
         16254: .word 0x00015bf1      <- local_esbm_ipc_service_recv | 1
         16264: .word 0x00075103      <- local_esbs_ctrl_ipc_service_recv | 1
```

and the raw literals `0x000162ed` / `0x00016bf1` / `0x0007c00d` no longer
appear anywhere in `.text`.

**14 new pins** were added to `g1_app_globals.ld` + `g1_app_symbols.h` in a
dedicated iteration-8 block: 12 interior rodata string pins (the log formats
and the two `%s()` tag strings) and two absolute RAM cells,
`g_20007b34` (the atomic shutdown-request flags word) and `g_2000ff4a` (the
last-handled esbm sequence byte). Both RAM cells land inside live objects in
our layout (`smp_work_queue_stack` and `kheap__system_heap`) — they are members
of the still-open 561-pin collision set, harmless on this boot because only the
service-id-1 handler is ever dispatched, and recorded here so the next
iteration can emit them if the esbm path starts running.

**No RAM re-shuffle.** RAM stayed at exactly 75,757 B across both builds, so
none of the latent absolute-RAM-pin collisions changed owner (contrast
iteration 7 §A.5, where +64 B of RAM turned a latent collision fatal).

#### A.6 Boot result — the fault is gone and the app finishes its init

Build `/private/tmp/g1-i8a-app` + the iteration-7 net, trace `/tmp/g1_i8a/`:

| app function | iteration 8 | iteration 7 |
|---|---:|---:|
| `ept_cb` → `g1_ipc0_ept_received` → `ipc0_ept_recv` | 5,036,937 … 5,036,949 | 5,036,942 … 5,036,954 |
| **`local_ipc_service_recv`** | **5,036,972** | — (jumped into `button_init` at raw 0x162ec) |
| `uptime_ticks_get` → `k_uptime_ticks_impl` | 5,036,982 | — |
| `runtime_info_sync` | 5,037,067 | — |
| `global_ipc_service_send` → `ipc_service_send` → `send` | 5,037,087 … 5,037,129 | — |
| `assert_print` / `_oops` / `z_fatal_error` | **never** | 5,037,038 / 5,038,893 / 5,044,262 |

The received message is sub-command **2** (the cpunet sync package): the
handler reads the uptime, finds it below the 10,001 ms reboot threshold, and
answers with `runtime_info_sync`, which sends the reply back over IPC. That is
the shipped protocol running end to end for the first time.

After that the app runs the RTC/DPPI teardown (`z_nrf_rtc_timer_chan_free`,
`nrfx_dppi_channel_free`, `nrfx_flag32_free`, all new) and enters the kernel
`idle` loop.

#### A.7 New first divergence — the CPUNET core spins on LFCLKSTAT

With the app fault removed, the machine is no longer reset, so both cores run
the full budget for the first time. Extending to golden's 3.0 s
(`/tmp/g1_i8b_long/`) makes the new blocker unambiguous:

| checkpoint | ours @3.0 s | golden @3.0 s |
|---|---:|---:|
| app instructions | 5,149,911 | 12,629,795 |
| net instructions | 295,091,064 | 2,157,739 |
| `radio TransmittedFrames` | **0** | **6** (first at t=1.5 s) |

* **App side:** `main` sends `runtime_info_sync` and then blocks in
  `k_sem_take` at 5,035,486 (`z_pend_curr → arch_swap`), and never runs again.
  The semaphore it waits on is the one `local_ipc_service_recv` releases on
  sub-commands **1** and **3** (`if (*(u32 *)(ctx+0x10) == 0) k_sem_give(ctx+8)`).
  Only sub-command 2 ever arrives, so `main` stays pended and the display / BT
  bring-up that follows it never starts. `spi_read_id`, `bt_enable`,
  `bt_start` and ADV_IND are therefore still unreached — **E4 is not
  completed.**
* **Net side, and this is the actual stop:** after handling the app's message
  the CPUNET runs
  `ept_cb → FUN_0102ab14 → FUN_01021a38 → FUN_01022e34 → FUN_010248d0`
  and **never leaves** `FUN_010248d0`:

  ```c
  void FUN_010248d0(void) {           /* recon/symbolized/net/FUN_010248d0.c */
      unsigned base = (unsigned)&g_154_critical_section_nest_cnt; /* 0x21001bd0 */
      while (FUN_01024b20(*(volatile unsigned *)(base + 0x20) & 3) == 0)
          ;
  }
  unsigned FUN_01024b20(unsigned char want) {   /* reads 0x41005000 + 0x418 */
      unsigned a = LFCLKSTAT, b = LFCLKSTAT;    /* CPUNET CLOCK */
      return (a & 0x10000) ? ((b & 3) == want) : 0;
  }
  ```

  0x41005000 is the CPUNET CLOCK/POWER/RESET block and +0x418 is **LFCLKSTAT**
  (bit 16 = STATE, bits 0..1 = SRC). The loop spins until the low-frequency
  clock reports *running* with the source the controller stored at
  `0x21001bf0`. It never does: `armemul`'s `NRF5340_ClockPowerReset` model
  (`models/NRF5340_ClockPowerReset.cs:224-230`) drives LFCLKSTAT.STATE from
  `lfclkRunning`, which is set only by an LFCLKSTART write, and nothing on our
  CPUNET issues one. 615,296 iterations at 0.15 s, ~18 M at 3.0 s.

  **This code path does not exist in golden at all.** The golden net trace
  (739 unique functions, E1–E5) never executes `FUN_010248d0`,
  `FUN_01024b20`, `FUN_01022e34`, `FUN_01021a38` or `FUN_0102ab14`; at the
  corresponding point it is inside the SoftDevice controller. So the CPUNET is
  taking a branch golden does not take, and the missing LFCLK start is
  downstream of that.

  **It is not new, and it is not caused by Step A.** The same loop is already
  in the iteration-7 net trace (620 iterations); iteration 7 only looked
  quiet because the app's `_oops` reset the machine 0.15 s in and stopped the
  net. Removing the app fault unmasked it. The net image was **not rebuilt**
  this iteration (`/private/tmp/g1-i7c-net` byte-for-byte).

**Classification: a CPUNET control-path divergence — the natural scope of
iteration 9.** The three sub-questions it has to answer are (a) why our CPUNET
enters `FUN_0102ab14`'s slot-allocation path at all when golden does not,
(b) which CPUNET code should have started the LFCLK, and (c) which sub-command
the net is supposed to send so `main`'s semaphore is released.

---

### Step B — library-displacement Batch 1 (goal G2)

#### B.1 Rows added

Batch 1 was re-derived from `recon/ownership/library_displacement_candidates.json`
with the report's own §4 predicate

```
core == app && confidence == high && upstream_object_in_link &&
referenced_by_linker_artifact == [] && callers.even_owned == 0 &&
component in {libc_newlib_nano, zcbor, zephyr_lib_os, zephyr_arch,
              zephyr_soc, zephyr_libc}
```

which yields exactly the documented **52 rows / 8,186 B**
(`libc_newlib_nano` 25, `zcbor` 9, `zephyr_lib_os` 7, `zephyr_arch` 7,
`zephyr_soc` 2, `zephyr_libc` 2). All 52 `exclude_reconstruction: true` rows
were appended to `recon/ownership/adoption_manifest.json` (`cores.app.entries`)
by `<scratchpad>/batch1.py`, each carrying the candidate's own evidence records
plus a `library_displacement_candidate` record with its linkage, caller counts
and boot-path flags. App manifest **571 → 623** entries, **557 → 609**
exclusions.

`recon/generated/app_retained_sources.cmake` was regenerated **only** by
`tools/gen_retained_sources.py` (retained 1707 → **1655**, matched sources
412 → **464**); `--check` reports "retained source lists are current". The
generated cmake was not hand-edited.

Verified in the build tree: all 52 reconstruction TUs produced a `.c.obj` in
the Step-A build and **none** of them is compiled in the Step-B build.

#### B.2 The callers that broke, and how they were wired

The first Step-B link failed with undefined references to **twelve** of the
displaced identities — `Balloc`, `Bfree`, `multadd`, `pow5mult`, `bigint_mult`,
`lshift`, `bigint_diff`, `clz32`, `bignum_compare_abs`, `d2b_decompose`,
`sbrk_impl`, `smakebuf_r` — from five *recovered newlib TUs that are not in
Batch 1* (`dtoa_r.c`, `i2b.c`, `bignum_div_trial_subtract.c`, `stdio_fclose.c`,
`_sbrk_r.c`). This is exactly the predicted failure mode, and the fix is the
goal: wire the callers to the real library API.

New bridge TU **`recon/application/app/src/g1_newlib_mprec_bridges.c`** (the
Batch 0 `g1_gpio_header_bridges.c` pattern) forwards each historical identity
onto the genuine newlib entry point:

| historical identity | forwards to |
|---|---|
| `Balloc` / `Bfree` | `_Balloc` / `_Bfree` |
| `multadd` / `pow5mult` / `bigint_mult` | `__multadd` / `__pow5mult` / `__multiply` |
| `lshift` / `bigint_diff` | `__lshift` / `__mdiff` |
| `clz32` / `bignum_compare_abs` | `__hi0bits` / `__mcmp` |
| `d2b_decompose` | `__d2b` (hard-float: r0=reent, d0=value, r1/r2=out) |
| `sbrk_impl` / `smakebuf_r` | `_sbrk` / `__smakebuf_r` |

Argument lists are taken from the **proven** reconstruction prototypes in
`recon/app/src/<name>.c`; the trailing Ghidra-artifact parameters that the
shipped code never reads (`pow5mult` #4, `bigint_diff` #4, `smakebuf_r` #3) are
accepted and dropped. AAPCS makes each forward exact, and GCC emits a 4-byte
`b.w` per bridge (confirmed: `readelf -sW` shows size 4 for every one).
**No recovered caller source was edited.** The TU is listed explicitly in
`recon/application/app/CMakeLists.txt` next to the Batch 0 bridge.

`_sbrk` was not previously in the link at all; referencing it from the bridge
pulls the genuine Zephyr libc hook in — which is why one new function,
`sbrk`, appears in the Step-B trace.

#### B.3 Verification and boot result

Rebuild `/private/tmp/g1-i8b-app`: **exit 0, 0 undefined, 0 duplicate**.
FLASH 629,932 → **627,680 B (63.88 %, −2,252 B)**; RAM unchanged at 75,757 B,
so **no RAM re-shuffle**. (The delta is smaller than the batch's 8,186 B of
displaced extent because most of those bodies were already `--gc-sections`
casualties and several upstream members are newly pulled in.)

Boot (`/tmp/g1_i8b/`, same net build): **5,041,553** instructions / **672**
unique at 0.15 s and **5,149,911** / **681** at 3.0 s — versus Step A's
5,041,477 / 671 and 5,151,848 / 680. **No regression:** the trace diff is
exactly one new function (`sbrk`, the genuine newlib hook) and **zero**
functions lost; every marker shifts by the same +76 instructions the bridge
thunks cost, in the same order:

| function | Step B | Step A |
|---|---:|---:|
| `main` | 4,667,595 | 4,667,579 |
| `button_init` | 4,753,935 | 4,753,859 |
| `settings_subsys_init` | 4,758,777 | 4,758,701 |
| `runtime_info_sync` | 5,034,643 | 5,034,567 |
| `local_ipc_service_recv` | 5,037,048 | 5,036,972 |

**Rows reverted: none.** All 52 survived the build and the boot.

---

### Regenerate (iteration 8)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app local_ipc_service_recv
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app local_esbm_ipc_service_recv
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app local_esbs_ctrl_ipc_service_recv
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/directed8.py h1|h2|h3|h1b|h2b
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/mutate8.py
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
recon/application/build_cohesive.sh app /private/tmp/g1-i8b-app
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i8b/trace.resc'       > /tmp/g1_i8b/run.out 2>&1        # 0.15 s
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i8b_long/trace.resc'  > /tmp/g1_i8b_long/run.out 2>&1   # 3.0 s
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
```

Files changed:
`recon/app/src/local_ipc_service_recv.c`,
`recon/app/src/local_esbm_ipc_service_recv.c`,
`recon/app/src/local_esbs_ctrl_ipc_service_recv.c` (new, proven) + their
`recon/verified/src/` mirrors and `recon/named/` readable mirrors,
`recon/symbolized/app/{local_ipc_service_recv,local_esbm_ipc_service_recv,local_esbs_ctrl_ipc_service_recv}.c`
(new build inputs),
`recon/symbolized/app/main.c` (three handler stores rebound),
`recon/symbols/g1_app_globals.ld` (3 rebinds + 14 new pins),
`recon/symbols/g1_app_symbols.h` (3 `__asm__` aliases + 3 ADDR macros + 14 externs),
`recon/catalogs/function_names_app.json` (3 durable entries, 2509 → 2512),
`recon/ownership/adoption_manifest.json` (52 Batch-1 exclusions),
`recon/application/app/src/g1_newlib_mprec_bridges.c` (new),
`recon/application/app/CMakeLists.txt` (1 TU listed),
`recon/generated/app_retained_sources.cmake` (regenerated by the sanctioned
generator only).
Scratchpad catalogs gained three records each (backed up as `*.json.i8bak`).
No `tools/` change, no Kconfig/`prj.conf`/devicetree change, `armemul`
additive only. Nothing committed.

---

## Iteration 9 — the CPUNET "cpunet-hw-id" handler pin (Step A) + library-displacement Batch 2 (Step B)

**Headline.** Iteration 8's LFCLK diagnosis was **wrong**, and this iteration
corrects it with measurements. The CPUNET was never legitimately inside MPSL's
timeslot path: the net's product `main` registers its IPC service handler as a
**raw, unrelocated image literal `0x0102aa79`**, and `FUN_0102ab14` was calling
straight into whatever our layout happened to place at that address. In the
iteration-8 layout that was `FUN_01021a38` — which really is
`mpsl_timeslot_session_open`, whose documented first action is to wait for the
LFCLK — so the "LFCLK divergence" was an *accident of the link map*, not a
clock bug. The LFCLK was running the whole time.

With the handler reconstructed (`FUN_0102a278`, CFG-proven, 13/13 tbb arms) and
the pointer relocated, IPC sub-commands **1/3 now arrive**, the app's `main`
unblocks from `k_sem_take`, and the boot advances from 672 to **762 unique app
functions**: display power-on, the audio codec, LSM6DSO, OPT3007, ST25DV, NVS
settings writes, the fuel gauge and the BLE work thread all run for the first
time. **E4 is still NOT complete** — `spi_read_id`, `bt_enable`/`bt_start` and
ADV_IND are still unreached — and the new blocker is a context switch into a
thread whose saved PC is `0x00000000`.

Step B displaced **16** `zephyr_kernel` sched/poll reconstructions with
**FLASH −1,264 B** and no boot regression; the 39-row `zephyr_drivers`
sub-batch was tried, **regressed the boot, and was reverted**.

Final artifacts: app `/private/tmp/g1-i9g-app` (Step A only:
`/private/tmp/g1-i9e-app`), net `/private/tmp/g1-i9c-net`. Traces
`/tmp/g1_i9a/` (iteration-8 baseline reproduced), `/tmp/g1_i9b/`, `/tmp/g1_i9c/`,
`/tmp/g1_i9d/`, `/tmp/g1_i9e/`, `/tmp/g1_i9f/` (reverted), `/tmp/g1_i9g/`.

### Measurements (all at the same 0.15 s budget, same `.resc`, same RNG seed)

| metric | iteration 8 (reproduced) | **iter 9 Step A** | **iter 9 Step A+B (final)** |
|---|---:|---:|---:|
| app instructions executed | 5,041,553 (full 0.15 s, no fault) | **5,647,329** (fatal at 0.048 s) | **5,612,329** (fatal at 0.048 s) |
| app unique functions | 672 | **762** | **760** |
| net instructions executed | 10,091,064 (3.08 M of them the LFCLK spin) | **289,451** | **289,451** |
| net unique functions | 435 | 420 | 420 |
| `local_ipc_service_recv` entries | 3 | **9** | 9 |
| app FLASH | 627,680 B (63.88 %) | 627,680 B (63.88 %) | **626,416 B (63.76 %)** |
| app RAM | 75,757 B (16.81 %) | 75,757 B (16.81 %) | **75,757 B (16.81 %)** |
| net FLASH | 228,009 B (98.52 %) | **229,161 B (99.02 %)** | 229,161 B (99.02 %) |
| net RAM | 54,140 B (82.61 %) | 54,140 B (82.61 %) | 54,140 B (82.61 %) |

Both links: `nm -u` = **0** undefined, 0 duplicate globals. No
`--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig/`prj.conf`/devicetree change; `armemul` untouched
(only extra `.resc` files under `/tmp`). Nothing committed.

**Honest note on the fixed-checkpoint counters.** The 0.15 s checkpoint now
reads **0/0/0** for both cores, because the app raises a usage fault at
0.048 s and `fatal_error` issues SYSRESETREQ, which resets the whole machine
and zeroes Renode's `ExecutedInstructions`. The numbers in the table are the
instructions actually executed *before* that reset, recovered from the
execution-trace logs. On every progress metric the boot advances (+90 unique
app functions, 103 new ones, 13 lost — see §A.7); it advances into a fault that
was previously unreachable because `main` never got past `k_sem_take`.

**Honest note on the net counters.** The net's 10,091,064 → 289,451 drop is not
a loss: 3,076,471 of the iteration-8 instructions were the `FUN_010248d0`
spin-loop (615,296 iterations) and the rest is simply the shorter wall-clock
window before the reset. The 15 "lost" net functions are the four displaced /
garbage-collected MPSL bodies plus RTC-teardown and logging paths that only run
later in the 0.15 s window.

---

### Step A — the real root cause: an unrelocated CPUNET service-handler pointer

#### A.1 Iteration 8's diagnosis was wrong, and here is the evidence

Iteration 8 §A.7 asserted that "golden's net never executes any of those four
functions" and that "nothing on our CPUNET ever issues LFCLKSTART". Both
statements are false. Read straight out of
`recon/emulator/reports/golden_boot_trace.json`:

| function | golden `first_i` | entries | instructions |
|---|---:|---:|---:|
| `FUN_0103038c` | 104,910 | 203 | 6,716 |
| `FUN_010248d0` (the "spinner") | 106,047 | 10 | **131** |
| `FUN_01024b20` | 106,142 | 5 | 110 |
| `FUN_01021a38` | 387,868 | 5 | 37 |
| `FUN_01022e34` | 387,916 | 4 | 53 |

Golden runs all of them, and its `FUN_010248d0` returns immediately
(131 instructions across 10 entries — 8 instructions is one pass of the loop).
Only `FUN_0102ab14` is genuinely absent from golden.

And our net *does* start the LFCLK. Its own trace shows
`sys_clock_driver_init → z_nrf_clock_control_lf_on → onoff_request →
onoff_start → lfclk_start → nrfx_clock_start → clock_event_handler →
clkstarted_handle → onoff_started_callback` at net instructions
140,864 … 141,315. A Renode diagnostic read of the **iteration-8 net image**
at t = 0.15 s confirms the hardware state:

```
LFCLKSTAT    = 0x00010002     (STATE = 1 running, SRC = 2 = LFXO)
LFCLKRUN     = 0x00000001
LFCLKSRC     = 0x00000002
LFCLKSRCCOPY = 0x00000002
mem[0x21001bd0] = 0 ; mem[0x21001bf0] = 0
cpunet PC    = 0x0102b8ac   (inside FUN_010248d0)
```

So `FUN_01024b20` read `LFCLKSTAT & 3 == 2` and compared it against
`*(0x21001bd0 + 0x20) & 3 == 0` — MPSL's private *expected-source* word, which
this build never initialises because the genuine `libmpsl.a` owns that state at
its own address. Renode's `NRF5340_ClockPowerReset` model is **not** the gap;
it implements TASKS_LFCLKSTART / LFCLKSTAT / LFCLKSRC fully
(`models/NRF5340_ClockPowerReset.cs:85-93, 219-235`) and golden exercises them.
No armemul change is needed, and none was made.

#### A.2 Why the CPUNET was in that code at all — the actual defect

Reading the trace one transition finer exposes it. Baseline
(`/tmp/g1_i9a/trace_net.log`), with our ELF's `nm`:

```
245,106  ept_cb                @ 0x103bf78
245,117  FUN_0102ab14          @ 0x102e954    (function entry)
245,137  FUN_01021a38          @ 0x102aa78    <-- FUN_01021a38 starts at 0x102aa30
```

The dispatch did **not** enter `FUN_01021a38`; it jumped to the absolute
address `0x0102aa78`, which merely *happened* to be 0x48 bytes inside it. Relink
the image (§A.6 tried displacing `FUN_01021a38` first) and the very same pointer
lands 0x100 bytes inside `main` instead, faulting on `blx` through a garbage
`state->send`.

The pointer's origin is in the shipped source itself,
`recon/net/src/FUN_0102a720.c`:

```c
cfg->id = 1;
cfg->name = (const char *)0x0103cd79u;       /* "cpunet-hw-id" */
cfg->callback = (const void *)0x0102aa79u;   /* raw callback back-map */
state->register_ep(cfg);
```

`0x0102aa79` is a **runtime** Thumb address; net runtime = net analysis +
0x800, so it denotes the function at **analysis VA 0x0102a278** — a Ghidra
function-catalog gap. This is exactly the class iteration 8 fixed on the app
core (its four `{id, name, handler}` service records), one core later.

#### A.3 `FUN_0102a278` — the CPUNET "cpunet-hw-id" service handler

Extents derived from the image: code **0x0102a278 .. 0x0102a368 (0xF0 = 240 B)**,
literal pool 0x0102a368 .. 0x0102a394 (44 B), next catalogued function
`FUN_0102a394`. Its literal pool resolves to `0x21000761/63/67` (the ESB
address mirror), `0x21000760` (a reply-pending flag), `0x21000580` (the net log
level), `0x210045f4` (the service-state slot) and five format strings, read out
of the image at analysis = runtime − 0x800:

| runtime literal | string |
|---|---|
| `0x0103ccda` | `"L %d, R %d, M %d C %d\n"` |
| `0x0103ccf1` | `"M %d\n"` |
| `0x0103ccf7` / `0x0103ccfa` / `0x0103ccfd` | `"H\n"` / `"L\n"` / `"P\n"` |

It is a 13-entry `tbb` switch on `packet[0]` with live arms for sub-commands
**0, 8, 10, 11, 12** (1..7, 9 and the >12 default return 0):

* **0** — role/mode/BT-identity sync: stores `packet[1..3]` into the service
  state at +0/+4/+8, mirrors the ESB primary/secondary addresses when
  `packet[4] != 0xff`, `packet[4] != 0` and `packet[5]` is in `1..0xfe`, then
  sends a fixed 16-byte reply whose first halfword is `0x0101` through
  `state->send`, and clears the pending flag at `0x21000760`.
* **8** — sets `(*0x210045f4)->mode = 1` and calls `FUN_0102bbc4`.
* **10 / 11 / 12** — `FUN_0102b794` / `FUN_0102b7a0` / `FUN_0102b7ac`, three
  4-instruction setters that write 2 / 1 / 3 to the ESB radio-state word at
  `0x210005b4` ("H" high-power, "L" low-power, "P" pairing).

`FUN_0102bbc4` (0x16 B) sets the flag at `0x21004fa5`, calls
`FUN_0102b758(1)` and tail-calls `FUN_0102b900(3)`.

**Five functions were reconstructed**, all Ghidra-catalog gaps:
`FUN_0102a278`, `FUN_0102bbc4`, `FUN_0102b794`, `FUN_0102b7a0`, `FUN_0102b7ac`.

#### A.4 Proof status — what was actually run

`net_recon_kit.prove(...)` (auto-saves to `recon/net/src/`) then the CLI
verifier:

| function | `net_recon_kit.prove` | `cfg_verify.py net <name>` |
|---|---|---|
| `FUN_0102a278` | `pass=True cfg_status=PASS checked=313` | **`PASS cases=13`** |
| `FUN_0102bbc4` | `pass=True cfg_status=PASS checked=300` | `PASS` |
| `FUN_0102b794` | `pass=True cfg_status=PASS checked=300` | `PASS` |
| `FUN_0102b7a0` | `pass=True cfg_status=PASS checked=300` | `PASS` |
| `FUN_0102b7ac` | `pass=True cfg_status=PASS checked=300` | `PASS` |

`cases=13` is exactly the `tbb` table size: cfg_verify drove **every** switch
arm from the original's own jump table.

Two reviewed-ABI declarations were needed and are recorded in the sources
themselves (the sanctioned `CFG_VERIFY_CALL_ARITIES=` header directive, no
`tools/` change): `FUN_0102a278` declares arity **2** for its single indirect
call (`state->send(message, 16)`, whose scratch r2 is not an argument), and
`FUN_0102bbc4` declares **1,1** for its two one-argument callees.

**Catalog note (disclosed).** None of the five was in the Ghidra catalog. One
record per function was appended to `<net scratchpad>/net_funcs.json`
(original backed up as `net_funcs.json.i9bak`) and five durable entries were
added to `recon/catalogs/function_names_net.json` (1304 → 1309), exactly as
iteration 4/8 did for the app core. **No `tools/` logic was changed.**

#### A.5 Heeding the harness blind spot — directed fixtures + mutation controls

**First mutation run (16 deliberate defects, cfg_verify fixtures only):
11 rejected, 5 survived.** The survivors were real fixture gaps:

| surviving mutant | why it survived |
|---|---|
| reply opcode `0x101 → 0x100` | the 16-byte reply buffer is a stack object; only the pointer and the length were compared |
| secondary bound `0xfd → 0xfe` | pseudorandom packets never produce `packet[5] == 0xff` together with a live `packet[4]` |
| primary sentinel `0xff → 0xfe` | same, for `packet[4] == 0xfe` |
| dropped `*0x21000760 = 0` | the pseudorandom flag byte was never non-zero |
| log guard `>1 → >0` | the pseudorandom log level was never exactly 1 |

A directed harness (`<scratchpad>/directed9.py`, calling `parity.emu.compare`
directly — the iteration-8 `directed8.py` pattern) closes all five:

* `arg_overrides` + `absolute_memory_overrides` drive a crafted 16-byte packet,
  a fully seeded 0xd0-byte service state, the log level (0,1,2,3) and the
  pending flag (0,1);
* `call_arities=[2]` keeps the reviewed `send` ABI;
* `candidate_direct_target_map` compares the resolved call **target**;
* **`paired_stack_objects`** pairs the shipped body's reply buffer at
  entry-SP−32 with the candidate's (offset recovered from the compiled
  prologue) and compares all **16 bytes** of content.

Results: **case-0 grid 128 fixtures PASS**, **sub-command grid 32 fixtures
PASS**. Re-running the five survivors under those fixtures: **all 5 REJECTED**,
both unmutated controls PASS. Net: **16 of 16 mutants rejected.**

#### A.6 What was changed, and one displacement that came out of the diagnosis

1. **`recon/net/src/FUN_0102a720.c`** — the raw literal is replaced, under the
   existing `#ifdef G1_COHESIVE_BUILD` relocation pattern already used in the
   same file for `G1_ESB_EVENT_HANDLER`, by `&FUN_0102a278`. The canonical
   (non-cohesive) path keeps `0x0102aa79`, and `cfg_verify.py net FUN_0102a720`
   still reports **`PASS cases=5`**. Verified in the linked ELF: the literal
   word is now `0x0102be91` (= `FUN_0102a278 | 1`) and the raw value
   `0x0102aa79` no longer appears anywhere in the image.
2. **`FUN_01021a38` → `mpsl_timeslot_session_open`** (net manifest row +
   `PROVIDE` in `recon/application/net/src/stock_call_aliases.ld`, next to the
   existing `FUN_0102a0e6 = mpsl_timeslot_session_close`). Identity established
   three independent ways: the shipped call site at 0x0102b84a..0x0102b850
   passes the signal callback in r0 and a one-byte session-id out-parameter in
   r1; the reconstruction returns −22/−12 and `mpsl_timeslot.h` documents
   `-NRF_ENOMEM`; and that header documents "*If the low frequency clock is not
   running when this function is called, the function will wait until the low
   frequency clock has started*" — precisely the `FUN_01022e34 → FUN_010248d0`
   LFCLK spin. The reconstruction reads MPSL's private clock state through
   original-image absolute RAM that this build never initialises, so displacing
   it onto the archive body is the correct fix regardless of the handler pin.
   `FUN_01022e34`, `FUN_010248d0` and `FUN_01024b20` lose their only caller and
   are garbage-collected. Cost: net FLASH +1,152 B total (98.52 % → 99.02 %).
3. **Three app device pins** (§A.7).

#### A.7 Boot result — `main` unblocks and the whole peripheral bring-up runs

With only the net handler rebound (`/tmp/g1_i9c/`), `ept_cb → FUN_0102ab14 →`
**`FUN_0102a278`**, `local_ipc_service_recv` is entered **9** times instead of 3,
`main` is re-entered, and the app immediately reaches `ancs_ctx_init` and
`power_for_panel`. It then faulted in `dev_ctrl_write1` on a NULL device
pointer — the iteration-5 absolute-DATA-pin class again, now reachable for the
first time. Three pins close it (`recon/symbols/g1_app_globals.ld` +
`g1_app_symbols.h`, identified by the name string in word 0 of the original
object, ordinals re-verified against this build's `devicetree_generated.h`):

| original | name string | name | our device |
|---|---|---|---|
| `0x00087cf8` | `0x000f614f` | `"LDO1"` | `__device_dts_ord_152` |
| `0x00087d10` | `0x000f6154` | `"BUCK2"` | `__device_dts_ord_151` |
| `0x00087ce0` | `0x000f614a` | `"LDO2"` | `__device_dts_ord_153` |

Cross-checked structurally, not just by name: in the shipped image
`*(0x8b8b8+0x1c) == *(0x8b8f8+0x1c) == 0x87c80` (the pmic@6b parent), and in
our build `config(ord 152)+0x1c == config(ord 151)+0x1c == __device_dts_ord_145`
— the same `mfd` slot at the same offset. Eight symbolized sources that spelled
those addresses as literals now spell them as `&rodata_87cf8 / _87d10 / _87ce0`
(`power_for_panel`, `power_down_panel`, `enable_ship_mode`,
`power_for_imu_and_mic`, `power_down_imu_and_mic`, `display_dev_reg_config`,
`device_reg3_init_config`, `dev_read_status_bit_reg34`,
`dev_page3_config_and_readback_dump`). App FLASH and RAM are unchanged
(627,680 B / 75,757 B), so **no RAM re-shuffle**.

**103 new app functions** appear, 13 are lost (all of them RTC/timer-teardown
paths that only run later in the 0.15 s window). A representative slice of what
now runs for the first time:

`power_for_panel`, `dev_write_reg3`, `dev_ctrl_write1`,
**`i2c_nrfx_twim_transfer`** (the real Zephyr I2C driver, completing the LDO1
write end to end), `power_for_imu_and_mic`, `lsm6dso_init_chip`,
`stmemsc_i2c_write`/`_read`, `audio_codec_select_page`/`_bus_write`/
`_read_reg0x0f`, `opt3007_init_ctx_setup`, `st25dv_read_chip_ids`,
`register_imu_funsion_context`, `burial_point_record_info_init`,
`quicknote_buffer_pool_init`, `getQuickNoteDataFromFlash`,
`getDashboardStartUpModeInfofromFlash`, `getAppLanguageInfofromFlash`,
`settings_save_one`, `settings_nvs_save`, `nvs_write`, `local_store_write`,
`device_info_register_persistent_fields`, `init_dashboard_info`,
`init_ble_work_thread`, `low_speed_peripheral_dispatch_thread`,
`fuel_gauge_update`, `npm1300_charger_sample_fetch`/`_channel_get`,
`msg_queue_init`, `handle_box_placement_event`, `periodic_check_run`,
`display_dev_reg_config`, `serialization_ipc_ept_register`.

**E4 completion markers — NOT reached.** `spi_read_id` (display probe),
`panel_on`, `bt_enable`, `bt_start` and `radio TransmittedFrames` are all still
zero/absent. **E4 is not completed.**

#### A.8 New first divergence — a context switch into PC = 0

```
5,294,060  wait_for_event
5,294,069  z_tick_sleep
5,294,229  sched_switch_handle_timeout
           ... add_to_waitq_locked -> pend_locked -> z_pend_curr -> arch_swap
           -> z_arm_pendsv -> in_fp_endif -> configure_builtin_stack_guard
5,296,253  PC = 0x00000000
5,296,254  z_arm_usage_fault   ("Attempt to execute undefined instruction",
                                every register 0, xpsr 0)
```

`z_arm_pendsv` restored a thread whose saved PC is `0x00000000`: one of the
threads created just before (`init_ble_work_thread` /
`low_speed_peripheral_dispatch_thread` and their siblings) has an **unrelocated
entry-point pointer** — the same relocation class as this iteration's handler
pin and iteration 8's three app handlers, applied to the thread graph rather
than to an IPC service table. `recon/emulator/reports/thread_wiring_check.md`
is the natural starting point for iteration 10.

---

### Step B — library-displacement Batch 2 (goal G2)

See `recon/ownership/library_displacement_report.md` §"Batch 2 applied" for the
row-level ledger. Summary:

* **B2a `zephyr_drivers` (39 rows) — TRIED, REGRESSED, REVERTED.** The link
  needed five bridges; two (`dev_write_reg4 → mfd_npm1300_reg_write2`,
  `rtc_read_extended_cycle_count → z_nrf_rtc_timer_read`) were written, and
  three rows whose upstream body is `static inline` / `.constprop` with no
  linkable symbol (`dev_ctrl_write1 → i2c_write_dt`,
  `flash_page_index_lookup → linear_range_get_win_index`,
  `layout_select_region → linear_range_group_get_win_index.constprop.0`) were
  dropped. The resulting build linked clean (FLASH −96 B) but the boot
  **regressed 762 → 690 unique functions** and died on
  `ASSERTION FAIL ... nrfx_twim.c:593` (`drv_inst_idx` / transfer-length check)
  inside the displaced TWIM path, losing `power_for_imu_and_mic`,
  `lsm6dso_init_chip` and the entire peripheral bring-up. Per the
  no-regression gate the whole sub-batch, its bridge TU and its CMake line were
  reverted.
* **B2b `zephyr_kernel` (16 rows) — APPLIED, CLEAN.** 18 candidates, 2 reverted
  (`z_tick_sleep`, `unready_thread`: both file-static in `sched.c`, no linkable
  symbol). Five referenced identities are bridged in the new
  `recon/application/app/src/g1_kernel_sched_bridges.c`
  (`sched_switch_handle_timeout → z_reset_time_slice`,
  `z_ready_thread_locked → z_ready_thread`,
  `z_sched_set_prio_and_requeue → z_set_prio`,
  `z_thread_suspend → z_impl_k_thread_suspend`,
  `poll_signal_event_locked → z_impl_k_poll_signal_raise`).
  Build: exit 0, **0 undefined, 0 duplicate**. FLASH 627,680 →
  **626,416 B (−1,264 B)**; RAM unchanged, so **no RAM re-shuffle**.
  Boot: **760 unique functions vs Step A's 762**, ending at the identical
  divergence (PC = 0 out of `z_arm_pendsv`, same `display_dev_reg_config →
  wait_for_event` predecessor). The two absent names are
  `sched_thread_should_preempt` (itself displaced onto `sliceable`) and
  `sched_ready_queue_insert` (whose only caller was the displaced
  `z_ready_thread_locked`, so it is now garbage-collected); both are direct
  consequences of the displacement, and **zero** behaviour was lost.

BT-host candidates (102 eligible app rows) and every net-core candidate were
explicitly excluded, as were `keep_reconstructed` and
`conflicts_with_manifest_retain_row` rows.

---

### Regenerate (iteration 9)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py net FUN_0102a278     # PASS cases=13
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py net FUN_0102bbc4
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py net FUN_0102b794     # + b7a0, b7ac
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py net FUN_0102a720     # PASS cases=5
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/directed9.py                # 128 + 32 fixtures
PYTHONSAFEPATH=1 .venv/bin/python -c 'import sys;sys.path.insert(0,"<scratchpad>");import directed9;directed9.mutate()'
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
recon/application/build_cohesive.sh net /private/tmp/g1-i9c-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
recon/application/build_cohesive.sh app /private/tmp/g1-i9g-app
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i9g/trace.resc' > /tmp/g1_i9g/run.out 2>&1
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
```

Files changed:
`recon/net/src/{FUN_0102a278,FUN_0102bbc4,FUN_0102b794,FUN_0102b7a0,FUN_0102b7ac}.c`
(new, proven) + their `recon/symbolized/net/` mirrors,
`recon/net/src/FUN_0102a720.c` (cohesive-build handler relocation only),
`recon/application/net/src/stock_call_aliases.ld` (1 PROVIDE),
`recon/catalogs/function_names_net.json` (5 durable entries, 1304 → 1309),
`recon/symbols/g1_app_globals.ld` + `recon/symbols/g1_app_symbols.h`
(3 device pins), nine `recon/symbolized/app/*.c` device-address rewrites,
`recon/ownership/adoption_manifest.json` (net +1 row, app +16 rows),
`recon/generated/{net,app}_retained_sources.cmake` (regenerated by the
sanctioned generator only),
`recon/application/app/src/g1_kernel_sched_bridges.c` (new),
`recon/application/app/CMakeLists.txt` (1 TU listed),
`recon/ownership/library_displacement_report.md`.
The net scratchpad catalog gained five records (backed up as
`net_funcs.json.i9bak`). No `tools/` change, no Kconfig/`prj.conf`/devicetree
change, `armemul` untouched. Nothing committed.

---

## Iteration 10 — the message-pool RAM collision that zeroed the idle stack (Step A) + library-displacement Batch 3 (Step B)

**Headline.** Iteration 9's blocker is solved and **the app boot no longer
faults or resets**. The thread with the NULL entry was **`z_idle_threads[0]`,
the Zephyr idle thread**, and its entry pointer was never wrong: the whole
64-byte window holding its saved exception frame had been **zeroed by
`msg_queue_init`**, which memsets 20 × 436 = 8720 bytes at the pinned absolute
address `g_message_pool = 0x20007dac`. In our build that window covers six live
Zephyr objects, `z_idle_stacks` among them. Emitting the pool as a real object
and rebinding its four pins removes the fault: the app now runs the whole 0.15 s
budget cleanly (**759 unique functions, 0 resets**) and, given a longer budget,
runs to **0.2498 s** and **781 unique functions** before the next divergence.

Two further genuine defects were found, proven and fixed along the way: a
**dropped `struct i2c_msg.flags` store** in `dev_ctrl_write1` (a stack write, so
structurally invisible to the parity harness), and the **unrelocated ST25DV ops
vtable** `rodata_88a38`, whose third entry is a 6-byte Ghidra catalog gap that
was reconstructed and proven (`FUN_0007c86c`).

**E4 is still NOT complete.** `spi_read_id`, `panel_on`, `spi_master_init`,
`bt_enable`, `bt_start` are all still unreached and `radio TransmittedFrames`
is **0**. No SPI display traffic occurred, so no graphics comparison against
`display_sensor_oracle.json` was possible this iteration.

Step B applied **4 upstream units (21 rows)** and **reverted 1 unit (3 rows)**;
FLASH delta **0 B** — the excluded reconstructions were already
garbage-collected, so the linked image is **byte-identical** (see §B.3, which
also corrects the method for finding rows that can still change the image).

Final artifacts: app `/private/tmp/g1-b3f-app` (byte-identical to the Step A
build `/private/tmp/g1-i10v-app`), net `/private/tmp/g1-i9c-net` (unchanged
from iteration 9 — the net core was not rebuilt this iteration). Traces
`/tmp/g1_i10a/` (iteration-9 baseline reproduced), `/tmp/g1_i10b/`,
`/tmp/g1_i10w/` (final, 0.15 s), `/tmp/g1_i10x/` (final, 0.6 s).

### Measurements

All rows below are **execution-traced** runs at the same `.resc`, quantum and
RNG seed as iterations 1–9, so they are directly comparable to the baseline and
to `golden_boot_trace.json`.

| metric | iteration 9 (reproduced) | **iter 10 final** |
|---|---:|---:|
| app instructions in 0.15 s | 5,612,329 (fatal reset at 0.048 s) | **5,360,315 (no reset)** |
| app unique functions in 0.15 s | 760 (18 of them the fault/panic path) | **759** |
| app unique functions at first fault | 760 @ 0.048 s | **781 @ 0.2498 s** |
| net instructions in 0.15 s | 289,451 | **290,688** |
| net unique functions | 420 | **432** |
| app resets in 0.15 s | 1 | **0** |
| `radio TransmittedFrames` | 0 | 0 |
| app FLASH | 626,416 B (63.76 %) | **626,444 B (63.76 %)** |
| app RAM | 75,757 B (16.81 %) | **84,477 B (18.75 %)** |
| net FLASH / RAM | 229,161 B (99.02 %) / 54,140 B | unchanged (net not rebuilt) |

Function-set diff vs the baseline: **18 lost, 17 gained**. All 18 lost are the
fault/panic path itself (`z_arm_usage_fault`, `z_arm_fault`, `z_fatal_error`,
`usage_fault.constprop.0`, `panic`, `sys_arch_reboot`, `k_sys_fatal_error_handler`,
`z_impl_log_panic`, `log_source_name_get`, `k_thread_name_get`, `print_formatted`,
`newline_print`, `is_ptr`, `z_log_get_tag`, `z_impl_k_timer_stop`,
`z_unpend1_no_timeout`, `?`) — i.e. they are gone *because the fault is gone*.
The 17 gained are the RTC/timer/scheduler paths that only run once the boot
survives past 0.048 s (`rtc_nrf_isr`, `rtc_cb`, `sys_clock_announce`,
`sys_clock_timeout_handler`, `z_thread_timeout`, `z_time_slice`,
`z_sched_wake_thread`, `z_timer_expiration_handler`, `z_impl_k_uptime_ticks`,
`z_nrf_rtc_timer_chan_free`, `nrfx_dppi_channel_free`, `nrfx_flag32_free`,
`nrfx_gppi_*`) **plus `dev_reg_modify_bits` and `app_msleep_thunk_a`**, which
are new real work unlocked by the `dev_ctrl_write1` defect fix (§A.3). Net gains
12 functions and loses none.

Both links: `nm -u` = **0** undefined, **0** duplicate globals. No
`--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change; `armemul`
untouched (only extra `.resc` files under `/tmp`). Nothing committed.

**Honest note on measurement regime.** Traced and untraced runs are *not*
comparable and this iteration is the first to quantify it. Renode's execution
tracer (and `AddHook`s) defeat the WFI halt, so a traced run executes ~117 MIPS
of virtual time while an untraced one executes ~9.6 MIPS once the system starts
idling. The same final image reaches 5,360,315 instructions at 0.15 s traced and
4,801,090 instructions at 0.5 s untraced — the *same execution point*. All
iteration 1–10 numbers, and the golden oracle, are traced runs, so the table
above is internally consistent; but hooks also perturb *scheduling* enough to
move divergences (§A.6), so every diagnostic hook result in this report is
labelled as such.

---

### Step A

#### A.1 Which thread had the NULL entry, and why it was not a thread-entry pin

A Renode hook on `z_impl_k_thread_create` (0x6cfdc) and on `z_setup_new_thread`
(0x6cf28) captured every thread the app creates, and a second hook on
`z_arm_pendsv`'s exception return (0x4d9e4) printed the restored frame whenever
its stacked PC was 0. On the iteration-9 build `/private/tmp/g1-i9g-app`:

```
SETUP thread=20004948 stack=20008e00 size=16384 entry=0006c929   (z_main_thread)
SETUP thread=20004870 stack=20008cc0 size=320   entry=0006d1b9   (z_idle_threads[0])
TCREATE thread=20003460 stack=20006e10 size=2048 entry=0004be9d  (logging_thread)
TCREATE thread=20004a20 ... 20003fd0 ... 20003e50 ... 20003358    (work queues)
SWITCH0 thread=20004870 psp=20008dd0 r0..r3=0 lr=0 pc=00000000
```

The faulting thread is **`z_idle_threads[0]` (0x20004870)** — created by the
kernel, not by any recovered `k_thread_create`, so this is **not** the
`ADDR_*_THUMB` / unrebound-pin class that iteration 9 predicted. Its initial
frame had been written correctly:

```
FR00 pc=0004da10 val=0006d1b9   (arch_new_thread: r0 slot = idle entry)
FRPC pc=0004da28 val=00077468   (arch_new_thread: PC slot = z_thread_entry)
PSPW pc=0004da44 val=20008de0   (arch_new_thread: callee_saved.psp)
PSPW pc=0004d96c val=20008dd0   (z_arm_pendsv saved PSP after the HW push)
```

but at the moment of the switch the **whole window 0x20008dc0..0x20008e00 read
zero**, so the restored PC was 0 and the CPU took "Attempt to execute undefined
instruction" → `z_fatal_error` → SYSRESETREQ at 0.048 s.

#### A.2 Root cause — `g_message_pool`, an 8.5 KiB absolute RAM pin

A byte-width write watchpoint on the stacked-PC slot found the writer
(doubleword watchpoints missed it — `memset` stores bytes):

```
B  pc=0007f22c val=00        (= memset+0xa)
MEMSET dst=20008d00 len=436 val=0 lr=0002d479   (= msg_queue_init+0x1c)
```

`msg_queue_init` (original 0x33c5c) clears the message pool with 20 iterations
of `memset_bytes(p, 0, 0x1b4)` starting at `g_message_pool`, i.e. the original
absolute range **0x20007dac .. 0x20009fbc** (20 × 436 = 8720 B). The pin ledger
brackets it exactly: the next pinned global is `g_whitelist_app_parse_buf` at
0x20009fbc, and the only three other pins inside are the pool's own interior
views (`g_notif_app_pkg_table_buf` = pool+0x10,
`g_message_table_mirror` = pool+0x1108 = slot 10,
`g_message_table_mirror_ovfl_slot` = pool+0x205c = slot 19).

In our build that 8.5 KiB window covers **six live Zephyr objects**:
`smp_work_queue_stack`, `bt_lw_stack_area`, `_k_mem_slab_buf_chan_slab`,
`z_interrupt_stacks`, `z_idle_stacks` and `z_main_stack`. This is the
absolute-RAM-pin collision class of iterations 6/7, at the largest scale seen so
far.

**Fix** (the established mechanism): the pool is emitted as one real
zero-initialised object, `g1_message_pool[20 * 436]` in
`recon/application/app/src/g1_app_ram_relocs.c` (group 3), and all four pins are
rebound onto it at their original relative offsets in
`recon/symbols/g1_app_globals.ld`. It is `.bss` in the shipped image too (the
image's `.data` ends at 0x20003e29), so zeroed storage reproduces it exactly.
No canonical parity body changed. App RAM 75,757 → 84,477 B (+8,720, exactly the
pool).

**Result (build `/private/tmp/g1-i10b-app`): the fault is gone.** The app runs
the full 0.15 s with 0 resets, 5,405,138 instructions and 757 unique functions.

#### A.3 Second defect — `dev_ctrl_write1` dropped `struct i2c_msg.flags`

With the reset gone the boot reached a new failure at 0.0455 s:

```
ASSERTION FAIL [... (p_instance->drv_inst_idx == NRFX_TWIM1_INST_IDX) && ...]
  @ WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c:593
path: main -> power_for_panel -> dev_write_reg3 -> dev_ctrl_write1
      -> i2c_nrfx_twim_transfer -> nrfx_twim_xfer
```

— the **same assertion that killed library-displacement Batch 2a**, which makes
this a useful cross-check on that failure too.

`dev_ctrl_write1` (original 0x83d60) is Zephyr's `i2c_write_dt`. Its original
Thumb is 32 bytes:

```
83d64  strd   r1, r2, [sp, #4]     ; msg.buf, msg.len
83d68  movs   r2, #2
83d6e  strb.w r2, [sp, #0xc]       ; msg.flags = 2  (I2C_MSG_WRITE|I2C_MSG_STOP)
83d74  add    r1, sp, #4           ; &msg
83d78  movs   r2, #1               ; num_msgs
83d7a  blx    r4                   ; api->transfer
```

The reconstruction declared only `local_14`/`uStack_10` (buf, len) and **never
wrote the flags byte**, so `i2c_nrfx_twim_transfer` read whatever the stack
happened to hold. This is a textbook instance of the documented harness blind
spot: `tools/parity` compares the *non-stack* memory-write trace, and the
message is a stack object, so both `emu.compare` and `cfg_verify` are
structurally incapable of seeing the missing store. It passed "300/300 PROVEN".

**This is a PROVEN defect**, so the canonical body was changed (the only
canonical change this iteration): `recon/app/src/FUN_00083d60.c` plus its
`recon/verified/src`, `recon/named` and `recon/symbolized/app` mirrors now
declare `struct { unsigned int buf; unsigned int len; unsigned char flags; }`
and set `msg.flags = 2`. `tools/cfg_verify.py app dev_ctrl_write1` → **PASS
cases=0** — reported honestly: cases=0 because the body is straight-line, and
the verifier is blind to the fixed store in *both* directions. The evidence is
the original disassembly above and the boot: the nrfx assertion disappears and
`dev_reg_modify_bits` runs for the first time.

#### A.4 Third defect — the unrelocated ST25DV ops vtable (`rodata_88a38`)

`serialization_ipc_ept_register` (0x259d4 — a mis-named identity: it is the
ST25DV/NFC EEPROM bring-up, not an IPC registrar) stores `&rodata_88a38` into
the ST25DV descriptor's +8 slot, and `st25dv_read_chip_ids` (0x25290) then calls
the table's third entry through `(*(void (**)(void))(*(int *)(desc + 8) + 8))()`.

`rodata_88a38` was a bare `PROVIDE(... = 0x00088a38)`. The pin ledger brackets
the table exactly (next pin `rodata_88a44`), so it is 12 bytes = three
**original-image Thumb function pointers**, read out of `app_update.bin`:

| word | value | identity |
|---|---|---|
| 0x88a38 | 0x00025789 | `ipc_send_len_prefixed_packet_locked_retry` (0x25788) |
| 0x88a3c | 0x000256dd | `ipc_ept_op_a_locked_retry` (0x256dc) |
| 0x88a40 | 0x0007c86d | **Ghidra catalog gap** at 0x7c86c |

In the rebuilt image 0x88a38 holds an unrelated string, so the indirect call
jumped to garbage (measured: usage fault "Illegal use of the EPSR" at
`st25dv_read_chip_ids+0x3a`). Both the table address **and** its contents have to
relocate, so — exactly like iteration 5's `gpio_dt_spec` tables — the table is
**emitted**: `recon/application/app/src/g1_st25dv_ops_table.c`, with
`PROVIDE(rodata_88a38 = g1_st25dv_ops_table)`.

**`FUN_0007c86c` reconstructed and proven.** The Ghidra catalog stops
`FUN_0007c85e` (`ipc_transport_ops_dispatch`) at 0x7c86c and resumes at the thunk
0x7c872, leaving 6 unowned bytes:

```
7c86c  ldr r3, [r0, #4]      ; descriptor->i2c_spec
7c86e  ldr r0, [r3, #0xc]    ; spec[12]  (= 0x1000, set by 0x259d4)
7c870  bx  lr
```

`recon_kit.prove(0x7c86c, 6, "FUN_0007c86c", ...)` → **`pass=True checked=300
cfg_status=PASS`**; `tools/cfg_verify.py app FUN_0007c86c` → **`PASS cases=0`**
(honest: the body is straight-line, so there is no branch or switch selector for
the CFG verifier to drive; the 300 random trials plus a byte-for-byte read of
the three instructions are the whole evidence).

**Catalog note (disclosed).** One record was appended to the scratchpad
`app_funcs.json` and `classified.json` (originals backed up as
`*.i10bak`) and one durable entry added to
`recon/catalogs/function_names_app.json` (2512 → 2513), exactly as iterations
4/8/9 did. New sources `recon/app/src/FUN_0007c86c.c` and its
`recon/symbolized/app/` mirror; `tools/gen_retained_sources.py` regenerated the
list (`--check` passes). **No `tools/` logic was changed.**

Both A.4 changes are FLASH-only (+28 B) and shift no RAM.

#### A.5 What was diagnosed but could NOT be landed — the ST25DV `i2c_dt_spec`

The next divergence after A.3/A.4 is fully root-caused and is recorded here so
iteration 11 does not have to re-derive it.

At 0.2498 s the boot takes a usage fault "Illegal use of the EPSR" at
`ipc_transport_ops_dispatch+0xc` (`bx ip`, `ip = 0`), reached through
`periodic_check_run → handle_box_placement_event → st25dv_mailbox_set_enabled →
read_bool_attr_0x2004 → ipc_send_len_prefixed_packet_locked_retry →
ipc_send_len_prefixed_packet → ipc_transport_ops_dispatch`. Despite the names,
that dispatch is **`i2c_transfer`**: it loads `dev->api` (+8) and
`api->transfer` (+8) and tail-calls it. `dev` came from
`*(u32 *)&g_st25dv_i2c_dev` (0x200023cc) **== 0**.

`g_st25dv_i2c_dev` is `.data` in the shipped image. Its load image is at flash
`0xf6d64 + 0x23cc = 0xf9130` and reads `{ .bus = 0x00087c68, .addr = 0x53 }`;
0x87c68's name string is **"i2c@9000"** and its config word 0 is 0x50009000, so
the bus is **i2c1** — which matches `armemul/platforms/nrf5340.repl`, where
`st25dv: Sensors.ST_ST25DV @ twim1 0x53`. The recovered code never writes word 0,
and in our build 0x200023cc is inside `fdtable`, so the bus pointer reads 0.

Two more pins of the same object are inside live objects
(`g_st25dv_i2c_cfg` 0x20007a48 inside `cancel`, `g_eeprom_comm_mutex`
0x20007a60 inside `sc_restore_params`), and `g_st25dv_dev` (0x20007a44) is
inside `smp_work_queue_stack` — `st25dv_read_chip_ids` stores the descriptor
there, `k_sleep(0x290)`s, then reloads it, and the work queue overwrites it in
between.

**The fix was written and measured, and it regressed, so it was REVERTED.**
Sequence, all measured:

| build | change on top of the message-pool fix | 0.15 s traced result |
|---|---|---|
| `g1-i10b-app` | (message pool only) | 5,405,138 instr / **757** fns, 0 resets |
| `g1-i10e/g/j-app` | + emit `g_st25dv_i2c_dev` (bus = `DEVICE_DT_GET(i2c1)`), `g_st25dv_i2c_cfg`, `g_eeprom_comm_mutex`; + ops table; + flags fix | fault moves to `st25dv_read_chip_ids+0x3a` (g_st25dv_dev still pinned in a live stack) |
| `g1-i10m-app` | + relocate the whole 74-pin run 0x200079a0..0x20007dac as one block | **603** fns — `main → sett_init → settings_subsys_init → k_mutex_lock` pends forever; RAM moved `settings_lock` (a *strong* pin at 0x20003868 in `g1_app_sdk_state.ld`) from inside `buf32` into `backend_data_0` |
| `g1-i10r/t-app` | + emit `settings_lock` as `K_MUTEX_DEFINE` (+20 B RAM) | **331** fns — `qspi_lock → k_sem_take` hits `z_spin_lock_valid` at `sem.c:114` and panics at 0.0001 s |

Every one of those changes is *individually correct*; the boot is simply so
sensitive to RAM layout that a **24-byte** shift moved a different pin into a
different live object each time. Under the no-regression gate all of them were
reverted, leaving only the message-pool relocation (which strictly improves) and
the two FLASH-only fixes.

A durable, measured lesson came out of the attempt and is recorded in the code:
**a linker-script `PROVIDE(name = block + off)` does NOT root `block` against
`--gc-sections`.** The first cluster-block build silently discarded
`.bss.g1_ram_block_79a0` and every one of the 74 pins resolved against a base of
**0** (`nm`: `00000000 A g_file_msg_pipe`, `000000a4 A g_st25dv_dev`). The
emitted relocation objects therefore now carry
`__attribute__((used, retain))` (SHF_GNU_RETAIN), which is why
`g1_message_pool` and `g1_st25dv_ops_table` are safe.

**Quantified for iteration 11:** in the final image **543 of 721 RAM pins land
inside a live object, 163 of them inside a thread stack** (measured on
`/private/tmp/g1-b3f-app` with `nm -nS` against the pin ledger). Chasing them one
fatal boot at a time does not converge. The structural options are (a) relocate
*all* RAM pins into one arena in a single step (so no intermediate layout is
ever exercised), or (b) reserve the pinned ranges from Zephyr's allocator. Both
are iteration-11 design work, not a first-divergence fix.

#### A.6 Diagnostic-perturbation caveat (new, and important)

Renode `AddHook`s split translation blocks and change interrupt interleaving
enough to move divergences. Measured on the identical build
`/private/tmp/g1-i10m-app`: with four marker hooks it usage-faults at 0.0656 s;
with execution tracing it reaches 0.07 s with neither the fault nor
`st25dv_read_chip_ids` in the trace at all; with three argument-printing hooks
it runs 0.05 s with no reset. Consequence for method: **hooks are for finding
values, never for measuring progress.** All headline numbers in this report come
from the standard traced run with no `AddHook`s.

#### A.7 New first divergence

```
0.2498 s  USAGE FAULT "Illegal use of the EPSR"
          pc = 0x00074a72 = ipc_transport_ops_dispatch+0xc  (bx ip, ip = 0)
          lr = 0x00021833, current thread 0x20004948 (z_main_thread)
```
Root cause, fix and the RAM-layout obstacle are §A.5.

**E4 completion markers — NOT reached.** `spi_read_id`, `panel_on`,
`spi_master_init`, `bt_enable`, `bt_start` and `display_thread_handler` are all
absent from the 0.6 s trace, and `radio TransmittedFrames` is **0**. **E4 is not
completed.** No SPI traffic reached the JBD panel model, so no comparison
against `display_sensor_oracle.json` was possible.

---

### Step B — library-displacement Batch 3 (goal G2)

See `recon/ownership/library_displacement_report.md` §"Batch 3 applied" for the
per-unit ledger. Summary: **4 units applied (21 rows), 1 unit reverted (3 rows),
FLASH delta 0 B, linked image byte-identical to the Step A build** (both
`md5 f10f2fbd3a53e29c1d3a74c9c1113080`), so boot no-regression is proven by
image identity rather than by a re-run.

---

### Regenerate (iteration 10)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app FUN_0007c86c    # PASS cases=0
PYTHONSAFEPATH=1 .venv/bin/python tools/cfg_verify.py app dev_ctrl_write1 # PASS cases=0
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
recon/application/build_cohesive.sh app /private/tmp/g1-b3f-app
# net is unchanged from iteration 9: /private/tmp/g1-i9c-net
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i10w/trace.resc' > /tmp/g1_i10w/run.out 2>&1
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
```

Files changed:
`recon/application/app/src/g1_app_ram_relocs.c` (group 3: `g1_message_pool`),
`recon/application/app/src/g1_st25dv_ops_table.c` (new),
`recon/application/app/CMakeLists.txt` (1 TU listed),
`recon/symbols/g1_app_globals.ld` (4 message-pool pins + `rodata_88a38`),
`recon/app/src/FUN_00083d60.c` + `recon/verified/src/FUN_00083d60.c` +
`recon/named/dev_ctrl_write1.c` + `recon/symbolized/app/dev_ctrl_write1.c`
(the proven `i2c_msg.flags` defect),
`recon/app/src/FUN_0007c86c.c` + `recon/symbolized/app/FUN_0007c86c.c` (new,
proven), `recon/catalogs/function_names_app.json` (+1 durable entry),
`recon/ownership/adoption_manifest.json` (+21 rows),
`recon/generated/app_retained_sources.cmake` (regenerated by the sanctioned
generator only), `recon/ownership/library_displacement_report.md`.
The app scratchpad catalog gained one record (backed up as
`app_funcs.json.i10bak` / `classified.json.i10bak`). No `tools/` change, no
Kconfig / `prj.conf` / devicetree change, `armemul` untouched. Nothing committed.

---

## Iteration 11 (structural RAM-pin pass)

**Headline.** The absolute-RAM-pin defect class is **closed structurally, in one
pass**. Every recovered RAM pin that lies inside the linked RAM region
(0x20002000 .. 0x20070000) now resolves *relative to a real linked object* —
680 of them to a single 0x27000-byte arena that reproduces the original
relative layout, 24 to the SDK objects they are genuinely interior views of
(`bt_dev`, `fdtable`), 1 to a newly emitted initialised object. Only 22 pins
remain literal, and all 22 are physically outside the linked RAM region, so no
linked object can ever occupy them. A mechanical checker
(`recon/emulator/scripts/check_ram_pin_collisions.py`) proves the property on
the linked ELF: **0 raw literal pins inside a live object, 0 rebinds escaping
their owner**. Run against the iteration-10 image with the pre-pass linker
scripts the same checker reports **472 colliding pins, 117 of them inside a
thread stack** (that counts the 649 pins that actually survive as absolute
symbols; scoring all 721 ledger literals against the same object map — including
the 72 whose names a real object strongly defines, so their PROVIDE is inert —
gives **545 / 163**, which is the figure iteration 10 §A.5 quoted).

The boot improves on every axis and **regresses on none**:

| metric | iter 10 baseline `/private/tmp/g1-b3f-app` | **iter 11 `/private/tmp/g1-i11c-app`** |
|---|---:|---:|
| app instr @0.15 s | 5,360,315 | **6,011,048** |
| app unique fns @0.15 s | 759 | **768** (3 lost, 12 gained) |
| app resets @0.15 s | 0 | **0** |
| app @0.6 s | 5,715,450 / 781, **fatal reset @0.2498 s** | **6,104,274 / 808, no fault, no reset** |
| app @2.0 s | (not run; baseline resets first) | **6,239,878 / 816, no fault, no reset** |
| net @0.15 s | 290,688 / 432 | **290,688 / 432** (identical) |
| net @0.6 s / @2.0 s | 290,688 / 432 | **302,962 / 452** and **369,627 / 465** |
| `radio TransmittedFrames` | 0 | 0 |
| app FLASH | 626,444 B (63.76 %) | **626,452 B (63.76 %)**, +8 B |
| app RAM | 84,477 B (18.75 %) | **244,229 B (54.21 %)**, +159,752 B |

The function set at 0.6 s is a **strict superset** of the baseline's non-fault
set: 47 gained, and the only 20 "lost" are the fault/panic path itself
(`z_arm_usage_fault`, `z_arm_fault`, `z_fatal_error`, `panic`, `sys_arch_reboot`,
`z_impl_log_panic`, …) — gone because the fault is gone.

**E4 is still NOT complete.** `spi_read_id`, `panel_on`, `spi_master_init`,
`bt_enable`, `bt_start`, `master_display_thread` and `display_thread_handler`
are all absent from the 2.0 s trace, and `radio TransmittedFrames` is **0**. No
SPI traffic reached the JBD panel model, so no comparison against
`display_sensor_oracle.json` was possible. The reason is now **fully diagnosed
and is a different defect class** — see §11.6.

Both links: `nm -u` = **0** undefined, **0** duplicate globals. No
`--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change, no canonical
`recon/app/src` body changed; `armemul` untouched. Nothing committed.
Net core not rebuilt (`/private/tmp/g1-i9c-net`, unchanged since iteration 9).

### 11.1 Why a structural pass, and what "structural" means here

Iteration 10 §A.5 measured the failure mode of first-divergence chasing: three
*individually correct* fixes each shifted RAM and pushed a *different* pin into
a *different* live object (759 → 603 → 331 unique functions). The class cannot
be retired pin by pin because every fix perturbs the layout the remaining pins
depend on.

The linked RAM region of this build is **0x20002000 .. 0x20070000**
(`zephyr.map`, "Memory region RAM"), and the highest recovered RAM pin below
its end is `g_display_thread_stack_buf` at **0x20028e68**. So one object of
**0x27000 bytes** covers every in-region pin:

```c
unsigned char g1_ram_arena[0x27000] __aligned(32) __attribute__((used, retain));
```

and each pin becomes

```
PROVIDE(name = g1_ram_arena + (original_address - 0x20002000));
```

Three properties follow, and they are the whole point:

1. **No recovered global can overlap a Zephyr/driver object ever again** — the
   entire recovered RAM image lives inside one linker-allocated object.
2. **All original relative distances are preserved exactly.** Interior views
   (pool slot N, struct field +off) and multi-object sweeps such as
   `msg_queue_init`'s 20 × 436-byte memset stay inside the arena by
   construction. `g_ble_work_thread_stack` (original 0x2001e968, 0x3000 B) and
   its top pin 0x20021968 keep their exact original 12 KiB separation.
3. **A later RAM shift is harmless** — the pins move *with* the arena, so the
   next iteration's changes cannot resurrect the class.

Sizing is deliberately the **full original span**, not a per-object estimate:
over-sizing costs dead `.bss`, under-sizing costs a corruption. Arena base
0x200030a0 ≡ 0 (mod 32) and the origin 0x20002000 ≡ 0 (mod 32), so every
original offset keeps its alignment up to 32 bytes.

`used, retain` is mandatory — iteration 10 measured a sibling block being
silently discarded by `--gc-sections`, after which every `PROVIDE(x = block +
off)` resolved against a base of 0.

### 11.2 Pin counts by class

The ledger is 721 literal `PROVIDE(name = 0x2000….)` records in
`recon/symbols/g1_app_globals.ld` plus 6 **strong** assignments in
`recon/symbols/g1_app_sdk_state.ld` (4 settings-subsystem, 2 fdtable) = **727
records**, of which the strong settings four are also RAM pins.

| class | count | treatment | evidence |
|---|---:|---|---|
| **(a) recovered-owned RAM** | **680** | `g1_ram_arena + off` | the address is not inside any SDK object at its *original* base; the shipped `.data` ends at 0x20003e29 so all pins ≥ that were `.bss` in the original too and zeroed storage reproduces them exactly |
| **(a′) recovered-owned, needs an initialiser** | **1** | emitted object `g1_st25dv_i2c_dev` | §11.3 |
| **(b) interior of a live SDK object** | **24** | `bt_dev + off` (20), `fdtable` / `fdtable + 8` (4) | §11.4 |
| **(d) outside the linked RAM region** | **22** | left literal | 0x20000000, 0x20000800 (below region start); 0x20070000 `__kernel_ram_end`; 0x2007fc00..0x2007fc70 (18 `g_all_static_info` / `g_dashboard_startup_mode_info_*` words, at/above region end) — no linked object can occupy them |

Objects **emitted** this iteration: `g1_ram_arena` (0x27000 B) and
`g1_st25dv_i2c_dev` (8 B). Objects **bound to an SDK owner**: 24 pins onto
`bt_dev` and `fdtable`. Objects **left literal**: 22.

The four previously emitted relocation objects (`g1_message_pool`,
`g1_app_event_processor_work`, the group-1 log-stack scalars, the IPC
serialization objects) were **left as they are** — they already carry
initialisers or proven storage, and minimum churn keeps the bisect honest.
Their arena slots are simply unused.

Note on the 682 → 680 correction: `g_fdtable_entries` / `g_fdtable_refcount_field`
were first rewritten to the arena by the bulk pass and then re-bound to
`fdtable` / `fdtable + 8`, because `g1_app_sdk_state.ld` already owns them with
a *strong* assignment that always wins over a PROVIDE. The checker caught the
inconsistency (it flagged the pin as "bound but escaping its owner"), which is
exactly what that check is for.

### 11.3 Class (a′) — the ST25DV `i2c_dt_spec`, the one pin that needed contents

Iteration 10 §A.5 root-caused the then-first divergence to
`g_st25dv_i2c_dev` (original 0x200023cc) reading a NULL bus pointer. It is
`.data` in the shipped image: load image at flash `0xf6d64 + 0x23cc = 0xf9130`
reads `{ .bus = 0x00087c68, .addr = 0x53 }`, and 0x87c68's name string is
`"i2c@9000"` with config word 0 = 0x50009000, i.e. **i2c1** — matching
`armemul/platforms/nrf5340.repl`, where `st25dv` sits on `twim1` at 0x53. No
recovered function writes word 0, so a zeroed arena slot would reproduce the
same fault. It is therefore emitted with its real initialiser:

```c
struct i2c_dt_spec g1_st25dv_i2c_dev __attribute__((used, retain)) = {
	.bus = DEVICE_DT_GET(DT_NODELABEL(i2c1)), .addr = 0x53,
};
```

Its two siblings from iteration 10 (`g_st25dv_i2c_cfg` 0x20007a48,
`g_eeprom_comm_mutex` 0x20007a60) and `g_st25dv_dev` (0x20007a44) are all above
the shipped `.data` end, i.e. `.bss` in the original, so the zeroed arena is
the faithful reproduction and no emission is needed. Iteration 10 had to emit
them only because they collided with `cancel` / `sc_restore_params` /
`smp_work_queue_stack`; the arena removes the collision instead.

**Measured effect:** the ST25DV/NFC path runs for the first time
(`ipc_transport_ops_dispatch`, `st25dv_ipc_request`,
`st25dv_ipc_request_chip_ids`, `st25dv_ipc_send_byte`,
`st25dv_mailbox_send_id_pair`, `st25dv_write_control_and_ack`,
`nfc_ipc_send_op20`, `adc_nfc_init/run`), and iteration 10's §A.7 usage fault
at `ipc_transport_ops_dispatch+0xc` is gone.

### 11.4 Class (b) — the pins that are genuinely SDK interior views

`bt_dev`'s **original** base is 0x20002000 with size 0x170 (proven in
`recon/wiring/GAPS.md`: `rx_queue` is `bt_dev + 0x144`, the receive work is at
0x20002980, the identity table and controller state span the block). Every pin
in [0x20002000, 0x20002170) is therefore a `bt_dev` field, and the naming is
independently coherent — `g_ble_dev_state` (+0), `g_bt_le_legacy_adv` (+0x18),
`g_ble_dev_ncmd_sem` (+0xd4), `g_ble_dev_le_pkts_sem` (+0x108),
`g_bt_hci_recv_fifo` (+0x144, = `rx_queue`), `hci_cmd_pool` (+0x14c),
`g_bt_dev_name` (+0x16c). All 20 are now `PROVIDE(name = bt_dev + off)`, which
is *identical to today's behaviour* while `bt_dev` happens to sit at
0x20002000 and *strictly better* the moment it moves. `fdtable`'s two pins keep
the strong ownership `g1_app_sdk_state.ld` already established.

**Class (b) is deliberately small, and this is a limitation, not an oversight.**
A linker script can only reference **global** symbols, and almost every other
candidate SDK owner in this build is a file-local static: `m_data` (nrfx ADC,
`d`), `m_cb` (7 distinct nrfx statics, `b`/`d`), `db_hash`, `gatt_sc`,
`gatt_delayed_store`, `impure_data`, `__global_locale`. Three pins with
unambiguous ADC naming (`adc_context` @ m_data+0x20, `g_adc_context_lock`
@ +0x60, `g_adc_saadc_ctrl_mutex` @ +0x78) and four with unambiguous nrfx-GPIOTE
naming (`g_gpiote_cb` at the proven original `m_cb` base 0x20002bc0,
`g_gpiote_lock`/`g_nrfx_gpiote_channels_mask` at +0x70/+0x74) are almost
certainly class (b) but **cannot be bound without globalising the static**
(the `--globalize-symbol=fdtable` precedent in `app/CMakeLists.txt`). They went
to the arena, which means the recovered accessor now uses private storage
instead of aliasing the driver's. Measured: no regression, and
`adc_nrfx_channel_setup` / `adc_nrfx_read` newly run. Recorded here as the one
known semantic risk of this pass.

### 11.5 The residual-collision check (the real deliverable)

`recon/emulator/scripts/check_ram_pin_collisions.py` reads **both** the linker
scripts (to know whether a pin is a raw hex literal or bound relative to a
symbol, and that a strong assignment beats a PROVIDE) and the **linked ELF**
(final pin values + every object's extent), then reports raw literals that land
inside a live object, raw literals outside the region, and rebinds whose offset
escapes the object they were bound to. Exit status is non-zero if either defect
exists.

On the iteration-10 image (same script, `--ld` pointed at the pre-pass scripts):
`raw_literal_pins_inside_a_live_object = 472` (117 of them inside a thread
stack), `raw_literal_pins_inside_ram_region_but_free = 152`,
`bound_pins_ok = 4`, exit status 1. Top owners `g1_message_pool` (74 foreign
pins inside the object iteration 10 emitted), `bt_lw_stack_area` (50),
`kheap__system_heap` (41), `z_main_stack` (30), `fdtable` (21), `key_pool` (21),
`bt_dev` (18), `smp_work_queue_stack` (17), `buf32` (15), `tx_meta_data` (15),
`num_complete_pool` (14), `subscriptions` (13), `z_interrupt_stacks` (10),
`z_idle_stacks` (10).

On the final image:

```
$ PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
      /private/tmp/g1-i11c-app/zephyr/zephyr.elf
elf                                           /private/tmp/g1-i11c-app/zephyr/zephyr.elf
ram_region                                    ['0x20002000', '0x20070000']
abs_ram_symbols                               649
raw_literal_pins_inside_a_live_object         0
raw_literal_pins_inside_ram_region_but_free   0
raw_literal_pins_outside_ram_region           20
bound_pins_ok                                 626
bound_pins_escaping_their_owner               0
abs_symbols_not_in_linker_scripts             3
unknown_inside_a_live_object                  0
EXIT=0
```

(649 absolute SRAM symbols = 626 bound + 20 literal-outside-region + 3 that are
not pins at all: `CONFIG_SRAM_BASE_ADDRESS`, `CONFIG_PM_SRAM_BASE`,
`__kernel_ram_end`. The ledger has 721 literal pins but only 649 survive as
absolute symbols — the other 72 names are strongly defined by a real object, so
their PROVIDE is inert.)

### 11.6 New first divergence — **the boot no longer faults; it under-runs**

There is **no fault and no reset anywhere in 2.0 s of virtual time**. `main`
completes its init, hands over to `low_speed_peripheral_dispatch_thread`, and
the periodic loop runs steadily (`periodic_check_run`, `check_work_mode`,
`check_sw0_status`, `check_disp_onboarding`, `try_enter_low_power_mode`,
`watchdog_feed_retry` → `wdt_npm1300_feed`, `refresh_box_field_timer`,
`process_box_event`, the ST25DV/NFC chain, the nPM1300 fuel gauge). Unique
functions plateau at **816** and app instructions at **6,239,878**; the golden
trace needs **7,273,380** to reach `spi_read_id` and **7,641,560** to reach
`bt_start`.

The divergence is therefore a **liveness** one: *every application worker
thread is created and none of them ever executes.* `ble_work_thread`,
`master_display_thread`, `ancs_main`, `imu_fusion_thread`,
`display_thread_handler`, `run_main_dispatch_thread` are all absent from the
2.0 s trace, while the Zephyr work-queue threads (whose `k_work_queue_start` is
displaced to stock) run normally.

**Root cause, proven against the raw disassembly (this is a NEW, different
defect class — the "lost information at a call" family, and it is the gate to
E4).** In Zephyr 3.4.99 with `CONFIG_TIMEOUT_64BIT`, `k_thread_create`'s last
parameter is a **64-bit `k_timeout_t delay`**, so AAPCS places it 8-byte
aligned at `sp+0x18` with `sp+0x14` as padding. Every original call site does
exactly that:

```
init_ble_work_thread     0x2201c   sub sp,#0x24 ; movs r2,#0; movs r3,#0; strd r2,r3,[sp,#0x18]
spawn_display_thread     0x49638   sub sp,#0x20 ; movs r2,#0; movs r3,#0; strd r2,r3,[sp,#0x18]
spawn_proxy_thread       0x47ad0   sub sp,#0x24 ; movs r2,#0; movs r3,#0; strd r2,r3,[sp,#0x18]
spawn_aging_mode_aux…    0x3304c   sub sp,#0x24 ; movs r2,#0; movs r3,#0; strd r2,r3,[sp,#0x18]
start_ancs_work_thread   0x198cc   sub sp,#0x20 ; movs r2,#0; movs r3,#0; strd r2,r3,[sp,#0x18]
start_aging_mode_thread  0x32fe8   sub sp,#0x20 ; movs r0,#0; movs r1,#0; strd r0,r1,[sp,#0x18]
spawn_flash_ops_…        0x23a54   sub sp,#0x24 ; movs r6,#0; movs r7,#0; strd r6,r7,[sp,#0x18] (x2)
k_thread_create veneer   0x7cb66   ldrd r4,r5,[sp,#0x38] ; strd r4,r5,[sp,#0x18]   (forwards its own delay)
```

Every corresponding reconstruction declares `z_impl_k_thread_create` with **8 or
9 `int` parameters** and passes at most `…, prio, options` — the 64-bit `delay`
is never passed, and the compiled frames are 0x1c bytes, so
`z_impl_k_thread_create` reads its `delay` from **beyond the caller's stack
frame**. A garbage (large/positive) delay schedules the thread's start
arbitrarily far in the future, which is exactly the observed symptom: created,
never run, no fault. Verified in the linked image, e.g. `init_ble_work_thread`
compiles to `sub sp,#28` with writes only at `sp+0,4,8,0xc,0x10`.

This is the documented harness blind spot again (`tools/parity` compares
*non-stack* writes, so neither `emu.compare` nor `cfg_verify` can see a missing
outgoing stack argument), and all of these bodies are marked "300/300 PROVEN".

**It was NOT fixed in this iteration** — it touches 8 canonical `recon/app/src`
bodies plus the `run_main_dispatch_thread` / `main_dispatch_thread_tick`
argument-order question (that veneer's reconstruction is `z_impl_k_thread_create()`
with *no* arguments, and its caller's `CREATE_DISPATCH_THREAD` macro passes
`priority` where `p2` belongs), which is a scope of its own. It is iteration
12 Step A, and the disassembly above is the whole evidence needed.

**Secondary, already fixed on the way:** at 0.2847 s the first build of this
iteration (`/private/tmp/g1-i11a-app`, arena only) usage-faulted "Illegal use of
the EPSR" at `adc_nfc_run+0x2a` (`blx r3`, r3 = 0), because `rodata_87c20` was
still a literal flash pin. Decoded from the shipped image it is the
`struct device` **"adc@e000"** (name 0xf5648; api 0x8b58c =
`{channel_setup 0x5f655, read 0x5f761, read_async 0, ref_internal 0x258 = 600 mV}`),
i.e. the SAADC, so it is rebound to `__device_dts_ord_88` — the same
data-pointer class as iterations 5/9. That is the difference between
`/private/tmp/g1-i11a-app` (804 fns, reset @0.2847 s) and the final
`/private/tmp/g1-i11c-app` (808 fns @0.6 s, 816 @2.0 s, no reset).

### 11.7 Bisect ledger (every build and boot actually run)

| build | change | 0.15 s traced | 0.6 s traced |
|---|---|---|---|
| `/private/tmp/g1-b3f-app` | iteration 10 final (baseline) | 5,360,315 / 759 / 0 resets | 5,715,450 / 781, reset @0.2498 s |
| `/private/tmp/g1-i11a-app` | + arena, + bt_dev/fdtable binds, + `g1_st25dv_i2c_dev` | 6,011,032 / **767** / 0 resets | 6,400,673 / 804, reset @0.2847 s (`adc_nfc_run+0x2a`) |
| `/private/tmp/g1-i11c-app` | + `rodata_87c20 = __device_dts_ord_88` | 6,011,048 / **768** / 0 resets | **6,104,274 / 808, no fault, no reset**; @2.0 s **6,239,878 / 816** |

0.15 s function-set diff vs baseline: **3 lost** (`encode_uint`,
`extract_decimal`, `outs` — printf helpers, a consequence of different log
content), **12 gained** (`FUN_0007c86c`, `adc_nfc_init`,
`adc_nrfx_channel_setup`, `clear_pending_state_flags`,
`ipc_ept_op_b_locked_retry`, `ipc_send_len_prefixed_packet`,
`ipc_transport_ops_dispatch`, `json_arr_encode`, `nfc_ipc_send_op20`,
`sleep_fixed_33_ticks`, `st25dv_ipc_request`, `st25dv_ipc_request_chip_ids`).
Net core identical at 0.15 s (290,688 / 432) and ahead at 0.6 s / 2.0 s.

No subset had to be reverted: both steps improved monotonically.

### Regenerate (iteration 11)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i11c-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i11c-app/zephyr/zephyr.elf          # exit 0
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
cd /Users/freedomcoder/Projects/armemul
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/tmp/g1_i11c/trace.resc' > /tmp/g1_i11c/run.out 2>&1     # 0.15 s
# 0.6 s: /tmp/g1_i11d/trace.resc   2.0 s: /tmp/g1_i11e/trace.resc
# analyze: <scratchpad>/analyze.py <nm.txt> <trace.log> <out.json>
```

Files changed:
`recon/application/app/src/g1_app_ram_relocs.c` (group 4: `g1_ram_arena`;
group 4b: `g1_st25dv_i2c_dev`),
`recon/symbols/g1_app_globals.ld` (680 arena rebinds, 20 `bt_dev` binds,
2 `fdtable` binds, 1 emitted-object bind, 1 `rodata_87c20` device rebind),
`recon/symbols/g1_app_sdk_state.ld` (the 4 strong settings assignments moved
onto the arena), new `recon/emulator/scripts/check_ram_pin_collisions.py`.
**No canonical `recon/app/src` body changed**, no `tools/` change, no
Kconfig / `prj.conf` / devicetree change, `armemul` untouched (only extra
`.resc` files under `/tmp`). Nothing committed.

## Iteration 12 — the dropped 64-bit `k_timeout_t delay` at every `k_thread_create`

**Headline.** The liveness blocker is **fixed and proven**: all nine
`k_thread_create` boundaries now pass the 64-bit `k_timeout_t delay` the
original writes at `sp+0x18`, every fixed body compiles to an
**instruction-for-instruction match of the original frame**, and the boot
changes from "16 threads created, none ever runs" to **worker threads actually
starting and executing** (`ble_work_thread` → `ancs_main` run 13 instructions
after `z_impl_k_thread_create` returns, via `z_sched_start` → `ready_thread` →
`z_reschedule` → `arch_swap`). The harness blind spot that hid this is now
closed by a new directed check,
`recon/emulator/scripts/check_thread_create_stack_args.py`, which **FAILs 8/9
sites on the pre-fix sources and PASSes 9/9 after** — the first mechanical
detector this repo has for *outgoing stack arguments*.

**E4 is still NOT reached, and the headline boot metrics REGRESSED.** Once the
threads really run, the boot panics 20 000 instructions later on a Zephyr
scheduler assertion. The panic's cause is diagnosed to a *second, independent*
misbound RAM pin (`g_current_thread_ptr`, which is `_kernel + 0x8`); rebinding
it removes the panic but exposes a *third* defect (a CC312-PAL/AES livelock),
so that rebind was **measured and REVERTED**. Honest summary: **the defect is
fixed, the boot goes functionally further and metrically backwards.**

| metric | iter 11 baseline `/private/tmp/g1-i11c-app` | **iter 12 final `/private/tmp/g1-i12d-app`** | (measured-and-reverted `g1-i12c-app`) |
|---|---:|---:|---:|
| app instr @0.15 s | 6,011,048 | **6,221,826** | 14,882,225 |
| app unique fns @0.15 s | 768 | **749** | 666 |
| app resets @0.15 s | 0 | **1 @ 0.0717 s** | 0 |
| app @2.0 s | 6,239,878 / 816, no fault, no reset | **1 reset, does not survive** | 199,631,345 instr, 0 resets, **livelocked** |
| net instr / fns @0.15 s | 290,688 / 432 | **286,515 / 420** | 282,706 / 430 |
| `radio TransmittedFrames` | 0 | **0** | 0 |
| app FLASH | 626,452 B (63.76 %) | **626,548 B (63.77 %)**, +96 B | 626,548 B |
| app RAM | 244,229 B (54.21 %) | **244,229 B (54.21 %)**, +0 B | 244,229 B |
| `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** | 0 / 0 |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** | 0 / 0, EXIT 0 |

No `--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change; `armemul`
untouched (only extra `.resc` files under `/tmp`). Nothing committed. Net core
not rebuilt (`/private/tmp/g1-i9c-net`, unchanged since iteration 9).

### 12.1 The defect, re-verified from raw bytes

`extract.read` + `arm-zephyr-eabi-objdump -b binary -M force-thumb` on
`app_update.bin`, e.g. `init_ble_work_thread` @0x2201c:

```
2201c  push {r4,r5,lr}      2203c  mvn.w r3,#14          ; prio  0xfffffff1
2201e  mov  r5,r0           22040  mov.w r2,#0x3000      ; stack_size
22020  sub  sp,#0x24        22044  strd  r3,r4,[sp,#0xc] ; prio, options
22032  movs r2,#0           22048  strd  r4,r4,[sp,#4]   ; p2, p3
22034  movs r3,#0           22050  str   r5,[sp,#0]      ; p1
22036  movs r4,#0           22054  bl    0x71eac
22038  strd r2,r3,[sp,#0x18]   <-- 64-bit k_timeout_t delay
```

Stock `z_impl_k_thread_create` (`~/ncs251/zephyr/kernel/thread.c:646`) is
`(new_thread, stack, stack_size, entry, p1, p2, p3, prio, options, k_timeout_t
delay)`; with `CONFIG_TIMEOUT_64BIT=1` (confirmed in
`zephyr/include/generated/autoconf.h`; `CONFIG_USERSPACE` absent) AAPCS puts
`delay` 8-byte aligned at `sp+0x18` with `sp+0x14` as padding, which is exactly
the frame above. Our pre-fix `init_ble_work_thread` linked to:

```
1e9e4  push {r4,r5,lr} ; 1e9e8  sub sp,#28    <-- 0x1c, not 0x24
       writes only sp+0,4,8,0xc,0x10 ; no strd at sp+0x18
```

so `z_impl_k_thread_create` read `delay` from **beyond the caller's frame**
(`sp+0x18` = the pushed `r4`, `sp+0x1c` = the pushed `lr`). `schedule_new_thread`
then took the `z_add_timeout` branch with a garbage tick count: created, never
started, no fault. That is precisely iteration 11 §11.6's diagnosis, now
confirmed byte-for-byte on both sides.

### 12.2 The nine call sites, before/after frame evidence

The candidates were compiled with the **exact cohesive-build command line**
(pulled from `compile_commands.json`) so the comparison is against real emitted
code, not an approximation. Every one is an instruction-for-instruction match of
the original; the only differences are the `orr.w r3,r3,#1` that iteration-P4's
pointer rebind adds to make an entry pointer Thumb, and literal-pool ordering.

| VA | body | original frame | pre-fix ours | post-fix ours |
|---|---|---|---|---|
| 0x2201c | `init_ble_work_thread` | `sub sp,#0x24` + `strd [sp,#0x18]` | `sub sp,#28`, no `[sp,#0x18]` | **`sub sp,#0x24` + `strd r2,r3,[sp,#24]`** |
| 0x49638 | `spawn_display_thread` | `sub sp,#0x20` + `strd [sp,#0x18]` | `sub sp,#24` | **`sub sp,#32` + `strd r2,r3,[sp,#24]`** |
| 0x47ad0 | `spawn_proxy_thread` | `sub sp,#0x24` + `strd [sp,#0x18]` | `push {r0..r3,r4,r5,r6,lr}` (28 B) | **`sub sp,#36` + `strd r2,r3,[sp,#24]`** |
| 0x3304c | `spawn_aging_mode_aux_thread` | `sub sp,#0x24` + `strd [sp,#0x18]` | 28 B frame | **`sub sp,#36` + `strd r2,r3,[sp,#24]`** |
| 0x198cc | `start_ancs_work_thread` | `sub sp,#0x20` + `strd [sp,#0x18]` | `sub sp,#24` | **`sub sp,#32` + `strd r2,r3,[sp,#24]`** |
| 0x32fe8 | `start_aging_mode_thread` | `sub sp,#0x20` + `strd r0,r1,[sp,#0x18]` | `sub sp,#24` | **`sub sp,#32` + `strd r0,r1,[sp,#24]`** |
| 0x23a54 ×2 | `spawn_flash_ops_and_brightness_threads` | `sub sp,#0x24` + `strd r6,r7,[sp,#0x18]` twice | `sub sp,#28`, neither | **`sub sp,#36` + both `strd r6,r7,[sp,#24]`** |
| 0x7cb66 | `main_dispatch_thread_tick` (veneer) | see below | **`b.w z_impl_k_thread_create`** | **exact veneer reproduced** |
| 0x2a65c | `run_main_dispatch_thread` | `sub sp,#20`, 4 outgoing words | already correct | unchanged behaviour |

**The veneer was the worst of the nine.** Its reconstruction was
`extern int z_impl_k_thread_create(void); void main_dispatch_thread_tick(void)
{ z_impl_k_thread_create(); }`, which GCC compiled to a single
`b.w z_impl_k_thread_create`. That tail call forwarded the *caller's* four-word
outgoing block verbatim, so `z_impl_k_thread_create` read
`p1=context, p2=prio, p3=0, prio=0, options=<caller's stack>, delay=<garbage>`
— i.e. **all eight dispatch threads got a corrupted argument frame**, not merely
a bad delay. The original is a genuine re-layer:

```
7cb66  push {r4,r5,lr} ; sub sp,#0x24
7cb6a  ldrd r4,r5,[sp,#0x38]   ; caller's own delay  (its sp+0x08)
7cb6e  strd r4,r5,[sp,#0x18]   ; callee delay
7cb74  ldr  r5,[sp,#0x34]      ; caller's prio       (its sp+0x04)
7cb76  str  r4,[sp,#0x10]      ; options = 0
7cb78  strd r4,r5,[sp,#0x08]   ; p3 = 0, prio
7cb7c  str  r4,[sp,#0x04]      ; p2 = 0
7cb7e  ldr  r4,[sp,#0x30]      ; caller's p1         (its sp+0x00)
7cb80  str  r4,[sp,#0x00]
7cb82  bl   0x71eac
```

so its true signature is
`(struct k_thread*, k_thread_stack_t*, size_t, k_thread_entry_t, void *p1,
int prio, k_timeout_t delay)` with `p2`, `p3` and `options` hard-coded to 0.
Written that way and compiled, GCC emits that block **instruction for
instruction, in the same order**.

**Resolution of iteration 11's argument-order question.** Iteration 11 suspected
`run_main_dispatch_thread`'s `CREATE_DISPATCH_THREAD` macro of "passing
`priority` where `p2` belongs". It does not. The original 0x2a65c uses
`sub sp,#20` and writes exactly four outgoing words —
`strd r4,r5,[sp]` (p1, prio) and `strd r6,r7,[sp,#8]` (the 64-bit delay = 0) —
which is precisely what the old 8-`uint32_t` prototype produced. `run_main_dispatch_thread`
was **already correct**; 100 % of that site's defect lived in the veneer's own
definition. The directed check confirms it independently: with `{0x7cb66: 4}`
pinned, 0x2a65c is the **only one of the nine sites that PASSed before the fix**.
Its prototype was still updated to the real `k_timeout_t` so caller and callee
agree; emitted code is unchanged apart from GCC now materialising the delay in
`r6/r7` (`movs r6,#0; movs r7,#0; strd r6,r7,[sp,#8]`) — which is what the
original does, and is closer to it than before.

**How they are written now.** Per the owner's stated direction (library types
for correctness) the build-tree bodies use the real Zephyr API:
`#include <zephyr/kernel.h>` and `k_thread_create(..., prio, 0, K_NO_WAIT)`
(plus `k_timer_init`, `k_sem_init` with their real prototypes where the same TU
declared them loosely). The syscall inline expands to a direct
`bl z_impl_k_thread_create`, so the emitted code is identical while a future
prototype mismatch becomes a compile error. One `#undef NRF_NVMC_S` is needed
per file because `g1_app_symbols.h` and nRFX's `nrf5340_application.h` both
define that macro. The **canonical `recon/app/src` bodies stay header-free**
(the parity harness compiles them standalone with stub callees), so there the
fix is the minimal, ABI-identical form: the `FUN_00071eac` prototype gains a
trailing `unsigned long long` and each call gains `, 0ULL`.

### 12.3 The new directed check — closing the blind spot

`emu.compare` keys its trace on the return register(s), the ordered *non-stack*
memory writes, and the call order with the callee's arguments — and it captures
**stack** arguments only for callees listed in `call_stack_arity_by_target`
(which `cfg_verify` feeds from `REVIEWED_TARGET_CALL_STACK_ARITIES`). There was
no reviewed entry for `z_impl_k_thread_create`, which is exactly why eight
bodies that never wrote `sp+0x18` were all "300/300 PROVEN".

`recon/emulator/scripts/check_thread_create_stack_args.py` pins
`{0x00071eac: 8}` at the eight direct sites and `{0x0007cb66: 4}` at the
veneer's caller. It reads the canonical bodies from `recon/app/src`, **changes
nothing under `tools/`** (the single cfg_verify-routed site augments that
module's reviewed dict in memory for the duration of the run), and it was
validated as *discriminating*, not merely green:

```
                       pre-fix sources        post-fix sources
FUN_0002201c   0x2201c   FAIL (60/60)             PASS (120)
FUN_00049638   0x49638   FAIL                     PASS
FUN_00047ad0   0x47ad0   FAIL                     PASS
FUN_0003304c   0x3304c   FAIL                     PASS
start_ancs_…   0x198cc   FAIL                     PASS
FUN_00032fe8   0x32fe8   FAIL                     PASS
FUN_00023a54   0x23a54   FAIL                     PASS
FUN_0007cb66   0x7cb66   FAIL                     PASS
FUN_0002a65c   0x2a65c   PASS  (already correct)  PASS
EXIT=1 (1/9)                                   EXIT=0 (9/9)
```

Three traps were found and handled while building it, and they are the reason a
naive version of this check would have been worthless:

1. **The candidate's call stubs move.** Without
   `candidate_direct_target_map=recon.LAST_DIRECT_TARGET_MAP` the candidate's
   semantic-target lookup misses, it captures **zero** stack words for every
   call, and all nine sites "FAIL" for a bookkeeping reason.
2. **Two sites never reach the call under random seeding**
   (`start_aging_mode_thread` needs `*(u8*)0x20019ef1 == 0`;
   `start_ancs_work_thread` needs `get_device_info()[0] == 2` and
   `is_battery_critical() != 1`). Both originally reported PASS *with the defect
   present*. They now carry reviewed path-forcing fixtures, and **every
   emu-routed site asserts the pinned callee was actually called** (`reached`
   column) so a never-reached PASS cannot recur.
3. **`start_ancs_work_thread` also needed reviewed register arities**
   (`get_device_info` 0, `is_battery_critical` 0, `debug_print` 0,
   `log_message` 2); with the default arity of 4 it mismatched on scratch
   registers regardless of stack arguments.

`cfg_verify` re-proof of all nine bodies after the fix: **9/9 PASS** (40 CFG
cases each, 8 for 0x2a65c), i.e. no regression in what it does cover.

### 12.4 Systematic sweep for the class

**Scope.** Rather than grep, the whole shipped `.text` was decoded for
`BL`-immediate instructions (T1 encoding, 25-bit signed displacement) and every
call to a target whose real Zephyr 3.4.99 prototype places arguments on the
stack was enumerated. Under `CONFIG_TIMEOUT_64BIT` the candidate set is small
and can be reasoned about exhaustively: a `k_timeout_t` costs two words but is
usually absorbed by `r2/r3`, so only four APIs actually spill —
`k_thread_create` (8 words), `k_pipe_put`/`k_pipe_get` (4, **not called by this
firmware**), `k_timer_start` (2) and `k_work_queue_start` (1). Everything else
in the plausible list (`k_work_schedule`, `k_work_reschedule`, `k_msgq_put/get`,
`k_sem_take`, `k_sleep`, `k_msleep`, `k_mutex_lock`, `k_poll`, `k_heap_alloc`,
`k_mem_slab_alloc`, `k_queue_get`, `k_stack_pop`, `k_thread_join`,
`k_condvar_wait`, `z_add_timeout`) passes its timeout in `r2/r3` and has **no**
outgoing stack word, so the class cannot bite there.

**Result — 26 call sites across the three live targets:**

| target | sites | verdict |
|---|---:|---|
| `z_impl_k_thread_create` @0x71eac | 13 (12 owners) | 9 fixed here; 3 in bodies **displaced to stock Zephyr** (`bt_enable` @0x54ace, `ipc_static_vrings_init` @0x4d2a4, `k_work_queue_start` @0x73180 — none retained, so the stock call sites are correct); **1 in a Ghidra catalog gap** (below) |
| `z_impl_k_timer_start` @0x75174 (2 words) | 7 | `main` (×2) and `uarte_nrfx_isr` pass with the pin; `ble_process_req_dispatch` and `main` were already in `REVIEWED_TARGET_CALL_STACK_ARITIES` with `{0x75174: 2}`; `img_mgmt_upload`, `opt3001_chip_init`, `saadc_start_read`, `z_log_msg_post_finalize` are stock-displaced or need cfg_verify context. **No defect found.** |
| `k_work_queue_start` @0x730e8 (1 word) | 5 | `ipc_rpmsg_backend_register` and `bt_settings_save_or_delete_key` PASS both with and without the pin; the rest are stock. **No defect found.** |

So the class is **confined to `k_thread_create`**, and within it to the nine
bodies fixed here — with one genuinely new finding:

**A 13th `k_thread_create` call at 0x260c2 lives in an uncatalogued function.**
Ghidra's nearest preceding symbol is `panel_level_calc_cached` (0x25ecc, size
196 → ends 0x25f90), and the next catalog entry is `update_imu_mode` (0x26100),
so the call sits in the gap [0x25f90, 0x26100). Its literals decode to
thread `0x20003fe8`, stack `0x20023568`, size 0x700, prio `mvn #10` = −11, and
**entry 0x0000fe89 = `imu_fusion_thread`**. No reconstruction owns that gap, so
**our build never creates the IMU fusion thread at all** — directly relevant to
the sensor half of the parity goal. Recovering that function is a concrete
iteration-13 item.

### 12.5 What the boot does now, and the next divergence

With the fix the scheduler behaves: `init_ble_work_thread` →
`z_impl_k_thread_create` → `z_setup_new_thread` → `z_sched_start` →
`ready_thread` → `update_cache` → `z_reschedule` → `arch_swap` → `z_arm_pendsv`
→ **`ble_work_thread` (0x1e784) executes**, calls **`ancs_main`**,
`get_device_info`, then `k_msleep`. That is the first time any application
worker thread has ever run in this project. Threads that execute: **2 of 16**
(`ble_work_thread`, `ancs_main`) — the rest are created later in `main`, past
the panic point.

**New first divergence (app), at instruction 5 929 081 / 0.0717 s:**
a `__ASSERT` inside the recovered `z_tick_sleep` (0x466e6..0x46708, sched.c line
1458) — after `z_swap` returns, `_current->base.thread_state` still has
`_THREAD_SUSPENDED` set. UART:

```
[00:00:00.071,746] <err> os: Faulting instruction address (r15/pc): 0x000779f8
[00:00:00.071,746] <err> os: >>> ZEPHYR FATAL ERROR 4: Kernel panic on CPU 0
[00:00:00.071,777] <err> os: Current thread: 0x20004e00      (= g_ble_work_thread)
```

**Root cause, proven from disassembly:** `z_tick_sleep` calls the recovered
`unready_thread` (0x4644c), whose last act is
`update_cache(*g_current_thread_ptr == thread)`. `g_current_thread_ptr` is pin
0x2000b450, which is `_kernel + 0x8` — `_kernel`'s original base is
**0x2000b448** (stated in `sched_update_cache`'s own provenance header, and
corroborated by the recovered `sched_update_cache` reading `[_kernel,#8]`
current, `[+12]` idle_thread, `[+24]` ready_q.cache, `[+28]` runq — exactly the
0x28-byte `struct z_kernel` our ELF links). Iteration 11 sent that pin to
`g1_ram_arena` instead, so the comparison reads dead storage, yields
`preempt_ok = 0`, and `sched_update_cache` takes its non-preemptible path
(`str r2,[r5,#24]` with `r2 = current`) — leaving `_kernel.ready_q.cache`
pointing at the very thread that just suspended itself. `z_arm_pendsv` switches
"to" the same thread, `z_tick_sleep` resumes with `SUSPENDED` still set, and
asserts.

### 12.6 The `_kernel` interior-pin rebind: proven correct, measured, REVERTED

A mechanical sweep (every arena pin whose original address lands inside the
extent of a real linked object whose name is itself a pin) found **4 candidates
across 12 owners**:

```
owner=_kernel  base=0x2000b448 size=0x28   g_current_thread_ptr      @0x2000b450 +0x8
owner=_kernel                              g_spinlock_validate_owner @0x2000b458 +0x10
owner=_kernel                              g_sched_ready_runq        @0x2000b464 +0x1c
owner=sc_cfg   base=0x2000ff18 size=0x24   g_bt_gatt_sc_cfg_addr_ff19@0x2000ff19 +0x1
```

`sc_cfg` was a **false positive of the sweep**: gatt.c's `sc_cfg` is a
file-local static (`nm`: `b sc_cfg`), so no linker-script reference can reach it
— the iteration-11 §11.4 class-(b) limitation. Binding to it produced an
`A sc_cfg` alias and the collision checker correctly reported
`bound_pins_escaping_their_owner = 1`. Reverted; the sweep should filter owners
to uppercase (global) `nm` classes.

The three `_kernel` binds are unambiguous. Measured individually:

| build | change | app @0.15 s | resets | notes |
|---|---|---:|---:|---|
| `/private/tmp/g1-i12a-app` | thread fix only | 6,221,826 / 749 | 1 @0.0717 s | `ble_work_thread`, `ancs_main` run |
| `/private/tmp/g1-i12d-app` | **+ `g_sched_ready_runq = _kernel+0x1c`** | 6,221,826 / 749 | 1 @0.0717 s | **byte-identical trace** to i12a → neutral, kept |
| `/private/tmp/g1-i12c-app` | + `g_current_thread_ptr`, + `g_spinlock_validate_owner` | 14,882,225 / 666 | **0** | **REVERTED** |

`g1-i12c-app` removes the panic entirely — the scheduler now preempts correctly
— but it unmasks the *next* defect and the boot never finishes `main`
(51 `main` entries vs 70). The first divergence between i12a and i12c is at
instruction 5 394 154, inside `__malloc_unlock` →
`g1_recon_retarget_lock_release_recursive` → `thunk_FUN_00072558`: with a real
`_current` that recursive lock stops short-circuiting and performs a genuine
`k_mutex_unlock`. Downstream the CC312 PAL enters a lock/AES loop that never
terminates — `ProcessAesDrv` **248 → 66,939** entries, `InitAes` **93 →
25,102**, `z_impl_k_mutex_unlock` **192 → 150,834**, `mutex_lock_platform`
**absent → 50,271**. A 2.0 s untraced run confirms a livelock: **199,631,345
instructions, 0 resets, UART silent after the boot banner** (≈99 % CPU busy vs
≈40 % for the baseline, so this is spinning, not slowness).

Per the standing rule the regressing subset was reverted. **Iteration 13 Step A
is to land `PROVIDE(g_current_thread_ptr = _kernel + 0x8)` together with a fix
for the CC312-PAL/newlib-retarget recursive-lock loop it exposes** — the two
have to move as one unit.

### 12.7 Function-set diff (0.15 s, vs iteration-11 baseline)

**Gained (24):** `ble_work_thread`, `ancs_main`, `k_msleep_ticks32768_d`
(the threads finally running) plus the whole panic path (`assert_post_action`,
`z_arm_svc`, `_oops`, `z_do_kernel_oops`, `z_arm_fatal_error`, `z_fatal_error`,
`k_sys_fatal_error_handler`, `panic`, `z_impl_log_panic`, `sys_arch_reboot`,
`is_ptr`, `k_thread_name_get`, `print_formatted`, `newline_print`,
`log_source_name_get`, `z_log_get_tag`, `encode_uint`, `extract_decimal`,
`outs`, `z_impl_k_timer_stop`, `z_unpend1_no_timeout`).

**Lost (43):** the periodic-loop and sensor tail that only executes *after*
0.0717 s — `periodic_check_run`, `low_speed_peripheral_dispatch_thread`,
`fuel_gauge_*`, `npm1300_charger_*`, `msg_queue_init`, `handle_box_placement_event`,
`display_dev_reg_config`, the `nrfx_gppi`/`nrfx_dppi` teardown, the softfloat
helpers they call. **None of these were broken; the boot simply dies earlier.**

### 12.8 E4 status and graphics-oracle comparison

**Not reached.** `spi_read_id`, `panel_on`, `spi_master_init`, `bt_enable`,
`bt_start`, `master_display_thread`, `display_thread_handler` are all absent
from the trace and `radio TransmittedFrames` is **0**. `power_for_panel` runs
(5 entries) but no SPI transaction reaches the JBD panel model, so **no
comparison against `display_sensor_oracle.json` was possible** — criteria G-5
(`0x9F`→`0x4010`, the three-band 153 600 B clear, five `0xC0` words, the
`0x46`/`0x31` brightness pairs) are all **untested, not failed**.

### Regenerate (iteration 12)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120   # EXIT=0, 9/9
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify as c;\
 [print(n, c.verify('app',n)['status']) for n in ('FUN_0002201c','FUN_00049638','FUN_00047ad0','FUN_0003304c',\
 'start_ancs_work_thread','FUN_00032fe8','FUN_00023a54','FUN_0007cb66','FUN_0002a65c')]"            # 9x PASS
recon/application/build_cohesive.sh app /private/tmp/g1-i12d-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i12d-app/zephyr/zephyr.elf                                                      # EXIT=0
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i12d /private/tmp/g1-i12d-app /private/tmp/g1-i9c-net 0.15
```

Files changed: `recon/app/src/{FUN_0002201c,FUN_00023a54,FUN_00032fe8,FUN_0003304c,
FUN_00047ad0,FUN_00049638,FUN_0007cb66,start_ancs_work_thread}.c` (canonical,
re-proven); the same nine bodies in `recon/named/` and `recon/symbolized/app/`
(the built tree, propagated by hand — `symbolize.py`'s sanctioned path is still
unavailable, its hardcoded scratchpad `symbol_map.json` being gone);
`recon/symbols/g1_app_globals.ld` (one rebind kept, two reverted with a comment,
one false positive documented); new
`recon/emulator/scripts/check_thread_create_stack_args.py`. No `tools/` change,
no Kconfig / `prj.conf` / devicetree change, `armemul` untouched. Nothing
committed.

## Iteration 13 — the paired landing (`_kernel + 0x8` + the entropy-length defect), and the IMU-fusion vtable

**Headline.** Iteration 12's paired fix is **landed and works**. The livelock it
was blocked on is root-caused to a *third* instance of the "lost information at
a call" family — `sys_rand32_get` (0x52c40) **dropped the `length = 4` register
argument** at its call to `entropy_get_entropy_isr_call` (0x52bf8), so the CC312
CTR_DRBG was asked for a garbage number of bytes. With that one word restored,
`PROVIDE(g_current_thread_ptr = _kernel + 0x8)` lands cleanly: **the 0.0717 s
kernel panic is gone, there is no livelock, and the boot survives 2.0 s of
virtual time with 822 unique functions — the best result this project has
reached** (iteration 11's no-reset baseline was 816 / 6,239,878).

Step B then reconstructed the **four uncatalogued IMU-fusion vtable functions**
(the gap that iteration 12 found the 13th `k_thread_create` in) and wired them
in. **`imu_fusion_init` and `imu_fusion_thread` now execute for the first time**,
the whole `lsm6dso_*` driver stack and the quaternion/orientation fusion math
run, and Renode logs real **LSM6DSO register traffic on twim2**. Getting there
required fixing two further latent defects that the new code path unmasked
(the `dev_ctrl_*` I²C-message family, and one more unrelocated `gpio_dt_spec`).
The final image reaches **839 unique functions at 0.15 s** but **resets once at
0.0892 s** on a *new*, precisely-located divergence (a NULL context handed to
`global_system_suspend`, whose `blx` then faults).

Both results are reported; nothing was reverted, because every change is
provably correct (cfg_verify + instruction-level frame comparison against the
shipped image) and the standing rule forbids reverting a provably-correct fix to
improve a metric.

| metric | iter 11 `g1-i11c-app` | iter 12 final `g1-i12d-app` | **iter 13 Step A `g1-i13a-app`** | **iter 13 final `g1-i13e-app`** |
|---|---:|---:|---:|---:|
| app instr @0.15 s | 6,011,048 | 6,221,826 | **6,004,916** | **6,388,996** |
| app unique fns @0.15 s | 768 | 749 | **777** | **839** |
| app resets | 0 | 1 @0.0717 s | **0** | **1 @0.0892 s** |
| app @2.0 s | 6,239,878 / 816, no reset | does not survive | **6,261,306 / 822, no reset** | 6,388,996 / 839, reset @0.0892 s |
| net instr / fns @0.15 s | 290,688 / 432 | 286,515 / 420 | **291,514 / 432** | 287,341 / 420 |
| `radio TransmittedFrames` | 0 | 0 | **0** | **0** |
| app FLASH | 626,452 B (63.76 %) | 626,548 B (63.77 %) | **626,548 B (63.77 %)** | **631,996 B (64.32 %)**, +5,448 B |
| app RAM | 244,229 B (54.21 %) | 244,229 B (54.21 %) | **244,229 B** | **244,229 B**, +0 B |
| `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | **0 / 0** | **0 / 0** |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | — | 9/9, EXIT 0 | 9/9 | **10/10, EXIT 0** |

No `--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change; `armemul`
untouched (only extra `.resc` files under `/tmp`). Nothing committed. Net core
not rebuilt (`/private/tmp/g1-i9c-net`, unchanged since iteration 9).

### 13.1 Step A — the livelock root cause: a dropped `length` at `sys_rand32_get`

Iteration 12 measured the livelock as "`ProcessAesDrv` 248 → 66,939 entries,
`mutex_lock_platform` absent → 50,271, 199,631,345 instructions in 2.0 s". Those
counters are symptoms two levels below the cause. Walking the i12c trace's
repeating cycle from the inside out gives the outermost recurring frame:

```
cc_mbedtls_ctr_drbg_random_with_add+0x162
  -> (return) nrf_cc3xx_platform_ctr_drbg_get+0x28
  -> (return) entropy_cc3xx_rng_get_entropy+0x44      <- the loop head
  -> nrf_cc3xx_platform_ctr_drbg_get  (next 1024-byte chunk)
```

`entropy_cc3xx_rng_get_entropy` (stock NCS `drivers/entropy/entropy_cc3xx.c`) is
a `while (offset < length)` loop that draws `min(length - offset, 1024)` bytes
per iteration; each 1024-byte chunk costs ~72,000 instructions because every AES
block goes through the CC312 PAL mutex dance. It is not an infinite loop — it
was simply given an enormous `length`. The i12c trace shows **125 entries**
(≈124 chunks) and still running; the golden trace never enters it at all.

Where `length` comes from, proven from the shipped bytes
(`arm-zephyr-eabi-objdump -b binary -M force-thumb` on `app_update.bin`):

```
sys_rand32_get @0x52c40
  52c68  movs r1,#4              ; length = 4
  52c6a  add.w r0,sp,r1          ; buffer = sp+4
  52c6e  bl   0x52bf8            ; entropy_get_entropy_isr_call(buf, 4)
```

and `entropy_get_entropy_isr_call` @0x52bf8 forwards both:

```
  52bfa  mov r3,r0 ; 52bfe mov r2,r1     ; save buf, len
  52c20  mov r1,r3 ; ldmia.w sp!,{r4,lr} ; ldr r0,=entropy_dev ; bx r3
                                          ; -> api->get_entropy(dev, buf, len)
```

Our reconstruction declared it `extern int entropy_get_entropy_isr_call(int*)`
and called `entropy_get_entropy_isr_call(&local_c)` — **one argument**. `r1` at
that point is whatever `z_device_is_ready()` left behind. With
`g_current_thread_ptr` pointing at the arena (i12a/i12d) that residue happened
to be **0**, so the driver returned immediately and the defect was invisible;
with the pin rebound (i12c) the residue was a large value and the CTR_DRBG
churned for the rest of the run. **The livelock was never a CC312-PAL or
newlib-retarget-lock defect at all** — those functions are correct; iteration
12's `__malloc_unlock` observation was the first *trace* difference, not the
cause.

The fix is one argument in `recon/app/src/FUN_00052c40.c` (+ the symbolized /
named mirrors):

```c
-extern int FUN_00052bf8(int*);
-    iVar2 = FUN_00052bf8(&local_c);
+extern int FUN_00052bf8(int*, int);
+    iVar2 = FUN_00052bf8(&local_c, 4);
```

Emitted code, verified in the linked ELF, now matches the original's sequence:

```
43be4  movs r1,#4 ; 43be6 add r0,sp,#12 ; 43be8 bl entropy_get_entropy_isr_call
```

This is the **fourth** member of the class the harness is structurally blind to
(outgoing stack args, dropped register args, wrong indirection level, stack
writes) — here a **dropped register argument**. `cfg_verify` reports PASS both
before and after, which is expected and is exactly why the disassembly is the
authority.

**Landed together with** `PROVIDE(g_current_thread_ptr = _kernel + 0x8)` and
`PROVIDE(g_spinlock_validate_owner = _kernel + 0x10)` in
`recon/symbols/g1_app_globals.ld` (iteration 12 §12.6's measured-and-reverted
pair; `g_sched_ready_runq = _kernel + 0x1c` had already been kept).

**Measured (`/private/tmp/g1-i13a-app`).** The 0.0717 s
`z_tick_sleep` `__ASSERT(!SUSPENDED)` panic is **gone**; the whole panic path
(`assert_post_action`, `_oops`, `z_do_kernel_oops`, `z_arm_fatal_error`,
`z_fatal_error`, `panic`, `sys_arch_reboot`, …) disappears from the trace.
`ProcessAesDrv` returns to **280 entries — exactly the golden trace's count**
(the shipped firmware's own figure), from 248 (i12d) and 66,939 (i12c).
2.0 s: **6,261,306 instructions, 822 unique functions, 0 faults, 0 resets.**

### 13.2 Step B — the IMU-fusion vtable, and how it also *was* the first divergence

Iteration 12 recorded a 13th `k_thread_create` at 0x260c2 inside the catalog gap
`[0x25f90, 0x26100)`. Chasing the iteration-13 Step-A boot's own first
divergence landed on the same gap from the other direction, which is the useful
result:

`main`'s last executed instruction in `g1-i13a-app` (2.0 s trace, transition
#5,937,086) is

```
163dc  ldr.w r3,[r4,#0xf70]      ; a function pointer out of the context struct
163e0  addw  r0,r4,#0xee4
163e4  blx   r3                  ; --> lands at 0x25FAC, i.e. 0x94 bytes INTO
                                 ;     low_speed_peripheral_dispatch_thread
```

`register_imu_funsion_context` (0x26250) is what fills that slot:

```
26252  ldr r3,=0x00025fad ; str.w r3,[r0,#0x8c]     <- main's [r4+0xf70]
26258  ldr r3,=0x00025df9 ; str.w r3,[r0,#0x90]
2625e  ldr r3,=0x00025dc5 ; str.w r3,[r0,#0x94]
26264  ldr r3,=0x00025d8d ; str.w r3,[r0,#0x98]
```

All four targets sit in Ghidra catalog gaps (`0x25d8c..0x25ecc` and
`0x25f90..0x26100`; the latter's first 0x1c bytes are
`panel_level_calc_cached`'s literal pool), so our build kept them as raw flash
literals `PROVIDE(rodata_25fad = 0x00025fad)` — and `main` branched into the
middle of an unrelated function. **The uncatalogued IMU function and the boot's
first divergence were the same defect.**

Each function's name is self-evidenced by the log tag it passes as the `"%s()"`
argument:

| VA | size (code) | log tag | name | vtable slot |
|---|---:|---|---|---|
| 0x25d8c | 0x28 | 0x9fb00 `"set_imu_thread_delay"` | `set_imu_thread_delay` | +0x98 |
| 0x25dc4 | 0x24 | 0x9faf9 `"resume"` | `imu_fusion_resume` | +0x94 |
| 0x25df8 | 0x24 | 0x9faf1 `"suspend"` | `imu_fusion_suspend` | +0x90 |
| 0x25fac | 0x124 | 0x9fae1 `"imu_fusion_init"` | `imu_fusion_init` | +0x8c |

`imu_fusion_init` is the substantial one: it refuses to run twice
(`ctx[0x14] != 0` → `-1`), stores the LSM6DSO `struct device *` 0x87d58 at
`ctx+0x1c`, calls the sensor API twice through `dev_api_call_slot0(dev, 3|7,
&ctx[0x20])` with an ODR word of `0x34` when `get_device_type() == 1`
(accelerometer, then gyro; `-3` / `-4` on failure — the two error strings are
literally *"Cannot set sampling frequency for accelerometer"* and
*"… for gyro."*), initialises the fusion state (`imu_fusion_state_init`),
marks the context live (`*(u16*)(ctx+0x14) = 0x100`), calls
`panel_level_calc_cached`, and finally creates the thread:

```
260ba  ldr r3,=0x0000fe89   ; entry  = imu_fusion_thread
260bc  ldr r1,=0x20023568   ; stack
260be  ldr r0,=0x20003fe8   ; thread object
260ae  mov.w r2,#0x700      ; stack size
260aa  mvn.w r3,#10         ; prio = -11
260a6  strd r2,r3,[sp,#0x18]; delay = K_NO_WAIT (the 64-bit k_timeout_t)
260c2  bl  0x71eac
```

All four were registered in the scratchpad catalogs (the sanctioned
iteration-4/8 route), reconstructed, and **`recon_kit.prove` / `cfg_verify`
PASS 200/200 each**. Wiring:

* new canonical bodies `recon/app/src/{imu_fusion_init,imu_fusion_resume,
  imu_fusion_suspend,set_imu_thread_delay}.c` (+ `recon/verified/src` mirror),
  symbolized build-tree copies, four entries added to
  `recon/catalogs/function_names_app.json`, and
  `tools/gen_retained_sources.py` regenerated (**`--check` clean**);
* `recon/symbolized/app/register_imu_funsion_context.c` now stores
  `ADDR_imu_fusion_init_THUMB` &c. instead of the `rodata_25*` literals. This is
  deliberate: it is the *only* real reference to those functions, so it is also
  what pulls them out of `libapp.a`. Binding the pins in the linker script alone
  was measured and does **not** work — a `PROVIDE` expression is not an archive
  reference, and the first attempt (`/private/tmp/g1-i13b-app`) linked with the
  four functions absent and FLASH byte-identical to `g1-i13a-app`;
* two new RAM pins on the existing arena, `g_imu_fusion_thread = arena+0x1fe8`
  (0x20003fe8) and `g_imu_fusion_thread_stack = arena+0x21568` (0x20023568).
  The stack size is corroborated by an already-present pin: `g_20023c68` =
  0x20023568 + 0x700.

**A 10th site was added to `check_thread_create_stack_args.py`.** It needs three
reviewed fixtures (zeroed argument scratch so `ctx[0x14] == 0`, forced `>= 0`
returns on call ordinals 2 and 4, and `g_log_level` pinned to 0 so the five
guarded log branches stay out of the call sequence), and it passes with all
eight outgoing words compared. Mutation battery actually run against it (60
trials each): `prio -11 → -12` **FAIL 60/60**, `delay 0 → 5` **FAIL 60/60**,
`p2 0 → 1` **FAIL 60/60**, and — honestly — `delay argument removed` **PASS**,
because dropping it shrinks the frame by exactly 8 bytes so `sp+0x18/0x1c` land
on the pushed `r4`/`r5` slots, which the harness enters with `r4 = r5 = 0`,
byte-identical to `K_NO_WAIT`. (The other eight sites lost more than 8 bytes and
hit the pushed `lr = RETURN_MAGIC`, which is why *they* failed pre-fix.) The
authority for that mutation here is the emitted frame, which is
instruction-for-instruction the original's:

```
ours   260c6 movs r2,#0 ; movs r3,#0 ; movs r5,#0
       260cc strd r2,r3,[sp,#24]   260d8 strd r3,r5,[sp,#12]
       260dc strd r5,r5,[sp,#4]    260e8 str  r4,[sp,#0]     260ea bl ...
orig   260a0 movs r2,#0 ; movs r3,#0 ; movs r5,#0
       260a6 strd r2,r3,[sp,#0x18] 260b2 strd r3,r5,[sp,#0xc]
       260b6 strd r5,r5,[sp,#4]    260c0 str  r4,[sp,#0]     260c2 bl 0x71eac
```

(the only difference is `sub sp,#32` vs `sub sp,#0x24`, because GCC needs four
callee-saved registers where the original used five.)

**Result: the IMU fusion thread is created and runs.** In `g1-i13e-app`:
`register_imu_funsion_context` 1 entry, `imu_fusion_init` 9 entries (first at
i=5,955,553), **`imu_fusion_thread` 56 entries** (first at i=5,970,236), and the
whole sensor stack behind it — `lsm6dso_attr_set`, `lsm6dso_xl_data_rate_set`,
`lsm6dso_gy_data_rate_set`, `lsm6dso_mem_bank_set`, `lsm6dso_read_reg`,
`lsm6dso_write_reg`, `lsm6dso_sample_fetch`, `lsm6dso_channel_get`,
`lsm6dso_acceleration_raw_get`, `lsm6dso_angular_rate_raw_get`,
`lsm6dso_accel_convert`, `lsm6dso_gyro_convert`, `imu_mahony_ahrs_update`,
`quaternion_to_euler`, `orientation_filter_update_dt`,
`orientation_get_pitch_deg`/`_yaw_deg`/`_heading_deg`, `fast_inverse_sqrt`,
`__ieee754_asinf`, `__ieee754_atan2f`. Renode's twim2 model logs real LSM6DSO
register accesses (offsets 0x46/0x47, the EmbeddedFunctions bank) — the first
IMU bus traffic this project has produced. `run_main_dispatch_thread` (5
entries) and `flash_ops_thread`/`brightness_level` also start for the first
time.

### 13.3 What the IMU path unmasked (both fixed, both provable)

**(a) The `dev_ctrl_*` I²C-message family — a stack-object reconstruction that
GCC legally deleted.** With the vtable linked, FLASH shifts and the boot reset at
0.0466 s on `nrfx_twim.c:593` (`primary_length < (1U << 16)`). Cause:

```
ours  dev_ctrl_write2   push {r0,r1,r4,lr} ; add r2,sp,#3 ; str r2,[sp,#4]
                        strb r1,[sp,#3] ; add r1,sp,#4 ; movs r2,#2 ; blx r4
orig  0x83d80           sub sp,#0x24
                        strb.w r1,[sp,#4]  strb.w r2,[sp,#5]      ; data[2]
                        str r2,[sp,#8]  str r2,[sp,#12]  strb.w r1,[sp,#16]
                        str r5,[sp,#20] str r1,[sp,#24]  strb.w r1,[sp,#28]
                        add r1,sp,#8 ; movs r2,#2 ; blx r4
```

The previous body declared six unrelated locals and passed `&local_28`, relying
on GCC laying them out contiguously as a two-element `i2c_msg` array. GCC kept
only the store whose address escapes and deleted the rest, so
`msgs[0].len`, `msgs[0].flags` and all of `msgs[1]` were uninitialised stack.
This is the same class iteration 10 already fixed one member of
(`dev_ctrl_write1` @0x83d60) — and, again, invisible to the harness, which
compares only NON-stack writes. Three siblings were wrong for related reasons:

| VA | name | defect | evidence |
|---|---|---|---|
| 0x83d80 | `dev_ctrl_write2` | 2-element `i2c_msg` array collapsed to one word | frame above |
| 0x83dba | `dev_ctrl_read1` | declared `(void)` calling `(void)` → GCC emitted a bare `b.w`, forwarding registers by accident and leaving the 5th (stack) argument `length = 1` as caller residue | `83dbc movs r4,#1 ; str r4,[sp,#0] ; bl 0x83d80` |
| 0x83e0e | `dev_reg_modify_bits` | declared 3 parameters; the original takes 5 (the 5th, an 8-bit mask, at `sp+0x28`) and does a real read-modify-write | `83e1a ldrb.w r9,[sp,#0x28]`, `83e48 bic/and/orr` |
| 0x841fc | `dev_set_mode_register` | passed 4 arguments to the 5-argument `dev_reg_modify_bits`, dropping the mask (0x47 / 0xb8) | `84216/84218 movne/moveq r2 ; 8422a str r2,[sp,#4] ; b.w 0x83e0e` |

All four rewritten, `cfg_verify` **PASS 200/200** each, and the emitted
`dev_ctrl_write2` / `dev_ctrl_read1` are now **instruction-for-instruction
identical to the shipped originals**, same frame size and same stack offsets:

```
77728 push {r4,r5,lr} ; sub sp,#0x24 ; ... ; strb.w r1,[sp,#4] ; strb.w r2,[sp,#5]
      str r2,[sp,#8] ; str r2,[sp,#12] ; strb.w r1,[sp,#16] ; str r3,[sp,#20]
      str r3,[sp,#24] ; strb.w r3,[sp,#28] ; add r1,sp,#8 ; movs r2,#2 ; blx r5
77762 push {r0,r1,r4,lr} ; movs r4,#1 ; str r4,[sp,#0] ; bl 0x77728
```

**(b) One more unrelocated `gpio_dt_spec`.** With real I²C the nPM1300 sequence
completes and `power_for_panel` advances to `gpio_dt_spec_activate` (0x179ec),
which is `ldr r0,=0x000889f8 ; movs r1,#1 ; b.w gpio_pin_set_dt`.
`PROVIDE(rodata_889f8 = 0x000889f8)` was still a raw flash literal, so
`gpio_pin_set_checked` got a bogus port pointer and asserted (fatal error 4 at
0.0477 s). This is exactly iteration 5's class — the descriptor itself embeds an
absolute `struct device *`, so a linker rebind cannot express it and the table
must be emitted by the build. Transcribed from the image:

```
0x889e8: { 0x00087b60 (gpio0 "gpio@842500"), pin 30, dt_flags 0 }
0x889f0: { 0x00087b60,                        pin 21, dt_flags 0 }
0x889f8: { 0x00087b60,                        pin 24, dt_flags 0 }   <- panel power
```

Added to `recon/application/app/src/g1_gpio_dt_specs.c` next to the existing
0x88340 / 0x889d0 / 0x889e0 entries and bound in `g1_app_globals.ld`.

### 13.4 Bisect ledger (every build and boot actually run)

| build | change | app @0.15 s | resets | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i13a-app` | **Step A**: `sys_rand32_get` length + `g_current_thread_ptr`/`g_spinlock_validate_owner` = `_kernel+0x8`/`+0x10` | 6,004,916 / **777** | **0** | @2.0 s **6,261,306 / 822, no reset** |
| `/private/tmp/g1-i13b-app` | + the four IMU functions, bound only through the linker script | 626,548 B FLASH, identical to i13a | — | **not linked** — `PROVIDE` is not an archive reference; not booted |
| `/private/tmp/g1-i13c-app` | + `register_imu_funsion_context` referencing them by symbol | 6,340,570 / 707 | 1 @0.0466 s | `nrfx_twim.c:593` assert (defect (a)) |
| `/private/tmp/g1-i13d-app` | + the four `dev_ctrl_*` fixes | 6,034,477 / 707 | 1 @0.0477 s | `gpio_pin_set_checked` assert (defect (b)) |
| `/private/tmp/g1-i13e-app` | + the three `gpio_dt_spec` descriptors | **6,388,996 / 839** | 1 @0.0892 s | **final**; IMU thread runs |

Function-set diff, `g1-i13e-app` vs `g1-i13a-app` (2.0 s): **83 gained**
(the LSM6DSO / fusion / orientation stack listed in §13.2, plus
`dev_api_call_slot0`, `get_device_type`, `panel_level_calc_cached`,
`gpio_dt_spec_activate`, `gpio_pin_set_dt`, `run_main_dispatch_thread`,
`main_dispatch_thread_tick`, `spawn_flash_ops_and_brightness_threads`,
`flash_ops_thread`, `brightness_level`, `opt3007_chip_init`, `wdt_npm1300_*`,
`init_watchdog`, `battery_soc_curve_model_init`, and the fault path), **66
lost** — all of them the periodic/NFC/ST25DV tail that only executes *after*
0.0892 s (`periodic_check_run`, `check_work_mode`, `check_sw0_status`,
`fuel_gauge_*`, `st25dv_*`, `adc_nfc_run`, `msg_queue_init`, …). None of those
were broken; the boot simply dies earlier.

### 13.5 E4 status and the oracle

**E4 is still NOT reached.** `spi_read_id`, `panel_on`, `spi_master_init`,
`bt_enable`, `bt_start`, `master_display_thread`, `display_thread_handler` are
all absent from every iteration-13 trace, and `radio TransmittedFrames` is **0**
in all of them. `power_for_panel` now runs 9 times (was 5) and gets as far as
driving its GPIO power-enable line, but **no SPI transaction reaches the JBD
panel model**, so no comparison against `display_sensor_oracle.json` criterion
G-5 was possible — `0x9F`→`0x4010`, the three-band 153,600 B clear, the five
`0xC0` words and the `0x46`/`0x31` brightness pairs are **untested, not failed**.

On the **sensor** half there is a first, partial result. `twim2` (LSM6DSO) now
carries real traffic where before there was none: the Renode model logs reads of
the EmbeddedFunctions-bank registers 0x46/0x47, and the driver stack that issues
them (`lsm6dso_mem_bank_set`, `lsm6dso_read_reg`, `lsm6dso_xl_data_rate_set`,
`lsm6dso_gy_data_rate_set`) executes. That is the precondition for the oracle's
**S-IMU** criterion ("identical init register writes AND identical steady-state
polling of 0x22/0x28"), but S-IMU itself was **not evaluated**: it needs the
opt-in `TraceFile` hook in `armemul/models/NRF5340_TWIM.cs` plus the scripted
20 s two-phase capture (`capture_display_sensor_oracle.sh`), which this
iteration did not run. Reported as "traffic exists, criterion untested".

### 13.6 New first divergence (drives iteration 14)

`/private/tmp/g1-i13e-app`, app instruction ≈6,388,9xx, virtual time
**0.0892 s**:

```
[00:00:00.089,141] <err> os: ***** USAGE FAULT *****
[00:00:00.089,141] <err> os:   Illegal use of the EPSR
[00:00:00.089,202] <err> os: Faulting instruction address (r15/pc): 0x0002821c
[00:00:00.089,202] <err> os: >>> ZEPHYR FATAL ERROR 35
```

0x2821c is `global_system_suspend + 0x34` (original 0x2bd7c), and the
instruction is another **context vtable dispatch**:

```
28214  ldr.w r3,[r4,#0xb70]
28218  addw  r0,r4,#0xb6c
2821c  blx   r3
```

with `r4 = 0` at the fault (the reported `r0/a1 = 0x00000b6c` is `r4 + 0xb6c`),
so `r3` is read out of flash address 0xb70 and is even ⇒ EPSR fault. Two things
are therefore wrong at that boundary and both are in classes this project has a
playbook for: **the context pointer handed to `global_system_suspend` is NULL**
(a caller/argument defect), and **the `+0xb70` slot is another code-pointer
table** that has to be found and rebound the way §13.2 rebound `+0x8c..+0x98`.
That is the concrete iteration-14 Step A.

### Regenerate (iteration 13)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check            # current
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
                                                                                  # EXIT=0, 10/10
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify as c;\
 [print(n, c.verify('app',n)['status']) for n in ('FUN_00052c40','imu_fusion_init','imu_fusion_resume',\
 'imu_fusion_suspend','set_imu_thread_delay','FUN_00083d80','FUN_00083dba','FUN_00083e0e','FUN_000841fc',\
 'register_imu_funsion_context')]"                                                # 10x PASS
recon/application/build_cohesive.sh app /private/tmp/g1-i13e-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i13e-app/zephyr/zephyr.elf                                    # EXIT=0
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i13e /private/tmp/g1-i13e-app /private/tmp/g1-i9c-net 0.15
# Step-A-only reference build: /private/tmp/g1-i13a-app (0 resets over 2.0 s)
```

Files changed: `recon/app/src/{FUN_00052c40,FUN_00083d80,FUN_00083dba,
FUN_00083e0e,FUN_000841fc}.c` (corrected + re-proven) and the new
`recon/app/src/{imu_fusion_init,imu_fusion_resume,imu_fusion_suspend,
set_imu_thread_delay}.c`; the same nine bodies mirrored into
`recon/verified/src`, `recon/symbolized/app` and `recon/named`;
`recon/symbolized/app/{sys_rand32_get,register_imu_funsion_context,
dev_ctrl_write2,dev_ctrl_read1,dev_reg_modify_bits,dev_set_mode_register}.c`;
`recon/symbols/g1_app_globals.ld` (the two `_kernel` interior pins, the four
IMU vtable rebinds, three `gpio_dt_spec` rebinds, two new arena RAM pins,
eleven log-string pins); `recon/symbols/g1_app_symbols.h`;
`recon/application/app/src/g1_gpio_dt_specs.c`;
`recon/catalogs/function_names_app.json` (four new names);
`recon/generated/app_retained_sources.cmake` (regenerated by its own tool);
`recon/emulator/scripts/check_thread_create_stack_args.py` (10th site).
Four records appended to the scratchpad catalogs `app_funcs.json` /
`classified.json` (backed up as `*.i13bak`), the iteration-4/8 route.
No `tools/` change, no Kconfig / `prj.conf` / devicetree change, `armemul`
untouched. Nothing committed.

## Iteration 14 — the projector-controller vtable (six more uncatalogued
## functions), the NULL context, the un-rebindable GPIO descriptors, and the
## first real sensor-parity measurement

**Headline.** Iteration 13's `global_system_suspend` fault is **root-caused and
gone**, and with it every reset: `/private/tmp/g1-i14b-app` boots
**fault-free and reset-free through 2.0 s of virtual time with 883 unique
functions** (previous reset-free best: iteration 13's `g1-i13a` at 822; previous
absolute best: `g1-i13e` at 839 *with* a reset at 0.0892 s). At 0.15 s it
reaches **882 unique functions, 0 resets** — 43 more than the iteration-13
final, with **every one of the 17 lost functions being the fault/panic path**
(`z_arm_fault`, `z_fatal_error`, `panic`, `sys_arch_reboot`, …).

Three defects, all in classes this project already has a playbook for:

1. **A ninth-slot vtable, six of whose nine targets Ghidra never catalogued.**
   `quicknote_buffer_pool_init` (0x47148) is misnamed — it is the
   **projector-controller vtable registrar**, called from `main` at 0x17324 with
   `r0 = device_ctx + 0xb6c`. It writes nine code pointers at
   `ctx+0xb6c .. ctx+0xb8c`. Ghidra catalogued only three targets
   (`jdb_panel_init` 0x46fc0, `panel_off` 0x46d2c, `panel_on` 0x46dd8) and
   **folded the other six into the tail of the preceding symbol**, so our build
   kept them as raw flash literals `rodata_46d8d`, `rodata_46f21`,
   `rodata_35775`, `rodata_7d4d7`, `rodata_7d4cb`, `rodata_46ce9`.
   `global_system_suspend` dispatches through slot +0x04 (`ctx+0xb70`).
2. **A dropped register argument at that same boundary** — the NULL context.
3. **Six `gpio_dt_spec` addresses that were hardcoded numeric literals in the
   symbolized sources**, so their `PROVIDE()` rebinds in `g1_app_globals.ld`
   could never apply.

Step B then produced the **first evaluation of `display_sensor_parity.md`'s
criteria against our rebuild** (full detail in the new
`recon/emulator/reports/sensor_parity_status.md`): **S-KEYS, S-MIC (negative)
and the gyro negative PASS by exact stream-hash equality**; S-ALS, S-NFC
(system port) and S-ADC are **byte-exact for every transaction our build emits**
and then stop; S-IMU and S-PMIC diverge inside their init sequences with a named
first-differing register; and **G-1/G-2/G-3/G-5 are not reached at all** — our
firmware still produces **zero** display SPI transactions.

| metric | iter 13 final `g1-i13e-app` | iter 13 reset-free `g1-i13a-app` | iter 14 `g1-i14a-app` | **iter 14 final `g1-i14b-app`** |
|---|---:|---:|---:|---:|
| app instr @0.15 s | 6,388,996 | 6,004,916 | 6,380,786 | **10,865,770** |
| app unique fns @0.15 s | 839 | 777 | 855 | **882** |
| app resets | 1 @0.0892 s | 0 | 1 @0.0893 s | **0** |
| app @2.0 s | 6,388,996 / 839, reset | 6,261,306 / 822, no reset | — | **195,865,770 / 883, no reset** |
| net instr / fns @0.15 s | 287,341 / 420 | 291,514 / 432 | 290,772 / 422 | **293,078 / 433** |
| net @2.0 s | — | — | — | **380,275 / 466** |
| `radio TransmittedFrames` | 0 | 0 | 0 | **0** |
| app FLASH | 631,996 B (64.32 %) | 626,548 B | 632,716 B | **632,740 B (64.40 %)**, +744 B |
| app RAM | 244,229 B (54.21 %) | 244,229 B | 244,229 B | **244,229 B**, +0 B |
| `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | 10/10 | 10/10 | **10/10, EXIT 0** |

No `--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change. `armemul` is
**untouched** (its two opt-in `TraceFile` hooks were already present from the
oracle capture and were not modified). Net core not rebuilt
(`/private/tmp/g1-i9c-net`, unchanged since iteration 9). Nothing committed.

### 14.1 Step A(1) — the NULL context: a dropped register argument at
### `prepare_system_suspend_state` (and the same defect in `global_system_resume`)

The iteration-13 fault was `global_system_suspend + 0x34` executing
`ldr.w r3,[r4,#0xb70] ; blx r3` with `r4 = 0`. `global_system_suspend`'s own
reconstruction is correct — it takes the context in `param_1`. The zero comes
from its callers. There are exactly two (found by scanning the image for
`bl`/`b.w` targets equal to 0x2bd7c):

```
prepare_system_suspend_state @0x289b0            global_system_resume @0x16854
  289b2  bl 0x47ab8                                168b0  bl 0x32ee4   ; is_battery_critical(r0=param_1)
  289b6  bl 0x167a8   ; get_device_info -> r0      168b4  cmp r0,#0
  289ba  bl 0x2bd7c   ; global_system_suspend(r0)  168b6  bne 0x1689c  ; returns ITS result
  289be  bl 0x167a8                                168b8  ldr r0,[r6,#0] ; r0 = *device_info
  289c2  movs r3,#1 ; strb.w r3,[r0,#0xee4]        168ba  cbz r4,0x16902
                                                   168bc  pop ; b.w 0x2bdf0  ; active_mode_shutdown(ctx)
                                                   16906  pop ; b.w 0x2bd7c  ; global_system_suspend(ctx)
```

Our sources declared `extern void global_system_suspend(void);` and called it
with **no arguments**, so `r0` was whatever `z_device_is_ready()` / the
preceding call left behind — reliably 0. This is the **fifth** member of the
class the harness is structurally blind to (dropped register args, dropped stack
args, wrong indirection levels, stack writes, collapsed stack objects): both
callers were at `PASS` under `cfg_verify` **before and after** the fix
(`prepare_system_suspend_state` 40 checks, `global_system_resume` 65 → 225),
because callees are order-keyed oracles whose argument registers are never
compared. The disassembly is the authority.

While rewriting `global_system_resume` against the frame above, four further
argument defects in the same function were corrected with the same evidence —
`bt_start(0)`→`bt_start(param_1)`, `gpio_set_fixed_output_889f0(0)`,
`imu_apply_normalized_mode(0)`, `gpio_set_pin1_dt_wrapper(0)` all pass `r0 =
param_1` in the original — plus the `is_battery_critical` **return value**
(0x168b6 returns the callee's result, our body returned `param_1`). Re-proven:
`recon_kit.prove` / `cfg_verify` **PASS** (200 and 225 checks).

### 14.2 Step A(2) — the `+0xb70` vtable is the whole projector/panel vtable

`quicknote_buffer_pool_init` @0x47148 is `main`'s counterpart to iteration 13's
`register_imu_funsion_context`:

```
17310  addw r0,r4,#0xee4 ; bl 0x26250   <- register_imu_funsion_context (iter 13)
17320  addw r0,r4,#0xb6c ; bl 0x47148   <- THIS registrar
```

```
47152  ldr r3,=0x46fc1 ; str r3,[r4,#0]      <- +0x00  jdb_panel_init          (already bound)
4715a  ldr r3,=0x46d8d ; str r3,[r4,#4]      <- +0x04  ctx+0xb70, the faulting slot
47162  ldr r3,=0x46f21 ; str r3,[r4,#8]      <- +0x08
4716a  ldr r3,=0x46d2d ; str r3,[r4,#0xc]    <- +0x0c  panel_off               (already bound)
47166  ldr r3,=0x46dd9 ; str r3,[r4,#0x10]   <- +0x10  panel_on                (already bound)
4716e  ldr r3,=0x35775 ; str r3,[r4,#0x14]   <- +0x14
47172  ldr r3,=0x7d4d7 ; str r3,[r4,#0x18]   <- +0x18
4717a  ldr r3,=0x7d4cb ; str r3,[r4,#0x1c]   <- +0x1c
47176  ldr r3,=0x46ce9 ; str r3,[r4,#0x20]   <- +0x20
```

Unlike iteration 13's four, these six do **not** sit in Ghidra catalog gaps —
they sit *inside* the declared extents of neighbouring symbols, i.e. Ghidra
over-reported those functions' sizes and swallowed the next function whole.
Each was read off the image (code, then its own literal pool) and named from the
log tag it passes:

| VA | size | container it was folded into | log tag | name | slot |
|---|---:|---|---|---|---|
| 0x46ce8 | 0x44 | `ui_set_imu_pitch_task` (0x46b80, declared 0x1ac) | 0xd732c `"panel_set_brightness_level"` | `panel_set_brightness_level` | +0x20 |
| 0x46d8c | 0x4c | `panel_off` (0x46d2c, declared 0xac) | 0xd72db `"panel_suspend"` | `panel_suspend` | **+0x04** |
| 0x46f20 | 0xa0 | `set_brightness_to_panel_reg` (0x46e3c, declared 0x184) | 0xd72c4 `"panel_resume"` | `panel_resume` | +0x08 |
| 0x35774 | 0x68 | `dump_whitelist_init` (0x35744, declared 0x98) | — | `panel_render_screen_dispatch` | +0x14 |
| 0x7d4ca | 0x0c | `get_localized_weekday_name` (0x7d4b2, declared 0x3a) | — | `projector_clear_canvas` | +0x1c |
| 0x7d4d6 | 0x16 | `get_localized_weekday_name` | — | `projector_flush_canvas` | +0x18 |

`panel_resume` @0x46f20 is the **E4 display bring-up path**:

```
46f64  bl 0x47638      ; jbd_panel_resume
46f68  bl 0x47724      ; spi_read_id
46f6c  movw r3,#0x4010 ; cmp r0,r3 ; beq ...   <- the JBD panel ID gate
46f7a  ...             ; else log 0xd728d "%s(): JBD PANEL init failure!\n"
46f9c  bl 0x46dd8      ; panel_on
46fa4  bl 0x46e3c      ; set_brightness_to_panel_reg(ctx[0x369])
```

All six reconstructed and **`recon_kit.prove` / `cfg_verify` PASS** (200/200,
200/200, 200/200, 203/203, 200/200, 200/200), re-verified after wiring
(40/40/40/43/40/40 CFG-directed checks each). Wiring is the iteration-13 route:
records added to the scratchpad catalogs `app_funcs.json` / `classified.json`
(backed up as `*.i14bak`) and to `recon/catalogs/function_names_app.json`; new
canonical bodies in `recon/app/src/` mirrored to `recon/verified/src`,
`recon/symbolized/app` and `recon/named`; six `__asm__`-alias rebinds
(`extern const unsigned char __g1_fp_<name>[] __asm__("<name>");` +
`ADDR_<name>_THUMB`) in `recon/symbols/g1_app_symbols.h`; the six
`PROVIDE(rodata_* = <name> | 1)` rebinds in `recon/symbols/g1_app_globals.ld`;
and — critically — `recon/symbolized/app/quicknote_buffer_pool_init.c` now
stores `ADDR_<name>_THUMB` instead of the `rodata_*` literals, because a
`PROVIDE` expression is not an archive reference and would leave the six
functions out of the link (measured in iteration 13 §13.2).

One new RAM pin: `g_screen_render_table = g1_ram_arena + 0x430` (original
0x20002430), the 16-entry / 16-byte-stride screen table
`panel_render_screen_dispatch` indexes. `check_ram_pin_collisions.py` still
reports 0 escaping pins / 0 unknowns inside a live object.

**Measured (`/private/tmp/g1-i14a-app`).** The `Illegal use of the EPSR` fault
is **gone**. `global_system_suspend` executes (2 entries), `panel_suspend` (3),
`panel_off` (1), and `bt_start` runs for the first time (3 entries).
855 unique functions. A *new* fault surfaced at 0.0893 s — see §14.3.

### 14.3 Step A(3) — six `gpio_dt_spec` addresses that no `PROVIDE` could reach

`g1-i14a-app` died at 0.0893 s with `ZEPHYR FATAL ERROR 4` (kernel panic) at
`assert_post_action+0xc`, from `gpio_pin_set_checked`'s
`__ASSERT(port_pin_mask & BIT(pin))`. Walking the trace back to the call:

```
global_system_resume -> gpio_set_pin1_dt_wrapper -> gpio_pin_set_dt
                     -> gpio_pin_set_checked -> printk -> assert_post_action
```

The original 0x17a10 is `movs r1,#1 ; ldr r0,=0x000889e8 ; b.w gpio_pin_set_dt`.
Iteration 13 already emitted the descriptors and pinned them
(`PROVIDE(rodata_889e8 = g1_gpio0_pin30_spec)` etc.) — but the **symbolized
sources spelled the descriptor address as a hardcoded numeric literal**:

```c
return gpio_pin_set_dt(0x000889e8U, 1U, arg2, arg3);   /* before */
```

A `PROVIDE` can only rebind a *named* reference. Our link therefore still
emitted `.word 0x000889e8` — a raw ORIGINAL-image flash address whose first word
is not a `struct device *` in our build — and `gpio_pin_set_checked` asserted on
the garbage `port_pin_mask`. Six sites were affected:

| source | descriptor | original bytes |
|---|---|---|
| `gpio_set_pin1_dt_wrapper` (0x17a10) | 0x889e8 | `{ gpio0, pin 30, 0 }` |
| `gpio_set_fixed_pin_dt` (0x17a1c) | 0x889e8 | " |
| `subsystem_enable_gpio_pin_set_adapter` (0x179f8) | 0x889f0 | `{ gpio0, pin 21, 0 }` |
| `gpio_set_fixed_output_889f0` (0x17a04) | 0x889f0 | " |
| `touch_pmic_reset_assert` (0x17a28) | 0x889d8 | `{ gpio0, pin 23, 0 }` — **descriptor did not exist yet** |
| `touch_pmic_reset_deassert` (0x17a34) | 0x889d8 | " |

All six now reference `((unsigned long)&rodata_889XX)`, and the missing
`0x889d8` descriptor was added to
`recon/application/app/src/g1_gpio_dt_specs.c` (`g1_gpio0_pin23_spec`) with its
pin and header extern. This is a *new* sub-class worth naming: the descriptor
was emitted **and** pinned correctly, but the consumer never named the symbol,
so the rebind was a no-op. It is worth sweeping the symbolized tree for other
raw `0x000[0-9a-f]{5}` literals that have a `PROVIDE` waiting for them.

**Measured (`/private/tmp/g1-i14b-app`, the final image).** **No faults, no
resets, at 0.15 s or at 2.0 s.** Function-set diff vs the iteration-13 final:
**60 gained, 17 lost**, and every one of the 17 lost is the fault/panic path
(`z_arm_fault`, `z_arm_usage_fault`, `z_arm_fatal_error`, `z_fatal_error`,
`panic`, `sys_arch_reboot`, `k_sys_fatal_error_handler`, `z_impl_log_panic`, …).
Gained, among others: `master_display_thread`, `display_thread_handler`,
`display_dispatch_thread`, `spawn_display_thread`, `spawn_proxy_thread`,
`proxy_thread_handler`, `transport_dispatch_thread`, `sync_to_slave`,
`trigger_screen_state_change`, `esb_pairing_sync_step`,
`spi_master_trans_data_tx_rx`, `projector_send_command`,
`projector_spi_write_chunked`, `projector_bus_lock`/`_unlock`,
`gui_set_active_canvas`, `bt_start`, `panel_suspend`, `panel_off`,
`jbd_panel_suspend`, `process_task_sync_event`, `k_msgq_get`.

### 14.4 E4 status and the G-5 comparison

**E4 is still NOT reached, but the display *thread graph* now runs.** Present
for the first time: `master_display_thread` (7 entries), `display_thread_handler`
(73 048 @0.15 s), `display_dispatch_thread` (8), `spi_master_trans_data_tx_rx`
(1), `bt_start` (3). Still absent: `spi_read_id`, `spi_master_init`,
`jdb_panel_init`, `panel_on`, `panel_resume`, `bt_enable`; `radio
TransmittedFrames` = **0**.

**G-5 comparison: not possible — there is no display SPI traffic to compare.**
A full 20 s two-phase capture of `g1-i14b-app` under the oracle's determinism
knobs (§14.5) recorded **0 transactions on `spim_a`**, `JBD FrameCounter` = 0,
`JournalCount` = 0, journal empty, framebuffer uniformly zero. The `0x9F`→
`0x4010` probe, the three-band 153 600 B clear, the five `0xC0` words
`0000/0014/1800/1814/0C0A` and the `0x46`/`0x31` brightness pairs `0F 04` /
`00 04` are therefore **UNTESTED, not failed**. `spim_b` is 0 == 0 (G-6),
but vacuously so.

### 14.5 Step B — the first real sensor-parity measurement

Full per-criterion table, first-difference detail and the exact reproduction
command are in **`recon/emulator/reports/sensor_parity_status.md`**. Summary:

| criterion | verdict |
|---|---|
| **S-KEYS** | **PASS** — `gpiote0` stream_sha256 **identical** (25 == 25 accesses, `CONFIG[7]=0x22901`, `CONFIG[6]=0x22A01`, `INTENSET` `0x80000000`/`0x80`/`0x40`); `gpiote1` 0 == 0 |
| **S-MIC** (negative) | **PASS** — `pdm0` stream_sha256 **identical**: exactly `PSEL.CLK ← 0x2D`, `PSEL.DIN ← 0x2E`, no ENABLE, no START, no DMA |
| gyro (negative) | **PASS** — `GyroscopeEnabled` = False after 20 s (accel True) |
| **S-ALS** | **PARTIAL, prefix-exact** — 7/33 txns, all 7 byte-identical, then stops |
| **S-NFC** | **PARTIAL / NOT-EXERCISED** — system port 6/22 byte-identical then stops; NFC EEPROM (0x53) **0**/25 |
| **S-ADC** | **PARTIAL, prefix-exact** — 5/998 accesses, all 5 byte-identical (`EVENTS_END`, `EVENTS_CALIBRATEDONE`, `INTENSET ← 0x12`), no conversion cycle |
| **S-IMU** | **PARTIAL** — 35/1089 txns; first **3** byte-identical, **first difference at txn #3** |
| **S-PMIC** | **PARTIAL** — 54/270 txns; **first difference at txn #0** |
| **S-ESB** | **FAIL** — `radio TransmittedFrames` = 0 |
| **G-1 / G-2 / G-3 / G-5** | **NOT REACHED** — 0 SPI transactions |
| **G-6** | PASS (vacuous) |

The two genuine parity findings:

* **S-IMU** — after an identical `FUNC_CFG_ACCESS ← 0x00` / `WHO_AM_I → 0x6C`
  handshake, the original does a `CTRL9_XL (0x18)` read-modify-write
  (`R E0`, `W 18E2`, then `0x62 ← 00`); **ours writes `FUNC_CFG_ACCESS ← 0x80`**
  and reads `0x46` (`FSM_ENABLE_A`) in the embedded-functions bank the original
  never enters. Classified **recon defect**: the golden trace's only `lsm6dso_*`
  symbol is `lsm6dso_init_chip` (37 entries) with **no** `mem_bank_set` /
  `fsm_enable_get` / `attr_set`, whereas ours runs `lsm6dso_mem_bank_set` 16×,
  `lsm6dso_fsm_enable_get` 16×, `lsm6dso_attr_set` 8× and `lsm6dso_init_chip`
  only 6×. The iteration-13 `imu_fusion_init` reaches the sensor through a
  `dev_api_call_slot0(dev, 3|7, …)` attr-set path the original does not take.
* **S-PMIC** — the original opens with a bank-0x06 write burst
  (`0x0602 ← 06`, `0x0616 ← 00`, `0x060C ← 00`, `0x0611 ← 00`); ours opens with
  bank-0x04 **reads** (`0x040F`, `0x0410`). Classified **recon defect
  (init-sequence ordering)** — the bus-level protocol is right, the routine
  order is not.

Everything else that is "partial" is **not-yet-reached**, not wrong: our build
reproduces every transaction it emits byte-for-byte and then stops, and it emits
**zero** transactions on every device during `p2_render`.

### 14.6 New first divergence (drives iteration 15) — the `display_thread_handler` free-run

With the faults gone the boot no longer dies; it **live-runs**. At 2.0 s the app
core executes **195 865 770 instructions** against the golden trace's
**12 629 795** — 15× — and the profile is one loop:

| function | ours @2.0 s (entries / instr) | golden (entries / instr) |
|---|---:|---:|
| `display_thread_handler` | 2 918 551 / 26 996 542 | 178 / 2 033 |
| `k_msgq_get` | 2 918 551 / 25 537 257 | 182 / 1 597 |
| `wake_display_thread_on_reflash` | 729 636 / 4 377 810 | 43 / 258 |
| `memset` + `memset_bytes` | 729 885 / 75 301 204 | — |

`display_thread_handler` (original 0x49090) derives its `k_msgq_get` timeout from
`g_dashboard_display_level` (original 0x20002544, correctly bound to
`g1_ram_arena + 0x544`):

```
orig  4914e ldr r3,=0x20002544 ; 49154 ldr r3,[r3]
      4915a bic.w ip,r3,r3,asr #31        ; clamp to >= 0
      4915e smlal r0,r1,ip,lr             ; * 0x8000, + 999
      49164 bl __aeabi_uldivmod           ; / 1000  -> ticks
      49170 bl k_msgq_get
ours  4238a ldr.w r3,[r9]   (r9 = g_dashboard_display_level)
      42390 bic.w ip,r3,r2 ; 42394 smlal r0,r1,ip,lr ; 4239e bl __aeabi_uldivmod
      423aa bl k_msgq_get
```

— instruction-for-instruction the original's frame, so this is **not** another
dropped-argument defect. The value is simply **0** in our build, making the
timeout `K_NO_WAIT`; the thread free-runs, re-clears the canvas every iteration
(`memset` is 38 % of all instructions) and starves every sensor thread, which is
exactly why `p2_render` records zero I²C traffic on every device. The only
writer, `set_dashboard_display_level_clamped` (0x48b44), executes in **neither**
trace, so the original's non-zero value must come from the settings store or
from a `.data` initialiser we have not reproduced. **That is iteration 15's
Step A.** The obvious companions are the still-absent `spi_master_init` /
`jdb_panel_init` / `spi_read_id` / `bt_enable` (all present in the golden trace)
and the two S-IMU / S-PMIC init-sequence defects located in §14.5.

### Regenerate (iteration 14)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check          # current
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
                                                                                # EXIT=0, 10/10
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify as c;\
 [print(n, c.verify('app',n)['status']) for n in ('panel_suspend','panel_resume',\
 'panel_set_brightness_level','panel_render_screen_dispatch','projector_clear_canvas',\
 'projector_flush_canvas','FUN_000289b0','FUN_00016854','quicknote_buffer_pool_init',\
 'global_system_suspend')]"                                                     # 10x PASS
recon/application/build_cohesive.sh app /private/tmp/g1-i14b-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i14b-app/zephyr/zephyr.elf                                  # EXIT=0
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i14b  /private/tmp/g1-i14b-app /private/tmp/g1-i9c-net 0.15
<scratchpad>/mkrun.sh i14b2 /private/tmp/g1-i14b-app /private/tmp/g1-i9c-net 2.0
# Step B capture + diff: see recon/emulator/reports/sensor_parity_status.md §1
```

Bisect ledger (every build and boot actually run):

| build | change | app @0.15 s | resets | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i14-app` | rebuild of the iteration-13 tree (baseline check) | 6,388,996 / 839 | 1 @0.0892 s | reproduces `g1-i13e-app` exactly |
| `/private/tmp/g1-i14a-app` | + the six vtable functions, the NULL-context fix, the `global_system_resume` argument fixes | 6,380,786 / **855** | 1 @0.0893 s | EPSR fault gone; new `gpio_pin_set_checked` assert |
| `/private/tmp/g1-i14b-app` | + the six `gpio_dt_spec` symbol references and `g1_gpio0_pin23_spec` | **10,865,770 / 882** | **0** | **final**; 195,865,770 / 883 / 0 resets @2.0 s |

Files changed: new `recon/app/src/{panel_suspend,panel_resume,
panel_set_brightness_level,panel_render_screen_dispatch,projector_clear_canvas,
projector_flush_canvas}.c` (+ `recon/verified/src` mirror, `recon/symbolized/app`
and `recon/named` copies); corrected + re-proven
`recon/app/src/{FUN_000289b0,FUN_00016854}.c` (+ mirrors) and
`recon/symbolized/app/{prepare_system_suspend_state,global_system_resume,
quicknote_buffer_pool_init,gpio_set_pin1_dt_wrapper,gpio_set_fixed_pin_dt,
gpio_set_fixed_output_889f0,subsystem_enable_gpio_pin_set_adapter,
touch_pmic_reset_assert,touch_pmic_reset_deassert}.c` (+ `recon/named` copies of
the first two); `recon/symbols/g1_app_symbols.h` (six `__asm__` aliases, six
`ADDR_*_THUMB`, five new log-string externs, `rodata_889d8`/`889e8`/`889f0`,
`g_screen_render_table`); `recon/symbols/g1_app_globals.ld` (six vtable rebinds,
five log-string pins, `rodata_889d8`, the `g_screen_render_table` RAM pin);
`recon/application/app/src/g1_gpio_dt_specs.c` (`g1_gpio0_pin23_spec`);
`recon/catalogs/function_names_app.json` (six new names);
`recon/generated/app_retained_sources.cmake` (regenerated by its own tool,
1623 → 1629 retained sources); `recon/emulator/scripts/capture_display_sensor_oracle.sh`
(additive `G1_RESC` / `G1_APP_ELF` / `G1_NET_ELF` / `G1_HOOKS` / `G1_CTX_*` /
`G1_P*_SECS` parameters — with none set it is byte-for-byte the previous oracle
capture); new `recon/emulator/reports/sensor_parity_status.md`. Six records
appended to the scratchpad catalogs `app_funcs.json` / `classified.json`
(backed up as `*.i14bak`), the iteration-4/8/13 route. No `tools/` change, no
Kconfig / `prj.conf` / devicetree change, `armemul` untouched. Nothing committed.

## Iteration 15 — the display free-run root cause (a whole `.data` section our
## build never loaded), and four more provably-wrong emissions on the E4 path

**Headline.** The `display_thread_handler` free-run is **root-caused and gone**,
and the cause was not local to the display at all: **every recovered CPUAPP
global below 0x20003e29 is `.data` in the shipped image and our build starts
all of them at ZERO**, because the RAM arena (`g1_ram_arena`, iteration 11) is
plain `.bss`. `g_dashboard_display_level` is one of 106 such globals; its
shipped initialiser is **`0x42` = 66, i.e. `K_MSEC(66)`**, and the clamp in its
only writer (`set_dashboard_display_level_clamped`, 0x48b44, `[0x21, 0x7d]` =
33..125 ms) confirms the units. With 0 the `k_msgq_get` timeout was
`K_NO_WAIT`; with 66 the display thread waits ~15 fps like the original.

Measured effect of that one fix alone (build `g1-i15a`, stage a1, four bytes):
app instructions @2.0 s fall from **195,865,770 to 66,209,805** and unique
functions rise from 883 to **932**; `display_thread_handler` goes from
**2,918,551 entries to 82**, `wake_display_thread_on_reflash` from 729,636 to
19, `memset` from 729,885 entries to 557.

Removing the free-run immediately unmasked four further defects, each found by
following the *first* divergence and each fixed with disassembly evidence:

1. **`sqrtf_hw` was an infinite mutual recursion.** `__builtin_sqrtf` under
   GCC's default `-fmath-errno` lowers to a **call to `sqrtf`**, and our
   `sqrtf` (0x75dc8) calls `sqrtf_hw` — so the emitted pair recursed until SP
   walked below 0x20000000. The shipped body is six bytes,
   `eeb1 0ac0  vsqrt.f32 s0,s0 / 4770  bx lr`; inline `__asm__("vsqrt.f32")`
   now emits **exactly those six bytes**.
2. **The four nPM1300 `linear_range` tables were identity pins.**
   `PROVIDE(rodata_8ba94 = 0x0008ba94)` handed `npm1300_charger_init`
   (`panel_temp_calibration_init`, 0x62644) our build's unrelated flash bytes.
3. **`layout_select_region` (0x84774) dropped three pass-through arguments** —
   the **sixth** member of the class the differential harness is structurally
   blind to.
4. **`delay_busy_wait_usec` called a hardcoded raw original-image address**
   (`(busy_wait_fn_t)0x00088841UL`) — a six-byte busy-wait leaf Ghidra never
   catalogued. Emitted as `coredep_delay_cycles`; the compiled bytes
   `0338fdd87047` are **byte-identical** to the shipped 0x88840.

(2)+(3) together are what kept **E4 out of reach**: the charger init returned
`-EINVAL`, and `main` therefore took its failure branch and **skipped
`call_hook(context, 0xb6c)` — i.e. `jdb_panel_init` — plus
`pt_nfc_eeprom_link_start()` and `notification_system_init()`**. With them
fixed, `panel_temp_calibration_init` (20/197 vs golden 38/398),
`jdb_panel_init`, `panel_init`, `spi_master_init` and
`projector_reset_sequence` all execute for the first time.

**E4 is still not reached.** The new first divergence is `nrfx_spim_xfer`
spinning on `EVENTS_END` (offset +0x118) that never arrives: **0 register
accesses on `spim_a` AND `spim_b`** (verified directly with
`sysbus LogPeripheralAccess`), so the instance's `p_reg` is neither modelled
SPIM. Golden runs `spim_select_instance_by_mode` (2/42) and `nrfx_spim_uninit`
(8/43); ours runs neither. That spin costs 187,696,414 instructions at 2.0 s
and is why the final build's aggregate counters are worse than `g1-i15b`'s.

| metric | iter 14 final `g1-i14b-app` | `g1-i15a-app` | `g1-i15b-app` | `g1-i15c-app` | `g1-i15d-app` | **iter 15 final `g1-i15e-app`** |
|---|---:|---:|---:|---:|---:|---:|
| app instr @0.15 s | 10,865,770 | 6,232,745 | 6,724,014 | 6,674,784 | 6,884,767 | **10,879,768** |
| app unique fns @0.15 s | 882 | 886 | 886 | 888 | 853 | **842** |
| app resets @0.15 s | 0 | 0 | 0 | 0 | **1** | **0** |
| app instr @2.0 s | 195,865,770 | 66,209,805 | **10,157,310** | 10,114,427 | — | 195,879,768 |
| app unique fns @2.0 s | 883 | 932 | **917** | 919 | — | 843 |
| app resets @2.0 s | 0 | **1** | 0 | 0 | — | **0** |
| net instr / fns @0.15 s | 293,078 / 433 | 293,534 / 433 | 293,961 / 433 | 293,961 / 433 | 288,578 / 432 | 288,578 / 432 |
| `radio TransmittedFrames` | 0 | 0 | 0 | 0 | 0 | **0** |
| app FLASH | 632,740 B (64.32 %) | 632,776 B | 635,024 B | 635,096 B | 635,096 B | **635,096 B (64.64 %)**, +2,356 B |
| app RAM | 244,229 B | 244,229 B | 244,229 B | 244,229 B | 244,229 B | **244,229 B**, +0 B |
| `nm -u` undefined / duplicate globals | 0 / 0 | — | 0 / 0 | 0 / 0 | — | **0 / 0** |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | — | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | — | 10/10, EXIT 0 | — | — | **10/10, EXIT 0** |
| `gen_retained_sources.py --check` | clean | clean | clean | clean | clean | **clean** |

No `--allow-multiple-definition`, no weak symbols, no numeric-root hacks, no
`tools/` change, no Kconfig / `prj.conf` / devicetree change. `armemul` is
**untouched**. Net core not rebuilt (`/private/tmp/g1-i9c-net`, unchanged since
iteration 9). Nothing committed.

**On the final-build regression.** `g1-i15e` is worse than `g1-i15b` on raw
instruction count and unique-function count *only because it gets further*: the
three fixes after `g1-i15b` are each proven against the shipped disassembly
(one of them byte-exactly), they turn on `jdb_panel_init` / `panel_init` /
`spi_master_init` / `projector_reset_sequence` — all present in the golden
trace — and they expose the SPIM `p_reg` defect that was previously hidden
behind a `-EINVAL`. Per the standing rule they are **kept, not reverted**, and
both measurements are reported.

### 15.1 Step A — the missing `.data` section (the free-run root cause)

`display_thread_handler` (0x49090) computes its `k_msgq_get` timeout from
`g_dashboard_display_level` (original 0x20002544, bound to `g1_ram_arena +
0x544`). Iteration 14 proved our emitted frame is instruction-for-instruction
the original's, so the defect had to be the *value*. It is:

```
shipped .data load image:  LMA(0x20000000 + x) = flash 0xf6d64 + x
0xf6d64 + 0x2544 = 0xf92a8  ->  42 00 00 00     = 0x42 = 66 (ms)
```

The load-image base is proven three independent ways, all reproduced by
`recon/application/gen_app_data_image.py --selftest`:

| offset | shipped bytes | identity |
|---|---|---|
| `+0x23cc` | `687c0800 53000000` | `g_st25dv_i2c_dev = { bus = 0x00087c68 ("i2c@9000"), addr = 0x53 }` (iteration 11) |
| `+0x2fe3` | `"S100demoglasses"` | `g_product_code_buf` |
| `+0x3003` | `"S100demodevice"` | `g_device_serial_buf` |
| `+0x34f7` | `80 00 00 …` | `g_md5_padding` (canonical MD5 pad block) |

This is **systemic, not a one-off**: of the 676 `PROVIDE(name = g1_ram_arena +
off)` pins, **598 actually resolve inside the arena**, **113 of those sit below
the shipped `.data` end 0x20003e29**, and **106 of those have a non-zero
shipped initialiser** our build replaced with zeros — including
`g_product_code_buf`, `g_device_serial_buf`, the 24 calendar/mail bundle-id
strings in `g_periodic_check_ok_flag`, `g_esb_sync_inbound_status = 0x13`,
`g_gpiote_lock = 0xff`, `g_spline_nan_sentinel = 0x7fc00000`,
`g_batt_soc_curve_charge_lo/hi`, and `g_20002bb8 = 64000000` (the CPU-cycle
constant `delay_busy_wait_usec` divides by).

**The fix** is a generated TU, `recon/application/app/src/g1_app_data_image.c`,
produced by `recon/application/gen_app_data_image.py`, that replays the shipped
`.data` bytes into the arena from a `const` flash image at `SYS_INIT(...,
PRE_KERNEL_1, 0)` — after `z_bss_zero`/`z_data_copy` and before any recovered
device or application initialiser. It is **not** a hardcoded constant: every
byte is read verbatim from `app_update.bin`.

**Policy (deliberately conservative, and documented in the generator).** The
load image also contains **absolute original-image pointers** — flash function
pointers and self-referential SRAM pointers — which are meaningless in our
build; restoring those verbatim would trade a loud NULL for a wild pointer. So
the generator restores only *units* that contain **no** pointer-looking
4-byte-aligned word (flash `[0xC200,0x100000)` or SRAM `[0x20000000,
0x20080000)`), where a unit is a maximal run of non-zero bytes split at every
pinned-object boundary and at every gap of >= 4 zero bytes. Two reviewed
exclusions are listed in the generator: `g_screen_render_table` (0x20002430,
11 x 16 B) because it interleaves screen ids with **function pointers** — ids
without handlers turns "no entry matched" into "matched, call 0", strictly
worse than an all-zero table — and the `k_mem_slab`/`k_mutex` block at
0x200037b8..0x20003890 whose only non-pointer field is a scalar. Everything
dropped keeps today's zero-initialised behaviour exactly.

Result: **85 runs, 1,199 bytes** restored (stage a2). FLASH grows 632,776 B
(`g1-i15a`) -> 635,024 B (`g1-i15b`), i.e. +2,248 B, which also carries the
15.2 fix; RAM +0 B.
The remaining 105 dropped units are the obvious follow-up: they need the
`g1_st25dv_i2c_dev` treatment (emit the object and re-point) or, for
self-referential SRAM pointers that land inside the arena, an arena-relative
relocation the generator does not do yet.

### 15.2 `sqrtf_hw`: `__builtin_sqrtf` is not `vsqrt.f32`

`g1-i15a` (stage a1) ran clean at 0.15 s but **reset in the 2.0 s run** (fault at app instruction 8,550,305, just past the 0.15 s mark). Trace:

```
sqrtf(0x47b68) -> sqrtf_hw(0x77e90) -> b.w 0x47b68 <sqrtf> -> ...
  each cycle: push {r3,lr} + vpush {d8}  = 16 bytes, lr = 0x47b77
  SP walks down past 0x20000000 (first out-of-range write logged by Renode:
    [cpuapp: 0x47B68] WriteDoubleWord at 0x1FFFFFF8, value 0x2000C594)
  -> exception return unstacks PC = 0 -> z_arm_usage_fault -> z_fatal_error
  -> sys_arch_reboot
```

`recon/symbolized/app/sqrtf_hw.c` said `return __builtin_sqrtf(value);`. Under
`-fmath-errno` (the default; Zephyr does not disable it) GCC lowers that to a
**tail call to `sqrtf`**, and `sqrtf` calls `sqrtf_hw`. The shipped 0x869c6 is
six bytes — `eeb1 0ac0 / 4770` — so the body is now
`__asm__("vsqrt.f32 %0, %1")`, which compiles to exactly those two
instructions. `cfg_verify.verify('app','FUN_000869c6')` **PASS**.

This one is worth naming as a class of its own: **a compiler builtin that is
semantically right but codegen-wrong**, invisible to a differential harness
whose callees are order-keyed oracles (the recursion never happens under
`emu.compare`, which stubs `sqrtf`).

### 15.3 The E4 blocker: `main` skipped `jdb_panel_init` because the nPM1300
### charger init returned `-EINVAL`

With the free-run gone, `main` ran to completion but **stopped at
`k_sem_take(..., K_FOREVER)` in its event loop having taken the failure
branch**. Walking the PCs it executed:

```
16d34  z_device_is_ready(fuel_gauge)          -> ready
16d50  z_device_is_ready(fuel_config)         -> ready
16e06  fuel_gauge_sample_init_timestamp(...)  -> >= 0
16e14  panel_temp_calibration_init(...)       -> < 0     <<< failure branch
16e1c/16d5a -> 16f0c   : SKIPS call_hook(ctx,0xb10), call_hook(ctx,0xb6c)
                         = jdb_panel_init, pt_nfc_eeprom_link_start(),
                           notification_system_init(), read_rtc_counter_ms()
```

`panel_temp_calibration_init` (0x62644) is the recovered `npm1300_charger_init`.
Its config struct is byte-identical to the original's
(`npm1300_charger_config_0` at our 0x8ba48 vs the shipped 0x8ba14: term
4,400,000 uV, warm 4,100,000 uV, 40,000 uA, 1,000,000 uA, 500,000 uA, four
`INT_MAX` thermistor slots, 100,000 ohm, beta 4,250 — every word matches). The
failure was in the lookup, and it had **two** independent causes.

**(a) Four identity pins that are DATA, not addresses.** The four
`struct linear_range` tables the charger init searches were still
`PROVIDE(rodata_8ba64 = 0x0008ba64)` etc. Read off the shipped image they
decode exactly as Zephyr 3.4.99's `npm1300_charger.c` tables:

```
0x8ba64 vbus_limit      { 100000,      0,  1,   1 }, { 500000, 100000, 5, 15 }
0x8ba7c dischg_limit    { 268090,   3230, 83, 415 }
0x8ba88 charger_current { 32000,    2000, 16, 400 }
0x8ba94 charger_volt    { 3500000, 50000,  0,   3 }, { 4000000, 50000, 4, 13 }
```

All four are interior views of one contiguous 72-byte block, so they are
emitted as one object (`recon/application/app/src/g1_npm1300_linear_ranges.c`,
byte-exact) and the four pins bound at their original relative offsets.
(`recon/data/rodata_0x8ba64.c` is the byte-verified owner of the first 52 bytes
of the same block but stops four bytes into `charger_volt_ranges`, so it cannot
be the binding target; it is left untouched so the verified-data ledger stays
as generated.)

**(b) `layout_select_region` (0x84774) dropped three pass-through arguments.**
Even with correct tables it still returned -22. The original is a tail call
that forwards **all four** arguments to 0x84602 (`flash_page_index_lookup`):

```
84774  push {r4,r5,r6}                       <- r1, r2, r3 are never touched
84776  ldrh r4,[r0,#8] ; ldrh r5,[r0,#10] ; subs r5,r5,r4
8477c  ldrd r4,r6,[r0] ; mla r4,r6,r5,r4 ; cmp r1,r4 ; ble 8479c
84788  ldrh r4,[r0,#20]; ldrh r5,[r0,#22]; subs r5,r5,r4
8478e  ldrd r4,r6,[r0,#12]; mla r4,r6,r5,r4; cmp r1,r4; bgt 847a2
8479a  adds r0,#12
8479c  pop {r4,r5,r6} ; b.w 0x84602
```

Our body was declared `layout_select_region(int *param_1, int param_2)`, so GCC
used **r2 and r3 as scratch** (`subs r2,r2,r3` at our 0x77b82/0x77b94) and
`max` arrived at `flash_page_index_lookup` as `max_idx - min_idx` = **9**
instead of 4,400,000 — `cmp r2,r6 ; bge` at our 0x77b2e/0x77b34 then failed
against `range->min` = 4,000,000 and returned `-EINVAL`. Declaring all four
parameters and forwarding them fixes it. `cfg_verify` **PASS** for both
`FUN_00084774` and `FUN_00084602` after the change — as expected, because the
harness never compares a callee's argument registers. **Sixth** member of this
class (dropped register args, dropped stack args, wrong indirection levels,
stack writes, collapsed stack objects, and now dropped *pass-through* args).

### 15.4 `delay_busy_wait_usec` executed rodata

`g1-i15d` (with 15.3 fixed) reached `jdb_panel_init` -> `panel_init` ->
`projector_reset_sequence` -> `delay_ms` and then died:

```
<err> os: Attempt to execute undefined instruction
<err> os: Faulting instruction address (r15/pc): 0x00088854   r14/lr: 0x00076fa1
<err> os: >>> ZEPHYR FATAL ERROR 36  -> Resetting system
```

`recon/symbolized/app/delay_busy_wait_usec.c` (FUN_0004c254) contained
`busy_wait_fn_t const busy_wait = (busy_wait_fn_t)0x00088841UL;` — a **raw
original-image Thumb address**, faithfully copied from the original's literal
pool (0x4c274: `.word 0x00088840`, `orr #1`, `bx r3`) but never rebound. Our
build puts unrelated rodata at 0x88840. The target is a six-byte leaf Ghidra
never catalogued, referenced from **nowhere else in the image**:

```
88840  3803  subs r0, r0, #3
88842  d8fd  bhi  .-2
88844  4770  bx   lr
```

i.e. nrfx's `nrfx_coredep_delay_us` three-cycle busy-wait kernel. It is now a
proper reconstruction, `coredep_delay_cycles` (canonical
`recon/app/src/FUN_00088840.c`), registered in
`recon/catalogs/function_names_app.json` and the scratchpad catalogs, with the
consumer changed to `ADDR_coredep_delay_cycles_THUMB`. **Proof: the compiled
`.text` is `0338fdd87047` — byte-identical to the shipped six bytes.** (This is
strictly stronger than a differential proof; `cfg_verify` cannot drive it,
returning `FAIL` with `checked: 0` because the busy-wait has no comparable
side effects.) The restored `.data` value `g_20002bb8 = 64000000` from 15.1 is
what makes the arithmetic right: `delay_ms(1)` -> 1000 us -> 64,000 cycles ->
21,333 loop iterations, which is exactly the 42,669 instructions the trace now
attributes to `coredep_delay_cycles`.

Same sub-class as iteration 14 section 14.3, and the sweep flagged there is now
quantified: **2,569 `PROVIDE(rodata_xxxxx = 0x000xxxxx)` identity pins remain**
in `g1_app_globals.ld`. Most are log-format strings (harmless-looking garbage
output); the dangerous ones are the two kinds found this iteration —
**dereferenced data tables** and **called function pointers**.

### 15.5 The new first divergence — `nrfx_spim_xfer` polls a SPIM that is not
### `spim_a` or `spim_b`

`g1-i15e` boots reset-free and reaches the panel bring-up, then hangs:

| function | ours @2.0 s | golden |
|---|---:|---:|
| `nrfx_spim_init` | 3 / 24 | 3 / 24 |
| `nrfx_spim_xfer` | 247 / **187,696,414** | 170 / 3,774 |
| `spim_select_instance_by_mode` | **ABSENT** | 2 / 42 |
| `nrfx_spim_uninit` | **ABSENT** | 8 / 43 |
| `spi_master_trans_data_tx_rx` | 1 / 13 | 68 / 714 |
| `projector_send_cmd_immediate` | **ABSENT** | 90 / 360 |
| `panel_init` | 1 / 6 | 20 / 52 |

The hot PCs are `0x63b12/16/18` — `ldr r3,[r4,#0x118] ; cmp r3,#0 ; beq .-6`,
i.e. polling `EVENTS_END` after `str r1,[r4,#0x10]` (`TASKS_START`). Measured
with `sysbus LogPeripheralAccess sysbus.spim_a/spim_b true` over 0.30 s:
**zero register accesses on either instance**, and `spim_a.jbd FrameCounter` =
`JournalCount` = 0. `spim_select_instance_by_mode` (0x26338) is the function
that writes the base — `mode == 3 -> 0x5000c000` (`spim_b`),
`mode == 4 -> 0x5000a000` (`spim_a`) — into `event+0xc`, and **it never runs in
our build** while golden runs it twice. So the `nrfx_spim_t` our
`nrfx_spim_xfer` receives still has an unset/uninitialised `p_reg`. That is
iteration 16's Step A.

### Regenerate (iteration 15)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py --selftest
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py --stage a2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check          # clean
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
                                                                                # EXIT=0, 10/10
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify as c;\
 [print(n, c.verify('app',n)['status']) for n in ('FUN_000869c6','FUN_00084774','FUN_00084602')]"
                                                                                # 3x PASS
# byte proof for the new 6-byte leaf:
#   arm-zephyr-eabi-gcc -c -Os -mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard \
#     -ffunction-sections recon/app/src/FUN_00088840.c  ->  .text = 0338fdd87047
recon/application/build_cohesive.sh app /private/tmp/g1-i15e-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i15e-app/zephyr/zephyr.elf                                  # EXIT=0
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i15e  /private/tmp/g1-i15e-app /private/tmp/g1-i9c-net 0.15
<scratchpad>/mkrun.sh i15e2 /private/tmp/g1-i15e-app /private/tmp/g1-i9c-net 2.0
# Step B capture + diff: see recon/emulator/reports/sensor_parity_status.md section 1
```

Bisect ledger (every build and boot actually run):

| build | change | app @0.15 s | resets | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i15a-app` | + arena `.data` restore, stage a1 (only `g_dashboard_display_level`, 4 B) | 6,232,745 / 886 | 0 @0.15 s; **1 in the 2.0 s run** (fault at app instr 8,550,305) | free-run gone (2,918,551 -> 82 `display_thread_handler` entries); unmasks the `sqrtf`/`sqrtf_hw` recursion |
| `/private/tmp/g1-i15b-app` | + stage a2 (85 runs / 1,199 B) + `sqrtf_hw` inline VSQRT | 6,724,014 / 886 | **0** | **10,157,310 / 917 / 0 resets @2.0 s** — best aggregate |
| `/private/tmp/g1-i15c-app` | + the four nPM1300 `linear_range` pins bound to an emitted block | 6,674,784 / 888 | 0 | 10,114,427 / 919 @2.0 s; charger init still `-EINVAL` |
| `/private/tmp/g1-i15d-app` | + `layout_select_region` 4-argument pass-through | 6,884,767 / 853 | **1** | charger init succeeds; `jdb_panel_init`/`spi_master_init` run; dies executing rodata at 0x88854 |
| `/private/tmp/g1-i15e-app` | + `coredep_delay_cycles` (0x88840) emitted and bound | 10,879,768 / 842 | **0** | **final**; 195,879,768 / 843 / 0 resets @2.0 s, dominated by the `nrfx_spim_xfer` poll |

Files changed: new `recon/application/gen_app_data_image.py` (generator +
`--selftest`) and its generated
`recon/application/app/src/g1_app_data_image.c`; new
`recon/application/app/src/g1_npm1300_linear_ranges.c`; new
`recon/app/src/FUN_00088840.c` (+ `recon/verified/src` mirror,
`recon/named/coredep_delay_cycles.c`,
`recon/symbolized/app/coredep_delay_cycles.c`); corrected + re-proven
`recon/app/src/{FUN_000869c6,FUN_00084774}.c` (+ `recon/verified/src` mirrors,
`recon/named/{sqrtf_hw,layout_select_region}.c`,
`recon/symbolized/app/{sqrtf_hw,layout_select_region}.c`);
`recon/symbolized/app/delay_busy_wait_usec.c` and
`recon/named/delay_busy_wait_usec.c` (raw 0x00088841 -> named symbol);
`recon/symbols/g1_app_symbols.h` (one `__asm__` alias + one `ADDR_*_THUMB`);
`recon/symbols/g1_app_globals.ld` (four `rodata_8baXX` rebinds);
`recon/application/app/CMakeLists.txt` (two new wiring TUs);
`recon/catalogs/function_names_app.json` (one new name);
`recon/generated/app_retained_sources.cmake` (regenerated by its own tool,
1,629 -> 1,630 retained sources);
`recon/emulator/reports/sensor_parity_status.md` (rewritten in place). One
record appended to the scratchpad catalogs `app_funcs.json` / `classified.json`
(backed up as `*.i15bak`). No `tools/` change, no Kconfig / `prj.conf` /
devicetree change, `armemul` untouched. Nothing committed.

## Iteration 16 — SPI reaches the panel: the panel-init sequence is now
## byte-identical to the shipped firmware (G-5), and `.data` pointers are
## restored relocation-aware

**Headline.** The iteration-15 `nrfx_spim_xfer` spin is gone and **our firmware
now drives the real JBD microdisplay**: the first **33 `spim_a` transactions of
our boot are BYTE-IDENTICAL to the shipped firmware's**, covering the entire
panel-init block of `display_sensor_parity.md` §3.1 — the `0x9F` ID probe
answered `0x4010`, the three-band 153,600 B full-panel clear, the five `0xC0`
words and both `0x46`/`0x31` brightness pairs. **G-5 passes on all four of its
enumerated elements.** `nrfx_spim_xfer` falls from **247 entries /
187,696,414 instructions to 165 / 3,663** against golden's 170 / 3,774, and
`panel_init` matches golden **exactly** at 20 / 52.

Two independent defects were fixed, and each unmasked the next one.

### 16.1 Step A — the SPIM `p_reg` defect (three identity pins)

`spi_master_init` (`FUN_00026418` @0x26418) builds the mode-4 `nrfx_spim_t` by
**copying two words of flash data**, not by using an immediate:

```
26424: ldr r2,[pc,#308]   ; literal @0x2655c = 0x000883b0
2642a: ldmia.w r2,{r0,r1} ; r0 = *(0x883b0), r1 = *(0x883b4)
26430: stmia.w r5,{r0,r1} ; -> sp+24, the mode-4 pair
...
264ae: (mode 4) ldmia r5!,{r0,r1} ; str r0,[r4,#12] / str r1,[r4,#16]
```

Verified against `app_update.bin` through `tools/extract.py`'s VA mapping
(`off = va - 0xC200 + 0x200`; the image carries a 0x200-byte MCUboot header,
magic `0x96f3b83d`, so a naive `va - 0xC200` read is off by 0x200 and yields
garbage):

```
0x883b0 = 0x5000a000   NRF_SPIM base -> `spim_a`
0x883b4 = 0x00000001   drv_inst_idx
0x883b8 = 0x000037f8
```

All three were still **identity pins**, so our build read its own unrelated
rodata and `p_reg` pointed into FLASH: `nrfx_spim_xfer` wrote `TASKS_START`
into read-only memory and polled `EVENTS_END` forever. Mode 3 was never
affected because it uses an **immediate** literal (`0x2655c-4` = `0x5000c000`),
which is exactly why only the display path was broken.

`recon/data/rodata_0x88340.c` is the byte-verified owner of that block and
already carries `0x5000a000 / 0x00000001 / 0x000037f8` at indices 28/29/30, so
the three pins are bound at their original relative offsets rather than
re-emitted:

```
PROVIDE(rodata_883b0 = rodata_0x88340 + 0x70);   /* -> 0x88720 in our link */
PROVIDE(rodata_883b4 = rodata_0x88340 + 0x74);
PROVIDE(rodata_883b8 = rodata_0x88340 + 0x78);
```

Build `g1-i16-app`. Effect: SPI reaches the panel for the first time, and the
run immediately hits a **new** fault (§16.2).

### 16.2 Step B — `.data` function pointers, restored RELOCATION-AWARE

With the SPIM spin removed, the boot ran on and took a
**USAGE FAULT / "Illegal use of the EPSR"** (INVSTATE) at `alloc_zeroed_node`
+0x6 with **`r3 = 0x00000000`** — `blx r3` on a NULL allocator:

```
0x00077cf6:  4798  blx r3        ; r0 = 0x28, r3 = 0
>>> ZEPHYR FATAL ERROR 35 ; fatal_error: Resetting system
```

Root cause: `g_cjson_hooks` (0x20002bac) is cJSON's
`internal_hooks = { malloc, free, realloc }`, and iteration 15's conservative
policy **drops every `.data` group containing a pointer word**, so all three
hooks were zero. The shipped initialiser is
`{ 0x00076d6d, 0x00076d7d, 0x000778e5 }`; `0x778e4` is uncatalogued and its
disassembly (`ldr r3,[pc,#8] (=0x20002d20, _impure_ptr) ; mov r2,r1 ; mov r1,r0
; ldr r0,[r3] ; b.w 0x876ec`) identifies it as newlib's
`realloc(p,n) -> _realloc_r(_impure_ptr,p,n)` thunk.

`recon/application/gen_app_data_image.py` gained **stage a3**, which restores
such a group *relocation-aware*: the bytes are copied and then **every pointer
word is overwritten with the address the symbol has in OUR link**, taken from
the linker through an `__asm__`-alias extern — never a raw absolute. Two exact
resolution classes are allowed, and a group is accepted **only if every pointer
word in it resolves**, so iteration 15's "a half-initialised table is worse than
an all-zero one" rule still holds:

* **FLASH pointer** → the catalogued function name for `word & ~1`, emitted as
  `*(void **)&g1_ram_arena[off] = (void *)((unsigned long)&__g1_dp_NAME | 1u)`.
* **SRAM pointer that points inside the group's own bytes** →
  `g1_ram_arena + (word - 0x20002000)`. These are the self-referential
  `sys_dlist_t` heads of the shipped kernel objects (`k_mutex` wait_q,
  `k_mem_slab`, work queues) — i.e. exactly the group the iteration-15 header
  deferred as *"needs arena-relative pointer relocation, which this generator
  does not do yet"*. **Restricting to self-references is what makes this safe**:
  a pointer to any *other* RAM address could name an object bound OUT of the
  arena (like `g_st25dv_i2c_dev`), whose arena slot is dead storage.

Restore units/bytes: **85 runs / 1,199 B → 146 runs / 1,899 B**, i.e. **61 new
groups / 700 B**, plus **155 relocated pointer words** (8 distinct flash
symbols: `malloc`, `free`, `realloc`, `settings_nvs_load`,
`app_event_manager_process_events`, `bt_gatt_pairing_complete`,
`qspi_nor_pm_action`, `uarte_nrfx_pm_action`). `g_screen_render_table` and
`g_st25dv_i2c_dev` correctly remain dropped (their pointers do not resolve).
Build `g1-i16b-app`; the cJSON fault is gone and unique functions rise
**884 → 907**.

### 16.3 Measurements (every number below was actually run)

| metric | `g1-i15b-app` (best aggregate) | `g1-i15e-app` (iter 15 final) | `g1-i16-app` (Step A) | **`g1-i16b-app` (Step A+B)** |
|---|---:|---:|---:|---:|
| app instr @0.15 s | 6,724,014 | 10,879,768 | 8,200,768 | **7,878,667** |
| app unique fns @0.15 s | 886 | 842 | 884 | **907** |
| app instr @2.0 s | 10,157,310 | 195,879,768 | 8,200,768 | **7,878,667** |
| app unique fns @2.0 s | **917** | 843 | 884 | **907** |
| SoC resets | 0 | 0 | **1** | **1** |
| net instr / fns @0.15 s | 293,961 / 433 | 288,578 / 432 | 288,578 / 432 | **288,578 / 432** |
| `radio TransmittedFrames` | 0 | 0 | 0 | **0** |
| app FLASH | 635,024 B | 635,096 B | 635,096 B | **639,556 B (65.09 %)** |
| app RAM | 244,229 B | 244,229 B | 244,229 B | **244,229 B** |
| `nm -u` undefined / duplicate | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | 10/10, EXIT 0 | 10/10, EXIT 0 | **10/10, EXIT 0** |
| `gen_retained_sources.py --check` | clean | clean | clean | **clean** |

The @2.0 s and @0.15 s figures are identical for both iteration-16 builds
because the SoC resets at **t ≈ 0.104 s** and Renode's nRF5340 platform has no
reset macro, so both cores halt there. **This is an honest regression on the
aggregate counters and it is reported as such**: `g1-i15b-app` still has the
better instruction/unique-function aggregate, and `g1-i15e-app` still runs the
sensor threads for the full 6 s. Iteration 16 buys correct, byte-exact display
behaviour at the cost of dying earlier — the same "further into a new stall"
trade iteration 15 documented, so **both builds are reported**.

SPI/display markers (ours `g1-i16b-app` vs golden):

| function | ours entries / instr | golden |
|---|---|---|
| `nrfx_spim_init` | **3 / 24** | 3 / 24 |
| `nrfx_spim_xfer` | **165 / 3,663** | 170 / 3,774 |
| `spi_master_trans_data_tx_rx` | **66 / 693** | 68 / 714 |
| `panel_init` | **20 / 52** | 20 / 52 |
| `spi_read_id` | **5 / 30** | fires |
| `spim_select_instance_by_mode` | ABSENT | 2 / 42 |
| `nrfx_spim_uninit` | ABSENT | 8 / 43 |
| `projector_send_cmd_immediate` | ABSENT | 90 / 360 |

E4 markers **gained**: `spi_read_id`, and the whole panel-init SPI block.
E4 markers still **missing**: `panel_on`, `panel_resume`, `bt_enable`,
`radio TransmittedFrames` = 0.

### 16.4 Graphics parity results

Measured with the oracle capture script against `g1-i16b-app`, identical
determinism knobs and stimulus.

| id | verdict | detail |
|---|---|---|
| **G-5** | **PASS (all four enumerated elements)** | `0x9F tx=9F000000 rx=00004010` probe answered and accepted; three-band clear `61446 / 61446 / 30726` B (= 153,600 pixel bytes); five `0xC0` words `0000 / 0014 / 1800 / 1814 / 0C0A` each followed by `0x97`; both brightness pairs `0x46=0F,0x31=04` and `0x46=00,0x31=04`. **Transactions 0–32 are byte-identical to the oracle.** The one §3.1 item we do not emit is the trailing `0xB9 FF` at index 33, cut off by the §16.5 reset. |
| **G-3** | **FAIL** | `spim_a.p1_boot` stream sha256 ours `8df70cec…` vs oracle `b64599b1…`; **33 vs 764** transactions. The **entire 33-transaction common prefix is identical** — the divergence is pure truncation at index 33 (`0xB9 tx=B9FF`), not a wrong byte. |
| **G-1** | **FAIL** | `p2_render` framebuffer: ours **0 lit pixels**, oracle **1,098**. We never render — the SoC resets before the dashboard paints. |
| **G-2** | **FAIL** | `p1_boot` framebuffer: ours 0 lit pixels / sha `0c5cc90b…`, oracle 656 lit pixels / sha `1d617c65…`. **G-4 localiser: first differing row y = 267, first differing pixel x = 178** (oracle `ffffff`, ours `000000`) — exactly the top-left of the oracle's lit bbox (178,267)–(449,287). Our panel is correctly *cleared*, just never painted. |
| **G-6** | **PASS** | `spim_b` transaction count **0** in both phases (hash EQ), as required. |

### 16.5 The new first divergence — the NFC EEPROM ops table (`.data`, 5 pointers)

After Step B the boot dies at a *different* NULL `blx`, at `attr_store_get`+0x6:

```
0x0002c6fe:  4798  blx r3      ; r6 = &g_pt_nfc_link_cfg, r3 = *(*(r6)) = 0
USAGE FAULT / Illegal use of the EPSR ; fatal_error: Resetting system
```

Causal chain, fully established:

1. `pt_nfc_eeprom_link_start` (0x30c90) calls
   `pt_nfc_eeprom_link_init(&g_pt_nfc_link_cfg_static)` — arena **+0x408**.
2. `pt_nfc_eeprom_link_init` (0x30b3c) returns −1 unless `param_1[0..3]` are
   **all non-zero**, and only then sets `g_pt_nfc_link_cfg`.
3. The shipped `.data` at arena+0x408 is the ops table
   `{ 0x00030c25, 0x00030c61, 0x0007d0c1, 0x0007d0c3, 0x00087c50, 0x6b }`;
   our build zeroes it, the guard fails, `g_pt_nfc_link_cfg` stays NULL, and
   `attr_store_get` dereferences it. Measured: `pt_nfc_eeprom_link_init`
   1 entry / **8 instructions** (the guard, and nothing else).
4. Stage a3 cannot yet restore this group because **not one of its five
   pointers resolves**:

| pointer | identity | status in our build |
|---|---|---|
| `0x30c24` | `misc_dev_api_transfer_op12` (catalogued, EXACT) | **garbage-collected** — the zeroed table was its only referrer |
| `0x30c60` | uncatalogued; **INTERIOR** to `misc_dev_api_transfer_op12` | Ghidra folded it into the preceding symbol |
| `0x7d0c0` | uncatalogued 2-byte `bx lr` stub; **INTERIOR** to `read_rtc_counter_ms` | same fold |
| `0x7d0c2` | uncatalogued; **INTERIOR** to `read_rtc_counter_ms` | same fold |
| `0x87c50` | `struct device`, name string **`"i2c@b000"`** (i2c2 / twim2) | needs `DEVICE_DT_GET` treatment like `g1_st25dv_i2c_dev` |

This is the **seventh** instance of the recurring "Ghidra folded a sibling
function into the tail of the preceding symbol" class (iteration 15 hit it as
`panel_suspend` / `panel_resume` / `coredep_delay_cycles`). **Iteration 17's
Step A** is therefore: split `0x30c60`, `0x7d0c0`, `0x7d0c2` out as emitted
objects, force-retain `misc_dev_api_transfer_op12`, bind `0x87c50` to
`DEVICE_DT_GET(DT_NODELABEL(i2c2))`, and let stage a3 restore arena+0x408.

### 16.6 `.data` follow-up status

Iteration 15 left **106 of 598** arena-resolving pins with non-zero shipped
initialisers zeroed. Stage a3 clears **61 groups / 700 B** of that backlog
relocation-aware. The remaining dropped set is **152 groups / ~1,801 B**,
dominated by pointers that name (a) GC'd or Ghidra-folded functions (the §16.5
class), (b) `struct device` pointers needing `DEVICE_DT_GET`, and (c) SRAM
pointers to objects bound OUT of the arena. None of these are byte-copyable;
each needs a named owner, which is the correct next unit of work.

### Regenerate (iteration 16)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
# Step A: the three SPIM pins are already in recon/symbols/g1_app_globals.ld
recon/application/build_cohesive.sh app /private/tmp/g1-i16-app
# Step B:
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py --selftest
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
    --stage a3 --elf /private/tmp/g1-i16-app/zephyr/zephyr.elf
recon/application/build_cohesive.sh app /private/tmp/g1-i16b-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i16b-app/zephyr/zephyr.elf                       # EXIT 0, 0/0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py \
    --trials 120                                                     # EXIT 0, 10/10
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i16b  /private/tmp/g1-i16b-app /private/tmp/g1-i9c-net 0.15
<scratchpad>/mkrun.sh i16b2 /private/tmp/g1-i16b-app /private/tmp/g1-i9c-net 2.0
# graphics + sensors:
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i16b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i16b2
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
    /tmp/g1_ours_i16b2 <scratchpad>/i16/rep_i16b
```

Bisect ledger (every build and boot actually run):

| build | change | app @0.15 s | resets | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i16-app` | Step A: three `rodata_883b*` pins bound to `rodata_0x88340 + 0x70/0x74/0x78` | 8,200,768 / 884 | **1** | **SPI reaches the panel**; `nrfx_spim_xfer` 187.7 M → 3,663 instr; new NULL-`blx` fault in `alloc_zeroed_node` (cJSON hooks) |
| `/private/tmp/g1-i16b-app` | + Step B: `gen_app_data_image.py` stage a3 (relocation-aware pointers) | 7,878,667 / **907** | **1** | cJSON fault gone; **G-5 passes**; new first divergence = the NFC ops table (§16.5) |

Files changed: `recon/symbols/g1_app_globals.ld` (three SPIM pins);
`recon/application/gen_app_data_image.py` (stage a3 + `resolve_pointer` +
`our_symbols` + `UNCATALOGUED`); regenerated
`recon/application/app/src/g1_app_data_image.c`;
`recon/emulator/reports/sensor_parity_status.md` (rewritten in place); this
report. **No `tools/` change**, no Kconfig / `prj.conf` / devicetree change,
`armemul` untouched. Nothing committed.

## Iteration 17 — the reset is gone: the NFC ops table is restored, the boot
## runs reset-free to 5.09 s, and the painting path is now blocked by ONE named
## defect on the NET core

**Headline.** The iteration-16 `t ≈ 0.104 s` reset is **fixed**. The shipped
`.data` ops table at arena `+0x408` is restored relocation-aware, so
`pt_nfc_eeprom_link_init` succeeds (2 entries / **32** instructions vs golden's
2 / 33, up from 1 / **8**), `g_pt_nfc_link_cfg` is non-NULL and `attr_store_get`
no longer faults. `/private/tmp/g1-i17d-app` boots **reset-free through 2.0 s
with 996 unique functions and 11,684,715 instructions** (previous best
aggregate, `g1-i15b`: 917 / 10,157,310; golden 12,629,795), and the whole SPI
display block, the NFC link and the sensor threads all run.

Everything the reset was suppressing came back at once:

| device, `p1_boot` | oracle | `g1-i15e` | `g1-i16b` | **`g1-i17d`** |
|---|---:|---:|---:|---:|
| `twim2` LSM6DSO | 1,089 | 969 | 25 | **983** |
| `twim1` nPM1300 | 291 | 85 | 85 | **199** |
| `twim1` OPT3001 | 33 | 7 | 7 | **14** |
| `twim1` ST25DV system port (0x57) | 22 | 6 | 6 | **12** |
| `twim1` ST25DV NFC EEPROM (0x53) | 25 | 0 | **0** | **11** |
| `saadc` register accesses | 998 | — | 5 | **17** |
| `spim_a` | 764 | 0 | 33 | **34** |

**G-5 still passes**, and the `spim_a` prefix grew by one: **all 34 transactions
we emit are byte-identical to the oracle's first 34**, now including the
trailing `0xB9 FF` that iteration 16 was cut off before. **G-1/G-2 still fail
with 0 lit pixels** — and iteration 17 establishes *exactly* why, with a
reproducible log line rather than an inference (§17.5).

Four defects were fixed, three of them new members of classes this project has
a playbook for, and one of them a **provably-wrong emission the harness is
structurally blind to** that was found while reading the ops table.

### 17.1 Step A — the NFC EEPROM ops table (arena +0x408)

The shipped `.data` at `0x20002408` is
`{ 0x00030c25, 0x00030c61, 0x0007d0c1, 0x0007d0c3, 0x00087c50, 0x6b }`, and
`pt_nfc_eeprom_link_init` (0x30b3c) returns −1 unless the first four words are
all non-zero:

```
30b4a  ldr r3,[r0,#0]  ; cmp r3,#0 ; beq -1
30b50  ldr r3,[r0,#4]  ; cmp r3,#0 ; beq -1
30b56  ldr r3,[r0,#8]  ; cmp r3,#0 ; beq -1
30b5c  ldr r3,[r0,#12] ; cmp r3,#0 ; beq -1
30b62  ldr r3,=g_pt_nfc_link_cfg ; str r0,[r3,#0]
```

Reading 0x30c24's frame gives the table's meaning: `base = *(0x20002418)` is a
`struct device *`, `field = base[8]` its `api`, `fp = api[8]` the i2c
`transfer` op, and the two 0x30cXX entries hand it a `{ buf, len, flags }`
descriptor array. So slots 0/1 are register-read / register-write, slot 2 a
no-op and slot 3 a delay; slot 4 is the bus device and slot 5 (`0x6b`) the
address.

Each of the five pointers needed a different remedy, exactly as iteration 16
predicted:

| pointer | identity | remedy |
|---|---|---|
| `0x30c24` | `misc_dev_api_transfer_op12` (catalogued) | was **garbage-collected**; the address-taken reference stage a3 now emits is what roots it (§17.3) |
| `0x30c60` | uncatalogued, **interior** to `misc_dev_api_transfer_op12` | reconstructed as **`misc_dev_api_write_op12`** |
| `0x7d0c0` | uncatalogued 2-byte `bx lr`, **interior** to `read_rtc_counter_ms` | reconstructed as **`nfc_link_ops_noop`** |
| `0x7d0c2` | uncatalogued, **interior** to `read_rtc_counter_ms` | reconstructed as **`nfc_link_delay_msec`** |
| `0x87c50` | `struct device`, name `"i2c@b000"`, `config->base` `0x5000b000` | new **`DEVICE_DT_GET(DT_NODELABEL(i2c2))`** resolution class |

This is the **seventh** instance of the "Ghidra folded a sibling function into
the tail of the preceding symbol" class. Both containers' own reconstructions
already stopped at the true code extent, so only the folded siblings were
missing. Their identities are read straight off the image:

* **`misc_dev_api_write_op12` @0x30c60** (code 0x30c60..0x30c8a, literal pool
  0x30c8c = `0x20002418`): one `{ buf, len, flags = 2 }` descriptor
  (`I2C_MSG_WRITE|I2C_MSG_STOP`), `transfer(dev, &msg, 1, 0x12)`.
* **`nfc_link_ops_noop` @0x7d0c0**: the shipped bytes are exactly `4770`.
  **PROOF: the compiled `.text` is `4770`, byte-identical.**
* **`nfc_link_delay_msec` @0x7d0c2** (code 0x7d0c2..0x7d0e8, next catalogued
  entry `serial_data_read_dispatch` 0x7d0e8):
  `bic.w r4,r0,r0,asr #31` (= `MAX(ms,0)`), `smlal` against `0x8000` with a
  999 bias, `__aeabi_uldivmod` by 1000, then `b.w k_sleep` — i.e.
  `k_sleep(K_MSEC(ms))`, because with `CONFIG_SYS_CLOCK_TICKS_PER_SEC = 32768`
  Zephyr 3.4's `Z_TIMEOUT_MS(t)` is `k_ms_to_ticks_ceil64(MAX(t, 0))`. The
  compiled body is the shipped instruction sequence modulo the scheduling of
  two independent `mov`s and the two relocated branch targets.

`cfg_verify.verify('app', …)` **PASS** for all three (40 CFG-directed checks
each) plus the corrected 0x30c24 (§17.2).

### 17.2 A provably-wrong emission found while reading the table:
### `misc_dev_api_transfer_op12` had **five of its six stack stores deleted**

The shipped 0x30c24 writes a two-element descriptor array before the call:

```
30c2a  strd r4,r1,[sp]        ; msgs[0] = { param_1, param_2 }
30c38  strb r1,[sp,#8]        ; msgs[0].flags = 0
30c2e  strd r2,r3,[sp,#12]    ; msgs[1] = { param_3, param_4 }
30c3e  strb r3,[sp,#20]       ; msgs[1].flags = 7
30c4c  blx  api->transfer(dev, msgs, 2, 0x12)
```

The recovered body declared the six fields as **separate stack scalars** and
passed only `&local_20`. Taking the address of `local_20` does not make the
others escape, so GCC legally dropped their stores — and did. Compiled, the
emitted frame was

```
push {r0,r1,r4,lr} ; str r0,[sp,#4] ; ... ; add r1,sp,#4 ; blx r4
```

i.e. **one** of the six shipped stores survived; the callee read whatever was
on the stack. Re-expressed as a real `struct g1_i2c_msg msgs[2]` the emitted
frame is instruction-for-instruction the original's (only the `0x20002418`
address materialisation differs, because our build reaches that global through
a linker pin instead of a literal pool). This is the **seventh** member of the
family the differential harness is structurally blind to (dropped register
args, dropped stack args, wrong indirection levels, stack writes, collapsed
stack objects, dropped pass-through args, and now **collapsed stack objects
that GCC deletes outright**) — `cfg_verify` returns **PASS both before and
after**, because it never inspects a callee's arguments or the stack.

### 17.3 Step B — two new exact resolution classes in `gen_app_data_image.py`

1. **`struct device` pointers.** `DEVICE_POINTERS` maps a shipped device-struct
   address to a devicetree node label, and stage a3 emits
   `DEVICE_DT_GET(DT_NODELABEL(<node>))`. Only devices whose shipped struct was
   read out of `app_update.bin` and whose `name` string *and* `config->base`
   identify the node beyond doubt are listed:

   ```
   0x00087c50  name "i2c@b000"  config->base 0x5000b000  -> i2c2 (TWIM2)
   0x00087c68  name "i2c@9000"  config->base 0x50009000  -> i2c1 (TWIM1)
   ```

2. **Archive-defined targets.** `our_symbols()` now reads the build's static
   archives (`<build>/app/*.a`) as well as the ELF. The question the gate must
   answer is "can this link define the symbol", and a symbol the *previous*
   link garbage-collected — because the zeroed `.data` word we are about to
   restore was its only referrer — is still definable. The address-taken
   reference stage a3 emits is itself what roots it, and the 0-undefined
   `nm -u` gate re-checks the result on the next build. This is what recovers
   `misc_dev_api_transfer_op12`, and it also unlocked **22 more** previously
   GC'd targets.

   One consequence is reported as found: rooting `bt_hci_core_recv_event`
   exposed a **missing pin**, `rodata_f2ed1`, while its three sibling
   log-format strings (`rodata_f2ddb` / `f2ef5` / `f2f45`) were all present in
   `g1_app_globals.ld`. Added.

3. **The EXCLUDE regions are now atomic (a policy repair).** Iteration 16's
   stage a3 iterated plain groups and **did not consult `EXCLUDE` at all**, so
   it could restore part of a reviewed object — measured: `g_screen_render_table`
   came out with three handlers set and eight screen ids still zero, which is
   precisely the half-initialised table the iteration-15 policy exists to
   forbid. `EXCLUDE` entries now carry an `atomic` flag and a3 restores such a
   region **whole or not at all**.

### 17.4 Step C — `g_screen_render_table` restored (eight more folded leaves)

With EXCLUDE atomic, `g_screen_render_table` (0x20002430, 11 × 16 B, the table
`panel_render_screen_dispatch` indexes) needed **every** pointer to resolve.
Three already did (`render_device_info_float_screen`, `dump_template_gyro_info`,
`gui_draw_timer_hms`, `draw_template_translate_screen`); the other eight slots
name **seven distinct uncatalogued 4-byte leaves**, each folded into the tail of
a neighbour and each referenced from **nowhere else in the image**:

| VA | folded into | screen id |
|---|---|---|
| `0x7d1b4` | `k_msleep_ticks32768_c` (0x7d194) | 4 |
| `0x7d1cc` | `ptr_load_u32` (0x7d1c8) | 5 |
| `0x7d240` | `set_device_sync_timestamp` (0x7d230) | 3 and 6 |
| `0x7d244` | `set_device_sync_timestamp` | 8 |
| `0x7d2f4` | `k_uptime_get_5` (0x7d2d8) | 7 |
| `0x7d356` | `k_uptime_get_6` (0x7d33a) | 9 |
| `0x7d37e` | `FUN_0007d37a` (0x7d37a) | 10 |

Every one is the same four bytes, `2000 movs r0,#0 / 4770 bx lr`.
**PROOF: each compiles to `00207047`, byte-identical to the shipped bytes at
its address.** `cfg_verify` **PASS** (40 checks each). The whole 176-byte table
— ids *and* handlers — is now restored as one unit, so
`panel_render_screen_dispatch` can no longer match an id and call 0.

### 17.5 The new first divergence — and it is on the NET core

With the reset gone the boot runs on. A dedicated 6.0 s app-core trace
(`/tmp/g1_i17d6`, UART captured) shows the next stop **precisely**, at
**t = 5.093 s** — which is exactly when `ancs_main`'s `50 × 100 ms` readiness
poll expires and it calls `bt_enable`:

```
[00:00:05.093,139] <err> ipc_service: Endpoint not registered
[00:00:05.093,139] <err> bt_hci_driver: Failed to send (err -2)
ASSERTION FAIL [buf] @ WEST_TOPDIR/zephyr/subsys/net/buf.c:467
<err> os: Faulting instruction address (r15/pc): 0x0007b45c
<err> os: >>> ZEPHYR FATAL ERROR 4: Kernel panic on CPU 0
<err> fatal_error: Resetting system
```

`ipc_service_send()` returns `-ENOENT` when `ept->instance == NULL`, i.e. the
HCI endpoint was never bound. The cause is on the other core:

```
CPUNET @2.0 s, top by instruction count
  rpmsg_get_endpoint        7 entries    53,146,996 instr   <<< 99.3 % of the core
  memset                   70 entries       137,530
  uarte_nrfx_poll_out    2904 entries        31,218
```

`rpmsg_get_endpoint` is upstream OpenAMP `rpmsg.c` (confirmed in
`zephyr.map`: `modules/open-amp/open-amp/lib/libopen_amp.a(rpmsg.c.obj)`,
0x103d048), a `metal_list_for_each` over `rdev->endpoints`. **It never
terminates**, so the net core never completes the endpoint bind, the app's HCI
endpoint stays unregistered, `bt_enable` fails, nothing advertises
(`radio TransmittedFrames = 0`, `vcentral Connected = False`), no display
`START` arrives — **and the dashboard is never painted.**

This closes the question this iteration was asked: *why is no pixel window ever
emitted after the clear?* The oracle's own trace answers it —
`spim_a.p1.trace` has **nothing between tick 1.21e8 (0.121 s) and 3.92e9
(3.92 s)**, and the ORACLE hooks show the sequence
`display_START action=0` → BLE connect → `display_START action=1` →
`BLIT notify_display_mode screen=10`. Every transaction after index 33 is
**downstream of the BLE link**, not of the display driver. Our display driver
reproduces the oracle byte-for-byte for everything it is asked to do; it is
never asked to paint.

The net core has not been rebuilt since iteration 9. Its `rdev->endpoints` list
head is almost certainly the CPUNET counterpart of the app-core defect
iteration 15 root-caused — a shipped `.data`/`.bss` object our net build never
initialises — which makes "give the net core the iteration-15 `.data`
treatment" the obvious iteration-18 Step A.

### 17.6 Measurements (every number below was actually run)

| metric | `g1-i15b-app` (old best aggregate) | `g1-i16b-app` (iter 16 final) | `g1-i17b-app` | **`g1-i17d-app` (iter 17 final)** |
|---|---:|---:|---:|---:|
| app instr @0.15 s | 6,724,014 | 7,878,667 | 8,086,343 | **8,060,397** |
| app unique fns @0.15 s | 886 | 907 | 953 | **957** |
| app instr @2.0 s | 10,157,310 | 7,878,667 | 11,731,356 | **11,684,715** |
| app unique fns @2.0 s | 917 | 907 | 994 | **996** |
| SoC resets @2.0 s | 0 | **1 (t≈0.104 s)** | **0** | **0** |
| SoC resets @6.0 s | not measured | (dead at 0.104 s) | not measured | **1 (t = 5.093 s, §17.5)** |
| net instr / fns @0.15 s | 293,961 / 433 | 288,578 / 432 | 288,578 / 432 | **288,578 / 432** |
| net instr / fns @2.0 s | not recorded | not recorded | 53,507,158 / 467 | **53,529,158 / 467** |
| `radio TransmittedFrames` | 0 | 0 | 0 | **0** |
| app FLASH | 635,024 B | 639,556 B | 645,648 B | **645,616 B (65.71 %)** |
| app RAM | 244,229 B | 244,229 B | 244,229 B | **244,229 B** |
| `nm -u` undefined / duplicate | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | 10/10, EXIT 0 | 10/10, EXIT 0 | **10/10, EXIT 0** |
| `gen_retained_sources.py --check` | clean | clean | clean | **clean** |
| `.data` restore (runs / bytes / relocated ptrs) | 85 / 1,199 / 0 | 146 / 1,899 / 155 | 165 / 2,083 / 194 | **154 / 2,151 / 184** |

(The stage-a3 run count *falls* from 165 to 154 between `i17b` and `i17d`
because §17.3(3) replaced eleven partial restores of `g_screen_render_table`
with one whole-table restore; the byte count rises.)

SPI / NFC markers, ours `g1-i17d-app` @2.0 s vs the golden autonomous trace:

| function | golden | **ours** |
|---|---|---|
| `nrfx_spim_init` | 3 / 24 | **3 / 24** |
| `nrfx_spim_xfer` | 170 / 3,774 | **170 / 3,774** |
| `nrfx_spim_uninit` | 8 / 43 | **8 / 43** |
| `spim_select_instance_by_mode` | 2 / 42 | **2 / 41** |
| `spi_master_trans_data_tx_rx` | 68 / 714 | **68 / 714** |
| `panel_init` | 20 / 52 | **20 / 52** |
| `spi_read_id` | 5 / 27 | **5 / 30** |
| `pt_nfc_eeprom_link_init` | 2 / 33 | **2 / 32** (was 1 / 8) |
| `pt_nfc_eeprom_link_start` | 2 / 9 | **2 / 9** |
| `attr_store_get` | 14 / 102 | **14 / 96** |
| `misc_dev_api_transfer_op12` | 12 / 138 | **12 / 132** |
| `projector_send_cmd_immediate` | 90 / 360 | **ABSENT** (BLE-gated, §17.5) |

Every one of the iteration-15/16 SPI markers is now an exact or near-exact
match. (`misc_dev_api_transfer_op12` and `read_rtc_counter_ms` cover a *larger*
address range in the golden trace than in ours, because that trace was built
before this iteration split their folded siblings out; the difference in
instruction counts is exactly the split-off code.)

### 17.7 Graphics parity results (`g1-i17d-app`)

| id | verdict | detail |
|---|---|---|
| **G-5** | **PASS** | all four enumerated elements byte-exact, and the `0xB9 FF` at index 33 that iteration 16 was cut off before is now emitted too — the entire `display_sensor_parity.md` §3.1 init block is reproduced. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` ours sha `f40cbd5d…` vs oracle `b64599b1…`, **34 vs 764** transactions; **all 34 shared transactions byte-identical**. `p2_render` 0 vs 2,881. |
| **G-1** | **FAIL** | `p2_render`: ours `0c5cc90b…` / **0 lit px**, oracle `b26c73b3…` / 1,098. |
| **G-2** | **FAIL** | `p1_boot`: ours `0c5cc90b…` / 0 lit px, oracle `1d617c65…` / 656. |
| **G-4** | *localiser, unchanged* | our framebuffer sha is **bit-identical to iteration 16's** (`0c5cc90b…`), so the localisation is unchanged rather than re-derived: first differing row y = 267, first differing pixel x = 178. |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash EQ, and we genuinely drive `spim_a`. |

**No pixels were painted.** The panel is correctly cleared and never painted,
for the reason established in §17.5.

### Regenerate (iteration 17)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
# Step A/B need two passes: the new leaves must exist in the build's archives
# before stage a3 will emit a reference to them (that reference is what roots
# them), and the 0-undefined link gate re-checks the result.
recon/application/build_cohesive.sh app /private/tmp/g1-i17a-app     # bootstrap
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py --selftest
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
    --stage a3 --elf /private/tmp/g1-i17a-app/zephyr/zephyr.elf
recon/application/build_cohesive.sh app /private/tmp/g1-i17b-app
# Step C (screen table) is the same two-pass shape:
recon/application/build_cohesive.sh app /private/tmp/g1-i17c-app      # bootstrap
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
    --stage a3 --elf /private/tmp/g1-i17c-app/zephyr/zephyr.elf
recon/application/build_cohesive.sh app /private/tmp/g1-i17d-app
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i17d-app/zephyr/zephyr.elf                        # EXIT 0, 0/0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py \
    --trials 120                                                      # EXIT 0, 10/10
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check    # clean
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify as c;\
 [print(n, c.verify('app',n)['status']) for n in ('FUN_00030c24','FUN_00030c60','FUN_0007d0c0',\
 'FUN_0007d0c2','FUN_0007d1b4','FUN_0007d1cc','FUN_0007d240','FUN_0007d244','FUN_0007d2f4',\
 'FUN_0007d356','FUN_0007d37e')]"                                     # 11x PASS
# net unchanged since iteration 9: /private/tmp/g1-i9c-net
<scratchpad>/mkrun.sh i17d  /private/tmp/g1-i17d-app /private/tmp/g1-i9c-net 0.15
<scratchpad>/mkrun.sh i17d2 /private/tmp/g1-i17d-app /private/tmp/g1-i9c-net 2.0
# the 6.0 s app-only probe that names the §17.5 blocker (uart0 backend + PC trace)
#   see /tmp/g1_i17d6/trace.resc
# graphics + sensors:
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i17d-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i9c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i17d
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
    /tmp/g1_ours_i17d <scratchpad>/i17/rep_i17d
```

Bisect ledger (every build and boot actually run):

| build | change | app @0.15 s | resets @2.0 s | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i17a-app` | 3 new folded leaves + corrected `misc_dev_api_transfer_op12` | **not booted** | — | bootstrap only: exists so stage a3 can see the new symbols in `libapp.a` |
| `/private/tmp/g1-i17b-app` | + stage a3 with the device / archive classes (165 runs, 194 ptrs) + the `rodata_f2ed1` pin | 8,086,343 / 953 | **0** | **the 0.104 s reset is gone**; 11,731,356 / 994 @2.0 s; sensors recover (S-IMU 25 → 983, S-NFC EEPROM 0 → 11) |
| `/private/tmp/g1-i17c-app` | 7 screen-table leaves + atomic EXCLUDE | **not booted** | — | bootstrap only, same reason |
| `/private/tmp/g1-i17d-app` | + `g_screen_render_table` restored whole (154 runs / 2,151 B / 184 ptrs) | 8,060,397 / **957** | **0** | **final**; 11,684,715 / **996** @2.0 s; graphics unchanged vs `i17b` (the table is BLE-gated too) |

Files changed: new `recon/app/src/{FUN_00030c60,FUN_0007d0c0,FUN_0007d0c2,
FUN_0007d1b4,FUN_0007d1cc,FUN_0007d240,FUN_0007d244,FUN_0007d2f4,FUN_0007d356,
FUN_0007d37e}.c` (+ `recon/verified/src` mirrors, `recon/named/*`,
`recon/symbolized/app/*`); corrected + re-proven
`recon/app/src/FUN_00030c24.c` (+ mirror, `recon/named/`,
`recon/symbolized/app/misc_dev_api_transfer_op12.c`);
`recon/application/gen_app_data_image.py` (`DEVICE_POINTERS`, archive-aware
`our_symbols`, atomic `EXCLUDE`) and its regenerated
`recon/application/app/src/g1_app_data_image.c`;
`recon/symbols/g1_app_globals.ld` (one missing `rodata_f2ed1` pin);
`recon/catalogs/function_names_app.json` (10 new names);
`recon/generated/app_retained_sources.cmake` (regenerated by its own tool,
1,630 → 1,640 retained sources);
`recon/emulator/reports/sensor_parity_status.md` (rewritten in place); this
report. Ten records appended to the scratchpad catalogs `app_funcs.json` /
`classified.json` (backed up as `*.i17bak`). **No `tools/` change**, no
Kconfig / `prj.conf` / devicetree change, `armemul` untouched. Nothing
committed.

## Iteration 18 — the CPUNET blocker is FIXED: the HCI endpoint binds, the
## `rpmsg_get_endpoint` spin is gone, and the net core's two "HCI rpmsg"
## threads run for the first time

**Headline.** Iteration 17's blocker is solved. `rpmsg_get_endpoint` no longer
spins: **net instructions at 2.0 s fall from 53,529,158 to 412,379** and the
app core's

```
[00:00:05.093,139] <err> ipc_service: Endpoint not registered
[00:00:05.093,139] <err> bt_hci_driver: Failed to send (err -2)
```

is **gone** — measured, not inferred: the string occurs **once** in the
iteration-17 6.0 s UART log (`/tmp/g1_i17d6/uart_app.log`) and **zero** times in
iteration 18's (`/tmp/g1_i18e6/uart_app.log`). The net core boots reset-free
through 2.0 s with **466 unique functions** and, for the first time, actually
schedules the "HCI rpmsg TX"/"HCI rpmsg RX" threads.

**The iteration-17 hypothesis was wrong, and the report says so.** The list
head was *not* an uninitialised shipped `.data` object: dumped at 2.0 s,
`rdev->endpoints` (`backend_data_0 + 0xe0`, offset taken from the build's own
DWARF) read `next = 0x21001e14`, `prev = 0x21001d9c` — a properly initialised,
self-consistent head. What was broken was a node *inside* the list, and the
cause is the CPUNET counterpart of the **app-core RAM-pin collision class**
(iterations 10/11), not of the `.data` class (iterations 15–17). **No net-side
`gen_net_data_image.py` was written**, because the evidence said it would not
have fixed anything.

**BLE still does not advertise.** `radio TransmittedFrames` = 0,
`vcentral Connected` = False. The boot now stops at a **different** assertion,
on the **app** core, one call deeper into the same path (§18.6).

### 18.1 Root cause, measured with Renode watchpoints

`backend_data_0` (the `ipc_rpmsg_static_vrings` backend instance) is at
0x21001cf8 in the iteration-17 net link and is 0x398 bytes long. Offsets inside
it were read from the build's DWARF, not guessed:
`backend_data_t.rpmsg_inst.rvdev.rdev.endpoints = +0xe0`, `struct
ipc_rpmsg_ept` is 0x70 bytes, `rpmsg_endpoint.node` is at +0x34 (confirmed
independently by `rpmsg_get_endpoint`'s own `sub.w r5, r4, #52`).

A 2.0 s dump of the whole struct shows the damage precisely:

| word | should be | actually was |
|---|---|---|
| `endpoints.next` | `&ns_ept.node` = 0x21001e14 | 0x21001e14 (OK) |
| `endpoints.prev` | `&endpoint[1].node` = 0x21001d9c | 0x21001d9c (OK) |
| `ns_ept.node.next` | `&endpoint[0].node` = 0x21001d2c | **0x00000000** |
| `endpoint[0].node.prev` | `&ns_ept.node` = 0x21001e14 | **0x00004f65** |

`metal_list_for_each` therefore walked `head -> ns_ept -> NULL` and never came
back to the head. Two `sysbus AddWatchpointHook`s named the writers:

```
WP-D30 pc=0x1037416  val=0x21001e14   <- rpmsg_register_endpoint+0x32 (correct)
WP-D30 pc=0x102dc9c  val=0x2100d1a6   <- FUN_01037f8c+0x68   (corruption)
WP-D30 pc=0x102dd2e  val=0x00009ecb   <- FUN_01037f8c+0xfa   (corruption)
WP-D30 pc=0x102dd2e  val=0x00004f66   <- FUN_01037f8c+0xfa   (corruption)
```

`FUN_01037f8c` is the **reconstruction of Zephyr's `z_add_timeout`**, and it
addresses `kernel/timeout.c`'s private state through raw original-image RAM
pins that, in the cohesive link, land inside live linker-allocated objects:

```
timeout_list        0x21000750 -> _sw_isr_table [0x21000708..0x210007f8] + 0x48
curr_tick           0x210044f0 -> sdc_mempool   [0x21002990..0x21007c51] + 0x1b60
announce_remaining  0x21004b6c -> sdc_mempool   + 0x21dc
timeout_lock        0x21004b70 -> sdc_mempool   + 0x21e0
last_count          0x21002b80 -> sdc_mempool   + 0x1f0   (sys_clock_elapsed)
```

So `queue->next` was a software-ISR-table word, the ordered-insert loop treated
arbitrary RAM as a chain of `struct _timeout`, and it wrote `dticks` and link
words all over `backend_data_0`. The writes at +0x68 / +0xfa are exactly
`to->dticks` and `position->ticks -= node->ticks` on a bogus node at
0x21001d20 (= `endpoint[0].ep.dest_addr`).

A mechanical sweep of the same class (the app-core
`check_ram_pin_collisions.py` logic, re-pointed at the CPUNET RAM window and
the net linker scripts, run from the scratchpad — **`recon/emulator/scripts` and
`tools/` were not modified**) found this is systemic: **72 raw literal net RAM
pins land inside a live linked object, 53 of which are referenced by a literal
that survives `--gc-sections`.** Iteration 18 fixes the ones on the boot path;
**49 live-referenced collisions remain** and are the named follow-up.

### 18.2 Step A — `kernel/timeout.c` is a SINGLETON and was linked twice

Our net image contains BOTH the stock unit (`z_add_timeout` @0x01039f28,
`timeout_list` @0x210006f8, announced by the stock `rtc_nrf_isr`) and the
reconstruction. Two timeout lists means the recovered callers' timeouts are
never announced, on top of the corruption. The repository's own ownership
records already identify 0x01037f8c as `z_add_timeout`
(`net_kernel_private_stock_adoption.json` `call_target_checks[4]`,
`net_zephyr_stock_atomic_adoption.json` `call_target_checks[269]`).

Five reconstructions are therefore excluded and their raw identities bridged to
the stock owners (evidence:
`recon/ownership/net_kernel_timeout_singleton_adoption.json`; five rows added to
`recon/ownership/adoption_manifest.json`; five `PROVIDE`s in
`recon/application/net/src/stock_call_aliases.ld`):

| raw | stock owner | unit |
|---|---|---|
| `FUN_010317c0` | `sys_clock_elapsed` | `drivers/timer/nrf_rtc_timer.c` |
| `FUN_01037f8c` | `z_add_timeout` | `kernel/timeout.c` |
| `FUN_010380d8` | `z_abort_timeout` | `kernel/timeout.c` |
| `FUN_0103814c` | `sys_clock_announce` | `kernel/timeout.c` |
| `FUN_01038284` | `sys_clock_tick_get` | `kernel/timeout.c` |

The three file-static helpers (`FUN_01037f00` = `elapsed`, `FUN_01037f14` =
`next_timeout`, `FUN_01037f54` = `remove_timeout`) have no linkable upstream
symbol; every caller is now excluded, so `--gc-sections` drops them and their
sources are left untouched.

**Also fixed here: `rodata_103bac9` was pinned in the WRONG ADDRESS SPACE.**
`z_impl_k_thread_create` (FUN_01035fa0) passes it to `z_add_timeout` as the
timeout callback. 0x0103bac9 is a stored pointer VALUE, i.e. a CPUNET *runtime*
address; its analysis address is 0x0103b2c9, and `netcore_image.bin` at analysis
0x0103b2c8 disassembles to `movs r1,#1 / subs r0,#24 / b.w 0x010378c4` — exactly
`z_thread_timeout` (`base.timeout` is at +0x18, the same offset FUN_01035fa0
passes). Analysis 0x0103bac8 is plain data. Rebound to
`PROVIDE(rodata_103bac9 = z_thread_timeout | 1)`.

Build `g1-i18a-net`. **Effect: none on the symptom** — net still 53,529,301
instructions at 2.0 s, still parked in `rpmsg_get_endpoint+0x28`. Correct fix,
wrong culprit; kept, and the next watchpoint run named the real one.

### 18.3 Step B — the two "HCI rpmsg" threads: colliding storage AND a dropped
### 64-bit `K_NO_WAIT`

The next watchpoint run pointed at `FUN_01035edc+0x9c` (`z_setup_new_thread`
writing `thread+0x74`) hitting 0x21001e14. A `k_thread_create` hook printed the
objects:

```
THREAD_CREATE obj=0x21001da0 lr=0x102f051   (FUN_0102afbc+0x28)
THREAD_CREATE obj=0x21001d08 lr=0x102f071   (FUN_0102afbc+0x48)
```

`FUN_0102afbc` is NCS 2.5.1's `samples/bluetooth/hci_rpmsg/src/main.c` body.
Its shipped storage is

```
struct k_thread RX 0x21001d08   stack 0x21006480 (0x800)   entry FUN_0102acf4
struct k_thread TX 0x21001da0   stack 0x21006cc0 (0x600)   entry FUN_0102adac
struct ipc_ept  HCI 0x21004608
names            0x0103d088 / 0x0103d095 (runtime) = "HCI rpmsg TX"/"HCI rpmsg RX"
```

and **every one of those addresses is inside a live object in our link**: the
two `k_thread`s inside `backend_data_0`, the two stacks and the `ipc_ept` inside
`sdc_mempool`. Real storage is now emitted in
`recon/application/net/src/g1_product_endpoints.c`, alongside the endpoint
configs and semaphores that file already owns.

**And a second, independent defect at the same call sites.** The shipped
0x0102afbc has a `sub sp, #36` frame and executes

```
102afd4  strd r6, r7, [sp, #24]      ; r6 = r7 = 0  -> the 64-bit K_NO_WAIT delay
102afd8  strd r5, r4, [sp, #12]      ; prio = -9, options = 0
102afdc  strd r4, r4, [sp, #4]       ; p2, p3
102afe4  str  r4, [sp, #0]           ; p1
```

but the reconstruction declared `FUN_01035fa0` with only **nine** parameters, so
GCC emitted a `sub sp, #28` frame and never wrote sp+24/sp+28. `FUN_01035fa0`
(= `z_impl_k_thread_create`) read an **uninitialised** `k_timeout_t delay`, took
its `z_add_timeout` branch instead of `z_sched_start`, and **the two HCI threads
never started** — which is also how the corrupting `z_add_timeout` call got
made in the first place. This is the same class as app-core iteration 12
(`k_thread_create` stack args) and the **eighth** member of the family the
differential harness is structurally blind to; `emu`/`cfg_verify` never compare
a callee's incoming stack frame.

Build `g1-i18b-net`. The threads now start — and immediately unmask §18.4.

### 18.4 Step C — three more mis-relocated original-image constants, each found
### by following the next fault

Each of these was reached only because the previous one was fixed; all three are
"a raw original-image address survived symbolization" and all three are proven
against `netcore_image.bin`.

1. **`arch_new_thread` planted a runtime-space `z_thread_entry`.**
   `g1-i18b-net` died at t = 0.342 s with `USAGE FAULT / Illegal use of the
   EPSR` at PC 0x0102c3e4 (`bx lr` with `lr = 0`). The net PC trace shows the
   very first `z_arm_pendsv` returning to **PC = 0x0102cc3c**, which in our link
   is the *middle* of `FUN_01033354`'s `ldmia.w sp!, {r4, lr}` — so the thread
   popped a garbage LR. `FUN_0102ece0` (= `arch_new_thread`) contains
   `uVar1 = 0x0102cc3d`, the shipped Thumb pointer to `z_thread_entry`;
   analysis 0x0102c43c disassembles to
   `push {r7,lr} / mov r5,r0 / mov r6,r1 / mov r7,r2 / mov r8,r3 /
   bl z_impl_z_current_get / mov r3,r0 / bl __aeabi_read_tp / mov r4,r0 /
   ldr.w r9,[pc,#24] / mov r2,r8 / str.w r3,[r9,r0] / mov r1,r6 / mov r0,r7 /
   blx r5`, instruction-for-instruction our linked `z_thread_entry`. Bound to
   `&z_thread_entry` under `G1_COHESIVE_BUILD`. Build `g1-i18c-net`.

2. **`hci_rpmsg.c`'s `tx_queue` and the `net_buf` pool list base.**
   `g1-i18c-net` died at t = 0.345 s with `ASSERTION FAIL @ spinlock.h:114`
   (recursive spinlock) inside `queue_insert`, `Current thread: 0x21001cf8` =
   the new TX thread. The TX thread does `net_buf_get(0x21000978, K_FOREVER)`;
   0x21000978 is the shipped `static K_FIFO_DEFINE(tx_queue)` and in our link it
   is 0x18 bytes into `net_buf_pool_area`'s third `struct net_buf_pool`
   (the section runs `_net_buf_pool_list_start` 0x210008f8 ..
   `_net_buf_pool_list_end` 0x21000994). Separately, `FUN_0102fc30`,
   `FUN_0102fdd0` and `FUN_0102ff94` compute `pool = 0x21000994 + id*0x34`;
   0x21000994 is the ORIGINAL `_net_buf_pool_list` base but our
   `_net_buf_pool_list_end`, so every pool word read back was one element past
   the array. Both are bound to real objects (`g1_hci_tx_queue`,
   `_net_buf_pool_list_start`). Build `g1-i18d-net`.

3. **`FUN_0102b1c8`'s ESB worker thread — storage fixed, start DEFERRED.**
   `g1-i18d-net` got to t = 1.455 s and then took `USAGE FAULT` at
   `rpmsg_virtio_rx_callback+0x84` (`blx r8` on `ept->cb`). A watchpoint on
   `endpoint[0].ep.cb` showed it set correctly to 0x0103c1fd, three messages
   delivered, and then **zeroed by `FUN_01035edc+0x96`** — a *third*
   `k_thread_create`, `FUN_0102b1c8`, whose shipped object 0x21001e38 also lands
   inside `backend_data_0` and whose stack 0x21007300 lands inside
   `sdc_mempool`. It drops the same 64-bit delay.
   Its storage is relocated. Its **entry point is NOT reconstructed**: the
   stored pointer 0x0102ba05 is runtime-space, analysis 0x0102b204, which lies
   *inside* `FUN_0102b1c8`'s declared Ghidra extent (next catalogued entry is
   `FUN_0102b2ac`) — an **eighth instance of the "Ghidra folded a sibling
   function into the tail of the preceding symbol" class**, 168 bytes with no
   reconstruction and no catalogue entry. Starting the thread would jump into
   unrelated text, so the delay is passed as **K_FOREVER**: the thread is
   created and never scheduled. **This is a deliberate, documented divergence**
   (the shipped firmware passes `K_NO_WAIT`), recorded in the source, and it is
   to be reverted to `K_NO_WAIT` the moment 0x0102b204 is reconstructed.
   Build `g1-i18e-net` — **final, and reset-free through 2.0 s**.

### 18.5 Measurements (every number below was actually run)

App core unchanged this iteration (`/private/tmp/g1-i17d-app`).

| metric | iter 17 net (`g1-i9c-net`) | `g1-i18a-net` | **iter 18 final `g1-i18e-net`** |
|---|---:|---:|---:|
| net instr @2.0 s (`cpunet ExecutedInstructions`) | 53,529,158 | 53,529,301 | **412,379** |
| net unique fns @2.0 s (from the PC trace) | 467 | — | **466** |
| net top consumer @2.0 s | `rpmsg_get_endpoint` 53,146,996 (99.3 %) | `rpmsg_get_endpoint` (still spinning) | `memset` 139,562; **`rpmsg_get_endpoint` not in the top 12** |
| app instr @2.0 s (`cpuapp ExecutedInstructions`) | 11,684,715 | 11,684,715 | **11,687,004** |
| app unique fns @2.0 s (from the PC trace) | 996 | — | **996** |
| SoC resets @2.0 s | 0 | 0 | **0** |
| SoC resets @6.0 s | 1 (t = 5.093 s) | — | **1 (t = 5.093 s, different cause — §18.6)** |
| `ipc_service: Endpoint not registered` in the 6 s UART | **1** | — | **0** |
| `radio TransmittedFrames` | 0 | 0 | **0** |
| net FLASH image span | 229,161 B | 228,633 B | **228,717 B** (end LMA 0x0104056d, *smaller* than iter 17's 0x01040729) |
| net RAM | 54,140 B | 54,140 B | **59,796 B (91.24 %)**, +5,656 B |
| net `nm -u` undefined / duplicate | 0 / 0 | 0 / 0 | **0 / 0** |
| app `check_ram_pin_collisions.py` | 0 / 0, EXIT 0 | — | **0 / 0, EXIT 0** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | — | **10/10, EXIT 0** |
| `gen_retained_sources.py --check` | clean | clean | **clean** |
| net literal RAM pins colliding with a live object (live-referenced) | 72 (53) | — | **69 (49)** |

The net image did **not** grow past its region: the FLASH enlargement of
`recon/application/net/app.overlay` was already in place and the image is
228,717 B against the modelled 231,424 B limit (2,707 B headroom), i.e. **484 B
smaller than iteration 17's**, because displacing the five duplicate
`kernel/timeout.c` bodies frees more than the new thread storage costs. No
Kconfig, `prj.conf` or devicetree change was made.

### 18.6 The new first divergence — still t = 5.093 s, but one call deeper

The 6.0 s run (`/tmp/g1_i18e6`, both UARTs captured) shows `bt_enable` now
reaching the transport and failing **inside** it rather than before it:

```
                                            (iteration 17)
[00:00:05.093,139] <err> ipc_service: Endpoint not registered
[00:00:05.093,139] <err> bt_hci_driver: Failed to send (err -2)
ASSERTION FAIL [buf] @ WEST_TOPDIR/zephyr/subsys/net/buf.c:467

                                            (iteration 18 — the two <err>
                                             lines are GONE)
ASSERTION FAIL [net_buf_simple_headroom(buf) >= len]
               @ WEST_TOPDIR/zephyr/subsys/net/buf_simple.c:301
<err> os: Faulting instruction address (r15/pc): 0x0007b45c   r14/lr: 0x0005f1a3
<err> os: >>> ZEPHYR FATAL ERROR 4: Kernel panic on CPU 0
```

Resolved against `/private/tmp/g1-i17d-app/zephyr/zephyr.elf`:
`0x0007b45c = assert_post_action+0xc`, `0x0005f1a3 = net_buf_simple_push+0x27`,
and the surrounding frames are `bt_rpmsg_send` (0x0005fd58) and
`ble_work_thread` (0x0001f52c). `bt_rpmsg_send` prepends the one-byte H:4 packet
indicator with `net_buf_push_u8()`; the buffer it is handed has **no headroom**,
even though `CONFIG_BT_HCI_RESERVE = 1` is set in the app build's
`autoconf.h` (line 177) and `CONFIG_BT_RPMSG = 1` (line 767). So the TX buffer
does not come from a `BT_BUF_RESERVE`-reserving allocation — an **app-core**
defect, and iteration 19's Step A. `bt_buf_get_tx` is absent from the app ELF's
symbol table, which is the thread to pull.

### 18.7 Graphics + sensor parity (`g1-i17d-app` + `g1-i18e-net`)

Full capture actually run, both phases, identical determinism knobs and
stimulus to the oracle, no memory poking:

```
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i17d-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i18e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /tmp/g1_ours_i18e
```

| id | verdict | detail |
|---|---|---|
| **G-5** | **PASS** (unchanged) | all four enumerated elements byte-exact, including the trailing `0xB9 FF`. |
| **G-3** | **FAIL (truncation only)**, unchanged | `p1_boot` **34 vs 764** transactions; **all 34 byte-identical**; first difference at index **34** (oracle `0x66 tx=66`, ours absent). `p2_render` 0 vs 2,881. |
| **G-1** | **FAIL**, unchanged | `p2_render` ours `0c5cc90b…` / **0 lit px**, oracle `b26c73b3…` / 1,098. |
| **G-2** | **FAIL**, unchanged | `p1_boot` ours `0c5cc90b…` / **0 lit px**, oracle `1d617c65…` / 656. |
| **G-4** | *localiser, unchanged* | our framebuffer sha is still bit-identical to iterations 16/17, so the localisation carries over unchanged: first differing row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`) — the top-left of the oracle's lit bbox (178,267)–(449,287). |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash EQ. |

**No pixels were painted, and the graphics numbers are bit-for-bit those of
iteration 17.** That is expected and is stated plainly: the app core still
resets at t = 5.093 s, before any BLE connection, and the oracle's `spim_a`
stream has nothing between 0.121 s and 3.92 s because every transaction after
index 33 is downstream of the BLE link. Iteration 18 moved the blocker one call
deeper; it did not yet reach the link.

Per-sensor `p1_boot` volumes are also unchanged (the app binary is unchanged and
the reset time is unchanged): LSM6DSO 983/1,089, nPM1300 199/291, OPT3001
14/33, ST25DV system port 12/22, NFC EEPROM 11/25, `saadc` 17/998, `spim_a`
34/764, `gpiote0` 25/25 (hash EQ), `pdm0` 2/2 (hash EQ), `spim_b` 0/0. Every
`p2_render` column is 0. Score is unchanged at **5 PASS / 5 PARTIAL / 4 FAIL**;
see `sensor_parity_status.md`.

**Re-proof.** Every corrected canonical reconstruction was re-verified with the
authoritative CFG-directed verifier after the change — `cfg_verify.verify('net',
n)` **PASS** for all eight: `FUN_0102afbc` (40 checks), `FUN_0102b1c8` (40),
`FUN_0102ece0` (40), `FUN_0102adac` (3), `FUN_0102adf0` (17), `FUN_0102fc30`
(44), `FUN_0102fdd0` (11), `FUN_0102ff94` (42). As expected this is necessary
but not sufficient: `cfg_verify` **also passed before** the FUN_0102afbc /
FUN_0102b1c8 fixes, because it never compares a callee's incoming stack frame —
which is precisely why the dropped `k_timeout_t` survived 300-trial parity.
(The `#ifdef G1_COHESIVE_BUILD` relocations are invisible to the harness; the
parity path keeps the original literals, and for the two `k_thread_create`
callers it now also emits the previously-missing delay words, i.e. the parity
body moved *towards* the shipped instruction sequence.)

### Regenerate (iteration 18)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py            # 964 -> 959 net
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check    # clean
recon/application/build_cohesive.sh net /private/tmp/g1-i18e-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
arm-zephyr-eabi-nm -u /private/tmp/g1-i18e-net/zephyr/zephyr.elf | wc -l   # 0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i17d-app/zephyr/zephyr.elf                             # EXIT 0, 0/0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py \
    --trials 120                                                           # EXIT 0, 10/10
# boot (2.0 s, both cores traced) and the 6.0 s UART probe that names §18.6:
#   <scratchpad>/i18e.resc  and  <scratchpad>/i18e6.resc
# graphics + sensors: see §18.7
```

Bisect ledger (every build and boot actually run; app fixed at `g1-i17d-app`):

| net build | change | net instr @2.0 s | resets | note |
|---|---|---:|---|---|
| `/private/tmp/g1-i18a-net` | `kernel/timeout.c` singleton displacement (5 rows) + `rodata_103bac9` → `z_thread_timeout` | 53,529,301 | 0 @2.0 s | correct, but **no symptom change** — still parked in `rpmsg_get_endpoint+0x28` |
| `/private/tmp/g1-i18b-net` | + HCI TX/RX thread objects, stacks, `ipc_ept`, names relocated; + the dropped 64-bit `K_NO_WAIT` | not reached | **1 (t = 0.342 s)** | threads start for the first time; USAGE FAULT, `bx lr` with `lr = 0` (`z_thread_entry` defect) |
| `/private/tmp/g1-i18c-net` | + `arch_new_thread` → `&z_thread_entry` | not reached | **1 (t = 0.345 s)** | first pendsv lands correctly; `spinlock.h:114` recursive-spinlock assert in `queue_insert` |
| `/private/tmp/g1-i18d-net` | + `g1_hci_tx_queue` + `_net_buf_pool_list_start` | not reached | **1 (t = 1.455 s)** | 3 rpmsg messages delivered, then `ept->cb` zeroed by a third colliding thread object |
| `/private/tmp/g1-i18e-net` | + ESB worker thread storage relocated, start deferred (K_FOREVER) | **412,379** | **0** | **final**; endpoint binds, `Endpoint not registered` gone |

Files changed: `recon/symbols/g1_net_globals.ld` (one function-pointer rebind);
`recon/application/net/src/stock_call_aliases.ld` (5 `PROVIDE`s);
new `recon/ownership/net_kernel_timeout_singleton_adoption.json`;
`recon/ownership/adoption_manifest.json` (5 net rows + summary);
`recon/generated/net_retained_sources.cmake` (regenerated by its own tool,
964 → 959 retained sources);
`recon/application/net/src/g1_product_endpoints.c` (three `k_thread`s, three
stacks, one `ipc_ept`, one `k_fifo`, two name strings);
`recon/net/src/{FUN_0102afbc,FUN_0102b1c8,FUN_0102ece0,FUN_0102adac,FUN_0102adf0,
FUN_0102fc30,FUN_0102fdd0,FUN_0102ff94}.c` and the compiled
`recon/symbolized/net/{FUN_0102ece0,FUN_0102fc30,FUN_0102fdd0,FUN_0102ff94}.c`
mirrors; `recon/emulator/reports/sensor_parity_status.md` (rewritten in place);
this report. **No `tools/` change**, no `recon/emulator/scripts/` change, no
Kconfig / `prj.conf` / devicetree change, `armemul` untouched. Nothing
committed.

### 18.8 Open, named, and NOT fixed

1. **`analysis 0x0102b204` (168 B) is unreconstructed** — the ESB worker thread
   entry; until it exists `FUN_0102b1c8` creates its thread with `K_FOREVER`
   (deliberate divergence, §18.4(3)).
2. **49 live-referenced net RAM-pin collisions remain**, dominated by recovered
   ESB / nrfx / SDC state pinned inside `sdc_mempool` and by four pins inside
   `_sw_isr_table` / `m_cb` / `backend_config_0` / `g1_ipc0_endpoint_config`.
   The app core solved this class structurally with `g1_ram_arena`; the net core
   **cannot** copy that directly — the pinned span is 0x6450 (25,680 B) and the
   net has 64 KiB of RAM with 59,796 B already in use. The tractable route is
   the one iteration 18 used: displace the recovered duplicates onto the stock
   owners so the pins stop being dereferenced at all.
3. **The net RAM-pin gate does not exist.** `check_ram_pin_collisions.py` is
   hard-coded to the app RAM window and the app linker scripts. It was driven
   for the net core from the scratchpad by importing the module and overriding
   `RAM_LO`/`RAM_HI`; making that a first-class `--ram`/`--ld` invocation is a
   one-line, additive change that was deliberately NOT made this iteration.
4. **Raw `0x21xxxxxx` literals inside net sources are invisible to that gate**
   anyway — the three thread objects fixed here were plain C literals, not
   `PROVIDE` pins. A source-level sweep is needed.
5. **The app-core `bt_rpmsg_send` headroom assertion** (§18.6) is the new first
   divergence.
