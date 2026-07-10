# imu_motion — IMU fusion, wear/tilt wake, pitch calibration

## Responsibility
Reads the inertial sensor (accelerometer + gyroscope) and fuses it to detect
that the glasses are worn and that the user has tilted their head up to look at
the HUD, which wakes the display. It also drives the on-glasses screen that lets
the wearer calibrate the vertical "pitch" so the projected image sits at a
comfortable elevation.

The topic cluster also pulls in a handful of shared **GUI-canvas primitives**
(`gui_set_active_canvas`, `gui_canvas_flags_*`, `gui_reset_dynamic_bitmap_frame_state`)
because the pitch-calibration task is their densest single caller. They are
general display-layer helpers, not IMU logic — see the note under *Key functions*.

## Flow
```
IMU hw (accel/gyro)
   │
   ├─ register_imu_funsion_context  (install 4-entry fusion callback table into ctx+0x8c..0x98)
   │        (called from system-init dispatcher FUN_00016eb8)
   │
   ├─ imu_set_enabled ──> update_imu_trigger_status
   │        write trigger -> device_info+0xee8; on rising edge while worn
   │        (mode 0xa, +0xb0c==0): set +0xfe9, submit work at device_info+0xaf4
   │        via FUN_00072880 (rtos scheduler primitive)  ──> display wake/reflash
   │
   └─ ui_set_imu_pitch_task  (pitch-calibration screen; action 1=draw/step, 2=exit)
            state machine over flags @0x2001cf8f; per-frame:
            gui_set_active_canvas → gui_canvas_flags_set_bit1 →
            imu_pitch_task_reset_render_state / gui_reset_dynamic_bitmap_frame_state →
            8x set_imu_pitch_reflash + reflash_fb_data_to_lcd(0x280 x 199)
            ("ble set user horiz pitch:%d", "set_imu_pitch: horiz_step over MAX")
```

## Key functions
IMU-specific:
- `register_imu_funsion_context` (@0x26250, entry) — installs the IMU fusion
  callback table (4 fn-ptrs 0x25fad/0x25df9/0x25dc5/0x25d8d) into the context
  struct; run once from the system-init dispatcher.
- `update_imu_trigger_status` (@0x2bcbc) — commits a trigger state into
  `device_info+0xee8`; on a rising trigger while worn it raises `+0xfe9` and
  submits the IMU work item at `device_info+0xaf4` via `FUN_00072880`.
- `imu_set_enabled` (@0x2bd4c, entry) — on/off wrapper: calls
  `update_imu_trigger_status(…,1/0,…)` then `trigger_screen_state_change`
  (log strings "imu on"/"imu off" at a24e4/a24dc).
- `ui_set_imu_pitch_task` (@0x46b80, entry) — the pitch-calibration screen
  dispatch handler; steps horizontal pitch and previews the HUD by AND-masking
  the canvas against a per-angle mask table and reflashing 8 frames.
- `dump_template_gyro_info` (@0x36164) — debug dump of the gyro template
  x/y/z (from device_info +0xef/+0xf3/+0xf7).

Shared GUI-canvas primitives (topic-clustered; logically gui/display layer):
- `gui_set_active_canvas` (@0x431b4) — `g_gui_active_canvas` (0x2000a034) <- arg.
- `gui_canvas_flags_set_bit1` / `gui_canvas_flags_clear_bit1` (@0x432d0/0x432ec)
  — set/clear bit1 of `g_gui_canvas_flags` (0x2000a030).
- `gui_reset_dynamic_bitmap_frame_state` (@0x43308) — zero the dyn-bitmap
  cycle/frame/limit counters (0x2000f6fe/f700/f702).
- `imu_pitch_task_reset_render_state` (@0x436f8) — zero the 6-word pitch render
  state block at g_obj_2000a018 (0x2000a018..0x2000a02c).
- `FUN_0007d3dc` (@0x7d3dc) — display helper thunk (`_tail(8,0,0)`); used to
  reset/clear display state around the pitch task.

## Owned data / structs
- Pitch render-state block `g_obj_2000a018` — 6 words 0x2000a018..0x2000a02c
  (recovered_structs.h), zeroed by `imu_pitch_task_reset_render_state`.
- GUI canvas globals `g_gui_active_canvas` (0x2000a034) and `g_gui_canvas_flags`
  (0x2000a030) — shared with the wider GUI layer.
- Dyn-bitmap frame counters 0x2000f6fe/f700/f702.
- Pitch-task flag byte-triple at 0x2001cf8f..0x2001cf91.
- `device_info_t` fields consumed: trigger state `+0xee8`, wear/pending flags
  `+0xb0c`/`+0xfe9`/`+0xfea`, IMU work item `+0xaf4`, gyro template
  `+0xef/+0xf3/+0xf7`, framebuffer ptrs `+0xeb4/+0xeb8`. (The IMU does not own
  device_info; it is defined by the system/state module.)

## Entry points
These are dispatch-table / callback targets, invoked by other modules' task
loops — the module defines no threads of its own (see wiring.md):
- `register_imu_funsion_context` — one-shot init, called from system-init
  dispatcher `FUN_00016eb8`.
- `imu_set_enabled` — called from the work-mode handler `FUN_0002af4c`.
- `ui_set_imu_pitch_task` — called from the UI task dispatcher `FUN_00048b5c`.
- `dump_template_gyro_info` — debug/telemetry, no in-module caller.

## Notes
The earlier draft described the `FUN_000431b4`–`0x436f8` cluster as
"fusion-math routines"; that was wrong. Proven bodies show they are simple
GUI-canvas / render-state accessors shared across the UI. Real fusion happens
in the callback table installed by `register_imu_funsion_context` (targets
0x25d8d/0x25dc5/0x25df9/0x25fad, outside this group).
