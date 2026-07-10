# onboarding — First-run onboarding flow + step retry watchdog

**Role.** Drives the guided first-run UI (pairing / tutorial) shown until
onboarding completes, and runs a per-step retry/timeout watchdog so a stalled
step is abandoned rather than hanging the flow. Completion state is tracked in
`device_info_t.onboarding_state` (`0x0CD`). Action packets arrive over BLE and
each step is mirrored to the slave lens so both displays advance together.

The live onboarding UI block is `*(device_info + 0x1014)`:
`[0]` active flag, `+2` action_cmd/step id, `+3` sub_step, `+4..+B` last-progress
timestamp (64-bit uptime), `+0x20` saved step snapshot.

## Key functions
- `onboarding_retry_watchdog_update()` (`@0x40708`) — **public API.** Caches the
  current step id (`0x200034F5`); when the step changes to one outside
  `{5,0x13,0x14,0x15}` it resets the retry (`0x2001CDD1`) and attempt
  (`0x2001CDD2`) counters, then sets the watchdog-active flag (`0x2001CDD3`).
  Called from `check_disp_onboarding`, `ui_onboarding_task`,
  `slave_display_thread` (esb_sync) and `FUN_00042a64` (BLE-put path).
- `check_disp_onboarding(a,b,c)` (`@0x26a08`) — **entry point.** Display gate:
  decides whether the onboarding screen should be presented (gates on
  `onboarding_pending_flag` `0x20018D93`, connection/link state via
  `get_device_info()+0x1014`, and `onboarding_state` `+0xCD`). On the show
  transition it starts the task (`update_persist_task_status(ctx,0xE,2)`), stamps
  a timestamp, and writes `onboarding_state`.
- `ui_onboarding_task(a,b,c)` (`@0x42d44`) — **entry point.** Onboarding action
  handler / UI step advance. `param_3` selects the action class (2 = finalize/
  reset, 1 = confirm). Runs the retry watchdog: on repeated same-step re-entry at
  <1001 ms spacing it increments the retry counter and, past 20 tries, forces
  step `0x14` / action_cmd `0xB`. Mirrors the step/sub_step reset flags
  (`0x2001CDCE`) and updates `onboarding_state`.
- `onboarding_clear_active_flag()` (`@0x7d39e`) — internal helper (single caller
  `check_disp_onboarding`): clears the UI active flag if set.
- `FUN_0007d3c2(...)` (`@0x7d3c2`) — shared 64-bit `|a-b|` helper (timestamp
  delta). Referenced here but NOT owned (also used by `FUN_0003cf44`,
  `FUN_00048b5c`).

## Owned data / structs
- `device_info_t.onboarding_state` (`+0x0CD`); onboarding UI block at
  `*(device_info+0x1014)` (fields above); scratch fields `+0xD5`, `+0xED5`.
- Module globals (SRAM): `onboarding_pending_flag` `0x20018D93`,
  `onboarding_last_step_cache` `0x200034F5`, `onboarding_retry_counter`
  `0x2001CDD1`, `onboarding_attempt_counter` `0x2001CDD2`,
  `onboarding_watchdog_active_flag` `0x2001CDD3`,
  `onboarding_secondary_reset_flag` `0x2001CDCE`, and the retry/watchdog block at
  `0x20004BF0` (byte counter at `+0`, 64-bit last-attempt timestamp at `+8`).

## Entry points
- **Display gate:** `check_disp_onboarding` — called from `FUN_0002a8d8`
  (display / work-mode path; has no callers itself → top-level dispatch).
- **Action handler:** `ui_onboarding_task` — called from `FUN_00048b5c`
  (← `FUN_00048e28`), the inbound onboarding-action processing path.
- **Inbound decode:** BLE `SVC_ONBOARDING` handler `onboarding_ble_process` in
  `ble_proto` (not owned here).

## RTOS objects
- **None.** No owned function calls `k_thread_*`, `k_msgq_*`, `k_sem_*`,
  `k_mutex_*`, or `k_work_*` init. This module runs entirely on threads owned by
  other modules. See `wiring.md`.

## Cross-module coupling
- Inbound decode in `ble_proto` (`onboarding_ble_process`); slave mirroring in
  `esb_sync` (`onboarding_sync_data`, `slave_display_thread`); completion state
  read by `system` (work-mode) and the display pipeline.
- Disconnection during onboarding is logged as
  `onboarding: disconnection between the AR Glasses and the Bluetooth application!`.
