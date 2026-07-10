# teleprompt — teleprompter script display

## Responsibility
Shows a scrolling teleprompter script on the glasses. The phone streams the
script and scroll control over BLE service `SVC_TELEPROMPTER` (0x0620); the
glasses render it and report progress and an "arrived" (end-reached) status back
over `SVC_TELEPROMPTER_ACK` (0x0600) / `SVC_TELEPROMPTER_PROG` (0x0601). Like
navigation, all content originates on the phone — the glasses are a paced display
surface.

> Scope note: no teleprompter function is reconstructed into `recon/named/` yet.
> The entry point `ui_teleprompter_task` and the packet handlers are known from
> firmware debug strings but live in the `ble_proto` / `system` dispatch groups
> (other agents' subsystems). This module is a documented map only.

## Protocol / state machine (from debug strings)
```
BLE_REQ_PUT_TELEPROMPTER_INFO (SVC 0x0620) ──> app dispatcher ──> ui_teleprompter_task
   packet types:
     init          "received teleprompter init packet"        ──> load script buffer
     text upgrade  "received teleprompter text upgrade packet" ──> append/replace text
     suspend       "received teleprompter suspend packet"      ──> pause scroll
     arrived stat  "received arrived status packet ..."        ──> report reached word
     exit          "received teleprompter func exit packet"    ──> tear down
   validation: "app send prompt word oversize, drop it";
               "teleprompter packet length error, input=%d packet=%d"
   states: TELEPROMPTER_DISPLAY_IDLE ─> TELEPROMPTER_TEXT_DISPLAY
                                      ─> TELEPROMPTER_DISPLAY_ABNORMAL_EXIT
   pacing: "received teleprompter counter down timer start event" (scroll timer)
```
Master/slave: on BLE disconnect the master sends Stop Teleprompter to the slave
and auto-exits ("The teleprompter automatically shuts down due to disconnection";
"teleprompter SLAVE disconnect EXIT").

## Globals / structs
- Script buffer: `device_info_t.teleprompter_data_ptr` (@ offset 0x1000, see
  `recon/application/app/src/device_info.h`).
- Countdown/scroll timer: `device_info_t.countdown_timer_ptr`.
- Service IDs: `SVC_TELEPROMPTER` / `_ACK` / `_PROG` in `even_protocol.h`.

## Entry points
- Thread: `ui_teleprompter_task` (not yet reconstructed).
- BLE sink: `BLE_REQ_PUT_TELEPROMPTER_INFO` handler in the app dispatcher.

## Notes
Renders through `gui_text` (`gui_utf_Wordwrap_draw` for the scrolling body) and
`display`. Reconstruction of `ui_teleprompter_task` would populate this module's
header with real prototypes.
