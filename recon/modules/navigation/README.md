# navigation — turn-by-turn & map HUD

## Responsibility
Displays phone-driven navigation on the glasses. The phone app computes the
route and pushes navigation info over BLE service `SVC_NAVIGATION` (0x0820); the
glasses render the current turn arrow, distance, and an overview/panoramic map
image, and mirror the screen to the slave lens over ESB. No routing happens on
the glasses — this is a display/state-machine subsystem.

> Scope note: only `navigation_direction_img_display` is reconstructed in
> `recon/named/`. The packet dispatcher and map renderers named below are known
> from firmware debug strings but live in the `ble_proto` / `system` dispatch
> groups (other agents' subsystems); they are documented here for completeness.

## Protocol / state machine (from debug strings)
```
BLE_REQ_PUT_NAVIGATION_INFO (SVC 0x0820) ──> app dispatcher ──> ui_navigation_task
   packet types:
     startup   "received navigation func startup packet"   ──> ENTER NAVIGATION INIT
     direction "APP send navigation offset ..."             ──> navigation_direction_img_display
     map data  "received navigation panoramic map data ..." ──> navigation_panoramic_map_display
               "Maps are compressed to only one pack!!!"        / navigation_overview_map_display
     arrived   ("navigation arrived 1/2 rst reflash")       ──> reflash arrival state
     exit      "received navigation func exit packet"       ──> auto/normal exit
   states: NAVIGATION INIT ─> NAVIGATION_RUNNING ─> ABNORMAL EXIT / exit
```
Master validates the slave's current ScreenID before forwarding ("the slave's
current ScreenID is not navigation, drop this command"). On BLE disconnect the
master sends Stop Navigation to the slave and auto-exits ("The navigation
automatically shuts down due to disconnection").

## Key functions
- `navigation_direction_img_display` (reconstructed) — draws the turn-arrow icon
  for `dir_id` 1..0x23 via `gui_bmp_bitmap_draw`; sized from
  `device_info_text_width/height_get`.
- `ui_navigation_task` (not reconstructed) — the navigation screen thread /
  packet state machine.
- `navigation_overview_map_display` / `navigation_panoramic_map_display` (not
  reconstructed) — blit the received map bitmaps.

## Globals / structs / entry points
- Service ID: `SVC_NAVIGATION 0x0820` (see `recon/application/app/src/even_protocol.h`).
- Uses the `display` screen state machine (`trigger_screen_state_change`) and
  `gui_text` bitmap blitters to render; syncs L→R over ESB.
- `device_info_t.next_screen_id` / `current_app_id` gate the navigation screen.

## Notes
Rendering primitives are shared with `display`/`gui_text`. The reconstructable
surface owned specifically by navigation is currently just the direction-icon
renderer; the rest awaits reconstruction of the app dispatcher functions.
