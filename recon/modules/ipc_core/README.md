# ipc_core — Inter-core IPC transport + dashboard response bridge

**Role.** Two cooperating jobs:

1. **IPC transport** — a thin wrapper over the Zephyr `ipc_service` / RPMsg
   endpoint that carries messages between the nRF5340 **application core** and
   the **network (radio) core** (endpoint 0). Installs the endpoint context,
   demuxes inbound buffers to the right registered handler, and provides a
   blocking send that treats IPC failure as fatal (reboots the SoC).
2. **Dashboard response bridge** — assembles small status packets from device
   state and pushes them into the app-core response message queue
   (`g_dashboard_response_msgq @0x2000392c`) with `k_msgq_put`, for the
   dashboard/widget sync path.

## Key functions
- `ipc0_ept_recv(buf, len)` — *@0x25a48* **RX callback (endpoint 0).** Reads
  `buf[0]` as a type byte, linear-scans the endpoint's handler table
  (`g_ipc0_endpoint @0x20007a84`, table at +4), and on match tail-calls the
  handler `*(fn*)(entry+8)` with `(ctx-0x714, buf+1, len-1)`. Logs the frame
  when unmatched.
- `global_ipc_service_send(data, len)` — *@0x25b78* **blocking TX.** Guards on
  the bound flag `@0x20007a80` and device state, calls `ipc_service_send`
  (endpoint `@0x20007a78`), retries up to a counter `@0x20007a74`, sleeps
  (`FUN_00074844(0x4000,0)`) between tries, and after >2 failures calls
  `sys_reboot` (`FUN_0004c0a8`) — "sys reboot because ipc failed".
- `send_response_data_to_msgqueue(payload, len)` — *@0x47b1c* zero-fills a
  24-byte record, copies `payload` (`len<=0x14`) at offset 4 with the length at
  offset 2, and `k_msgq_put`s it into `g_dashboard_response_msgq`.
- `send_response_data_to_ble(...)` — *@0x47ba8* (`FUN_00047ba8`) enqueues a
  fixed **type-1** 24-byte control record into the same response msgq.
- `send_dashboard_status_sync(...)` — *@0x3ae6c* (`FUN_0003ae6c`) builds a
  **10-byte** dashboard status frame (header word `0xa22`; bytes from
  `msg_content_recalc_unread`, device_info offsets `+0x5f/+0x64/+0x65`, and a
  widget index chosen by mode selector `g_dashboard_widget_state+0x1a`), then
  posts it via `send_response_data_to_msgqueue` + `send_response_data_to_ble`.
- `send_dashboard_status_sync_compact(...)` — *@0x3af04* (`FUN_0003af04`)
  **8-byte** variant driven by mode selector `@0x2000496a`.
- `getStocksIndex()` / `getNewsIndex()` — *@0x370bc / @0x3719c* latch the
  stocks/news widget index from `@0x2001b815 / @0x2001b814` into
  `g_dashboard_widget_state` (offset +3 / +5) and return it.

### Internal (platform init, not cross-module API)
- `init_msgq_uid()` — *@0x18e04* `z_impl_k_msgq_alloc_init(g_uid_pipe, 8, 10)`
  — heap-allocates the 8-byte × 10-slot UID pipe message queue.
- `register_ipc_service_context(ctx, …)` — *@0x25d40* writes the endpoint
  callback thunks (`+0x60 = 0x25b79`, `+0x64 = 0x25ae9`) into the context and
  publishes it as `g_ipc0_endpoint @0x20007a84`.

## State it owns / structs
- **`g_uid_pipe` @0x20006a38** — msgq (8-byte msgs, 10 slots) allocated by
  `init_msgq_uid` (DEFINED by this module; see wiring.md).
- **`g_ipc0_endpoint` @0x20007a84** — the ipc_service endpoint context pointer,
  plus its transport globals: send handle `@0x20007a78`, bound flag
  `@0x20007a80`, retry counter `@0x20007a74`.
- **`g_dashboard_widget_state` @0x20004950** — the widget index/mode block that
  the dashboard status frames and `getStocks/NewsIndex` read/write.
- References (does NOT define) **`g_dashboard_response_msgq` @0x2000392c** — the
  response queue it enqueues into; that msgq is defined by another module.
- Shared payloads: IPC frames are the device-wide `GLOBAL->*_sync_pkg` structs
  also used by `esb_sync` and the display pipeline; this module transports them.

## Entry points
- **RX callback:** `ipc0_ept_recv @0x25a48` — installed via
  `register_ipc_service_context`; invoked by the ipc_service backend on RX.
- **Platform init:** `init_msgq_uid @0x18e04` (caller @0x19718) and
  `register_ipc_service_context @0x25d40` (caller @0x16eb8) — run once from the
  boot/init sequence.
- **TX + status API:** `global_ipc_service_send`,
  `send_dashboard_status_sync[_compact]`, `send_response_data_to_msgqueue`,
  `send_response_data_to_ble` — called across the firmware (ESB sync, system,
  UI dashboard task).

## Cross-module coupling
- `esb_sync` / `system` call `global_ipc_service_send` and rely on its
  reboot-on-failure behavior.
- The net core is the peer on endpoint 0; frame structs are shared with it.
- The UI dashboard task drives the `send_dashboard_status_sync*` builders.
