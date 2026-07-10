# analytics — Usage telemetry ("burial point")

**Role.** Records aggregated usage counters into the `buried_point_data[192]`
region of `device_info_t`, rolls them by day, persists them to flash, and hands
the blob to the phone on request. "Burial point" (埋点) is the vendor's term for
in-app analytics events.

## Key functions
- `enter_wear_burial_point()` — increments the wear/usage counter when the
  glasses are put on.
- `update_burial_point_day_index(...)` — advances the per-day counter slot so
  events are bucketed by day.
- `load_burial_point(dst, ...)` — restores the counter blob from flash at boot
  (`burial_point read error!`).
- `load_sys_setting(dst)` — companion boot-time settings load.

Related (owned by other modules):
- `update_burial_point_to_flash` (in `flash_store`) — the writer that persists
  the blob (`update_burial_point_to_flash!!!`).
- BLE upload path `BLE_GET_BURIAL_POINT_DATA` (in `ble_proto`) — sends the blob
  to the phone.

## State it owns / structs
- `device_info_t.buried_point_data[192]` — the in-RAM counter array (per-day
  buckets, per-event counters).
- Day-index cursor used by `update_burial_point_day_index`.

## Entry points
- **Event hooks:** `enter_wear_burial_point` and the day-index update are called
  from the wear-detection / work-mode paths in `system`.
- **Boot restore:** `load_burial_point` / `load_sys_setting`.

## Cross-module coupling
- Persistence via `flash_store` (`update_burial_point_to_flash`,
  `load_burial_point`).
- Upload via `ble_proto` GET handler.
- Trigger source is `system` (wear/work-mode events).
