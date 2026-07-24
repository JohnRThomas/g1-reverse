# Thread-wiring + boot-path-fix propagation check (CPUAPP/CPUNET cohesive build)

Finalization pass for boot-parity: propagate the two corrected boot-path sources
into the app image, rebuild both cores honestly, and verify the dynamic
thread-creation graph is wired on both cores.

Build baseline: committed `b83dab8e` + `1ae0cb4b` (clean link both cores).
Toolchain nm: `zephyr-sdk-0.16.5-1/arm-zephyr-eabi/bin/arm-zephyr-eabi-nm`.
Nothing committed by this pass.

---

## Task 1 — propagation of the two corrected app sources

The build compiles `recon/symbolized/app/*.c` (via `recon/named/*.c`), NOT
`recon/app/src/*.c`. The two boot-path fixes had been saved only to
`recon/app/src` + `recon/verified/src`.

**Sanctioned-tool path was not viable this session, so propagation was surgical
(the task's sanctioned fallback).** `tools/symbolize.py` and
`tools/build_symbol_map.py` both hard-code the stale scratchpad
`bf259b2e-.../symbol_map.json`, which no longer exists, and `refgraph_app.json`
(required by `build_symbol_map.py` to distinguish real address literals from
scalars) is also gone. Regenerating the map degraded would have mis-classified
addresses and materially rewritten the whole symbolized tree — violating the
"only the 2 target files change materially" constraint. Surgical propagation was
performed instead, guaranteeing exactly that blast radius.

Findings when diffing the trees:

- **`now_has_persist_task`** — named + symbolized were **stale/buggy**: both log
  calls were no-arg `log_message()` / `debug_print()` (the vacuous "300/300
  PROVEN" body). Rewrote both to the corrected body: `log_message`/`debug_print`
  called with the full 5-arg list `(0xa2566, 0xa267b, uVar3, param_2, b)` and the
  `b = *(u8*)(param_1+0xd5)` load, matching `recon/app/src`.
- **`update_persist_task_status_to_idle`** — named + symbolized were **already
  semantically correct** (they already called `log_message(&rodata_a25d9,
  &rodata_a2625)` 2-arg and `debug_print(...,0)` 3-arg). Only the provenance
  comment was stale ("300/300 PROVEN", `log_message` missing from the callee
  list); refreshed the comment. Body unchanged.

String-pointer note: the corrected `now_has` introduces flash string pointers
`0xa2566`/`0xa267b`. These are **kept as numeric literals** in the symbolized
copy (not turned into `&rodata_*` symbols) because — unlike `rodata_a25d9`/
`rodata_a2625`, which have `PROVIDE()` backing in `g1_app_globals.ld` — no
symbol is provided for `0xa2566`/`0xa267b`; inventing one would break the honest
link. This matches the raw `recon/app/src` form and is auditable.

Files changed (exactly 4, verified via `git status`):
`recon/named/{now_has_persist_task,update_persist_task_status_to_idle}.c`,
`recon/symbolized/app/{now_has_persist_task,update_persist_task_status_to_idle}.c`.

---

## Task 2 — clean rebuild, fixes present

Both builds were actually run this session (`build_cohesive.sh`).

| core | ELF | undefined (`nm -u`) | duplicate global defs | FLASH | RAM |
|------|-----|:---:|:---:|-------|-----|
| **app** (core image) | `/private/tmp/g1-p2fin-app/zephyr/zephyr.elf` | **0** | **0** | **616020 / 982528 B = 62.70%** | 75501 / 440 KB = 16.76% |
| **net** (standalone probe) | `/private/tmp/g1-p2fin-net/zephyr/zephyr.elf` | **0** | **0** | **227961 B / 226 KB = 98.50%** | 54076 / 64 KB = 82.51% |

- The app is a multi-image build; the app *core* is the 982528-B-region image
  above. (Sibling images in the same tree: mcuboot 38928/48 KB, b0n
  23426/34176 B, hci_rpmsg net-child 182056/222 KB — not the verification
  targets.)
- "Duplicate" = duplicate **global** (uppercase `T/D/B/R`) definitions; 0 on both
  cores. Local `static` symbols shared across TUs (`atomic_*`, `lock`,
  `mbox_callback`, …) are expected and harmless — the honest link (no
  `--allow-multiple-definition`) succeeded.

**Fixes compiled in (verified in the linked app ELF):**
- `now_has_persist_task` and `update_persist_task_status_to_idle` both present
  (`nm`: `0x00026700`, `0x0002694c`).
- `now_has_persist_task.c.obj` carries `R_ARM_THM_CALL` relocations to
  **`log_message`** (off 0x42) and **`debug_print`** (off 0x4c) — the corrected
  targets — plus `signal_persist_task_event`; both resolve in the ELF
  (`log_message` @0x00073abc, `debug_print` @0x000174d0). No unresolved no-op
  `DEBUG_PRINT` call remains.

Net was rebuilt and still links to a `zephyr.elf`, unaffected by the app-only
source changes.

---

## Task 3 — dynamic thread-creation graph presence

No static `K_THREAD_DEFINE`; all app/net application threads are spawned
dynamically via `k_thread_create`. Entry functions are checked for presence in
the linked ELF; the graph wiring is confirmed via the call graph.

### App (build retains all sections: `G1_INTEGRATION_PROBE_RETAIN_ALL=ON`)

Roots: **`main` present** (`nm` @0x00015510, catalog 0x00016eb8) and calls
`run_main_dispatch_thread`; **`run_main_dispatch_thread` present** (@0x00024ebc,
catalog 0x0002a65c). Wiring: `main → run_main_dispatch_thread →` 8 spawn helpers
(`start_ancs_work_thread`, `init_ble_work_thread`,
`spawn_flash_ops_and_brightness_threads`, `spawn_display_thread`,
`spawn_proxy_thread`, `start_aging_mode_thread`, `spawn_aging_mode_aux_thread`,
`main_dispatch_thread_tick`) — each calls `z_impl_k_thread_create`.

All **16/16 application thread entry functions present**:

| graph thread | entry VA | resolved symbol | in app ELF |
|--------------|----------|-----------------|:---:|
| ancs | 0x00019718 | `ble_ancs_data_req_thread` | ✅ |
| ble_projector | 0x00021da8 | `ble_work_thread` | ✅ |
| flash | 0x00023480 | `flash_ops_thread` | ✅ |
| brightness | 0x00023844 | `brightness_level` | ✅ |
| run_main_a | 0x0002a8d8 / 0x0002685c | `low_speed_peripheral_dispatch_thread` / `…_for_test` | ✅ |
| run_main_b | 0x000286f8 | `process_task_sync_event` | ✅ |
| run_main_c | 0x0002a4f4 | `transport_dispatch_thread` | ✅ |
| run_main_d | 0x00028bec | `display_dispatch_thread` | ✅ |
| run_main_e | 0x0002692c | `master_display_thread` | ✅ |
| run_main_f | 0x00027cfc | `slave_display_thread` (conditional) | ✅ |
| run_main_g | 0x0002a0d8 / 0x00028a1c | `touch_key_thread` / `click_event_dispatch_loop` | ✅ |
| run_main_h | 0x0002955c | `key_event_thread` | ✅ |
| aging_a | 0x00032420 | `aging_mode_thread` | ✅ |
| aging_b | 0x000324bc | `mic_transm_thread` | ✅ |
| proxy | 0x00047c48 | `proxy_thread_handler` | ✅ |
| display | 0x00049090 | `display_thread_handler` | ✅ |
| bt_rx (stock Zephyr BT) | 0x000545f0 | `hci_tx_thread` (catalog) | ⚠️ not present — **expected**; stock BT-RX, "do not redefine" (graph A4). `CONFIG_BT_RX_*` + `rx_thread_data` are present. |

Caveat (honest): the spawn helpers pass the entry as a fixed original-image
Thumb-address literal (`ADDR_ble_ancs_data_req_thread_THUMB = 0x19719`, etc.),
**not** a symbol relocation to the rebuilt function. So the wiring is present and
carries the correct original entry addresses, but the retained-reference to each
entry function comes from `--no-gc-sections`, not from the call site. Rebinding
these to `&<entry_symbol>` (so they relocate to our addresses) is a later
byte-relocation / full-cohesion step, not a boot-parity blocker.

### Net (build gc's sections: `G1_INTEGRATION_PROBE_RETAIN_ALL=OFF`)

- **Net real main present + rooted.** `FUN_0102a720` (= `g1_cpunet_main`, catalog
  0x0102a720) is at `0x0102a570`, and Zephyr **`main` binds to the same address
  0x0102a570** (forced root `-Wl,-u,FUN_0102a720` in the net CMake; net app
  compiles raw `recon/net/src/*`, so the human name `g1_cpunet_main` does not
  appear). ✅
- ESB subsystem compiled in (`nrf/subsys/esb`: `esb.c`, `esb_dppi.c`;
  `CONFIG_ESB=y`); `z_impl_k_thread_create` present.

| graph thread | owner | entry symbol | in net ELF |
|--------------|-------|--------------|:---:|
| main → g1_cpunet_main | application | `FUN_0102a720` (main→0x0102a570) | ✅ rooted |
| cpunet-esbm (ESB master role) | application | *unpinned in graph (N3)* | ❌ **not wired** |
| cpunet-esbs (ESB slave role) | application | *unpinned in graph (N3)* | ❌ **not wired** |
| mpsl_nonpreemptible / MPSL Work / HCI rpmsg TX/RX / sysworkq | sdk_stock | (SDK) | n/a (stock) |

**GAP flagged — net ESB role threads not wired (known graph gap N3).** The
`cpunet-esbm`/`cpunet-esbs` thread-name strings are absent from every
reconstructed net source *and* from the linked net ELF, and **no reconstructed
net object calls `k_thread_create`**. `g1_cpunet_main`'s reconstructed tree
(`FUN_0102a720` → its `FUN_*` callees) does not reach a `k_thread_create` for the
ESB role threads. Per `boot_init_graph_net.md` §4/N3 these `k_thread_create` call
sites inside `g1_cpunet_main`'s tree are "not yet pinned (entry/prio/stack/args)".
Consequence: our net build spawns fewer application threads than the original —
the two ESB master/slave role threads are missing from the dynamic pool. This is
a pre-existing wiring gap, not a regression from this pass.

---

## Summary of gates

- App rebuild: **clean** (0 undefined, 0 duplicate-global). Both boot-path fixes
  compiled in; `now_has` now calls `log_message`/`debug_print` with full args.
  FLASH 62.70%.
- Net rebuild: **clean** (0 undefined, 0 duplicate-global), links to `zephyr.elf`.
  FLASH 98.50%. Net real main rooted.
- Thread graph: **app 16/16 application entries present and wired** (bt_rx is
  stock/expected). **Net main rooted; the 2 ESB role threads are NOT wired
  (gap N3)** — the one outstanding wiring gap for net boot-parity.
