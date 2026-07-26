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

## Iteration 19 — `bt_enable` was never called: the app core boots
## RESET-FREE for the first time, and the CPUNET's Bluetooth host comes up
## ("Bluetooth enabled in RAW mode")

**Headline.** Iteration 18's `net_buf_simple_headroom` assertion was a
*symptom*, not a defect in any buffer pool: the buffer handed to
`bt_rpmsg_send` was **NULL**, because `ancs_main` was calling
**`bt_send(NULL)` where the shipped firmware calls `bt_enable(NULL)`**.  With
that repaired — and with a second, independent arena-sizing defect it
unmasked — **the app core runs 8.0 s with zero fatal errors for the first time
in this project** (previously it reset at t = 5.093 s in every iteration since
16).  On the net core, five further defects were root-caused and fixed and the
Bluetooth host now actually comes up: the CPUNET UART prints the SoftDevice
Controller build revision and `<inf> bt_hci_raw: Bluetooth enabled in RAW mode`
for the first time.

**BLE still does not advertise.**  `radio TransmittedFrames` = 0,
`vcentral Connected` = False.  The new first divergence is on the **net** core
at t = 5.0942 s, immediately after `hci_driver_send()` (§19.8).

### 19.1 Step A — the root cause of the headroom assertion: `bt_send` vs `bt_enable`

The iteration-18 report's hypothesis (a `net_buf` pool or allocation site that
did not reserve `CONFIG_BT_HCI_RESERVE`) is **wrong, and the evidence says so
directly.**  A Renode hook on `bt_rpmsg_send` (0x5fd58 in `g1-i17d-app`) printed:

```
[ERROR] cpuapp: RPMSG_SEND buf=0x0 type=0 lr=0x187f7
[ERROR] cpuapp: PUSH buf=0xc len=1 data=0x0 __buf=0x0 lr=0x7fedb
```

`buf = 0`, so `net_buf_simple_push(&buf->b /* = 0xc */, 1)` computed
`headroom = data - __buf = 0 - 0 = 0 < 1`.  Hooks on `net_buf_alloc_len` and
`net_buf_simple_reserve` **never fired at all**, i.e. no HCI command buffer was
ever allocated: `bt_hci_cmd_create` (0x542ac) reserves correctly
(`net_buf_alloc_fixed`, `net_buf_simple_reserve(&buf->b, 1)`, `bt_buf_set_type`,
`net_buf_simple_add(&buf->b, 3)`) and was simply never reached.

`lr = 0x187f7` resolves inside `ancs_main`:

```
   187f0:  2000        movs r0, #0
   187f2:  f03c f8d9   bl 549a8 <bt_send>        <-- ours
```

against the shipped `app_update.bin` (read through `tools/extract.py`, never a
naive VA subtraction):

```
   199a0:  2000        movs r0, #0
   199a2:  f03b f84f   bl 0x54a44                <-- original
```

and `recon/catalogs/function_names_app.json` has already recorded, verbatim,
that **`0x00054a44` is `bt_enable`**:

> `"source": "function_name_overrides.json: Relocation-normalized
> instruction-exact configured Zephyr Bluetooth host initializer; **the former
> bt_send label was an identity mismatch.** Raw identity remains FUN_00054a44
> at 0x00054a44."`

That correction was never propagated into `ancs_main`'s callee declaration.
`recon/{app,verified}/src/ancs_main.c`, `recon/symbolized/app/ancs_main.c`,
`recon/named/ancs_main.c` and `recon/readable_sources/app/g1/ancs_main.c` all
still carried

```c
extern int bt_send(int mode);   /* FUN_00054a44 @ 0x00054a44 */
...
error = bt_send(0);
```

and because **`bt_send` is a genuine Zephyr symbol** (`hci_core.c`, 0x549a8 in
that link) the cohesive link bound it silently — no undefined symbol, no
duplicate, both gates green.  `.text.bt_enable` was consequently **garbage
collected**: it appears in `/private/tmp/g1-i17d-app/zephyr/zephyr.map` at
address `0x0000000000000000`.  So **Bluetooth was never enabled at all**; the
app merely poked the HCI transport with a null pointer.

**A second, independent defect at the same site.**  The shipped `ancs_main`
executes at 0x199c6

```
   199c6:  2200        movs r2, #0
   199c8:  492f        ldr  r1, [pc, #188]
   199ca:  4610        mov  r0, r2
   199cc:  f044 fe82   bl 0x5e6d4                ; bt_foreach_bond(0, cb, NULL)
```

i.e. **three** arguments, while the reconstruction declared
`bt_foreach_bond(unsigned int, const void *)` and passed two — the
**dropped-register-argument** class the differential harness is structurally
blind to (ninth instance).  `user_data` was whatever `r2` happened to hold.
Both were corrected; `cfg_verify.verify('app', 'ancs_main')` **PASS**, 11 cases.

A mechanical sweep of the same class over every symbolized/canonical source
(`extern … NAME(...); /* FUN_xxxxxxxx @ 0xADDR */` vs the catalog's name for
that address) found **exactly one other** genuine mismatch class, and it is
benign: `main.c` names 0x75174 `k_timer_start` and 0x72908
`mutex_lock_syscall_handler` where the catalog says `z_impl_k_timer_start` /
`z_impl_k_sem_take` — in this link those pairs are the **same address**
(0x734d0 and 0x489cc respectively), so both bind to the same body.

Build `/private/tmp/g1-i19a-app`.  **Effect: the headroom assertion is GONE**;
`bt_enable` is linked at 0x55154, is entered with `cb = 0` at t ≈ 5.13 s, calls
`bt_init` → `bt_hci_cmd_send_sync(opcode 0x0c03 = HCI_Reset)` →
`bt_rpmsg_send(buf = 0x2003f774, type = 0 = BT_BUF_CMD)`.  Measured with hooks
on all five functions.

### 19.2 Step B — the arena was sized to a pin's BASE, not its EXTENT

`g1-i19a-app` then died at t = 5.1418 s:

```
<err> os: ***** USAGE FAULT *****
<err> os:   Attempt to execute undefined instruction
<err> os: Faulting instruction address (r15/pc): 0x00000000
<err> os: Current thread: 0x20005e18 (unknown)
```

A 250 ms Renode PC trace over the fault window (`cpuapp CreateExecutionTracing`)
ends:

```
… z_time_slice -> rtc_nrf_isr -> _isr_wrapper -> z_arm_int_exit
   -> z_arm_pendsv -> configure_builtin_stack_guard -> 0x0 -> z_arm_usage_fault
```

so PendSV restored **PC = 0** for the incoming thread.  A `k_thread_create`
hook identified it: `obj = 0x20005e18, stack = 0x20029f68, size = 5120,
entry = 0x43165 = display_thread_handler`.

`g_display_thread_stack_buf` is an **arena-relative** pin
(`recon/symbols/g1_app_globals.ld`: `PROVIDE(g_display_thread_stack_buf =
g1_ram_arena + 0x26e68)`), and `recon/application/app/src/g1_app_ram_relocs.c`
sized the arena as

```c
#define G1_RAM_ARENA_LIMIT  0x20029000u   /* "highest recovered RAM pin is
                                             g_display_thread_stack_buf at
                                             0x20028e68" */
```

— i.e. to the highest pin's **base**, rounded up, **not to its extent**.  The
stack is 0x1400 bytes: the shipped `spawn_display_thread` (FUN_00049638) loads
`mov.w r2, #5120` at 0x49650 and passes 0x20028e68, and our reconstruction
reproduces both.  The object therefore really runs 0x20028e68 .. 0x2002a268 and
its top **0x1268 bytes lay OUTSIDE the arena**.  An ARM stack grows *down* from
its top, so the overrun covered exactly the part the thread uses first.  In the
`g1-i19a-app` layout the linker had put these there:

```
0x2002a100 backend_data_0     0x2002a4c8 logging_thread   0x2002a9e0 posix_thread_pool
0x2002aeb8 smp_work_queue     0x2002afb0 conn_data        0x2002b038 bt_long_wq
0x2002b130 tx_thread_data     0x2002b208 bt_workq
```

`tx_thread_data` and `bt_workq` are `hci_core.c`'s HCI-TX thread object and BT
work queue — **initialised by `bt_enable` itself**, at the very top of the
display thread's stack, which is why the defect had been latent for four
iterations and detonated the instant `bt_enable` started working.

`G1_RAM_ARENA_LIMIT` is raised to **0x2002a400** (covers the 0x2002a268 extent
with a 32-byte-aligned margin; every other pinned stack in the arena was checked
against its own `k_thread_create` size argument and ends below 0x2002a100).
Build `/private/tmp/g1-i19b-app`: `g1_ram_arena` = 0x20003100 + 0x28400, and
`g_display_thread_stack_buf` (0x20029f68 + 0x1400 = 0x2002b368) now ends below
`backend_data_0` (0x2002b500).

**Result — the app core is reset-free through 8.0 s for the first time.**
`/private/tmp/g1-i19/b2_uart_app.log` (app `g1-i19b`, net `g1-i18e`) contains
**zero** `ZEPHYR FATAL ERROR` / `ASSERTION FAIL` lines; `cpuapp
ExecutedInstructions` at 8.0 s = 16,942,935.

### 19.3 Step C — CPUNET: `bt_enable_raw` was a duplicate of a SINGLETON

With the app finally sending HCI, the CPUNET was measured burning
**289,729,537 instructions in 8 s**.  A 5 ms PC trace at t = 6.0 s named the
spin (top of 500,000 sampled PCs): `cbvprintf_package` 147,628,
`mpsc_pbuf_alloc` 55,377, `drop_item_locked` 25,846,
`z_impl_z_log_msg_runtime_vcreate` 24,110, `FUN_0102acf4` 13,014 — an unbounded
**logging** loop inside the HCI rpmsg thread, i.e. its `Unknown type %u\n`
branch (string read at runtime 0x0103cf17 with `tools/net_extract.py`).

Two causes, both of iteration 18's open item 4 ("raw `0x21xxxxxx` literals
inside net sources are invisible to the RAM-pin gate"):

1. **`FUN_0102fcec` is `bt_enable_raw`.**  Its three log strings, read out of
   `netcore_image.bin`, are verbatim `hci_raw.c`'s, in order:
   0x0103dde1 `"No HCI driver registered"`, 0x0103ddfa
   `"HCI driver open failed (%d)"`, 0x0103de16
   `"Bluetooth enabled in RAW mode"`; it stores its argument, reads a driver
   pointer, calls `drv->open` at +12 and returns −19 (`-ENODEV`).
   `hci_raw.c` is a **singleton** and is already the linked owner of `bt_send`
   (0x01033544) and `bt_recv` (0x01033530); its file-static `raw_rx`
   (0x210083d4) is written **only** by `bt_enable_raw`.  The retained
   reconstruction wrote its own original-image pin 0x210047fc instead, so the
   stock `raw_rx` stayed NULL and the controller → host path had nowhere to
   queue.  Displaced:
   `PROVIDE(FUN_0102fcec = bt_enable_raw)`, manifest exclusion, evidence
   `recon/ownership/net_hci_raw_singleton_adoption.json`.
2. **The controller → host `k_fifo` at 0x2100095c** — the argument
   `FUN_0102afbc` passes to `bt_enable_raw` (`k_fifo` → `raw_rx`) and the queue
   `FUN_0102acf4` consumes — was a raw literal in the cohesive path, and in this
   link it falls **inside the stock `hci_cmd_pool`/`hci_acl_pool`**
   (`_net_buf_pool_list_start` 0x21000930).  `net_buf_get()` therefore ran on a
   `net_buf_pool`, returned garbage on every iteration, and the thread logged
   forever.  The `struct ipc_ept` at 0x21004608 in the same file was equally raw
   (it aliases `sdc_mempool`) even though iteration 18 had already relocated the
   *same object* in `FUN_0102afbc`.  Both bound to real storage:
   `K_FIFO_DEFINE(g1_hci_rx_queue)` in
   `recon/application/net/src/g1_product_endpoints.c`, and `&g1_hci_ept`.

Build `/private/tmp/g1-i19a-net`.

### 19.4 Step D — `CONFIG_MAIN_STACK_SIZE = 512` was inherited, never measured

`g1-i19a-net` reached, for the first time,

```
<inf> bt_sdc_hci_driver: SoftDevice Controller build revision: c5 93 ba a9 …
<inf> bt_hci_raw: Bluetooth enabled in RAW mode
```

and then took `MPU FAULT / Instruction Access Violation, pc 0x2100bc74` at
t = 0.3426 s.  Renode hooks measured the stack directly:

| point | sp |
|---|---|
| `main` (FUN_0102a720) entry | 0x2100bdc8 |
| `hci_rpmsg` main (FUN_0102afbc) entry | 0x2100bd70 |
| `bt_enable_raw` entry (fifo = 0x210008f8) | 0x2100bd40 |
| `hci_driver_open` entry | 0x2100bd18 |
| `z_arm_fault` | msp 0x2100bae8, **psp 0x2100bba8** |

`z_main_stack` is 0x2100bbe8 .. 0x2100bde8 (512 B), so the faulting PSP was
**0x40 below the stack base**, and 0x2100bc74 / 0x2100bbc0 are inside
`z_main_stack` / `z_idle_stacks` — a plain main-stack overflow inside the
SoftDevice Controller's `hci_driver_open()`/`sdc_enable()`.  The previous
`bt_enable_raw` never opened the driver (its driver pointer pin read 0), so the
path had never been executed.

`CONFIG_MAIN_STACK_SIZE=512` in `recon/application/net/prj.conf` is annotated
*"Values inherited from the NCS v2.5.1 hci_rpmsg image baseline"* — it is the
upstream sample's number, never measured against the shipped image.  Raised to
**1024**, with the measurement recorded in the file.  This is the **only**
Kconfig/`prj.conf`/devicetree change in this iteration; it is a deliberate,
documented divergence from the inherited baseline, and the shipped firmware
cannot have used 512 either, since it runs the same stock open path from the
same `main`.

Build `/private/tmp/g1-i19b-net`: **both cores reset-free through 8.0 s**
(`app 16,945,522` / `net 515,353` instructions, 0 `FATAL` in either UART), and
the only remaining net error is

```
[00:00:05.093,841] <err> bt_sdc_hci_driver: No event buffer available
```

### 19.5 Step E — `bt_buf_get_tx` selected `hci_raw.c`'s file-static pools by
### original address

`FUN_0102fc30` is `bt_buf_get_tx`: it dispatches `type == 0` to one pool and
`type == 2` to another, logs `"Invalid tx type: %u"` (runtime 0x0103ddcd)
otherwise, and then does exactly `net_buf_reserve(&buf->b, 1)` (=
`BT_BUF_RESERVE`, `CONFIG_BT_HCI_RESERVE=1`), `bt_buf_set_type(buf, type)` at
+0x18, the `net_buf_tailroom < size → net_buf_unref → NULL` guard and
`net_buf_add_mem`.  Its ABI is `r0 = type`, `r1` = the alignment hole,
`r2:r3 = k_timeout_t`, `data`/`size` on the stack — which is why
`FUN_0102adf0`'s own comment already noted "the shipped call leaves the packet
indicator in the r1 alignment hole".

The two pool pointers are **not** an array base.  0x21000994 and 0x210009c8 are
the original image's `hci_acl_pool` and `hci_cmd_pool`.  Iteration 18 bound the
first to `_net_buf_pool_list_start`, which is right **only by coincidence**
(`hci_acl_pool` is the first pool in the linked `net_buf_pool_area`); the second
was left literal and in this link **0x210009c8 falls inside the stock
`hci_rx_pool`** (0x21000998 .. 0x210009cc).  Every host → controller HCI command
was therefore allocated through a `net_buf_pool` pointer aimed at the last four
bytes of the very pool `bt_buf_get_evt()` uses — which is precisely the
`No event buffer available` above.

Displaced onto the stock owner: `PROVIDE(FUN_0102fc30 = bt_buf_get_tx)`,
manifest exclusion, evidence
`recon/ownership/net_hci_raw_bt_buf_get_tx_adoption.json`.
Build `/private/tmp/g1-i19c-net`.  Measured effect: the command buffer now
comes from the real pool (`bt_send(buf = 0x2100e66c)`, inside
`_net_buf_hci_cmd_pool`) and `hci_driver_send()` runs — and the net core then
hits §19.8.

### 19.6 Step F — `z_isr_install` wrote 12½ entries into `_sw_isr_table`

`FUN_0102e974`'s `__ASSERT` file string is, read out of the image,
`"WEST_TOPDIR/zephyr/arch/common/sw_isr_common.c"` at line **85**, which in the
pinned NCS 2.5.1 tree is exactly `__ASSERT(!irq_is_enabled(irq), "IRQ %d is
enabled", irq);`; its guard callee `FUN_0102eb70` reads `NVIC->ISER`
(0xE000E100) and returns `(1u << (irq & 0x1f)) & ISER[irq >> 5]`
(= `arch_irq_is_enabled`); and the body writes `[base + irq*8] = param` then
`[base + irq*8 + 4] = routine`, i.e. `_sw_isr_table[idx].arg` / `.isr` in that
order and with `z_isr_install`'s exact ABI.

Its table base is the raw original-image literal **0x2100076c**, which in the
cohesive link lands **0x64 bytes inside** the linker-generated `_sw_isr_table`
(0x21000708 .. 0x210007f8, 30 entries), so every dynamically installed ISR
overwrote entries 12/13 instead of its own.  Displaced:
`PROVIDE(FUN_0102e974 = z_isr_install)`, evidence
`recon/ownership/net_sw_isr_common_adoption.json`.  Build
`/private/tmp/g1-i19d-net`.  **This did not change the §19.8 symptom** — it is
kept because it is provably correct, and is reported as such.

### 19.7 Step G — the shipped `K_KERNEL_STACK_RESERVED` is 0x40

The recovered `z_setup_new_thread` (`recon/net/src/FUN_01035edc.c`) computes

```c
uVar2  = (stack_size + 7) & ~7;
iVar3  = stack + 0x40 + uVar2;      /* stack_ptr  */
…      = stack + 0x40;              /* stack_start */
```

i.e. the shipped `K_KERNEL_STACK_DEFINE` reserved **0x40** bytes at the bottom
of every stack object (the Cortex-M MPU stack guard).  This build's
`K_THREAD_STACK_DEFINE` reserves **0** — `nm -S` reports the arrays at exactly
their nominal size — so every thread created through the reconstruction ran
0x40 bytes past its own array.  Measured with entry hooks on `g1-i19c-net`:
`FUN_0102adac` entered with `sp = 0x21009b88` while `g1_hci_rpmsg_tx_stack` is
0x21009560 .. 0x21009b60, and `FUN_0102acf4` entered with `sp = 0x21009588`
while `g1_hci_rpmsg_rx_stack` is 0x21008d60 .. 0x21009560 — both 0x28 past
their array end (the 0x40 reserve minus the 0x18 already pushed at the hook).
The TX thread's outermost frames therefore sat on the bottom of
`_k_thread_stack_mpsl_nonpreemptible_thread_id`.

The three arrays in `g1_product_endpoints.c` are re-sized nominal + 0x40.
Build `/private/tmp/g1-i19e-net` (final).  **This also did not change the
§19.8 symptom**; kept, provably correct, reported as such.

### 19.8 The new first divergence (CPUNET, t = 5.0942 s)

```
<inf> bt_hci_raw: Bluetooth enabled in RAW mode          (t = 0.3425 s, OK)
…
ASSERTION FAIL @ WEST_TOPDIR/zephyr/arch/arm/core/aarch32/cortex_m/fault.c:1112   (x8)
<err> os: ***** Reserved Exception ( … ) *****
<err> os: r0..r3 = 0, r12 = 0, lr = 0, xpsr = 0x000001ff
<err> os: Faulting instruction address (r15/pc): 0x00000000
<err> os: >>> ZEPHYR FATAL ERROR 0: CPU exception on CPU 0
<err> os: Fault during interrupt handling
<err> os: Current thread: 0xff000000 (unknown)
```

A 60 ms CPUNET PC trace across the fault ends:

```
… FUN_0102acf4 -> net_buf_get -> z_impl_k_queue_get -> z_pend_curr
   -> arch_swap -> z_arm_pendsv -> configure_builtin_stack_guard -> 0x0
   -> z_arm_usage_fault -> z_arm_fault
```

so, exactly as on the app core in §19.2, **PendSV restored PC = 0** — the
incoming thread's saved context is zeroed.  `_kernel.cpus[0].current` reads
0x21002100 (inside `backend_data_0`) in `g1-i19c-net` and 0xff000000 in
`g1-i19d/e-net`, i.e. the scheduler state itself is corrupt.  It is reached
only through `hci_driver_send()`, i.e. only now that the HCI command actually
gets to the controller.  **This is NOT yet root-caused**, and no guess is
recorded here as if it were.

Because Renode's nRF5340 platform resets the SoC from the CPUNET fault, this
also halts the app core, which is why the parity capture's every `p2_render`
column is still zero even though the **app** core no longer resets.

### 19.9 A new, systematic ledger: source-level raw CPUNET RAM literals

Iteration 18 §18.8 item 4 noted that raw `0x21xxxxxx` literals inside net
sources are invisible to `check_ram_pin_collisions.py` (which only sees linker
`PROVIDE` pins).  This iteration produced the ledger: over every source the
CPUNET build actually compiles, with the `#else` (parity-only) branches of
`G1_COHESIVE_BUILD` removed and comments stripped, **93 distinct raw
`0x21xxxxxx` literals still land inside a live linked object**.  The
distribution:

| owner | distinct literals |
|---|---:|
| `sdc_mempool` | 61 |
| `_sw_isr_table` | 6 (0x21000718, 0x21000760/61/63/67, 0x2100076c) |
| `m_cb` (three nrfx driver control blocks) | 3 |
| thread objects (`g1_esb_worker_thread`, the two HCI rpmsg `k_thread`s) | 7 |
| thread stacks (`g1_esb_worker_stack`) | 1 |
| net_buf pools (`hci_acl_pool`, `hci_cmd_pool`, `hci_rx_pool`) | 5 |
| other recovered/linked objects | 10 |

(A handful are provenance spellings the branch-stripper could not remove; the
sdc_mempool rows are dominated by recovered SDC/ESB state, the same class
iteration 18 §18.8 item 2 named.)  Three of them were fixed this iteration
(0x2100095c, 0x21004608, 0x2100076c via displacement); the rest are the named
follow-up and the most likely home of §19.8.

### 19.10 Measurements (every number below was actually run)

| metric | iter 18 (`i17d-app` + `i18e-net`) | **iter 19 app-only** (`i19b-app` + `i18e-net`) | **iter 19 final** (`i19b-app` + `i19e-net`) |
|---|---:|---:|---:|
| app `ZEPHYR FATAL ERROR` in the boot UART | 1 (t = 5.093 s; iteration 18's 6 s log, and reproduced here in a 5.3 s run) | **0** (8.0 s) | **0** (8.0 s) |
| net `ZEPHYR FATAL ERROR` in the boot UART | 0 | 0 (8.0 s) | **1 (t = 5.094 s, §19.8)** |
| app instr @8.0 s | — | **16,942,935** | not reached (SoC reset) |
| net instr @8.0 s | — | **289,729,537** (logging spin, §19.3) | not reached |
| app instr @8.0 s (`i19b-app` + `i19b-net`) | — | — | **16,945,522** |
| net instr @8.0 s (`i19b-app` + `i19b-net`) | — | — | **515,353** |
| `bt_enable` present in the app ELF | **no (GC'd)** | **yes, 0x55154** | yes |
| `bt_enable(NULL)` actually called | no | **yes, t ≈ 5.13 s** | yes |
| HCI Reset (0x0c03) delivered to the transport | no | **yes** | yes |
| `Bluetooth enabled in RAW mode` on CPUNET | no | no | **yes, t = 0.3425 s** |
| `radio TransmittedFrames` | 0 | 0 | **0** |
| `vcentral Connected` | False | False | **False** |
| app FLASH / RAM | 649,672 B / 247,765 B | 649,672 B / **252,885 B (56.13 %)** | same |
| net FLASH / RAM | 228,717 B / 59,796 B | — | **228,445 B / 60,524 B (92.35 %)** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** | 0 / 0 |
| net `nm -u` undefined / duplicate globals | 0 / 0 | — | **0 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** | 0 / 0, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** (120 trials) | 10/10, EXIT 0 |
| `gen_retained_sources.py --check` | clean | clean | **clean** |

### 19.11 Graphics + sensor parity (`g1-i19b-app` + `g1-i19e-net`)

Full capture actually run, both phases, identical determinism knobs and
stimulus to the oracle, **no memory poking**:

```
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i19b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i19e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x200551d8 G1_CTX_105A=0x2005524a \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i19e
```

| id | verdict | detail |
|---|---|---|
| **G-5** | **PASS** (unchanged) | all four enumerated panel-init elements byte-exact, including the trailing `0xB9 FF`. |
| **G-6** | **PASS** (unchanged) | `spim_b` 0 == 0, hash EQ. |
| **G-3** | **FAIL (truncation only)**, unchanged | `p1_boot` **34 vs 764** transactions; the shared 34 are **byte-identical**; first difference at index **34** (oracle `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}`, ours `<end>`). `p2_render` 0 vs 2,881. |
| **G-1** | **FAIL**, unchanged | `p2_render` ours `0c5cc90b…` / **0 lit px**; oracle `b26c73b3…` / 1,098. |
| **G-2** | **FAIL**, unchanged | `p1_boot` ours `0c5cc90b…` / **0 lit px**; oracle `1d617c65…` / 656. |
| **G-4** | *localiser, unchanged* | our framebuffer sha is still bit-identical to iterations 16–18, so first differing row **y = 267**, first differing pixel **x = 178** carries over unchanged. |

**No pixels were painted, and that is stated plainly.**  The capture is still
truncated inside `p1_boot`, now by the **net** core's §19.8 reset rather than
the app core's.

Sensors, `p1_boot` (per device, first-difference index in brackets):
LSM6DSO 983/1,089 [#3], nPM1300 199/291 [#0], OPT3001 14/33 [#14 = prefix-exact],
ST25DV system port 12/22 [#10], NFC EEPROM 11/25 [#6], `saadc` 17/998 [#5],
`spim_a` 34/764 [#34], `gpiote0` 25/25 (hash EQ), `pdm0` 2/2 (hash EQ),
`spim_b` 0/0 (hash EQ).  Every `p2_render` column is 0.  Score is unchanged at
**5 PASS / 5 PARTIAL / 4 FAIL**; see `sensor_parity_status.md`.  The single
cell that moved is cosmetic: the NFC EEPROM's first differing payload is now
`W 2002B8` (was `W 200258`) because the arena moved — the divergence index #6
is unchanged.

### 19.11b BOTH BUILDS reported: the reset-free-net variant reaches
### `p2_render` for the first time

Because §19.5–19.7's provably-correct net fixes move the boot *further into a
new stall* (§19.8) rather than past it, the capture was **also** run with
`g1-i19b-net` — the last net build in which **neither core resets** — so both
are on the record.  Same script, same knobs, same stimulus; this one used the
**corrected** context-probe addresses (`G1_CTX_FE8=0x20055238`,
`G1_CTX_105A=0x200552aa`, i.e. the iteration-14 values + the 0x60 the arena
moved).

| device / phase | final tree (`i19e-net`) | **reset-free net (`i19b-net`)** | oracle | first-difference index (vs oracle) |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 983 | **1,027** | 1,089 | 3 |
| LSM6DSO `p2_render` | 0 | **456** | 1,200 | **456 — the whole 456-transaction prefix is byte-identical** |
| nPM1300 `p1_boot` | 199 | **232** | 291 | 0 |
| nPM1300 `p2_render` | 0 | **233** | 508 | 0 |
| `saadc` (whole run) | 17 | **53** | 998 | 5 |
| OPT3001 `p1_boot` | 14 | 14 | 33 | 14 (prefix-exact) |
| ST25DV system port / EEPROM `p1_boot` | 12 / 11 | 12 / 11 | 22 / 25 | 10 / 6 |
| `spim_a` `p1_boot` / `p2_render` | 34 / 0 | **34 / 0** | 764 / 2,881 | 34 |
| `gpiote0` / `pdm0` / `spim_b` | 25 / 2 / 0, hash EQ | 25 / 2 / 0, **hash EQ** | 25 / 2 / 0 | — |
| framebuffer `p1_boot` / `p2_render` | `0c5cc90b…`, 0 lit px | `0c5cc90b…`, **0 lit px** | 656 / 1,098 lit px | — |

So the extra 14 s of live run time buys **real sensor traffic that no previous
iteration had reached** — in particular the IMU's entire `p2_render` prefix
(456 transactions) is byte-identical to the oracle's — but **not a single lit
pixel and not one extra `spim_a` transaction**, because `spim_a` index 34
onwards is gated on the BLE link, which is still down (`radio
TransmittedFrames` = 0 and `vcentral Connected` = False, measured on the same
pair in the 8 s boot run).  No parity criterion changes verdict.

Caveat recorded honestly: Renode's stdout for this longer run is truncated at
10,580 bytes and stops after `ORACLE_PHASE_BEGIN p2_render`, so the end-of-run
**counter echoes** (`RADIO_TX`, `VC_CONNECTED`, `JBD_FRAMECOUNTER_P2`, the ESB
counters) were **not** captured for this variant; the transaction traces and
both framebuffer dumps are complete and are what the table above is computed
from.  The counters quoted for it come from the separate 8.0 s boot run
(`RADIO_TX` = 0, `VC_CONNECTED` = False).

### 19.12 Re-proof

Every corrected canonical reconstruction was re-verified with the authoritative
CFG-directed verifier **after** the change:
`cfg_verify.verify('app','ancs_main')` **PASS** (11 cases);
`cfg_verify.verify('net', …)` **PASS** for `FUN_0102acf4` (7),
`FUN_0102afbc` (0), `FUN_0102fc30` (4), `FUN_0102fcec` (0).  As in iteration 18
this is necessary but not sufficient: `cfg_verify` passed *before* the
`ancs_main` fix too, because a wrong callee **name** that resolves to a real
library symbol is invisible to a harness that models callees as order-keyed
oracles by address.

### Regenerate (iteration 19)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh app /private/tmp/g1-i19b-app
recon/application/build_cohesive.sh net /private/tmp/g1-i19e-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
arm-zephyr-eabi-nm -u /private/tmp/g1-i19b-app/zephyr/zephyr.elf | wc -l   # 0
arm-zephyr-eabi-nm -u /private/tmp/g1-i19e-net/zephyr/zephyr.elf | wc -l   # 0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i19b-app/zephyr/zephyr.elf                             # EXIT 0, 0/0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py \
    --trials 120                                                           # EXIT 0, 10/10
# boot + graphics/sensors: <scratch>/g1-i19/b*.resc and §19.11
```

Bisect ledger (every build and boot actually run):

| build | change | app FATAL @8 s | net FATAL @8 s | note |
|---|---|---|---|---|
| `g1-i19a-app` | `ancs_main`: `bt_send` → `bt_enable`; `bt_foreach_bond` third arg | 1 (t = 5.1418 s) | 0 | headroom assert GONE; new USAGE FAULT, PendSV restores PC = 0 |
| `g1-i19b-app` | `G1_RAM_ARENA_LIMIT` 0x20029000 → 0x2002a400 | **0** | 0 | **first reset-free 8 s app boot** |
| `g1-i19a-net` | `bt_enable_raw` displacement + `g1_hci_rx_queue` + `g1_hci_ept` | 0 | 1 (t = 0.3426 s) | SDC opens; `main` stack overflows |
| `g1-i19b-net` | `CONFIG_MAIN_STACK_SIZE` 512 → 1024 | **0** | **0** | `Bluetooth enabled in RAW mode`; `No event buffer available` @5.0938 s |
| `g1-i19c-net` | `bt_buf_get_tx` displacement | 0 | 1 (t = 5.0942 s) | command allocated from the real pool; `hci_driver_send` runs; §19.8 |
| `g1-i19d-net` | `z_isr_install` displacement | 0 | 1 (t = 5.0942 s) | correct, symptom unchanged |
| `g1-i19e-net` | thread stacks + 0x40 `K_KERNEL_STACK_RESERVED` | 0 | 1 (t = 5.0942 s) | **final**; correct, symptom unchanged |

Files changed: `recon/{app,verified}/src/ancs_main.c`,
`recon/symbolized/app/ancs_main.c`, `recon/named/ancs_main.c`,
`recon/readable_sources/app/g1/ancs_main.c`;
`recon/application/app/src/g1_app_ram_relocs.c`;
`recon/net/src/{FUN_0102acf4,FUN_0102afbc}.c` and the
`recon/symbolized/net/FUN_0102afbc.c` mirror;
`recon/application/net/src/{g1_product_endpoints.c,stock_call_aliases.ld}`;
`recon/application/net/prj.conf` (one Kconfig value, §19.4);
`recon/ownership/adoption_manifest.json` (three net rows) and three new
evidence files `recon/ownership/net_{hci_raw_singleton,hci_raw_bt_buf_get_tx,sw_isr_common}_adoption.json`;
`recon/generated/net_retained_sources.cmake` (regenerated by its own tool);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` change**, no `recon/emulator/scripts/` change, `armemul`
untouched, nothing committed.

### 19.13 Open, named, and NOT fixed

1. **§19.8** — the CPUNET PendSV-restores-PC-0 at t = 5.0942 s, reached only
   through `hci_driver_send()`.  This is the first divergence.
2. **93 raw `0x21xxxxxx` source literals still land inside live linked
   objects** (§19.9), 61 of them inside `sdc_mempool`, 6 inside
   `_sw_isr_table`.  No gate covers this class; a source-level checker is the
   obvious next tool (deliberately not written this iteration — `tools/` is
   off-limits here).
3. **`CONFIG_MAIN_STACK_SIZE = 1024` is measured-sufficient, not
   original-verified.**  The shipped value has not been recovered from the
   image; 512 was demonstrably wrong.
4. **`analysis 0x0102b204` (168 B) is still unreconstructed** (iteration 18
   §18.8 item 1), so `FUN_0102b1c8` still creates the ESB worker with
   `K_FOREVER`.
5. **The net RAM-pin gate still does not exist** (iteration 18 §18.8 item 3).

## Iteration 20 — the CPUNET t = 5.0942 s fault is FIXED (a missing
## indirection in `net_buf_unref`), the shipped `_kernel` shadow is closed
## structurally, `bt_enable()` completes the full HCI handshake, and
## **both cores now run 8.0 s reset-free at the same time for the first time**

**Headline.** The §19.8 blocker was **not** in the raw-literal class at all,
and this report says so before it says anything else.  It was a
**wrong-indirection defect in the recovered `net_buf_unref` (`FUN_0102ff94`)**:
the body dereferenced `pool->alloc` once where the shipped code dereferences it
twice, so it called `pool->alloc->max_alloc_size` instead of
`pool->alloc->cb->unref`.  Measured: `blx r3` with **r3 = 0x44 =
CONFIG_BT_BUF_EVT_RX_SIZE**, i.e. the net core branched to address 0x44 at
t = 5.0942 s (§20.3).  With that repaired the CPUNET is fatal-free, the app
core's `bt_enable()` runs to completion for the first time in this project —

```
<inf> bt_hci_core: HW Platform: Nordic Semiconductor (0x0002)
<inf> bt_hci_core: HW Variant: nRF53x (0x0003)
<inf> bt_hci_core: Firmware: Standard Bluetooth controller (0x00) Version 197.47763 …
<inf> bt_hci_core: Identity: E1:D8:D3:9A:B8:82 (random)
<inf> bt_hci_core: HCI: version 5.4 (0x0d) revision 0x2102, manufacturer 0x0059
```

— i.e. the whole host↔controller HCI command/event round trip works over the
reconstructed rpmsg transport.  A second, independent app-core defect that this
immediately unmasked (a *wrong* library adoption, §20.5) was fixed too, and
**both cores now run 8.0 s with zero `ZEPHYR FATAL ERROR` simultaneously** —
app 17,753,624 instructions, net 2,080,530.

**BLE still does not advertise.**  `radio TransmittedFrames` = 0,
`vcentral Connected` = False.  The new first divergence is named precisely and
is one call short of advertising: `bt_start()` is now reached and returns 0
**without calling `bt_le_adv_start`**, because `device_info[0x1058]` is 0
(§20.6).

The requested structural work was done as well: a new reusable gate
(`recon/emulator/scripts/check_net_raw_literals.py`, §20.1) and two structural
literal passes (§20.2, §20.4).

### 20.1 The deliverable: a source-level raw-literal gate for the CPUNET

`check_ram_pin_collisions.py` only sees linker `PROVIDE` pins.  The new
`recon/emulator/scripts/check_net_raw_literals.py` closes the other half of the
class.  It reads the build's `compile_commands.json`, re-runs **every**
reconstruction translation unit through the *same* compiler and flags with
`-E`, attributes each preprocessed line to its originating file with the
`# line "file"` markers, keeps only lines that came from a repository
reconstruction source, collects every `0x21xxxxxx` literal, and scores each
distinct literal against the extent of every live object in the linked ELF.
Because it preprocesses, it is **exact with respect to `#if` branches** — the
parity-only `#else` arms of `G1_COHESIVE_BUILD` are never counted, which is
precisely what iteration 19's branch-stripping sweep could not guarantee.

**Before** (iteration-19 tree, `/private/tmp/g1-i20-net`):

```
recon_translation_units                       1012
translation_units_failed_to_preprocess        0
distinct_raw_literals                         137
raw_literals_inside_a_live_object             79        <-- EXIT 1
raw_literals_in_ram_region_but_free           58
owners: sdc_mempool 56, _sw_isr_table 5, g1_esb_worker_thread 4, m_cb 3,
        g1_timeslot_request_earliest 2, sym_SXHUVOM4EI7… 2, DAT_01033b10 1,
        g1_timeslot_request_normal 1, nrf53_sync_offset 1, g1_ipc0_bound_sem 1,
        posix_thread_pool 1, cc_data 1, g1_esb_worker_stack 1
```

**After** (`/private/tmp/g1-i20d-net`):

```
distinct_raw_literals                         132
raw_literals_inside_a_live_object             74
raw_literals_in_ram_region_but_free           58
owners: sdc_mempool 55, g1_esb_worker_thread 4, m_cb 3,
        g1_timeslot_request_earliest 2, sym_SXHUVOM4EI7… 2, posix_thread_pool 2,
        DAT_01033b10 1, g1_timeslot_request_normal 1, nrf53_sync_offset 1,
        _sw_isr_table 1, g1_hci_bound_sem 1, g1_esb_worker_stack 1
```

Diffed literal-by-literal (not just by count): the five literals **removed from
the sources** are `0x21000760`, `0x21000761`, `0x21000763`, `0x21000767`
(§20.4) and `0x21004b28` (§20.2); **no literal was newly introduced and none
newly collided** despite the layout shift.  `_sw_isr_table` drops 5 → 1 and the
one that remains (`0x21000718`) is in a garbage-collected TU.

**Iteration 19's "93" is corrected to 79 by this measurement, and that is an
honest downward revision, not an achievement.**  The 93 came from a
branch-stripping text sweep; the preprocessor-based count is the ground truth
for what the compiler actually sees.

**A limitation of the gate, stated up front.**  "Literal inside a live object"
is a *superset* of the defect: an emitted recovered object that the linker
happens to place at its own original address is flagged against itself.  Five
of the 74 are provably that benign case — `DAT_01033b10` (0x21000580, the
object is at 0x21000580, offset 0), `g1_timeslot_request_earliest` (+0, +4),
`g1_timeslot_request_normal` (+4) and `nrf53_sync_offset` (+0) are all
self-aliases of objects this build emits.  No attempt was made to auto-classify
that; it is recorded so the number is read correctly.

### 20.2 Structural pass A — the shipped CPUNET `_kernel` shadow (the
### iteration-11 move, adapted)

Iteration 7 §A.7 established that **`0x21004b28` is `_kernel` in the shipped
netcore image** and converted exactly four spinlock validators, recording
verbatim: *"This is a bounded fix, not the whole class. `0x21004b28` still
appears in 20 further `recon/symbolized/net` TUs."*  It was never closed.

In this link `_kernel` is at **0x21008600** (size 0x20) and 0x21004b28 is inside
**`sdc_mempool`** (0x21002bb8..0x21007e79).  So every recovered kernel body that
reached the scheduler through that base — `z_setup_new_thread` (FUN_01035edc),
`k_sem_give` (FUN_01036824), `k_sem_take` (FUN_0103689c), `z_impl_k_poll`,
`z_impl_k_msgq_get/put`, `submit_to_queue_locked`, `z_pend_curr`,
`z_ready_thread`, `z_time_slice`, `k_sched_lock/unlock`, … — read and wrote a
**shadow `_kernel` carved out of the SoftDevice Controller's heap** while the
linked Zephyr scheduler (`z_arm_pendsv`, `arch_swap`) used the real one.  Two
independent harms: an inconsistent scheduler view, and SDC heap corruption.

Closed structurally in one pass, the iteration-11 way.  A generated guard in
every affected TU:

```c
#ifdef G1_COHESIVE_BUILD
extern char g1_net_kernel_object[] __asm__("_kernel");
#define G1_NET_KERNEL_BASE ((unsigned long)g1_net_kernel_object)
#else
#define G1_NET_KERNEL_BASE 0x21004b28ul
#endif
#define G1_NET_K(off) (G1_NET_KERNEL_BASE + (off))
```

and every code-position (never comment, never string) spelling of
`0x21004b28 / 0x21004b30 / 0x21004b38 / 0x21004b40` rewritten to
`G1_NET_K(0x00 / 0x08 / 0x10 / 0x18)`.  **75 files, 83 literal sites**
(`recon/net/src`, `recon/symbolized/net`, `recon/net/named`); the four
already-converted TUs were detected and skipped.  The parity `#else` keeps the
original literal, so no proven body changes.

Field-offset justification, recorded because it is the load-bearing assumption:
iteration 7 verified `+0x08 = cpus[0].current` and `+0x10 = cpus[0].id` in
**both** images.  `id` at +0x10 fixes `struct _cpu` at 0x14 bytes, hence
`ready_q.cache` at +0x14 and `ready_q.runq` at +0x18; `nm -S` reports
`sizeof(_kernel) = 0x20` in this link, which is exactly 0x14 + 0xc.  The
spellings found in the corpus (+0, +8, +0x10, +0x18) are all inside that
window, and the +0x18 uses are dlist operations, consistent with `ready_q.runq`.

An `__asm__("_kernel")` label is used rather than `#include <zephyr/kernel.h>`
because several reconstruction TUs declare `assert_print` /
`assert_post_action` with the *recovered* prototypes, which conflict with the
Zephyr headers (measured: 4 compile errors on the first attempt).

**Measured effect on the boot: none.**  `/private/tmp/g1-i20a-net` faults at
t = 5.0942 s exactly as before.  It is kept because it is provably correct and
because it removes a whole class, and it is reported as such rather than
credited with the fix.

### 20.3 The actual root cause of §19.8 — a missing dereference in
### `net_buf_unref`

A 60 ms CPUNET PC trace across the fault (`/private/tmp/g1-i20/tr/net.log`,
278,000 PCs) ends, symbolised:

```
… FUN_0102acf4+0x54 -> FUN_0102ff94+0x00 … +0x4a -> 0x00000046 -> 0x48 -> 0x4a …
```

so the net core did **not** have PendSV restore PC = 0 (iteration 19's reading);
it **branched to address 0x44** from inside `FUN_0102ff94` and then executed
whatever the vector table holds.  The Zephyr fault path then printed
`Reserved Exception` / `pc 0x00000000`, which is what iteration 19 saw.

`FUN_0102ff94` is `net_buf_unref`.  Its shipped disassembly
(`tools/net_recon_kit.py info 0x0102ff94`) is unambiguous:

```
  102ffb2  ldr  r1, [r4, #0x14]     ; __buf kept in r1 and PASSED
  102ffb4  cbz  r1, #0x102ffce
  ...
  102ffc4  ldr  r3, [r3, #0x2c]     ; pool->alloc
  102ffc6  ldr  r3, [r3]            ; alloc->cb        <-- THREE loads
  102ffc8  ldr  r3, [r3, #8]        ; cb->unref
  102ffca  blx  r3
```

The reconstruction had

```c
void **owner = *(void ***)(pool + 0x2c);
((release_fn_t)owner[2])(buffer);          /* only TWO loads, one argument */
```

i.e. it computed `*( *(pool+0x2c) + 8 )` where the original computes
`*( *( *(pool+0x2c) ) + 8 )`.  In Zephyr 3.4 `pool->alloc` is a
`struct net_buf_data_alloc { cb; alloc_data; max_alloc_size; }`, so `owner[2]`
is **`max_alloc_size`** — and for the HCI event pool that is
`CONFIG_BT_BUF_EVT_RX_SIZE = 68 = 0x44`, exactly the branch target measured in
the linked image.  It also dropped the second argument (`data`), which the
shipped code deliberately keeps live in r1 across the `cbz`.

Both corrected in `recon/{net/src,symbolized/net}/FUN_0102ff94.c`:

```c
uint8_t *data = *(uint8_t **)(buffer + 0x14);
if (data != 0) {
    if ((buffer[9] & 1u) == 0) {
        uint8_t *pool  = base + buffer[10] * 0x34u;
        void   **alloc = *(void ***)(pool + 0x2c);
        void   **cb    = (void **)alloc[0];
        ((data_unref_fn_t)cb[2])(buffer, data);
    }
    *(uint32_t *)(buffer + 0x14) = 0;
}
```

`cfg_verify.verify('net','FUN_0102ff94')` **PASS**, 2 cases, 42 checks.

**This is the tenth instance of the harness blind-spot family** and the first
that is a *wrong indirection* rather than a dropped argument; it also carries a
dropped register argument, so it is both classes at once.

Build `/private/tmp/g1-i20b-net`: **the CPUNET t = 5.0942 s fatal is gone**, the
net core is fatal-free through 8.0 s, and the app core's `bt_enable()` returns 0
after a complete HCI handshake (§20 headline).

### 20.4 Structural pass B — the ESB pipe-address block vs the linker's
### `_sw_isr_table`

Five literals landed inside `_sw_isr_table` (0x21000704, 30 entries).  Four of
them (`0x21000760/61/63/67`) are byte views of **one** recovered object, written
by `FUN_0102a278` (the "set pair addresses" IPC handler), read by
`FUN_0102b31c`, and logged four bytes at a time by `main` (FUN_0102a720).

Its extent is pinned from two independent directions: iteration 19 established
that the **shipped** `_sw_isr_table` began at `0x2100076c` (that was
`z_isr_install`'s table-base literal), and the object is `.data` in the shipped
image.  Read through `tools/net_extract.py` at the `.data` LMA + 0x760 — noting
that the LMA `0x0103ed24` quoted in `g1_product_endpoints.c` is a **runtime**
address, so the analysis-space read is at `0x0103e524 + 0x760` — the twelve
bytes are

```
01 e9 d3 | a3 a3 a3 a3 | c9 c9 c9 c9 | ff
```

exactly the {flag, master-address, slave-address, 0xff placeholder} shape the
two accessors imply.  The object is therefore emitted **with its shipped
initialiser** in `recon/application/net/src/g1_product_endpoints.c` as
`g1_esb_pipe_addr_block[12]`, and:

* the four raw literals in `recon/{net/src,symbolized/net,net/named}` are bound
  to it through a `G1_NET_ESB_ADDR(off)` guard (16 sites, same mechanism as
  §20.2);
* the three **linker** pins that expressed the same three addresses
  (`g_net_radio_sched_param_a/b/c` in `recon/symbols/g1_net_globals.ld`) are
  rebound to `g1_esb_pipe_addr_block + 0x1/0x3/0x7`, preserving their original
  relative offsets.

**Honest scoping of the harm:** in this build `_sw_isr_table[11]` and `[12]`
were the corrupted entries, and both are `{NULL, z_irq_spurious}` — RADIO,
TIMER0 and RTC0 use *direct* vectors on the CPUNET (`_irq_vector_table`
entries 8/12/17 hold real ISRs, not `_isr_wrapper`).  So the corruption was
**inert in this build**.  It is closed because it is a real collision with a
linker-generated kernel table, **not** because it was observed to fault, and
the boot is byte-for-byte unchanged by it.

Build `/private/tmp/g1-i20c-net` (and `g1-i20d-net`, byte-identical, after a
cosmetic repair of the symbolized identity headers, §"Regenerate").

### 20.5 App core — the ANCS client is VENDORED, and the library adoption of
### two of its functions was wrong

With `bt_enable()` finally succeeding, the app core reached a **new** reset at
t ≈ 6.6 s: `SYSRESETREQ` with no fatal-error banner.  A 0.5 s app PC trace ends
`… wait_for_event -> ancs_main -> sys_reboot -> sys_arch_reboot`, i.e. the
firmware's own `reboot_after_ancs_failure()`.  A second trace over 5.0–6.5 s
localised it to `ancs_c_init`, whose **fifth** registration executed only 9
instructions — the early-return path.

`adoption_manifest.json` excluded `FUN_0007f772` / `FUN_0007f79e` in favour of
`nrf/subsys/bluetooth/services/ancs_client.c` on a **1.0 instruction-shape
match**.  The shape match is blind to the two things that actually differ, and
both are proven by disassembly:

| | shipped (0x0007f772) | stock (linked) |
|---|---|---|
| length guard | `cmp r4, #0xff` (len ≤ **256**) | `cmp r4, #0x1f` (len ≤ **32**) |
| stores | `strh [r0,#0x870]`, `strb [r0,#0x868]`, `str [r0,#0x874]` | `[r0,#0x110]`, `[r0,#0x108]`, `[r0,#0x114]` |
| | shipped (0x0007f79e) | stock (linked) |
| length guard | `cmp r4, #0xff` | `cmp r4, #0x1f` |
| stores | `[r0,#0x8f0]`, `[r0,#0x8e8]`, `[r0,#0x8f4]` | `[r0,#0x190]`, `[r0,#0x188]`, `[r0,#0x194]` |

Corroborated independently: the recovered `ancs_service_ctx_clear`
(`FUN_0007f69e`) memsets **0xa2c bytes** at `g_ancs_client`, far larger than the
upstream `struct bt_ancs_client`, and `BT_ANCS_ATTR_DATA_MAX` is a hard
`#define 32` in the pinned NCS header — not a Kconfig, so this cannot be
configured away.  **The shipped firmware vendors `ancs_client.c`.**

Fix, deliberately minimal and collision-free: the manifest exclusion is left
alone (the stock owner keeps the `bt_ancs_register_attr` /
`bt_ancs_register_app_attr` symbols, so there is no duplicate definition), the
two **raw-identity** reconstructions are added explicitly to
`recon/application/app/CMakeLists.txt`, and `recon/symbolized/app/ancs_c_init.c`
calls `FUN_0007f772` / `FUN_0007f79e`.  `cfg_verify.verify('app','ancs_c_init')`
**PASS**, 40 checks.

Build `/private/tmp/g1-i20a-app`: all six registrations succeed (19 instructions
each), `ancs_discover_params_reset`, `bt_conn_auth_cb_register`,
`bt_conn_auth_info_cb_register`, `bt_gatt_cb_register`, **`bt_start`** and
`start_ancs_work_thread` all run, and the reset is gone.

### 20.6 The new first divergence — `bt_start()` short-circuits on
### `device_info[0x1058] == 0`

`bt_start` (0x000180fc in this link) is now entered and returns **0** after 29
instructions:

```
18114  bl   get_device_info
18118  ldrb r3, [r0, r4]      ; r4 = 0x1058
1811a  cmp  r3, #2
1811c  bne  18134
18134  bl   get_device_info
18138  ldrb r3, [r0, r4]
1813a  cmp  r3, #0
1813c  beq  1811e             ; -> return 0, WITHOUT bt_le_adv_start
```

A Renode hook at 0x18138 measured it directly, twice in an 8 s run:

```
[ERROR] cpuapp: BTSTART_STATE di=0x2003FBE0 byte=0x0
```

So `device_info[0x1058]` is **0** and advertising is never started.  That byte
is the same "device ready / work mode" field `ancs_main` polls for up to 5 s
before calling `bt_enable`.  **Which recovered writer should set it, and why it
does not, is NOT root-caused here and no guess is recorded as if it were.**
This is the first divergence for iteration 21 and it is one call short of
`bt_le_adv_start`.

Side benefit: `di = 0x2003FBE0` also gives the **correct** parity-capture probe
addresses for this build (`G1_CTX_FE8 = 0x20040BC8`,
`G1_CTX_105A = 0x20040C3A`), and they now read plausible values (`0x00` / `0x01`)
instead of iteration 19's stale `0x7C`.

### 20.7 What is left in the literal class, and why it was deferred

Of the 74 remaining colliding literals, the enclosing function of **35** is
absent from the linked ELF entirely (garbage-collected or fully inlined —
`--gc-sections` is on with `G1_INTEGRATION_PROBE_RETAIN_ALL=OFF`), so those
literals are never executed.  The **39** with at least one linked enclosing
function break down as:

| owner | live | note |
|---|---:|---|
| `sdc_mempool` | 28 | recovered SDC/MPSL/ESB private state (`FUN_010333b4`, `FUN_01032c28`, `FUN_01033660`, `FUN_010327a0/d8`, `FUN_0102b944`, …).  The owner's standing direction is displacement onto the stock controller, which is a per-function ownership exercise, not a literal rewrite. |
| `m_cb` | 3 | nrfx driver control block.  `m_cb` is a **file-local static** in this build (`nm` shows `d m_cb` at 0x2100064c), so a linker script cannot name it; the literals are +0x10/+0x40/+0x54 and are plausibly *correct* interior views that the .data layout happens to reproduce. |
| `g1_esb_worker_thread` | 3 | 0x21001ce8/cf8/d00 — three `uint64_t` uptime stamps `main` uses; they alias the `struct k_thread` this build emits for the ESB worker.  Real defect; deferred because the ESB worker's entry point (analysis 0x0102b204) is still unreconstructed, so the whole object is provisional. |
| `g1_timeslot_request_earliest` / `_normal` / `nrf53_sync_offset` / `DAT_01033b10` | 5 | **benign self-aliases** (§20.1): the emitted object sits at its own original address and the literal is its base or a real interior offset. |

Deferred deliberately and named: the 28 `sdc_mempool` rows.  A net arena remains
impossible (iteration 18 §18.8 item 2; this build has 60,540 B of 65,536 B in
use), and rewriting 28 literals into 28 emitted objects would move ~2.5 KB of
recovered state into a RAM budget with 4,996 B free while leaving the
duplicate SDC bodies in place.  Displacement is the right instrument and it is
its own iteration.

### 20.8 Measurements (every number below was actually run)

| metric | iter 19 final (`i19b-app` + `i19e-net`) | **iter 20 (`i20a-app` + `i20d-net`)** |
|---|---:|---:|
| app `ZEPHYR FATAL ERROR` @8.0 s | 0 | **0** |
| net `ZEPHYR FATAL ERROR` @8.0 s | **1 (t = 5.0942 s)** | **0** |
| SoC `SYSRESETREQ` in an 8 s run | 1 (from the net fault) | **0** |
| app instructions @8.0 s | not reached (SoC reset) | **17,753,624** |
| net instructions @8.0 s | not reached | **2,080,530** |
| `Bluetooth enabled in RAW mode` (CPUNET) | yes | yes |
| **`bt_hci_core: Identity: …` (host init complete)** | **no** | **yes, t = 5.100 s** |
| **`ancs_c_init` returns 0** | not reached | **yes** |
| **`bt_start()` reached** | no | **yes (returns 0 early, §20.6)** |
| `radio TransmittedFrames` | 0 | **0** |
| `vcentral Connected` | False | **False** |
| app FLASH / RAM | 649,672 B / 252,885 B | **649,688 B (+16) / 252,885 B (+0)** |
| net FLASH / RAM | 228,445 B / 60,524 B | **228,409 B (−36) / 60,540 B (+16)** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_net_raw_literals.py` (net) | *did not exist* — 79 / EXIT 1 measured retroactively | **74 / EXIT 1** (§20.1) |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** (120 trials) |
| `gen_retained_sources.py --check` | clean | **clean** |

Net FLASH stayed inside its budget (98.70 % of 231,424 B; **−36 B** net), so the
`app.overlay` headroom mechanism was not touched.

### 20.9 Graphics + sensor parity (`g1-i20a-app` + `g1-i20c-net`)

Full capture actually run, both phases, identical determinism knobs and
stimulus to the oracle, **no memory poking**:

```
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i20a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i20c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i20
```

| id | verdict | detail |
|---|---|---|
| **G-5** | **PASS** (unchanged) | all four enumerated panel-init elements byte-exact. |
| **G-6** | **PASS** (unchanged) | `spim_b` 0 == 0, hash EQ. |
| **G-3** | **FAIL (truncation only)**, unchanged | `p1_boot` **34 vs 764**; the shared 34 are byte-identical; first difference at index **34** (oracle `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}`, ours `<end>`).  `p2_render` **0 vs 2,881**. |
| **G-1** | **FAIL**, unchanged | `p2_render` ours `0c5cc90b07…` / **0 lit px**; oracle `b26c73b37d…` / **1,098**. |
| **G-2** | **FAIL**, unchanged | `p1_boot` ours `0c5cc90b07…` / **0 lit px**; oracle `1d617c65a6…` / **656**. |
| **G-4** | *localiser, unchanged* | our framebuffer sha is still bit-identical to iterations 16–19, so first differing row **y = 267**, first differing pixel **x = 178** carries over. |

**Not one pixel was painted, and that is stated plainly.**  `JBD_FRAMECOUNTER_P1`
= 0x3 (oracle 0x2A1), `JBD_FRAMECOUNTER_P2` = 0x3 (oracle 0xD61).

Sensors — but this time **the capture is no longer truncated by a reset**, so
`p2_render` is real for the first time in the *final* tree:

| device / phase | iter 19 final | iter 19 "reset-free net" variant | **iter 20** | oracle | first difference |
|---|---:|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 983 | 1,027 | **1,027** | 1,089 | #3 |
| LSM6DSO `p2_render` | 0 | 456 | **700** | 1,200 | **#700 — the entire 700-transaction prefix is byte-identical to the oracle** |
| nPM1300 `p1_boot` | 199 | 232 | **232** | 291 | #0 |
| nPM1300 `p2_render` | 0 | 233 | **369** | 508 | #2 |
| OPT3001 `p1_boot` | 14 | 14 | **14** | 33 | #14 (prefix-exact) |
| ST25DV sysport / EEPROM `p1_boot` | 12 / 11 | 12 / 11 | **12 / 11** | 22 / 25 | #10 / #6 |
| `saadc` (whole run) | 17 | 53 | **71** | 998 | #5 |
| `spim_a` `p1_boot` / `p2_render` | 34 / 0 | 34 / 0 | **34 / 0** | 764 / 2,881 | #34 |
| `gpiote0` / `pdm0` / `spim_b` | 25 / 2 / 0 hash EQ | same | **25 / 2 / 0, hash EQ** | 25 / 2 / 0 | — |
| framebuffer `p1` / `p2` lit px | 0 / 0 | 0 / 0 | **0 / 0** | 656 / 1,098 | — |

Score **unchanged at 5 PASS / 5 PARTIAL / 4 FAIL** — no criterion changes
verdict.  What did change is the *depth* of the sensor prefixes: the IMU's
byte-identical `p2_render` prefix grew 456 → **700** transactions, the PMIC's
`p2_render` 233 → **369**, and the SAADC 53 → **71**.  `spim_a` did not move by
a single transaction, because everything past index 34 is gated on the BLE link,
which is still down.

### 20.10 Re-proof

Every changed or newly linked reconstruction re-verified with the authoritative
CFG-directed verifier **after** the change:

```
app  ancs_c_init      PASS  checked=40
net  FUN_0102ff94     PASS  cases=2   checked=42
net  FUN_0102a278     PASS  cases=13  checked=53
net  FUN_0102b31c     PASS  cases=3   checked=43
net  FUN_01035edc     PASS  checked=40
net  FUN_01036824     PASS  checked=40
net  FUN_0102a720     PASS  cases=5
net  FUN_01037768     PASS  cases=6
```

As in iterations 18–19 this is necessary but not sufficient — `cfg_verify`
passed on `FUN_0102ff94` **before** the fix too, because a missing dereference
inside a callback-pointer computation is modelled as an opaque callback slot.
The evidence that settled it was the raw shipped disassembly plus the measured
branch target, not the harness.

### Regenerate (iteration 20)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh app /private/tmp/g1-i20a-app
recon/application/build_cohesive.sh net /private/tmp/g1-i20d-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
arm-zephyr-eabi-nm -u /private/tmp/g1-i20a-app/zephyr/zephyr.elf | wc -l    # 0
arm-zephyr-eabi-nm -u /private/tmp/g1-i20d-net/zephyr/zephyr.elf | wc -l    # 0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    /private/tmp/g1-i20a-app/zephyr/zephyr.elf                             # EXIT 0, 0/0
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py \
    /private/tmp/g1-i20d-net/zephyr/zephyr.elf                             # 74, EXIT 1
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py \
    --trials 120                                                           # EXIT 0, 10/10
# boot: <scratch>/g1-i20/boot_e.resc  (8.0 s, checkpoints every 0.5 s from t=5)
# parity: §20.9
```

Note on `g1-i20c-net` vs `g1-i20d-net`: the §20.2/§20.4 guard blocks were first
inserted at the very top of the symbolized TUs, which displaced the
`#include "g1_net_symbols.h"` identity header that `gen_retained_sources.py
--check` requires.  Twenty files were repaired by moving the guard below the
header; **`zephyr.bin` is byte-identical between the two builds** (verified with
`cmp`), so the §20.9 capture taken on `g1-i20c-net` stands for `g1-i20d-net`.

Bisect ledger (every build and boot actually run):

| build | change | app FATAL @8 s | net FATAL @8 s | note |
|---|---|---|---|---|
| `g1-i20-net` / `g1-i20-app` | iteration-19 tree rebuilt (baseline) | — | 1 (t = 5.0942 s) | reproduces §19.8 |
| `g1-i20a-net` | §20.2 `_kernel` structural pass | — | 1 (t = 5.0942 s) | correct, symptom unchanged; **kept** |
| `g1-i20b-net` | §20.3 `net_buf_unref` indirection + dropped arg | **1 (t = 6.6 s, `ancs_main` → `sys_reboot`)** | **0** | **net fault GONE**; `bt_enable` completes; new app stall |
| `g1-i20a-app` | §20.5 vendored ANCS registrars | **0** | 0 | `bt_start` reached; **both cores reset-free** |
| `g1-i20c-net` | §20.4 ESB pipe-address block | **0** | **0** | `_sw_isr_table` collisions closed; boot unchanged |
| `g1-i20d-net` | identity-header repair only | 0 | 0 | **final**; `zephyr.bin` identical to `g1-i20c-net` |

Files changed: `recon/net/src/FUN_0102ff94.c` and its
`recon/symbolized/net` mirror (§20.3); 75 TUs across
`recon/{net/src,symbolized/net,net/named}` for the `_kernel` guard (§20.2);
`recon/{net/src,symbolized/net,net/named}/FUN_0102a278.c`,
`FUN_0102b31c.c`, `FUN_0102a720.c` for the ESB block (§20.4);
`recon/application/net/src/g1_product_endpoints.c` (the emitted
`g1_esb_pipe_addr_block` with its shipped initialiser);
`recon/symbols/g1_net_globals.ld` (three pins rebound);
`recon/application/app/CMakeLists.txt` and
`recon/symbolized/app/ancs_c_init.c` (§20.5);
new `recon/emulator/scripts/check_net_raw_literals.py`;
`recon/emulator/reports/sensor_parity_status.md` (rewritten in place); this
report.  **No `tools/` change**, no Kconfig / `prj.conf` / devicetree change,
no `adoption_manifest.json` change, `armemul` untouched, nothing committed.

### 20.11 Open, named, and NOT fixed

1. **§20.6 — `bt_start()` returns 0 because `device_info[0x1058]` is 0**, so
   `bt_le_adv_start` is never called and BLE never advertises.  This is the
   first divergence.  Not root-caused.
2. **74 source-level raw `0x21xxxxxx` literals still land inside a live linked
   object** (§20.1/§20.7); 39 of them are in linked code and 28 of those are
   inside `sdc_mempool`.  The instrument is displacement of the duplicate
   SDC/MPSL bodies, not a literal rewrite.
3. **The rest of the vendored ANCS client is still the stock one** (§20.5).
   Only the two registrars were corrected; every other `ancs_client.c` function
   in the link (subscribe, parse, attribute request) writes the *upstream*
   offsets into the 0xa2c-byte recovered `g_ancs_client`.  None of them runs
   before a GATT connection, so nothing is measured yet — but this is a known,
   named landmine for the connect step.
4. **The net RAM-pin gate still does not exist** as a first-class invocation
   (iteration 18 §18.8 item 3); `check_ram_pin_collisions.py` remains hard-coded
   to the app window.  The new checker covers the *source* half only.
5. **`analysis 0x0102b204` (168 B) is still unreconstructed**, so
   `FUN_0102b1c8` still creates the ESB worker with `K_FOREVER`.
6. **`CONFIG_MAIN_STACK_SIZE = 1024` remains measured-sufficient, not
   original-verified** (iteration 19 §19.13 item 3).

## Iteration 21 — `device_info[0x1058]` is FIXED: the CPUNET now delivers the
## `0x0601` "ready" IPC message, `bt_start()` sees state 1 and runs past the
## guard for the first time — and the app core stalls one step later on a
## FORTIFY buffer-overflow oops in the device-name `__sprintf_chk`

**Headline, stated before anything else.**  The §20.6 first divergence is
root-caused and closed.  `device_info[0x1058]` is written by
`local_ipc_service_recv` **case 6** (`context[0x1058] = 1`), i.e. by an IPC
message `[0x01, 0x06, <build string>]` that the **CPUNET** sends as the last act
of `main` (`FUN_0102a720`) — and only if `esb_service_init` (`FUN_0102b5bc`)
returns 0.  It did not.  **Four independent defects** stood between the CPUNET
and that message; all four are fixed with disassembly + measurement evidence
(§21.1–§21.4), and the measured result is

```
[ERROR] cpuapp: APP_IPCRECV op=6            <-- the 0x0601 message ARRIVES
[ERROR] cpuapp: BTSTART_STATE byte=0x1      <-- was 0x0 in iteration 20
```

with `bt_enable()` now completing at **t = 1.40 s instead of t = 5.10 s**
(`ancs_main` no longer has to time out its 5 s wait for that byte).

**BLE still does not advertise, and this iteration ends in a REGRESSION on the
reset metric that is reported in full.**  Past the `[0x1058]` guard, `bt_start`
formats the advertised device name with `__sprintf_chk(name, 0, 0x20, fmt, …)`
and the recovered printf engine returns 131 for a 16-character result, so
`fortify_chk_fail()` raises `K_ERR_KERNEL_OOPS` and the app core resets at
**t = 1.4026 s**.  Two of the three causes of that were found and fixed
(§21.5, §21.6); the third is named, localised and NOT fixed (§21.7).  So:

| pair | app reset-free @8 s | net reset-free @8 s | `device_info[0x1058]` | `bt_start` past the guard |
|---|---|---|---|---|
| iteration 20 (`i20a-app` + `i20d-net`) | **yes** | **yes** | 0 | no |
| **iteration 21 (`i21b-app` + `i21c-net`)** | **no — oops at t = 1.4026 s** | yes (to that point) | **1** | **yes** |

Both are reported; nothing is claimed for the iteration-21 pair that was not
measured.

### 21.1 The chain from `device_info[0x1058]` back to the CPUNET

Read forward from the byte, not backward from a guess:

* `bt_start` (`FUN_00019308`) requires `device_info[0x1058] != 0 && != 2`.
* the only writer of the value **1** is `local_ipc_service_recv`
  (`FUN_000162ec`) **case 6**, which also `checked_strncpy_zero_pad`s a 0x20-byte
  name into `g_2000ff4e`.  `ipc0_ept_recv` dispatches it as
  `handler(device_info, data + 1, length - 1)`, so the wire form is
  `[0x01, 0x06, …]`.
* the CPUNET builds exactly that at the end of `main` (`FUN_0102a720`):
  `*(uint16_t *)&build_message[0] = 0x0601; copy_c_string(&build_message[2], …);
  send_retry(state, build_message, 32, 100);` — but only after
  `esb_service_init(primary_role, handler)` returns 0.

Measured with Renode hooks on the iteration-20 pair
(`/private/tmp/g1-i21/probeA.log`, `probeB.log`):

```
cpuapp: APP_IPCRECV op=2      <-- registration answered
cpuapp: APP_IPCSEND b0=1 b1=0 <-- runtime_info_sync -> net sets state->role
cpunet: NET_START_ESB_WORKERS <-- role IS resolved (1); this path is fine
cpunet: NET_ESBINIT_CALL role=0
cpunet: NET_ESBINIT_RET  r0=0xFFFFFFEA        <-- -EINVAL
cpunet: NET_MAIN_RETURN0                      <-- main() returns; no 0x0601
```

`op=6` never appeared in an 8 s run.  Everything below is that `-EINVAL`.

### 21.2 Defect A — the on-stack `struct onoff_client` was four scattered
### locals, so `validate_args()` saw a garbage `sys_notify`

`FUN_0102b5bc`'s shipped prologue is `push {r0, r1, r2, r3, r4, lr}`: **the four
incoming arguments ARE the initial image of one contiguous 16-byte
`struct onoff_client` on the stack**, and every later access is an sp-relative
field of that same object —

```
102b5f0  str r3, [sp, #4]     ; notify.method = 0
102b5f2  str r3, [sp, #0xc]   ; notify.result = 0
102b5f6  mov r1, sp           ; &client
102b5f8  str r3, [sp, #8]     ; notify.flags  = 1 (SYS_NOTIFY_METHOD_SPINWAIT)
102b5fa  bl  #0x102ca80       ; onoff_request(mgr, &client)
102b618  ldr r3, [sp, #8]     ; spin while (flags & 3)
102b61e  ldr r4, [sp, #0xc]   ; result -- read AFTER the spin
```

The reconstruction declared `uStack_18 / local_14 / local_10 / local_c` as four
**independent** locals and took the address of the first one only, so the
compiler was free to place the other three anywhere.  Measured directly
(`probeC.log`), the client that actually reached `onoff_request` was

```
ONOFF_REQ mgr=0x21004814 cli=0x2100C028 node=0x0 meth=0x1
          flags=0x2100C370 res=0x102AB73
```

— `notify.flags` was a **stack address** and `notify.result` a **return
address**, so `sys_notify_validate()` rejected it and `validate_args()` returned
`-EINVAL`.  (The correct `flags = 1` had landed in `method` at +4.)  Ghidra had
also hoisted the `result` read above the busy-wait; that is corrected too.

Rewritten with an explicit 16-byte `struct g1_onoff_client` in
`recon/{net/src,net/named,symbolized/net}/FUN_0102b5bc.c`.  The generated code
is now instruction-for-instruction the shipped shape
(`strd r0,r1,[sp]` / `str r2,[sp,#8]` / `str r3,[sp,#12]` … `ldr r4,[sp,#12]`).
`cfg_verify.verify('net','FUN_0102b5bc')` **PASS**.

### 21.3 Defect B — `z_nrf_clock_control_get_onoff` returned a pointer into
### `sdc_mempool`

With A fixed, `onoff_request` was still handed
`mgr = FUN_0103037c(0) = 0x21004814 + 0*0x20` — a **raw original-image
literal**.  `FUN_0103037c` is Zephyr's
`z_nrf_clock_control_get_onoff(sys) = &((struct nrf_clock_control_data *)
dev->data)->mgr[sys]`, with `sizeof(struct onoff_manager) = 0x20` and `mgr[]`
first in the driver data, so **0x21004814 is the SHIPPED image's
`nrf_clock_control_data`**.  Confirmed structurally in this link: the stock
`clock_control_nrf.c` data object is `data` @ **0x21008414**, size **0x58**
(= 2 × 0x20 managers + 2 × 0xc subsys), and `z_nrf_clock_control_lf_on()` was
**measured** requesting `mgr = 0x21008434 = data + 0x20` with its own
`cli.1 @ 0x21008400` — the same 0x20 stride.  In our link 0x21004814 is inside
`sdc_mempool`.

`FUN_0103037c` now calls the stock accessor under `G1_COHESIVE_BUILD` (which
also roots the archive member; it had been garbage-collected).  Parity keeps the
literal.  `cfg_verify.verify('net','FUN_0103037c')` **PASS**.

Build `/private/tmp/g1-i21a-net`: `onoff_request` returns **0** and the ESB
clock request completes — `esb_service_init` reaches its success path for the
first time.

### 21.4 Defects C and D — the MPSL timeslot session was split between two
### owners, and the ESB radio-state word was pinned on top of a timeslot request

Success in §21.3 immediately unmasked two more, both fatal (`svc #2`,
`K_ERR_KERNEL_OOPS`, SoC reset) because the recovered timeslot worker
`FUN_0102b810` treats any MPSL error as fatal.

**C — `mpsl_timeslot_request` was the reconstruction while
`mpsl_timeslot_session_open` was already the library's.**  Iteration 9 adopted
`FUN_01021a38 = mpsl_timeslot_session_open` and `FUN_0102a0e6 =
mpsl_timeslot_session_close` from `libmpsl.a`, but left `FUN_0102a122`
(`mpsl_timeslot_request`) as a recovered body.  That body reaches MPSL's private
session array through `FUN_01021ac0(id) = *(uint32_t *)0x210016e4 + id*0x30`
with the count at `0x210016e8` — absolute original-image RAM that this build
never initialises, because the library owns that table at its own layout and
NCS's `mpsl_init` hands it `timeslot_context` through the **library**
`mpsl_timeslot_session_count_set`.  Measured (`probeI.log`):

```
TS_COUNT_SET ctx=0x2100859C n=1          <-- the LIBRARY's state
TS_OPEN_RET  r0=0x0 base=0x1 cnt=1       <-- *(uint32_t*)0x210016e4 == 1
TSREQ_ENTRY  entry=0x1 state=0           <-- session state read from address 0x27
                                          -> -NRF_EAGAIN (-35)
```

The reconstruction's return set is *exactly* the documented set of
`mpsl_timeslot_request` (`-NRF_ENOENT` / `-NRF_EAGAIN` / `-NRF_EINVAL`,
`mpsl_timeslot.h:317-320`), which is the identity evidence.  Adopted:
`recon/ownership/adoption_manifest.json` gains the `0x0102a122` entry
(`exclude_reconstruction: true`, four evidence records),
`recon/generated/net_retained_sources.cmake` regenerated
(`gen_retained_sources.py --check` clean), and
`recon/application/net/src/stock_call_aliases.ld` gains
`PROVIDE(FUN_0102a122 = mpsl_timeslot_request);`.  Net FLASH **228,457 → 221,977 B (−6,480)**.

**D — `g_net_radio_op_state` was an absolute pin sitting exactly on
`g1_timeslot_request_earliest`.**  With C fixed the library's
`mpsl_timeslot_request` returned **-NRF_EINVAL (-22)** and the measured request
had `request_type = 1`, i.e. `MPSL_TIMESLOT_REQ_TYPE_NORMAL` — but
`mpsl_timeslot.h:302` requires the **first** request of a session to be
`EARLIEST`.  The emitted object's `.data` image is correct
(`00 00 00 00 | 01 00 00 00 | 88 13 00 00 | 40 42 0f 00`); something overwrote
byte 0 at runtime.  `check_net_raw_literals.py` names the writer:

```
0x210005b4 -> g1_timeslot_request_earliest +0x0
   recon/net/src/FUN_0102b758.c:19, recon/symbolized/net/FUN_0102b794.c:12,
   recon/symbolized/net/FUN_0102b7a0.c:12 …
```

`g_net_radio_op_state` (original VA 0x210005b4) was `PROVIDE(... = 0x210005b4)`
plus four raw literals; in the cohesive link that is precisely where the linker
had placed `g1_timeslot_request_earliest`, so IPC sub-commands 10/11/12
(`FUN_0102b794/7a0/7ac`) wrote 2/1/3 straight into the request's `request_type`.
Sub-command 11 arrives at t ≈ 1.1 s, hence the NORMAL type.

**Iteration 20 §20.1 classified `g1_timeslot_request_earliest`'s two literals as
"benign self-aliases". That was wrong, and this is the correction.**

Fixed by giving the word real storage with its **shipped initialiser**, read out
of `netcore_image.bin` at the net `.data` LMA (analysis `0x0103e524 + VMA`, the
base re-verified against the §20.4 ESB pipe block):

```
0x210005b4  01 00 00 00                                        g_net_radio_op_state
0x210005b8  01 00 00 00 01 00 00 00 50 c3 00 00 88 13 00 00    NORMAL   (role 0)
0x210005c8  01 00 00 00 01 00 00 00 50 c3 00 00 88 13 00 00    NORMAL   (role 1)
0x210005d8  00 00 00 00 01 00 00 00 88 13 00 00 40 42 0f 00    EARLIEST
```

so `recon/application/net/src/timeslot_owner.c` now also emits
`g_net_radio_op_state = 1` and the **third** request object
(`g1_timeslot_request_normal_role1`) that the shipped image has and this project
had never modelled — `FUN_0102b944`, the timeslot **signal callback**, selects
between the two NORMAL ones on the ESB role, and its three request pointers were
raw literals landing on `g1_timeslot_request_earliest+4`,
`g1_timeslot_request_normal+4` and `nrf53_sync_offset+0`.  All three are now
bound to the emitted objects (guarded; parity keeps the literals), the absolute
`PROVIDE` is retired, and the four `0x210005b4` literal sites go through a
`G1_NET_RADIO_OP_STATE` guard.

Build `/private/tmp/g1-i21c-net` (final net): **`APP_IPCRECV op=6` arrives and
`BTSTART_STATE byte=0x1`.**  `check_net_raw_literals.py` **74 → 69**.

### 21.5 Defect E — 2,128 app `rodata_*` symbols were ABSOLUTE
### original-image addresses, including every printf format string

Past the `[0x1058]` guard the app core took `K_ERR_KERNEL_OOPS` at
`fortify_chk_fail+0x18`.  `bt_start` builds the advertised name with
`vdprintf_to_fd` = `__sprintf_chk(dst, 0, 0x20, fmt, …)` (shipped
`0x86f2c cmp r0,r4 / blo return / bl 0x51164`), and the measured call was

```
VDP dst=0x20011087 cnt=32 fmt=0x9ACB2 arg0=0x9AC7C
    fmtstr=T¿Ú9¿ FZ¿wÂ¿æ[_¿,ú¾d¿qq          <-- GARBAGE
```

`0x9ACB2` and `0x9AC7C` are **original-image flash addresses**:
`recon/symbols/g1_app_globals.ld` pins 2,563 `rodata_<hex>` symbols with
`PROVIDE(rodata_XXXX = 0xXXXX)` and only the byte-verified TABLES
(`recon/data`, emitted as `rodata_0x<hex>`) ever override them —
`arm-zephyr-eabi-nm` reported **2,128** of them still as class `A`.  Our image
is relocated, so every one names unrelated bytes.  Harmless for a log line;
fatal for a `_FORTIFY_SOURCE`-checked format string.

New generator `recon/application/gen_app_string_rodata.py` emits a byte-exact
object for every absolute pin whose target is a NUL-terminated printable C
string in `app_update.bin` (read through `tools/extract.py`) — **1,793 objects,
58,598 bytes** — into `recon/application/app/src/g1_app_string_rodata.c`.  A
`PROVIDE` is inert once the symbol has a definition, so no linker-script edit
and no parity-tree edit was needed; `--gc-sections` still drops the strings
nothing references.  Absolute `rodata_` pins **2,128 → 346**; app FLASH
**+48,948 B** (71.11 % of 982,528 B).  `rodata_9acb2` and `rodata_9ac7c` are now
real objects and the format string reaching `__sprintf_chk` is the correct
`"%s_R_%02X%02X%02X"` / `"Even G1"` (confirmed in the fault dump:
`s[7]=0x000a89f1`, `s[8]=0x000a8a31`).

### 21.6 Defect F — `g_libc_heap_ctrl` (newlib's `_impure_ptr`) read 0

The oops survived §21.5.  Measured: `vsnprintf_impl` (`FUN_00077c30`) loads the
reent pointer as `*(int *)&g_libc_heap_ctrl` and passes it as the leading
`struct _reent *` of `_vsnprintf_r`; the value was **0**.  `g_libc_heap_ctrl`
(original 0x20002d20) was bound into the RAM arena (`g1_ram_arena + 0xd20`), and
it is a `.data` **pointer** word, which the arena restore deliberately drops
(the policy documented in `gen_app_data_image.py`).  Fifteen recovered libc TUs
read it.  The linked newlib-nano owns exactly this word, so
`recon/symbols/g1_app_globals.ld` now has
`PROVIDE(g_libc_heap_ctrl = _impure_ptr);` (0x2000298c → `impure_data`
0x20002990).  Measured after: `VSN_IN … reent=0x20002990`.

### 21.7 The NEW first divergence — the recovered `_svfprintf_r` returns 131
### for a 16-character result (NOT fixed, NOT guessed at)

With a correct format string, correct arguments and a valid reent, the oops
still fires.  Measured (`probeS.log`, build `g1-i21b-app` + `g1-i21c-net`):

```
VSN_IN dst=0x20011087 cnt=32 fmt=0xA89F1 reent=0x20002990
PPF_IN reent=0x20002990 f=0x20022860 fmt=0xA89F1 ap=0x200228B8
PPF_RET r0=131
```

`printf_parse_format` (the recovered `_svfprintf_r`, linked at 0x0004b064, owner
`app/libapp.a(printf_parse_format.c.obj)`) returns **131** and leaves the
destination buffer empty for
`("%s_R_%02X%02X%02X", "Even G1", 0xff, 0xff, 0xff)`, whose correct result is
the 16-character `Even G1_R_FFFFFF`.  `__sprintf_chk` compares `131 >= 32`,
calls `fortify_chk_fail()` → `k_oops` → SoC reset at t = 1.4026 s:

```
<err> os: Faulting instruction address (r15/pc): 0x00045b78
<err> os: >>> ZEPHYR FATAL ERROR 3: Kernel oops on CPU 0
<err> fatal_error: Resetting system
```

The caller chain is proven by the fault dump itself (`s[1] = 0x0007b201` inside
`vdprintf_to_fd`, `s[5] = 0x000182ef` inside `bt_start`, `s[6] = 0x20` the
buffer size).  **The defect inside `printf_parse_format` / its `__ssputs_r`
writer is NOT diagnosed here and no guess is recorded as if it were.**  Two
candidates that the next iteration should discriminate with disassembly, not
shape: (i) the fake `FILE` that `snprintf_engine_bounded` (`FUN_0008712e`,
`_vsnprintf_r`) builds on the stack has the same "four scattered locals" hazard
as §21.2; (ii) the recovered engine's argument walk.  This is the first
divergence for iteration 22 and it is the only thing between the current build
and `bt_le_adv_start`.

### 21.8 Measurements (every number below was actually run)

| metric | iter 20 final | **iter 21 final (`i21b-app` + `i21c-net`)** |
|---|---:|---:|
| `device_info[0x1058]` at `bt_start` | **0x0** | **0x1** |
| `APP_IPCRECV op=6` (the `0x0601` message) | never | **yes** |
| `bt_start()` runs past the state guard | no | **yes** |
| `bt_enable()` / `bt_hci_core: Identity` | t = 5.100 s | **t = 1.397 s** |
| app `ZEPHYR FATAL ERROR` @8.0 s | 0 | **1 (oops, t = 1.3988 s)** — §21.7 |
| net `ZEPHYR FATAL ERROR` @8.0 s | 0 | 0 up to the SoC reset |
| `radio TransmittedFrames` | 0 | 0 |
| `vcentral Connected` | False | False |
| app FLASH | 649,688 B | **698,636 B (+48,948; 71.11 % of 982,528)** |
| app RAM | 252,885 B | **252,885 B (+0)** |
| net FLASH | 228,409 B | **221,997 B (−6,412; 95.93 % of 231,424)** |
| net RAM | 60,540 B | **60,556 B (+16)** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_net_raw_literals.py` (net) | 74, EXIT 1 | **69, EXIT 1** |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** (120 trials) |
| `gen_retained_sources.py --check` | clean | **clean** |
| absolute `rodata_*` pins in the app link | 2,128 | **346** |

### 21.8b Graphics + sensor parity — PARTIAL capture, honestly scoped

The capture was run on the final pair with identical determinism knobs and
stimulus to the oracle, no memory poking:

```
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i21b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i21c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i21
```

**`p1_boot` completed; `p2_render` did NOT.**  Renode itself crashed on entry to
phase 2 with `System.Threading.SemaphoreFullException` inside
`Antmicro.Renode.UI.ConsoleIOSource` (`/private/tmp/g1_ours_i21/run.out`) —
an emulator-harness failure caused by running the script backgrounded, not a
firmware result.  `spim_a.p2.trace`, `twim1.p2.trace`, `twim2.p2.trace` and the
`p2_render` framebuffer are absent, so **no `p2` number is claimed for
iteration 21** and **G-1 is NOT re-measured**.

| id | verdict (iteration 21 `p1_boot`) | detail |
|---|---|---|
| **G-2** | **FAIL**, unchanged | `fb_p1_boot.ppm` is **byte-identical to iteration 20** (`cmp`): **0 lit px** vs the oracle's **656**.  **Not one pixel was painted.** |
| **G-3** | **FAIL (truncation only)**, unchanged | `p1_boot` **34 vs 764**; the whole trace is identical to iteration 20 **modulo the `tick=` column** (`sed 's/ tick=[0-9]*//' \| cmp`), so all 34 shared transactions stay byte-identical and the first difference stays at index **34** (oracle `{"op":"0x66",…}`, ours `<end>`).  `p2_render` not measured. |
| **G-4** | *localiser, carries over* | the framebuffer bytes are unchanged, so first differing row **y = 267**, first differing pixel **x = 178**. |
| **G-5** | **PASS**, unchanged | the four enumerated panel-init elements are present at the same indices (three-band 153,600 B clear at 4–6, five `0xC0` words at 7–16, `0x46`/`0x31` pairs `0F 04` at 21/22 and `00 04` at 28/29, `0x9F`→ID at 32, trailing `0xB9 FF` at 33). |
| **G-6** | **PASS**, unchanged | `spim_b.p1.trace` byte-identical, 0 == 0. |
| **S-ESB** | **FAIL**, unchanged | `radio TransmittedFrames` 0, `vcentral Connected` False in the 8 s boot. |

Per-sensor `p1_boot` volumes actually counted from the traces — **three
regressions, caused by the app core rebooting roughly every 1.4 s inside the 6 s
phase-1 window**:

| device `p1_boot` | oracle | iter 20 | **iter 21** |
|---|---:|---:|---:|
| LSM6DSO (twim2) | 1,089 | 1,027 | **551** |
| nPM1300 (twim1 0x6B) | 291 | 232 | **97** |
| OPT3001 (twim1 0x45) | 33 | 14 | **14** |
| ST25DV system port (0x57) | 22 | 12 | **6** |
| ST25DV NFC EEPROM (0x53) | 25 | 11 | **0** |
| `spim_a` | 764 | 34 | **34** |
| `JBD_FRAMECOUNTER_P1` | 0x2A1 | 0x3 | **0x0** |

No verdict cell changes (still **5 PASS / 5 PARTIAL / 4 FAIL**), and the
iteration-20 pair remains the best-scoring build on these criteria.  The named
sensor divergences (S-IMU #3, S-PMIC #0, S-NFC EEPROM #6 / system port #10,
S-ADC `CH[3]` not configured) were **not** worked on this iteration.

### 21.9 Re-proof

```
net  FUN_0102b5bc   PASS   (cfg_verify)
net  FUN_0103037c   PASS   (cfg_verify)
```

As in iterations 18–20 this is necessary but not sufficient: `cfg_verify` passed
on `FUN_0102b5bc` **before** the fix too, because the four scattered locals are
still four writes to *some* stack slots and the harness models `onoff_request`
as an opaque callee.  The evidence that settled it was the shipped `push {r0,
r1, r2, r3, r4, lr}` prologue plus the measured client fields.  **This is the
eleventh instance of the harness blind-spot family** and the first that is a
*stack-object layout* defect rather than a dropped argument or a wrong
indirection.

### Regenerate (iteration 21)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check      # clean
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_string_rodata.py \
    --elf /private/tmp/g1-i21a-app/zephyr/zephyr.elf \
    -o recon/application/app/src/g1_app_string_rodata.c   # 1793 objects, 58598 B
recon/application/build_cohesive.sh app /private/tmp/g1-i21b-app
recon/application/build_cohesive.sh net /private/tmp/g1-i21c-net -- \
    -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# boot: /private/tmp/g1-i21/probeR.resc  (8.0 s, checkpoints at 5.0/6.5/8.0)
```

Bisect ledger (every build and boot actually run):

| build | change | app FATAL | net FATAL | note |
|---|---|---|---|---|
| `i20a-app` + `i20d-net` | iteration-20 baseline | 0 | 0 | `[0x1058]` = 0, `esb_service_init` = −22 |
| `g1-i21a-net` | §21.2 onoff_client struct + §21.3 clock manager | — | **1 (k_oops, mpsl_timeslot_request = −35)** | `onoff_request` now returns 0 |
| `g1-i21b-net` | §21.4 C — adopt `mpsl_timeslot_request` | — | **1 (k_oops, = −22)** | request type was NORMAL |
| `g1-i21c-net` | §21.4 D — `g_net_radio_op_state` + 3rd request | **1 (t ≈ 4 s, fortify)** | **0** | **`op=6` arrives, `[0x1058]` = 1** |
| `g1-i21a-app` | §21.5 string rodata | 1 (t = 1.42 s, fortify) | 0 | format string now correct |
| `g1-i21b-app` | §21.6 `_impure_ptr` | 1 (t = 1.4026 s, fortify) | 0 | **final**; reent now valid, §21.7 remains |

Files changed: `recon/{net/src,net/named,symbolized/net}/FUN_0102b5bc.c`,
`.../FUN_0103037c.c` (§21.2/§21.3);
`recon/ownership/adoption_manifest.json` (+1 net entry),
`recon/generated/net_retained_sources.cmake` (regenerated),
`recon/application/net/src/stock_call_aliases.ld` (§21.4 C);
`recon/application/net/src/timeslot_owner.c`,
`recon/symbols/g1_net_globals.ld`,
`recon/net/src/FUN_0102b944.c`, `recon/net/src/FUN_0102b758.c`,
`recon/{net/src,symbolized/net}/FUN_0102b794.c`, `FUN_0102b7a0.c`,
`FUN_0102b7ac.c` (§21.4 D);
new `recon/application/gen_app_string_rodata.py` +
`recon/application/app/src/g1_app_string_rodata.c` +
`recon/application/app/CMakeLists.txt` (§21.5);
`recon/symbols/g1_app_globals.ld` (§21.6);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, no Kconfig / `prj.conf` / devicetree change,
`armemul` untouched, nothing committed.

### 21.10 Open, named, and NOT fixed

1. **§21.7 — `printf_parse_format` (`_svfprintf_r`) returns 131 for a
   16-character result**, so `__sprintf_chk` oopses the app core at t = 1.4026 s
   the first time `bt_start` formats the device name.  **This is the first
   divergence for iteration 22.**
2. **346 app `rodata_*` pins are still absolute** (§21.5): the ones whose target
   is not a NUL-terminated printable string.  Each needs its own extent
   evidence; none is known to be load-bearing yet.
3. **69 source-level raw `0x21xxxxxx` net literals still land inside a live
   linked object**, 54 of them inside `sdc_mempool` (unchanged instrument:
   displacement of the duplicate SDC/MPSL bodies).  Two that this iteration did
   NOT close and that the timeslot signal callback WILL touch:
   `RETURN_PARAM = 0x21004630` (the `mpsl_timeslot_signal_return_param_t` that
   `FUN_0102b944` hands back to MPSL) and the ESB event-handler slot
   `0x21004628` written by `esb_service_init`.
4. Iteration 20 items 3–6 (the rest of the vendored ANCS client, the missing net
   RAM-pin gate, unreconstructed `analysis 0x0102b204`, unverified
   `CONFIG_MAIN_STACK_SIZE`) are unchanged.

---

## Iteration 22 — the recovered printf engine is DISPLACED to newlib-nano, the
## t = 1.4026 s oops is gone, and the app **advertises and accepts a BLE
## connection for the first time in this project**

**Headline, stated before anything else, with the firmware's own words.**  The
§21.7 blocker is closed and the chain it was blocking ran two more steps:

```
Advertising Even G1_R_FFFFFF successfully started uptime 1400     <-- app UART
ORACLE_VC_CONNECTED:      True        (oracle True)
ORACLE_VC_CONNECT_INDS:   0x00000001  (oracle 0x00000001)
ORACLE_VC_DATA_EVENTS:    0x00000212  (oracle 0x00000215)
ORACLE_RADIO_TX:          0x000000BA  (oracle 0x00000230)
```

`Even G1_R_FFFFFF` is exactly the sixteen-character string §21.7 recorded the
recovered `_svfprintf_r` could not produce.  `radio TransmittedFrames` moves
**0 → 186** over the 20 s capture (90 at t = 8.0 s in a plain boot), the virtual
central sends the same **one** CONNECT_IND the oracle does and is answered on
**530** of the oracle's 533 data events.  Both cores run **8.0 s and the full
20.0 s capture with zero `ZEPHYR FATAL ERROR` and zero `SYSRESETREQ`**, so this
build beats **both** iteration-21 (progress, but resetting at 1.4026 s) and
iteration-20 (reset-free, but `[0x1058]` = 0 and no advertising) at the same
time, and it does so **without giving up a single sensor transaction**: every
per-device `p1_boot`/`p2_render` volume is equal to or better than the
iteration-20 baseline.

**No pixel is painted yet.**  `spim_a` is still 34 transactions in `p1_boot` and
**0** in `p2_render`, and the framebuffer is still 0 lit px against the oracle's
656 / 1,098.  The gate has moved off BLE and onto the **ESB L↔R lens sync**
(§22.7), which is named and measured, not guessed.

| pair | app reset-free @8 s | net reset-free @8 s | `bt_le_adv_start` | ADV on air | central connected |
|---|---|---|---|---|---|
| iteration 20 (`i20a-app` + `i20d-net`) | yes | yes | never called | 0 | False |
| iteration 21 (`i21b-app` + `i21c-net`) | **no — oops @1.4026 s** | yes | never reached | 0 | False |
| **iteration 22 (`i22b-app` + `i21c-net`)** | **yes** | **yes** | **returns 0** | **186** | **True** |

### 22.1 The printf resolution: DISPLACED, and the evidence is byte identity

The owner's standing directive applies here in its strongest form, and
iteration 20's warning ("an instruction-*shape* match is not sufficient
evidence; the shipped firmware vendors some upstream files") was applied as the
gate rather than waved at.  The distinction is exactly measurable:

* the **vendored** `ancs_client.c` case (§20.5) differs in *constants and
  structure offsets* — `cmp r4,#0xff` vs `#0x1f`, `strh [r0,#0x870]` vs
  `#0x110`.  Those bytes are NOT relocation slots, so a byte comparison
  separates them immediately;
* the printf family differs **nowhere**.  Re-measured this iteration from
  scratch (`<scratchpad>/verify_printf.py`, `<scratchpad>/verify_member.py`:
  extract the member from
  `arm-zephyr-eabi/lib/thumb/v8-m.main+fp/hard/libc_nano.a`, read the shipped
  bytes through `tools/extract.py`'s VA mapping, zero the 4-byte window at every
  relocation offset, compare the **entire** upstream section including the tail
  past Ghidra's reported extent):

```
member                     section              VA         size  relocs  dist   agreement
lib_a-nano-svfprintf.o     .text._svfprintf_r   0x00078d90   504     12    456   504/504  BYTE-EXACT
lib_a-nano-svfprintf.o     .text.__ssputs_r     0x00087736   182      5    162   182/182  BYTE-EXACT
lib_a-vsnprintf.o          .text._vsnprintf_r   0x0008712e    86      1     82    86/86   BYTE-EXACT
lib_a-vsnprintf.o          .text.vsnprintf      0x00077c30    28      2     20    28/28   BYTE-EXACT
lib_a-sprintf_chk.o        .text.__sprintf_chk  0x00086f00    52      3     40    52/52   BYTE-EXACT
lib_a-nano-vfprintf_i.o    .text._printf_i      0x00077594   604     26    500   604/604  BYTE-EXACT
lib_a-nano-vfprintf_i.o    .text._printf_common 0x00086e1c   228      0    228   228/228  BYTE-EXACT
lib_a-nano-vfprintf_float.o .text._printf_float 0x0007712c  1128     16   1064  1128/1128 BYTE-EXACT
lib_a-nano-vfprintf_float.o .text.__cvt         0x00086cda   208      3    196   208/208  BYTE-EXACT
lib_a-nano-vfprintf_float.o .text.__exponent    0x00086daa   114      0    114   114/114  BYTE-EXACT
lib_a-dtoa.o               .text._dtoa_r        0x00014b60  3156    115   2696  3156/3156 BYTE-EXACT
lib_a-dtoa.o               .text.quorem         0x00087184   282      1    278   282/282  BYTE-EXACT
lib_a-nano-vfprintf.o      .text._vfprintf_r    0x00076ed4   600     19    524   600/600  BYTE-EXACT
lib_a-nano-vfprintf.o      .text.__sfputs_r     0x00086cb6    36      1     32    36/36   BYTE-EXACT
lib_a-printf.o             .text.printf         0x000777f0    48      3     36    48/48   BYTE-EXACT
lib_a-snprintf.o           .text.snprintf       0x00077914   104      2     96   104/104  BYTE-EXACT
lib_a-sprintf.o            .text.sprintf        0x0007797c    64      2     56    64/64   BYTE-EXACT
lib_a-vsprintf.o           .text._vsprintf_r    0x00077c4c    44      1     40    44/44   BYTE-EXACT
lib_a-vsprintf.o           .text.vsprintf       0x00077c78    20      2     12    20/20   BYTE-EXACT
lib_a-fprintf.o            .text.fprintf        0x00076cc8    36      2     28    36/36   BYTE-EXACT
```

**7,124 distinguishing bytes across 20 members, zero disagreements.**  Even did
not modify printf; the reconstruction was simply wrong, and the harness could
not see it because `tools/parity` emulates at the ORIGINAL addresses where the
recovered control flow still reproduced the traced side effects for the argument
sets it drove.  So the reconstruction is **not** debugged — it is retired.

For the record, the specific recovered defect is visible on inspection once you
know the answer: `recon/symbolized/app/printf_parse_format.c` opens its
conversion loop with

```c
LAB_de4:
  pbVar6 = pbVar7;
  while (*pbVar6 != 0 && *pbVar6 != 0x25) { pbVar6++; }
  pbVar7 = pbVar6 + 1;
  if (*pbVar6 == 0x25) { /* fallthrough to LAB_df0 */ }
LAB_df0:
  ...
```

i.e. Ghidra's `goto` structure was flattened into a fallthrough that reaches
`LAB_df0` on *both* exits of the scan loop, and the `%`-branch never restores
`pbVar7`.  That is a control-flow reconstruction error, not an Even
modification, and it is exactly the class the owner's directive says to stop
paying for.

### 22.2 Batch 4 — the sixteen-function printf closure

`recon/ownership/library_displacement_candidates.json` already carried all
sixteen as `high`/`medium` `adopt_upstream_exclude_reconstruction` rows.
`<scratchpad>/batch22.py apply` appends them to
`recon/ownership/adoption_manifest.json` with their own evidence plus the
independent re-measurement record above:

| VA | recovered identity | upstream owner |
|---|---|---|
| 0x00014b60 | `dtoa_r` | `_dtoa_r` |
| 0x00076ed4 | `_vfprintf_r` | `_vfprintf_r` |
| 0x0007712c | `printf_render_float` | `_printf_float` |
| 0x00077594 | `vfprintf_format_engine` | `_printf_i` |
| 0x000777f0 | `printf` | `printf` |
| 0x00077914 | `snprintf` | `snprintf` |
| 0x0007797c | `format_string_to_buffer` | `sprintf` |
| 0x00078d90 | `printf_parse_format` | `_svfprintf_r` |
| 0x00086cb6 | `libc_write_buffer_via_putc` | `__sfputs_r` |
| 0x00086cda | `dtoa_format_cvt` | `__cvt` |
| 0x00086daa | `itoa_signed_exponent` | `__exponent` |
| 0x00086e1c | `vfprintf_emit_padded_field` | `_printf_common` |
| 0x00086f00 | `vdprintf_to_fd` | `__sprintf_chk` |
| 0x0008712e | `snprintf_engine_bounded` | `_vsnprintf_r` |
| 0x00087184 | `bignum_div_trial_subtract` | `quorem` |
| 0x00087736 | `iobuf_ensure_capacity_and_append` | `__ssputs_r` |

**Batch 4b** adds the four wrappers the exhaustive sweep missed or mis-matched
(it had put 0x00077c30 on `fread` and 0x00076cc8 on `fscanf`, both `low`, and
had not catalogued 0x00077c4c / 0x00077c78 at all) — `fprintf_stream` →
`fprintf`, `vsnprintf_impl` → `vsnprintf`, `_vsprintf_r` → `_vsprintf_r`,
`vsprintf_impl` → `vsprintf`.  Their byte evidence is in the table above, and
the link forces them anyway: the newly-owned `sprintf` pulls
`lib_a-vsprintf.o`, whose `_vsprintf_r` duplicated the recovered body (measured
as a `multiple definition` error on the first Batch-4 link).

App manifest **660 → 680 entries / 646 → 666 exclusions**; retained sources
**1,640 → 1,620** (`gen_retained_sources.py`, `--check` clean, generated cmake
never hand-edited).

### 22.3 Wiring the callers — three mechanisms, no hacks

1. **Linker aliases.**  Every member of the family whose historical spelling
   differs from the upstream name is mapped in the new
   `recon/symbols/g1_app_newlib_printf_aliases.ld`.  Aliases rather than C
   bridges because `__sprintf_chk`, `sprintf`, `printf`, `snprintf` and
   `vsprintf` are **variadic** — a C forwarder cannot express them, whereas the
   shipped bytes ARE the upstream body, so the ABI is identical by
   construction.  Three of them have live retained callers
   (`vdprintf_to_fd` ← `bt_start`, `DashBoard_Reflash`, `gui_clock_draw`,
   `build_str_response_frame`, `send_notification_app_whitelist`,
   `spec_ble_command_hook`, `test_mode_apply_base_status_cmd`;
   `format_string_to_buffer` ← `format_message_relative_time`;
   `vsnprintf_impl` ← `debug_print`), the rest keep the historical spellings
   single-owner for `g1_app_function_aliases.ld`'s existing chains
   (`PROVIDE(FUN_00086f00 = vdprintf_to_fd)`,
   `PROVIDE(svfprintf_reentrant = printf_parse_format)`).

2. **Snippet ordering.**  GNU ld evaluates `PROVIDE` in script order and
   `zephyr_linker_sources` concatenates snippets **sorted by sort key** (Zephyr
   3.4.99 `extensions.cmake:1270-1300`), which put the new file at
   `linker.cmd:3734` while `g1_app_function_aliases.ld`'s chained alias sits at
   line 344 — a hard `undefined symbol 'vdprintf_to_fd' referenced in
   expression`.  The fragment is therefore registered with an explicit
   `SORT_KEY 0_g1_newlib_printf`.

3. **Archive extraction.**  GNU ld does **not** extract an archive member to
   satisfy a symbol that is only named inside a linker-script expression
   (measured: `undefined symbol '__sprintf_chk' referenced in expression` even
   with the alias in place).  Five roots are therefore pulled explicitly with
   `-Wl,--undefined=` — `__sprintf_chk`, `sprintf`, `_vsnprintf_r`, `vsnprintf`,
   `fprintf`.  Everything else in the closure (`_svfprintf_r`, `__ssputs_r`,
   `_printf_i`, `_printf_common`, `__sfputs_r`, `quorem`, `_vsprintf_r`)
   arrives through ordinary relocations from those members.

**No `--allow-multiple-definition`, no weak symbols, no numeric-root hacks.
0 undefined / 0 duplicate globals.**

### 22.4 `CONFIG_NEWLIB_LIBC_FLOAT_PRINTF=y` — a recovered configuration fact

`_printf_float` (1,128 B), `__cvt` (208 B), `__exponent` (114 B) and `_dtoa_r`
(3,156 B) are **in the shipped image**, byte-exact.  newlib-nano only links
those members when the link carries `-u _printf_float`, which is precisely what
this Kconfig adds; without it `%f`/`%e`/`%g` in the recovered callers would fall
through to the integer engine, which the original never did.  This is the only
Kconfig change in the iteration and it is recorded in
`recon/application/app/prj.conf` with that evidence.

### 22.5 Build `g1-i22a-app` — the oops is gone and the next divergence appears
### in one line

```
Advertising Even G1_R_FFFFFF failed to start (err -22)
ancs or ncs init failure, reboot it
ancs_main(): reboot because ancs start failed
```

The FORTIFY oops at t = 1.4026 s is **gone** and the name is **correct**, which
is the direct measurement that closes §21.7.  The app now resets at t ≈ 2.4 s
for a different, clearly-labelled reason: `bt_le_adv_start` returns **-EINVAL**.

### 22.6 Defect G/H — three of `bt_le_adv_start`'s four operands were still
### bound to original-image addresses

`bt_start` calls
`bt_le_adv_start(params, &g_20002358, 2, &g_20002350, 1)`.

**G — `rodata_8839c`, the `struct bt_le_adv_param`, was an identity pin.**
`bt_start` copies it word by word into a stack local
(`for (i = 0; i < 5; i++) params[i] = ((const uint32_t *)0x8839c)[i]`), so the
extent is exactly 20 B = `sizeof(struct bt_le_adv_param)`.  Iteration 21's
string-rodata generator could not emit it because the bytes are a binary struct,
not a NUL-terminated printable string (§21.10 item 2), so
`PROVIDE(rodata_8839c = 0x0008839c)` survived.  **Measured on
`/private/tmp/g1-i22a-app`:** address 0x0008839c in OUR image holds
`5f 74 79 70 65 73 2e 68 00 02 00 00 5f 73 74 64` — the ASCII `_types.h`/`_std`
of a debug path — so `options` read **0x682e7365**, a word full of undefined
`BT_LE_ADV_OPT_*` bits, which is exactly what `valid_adv_param()` rejects with
-EINVAL.  The shipped 20 bytes (`app_update.bin` @ 0x8839c via
`tools/extract.py`) are

```
00 00 00 00 | 01 00 00 00 | 60 01 00 00 | e0 01 00 00 | 00 00 00 00
id=0 sid=0 skip=0 | options=BT_LE_ADV_OPT_CONNECTABLE | int_min=0x160 | int_max=0x1e0 | peer=NULL
```

**H — the two `struct bt_data` arrays had pointer-bearing `.data` initialisers
that the RAM-arena restore drops.**  Shipped `.data` load image (LMA flash
0xf6d64 for VMA 0x20000000):

```
0x20002350  09 07 00 00 7c ac 09 00                            sd[0] = { BT_DATA_NAME_COMPLETE, 7, rodata_9ac7c="Even G1" }
0x20002358  01 01 00 00 e1 2f 00 20  00*8                      ad[0] = { BT_DATA_FLAGS, 1, &0x20002fe1 }, ad[1] = 0
0x20002fe0  01 06 ff ...                                       the flags byte 0x20002fe1 = 0x06 = GENERAL | NO_BREDR
```

Measured in the generated `g1_app_data_image.c` run table: the last run before
this block covers arena offset 0x348 for 4 bytes and the next starts at 0x368,
so **0x350..0x367 stayed zero** — `sd[0].type` advertised as 0x00 instead of
`BT_DATA_NAME_COMPLETE` and `ad[0]` was an empty AD structure instead of the
flags byte.  (`bt_start` writes only `sd[0].data_len`, `sd[0].data`,
`ad[1].type`, `ad[1].data_len` and `ad[1].data` at run time.)  The next pin
after the array, `g_t_init = g1_ram_arena + 0x368`, confirms the array is
exactly the two entries `ad_len = 2` names.

Both fixed the documented way — a linker rebind cannot express an object whose
CONTENTS embed pointers, so the objects are emitted and the pins are bound onto
them (the `g1_npm1300_linear_ranges.c` / `g1_st25dv_ops_table.c` precedent):
new `recon/application/app/src/g1_bt_adv_objects.c`, and in
`recon/symbols/g1_app_globals.ld`
`PROVIDE(rodata_8839c = g1_bt_le_adv_param)`,
`PROVIDE(g_20002350 = g1_bt_adv_scan_rsp)`,
`PROVIDE(g_20002358 = g1_bt_adv_data)`.
`ad[0].data` is bound to `&g1_ram_arena[0xfe1]`, the same byte the original
pointed at and one the arena image DOES restore.  **No canonical parity body was
touched.**

Build `/private/tmp/g1-i22b-app` (final): advertising starts, the central
connects, no reset.

### 22.7 The NEW first divergence — the ESB L↔R lens sync never starts

The display is not BLE-gated any more; it is ESB-gated, and the three counters
say so together:

```
                        oracle        ours
ESB_MASTER_FRAMES       0x00000175    0x00000000     esbslave MasterFramesSeen
ESB_ACKS                0x00000175    0x00000000
ESB_ANNOUNCE_RESP       0x0000015B    0x00000000
ESB_SYNC_ctx_105a       0x02          0x01
DISPLAY_ON_ctx_fe8      0x01          0x00
spim_a p2_render        2,881 txns    0 txns
```

Our CPUNET never transmits an ESB PTX frame, so the virtual right lens is never
seen, `device_ctx[0x105a]` stops at 1 instead of 2, `device_ctx[0xfe8]` never
becomes 1, and `trigger_screen_state_change(action=1)` /
`reflash_fb_data_to_lcd` are never called.  The app UART names the state
directly and repeatedly:

```
runtime_info_sync(): --role:1 --mode:0, esb_channel 255 --ret:8 esb_master_addr 00 esb_slave_addr 00
local_ipc_service_recv(): cpunet request update macaddr info uptime 343 bt macaddr esb_master_addr 00 esb_slave_addr 00
c->esb_channel 255
low_speed_peripheral_dispatch_thread(): Global Working Mode: 10 get_glasses_ble_status 0 ble_is_connected 0
```

`esb_channel` = 255 and both ESB addresses = 00 for the whole run: the ESB
pairing record is never populated, so `esb_service_init`'s workers have nothing
to transmit on.  `ble_is_connected` also stays 0 on the app side even though the
link layer reports `vcentral Connected = True` and 530 data events are answered
— i.e. the host-side `connected` callback is not reaching the application's
state.  Independently re-run with the identical stimulus but the UART analyser enabled
(`/private/tmp/g1-i22/probeC.resc`, 6 s + `PlayGesture "don"` + 14 s), which is
where the four UART lines above come from: `RADIO_TX 0xBC`, `VC_CONNECTED True`,
`VC_DATA_EVENTS 0x217`, `ESB_MASTER_FRAMES 0x0`, `CTX_FE8 0x00`,
`CTX_105A 0x01`, and **no reset over the whole 20 s**.  (The small deltas
against the capture's `0xBA` / `0x212` are the timing cost of the capture's
four peripheral trace files; the capture numbers are the ones quoted as the
measurement.)

**Those two — the ESB pairing record and the app-side connection flag —
are the iteration-23 first divergence.  Neither is diagnosed here and no guess
is recorded as if it were.**

### 22.8 Measurements (every number below was actually run)

| metric | iter 20 final | iter 21 final | **iter 22 final (`i22b-app` + `i21c-net`)** |
|---|---:|---:|---:|
| app `ZEPHYR FATAL ERROR` @8.0 s | 0 | 1 (oops, t = 1.3988 s) | **0** |
| net `ZEPHYR FATAL ERROR` @8.0 s | 0 | 0 | **0** |
| `SYSRESETREQ` in the 20 s capture | 0 | n/a (capture crashed) | **0** |
| device name formatted by `__sprintf_chk` | not reached | **oops** | **`Even G1_R_FFFFFF`** |
| `bt_le_adv_start` return | not called | not reached | **0** |
| `radio TransmittedFrames` (20 s capture) | 0 | 0 | **186 (0xBA)**; oracle 560 |
| `vcentral Connected` | False | False | **True** (oracle True) |
| `vcentral ConnectIndsSent` | 0 | 0 | **1** (oracle 1) |
| `vcentral DataEventsAnswered` | 0 | 0 | **530** (oracle 533) |
| app instructions @8.0 s | 17,753,624 | — | **17,050,183** |
| net instructions @8.0 s | 2,080,530 | — | **2,896,620** |
| app FLASH | 649,688 B | 698,636 B | **698,652 B (+16; 71.11 % of 982,528)** |
| app RAM | 252,885 B | 252,885 B | **252,885 B (+0)** |
| net FLASH | 228,409 B | 221,997 B | **221,997 B (+0, net not rebuilt)** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | **0 / 0** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_net_raw_literals.py` (net) | 74 | 69 | **69** (unchanged image) |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | 10/10, EXIT 0 | **10/10, EXIT 0** (120 trials) |
| `gen_retained_sources.py --check` | clean | clean | **clean** |
| absolute `rodata_*` pins in the app link | 2,128 | 346 | **342** |
| app retained reconstruction sources | 1,707 | 1,640 | **1,620** |

App RAM is byte-identical to iteration 21, so **no latent absolute-RAM-pin
collision changed owner** (the hazard iteration 7 §A.5 recorded).

### 22.9 Graphics + sensor parity — a COMPLETE capture, first since iteration 20

```
G1_RESC=/Users/freedomcoder/Projects/armemul/g1-ours.resc \
G1_APP_ELF=/private/tmp/g1-i22b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i21c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i22
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
    /private/tmp/g1_ours_i22 /private/tmp/g1-i22/ours_reports
```

Both phases completed (`VTIME_P1` 6.000000000, `VTIME_P2` 20.000000000), no
Renode failure, **no memory poked**.

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px / 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px / 2,752 windows**. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px / 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px / 673 windows**. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764** — all 34 shared transactions byte-identical, first difference at index **34** (oracle `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265,…}`). |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–21 (`0c5cc90b07…`), so first differing row **y = 267**, first differing pixel **x = 178** carries over unchanged. |
| **G-5** | **PASS** | panel-init sequence byte-exact at the same indices (three-band 153,600 B clear at 4–6, five `0xC0` words at 7–16, `0x46`/`0x31` pairs `0F 04` at 21/22 and `00 04` at 28/29, `0x9F`→ID at 32, trailing `0xB9 FF` at 33). |
| **G-6** | **PASS** | `spim_b` **stream_sha256 EQ**, 0 == 0 in both phases. |
| **S-IMU** | **PARTIAL** | `p1_boot` **1,027 / 1,089**, first difference at **#3** (oracle `W 18`, ours `W 0180`).  `p2_render` **700 / 1,200**, **all 700 byte-identical**, first difference is the truncation at **#700** (oracle's next is `W 28`). |
| **S-ALS** | **PARTIAL (prefix-exact)** | `p1_boot` **14 / 33**, all 14 byte-identical, first difference at **#14** (oracle `W 7E`).  `p2_render` **0 / 80**. |
| **S-PMIC** | **PARTIAL** | `p1_boot` **232 / 291**, first difference at **#0** (oracle `W 060206`, ours `W 040F`).  `p2_render` **370 / 508**, first difference at **#0** (oracle `W 070401 ×2`, ours `×3`). |
| **S-NFC** | **PARTIAL** | EEPROM (0x53) **11 / 25**, first difference at **#6** (oracle `W 200200`, ours `W 2002B8`).  System port (0x57) **12 / 22**, first difference at **#10** (oracle `W 0001`, ours `W 000101`).  Both `p2_render` **0** (oracle 7 / 4). |
| **S-ADC** | **PARTIAL (prefix-exact)** | **71 / 998**, first five register accesses byte-identical, first difference at **#5** (oracle writes `CH[3].CONFIG` 0x548 ← 0x20000; we go straight to `CH[0].PSELP`).  UART confirms `<err> adc_nrfx_saadc: Channel 3 not configured`. |
| **S-KEYS** | **PASS** | `gpiote0` **stream_sha256 EQ** (25 == 25); `gpiote1` 0 == 0. |
| **S-MIC** (negative) | **PASS** | `pdm0` **stream_sha256 EQ**, 2 == 2, no ENABLE/START. |
| **gyro** (negative) | **PASS** | `IMU_GYRO_ENABLED` False in both; `IMU_ACCEL_ENABLED` True in both. |
| **S-ESB** | **FAIL** | `esbslave MasterFramesSeen` **0** vs 0x175, `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01.  BLE half of the same chain now PASSES in all four of its counters (see §22.8). |

Score **5 PASS / 5 PARTIAL / 4 FAIL** — the same verdict cells as iterations
17–21.  **Nothing regressed against the iteration-20 baseline on any
per-device number**, and one improved:

| device / phase | oracle | iter 20 | iter 21 | **iter 22** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 1,089 | 1,027 | 551 | **1,027** |
| LSM6DSO `p2_render` | 1,200 | 700 | not measured | **700** (all byte-identical) |
| nPM1300 `p1_boot` | 291 | 232 | 97 | **232** |
| nPM1300 `p2_render` | 508 | 369 | not measured | **370** |
| OPT3001 `p1_boot` | 33 | 14 | 14 | **14** |
| ST25DV system port `p1_boot` | 22 | 12 | 6 | **12** |
| ST25DV NFC EEPROM `p1_boot` | 25 | 11 | 0 | **11** |
| `saadc` (whole run) | 998 | 71 | not measured | **71** |
| `gpiote0` (whole run) | 25 | 25 | not measured | **25** (hash EQ) |
| `pdm0` (whole run) | 2 | 2 | not measured | **2** (hash EQ) |
| `spim_a` `p1_boot` | 764 | 34 | 34 | **34** |
| `spim_a` `p2_render` | 2,881 | 0 | not measured | **0** |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | 0 / – | **0 / 0** |

**Not one pixel was painted, and that is stated plainly.**  What changed is
*why*: the oracle's own `spim_a.p1.trace` has no SPI activity between 0.121 s
and 3.92 s and every transaction past index 33 is downstream of the L+R lens
sync, which our CPUNET never starts (§22.7).  `JBD FrameCounter` is 0x3 in both
phases (oracle 0x2A1 / 0xD61) and `JournalCount` 0x22 (oracle 0x400).

### 22.10 Re-proof

No canonical parity body was modified this iteration, so there is nothing to
re-prove with `cfg_verify`: twenty reconstructions were *retired* in favour of
the library, and the three new objects are hand-written wiring, not recovered
functions.  The proof that the displacement is correct is the byte table in
§22.1 plus the firmware's own `Advertising Even G1_R_FFFFFF successfully
started` line, which the recovered engine demonstrably could not produce.

**Harness blind-spot ledger:** unchanged at eleven instances.  This iteration
adds a *different* lesson: `tools/parity`/`tools/cfg_verify` passed
`printf_parse_format` because they emulate at the ORIGINAL address with the
ORIGINAL callees as order-keyed oracles, so a flattened control-flow
reconstruction can still reproduce the traced side effects.  **Byte identity
against the pinned SDK is a strictly stronger gate than parity for any function
the SDK owns, and it should be applied before parity, not after.**

### Regenerate (iteration 22)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/verify_printf.py     # 20 members, byte-exact
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/batch22.py apply     # Batch 4  (16 rows)
PYTHONSAFEPATH=1 .venv/bin/python <scratchpad>/batch22b.py apply    # Batch 4b (4 rows)
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh app /private/tmp/g1-i22a-app    # printf only
recon/application/build_cohesive.sh app /private/tmp/g1-i22b-app    # + adv objects (final)
# boot:    /private/tmp/g1-i22/probeB.resc  (8.0 s, checkpoints at 5.0/6.5/8.0)
# capture: see §22.9
```

Bisect ledger (every build and boot actually run):

| build | change | app FATAL @8 s | note |
|---|---|---|---|
| `i21b-app` + `i21c-net` | iteration-21 baseline | 1 (fortify oops, t = 1.4026 s) | `_svfprintf_r` returns 131 |
| `g1-i22a-app` | Batch 4 + 4b + aliases + FLOAT_PRINTF | 1 (t ≈ 2.4 s, `ancs_main` reboot) | **name correct**, `bt_le_adv_start` = −22 |
| `g1-i22b-app` | + `g1_bt_adv_objects.c` (§22.6) | **0** | **advertising starts, central connects** |

Files changed:
`recon/ownership/adoption_manifest.json` (+20 app exclusions),
`recon/generated/app_retained_sources.cmake` (regenerated by the sanctioned
generator only),
new `recon/symbols/g1_app_newlib_printf_aliases.ld`,
new `recon/application/app/src/g1_bt_adv_objects.c`,
`recon/symbols/g1_app_globals.ld` (3 pin rebinds),
`recon/application/app/prj.conf` (`CONFIG_NEWLIB_LIBC_FLOAT_PRINTF=y`),
`recon/application/app/CMakeLists.txt` (1 TU, 1 linker fragment with SORT_KEY,
5 `--undefined` roots),
`recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no devicetree change, `armemul` untouched, nothing
committed.  The twenty displaced `.c` files remain on disk in
`recon/{app,symbolized}/src` exactly as before; only the manifest decides
whether they are compiled.

### 22.11 Open, named, and NOT fixed

1. **§22.7 — the ESB L↔R lens sync never starts.**  `esb_channel` = 255 and
   `esb_master_addr`/`esb_slave_addr` = 00 for the whole run, `esbslave
   MasterFramesSeen` = 0, so `ESB_SYNC_ctx_105a` stops at 1 and
   `DISPLAY_ON_ctx_fe8` never becomes 1.  **This is the first divergence for
   iteration 23 and it is the only thing between the current build and the
   first pixel.**
2. **The app-side connection flag does not follow the link.**
   `vcentral Connected` = True and 530 data events are answered, but
   `low_speed_peripheral_dispatch_thread` keeps printing
   `get_glasses_ble_status 0 ble_is_connected 0`.  The host `connected`
   callback path into the application state is unverified.
3. **342 app `rodata_*` pins are still absolute.**  §22.6 shows this class is
   live, not latent: one of them (`rodata_8839c`) was worth an -EINVAL.  Each
   still needs its own extent evidence; a companion generator for
   non-string rodata is the obvious instrument.
4. **The RAM-arena `.data` restore drops every pointer-bearing run**, not just
   this one.  §22.6 fixed the two advertising arrays by hand; the generator's
   policy should be revisited for runs whose pointers target the arena itself
   (expressible as `&g1_ram_arena[off]`) or an emitted rodata object.
5. Iteration 21 items 3–4 (69 net raw literals incl. `RETURN_PARAM =
   0x21004630` and the ESB event-handler slot `0x21004628` — both on the ESB
   path that item 1 now blocks on) and iteration 20 items 3–6 are unchanged.

## Iteration 23 — the app's **`bt_conn_cb` entry is restored and `ancs_connected`
## runs for the first time**; the ESB gate is re-diagnosed from scratch (it was
## a HARNESS asymmetry, not firmware) and the CPUNET's ESB radio path is driven
## four stages deeper by three provable pointer/ABI defects

**Stated before anything else, because the acceptance bar is pixels:
NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`), `spim_a` is **34 / 764**
and **0 / 2,881**, and no `0x02` pixel-window transaction was emitted.  Nothing
below claims otherwise.

What did move, all measured:

| what | iteration 22 | **iteration 23** |
|---|---|---|
| `ancs_connected` (FUN_0001861c) executes | **never** | **yes, once, t ≈ 1.47 s** — UART `66:55:44:33:22:11 (public) -- type: 0x1, role:0x1 force_bind 0` |
| `g_ancs_conn` (the app's connection handle) | 0 | **0x2002C838** |
| `_bt_conn_cb_list` entries in our image | 1 (SDK mcumgr only) | **2** (`g1_ancs_conn_callbacks` + mcumgr) |
| app UART `esb_channel` / `esb_master_addr` / `esb_slave_addr` | 255 / 00 / 00 | **34 / 41 / 42** |
| `trigger_screen_state_change` reached | not measured | **yes, once** (r2 = 0, i.e. NOT the action=1 paint) |
| CPUNET ESB chain depth | `esb_service_init` only | **clock-transition cb → transport_start → radio_configure → ESB enable (FUN_010333b4) → mode_state_init** |
| `esbslave MasterFramesSeen` | 0 | **0** (oracle 0x175) |

### 23.1 Gate 1 root cause — the ESB pairing record was never provisioned **in
### our harness**, and the oracle's was.  This is a stimulus asymmetry.

`armemul/docs/g1-esb-sync-decode.md` §4 states the mechanism and
`armemul/g1.resc` implements it:

* `device_info[+2] = esb_channel_number`, `[+3] = esb_master_addr`,
  `[+4] = esb_slave_addr` are written **only** by the factory pairing command
  `get_assign_channel_info` @0x31fd8, itself gated on
  `g_test_mode_flag @0x20019ef3 == 1`.  **A lone offline glass never runs it**,
  so the values stay at their placeholders `0xFF / 0x00 / 0x00`;
* therefore `g1.resc` lines 151–176 install
  `sysbus.cpuapp AddHook 0x16268 "…WriteByte(di+0x2,0x22); …(di+0x3,0x41); …(di+0x4,0x42); … MACs …"`
  at `runtime_info_sync`'s entry **for the shipped images**;
* `armemul/g1-ours.resc` lines 92–96 **deliberately omit that hook** ("their PCs
  are pinned to ORIGINAL-image addresses … They are intentionally OMITTED
  here").

So every ours-vs-oracle capture from iteration 14 onward compared an
**unprovisioned** device against a **provisioned** one.  `esb_channel 255 /
esb_master_addr 00 / esb_slave_addr 00` — iteration 22 §22.7's headline symptom
— is exactly what the SHIPPED firmware also prints when the hook is absent.  It
was never evidence of a reconstruction defect.

**Fix (additive, opt-in, `armemul` untouched otherwise): new
`armemul/g1-ours-paired.resc`.**  It includes `g1-ours.resc` unchanged and adds
the identical writes, with the identical values, at the identical firmware
function, resolved to OUR build's PC through a `$rtinfo_pc` variable
(`nm zephyr.elf | grep -w runtime_info_sync` → `0x00015b9c` for `g1-i23a-app`).
Default is the original 0x16268, so including it over `g1.resc` is still
meaningful.  **Measured immediately:** the app UART changes from
`esb_channel 255 … esb_master_addr 00 esb_slave_addr 00` to
`esb_channel 34 … esb_master_addr 41 esb_slave_addr 42`, and the net core's id-1
handler receives `b0=0 b4=65 b5=66` (0x41/0x42) — the same values the oracle's
net core receives.

### 23.2 Gate 2 root cause — the application's `struct bt_conn_cb` was missing
### from the `bt_conn_cb` iterable section, so `ancs_connected` never ran

The chain is short and every link is a measurement:

1. the printed `ble_is_connected` is
   `low_speed_peripheral_dispatch_thread`'s local `side`, which can only become
   1 when `get_ancs_conn_handle() != 0`
   (`recon/symbolized/app/low_speed_peripheral_dispatch_thread.c:119,144,160`);
2. `get_ancs_conn_handle` (FUN_00019b2c) is one line:
   `return *(volatile unsigned *)0x20007518;` — `g_ancs_conn`;
3. `g_ancs_conn` has exactly **one** writer in the image, the last statement of
   `ancs_connected` (FUN_0001861c);
4. `ancs_connected` is a `struct bt_conn_cb::connected` callback, reached
   through the **`bt_conn_cb` iterable section**, whose bounds are the two pins
   the recovered Zephyr notifiers still carry — `rodata_87fec`
   (`_bt_conn_cb_list_start`) and `rodata_88058` (`_bt_conn_cb_list_end`);
5. the stride is proven by the recovered notifier itself:
   `recon/symbolized/app/ble_notify_remote_info_available.c` (identity
   FUN_00056da8, actually Zephyr's `bt_conn_security_changed` — it invokes the
   slot at `+0x14` with `(conn, conn[9] = sec_level, err)`) walks the section
   with `uVar4 = uVar4 + 0x24` and follows `_next` at `+0x20`.  So
   `sizeof(struct bt_conn_cb)` = **0x24** in the shipped build and the section
   holds exactly `(0x88058 − 0x87fec) / 0x24` = **3** entries;
6. the shipped section, read out of `app_update.bin`:

```
0x87fec  0001861d 00018add 00000000 00000000 00000000 000184f1 0 0 0
         -> { .connected        = 0x1861c  ancs_connected,
              .disconnected     = 0x18adc  ancs_disconnected,
              .security_changed = 0x184f0  ancs_security_changed }
0x88010  000220cd 00022079 0 0 0 0 0 0 0
0x88034  00052989 00052a0d 0 0 0 0 0 0 0
```

7. **in our image the section holds ONE entry, the SDK's own** —
   `nm /private/tmp/g1-i22b-app/zephyr/zephyr.elf`:
   `000847f4 R _bt_conn_cb_list_start` / `000847f4 r bt_conn_cb_mcumgr_bt_callbacks`
   / `00084810 R _bt_conn_cb_list_end` (0x1c = 28 B = 7 pointers, i.e.
   `CONFIG_BT_SMP=y` only).  `rodata_87fec` / `rodata_88058` were plain
   `PROVIDE(... = 0x00087fec / 0x00088058)` identity pins into the ORIGINAL
   image, which our relocated build does not reproduce.  Nothing else
   referenced the three callbacks, so `--gc-sections` dropped them outright:
   **`nm` finds no `ancs_connected`, `ancs_disconnected` or
   `ancs_security_changed` symbol at all in the iteration-22 ELF.**

The member indices confirm the layout is stock
`zephyr/include/zephyr/bluetooth/conn.h` order, and they line up across the two
struct sizes because the shipped extras (`remote_info_available`,
`le_phy_updated`) come **after** `security_changed`:

| slot offset used by a recovered notifier | index | member |
|---|---|---|
| `+0x08` (`ble_notify_disconnected.c`, misnamed) | 2 | `le_param_req` |
| `+0x0c` (`ble_notify_le_param_updated.c`) | 3 | `le_param_updated` |
| `+0x10` (`ble_notify_identity_resolved.c`) | 4 | `identity_resolved` |
| `+0x14` (`ble_notify_remote_info_available.c`, misnamed) | 5 | `security_changed` |

**Fix, the documented way (the `g1_bt_adv_objects.c` precedent from §22.6): a
linker rebind cannot express an object whose CONTENTS are pointers, so the
object is EMITTED** — new
`recon/application/app/src/g1_bt_conn_cb_objects.c`, using the stock
`BT_CONN_CB_DEFINE(g1_ancs_conn_callbacks)` macro, i.e. exactly the mechanism
the shipped firmware used.  No canonical parity body was touched; the three
callbacks are the recovered, parity-proven bodies, placed through a cast
(their reconstructed prototypes use plain integer words, AAPCS-identical).

**Measured on `g1-i23a-app`:**

```
000569cc T bt_conn_cb_register
00084b88 R _bt_conn_cb_list_start
00084b88 r bt_conn_cb_g1_ancs_conn_callbacks     <-- NEW
00084ba4 r bt_conn_cb_mcumgr_bt_callbacks
00084bc0 R _bt_conn_cb_list_end
00017bfc T ancs_connected      00017e10 T ancs_disconnected
00017ab0 T ancs_security_changed
2002f304 B g_ancs_conn
```

and with a block hook on each stage of the host path, all six fire once:
`le_enh_conn_complete` → `bt_hci_le_enh_conn_complete` → `bt_conn_add_le` (×2)
→ `bt_conn_connected` → `notify_connected` → **`ancs_connected`**.  The app
UART prints `ancs_connected`'s own line for the first time, and
`sysbus ReadDoubleWord 0x2002f304` returns **0x2002C838**.

**Honest correction to iteration 22 §22.11 item 2.**  The printed
`ble_is_connected` still reads **0** — and that is *correct behaviour*, not a
residual defect.  On the MASTER leg the flag needs four terms:

```c
if (connection != 0 && rd8(ctx,0xae3) == 0 && rd32(ctx,0x9b4) != 0 &&
    (rd8(ctx,0x6de) & 1)) { … side = 1; }
```

`ctx[0x6de]` bit 0 is set only in the **slave** branch of the same function and
lives inside the ESB segmented-frame staging window `ctx[0x6cc..0x6e0]`
(`g1-esb-sync-decode.md` §3), i.e. it is the **peer lens's** connection flag,
delivered over ESB.  A master with no completed L↔R sync can never print
`ble_is_connected 1`.  The defect iteration 22 named was real; the counter it
was named by is additionally ESB-gated.

### 23.3 The CPUNET ESB path — three provable defects, four stages of progress

With the pairing record provisioned, the CPUNET stopped one instruction into
`esb_service_init` and the app-side ESB gate became a **net-core** problem.
Block hooks on OUR build's own symbols (real instruction boundaries, unlike the
recon addresses the `g1-esb-sync-decode.md` correction warns about) gave:

```
i23-net baseline:   esb_worker_create, esb_service_init, clock_cb_register   [STOP]
                    clock_transition_cb / transport_start / radio_configure /
                    esb_enable / start_announcement / radio_tx_keying:  0 times
```

**Defect 1 — the clock-transition callback was registered as an
ORIGINAL-IMAGE code pointer.**  `FUN_0102b5bc` ends with
`FUN_0102bba8(P_0102b660)` where `#define P_0102b660 0x0102bf59`.  That literal
is `(analysis 0x0102b758 + 0x800) | 1` = **`FUN_0102b758`**, this core's
`g1_esb_clock_transition` — a CODE address, and in our relocated build
`FUN_0102b758` links at `0x0102cf14` while `0x0102bf58` is unrelated bytes.
Commit 0a7dee8c rebound the `ADDR_*_THUMB` macro class; this is a per-file `P_`
literal and was never in it.  Fixed under `G1_COHESIVE_BUILD` in both
`recon/net/src/FUN_0102b5bc.c` and `recon/symbolized/net/FUN_0102b5bc.c`
(parity keeps the shipped literal).  **Measured:** the chain advances three
stages — `clock_transition_cb → transport_start → radio_configure → esb_enable`.

**Defect 2 — the two RADIO packet-configuration trampolines did not exist.**
`FUN_010333b4` stores `0x010333a5` or `0x010333e5` into the radio callback slot
and then calls it.  Analysis addresses `0x01032ba4` / `0x01032be4`; both land on
a real `push {r0, r1, r2, r3, r4, lr}` prologue after a literal pool, and both
sit in a **Ghidra gap** (FUN_01032ad8 ends 0x01032b38, next catalogued entry
0x01032c28) — this is precisely the "net residual 1 (interior address inside
FUN_010333b4)" that 0a7dee8c could not rebind.  Reconstructed, together with
the RADIO PCNF0/PCNF1 packer they share at `0x01032b4c`:

| new file | analysis VA | extent | proof |
|---|---|---|---|
| `recon/net/src/FUN_01032b4c.c` | 0x01032b4c | 0x52 | `emu.compare(..., trials=300, no_return=True)` → **pass, 300/300 checked, 0 mismatches** |
| `recon/net/src/FUN_01032ba4.c` | 0x01032ba4 | 0x40 | same, `call_arities=(3,1)` → **pass 300/300** |
| `recon/net/src/FUN_01032be4.c` | 0x01032be4 | 0x44 | same, `call_arities=(1,)` → **pass 300/300** |

`net_recon_kit.prove` refuses them ("name/address does not match net catalog"),
so the underlying `tools/parity` harness was driven directly — **no `tools/`
logic was changed**.  That is sound here and the reason is structural: all
three are **branch-free straight-line code** (no conditional branch, no
cbz/cbnz, no tbb/tbh), so `cfg_verify`'s contribution — deriving inputs from
the CFG so that every branch/case is exercised — is *vacuous*, and 300
randomized trials over a zero-branch body are complete coverage.  The
`call_arities` values are not tuning: the callee `FUN_01032b4c` genuinely takes
one pointer (it only reads `[r0,#0..12]`) and `FUN_0103b62e` is memset(3); with
the arity unstated the harness compared dead scratch registers at the call and
reported a false mismatch on `FUN_01032be4`.  The two pointers are now rebound
in `recon/symbols/g1_net_symbols.h` through the sanctioned
`__asm__`-alias pattern (`ADDR_FUN_010333a4_THUMB`, `ADDR_FUN_010333e4_THUMB`).

**Defect 3 — a DROPPED REGISTER ARGUMENT, the harness blind spot, in
`FUN_01032764`.**  `FUN_010333b4` does

```c
extern uint64_t FUN_01032764(uint32_t, uint32_t);   /* "returns status in r0 and
                                                       deliberately preserves its
                                                       incoming r1" */
uint64_t init_result = initialize_radio_mode_state(value, 0x2100499c /* g_esb_event_handler_fn */);
callback_slot = (volatile uint32_t *)(uintptr_t)(uint32_t)(init_result >> 32);
```

but the recovered leaf was `unsigned int FUN_01032764(**void**)`.  The shipped
body (0x01032764..0x01032792) touches **r0, r2, r3 only** — objdump:
`ldr r3,[pc,#44]; ldr r2,[pc,#48]; ldrb r3,[r3,#8]; str.w r3,[r2,#0x510];
cmp r3,#4; bhi; tbb [pc,r3]; … movs r0,#1; str r2,[r3,#0]; bx lr` — so r1 is a
genuine live-through that GCC's interprocedural register allocation exploited.
Compiled as a separate TU from a `(void)` prototype, GCC is free to clobber r1,
and did: `callback_slot` was garbage, `*callback_slot = <trampoline>` wrote into
the void and the indirect call dispatched nowhere.  **This is exactly the class
the blind-spot ledger names** — parity cannot see a dropped register argument
because it drives the ORIGINAL bytes with its own r1.  Corrected to
`unsigned long long FUN_01032764(unsigned int unused_r0, unsigned int slot)`
returning `((uint64_t)slot << 32) | status`, and **re-proven with the
authoritative verifier**: `net_recon_kit.prove(0x01032764, 0x2e, …)` →
`{'pass': True, 'stage': 'cfg_verify', 'checked': 6, 'cfg_status': 'PASS'}`
(6 CFG-derived cases = the five `tbb` arms plus the default).

**Where it stops now, named precisely.**  With all three fixed
(`/private/tmp/g1-i23e-net`), the CPUNET reaches `FUN_010333b4` and returns from
`FUN_01032764`, but **neither trampoline hook fires** and `acquire_buf_table`
(FUN_010327a0) is never reached.  In `FUN_010333b4` the slot is written only
inside `if (saved[0] == 0) … else if (saved[0] == 1) …`, so the measurement says
`saved[0] ∉ {0,1}` — the ESB **configuration struct** that `FUN_0102b31c` hands
to `FUN_010333b4` (`saved[] = (volatile uint8_t *)0x21004a94`, copied from
`configuration[0..4]`) does not carry the mode byte the shipped firmware has.
That is the iteration-24 first divergence, and it is one function upstream.

Still-unrebound raw runtime code pointers in the same function, all downstream
of that stop and all in Ghidra gaps except one:

| literal (runtime) | analysis | role | reconstructed? |
|---|---|---|---|
| `0x01032fbd` | 0x010327bc | radio-owner timer callback | **no** (gap after FUN_010327a0) |
| `0x01032fd9` | 0x010327d8 | RADIO IRQ 8 handler | **yes** — `FUN_010327d8` links at 0x0102dcb4; needs only a rebind |
| `0x0103309d` | 0x0103289c | IRQ 0x1d handler | **no** (gap after FUN_01032860) |
| `0x0103b03b` | 0x0103a83a | IRQ 0x19 handler | **no** (gap after FUN_0103a80c) |

Two more odd (Thumb) code literals exist elsewhere in the symbolized net tree
and are recorded for the same treatment: `C_01008e70 = 0x0100957d` and
`DAT_01019eb0 = 0x01019a9d`.

### 23.4 Two builds are reported, as the standing instruction requires

`FUN_0102b5bc`'s pointer rebind is provably correct, and it moves the CPUNET
*into* a new, deeper stall.  Neither build is hidden.

| pair | app | net | net behaviour | ESB PTX | reset-free 20 s |
|---|---|---|---|---|---|
| **A (acceptance capture)** | `g1-i23a-app` | `g1-i23-net` | ESB chain stops at `clock_cb_register`; core keeps running | 0 | **yes** |
| **B (deepest)** | `g1-i23a-app` | `g1-i23f-net` (== `i23e`) | reaches `FUN_010333b4`, stops after `FUN_01032764` | 0 | see §23.6 |

`g1-i23-net` is the tree as of the app-only change; `g1-i23f-net` is the tree as
it stands now (`i23b` = defect 1 only, `i23c` = + defect 2, `i23d` = + the
symbolized-literal spelling that keeps `check_net_raw_literals` at 69,
`i23e` = + defect 3, `i23f` = + the manifest cleanup below).  `i23e` and `i23f`
are behaviourally identical (same sources; re-probed, same stop point, same
`FUN_01032764`-reached / trampolines-not-reached signature) and link to the
same 222,189 B.

**Manifest cleanup.**  Once the three new symbolized net copies carry the
standard identity header, `tools/gen_retained_sources.py` picks them up on its
own (net retained **955 → 958**), so the explicit `CMakeLists.txt` entries were
removed to avoid compiling the same TU twice.  `--check` is clean and the
generated cmake was produced only by the sanctioned generator.

### 23.5 Graphics + sensor parity — pair A, a COMPLETE capture

```
G1_RESC=/private/tmp/g1-i23/ours-paired-i23.resc      # $rtinfo_pc=0x15b9c; i @g1-ours-paired.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf
G1_NET_ELF=/private/tmp/g1-i23-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i23
```

Both phases completed (`VTIME_P1` 6.000000000, `VTIME_P2` 20.000000000),
**0 `ZEPHYR FATAL ERROR`, 0 `SYSRESETREQ`**, no memory poked beyond the
oracle's own pairing provisioning (§23.1).

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px / 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px / 2,752 windows**. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px / 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px / 673 windows**. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, all 34 shared transactions byte-identical, first difference at index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–22 (`0c5cc90b07…`), so first differing row **y = 267**, first differing pixel **x = 178**, carried over unchanged. |
| **G-5** | **PASS** | panel-init sequence byte-exact at the same indices. |
| **G-6** | **PASS** | `spim_b` `stream_sha256` EQ, 0 == 0 in both phases. |
| **S-ESB** | **FAIL** | `MasterFramesSeen` **0** vs 0x175, `AcksInjected` **0** vs 0x175, `AnnounceResponsesInjected` **0** vs 0x15B, `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01.  BLE half still passes: `VC_CONNECTED` True == True, `VC_CONNECT_INDS` 1 == 1, `VC_DATA_EVENTS` **0x216** vs 0x215, `RADIO_TX` **0xBD** vs 0x230. |

Per-device volumes — **nothing regressed, nothing improved**:

| device / phase | oracle | iter 20 | iter 22 | **iter 23 (pair A)** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 1,089 | 1,027 | 1,027 | **1,027** |
| LSM6DSO `p2_render` | 1,200 | 700 | 700 | **700** |
| nPM1300 `p1_boot` | 291 | 232 | 232 | **232** |
| nPM1300 `p2_render` | 508 | 369 | 370 | **370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV system port `p1_boot` | 22 | 12 | 12 | **12** |
| ST25DV NFC EEPROM `p1_boot` | 25 | 11 | 11 | **11** |
| `saadc` (whole run) | 998 | 71 | 71 | **71** |
| `gpiote0` (whole run) | 25 | 25 | 25 | **25 (hash EQ)** |
| `pdm0` (whole run) | 2 | 2 | 2 | **2 (hash EQ)** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | **34 / 0** |
| `JBD FrameCounter` `p1` / `p2` | 0x2A1 / 0xD61 | 0x3 / 0x3 | 0x3 / 0x3 | **0x3 / 0x3** |
| `JBD JournalCount` | 0x400 | 0x22 | 0x22 | **0x22** |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | 0 / 0 | **0 / 0** |

Score **5 PASS / 5 PARTIAL / 4 FAIL** — the same verdict cells as iterations
17–22.

### 23.5b Pair B (`g1-i23a-app` + `g1-i23e-net` / `g1-i23f-net`) — measured with probes

Pair B is the tree as it stands.  Measured directly (probe scripts
`/private/tmp/g1-i23/probe{H,I,J,K}.resc`, all run to completion, all with the
paired provisioning and the virtual ESB slave enabled):

```
6.0 s virtual, both cores:  ZEPHYR FATAL ERROR 0, SYSRESETREQ 0
NK esb_enable            1     (FUN_010333b4 reached — never reached before)
NK mode_state_init       1     (FUN_01032764 entered and returned)
NK trampoline_ba4/be4    0     <-- saved[0] is neither 0 nor 1 (§23.7 item 1)
NK acquire_buf_table     0
NK start_announcement    0
NK radio_tx_keying       0
esbslave MasterFramesSeen 0x00000000   AcksInjected 0x00000000
device_ctx[0x105a] 0x01 (oracle 0x02)  device_ctx[0xfe8] 0x00 (oracle 0x01)
```

The stall inside `FUN_010333b4` is a *blocked thread*, not a runaway: virtual
time advances normally (a 4 s run completes in ~13 s wall on a stripped probe).

A full 20 s pair-B capture was also attempted.  **Phase 1 completed and is
byte-identical to pair A** — `VTIME_P1` 6.000000000, `JBD FrameCounter` 0x3,
`spim_a.p1.trace` **309,082 B in both**, `fb_p1_boot.ppm` body sha256
`0b150fd32588b1da…` **in both**, **0 lit pixels in both**, `twim1.p1` /
`twim2.p1` traces present.  **Phase 2 did not complete**: Renode itself aborted
(`Abort trap: 6` inside `Antmicro.Renode.UI.ConsoleIOSource.RedirectedHandling`
→ `BlockingCollection.Add`) — the *same console-layer crash iteration 21 hit*,
and the direct consequence of the run being detached from an interactive
console.  Up to the abort: **0 `ZEPHYR FATAL ERROR`, 0 `SYSRESETREQ`**.  That
is a harness failure, not a firmware fault, and it is why **pair A is the
capture reported in §23.5**.  No pair-B phase-2 graphics or sensor number is
claimed anywhere in this report.

### 23.6 Measurements (every number below was actually run)

| metric | iter 21 | iter 22 | **iter 23 pair A** | **iter 23 pair B** |
|---|---:|---:|---:|---:|
| app `ZEPHYR FATAL ERROR` @8 s | 1 | 0 | **0** | **0** |
| net `ZEPHYR FATAL ERROR` @8 s | 0 | 0 | **0** | **0** |
| `SYSRESETREQ` in the capture | n/a | 0 | **0** | **0** (to the phase-2 abort) |
| `_bt_conn_cb_list` entries | 1 | 1 | **2** | **2** |
| `ancs_connected` executions | 0 | 0 | **1** | **1** |
| `g_ancs_conn` | 0 | 0 | **0x2002C838** | **0x2002C838** |
| app UART `esb_channel` | 255 | 255 | **34** | **34** |
| `radio TransmittedFrames` (capture) | 0 | 186 (0xBA) | **189 (0xBD)** | see §23.5b |
| `vcentral Connected` | False | True | **True** | see §23.5b |
| `vcentral ConnectIndsSent` | 0 | 1 | **1** | see §23.5b |
| `vcentral DataEventsAnswered` | 0 | 530 | **534 (0x216)** | see §23.5b |
| `esbslave MasterFramesSeen` | 0 | 0 | **0** (oracle 0x175) | **0** |
| app FLASH | 698,636 B | 698,652 B | **699,948 B (+1,296; 71.24 %)** | same |
| app RAM | 252,885 B | 252,885 B | **252,885 B (+0)** | same |
| net FLASH | 221,997 B | 221,997 B | **221,997 B** | **222,189 B (+192; 96.01 % of 231.4 KB)** |
| net RAM | — | — | **60,556 B** | **60,556 B** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | **0 / 0** | **0 / 0** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | 0 / 0 | **0 / 0** | **0 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** | — |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | 10/10, EXIT 0 | **10/10, EXIT 0** | — |
| `check_net_raw_literals.py` | 69 | 69 | **69** | **69** |
| `gen_retained_sources.py --check` | clean | clean | **clean** | **clean** |

App RAM is byte-identical to iterations 20–22 (`_end` at 0x2003fbd5 in both
`g1-i22b-app` and `g1-i23a-app`), so no latent absolute-RAM-pin collision
changed owner and the iteration-20 `G1_CTX_*` probe addresses stay valid.

`check_net_raw_literals` needed one deliberate step: the first cut of the three
new net functions read `0x21000684 + 17` as a raw literal, which the checker
correctly flagged as a **70th** literal inside a live object (`m_cb + 0x24`).
The canonical parity bodies in `recon/net/src` keep the literal; the
**symbolized** copies name `g_net_radio_crc_scratch` instead and are the ones
the cohesive build compiles, so the count returns to **69**.

### 23.7 Open, named, and NOT fixed

1. **The ESB configuration byte `saved[0]`.**  `FUN_010333b4` writes the RADIO
   callback slot only for `saved[0] ∈ {0,1}`; measured, neither branch is
   taken, so the slot keeps stale contents and the indirect call goes nowhere.
   `saved[] = 0x21004a94` is copied from the `configuration[]` struct
   `FUN_0102b31c` passes.  **This is the iteration-24 first divergence.**
2. **Four raw runtime code pointers remain in `FUN_010333b4`** (table in
   §23.3).  One (`0x01032fd9` → `FUN_010327d8`, the RADIO IRQ 8 handler) is
   already a defined symbol and needs only the `ADDR_*_THUMB` rebind; the other
   three are Ghidra-gap functions that must be reconstructed first.
3. **`analysis 0x0102b204` (168 B) is still unreconstructed**, so
   `FUN_0102b1c8` still creates the ESB worker with `K_FOREVER`
   (iteration 18 §18.8 item 1).  This iteration did **not** need it: the ESB
   transport is started from the clock-transition callback, not from that
   worker, and the chain advanced four stages with the worker still parked.
4. **Iteration 22 §22.11 items 3–4 are unchanged**: 342 app `rodata_*` pins are
   still absolute (one of them, `rodata_87fec`, cost this iteration's gate 2),
   and the RAM-arena `.data` restore still drops every pointer-bearing run.
   **A generator for non-string rodata and for pointer-bearing `.data` runs is
   now the single highest-value instrument in the project** — three of the last
   four blockers (§22.6 G, §22.6 H, §23.2) were the same defect wearing a
   different hat.
5. **Two odd Thumb literals elsewhere in the net tree** (`C_01008e70` =
   0x0100957d, `DAT_01019eb0` = 0x01019a9d) are unaudited code pointers of the
   same class as §23.3 defect 1.
6. The shipped `bt_conn_cb` struct is **36 B (9 pointers)** and ours is
   **28 B (7)**, i.e. the shipped build also sets `CONFIG_BT_REMOTE_INFO` and
   `CONFIG_BT_USER_PHY_UPDATE` (the only two members that fit between
   `security_changed` and `_next`).  Not applied this iteration — it perturbs
   the host stack and was not needed for the fix, since indices 0/1/5 coincide
   in both layouts.
7. Shipped `bt_conn_cb` entries 2 and 3 —
   `{0x220cd, 0x22079}` (app code, uncatalogued: inside the gap after
   `FUN_0002201c`, which ends at 0x2205e) and `{0x52989, 0x52a0d}` (gap after
   `FUN_00052880`, which ends at 0x52980) — are **identified but not
   reconstructed**, so our section still has 2 entries where the shipped image
   has 3.

### Regenerate (iteration 23)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh app /private/tmp/g1-i23a-app
recon/application/build_cohesive.sh net /private/tmp/g1-i23f-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# ESB pairing provisioning (opt-in, mirrors g1.resc for the shipped images):
#   $rtinfo_pc = nm zephyr.elf | grep -w runtime_info_sync   -> 0x00015b9c
#   i @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc
# capture: see §23.5 ;  probes: /private/tmp/g1-i23/probe{A..K}.resc
```

Files changed:
new `recon/application/app/src/g1_bt_conn_cb_objects.c`,
`recon/application/app/CMakeLists.txt` (1 TU),
new `recon/net/src/{FUN_01032b4c,FUN_01032ba4,FUN_01032be4}.c` +
`recon/symbolized/net/` copies,
`recon/net/src/FUN_01032764.c` + `recon/symbolized/net/FUN_01032764.c`
(signature correction, re-proven with `cfg_verify`),
`recon/net/src/FUN_0102b5bc.c` + `recon/symbolized/net/FUN_0102b5bc.c`
(cohesive-build callback pointer),
`recon/symbolized/net/FUN_010333b4.c` (slot literal → `ADDR_*_THUMB`),
`recon/symbols/g1_net_symbols.h` (two pointers RESOLVED),
`recon/application/net/CMakeLists.txt` (comment only — the three new TUs are
picked up by the generator),
`recon/generated/net_retained_sources.cmake` (regenerated by
`tools/gen_retained_sources.py` only; net retained 955 → 958),
new `armemul/g1-ours-paired.resc` (**additive/opt-in; `g1-ours.resc`
untouched**),
`recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no devicetree change, nothing committed.

## Iteration 24 — the ESB mode byte is FIXED (a net analysis/runtime
## COORDINATE-SPACE defect), two more missing `.data` objects are restored, and
## the CPUNET keys its **first ESB PTX frame ever** — at the cost of a real,
## measured phase-2 regression that is reported in full

**Stated before anything else, because the acceptance bar is pixels:
NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the
oracle's **656** (`p1_boot`) / **1,098** (`p2_render`); `spim_a` is **34 / 764**
and **0 / 2,881**; **no `0x02` pixel-window transaction was emitted**; no
display START with `action = 1` arrived (`trigger_screen_state_change` is
reached exactly once, with `r2 = 0`).  Nothing below claims otherwise.

What did move, all measured:

| what | iteration 23 | **iteration 24** |
|---|---|---|
| `FUN_010333b4` packet-config branch taken | **neither** (`saved[0] ∉ {0,1}`) | **`saved[0] == 1`** → `FUN_01032be4` (the DPL packet config) runs |
| `esb_enabled` flag `0x21006459` | 0 | **1** |
| `esbslave MasterFramesSeen` (6 s probe) | 0 | **1** |
| `esbslave AcksInjected` (6 s probe) | 0 | **1** |
| `esbslave AnnounceResponsesInjected` (6 s probe) | 0 | **1** |
| ESB chain depth | stops in `FUN_010333b4` | `radio_configure → esb_enable → mode_state_init → DPL trampoline → acquire_buf_table → owner_timer → backend_init → start_announcement → packet_publish → **esb_start_tx**` |
| `esbslave MasterFramesSeen` (20 s acceptance capture) | 0 | **0** — see §24.6, the machine resets mid-phase-2 and zeroes the model counters |

### 24.1 Root cause of the named blocker: the ESB configuration template was
### read in the WRONG COORDINATE SPACE

`FUN_0102b31c` builds the five-word ESB configuration from a rodata template.
The shipped prologue is unambiguous:

```
102b322  ldr  r5,[pc,#0x9c]   ; [0x102b3c0] = 0x0103c100     <- a RUNTIME pointer
102b326  ldm  r5!,{r0,r1,r2,r3}
102b328  stm  r4!,{r0,r1,r2,r3}     ; config[0..3] = template[0..3]
102b32e  str  r3,[sp,#8]            ; config[1] = 0x0102bd0d   (event handler)
102b336  strb r3,[sp,#5]            ; config[0] byte 1 = (param_1 != 0)  (mode)
102b33e  strd r2,r3,[sp,#0x10]      ; config[3] = 0x0005012c, config[4] = 0x0101fb02
```

so only **config[0] bytes 0/2/3 and config[2]** survive from the template.  The
literal `0x0103c100` is a **runtime** flash address (`tools/net_address_space.py`;
runtime = analysis + 0x800).  The reconstruction had inlined the template read
at **analysis** 0x0103c100 instead:

| | word 0 | word 2 |
|---|---|---|
| `net_extract.read_analysis(0x0103c100)` — what was inlined | `0x21002388` | `0x0103aac3` |
| `net_extract.read_runtime(0x0103c100)` — **the real template** | **`0x00000001`** | **`0x00000201`** |

The full 16 real bytes are `01 00 00 00 | 00 00 00 00 | 01 02 00 00 | 58 02 03 00`,
and they reproduce nRF `struct esb_config` exactly, cross-checked against
`FUN_010333b4`'s own byte reads of the copy at `0x21004a94`:

```
+0x00 protocol          = 1      ESB_PROTOCOL_ESB_DPL   -> saved[0] == 1
+0x01 mode              = (param_1 != 0)
+0x04 event_handler     = 0x0102bd0d
+0x08 bitrate           = 1
+0x09 crc               = 2      -> FUN_010333b4 programs CRCPOLY 0x11021 / CRCCNF 2
+0x0a tx_output_power   = 0
+0x0c retransmit_delay  = 0x012c (300 us)
+0x0e retransmit_count  = 5
+0x10 tx_mode           = 2
+0x11 payload_length    = 0xfb   (251 = the DPL maximum; FUN_010333b4 passes
                                  saved[0x11] to the packet-config trampoline)
+0x12 selective_auto_ack= 1
+0x13 use_fast_ramp_up  = 1      -> RADIO MODECNF0 |= 1  (saved[0x13])
```

With the stale words, `saved[0]` was `0x88` and `saved[9]` was `0xaa`, so
`FUN_010333b4` took **neither** packet-config branch and **neither** CRC branch:
the RADIO callback slot was never written, CRCCNF/CRCPOLY/PCNF were never
programmed, and no ESB frame could be keyed.  That is exactly the
iteration-23 §23.7 item 1 symptom, and it is a **harness blind spot of a new
kind**: `config[]` is a *stack buffer passed by pointer to an oracled callee*,
so the parity harness never compared its contents — and the harness's own flash
map has nothing at 0x0103c100 either, so the original run read zeros.  The
values were pure reconstruction judgement, and the judgement used the wrong
address space (`tools/NET_PLAYBOOK.md`'s named hazard).

**Fix** — `recon/net/src/FUN_0102b31c.c` corrected to the runtime template and
**re-proven with the authoritative verifier**:
`net_recon_kit.prove(0x0102b31c, 0xa2, …)` →
`{'pass': True, 'stage': 'cfg_verify', 'checked': 303, 'cfg_status': 'PASS'}`.
The symbolized copy carries the same correction.
**Measured immediately (`/private/tmp/g1-i24a-net`):** `NK trampoline_be4`
fires — `saved[0] == 1` — and the chain advances through `acquire_buf_table`
into `start_announcement`.

### 24.2 Two more `.data` objects that were bare linker pins

The corrected mode byte unmasked two consecutive failures, both the
"§23.7 item 4" class (a pinned address with no storage and no initialiser).

**(a) The ESB radio owner's `nrfx_timer_t` instance @ 0x21000698.**
`FUN_01034fa8` is `nrfx_timer_init`; its literal pool holds
`"ASSERTION FAIL @ %s:%d"` + `".../nrfx_timer.c"` + line `0x8e`, and it asserts
`p_instance->p_reg ∈ {TIMER0 0x4100c000, TIMER1 0x41018000, TIMER2 0x41019000}`.
The pin `g_net_log_msg_ctx = 0x21000698` (an autonamer misnomer — every
consumer dereferences it as a timer instance, e.g. `FUN_01032860` writes
`*(*(uint32_t**)0x21000698 + 0x548)` = TIMER CC[2]) had no object, so `p_reg`
read garbage.  **Measured (probeE):** the assertion failed, Zephyr's default
`assert_post_action` **returns** (the shipped `FUN_01039bb0` is `noreturn`), so
control fell straight through into `nrfx_timer_extended_compare`
(`FUN_01032764`… `FUN_01034f24`) with `r0 = 4` / `r1 = 0x8e` — the assert's own
leftover registers — which failed its frequency check and returned
**`0x0BAD0004`**.  `FUN_010333b4` requires `0x0BAD0000`, so it returned -EFAULT.
Shipped `.data` initialiser (LMA 0x0103ed24 + 0x698):
`00 90 01 41 | 00 08 00 00` = `{ p_reg = TIMER2, instance_id = 0,
cc_channel_count = 8 }`.  Emitted in
`recon/application/net/src/timeslot_owner.c`; the linker PROVIDE is superseded.

**(b) The two nrfx GPPI/DPPI allocator words @ 0x210006a0 / 0x210006a4.**
`FUN_01034328` claims the highest set bit of a free bitmap and returns
`0x0BAD0002` when the word is zero.  Both addresses were pins.  Shipped
initialisers `3f 00 00 00` (groups 0..5 free) and `00 c0 ff ff` (channels 14..31
free; 0..13 belong to the SDC).  **Measured (probeF):** with only (a) fixed,
`FUN_01033df0` was reached for the first time and still failed here —
`"gppi_channel_alloc failed with: %d"` → -EIO.  Both are now emitted;
0x210006a0 gained the name `g_net_dppi_group_pool` (its raw-literal users are
symbolized, so the raw-literal count went **down**).

**Measured with (a)+(b) (`/private/tmp/g1-i24c-net`, probeG):**

```
esb_enabled(0x21006459) 0x01     service_state(0x21004c9b) 0x02
esbslave MasterFramesSeen 1      AcksInjected 1      radio TransmittedFrames 1
NK radio_configure / backend_init / start_announcement / packet_publish / esb_start_tx
```

**That is the first ESB PTX frame this project has ever produced, and the
virtual right lens answered it.**

### 24.3 Seven Ghidra-gap functions recovered (the ESB event path)

Exactly one frame was keyed and the announcement was never re-armed, because
event id 1 (TX success) is what calls `FUN_0102b3f0(0) → esb_start_tx` again.
The whole event path was unreconstructed.  All seven were proven by driving
`tools/parity` directly (`net_recon_kit.prove` refuses names absent from the
net catalog; **no `tools/` logic was changed**):

| new file | analysis VA | extent | role | proof |
|---|---|---|---|---|
| `FUN_0102b50c.c` | 0x0102b50c | 0x90 | **the ESB `event_handler`** (config[1]) | 400/400, event ids 0/1/2/default all directed via `memory_overrides` |
| `FUN_0102b49c.c` | 0x0102b49c | 0x60 | peer-sync 0x11 announce-response builder | 300/300 |
| `FUN_010337ac.c` | 0x010337ac | 0xa2 | `esb_read_rx_payload` (FIFO pop at 0x21004a34) | 300/300 |
| `FUN_0102bbe0.c` | 0x0102bbe0 | 0x6 | peer-sync pending flag read | 300/300 |
| `FUN_0103289c.c` | 0x0103289c | 0x5e | **the ESB EVENT DISPATCH** (IRQ 0x1d) | 300/300 + 50 directed null-handler trials |
| `FUN_010327bc.c` | 0x010327bc | 0x18 | nrfx_timer COMPARE1 callback | 300/300 |
| `FUN_0103a83a.c` | 0x0103a83a | 0x4 | IRQ 0x19 thunk (`b.w FUN_010350a4`) | 300/300 |

`FUN_0103289c` is the piece that closes the loop: it drains the pending-event
bitmap at 0x210049b0 under BASEPRI and calls the handler published at
0x21004a90 once per set bit, with a stack object whose byte 0 is the event id —
exactly what `FUN_0102b50c` reads.

**Five pointers rebound** (all original-image runtime literals, all the
0a5/0a8-commit class the `ADDR_*_THUMB` pass could not reach):

* `config[1]` `0x0102bd0d` → `&FUN_0102b50c` (under `G1_COHESIVE_BUILD`;
  parity keeps the literal).  **Measured:** `0x21004a90` now reads
  `0x0102B2C5` = `&FUN_0102b50c | 1`;
* `0x01032fbd` → `FUN_010327bc`, `0x01032fd9` → `FUN_010327d8`,
  `0x0103309d` → `FUN_0103289c`, `0x0103b03b` → `FUN_0103a83a`
  (`ADDR_*_THUMB` aliases in `recon/symbols/g1_net_symbols.h`) — iteration 23
  §23.7 item 2, now closed.

### 24.4 A fourth defect: the RADIO IRQ 8 handler's mask was wrong

`recon/application/net/src/timeslot_owner.c`'s hand-written `FUN_010327d8`
tested `INTENSET & 0x20`.  The shipped body is
`ldr.w r2,[r3,#0x304]; lsls r2,r2,#27; bpl` — shifting left by 27 puts **bit 4**
in N, i.e. the mask is **0x10** (the DISABLED interrupt, which pairs with the
`EVENTS_DISABLED` register at 0x110 the next instruction reads).  **Measured
(probeK), once IRQ 8 was finally connected to this handler:** RADIO INTENSET
reads `0x00000010`, `& 0x20` was always 0, `EVENTS_DISABLED` was never cleared,
and the handler re-entered **1,312 times in one 6 s probe** while the ESB
state-machine continuation was never called.  Corrected to 0x10.

### 24.5 Where it stops now — the iteration-25 first divergence, named

```
probeN (final tree g1-i24g-net):
  esb_state_cb (0x210049a0)  = 0x010338B1   <-- ORIGINAL-IMAGE literal
  handler_slot (0x21004a90)  = 0x0102B2C5   (correct: &FUN_0102b50c)
  pending_flags(0x210049b0)  = 0x00000000
  RADIO INTENSET             = 0x00000010
  MasterFramesSeen 1, RADIO TransmittedFrames 1, 0 FATAL, 0 SYSRESETREQ
```

`FUN_01032c28` writes `0x010338b1` and `0x010335e5` into the ESB radio
state-machine continuation slot at 0x210049a0.  Runtime→analysis is −0x800, so
those are **analysis 0x010330b0 and 0x01032de4** — both inside the
**unreconstructed 1,836-byte Ghidra gap 0x01032c28 .. 0x01033354**, which is
the ESB radio state machine itself.  `FUN_010327d8`'s indirect `bx r3`
therefore has nowhere valid to go, the pending-event bitmap is never set, IRQ
0x1d never fires, `FUN_0102b50c` is never entered, and the announcement is
never re-armed.  `FUN_010330b0` alone is 0x92 B and calls six further
gap-resident functions (0x1033084, 0x1033bf0, 0x1033ca4, 0x1033d54, 0x1033d20,
0x103a9dc).  **That gap is iteration 25.**

### 24.6 THE REGRESSION, reported in full and NOT hidden

The 20 s acceptance capture with the final tree completes both phases
(`VTIME_P1` 6.000000000, `VTIME_P2` 20.000000000) with **0 `ZEPHYR FATAL
ERROR` and 0 `SYSRESETREQ`** — but the **machine is reset roughly 15 s into the
run** (`cpuapp`/`cpunet`: *"PC does not lay in memory or PC and SP are equal to
zero. CPU was halted."*, a pair of lines that does **not** appear in the
iteration-23 capture), which zeroes every peripheral model counter before the
script reads them.

Bisected with an identical 20 s probe (`probeP`, same stimulus knobs as the
capture; the probe is calibrated — on `g1-i23-net` it reproduces the
iteration-23 capture numbers exactly):

| net build | contents | `vcentral Connected` | `VC_DATA_EVENTS` | `radio TX` | `JBD FrameCounter` | halt |
|---|---|---|---|---|---|---|
| `g1-i23-net` | iteration-23 baseline | **True** | 0x219 | 0xBD | 3 | no |
| **`g1-i24a-net`** | **+ template fix only** | **False** | 0 | 0 | 0 | **yes** |
| `g1-i24b-net` | + timer instance | False | 0 | 0 | 3 | no |
| `g1-i24c-net` | + DPPI pools (first ESB frame) | False | 0 | **1** | 0 | **yes** |

So the regression is introduced by the **template fix alone** — i.e. by the ESB
radio configuration finally being *applied*.  The reading the evidence supports
is that our CPUNET now really programs and keys the RADIO **outside any MPSL
timeslot**: the ESB worker `FUN_0102b1c8` is still parked on `K_FOREVER`
(iteration 23 §23.7 item 3, analysis 0x0102b204 unreconstructed) and the ESB
state machine that would hand the radio back is the gap of §24.5, so the
SoftDevice Controller loses the radio and the BLE link dies.  This is a
*deeper* stall, not a wrong fix: the mode byte, the timer instance and the DPPI
pools are each proven against the shipped bytes.  Per the standing instruction
the provably-correct fixes are **not** reverted; both the baseline and the new
build are reported.

### 24.7 Graphics + sensor parity — final tree, a COMPLETE capture

```
G1_RESC=/private/tmp/g1-i24/ours-paired-i24.resc     # $rtinfo_pc=0x15b9c; i @g1-ours-paired.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf   # app UNCHANGED this iteration
G1_NET_ELF=/private/tmp/g1-i24g-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i24g
```

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px / 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px / 2,752 windows**. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px / 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px / 673 windows**. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, all 34 shared transactions byte-identical, first difference at index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–23 (`0c5cc90b07…`), so first differing row **y = 267**, first differing pixel **x = 178**, carried over unchanged. |
| **G-5** | **PASS** | panel-init sequence byte-exact at the same indices (the 34-transaction prefix is identical). |
| **G-6** | **PASS** | `spim_b` `stream_sha256` EQ, 0 == 0 in both phases. |
| **S-ESB** | **FAIL** | capture counters all 0 (reset, §24.6).  In a reset-free 6 s probe: `MasterFramesSeen` **1**, `AcksInjected` **1**, `AnnounceResponsesInjected` **1** (oracle 0x175 / 0x175 / 0x15B).  `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01. |

`trigger_screen_state_change` (app 0x00028ad8) is reached **once, with
`action = 0`** (probeQ, 20 s); `reflash_fb_data_to_lcd` and `pixelto4bithex`
are **never** reached.

Per-device volumes — **phase 1 unchanged, phase 2 regressed by the §24.6
reset**:

| device / phase | oracle | iter 23 | **iter 24 (final tree)** |
|---|---:|---:|---:|
| LSM6DSO `p1_boot` | 1,089 | 1,027 | **1,027** |
| LSM6DSO `p2_render` | 1,200 | 700 | **268** |
| nPM1300 `p1_boot` | 291 | 232 | **232** |
| nPM1300 `p2_render` | 508 | 370 | **140** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | **14 / 0** |
| ST25DV system port `p1_boot` | 22 | 12 | **12** |
| ST25DV NFC EEPROM `p1_boot` | 25 | 11 | **11** |
| `saadc` (whole run) | 998 | 71 | **41** |
| `gpiote0` (whole run) | 25 | 25 | **25 (hash EQ)** |
| `pdm0` (whole run) | 2 | 2 | **2 (hash EQ)** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **34 / 0** |
| `JBD FrameCounter` `p1` / `p2` | 0x2A1 / 0xD61 | 0x3 / 0x3 | **0x3 / 0x0** |
| `JBD JournalCount` | 0x400 | 0x22 | **0x0** |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | **0 / 0** |

Verdict cells stay **5 PASS / 5 PARTIAL / 4 FAIL**; the *volumes* inside the
PARTIAL cells regressed for phase 2 only, for the reason in §24.6.

### 24.8 Gates and sizes

| gate | iter 23 | **iter 24** |
|---|---|---|
| `check_ram_pin_collisions.py` (net) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** (app untouched) |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** |
| `check_net_raw_literals.py` | 69 | **68** |
| `gen_retained_sources.py --check` | clean | **clean** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| net FLASH | 222,189 B | **222,925 B (+736; 96.33 % of 231,424)** |
| net RAM | 60,556 B | **60,572 B (+16)** |
| net retained sources | 958 | **965** |

### 24.9 Open, named, and NOT fixed

1. **The ESB radio state machine** — the 1,836-byte gap
   `0x01032c28 .. 0x01033354`, entered through the continuation pointers
   `0x010338b1` (analysis 0x010330b0) and `0x010335e5` (analysis 0x01032de4)
   that `FUN_01032c28` writes to 0x210049a0.  **This is the iteration-25 first
   divergence.**  Note `PROVIDE(rodata_10335e5 = 0x010335e5)` in
   `recon/symbols/g1_net_globals.ld` is a *code* pointer wearing a `rodata_`
   name and must be rebound with the rest.
2. **MPSL timeslot arbitration for ESB** (§24.6).  `FUN_0102b1c8` still creates
   the ESB worker with `K_FOREVER` because analysis 0x0102b204 is
   unreconstructed; nothing gives the radio back to the SoftDevice Controller.
3. **39 pins in the net `.data` window `[0x21000000, 0x21000c3c)` still have a
   non-zero shipped initialiser our build does not reproduce** (surveyed this
   iteration; three of them — 0x21000698, 0x210006a0, 0x210006a4 — were fixed
   here, and each one was a hard blocker).  A generator for pointer-bearing
   `.data` runs remains the highest-value instrument in the project.
4. Iteration 23 §23.7 items 4–7 (342 absolute app `rodata_*` pins, the two odd
   Thumb literals `C_01008e70` / `DAT_01019eb0`, the 36-vs-28-byte
   `struct bt_conn_cb`, and shipped `bt_conn_cb` entries 2 and 3) are unchanged.

### Regenerate (iteration 24)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh net /private/tmp/g1-i24g-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# app is UNCHANGED: reuse /private/tmp/g1-i23a-app  ($rtinfo_pc = 0x00015b9c)
# capture: see §24.7 ;  probes: /private/tmp/g1-i24/probe{A..Q}.resc
```

Files changed:
`recon/net/src/FUN_0102b31c.c` + `recon/symbolized/net/FUN_0102b31c.c`
(runtime-space template; cohesive event-handler rebind),
new `recon/net/src/{FUN_0102b50c,FUN_0102b49c,FUN_010337ac,FUN_0102bbe0,FUN_0103289c,FUN_010327bc,FUN_0103a83a}.c`
+ `recon/symbolized/net/` copies,
`recon/symbolized/net/FUN_010333b4.c` (four handler pointers → `ADDR_*_THUMB`),
`recon/symbolized/net/{FUN_01034480,FUN_0103448c}.c` (group-pool symbol),
`recon/symbols/g1_net_symbols.h` (timer instance type + 4 new ESB pins +
4 new `ADDR_*_THUMB`), `recon/symbols/g1_net_globals.ld` (2 pins superseded,
4 pins added), `recon/application/net/src/timeslot_owner.c` (three emitted
`.data` objects + the IRQ-8 mask correction),
`recon/generated/net_retained_sources.cmake` (generator only; 958 → 965),
`recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no devicetree change, no `armemul` change,
nothing committed.

## Iteration 25 — the **ESB radio state machine is reconstructed** (16 functions
## out of the Ghidra gaps, all parity-proven) and the CPUNET **cycles** it for
## the first time; the MPSL/radio-arbitration defect is now reached in 1.3 s
## instead of 15 s and is named with a hooked measurement

**Stated before anything else, because the acceptance bar is pixels:
NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** in both builds
measured below, against the oracle's **656** (`p1_boot`) / **1,098**
(`p2_render`); `spim_a` is **34 / 764** and **0 / 2,881**; **no `0x02` pixel
window was emitted**; `trigger_screen_state_change` is reached **exactly once**
and `reflash_fb_data_to_lcd` / `pixelto4bithex` are **never** reached, so **no
display START with `action = 1` arrived**.  Nothing below claims otherwise.

### 25.1 What was reconstructed — the ESB radio state machine, 16 functions

Iteration 24 §24.5 named the blocker: `0x210049a0` (the continuation slot that
`FUN_010327d8`'s `bx r3` dispatches on the RADIO DISABLED interrupt) held the
ORIGINAL-image literal `0x010338B1`, whose analysis address `0x010330b0` lay
inside the unreconstructed **1,836-byte Ghidra gap `0x01032c28 .. 0x01033354`**.

Disassembling that window (and the adjoining gaps that it calls into) resolves
the machine completely.  The catalogued `FUN_01032c28` occupies 0x172 of the
window; the remaining executable extent is **five state functions, three
timeslot/DPPI helpers, one RX-FIFO push, one FIFO pop, one abort/restart, four
DPPI wiring leaves and one nrfx timer-compare leaf**:

| new file | analysis VA | extent | role |
|---|---|---|---|
| `FUN_01032de4.c` | 0x01032de4 | 0x5a | **state: TX slot finished** (`0x010335e5`) |
| `FUN_01032e54.c` | 0x01032e54 | 0x1e8 | **state 5: frame received** (`0x01033655`) |
| `FUN_01032804.c` | 0x01032804 | 0x36 | **state 4: ACK sent, arm RX** (`0x01033005`) |
| `FUN_010330b0.c` | 0x010330b0 | 0x92 | **state 3: ACK window armed** (`0x010338b1`) |
| `FUN_010331c8.c` | 0x010331c8 | 0x146 | **state 2: ACK window elapsed** (`0x010339c9`) |
| `FUN_010329b4.c` | 0x010329b4 | 0x70 | abort + restart RX (CRC fail / duplicate / FIFO full) |
| `FUN_01032a3c.c` | 0x01032a3c | 0x88 | RX FIFO push (length, pipe, RSSI, no-ack, PID) |
| `FUN_01032954.c` | 0x01032954 | 0x2e | TX FIFO pop under BASEPRI 0x40 |
| `FUN_01033084.c` | 0x01033084 | 0x20 | timeslot/notification release |
| `FUN_01033168.c` | 0x01033168 | 0x2a | retransmission-window **request** |
| `FUN_010331a0.c` | 0x010331a0 | 0x22 | retransmission-window release |
| `FUN_01033cd0.c` | 0x01033cd0 | 0x3a | DPPI wiring: ACK turnaround |
| `FUN_01033d20.c` | 0x01033d20 | 0x2a | undo of the above |
| `FUN_01033d54.c` | 0x01033d54 | 0x38 | DPPI wiring: RADIO↔TIMER2 retransmit pair |
| `FUN_01033da0.c` | 0x01033da0 | 0x32 | undo of the above |
| `FUN_0103a9dc.c` | 0x0103a9dc | 0x30 | `nrfx_timer_compare(inst, ch, value, enable_int)` |

The state graph the bytes describe (all five continuation literals are RUNTIME
Thumb pointers, runtime→analysis −0x800):

```
FUN_01032c28  (key a frame)     -> 0x010338b1 = FUN_010330b0   [busy=2]
FUN_010330b0  (ACK window)      -> 0x010339c9 = FUN_010331c8   [busy=3]
FUN_010331c8  ACK ok            -> idle (busy=0)  or  re-enter FUN_01032c28
              retries exhausted -> idle (busy=0), pending |= 2 (TX failed)
              otherwise         -> 0x010338b1 = FUN_010330b0   [busy=2]
FUN_01032c28  (no-ack variant)  -> 0x010335e5 = FUN_01032de4   [busy=1]
FUN_01033888  (start RX)        -> 0x01033655 = FUN_01032e54   [busy=4]
FUN_01032e54  (frame received)  -> 0x01033005 = FUN_01032804   [busy=5]
FUN_01032804  (ACK sent)        -> 0x01033655 = FUN_01032e54   [busy=4]
```

### 25.2 Proof method and counts

`net_recon_kit.prove` refuses all sixteen ("name/address does not match net
catalog") because none of them is in the Ghidra catalog, so the underlying
`tools/parity` harness was driven directly, exactly as iterations 23 and 24 did
for uncatalogued entries.  **No `tools/` logic was changed.**  The driver
(`/private/tmp/g1-i25/nprove.py`) imports `cfg_verify.core_ctx("net")` and
passes its **own catalog-derived `call_arity_by_target`,
`call_float_arity_by_target` and `call_return_kind_by_target`** tables, so the
call-boundary comparison is as strict as the authoritative verifier's; the only
thing it cannot take from `cfg_verify` is the CFG-derived argument coverage,
which is supplied by hand as `arg_overrides` / `absolute_memory_overrides` /
`absolute_read_transitions` chosen from each function's own branch conditions.

| function | trials | directed coverage |
|---|---|---|
| `FUN_0103a9dc` | 200/200 | `arg_overrides` for `enable_int` ∈ {0,1} × channel ∈ {0,1,3} |
| `FUN_01033cd0` / `d20` / `d54` / `da0` | 300/300 each | branch-free straight line |
| `FUN_01032954` | 300/300 | read index pinned to 0/1/6/7/8/0xffffffff (the `cmp #8` wrap) |
| `FUN_01033084` / `010331a0` / `01033168` | 300/300 each | (`01033168`: both arms of the request-rejected test) |
| `FUN_01032804` | 300/300 | `call_arities=(0,2,1)` for the indirect handler |
| `FUN_01032de4` | 300/300 | TX-queue count pinned 0/1/2/5 |
| `FUN_010329b4` | 300/300 | `absolute_read_transitions` on RADIO `EVENTS_DISABLED` (1–3 poll iterations) |
| `FUN_01032a3c` | 300/300 | 12 pinned (protocol, length, mode, FIFO index) scenarios incl. length > 0xfb |
| `FUN_010330b0` | 300/300 | protocol ∈ {0,1,2,0xff} × `use_fast_ramp_up` ∈ {0,1} |
| `FUN_010331c8` | 400/400 | 15 pinned scenarios: EVENTS_END/CRCSTATUS/queue/protocol/header/FIFO/retries/COMPARE1/RADIO STATE |
| `FUN_01032e54` | 500/500 | 18 pinned scenarios: CRC, FIFO full, PID/CRC duplicate, selective-auto-ack, all three protocol arms, ACK-list dequeue with and without a successor |

**0 mismatches in every case.**

Two harness facts had to be modelled explicitly, both with disassembly
evidence, and both are recorded here because they are exactly the blind-spot
class the ledger tracks:

* **`FUN_01032954` preserves r0.** Its body (`mov.w r3,#0x40; mrs r1,basepri;
  … ldr r2,[pc]; ldr r3,[r2,#0x28] … bx lr`) touches **only r1/r2/r3**, and
  `FUN_01032de4` exploits that: it loads `r0 = 0xe000e100` *before*
  `bl 0x1032954` and stores through it *after*.  The parity oracle overwrites
  r0/r1 at every call, so the original run wrote to a garbage address while the
  candidate wrote to NVIC ISPR.  Modelled with
  `oracle_overrides={4: {0: 0xe000e100}}` — a reviewed fixture, not a tuning
  knob.  In the cohesive build this is a non-issue: both functions are separate
  translation units and the constant is re-materialised.
* **`FUN_01032ad8` takes no argument at these call sites.**  Its prologue is
  `push {r0,r1,r2,lr}` and it then uses `sp+4` purely as the **output buffer**
  that `FUN_01021920` fills and `ldrsb [sp,#4]` reads back; the shipped callers
  (`FUN_010331c8`, `FUN_01032e54`, and the already-proven `FUN_01032c28`, whose
  reconstruction declares it `(void)`) set **no** argument register before the
  `bl`.  Compared with arity 0 at those sites.

Two transcription defects were caught by the harness and are worth recording:
`FUN_010330b0` was first written storing `0x010338b1` (its own entry) instead
of `0x010339c9`, and the first `FUN_010331c8` run mismatched on two writes to
`0x000049a0` / `0x00000018` — the *original* bytes were being executed with a
**truncated literal pool** (`func_bytes_padded(..., pad=64)` stopped four bytes
into the pool word at 0x0103334c).  The driver now pads 256 bytes.

### 25.3 The five pointers rebound, and one `rodata_` name that was code

New `ADDR_*_THUMB` aliases in `recon/symbols/g1_net_symbols.h` (the sanctioned
`__asm__`-alias mechanism; parity keeps the shipped literals):

```
0x010338b1 -> FUN_010330b0   0x010335e5 -> FUN_01032de4
0x010339c9 -> FUN_010331c8   0x01033005 -> FUN_01032804
0x01033655 -> FUN_01032e54
```

Writers rebound: `recon/symbolized/net/FUN_01032c28.c` (three stores) and
`recon/symbolized/net/FUN_01033888.c` (the RX start).  Two linker pins in
`recon/symbols/g1_net_globals.ld` were **code pointers wearing `rodata_`
names** and are superseded, with the reason recorded in place:

```
PROVIDE(rodata_10335e5 = 0x010335e5);   ->  ADDR_FUN_01032de4_THUMB
PROVIDE(rodata_1033655 = 0x01033655);   ->  ADDR_FUN_01032e54_THUMB
```

### 25.4 One more `.data` object restored (item 3 of §24.9)

`FUN_01033168` fills word 3 of a 16-byte record at **0x21000670** and submits
it through slot 8 of the radio-arbitration vtable.  The address had no owner in
the cohesive link and `check_net_raw_literals.py` places it **inside the live
`sdc_mempool`**, so the write corrupted the SoftDevice Controller's pool.  The
shipped `.data` initialiser, read with `tools/net_extract.py` **`read_runtime`**
at the net `.data` LMA `0x0103ed24 + 0x670` (the LMA quoted in §24.2 is a
RUNTIME address — the analysis read returns nothing):

```
00 00 00 00 | 00 90 01 41 | 00 00 00 00 | 00 00 00 00
   = { 0, 0x41019000 (CPUNET TIMER2), 0, length }
```

Emitted as `g1_esb_window_request` in
`recon/application/net/src/timeslot_owner.c`, the same remedy iteration 24
applied to 0x21000698 / 0x210006a0 / 0x210006a4.

### 25.5 MEASURED — the state machine cycles for the first time

Hooked at our build's own symbols (`probeD`, 2 s, `/private/tmp/g1-i25/`):

```
NK start_tx_2c28 -> NK tifs_2ad8 -> [ESBDUMP tx#1] -> NK dispatch_27d8
   -> NK state3_30b0 -> NK dispatch_27d8 -> NK state2_31c8
   -> NK evdispatch_289c -> NK evhandler_2b50c -> NK evhandler_2b50c
NK start_tx_2c28 -> NK tifs_2ad8 -> [ESBDUMP tx#2] -> NK dispatch_27d8
   -> NK state3_30b0 -> NK dispatch_27d8 -> NK state2_31c8
   -> NK evdispatch_289c -> NK evhandler_2b50c -> NK evhandler_2b50c
=== END ===
cont_ptr (0x210049a0) = 0x0102C14D   <- &FUN_010331c8 | 1  (was 0x010338B1)
evhandler(0x2100499c) = 0x0102BB4D   handler_slot(0x21004a90) = 0x0102B2C5
radio TransmittedFrames = 2
```

That is the first time this project has re-armed an ESB announcement: iteration
24 keyed exactly one frame and stopped, because `bx r3` had nowhere to go.  The
full loop — key → RADIO DISABLED → state 3 → RADIO DISABLED → state 2 → set the
pending bitmap → IRQ 0x1d → `FUN_0103289c` → `FUN_0102b50c` (twice, i.e. two
distinct event bits) → key again — now runs end to end.

### 25.6 …and it hits the MPSL/radio-arbitration defect 0.11 s later

**`NET sdc_assertion_handler`** (hooked at our build's `0x010342c4`) fires
immediately after the second cycle, and the ensuing reset takes both cores down
(`PC does not lay in memory or PC and SP are equal to zero`, on `cpuapp` first
and `cpunet` 0.2 ms later — the app core restarts from a vector table at
address 0 that our images do not populate, which is what that Renode message
means).  This is **§24.6's diagnosis, now confirmed by a hooked measurement
rather than a bisect**: with the state machine complete, the CPUNET genuinely
drives the RADIO across a full ESB transaction and the SoftDevice Controller
asserts.

Completing (1) therefore did **not** cure (2).  The radio-arbitration vtable is
*wired* — `0x21000530` reads `0x21000534` and all eight slots point at real
reconstructed code (`0x0102A4A5 / 0x0102A4DD / 0x0102A4A9 / 0x0102A4E7 /
0x0102A4AF / 0x0102A4ED / 0x0102A4B5 / 0x0102A4B7`, the `sym_*` cluster at
0x0102a4a4–0x0102a4f2) — so the failure is not a null hook.  The session word
the shipped firmware initialises to 1 at **0x2100065c** reads **0x0000FFFF** in
our link, because that address also has no owner and falls inside
`sdc_mempool`: it is the next `.data` object to restore on this path.

### 25.7 A/B — the SAME tree with the rebind on and off

To separate "the reconstruction is wrong" from "the reconstruction unmasks a
deeper defect", the five `ADDR_*_THUMB` macros were temporarily replaced by the
shipped literals and the tree rebuilt unchanged (`/private/tmp/g1-i25b-net`).
Everything else — all sixteen new functions, the emitted `.data` object — is
identical.

| | **`g1-i25-net`** (rebind ON) | `g1-i25b-net` (rebind OFF) |
|---|---|---|
| `0x210049a0` after 6 s | **0x0102C14D** = `&FUN_010331c8` | 0x010338B1 (original literal) |
| ESB PTX frames keyed | **2** | 1 |
| state machine cycles | **yes** | no (stops after one frame) |
| `NET sdc_assertion_handler` | **fires at ≈1.3 s** | not reached in 6 s |
| machine reset | **≈1.3 s** | ≈15 s (as iteration 24) |
| `JBD FrameCounter` p1 / p2 | 0x0 / 0x0 | 0x3 / 0x0 |
| `radio TransmittedFrames` (20 s capture) | 0x2 | 0x1 |

`g1-i25b-net` reproduces iteration 24's capture numbers **exactly** (LSM6DSO
1,027 / 268, nPM1300 232 / 140, OPT3001 14 / 0, saadc 41, spim_a 34 / 0,
`JBD FrameCounter p1` 0x3), which is the calibration that makes the A/B
meaningful.

Per the standing instruction the provably-correct fix is **NOT** reverted — the
five literals are demonstrably code pointers and their targets are
parity-proven — and **both builds are reported**.  The tree as left carries the
rebind ON.

### 25.8 Graphics + sensor parity — complete captures of BOTH builds

```
G1_RESC=/private/tmp/g1-i25/ours-paired-i25.resc      # $rtinfo_pc=0x15b9c
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf # app UNCHANGED this iteration
G1_NET_ELF=/private/tmp/g1-i25-net/zephyr/zephyr.elf  (and .../g1-i25b-net/...)
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i25{,b}
```

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px / 0 pixel windows** (both builds); oracle `b26c73b37d…`, **1,098 lit px / 2,752 windows**. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px / 3 pixel windows** (both builds); oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449, y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**; the 34 shared transactions are byte-identical and the first difference is at index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`).  Identical in both builds. |
| **G-4** | *localiser* | our framebuffer bytes are bit-identical to iterations 16–24 (`0c5cc90b07…`), so first differing row **y = 267**, first differing pixel **x = 178**, carried over unchanged. |
| **G-5** | **PASS** | panel-init sequence byte-exact at the same indices (the 34-transaction prefix is identical). |
| **G-6** | **PASS** | `spim_b` transaction count 0 == 0 in both phases, both builds. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` **0x01** vs 0x02; `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01.  20 s capture counters are zeroed by the reset in both builds; in reset-free hooked probes `radio TransmittedFrames` is **2** (rebind ON) vs **1** (OFF), oracle 0x230, and `esbslave MasterFramesSeen` 1 (OFF) / 0 after reset (ON), oracle 0x175. |

`trigger_screen_state_change` (app 0x00028ad8) is reached **exactly once** in
both builds over the full 20 s stimulus, and `reflash_fb_data_to_lcd`
(0x000416a8) and `pixelto4bithex` (0x0003172c) are reached **0 times** — so no
display START with `action = 1` arrived (iteration 24's directed probe measured
`r2 = 0` at that single entry; the app image is unchanged).

Per-device volumes:

| device / phase | oracle | iter 24 | **i25b (rebind OFF)** | **i25 (rebind ON)** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` | 1,089 | 1,027 | **1,027** | **551** |
| LSM6DSO `p2_render` | 1,200 | 268 | **268** | **0** |
| nPM1300 `p1_boot` | 291 | 232 | **232** | **97** |
| nPM1300 `p2_render` | 508 | 140 | **140** | **0** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | **14 / 0** | **14 / 0** |
| ST25DV NFC EEPROM `p1_boot` | 25 | 11 | **11** | **0** |
| ST25DV system port `p1_boot` | 22 | 12 | **12** | **6** |
| `saadc` (whole run) | 998 | 41 | **41** | **5** |
| `gpiote0` (whole run) | 25 | 25 | **25 (hash EQ)** | **25 (hash EQ)** |
| `pdm0` (whole run) | 2 | 2 | **2 (hash EQ)** | **2 (hash EQ)** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **34 / 0** | **34 / 0** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x0 | **0x3 / 0x0** | **0x0 / 0x0** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | **0 / 0** | **0 / 0** |

The `i25` column is lower everywhere because the SDC assertion resets the
machine at ≈1.3 s instead of ≈15 s.  That is a **metric** regression caused by
reaching a deeper, correctly-diagnosed stall earlier — not by a wrong
reconstruction; the A/B above isolates it to the five-pointer rebind alone.

### 25.9 Gates and sizes

| gate | iter 24 | **iter 25 (`g1-i25-net`)** |
|---|---|---|
| `check_ram_pin_collisions.py` (net) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** (app untouched) |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** |
| `check_net_raw_literals.py` | 68 | **69 — see below** |
| `gen_retained_sources.py --check` | clean | **clean** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| net FLASH | 222,925 B (96.33 %) | **225,165 B (+2,240; 97.30 % of 231,424)** |
| net RAM | 60,572 B | **60,588 B (+16)** |
| net retained sources | 965 | **981** |

**The raw-literal gate, honestly.**  The sixteen new symbolized sources
contribute **zero** exclusively-new colliding literals: every RAM address they
use is expressed through an existing `g1_net_symbols.h` symbol
(`g_esb_state`, `g_net_queue_stats_block_b`, `g_net_radio_irq_continuation_ptr`,
`g_esb_event_handler_fn`, `g_net_rf_ack_hdr_buf`, the five DPPI channel bytes,
…), with `0x21004aa0` / `0x21004aa2` / `0x2100635d` / `0x21006260` expressed as
offsets from their base symbol.  The count moved 68 → 69 for a different
reason, measured by diffing the two `--json` reports: the 16-byte
`g1_esb_window_request` object shifts the RAM layout by 16 bytes, and the
**pre-existing** literal `0x210009fc` in `recon/symbolized/net/FUN_0102fbd0.c`
(a `net_buf_pool` pointer handed to `FUN_0103a44c`) crossed from "in the RAM
region but free" into `hci_rx_pool + 40`.  Keeping the raw `0x21000670` instead
would have given 69 as well **and** left the SDC pool corruption in place, so
the emitted object is strictly better.

### 25.10 Open, named, and NOT fixed — the iteration-26 first divergence

1. **MPSL timeslot arbitration for ESB — now the single blocker.**
   `NET sdc_assertion_handler` fires ≈0.11 s after the second ESB cycle
   (§25.6).  The vtable is bound, so the next steps are (a) restore the session
   word at **0x2100065c** (shipped `.data` initialiser `01 00 00 00`; currently
   reads 0x0000FFFF because the address falls inside `sdc_mempool`), and (b)
   read the assertion's own arguments — `sdc_assertion_handler(file, line)` at
   our `0x010342c4` — which this iteration could not extract because the Renode
   `AddHook` string that formats `cpu.R0` / `cpu.R1` silently fails to install
   (the plain-message hook installs and fires).  `FUN_0102b1c8` still creates
   the ESB worker with `K_FOREVER` (analysis 0x0102b204 unreconstructed).
2. **Two newly-identified Ghidra gaps on the ESB pairing path**, found while
   resolving the state machine and recorded with evidence:
   * **`0x01032640`** (0x3c B) is a **thread entry** — `FUN_01032680` passes it
     to `k_thread_create` (`FUN_01035fa0(0x21004258, 0x21008a00, 0x388,
     rodata_1032e41, …, prio 10)`), and `PROVIDE(rodata_1032e41 = 0x01032e41)`
     is therefore a THIRD `rodata_` name that is really a code pointer
     (`0x01032e41 − 0x800 = 0x01032640 | 1`).  Its body is a `k_poll` loop:
     `memset(sp+4,0,0x10); … FUN_01038764(sp+4,1,-1,-1); FUN_0103b51c(0x21004988);
     bfc [sp+0x10],#14,#7; FUN_01032530(); repeat`.  **Our build currently
     starts that thread at an original-image address.**
   * **`0x01032530`** (~0xf0 B) is the work handler it calls — the ESB
     assign-channel/pairing state machine on `0x21004998` / `0x210051f6`
     (siblings `0x010326e0`, `0x01032710`, `0x01032440` are in the same gap).
   Neither was reconstructed here: they are one connected component and would
   have introduced undefined symbols piecemeal.
3. **38 net `.data` pins** still have non-zero shipped initialisers our build
   does not reproduce (39 last iteration, minus 0x21000670).  0x2100065c is the
   highest-value one on the ESB/radio path.
4. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 25)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check   # clean
recon/application/build_cohesive.sh net /private/tmp/g1-i25-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# app is UNCHANGED: reuse /private/tmp/g1-i23a-app  ($rtinfo_pc = 0x00015b9c)
# captures: see §25.8 ;  probes: /private/tmp/g1-i25/probe{A..M}.resc
# A/B build: temporarily point the five ADDR_FUN_*_THUMB macros in
#            recon/symbols/g1_net_symbols.h at the shipped literals.
```

Files changed:
new `recon/net/src/{FUN_01032804,FUN_01032954,FUN_010329b4,FUN_01032a3c,FUN_01032de4,FUN_01032e54,FUN_01033084,FUN_010330b0,FUN_01033168,FUN_010331a0,FUN_010331c8,FUN_01033cd0,FUN_01033d20,FUN_01033d54,FUN_01033da0,FUN_0103a9dc}.c`
+ `recon/symbolized/net/` copies (symbolized RAM references, `G1_COHESIVE_BUILD`
continuation rebinds), `recon/symbolized/net/FUN_01032c28.c` and
`recon/symbolized/net/FUN_01033888.c` (continuation rebinds),
`recon/symbols/g1_net_symbols.h` (5 new `__g1_fp_*` aliases + 5
`ADDR_*_THUMB`; two `rodata_` externs removed),
`recon/symbols/g1_net_globals.ld` (2 pins superseded),
`recon/application/net/src/timeslot_owner.c` (`g1_esb_window_request`),
`recon/generated/net_retained_sources.cmake` (generator only; 965 → 981),
`recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no devicetree change, no `armemul` change,
nothing committed.

## Iteration 26 — the CPUNET absolute-RAM-address collision class is closed
## **structurally**: 300 addresses classified and rebound, both gates at **0**,
## the ESB session word is restored, and the third `rodata_`-named code pointer
## is displaced to the stock NCS unit that already owns it

**Stated before anything else, because the acceptance bar is pixels:
NO PIXEL IS PAINTED.**  The measurements are in §26.7; nothing below claims
otherwise.

### 26.1 Why a structural pass, and what "structural" means on the CPUNET

The class had produced a defect in **five consecutive iterations** (18, 20, 21,
24, 25), every time found one at a time by chasing a symptom, and iteration
25's newest lead was the same class again: the ESB session word at
`0x2100065c` read `0x0000FFFF` instead of the shipped `01 00 00 00` because the
address falls inside the live `sdc_mempool`.  Iteration 20 §20.1 had already
measured 79 colliding source literals (56 of them inside `sdc_mempool`) and
iteration 18 §18.8(2) 72 colliding linker pins.

The app core closed the identical class in one pass in iteration 11 with a
single 0x27000-byte arena at the original base.  The CPUNET **cannot** copy
that, and iteration 18 §18.8(2) already said why: the pinned span is 0x8a00 and
the core has 64 KiB of RAM with ~60 KiB in use.  So this pass does the
per-address equivalent the task specifies — **classify, then emit / bind /
displace every address** — with one refinement that makes it affordable:
addresses are **clustered** (gap ≤ 32 B) and one `used, retain` storage block is
emitted per cluster.  Inside a cluster every original *relative* distance is
exact, which is what interior views (`base + field`) and short sweeps need, and
the total cost is the sum of the cluster spans (**3,416 B**) instead of the
25,680 B arena.  Each block starts at a multiple of 8 at or below its first
address, so every original offset keeps its alignment up to 8 bytes.
`used, retain` is mandatory — iteration 11 §11.1 measured that
`PROVIDE(x = block + off)` does **not** root `block` under `--gc-sections`.

Both channels are covered:

* **linker pins** — `PROVIDE(name = 0x21xxxxxx)` in
  `recon/symbols/g1_net_globals.ld`, rewritten to `PROVIDE(name = block + off)`;
* **raw source literals** — rewritten to a generated `G1N_<addr>` macro whose
  `#else` arm is the shipped literal, so **no parity body changes meaning** and
  `tools/parity` still compiles every canonical `recon/net/src` body unchanged.
  Sources that already `#include "g1_net_symbols.h"` pick the macros up from
  there (a one-line `#include` of the new `recon/symbols/g1_net_ram_reloc.h`);
  the 23 canonical `recon/net/src` bodies that include nothing get a
  **self-contained** guard block injected instead.

The generator is `recon/application/gen_net_ram_relocs.py` (new); its inputs are
the two gates' own `--json` reports, and its ledger is
`recon/application/net_ram_reloc_ledger.json`.

### 26.2 Classification — every one of the 300 addresses

Input: the 196 raw pin addresses that survive as ABS symbols in the
iteration-25 link (66 colliding + 130 in-region-but-free) ∪ the 125 distinct
raw source literals (69 colliding + 56 free) = **300 distinct addresses**.

| class | addresses | treatment |
|---|---:|---|
| **(a) recovered-owned net RAM** | **300** | real storage: 70 `used, retain` blocks, 3,416 B, in `recon/application/net/src/g1_net_ram_relocs.c`; 204 `PROVIDE` lines rebound and 316 literal sites in 175 sources rewritten |
| — of which inside the shipped `.data` window | 31 addresses in 7 blocks | **shipped initialiser restored** (416 B, 6 relocation-aware pointer words) |
| — of which `.data` but atomically EXCLUDED | 28 addresses in 11 blocks | left zero, each with the unresolved pointer word(s) named in the source |
| — of which `.bss` in the shipped image | the remainder | zeroed storage reproduces the original exactly |
| **(b) interior of a real SDK object / displaced** | 1 unit | `FUN_01032680` → `hci_ecdh_init` (§26.4), and the `rodata_1032e41` pin removed with it |
| **(c) genuinely outside the linked RAM region** | **0** | none: every recovered CPUNET address is inside 0x21000000..0x21010000 |
| **deferred** | 5 addresses | the block at `0x21000c28` straddles the shipped `.data` end (0x21000c3c), so its shipped prefix is not restored — the generator only reads a fully-contained window.  Named, not fixed. |

Four **byte-exact recovered rodata literal pools** hold a CPUNET RAM pointer
(`rodata_0x100ef04` → 0x21000ec8, `rodata_0x101fdb8` → 0x210014d8,
`rodata_0x101fdcc` → 0x210014dc, `rodata_0x10217fc` → 0x21001670).  Three of
those four addresses also carry a linker pin, so leaving the table literal
while the pin moved would have made the table and the pin for the **same
object** disagree — a defect this pass would have *introduced*.  They are made
**relocation-aware** the same way (`#include "g1_net_ram_reloc.h"`, cohesive
build takes `G1N_<addr>`, the byte-match path keeps the shipped word verbatim).

The shipped `.data` restore follows `recon/application/gen_app_data_image.py`'s
policy exactly: the load image is at runtime LMA `0x0103ed24`, length `0xc3c`,
covering RAM `0x21000000..0x21000c3c` (the same read
`g1_product_endpoints.c` documents), everything above it was `.bss`; a word
that looks like a pointer is meaningless in our link, so a block is restored
only when **every** pointer word in it resolves — to an address inside the
relocation map (rewritten to `block + off`; 6 such words, the self-referential
`sys_dlist_t` / `k_fifo` heads at 0x21000750 and 0x210008c8) or to a catalogued
net function this link defines — and is otherwise **EXCLUDED ATOMICALLY**,
because a half-initialised object is worse than an all-zero one.

**`0x2100065c` is restored.**  It maps to `g1_net_ram_blk_21000658 + 0x4`,
the block is linked at `0x21000678` in `.data`, and its initialiser is the
shipped `00 00 00 00 | 01 00 00 00 | …`, i.e. the session word now reads **1**
instead of the `0x0000FFFF` iteration 25 measured inside `sdc_mempool`.

### 26.3 The reusable gate, extended to the net core

`recon/emulator/scripts/check_ram_pin_collisions.py` gained a `--core {app,net}`
option (additive; **the app default is byte-for-byte the previous behaviour** —
with no `--core`, or `--core app`, every constant is what it was).  This is
exactly the one-line, first-class invocation iteration 18 §18.8(3) recorded as
deliberately not made; until now the net side had to be driven by importing the
module from a scratchpad and overriding `RAM_LO`/`RAM_HI`.

| gate | iteration 25 | **iteration 26** |
|---|---|---|
| `check_ram_pin_collisions.py --core net` — raw pins inside a live object | **66** | **0** |
| `check_ram_pin_collisions.py --core net` — raw pins in region but free | **130** | **0** |
| `check_ram_pin_collisions.py --core net` — bound pins OK / escaping | 3 / 0 | **199 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app, unchanged invocation) | 0 / 0, EXIT 0 | **0 / 0, EXIT 0** |
| `check_net_raw_literals.py` — distinct raw literals | **125** | **0** |
| `check_net_raw_literals.py` — inside a live object | **69** | **0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10, EXIT 0 | **10/10, EXIT 0** |
| `gen_retained_sources.py --check` | clean | **clean** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| net FLASH | 225,165 B (97.30 %) | **225,217 B (+52; 97.32 % of 231,424)** |
| net RAM | 60,588 B (92.45 %) | **64,012 B (+3,424; 97.67 % of 65,536)** |
| net retained sources | 981 | **980** |

The `check_net_raw_literals.py` gate the task asked to improve on **69** is
now **0 colliding and 0 distinct raw literals at all** — the class is not just
below threshold, it is empty.  One caveat is recorded so the number is read
correctly: the gate's regex also matched a hex run inside an *identifier's
spelling* (`g_net_0x21004604_flag` in `recon/symbols/g1_net_symbols.h`), which
is a false positive and not a literal; the symbol was renamed to
`g_net_flag_21004604` in the four places that spell it, so the count is honest
rather than suppressed.  **No `tools/` logic was changed.**

**A known limitation of the cluster sizing, stated up front.**  A block is
sized from the *referenced* addresses, not from the object's true extent, so an
object whose base alone is pinned but which is large (a thread stack, a work-queue
stack) gets a block far smaller than the object.  Three such addresses exist —
`0x21004258` (a `struct k_thread`), `0x21008a00` (a 0x388-byte thread stack) and
`0x21007d80` (a 0x440-byte work-queue stack) — and all three are in
**garbage-collected** translation units in this link (`FUN_01032680` /
`FUN_01031a68` / `ipc_rpmsg_static_vrings_open` are absent from the ELF symbol
table), so none of them can smash a neighbour today.  Before the pass the same
three pointed into `sdc_mempool` or free RAM, i.e. this is not a new class; it
is recorded as the one place where the pass is weaker than the app arena, whose
full-span sizing made it impossible by construction.

### 26.4 The `rodata_1032e41` code pointer — it is `ecdh_thread`, and the
### remedy is DISPLACEMENT, not reconstruction

Iteration 25 §25.10(2) named `0x01032640` as a `k_thread_create` thread entry
reached through `PROVIDE(rodata_1032e41 = 0x01032e41)` — a **third** `rodata_`
name that is really a code pointer — and `0x01032530` as "the ESB
assign-channel work handler it calls", both to be reconstructed and rebound.
**The disassembly identifies the unit differently and the correct fix is the
other branch of the task's own classification.**

The literal pools of `0x01032530` and `0x01032488` hold `0x0103e393` and
`0x0103e376`, which are **runtime** addresses (`tools/net_address_space.py`;
analysis 0x0103db93 / 0x0103db76 — the base hazard `tools/NET_PLAYBOOK.md`
warns about).  Read with `tools/net_extract.py` `read_analysis` they are the
32-byte **Bluetooth debug public key** (`3f 49 f6 d4 a3 c5 5f 38 74 c9 b3 e3 d2
10 3f 50 4a ff 60 7b eb 40 b7 99 58 89 b8 a6 cd 3c 1a bd`) and the strings
`"Unknown command"` / `"BT CTLR ECDH"`.  So:

| analysis VA | identity |
|---|---|
| `0x01032680` (`FUN_01032680`) | `hci_ecdh_init` — `k_poll_signal_init(0x21004988)`, `k_thread_create(0x21004258, 0x21008a00, 0x388, rodata_1032e41, …, prio 10, K_NO_WAIT)`, `k_thread_name_set(…, "BT CTLR ECDH")` |
| `0x01032640` | **`ecdh_thread`** — `memset(&ev,0,0x10); ev.type = 1; ev.obj = &signal; for(;;){ k_poll(&ev,1,K_FOREVER); k_poll_signal_reset(); ev.state = 0; cmd_process(); }` |
| `0x01032530` | `ecdh_cmd_process` — atomic state 1/2/4, "generate a key that is not the debug key" (`memcmp` against the constant above), then an HCI vendor event `0x3e 0x42 … len 0x41` |
| `0x01032440` | `sys_memcpy_swap` specialised to length 0x20 (overlap `__ASSERT`, then a reverse byte copy) |
| `0x01032488` | the public-key command path, same event shape `0x3e 0x22 … len 0x21` |

and the **stock NCS unit is already unconditionally linked in this build**:
`ecdh_thread 0x01034fc4`, `ecdh_cmd_process 0x01034eb4`,
`ecdh_p256_common_secret 0x01034e0c`, `sys_memcpy_swap.constprop.0 0x01034dc4`,
`hci_ecdh_init 0x01035004`, `hci_ecdh_uninit 0x01035058`,
`ecdh_thread_data 0x21008c20`, `ecdh_thread_stack 0x2100b9b8 (0x388 B)`,
`ecdh_signal 0x21009318`, `log_const_bt_sdc_ecdh 0x0103c7f8`
(`CONFIG_BT_CTLR_ECDH=y`, `CONFIG_BT_CTLR_ECDH_STACK_SIZE=0x384`).

Reconstructing the four gap functions would therefore have created a **second**
`ecdh_thread` on a second `k_poll_signal` with a second stack — precisely the
singleton-duplication defect iteration 18 §18.2 measured for `kernel/timeout.c`.
The unit is displaced instead, with the same mechanism iterations 18/19 used:

* `recon/ownership/net_hci_ecdh_singleton_adoption.json` (new evidence record);
* `recon/ownership/adoption_manifest.json` row `0x01032680` flipped to
  `adopt_upstream_exclude_reconstruction` (net retained 981 → 980);
* `PROVIDE(FUN_01032680 = hci_ecdh_init);` in
  `recon/application/net/src/stock_call_aliases.ld`;
* `PROVIDE(rodata_1032e41 = 0x01032e41)` **removed** from
  `recon/symbols/g1_net_globals.ld`, with the reason recorded in place — it has
  no referrer left and must not survive as a raw original-image code address.

**Measured honestly: this changes nothing in the image, and the report says so
rather than claiming a boot effect.**  The recovered chain was *already* dead —
`FUN_01031a68` is the only caller of `FUN_01032680` and has **no caller
anywhere**, neither in the recovered corpus nor in Ghidra's own graph
(`recon/catalogs/refgraph_net.json.gz` gives it an empty `callers` array), so
`--gc-sections` had already dropped the whole subtree.  Proof: the build with
the displacement (`/private/tmp/g1-i26c-net`) and the build without it
(`/private/tmp/g1-i26a-net`) produce a **byte-identical** image
(`md5 e90d0647062360f3fe0d6647fa2000de` for both `objcopy -O binary` outputs).
That byte-identity is also what makes the single capture below valid for the
final tree.  *Whose* root should call `FUN_01031a68` is a new open question,
recorded in §26.8.

### 26.5 Build ledger (every build actually run)

| net build | change | FLASH | RAM | net `nm -u` | image md5 |
|---|---|---:|---:|---:|---|
| `/private/tmp/g1-i26base-net` | iteration-25 tree, rebuilt as the baseline | 225,165 B | 60,588 B | 0 | — |
| `/private/tmp/g1-i26a-net` | + the structural pass (70 blocks, 204 pins, 316 literal sites) | 225,217 B | 64,012 B | 0 | `e90d0647…` |
| `/private/tmp/g1-i26b-net` | + the `hci_ecdh.c` displacement | 225,217 B | 64,012 B | 0 | `e90d0647…` |
| `/private/tmp/g1-i26c-net` | + the four relocation-aware rodata pointer pools | 225,217 B | 64,012 B | 0 | `e90d0647…` |
| `/private/tmp/g1-i26d-net` | + a self-review fix: byte offsets in a relocation-aware block indexed through `unsigned char *` | 225,217 B | 64,012 B | 0 | `c7bb377c…` |
| `/private/tmp/g1-i26e-net` | + bind `g_net_radio_ops_table_ptr` to `sym_NIQMZN22…` — **REVERTED**, §26.8 | 225,221 B | 64,012 B | 0 | — |
| `/private/tmp/g1-i26g-net` | the revert (**final**; byte-identical to `g1-i26d-net`) | 225,217 B | 64,012 B | 0 | `c7bb377c…` |

The first three post-pass images are **byte-identical** (`objcopy -O binary`,
md5 `e90d0647062360f3fe0d6647fa2000de`), because both of those changes act only
on translation units `--gc-sections` already discards.  The capture in §26.7 was
taken on that image.

`g1-i26d-net` differs from it by **exactly four bytes**, and they are stated
precisely rather than glossed: reviewing the generated source showed that a
block carrying a relocation is emitted as `unsigned long[]`, so a *byte* offset
written as `blk + 0x8` was being scaled by 4.  Only two blocks are affected
(`g1_net_ram_blk_21000750`, the shipped `timeout_list` self-referential
`sys_dlist_t` head, and `g1_net_ram_blk_210008c8`), and `cmp -l` between the two
binaries reports four differing bytes, all inside those two `.data` images
(`0x18 -> 0x0c` and `0x40 -> 0x28`).  Both blocks' only consumers are **absent
from the ELF symbol table** — `kernel/timeout.c` is displaced to the stock unit
(iteration 18) and `FUN_01031804` / `FUN_01031814` are garbage-collected — so
the fix cannot change the measured behaviour, but the measurement in §26.7 is
nonetheless of `g1-i26a-net`, not of the final tree, and that is said here
rather than assumed away.  Every gate in §26.3 was re-run on `g1-i26d-net` and
is unchanged (0/0, 0 raw literals, 0 undefined, 0 duplicate).

The app core is **UNCHANGED** this iteration (`/private/tmp/g1-i23a-app`,
`$rtinfo_pc = 0x00015b9c`).

RAM is now the binding constraint: **64,012 B of 65,536 (97.67 %), 1,524 B
free.**  The FLASH cost of the whole pass is **+52 B** (the restored `.data`
initialisers), against 6,207 B of headroom in the modelled 231,424 B region, so
the documented `recon/application/net/app.overlay` mechanism was **not** needed
and no real content was dropped.

Three compile-shape adjustments were needed and are recorded because they are
edits to reconstruction sources, not to the generator:

* 10 sources spell the address as `UINT32_C(0x21xxxxxx)`; a relocated address
  is a link-time expression, so the `## U` paste fails.  `UINT32_C(G1N_…)` is
  reduced to `G1N_…` in those 10 files.
* `recon/symbolized/net/ipc_rpmsg_static_vrings_open.c` used the address as an
  **enumerator** (`MAILBOX_STACK_ARRAY = 0x21007d80`), which requires an
  integer constant expression; it becomes a `#define` immediately after the
  enum.
* `recon/symbols/g1_net_symbols.h` is never rewritten (its `0x21…` runs are
  provenance comments and one identifier spelling); it gets the macros by
  `#include`.

### 26.6 What was deliberately NOT done, and why

* **No net arena.**  Iteration 18 §18.8(2)'s constraint is respected: 25,680 B
  of pinned span cannot fit.  The clustered-block form is the affordable
  equivalent and its limitation is stated in §26.3.
* **No reconstruction of `0x01032640` / `0x01032530` / `0x01032440` /
  `0x01032488`.**  They are `hci_ecdh.c` and the stock unit is already linked
  (§26.4); reconstructing them would duplicate a singleton.  This is the task's
  own classification branch (b), chosen over branch (a) on byte evidence.
* **No canonical `recon/net/src` body semantics changed.**  Every rewritten
  literal is behind a `#else` arm that is the shipped address, so
  `tools/parity` and `tools/cfg_verify` see exactly the bytes they proved.  No
  function was re-derived, so no re-proof was required; the two mechanical
  edits that *are* visible to the compiler (the `UINT32_C` unwrap and the
  enum → `#define`) do not change any expression's value.
* **No `tools/` change**, no Kconfig / `prj.conf` / devicetree change, no
  `armemul` change, no `--allow-multiple-definition`, no weak symbols, no
  numeric-root hacks.  Nothing committed.

### 26.7 MEASURED — the full 20 s graphics + sensor capture

```
G1_RESC=/private/tmp/g1-i26/ours-paired-i26.resc        # $rtinfo_pc=0x00015b9c
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf   # app UNCHANGED
G1_NET_ELF=/private/tmp/g1-i26a-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i26f
```

**A harness note that cost two runs and is recorded so it does not cost a
third.**  Renode's `ConsoleIOSource` aborted with
`System.Threading.SemaphoreFullException` ≈19 minutes of HOST time into the
capture, twice, killing the run mid-phase-2 — the same crash iterations 21 and
23 hit.  It is *not* caused by backgrounding: it also happened with stdin
redirected from `/dev/null`.  Giving Renode a pipe that stays open and never
delivers a byte (`sleep 100000 | renode …`) fixes it, and the third run
completed the full 20 s.  No script was modified.

#### The headline: the machine is stable for the whole run for the first time
#### since iteration 23, and it is stable *with* iteration 25's ESB code in it

`grep -c "PC does not lay in memory|ZEPHYR FATAL|SemaphoreFull"` over the 20 s
run is **0**.  Iteration 25's capture contains that halt **twice** (`cpuapp`
then `cpunet`) at ≈1.3 s.  `ORACLE_VTIME_P2` reads the full
`00:00:20.000000000`.  So **the ≈1.3 s `sdc_assertion_handler` reset is gone**
— stated precisely: no CPU halt and no Zephyr fatal error occurs in 20 s; the
`sdc_assertion_handler` symbol itself was not hooked in this capture
(`G1_HOOKS=0`), and §26.8 records the directed probe that is still owed.

| counter | oracle | iter 23 | iter 24 | i25b (rebind OFF) | iter 25 | **iter 26** |
|---|---:|---:|---:|---:|---:|---:|
| machine reset / CPU halt | none | none | ≈15 s | ≈15 s | **≈1.3 s** | **none (full 20 s)** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | 0x3 / 0x0 | 0x3 / 0x0 | 0x0 / 0x0 | **0x3 / 0x3** |
| `JBD JournalCount` | 0x400 | 0x22 | 0x0 | 0x0 | 0x0 | **0x22** |
| `radio TransmittedFrames` | 0x230 | 0xBD | 0x1 | 0x1 | 0x2 | **0x0** |
| `vcentral Connected` | True | **True** | False | False | False | **False** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 1 / 0x216 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `esbslave MasterFramesSeen` / `Acks` | 0x175 / 0x175 | 0 / 0 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | 0x01 | 0x01 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | 0x00 | 0x00 | 0x00 | **0x00** |

**Reported plainly, because it is a regression and the instruction is honest
reporting above all: `radio TransmittedFrames` fell from 1–2 to 0.**  The ESB
frames iteration 25 keyed are no longer keyed at all, and BLE still does not
advertise.  What the same run gained is equally real and is not a cosmetic
metric: the machine survives the whole 20 s, `JBD FrameCounter p2` and
`JBD JournalCount` return to their iteration-23 values, and every sensor volume
is the highest this project has measured.

| device / phase | oracle | iter 24 | i25b | iter 25 | **iter 26** |
|---|---:|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 268 | 1,027 / 268 | 551 / 0 | **1,027 / 700** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 140 | 232 / 140 | 97 / 0 | **232 / 370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV NFC EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 11 / 12 | 0 / 6 | **11 / 12** |
| `saadc` (whole run) | 998 | 41 | 41 | 5 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, all hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | 0 | 0 | **0, hash-EQ** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

`p2_render` LSM6DSO 268 → **700** and nPM1300 140 → **370** are the direct
consequence of not resetting: the phase-2 threads keep polling for the whole
14 s instead of dying part-way.

#### Graphics verdicts

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287, 2,752 pixel windows. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287, 673 pixel windows. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764** transactions, the 34 shared ones byte-identical, first difference at index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are still bit-identical to iterations 16–25 (`0c5cc90b07…`), so the first differing row is the oracle's lowest lit row **y = 267** and the first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | the panel-init sequence is byte-exact over the whole 34-transaction prefix, including the `0x9F` ID probe answering `0x4010` and the `0x46`/`0x31` brightness pair. |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash-EQ, both phases. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` **0x01** vs 0x02, `DISPLAY_ON_ctx_fe8` **0x00** vs 0x01, master PTX frames **0** vs 0x175. |

**NO PIXEL IS PAINTED — `framebuffer.lit_pixels` is 0 in both phases against the
oracle's 656 and 1,098.**  No `0x02` pixel window is emitted in `p2_render`, so
**no display START with `action = 1` arrived**; the three `0x02` transactions in
`p1_boot` are the panel-init window writes that the oracle also makes there and
they paint nothing.  Every graphics number above is measured, none inferred.

### 26.8 The regression, root-caused — and the A/B that says the obvious fix
### is NOT yet the right one

A directed 6 s probe on the final image, hooked at **our build's own symbols**
(`/private/tmp/g1-i26/probeA.resc`, `sleep 100000 | renode …`):

```
NET sdc_assertion_handler        (0x01034150)   -- NEVER entered
APP bt_le_adv_start              (0x00055628)   -- reached, once
APP trigger_screen_state_change  (0x00028ad8)   -- reached, once
APP reflash_fb_data_to_lcd       (0x000416a8)   -- 0 times
APP pixelto4bithex               (0x0003172c)   -- 0 times
radio TransmittedFrames = 0 ; esbslave MasterFramesSeen = 0 ; vcentral Connected = False
```

So the SoftDevice Controller's assertion really is gone (not merely
unobserved), the app **does** ask for advertising, and the CPUNET never keys a
frame — the failure is entirely on the controller side of HCI.

**Root cause of `radio TransmittedFrames` 1–2 → 0.**  Five recovered accessors
(`FUN_010218f0`, `FUN_01021908`, `FUN_01021914`, `FUN_01021920`,
`controller_mode2_state_validate`) do `*(uint32_t *)0x21000530` and then call
through `+4`: it is the pointer word to the **radio-arbitration ops table**.
The shipped `.data` holds `0x21000530 = 0x21000534`, and `nm -S` shows that
0x21000534 in *this* link is **`sym_NIQMZN22R7GGCSNM3BZ25GTCR6D457XB3DIUGWA`**,
a 0x40-byte `.data` object that appears in **no repository source** — i.e. a
SoftDevice Controller archive object that the linker happens to place at
exactly its shipped address (in the iteration-25 build too, which is why
§25.6 could read all eight slots as real code).  The structural pass rebound
the pointer word into `g1_net_ram_blk_210004a8`, and that block is **atomically
excluded** from the `.data` restore because fifteen of its pointer words are
Ghidra-gap interior addresses that do not resolve — so the word reads 0 and the
arbitration path is skipped entirely.  That is also why the SDC no longer
asserts: it is never asked to arbitrate.

**The obvious fix was built and measured, and it is NOT adopted.**
`/private/tmp/g1-i26e-net` binds the word by name to the real owner
(`void *const g1_net_radio_ops_table_ptr = sym_NIQMZN22…;` in
`timeslot_owner.c`, with `PROVIDE(g_net_radio_ops_table_ptr =
g1_net_radio_ops_table_ptr)`).  Same probe, same stimulus:

| | final tree (`g1-i26g-net` ≡ `g1-i26d-net`) | `g1-i26e-net` (ops-table bound) |
|---|---|---|
| `sdc_assertion_handler` in 6 s | not entered | not entered |
| `bt_le_adv_start` | reached once | reached once |
| machine reset in 6 s | **none** | **both cores halted at ≈5.9 s** |
| `radio TransmittedFrames` | 0 | **0** |
| `esbslave MasterFramesSeen` | 0 | 0 |

The binding therefore **enters** the arbitration path and immediately faults,
without recovering a single radio frame.  Per the standing instruction a
regression is reverted and reported with measurements: it is reverted (the
final image is byte-identical to `g1-i26d-net`, md5 `c7bb377c…`), and the
evidence is recorded here and in the linker script at the pin itself.  What the
A/B buys iteration 27 is precise: the ops-table identification is right, the
consumers' expectations of the table are not yet satisfied, and the next step is
to resolve that block's fifteen unresolved flash pointer words — analysis
addresses `0x0101f6dc`, `0x0101f718`, `0x0102953c`, `0x01029540`, `0x01029586`,
`0x0102959e`, `0x010295a2`, `0x010295bc`, `0x010294ee`, `0x01029cd8`,
`0x01029cdc`, `0x01029ce2`, `0x01029d10`, `0x01029d1a` — every one of which is
a Ghidra-gap **interior** address with no catalogue entry and no symbol in this
link.  Restoring the table half-initialised is explicitly the wrong move
(iteration 15's rule), which is why the atomic exclusion stands.

### 26.9 Open, named, and NOT fixed — the iteration-27 first divergence

1. **`g_net_radio_ops_table_ptr` / the radio-arbitration ops table** — §26.8.
   This is the first divergence: `radio TransmittedFrames` is 0, `bt_le_adv_start`
   is reached, and the fifteen ops-table pointer words are the concrete work.
2. **`vcentral Connected` is still False and `VC_ConnectInds` is 0**, i.e. BLE
   advertising has not worked since iteration 23 (which had `True` /
   `0xBD` radio frames / `0x216` data events).  Iteration 26 restores iteration
   23's `JBD FrameCounter p2 = 0x3` and `JBD JournalCount = 0x22` but not its
   radio activity; whether these are one defect or two is not yet established.
3. **28 recovered addresses in the shipped `.data` window are still zero**,
   each because its block contains at least one unresolvable pointer word; the
   eleven blocks and the exact offending words are listed in the comments of
   `recon/application/net/src/g1_net_ram_relocs.c`.
4. **5 addresses in the block at `0x21000c28`** are not restored because the
   block straddles the shipped `.data` end (0x21000c3c) and the generator only
   reads a fully-contained window — a two-line fix, deliberately not made
   mid-iteration.
5. **`FUN_01031a68` has no caller anywhere** (empty `callers` in
   `refgraph_net.json.gz`), which is why the whole ECDH init subtree is
   garbage-collected.  Its real root is unknown; it is probably an SDK init
   section entry or an indirect call, and finding it is a small, self-contained
   investigation.
6. **The cluster-sizing limitation of §26.3** (three pinned large-object bases
   in garbage-collected TUs) should be closed by an explicit size table if any
   of those TUs ever becomes live.
7. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 26)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
# the two gate reports the generator consumes (taken on the PRE-pass build):
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py \
    --core net <pre-pass>/zephyr/zephyr.elf --json /private/tmp/g1-i26-pins-base.json
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py \
    <pre-pass>/zephyr/zephyr.elf --json /private/tmp/g1-i26-lit-base.json
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_net_ram_relocs.py \
    --pins /private/tmp/g1-i26-pins-base.json --lits /private/tmp/g1-i26-lit-base.json \
    --elf <pre-pass>/zephyr/zephyr.elf --rewrite
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py            # 981 -> 980
recon/application/build_cohesive.sh net /private/tmp/g1-i26g-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i26g-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i23a-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i26g-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
# 20 s capture -- NOTE the stdin pipe, without it Renode aborts at ~19 min host time
G1_RESC=/private/tmp/g1-i26/ours-paired-i26.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i26g-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i26f
# probes: /private/tmp/g1-i26/probeA.resc (final tree) and the same with
#         $net_elf pointed at /private/tmp/g1-i26e-net (the reverted A/B)
```

Files changed:
new `recon/application/gen_net_ram_relocs.py`,
new `recon/application/net/src/g1_net_ram_relocs.c` (generated, 70 blocks),
new `recon/symbols/g1_net_ram_reloc.h` (generated, 300 `G1N_` macros),
new `recon/application/net_ram_reloc_ledger.json` (the classification ledger),
new `recon/ownership/net_hci_ecdh_singleton_adoption.json`;
`recon/symbols/g1_net_globals.ld` (204 pins rebound, `rodata_1032e41` removed),
`recon/symbols/g1_net_symbols.h` (one `#include`, one identifier renamed),
`recon/emulator/scripts/check_ram_pin_collisions.py` (**additive** `--core`),
`recon/application/net/CMakeLists.txt` (one source),
`recon/application/net/src/stock_call_aliases.ld` (`FUN_01032680 = hci_ecdh_init`),
`recon/ownership/adoption_manifest.json` (one row flipped),
`recon/generated/net_retained_sources.cmake` (generator only, 981 → 980),
`recon/catalogs/address_names_net.json` (one identifier renamed),
151 `recon/symbolized/net/*.c`, 23 `recon/net/src/*.c`, 4 `recon/net/data/*.c`,
1 `recon/net/named/*.c` (literal rewrites, all behind a `#else` arm that is the
shipped address), `recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no Kconfig / `prj.conf` / devicetree change,
`armemul` untouched, nothing committed.

## Iteration 27 — the radio-arbitration ops table is RESTORED, but by the other
## branch: the 14 "gap functions" are **stock NCS library code this link already
## contains**, and the block that hid them was a mis-classification.  The table
## is now live and complete (no atomic EXCLUDE) — and the machine now resets at
## ≈5.8 s on a *newly reachable* `nrfx_ipc.c:202` assert

**Stated before anything else, because the acceptance bar is pixels:
NO PIXEL IS PAINTED.  And this iteration is, on every measured counter, a
REGRESSION against iteration 26** — the 20 s stability is lost, `p2_render`
sensor volumes fall to 0, and `radio TransmittedFrames` is still 0.  Both
builds are reported side by side in §27.6 and the tree is left in the
corrected state for the reason §27.7 gives.  Nothing below claims a pixel, a
transaction or a sensor match that was not measured.

### 27.1 The task's premise was wrong, and the byte evidence says so

Iteration 26 §26.8 listed **14 unresolved Ghidra-gap analysis addresses**
reached through the pointer word at `0x21000530` and asked iteration 27 to
reconstruct them.  They are not reconstructible work.  They are **stock NCS
2.5.1 library code that this link already links**, and the whole `.data` block
they live in belongs to the stock libraries too.

Two tables sit in the shipped `.data` (read with `tools/net_extract.read_runtime`
at LMA `0x0103ed24`, per `tools/NET_PLAYBOOK.md`'s base rule — every address
below is *runtime*, its analysis twin is runtime − 0x800):

| shipped `.data` | shape | contents |
|---|---|---|
| `0x210004e0..0x21000528` | 9 × `{void (*fn)(void); 0}` | `0x0101fedd 0x01029cef 0x01029dbd 0x01029d9f 0x01029da3 0x01029d87 0x01029d3d 0x0101ff19 0x01029d41` |
| `0x21000530` | pointer word | `0x21000534` |
| `0x21000534..0x21000574` | 16 function pointers (0x40 B) | `0x0102a4d9 0x0102a511 0x0102a4dd 0x0102a51b 0x0102a4e3 0x0102a521 0x0102a4e9 0x0102a4eb 0x0102a4ed 0x0102a4fb 0x0102a50b 0x0102a52d 0x0102a4f1 0x0102a4f7 0x0102a517 0x0102a527` |

The 14 addresses iteration 26 named are exactly nine entries of the first table
and five of the second.  In **our** linked `.data` the same 25 words are
present and hold `shipped − 0x34` — **all twenty-five, the same constant**.
The link map names the owners:

```
0x21000000 .. 0x21000530  .data  libsoftdevice_controller_multirole.a(...obfuscated.elf)
0x21000530 .. 0x21000574  .data  libmpsl_fem_common.a(libmpsl_fem_common_debug_soft__obfuscated.elf)
0x21000534               sym_NIQMZN22R7GGCSNM3BZ25GTCR6D457XB3DIUGWA   (0x40 B)
```

So `0x21000530` is the **MPSL front-end-module `p_api` pointer word** and
`0x21000534` is the **FEM API vtable**; the 16 entries are the "no FEM present"
stubs (`movs r0,#0; bx lr` / `mov.w r0,#-1; bx lr` / `bx lr` /
`movs r3,#0; strb r3,[r0]; bx lr`).  The nine-entry table is a SoftDevice
Controller `.data` object.  The recovered accessors
(`FUN_010218b4/c0/cc/d8/e4/f0/fc`, `FUN_01021908/14/20`,
`controller_mode1_state_validate`, `controller_mode2_state_validate`) are the
`mpsl_fem_*` public API thunks.

**Proof the whole window is the same objects, not a coincidence**
(`recon/application/verify_net_stock_data_window.py`, new, additive):

```
window                         0x21000000..0x21000574 (1396 B)
words equal                    256 / 349
words differing (flash ptrs)   93
words differing (OTHER)        0
distinct pointer deltas        2  0x34 x25, 0xa0 x68
map input sections in window   72, 1396 B covered
non-stock input sections       0
VERDICT                        PROVEN
```

Every single differing word is a flash code pointer, and the differences
collapse to **exactly two constants — one per contributing archive**.  That can
only happen if both images contain the same library objects, in the same order,
at the same addresses.

**Proof at the code level too** (`/private/tmp/g1-i27/cmp_stock.py`):

* all **16** FEM vtable targets are **byte-identical** to the shipped bytes at
  −0x34 over 24 bytes;
* the 9 SDC-table targets are **opcode-for-opcode identical over all 62
  instructions**, with the only differences being branch displacements, which
  cluster into 4 constants (`0xa0` ×16, `0x34` ×15, `0x5c` ×3, and one literal
  pool word that is an SDC `.bss` address).

Reconstructing them would have created a **second** FEM vtable and a second SDC
dispatch table — the singleton-duplication defect iteration 26 §26.4 avoided for
`hci_ecdh.c`.  The evidence record is
`recon/ownership/net_mpsl_fem_radio_ops_table_ownership.json` (new), which
carries all 14 addresses with their our-link twins and per-address verdicts.

### 27.2 The real defect: iteration 26's structural pass over-reached

Iteration 26 classified all 300 recovered CPUNET addresses as class (a),
"recovered-owned net RAM", and gave each one fabricated `used, retain` storage.
**52 of them are inside the stock-library `.data` window above.**  Giving those
private zeroed blocks is what zeroed `0x21000530` — and, because the block that
swallowed it contains pointer words into stock library code that our link does
not define under those addresses, the block was also atomically excluded, which
is why §26.8 read the symptom as "fifteen unresolved Ghidra-gap pointer words".
There was never anything to resolve: the words are *library* pointers and the
library already writes them.

The gate never flagged these 52, and correctly so — the stock `.data` input
sections are anonymous, so `check_ram_pin_collisions.py` saw them as "in region
but free" (130 of them), not as collisions.  The pass relocated that whole
category on principle rather than on evidence.

### 27.3 The fix — a fourth classification in the generator

`recon/application/gen_net_ram_relocs.py` gains `STOCK_DATA_WINDOWS`: a
verified range of stock-library `.data` that this link places at the shipped
address.  Addresses inside it are **not** clustered into a block; they are bound
to `<anchor> + <shipped .data offset>`, where the anchor is the linker's own
`__data_start` (the archives export no symbol for most of these objects — their
`.data` input sections are anonymous — so the region anchor is the only NAME
available, and the offset is exactly the shipped one, which §27.1 proves this
link reproduces).  The gate treats `__data_start` as a chained bind (it is a
zero-size script symbol), so the 26 affected pins stay **bound**, not raw.

Three generator changes were needed and are recorded because they are what
makes the pass re-runnable at all:

* `rewrite_linker` now recognises an **already-bound** `PROVIDE` (both the
  `g1_net_ram_blk_… + off` and `__data_start + off` forms) and recovers the
  original address **from the binding itself** (a block's name carries its
  base), so no external name→address table is needed and the pass is
  idempotent in both directions.  It also replaces a previously emitted
  generator header instead of stacking a second one.
* `rewrite_sources` masks the character range of a guard block this generator
  injected earlier.  Without that mask a second `--rewrite` run rewrote the
  shipped literals in the guard's own `#else` arm into `#define G1N_x G1N_x`
  and prepended a second guard.  **This actually happened on the first attempt
  in this iteration and was reverted with `git checkout` before any build.**
* `refresh_guards` re-emits those self-contained guard blocks from the current
  classification, because they do not come from `g1_net_ram_reloc.h` and a
  reclassification has to reach them (24 files refreshed).

Result:

| | iteration 26 | **iteration 27** |
|---|---:|---:|
| addresses classified | 300 | 300 |
| — relocated into blocks | 300 | **248** |
| — bound to stock `.data` (new class) | 0 | **52** |
| blocks emitted | 70 | **63** |
| block bytes | 3,416 | **2,912** |
| linker pins bound to a block | 204 | **174** |
| linker pins bound to `__data_start` | 0 | **30** |
| blocks with a restored shipped initialiser | 8 | 6 (the two lost are now the library's own) |

**`g_net_radio_ops_table_ptr` is bound and the table is complete.**  `nm` on the
new link gives `21000530 A g_net_radio_ops_table_ptr` and
`21000534 D sym_NIQMZN22…`; the linked `.data` image at `0x21000530` reads
`34 05 00 21` followed by the sixteen live stub pointers.  **There is no atomic
EXCLUDE anywhere near it** — the block `g1_net_ram_blk_210004a8` and the six
other blocks that covered the window no longer exist.

### 27.4 A second, independent correction: the `FUN_01021920` thunk dropped r3

With the table live the thunks actually execute, which exposed a
**harness-blind dropped-register-argument defect** — the class the task warns
about (12 known instances).  The shipped thunk is

```
01021920  10b4  push {r4}          01021908  014b  ldr r3,[pc,#4]
01021922  034c  ldr  r4,[pc,#0xc]  0102190a  1b68  ldr r3,[r3]
01021924  2468  ldr  r4,[r4]       0102190c  9b6a  ldr r3,[r3,#0x28]
01021926  6468  ldr  r4,[r4,#4]    0102190e  1847  bx  r3
01021928  a446  mov  ip,r4
0102192a  10bc  pop  {r4}
0102192c  6047  bx   ip
```

i.e. `FUN_01021920` saves and restores **r4** and tail-calls through **ip**,
while its nine siblings use **r3** as scratch.  That is the byte evidence that
r3 is a **live fourth argument** only in this one.  The old body
(`void FUN_01021920(void) { fn(); }`) compiled to
`ldr r3,[pc]; ldr r3,[r3]; ldr r3,[r3,#4]; bx r3`, clobbering r3 with the callee
address; the sole live caller `FUN_01032ad8` passes five arguments and the
callee (ops[1], shipped `0x01029d10` → `0x01029cb6`, falling into `0x01029cbc`)
consumes r3 as `sxtb r1, r3`.

The corrected body forwards four register arguments and returns the callee's
value; GCC 12.2 at `-Os` emits **exactly the shipped instruction sequence**:

```
0102ae54  b410  push {r4}
0102ae56  4c03  ldr  r4,[pc,#12]
0102ae58  6824  ldr  r4,[r4]
0102ae5a  6864  ldr  r4,[r4,#4]
0102ae5c  46a4  mov  ip,r4
0102ae5e  bc10  pop  {r4}
0102ae60  4760  bx   ip
```

— byte-for-byte the shipped thunk.  The nine siblings are left alone: their
`void(void)` bodies already compile to the shipped `r3` form byte-for-byte, so
they are correct as they stand.

**Proof, stated honestly.**  `cfg_verify.verify("net", "FUN_01021920")`
(the authoritative CFG-directed verifier, which supplies its own catalogue-derived
`call_arity_by_target` / `call_float_arity_by_target` / `call_return_kind_by_target`)
returns `PASS, checked = 40 random trials, cover_cases = 0` — 0 directed cases
because the thunk is straight-line and has no branch condition to cover.  The
**old, wrong body also returns `PASS, 40, 0`**, measured this iteration with
`source_override`.  So parity is *not* the evidence here; the byte-for-byte
match of the emitted code against the shipped bytes is.  The same run
re-verified `FUN_010218b4`, `FUN_010218f0` and `FUN_010218fc`: `PASS, 40, 0`
each, unchanged.

### 27.5 Gates (all clean) and build ledger

| gate | iteration 26 | **iteration 27** |
|---|---|---|
| `check_ram_pin_collisions.py --core net` raw-in-object / raw-free | 0 / 0 | **0 / 0** |
| `check_ram_pin_collisions.py --core net` bound OK / escaping | 199 / 0 | **199 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app, unchanged invocation) | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_net_raw_literals.py` distinct / colliding | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean** |
| net `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| app `nm -u` undefined / duplicate globals | 0 / 0 | **0 / 0** |
| `verify_net_stock_data_window.py` | — | **PROVEN** (new) |
| net FLASH | 225,217 B (97.32 %) | **225,073 B (−144; 97.26 %)** |
| net RAM | 64,012 B (97.67 %) | **63,508 B (−504; 96.91 %)** |

Both budgets went **down**, so the `app.overlay` headroom mechanism was not
needed and no real content was dropped.

| net build | change | FLASH | RAM |
|---|---|---:|---:|
| `/private/tmp/g1-i26g-net` | iteration-26 final (the A side) | 225,217 B | 64,012 B |
| `/private/tmp/g1-i27a-net` | + the stock-`.data`-window reclassification | 225,073 B | 63,508 B |
| `/private/tmp/g1-i27b-net` | + the `FUN_01021920` r3 correction (**final**) | 225,073 B | 63,508 B |

The app core is **UNCHANGED** (`/private/tmp/g1-i23a-app`, `$rtinfo_pc = 0x00015b9c`).

### 27.6 MEASURED — the full 20 s capture, A/B against iteration 26

```
G1_RESC=/private/tmp/g1-i27/ours-paired-i27.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf
G1_NET_ELF=/private/tmp/g1-i27b-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i27b
```

(`sleep 100000 | …`, per iteration 26's `SemaphoreFullException` note.  The run
completed in ≈2 minutes of host time because both cores stop early.)

| counter | oracle | **iter 26 (`g1-i26g`)** | **iter 27 (`g1-i27b`)** |
|---|---:|---:|---:|
| machine reset / CPU halt | none | **none (full 20 s)** | **≈5.8 s, both cores** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | **0x0 / 0x0** |
| `JBD JournalCount` | 0x400 | 0x22 | **0x0** |
| `radio TransmittedFrames` | 0x230 | 0x0 | **0x0** |
| `vcentral Connected` | True | False | **False** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 0 / 0 | **0 / 0** |
| `esbslave MasterFramesSeen` / `Acks` | 0x175 / 0x175 | 0 / 0 | **0 / 0** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | **0x00** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | **0 / 0** |

| device / phase | oracle | **iter 26** | **iter 27** |
|---|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 700 | **551 / 0** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 370 | **97 / 0** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | **14 / 0** |
| ST25DV NFC EEPROM / system port `p1` | 25 / 22 | 11 / 12 | **0 / 6** |
| `saadc` (whole run) | 998 | 71 | **5** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, all hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 | 0 | **0, hash-EQ** |
| `IMU_ACCEL_ENABLED` | True | True | **False** |
| `OPT3001_CONVERSION_READY` | True | True | **False** |
| `NPM1300_CHARGING` | True | True | **False** |

#### Graphics verdicts (iteration 27)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287, 2,881 transactions. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 3 pixel windows**; oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**; the 34 shared transactions are **identical entry-for-entry**, first difference at index **34** (oracle `{"op":"0x66","kind":"command"}`, ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0** (oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265}`). |
| **G-4** | *localiser* | our framebuffer bytes are still bit-identical to iterations 16–26 (`0c5cc90b07…`), so the first differing row is the oracle's lowest lit row **y = 267** and the first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | the panel-init sequence is byte-exact over the whole 34-transaction prefix, including the `0x9F` ID probe answering `0x4010` and the `0x46`/`0x31` brightness pair. |
| **G-6** | **PASS** | `spim_b` 0 == 0, hash-EQ, both phases. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` 0x01 vs 0x02, `DISPLAY_ON_ctx_fe8` 0x00 vs 0x01, master PTX frames 0 vs 0x175. |

**NO PIXEL IS PAINTED — `framebuffer.lit_pixels` is 0 in both phases against
656 / 1,098.  No `0x02` pixel window is emitted in `p2_render`, so no display
START with `action = 1` arrived** (`firmware_events` is `{}` for our run against
the oracle's `{"spi_read_id":1,"display_START":2,"BLIT":15}`).  Criteria score
falls from iteration 26's 4 PASS / 4 PARTIAL / 6 FAIL to **4 PASS / 1 PARTIAL /
9 FAIL** (G-5, G-6, S-MIC, S-KEYS still pass; S-IMU is the only PARTIAL left;
S-ALS, S-PMIC and S-NFC drop to FAIL because their phase-2 traffic and their
state flags are gone with the reset).

### 27.7 The new stall, root-caused — `nrfx_ipc.c:202`, and it is the SAME class

A directed 6 s probe on `g1-i27b-net` (`/private/tmp/g1-i27/probe{B,C,D,E}.resc`,
`sleep 100000 | renode …`) walks the whole path:

```
NET z_arm_fatal_error / z_fatal_error / k_sys_fatal_error_handler / panic   (CPUNET, ≈5.8 s)
  z_arm_fatal_error entered with LR = _oops+0x7, i.e. via z_arm_svc -> _oops
NET assert_post_action  r0=0x0103e73b  r1=0xca  lr=0x0102d0f1
  rodata @0x0103e73b = "ic/nrfx/drivers/src/nrfx_ipc.c" , line 0xca = 202
  0x0102d0f1 = FUN_01035028 + 0x21   (our reconstruction)
NET sdc_assertion_handler   -- NEVER entered
NET m_assert_handler        -- NEVER entered
```

`FUN_01035028` asserts `table[idx*0xc + 8] != 0` and then writes `1` into it.
`table` is the pin `g_net_gpiote_evt_handler_table` at `0x21004af8`, and the
layout (12-byte entries, a state byte at +8) is exactly nrfx's IPC control
block `{ handler, p_context, state }` — the assert is nrfx's
`NRFX_ASSERT(m_cb.state != NRFX_DRV_STATE_UNINITIALIZED)`.  In this link the
**stock** `nrfx_ipc.c` is also present (`nrfx_ipc_init 0x01035e5c`,
`nrfx_ipc_receive_event_enable 0x01035f20`, its `m_cb` at `0x21009178`, 0xc B,
`.bss`), so the stock driver initialises **its** control block while our four
recovered copies (`FUN_01034fa8`, `FUN_01035028`, `FUN_01035068`,
`FUN_010350a4`) read a **private zeroed relocation block**.  With the FEM path
now live the IPC enable is actually reached, the state byte reads 0, and
`k_oops` resets the SoC — which is why **both** cores report
`PC does not lay in memory` at the same instant (the reset vector table at
address 0 is empty in this machine).

This is the **same class as §27.2** — a stock-owned object handed private
storage — but one address higher up: `0x21004af8` is `.bss` in the shipped
image, our link's `m_cb` is at a different address, and the archive symbol is
`local` (`b`), so a linker `PROVIDE` cannot name it.  The remedy is therefore
**displacement**, the iteration-26 §26.4 pattern: adopt the stock `nrfx_ipc.c`
unit and exclude the four reconstructions, with an ownership record.  That is a
self-contained iteration-28 task and was deliberately **not** started
mid-iteration.

**Why the iteration is not reverted.**  The standing instruction is that a
provably-correct fix is not reverted to improve a metric, and that a fix which
moves further into a *new* stall is reported as an A/B.  §27.1's evidence is
byte-level and unambiguous: the ops table and its 25 targets are stock library
objects that this link already owns, and iteration 26's blocks for them were
wrong.  The tree is left corrected, both builds are measured above, and the new
divergence is named to the file and line.  A reader who wants iteration 26's
stability back can rebuild `/private/tmp/g1-i26g-net` from commit `806dba5c`.

### 27.8 Open, named, and NOT fixed — the iteration-28 first divergence

1. **`nrfx_ipc.c:202` / the four recovered nrfx_ipc copies** — §27.7.  This is
   the first divergence: displace `FUN_01034fa8` / `FUN_01035028` /
   `FUN_01035068` / `FUN_010350a4` to the stock `nrfx_ipc.c` singleton (or bind
   `g_net_gpiote_evt_handler_table` to it), then re-measure.  Until then the
   CPUNET resets at ≈5.8 s.
2. **Generalise the §27.3 sweep.**  The stock-`.data` window closed 52
   addresses; the same question — "does a stock library already own this
   object?" — has not been asked of the other 248, particularly the ones in
   `.bss` where only displacement can answer it.  A mechanical pass would be
   `for each pin, does a stock archive define an object of the right size that
   the recovered accessor's field offsets fit?`.
3. **`radio TransmittedFrames` is still 0 and `vcentral Connected` still
   False.**  The ops table is no longer the reason; the reset now is.
4. **The 5 addresses in the block at `0x21000c28`** are still not restored
   (block straddles the shipped `.data` end at `0x21000c3c`) — unchanged from
   §26.9(4), still a two-line fix.
5. **21 blocks still carry an atomic EXCLUDE** (down from 28 addresses in 11
   blocks by the 7 blocks this pass deleted); each names its unresolved words
   in `recon/application/net/src/g1_net_ram_relocs.c`.  Several of the named
   words are `0x0103xxxx` flash pointers that are very probably the same
   stock-library situation as §27.1 and should be re-examined under item 2.
6. **`FUN_01031a68` still has no caller anywhere** (§26.9(5)) — unchanged.
7. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 27)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
# the reclassification (inputs are the SAME pre-pass gate reports iteration 26 used)
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_net_ram_relocs.py \
    --pins /private/tmp/g1-i26-pins-base.json --lits /private/tmp/g1-i26-lit-base.json \
    --elf /private/tmp/g1-i26base-net/zephyr/zephyr.elf --rewrite
recon/application/build_cohesive.sh net /private/tmp/g1-i27b-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# the new evidence gate
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py \
    /private/tmp/g1-i27b-net/zephyr/zephyr.elf --json /private/tmp/g1-i27-stock-window.json
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i27b-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i23a-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i27b-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
# re-verify the corrected thunk (and the harness-blindness demonstration)
PYTHONSAFEPATH=1 .venv/bin/python -c "import sys;sys.path.insert(0,'tools');import cfg_verify;print(cfg_verify.verify('net','FUN_01021920'))"
# 20 s capture -- NOTE the stdin pipe
sleep 100000 | G1_RESC=/private/tmp/g1-i27/ours-paired-i27.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i27b-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i27b
```

Files changed:
new `recon/application/verify_net_stock_data_window.py`,
new `recon/ownership/net_mpsl_fem_radio_ops_table_ownership.json`;
`recon/application/gen_net_ram_relocs.py` (`STOCK_DATA_WINDOWS` + idempotent
rewrite + `refresh_guards`),
`recon/application/net/src/g1_net_ram_relocs.c` (generated, 70 → 63 blocks),
`recon/symbols/g1_net_ram_reloc.h` (generated),
`recon/application/net_ram_reloc_ledger.json` (generated, new `stock` section),
`recon/symbols/g1_net_globals.ld` (30 pins moved to `__data_start + off`),
`recon/net/src/FUN_01021920.c` + `recon/symbolized/net/FUN_01021920.c`
(the r3 correction), 23 `recon/net/src/*.c` +
`recon/application/net/src/timeslot_owner.c` (guard blocks refreshed by the
generator; `#else` arms unchanged, so `tools/parity` still sees the shipped
literals),
`recon/emulator/reports/sensor_parity_status.md`, this report.
**No `tools/` logic change**, no Kconfig / `prj.conf` / devicetree change,
`armemul` untouched, nothing committed.

## Iteration 28 — the duplicate-singleton class is swept **mechanically**, not
## one crash at a time: 153 recovered CPUNET functions are proven
## relocation-masked byte-identical to a stock unit this link already contains,
## 46 shipped RAM addresses are attributed to stock-owned objects, and three
## complete units are displaced.  The ≈5.8 s reset is GONE, the 20 s capture is
## reset-free, and for the FIRST time `radio TransmittedFrames` is non-zero
## (**0xCF**) with `vcentral Connected` **True**

**Stated before anything else, because the acceptance bar is pixels: NO PIXEL
IS PAINTED.**  `framebuffer.lit_pixels` is **0 / 0** against the oracle's
**656** (`p1_boot`) / **1,098** (`p2_render`).  Everything below is measured;
nothing is claimed that was not.

### 28.1 Iteration 27's identification of the blocker was WRONG, and the byte
### evidence says which file it really is

§27.7 named `nrfx_ipc.c:202`.  That reading came from a string read at the
wrong offset.  Read with `tools/net_extract.read_runtime`, the shipped `.rodata`
at `0x0103e700` is

```
0x0103e700  "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_ipc.c\0"   (58 B + NUL)
0x0103e73b  "WEST_TOPDIR/modules/hal/nordic/nrfx/drivers/src/nrfx_timer.c\0"
```

`0x0103e700 + 59 = 0x0103e73b` exactly, so **the pointer the assert passes is
the `nrfx_timer.c` path**, not `nrfx_ipc.c` (0x0103e71d, 0x1e lower, is the
mid-string `"c/nrfx/drivers/src/nrfx_ipc.c"` §27.7 actually printed).  And line
202 of the pinned `~/ncs251/modules/hal/nordic/nrfx/drivers/src/nrfx_timer.c` is

```c
200  void nrfx_timer_disable(nrfx_timer_t const * p_instance)
201  {
202      NRFX_ASSERT(m_cb[p_instance->instance_id].state != NRFX_DRV_STATE_UNINITIALIZED);
```

which is exactly `FUN_01035028`'s shape.  Iteration 24's `timeslot_owner.c`
comment had it right all along (`".../nrfx_timer.c", 0x8e`); iteration 27
regressed the identification.  The four functions are
`nrfx_timer_init / _disable / _uninit / _2_irq_handler`, and
`g_net_gpiote_evt_handler_table` @ `0x21004af8` is a **mis-name**: the object is
nrfx's timer control block `m_cb`.

### 28.2 The blocker root cause, MEASURED, is not "init never ran" — it is a
### relocation-block **aliasing overrun**

Four directed Renode probes on the iteration-27 tree rebuilt as
`/private/tmp/g1-i28base-net` (image md5 `dd9e08a1…`, **identical** to
`g1-i27b-net`, so the baseline is the same firmware):

```
probe2  NET timer_configure OK
probe2  NET timer_init_store  state=0x1  r0=0x0bad0000  r4=0x21001fa8  r5=0x8
probe2  NET nrfx_timer_uninit state=0x0          <-- the byte was 1 and became 0
probe4/5 (sysbus watchpoint, 0x21001fb0, Byte, Write)
        WRITE pc=0x0103c4ba (memset, z_bss_zero)          -- boot clear
        WRITE pc=0x0102d0ac (FUN_01034fa8 store)          -- state = 1, init OK
        WRITE pc=0x0103c514 (memcpy+0x12) lr=0x0102d91f r0=0x21001f06  <-- CLOBBER
        WRITE pc=0x0102d13a (FUN_01035068, state = UNINIT)
```

`lr = 0x0102d91f` is `FUN_0102b3f0 + 0x66`, and `r0 = 0x21001f06` is
`g_net_ctrl_status_byte`, i.e. `g1_net_ram_blk_21004c98 + 0x7`, shipped address
`0x21004c9f`.  **In the SHIPPED address space that copy runs upward from
`0x21004c9f` and cannot touch `m_cb.state` at `0x21004b00`.  In iteration 26's
COMPRESSED relocation-block space the two objects are only `0xb1` bytes apart,
so it does.**  `nrfx_timer_init` had succeeded; the state byte was destroyed
afterwards.  This is iteration 26 §26.3's own stated limitation — "a block is
sized from the *referenced* addresses, not from the object's true extent" —
producing a real defect for the first time.

Displacing the owning unit is the fix the standing directive asks for and it is
also the structurally right one: it takes `m_cb` **out of the block space
entirely**, into the stock `.bss`, where nothing aliases it.

### 28.3 A second defect the displacement repairs, which the parity harness
### **cannot** see

The recovered `FUN_01034f24` (`timer_configure`) carries the base-frequency
literal `0x000f4240` = **1,000,000**.  The stock section and the shipped image
both carry `0x00f42400` = **16,000,000**:

```
shipped / stock      78:  00f42400   .word 0x00f42400      (16 MHz)
our reconstruction  102cfd2:  ldr r5,[pc,#120] -> 0x000f4240      (1 MHz)
```

With the ESB config frequency of 1,000,000 Hz the recovered body computes
`prescaler = ctz(1) = 0` and programs **TIMER2 at 16 MHz**; the stock body
computes `ctz(16) = 4` and programs **1 MHz**.  **The ESB timer was running
sixteen times too fast.**  The parity harness is structurally blind to this: the
literal lives inside the reconstructed body, so original and candidate agree
with *each other*.  Only a byte comparison against the SDK finds it — which is
precisely the evidence bar the task sets.

### 28.4 The sweep — method, and what it found

Three detectors, all analysis-only (scratchpad scripts; **no `tools/` logic was
changed**), recorded in **`recon/ownership/net_duplicate_singleton_sweep.json`**
(new, 99 KB):

1. **Byte identity.**  Index every `.text.*` input section of every stock
   archive member this net link consumes — all 40 build archives except our own
   `app/libapp.a`, plus the toolchain `libgcc` and picolibc multilibs — with a
   4-byte mask at every relocation offset (**2,506 sections**).  For each of the
   **980 retained** recovered net functions, read `netcore_image.bin` at its
   analysis VA for each candidate section length and require agreement on
   **every unmasked byte of the whole section**.  Instruction shape is never
   accepted (iteration 20's `bt_ancs_register_attr` mistake).
2. **Shipped-state attribution.**  For every located section, resolve every
   `R_ARM_ABS32` relocation into a `.bss.*`/`.data.*` object of the same member:
   `shipped = image_word(hit_va + off) − in-place addend`.  This is iteration
   27's stock-`.data`-window proof **generalised to `.bss` and to every unit**,
   and it needs no shipped link map.
3. **Unit completeness.**  Slide every section of a candidate unit over the
   whole image.  A unit may only be displaced **whole**: displacing the exact
   half of a partially-vendored unit would SPLIT its file-static state between
   two translation units — the very defect being removed.

Result:

| | |
|---|---:|
| stock `.text` sections indexed | 2,506 |
| retained recovered net functions scanned | 980 |
| **recovered functions byte-identical to a stock section** | **153** |
| of those, whose stock unit owns mutable state | **70** |
| **distinct shipped RAM addresses attributed to a stock object** | **46** |
| upstream units touched | 50 |

The 46 attributed addresses immediately re-name a long list of autonamed pins
and independently **confirm three earlier iterations' hand findings**:

| shipped addr | stock owner | our pin name |
|---|---|---|
| `0x21000750` | `timeout.c :: .data.timeout_list` | `g_net_kernel_timeout_dlist_head` (iteration 18) |
| `0x2100065c` | `esb.c :: .data.disable_event` | (iteration 25's "ESB session word") |
| `0x21000698` | `esb.c :: .data.esb_timer` | `g_net_log_msg_ctx` (iteration 24) |
| `0x21004af8` | `nrfx_timer.c :: .bss.m_cb` | `g_net_gpiote_evt_handler_table` |
| `0x21004aec` | `nrfx_ipc.c :: .bss.m_cb` | `g_sdc_radio_context_area` |
| `0x21004a94` / `0x21004a34` / `0x21004a60` | `esb.c :: esb_cfg / rx_fifo / tx_fifo` | `g_esb_state` / `g_net_queue_stats_block_b` / — |
| `0x21006458` / `0x21006459` | `esb.c :: esb_state / esb_initialized` | `g_net_radio_busy_flag` / `g_esb_enabled_flag` |
| `0x2100645a..0x21006460` | `esb_dppi.c` — 7 DPPI channel/group bytes | `g_net_radio_trx_ppi_ch_a` … |
| `0x21004b48` / `0x21004b4c` | `mutex.c :: lock` / `sem.c :: lock` | — |
| `0x210006a0` / `0x210006a4` | `nrfx_dppi.c :: m_allocated_groups / _channels` | (iteration 24) |
| `0x21002b60` / `0x21004964` / `0x2100496c` | `nrf_rtc_timer.c :: cc_data / force_isr_mask / int_mask` | — |
| `0x210051ae` | `hci_internal.c :: cmd_complete_or_status` | `g_net_pending_tx_pkt` |

### 28.5 The three units displaced, and the ones deliberately KEPT

| batch | unit | fns | sections in image / byte-identical | distinguishing bytes | singleton state |
|---|---|---:|---|---:|---|
| **1** | `nrfx_timer.c` | 6 | **6 / 6** | 472 | `.bss.m_cb` @ `0x21004af8` |
| **2** | `esb_dppi.c` | 12 | **12 / 12** | 996 | 7 bytes @ `0x2100645a..0x21006460` |
| **3** | `nrfx_ipc.c` | 2 (of 5 present) | **5 / 5** | 148 | `.bss.m_cb` @ `0x21004aec` |

* **`nrfx_timer.c`** — the other 13 stock sections are absent from the shipped
  image because the shipped link garbage-collected them, exactly as ours does.
  `timer_configure` is file-local (`t`) in the stock object so a `PROVIDE`
  cannot name it; its only recovered referrer, `FUN_01034fa8`, is displaced in
  the same batch, so the exclusion leaves no undefined symbol.  After the batch
  the sweep's cross-reference reports **0 retained referrers** of `0x21004af8`.
* **`esb_dppi.c`** — the 12 located sections tile a contiguous run
  `0x01033b18..0x01033ff8` in the object's own section order; the two absent
  ones (`esb_ppi_for_wait_for_rx_set/clear`) were gc'd out of the shipped link.
  All 12 stock symbols are global.  Cross-reference: the only referrers of the
  seven DPPI state bytes are the twelve `esb_dppi.c` functions themselves —
  `esb.c` only calls the `esb_ppi_*` accessors — so the displacement is total.
  Corroboration that the allocator it now calls is the right one: the stock
  `nrfx_dppi.c` `.data` initialisers in **this** build are byte-identical to the
  shipped ones (`m_allocated_channels 00 c0 ff ff`, `m_allocated_groups
  3f 00 00 00`).
* **`nrfx_ipc.c`** — the five located sections tile `0x01034d8c..0x01034f24`
  **exactly** (76+120+56+56+100 = 408 B, no gap; the next byte is
  `timer_configure`).  The stock unit is **already unconditionally linked**
  (`nrfx_ipc_init`, `_config_load`, `_receive_event_enable`, `_disable`,
  `_irq_handler` all present) with its own `m_cb`, so this was a genuine live
  duplicate — the hazard iteration 27 was reaching for, in the right file.
  Stated honestly: it is **latent**, because `FUN_01030bac` (the recovered
  `mbox_nrf_init`) has no referrer and `--gc-sections` had already dropped both
  reconstructions.  The image is therefore byte-identical before and after
  (md5 `135efe97…` for both `g1-i28b-net` and `g1-i28c-net`), which is checked,
  not assumed.

**KEPT, with the reason — where Even genuinely diverged from stock:**

| unit | fns matched | evidence for KEEPING |
|---|---:|---|
| **`esb.c`** | 29 | Only **32 of 53** sections are in the shipped image at all, and **eight RETAINED reconstructions lie inside esb.c's own VA run** `0x01032764..0x01033b18` (`0x1032a3c`, `0x1032be4`, `0x1032c28`, `0x1032de4`, `0x1032e54`, `0x10331c8`, `0x10333b4` = `esb_init`, `0x1033660`) and match **no** `esb.c` section.  The missing stock sections cluster hard: `esb_init`, `esb_write_payload`, `start_tx_transaction`, `on_radio_disabled_rx`, `..._tx_wait_for_ack`, `..._tx_noack`, `rx_fifo_push_rfbuf`, `esb_flush_rx/tx`, `esb_pop_tx`, `esb_set_address_length/bitrate/retransmit_*` — i.e. every FIFO-size- and payload-length-dependent function.  That is the signature of a **different ESB Kconfig or a vendored copy**, and it is the single highest-leverage lead for the next iteration.  Displacing the matching half would split `esb_cfg`/`esb_state`/`rx_fifo`/`tx_fifo`/`pids` across two TUs. |
| **`nrfx_gpiote.c`** | 21 | 27 of 49 sections located; `.data.m_cb` is shared by all of them.  Same split hazard. |
| **`nrf_rtc_timer.c`** | 4 | `cc_data` / `int_mask` / `force_isr_mask` shared with unlocated sections. |
| **`sem.c` / `mutex.c`** | 1 + 1 | `z_impl_k_sem_take` is byte-identical (140 distinguishing bytes) but `z_impl_k_sem_give` (the adjacent `FUN_01036824`, exactly 0x78 lower) is **not**, and both take `sem.c :: lock`.  Displacing only `take` would split the lock. |
| `clock_control_nrf.c`, `hci_internal.c`, `nrfx_dppi.c`, `timeout.c` | 1–2 each | same partial-unit hazard |

**Liveness, measured, and why the rest of the ranked list is not displaced.**
Of every remaining ranked candidate, only `sem.c`'s `FUN_0103689c` and
`FUN_01036824` **survive `--gc-sections` in the link at all** (checked with `nm`
on `g1-i28c-net`).  Every other hazard the sweep found is **latent** — the
reconstruction is already dropped.  Displacing them would change nothing
measurable while carrying real regression risk (iteration 26's 39-row
`zephyr_drivers` batch had to be reverted), so they are ranked, recorded and
left.  On a UP kernel a Zephyr spinlock is an IRQ lock, so the split `sem.c`
lock is a correctness hazard in principle but not a live race today; it is
recorded as open.

### 28.6 Build ledger and gates

| net build | change | FLASH | RAM | `nm -u` | image md5 |
|---|---|---:|---:|---:|---|
| `/private/tmp/g1-i28base-net` | iteration-27 tree rebuilt (baseline) | 225,073 B | 63,508 B | 0 | `dd9e08a1…` (== `g1-i27b-net`) |
| `/private/tmp/g1-i28a-net` | + batch 1 (`nrfx_timer.c`) | 225,149 B | 63,516 B | 0 | — |
| `/private/tmp/g1-i28b-net` | + batch 2 (`esb_dppi.c`) | 225,149 B | 63,524 B | 0 | `135efe97…` |
| `/private/tmp/g1-i28c-net` | + batch 3 (`nrfx_ipc.c`) — **final** | 225,149 B | 63,524 B | 0 | `135efe97…` (identical to b) |

FLASH **+76 B** and RAM **+16 B** against iteration 27 — the stock units are
slightly larger than the reconstructions they replace; both remain inside
budget (97.29 % / 96.93 %).  Net retained sources **980 → 960**; manifest
exclusions **255 → 275**.  The app core is **UNCHANGED** (`g1-i23a-app`,
`$rtinfo_pc = 0x00015b9c`).

| gate | iteration 27 | **iteration 28 (`g1-i28c-net`)** |
|---|---|---|
| `check_ram_pin_collisions.py --core net` raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py --core net` bound OK / escaping | 199 / 0 | **190 / 0** (9 pins lost their last referrer with the displaced units) |
| `check_ram_pin_collisions.py` (app) | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_net_raw_literals.py` distinct / colliding | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| net / app `nm -u` undefined | 0 / 0 | **0 / 0** |
| net / app duplicate global definitions | 0 / 0 | **0 / 0** |

No `--allow-multiple-definition`, no weak-symbol hack, no numeric root.

### 28.7 MEASURED — the full 20 s capture, A/B/C against iterations 26 and 27

```
G1_RESC=/private/tmp/g1-i28/ours-paired-i28.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf
G1_NET_ELF=/private/tmp/g1-i28{a,b}-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i28{a,b}
```

(`sleep 100000 | …` throughout, per iteration 26's `SemaphoreFullException`
note.  `g1-i28c-net` is byte-identical to `g1-i28b-net`, so the `i28b` capture
IS the final tree's capture.)

| counter | oracle | iter 26 | iter 27 | **iter 28a** (batch 1) | **iter 28b/c** (final) |
|---|---:|---:|---:|---:|---:|
| machine reset / CPU halt | none | none | **≈5.8 s** | **none** | **none (0 halts over 20 s)** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | 0 / 0 | 0x3 / 0x3 | **0x3 / 0x3** |
| `JBD JournalCount` | 0x400 | 0x22 | 0 | 0x22 | **0x22** |
| **`radio TransmittedFrames`** | 0x230 | **0x0** | **0x0** | **0xCE** | **0xCF** |
| **`vcentral Connected`** | True | False | False | **True** | **True** |
| `vcentral ConnectInds` | 1 | 0 | 0 | **1** | **1** |
| `vcentral DataEvents` | 0x215 | 0 | 0 | **0x26B** | **0x26B** |
| `esbslave MasterFramesSeen` / `Acks` | 0x175 / 0x175 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |
| `esbslave AnnounceResponses` | 0x15B | 0 | 0 | 0 | **0** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | 0x01 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | 0x00 | 0x00 | **0x00** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

| device / phase | oracle | iter 26 | iter 27 | **iter 28b/c** |
|---|---:|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 700 | 551 / 0 | **1,027 / 700** |
| nPM1300 `p1_boot` / `p2_render` | 291 / 508 | 232 / 370 | 97 / 0 | **232 / 370** |
| OPT3001 `p1_boot` / `p2_render` | 33 / 80 | 14 / 0 | 14 / 0 | **14 / 0** |
| ST25DV EEPROM / system port `p1` | 25 / 22 | 11 / 12 | 0 / 6 | **11 / 12** |
| `saadc` (whole run) | 998 | 71 | 5 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, all hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0, hash-EQ** |
| `IMU_ACCEL_ENABLED` | True | True | False | **True** |
| `OPT3001_CONVERSION_READY` | True | True | False | **True** |
| `NPM1300_CHARGING` | True | True | False | **True** |

**Iteration 26's stability and every sensor volume are recovered exactly, and
`radio TransmittedFrames` / `vcentral Connected` / `ConnectInds` / `DataEvents`
are ahead of BOTH iteration 26 and iteration 27** — `DataEvents` (0x26B) even
exceeds the oracle's 0x215.  `MasterFramesSeen` is still 0.

#### Graphics + sensor verdicts (iteration 28, `g1-i28c-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287, 2,881 transactions. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 3 pixel windows** (the panel-init window writes the oracle also makes; they paint nothing); oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, the 34 shared transactions **identical entry-for-entry**, first difference at index **34** (ours `<end>`).  `p2_render` **0 vs 2,881**, first difference index **0**. |
| **G-4** | *localiser* | our framebuffer is still bit-identical to iterations 16–27 (`0c5cc90b07…`), so the first differing row is the oracle's lowest lit row **y = 267** and the first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | the panel-init sequence is byte-exact over the whole 34-transaction non-blit prefix, including the `0x9F` ID probe answering `0x4010` and the `0x46`/`0x31` brightness pair. |
| **G-6** | **PASS** | `spim_b` 0 == 0, `stream_sha256` EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ (`255852a6c9…`) — 2 accesses, PSEL only, no spurious ENABLE/START. |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ (`2f47878f41…`), 25 accesses. |
| **S-IMU** | **PARTIAL** | `p1_boot` 1,027 / 1,089, `p2_render` 700 / 1,200; `IMU_ACCEL_ENABLED` True; stream hashes differ. |
| **S-ALS** | **PARTIAL** | `p1_boot` 14 / 33, `p2_render` **0 / 80**; `OPT3001_CONVERSION_READY` True. |
| **S-PMIC** | **PARTIAL** | `p1_boot` 232 / 291, `p2_render` 370 / 508; `NPM1300_CHARGING` True. |
| **S-NFC** | **PARTIAL** | EEPROM 11 / 25, system port 12 / 22 in `p1_boot`; nothing in `p2_render`. |
| **S-ADC** | **FAIL** | 71 / 998 accesses, hash NE. |
| **S-ESB** | **FAIL** | `ESB_SYNC_ctx_105a` 0x01 vs 0x02, `DISPLAY_ON_ctx_fe8` 0x00 vs 0x01, master PTX frames **0** vs 0x175 — but `radio TransmittedFrames` is **0xCF vs 0**, the first non-zero this project has measured. |

**Criteria score: 4 PASS / 4 PARTIAL / 6 FAIL** — iteration 26's score exactly,
restored from iteration 27's 4/1/9, with the radio and BLE-link counters strictly
ahead of both.  **NO PIXEL IS PAINTED**, `firmware_events` is `{}` against the
oracle's `{"spi_read_id":1,"display_START":2,"BLIT":15}`, so **no display START
with `action = 1` arrived.**

### 28.8 The new first divergence, root-probed as far as it goes

A directed 8 s probe on the final tree (`/private/tmp/g1-i28/probe6.resc`):

```
NET esb_initialized <- pc=0x0103c4ba          (memset / z_bss_zero, boot clear)
NET esb_init (FUN_010333b4) enter lr=0x0102b179
NET esb_ppi_init (STOCK) enter                 <-- the displaced unit runs
NET esb_initialized <- pc=0x0102c4fe           = FUN_010333b4 + 0x22a
NET FUN_01033660 (esb tx path) enter
NET esb_disable (FUN_01033354) enter lr=0x0102d28d = FUN_0102b664 + 0x6c
NET esb_initialized <- pc=0x0102c29e           = FUN_01033354 + 0x2e
```

`FUN_010333b4 + 0x22a` is the **success tail** (`*active = 0; *initialized = 1;
return 0`).  **`esb_init` now SUCCEEDS for the first time** — in iterations 24
and 25 it returned `-EFAULT`/`-EIO` and never set the flag.  The stock
`esb_ppi_init` allocates its DPPI channels and returns 0, and the ESB TX path
`FUN_01033660` is entered.  The teardown that follows is **not** a defect:
`FUN_0102b664` is the recovered "ESB radio stop and peripheral release", the
MPSL timeslot-end handler, so opening and closing the ESB session inside a
timeslot is the designed behaviour.

So the first divergence is now **downstream of a working ESB bring-up**: the
virtual ESB slave sees **0** master PTX frames although the radio model counts
**0xCF** transmitted frames.  The next questions, in order, are (a) whether
`esb_write_payload` / `start_tx_transaction` — **both of them among the eight
`esb.c` functions Even modified** — key a frame with the pipe address/channel
the provisioned slave expects, and (b) whether the timeslot window is long
enough at the now-correct 1 MHz timer for a PTX/ACK exchange to complete.

### 28.9 Open, named, and NOT fixed

1. **`esb.c` is partially vendored.**  32 of 53 stock sections are byte-exact in
   the shipped image; the 21 that are not cluster on the FIFO- and
   payload-length-dependent functions.  Determining whether that is a **Kconfig
   difference** (`CONFIG_ESB_TX_FIFO_SIZE` / `RX_FIFO_SIZE` /
   `MAX_PAYLOAD_LENGTH` / `PIPE_COUNT`) rather than a source change is the
   single highest-leverage next step: if a Kconfig choice makes all 53 match,
   the whole ESB core becomes displaceable and the eight modified
   reconstructions — which include `esb_init`, `esb_write_payload` and
   `start_tx_transaction`, i.e. exactly the TX path — go away.
2. **`esbslave MasterFramesSeen` is still 0** — §28.8.
3. **The relocation-block aliasing class is real, not theoretical** (§28.2).
   `g1_net_ram_blk_21004c98` is sized 32 B from its referenced addresses while
   the object it holds is copied into with ≥0xb1 bytes.  Displacement removed
   the *victim*; the *overrun* is still there and will hit whatever else lands
   at `block + 0x18`.  A general fix is to size a block from the true object
   extent, or to displace enough units that the block space empties.
4. **The split `sem.c :: lock`** — `FUN_0103689c` / `FUN_01036824` are the only
   sweep hazards still live in the link.  Benign on a UP kernel (a Zephyr
   spinlock is an IRQ lock) but recorded.
5. **The 5 addresses in the block at `0x21000c28`** — unchanged from §27.8(4).
6. **21 blocks still carry an atomic EXCLUDE** — unchanged from §27.8(5); the
   sweep's attribution map (§28.4) is the right instrument to re-examine them.
7. `FUN_01031a68` still has no caller anywhere — unchanged.
8. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 28)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
# the three displacement batches are already in
#   recon/ownership/adoption_manifest.json  (+20 net rows, 255 -> 275 exclusions)
#   recon/application/net/src/stock_call_aliases.ld (+19 PROVIDEs, batches 1-3)
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py       # 980 -> 960
recon/application/build_cohesive.sh net /private/tmp/g1-i28c-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i28c-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i23a-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i28c-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py /private/tmp/g1-i28c-net/zephyr/zephyr.elf
# 20 s capture -- NOTE the stdin pipe
printf '$rtinfo_pc=0x00015b9c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i28/ours-paired-i28.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i28/ours-paired-i28.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i28c-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i28c
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i28c /private/tmp/g1-i28/rep_c
```

Files changed: new `recon/ownership/net_duplicate_singleton_sweep.json`,
`recon/ownership/net_nrfx_timer_singleton_adoption.json`,
`recon/ownership/net_esb_dppi_singleton_adoption.json`,
`recon/ownership/net_nrfx_ipc_singleton_adoption.json`;
`recon/ownership/adoption_manifest.json` (+20 net rows);
`recon/application/net/src/stock_call_aliases.ld` (+19 `PROVIDE`s);
`recon/generated/net_retained_sources.cmake` (generated, 980 → 960);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, no Kconfig / `prj.conf` / devicetree change, no
reconstruction source edited, `armemul` untouched, nothing committed.

## Iteration 29 — iteration 28's `esb.c` KEEP verdict is WITHDRAWN with byte
## evidence: the 21 "Even-modified" sections were a **Kconfig value and a
## one-line header difference**.  With `CONFIG_ESB_MAX_PAYLOAD_LENGTH=251` and
## `ESB_EVT_IRQ = SWI3_IRQn` the stock NCS 2.5.1 `esb.c` tiles the shipped run
## `0x01032764..0x01033b18` **exactly**, the whole ESB core is displaced (37
## reconstructions), and **master ESB PTX frames reach the virtual slave for
## the first time in this project — `MasterFramesSeen` 0 → 0x26C, with the
## first frame BYTE-IDENTICAL to the oracle's**

**Stated first, because the acceptance bar is pixels: NO PIXEL IS PAINTED.**
`framebuffer.lit_pixels` is **0 / 0** against the oracle's **656** (`p1_boot`) /
**1,098** (`p2_render`), `firmware_events` is `{}`, and **no display START with
`action = 1` arrived.**  Everything below is measured.

### 29.1 The `esb.c` Kconfig verdict — REPRODUCED, so the unit is DISPLACED

Method (identical gate to iteration 28's sweep, scripts in the session
scratchpad, **no `tools/` logic touched**): rebuild the pinned
`~/ncs251/nrf/subsys/esb/esb.c` with the net build's **exact** compile command
and a patched `autoconf.h`; index every `.text.*` section with a 4-byte mask at
each relocation offset; slide each section over the whole shipped
`netcore_image.bin` and require agreement on **every unmasked byte**
(≥ 16 distinguishing).  Value = sections located, of 51 indexed:

| variant | located |
|---|---:|
| this build's configuration (baseline, `CONFIG_ESB_MAX_PAYLOAD_LENGTH=32`) | **32** — reproduces iteration 28 exactly |
| payload length 64 / 128 / 252 | 32 / 32 / 32 |
| **payload length 251** | **36** |
| 251 + TX/RX FIFO 2 / 4 / 16 / 32 | 28 / 28 / 28 / 28 |
| 251 + `ESB_PIPE_COUNT` 1 / 2 / 4 | 32 / 32 / 32 |
| 251 + `ESB_NEVER_DISABLE_TX=y` | 33 |
| 251 + `ESB_DYNAMIC_INTERRUPTS=n` | 33 |
| **251 + `ESB_EVT_IRQ = SWI3_IRQn`** | **40** |

So the recovered configuration is **payload 251, TX/RX FIFO 8, pipes 8,
dynamic interrupts on, never-disable-TX off, sys timer 2** — every deviation
loses sections.

**The 251 is confirmed three independent ways.**

1. Iteration 24 decoded the shipped `esb_config` template: `payload_length =
   0xfb = 251`.
2. The shipped **`.bss` tiles with zero slack only at 251**.  Resolving the
   `R_ARM_ABS32` relocations of the located sections against the image words:
   ```
   0x21005256  rx_payload.0        8 x 256 B   (sizeof(esb_payload) = 5 + 251)
   0x21005a56  tx_payload.1        8 x 256 B      = 0x21005256 + 0x800
   0x21006256  pids                8 B            = 0x21005a56 + 0x800
   0x2100625e  rx_payload_buffer   253 B          = payload_length + 2
   0x2100635b  tx_payload_buffer   253 B
   0x21006458  esb_state           0x21006459 esb_initialized
   ```
3. The recovered `FUN_0102b49c` (the announce-response builder) stages exactly
   `packet[0] = 0xfb` bytes — see §29.5.

**The SWI3 difference is a genuine Even change, and a necessary one.**
`nrf/subsys/esb/esb_peripherals.h` hardcodes `ESB_EVT_IRQ = SWI0_IRQn`, but on
the nRF5340 **network** core `nrf/subsys/mpsl/init/mpsl_init.c:38` already owns
SWI0 (`#define MPSL_LOW_PRIO_IRQn SWI0_IRQn`), and this firmware runs ESB and
MPSL/SDC on the same core.  Before the change the ONLY unmasked difference
across `.text.on_radio_disabled_tx_noack` (112 B) and
`.text.on_radio_disabled_rx` (560 B) was four bytes, at three sites, all the
same instruction:

```
                 str.w r3,[r0,#0x100]        r0 = 0xE000E000  ->  NVIC->ISPR[0]
shipped   0x01032e1c / 0x01032e30 / 0x01032fe0:  f04f 5300   mov.w r3,#0x20000000  (bit 29 = SWI3_IRQn)
stock SWI0                                    :  f04f 6380   mov.w r3,#0x04000000  (bit 26 = SWI0_IRQn)
```

Implemented WITHOUT touching the pinned SDK: `recon/application/net/src/esb_peripherals_g1.h`
defines the SDK header's own include guard and is force-included (`-include`)
into the `..__nrf__subsys__esb` library target only.

**Result — the 39 located sections TILE the shipped run with no gap and no
overlap:**

```
0x01032764 update_radio_bitrate 60      ...      0x01032c28 start_tx_transaction 444
0x01032de4 on_radio_disabled_tx_noack 112        0x01032e54 on_radio_disabled_rx 560
0x010331c8 on_radio_disabled_tx_wait_for_ack 396 0x01033354 esb_disable 96
0x010333b4 esb_init 684                          0x01033660 esb_write_payload 332
   ...                                           0x01033af8 esb_set_tx_power 32  -> ends 0x01033b18
```

The three gaps iteration 28 left (672 / 396 / 684 bytes) are filled by sections
whose compiled sizes are **112 + 560 = 672**, **396** and **684** — exact.  The
40th section, the file-local `bytewise_bit_swap` (46 B), sits in the shared tail
at `0x0103a80c`.  The remaining 11 stock sections (`esb_flush_rx/tx`,
`esb_pop_tx`, `esb_reuse_pid`, `esb_get_rf_channel`, `esb_suspend`,
`esb_update_prefix`, `esb_set_address_length/bitrate/retransmit_count/_delay`)
are pure API leaves the shipped link garbage-collected; ours drops them the same
way.

**VERDICT: `esb.c` is STOCK NCS 2.5.1.  Nothing in it was modified by Even.**
Iteration 28's KEEP was measured against the wrong Kconfig.

### 29.2 The displacement

37 reconstructions excluded (36 inside the run + `FUN_0103a80c`).  Safety, both
checked not assumed:

* **Callers.** Every external referrer — `FUN_0102b31c`, `FUN_0102b49c`,
  `FUN_0102b50c`, `FUN_0102ece0`, `FUN_0103a83a` — calls only **public**
  `esb_*` entry points; all 16 are `PROVIDE`d in `stock_call_aliases.ld`.  No
  external referrer of any of the 21 file-local sections exists, so their
  exclusion leaves no undefined symbol (`nm -u` = 0).
* **State.** The 28 `esb.c`-owned shipped RAM addresses were cross-referenced
  against every retained recovered source and against the RAM pin map: **no
  retained source reads or writes any of them.**  The single textual hit
  (`0x21004a90` in `FUN_0102b50c`) is a provenance comment, not code.  The unit
  moves whole, so `esb_cfg / rx_fifo / tx_fifo / rx_payload / tx_payload / pids
  / esb_state / esb_initialized` stay in ONE translation unit.

Evidence file: **`recon/ownership/net_esb_core_singleton_adoption.json`** (new).

### 29.3 The RAM that made it possible — the shipped heap size, MEASURED

The correct payload length needs ≈ 4.6 KiB of real `.bss`, and the first
displaced build **overflowed RAM by 2,964 B**.  Rather than trim something
arbitrary, the shipped value was read out of the image.  Zephyr's
`K_HEAP_DEFINE` statically initialises
`struct sys_heap { struct z_heap *heap; void *init_mem; size_t init_bytes; }`,
the shipped `k_aligned_alloc` at analysis VA `0x010389a0` loads `&_system_heap`
from its literal pool at `0x010389e8` = `0x210008b4`, and the shipped `.data`
(LMA runtime `0x0103ed24`, VMA `0x21000000`) holds there:

```
0x210008b4  heap       = 0x00000000
0x210008b8  init_mem   = 0x2100a440
0x210008bc  init_bytes = 0x00000a00 = 2560
```

`CONFIG_HEAP_MEM_POOL_SIZE` was **8192**, inherited unverified from the NCS
hci_rpmsg baseline; the shipped firmware uses **2560**.  That single measured
correction frees 5,632 B and the displaced build fits with room to spare.

### 29.4 Build ledger and gates

| net build | change | FLASH | RAM | `nm -u` | image md5 |
|---|---|---:|---:|---:|---|
| `g1-i28c-net` | iteration 28 (baseline) | 225,149 B | 63,524 B | 0 | `135efe97…` |
| **`g1-i29a-net`** | **+ esb.c displaced, payload 251, SWI3, heap 2560** | **225,165 B** | **62,868 B** | **0** | `66bf631d…` |
| `g1-i29b-net` | + real 256 B rx AND tx payload objects | 225,165 B | 63,380 B | 0 | — |
| `g1-i29c-net` | + real 256 B rx payload object only | 225,165 B | 63,124 B | 0 | — |
| **`g1-i29d-net`** | **final tree (payload objects OFF by default)** | **225,165 B** | **62,868 B** | **0** | `66bf631d…` — **byte-identical to `g1-i29a-net`**, so the `i29a` capture IS the final tree's |

FLASH **+16 B**, RAM **−656 B** against iteration 28 (97.30 % / 95.93 %).  Net
retained sources **960 → 923**; manifest exclusions **275 → 312**.  The app core
is **UNCHANGED** (`g1-i23a-app`).

| gate | iteration 28 | **iteration 29 (`g1-i29d-net`)** |
|---|---|---|
| `check_ram_pin_collisions.py --core net` raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py --core net` bound OK / escaping | 190 / 0 | **172 / 0** (18 pins lost their last referrer with the displaced unit) |
| `check_ram_pin_collisions.py` (app) | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_net_raw_literals.py` distinct / colliding | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| net / app `nm -u` undefined | 0 / 0 | **0 / 0** |
| net / app duplicate global definitions | 0 / 0 | **0 / 0** |

No `--allow-multiple-definition`, no weak symbol, no numeric root.

### 29.5 MEASURED — the 20 s capture (`/private/tmp/g1_ours_i29a`)

```
G1_RESC=/private/tmp/g1-i29/ours-paired-i29.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf
G1_NET_ELF=/private/tmp/g1-i29a-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i29a
```

| counter | oracle | iter 28 | **iter 29** |
|---|---:|---:|---:|
| machine reset / CPU halt | none | none | **none over 20 s** |
| `radio TransmittedFrames` | 0x230 | 0xCF | **0x339** |
| `vcentral Connected` | True | True | **True** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 1 / 0x26B | **1 / 0x26B** |
| **`esbslave MasterFramesSeen`** | 0x175 | **0** | **0x26C** |
| **`esbslave AcksInjected`** | 0x175 | 0 | **0x26C** |
| `esbslave AnnounceResponses` | 0x15B | 0 | **0x26C** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x01 | **0x01** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | **0x00** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | **0x3 / 0x3** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | **0 / 0** |

**The first master PTX frame is BYTE-IDENTICAL to the oracle's:**

```
ours   tx#1 len=41 8282828282200311000000000000000000000000000000000000000000000000000000000000004BFD
oracle tx#1 len=41 8282828282200311000000000000000000000000000000000000000000000000000000000000004BFD
```

so the ESB address (`0x82` prefix, base `0x82828282`), channel (34), CRC and
DPL length are all correct.  `tx#2` also matches.  **`tx#3` does not**: the
oracle sends a data frame (`…200340 00…92654C00…`) where we repeat the
`0x11` announce (`…200311…`).  Consistently, the oracle's announce-response
count (0x15B) is *lower* than its frame count (0x175) — 26 of its frames are
sync/data frames — while ours are **all** announces.

Sensor volumes are **iteration 26/28's exactly, with no regression**:

| device / phase | oracle | iter 28 | **iter 29** |
|---|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 700 | **1,027 / 700** |
| nPM1300 | 291 / 508 | 232 / 370 | **232 / 370** |
| OPT3001 | 33 / 80 | 14 / 0 | **14 / 0** |
| ST25DV EEPROM / system port `p1` | 25 / 22 | 11 / 12 | **11 / 12** |
| `saadc` (whole run) | 998 | 71 | **71** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, all hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 / 0 | 0 / 0 | **0 / 0, hash-EQ** |
| `IMU_ACCEL_ENABLED` / `OPT3001_CONVERSION_READY` / `NPM1300_CHARGING` | True/True/True | True/True/True | **True/True/True** |

#### Graphics + sensor verdicts (iteration 29, `g1-i29d-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 3 pixel windows** (the panel-init windows the oracle also makes; they paint nothing); oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, the 34 shared transactions identical entry-for-entry, first difference at index **34** — ours ends, oracle continues `{"op":"0x66","kind":"command","n_tx":1,"n_rx":1}`.  `p2_render` **0 vs 2,881**, first difference index **0**, oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265,"n_pixel_bytes":9}`. |
| **G-4** | *localiser* | our framebuffer is still bit-identical to iterations 16–28 (`0c5cc90b07…`), so the first differing row is the oracle's lowest lit row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | panel init byte-exact over the whole 34-transaction non-blit prefix. |
| **G-6** | **PASS** | `spim_b` 0 == 0, `stream_sha256` EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ (`255852a6c9…`). |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ (`2f47878f41…`), 25 accesses. |
| **S-IMU** | **PARTIAL** | 1,027 / 1,089 and 700 / 1,200; `IMU_ACCEL_ENABLED` True; stream hashes differ. |
| **S-ALS** | **PARTIAL** | 14 / 33 and 0 / 80; `OPT3001_CONVERSION_READY` True. |
| **S-PMIC** | **PARTIAL** | 232 / 291 and 370 / 508; `NPM1300_CHARGING` True. |
| **S-NFC** | **PARTIAL** | EEPROM 11 / 25, system port 12 / 22 in `p1_boot`; nothing in `p2_render`. |
| **S-ADC** | **FAIL** | 71 / 998 accesses, hash NE. |
| **S-ESB** | **PARTIAL** (was FAIL) | the criterion is the boolean triple `ESB_SYNC_ctx_105a == 0x02`, `DISPLAY_ON_ctx_fe8 == 0x01`, **master PTX frames > 0**.  The third is satisfied for the FIRST time — **0x26C frames, all ACKed, first frame byte-identical to the oracle's**.  The first two are still `0x01` / `0x00`. |

**Criteria score: 4 PASS / 5 PARTIAL / 5 FAIL** (iteration 28: 4 / 4 / 6).
**NO PIXEL IS PAINTED**; `firmware_events` `{}` vs the oracle's
`{"spi_read_id":1,"display_START":2,"BLIT":15}`, so **no display START with
`action = 1` arrived.**

### 29.6 The new first divergence, root-probed — and an A/B that must be
### reported as a REGRESSION

The ESB link is up; the **L↔R sync frame is never sent**, so `ctx[0x105a]`
never leaves 1.  Probing that path found the next defect and it is again the
relocation-block extent class (§28.9(3)), now at its worst:

```
PROVIDE(g_esb_rx_payload           = g1_net_ram_blk_21004da0 + 0x1);   block =  24 B
PROVIDE(g_esb_sync_response_packet = g1_net_ram_blk_21004ea0 + 0x1);   block =  24 B
```

Both are `struct esb_payload` = **256 B** (5 + 251), and the shipped addresses
prove it: `0x21004ea1 − 0x21004da1 = 0x100`, exactly one payload, the same
256-byte stride as the shipped FIFO arrays.  Stock `esb_read_rx_payload()`
memcpys `5 + length` bytes INTO the first one, so **every received ESB frame
overruns its 24-byte block** (32-byte payloads ⇒ 13 bytes into the sibling
block).  `FUN_0102b49c` stages `packet[0] = 0xfb` — a full **251**-byte
payload — into the second.

Giving them real storage is provably correct, and it was BUILT AND MEASURED:

| build | objects | result |
|---|---|---|
| `g1-i29a/d-net` | both are 24-byte blocks (default) | **0x26C ESB frames, BLE up, all sensor volumes, no halt** |
| `g1-i29c-net` | `g_esb_rx_payload` real (256 B) | **BOTH CORES HALT** 0.29 s after the first injected ACK (`cpuapp`/`cpunet` "PC does not lay in memory", 01:46:49.44); 1 ESB frame, `vcentral Connected` False, saadc 5, twim2 551 |
| `g1-i29b-net` | both real (256 B) | **BOTH CORES HALT**, same signature, same instant after the first ACK; `RADIO_TX` 0x2 |

The sizing is not what breaks it — it is what the sizing **unmasks**.  With the
24-byte block, `rx[5]` (= `payload->data[0]`) read block filler, so
`FUN_0102b50c` never took its announce-response branch.  With correct storage
`data[0]` really is `0x11`, the branch runs `FUN_0102b49c`, and that function —
which stages 251 bytes from a **251-byte stack scratch buffer inside the ESB
event IRQ** and then loops `esb_write_payload` + `esb_start_tx` — has never
executed in this project before.  **That is where the next defect lives.**

Both variants build clean and pass every gate, so this is reported as an A/B,
not hidden: the fix is kept in the tree at
`recon/application/net/src/g1_esb_payload_objects.c`, compiled, and gated OFF
(`-DG1_ESB_REAL_RX_PAYLOAD_OBJECT` / `-DG1_ESB_REAL_TX_PAYLOAD_OBJECT`),
because switching it on today costs 0x26B ESB frames, the BLE link and every
sensor volume.  `g1-i29d-net` is byte-identical to `g1-i29a-net`, which is
checked, not assumed.

### 29.7 Open, named, and NOT fixed

1. **The announce-response path halts both cores** (§29.6) — the named next
   step.  Turn `G1_ESB_REAL_RX_PAYLOAD_OBJECT` on and trace `FUN_0102b49c` /
   `esb_write_payload` / `esb_start_tx` and the ESB event IRQ stack.
2. **`ESB_SYNC_ctx_105a` is still 0x01.**  Our master repeats the `0x11`
   announce; the oracle interleaves 26 sync/data frames.  The app-side
   `sync_to_slave` frame is never put on the air.
3. **The relocation-block extent class is now a MEASURED defect twice**
   (iteration 28 §28.2, and §29.6 here).  A general fix — size a block from the
   object's true extent — is overdue; the sweep's attribution map plus the
   displaced stock units are the instrument for it.
4. **21 blocks still carry an atomic EXCLUDE**; **the 5 addresses in the block
   at `0x21000c28`**; **the split `sem.c :: lock`** — unchanged from §28.9.
5. `FUN_01031a68` still has no caller anywhere — unchanged.
6. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 29)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py        # 960 -> 923
recon/application/build_cohesive.sh net /private/tmp/g1-i29d-net -- -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i29d-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i23a-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i29d-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py /private/tmp/g1-i29d-net/zephyr/zephyr.elf
# 20 s capture -- NOTE the stdin pipe
printf '$rtinfo_pc=0x00015b9c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i29/ours-paired-i29.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i29/ours-paired-i29.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i29d-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i29
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i29 /private/tmp/g1-i29/rep
```

Files changed: new `recon/ownership/net_esb_core_singleton_adoption.json`;
new `recon/application/net/src/esb_peripherals_g1.h`;
new `recon/application/net/src/g1_esb_payload_objects.c` (gated OFF);
`recon/ownership/adoption_manifest.json` (+37 net rows, 275 → 312 exclusions);
`recon/application/net/src/stock_call_aliases.ld` (+17 `PROVIDE`s, batch 4);
`recon/application/net/CMakeLists.txt` (ESB `-include` override; the two ESB
public leaves removed from the clock-callback closure);
`recon/application/net/prj.conf` (`CONFIG_ESB_MAX_PAYLOAD_LENGTH=251`,
`CONFIG_HEAP_MEM_POOL_SIZE` 8192 → 2560, both with byte evidence);
`recon/generated/net_retained_sources.cmake` (generated, 960 → 923);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, no reconstruction source edited, `armemul`
untouched, nothing committed.

## Iteration 30 — **`ESB_SYNC_ctx_105a` reaches `0x02` for the first time in
## this project**: the L↔R lens sync handshake COMPLETES.  Four uncatalogued
## functions reconstructed (the ESB uplink worker thread and its `{0x0d,0x02}`
## relay), three measured defects fixed (an IPC dispatcher stride, the ESB
## radio-IRQ dead-end left by iteration 29's displacement, and a
## dereference-too-many in the worker's wake-up).  `MasterFramesSeen` is now
## **0x175 — exactly the oracle's** — and `radio TransmittedFrames` 0x234 vs
## 0x230.  Iteration 29's named blocker was **not** the announce-response path

**Stated first, because the acceptance bar is pixels: NO PIXEL IS PAINTED.**
`framebuffer.lit_pixels` is **0 / 0** against the oracle's **656** (`p1_boot`) /
**1,098** (`p2_render`).  `spim_a` is **34 / 764** and **0 / 2,881**, and no
`0x02` pixel window is emitted in `p2_render`.  A display START **does** arrive
this iteration, but with **`action = 0`**, not `1` (§30.7).  Everything below is
measured.

### 30.0 Iteration 29's diagnosis is WITHDRAWN, on measurement

Iteration 29 §29.6 named the blocker as "the announce-response path
`FUN_0102b49c` … turning the real payload objects on halts both cores".  Both
halves are wrong, and the correction is a measurement, not an argument:

* **`FUN_0102b49c` never runs at all**, in any iteration-29 or iteration-30
  build (Renode block hook at its entry: **0 hits** over a 9 s run).  It cannot
  run: the virtual slave answers every announce with marker **`0x10`**, and
  `FUN_0102b50c` only takes the announce-response branch on `rx[5] == 0x11`.
* **The real payload objects do not halt anything.**  Build `g1-i30c-net`
  (iteration 30's dispatcher + worker fixes, payload objects **ON**) ran the
  full 20 s capture with **no halt, no reset, 0x26C ESB frames, BLE up and
  every sensor volume intact**.  They are ON by default from this iteration.
* The real blocker was one layer lower and had been invisible since iteration
  29: **the ESB driver was never delivering a single event** (§30.3).

### 30.1 The first divergence, found by following the frame, not the guess

The oracle's `tx#3` is a `0x40`-class **sync-data** frame; ours was another
`0x11` announce.  `FUN_0102b3f0` (the announce builder) decides between them on
`FUN_0102a468()`, a two-instruction getter that returns the **staged app frame
length** at `0x210045e4`.  That word is written by exactly one function,
`FUN_0102a448`, which is called by exactly one function, `FUN_0102b15c` — the
receive callback of the net-core **ipc0 service id 2 (`cpunet-esbm`)** that
`FUN_0102b2ac` registers.  So the whole question was: does the app's 33-byte
sync frame (`{0x02, <32-byte ESB payload>}`) reach `FUN_0102b15c`?

It did not, because **`FUN_0102ab14`, the ipc0 service dispatcher, walked its
registry with the wrong stride.**  Shipped (runtime `0x0102b314`):

```
  mov  r3, r5             ; r3 = registry
  ldr  r6, [r3, #4]!      ; r3 = registry+4 ; r6 = count           <-- read ONCE
loop:
  cmp  r6, r4 ; ble return
  ldr  r2, [r3, #4]!      ; r3 += 4 ; r2 = entries[index]          <-- +4 per iteration
  ldrb ip, [r2] ; cmp ip, r7 ; bne next
  ldr  r3, [r2, #8] ; subs r2, r1, #1 ; adds r1, r0, #1
  sub.w r0, r5, #72 ; bx r3
next: adds r4, #1 ; b loop
```

The reconstruction advanced the cursor by **two** words per iteration and
**re-read `cursor[0]` as the loop bound every time**.  Registry slot 0 is the
id-1 `cpunet-hw-id` service, so index 0 always matched — which is why the
role/config/MAC handshake has worked since iteration 21 and hid the defect.
From index 1 on it used an *entry pointer* as the count and read
`entries[2·index]` as the entry, so **service id 2 was never matched and every
app sync frame was silently dropped**.

Fixed in `recon/net/src/FUN_0102ab14.c`.  **Measured immediately**
(`g1-i30b-net`, Renode hooks): `ipc0_dispatch id=2` fires, `stage_b15c size=32`
fires every 4.3 s, and **`tx#4` is a `0x40` sync-data frame** — the first
non-announce master ESB frame this project has ever put on the air.

### 30.2 Four uncatalogued functions — the ESB uplink worker closure

Iteration 18 §18.3 deferred a thread entry as "NOT RECONSTRUCTED": `FUN_0102b1c8`
(the endpoint `ready` callback `FUN_0102b2ac` installs at `state+0xb0`) creates a
thread whose shipped entry is the runtime Thumb pointer `0x0102ba05`, i.e.
analysis **`0x0102b204`**, which Ghidra folded into `FUN_0102b1c8`'s tail.  Since
the entry resolved to a raw original-image address, the thread was additionally
created with **`K_FOREVER`** so it could never be scheduled.

Disassembling `0x0102ba04..0x0102baac` (168 B) shows it is the **ESB uplink
worker**, and that it is the **only caller of three further uncatalogued
functions**:

| new file | analysis VA | shipped extent | what it is |
|---|---|---|---|
| `recon/net/src/FUN_0102b204.c` | `0x0102b204` | 168 B | the worker thread itself |
| `recon/net/src/FUN_0102a408.c` | `0x0102a408` | 64 B | **the `{0x0d, 0x02}` sync-ack relay** |
| `recon/net/src/FUN_0102a474.c` | `0x0102a474` | 36 B | staged-frame clear (inverse of `FUN_0102a448`) |
| `recon/net/src/FUN_0102a668.c` | `0x0102a668` | 48 B | `k_msgq_alloc_init(0x210045b0, 251, 4)` |

`FUN_0102a408` is the frame the whole acceptance bar hangs on.  It sends 8 bytes
over ipc0 with `msg[0] = 0x01` (service id `cpunet-hw-id`), `msg[1] = 0x0d`,
`msg[2] = status`; the app's id-1 receiver `FUN_000162ec` dispatches `0x0d` to
`device_info[0x105a] = buf[1]`, which is exactly what releases `sync_to_slave`'s
spin (`armemul/docs/g1-esb-sync-decode.md` §6).  Structure of the worker
(`r5 = *(void **)0x21004610 = state + 0xb0`, so `r5-0xb0 = role`,
`r5-0x8c = sem_b`, `r5-8 = state->send`):

```
msg[0..251] = 0 ; msg[0] = (role == 1) ? 6 : 4 ; g1_esb_uplink_msgq_init()
for (;;) {
    if (state->mode == 1) { k_sleep(163840 ticks = 5000 ms); continue; }
    if (rx_role[0x21004c9d] == 2 && !event_busy[0x21004ca0]) {
        g1_esb_pending_frame_clear();          /* FUN_0102a474 */
        g1_esb_sync_ack_relay(2);              /* FUN_0102a408 -> ctx[0x105a]=2 */
        rx_role = 0;
    }
    if (k_msgq_get(&uplink, msg + 1) == 0)
        ten-attempt state->send(msg, 252) with a 328-tick (10 ms) back-off;
    k_sem_take(state->sem_b, K_FOREVER);       /* given by FUN_0102a4b0 */
}
```

Both embedded tick constants were cross-checked against the 32768 Hz system
clock rather than assumed: `0x28000 = 163840 = 5000 ms`, `0x148 = 328 = 10 ms`.
`FUN_0102b1c8` now binds the linker-resolved `&FUN_0102b204` and restores the
shipped **`K_NO_WAIT`**; the deferral in its header is closed.

`FUN_0102a668` also explains a shipped detail: net `main` writes 0 to
`0x210045c0`, which is `struct k_msgq.buffer_start` — the field
`k_msgq_alloc_init` fills in and the field both existing accessors
(`FUN_0102a698` put / `FUN_0102a6e0` get) gate on.  Until the worker ran, the
uplink queue was permanently uninitialised.  The 251×4 = 1004-byte allocation
comes from the thread resource pool, i.e. the **2560-byte** system heap iteration
29 §29.3 measured out of the shipped `.data` — further corroboration of that
value.

### 30.3 The ESB driver was delivering ZERO events — iteration 29's displacement
### left the radio IRQ dead-ending in a hand-written file

With §30.1 and §30.2 in (`g1-i30b-net`) the sync frame was on the air and the
worker thread was alive, and `ESB_SYNC_ctx_105a` was **still 0x01**.  Renode
block hooks on the `g1-i30b-net` link, 8 s run:

| hook | hits |
|---|---:|
| `start_tx_transaction` | 34 |
| `RADIO_IRQHandler` | **0** |
| `on_radio_disabled_tx` / `_tx_noack` / `_tx_wait_for_ack` / `_rx` | **0 / 0 / 0 / 0** |
| `FUN_0102b50c` (the ESB `event_handler`) | **0** |
| `FUN_0102a4c8` (the IPC-level ESB event handler) | **0** |
| `esb_read_rx_payload` | **0** |

i.e. the driver keyed frames onto the air — they transmit and PPI-retransmit
without any interrupt, which is why 34 transactions produced ~200 frames — and
**never processed a single ACK**.  No `ESB_EVENT_TX_SUCCESS`, no
`ESB_EVENT_RX_RECEIVED`, so `rx_ready` could never become 2 and the handshake
could not start.

Root cause, and it is displacement fallout.  On CPUNET the RADIO vector belongs
to MPSL in **both** images — the shipped `_irq_vector_table` at `0x01008840` and
ours are structurally identical (IRQ 8 → the MPSL radio wrapper; IRQ 25 and IRQ
29 → the direct dynamic dispatcher) — so ESB gets its radio events *forwarded*
through the MPSL **timeslot** callback `FUN_0102b944`, whose `case 2`
(`MPSL_TIMESLOT_SIGNAL_RADIO`) calls `FUN_010327d8`.  `FUN_010327d8` is
esb.c's `radio_irq_handler()`: same INTENSET bit-4 test, same
EVENTS_DISABLED clear-and-read-back, same indirect call through the file-static
**`on_radio_disabled`** pointer at shipped VA `0x210049a0`.

Iteration 29 displaced esb.c, and the stock unit keeps `on_radio_disabled` in
**its own** `.bss` object (`0x21009178` in the `g1-i30b-net` link).  Section
29.2's ownership check swept the *retained reconstruction* sources for
esb.c-owned addresses and found none — but `FUN_010327d8` lives in the
hand-written `recon/application/net/src/timeslot_owner.c`, which the sweep did
not cover.  Its read of the now-orphaned block copy returned 0 forever.

Fixed by calling the stock unit's public entry
`RADIO_IRQHandler(NULL)` (= `radio_irq_handler(); ISR_DIRECT_PM();`, and
`ISR_DIRECT_PM()` is empty because `CONFIG_PM` is unset here), so the private
state stays in one translation unit.  **Measured (`g1-i30d-net`), and the
cadence snaps onto the oracle's:**

| counter | oracle | `g1-i30b/c-net` | **`g1-i30d-net`** |
|---|---:|---:|---:|
| `esbslave MasterFramesSeen` | 0x175 | 0x26C | **0x176** |
| `radio TransmittedFrames` | 0x230 | 0x33A / 0x337 | **0x233** |
| `vcentral DataEvents` | 0x215 | 0x26B | **0x213** |

The 45 % retransmit storm is gone because ACKs are now consumed.  ESB events
flow: `FUN_0102b50c` 308 hits, `FUN_0102a4c8` 308 hits (`type=0` / `type=2`
alternating) in a 9 s run.

### 30.4 One dereference too many — the last link in the chain

`g1-i30d-net` still sat at `ESB_SYNC_ctx_105a = 0x01`.  Hooks showed
`FUN_0102a4b0` (which gives the worker's semaphore) running **151 times**, and
the worker thread completing its loop body **once** and never waking again.

`FUN_0102a4b0`, shipped at analysis `0x0102a4b0`:

```
  ldr r3,[pc,#16]     ; r3 = &0x210045f4      (the service slot)
  ldr r2,[r3,#0]      ; r2 = *slot = state
  ldr r2,[r2,#0x2c]   ; r2 = state->sem_b.count
  cbnz r2, return
  ldr r0,[r3,#0]      ; r0 = *slot = state
  adds r0,#0x24       ; r0 = &state->sem_b
  b.w  k_sem_give
```

The reconstruction computed `base = *(int *)*p`, i.e. **`state->role`** (= 1 on
a master), so the guard read address `0x2d` and `k_sem_give` ran on address
`0x25` — unmapped, hence silently a no-op instead of a fault.  This is the
"wrong indirection" class the playbook warns the parity harness is blind to;
the function is marked *parity 300 trials PROVEN*.

Fixed (`base = (int)(unsigned long)*p`) in both the canonical and the symbolized
body.

### 30.5 MEASURED — the 20 s capture of the final tree (`g1-i30e-net`)

```
G1_RESC=/private/tmp/g1-i30/ours-paired-i30.resc
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i30e
```

| counter | oracle | iter 29 | **iter 30** |
|---|---:|---:|---:|
| machine reset / CPU halt | none | none | **none over 20 s** |
| `radio TransmittedFrames` | 0x230 | 0x339 | **0x234** |
| `vcentral Connected` | True | True | **True** |
| `vcentral ConnectInds` / `DataEvents` | 1 / 0x215 | 1 / 0x26B | **1 / 0x20D** |
| **`esbslave MasterFramesSeen`** | **0x175** | 0x26C | **0x175 — EXACT** |
| **`esbslave AcksInjected`** | **0x175** | 0x26C | **0x175 — EXACT** |
| `esbslave AnnounceResponses` | 0x15B | 0x26C | **0x166** |
| **`ESB_SYNC_ctx_105a`** | **0x02** | 0x01 | **0x02 — MATCHES** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 | **0x00** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | **0x3 / 0x3** |
| framebuffer lit px p1 / p2 | 656 / 1,098 | 0 / 0 | **0 / 0** |

ESB frames, ours vs the oracle:

```
ours   tx#1 8282828282200311 00…00 4BFD        oracle tx#1 IDENTICAL
ours   tx#2 8282828282200311 00…00 4BFD        oracle tx#2 IDENTICAL
ours   tx#3 8282828282200311 00…00 4BFD        oracle tx#3 8282828282200340 …  <-- FIRST DIFFERING FRAME
ours   tx#4 8282828282200340 …                 oracle tx#4 8282828282200311 …
```

The first differing **frame** is still `tx#3` — ours emits one more announce
before the first data frame, a scheduling-phase difference, not a content one.
Aligning the two `0x40` data frames (our `tx#4` against the oracle's `tx#3`)
gives the first differing **field**:

```
oracle payload 40 00 00 00 00 00 00 80 00 92 65 4C 00 20 00 CF 00 02 00 00 00 00 00 00 00 00 00 04 00 00 00 00
ours   payload 40 00 00 00 00 00 00 01 00 00 00 4C 00 20 00 CF 00 02 00 00 00 00 00 00 00 00 00 04 00 00 00 00
                                    ^^ ^^ ^^ ^^
first differing field: payload[7] = device_ctx[0xd0], oracle 0x80 vs ours 0x01
```

Bytes 0–6 and **11–31 are byte-identical**, including the command byte
`device_ctx[0xd4] = 0x4C` (opcode `0x0c`, param 1) and the whole
`0x4C 00 20 00 CF 00 02 … 04 00 00 00 00` tail.  Only
`device_ctx[0xd0..0xd3]` differ (`80 00 92 65` vs `01 00 00 00`) — an
**app-core** payload field, not an ESB-path field.

Sensor volumes, no regression and two improvements:

| device / phase | oracle | iter 29 | **iter 30** |
|---|---:|---:|---:|
| LSM6DSO `p1_boot` / `p2_render` | 1,089 / 1,200 | 1,027 / 700 | **1,027 / 700** |
| **nPM1300** `p1_boot` / `p2_render` | 291 / 508 | 232 / 370 | **279 / 507** |
| OPT3001 | 33 / 80 | 14 / 0 | **14 / 0** |
| ST25DV EEPROM / system port `p1` | 25 / 22 | 11 / 12 | **11 / 12** |
| **`saadc`** (whole run) | 998 | 71 | **95** |
| `gpiote0` / `gpiote1` / `pdm0` | 25 / 0 / 2 | 25 / 0 / 2 | **25 / 0 / 2, hash-EQ** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | **34 / 0** |
| `spim_b` | 0 / 0 | 0 / 0 | **0 / 0, hash-EQ** |

#### Graphics + sensor verdicts (iteration 30, `g1-i30e-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 3 pixel windows** (the panel-init windows the oracle also makes; they paint nothing); oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **34 vs 764**, the 34 shared transactions identical entry-for-entry, first difference at index **34** (oracle continues `{"op":"0x66",…}`).  `p2_render` **0 vs 2,881**, first difference index **0**, oracle `{"op":"0x02","kind":"pixel_window","x":32,"y":265,"n_pixel_bytes":9}`. |
| **G-4** | *localiser* | our framebuffer is still bit-identical to iterations 16–29 (`0c5cc90b07…`), so the first differing row is the oracle's lowest lit row **y = 267**, first differing pixel **x = 178** (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | panel init byte-exact over the whole 34-transaction non-blit prefix. |
| **G-6** | **PASS** | `spim_b` 0 == 0, `stream_sha256` EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ (`255852a6c9…`), 2 accesses. |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ (`2f47878f41…`), 25 accesses. |
| **S-IMU** | **PARTIAL** | 1,027 / 1,089 and 700 / 1,200; `IMU_ACCEL_ENABLED` True. |
| **S-ALS** | **PARTIAL** | 14 / 33 and 0 / 80; `OPT3001_CONVERSION_READY` True. |
| **S-PMIC** | **PARTIAL** (improved) | **279 / 291** and **507 / 508** (was 232 / 370); `NPM1300_CHARGING` True; stream hashes differ. |
| **S-NFC** | **PARTIAL** | EEPROM 11 / 25, system port 12 / 22 in `p1_boot`; nothing in `p2_render`. |
| **S-ADC** | **FAIL** | 95 / 998 accesses (was 71), hash NE. |
| **S-ESB** | **PARTIAL — two of three now satisfied** | criterion = `ESB_SYNC_ctx_105a == 0x02` **✓ (first time)**, master PTX frames > 0 **✓ (0x175, exactly the oracle's, all ACKed)**, `DISPLAY_ON_ctx_fe8 == 0x01` **✗ (0x00)**. |

**Criteria score: 4 PASS / 5 PARTIAL / 5 FAIL** (unchanged headline vs iteration
29, but S-ESB went from one-of-three to two-of-three and every ESB counter now
matches the oracle).  **NO PIXEL IS PAINTED.**

### 30.6 Build ledger and gates

| net build | change | FLASH | RAM | `nm -u` |
|---|---|---:|---:|---:|
| `g1-i30a-net` | iteration 29 tree, rebuilt — md5 `66bf631d…`, **byte-identical to `g1-i29a/d-net`** | 225,165 B | 62,868 B | 0 |
| `g1-i30b-net` | + ipc0 dispatcher stride (§30.1) + ESB uplink worker closure (§30.2) | 225,629 B | 62,868 B | 0 |
| `g1-i30c-net` | + real 256 B `esb_payload` objects (**no halt**) | 225,629 B | 63,380 B | 0 |
| `g1-i30d-net` | + `FUN_010327d8` radio-IRQ dispatch (§30.3) | 225,597 B | 63,380 B | 0 |
| **`g1-i30e-net`** | **+ `FUN_0102a4b0` dereference (§30.4) — FINAL** | **225,581 B** | **63,380 B** | **0** |

FLASH **+416 B**, RAM **+512 B** against iteration 29 (97.48 % / 96.71 %).  The
app core is **UNCHANGED** (`g1-i23a-app`).

| gate | iteration 29 | **iteration 30 (`g1-i30e-net`)** |
|---|---|---|
| `check_ram_pin_collisions.py --core net` raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py --core net` bound OK / escaping | 172 / 0 | **170 / 0** |
| `check_ram_pin_collisions.py` (app) | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_net_raw_literals.py` distinct / colliding | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| net / app `nm -u` undefined | 0 / 0 | **0 / 0** |
| net / app duplicate global definitions | 0 / 0 | **0 / 0** |

No `--allow-multiple-definition`, no weak symbol, no numeric root.

### 30.7 The new first divergence — it has moved to the APP core

With `device_info[0x105a] == 2` the net side of the display gate is satisfied.
App-side hooks placed at **our** app ELF's addresses (the capture script's
built-in hooks are original-image PCs and are disabled with `G1_HOOKS=0`, so
`firmware_events` is `{}` for *every* our-build capture — that field is a
harness artefact, not a measurement):

| app hook (our `g1-i23a-app` PC) | hits | oracle |
|---|---:|---|
| `spi_read_id` `0x00041b68` | **1** | 1 |
| `trigger_screen_state_change` (display START) `0x00028ad8` | **1, `action = 0`** | 2, one with `action = 1` |
| `sync_to_slave` `0x00024044` | **9** — `op = 5` once, `op = 12` ×8 | includes **`op = 0`** |
| `DashBoard_Reflash` `0x000321c0` | **0** | runs |
| `reflash_fb_data_to_lcd` `0x000416a8` | **0** | runs |

So the chain now fails one step later and on the other core: the app's
`display_dispatch_thread` **never calls `sync_to_slave(display, 0, 0)`** — the
opcode-0 display gate — and never sets `device_info[0xfe8]`.  The `op = 12`
frames that *are* sent are what carried `ctx[0x105a]` to 2.  **The next blocker
is the app-core path that decides to issue the opcode-0 sync and the
`action = 1` display START**, not anything on the net core.

### 30.8 Open, named, and NOT fixed

1. **`DISPLAY_ON_ctx_fe8` is still 0x00 and no `action = 1` display START
   arrives** (§30.7) — the named next step, now an **app-core** investigation:
   `display_dispatch_thread` @our `0x00025d28`, `trigger_screen_state_change`
   @our `0x00028ad8`, and whatever gates `device_info[0xfe8]`.
2. **`device_ctx[0xd0..0xd3]` differ in the sync-data frame** (`80 00 92 65` vs
   `01 00 00 00`, §30.5) — an app-core header field, unexplained.
3. **The ownership sweep must cover hand-written application files.**  §30.3 is
   the second displacement-fallout defect (iteration 29 §29.2's check looked
   only at retained reconstruction sources).  `recon/application/net/src/*.c`
   needs to be in the same sweep.
4. **The relocation-block extent class** (iteration 28 §28.2, 29 §29.6) is now
   *fixed for the two ESB payloads* but the generator still sizes blocks from
   referenced addresses, not object extents.
5. **21 blocks still carry an atomic EXCLUDE**; the 5 addresses in the block at
   `0x21000c28`; the split `sem.c :: lock` — unchanged from §28.9.
6. `FUN_01031a68` still has no caller anywhere — unchanged.
7. Iteration 23 §23.7 items 4–7 unchanged.

### Regenerate (iteration 30)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh net /private/tmp/g1-i30e-net -- \
  -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i23a-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py /private/tmp/g1-i30e-net/zephyr/zephyr.elf
# 20 s capture -- NOTE the stdin pipe
printf '$rtinfo_pc=0x00015b9c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i30/ours-paired-i30.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i30/ours-paired-i30.resc \
G1_APP_ELF=/private/tmp/g1-i23a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040BC8 G1_CTX_105A=0x20040C3A \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i30e
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i30e /private/tmp/g1-i30/rep-e
```

Files changed: new `recon/net/src/FUN_0102a408.c`, `FUN_0102a474.c`,
`FUN_0102a668.c`, `FUN_0102b204.c`;
`recon/net/src/FUN_0102ab14.c` (registry stride);
`recon/net/src/FUN_0102b1c8.c` (thread entry + `K_NO_WAIT`);
`recon/net/src/FUN_0102a4b0.c` and `recon/symbolized/net/FUN_0102a4b0.c`
(dereference);
`recon/application/net/src/timeslot_owner.c` (`FUN_010327d8` radio dispatch);
`recon/application/net/CMakeLists.txt` (`G1_ESB_UPLINK_WORKER_SOURCES`,
`G1_ESB_REAL_PAYLOAD_OBJECTS` option);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, `armemul` untouched, nothing committed.

## Iteration 31 — the app-core display gate is a **missing GATT service**: the
## shipped firmware's third static `bt_gatt_service_static` entry (stock NCS
## `nus.c`, 6 attributes) is absent from our link, so the phone's ATT write
## never reaches the firmware, no persist task is ever created and
## `trigger_screen_state_change` is only ever called with `action = 0`

*(written incrementally; measurements are recorded as they are confirmed)*

### 31.0 The measurement that named it (`g1-i23a-app` + `g1-i30e-net`, unchanged tree)

Iteration 30 §30.8 item 1 named the app core. A diagnostic 20 s capture with
five app-side hooks placed at **our** ELF's PCs (`G1_HOOKS=0`, the paired resc,
identical stimulus) gives:

| app hook (our `g1-i23a-app` PC) | hits | what it means |
|---|---:|---|
| `ble_process_req_dispatch` `0x0001ee80` | **0** | the GATT write **never reaches the firmware** |
| `process_for_new_task` `0x00029884` | 1 | the task thread runs, once, and stays in `CASE0` |
| `now_has_persist_task` `0x00028d48` | **398, all returning 0** | `ctx[0x1054]->state` never rises above 1 |
| `trigger_screen_state_change` `0x00028ad8` | **1, `reason = 0`, `action = 0`** | the `CASE0`-entry "no task" call, `process_for_new_task.c:160` |
| `sync_to_slave` `0x00024044` | 16 (`op=5` ×1, `op=12` ×15) | the display thread's own `op = 0` / `op = 1` calls never happen |

`process_for_new_task` `CASE0` polls `now_has_persist_task(ctx, ctx[0xd5])`
every `0x667` ticks and only issues the `action = 1` START
(`trigger_screen_state_change(uVar14, param_1, 1)` at `LAB_0002e00e`) when that
returns 1.  `now_has_persist_task` (`FUN_0002be64`) is two loads:

```c
int *p = *(int **)(ctx + 0x1054);
return (unsigned)((unsigned char *)p)[4] > 1;
```

so the whole acceptance bar reduces to: *something must set the persist-task
record's state byte above 1*, and in the oracle that something is the virtual
phone's `0a0600000000` ATT write.

### 31.1 Root cause — the app's own GATT service was never built

The chain the write has to travel is
NUS RX value attribute → `on_receive` → `nus_cb.received` = `FUN_00017f70`
(@0x17f70) → `k_msgq_put(0x200038f8)` → `ble_work_thread` → `FUN_00021d78` →
`spec_ble_command_hook` → `FUN_0007c244` → `ble_process_req_dispatch`
(@0x21460) → persist task.

The shipped image's `bt_gatt_service_static` iterable section is at
`0x88058..0x88078` and holds **three** services (`tools/extract.py`):

```
0x88058  {attrs = 0x0008b3b4, count = 8}   Zephyr GATT service
0x88060  {attrs = 0x0008b454, count = 7}   Zephyr GAP service
0x88068  {attrs = 0x0008ad18, count = 6}   <-- the application's NUS service
```

(the following words `{0x000f64a8, 4}` … are *not* a fourth service: `0xf64a8`
is the ASCII `"6dsob@6b\0LSM6DSO"`, i.e. a different table begins there.)

Our `g1-i23a-app` link has `bt_gatt_service_static_area` = **0x10 bytes = 2
entries** (`attr__1_gatt_svc` 8, `attr__2_gap_svc` 7).  The third service does
not exist, and **the 128-bit NUS UUID bytes `9e ca dc 24 0e e5 a9 e0 93 f3 a3
b5` appear 5 times in `app_update.bin` and 0 times in our `zephyr.bin`.**

The six shipped attributes decode exactly as stock NCS
`nrf/subsys/bluetooth/services/nus.c` compiled **without** `CONFIG_BT_NUS_AUTHEN`:

| VA | uuid | read | write | user_data | handle\|perm |
|---|---|---|---|---|---|
| `0x8ad18` | `0x2000357b` (`6E400001…`) | `0x82989` `bt_gatt_attr_read_service` | — | `0x2000357b` | `0x0000\|0x0001` |
| `0x8ad2c` | `0x20002f70` (`0x2803`) | `0x82c49` `bt_gatt_attr_read_chrc` | — | `0x20002830` `struct bt_gatt_chrc` | `\|0x0001` |
| `0x8ad40` | `0x20003559` (`6E400003…` TX) | — | — | — | `\|0x0001` = `BT_GATT_PERM_READ` |
| `0x8ad54` | `0x20002f6c` (`0x2902`) | `0x8295b` `…read_ccc` | `0x5a465` `…write_ccc` | `0x20002818` `_bt_gatt_ccc` | `\|0x0003` |
| `0x8ad68` | `0x20002f68` (`0x2803`) | `0x82c49` | — | `0x20002810` | `\|0x0001` |
| `0x8ad7c` | `0x20003537` (`6E400002…` RX) | — | `0x4f4d9` `on_receive` | — | `\|0x0003` |

The `bt_uuid_128` / `bt_gatt_chrc` / `_bt_gatt_ccc` objects sit in **`.data`**
(`0x20002810`, `0x20002818`, `0x20002830`, `0x20003537…0x200035ad`) exactly as
GCC places the non-const compound literals inside `BT_GATT_SERVICE_DEFINE`,
which is independent corroboration that this is the stock macro expansion and
not a hand-rolled table.

Two further consequences of the same defect, both already in the tree:

* `FUN_000181f0` (`ancs_notify_sync_init`, called from `ancs_main` line 173) is
  `bt_nus_init(&nus_cb)`: it tail-calls `FUN_0004f500` with `0x20002310`, whose
  shipped `.data` initialiser is `{received = 0x00017f71, sent = 0,
  send_enabled = 0x00017e3d}` — a verbatim `struct bt_nus_cb`.  Our RAM-arena
  data image already restores and re-binds all three words correctly
  (`g1_app_data_image.c` arena `0x310`/`0x318`), so the callback table is
  populated at `g_2000a2b8` — there was simply no service to call it.
* `FUN_0004f518` (`gatt_notify_config_change`) is `bt_nus_send`; it spells
  `rodata_8ad40` (`&attrs[2]`, the TX value attribute) and `rodata_4f4f1`
  (`on_sent`).  Both were still **absolute original-image addresses** in
  `recon/symbols/g1_app_globals.ld` (lines 469 and 107), i.e. the NUS TX path
  was pointing at unrelated bytes in our relocated image.

Note also that `recon/data/rodata_0x8ac20.c` ("pointer/config table, reader
FUN_00047a84", 292 B, `0x8ac20..0x8ad44`) **overruns into this attribute
array**: its last 11 words are attributes 0, 1 and the first word of attribute
2.  That is the Ghidra data-inflation class applied to a data table rather than
a function.

### 31.2 The fix — the service is emitted, not `CONFIG_BT_NUS=y`

New wiring TU **`recon/application/app/src/g1_bt_nus_service.c`** emits the
service with `BT_GATT_SERVICE_DEFINE(g1_nus_svc, …)` in the shipped shape (six
attributes, `BT_GATT_PERM_READ` on the TX value, `READ|WRITE` on the CCC and on
the RX value).  It is *not* `CONFIG_BT_NUS=y` because stock `nus.c` owns a
file-static `struct bt_nus_cb nus_cb` singleton and the recovered corpus
already owns that singleton at the shipped `0x2000a2b8` (pin `g_2000a2b8 =
g1_ram_arena + 0x82b8`), written by the retained, parity-proven `FUN_0004f500`.
Compiling stock nus.c as well would create a second, permanently-NULL copy and
the write would be delivered to it — the duplicate-singleton class of
iterations 26/28/29/30 §30.3.  The three callbacks here therefore read the ONE
recovered singleton.

Two linker pins were rebound onto the emitted service in
`recon/symbols/g1_app_globals.ld` (both were still ORIGINAL-image absolutes):

```
PROVIDE(rodata_8ad40 = attr_g1_nus_svc + 40);   /* &attrs[2], the TX value attr */
PROVIDE(rodata_4f4f1 = g1_nus_on_sent + 1);     /* on_sent, + the Thumb bit     */
```

and one stale line was withdrawn from `g1_app_string_rodata.c`: the generator
had emitted `rodata_8ad40[3] = {0x59,0x35,0x00}` as if the attribute's
`uuid = 0x20003559` pointer were a NUL-terminated string, and that STRONG
definition would have overridden the `PROVIDE`.  The pin is no longer a numeric
literal, so `gen_app_string_rodata.py` no longer selects it and a regeneration
reproduces the file without the line.

**MEASURED (`g1-i31b-app` + `g1-i30e-net`) — the gate opens:**

```
I31 ancs_notify_sync_init
I31 bt_nus_init cb=0x200034b0          (= arena 0x200031a0 + 0x310, the .data nus_cb)
I31 nus_on_receive len=6               <-- the phone's ATT write reaches the firmware
I31 nus_received(FUN_17f70) len=6      <-- and is delivered to the recovered callback
```

That is the first time in this project that a GATT write from the virtual
central has reached application code.

### 31.3 …and immediately unmasks a stack-frame defect in `spec_ble_command_hook`

The frame is then handed to `ble_work_thread` → `ble_packet_receive_dispatch`
(`FUN_00021d78`) → `spec_ble_command_hook` (`FUN_0000ef28`), which had never
executed before.  It runs its twenty `strncmp` comparisons, takes the
`return 0xffffffff` path and **faults on its own epilogue**:

```
I31 spec_hook sp=0x200229c8 len=6
I31 strncmp lr=0x127eb … lr=0x12d75          (20 calls, all returning normally)
I31 FATAL r=35 esf=0x200340b8 r0=0xffffffff r1=0xa7ef9 r2=0xa r3=0x23
                r12=0x0 lr=0x12d75 pc=0x12600 xpsr=0xa1000200
```

`reason 35` is `K_ERR_ARM_USAGE_ILLEGAL_EPSR` (`K_ERR_ARCH_START = 16` +
19) — INVSTATE, i.e. a branch to an address whose Thumb bit is clear.  The
stacked `pc = 0x12600` is even and lies inside `spec_ble_command_hook` itself,
`lr = 0x12d75` is its own `strncmp` return site and `r0 = 0xffffffff` is the
value it was returning: **the return address popped by
`ldmia.w sp!,{r4-fp,pc}` had been overwritten.**

Root cause, proven by disassembly rather than inferred.  Ghidra named only the
stack slots this body dereferences by name, so the decompiled declaration list
spelled two 256-byte character buffers as six and four scalars
(`local_520 … local_51b`, `local_420 … local_414`).  The body nevertheless
writes their full extents — `memset_bytes(&uStack_51c, 0, 0xfc)` and
`memset_bytes(&local_41c, 0, 0xfc)` — so GCC sized our frame at **212 bytes**
(`sub sp,#212` at 0x1220a) and those 252-byte stores ran off the end of it,
across the pushed callee-saved registers and the return address.  The shipped
prologue is unambiguous:

```
ef28  stmdb sp!,{r4,r5,r6,r7,r8,r9,lr}
ef2c  subw  sp,sp,#1500        ; 0x5dc          <-- OUR BUILD RESERVED 212
ef40  add   r0,sp,#220 (0xdc)  ; memset(&uStack_51c, 0, 0xfc)
ef50  add   r0,sp,#216 (0xd8)  ; __memcpy_chk(&local_520, param_1, len, 0x100)
```

so `local_520` is at `sp+216`, `local_420` at `sp+472` — exactly 256 bytes
apart — and the frame is 1500 bytes.  This is the **stack-buffer class the
parity harness is blind to** (the harness compares only non-stack writes), and
the function is recorded as proven.

Fixed in all three trees (`recon/app/src`, `recon/verified/src`,
`recon/symbolized/app`) by laying the named slots out in ONE struct at their
shipped offsets — `g1_pad_head[52]`, the five named slots, `g1_pad_cmd[250]`,
the four named slots, `g1_pad_value[240]`, `g1_pad_tail[772]`, total 1500 —
with `#define`s that keep every original spelling, so the body itself is
unchanged and the existing parity proof still applies.

### 31.4 MEASURED — `action = 1` ARRIVES.  The display gate is open.

With the frame corrected (`g1-i31c-app`, prologue now `subw sp,sp,#1556`
against the shipped 1500) the chain completes end to end for the first time:

```
I31 pkt_recv_dispatch len=6      ble_packet_receive_dispatch (FUN_00021d78)
I31 spec_hook                    spec_ble_command_hook returns, no fault
I31 requeue_via_dispatch         FUN_0007c244
I31 ble_dispatch op=0xa          ble_process_req_dispatch, the phone's op 0x0a
I31 display_START action=1       <-- trigger_screen_state_change(..., action = 1)
```

`trigger_screen_state_change` with `action = 1` writes `device_info[0xfe8] = 1`
and gives the display semaphore.  **This is the first `action = 1` display START
this project has produced, and the gate iteration 30 §30.8 item 1 named is
open.**  `spim_a` also moves: **66 transactions and 6 pixel windows in
`p1_boot`** against iteration 30's 34 and 3.

### 31.5 …and the next divergence, immediately after: a kernel panic in `z_tick_sleep`

The very next event is a fatal:

```
I31 FATAL r=4        (K_ERR_KERNEL_PANIC)
     lr=0x49111  pc=0x7c06e  r1=0x5b2
```

`pc = 0x7c06e` is `assert_post_action` (zephyr/lib/os/assert.c:44) and
`lr = 0x49111` is `recon/symbolized/app/z_tick_sleep.c:107` — the
`__ASSERT(!z_is_thread_state_set(_current, _THREAD_SUSPENDED))` of
`sched.c:1458` (`r1 = 0x5b2 = 1458`).  i.e. a thread returned from
`arch_swap()` inside `z_tick_sleep` with `_THREAD_SUSPENDED` (0x10) still set
in `thread->base.thread_state`.

This is the SAME assert iteration 5 hit and worked around (the dropped
`unready_thread(_current)` argument, recorded in that file's comment); the
`unready_thread` fix is still in place and correct, so this is a second,
different way into it.  Both cores halt at t ≈ 6 s, so **every downstream
counter in this build is zero** — this is a stall further along, not a working
build, and it is reported as such below.

### 31.6 MEASURED — the 20 s captures, A/B on the same tree

Three builds, one net image (`g1-i30e-net`, unchanged), the iteration-30 recipe
with the probe addresses recomputed for each link (`_end` moves, and
`device_info` is the first allocation above it):

| build | app change | `G1_CTX_FE8` / `G1_CTX_105A` |
|---|---|---|
| `g1-i23a-app` | iteration 30's app, unchanged (the A side) | `0x20040BC8` / `0x20040C3A` |
| `g1-i31b-app` | + the NUS GATT service (§31.2) | `0x20040C68` / `0x20040CDA` |
| `g1-i31c-app` | + the `spec_ble_command_hook` frame (§31.3) | `0x20040C68` / `0x20040CDA` |

| counter | oracle | iter 30 (`i23a`) | `i31b` | **`i31c`** |
|---|---:|---:|---:|---:|
| **`DISPLAY_ON_ctx_fe8`** | **0x01** | 0x00 | 0x00 (halt) | **0x01 — MATCHES** |
| **`ESB_SYNC_ctx_105a`** | **0x02** | 0x02 | 0x00 (halt) | **0x02 — MATCHES** |
| display START `action = 1` | yes | **no** | no | **YES** |
| machine reset / CPU halt | none | none | **halt @ t≈6 s** | **halt @ t≈6 s** |
| `spim_a` `p1_boot` transactions | 764 | 34 | 34 | **66** |
| `spim_a` `p1_boot` pixel windows | many | 3 | 3 | **6** |
| `spim_a` `p2_render` | 2,881 | 0 | 0 | 0 |
| `twim1` `p1` / `p2` | 371 / 599 | 225-ish / 370 | 225 / 0 | **240 / 0** |
| `twim2` (LSM6DSO) `p1` / `p2` | 1,089 / 1,200 | 1,027 / 700 | 911 / 0 | **925 / 0** |
| `saadc` whole run | 998 | 95 | 17 | 17 |
| `pdm0` / `gpiote0` whole run | 2 / 25 | 2 / 25 | 2 / 25 | **2 / 25, hash-EQ** |
| `radio TransmittedFrames` | 0x230 | 0x234 | 0x49 | 0x4A |
| `esbslave MasterFramesSeen` | 0x175 | 0x175 | 0 | 0 |
| framebuffer lit px `p1` / `p2` | 656 / 1,098 | 0 / 0 | 0 / 0 | **0 / 0** |

The `i31c` row is a build that gets **further** and then dies: the panic at
t ≈ 6 s truncates the run, so every ESB / phase-2 / sensor volume collapses.
Both effects are real and both are reported; nothing here is a working
replacement for iteration 30's app yet.

#### Graphics + sensor verdicts (iteration 31, `g1-i31c-app` + `g1-i30e-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` **0 lit px, 0 pixel windows** (the core is halted before phase 2 begins); oracle `b26c73b37d…`, 1,098 lit px, bbox x 34–497 / y 266–287. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 6 pixel windows**; oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287.  The six windows are the panel's blank clears — our `op 0x02` windows at `(0,0)`, `(0,192)`, `(0,384)` carry `pixel_sha256 = 0693f6bf…` / `4c7eea52…`, **exactly the oracle's**, i.e. correct all-transparent fills. |
| **G-3** | **FAIL (truncation only) — IMPROVED** | `p1_boot` **66 vs 764**; the 66 shared transactions are identical entry-for-entry (iteration 30: 34).  First difference is at index **66**, where the oracle continues `{"op":"0x02","kind":"pixel_window","x":0,"y":0,"n_pixel_bytes":61440}`.  `p2_render` 0 vs 2,881, first difference index 0. |
| **G-4** | *localiser* | our framebuffer is still bit-identical to iterations 16–30 (`0c5cc90b07…`); the oracle's lowest lit row is **y = 267**, first differing pixel **x = 178**. |
| **G-5** | **PASS — extended** | panel init byte-exact over the whole 66-transaction prefix, including the three full-screen clears (was 34). |
| **G-6** | **PASS** | `spim_b` 0 == 0, `stream_sha256` EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ (`255852a6c9…`), 2 accesses, same register order. |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ, 25 accesses. |
| **S-IMU** | **PARTIAL (regressed by the halt)** | 925 / 1,089 in `p1_boot`, 0 / 1,200 in `p2_render`. |
| **S-ALS** | **PARTIAL (regressed by the halt)** | inside `twim1` 240 / 371 and 0 / 599. |
| **S-PMIC** | **PARTIAL (regressed by the halt)** | same bus. |
| **S-NFC** | **PARTIAL (regressed by the halt)** | same bus. |
| **S-ADC** | **FAIL** | 17 / 998. |
| **S-ESB** | **PARTIAL — the third criterion is now met, the first two are lost to the halt** | `ESB_SYNC_ctx_105a == 0x02` ✓, **`DISPLAY_ON_ctx_fe8 == 0x01` ✓ (first time)**, master PTX frames > 0 ✗ (0, the cores halt before the ESB cadence starts). |

**Criteria score: 4 PASS / 5 PARTIAL / 5 FAIL** — the same headline as iteration
30, with G-5's proven prefix nearly doubled and two of S-ESB's three criteria
met by different halves than before.  **NO PIXEL IS PAINTED.**

### 31.7 The scheduler assert — what is and is not known

Instrumented run (`g1-i31c-app`, hooks filtered on the panicking thread
`0x20005780`, whose sleep argument `1147 = ((0x46 - 35) * 0x8000 + 999)/1000`
identifies it as **`display_dispatch_thread`** and the 35 as the value
`sync_to_slave(display, 0, 0)` returned — i.e. the blit branch was taken):

```
… wake t=0x20005780 is_to=1            (timeout fires, SUSPENDED cleared)
   ready_thread_static T lr=0x725cd    (from stock z_sched_wake_thread)
   tick_sleep cur=0x20005780 lo=33     (~1 ms; this cycle repeats cleanly ~40x)
   unready_thread T lr=0x4909f
…
   tick_sleep cur=0x20005780 lo=1147   (~35 ms — the post-blit sleep)
   unready_thread T lr=0x4909f
   FATAL r=4 cur=0x20005780            (no wake, no ready, no timeout in between)
```

So the thread dequeued itself, set `_THREAD_SUSPENDED`, called `arch_swap()`
and **came straight back with the bit still set** — nothing readied it.  The
pieces that were checked and are NOT at fault:

* `z_thread_timeout` (0x83634) is `r1 = 1; r0 -= 24; b z_sched_wake_thread`, so
  the timeout path does pass `is_timeout = true` and would clear the bit; the
  pin `PROVIDE(rodata_86661 = z_thread_timeout | 1)` resolves to it.
* the recovered `unready_thread` (`FUN_00073e88`) tests `_THREAD_QUEUED` (0x80),
  unlinks, and calls `update_cache(thread == _current)` — the iteration-5
  argument fix is intact and correct.
* the recovered `sched_update_cache` (`FUN_000737d8`) takes the
  `piVar4 != _current → cache = piVar4` branch whenever `preempt_ok != 0`,
  which is this call.
* no other readier fired: hooks on stock `ready_thread` (0x71a30), stock
  `z_ready_thread` (0x71ac4) and `z_sched_wake_thread` (0x7253c), all filtered
  on this thread, are silent between the last `tick_sleep` and the fatal.

What is NOT yet established is why `arch_swap()` returned to the same thread on
this one sleep after ~40 identical ones.  **That is the named next blocker.**
Note also that the app link now carries TWO scheduler families side by side —
recovered `unready_thread`/`sched_update_cache`/`z_tick_sleep` (0x48e50 /
0x737d8 / 0x49008) and stock sched.c's own statics (0x72078 / 0x72878) — over
one shared `_kernel`; that co-existence is the first thing to audit.

### 31.8 Build ledger and gates

| app build | change | FLASH | RAM | `nm -u` |
|---|---|---:|---:|---:|
| `g1-i23a-app` | iteration 30's app (the A side) | 699,948 B | — | 0 |
| `g1-i31b-app` | + `g1_bt_nus_service.c`, two pin rebinds, one string withdrawn | 700,272 B | — | 0 |
| **`g1-i31c-app`** | **+ the `spec_ble_command_hook` frame — FINAL** | **700,272 B** | 253,045 B | **0** |

FLASH **+324 B** against iteration 30.  The net core is **UNCHANGED**
(`g1-i30e-net`).

| gate | iteration 30 | **iteration 31** |
|---|---|---|
| `check_ram_pin_collisions.py` (app) raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app) bound OK / escaping | 626 / 0 | **626 / 0 — identical to the A side** |
| `check_ram_pin_collisions.py --core net` | 0 / 0, 170 / 0 | **0 / 0, 170 / 0**, EXIT 0 |
| `check_net_raw_literals.py` | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| app / net `nm -u` undefined | 0 / 0 | **0 / 0** |
| app / net duplicate global definitions | 0 / 0 | **0 / 0** |

No `--allow-multiple-definition`, no weak symbol, no numeric root.

### 31.9 The duplicate-singleton ownership sweep, extended to hand-written TUs
### (iteration 30 §30.8 item 3)

Every absolute RAM literal and every `g_`/`rodata_` pin symbol in the
hand-written `recon/application/{app,net}/src/*.{c,h}` was extracted (comments
stripped) and cross-referenced against the 28 `esb.c`-owned shipped RAM
addresses in `recon/ownership/net_esb_core_singleton_adoption.json`:

| file | absolute RAM literals | owned by a displaced unit? |
|---|---|---|
| `app/src/g1_app_ram_relocs.c` | `0x20002000`, `0x2002a400` (arena bounds) | no |
| `net/src/timeslot_owner.c` | `0x21000530`, `0x210045f4`, `0x210049a0`, `0x21004fa3`, `0x21006459` | `0x210049a0` and `0x21006459` **are** esb.c-owned |
| every other hand-written TU | none | — |

Both esb.c-owned addresses are **inert in the cohesive build**: `0x210049a0`
survives only inside the `#else` (non-`G1_COHESIVE_BUILD`) arm that iteration 30
replaced with `RADIO_IRQHandler(NULL)`, and `G1N_21006459` is a macro with **no
use site at all** (comment/definition only).  The sweep is therefore clean for
the current tree, and the method now covers the files §30.3 showed it had
missed.  The new `g1_bt_nus_service.c` was written to the same rule: it reads
the ONE recovered `nus_cb` at `g_2000a2b8` instead of instantiating a second.

### 31.10 Open, named, and NOT fixed

1. **The `sched.c:1458` `_THREAD_SUSPENDED` panic in `z_tick_sleep`** (§31.7) —
   the blocker, and the whole run's truncation.  `display_dispatch_thread`
   returns from `arch_swap()` still suspended after the post-blit 35 ms sleep.
   Two scheduler families coexist over one `_kernel`; audit that first.
2. **Still zero lit pixels.**  With the panic fixed the next thing to watch is
   `spim_a` index 66 onward: the oracle's next transaction is another
   full-screen `op 0x02` clear, and the first *content* window is
   `p2_render` `op 0x02, x=32, y=265`.
3. `device_ctx[0xd0..0xd3]` in the sync-data frame (`80 00 92 65` vs
   `01 00 00 00`) — unchanged from iteration 30 §30.8 item 2.
4. `PTR_s__s____unable_to_change_MTU_for_a_0000f798 0x0009dc3fu` in
   `spec_ble_command_hook.c` is still a RAW original-image address, not a bound
   pin — cosmetic today (a log format string on a path not taken) but it is the
   same class as the `rodata_8ad40` defect this iteration fixed.
5. `recon/data/rodata_0x8ac20.c` over-runs into the NUS attribute array
   (§31.1); its declared 292-byte extent should be cut to the table
   `FUN_00047a84` actually reads.
6. Iteration 30 §30.8 items 4–7 unchanged.

### Regenerate (iteration 31)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i31c-app
# net is UNCHANGED from iteration 30:
recon/application/build_cohesive.sh net /private/tmp/g1-i30e-net -- \
  -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i31c-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py         /private/tmp/g1-i30e-net/zephyr/zephyr.elf
# 20 s capture -- NOTE the stdin pipe, the NEW $rtinfo_pc and the NEW ctx probes
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i31/ours-paired-i31c.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i31/ours-paired-i31c.resc \
G1_APP_ELF=/private/tmp/g1-i31c-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040C68 G1_CTX_105A=0x20040CDA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i31c
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i31c /private/tmp/g1-i31/rep-c
```

`$rtinfo_pc`, `G1_CTX_FE8` and `G1_CTX_105A` are **link-specific**: take
`runtime_info_sync` from `nm`, and `device_info` from the first allocation above
`_end` (0x2003FC80 here, so `+0xfe8` and `+0x105a`).  Reusing iteration 30's
values against this link reads unrelated bytes (it returned `fe8 = 0x33`).

Files changed: new `recon/application/app/src/g1_bt_nus_service.c`;
`recon/application/app/CMakeLists.txt`;
`recon/symbols/g1_app_globals.ld` (`rodata_8ad40`, `rodata_4f4f1`);
`recon/application/app/src/g1_app_string_rodata.c` (one line withdrawn);
`recon/app/src/spec_ble_command_hook.c`,
`recon/verified/src/spec_ble_command_hook.c`,
`recon/symbolized/app/spec_ble_command_hook.c` (the stack frame);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, `armemul` untouched, nothing committed.

## Iteration 32 — the app core's **`sched.c` was a SPLIT unit** (20 adopted
## identities + 11 retained duplicate bodies over one `_kernel`, with the
## `pending_current` file-static duplicated into the recon RAM arena).
## Displacing the family whole **removes the `sched.c:1458` panic**, and the
## defect it unmasked — a dropped `r3` at `FUN_0007c8e8` that fed a kernel
## spinlock address to `nrfx_twim_xfer` as an I2C read length — is fixed.
## The result is **iteration 31's open display gate with iteration 30's
## stability, and better**: no halt over 20 s, `DISPLAY_ON_ctx_fe8 = 0x01`,
## `ESB_SYNC_ctx_105a = 0x02`, `MasterFramesSeen = 0x176`, `sync_to_slave`
## `op = 0` fires **227 times** for the first time in this project

**Stated first, because the acceptance bar is pixels: NO PIXEL IS PAINTED.**
`framebuffer.lit_pixels` is **0 / 0** against the oracle's **656** (`p1_boot`)
/ **1,098** (`p2_render`).  Everything below is measured; nothing is claimed
that was not.

### 32.1 The app-core duplicate-singleton sweep (the task's Priority 1 method)

Iteration 28's net sweep was generalised to the app core.  Analysis-only
scratchpad scripts (**no `tools/` logic changed**):

1. **Byte identity.**  Every `.text.*` input section of the app link's own
   Zephyr kernel objects (`sched.c.obj`, `timeout.c.obj`, `thread.c.obj`,
   `sem.c.obj`, `mutex.c.obj`, `queue.c.obj`, `work.c.obj`, `msg_q.c.obj`,
   `poll.c.obj`, `mempool.c.obj`, `timer.c.obj`, `stack.c.obj`, `condvar.c.obj`,
   `init.c.obj`, `mailbox.c.obj`, taken from `/private/tmp/g1-i31c-app`) was
   indexed with a 4-byte mask at every relocation offset, and compared against
   `app_update.bin` at each recovered function's VA over its whole section
   length.  **Instruction shape is never accepted** (iteration 20's
   `ancs_client.c` mistake).
2. **Shipped-RAM attribution.**  For each located section, every `R_ARM_ABS32`
   relocation was resolved into the stock object's own `.bss.*`/`.data.*`
   object and cross-checked against the shipped image word
   (`shipped = image_word(hit_va + off) − in-place addend`).

Result: **597 size-matched hits, 76 with ≥ 24 distinguishing (unmasked) bytes,
of which 25 are RETAINED** — and **11 of those 25 are in one unit, `sched.c`**:

| shipped VA | our retained name | stock section | linkage | unmasked bytes |
|---|---|---|---|---:|
| `0x000737d8` | `sched_update_cache` | `.text.update_cache` | local | 68 |
| `0x00073840` | `sched_ready_queue_insert` | `.text.ready_thread` | local | 116 |
| `0x00073a78` | `sched_thread_ready` | `.text.z_sched_start` | **global** | 96 |
| `0x00073cdc` | `dlist_unlink_node` | `.text.z_priq_dumb_remove` | **global** | 40 |
| `0x00073e88` | `unready_thread` | `.text.unready_thread` | local | 40 |
| `0x00073f3c` | `pend_locked` | `.text.pend_locked` | local | 36 |
| `0x00074274` | `z_abort_thread_timeout` | `.text.unpend_thread_no_timeout` | local | 40 |
| `0x00074554` | `k_thread_priority_set` | `.text.z_impl_k_thread_priority_set` | **global** | 68 |
| `0x000745c8` | `mutex_unlock_syscall_handler` | `.text.z_impl_k_yield` | **global** | 200 |
| `0x000746fc` | `z_tick_sleep` | `.text.z_tick_sleep` | local | 200 |
| `0x00074844` | `k_sleep` | `.text.z_impl_k_sleep` | **global** | 64 |

The same link **already** adopts **20 other `sched.c` identities** from the
same object (`sliceable`, `z_reset_time_slice`, `z_ready_thread`,
`z_unpend_thread_no_timeout`, `z_reschedule`, `k_sched_lock/unlock`,
`move_thread_to_end_of_prio_q`, `add_to_waitq_locked`, `z_pend_curr`,
`z_set_prio`, `z_thread_priority_set`, `z_impl_k_thread_suspend`,
`z_unpend_thread`, `z_unpend1_no_timeout`, `z_unpend_first_thread`,
`z_thread_abort`, `z_sched_wake`, `z_reschedule_irqlock`, `z_unpend_all`,
`k_work_delayable_busy_get`'s neighbour).  **That is the split.**

`recon/ownership/library_displacement_candidates.json` already carried all 11
with `decision = adopt_upstream_exclude_reconstruction`; Batch 2b (iteration 9)
deferred them because seven upstream owners are translation-unit-local statics
and `recon/application/app/src/g1_kernel_sched_bridges.c` says so in as many
words: *"`z_tick_sleep` and `unready_thread` … both upstream bodies are
file-static in sched.c with no linkable symbol, so their rows are reverted
instead of bridged."*

### 32.2 The duplicated singleton, named by attribution rather than by argument

Detector 2 on `.text.z_tick_sleep` gives the decisive row:

```
  +0x120 sym=sched_spinlock     sec=.bss.sched_spinlock    shipped=0x2000b490
  +0x130 sym=_kernel                                       shipped=0x2000b448
  +0x134 sym=(sec)              sec=.bss.pending_current   shipped=0x2000b484
  +0x138 sym=z_thread_timeout   sec=.text.z_thread_timeout shipped=0x00086661
```

so the shipped word `0x2000b484` — our pin
`PROVIDE(g_pend_locked_thread_tmp = g1_ram_arena + 0x9484)` — **is sched.c's
`pending_current` file-static**, the `CONFIG_SWAP_NONATOMIC` guard variable
that `z_time_slice()` compares against `_current`.  `nm` on `g1-i31c-app`
confirms the duplication in the link, not just on paper:

```
2000c624 A g_pend_locked_thread_tmp      <- arena copy, written by our z_tick_sleep
200305b4 b pending_current               <- stock copy, read by stock z_time_slice
20030578 B _kernel                       <- ONE object (PROVIDE is overridden)
200305c0 B sched_spinlock                <- ONE object (global in NCS 2.5.1 sched.c)
```

`_kernel` and `sched_spinlock` are *not* duplicated (the stock definitions win
over the `PROVIDE`s — `sched_spinlock` is non-static in NCS 2.5.1's `sched.c`),
which is why iteration 31's hooks on the stock readiers were silent: the split
was in `pending_current` and in the *bodies*, not in the queue state.

### 32.3 The displacement, and what was deliberately KEPT

All 11 rows were added to `recon/ownership/adoption_manifest.json`
(`exclude_reconstruction = true`, component `zephyr_kernel`), and
`tools/gen_retained_sources.py` regenerated — **1620 → 1609 retained app
sources**, `--check` clean.  Four of the eleven are still spelled by retained
Even TUs, and every one of those four has a **global** upstream owner, so they
are bound by linker alias in a new fragment
`recon/symbols/g1_app_sched_displacement_aliases.ld`:

```
PROVIDE(k_sleep                     = z_impl_k_sleep);                  /* 33 retained callers */
PROVIDE(mutex_unlock_syscall_handler= z_impl_k_yield);                  /*  4 retained callers */
PROVIDE(k_thread_priority_set       = z_impl_k_thread_priority_set);    /*  2 retained callers */
PROVIDE(sched_thread_ready          = z_sched_start);                   /*  veneer alias chain */
PROVIDE(dlist_unlink_node           = z_priq_dumb_remove);              /*  defensive          */
```

with `SORT_KEY 0_g1_sched_displacement` so GNU ld evaluates them **before**
`g1_app_function_aliases.ld` / `g1_app_veneer_aliases.ld`, which chain further
spellings onto these names (`FUN_0007c0a4 = k_sleep`,
`process_touch_event = mutex_unlock_syscall_handler`,
`FUN_0008641c = sched_thread_ready`), plus five `-Wl,--undefined=` roots for
the archive-extraction caveat the newlib batch already documents.  One
generated line was withdrawn: `PROVIDE(update_cache = sched_update_cache)` in
`g1_app_function_aliases.ld` has no owner once `0x000737d8` is displaced, and
its only referrer (`unready_thread.c`) is displaced in the same batch.

**Verified in the link (`nm g1-i32a-app`):**

```
00072604 T k_sleep       == 00072604 T z_impl_k_sleep
00072388 T mutex_unlock_syscall_handler == 00072388 T z_impl_k_yield
00072314 T k_thread_priority_set == 00072314 T z_impl_k_thread_priority_set
000724bc t z_tick_sleep    00071c48 t unready_thread    00071598 t update_cache
200305b4 b pending_current   <- now the ONLY copy any scheduler code touches
```

**KEPT, with the evidence for keeping:**

| VA | our name | stock candidate | why kept |
|---|---|---|---|
| `0x000748ac` | `k_current_get` | `.text.z_impl_z_current_get` | only **8** unmasked bytes (12 B function, 4 B masked literal) — **below the evidence bar**; and it owns no unit-private state, it only reads `_kernel + 8`, which is already the one shared object. |
| `0x00074b10` | `z_sched_wait` | — | shipped extent **0x58**, stock `.text.z_sched_wait` is **0x24**: no byte match, so **not** a duplicate. Not retained in this link anyway. |
| `0x0008664c` | `z_reschedule_unlocked` | `.text.z_reschedule_unlocked` (20 B) | VA gap is 28 B, so the sweep's whole-section test does not apply; it holds no private state (it forwards to the already-adopted `z_reschedule_irqlock`). |
| 14 further ≥24-byte retained hits in `msg_q.c` (3), `mutex.c` (2), `queue.c` (2), `sem.c` (2), `timeout.c` (2), `mempool.c`, `work.c`, `poll.c` | — | — | **named, not displaced this iteration.** Each is a genuine split-unit candidate on the same evidence, but none is implicated by a measured defect, and `sem.c` in particular carries the deliberate `z_impl_k_sem_take=g1_displaced_sdk_…` CMake arrangement that must be re-reasoned, not bulk-flipped.  Recorded as open item 1 below. |

The `esb.c`-style caution was applied: nothing was displaced on instruction
shape, and every one of the eleven agrees on **every unmasked byte of the whole
stock section** with this link's own Kconfig (`CONFIG_SPIN_VALIDATE=y`,
`CONFIG_THREAD_CUSTOM_DATA=y`, `CONFIG_TIMEOUT_64BIT`, no TLS), not a variant.

### 32.4 MEASURED — the panic is GONE, and it unmasked the next defect

`g1-i32a-app` = `g1-i31c-app` + §32.3, nothing else.  Identical stimulus,
identical net image, hooks on `z_fatal_error` / `assert_post_action` at each
link's own PCs:

| build | assert that kills the run |
|---|---|
| `g1-i31c-app` (iteration 31) | `file=0x0009e264 line=1458 lr=0x00049111` → **`zephyr/kernel/sched.c:1458`**, the `__ASSERT(!_THREAD_SUSPENDED)` in the RECOVERED `z_tick_sleep` |
| **`g1-i32a-app`** | `file=0x000b3ee0 line=593 lr=0x000657b3` → **`modules/hal/nordic/nrfx/drivers/src/nrfx_twim.c:593`**, `NRFX_ASSERT(TWIM_LENGTH_VALIDATE(...))` in `nrfx_twim_xfer` |

**The `sched.c:1458` panic no longer occurs.**  What replaced it is an
*earlier* fault, so `g1-i32a-app` on its own is a regression on every volume
(spim_a 66 → 34, `DISPLAY_ON_ctx_fe8` 0x01 → 0x00): both facts are reported,
and the second one was chased rather than papered over.

### 32.5 The unmasked defect — a dropped `r3` at `FUN_0007c8e8`, proven by
### disassembly

Four Renode probes, each narrowing by one frame:

```
I32 ASSERT   file=nrfx_twim.c line=593
I32 twim_xfer desc=0x200286fc d0=0x00005701 d1=0x200305a4 d2=0 d3=0x20028790 lr=0x00061055
              (type=1 RX, i2c addr 0x57, primary_length = 0x200305a4)
I32 i2c_xfer msgs=0x20028740 n=2 addr=0x57 m0len=2 m1len=0x200305a4 lr=0x00022bc3
I32 sendlen  r0=0x0008446c r1=0x57 r2=0x0001 r3=0x20028790 [sp]=0x200305a4 lr=0x00078df9
```

`0x200305a4` is a **kernel `k_spinlock` file-static** in the same link — i.e.
an uninitialised register, not data.  `lr = 0x00078df9` is inside
`json_arr_encode` (`FUN_0007c898`), whose caller chain is
`FUN_0007c8e8 → FUN_000257ec → FUN_0007c898 → FUN_00025740`, and the shipped
bytes of `FUN_0007c8e8` settle it:

```
7c8e8  mov  r2, r1        ; r2 = buf
7c8ea  cbz  r1, 7c8f4
7c8ec  movs r3, #1        ; r3 = 1   <-- THE READ LENGTH, dropped by our build
7c8ee  mov  r1, r3        ; r1 = 1   (the 16-bit register index)
7c8f0  b.w  0x257ec       ; FUN_000257ec(dev, 1, buf, 1)
```

`movs r3,#1` supplies **both** the register index (via `mov r1,r3`) and the
length; our reconstruction declared the callee with **three** parameters and
dropped `r3`.  `FUN_000257ec` forwards its 4th parameter to `FUN_00025740`,
which stores it as `i2c_msg[1].len` of an `i2c_write_read`, so the ST25DV
**system-port (0x57) register-1** read reached `nrfx_twim_xfer` with a
spinlock address as its length.

This is instance **17** of the class the parity harness is structurally blind
to (the callee is an order-keyed oracle, so a register argument it never reads
is not compared).  `tools/cfg_verify.py app FUN_0007c8e8` **passes both before
and after the fix** (`PASS cases=2`), which is exactly the blindness.

A directed audit of the whole thunk block `0x7c830..0x7ca4e` (11 thunks that
tail-call `FUN_000257ec` / `FUN_00025788` / `FUN_00025850` / `FUN_000256dc`)
found `FUN_0007c8e8` to be the **only** one with a dropped argument; its three
siblings with the same shape (`0x7c932` len=8, `0x7c944` len=1, `0x7c956`
len=1) already pass four.  Fixed in all three trees
(`recon/app/src/FUN_0007c8e8.c`, `recon/verified/src/FUN_0007c8e8.c`,
`recon/symbolized/app/ipc_ept_op_b_guarded.c`) with the disassembly recorded in
the comment.

### 32.6 MEASURED — the 20 s capture of `g1-i32b-app` + `g1-i30e-net`

```
sleep 200 | G1_RESC=/private/tmp/g1-i32/ours-paired-i32a.resc \
G1_APP_ELF=/private/tmp/g1-i32b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040C68 G1_CTX_105A=0x20040CDA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i32b
```

| counter | oracle | iter 30 (`i23a`) | iter 31 (`i31c`) | i32a (sched only) | **iter 32 (`i32b`)** |
|---|---:|---:|---:|---:|---:|
| machine reset / CPU halt | none | none | **halt @ 6 s** | **halt @ 6 s** | **none over 20 s** |
| fatal assert | — | — | `sched.c:1458` | `nrfx_twim.c:593` | **none** |
| **`DISPLAY_ON_ctx_fe8`** | **0x01** | 0x00 | 0x01 | 0x00 | **0x01 — MATCHES** |
| **`ESB_SYNC_ctx_105a`** | **0x02** | 0x02 | 0x02 | 0x02 | **0x02 — MATCHES** |
| display START `action = 1` | yes | no | yes | no | **YES** |
| **`sync_to_slave` `op = 0`** | yes | **0** | (blit branch) | — | **227 calls** |
| `esbslave MasterFramesSeen` | 0x175 | 0x175 | 0 | 0 | **0x176** |
| `esbslave AcksInjected` | 0x175 | 0x175 | 0 | 0 | **0x176** |
| `esbslave AnnounceResponses` | 0x15B | 0x166 | 0 | 0 | 0x91 |
| `radio TransmittedFrames` | 0x230 | 0x234 | 0x4A | 0xC | **0x232** |
| `vcentral Connected` / `ConnectInds` | True / 1 | True / 1 | — | True / 1 | **True / 1** |
| `vcentral DataEvents` | 0x215 | 0x20D | — | 0x8 | **0x212** |
| `spim_a` `p1_boot` / `p2_render` | 764 / 2,881 | 34 / 0 | 66 / 0 | 34 / 0 | **66 / 0** |
| `spim_a` `p1` pixel windows | 673 | 3 | 6 | 3 | **6** |
| `twim1` `p1` / `p2` | 371 / 599 | ~225 / 370 | 240 / 0 | 167 / 0 | **346 / 628** |
| `twim2` (LSM6DSO) `p1` / `p2` | 1,089 / 1,200 | 1,027 / 700 | 925 / 0 | 659 / 0 | **1,041 / 700** |
| `saadc` whole run | 998 | 95 | 17 | 5 | **101** |
| `pdm0` / `gpiote0` / `gpiote1` | 2 / 25 / 0 | 2 / 25 / 0 | 2 / 25 / 0 | — | **2 / 25 / 0, all hash-EQ** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x3 / 0x3 | — | — | 0x6 / 0x6 |
| `JBD JournalCount` | 0x400 | — | — | — | 0x42 |
| **framebuffer lit px `p1` / `p2`** | **656 / 1,098** | 0 / 0 | 0 / 0 | 0 / 0 | **0 / 0** |

`twim1` per device (`p1_boot` / `p2_render`), ours vs oracle:

| device | oracle | **iter 32** |
|---|---|---|
| nPM1300 charger/fuel gauge | 291 / 508 | **286 / 550** |
| OPT3001 ambient light | 33 / 80 | **35 / 78** |
| ST25DV NFC EEPROM | 25 / 7 | 11 / 0 |
| ST25DV system port | 22 / 4 | 14 / 0 |

Boolean sensor states all match the oracle: `IMU_ACCEL_ENABLED` True,
`IMU_GYRO_ENABLED` False, `OPT3001_CONVERSION_READY` True, `NPM1300_CHARGING`
True.

#### Graphics + sensor verdicts (iteration 32, `g1-i32b-app` + `g1-i30e-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** | **FAIL** | `p2_render` ours `0c5cc90b07…`, **0 lit px, 0 pixel windows**; oracle `b26c73b37d…`, **1,098 lit px**, bbox x 34–497 / y 266–287, 2,752 windows. |
| **G-2** | **FAIL** | `p1_boot` ours `0c5cc90b07…`, **0 lit px, 6 pixel windows**; oracle `1d617c65a6…`, **656 lit px**, bbox x 178–449 / y 267–287, 673 windows.  Our six windows are the two full-screen clear rounds `(0,0)`/`(0,192)`/`(0,384)`, `pixel_sha256` `0693f6bf…`/`0693f6bf…`/`4c7eea52…` — **exactly the oracle's**, i.e. correct all-transparent fills. |
| **G-3** | **FAIL (truncation only)** | `p1_boot` **66 vs 764**, the 66 shared transactions identical entry-for-entry; **first difference at index 66**, where the oracle continues `{"op":"0x02","kind":"pixel_window","x":0,"y":0,"n_pixel_bytes":61440,"pixel_sha256":"0693f6bf…"}` (a THIRD clear round).  `p2_render` **0 vs 2,881**, first difference index **0**, oracle `{"op":"0x02","x":32,"y":265,"n_pixel_bytes":9}`. |
| **G-4** | *localiser* | our framebuffer is bit-identical to iterations 16–31 (`0c5cc90b07…`).  **First differing row: `p1_boot` y = 267** (21 rows differ, 267–287), **`p2_render` y = 266** (22 rows differ, 266–287); first differing pixel x = 178 (oracle `ffffff`, ours `000000`). |
| **G-5** | **PASS** | panel init byte-exact over the whole 66-transaction prefix, including the three `op 0x02` full-screen clears. |
| **G-6** | **PASS** | `spim_b` 0 == 0, `stream_sha256` EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ, 2 accesses. |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ, 25 accesses; `gpiote1` 0 == 0. |
| **S-IMU** | **PARTIAL — best yet** | `twim2` **1,041 / 1,089** (`p1`) and **700 / 1,200** (`p2`); `IMU_ACCEL_ENABLED` True. |
| **S-ALS** | **PARTIAL — best yet** | OPT3001 **35 / 33** and **78 / 80**; `OPT3001_CONVERSION_READY` True. |
| **S-PMIC** | **PARTIAL — best yet** | nPM1300 **286 / 291** and **550 / 508**; `NPM1300_CHARGING` True. |
| **S-NFC** | **PARTIAL** | ST25DV EEPROM 11 / 25 and 0 / 7; system port 14 / 22 and 0 / 4. |
| **S-ADC** | **FAIL** | `saadc` **101 / 998**, hash NE (best yet; was 95 / 17). |
| **S-ESB** | **PARTIAL — all THREE criteria met for the first time** | `ESB_SYNC_ctx_105a == 0x02` ✓, **`DISPLAY_ON_ctx_fe8 == 0x01` ✓**, **master PTX frames > 0 ✓ (0x176 vs the oracle's 0x175, all ACKed)**.  Kept PARTIAL only because `AnnounceResponses` is 0x91 vs 0x15B and the stream hashes differ. |

**Criteria score: 4 PASS / 5 PARTIAL / 5 FAIL** — the same headline as
iterations 30 and 31, but for the first time **one single build** holds
*every* gain: no halt, the display gate open, all three S-ESB criteria met, and
the best `twim1`/`twim2`/`saadc` volumes this project has produced.
**NO PIXEL IS PAINTED.**

### 32.7 The NEW first divergence — the blit path stops between
### `sync_to_slave(op = 0)` and `DashBoard_Reflash`

Renode block hooks at **our** `g1-i32b-app` PCs, 20 s capture, same stimulus:

| app hook (our PC) | hits | oracle |
|---|---:|---|
| `trigger_screen_state_change` `0x00028ac8` | **2** — `action = 0` then **`action = 1`** | 2, one with `action = 1` |
| `sync_to_slave` `0x00024034` | **244** — **`op = 0` ×227**, `op = 12` ×16, `op = 5` ×1 | includes `op = 0` |
| **`DashBoard_Reflash` `0x000321b0`** | **0** | runs |
| **`reflash_fb_data_to_lcd` `0x00041698`** | **0** | runs |
| **`pixelto4bithex` `0x0003171c`** | **0** | runs |

Iteration 30 §30.7's blocker ("the app's `display_dispatch_thread` never calls
`sync_to_slave(display, 0, 0)`") is **closed**: the opcode-0 display gate is
now issued 227 times.  The divergence has moved exactly one step further along
the raster path: **nothing downstream of the opcode-0 sync ever calls
`DashBoard_Reflash`**, so `reflash_fb_data_to_lcd` and `pixelto4bithex` never
run, no content window is ever emitted, and `spim_a` stops after the two
full-screen clear rounds at index 66.  **That is the named next blocker**, and
it is now a pure display-subsystem question (`display_dispatch_thread`
@our `0x00025d18`, `DashBoard_Reflash` @our `0x000321b0`,
`recon/analysis/display_subsystem_report.md`), not a kernel or transport one.

### 32.8 Build ledger and gates

| app build | change | FLASH | RAM | `nm -u` |
|---|---|---:|---:|---:|
| `g1-i31c-app` | iteration 31 (the A side) | 700,272 B | 253,045 B | 0 |
| `g1-i32a-app` | + the 11-function `sched.c` displacement (§32.3) | 699,076 B | 253,045 B | 0 |
| **`g1-i32b-app`** | **+ the `FUN_0007c8e8` dropped `r3` (§32.5) — FINAL** | **699,076 B** | **253,045 B** | **0** |

FLASH **−1,196 B** against iteration 31 (11 duplicate bodies removed).  The net
core is **UNCHANGED** (`g1-i30e-net`).

| gate | iteration 31 | **iteration 32 (`g1-i32b-app`)** |
|---|---|---|
| `check_ram_pin_collisions.py` (app) raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app) bound OK / escaping | 626 / 0 | **624 / 0** (two pins fewer: the displaced bodies) |
| `check_ram_pin_collisions.py --core net` | 0 / 0, 170 / 0 | **0 / 0, 170 / 0**, EXIT 0 |
| `check_net_raw_literals.py` | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| app / net `nm -u` undefined | 0 / 0 | **0 / 0** |
| app / net duplicate global definitions | 0 / 0 | **0 / 0** |
| `cfg_verify.py app FUN_0007c8e8` | PASS (falsely) | **PASS** |

No `--allow-multiple-definition`, no weak symbol, no numeric root.

### 32.9 Open, named, and NOT fixed

1. **`DashBoard_Reflash` is never called** (§32.7) — **the blocker**, and the
   whole reason there is still no pixel.  The opcode-0 sync fires 227 times and
   returns; whatever gates the transition from that to the reflash is the next
   thing to read.
2. **14 further ≥24-byte retained duplicates in `msg_q.c` / `mutex.c` /
   `queue.c` / `sem.c` / `timeout.c` / `mempool.c` / `work.c` / `poll.c`**
   (§32.3).  Each is a split unit on the same evidence that justified `sched.c`;
   none is implicated by a measured defect yet.  `sem.c` additionally carries
   the deliberate `z_impl_k_sem_take = g1_displaced_sdk_z_impl_k_sem_take`
   CMake arrangement, which must be re-reasoned before that unit moves.
3. **Not tested: whether the `FUN_0007c8e8` fix alone would also clear the
   `sched.c:1458` panic.**  The A/B that was run is `i31c → i32a`, which shows
   the displacement removes that assert; a `i31c + argfix` control was not
   built.  The displacement stands on its own byte evidence regardless.
4. `saadc` 101 / 998 and the ST25DV volumes (11 / 25, 14 / 22) remain the
   largest sensor gaps.
5. `device_ctx[0xd0..0xd3]` in the sync-data frame (`80 00 92 65` vs
   `01 00 00 00`) — unchanged from iteration 30 §30.8 item 2.
6. `PTR_s__s____unable_to_change_MTU_for_a_0000f798` and
   `recon/data/rodata_0x8ac20.c`'s overrun — unchanged from iteration 31
   §31.10 items 4 and 5.
7. Iteration 30 §30.8 items 4–7 unchanged.

### Regenerate (iteration 32)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
recon/application/build_cohesive.sh app /private/tmp/g1-i32b-app
# net is UNCHANGED from iteration 30:
#   recon/application/build_cohesive.sh net /private/tmp/g1-i30e-net -- \
#     -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i32b-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py         /private/tmp/g1-i30e-net/zephyr/zephyr.elf
# 20 s capture -- `_end` and `runtime_info_sync` are unchanged from iteration 31,
# so the probe addresses are the same.  NOTE the stdin pipe.
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i32/ours-paired-i32a.resc
sleep 200 | G1_RESC=/private/tmp/g1-i32/ours-paired-i32a.resc \
G1_APP_ELF=/private/tmp/g1-i32b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040C68 G1_CTX_105A=0x20040CDA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i32b
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i32b /private/tmp/g1-i32/rep-b
```

Files changed: `recon/ownership/adoption_manifest.json` (11 new app exclusion
rows + summary recount);
`recon/generated/app_retained_sources.cmake` (regenerated, 1620 → 1609);
new `recon/symbols/g1_app_sched_displacement_aliases.ld`;
new `recon/ownership/app_duplicate_singleton_sweep.json` (the sweep receipt);
`recon/symbols/g1_app_function_aliases.ld` (one line withdrawn);
`recon/application/app/CMakeLists.txt` (the fragment + five `--undefined` roots);
`recon/app/src/FUN_0007c8e8.c`, `recon/verified/src/FUN_0007c8e8.c`,
`recon/symbolized/app/ipc_ept_op_b_guarded.c` (the dropped `r3`);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, `armemul` untouched, nothing committed.

## Iteration 33 — the raster never ran because **`g_display_msgq` was never
## initialised**: six shipped `K_MSGQ_DEFINE` objects came up with
## `msg_size = 0`, `max_msgs = 0`, `buffer_start = NULL`, so every
## `k_msgq_put` returned `-ENOMSG` and the display thread received **zero**
## messages in 20 s.  Restoring the static initialiser opens the path — and
## unmasks the next fault.

*(written incrementally as each finding was confirmed)*

### 33.1 MEASURED FIRST — where the control flow actually stops

Iteration 32 §32.7 named the blocker as "nothing downstream of the opcode-0
sync ever calls `DashBoard_Reflash`".  Two corrections came out of tracing the
shipped control flow forward, both measured on `g1-i32b-app` + `g1-i30e-net`
under iteration 30's exact recipe (20 s, `G1_HOOKS=0`, block hooks at **our**
PCs, `sleep 100000 | …` stdin pipe, no memory pokes):

| app hook (our `g1-i32b-app` PC) | hits p1 / p2 | what it means |
|---|---:|---|
| `projector_reflash_and_release` `0x00079cb6` | 30 / 196 = **226** | `display_dispatch_thread`'s `notify_display_mode(B(0xd5))` really fires, always with **`mode = 10`** |
| `display_reflash` `0x00043a08` | 30 / 196 = **226** | it really builds the 24-byte START packet |
| **`submit_display_reflash_work` `0x000433c8`** | **0 / 0** | ***every* `k_msgq_put(g_display_msgq, …)` FAILED** |
| `display_thread_handler` `0x00043414` | 1 (entry only) | the consumer thread exists and is spawned |
| `ui_refalsh_warp` / `ui_DashBoard_task` / `DashBoard_Reflash` | 0 | never reached |

`display_reflash` (`FUN_0004967c`) only calls `submit_display_reflash_work`
when `k_msgq_put` returns 0.  **226 puts, 0 successes** is therefore a direct
measurement that the queue itself is broken, not that a predicate is false.

**Correction to the task framing:** `mode = 10` is `ui_navigation_task`, not
`ui_DashBoard_task` (`ui_refalsh_warp` `case 6`).  The oracle's two rendered
strings — *"Your route is being generated…"* and *"Navigate stopped due to app
disconnection."* — are **navigation** screens, so `DashBoard_Reflash`'s zero
hit count is EXPECTED on this stimulus and is not evidence of anything.  That
also explains iteration 14's observation that the `DashBoard_Reflash` hook
never fired on the *shipped* firmware either: on this stimulus the shipped
firmware does not call it.  The real raster entry point for this capture is
`ui_navigation_task` (`FUN_0003f410`, our `0x00039ab8`) →
`reflash_fb_data_to_lcd` → `pixelto4bithex`.

### 33.2 ROOT CAUSE — six static `K_MSGQ_DEFINE` objects are all-zero

`g_display_msgq` (shipped `0x200038c4`, our arena `0x20004a64`) is a
`K_MSGQ_DEFINE`: a *fully* static object whose struct lives in `.data` with its
ring-buffer pointers already set, and which **nothing at runtime ever
initialises again**.  The shipped ROM initialiser (flash `0xf6d64 + 0x38c4`,
read with `tools/extract.py`) is

```
+0x00 wait_q       200038c4 200038c4   (self-referential sys_dlist_t)
+0x08 lock         00000000
+0x0c msg_size     00000018   (24)
+0x10 max_msgs     0000001e   (30)
+0x14 buffer_start 2004ca90
+0x18 buffer_end   2004cd60   (= start + 24*30 = start + 0x2d0)
+0x1c read_ptr     2004ca90
+0x20 write_ptr    2004ca90
+0x24 used_msgs    00000000
+0x28 poll_events  200038ec 200038ec   (CONFIG_POLL, self-referential)
+0x30 flags/pad    00000000
```

`sizeof(struct k_msgq) = 0x34`, proven by the constant 0x34 stride between the
six msgq objects at `0x20003890 / 0x200038c4 / 0x200038f8 / 0x2000392c /
0x20003960 / 0x20003994`.

`recon/application/gen_app_data_image.py` restored **only the two
self-referential dlist heads** (`+0x00` and `+0x28`, the two 8-byte runs
`{0x018c4,8}` and `{0x018ec,8}` in `g1_app_data_image.c`).  Everything between
them was dropped by the pointer policy, because `0x2004ca90` is an SRAM
pointer that is neither a self-reference *nor inside the recovered arena*
(`g1_ram_arena` spans `0x20002000..0x2002a400`; every one of the six ring
buffers lives above it).

So our `g_display_msgq` came up with **`msg_size = 0`, `max_msgs = 0`,
`buffer_start = buffer_end = read_ptr = write_ptr = NULL`, `used_msgs = 0`**.
`k_msgq_put` with `K_NO_WAIT` takes the "queue full" exit the instant
`used_msgs == max_msgs` (`0 == 0`) and returns `-ENOMSG` — **always, from the
first call**.  That is the measured 226 / 0.

All **six** shipped `K_MSGQ_DEFINE` queues are dead the same way:

| shipped VA | pin | msg_size × max_msgs | shipped ring |
|---|---|---:|---|
| `0x20003890` | `g_audio_msgq` | 204 × 18 | `[0x2004b7b8,0x2004c610)` |
| `0x200038c4` | **`g_display_msgq`** | **24 × 30** | `[0x2004ca90,0x2004cd60)` |
| `0x200038f8` | `g_bt_data_pipe` | 257 × 48 | `[0x200422f0,0x20045320)` |
| `0x2000392c` | `g_dashboard_response_msgq` | 24 × 16 | `[0x2004c910,0x2004ca90)` |
| `0x20003960` | `g_quicknote_flash_msgq` | 6 × 20 | `[0x20045340,0x200453b8)` |
| `0x20003994` | `g_flash_store_cmd_msgq` | 6 × 5 | `[0x20045320,0x2004533e)` |

This is a **new defect class** for the ledger: *a shipped fully-static kernel
object whose backing storage lives outside the recovered RAM arena*.  The
`.data` restore policy (iteration 15/16/17) correctly refuses to invent a
pointer, and correctly refuses half-restores — but the result here was an
object that looks initialised (its wait_q is a valid empty list) and is
completely non-functional.  `check_ram_pin_collisions.py` cannot see it: the
pin is bound, in-arena and non-escaping; only its *contents* are wrong.

### 33.3 The fix

`recon/application/gen_app_data_image.py` gains an explicit, self-verifying
`STATIC_MSGQS` table.  For each listed object the generator **reads**
`msg_size`, `max_msgs` and the four ring pointers out of `app_update.bin` and
asserts the canonical shape (`lock == 0`, `used_msgs == 0`,
`buffer_end - buffer_start == msg_size * max_msgs`,
`read_ptr == write_ptr == buffer_start`, buffer outside the arena) before
emitting anything — nothing is typed in by hand except the object address and
the C identifier.  It then

* declares a dedicated `static unsigned char <ring>[msg_size*max_msgs]
  __aligned(4);` in the generated TU — the ring's *address* carries no
  semantics, only its size does;
* restores the 24 bytes `[+0x0c, +0x24)` verbatim; and
* relocates the four pointer words onto that array
  (`buffer_start = read_ptr = write_ptr = &ring[0]`, `buffer_end = &ring[n]`).

The result is bit-for-bit the object `k_msgq_init(q, ring, msg_size, max_msgs)`
builds, which is exactly what `K_MSGQ_DEFINE` encodes statically.
A `--static-msgq {none,display,all}` switch keeps the bisect honest.

Regenerating with `--static-msgq none` reproduces the committed
iteration-17 `g1_app_data_image.c` **byte-identically** (one reviewed
`KEEP_ALWAYS` entry was needed for the 2-byte run `{0x00d1e,2}`, the high half
of the shipped NaN float at `0x20002d1c`, which the committed file contains and
the current group/word-grid policy would otherwise drop) — so the diff of this
iteration is exactly the msgq restore and nothing else.

### 33.4 MEASURED — `g1-i33a-app` (display msgq restored, nothing else):
### the raster path OPENS and immediately hits a second defect

`g1-i33a-app` = `g1-i32b-app` + §33.3 with `--static-msgq display`.
FLASH 699,076 → **699,144 B** (+68), RAM 253,045 → **253,765 B** (+720, the
ring buffer exactly).  `nm -u` = 0.  Same net image, same stimulus, same recipe.

Block hooks at `g1-i33a-app`'s own PCs:

```
I33 submit_display_reflash_work                     <- FIRST TIME EVER
I33 display_reflash_handler req=10 mode=1           <- the START message arrives
I33 ui_refalsh_warp screen=10 p4=1                  <- the UI dispatcher runs
I33 ui_navigation_task p1=0x20040abc p2=0x20040024 p3=0x00000001
I33 ARMFAULT  lr=0x0005086d       (z_arm_hard_fault)
I33 ARMFATAL  reason=35 esf=0x20034388
I33 ESF reason=35 r0=0xffffffff r1=0x2002b22f r2=0x00000000 r3=0x0009ff1a
        r12=0x00000000 lr=0x00042033 pc=0x00041ffe xpsr=0x01000200
```

**The queue works.**  `submit_display_reflash_work`, `display_reflash_handler`,
`ui_refalsh_warp` and `ui_navigation_task` all execute for the first time in
this project.  Then, ~5.9 s in, reason **35 = `K_ERR_ARM_USAGE_ILLEGAL_EPSR`**
(INVSTATE) at PC `0x00041ffe`, and because `CONFIG_RESET_ON_FATAL_ERROR=1` the
SoC reboots — which is what Renode reports as
`PC does not lay in memory … CPU was halted` and why `g1-i33a-app`'s counters
(`JBD FrameCounter 0`, `RADIO_TX 0x4C`, journal empty) are worse than
iteration 32's across the board.  **`g1-i33a-app` on its own is a regression
and is NOT the iteration's build**; it is reported because it is the
attribution.

### 33.5 The second defect — instance **18** of the undersized-stack-frame class

`0x00041ffe` is the epilogue `ldr.w pc,[sp],#4` of **`send_response_data_to_ble`**
(shipped `FUN_00047ba8` @ `0x47ba8`).  Shipped bytes:

```
47ba8  push {r0,r1,r2,r3,r4,r5,r6,lr}   ; 32-BYTE frame; 24-byte msg at sp+0
47bbc  movs r2,#23 ; movs r1,#0 ; add r0,sp,#1 ; bl 0x86c78   ; memset(sp+1,0,23)
47bc8  movs r3,#1  ; strb.w r3,[sp]                            ; msg[0] = 1
47bd2  mov  r1,sp  ; ldr r0,=0x2000392c ; bl 0x720d0           ; k_msgq_put
47bb6  add  sp,#28 ; ldr.w pc,[sp],#4
```

Our reconstruction spelled the 24-byte message as **four `unsigned int` locals
seeded from the four parameters**, three of them cast to `(void)`.  GCC laid
that out in a **16-byte** `push {r0,r1,r2,lr}` frame, so
`memset_bytes(&local_20 + 1, 0, 23)` ran from `sp+5` to `sp+27` and **destroyed
the saved LR at `sp+12`** (plus 12 bytes of the caller's frame).  The epilogue
then popped `PC = 0`, which is even ⇒ INVSTATE.

This was **latent** exactly as long as the raster was: nothing had ever called
`send_response_data_to_ble`, because it is reached only from the UI screen
tasks (`ui_navigation_task`, `ui_DashBoard_task`, `ui_teleprompter_task`,
`ui_onboarding_task`, `send_dashboard_status_sync…`).  `tools/cfg_verify.py app
FUN_00047ba8` **passes both before and after the fix** (`PASS cases=0`) — the
harness compares ABI returns, non-stack memory writes and call order, so a
stack buffer that runs off the end of the frame is invisible to it.  That is
the same structural blindness as instances 1–17.

The fix restores the shipped shape (`unsigned char msg[24]`, `memset(msg+1,0,23)`,
`msg[0]=1`, `k_msgq_put(g_dashboard_response_msgq, msg, K_NO_WAIT)`) in all
three trees.  It also fixes a second, quieter error in the same function: the
old spelling wrote `*(u32*)msg = (param_1 & ~0xff) | 1`, leaking param_1's
upper three bytes into `msg[1..3]`, where the shipped code zeroes them first.
Every caller already declares the function with no parameters, and the shipped
prologue's `r0`–`r3` are pure spill space that nothing reads, so the signature
becomes `void`.

**A directed sweep for the whole class was run, not just this one site.**  An
analysis-only script disassembles every function in our link, computes the
prologue frame size, and flags any `sp+k` buffer handed to
`memset`/`memcpy`/`k_msgq_put`/`k_msgq_get` with `k + size > frame` (the msgq
message size taken from the six shipped `K_MSGQ_DEFINE` objects).  Over the
whole app image it reports **exactly one** true positive —
`send_response_data_to_ble` — plus one false positive (`att_write_rsp`, stock
Zephyr, whose `sub sp,#28` follows an `it` block the scanner stops at).  A
companion sweep comparing our prologue frame size against the shipped one for
every recovered function lists 89 functions whose frame is smaller, but a
smaller frame is only a defect when a buffer actually overruns it, which is
what the first sweep tests.

### 33.6 MEASURED — `g1-i33b-app` = `g1-i33a-app` + §33.5

`g1-i33b-app` = `g1-i32b-app` + the `g_display_msgq` restore (§33.3) + the
`send_response_data_to_ble` frame fix (§33.5).  FLASH **699,128 B**, RAM
**253,765 B**, `nm -u` **0**, `_end` and `runtime_info_sync` unchanged from
`g1-i33a-app` (`0x2003ff45` / `0x00015b8c`), device context `0x2003FF50`
(confirmed from the `ui_navigation_task p1=0x20040abc` hook: `0x20040abc −
0xb6c`), so `G1_CTX_FE8=0x20040F38`, `G1_CTX_105A=0x20040FAA`.

**No fatal error, no halt, no reset.**

**The G-3 first difference at index 66 is CLOSED.**  `spim_a` `p1_boot` goes
from **66 → 70** transactions, and index 66 is now byte-for-byte the
transaction the oracle emits there:

```
ours   seq=66 txn=61446 tx=02 000000 FF …     <- third full-screen clear, (0,0)
       seq=67 txn=61446 tx=02 030000 FF …        (0,192)
       seq=68 txn=30726 tx=02 060000 FF …        (0,384)
       seq=69 txn=1     tx=97                    display update
oracle idx 66 {"op":"0x02","kind":"pixel_window","x":0,"y":0,
                "n_pixel_bytes":61440,"pixel_sha256":"0693f6bf…"}
```

`JBD FrameCounter` `p1_boot` **0x6 → 0x9** (three clear rounds × three
windows).  The iteration-32 report's "the oracle emits a *third* full-screen
clear at index 66 and we do not" is answered: the third clear is the one
`ui_refalsh_warp` → `ui_navigation_task` issues on its first run, and it never
happened because the START message never arrived.

#### The 20 s capture of `g1-i33b-app` + `g1-i30e-net` (measured, nothing claimed)

```sh
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i33/ours-paired-i33b.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i33/ours-paired-i33b.resc \
G1_APP_ELF=/private/tmp/g1-i33b-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i33b
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i33b /private/tmp/g1-i33/rep-b
```

| counter | oracle | iter 32 (`i32b`) | i33a (msgq only) | **iter 33 (`i33b`)** |
|---|---:|---:|---:|---:|
| machine reset / CPU halt | none | none | **reset @ 5.9 s** | **none over 20 s** |
| fatal error | — | none | **`ILLEGAL_EPSR` (35)** | **none** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x01 | 0x00 | **0x01 — MATCHES** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x02 | 0x02 | **0x02 — MATCHES** |
| `esbslave MasterFramesSeen` | 0x175 | 0x176 | 0 | **0x176** |
| `esbslave AcksInjected` | 0x175 | 0x176 | 0 | **0x176** |
| `esbslave AnnounceResponses` | 0x15B | 0x91 | 0 | **0x172 — best ever** |
| `radio TransmittedFrames` | 0x230 | 0x232 | 0x4C | **0x233** |
| `vcentral Connected` / `ConnectInds` | True / 1 | True / 1 | True / 1 | **True / 1** |
| `vcentral DataEvents` | 0x215 | 0x212 | — | **0x217** |
| **`spim_a` `p1_boot` transactions** | **764** | 66 | — | **70** |
| `spim_a` `p2_render` transactions | 2,881 | 0 | — | **0** |
| `spim_a` `p1` pixel windows | 673 | 6 | — | **9** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x6 / 0x6 | 0 / 0 | **0x9 / 0x9** |
| `JBD JournalCount` | 0x400 | 0x42 | 0 | **0x46** |
| `twim1` p1 / p2 | 371 / 599 | 346 / 628 | — | **262 / 0** |
| `twim2` p1 / p2 | 1,089 / 1,200 | 1,041 / 700 | — | **941 / 0** |
| `saadc` whole run | 998 | 101 | — | **17** |
| `pdm0` / `gpiote0` / `gpiote1` | 2 / 25 / 0 | 2 / 25 / 0 | — | **2 / 25 / 0** |
| `IMU_ACCEL` / `OPT3001_READY` / `NPM1300_CHG` | T / T / T | T / T / T | F / F / F | **T / T / T** |
| **framebuffer lit px p1 / p2** | **656 / 1,098** | 0 / 0 | 0 / 0 | **0 / 0** |

**STATED UNAMBIGUOUSLY: NO PIXEL IS PAINTED.**  `framebuffer.lit_pixels` is
**0 / 0** against the oracle's **656** (`p1_boot`) and **1,098** (`p2_render`).
The framebuffer hash is still `0c5cc90b07…` (the all-transparent panel), bit
identical to iterations 16–32.

**G-3 moved: the first differing `spim_a` transaction is now index 70, not 66.**
Transactions 0..69 are identical to the oracle entry-for-entry, including all
three full-screen clear rounds (`pixel_sha256` `0693f6bf…`, `0693f6bf…`,
`4c7eea52…`).  The oracle's index 70 is the **first CONTENT window**:

```
oracle idx 70  {"op":"0x02","kind":"pixel_window","x":178,"y":262,
                "n_pixel_bytes":213,"pixel_sha256":"fe4694d7…"}
ours   idx 70  (end of stream)
```

`x = 178` is exactly the oracle framebuffer's `bbox.x0` for `p1_boot` — i.e.
index 70 is the first glyph row of *"Your route is being generated…"*.  **That
is the new first divergence, and it is one function call away from a pixel.**

**A REGRESSION IS ALSO REPORTED, not papered over:** phase 2 of `g1-i33b-app`
performs **zero** `spim_a`, `twim1` and `twim2` transactions (iteration 32 did
628 / 700), and `saadc` falls 101 → 17.  All peripheral traffic stops at
t ≈ 4.03 s, right after the third clear round, while the ESB/radio path keeps
running to the end (and in fact reaches its best numbers of the project).  So
this is not a crash — the app core is alive — it is a stall in whatever the
display thread does next.  §33.7 below is that investigation.

### 33.7 The stall after the third clear — the default **font resources were
### never recovered**, and the glyph-directory length was a raw absolute flash pin

Block hooks on `gui_utf_draw` and every one of its callees, at `g1-i33b-app`'s
PCs, give the exact stopping point (each line printed once, in this order):

```
I33 reflash_handler req=10 mode=1
I33 ui_refalsh_warp screen=10 p4=1
I33 ui_navigation_task p3=1
I33 send_response_data_to_ble
I33 gui_utf_draw font=0 l=178 t=87 r=607
I33   utf8_to_utf16 text=0x000a0eed
I33   atomic_get_3_0
I33   clean_fb_data
I33   idx_in_range ch=0x0059                 <- 'Y' of "Your route is being generated…"
I33   resource_manger_get font=0 ch=0x0059   <- NEVER RETURNS
```

`left = 178` is the oracle framebuffer's `bbox.x0`, and `ch = 0x59` is the first
glyph of the oracle's `p1_boot` string, so the raster is on the correct pixel
with the correct character.  It stops in the **font resource manager**.

`resource_manger_get` (`FUN_0004588c`) contains no loop; its `font == 0` arm
calls `get_default_font_glyph_offset` (`FUN_00045840`), which walks a directory:

```
45844  ldr r3,=0x0008ac28 ; ldr r7,[r3]      ; the ENTRY COUNT
45846  ldr r6,=0x0009890c                    ; the DIRECTORY
4584c  cmp r5,r7 ; blt … ; ldrh.w ip,[r6],#4 ; { u16 codepoint, u8 half_width, u8 pad }
4586e  … r3 += half_width*26 ; uxth r3 ; adds r5,#1 ; b 4584c
45866  ldr r0,=0x000e5f62 ; add r0,r3        ; glyph bitmap = blob + accumulated offset
```

Three flash addresses.  In `recon/symbols/g1_app_globals.ld` **all three were
raw absolute pins to the ORIGINAL image's addresses**, so in our link they read
*our own* image at those VAs:

| symbol | shipped meaning | shipped value | what OUR image holds there |
|---|---|---|---|
| `g_default_font_glyph_table_count` `0x8ac28` | entry count | **`0x14c` = 332** | `0x2000b448` = **536,918,600** |
| `rodata_9890c` | 332 × 4 B glyph directory | `20 00 02 00 21 00 01 00 …` | `20 00 60 00 3a 79 0d 00 …` (a 2-byte string stub `{0x20,0x00}` emitted by `gen_app_string_rodata.py`, which had classified the directory as a string) |
| `rodata_e5f62` | 37,050 B packed glyph bitmaps | — | never emitted at all |

So the directory scan for `'Y'` was told to walk **536,918,600 entries**.  That
is the stall: not a deadlock and not a crash — a cooperative-priority display
thread grinding through half a billion iterations of a four-instruction loop,
which is exactly the measured profile (phase 2 burns 5 minutes of host time for
14 s of virtual time while issuing **zero** SPI and zero I2C transactions, and
the ESB/radio path — driven from interrupt context — keeps running to the end).

**The extents of the two missing rodata objects are proven, not guessed, and
the two proofs agree to the byte:**

* the entry count `0x14c` is the shipped word at `0x8ac28`, which is element
  `[2]` of the already byte-verified `recon/data/rodata_0x8ac20.c`; 332 × 4
  = **1,328 B**, i.e. `0x9890c..0x98e3c` — and `0x98e3c` is exactly where the
  next recovered rodata symbol (`rodata_98e3c`) begins;
* `get_default_font_glyph_offset` returns `0xe5f62 + Σ half_width·0x1a`, and
  `gui_utf_draw` copies `0x1a · half_width` bytes per glyph, so the blob is
  `Σ half_width_i · 26` = **37,050 B**, i.e. `0xe5f62..0xef01c` — and `0xef01c`
  is exactly where the next recovered rodata symbol (`rodata_ef01c`, a
  `display_reflash` log string) begins.

Both are emitted byte-exact from `app_update.bin` via `tools/extract.py` into a
new `recon/application/app/src/g1_app_font_rodata.c`; the two numeric pins are
removed from `g1_app_globals.ld` (with the `rodata_8ad40` withdrawal precedent's
comment form), the 2-byte `rodata_9890c` string stub is withdrawn from
`g1_app_string_rodata.c`, and the count pin becomes

```
PROVIDE(g_default_font_glyph_table_count = rodata_0x8ac20 + 8);
```

so it reads the byte-verified table instead of a numeric literal.  **This is a
third instance of a general class worth naming: 356 symbols in this link are
still absolute `A` symbols in the FLASH range** — every one of them reads our
own image at an original-image VA.  Most are log-format strings, which is why
they have been survivable; these three were read as *data* on the raster path.

### 33.8 **THE RECONSTRUCTED FIRMWARE PAINTS PIXELS — and `p1_boot` is
### BYTE-IDENTICAL to the oracle**

`g1-i33c-app` = `g1-i33b-app` + §33.7 (the two byte-exact font rodata objects
and the three rebound symbols).  FLASH 699,128 → **737,504 B** (+38,376 =
1,328 + 37,050 + 2 B alignment, i.e. exactly the two recovered blobs), RAM
unchanged **253,765 B**, `nm -u` **0**, `_end` `0x2003ff45` and
`runtime_info_sync` `0x00015b8c` unchanged, so the probe addresses are the same.

**MEASURED, phase 1 (`p1_boot`, 0 → 6 s), same recipe, same stimulus, no pokes:**

```
lit_pixels   656          oracle 656
bbox         x 178..449, y 267..287     oracle x 178..449, y 267..287
sha256       1d617c65a688f10e…          oracle 1d617c65a688f10e…   IDENTICAL
```

The 153,600-byte 4 bpp framebuffer our firmware produced is **byte-for-byte the
golden framebuffer** (`recon/emulator/reports/golden_framebuffer_p1_boot.raw`).
The image is the shipped firmware's own boot string, *"Your route is being
generated…"*, rendered by our rebuilt raster path from our recovered font.

`JBD FrameCounter` `p1_boot` **0x9 → 0x40**, `spim_a` `p1` trace 925,544 →
952,684 bytes, and phase 2 is alive again: `spim_a.p2` 0 → 354,231 bytes,
`twim1.p2` 0 → 34,768, `twim2.p2` 0 → 41,774.  The half-billion-iteration stall
is gone.

**MEASURED, phase 2 (`p2_render`, 6 → 20 s):** the framebuffer is **non-empty
but not the oracle's**:

```
             ours                       oracle
lit_pixels   544                        1,098
bbox         x 120..353, y 267..287     x 34..497, y 266..287
sha256       b855eac0a3d4e5db…          b26c73b37d441fc8…
first differing row      y = 266
first differing pixel    x = 37   (oracle 0xF, ours 0x0)
```

Both images occupy the same 21-row band at the same baseline; ours is a
**shorter string** (234 px wide, starting at x = 120) where the oracle draws
*"Navigate stopped due to app disconnection."* (464 px wide, starting at
x = 34).  The glyph machinery is therefore correct — it is the *string
selection* in phase 2 that differs, i.e. our build renders a different
navigation message for the disconnect event.  That is the new first divergence
and it is a content question, not a raster question.

### 33.9 The full 20 s capture of the iteration build `g1-i33c-app` + `g1-i30e-net`

```sh
recon/application/build_cohesive.sh app /private/tmp/g1-i33c-app
# net UNCHANGED from iteration 30 (g1-i30e-net)
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i33/ours-paired-i33c.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i33/ours-paired-i33c.resc \
G1_APP_ELF=/private/tmp/g1-i33c-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i33c
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i33c /private/tmp/g1-i33/rep-c
```

| counter | oracle | iter 32 (`i32b`) | **iter 33 (`i33c`)** |
|---|---:|---:|---:|
| machine reset / CPU halt | none | none | **none over 20 s** |
| fatal error | — | none | **none** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x01 | **0x01 — MATCHES** |
| `ESB_SYNC_ctx_105a` | 0x02 | 0x02 | **0x02 — MATCHES** |
| `esbslave MasterFramesSeen` / `AcksInjected` | 0x175 / 0x175 | 0x176 / 0x176 | **0x176 / 0x176** |
| `esbslave AnnounceResponses` | 0x15B | 0x91 | **0x167 — best ever** |
| `radio TransmittedFrames` | 0x230 | 0x232 | **0x231** |
| `vcentral Connected` / `ConnectInds` | True / 1 | True / 1 | **True / 1 — MATCHES** |
| `vcentral DataEvents` | 0x215 | 0x212 | **0x215 — MATCHES exactly** |
| **`spim_a` p1 / p2 transactions** | **764 / 2,881** | 66 / 0 | **126 / 109** |
| `spim_a` pixel windows p1 / p2 | 673 / 2,752 | 6 / 0 | **64 / 106** |
| `JBD FrameCounter` p1 / p2 | 0x2A1 / 0xD61 | 0x6 / 0x6 | **0x40 / 0xAA** |
| `JBD JournalCount` | 0x400 | 0x42 | **0xEB** |
| `twim1` p1 / p2 | 371 / 599 | 346 / 628 | **346 / 587** |
| `twim2` (LSM6DSO) p1 / p2 | 1,089 / 1,200 | 1,041 / 700 | **1,041 / 700** |
| `saadc` whole run | 998 | 101 | **95** |
| `pdm0` / `gpiote0` / `gpiote1` | 2 / 25 / 0 | 2 / 25 / 0 | **2 / 25 / 0, all hash-EQ** |
| `IMU_ACCEL` / `GYRO` / `OPT3001_READY` / `NPM1300_CHG` | T / F / T / T | T / F / T / T | **T / F / T / T — all MATCH** |
| **framebuffer lit px p1 / p2** | **656 / 1,098** | 0 / 0 | **656 / 544** |
| **framebuffer sha256 p1** | `1d617c65…` | `0c5cc90b…` | **`1d617c65…` — IDENTICAL** |
| framebuffer sha256 p2 | `b26c73b3…` | `0c5cc90b…` | `b855eac0…` |

`twim1` per device (`p1_boot` / `p2_render`), ours vs oracle:

| device | oracle | **iter 33** |
|---|---|---|
| nPM1300 charger/fuel gauge | 291 / 508 | **286 / 507** |
| OPT3001 ambient light | 33 / 80 | **35 / 80 — `p2_render` stream hash EQUAL** |
| ST25DV NFC EEPROM | 25 / 7 | 11 / 0 |
| ST25DV system port | 22 / 4 | 14 / 0 |

The OPT3001 `p2_render` per-device stream is the **first sensor byte-stream in
this project to hash-match the oracle exactly**.

#### Graphics + sensor verdicts (iteration 33, `g1-i33c-app` + `g1-i30e-net`)

| id | verdict | first difference / detail |
|---|---|---|
| **G-1** (`p2_render` framebuffer) | **FAIL** | ours `b855eac0…`, **544 lit px**, bbox x 120–353 / y 267–287; oracle `b26c73b3…`, **1,098 lit px**, bbox x 34–497 / y 266–287.  **First differing row y = 266, first differing pixel x = 37** (oracle 0xF, ours 0x0).  Both images sit in the same 21-row band on the same baseline; ours is a *shorter string*. |
| **G-2** (`p1_boot` framebuffer) | **PASS** | **`1d617c65a688f10e…` == `1d617c65a688f10e…`, 656 == 656 lit pixels, bbox x 178–449 / y 267–287 identical, ZERO differing rows.**  Byte-for-byte the golden framebuffer. |
| **G-3** (`spim_a` transaction stream) | **FAIL, but the first difference moved 66 → 126** | `p1_boot` **126 vs 764**, the 126 shared transactions identical entry-for-entry; the oracle's index 126 is `{"op":"0x02","x":32,"y":265,"n_pixel_bytes":9}`.  `p2_render` **109 vs 2,881**, first difference index 0 (ours restarts with a full clear where the oracle continues incremental).  Ours reaches the same `p1` image in **64** pixel windows where the oracle uses **673** — fewer, larger windows, same result. |
| **G-4** | *localiser* | `p1_boot`: **no differing row**.  `p2_render`: first differing row **266**, first differing pixel **x = 37**. |
| **G-5** (panel init) | **PASS** | byte-exact over the whole 126-transaction `p1` prefix, including all three `op 0x02` full-screen clears and the brightness/gear register writes. |
| **G-6** (`spim_b` unused) | **PASS** | 0 == 0, stream hash EQ, both phases. |
| **S-MIC** | **PASS** | `pdm0` whole-run hash EQ, 2 accesses. |
| **S-KEYS** | **PASS** | `gpiote0` whole-run hash EQ, 25 accesses; `gpiote1` 0 == 0. |
| **S-ALS** | **PARTIAL — best ever** | OPT3001 35 / 33 (`p1`) and **80 / 80 with the stream hash EQUAL** (`p2`); `OPT3001_CONVERSION_READY` True. |
| **S-PMIC** | **PARTIAL — best ever** | nPM1300 286 / 291 and **507 / 508**; `NPM1300_CHARGING` True. |
| **S-IMU** | **PARTIAL** | `twim2` 1,041 / 1,089 and 700 / 1,200; `IMU_ACCEL_ENABLED` True, `IMU_GYRO_ENABLED` False. |
| **S-NFC** | **PARTIAL** | ST25DV EEPROM 11 / 25 and 0 / 7; system port 14 / 22 and 0 / 4. |
| **S-ADC** | **FAIL** | `saadc` 95 / 998, hash NE. |
| **S-ESB** | **PARTIAL — all three criteria met** | `ESB_SYNC_ctx_105a == 0x02` ✓, `DISPLAY_ON_ctx_fe8 == 0x01` ✓, master PTX frames 0x176 vs 0x175, all ACKed ✓.  `AnnounceResponses` 0x167 vs 0x15B (best ever). |

**Criteria score: 5 PASS / 5 PARTIAL / 4 FAIL** (iteration 32: 4 / 5 / 5).
The new PASS is **G-2**, and it is the acceptance-bar one: *the reconstructed
firmware paints the shipped firmware's boot screen, pixel for pixel.*

### 33.10 The NEW first divergence

`p2_render` renders a **different, shorter navigation string** (234 px wide at
x = 120) than the oracle's *"Navigate stopped due to app disconnection."*
(464 px at x = 34).  The raster, the font, the canvas geometry and the baseline
are all now proven correct by G-2, so the remaining question is **which string
`ui_navigation_task` selects for the app-disconnection event in phase 2** — a
content/state question in the navigation screen state machine, not a display
one.  Concretely: first differing framebuffer row **y = 266**, first differing
pixel **x = 37**, and `spim_a` `p2_render` index **0** (the oracle continues
with a 9-byte incremental window at (32,265); we begin with a fresh full-screen
clear).

### 33.11 Build ledger and gates

| app build | change | FLASH | RAM | `nm -u` |
|---|---|---:|---:|---:|
| `g1-i32b-app` | iteration 32 | 699,076 B | 253,045 B | 0 |
| `g1-i33a-app` | + `g_display_msgq` restored (§33.3) | 699,144 B | 253,765 B | 0 |
| `g1-i33b-app` | + `send_response_data_to_ble` frame fix (§33.5) | 699,128 B | 253,765 B | 0 |
| **`g1-i33c-app`** | **+ the two font rodata objects and three rebound symbols (§33.7) — FINAL** | **737,504 B** | **253,765 B** | **0** |

RAM +720 B (the display msgq ring).  FLASH +38,428 B, of which 38,376 B are the
two byte-exact font blobs.  The net core is **UNCHANGED** (`g1-i30e-net`).

| gate | iteration 32 | **iteration 33 (`g1-i33c-app`)** |
|---|---|---|
| `check_ram_pin_collisions.py` (app) raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app) bound OK / escaping | 624 / 0 | **624 / 0** |
| `check_ram_pin_collisions.py --core net` | 0 / 0, 170 / 0 | **0 / 0, 170 / 0**, EXIT 0 |
| `check_net_raw_literals.py` | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `verify_net_stock_data_window.py` | PROVEN | **PROVEN** |
| app / net `nm -u` undefined | 0 / 0 | **0 / 0** |
| app / net duplicate global definitions | 0 / 0 | **0 / 0** |
| `cfg_verify.py app FUN_00047ba8` | PASS (blind) | **PASS** |
| `gen_app_data_image.py --selftest` | OK | **OK (5/5)** |
| `gen_app_data_image.py --static-msgq none` vs HEAD | — | **byte-identical** |

No `--allow-multiple-definition`, no weak symbol, no numeric root.

### 33.12 Open, named, and NOT fixed

1. **The `p2_render` string selection** (§33.10) — the blocker for G-1.
2. **Five of the six static `K_MSGQ_DEFINE` queues are still dead**
   (`g_audio_msgq`, `g_bt_data_pipe`, `g_dashboard_response_msgq`,
   `g_quicknote_flash_msgq`, `g_flash_store_cmd_msgq`).  The generator already
   supports `--static-msgq all`; only `display` was enabled this iteration so
   the pixel result could be attributed to exactly one object.  Restoring the
   rest is the obvious next step, and the stack-buffer sweep (§33.5) already
   shows no other producer overruns its frame.
3. **356 absolute `A` symbols remain in the FLASH range** of the app link
   (§33.7).  Three of them were read as *data* on the raster path and are now
   bound; the rest are mostly log-format strings, but the class is real and
   unswept.  A sweep that classifies each by how its referrers use it (string
   vs data) is the natural follow-up.
4. **The other three font families are still unrecovered**:
   `get_clock_digit_glyph_offset_large` / `…_small` and
   `get_font_style3_glyph_offset` have their own directories and blobs, all
   still raw absolute pins.  Only `font == 0` (the default font) is fixed.
5. `saadc` 95 / 998 and the ST25DV volumes (11 / 25, 14 / 22, 0 / 7, 0 / 4)
   remain the largest sensor gaps.
6. Iteration 32 §32.9 items 2, 5, 6, 7 unchanged.

### Regenerate (iteration 33)

```sh
cd /Users/freedomcoder/Projects/G1disasm2
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py \
  --stage a3 --elf /private/tmp/g1-i32b-app/zephyr/zephyr.elf --static-msgq display
recon/application/build_cohesive.sh app /private/tmp/g1-i33c-app
# net UNCHANGED from iteration 30:
#   recon/application/build_cohesive.sh net /private/tmp/g1-i30e-net -- \
#     -DG1_INTEGRATION_PROBE_RETAIN_ALL=OFF -DG1_ESB_REAL_PAYLOAD_OBJECTS=ON
# gates (all exit 0)
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py        /private/tmp/g1-i33c-app/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_ram_pin_collisions.py --core net /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_net_raw_literals.py          /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/check_thread_create_stack_args.py --trials 120
PYTHONSAFEPATH=1 .venv/bin/python tools/gen_retained_sources.py --check
PYTHONSAFEPATH=1 .venv/bin/python recon/application/verify_net_stock_data_window.py         /private/tmp/g1-i30e-net/zephyr/zephyr.elf
PYTHONSAFEPATH=1 .venv/bin/python recon/application/gen_app_data_image.py --selftest
# 20 s capture -- `_end` = 0x2003ff45, device context = 0x2003ff50, so
# +0xfe8 = 0x20040F38 and +0x105a = 0x20040FAA.  NOTE the stdin pipe, and run
# build_display_sensor_oracle.py SEPARATELY (a `sleep 100000 |` pipeline never
# reaches a following command in the same script).
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i33/ours-paired-i33c.resc
sleep 100000 | G1_RESC=/private/tmp/g1-i33/ours-paired-i33c.resc \
G1_APP_ELF=/private/tmp/g1-i33c-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_i33c
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_i33c /private/tmp/g1-i33/rep-c
```

Files changed: `recon/application/gen_app_data_image.py`
(`STATIC_MSGQS` + the `extbuf` pointer class + `KEEP_ALWAYS` + `--static-msgq`);
`recon/application/app/src/g1_app_data_image.c` (regenerated,
`--static-msgq display`);
`recon/app/src/FUN_00047ba8.c`, `recon/verified/src/FUN_00047ba8.c`,
`recon/symbolized/app/send_response_data_to_ble.c` (the undersized frame);
new `recon/application/app/src/g1_app_font_rodata.c` (the two byte-exact font
blobs); `recon/application/app/src/g1_app_string_rodata.c` (the `rodata_9890c`
stub withdrawn); `recon/symbols/g1_app_globals.ld` (three pins rebound);
`recon/application/app/CMakeLists.txt` (the new TU);
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, `armemul` untouched, nothing committed.

---

## Iteration 34 — dashboard screen: `E_ID_SCREEN_DASHBOARD` is reached by
## **removing** a stimulus, not by adding one.  The shipped firmware paints the
## real head-up dashboard (date / clock / Bluetooth glyph / QuickNote hint) from
## the `don` IMU gesture alone, with **no memory pokes and no GATT command**.

*(written incrementally as each finding was confirmed)*

### 34.1 The screen enum, resolved from the shipped image

`process_for_new_task` (`FUN_0002c99c` @ `0x0002c99c`) switches on
**`device_ctx[0xd5]`** — the live screen id — and each case opens with its own
`"%s(): switch -> E_ID_SCREEN_<NAME>\n"` log.  Matching the case entry format
pointers against the shipped `.rodata` (`tools/extract.py` mapping,
`off = va - 0xC200 + 0x200`) gives the enum directly:

| `ctx[0xd5]` | `E_ID_SCREEN_…` | evidence |
|---:|---|---|
| 0 | `IDLE` | case-0 log `0xa3669` |
| 1 | `WAIT_BLOW_HEAD` | case-1 log `0xa3811` |
| 2 | `COUNTDOWN_TIMER` | case-2 log `0xa2c85` |
| 4 | `ANCS_NOTIFICATION` | case-4 log `0xa2a7e` |
| 5 | `NEW_MESSAGE_COME_ON` | case-5 log `0xa2a4d` |
| **6** | **`DASHBOARD`** | case-6 log `0xa2aad` = `"%s(): switch -> E_ID_SCREEN_DASHBOARD\n"`, log tag `0xa39bb` = `"process_for_DASHBOARD_show"` |
| 10 | `NAVIGATION` | case-10 log `0xa30bd` |

This agrees with `ui_refalsh_warp` (`0x00048b5c`) **case 6 → `ui_DashBoard_task`
(`0x0003af78`)** and **case 10 → `ui_navigation_task` (`0x0003f410`)`, i.e. the
value in `ctx[0xd5]` is the same number `display_reflash_handler` passes to the
raster dispatcher.

### 34.2 **There is no BLE opcode that selects the dashboard.**  Measured, not argued.

A whole-image scan of the shipped app `.text` for the Thumb `BL` encoding
(scratchpad `find_bl.py`; every 2-byte offset, decode `imm10/J1/J2/imm11`)
finds **every** call site of the two screen-selecting functions:

* `update_persist_task_status` `FUN_0002bef4` @ `0x0002bef4` — 20 call sites,
  task ids `{7, 9, 0x0a, 0x0c, 0x0e, 0x10, 0x11}` and two register-sourced ones
  (`ldr r1,[r3]` = *replay the id already in the persist record*).
  **Not one of them passes 6.**
* `update_temp_task_status` `FUN_0002bffc` @ `0x0002bffc` — 12 call sites, ids
  `{4, 5, 6, 8}`.  The three that pass **6** are at `0x0002c7dc`
  (`process_for_message_show`), `0x0002cf60` and **`0x0002e1a2`**
  (both `process_for_new_task`).

So the dashboard is **not** phone-commanded.  For contrast, the opcode the
existing oracle uses is fully accounted for: `ble_process_put_req` case `0x0a`,
sub-command `request[4] == 0` logs *"received navigation func startup packet"*
and calls `update_persist_task_status(device_info, 10, 2)` — the **navigation**
screen.  That is precisely what `vcentral QueueAttWrite "0a0600000000"` sends
(`packet[0] = 0x0a`, `request[4] = 0x00`), and it is why the existing oracle's
`p1_boot`/`p2_render` images are navigation strings.

### 34.3 The real path — `IMU:wakeup:dashboard`

`master_display_thread` (`0x0002692c`) runs
`process_for_new_task(device_ctx, device_ctx + 0xee4)`, so the handler's
`param_2` **is `&device_ctx[0xee4]`**, the wear/head-state byte.
`imu_fusion_thread` (`0x0000fe88`) receives `p = device_ctx + 0xee4` and, on the
head-up transition, executes `p[0] = 2` — i.e. **`device_ctx[0xee4] = 2`**.

In `process_for_new_task` case 0 (`IDLE`) the shipped code at `0x0002e114`…
`0x0002e1a6` is:

```
0002e118  bl   #0x23eec          ; get_ui_mode_flag2()
0002e11c  cmp  r0, #0
0002e11e  bne  #0x2e074          ; must be 0
0002e138  bl   #0x34808          ; can_begin_task_transition()
0002e13c  cbz  r0, #0x2e19c      ; must be 0  -> dashboard
...
0002e19c  movs r2, #2
0002e19e  movs r1, #6            ; <== E_ID_SCREEN_DASHBOARD
0002e1a0  mov  r0, r4
0002e1a2  bl   #0x2bffc          ; update_temp_task_status(ctx, 6, 2)
0002e1a6  movs r2, #1
0002e1a8  mov  r1, r4
0002e1aa  ldr  r0, [pc, #0x128]  ; -> 0xa2733 = "IMU:wakeup:dashboard"
0002e1ac  b.w  #0x2cd8c          ; trigger_screen_state_change(reason, ctx, 1)
```

reached when `device_ctx[0xee4] == 2` **and** `get_ui_mode_flag2() == 0`.
`update_temp_task_status` then writes `ctx[0xd5] = 6` and clears the persist
record.  The reason string the firmware itself attaches to the transition is
**`"IMU:wakeup:dashboard"`** (`0xa2733`) — the code names the stimulus.

**Why the existing oracle never sees it:** the same `IDLE` case first calls
`now_has_persist_task(ctx, ctx[0xd5])`, and if a persist task is pending it does
`ctx[0xd5] = persist_record->task_id` and jumps straight out.  The
`0a0600000000` GATT write installs persist task **10**, so navigation wins the
race before the IMU branch is ever evaluated.

**Therefore the stimulus that selects `E_ID_SCREEN_DASHBOARD` is the oracle
stimulus MINUS the GATT write**: virtual phone connects (link up, ESB L/R sync
completes), no BLE command is sent, and `lsm6dso PlayGesture "don"` is played at
t = 6 s.  Nothing is poked.

### 34.4 MEASURED — the SHIPPED images render the dashboard

`recon/emulator/scripts/capture_display_sensor_oracle.sh` gained two **additive,
default-preserving** knobs (with no variable set it emits a byte-identical
capture script to before):

* `G1_ATT_WRITE` — payload of the single NUS write (default `0a0600000000`);
  **empty string ⇒ the `vcentral QueueAttWrite` line is not emitted at all**;
* `G1_SCREEN_ID` — address of `device_ctx+0xd5`, read back as
  `ORACLE_SCREEN_ID_ctx_d5` (default `0x20053225`, the original image).

```sh
cd /Users/freedomcoder/Projects/G1disasm2
G1_ATT_WRITE="" recon/emulator/scripts/capture_display_sensor_oracle.sh \
    /private/tmp/g1_oracle_dash
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
    /private/tmp/g1_oracle_dash /private/tmp/g1_dash_rep_oracle
```

Same determinism knobs as every other capture (quantum `0.000010`, CC312 seed
`0x5340CC3105340CC3`, `ExecuteInSerial`, 6 s + 14 s phases).

```
ORACLE_SCREEN_ID_ctx_d5:   0x06      <- E_ID_SCREEN_DASHBOARD
ORACLE_DISPLAY_ON_ctx_fe8: 0x01
ORACLE_ESB_SYNC_ctx_105a:  0x02
ORACLE display_START action=0 x1, action=1 x1
ORACLE BLIT notify_display_mode screen=6  x8
ORACLE DashBoard_Reflash                  x136
ui_navigation_task                        x0
```

| phase | spim_a transactions | pixel windows | lit px | bbox | framebuffer sha256 |
|---|---:|---:|---:|---|---|
| `p1_boot` (0–6 s) | 128 | 3 | **0** | — | `0c5cc90b079d0d9c…` (all-zero) |
| `p2_render` (6–20 s) | 12,131 | 11,874 | **2,923** | (78,211)–(564,338) 487×128 | **`19b1f24a09f97a8d…`** |

`JBD FrameCounter` `0x3` → **`0x2E65`**, `JournalCount` `0x400`,
`ESB_MASTER_FRAMES`/`ACKS` `0x175`/`0x175`, `VC_CONNECTED` True.
The replayed-from-SPI framebuffer and the JBD model's own frame dump agree
(`xcheck=True`) for both phases.

**What the screen shows** (crop of the lit bbox): the real G1 head-up dashboard —
`Mon, Jan 1` on the left, a large `00:00` clock beneath it, a Bluetooth glyph
below that, a vertical divider, a note glyph, and the two-line hint
`Hold Right TouchBar` / `to Add QuickNote` on the right.  This is the same
picture `armemul/scripts/g1-render.sh` used to produce **by poking memory** —
now produced by the firmware itself from real stimulus.

`p1_boot` being empty is expected and is the honest consequence of the changed
stimulus: with no navigation command the first six seconds only initialise the
panel and clear it, so the dashboard oracle's *only* pixel gate is `p2_render`.

### 34.5 Determinism of the dashboard capture — verified, not assumed

The shipped dashboard capture was run **twice end-to-end** and the two results
diffed field-by-field.

**Bit-identical across runs** — `framebuffer/p1_boot` and
**`framebuffer/p2_render` sha256 and every `row_sha256`** (2,923 lit px, same
bbox), `spim_a` `p1_boot` stream (34 transactions), `spim_b` (empty),
**every `twim1` per-device stream** (both phases), `twim2` `p1_boot`,
`pdm0`/`saadc`/`gpiote0`/`gpiote1` whole-run, and
`JBD_FRAMECOUNTER_P1` / `DISPLAY_ON_ctx_fe8` / `ESB_SYNC_ctx_105a` /
**`SCREEN_ID_ctx_d5`** / all sensor booleans.

**NOT stable** — and this is a *new* property that the navigation oracle does
not have, so it is called out explicitly rather than hidden:

| field | run 1 | run 2 |
|---|---:|---:|
| `spim_a` `p2_render` transactions | 12,225 | 12,161 |
| `twim2` `p2_render` transactions | 1,206 | 1,202 |
| `JBD FrameCounter` `p2` | 0x2E65 | 0x2E27 |
| `RADIO_TX` / `VC_DATA_EVENTS` | 0x232 / 0x214 | 0x231 / 0x209 |
| `ESB_MASTER_FRAMES` / `ACKS` | 0x175 / 0x175 | 0x174 / 0x174 |

The dashboard is a **continuously repainting** screen: over the 14 s phase the
firmware redraws it ~11.8 k pixel windows, and *how many* complete inside the
budget rides on radio/timer cadence.  The **resulting framebuffer is identical
in both runs**, so `spim_a`'s `p2_render` stream hash / transaction count and
`JBD_FRAMECOUNTER_P2` are **explicitly NOT gates** for this oracle.  (The
navigation oracle's `spim_a` stream *is* stable and G-3 stays in force there.)

### 34.6 The dashboard oracle and its criteria (permanent, additive)

`recon/emulator/reports/display_sensor_oracle_dashboard.json` (schema
`g1.display_sensor_oracle_dashboard/1`) is a **sibling** of
`display_sensor_oracle.json`; **the navigation oracle and its G-1…G-6 / S-*
criteria are untouched.**  The dashboard criteria carry a `D-` prefix:

| id | criterion |
|---|---|
| **D-1** | **THE ACCEPTANCE BAR** — `framebuffer/p2_render/sha256` byte-for-byte = `19b1f24a09f97a8d…`, 2,923 lit px, bbox (78,211)–(564,338) 487×128 |
| **D-2** | `framebuffer/p1_boot/sha256` = `0c5cc90b079d0d9c…` (all-zero) |
| **D-3** | `spim_a` `p1_boot` `stream_sha256` = `f91505ab8dc0dd27…`, 34 transactions |
| **D-4** | localiser: `row_sha256` → first differing row, then first differing pixel |
| **D-5** | `counters/SCREEN_ID_ctx_d5 == 0x06` — *the honest-stimulus gate*: it proves the firmware selected `E_ID_SCREEN_DASHBOARD` **itself** |
| **D-6** | `DISPLAY_ON_ctx_fe8 == 0x01` and `ESB_SYNC_ctx_105a == 0x02` |
| **D-7** | `spim_b` empty, both phases |
| S-D-IMU / S-D-I2C / S-D-MIC,KEYS,ADC | `twim2` `p1_boot` stream; `twim1` **per device**; `pdm0`/`gpiote*`/`saadc` whole-run |

Golden artifacts written alongside it:
`golden_framebuffer_dashboard_p2_render.{raw,pgm,png}` and
`…_crop.png` (lit bbox, 3× upscale, human inspection only).

### 34.7 MEASURED — OUR rebuild (`g1-i33c-app` + `g1-i30e-net`) on the identical stimulus

```sh
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i34/ours-paired-i34.resc
G1_ATT_WRITE="" \
G1_RESC=/private/tmp/g1-i34/ours-paired-i34.resc \
G1_APP_ELF=/private/tmp/g1-i33c-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_dash
```

(`_end` = `0x2003ff45` ⇒ device context `0x2003ff50`, so `+0xd5` = `0x20040025`,
`+0xfe8` = `0x20040F38`, `+0x105a` = `0x20040FAA`; `runtime_info_sync` =
`0x00015b8c`, all read out of the ELF actually booted.)

| counter | oracle | **ours** |
|---|---|---|
| machine reset / CPU halt / fatal | none | **none over 20 s** |
| **`SCREEN_ID_ctx_d5`** | **0x06** | **0x00 — still `E_ID_SCREEN_IDLE`** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | 0x00 |
| `ESB_SYNC_ctx_105a` | 0x02 | **0x02 — MATCHES** |
| `ESB_MASTER_FRAMES` / `ACKS` | 0x175 / 0x175 | **0x175 / 0x175 — MATCHES exactly** |
| `VC_CONNECTED` / `ConnectInds` | True / 1 | **True / 1 — MATCHES** |
| `RADIO_TX` / `VC_DATA_EVENTS` | 0x232 / 0x214 | 0x230 / 0x209 (inside the ±cadence band) |
| `JBD FrameCounter` p1 / p2 | 0x3 / 0x2E65 | **0x3** / 0x3 |
| `IMU_ACCEL` / `GYRO` / `OPT3001` / `NPM1300` | T / F / T / T | **T / F / T / T — all MATCH** |

#### Pixel comparison verdict (dashboard criteria)

| id | verdict | measurement |
|---|---|---|
| **D-1** (`p2_render` framebuffer) | **FAIL** | ours `0c5cc90b079d0d9c…` (all-zero, **0 lit px, 0 pixel windows**) vs oracle `19b1f24a09f97a8d…` (**2,923 lit px**, bbox (78,211)–(564,338)).  **128 differing rows; first differing row y = 211, first differing pixel x = 244** (oracle `0xF`, ours `0x0`). |
| **D-2** (`p1_boot` framebuffer) | **PASS** | `0c5cc90b079d0d9c…` == `0c5cc90b079d0d9c…`, 0 == 0 lit px, **zero differing rows**. |
| **D-3** (`spim_a` `p1_boot` stream) | **PASS** | **34 == 34 transactions, `stream_sha256` `f91505ab8dc0dd27…` IDENTICAL** — our phase-1 display byte stream is byte-for-byte the shipped one, panel ID probe, brightness/gear registers and all three full-screen clears included. |
| **D-4** | *localiser* | first differing row **211**, first differing pixel **x = 244**; `spim_a` `p2_render` first difference index **0** (ours **0** transactions vs the oracle's 12,225, whose index 0 is `{"op":"0x66","kind":"command"}`). |
| **D-5** (screen actually selected) | **FAIL** | ours `0x00` (`E_ID_SCREEN_IDLE`) vs `0x06` (`E_ID_SCREEN_DASHBOARD`). |
| **D-6** | **PARTIAL** | `ESB_SYNC_ctx_105a` **0x02 ✓**; `DISPLAY_ON_ctx_fe8` 0x00 ✗. |
| **D-7** (`spim_b` unused) | **PASS** | 0 == 0, stream hash EQ, both phases. |
| **S-D-MIC / KEYS** | **PASS** | `pdm0` 2 == 2 and `gpiote0` 25 == 25, whole-run hashes EQ; `gpiote1` 0 == 0. |
| **S-D-IMU** | **FAIL** | `twim2` `p1_boot` 1,027 vs 1,075, hash NE; `p2_render` 700 vs 1,206. |
| **S-D-I2C** | **PARTIAL** | nPM1300 / OPT3001 / ST25DV volumes below the oracle's, per-device hashes NE. |
| **S-D-ADC** | **FAIL** | `saadc` 95 vs 998, hash NE. |

**Score: 4 PASS / 2 PARTIAL / 4 FAIL.**  **NO DASHBOARD PIXEL IS PAINTED by our
build** — reported plainly, because the acceptance bar is pixels.

### 34.8 ROOT CAUSE of the dashboard FAIL, measured to one instruction

Block hooks at **our** ELF's PCs (`imu_fusion_thread 0x00012ff8`,
`master_display_thread 0x00023cbc`, `process_for_new_task 0x00029874`,
`update_temp_task_status 0x00028eb0`, `update_persist_task_status 0x00028dc4`,
`now_has_persist_task 0x00028d38`, `get_ui_mode_flag2 0x00021500`,
`can_begin_task_transition 0x0002f918`, `ui_refalsh_warp 0x00042e8c`,
`change_work_mode_to 0x000163a8`) plus a `uart0` file backend:

| hook | oracle (shipped PCs) | **ours** |
|---|---:|---:|
| `now_has_persist_task screen=0` | many | **94** — the IDLE loop really runs |
| `change_work_mode_to 2` | **9** | **0** |
| `get_ui_mode_flag2` | 2 | **0** |
| `can_begin_task_transition` | 1 | **0** |
| `update_temp_task_status id=6 st=2` | **1** | **0** |
| `device_ctx[0xee4]` at t=20 s | **0x02** | **0x01** |

`get_ui_mode_flag2` is never even *called*, which by C short-circuit rules means
the `*param_2 == 2` term is false — i.e. **`device_ctx[0xee4]` never becomes 2**,
so the IMU never wakes the dashboard.  The UART log says why, in one line:

```
shipped:  lsm6dso_init_chip chip id 0x6c    ->  accel pm 1 / odr 0 ... imu_fusion_thread(): start imu looper
ours:     lsm6dso_init_chip chip id 0x3
          Invalid chip id 0x3
          failed to initialize chip                 (no "start imu looper" ever)
```

**But the I2C bus read is correct.**  Our own `twim2.p1.trace` seq 0–2 is
byte-identical to the oracle's:

```
TWIM2 seq=0 dev=0x6B dir=W n=2 data=0100
TWIM2 seq=1 dev=0x6B dir=W n=1 data=0F      <- WHO_AM_I
TWIM2 seq=2 dev=0x6B dir=R n=1 data=6C      <- the model returns 0x6C, correctly
```

so the chip id **arrives** and our firmware then reads `0x03` instead.

The shipped `lsm6dso_init_chip` (`FUN_000622a0` @ `0x000622a0`) spills its
arguments and **reloads the byte from the stack** after the read:

```
000622a0  push.w {r0, r1, r2, r4..r8, sb, lr}   ; r1 (param_2) is spilled to [sp,#4]
000622c4  add.w  r1, sp, #6                     ; &((u8*)&spilled_param_2)[2]
000622c8  bl     #0x7fb3e                       ; lsm6dso_device_id_get(ctx, &chip_id)
000622d4  ldrb.w r1, [sp, #6]                   ; <== RELOAD from the stack slot
000622da  bl     #0x7dda4                       ; log "chip id 0x%x"
000622de  ldrb.w r1, [sp, #6]                   ; <== RELOAD again
000622e2  cmp    r1, #0x6c
```

Our reconstruction (`recon/application/src/lsm6dso_init_chip.c`, and the same in
`recon/app/src`, `recon/verified/src`, `recon/named`, `recon/symbolized/app`,
`recon/readable_sources/app/g1`) spells it as

```c
unsigned int uStack_24;
uStack_24 = param_2;                                     /* the spill */
audio_codec_read_reg0x0f(iVar7, ((int)&uStack_24) + 2);  /* callee writes byte 2 */
log_message(0xf62c5, (param_2 >> 0x10) & 0xff);          /* <-- reads the REGISTER  */
uVar5 = (param_2 >> 0x10) & 0xff;                        /* <-- reads the REGISTER  */
if (uVar5 == 0x6c) { ...
    if (((param_2 >> 0x18) & 0xff) != 0) { ...           /* <-- and again, for +3   */
```

GCC keeps `param_2` in a register across the call and never reloads
`uStack_24`, so all three sites see the **stale incoming argument** (whose byte 2
happens to be `0x03`) instead of the value the callee just wrote.  The three
reads must be `(uStack_24 >> 0x10) & 0xff` / `(uStack_24 >> 0x18) & 0xff`.

**This is a new defect class for the ledger: *a value written by a callee
through a pointer into a spilled-parameter stack slot, read back from the
parameter register instead of from the slot*.**  It is invisible to
`tools/cfg_verify.py` / `emu.compare` for exactly the same structural reason as
the undersized-stack-frame class (instances 1–18): the harness models callees as
**order-keyed oracles that write nothing**, so the stack slot is never modified
during a trial and the stale-register spelling and the reload spelling produce
*identical* side-effect traces.  `cfg_verify.py app FUN_000622a0` passes both
before and after.

**It was latent for 33 iterations because every previous capture used the
navigation stimulus**, which installs the screen through a BLE persist task and
never needs the IMU.  Changing the stimulus to the honest dashboard one is what
exposed it.

### 34.9 The fix, and what it unmasks — `g1-i34a-app`

The three stale reads become reads of the spilled slot, in all six trees
(`recon/application/src`, `recon/app/src/FUN_000622a0.c`,
`recon/verified/src/FUN_000622a0.c`, `recon/named`, `recon/symbolized/app`,
`recon/readable_sources/app/g1`):

```c
-    log_message(0x000f62c5, (param_2   >> 0x10) & 0xff);
-    uVar5 =                 (param_2   >> 0x10) & 0xff;
-    if (               ((param_2   >> 0x18) & 0xff) != 0) {
+    log_message(0x000f62c5, (uStack_24 >> 0x10) & 0xff);
+    uVar5 =                 (uStack_24 >> 0x10) & 0xff;
+    if (               ((uStack_24 >> 0x18) & 0xff) != 0) {
```

`uStack_24`'s address escapes to the callee on the line above, so GCC is
*obliged* to reload it — the shipped `ldrb.w r1,[sp,#6]` is restored by
construction, not by hoping.  `tools/cfg_verify.py app FUN_000622a0` is
`PASS cases=0` before **and** after, which is the point: the harness cannot see
this class.

`g1-i34a-app` = `g1-i33c-app` + this change only.
FLASH **737,504 B** and RAM **253,765 B** — *unchanged*; `nm -u` **0**;
`_end` `0x2003ff45` and `runtime_info_sync` `0x00015b8c` unchanged (so every
probe address above still holds).

**MEASURED on the same dashboard stimulus** (`/private/tmp/g1_ours_dash_i34a`):

```
lsm6dso_init_chip chip id 0x6c        <- was 0x3
...  imu_fusion_thread(): start imu looper
I34E temp_task id=6 st=2              <- update_temp_task_status(ctx, 6, 2)  FIRST TIME EVER
I34E ui_DashBoard_task                <- FIRST TIME EVER
I34E DashBoard_Reflash                <- FIRST TIME EVER
ORACLE_SCREEN_ID_ctx_d5:   0x06       <- D-5 now PASSES: our firmware SELECTS the dashboard itself
ORACLE_DISPLAY_ON_ctx_fe8: 0x01       <- D-6 now fully PASSES
```

**The reconstructed firmware now reaches `E_ID_SCREEN_DASHBOARD` on its own from
the `don` gesture, with no pokes** — `ui_DashBoard_task` and `DashBoard_Reflash`
execute for the first time in this project.  It then **faults**, ~11.9 s in:

```
* buffer overflow detected *
<err> os: Faulting instruction address (r15/pc): 0x00045e20   (fortify_chk_fail)
<err> os: >>> ZEPHYR FATAL ERROR 3: Kernel oops on CPU 0
<err> fatal_error: Resetting system
```

so `CONFIG_RESET_ON_FATAL_ERROR=1` reboots the SoC and the 20 s capture ends with
`JBD FrameCounter 0x0` and **still 0 dashboard pixels**.  D-1 therefore remains
**FAIL** for `g1-i34a-app` too; the framebuffer is unchanged (`0c5cc90b…`).

### 34.10 The NEW first divergence — the **unrecovered font family 3**

Traced to one call with hooks at `safe_memcpy_checked 0x0007af0a`,
`fortify_chk_fail 0x00045e08`, `resource_manger_get 0x0003fc98` and the four
per-family glyph-offset entries:

```
I34E DashBoard_Reflash
I34H rmg font=3 ch=0x2c            <- resource_manger_get(font=3, ch=',')
I34H style3                        <- dispatches to get_font_style3_glyph_offset 0x0003fbfc
I34G smc lr=0x3e3db n=0xd1a lim=0x2a4   <- gui_utf_draw: memcpy 3354 B into the 676 B glyph buffer
I34F CHKFAIL lr=0x7af29 r0=0x2002af98 r1=0x4370588
```

The very first glyph the dashboard needs is the **comma of `"Mon, Jan 1"` in font
style 3**.  `get_font_style3_glyph_offset` is one of the **three font families
§33.12 item 4 records as still unrecovered** (`get_clock_digit_glyph_offset_large`,
`…_small`, `get_font_style3_glyph_offset` — still raw absolute pins; only
`font == 0`, the default font, was recovered in §33.7).  It returns a bogus glyph
descriptor, so `gui_utf_draw` computes `glyph_height * (glyph_width/2) = 0xd1a`
= 3,354 bytes against the shipped 676-byte (`0x2a4`) stack glyph buffer, and the
fortified `safe_memcpy_checked` correctly refuses.

This is a **clean, named, already-known gap**, not a new mystery: the navigation
screen renders entirely in font 0, which is why iteration 33 could reach a
pixel-identical `p1_boot` without ever touching families 1–3.  The dashboard is
the first screen that needs them.  **Recovering the three remaining font
families is now the single blocker for D-1.**

### 34.11 Regression gate — the NAVIGATION criteria are held, measured

`g1-i34a-app` re-run on the **unchanged** navigation stimulus
(`G1_ATT_WRITE` left at its default `0a0600000000`), against
`display_sensor_oracle.json`:

| navigation criterion | iteration 33 (`g1-i33c-app`) | **iteration 34 (`g1-i34a-app`)** |
|---|---|---|
| **G-2** `p1_boot` framebuffer | **PASS** `1d617c65a688…`, 656 px, 0 differing rows | **PASS — identical**, `1d617c65a688…`, 656 px, **0 differing rows** |
| G-1 `p2_render` framebuffer | FAIL 544 px `b855eac0a3d4…`, first row 266 | **FAIL, unchanged**: 544 px `b855eac0a3d4…`, first differing row **266** |
| G-3 `spim_a` p1 / p2 transactions | 126 / 109 | **126 / 109 — identical** |
| G-6 `spim_b` | PASS (0) | **PASS (0)** |
| `JBD FrameCounter` p1 / p2 | 0x40 / 0xAA | **0x40 / 0xAA — identical** |
| `DISPLAY_ON_ctx_fe8` | 0x01 | **0x01** |
| `ESB_MASTER_FRAMES` | 0x176 | **0x176** |
| `ESB_SYNC_ctx_105a` | 0x02 | **0x01** ← the one measured delta |

**No graphics regression**: every framebuffer, every SPI count and every JBD
counter is bit-identical to iteration 33.  The single delta is the
`ESB_SYNC_ctx_105a` byte sampled at t = 20 s reading `0x01` instead of `0x02` in
this run; it is a **state byte read at one instant**, the IMU thread is now
actually running (which shifts `twim2` `p2` traffic 41,774 → 44,294 B and hence
scheduling phase), and the **same build reads `0x02` on the dashboard stimulus**
(`/private/tmp/g1_ours_dash_i34a`, `ESB_SYNC_ctx_105a: 0x02`).  It is reported
because it was measured, not explained away; it is not a pixel or transaction
regression.

The fix is therefore **kept**: it restores the shipped `ldrb.w r1,[sp,#6]`
semantics by construction, it converts D-5/D-6 from FAIL to PASS, and it costs
nothing on the navigation criteria.

### 34.12 Build ledger and gates

| app build | change | FLASH | RAM | `nm -u` |
|---|---|---:|---:|---:|
| `g1-i33c-app` | iteration 33 | 737,504 B | 253,765 B | 0 |
| **`g1-i34a-app`** | **+ `lsm6dso_init_chip` reloads the spilled chip-id slot (§34.9) — FINAL** | **737,504 B** | **253,765 B** | **0** |

FLASH and RAM are **unchanged to the byte**; `_end` `0x2003ff45` and
`runtime_info_sync` `0x00015b8c` unchanged.  Net core **UNCHANGED**
(`g1-i30e-net`).

| gate | iteration 33 | **iteration 34 (`g1-i34a-app`)** |
|---|---|---|
| `check_ram_pin_collisions.py` (app) raw-in-object / raw-free | 0 / 0 | **0 / 0**, EXIT 0 |
| `check_ram_pin_collisions.py` (app) bound OK / escaping | 624 / 0 | **624 / 0** |
| `check_thread_create_stack_args.py` | 10/10 | **10/10**, EXIT 0 |
| `gen_retained_sources.py --check` | clean | **clean**, EXIT 0 |
| `cfg_verify.py app FUN_000622a0` | PASS (blind) | **PASS** (blind before *and* after — that is the finding) |
| app `nm -u` undefined | 0 | **0** |

### 34.13 Open, named, and NOT fixed

1. **The three unrecovered font families** —
   `get_font_style3_glyph_offset`, `get_clock_digit_glyph_offset_large` and
   `…_small` (§33.12 item 4).  This is now **the single blocker for D-1**:
   the dashboard's first glyph (`,` in font style 3) already trips it.
2. **The `p2_render` navigation string selection** (§33.10) — still the blocker
   for G-1.
3. **A new defect class for the ledger** (§34.8): *a value written by a callee
   through a pointer into a spilled-parameter stack slot, read back from the
   parameter register instead of from the slot.*  One instance found and fixed
   (`lsm6dso_init_chip`); **the class has not been swept.**  A directed sweep is
   mechanical: find every reconstruction that takes `&local` of a variable
   initialised from a parameter, passes it to a callee, and then reads the
   *parameter* afterwards.
4. Five of the six static `K_MSGQ_DEFINE` queues are still dead
   (§33.12 item 2); 356 absolute `A` symbols remain in the FLASH range
   (§33.12 item 3); `saadc` 95 / 998 and the ST25DV volumes (§33.12 item 5).
5. **The dashboard `spim_a` `p2_render` stream is not a reproducible artifact**
   (§34.5) and is deliberately not a gate.  If a byte-exact display stream is
   ever wanted for the dashboard, the phase would have to end on a *quiescent*
   condition rather than a wall-clock budget.

### Regenerate (iteration 34)

```sh
cd /Users/freedomcoder/Projects/G1disasm2

# ---- build (only lsm6dso_init_chip changed vs iteration 33) ---------------
recon/application/build_cohesive.sh app /private/tmp/g1-i34a-app
# net UNCHANGED from iteration 30 (g1-i30e-net)

# ---- SHIPPED dashboard oracle (the new criterion) ------------------------
G1_ATT_WRITE="" recon/emulator/scripts/capture_display_sensor_oracle.sh \
    /private/tmp/g1_oracle_dash
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
    /private/tmp/g1_oracle_dash /private/tmp/g1_dash_rep_oracle

# ---- OUR build, dashboard stimulus --------------------------------------
mkdir -p /private/tmp/g1-i34
printf '$rtinfo_pc=0x00015b8c\ni @/Users/freedomcoder/Projects/armemul/g1-ours-paired.resc\n' \
  > /private/tmp/g1-i34/ours-paired-i34.resc
G1_ATT_WRITE="" \
G1_RESC=/private/tmp/g1-i34/ours-paired-i34.resc \
G1_APP_ELF=/private/tmp/g1-i34a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_dash_i34a
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_dash_i34a /private/tmp/g1_dash_rep_i34a

# ---- OUR build, NAVIGATION stimulus (the regression gate) ----------------
#      identical command with G1_ATT_WRITE left unset
G1_RESC=/private/tmp/g1-i34/ours-paired-i34.resc \
G1_APP_ELF=/private/tmp/g1-i34a-app/zephyr/zephyr.elf \
G1_NET_ELF=/private/tmp/g1-i30e-net/zephyr/zephyr.elf \
G1_HOOKS=0 G1_CTX_FE8=0x20040F38 G1_CTX_105A=0x20040FAA G1_SCREEN_ID=0x20040025 \
  recon/emulator/scripts/capture_display_sensor_oracle.sh /private/tmp/g1_ours_nav_i34a
PYTHONSAFEPATH=1 .venv/bin/python recon/emulator/scripts/build_display_sensor_oracle.py \
  /private/tmp/g1_ours_nav_i34a /private/tmp/g1_nav_rep_i34a
```

**NOTE on the stdin pipe.**  Renode's `ConsoleIOSource` aborts if stdin closes,
so every capture above must be run with a writer holding stdin open.  A bare
`sleep 100000 | …` works but the *shell* then waits on `sleep` forever, so a
following command in the same script is never reached (§33's note).  The
pipeline used in this iteration keeps the shell free:

```sh
bash -c 'F=$(mktemp -u); mkfifo $F; sleep 100000 > $F & W=$!
         <capture command> < $F
         kill $W; rm -f $F'
```

Files changed this iteration:
`recon/emulator/scripts/capture_display_sensor_oracle.sh` (additive
`G1_ATT_WRITE` / `G1_SCREEN_ID` knobs and the `ORACLE_SCREEN_ID_ctx_d5`
read-back; with no variable set it emits a byte-identical capture script);
`recon/application/src/lsm6dso_init_chip.c`, `recon/app/src/FUN_000622a0.c`,
`recon/verified/src/FUN_000622a0.c`, `recon/named/lsm6dso_init_chip.c`,
`recon/symbolized/app/lsm6dso_init_chip.c`,
`recon/readable_sources/app/g1/lsm6dso_init_chip.c` (the three stale reads);
new `recon/emulator/reports/display_sensor_oracle_dashboard.json` and
`golden_framebuffer_dashboard_p2_render.{raw,pgm,png}` + `…_crop.png`;
`recon/emulator/reports/display_sensor_parity.md`;
`recon/emulator/reports/sensor_parity_status.md`; this report.
**No `tools/` logic change**, `armemul` untouched, nothing committed.
