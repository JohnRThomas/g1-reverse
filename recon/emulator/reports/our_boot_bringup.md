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
