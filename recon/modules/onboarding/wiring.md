# onboarding — RTOS wiring

## Objects DEFINED by this module

**None.**

Every function owned by the onboarding module was read from its proven body
(`recon/verified/src/*.c`) and none contains an RTOS-object definition or init
call — no `k_thread_create` / `K_THREAD_DEFINE`, no `k_msgq_init` /
`K_MSGQ_DEFINE`, no `k_sem_init`, `k_mutex_init`, or `k_work_*`:

| addr    | function                          | RTOS init calls |
|---------|-----------------------------------|-----------------|
| 0x26a08 | check_disp_onboarding             | none — only `update_persist_task_status(ctx,0xE,2)` (task-status update, not a definition) |
| 0x40708 | onboarding_retry_watchdog_update  | none |
| 0x42d44 | ui_onboarding_task                | none |
| 0x7d39e | onboarding_clear_active_flag      | none |
| 0x7d3c2 | FUN_0007d3c2 (shared |a-b| util)  | none |

The name `ui_onboarding_task` is descriptive only; it is a plain handler invoked
by another module's dispatcher, **not** a `K_THREAD_DEFINE` entry.

## Hosting threads (owned elsewhere — inputs for wiring reconstruction)

This module's entry points run on threads defined by other modules. Their
definitions must be recovered when those modules are processed:

- `check_disp_onboarding` (0x26a08) ← `FUN_0002a8d8` (0x2a8d8, no callers →
  top-level thread/dispatch entry in the display / work-mode subsystem).
- `ui_onboarding_task` (0x42d44) ← `FUN_00048b5c` (0x48b5c) ← `FUN_00048e28`
  (0x48e28) — inbound onboarding-action processing path.
- `onboarding_retry_watchdog_update` (0x40708) is additionally called from
  `slave_display_thread` (0x27cfe, esb_sync) and `FUN_00042a64` (0x42a64 ←
  `ble_process_put_req`, the BLE RX path).

## Shared state touched (not RTOS primitives)

- `device_info_t.onboarding_state` (+0x0CD) and the onboarding UI block at
  `*(device_info+0x1014)`.
- SRAM flags/counters: `0x20018D93` (pending), `0x200034F5` (last-step cache),
  `0x2001CDD1/2/3` (retry / attempt counters, watchdog-active flag),
  `0x2001CDCE` (secondary reset flag), retry block at `0x20004BF0`
  (byte counter `+0`, 64-bit last-attempt timestamp `+8`).

These are plain globals guarded by the hosting threads' serialization, with no
onboarding-owned lock; concurrency is inherited from the host threads above.
