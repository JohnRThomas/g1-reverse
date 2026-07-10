# dashboard — home HUD screen & startup-mode config

## Responsibility
The dashboard is the glasses' default heads-up display: clock, date, and one
configurable widget slot (default view / stocks / news). This module owns:
- the dashboard screen render routine (`ui_DashBoard_task`), driven by the
  **display thread** (not its own thread);
- the gesture / BLE entry action (`handle_dashboard_action`);
- the persisted **startup-mode** config (which widget + index) — saved to flash
  and mirrored to the slave (right) lens over ESB;
- a **dwell timer** and per-day **usage analytics** (burial points).

It renders through the `gui_*` canvas API and is opened via the `display`
screen state machine. Config traffic arrives over the app BLE protocol and is
persisted through the shared flash-store command queue.

## Flow
```
touch double-click / BLE cmd ─▶ handle_dashboard_action ─▶ sets widget selector (0x2001b815)
BLE "set startup mode" ────────▶ upgradeDashboardStartupModeInfoToFlash ─▶ k_msgq_put(flash_store_cmd)
                                        └▶ SendDashBoardStartupModeInfoToSlave ─▶ k_msgq_put(dashboard_response) ─▶ ESB ─▶ slave
boot ─▶ init_dashboard_info ─▶ FUN_00016658 (restore snapshot 0x2007fc00 → device_info) / defaults
display thread ─▶ ui_DashBoard_task(action) ─▶ DashBoard_Reflash + gui canvas ─▶ reflash_fb_data_to_lcd
                                        ├▶ enter_/exit_dashboard_burial_point (dwell analytics)
                                        └▶ SendPowerInfoToSlave / send_dashboard_status_sync
```
Debug strings confirm the mechanics ("dashboard double click startup command",
"startup mode = %d", "DashBoard_Reflash", dashboard lock timeout).

## Key functions (name — role)
- `ui_DashBoard_task` — dashboard screen render/update; composes the HUD from
  `g_dashboard_widget_state` + widget indices, runs the 4-pass framebuffer blend
  loop, reflashes the LCD, and drives dwell analytics. **Screen callback of the
  display thread**, dispatched on `action` (0/1 reflash, 2 exit, 4 switch widget,
  6/7 flag toggles).
- `handle_dashboard_action` — gesture/BLE action sink; writes the widget selector
  to `g_dashboard_widget_state[3]` and `g_stocks_widget_index_raw` (0x2001b815).
- `init_dashboard_info` — boot init: restores persisted state (via `FUN_00016658`)
  or applies defaults, then loads 4 quicknote records from flash.
- `upgradeDashboardStartupModeInfoToFlash` / `getDashboardStartUpModeInfofromFlash`
  / `cleanDashBoardStartUpModeInfo` — persist / load / reset the startup-mode
  config; persist & reset push a command onto the shared flash-store queue.
- `SendDashBoardStartupModeInfoToSlave` — mirror startup mode to the slave lens
  via the dashboard response queue (ESB).
- `SendDashboardLockInfoToApp` — report dashboard lock state to the phone.
- `get_dashboard_sum_time` / `enter_dashboard_burial_point` /
  `exit_dashboard_burial_point` — dwell-time accounting + usage analytics.

### Deduced FUN_ purposes
- `FUN_0001672c` — setter: writes one byte into the dashboard config snapshot
  mirror at `0x2007fc69` (persisted startup default selector). **[public api]**
- `FUN_00037060` — copies live widget-0 index (`0x2001b816`) into
  `g_dashboard_widget_state[1]`, mirrors it via `FUN_0001672c`, returns it. **[public api]**
- `FUN_00016658` — restores the persisted dashboard config block from the RAM
  snapshot (`0x2007fc00…`) into the live `device_info` struct (`+0xfec`) at boot.
- `FUN_0004a4b4` — records a session marker (two args) plus a `k_uptime_get`
  timestamp at `0x20004df0…dfc`.
- `FUN_00048b44` — clamps its arg to `[0x21..0x7d]` and writes display register
  `0x20002544` (brightness/contrast); called with `0x42` from the render task.
- `FUN_0007d1d0` / `FUN_0007ca4e` — atomic reads of a status/lock flags word.
- `FUN_0007d248` — range-checks both lenses' charge/status bytes
  (`device_info[0xfc0/0xfc1]`), returns 0 (ok) / -1.
- `FUN_0007dac0` — returns today's burial-point day slot (0..6, 7 = unavailable);
  shared with wear-time/system analytics. **[public api]**
- `FUN_0007db50` — divides an elapsed-ms interval to seconds and accumulates it
  into today's per-day dashboard dwell bucket in `device_info`.

## Globals / structs owned
- `g_dashboard_widget_state` @ `0x20004950` — live widget/render state (byte
  fields: [1] widget-0 idx, [3] selector, plus timers at +0x10/+0x14).
- Widget index bytes: `g_news_widget_index_raw` @ `0x2001b814`,
  `g_stocks_widget_index_raw` @ `0x2001b815`, `g_widget0_index_raw` @ `0x2001b816`.
- Dashboard **config snapshot** @ `0x2007fc00…` (persisted startup-mode block,
  mirror of the flash record; byte `+0x69` = default selector).
- Session/dwell timestamps @ `0x20004df0…dfc`.
- Display level register @ `0x20002544`.
- Note: stocks/news **feed content** is populated by the `ancs_notify` module;
  the startup-mode **flash record** lives in the shared flash store; the widget
  selector byte is shared with `touch_key`/`quicknote`.

## Entry points
- `ui_DashBoard_task` — screen render callback, invoked by the **display** thread
  (`ui_raster_height_task`). This module defines no thread of its own.
- `init_dashboard_info` — boot initialisation.
- `handle_dashboard_action` — gesture/BLE action sink.
- `upgradeDashboardStartupModeInfoToFlash`, `cleanDashBoardStartUpModeInfo`,
  `getDashboardStartUpModeInfofromFlash`, `SendDashboardLockInfoToApp`,
  `SendDashBoardStartupModeInfoToSlave` — reached from BLE protocol dispatch and
  the flash-restore path.
