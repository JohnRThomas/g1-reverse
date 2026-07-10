# analytics — RTOS wiring & owned state

Source of truth: proven bodies in `recon/named/*.c` and `recon/verified/src/*.c`
for the 18 functions grouped into `analytics`
(`topic_groups.json["analytics"]`). Addresses are app-core flash offsets
(link base 0xC200).

## RTOS objects DEFINED by this module

**None.**

The analytics module creates no Zephyr kernel objects. Every proven body in the
group was inspected for `k_thread_create` / `K_THREAD_DEFINE`,
`k_msgq_init` / `K_MSGQ_DEFINE`, `k_sem_init`, `k_mutex_init`, `k_timer_init`,
`k_work_init`, and `k_queue_init` — there are **zero** such calls.

The module has no thread of its own: all of its functions run in the caller's
context. The two "init" functions it exposes only load persisted state and reset
plain counters; they do not spin up any RTOS primitive:

- `init_analytics_settings` @0x7c360 (`FUN_0007c360`) — calls
  `load_sys_setting` → `load_usr_setting` → `load_burial_point`, then on success
  `reset_countdown_timer_default(*(device_info+0xff0))`. The
  "timer" it resets is a **software byte counter**, not a `k_timer`: 
  `reset_countdown_timer_default` @0x7d1b8 (`FUN_0007d1b8`) merely writes 5 bytes
  (`buf[0]=0x3c; buf[1..4]=0`) into a struct field — no `k_timer_init`.

The RTC/entropy helpers pulled into this topic group by call-graph proximity are
**pure readers of hardware/kernel state owned elsewhere**, and likewise define
nothing:

- `rtc_read_extended_cycle_count` @0x63610 / `rtc_get_elapsed_cycles_since_baseline`
  @0x74b68 — read the nRF RTC counter register `0x50015504` and the
  overflow-tracking globals; no object created.
- `entropy_get_entropy_isr_call` @0x52bf8 / `sys_rand32_get` @0x52c40 — call
  through the entropy driver's function-pointer table at `0x00087b90`; no object
  created.
- `sys_clock_cycle_get_32` @0x84c76 — thin wrapper over `rtc_read_extended_cycle_count`.

## Data / flash-backed state this module OWNS

The module is **state-, not object-, centric**: it owns the "burial point" (埋点,
usage-telemetry) counters and their flash backing. All live state is carved out
of the shared `device_info_t` instance (base pointer = `get_device_info()` /
`FUN_000167a8`, param named `param_1` in the loaders), plus two flash records.

### Flash records (persisted backing store)

| Flash addr | Size | Read by | Purpose |
|---|---|---|---|
| `0x00130000` | 0x84 B | `load_sys_setting` @0x22bd0 | System-settings record → scattered into `device_info_t` config fields |
| `0x00135000` | 0xC0 B | `load_burial_point` @0x230e0 | Burial-point counter blob → `device_info_t+0x10c6` |

`load_burial_point` (@0x230e0) reads 0xC0 bytes from `0x135000` into
`device_info+0x10c6`; if the record is blank (`*(base+0xda)==-1` or
`*(base+0xdc)==0`, base = `param+0x1000`) it re-seeds: `memset` 0xBC bytes at
`base+0xca`, stamps a `sys_rand32_get()` id at `base+0xc6`, sets `base+0xda=7`,
`base+0xdc=1`. The sister **writer** `update_burial_point_to_flash` lives in
`flash_store`, not here.

### In-RAM burial-point region (inside `device_info_t`)

Owned/mutated exclusively by this module's event hooks. Offsets are from the
`device_info_t` base:

| Offset | Field | Written by |
|---|---|---|
| `+0x10ac` | wear-active flag (1 = worn) | `enter_wear_burial_point` @0x4a890 |
| `+0x10ad` | current burial-point type (0..6) | `enter_wear_burial_point` |
| `+0x10ae` / `+0x10b2` | wear-start timestamp (lo/hi of `k_uptime_get_10`) | `enter_wear_burial_point` |
| `+0x10ce` | total wear-event counter | `enter_wear_burial_point` (`++`) |
| `+0x10e6 + type*0xc` | per-type event counter | `enter_wear_burial_point` (`++`) |
| `+0x10c6 .. +0x1186` | flash-backed blob (0xC0 B) incl. seed id `+0xc6`, epoch `+0xda`, valid flag `+0xdc` (offsets rel. `param+0x1000`) | `load_burial_point` @0x230e0 |
| `+0xff0` | countdown-timer software struct (5-byte counter) | reset via `init_analytics_settings` → `reset_countdown_timer_default` |

`update_burial_point_day_index` @0x4a5b0 buckets events by day: it reads
`get_system_unix_time` (@0x7d216, itself `*(device_info+0xfec)`), converts via
`unix_timestamp_to_datetime` (@0x4a1b8), and gates roll-over on year `< 0x7e9`
(2025) / month check — it validates the day cursor rather than owning a distinct
global.

### RAM globals touched (owned by other modules, listed for completeness)

- `0x2000230c` g_log_level, `0x20007554` g_log_use_alt_sink — logging gate only.
- `0x20002fe3` g_product_code_buf, `0x20003003` — populated by `load_sys_setting`
  from the settings record (device-identity fields; owned by `system`/device_info).
- `0x2000a0b4` (5-slot uptime ring), `0x2001d449`/`0x2001d44a` (ring cursor +
  init flag), `0x50005114` — touched only by `cpu_idle_wfi_gate_check` @0x4c1f0,
  a dedup/idle helper grouped here by call proximity; not part of the burial-point
  data model.
- `0x2000b2dc`, `0x200066b8/bc`, `0x2000b494`, RTC reg `0x50015504` — RTC
  overflow bookkeeping, owned by the clock/RTC module; only read here.

## Summary

- **RTOS objects defined: none.** No threads, message queues, semaphores,
  mutexes, timers, work items, or queues are created by any analytics function.
  The module runs entirely in its callers' contexts.
- **Owned state:** the burial-point usage-telemetry counters, held in the
  `device_info_t+0x10ac..+0x1186` sub-region and persisted to flash record
  `0x135000` (0xC0 B); plus the system-settings load path from flash record
  `0x130000` (0x84 B). The flash *writer* and the BLE upload path live in
  `flash_store` and `ble_proto` respectively.
