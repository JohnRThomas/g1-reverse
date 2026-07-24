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
