# battery — RTOS wiring

## Summary
**The battery module defines NO RTOS objects.**

No `K_THREAD_DEFINE`, `K_MSGQ_DEFINE`, `K_SEM_DEFINE`, `k_thread_create`,
`k_msgq_init`, `k_sem_init`, `k_mutex_init`, `k_work_init`, or `k_timer_init`
appears in any of the 45 proven bodies of the graph's `battery` unit. Verified by
scanning every reconstructed source file for the unit's functions in
`recon/verified/` and `recon/named/` (fuel_gauge_update, load_usr_setting,
opt3007_chip_init/deinit, set_shutdown_flag, check_battery_critical, and the
0x188xx / 0x4exxx / 0x7fxxx helpers): zero matches.

The module is a **passive, polled library**. Its work is driven entirely by
threads owned by other modules; it synchronizes only through shared globals and,
indirectly, two `k_*` thunks it does not define.

## What it uses but does not define
- `FUN_000330c4` -> `FUN_0007c8b0` -> `thunk_FUN_000723b8`, and
  `FUN_000330d8` -> `FUN_0007c8c4` -> `thunk_FUN_00072558`.
  These are thin thunks into a shared kernel primitive (likely a
  mutex/semaphore lock+unlock pair) that lives in another module. The battery
  code only *calls* them; the object is defined elsewhere. Cite:
  `recon/named/FUN_0005420c.c` neighbourhood and refgraph edges
  0x330c4->0x7c8b0->0x723b8, 0x330d8->0x7c8c4->0x72558.
- `send_event_status` (BLE report) and `sync_to_slave` (ESB mirror) are invoked
  from `fuel_gauge_update` (0x10b18) and `set_shutdown_flag` (0x7cbfe) — both
  are queue/transport entry points defined by the ble / esb modules.

## Driving threads (external — the wiring INPUT this module feeds)
These are the RTOS contexts that call into battery; document them when
reconstructing the owners' wiring:

| battery entry (addr)            | called by (thread / callback)                              |
|---------------------------------|------------------------------------------------------------|
| fuel_gauge_update (0x10b18)     | FUN_0002685c, FUN_00026c8c, FUN_0002a8d8 (system power poll)|
| check_battery_critical (0x2bed0)| check_work_mode, slave_display_thread, display_dispatch_thread, FUN_0007cce8, FUN_0007cdb6 |
| set_shutdown_flag (0x7cbfe)     | handle_attitude_trigger, ble_process_put_req, check_work_mode, slave_display_thread, key_event_thread, FUN_00017f70, FUN_00019ed4, FUN_00023844, FUN_0002a8d8 |
| is_battery_critical (0x32ee4)   | ~20 readers (handle_attitude_trigger, ble_process_put_req, sync_to_slave, display + key threads, …) |
| opt3007_chip_init (0x2e67c)     | FUN_00046dd8 (panel_on power path)                          |
| opt3007_chip_deinit (0x2e8b4)   | FUN_00046d2c (panel_off power path)                         |
| load_usr_setting (0x22e78)      | FUN_0007c360 (settings/boot)                               |
| FUN_0002ea28 (opt3007 sample)   | FUN_00016eb8                                                |

## Shared-state synchronization (in lieu of RTOS objects)
- Critical/low-power flag byte @ **0x20019ef3** — set by `set_battery_critical_flag`
  (FUN_00032ef0, 0x32ef0) and `load_usr_setting`; read by `is_battery_critical`
  (0x32ee4). Cited bodies: `recon/verified/src_sym/FUN_00032ef0.c`,
  `recon/verified/src_sym/is_battery_critical.c`.
- Busy/spin guard byte @ **0x20018d9c** — `check_battery_critical` (0x2bed0)
  spins on it calling `FUN_0007cdf8` until clear. Cite:
  `recon/verified/src_sym/check_battery_critical.c`.
- Atomic bit flags @ **0x20006ab4** (subscribe-in-progress) manipulated via
  `atomic_test_and_set_bit` in the GATT helpers (FUN_0004f040, 0x4f040). Cite:
  `recon/named/FUN_0004f040.c`.
- OPT3007 present flag @ **0x20018da1**; fuel-gauge counters @ 0x20007514,
  0x20006ab8+0x367.

## Conclusion for wiring reconstruction
Attribute no thread/msgq/sem/mutex/work/timer to `battery`. When wiring is
assembled, list battery only as a **consumer** driven by the power-poll,
display-panel, key-event, and BLE-dispatch threads above.
