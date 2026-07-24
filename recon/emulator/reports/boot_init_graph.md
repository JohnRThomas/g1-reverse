# Boot init + thread-creation graph (static evidence)

Static recovery of the SoC/kernel/driver **init-level graph** and the
**thread-creation graph** from the shipped images, plus the concrete wiring
proposal for replacing the cohesive build's *temporary main* with the real
init graph. Analysis only — no build/tool/recon changes.

- App image `app_update.bin` (link base `0xC200`, sha `e0614feb…`).
- Net image `netcore_image.bin` (analysis base `0x01008000`, runtime/link base
  `0x01008800`, delta `0x800`; init pointers are runtime-based).
- Machine-readable: `boot_init_graph_app.json`, `boot_init_graph_net.json`.

---

## 1. Headline finding

**Neither core registers a single application-owned `SYS_INIT` / `DEVICE_DT`
entry.** Every entry in every init level on both cores is stock
Zephyr / nrfxlib / Nordic SoC code that the pinned NCS 2.5.1 SDK emits
automatically from Kconfig + devicetree. All Even-specific bring-up happens
**inside `main()`**, which spawns the application threads **dynamically via
`k_thread_create`** — there are **no static `K_THREAD_DEFINE`** application
threads either.

Consequence for the rebuild: the init-level arrays do **not** need any
hand-written `SYS_INIT`/`DEVICE` registrations — they fall out of the correct
`prj.conf` + `.overlay`. The *only* thing the temporary main hides is the real
`main()` and its dynamic thread pool. Replace the temporary main with the real
`main` and the boot graph matches the original.

| core | init entries | app-owned init | sdk/stock init | unresolved init | threads (app / sdk) |
|------|:---:|:---:|:---:|:---:|:---:|
| app  | 48 (across 4 levels) | **0** | 48 | 0 | 16 app-dynamic / 1 stock BT |
| net  | 26 (across 3 levels) | **0** | 24 | 2 (sdk-region) | 3 app-dynamic / 5 sdk |

---

## 2. App core (`app_update.bin`)

Init arrays (from `recon/catalogs/app_root_inventory.json`, curated + verified
against the NCS 2.5.1 `refapp` build; every entry `ownership:"stock"`):

| level | bounds (VA) | count | notable entries |
|-------|-------------|:---:|-----------------|
| PRE_KERNEL_1 | `0x879b0`–`0x87a38` | 17 | nordicsemi_nrf53_init, posix pools, clock_control_nrf_init, kheap/mem_slab, gpio_nrfx ×2, cc3xx early, entropy ×2, wdt, uarte, uart_console |
| PRE_KERNEL_2 | `0x87a38`–`0x87a40` | 1 | sys_clock_driver_init (nrf_rtc_timer) |
| POST_KERNEL | `0x87a40`–`0x87b20` | 28 | rtc_pretick, log_init, mbox, malloc_prepare, nrf_cc3xx_platform_init, k_sys_work_q, qspi_nor, ipc_static_vrings, adc, soc_flash, i2c ×2, remoteproc_mgr_boot (CPUNET boot), long_wq/bt_rpmsg, npm1300 mfd/gpio/wdt/regulators ×5, pdm, opt3001, npm1300_charger, sync_rtc_setup |
| APPLICATION | `0x87b20`–`0x87b30` | 2 | mcumgr_handlers_init, smp_init |

- 26 `struct device` handles at `0x87b30` (stride 24), all stock drivers.
- SW-ISR table at `0x87da0` (69 slots, 11 non-default) — all stock driver ISRs.

**All 48 init entries are SDK-owned. Zero must be hand-registered.**

### App threads (all dynamic `k_thread_create`, `prio<0` = coop)

The kernel main thread runs **`main` @ `0x00016eb8`** (the real main to install).
`run_main_dispatch_thread` @ `0x0002a65c` (reached from main) is the spawn hub
for the `run_main_*` pool. 16 application threads + 1 stock Zephyr BT-RX thread:

- ancs `0x19950/0x19718` (-11); ble_projector `0x21da8` (-15); flash `0x23480`
  (-12); brightness `0x23844` (-11); display `0x49090` (-14); proxy `0x47c48`
  (-12); aging_a `0x32420` (-12); aging_b `0x324bc` (-12).
- run_main pool a–h: entries `0x2a8d8/0x2685c`, `0x286f8`, `0x2a4f4`, `0x28bec`,
  `0x2692c`, `0x27cfc` (conditional, mode 2), `0x2a0d8/0x28a1c`, `0x2955c`;
  prios -9…-14; stacks 1024–3072.
- bt_rx `0x545f0` (-9) — **stock Zephyr BT**, not app.

The **3 previously-missing thread roots are resolved** (all cfg_verify PASS,
named, in `recon/app/src/`), per `ownership/app_missing_thread_roots_recovery.json`:

| root | entry | status |
|------|-------|--------|
| master_display_thread | `0x2692c` | real catalog-missing entry; reconstructed |
| slave_display_thread  | `0x27cfc` | real entry (2 bytes before Ghidra entry) |
| aging_mode_thread     | `0x32420` | real catalog-missing entry; reconstructed |

---

## 3. Net core (`netcore_image.bin`)

Init arrays located structurally and confirmed via the `z_sys_init_run_level`
`levels[]` boundary table at runtime `0x0103cb48`
(`EARLY=PRE_KERNEL_1=idx0`, `PRE_KERNEL_2=idx15`, `POST_KERNEL=idx16`,
`APPLICATION=end=idx26`). The 26-entry init array is `0x0103be64`–`0x0103bf34`;
the 7-device handle array begins exactly at `0x0103bf34`.

| level | count | resolved contents |
|-------|:---:|-------------------|
| EARLY | 0 | — |
| PRE_KERNEL_1 | 15 | nordicsemi_nrf53_init; posix barrier/cond/mutex/thread pools; clock_control_nrf_init (`clock@41005000`); kheap_init; init_mem_slab_module; gpio_nrfx_init ×2 (`gpio@418c0500/0800`); mpsl_lib_init_sys; mpsl_fem_api_init*; entropy_nrf5_init (`random@41009000`); uarte_nrfx_init (`uart@41013000`); uart_console_init |
| PRE_KERNEL_2 | 1 | sys_clock_driver_init (nrf_rtc_timer) |
| POST_KERNEL | 10 | rtc_pretick_init; **[idx17 unresolved]**; mbox_nrfx_init (`mbox@41012000`); malloc_prepare; mpsl_low_prio_init; k_sys_work_q_init; backend_init (ipc rpmsg, `ipc0`); hci_driver_init (bt_sdc); sync_rtc_setup; **[idx25 unresolved]** |
| APPLICATION | 0 | — |

Naming evidence: dev-handle name strings; `__ASSERT` source-file literals in
each fn's literal pool (e.g. `zephyr/lib/posix/barrier.c`,
`zephyr/kernel/kheap.c`, `Failed synchronized RTC setup (err: %d)`); and
prologue byte-signature match vs the config-matched
`refapp/build/hci_rpmsg/zephyr.elf` (nordicsemi_nrf53_init 1.00, rtc_pretick
1.00, mpsl_lib_init_sys 0.94, mpsl_low_prio 0.88, k_sys_work_q 0.84,
malloc_prepare 0.81, uart_console 0.78, sys_clock_driver 0.78).
`*` mpsl_fem_api_init: symbol inferred by array position (stock).

**24 of 26 SDK-owned; 0 app-owned.** Two entries could **not** be resolved to a
symbol — see §5.

### Net threads

The net main thread runs **`g1_cpunet_main`** (`FUN_0102a720`, analysis
`0x0102a720` / runtime `0x0102af20`) — Even's custom net main, cfg_verify PASS,
reached via stock `bg_thread_main +0x1c` (`ownership/net_current_callback_recovery.json`).
It is the net "real main" to install.

Threads (names from `k_thread_create` name strings in the image):

- **application (dynamic):** `main`→g1_cpunet_main; `cpunet-esbm` (ESB master
  role, `nrf/subsys/esb`); `cpunet-esbs` (ESB slave role). Spawned under the
  ESB bring-up in g1_cpunet_main.
- **sdk/stock:** `mpsl_nonpreemptible_thread_id`, `MPSL Work` (nrfxlib MPSL);
  `HCI rpmsg TX`, `HCI rpmsg RX` (stock transport); `sysworkq`
  (k_sys_work_q_init, POST idx21).

Entry addr / prio / stack for the ESB/MPSL/HCI threads are **not yet pinned to
the specific `k_thread_create` call sites** (see gap N3).

---

## 4. Gap list — to replace the temporary main with the real init graph

Wire into `recon/application/app` and `recon/application/net`:

**App (A):**
- **A1.** Install real `main` (`0x00016eb8`) as the app main; drop the temporary
  main. It transitively reaches `run_main_dispatch_thread 0x2a65c`.
- **A2.** No `SYS_INIT`/`DEVICE` to hand-write — all 48 entries + 26 devices are
  SDK. They must reproduce from `prj.conf` + `g1_board.overlay`; verify the
  build's own init arrays match the four level counts **17 / 1 / 28 / 2** and 26
  devices (gate already in `app_root_inventory.json`).
- **A3.** Ensure the 16 app threads are created by the reconstructed
  `main`/`run_main_dispatch_thread` bodies (they are dynamic — do **not** add
  `K_THREAD_DEFINE`). Args/stacks/prios per `wiring/app_objects.c` and
  `boot_init_graph_app.json`.
- **A4.** `bt_rx 0x545f0` comes from the stock BT host TU — do not redefine.

**Net (N):**
- **N1.** Install `g1_cpunet_main` (`0x0102af20`) as the net main; drop the
  temporary net main. Stock `bg_thread_main` calls it.
- **N2.** No app `SYS_INIT`/`DEVICE` to hand-write — all 26 entries + 7 devices
  are SDK. Reproduce from net `prj.conf` (note: enables `CONFIG_POSIX_API`,
  `CONFIG_HEAP_MEM_POOL_SIZE`, MPSL, SDC/BT, IPC, `CONFIG_NRF53_SYNC_RTC`) +
  overlay. Verify level counts **15 / 1 / 10** and 7 devices.
- **N3.** Pin the ESB (`cpunet-esbm`/`cpunet-esbs`) `k_thread_create` sites
  inside g1_cpunet_main's tree (entry/prio/stack/args) so the dynamic net thread
  pool reproduces. MPSL/HCI/sysworkq threads are SDK — do not redefine.

**Blocking risk:** none of the gaps require unrecovered code — `main`
(both cores) and the thread roots are already reconstructed and cfg_verified.
The two unresolved net init symbols (§5) are SDK-region and do not block, but
should be pinned for a byte-exact `.text` comparison.

---

## 5. Init entries not resolved to a symbol

App: **none** (all 48 named).

Net: **2** (both PRE-classified `sdk_unresolved`; both sit in SDK address regions
and reference **no** application strings or code, so neither is app-owned):

- **POST idx17** — init fn runtime `0x0102e434` (analysis `0x0102dc34`). Not in
  the refapp hci_rpmsg build; prologue matches nothing there. Sets up a 0x24
  stack frame + calls `0x103bb8e`. Best guess: `log_init` or a controller work
  init. **Symbol unconfirmed.**
- **POST idx25** — init fn runtime `0x01034934` (analysis `0x01034134`). Not in
  refapp; register-heavy loop pushing r4-r8/sb, iterating a table
  (`0x1008a00`). Candidate ESB/SDC or nrfx-clock-mpsl init. **Symbol
  unconfirmed.**

Both are the "extra" POST entries the Even net build has beyond the reference
hci_rpmsg build (Even also adds `sync_rtc_setup` at idx24, which the reference
lacks). They warrant a per-function disassembly pass before a byte-exact net
`.text` comparison, but do not affect the "zero app-owned init" conclusion.
