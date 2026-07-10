# ancs_notify — phone notification ingest, filtering & display

## Responsibility
Brings phone notifications onto the glasses. On iOS it acts as an ANCS (Apple
Notification Center Service) GATT client; on both iOS and Android the Even app
can also push notifications through the app BLE protocol. Notifications are
parsed, filtered against a user-editable per-app whitelist, stored in a fixed
message pool, de-duplicated/expired, and rendered on the panel via
`gui_text` `draw_message`. This is the largest assigned group (557 functions),
but only a small subset is the true ANCS surface — see "Public/internal" below.

## Ingest pipeline
```
iOS:  ANCS GATT  ──> bt_ancs_data_source_handler ──┐
                                                    │ enqueue_ancs ──> g_ancs_msgq
app:  BLE cmd    ──> post_notification_cmd_process ─┘        │       (436B x 10)
                                                     ancs_main (thread, prio -11)
                                                             │ dequeue_ancs
                                                             ▼
              parse_ncs_notification / parse_receiver_*_pkcs7
                                                             │
              is_on_whitelist_by_identifier  (drop if not whitelisted:
                        "blocked! app(%s) not in whitelist")
                                                             │
              push_message ──> g_message_pool / g_message_table
                                                             │
              is_msg_expiration / clear_timeout_message  (age out)
                                                             │
              draw_message (gui_text) ──> display reflash
```

## Public / internal split (graph-driven)
Public API = the reference graph's `api` set: **60 symbols** actually reached
from other modules (or via data as callbacks). Everything else the module only
calls internally, so it is `static`. This corrects the previous header, which
over-exposed the ANCS client, parse, store and whitelist helpers as public even
though they have no cross-module callers.

Genuine cross-module ANCS surface (named, in `api`):
- `bt_ancs_data_source_handler` (0x18c48) — ANCS data-source GATT callback.
- `post_notification_cmd_process` (0x338ec) — app-BLE post-notification command
  (called from `ble_proto` @0x21460).
- `get_notification_counts_cmd_process` (0x33abc) — counts query (`ble_proto`).
- `clear_timeout_message` (0x33d58) / `is_msg_expiration` (0x3444c) — TTL sweep +
  test (called from `system`).
- `confirm_message` (0x34524) — mark read/handled (called from `esb_sync`).
- `ble_whitelist_app` (0x22218) — whitelist advertising helper.
- `mobile_send_notification_to_ble_device_test` (0x21c04),
  `simulator_ancs_calendar_schedule_trigger` (0x21cd8) — test/sim injectors
  (from `ble_proto`).
- `update_temp_task_status` (0x2bffc) — status latch used by `esb_sync`/`system`.

Module-hosted generic utilities also in `api` (used engine-wide, live here by
call-graph residence, not ANCS logic): `random` (0x17f70), `debug_print`
(0x19c70, the alternate log sink almost every module calls), `local_store_write`
(0x22168), `uart_callback` (0x33384).

Module-internal (now `static`, NOT public): `ancs_c_init`,
`request_ancs_attr_ext`, `ancs_connected/disconnected/security_changed`,
`ancs_main`, `start_ancs_work_thread`, `init_msgq_ancs`, `enqueue_ancs`,
`dequeue_ancs`, `parse_ncs_notification`, `parse_receiver_*_pkcs7`,
`push_message`, `post_notification_cmd_response`, `load_whitelist`,
`store_whitelist`, `is_on_whitelist_by_identifier`, `convert_app_whitelist_to_json`,
`put_whitelist_app_from_app`, `check_bind_status`, the stocks/news feed helpers,
and the misc helpers (`le_adv_update`, `get_timestamp`, `uint32_to_little_endian`,
`setDelayExitValue`, `memset_bytes`, `printf_like`).

## Deduced roles of remaining FUN_* api entries
45 of the 60 api symbols are still unnamed. Deductions from callers+callees:
- Small BLE / accessor helpers (called by ble_proto/audio/battery/system):
  `FUN_0000d588` (4-byte state accessor), `FUN_000181fc` (6-byte getter),
  `FUN_00012c18` (record deserialize), `FUN_00018334`/`FUN_000183ac`
  (bt-attr build + its log wrapper), `FUN_0002c1fc` (message-table op wrapper),
  `FUN_0002c30c`/`FUN_00033c4c` (tiny accessors/flags), `FUN_000336a0`,
  `FUN_00033b4c` (notification/message helpers, from `system`), `FUN_00035498`
  (whitelist/notify cmd from `ble_proto`, uses `convert_app_whitelist_to_json`).
- **Spillover cluster 0x4d000–0x5a000** (~30 symbols): a self-contained low-level
  library that is NOT ANCS logic — it landed in this group by call-graph
  proximity. Evidence: `FUN_000507d4` is a critical section
  (`isCurrentModePrivileged`/`setBasePriority`/ISB); the cluster is dominated by
  list/tree walks (`FUN_000566a4` is recursive, `FUN_00056704` serializes),
  record/format builders (`FUN_00057db0`, 1184 B) and lock thunks
  (`FUN_0007e2ec`/`FUN_0007e2fa`). Its cross-module callers are `flash_store`,
  `battery`, `ble_proto`, `system`. Treat as generic serialization/persistence
  helpers pending its own module split; do not read ANCS meaning into them.

## RTOS objects defined (see wiring.md for exact params)
- **Message queue** `g_ancs_msgq` @ 0x20006a6c — `k_msgq_init` in
  `init_msgq_ancs` @0x18b6c: msg_size **436 B**, depth **10**.
- **Worker thread** `ancs_main` — `k_thread_create` in `start_ancs_work_thread`
  @0x198cc: stack @0x2001d568 size **0x1400 (5120 B)**, entry 0x19719
  (body `ancs_main` @0x19950), priority **-11** (cooperative), arg = conn handle.
  Self-restarts (ancs_main re-calls start_ancs_work_thread on exit).
- No sem/mutex/work defined in this module's init paths.

## Globals / structs owned
- `g_ancs_msgq`        @ 0x20006a6c — 436B×10 notification queue.
- `g_ancs_active_conn` @ 0x20006ab8 — active ANCS connection (latched by ancs_main).
- `g_ancs_client`      @ 0x20006ae8 — ANCS GATT client ctx; attr scratch @0x20006aa0/aac.
- `g_message_pool` @ 0x20007dac, `g_message_table_mirror` @ 0x20008eb4,
  `g_message_table_slot_count` @ 0x2001a22b — the notification store.
- Whitelist blob in flash (via `load_whitelist`/`store_whitelist`).
- `device_info_t.ancs_enable_flag`, `phone_connection_type` (1=iOS/2=Android),
  `message_stay_time_mode`.

## Entry points (no in-module caller / reached from RTOS or callbacks)
- **Thread body:** `ancs_main` @0x19950 (spawned by `start_ancs_work_thread`).
- **GATT callbacks:** `bt_ancs_data_source_handler`, `ancs_connected`,
  `ancs_disconnected`, `ancs_security_changed`.
- **BLE app-command sinks:** `post_notification_cmd_process`,
  `get_notification_counts_cmd_process`, `mobile_send_notification_to_ble_device_test`,
  `simulator_ancs_calendar_schedule_trigger`, `put_whitelist_app_from_app`.
- Graph `entry_points` for the group also list low-level FUN_ callbacks
  (0xe3a0, 0xe954, 0xe9b4, 0xea70, 0xeb7c, 0x230bc, 0x26b88, 0x2c498, …) —
  most belong to the spillover cluster / util residents, not ANCS proper.

## Notes
The group still contains a large tail of unnamed `FUN_*` and generic residents
(`printf_like`, `random`, `memset_bytes`, `uint32_to_little_endian`,
`nullsub_*`). Treat the whitelist / message-pool / ANCS-client functions as the
real subsystem; the 0x4d000–0x5a000 cluster is a candidate for its own module.
