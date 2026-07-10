# battery — fuel gauge, charge state, critical/shutdown, ambient light

## Responsibility
Tracks the pack state-of-charge from the fuel gauge, reads the charging-case
("glass box") status/percent, maintains the low-power / critical-shutdown flag,
loads and persists the user power settings, and owns the OPT3007 ambient-light
sensor whose lux reading drives display auto-brightness. SoC is written into the
shared `device_info` block, reported to the phone (BLE), and mirrored to the
slave lens (ESB).

The reference-graph unit also groups a set of **battery-gated peer BLE-link /
GATT helpers** with this module. They are not battery-core; they are here only
because each one calls `is_battery_critical()` as a precondition before using
the radio. They are kept in a separate section throughout.

## Flow
```
fuel gauge (I2C) ─> fuel_gauge_update ─> device_info SoC ─> send_event_status (BLE)
                                                          └─> sync_to_slave (ESB)
charger/case ─> get_glassbox_charge_status / get_glassbox_charge_percent
                                                          └─> ble_encode_charge_status_report

critical flag @0x20019ef3:
   set_battery_critical_flag (FUN_00032ef0) ── writes ──┐
   load_usr_setting ────────────────────────────────────┤
                                                         ▼
   is_battery_critical (read) ─> check_battery_critical ─> set_shutdown_flag ─> power off
                                 (spin-guard @0x20018d9c)

OPT3007 (I2C):
   opt3007_chip_init ─> opt3007_read_lux_raw ─> get_lux_info / opt3007_get_max_lux
                                                          └─> display auto-brightness
   opt3007_chip_deinit  (called from panel_off path)
```

## Key functions (name — role)
Battery / charge core:
- `fuel_gauge_update` (0x10b18) — poll the gauge, update SoC, emit BLE status,
  sync to slave. Driven by other modules' poll functions (see Entry points).
- `get_glassbox_charge_status` (0x32784) / `get_glassbox_charge_percent`
  (0x327c4) — charging-case charge state and its battery percent.
- `check_battery_critical` (0x2bed0) — spin-wait guard on 0x20018d9c, returns
  `device_info+0xd5 > 1` (work-mode / low-power gate for shutdown).
- `is_battery_critical` (0x32ee4) — read the critical flag byte @0x20019ef3.
- `set_battery_critical_flag` (FUN_00032ef0, 0x32ef0) — write that same flag
  byte (the setter for is_battery_critical), with debug log.
- `set_shutdown_flag` (0x7cbfe) — run the critical guard, clear pending
  task/ESB state, optionally emit a status event, drop to idle.
- `load_usr_setting` (0x22e78) — load user power/behaviour settings from flash.
- `usr_setting_write_flash` (FUN_0007c28e, 0x7c28e) — persist the 0x20-byte
  settings block to flash @0x134000.
- `get_product_code_buf` (FUN_000232b8, 0x232b8) — accessor returning
  `&g_product_code_buf` (0x20002fe3).
- `ble_encode_charge_status_report` (FUN_00021334, 0x21334) — build a 0xc9xx
  BLE report packet (opcodes 0x9..0x12, 0xf0..0xf2) including charge-box
  status/percent, then dispatch via the ctx vtable.

OPT3007 ambient-light sensor:
- `opt3007_chip_init` (0x2e67c) / `opt3007_chip_deinit` (0x2e8b4) — bring the
  OPT3007 up/down over I2C (verifies mfg id 0x5449, device id 0x3001).
- `opt3007_read_lux_raw` (FUN_0002e648, 0x2e648) — I2C register read +
  `(mantissa & 0xfff) << exponent` lux conversion.
- `get_lux_info` (0x10fc8) — current lux + valid flag.
- `opt3007_get_max_lux` (0x10a68) — peak-lux / luminance-curve math mapping
  ambient light to a panel brightness level (uses float helpers).

Battery-gated peer BLE-link / GATT helpers (topic-adjacent, not battery-core):
- `peer_device_info_refresh` (FUN_00018730) — snapshot device-info record and,
  when not battery-critical, refresh the cached peer/bond info (+0x1069 block).
- `peer_gatt_subscribe_start` (FUN_000187e8) — kick GATT service discovery /
  CCC-subscribe on the peer lens when connected (state==2) and not critical.
- `gatt_discovery_complete_cb` (FUN_000188d8) / `gatt_discovery_not_found_cb`
  (FUN_000189a0) — GATT Discovery Manager callbacks that walk attributes
  (FUN_0004ee68) and subscribe/write CCC (FUN_0004f040/0f0ec/0f418).
- `gatt_dm_cb_a/b/c/d` (FUN_00018894/188b0/18978/18a1c) — thin logging wrappers
  around `peer_gatt_subscribe_start`.
- `lookup_known_device` (FUN_00059c70) — scan `g_known_device_table`
  (0x2000af18, 3 x 0x10 entries) for a peer conn/addr match.

## Owned data / structs
- `device_info` fields: SoC (`+0xd5` work-mode/level, `+0x1069` device-info
  block), consumed by display (brightness) and system power logic.
- Critical/low-power flag byte @ **0x20019ef3** (set by FUN_00032ef0, read by
  is_battery_critical). Spin-guard byte @ **0x20018d9c**.
- `g_product_code_buf` @ 0x20002fe3.
- OPT3007 I2C context; sensor "present" flag @ **0x20018da1**; config regs at
  0x20007b6c / 0x2000230c.
- `g_known_device_table` @ 0x2000af18 (3 x 0x10) — peer/bond records.
- Fuel-gauge sample counters @ 0x20007514, 0x20006ab8+0x367, flag @ 0x20006ab4.
- `n_owned_data = 267` data objects attributed to the unit by the graph.

## Entry points
The module owns no threads. Its entry points are called by other modules' RTOS
threads / callbacks:
- `fuel_gauge_update` — polled by `FUN_0002685c`, `FUN_00026c8c`,
  `FUN_0002a8d8` (system/power poll paths).
- `is_battery_critical` — read by ~20 callers (handle_attitude_trigger,
  ble_process_put_req, sync_to_slave, display threads, key_event_thread, …).
- `check_battery_critical` / `set_shutdown_flag` — called by `check_work_mode`,
  `slave_display_thread`, `display_dispatch_thread`, `key_event_thread`,
  `ble_process_put_req`, `handle_attitude_trigger`.
- `opt3007_chip_init` / `opt3007_chip_deinit` — from the display panel power
  path (FUN_00046dd8 / FUN_00046d2c, i.e. panel_on / panel_off).
- `load_usr_setting` — from `FUN_0007c360` (settings/boot).
- `FUN_0002ea28` (opt3007 sample handler) — from `FUN_00016eb8`.

## Notes
`is_battery_critical`/`set_battery_critical_flag` share flag byte 0x20019ef3 —
that get/set pairing was the key deduction linking FUN_00032ef0 to the module.
The 0x188xx GATT family and FUN_00059c70/0x54/0x5c helpers are BLE-link code
gated by battery state, not gauge logic; treat them as adjacent, not core.
