# quicknote — QuickNote capture (voice-note text + audio)

**Role.** Implements the QuickNote feature: a captured note carries a title +
text plus an associated audio record. This module runs the QuickNote UI/mode
and is the *producer/consumer front-end* of the QuickNote-flash command queue;
the persistent records are stored, verified and drained by `flash_store`.

Module unit (graph): 6 functions, 117 owned data objects. Every reconstructed
body cited here is Unicorn-parity PROVEN.

## Public API (graph `api` set — called from other modules by symbol)
- `getQuickNoteBKPQueueCacheData(a, b, c)` — @0x24684. Dequeues one entry from
  the QuickNote-flash backup queue cache (`g_quicknote_flash_msgq` @0x20003960,
  12-byte messages) into the caller's 3-word slot. Returns 0 on success, -1 when
  empty/failure (with gated debug logging).
- `prepare_quick_note_mode(buf, kind, a, b)` — @0x7cdb6. Arms the lens into
  QuickNote "slave" mode: guarded by `check_battery_critical()` and a screen-id
  check (`buf[0xd5] == 6 || == 4`); optionally emits an event status, forces the
  persist task to idle (`update_persist_task_status_to_idle`) and clears the
  capture buffer (`memset_bytes`). (`Quick Note Slave Start up...`,
  `QUICK NOTE SLAVE Delay EXIT`.)

## Entry points (reached by dispatch/registration, not by symbol)
- **UI task / renderer:** `ui_QuickNote_task(ctx, _, phase)` — @0x3b824. The
  QuickNote screen state-machine, invoked per frame by the main UI dispatcher
  `FUN_00048b5c`. Drives a 3-state UI byte `g_quicknote_ui_state` @0x20004978
  (0 = arm/record, 1 = recording, 2 = review/timeout) off the `phase` argument
  (0/1/2/3), starts audio capture (`dmic_record_start`), renders text/bitmaps
  via the `gui_*` primitives + `reflash_fb_data_to_lcd`, and runs a delay-exit
  countdown: deadline computed from uptime (`thunk_FUN_00074f68`) plus
  `getDelayExitValue()` and a config window @0x200024e8, stored in the state
  struct at +4/+8/+0xc.
- **Delete command:** `deleteQuickNoteData(note_num, _, param3)` — @0x244a8.
  Enqueues a delete command `{0x00010002, note_num, param3}` onto
  `g_quicknote_flash_msgq`, then signals the `g_app_language_msgq` sem
  (@0x200079e4, via `FUN_00072880`). Returns 0 / 0xffffffff on queue-full.
  (`received empty quick note data, delete quick note num.%d`,
  `received delete all quick note audio file command .`)

## Internal helpers (auto-named `FUN_*`)
- `FUN_00037098()` — @0x37098. **Reset the dashboard/widget scroll-index state:**
  zeros `g_dashboard_widget_state[1]` (news index @0x20004951) and
  `g_widget0_index_raw` (@0x2001b816), then clears shared-RAM control byte
  0x2007fc69 via `FUN_0001672c(0)`. Cross-cutting reset also used by the
  dashboard flows (callers 0x2316c, 0x3727c); reached from QuickNote via
  `getQuickNoteBKPQueueCacheData`. Not QuickNote-specific despite topic grouping.
- `FUN_00049040()` — @0x49040. **`getDelayExitValue()`**: returns
  `g_delay_exit_value` @0x2000a094 (the slave delay-exit countdown seed).
  Address-identical to the named `getDelayExitValue`; `ui_QuickNote_task` calls
  it under that alias.

## State it owns / structs
- `g_quicknote_ui_state` @0x20004978 — 16-byte QuickNote UI/state struct
  (state byte at +0; delay-exit deadline words at +4/+8/+0xc), cleared with
  `memset_bytes(...,0,0x10)`.
- QuickNote exit/confirm flag @0x2001b817 (`DAT_0003bde8`).
- `g_delay_exit_value` @0x2000a094 (delay-exit countdown seed).
- The persistent records + backup queue live in `flash_store`; this module only
  reaches them through `g_quicknote_flash_msgq` (see wiring.md).

## Cross-module coupling
- **flash_store** — the other endpoint of `g_quicknote_flash_msgq`
  (`upgradeQuickNoteDataToFlash` producer, `drain_quick_note_data_queue` /
  `QuickNoteStoreHandler` consumers, `getQuickNoteDataFromFlash` restore):
  `SEND QUICKNOTE TEXT Store(%d) Command...`, `quicknote %d store sucess`.
- **ble_proto** — inbound note title/text/audio commands
  (`Quick Note Title = %s, TXET = %s`).
- **system / display** — screen/work-mode changes and the GUI/LCD pipeline
  (`gui_*`, `reflash_fb_data_to_lcd`); audio via `dmic_record_start`.
