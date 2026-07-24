# Golden Boot Trace — shipped Even Realities G1 firmware in Renode

`golden_boot_trace.json` is a **deterministic behavioral oracle** of the SHIPPED
G1 images booting inside the Renode nRF5340 emulator. It is an ordered,
per-core list of **function-entry events** (first-entry order + repeat counts +
instructions-executed), each mapped to the recon symbol name, with milestone
markers **E1–E5**. A firmware rebuilt from reconstructed C sources must
reproduce this event order/structure; use this file as the diff target.

It is bounded (one entry per unique function per core, ~1117 app + ~739 net),
**not** a multi-GB per-instruction log. The raw PC traces it is derived from
(~12.6M app + ~2.2M net lines) are intermediate and discarded.

## Images (read-only)

| core | image | base | sha256 |
|------|-------|------|--------|
| CPUAPP | `app_update.bin` | link 0xC200 | `e0614feb…b42fd3b` |
| CPUNET | `netcore_image.bin` | runtime 0x01008800 | `ec4e4b60…158f7ca4` |

## Determinism knobs (fixed; the trace regenerates identically)

| knob | value |
|------|-------|
| Emulator | Renode 1.16.1 (d66b0c2a) |
| Global quantum | `0.000010` s (`emulation SetGlobalQuantum`) |
| Core scheduling | serial — `MasterTimeSource.ExecuteInSerial = True` (in `g1.resc`), removes the cross-core NVIC race |
| CC312 entropy | `NRF5340_CC3xx_RNG` SplitMix64, **seed `0x5340CC3105340CC3`** — the only stochastic source; fixed ⇒ identical entropy stream |
| Virtual-time budget | `3.0` s (in six 0.5 s checkpoints) |
| External stimulus | **none** — `vcentral` / `esbslave` / gesture all disabled → pure autonomous boot |
| Trace format | `cpu CreateExecutionTracing … PC`; trace line index == `cpu.ExecutedInstructions` (0-based) |
| PC → symbol | greatest catalog address ≤ PC. App: `function_names_app.json` `by_address`. Net: `net_address_spaces.json` `functions[].runtime_address` (execution base 0x01008800, **not** analysis base 0x01008000) |

The instruction indices `first_i` in the JSON **are** the `ExecutedInstructions`
counter values, so they are exactly comparable run-to-run.

## Milestones reached: E1, E2, E3, E4, E5 (all)

| marker | meaning | core | anchor (first_i / exec_instr) |
|--------|---------|------|-------------------------------|
| **E1** | reset → kernel bring-up | app | reset vector `i=0`; region_init `448729`, k_sem_init `449110` |
| **E2** | device / SYS_INIT driver init | app | `clock_control_nrf_init` `449683`; gpiote `451254`; **`nrf_cc3xx_platform_init` `451908`** |
| **E3** | `main()` + thread creation | app | `z_impl_k_thread_create` `982573`; `main` `5045146` |
| **E4** | "it lives": net released + IPC + display init + first ADV_IND | app+net | `bt_start` `7641560` |
| **E5** | steady state (operational loop) | app+net | `12097930` (virtual t=2.0 s) |

### E1 — reset → kernel
Reset vector (SP/PC from VTOR 0xC200) → `.bss`/`.data` init (`memset_bytes`,
`memcpy`) → `region_init` → `arm_core_mpu_configure` → kernel objects
(`z_impl_k_sem_init`, `kmutex_dlist_init`). **Cross-checks `original_boot.json`**
(the Unicorn strict boot): region_init@448729 vs 448730, k_sem_init@449110 vs
449109, clock_control_nrf_init@449683 vs 449682 — the Renode boot chain matches
the independent Unicorn oracle to within a handful of instructions.

### E2 — device / SYS_INIT init
`clock_control_nrf_init`, `nrfx_clock_init/enable`, `onoff_manager_init`,
`sys_heap_init`, `g1_recon_nrfx_gpiote_init`, and **`nrf_cc3xx_platform_init`**.
This is **past the CC312/TRNG blocker** that halted the Unicorn boot
(`boot_blockers.md`): the seeded `NRF5340_CC3xx_RNG` model answers the ROSC
entropy poll so the TRNG startup self-test completes and boot proceeds.

### E3 — main + threads
Kernel threads created (`z_impl_k_thread_create`), then application `main()`
(0x16eb8) and `thread_entry_no_return`, `settings_subsys_init`.

### E4 — "it lives"
All four sub-conditions confirmed autonomously (no phone / no paired lens):
- **CPUNET released & executing** — app cleared `RESET.NETWORK.FORCEOFF`
  (0x50005614); net begins at its reset vector 0x0102fc8c (`net_first_i=0`).
  Net is running by the t=0.5 s checkpoint.
- **IPC up** — `ipc_service_send` (OpenAMP/rpmsg over `sram0_shared`), `449669`.
- **Display init** — JBD panel SPI ID probe `spi_read_id` (0x47724), `7273380`.
- **BLE stack start** — `bt_start` (0x19308), `7641560`.
- **First BLE ADV_IND** — modeled RADIO `TransmittedFrames` 0→1 in the
  **t∈(1.0, 1.5] s** window (see checkpoints), climbing to 6 by t=2.0 s.

### E5 — steady state
Boot/init one-shots are done; the app core is dominated by
`arch_cpu_idle`/`wfi_idle_loop` (WFI halts the core between periodic wakeups —
which is why the app only executes ~12.6M instructions in 3 virtual seconds,
most of it idle), the net SDC advertising loop cycles (radio frames hold at 6),
and new-function discovery has flatlined into periodic-task first-invocations
(watchdog feed, timers). No further boot phases.

## Checkpoints (virtual time → radio frames, per-core ExecutedInstructions)

| t (s) | radio_tx | app_exec_instr | net_exec_instr |
|-------|----------|----------------|----------------|
| 0.5 | 0 | 8,632,484 | 381,621 |
| 1.0 | 0 | 9,367,446 | 381,621 |
| 1.5 | **1** | 10,093,205 | 422,490 |
| 2.0 | 6 | 12,097,930 | 2,157,739 |
| 2.5 | 6 | 12,369,194 | 2,157,739 |
| 3.0 | 6 | 12,629,795 | 2,157,739 |

## Regenerate (one command)

```sh
mkdir -p /tmp/g1_golden && cd /Users/freedomcoder/Projects/armemul && \
~/tools/Renode.app/Contents/MacOS/renode --disable-xwt --console --plain \
  -e 'i @/Users/freedomcoder/Projects/G1disasm2/recon/emulator/scripts/golden_trace.resc' \
  > /tmp/g1_golden/golden_run.out 2>&1 ; \
R=/Users/freedomcoder/Projects/G1disasm2 ; V="PYTHONSAFEPATH=1 $R/.venv/bin/python" ; \
$V $R/recon/emulator/scripts/analyze_trace.py app /tmp/g1_golden/trace_app.log /tmp/g1_golden/events_app.json ; \
$V $R/recon/emulator/scripts/analyze_trace.py net /tmp/g1_golden/trace_net.log /tmp/g1_golden/events_net.json ; \
$V $R/recon/emulator/scripts/build_golden.py /tmp/g1_golden
```

Scripts live in `recon/emulator/scripts/` (`golden_trace.resc`,
`analyze_trace.py`, `build_golden.py`); `build_golden.py` writes
`recon/emulator/reports/golden_boot_trace.json`.

## Scope / limitations

- **Autonomous boot only.** No BLE central and no ESB right-lens peer are
  attached, so the trace is the firmware's own boot with zero external timing
  dependence — the most reproducible oracle. First ADV_IND still occurs (the
  SDC advertises autonomously). The `g1-selfdrive.sh` acceptance harness adds a
  virtual phone (CONNECT/GATT) and a virtual lens (ESB sync → display blit);
  those paths are **beyond E5** and deliberately excluded here to keep the
  oracle deterministic and stimulus-free.
- **Symbol granularity.** PC→name uses "greatest catalog address ≤ PC" (as
  specified). Code regions with no named symbol fold into the preceding
  function — e.g. the reset handler at 0x50a98 (no dedicated symbol) reports as
  the `z_arm_fault` region. This is deterministic and does not affect the
  first-entry/order oracle.
- **Radio frame cadence** is a property of the `NRF5340_RADIO` timing model, not
  the firmware; the E4 "first ADV_IND" marker records the firmware reaching a
  transmitting advertising state, evidenced by `TransmittedFrames` crossing 0→1.
```
