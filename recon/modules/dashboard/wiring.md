# dashboard — RTOS wiring

## RTOS objects DEFINED by this module
**None.** Every proven body in this module was inspected for `K_THREAD_DEFINE`,
`K_MSGQ_DEFINE`, `k_thread_create`, and `k_sem/mutex/work` init — none appear.
The dashboard does not own a thread, message queue, semaphore, mutex, or work
item. It is a *client* that runs on the display thread and produces to queues
owned by other modules.

### Execution context
- `ui_DashBoard_task` @ `0x3af78` is **not** a thread entry despite the name. It
  is a display screen-state callback, invoked synchronously by the display
  thread `ui_raster_height_task` (module `display`) and by `0x48b5c`. There is
  no `K_THREAD_DEFINE(ui_DashBoard_task, …)` anywhere.

## External RTOS objects this module DEPENDS ON (produces to)
These are DEFINED elsewhere (flash-store / protocol / language modules); the
dashboard only enqueues to them. Listed here as input to the wiring
reconstruction of the owning modules.

| Object | Address | Owner (to confirm) | How dashboard uses it |
| --- | --- | --- | --- |
| `g_flash_store_cmd_msgq` | `0x20003994` | flash store | `k_msgq_put(0x20003994, buf, 0, 0)` — persist/reset startup mode. cite: `upgradeDashboardStartupModeInfoToFlash` @ 0x23bfc; `cleanDashBoardStartUpModeInfo` @ 0x23c88. Message = `{0x00010003, mode, idx}` (upgrade) / reset variant. |
| `g_app_language_msgq` | `0x200079e4` | app / language | signalled via `FUN_00072880(0x200079e4)` after a successful flash-store enqueue. cite: `upgradeDashboardStartupModeInfoToFlash` @ 0x23bfc, `cleanDashBoardStartUpModeInfo` @ 0x23c88. |
| `g_dashboard_response_msgq` | ptr @ `0x2000392c` | protocol/response | `k_msgq_put(*0x2000392c, buf, 0, 0)` — mirror startup mode to slave. cite: `SendDashBoardStartupModeInfoToSlave` @ 0x48a3c. |
| app response queue (via `send_response_data_to_msgqueue`) | — | protocol | phone lock/status reports. cite: `SendDashboardLockInfoToApp` @ 0x25e2c, `ui_DashBoard_task` @ 0x3af78. |

## Timing / uptime calls (no object defined)
- `k_uptime_get` (`thunk_FUN_00074f68`) — read for dwell timers in
  `ui_DashBoard_task` @ 0x3af78 and for the session marker in `FUN_0004a4b4`
  @ 0x4a4b4 (`k_uptime_get_9`). These are kernel time reads, not object defs.

## Summary
dashboard defines **0** threads, **0** msgqs, **0** sems/mutexes/work items.
It runs on the display thread and publishes to 3 externally-defined message
queues (flash-store cmd, app-language, dashboard-response) plus the protocol
response path.
