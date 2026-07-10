# display — projector panel driver & framebuffer refresh

## Responsibility
Drives the two JBD micro-LED projector panels (left = master, right = slave)
and the framebuffer ("canvas") refresh pipeline. It is the lowest UI layer:
`gui_text`/`gui_*` draw glyphs and bitmaps into a RAM canvas, and this module
powers the panel, sets brightness, and blits the canvas to the LCD. It also runs
the screen open/close state machine that multiplexes the panel between the
on-glasses apps (dashboard, navigation, teleprompter, notifications, translate).

## Display pipeline
```
app / BLE cmd ──> trigger_screen_state_change ──> screen state machine
gui_text draw ──> canvas (framebuffer in RAM)
                         │
   display_reflash ──────┤ (posts work)
                         ▼
   display_reflash_handler  ──> ui_refalsh_warp ──> reflash_fb_data_to_lcd[_ex]
                                                        ──> JBD panel bus
```
- `ui_raster_height_task` is a thread that recomputes the canvas placement
  (raster height / canvas distance "gears", stored in `device_info_t`) and
  triggers a full clear+redraw; log: `ui_raster_height_task reflash...` /
  `ui_raster_height_task exit...`.
- Reflash is deferred through a work item so BLE/ESB callbacks stay short
  (`display_reflash` enqueues, `display_reflash_handler` runs it).

## Key functions
- `panel_init` / `jdb_panel_init` — bring up the JBD panel, load init regs.
- `power_for_panel` / `power_down_panel` — panel power rails (enable ldsw1 1.8v,
  turn off -2v, etc.; see debug strings "enable ldsw1 1.8v for panel").
- `jbd_panel_suspend` / `jbd_panel_resume` — low-power gating.
- `panel_on` / `panel_off` — display enable/blank.
- `set_brightness_to_panel_reg[_in_running]` — write brightness level to panel
  register; `set_brightness_lum_base` maps ambient lux → brightness (ties into
  `battery`/opt3007 ambient-light sensor and `auto_brightness_flag`).
- `reflash_fb_data_to_lcd[_ex]` — DMA/SPI blit of the canvas to the panel.
- `cal_panel_canvas_coord` — compute on-panel canvas origin from the gear
  settings.
- `trigger_screen_state_change` — central screen-id transition (uses
  `device_info_t.next_screen_id` / `current_app_id`).
- `display_close` / `display_close_screen` / `display_DelayClose` /
  `display_MasterSendClose` — tear down a screen; master tells slave to close.
- `display_inputEvent` / `display_powerEvent` — feed touch/power events into the
  display state machine.
- `update_display_status` — update `device_info_t.display_state`.
- `navigation_direction_img_display` — draw a turn-arrow icon (dir 1..0x23) via
  `gui_bmp_bitmap_draw`; owned here, used by the navigation app.
- `draw_template_translate_screen` — layout for the live-translate screen.

## Globals / structs owned
- `device_info_t` fields: `display_command`, `display_state`, `display_mode_flag`,
  `display_setting_mode`, `display_silent_mode`, `auto_brightness_flag`,
  `next_screen_id`, `current_app_id`, `display_control_ptr`, `raster_config_ptr`,
  `display_raster_height_gear`, `display_canvas_distance_gear`
  (see `recon/application/app/src/device_info.h`).
- Projector control block: `device_info_t.projector_controller[888]`
  (`struct projector_controller_t`, per-panel L/R state).
- `g_obj_2000a018` (recovered_structs.h) — panel/canvas register mirror accessed
  by `jdb_panel_init`, `FUN_00047028`, `FUN_0004904c` and friends.

## Public API (reference-graph `api` set)
15 display-owned functions are called from other modules and form the public
surface (see `display.h`): `power_down_panel`, `jdb_panel_init`, `panel_off`,
`panel_on`, `jbd_panel_suspend`, `jbd_panel_resume`, `set_brightness_lum_base`,
`reflash_fb_data_to_lcd`, `reflash_fb_data_to_lcd_ex`, `gui_screen_clear`,
`projector_reflash_and_release` (0x7d874), `trigger_screen_state_change`,
`draw_template_translate_screen`, `display_close_screen`, `display_DelayClose`,
plus the two low panel-bus primitives `panel_bus_get_handle` (0x7d4ec) and
`panel_reg_seq_7d70a` (0x7d70a). The remaining api entries the topic classifier
attached (0x527dc, 0x52880, 0x609f4, 0x71294, 0x72908, 0x73cdc, 0x80c20,
0x85a9c) are shared OpenAMP/RPMsg/GATT/msgq infra, NOT display-owned — flagged
`[shared-infra]` in `display.h`.

## Remaining FUN_ helpers — deduced purpose
- `FUN_0001655c` (0x1655c) — 6-byte panel-state flag stub, shared by
  `panel_off`/`panel_on`.
- `FUN_000179e0` (0x179e0) — 8-byte rail helper returning a constant, from
  `power_down_panel`.
- `FUN_00036024` (0x36024) — 8-byte getter used by `display_close_screen`.
- `FUN_00036d38` (0x36d38, entry) — **dashboard status-field partial refresh**:
  when `FUN_00023ee0()` status value changes, `clean_fb_data` + `reflash` the
  status glyph region; special-cases value 6.
- `FUN_00047028` (0x47028) — brightness register sub-write for
  `set_brightness_to_panel_reg_in_running` (calls the 0x7d67e/0x7d696 reg pokes).
- `FUN_0004904c` = `submit_display_reflash_work` — enqueues the reflash work
  item onto `g_display_thread_id`.
- `FUN_00049090` (0x49090) — **display dispatch thread body**: drains
  `g_display_msgq` (0x200038c4), dispatches by command byte to
  `display_reflash_handler` and the panel API.
- `FUN_00049638` (0x49638) — **display thread creator** (see wiring.md).
- `FUN_000745c8` (0x745c8) — irq-locked queue-put-with-wake (msgq/work plumbing).
- `0x7d642 / 0x7d658 / 0x7d67e / 0x7d6ae / 0x7d6f4 / 0x7d74e / 0x7d772 /
  0x7d77c / 0x7d82e` — the **JBD panel-register read/write bit-bang cluster**
  used by `panel_init`, `set_brightness_to_panel_reg`, `reflash_*`.
- `[shared-infra]` bodies (`FUN_000527dc` conn-lookup, `FUN_00052880`
  gatt-notify-chunked, `FUN_00056f4c` conn-param parse, `FUN_000609f4`
  cond-mutex-lock, `FUN_00071294` rpmsg-tx, `FUN_00071314` rpmsg-tx-space,
  `FUN_00072908` msgq-ring-put, `FUN_00073cdc` irq-lock helper, `FUN_00080c06/
  0x80c20/0x80c7c` CCC checks, `FUN_000857e0/0x8583a/0x859b6/0x85a9c/0x85b0c`
  OpenAMP virtqueue notify/release) — RPMsg/GATT IPC the master↔slave display
  sync rides on; documented in `display.h` but owned by ipc/ble.

## Entry points
- **Threads:** display dispatch/reflash thread (`FUN_00049090`, created by
  `FUN_00049638`); `ui_raster_height_task` (raster-height UI task); the app
  `display_dispatch_thread` / `key_event_thread` / `slave_display_thread` that
  drive this API.
- **Work / queue callbacks:** `display_reflash_handler` (via `display_reflash`
  → `g_display_msgq`); `FUN_0004906c` flushes pending reflash work.
- **Event sinks:** `display_inputEvent`, `display_powerEvent`,
  `display_MasterSendClose`, `update_display_status`,
  `trigger_screen_state_change` (called from BLE/ESB dispatch and app UI tasks).

## RTOS objects defined (see wiring.md)
- **msgq** `g_display_msgq` @ 0x200038c4 — display command queue, msg_size 24 B
  (static `K_MSGQ_DEFINE`; depth unrecovered).
- **thread** display dispatch/reflash worker — tcb 0x20004d18, stack 0x20028e68,
  entry `FUN_00049090`, id → `g_display_thread_id` @ 0x2000a09c
  (stack size/prio unrecovered).
- **sem** @ 0x200079e4 — `k_sem_init(0, limit 20)` in
  `spawn_flash_ops_and_brightness_threads`; co-spawns the flash-ops thread
  (stack 2048, prio -12) and brightness thread (stack 5120, prio -11).

## Notes
`FUN_00049090` (dispatch thread) and `FUN_00049638` (thread creator) are not yet
reconstructed to proven bodies — their control-block/stack/entry addresses are
recovered from the reference graph's data-refs, but exact `k_thread_create`
stack-size/priority args await reconstruction. See `recon/named/<name>.c` for
the bodies that are proven.
