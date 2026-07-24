# Library-displacement candidates — recovered functions that are actually SDK code

**Analysis only.** Nothing in `recon/application/`, `recon/generated/`, `recon/symbols/`,
`recon/app/src`, `recon/net/src`, `recon/symbolized/`, `recon/ownership/adoption_manifest.json`
or `tools/` was modified. The two files written by this pass are
`recon/ownership/library_displacement_candidates.json` (machine-readable, manifest-ready)
and this report.

*Snapshot caveat:* the retained-source set, `recon/symbols/g1_app_globals.ld` and
`recon/generated/app_retained_sources.cmake` were read at the start of this pass while another
agent was editing build files. Re-derive the "retained" flag before applying a batch if those
files have moved; the byte evidence itself is snapshot-independent (it compares
`app_update.bin` / `netcore_image.bin` against the pinned SDK).

---

## 0. Why this exists (restating the owner's directive)

Recovered hand-reconstructions of stock library code are a liability. They carry defects the
parity harness **cannot** see, because `tools/parity` and `tools/cfg_verify` emulate at the
*original* addresses where wrong-but-accidentally-working codegen still reproduces the
side-effect trace. `our_boot_bringup.md` iteration 5 §3 proved the class exists:

* `gpio_pin_configure` / `gpio_pin_configure_17688` dereferenced `dev->config` one pointer level
  too deep — invisible until the *correct* device pointer was bound;
* `gpio_pin_set_checked`, `gpio_pin_configure_17688` and `z_tick_sleep` dropped arguments at
  `(*UNRECOVERED_JUMPTABLE)()` / zero-argument `extern` call sites and only worked because the
  original codegen happened to leave the right values in r0–r2.

All of those pass parity today. Displacing the affected bodies to the real SDK removes that
whole class and restores real types.

---

## 1. Method and the evidence gate

The primary gate is the same one `tools/build_app_bluetooth_stock_adoption.py` already uses,
applied exhaustively instead of to a hand-picked list:

1. Index **every** `.text.<sym>` section of **every** object file and archive member of the
   pinned NCS 2.5.1 builds — the iteration-5 cohesive build `/private/tmp/g1-i5d-app`
   (app + `hci_rpmsg`), `~/ncs251/refapp/build`, `~/ncs251/netref_build`,
   `~/ncs251/nrfxlib/softdevice_controller/lib/cortex-m33+nodsp/soft-float`, and the
   arm-zephyr-eabi 12.2.0 `libgcc.a` / `libc_nano.a` / `libm_nano.a` multilib archives.
   **5 996 app symbols, 2 335 net symbols.**
2. For every catalogued firmware function, compare the shipped image bytes at its VA with each
   upstream section after zeroing the 4-byte window at every relocation offset.
3. Keep only pairs that agree over the **entire upstream section** — including the tail past
   Ghidra's reported function size. This is the decisive refinement: **647 of 648 app matches
   and 33 of 33 net matches agree over the full upstream section**, which proves the size
   deltas were Ghidra under-reporting (trailing literal pool), not code divergence.
4. Re-score with **distinguishing bytes** = section length − 4 × (relocation slots masked), so a
   relocation-dominated stub cannot pass on masking alone.

Corroborating signals recorded per candidate:

| signal | what it proves | fired on |
|---|---|---:|
| `relocation_masked_byte_exact` | the shipped bytes ARE the pinned SDK object's bytes | 662 |
| `symbol_name_identity` | the naming waves independently landed on the upstream name | 192 |
| `assert_literal_source_path` | the literal pool carries the `__ASSERT`/log file string of the matched unit (e.g. `WEST_TOPDIR/zephyr/subsys/bluetooth/host/att.c`) | 86 |
| `sdk_unit_cluster` | ≥3 recovered functions map to the same upstream unit | most |
| `upstream_unit_already_linked` | the upstream object is *already* pulled into the current cohesive link, so the reconstruction is a duplicate body | 605 (+4 header inlines = 609) |
| `even_callers_present` | counter-risk: call sites outside the library closure must be redirected | 221 (225 candidates by field; 791 call sites total) |

**Control check.** No Even-specific function is in the candidate list: `main`,
`ble_process_put_req`, `master_display_thread`, `slave_display_thread`, `aging_mode_thread`,
`imu_fusion_thread`, `button_init`, `register_ipc_service_context`, `check_sw0_status`,
`pt_nfc_eeprom_link_start`, `spi_master_install_ops`, `flash_settings_read`, `get_lux_info`,
`fuel_gauge_update` all fail the gate. The one weak false positive that survived the gate
(`us_to_ticks_scaled_v2` ↔ `lsm6dso_accel_convert`, agreement 52/60) was pushed to `ambiguous`.

**Independent confirmation from the other direction.** Every retained app function whose literal
pool names an SDK `.c` path either byte-matched (114) or is already excluded by the manifest
(114) — the string signal and the byte signal agree completely. The 35 that carry an SDK path
literal but match nothing are handled in §6.

---

## 2. Counts

**666 candidates** (633 app, 33 net) across **163 upstream units**, representing
**87 498 bytes** of shipped firmware text. These are *in addition to* the 553 app and 244 net
exclusions already in `adoption_manifest.json`.

| confidence | n |
|---|---:|
| high | 507 |
| medium | 145 |
| low | 14 |

| kind (manifest `kind` vocabulary) | n |
|---|---:|
| `source` (owned by one upstream `.c`) | 525 |
| `archive` (newlib-nano / libgcc member) | 88 |
| `static_helper` (out-lined `static inline`, shared by several units) | 53 |

| component | high | medium | low | total | on golden boot path | pin/alias-bound |
|---|---:|---:|---:|---:|---:|---:|
| `zephyr_bt_host` | 180 | 33 | 4 | 217 | 45 | 32 |
| `libc_newlib_nano` | 71 | 17 | 0 | 88 | 22 | 11 |
| `zephyr_drivers` | 70 | 17 | 0 | 87 | 69 | 8 |
| `hal_nordic_nrfx` | 39 | 18 | 1 | 58 | 39 | 0 |
| `zephyr_kernel` | 40 | 2 | 3 | 45 | 39 | 13 |
| `nrf_subsys` | 18 | 9 | 0 | 27 | 5 | 2 |
| `zephyr_lib_os` | 16 | 9 | 0 | 25 | 21 | 11 |
| `zcbor` | 14 | 8 | 3 | 25 | 0 | 2 |
| `hal_st` | 15 | 2 | 0 | 17 | 15 | 0 |
| `zephyr_arch` | 9 | 5 | 0 | 14 | 11 | 0 |
| `zephyr_logging` | 7 | 6 | 0 | 13 | 8 | 3 |
| `other` (libmetal etc.) | 4 | 6 | 1 | 11 | 6 | 0 |
| `zephyr_ipc` | 6 | 2 | 0 | 8 | 5 | 1 |
| `zephyr_soc` | 7 | 0 | 0 | 7 | 7 | 1 |
| `zephyr_libc` | 3 | 3 | 0 | 6 | 4 | 0 |
| `zephyr_mcumgr` | 2 | 2 | 2 | 6 | 0 | 1 |
| `zephyr_settings` | 2 | 1 | 0 | 3 | 3 | 1 |
| `open_amp` | 1 | 2 | 0 | 3 | 1 | 1 |
| `zephyr_subsys` | 1 | 1 | 0 | 2 | 2 | 0 |
| `zephyr_net_buf` | 2 | 0 | 0 | 2 | 1 | 0 |
| `nrf_lib` | 0 | 1 | 0 | 1 | 0 | 0 |
| `mbedtls` | 0 | 1 | 0 | 1 | 1 | 0 |

Largest upstream units (app unless marked):

| core | upstream unit | n | high | on boot path | Even call sites | pin-bound | bytes |
|---|---|---:|---:|---:|---:|---:|---:|
| app | `zephyr/subsys/bluetooth/host/gatt.c` | 61 | 51 | 10 | 26 | 18 | 8024 |
| app | `zephyr/subsys/bluetooth/host/l2cap.c` | 33 | 24 | 0 | 1 | 3 | 4150 |
| app | `zephyr/subsys/bluetooth/host/att.c` | 30 | 24 | 0 | 31 | 1 | 4210 |
| app | `zephyr/subsys/bluetooth/host/smp.c` | 28 | 24 | 2 | 12 | 3 | 5196 |
| app | `zephyr/subsys/bluetooth/host/hci_core.c` | 25 | 22 | 13 | 9 | 5 | 3014 |
| app | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | 22 | 14 | 15 | 7 | 0 | 2184 |
| app | `zephyr/kernel/sched.c` | 21 | 21 | 17 | 41 | 5 | 2522 |
| app | `newlib-nano lib_a-mprec.o` | 18 | 17 | 0 | 0 | 0 | 2320 |
| app | `modules/lib/zcbor/src/zcbor_decode.c` | 18 | 8 | 0 | 7 | 1 | 1080 |
| app | `modules/hal/st/.../lsm6dso_reg.c` | 17 | 15 | 15 | 13 | 0 | 1276 |
| app | `nrf/subsys/bluetooth/gatt_dm.c` | 16 | 11 | 2 | 14 | 1 | 1532 |
| app | `zephyr/drivers/flash/nrf_qspi_nor.c` | 13 | 10 | 9 | 14 | 1 | 1426 |
| app | `zephyr/subsys/bluetooth/host/conn.c` | 12 | 12 | 1 | 11 | 1 | 2066 |
| app | `zephyr/subsys/bluetooth/host/id.c` | 11 | 9 | 7 | 3 | 1 | 1124 |
| app | `zephyr/drivers/timer/nrf_rtc_timer.c` | 9 | 9 | 9 | 0 | 1 | 648 |
| net | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` | 7 | 2 | 1 | 19 | 0 | 232 |

---

## 3. Boot-path value

* **304 candidates run on the golden trace** (`recon/emulator/reports/golden_boot_trace.json`,
  app core), **228 of them at `high` confidence**.
* **36 candidates already execute on our current iteration-5 trace**
  (`recon/emulator/reports/our_boot_trace_app.json`) — these are the ones whose displacement can
  change boot behaviour *immediately*, so they are the ones to watch in the no-regression gate:
  `serialization_register_endpoint`, `z_log_msg_runtime_create`, `region_init`, `sbrk_impl`,
  `g1_recon_retarget_lock_{acquire,release}_recursive`, `bt_gatt_service_init`, `smp_init`,
  `qspi_get_zephyr_ret_code`, `nrf_gpio_pin_port_decode`, `uarte_nrfx_configure`,
  `rtc_read_extended_cycle_count`, `compare_set`, `twim_configure`, `z_fatal_error`,
  `z_impl_k_sem_take`, `unready_thread`, `pend_locked`,
  `rtc_get_elapsed_cycles_since_baseline`, `next_timeout`, `k_uptime_ticks_impl`,
  the eight `zephyr/lib/os/heap.c` chunk helpers, `process_recheck`, `validate_args`,
  `notify_one`, `atomic_inc`, `atomic_or`, `pinctrl_apply_state`, `xfer_completeness_check`,
  `memcpy`, `memset_bytes`.
* 22 net candidates are on golden's net trace.

### 3a. The four highest-value items in the whole list

`zephyr/include/zephyr/drivers/gpio.h` out-lined static inlines — **exactly the bodies iteration 5
proved defective**:

| va | current symbol | upstream |
|---|---|---|
| `0x00017688` | `gpio_pin_configure_17688` | `gpio_pin_configure` (gpio.h inline) |
| `0x00017858` | `gpio_pin_configure` | `gpio_pin_configure` (gpio.h inline) |
| `0x000177c4` | `gpio_pin_get_raw_checked` | `gpio_pin_get_raw` (gpio.h inline) |
| `0x00017980` | `gpio_pin_get_checked` | `gpio_pin_get_raw` (gpio.h inline) |

Evidence is the `__ASSERT` file literal `WEST_TOPDIR/zephyr/include/zephyr/drivers/gpio.h` in
each literal pool — that assertion text exists **only** inside the gpio.h inline bodies, so these
out-lined functions *are* those inlines. There is no byte comparand (our pinned build inlines
them, so no `.text.<sym>` section exists), and there is no external symbol to bind to: displacing
means deleting the four reconstruction TUs and having the calling TU include
`<zephyr/drivers/gpio.h>` so the compiler re-inlines them. All four are on the boot path and all
four carry a known reconstruction defect. **Do these first.**

---

## 4. Recommended application order

Each batch is chosen so that the risky dimensions (symbol binding, Even call sites, boot-path
sensitivity) increase monotonically. Batch membership is derivable from the JSON:
`confidence == "high" && upstream_object_in_link && referenced_by_linker_artifact == [] &&
callers.even_owned == 0`, then split by component.

**Batch 0 — the four `gpio.h` inlines (4 functions, 512 B).**
Small, self-contained, on the boot path, and the only candidates with a *proven* defect. Doing
them first also validates the "re-inline from the header" mechanic that Batch 5 depends on.

**Batch 1 — leaf libc / lib-os / zcbor / arch primitives (52 functions, 8 186 B).**
`libc_newlib_nano` 25, `zcbor` 9, `zephyr_lib_os` 7, `zephyr_arch` 7, `zephyr_soc` 2,
`zephyr_libc` 2. No Even callers, no pin/alias references, upstream unit already linked. Pure
duplicate removal — the lowest-risk possible first move, and it exercises the whole verification
loop before anything with state does.

**Batch 2 — kernel / logging / settings / ipc / mcumgr leaves (31 functions, 4 510 B).**
`zephyr_kernel` 18, `zephyr_logging` 4, `zephyr_ipc` 3, `zephyr_mcumgr` 2, `zephyr_settings` 1,
libmetal 3. Still zero Even callers and zero pin references, but these touch scheduler/logging
state, so this is the first batch that can move the boot trace.

**Batch 3 — driver and nrfx clusters (71 functions, 8 520 B).**
`zephyr_drivers` 39, `hal_nordic_nrfx` 29, `hal_st` 3. 69 of the 87 `zephyr_drivers` candidates
are on the golden boot path, so this is where the boot-behaviour risk concentrates. Apply
**one upstream unit at a time** (`nrf_rtc_timer.c` → `regulator_npm1300.c` → `mfd_npm1300.c` →
`nrfx_spim.c` → `nrfx_twim.c` → `nrfx_gpiote.c` → `nrf_qspi_nor.c`) and re-trace between units.

**Batch 4 — `modules/hal/st/.../lsm6dso_reg.c` (17 functions, 1 276 B).**
Special case worth calling out: `lsm6dso_reg.c` is **already compiled into the app target**
(`recon/application/app/CMakeLists.txt` line 162), so all 17 recovered bodies —
`audio_codec_set_reg10_field2`, `read_6byte_id_words`, `settings_read_6byte_id28` … — are
duplicate copies of `lsm6dso_xl_full_scale_set`, `lsm6dso_angular_rate_raw_get`,
`lsm6dso_acceleration_raw_get` … that sit in the image twice under wrong names. Displacement here
is a *rename of 13 Even call sites* onto the real `lsm6dso_*` API, which also fixes 17 badly
misleading recovered names.

**Batch 5 — out-lined `static_helper` set (53 functions).**
`atomic_and/or/set_bit/test_bit`, `bt_addr_le_copy`, `sys_slist_*`, `net_buf_frags_len`,
`pinctrl_apply_state`, `i2c_write_dt`, … Each is a header `static inline` that GCC out-lined; the
recovered corpus has up to six copies of the same helper under `_0`/`_1`/`_2` suffixes. There is
no external symbol to bind, so every caller must switch to the owning header in the same batch.
High value (removes the `_N` duplicate-name family entirely) but it is a source edit, not a
manifest exclusion.

**Batch 6 — Bluetooth host (217 candidates, ~28 KB).**
Last, and only unit-by-unit. Reasons: 32 of them are referenced by linker artifacts, they carry
99 Even call sites, and the whole BT set was originally validated only against the dedicated
configuration in `tools/build_app_bluetooth_stock_adoption.py`
(`/private/tmp/g1-bt-custom-notls-main16k-evidence`), not against the default cohesive build.
Order within the batch: `l2cap.c` (1 Even caller) → `id.c` → `adv.c` → `conn.c` → `hci_core.c` →
`smp.c` → `att.c` (31 Even callers) → `gatt.c` (26 Even callers, 18 pin-bound).

**Net core — 33 candidates, apply last of all.** See the FLASH risk in §7.

---

## 5. Findings that contradict existing decisions

**Eight candidates conflict with a `retain_reconstruction` row already in
`adoption_manifest.json`.** Those rows were written from *scored* heuristics
(`opcode_score_below_threshold`, `instruction_length_score_below_threshold`); a direct
relocation-masked byte comparison over the full upstream section passes for all eight:

| va | current symbol | upstream symbol | upstream unit |
|---|---|---|---|
| `0x0004d490` | `z_log_dropped_read_and_clear_0` | `z_log_dropped_read_and_clear` | `zephyr/subsys/logging/log_core.c` |
| `0x0004d678` | `g1_recon_z_impl_log_panic` | `z_impl_log_panic` | `zephyr/subsys/logging/log_core.c` |
| `0x0004def8` | `g1_recon_log_backend_uart_panic` | `panic` | `zephyr/subsys/logging/backends/log_backend_uart.c` |
| `0x000510fc` | `g1_recon_retarget_lock_acquire_recursive` | `__retarget_lock_acquire_recursive` | `zephyr/lib/libc/newlib/libc-hooks.c` |
| `0x00051134` | `g1_recon_retarget_lock_release_recursive` | `__retarget_lock_release_recursive` | `zephyr/lib/libc/newlib/libc-hooks.c` |
| `0x00065940` | `g1_recon_nrfx_gpiote_init` | `nrfx_gpiote_init` | `modules/hal/nordic/nrfx/drivers/src/nrfx_gpiote.c` |
| `0x00067e8c` | `g1_recon_nrfx_wdt_channel_alloc` | `nrfx_wdt_channel_alloc` | `modules/hal/nordic/nrfx/drivers/src/nrfx_wdt.c` |
| `0x00072908` | `z_impl_k_sem_take` | `z_impl_k_sem_take` | `zephyr/kernel/sem.c` |

`z_impl_k_sem_take` deserves its own note. `recon/application/app/CMakeLists.txt` currently
renames the *SDK* body out of the way
(`z_impl_k_sem_take=g1_displaced_sdk_z_impl_k_sem_take`) because "the pinned Zephyr sem.c body
fails the instruction/shape ownership gates". The shipped 202-byte body is **byte-identical
(relocation-masked, full 244-byte section) to that very SDK body**, and it is on our current boot
trace. If the comparison is accepted, the rename hack can go away and `sem.c` can own the symbol
outright. Do not act on this without re-reviewing the original receipt — it is flagged
`conflicts_with_manifest_retain_row: true` in the JSON, not silently adopted.

Two other hygiene observations (not acted on): several `current_symbol` values in
`adoption_manifest.json` are stale relative to `recon/catalogs/function_names_app.json` after the
563-function rename wave (e.g. `0x0004d678` is recorded as `log_init` but is now
`g1_recon_z_impl_log_panic`; `0x00067e8c` is recorded as `nrfx_dppi_channel_alloc` but is now
`g1_recon_nrfx_wdt_channel_alloc`). Identity is by VA, so this is cosmetic, but it makes the
manifest hard to read.

---

## 6. `keep_reconstructed` — stock-shaped but NOT stock (27 functions)

These are the dangerous ones: they look like library code and would be wrongly displaced by a
name- or shape-based rule. Full records with evidence are in the `keep_reconstructed` array.

**(a) Even's own code wearing Zephyr assert macros — 3.** The literal pool names *Even's own
source tree*, which is decisive counter-evidence and also reveals the original layout:

| va | symbol | literal |
|---|---|---|
| `0x00033384` | `uart_callback` | `../src/production_test/serial_port.c` |
| `0x000332dc` | `init_serial_port` | `../src/production_test/serial_thread.c` |
| `0x00026418` | `spi_master_init` | `../src/spim_spis/spim.c` |

**(b) Stock unit literal, no byte match anywhere — 20.** Each carries the `__ASSERT`/log file
string of a real SDK unit, yet nothing in the 5 996-symbol pinned index is byte-identical, while
*siblings from the same unit do match*. That makes them either an Even modification of the
upstream body or a configuration variant our pinned build does not reproduce. **Both readings
require keeping the reconstruction** until the owning unit is rebuilt under the recovered Kconfig
and re-compared.

| unit | functions |
|---|---|
| `zephyr/subsys/bluetooth/host/conn.c` | `bt_conn_notify_connected`, `ble_notify_disconnected`, `ble_notify_le_param_updated`, `ble_notify_identity_resolved`, `ble_notify_remote_info_available`, `ble_conn_ref`, `ble_conn_unref`, `ble_conn_process_complete_or_disconnect` |
| `zephyr/subsys/bluetooth/host/gatt.c` | `gatt_register_service_200028b8` |
| `zephyr/drivers/serial/uart_nrfx_uarte.c` | `uarte_nrfx_pm_action`, `uarte_nrfx_tx_start` |
| `zephyr/kernel/mempool.c` | `resource_pool_aligned_alloc`, `malloc_impl` |
| `zephyr/lib/os/heap.c` | `g1_recon_k_heap_init` |
| `modules/lib/open-amp/.../rpmsg_virtio.c` | `rpmsg_virtio_tx_enqueue`, `rpmsg_virtio_rx_notify` |
| `nrf/subsys/app_event_manager`, `nrf/subsys/caf/*` | `app_event_alloc`, `module_state_event_log_handler`, `power_manager_restrict_event_log`, `power_manager_system_off` |

The `conn.c` cluster is the most suspicious: eight `bt_conn_*` notify/ref helpers from a unit
whose other twelve functions match byte-for-byte. That is the shape of a deliberate Even
modification to the connection-callback path, and it is precisely why a blanket
"displace everything named `bt_*`" rule would be wrong.

**(c) Manifest retentions the byte sweep independently confirms — 4.**
`g1_recon_z_log_msg_free`, `z_log_msg_pending` (`0x0004d588`), `crc16_reflect` (`0x0007d9c0`),
`bt_conn_set_security` (`0x0008149a`). No relocation-masked match exists for any of them; the
existing retention holds.

**(d) One partial-agreement case worth naming.** `att_timeout` (`0x00059920`) agrees with
`att.c`'s `att_timeout` for 156 of its 158 bytes and then diverges — a genuine tail difference in
a function otherwise from a fully-matching unit. It sits in `ambiguous`, not in the candidates.

---

## 7. Risks

1. **87 candidates are referenced by a build artifact** (`referenced_by_linker_artifact` in the
   JSON): `app_address_taken_roots.cmake` 33, `g1_app_symbols.h` 32,
   `g1_app_function_aliases.ld` 16, `g1_app_veneer_aliases.ld` 7, `g1_app_aliases.ld` 7,
   `g1_net_readable_aliases.ld` 7, `g1_app_globals.ld` 4, `g1_app_readable_aliases.ld` 3,
   `g1_app_public_sdk_aliases.ld` 1. The 33 `app_address_taken_roots.cmake` entries are the worst
   case: the recovered identity is stored in a shipped callback/config table, so the recon
   definition is currently a GC root. Most of their upstream owners are **translation-unit-local**
   — the same constraint that made 28 of the 83 code-pointer pins "BLOCKED (SDK-static)" in the
   iteration-3 sweep. Displacing those needs the artifact updated (or the reference dropped) in
   the same batch, not afterwards.
2. **225 candidates have at least one Even call site (791 call sites in total).** Displacing a TU-local or header-inline
   owner leaves those references undefined unless the caller is converted to the upstream symbol
   or to the owning header in the same commit. `zephyr/kernel/sem.c` (45 Even call sites),
   `zephyr/kernel/sched.c` (41), `zephyr/subsys/bluetooth/host/att.c` (31),
   `zephyr/kernel/mutex.c` (29) and `gatt.c` (26) are the concentrations.
3. **FLASH growth. Recovered code is leaner than the SDK.** Commit `b83dab8e` already recorded
   the net core physically linking with 0 undefined / 0 duplicate but **overflowing FLASH by
   633 B**, "a genuine recovered↔SDK duplication residual (original image fits with 1696 B spare;
   ours is ~2.3 KB larger from linking lean recovered code alongside SDK archives)". Displacement
   *pulls more SDK members in*, so it can make that worse before the duplication-elimination
   endgame makes it better. Concretely: 609 of the 666 candidates target objects that are
   *already* in the link, so removing those reconstructions should be net-negative on size;
   the 57 whose upstream object is **not** currently linked (notably
   `newlib-nano lib_a-dtoa.o` 3 308 B and `lib_a-nano-vfprintf_float.o` 1 422 B) will pull new
   members in. **Apply the net-core batch last and measure FLASH after every batch.**
4. **Configuration variance is the main source of false confidence.** A byte match proves the
   shipped bytes equal *our current build's* object for that unit. Where our Kconfig differs from
   the recovered one, the match simply will not occur — which is safe — but the converse trap is
   real for the Bluetooth host, whose stock evidence was gathered under a *different*
   configuration (`tools/build_app_bluetooth_stock_adoption.py`). Treat BT `medium` rows as
   unresolved until re-matched under the cohesive build's own config.
5. **`static_helper` displacement is a source edit, not a manifest exclusion.** The 53
   out-lined-inline candidates (and the 4 `gpio.h` ones) have no external symbol. An
   `exclude_reconstruction` row alone would produce undefined references.
6. **`rodata_87c08` precedent.** Iteration 5 reverted a *correct* `ipc0` device-pin rebind because
   it regressed the boot (the app blocked on the rpmsg endpoint bind). A correct displacement can
   likewise regress the trace by making previously-dead code live. The no-regression gate is
   about behaviour, not correctness — record the measurement and the re-apply condition rather
   than silently reverting, exactly as `g1_app_globals.ld` does today.

---

## 8. What must be re-verified after **every** batch

1. **Clean link.** `recon/application/build_cohesive.sh app <outdir>` → exit 0;
   `nm -u` on the final `zephyr.elf` = **0 undefined**; **0 duplicate global definitions**; no
   `--allow-multiple-definition`, no weak definition, no numeric linker root introduced.
   Repeat for `net`.
2. **Symbol-ownership diff.** `readelf -sW` before/after: every displaced VA's symbol must now
   resolve into the upstream object (check the `.map`), and no previously-resolved reference may
   have become a `PROVIDE`d absolute.
3. **FLASH/RAM delta recorded** for both cores against the previous batch (app baseline
   iteration 5: FLASH 626 680 / 982 528 B = 63.78 %, RAM 75 573 B = 16.77 %; net baseline: 633 B
   over budget). Any batch that grows FLASH must say which upstream members it newly pulled in.
4. **Boot no-regression vs the current trace.** Re-run the unmodified `armemul/g1-ours.resc`
   through an additive `$app_elf`/`$net_elf` override with the same 0.15 s budget, 10 µs quantum
   and seeded RNG, then diff `first_i` per function against
   `recon/emulator/reports/our_boot_trace_app.json` / `our_boot_trace_net.json`. Gate:
   * the iteration-5 prefix markers stay instruction-identical —
     `region_init` 80 111, `nrf_cc3xx_platform_init` 83 071, `z_impl_k_thread_create` 613 974,
     `main` 4 667 207, `ipc_service_open_instance` 4 668 358,
     `register_ipc_service_context` 4 701 823, `spi_master_install_ops` 4 701 955,
     `button_init` 4 701 966;
   * app unique functions ≥ 601 and instructions ≥ 5 067 675;
   * `grep -iE "abort|fault|halted|SYSRESETREQ"` on the app core stays **empty** (iteration 5 was
     the first fault-free run — that property must not be lost);
   * the run still ends alive and idling, not in `z_arm_fatal_error`.
5. **Per-function re-verification is NOT required and NOT meaningful for a displaced function** —
   `tools/cfg_verify` proves the *reconstruction* against the original address, and a displaced
   function no longer has a reconstruction. What replaces it is the byte evidence in the JSON
   plus items 1–4. Conversely, **do not delete a reconstruction from `recon/app/src` /
   `recon/net/src`**: the canonical proven bodies stay as evidence; displacement is expressed as
   an `exclude_reconstruction` row (or, for `static_helper`, a build-shell source edit).
6. **If a batch regresses the trace**, revert that batch only, and record the measurement and the
   re-apply condition next to the row — the iteration-5 `rodata_87c08` pattern.

---

## 9. Regenerate

The analysis is reproducible from committed inputs plus the pinned SDK and the iteration-5 build:

```sh
# inputs
#   app_update.bin, netcore_image.bin
#   recon/catalogs/{app,net}_funcs.json.gz, function_names_{app,net}.json,
#                  refgraph_{app,net}.json.gz
#   recon/generated/{app,net}_retained_sources.cmake
#   recon/ownership/adoption_manifest.json
#   recon/emulator/reports/golden_boot_trace.json, our_boot_trace_{app,net}.json
#   /private/tmp/g1-i5d-app  (iteration-5 cohesive build: objects, archives, zephyr_final.map)
#   ~/ncs251 + ~/ncs251/refapp/build + ~/ncs251/netref_build + ~/ncs251/nrfxlib
#   ~/zephyr-sdk-0.16.5-1/arm-zephyr-eabi (libgcc / libc_nano / libm_nano multilib)
recon/application/build_cohesive.sh app /private/tmp/g1-i5d-app   # if the build is gone
```

Method, in one line: index every `.text.<sym>` section of every pinned-SDK object and archive
member, compare it against the shipped image at each catalogued function VA with all relocation
windows zeroed, keep only full-section agreements, and score by the bytes that no relocation
covers.
