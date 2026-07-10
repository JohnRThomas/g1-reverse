# ipc_core — RTOS wiring

RTOS objects this module **defines / initialises**, read directly out of its
init functions in the proven bodies (`recon/verified/src/*.c`,
`recon/named/*.c`). All parity-PROVEN (300/300).

## Message queues

### g_uid_pipe  (DEFINED)
- **Where:** `init_msgq_uid()` @0x18e04 (`recon/verified/src/init_msgq_uid.c`,
  named `recon/named/init_msgq_uid.c`).
- **Init call:** `z_impl_k_msgq_alloc_init(&g_uid_pipe, 8, 10)`
  (Ghidra `FUN_00086448(0x20006a38, 8, 10)`).
- **Equivalent:** `k_msgq_alloc_init(msgq=g_uid_pipe@0x20006a38, msg_size=8,
  max_msgs=10)` — heap-backed msgq, **not** a static `K_MSGQ_DEFINE`.
- Return checked; on failure logs (`0x9a949`/`0x9b182`). Called once from the
  init path (caller @0x19718).

### g_dashboard_response_msgq  (REFERENCED — defined elsewhere)
- **Where used:** `send_response_data_to_msgqueue()` @0x47b1c and
  `send_response_data_to_ble()` @0x47ba8.
- **Access:** `k_msgq_put(*g_dashboard_response_msgq@0x2000392c, rec, K_NO_WAIT)`
  (Ghidra `FUN_000720d0(*0x2000392c, buf, 0, 0)`), 24-byte records.
- `0x2000392c` holds a **pointer** to the msgq; the `K_MSGQ_DEFINE` /
  `k_msgq_init` for it lives in the owning module (dashboard/UI), not here.
  Msg size in flight = 24 bytes (payload `<=0x14` + 4-byte header).

## IPC service endpoint (transport object, not a Zephyr sync primitive)

### g_ipc0_endpoint  (DEFINED / published)
- **Where:** `register_ipc_service_context()` @0x25d40
  (`recon/verified/src/register_ipc_service_context.c`).
- Writes the endpoint callback thunks into the context struct:
  `ctx[+0x60] = 0x00025b79`, `ctx[+0x64] = 0x00025ae9`, then publishes the
  context pointer as `g_ipc0_endpoint @0x20007a84`. Called once (caller @0x16eb8).
- **RX callback:** `ipc0_ept_recv` @0x25a48 (dispatches via the handler table at
  `g_ipc0_endpoint+4`).
- **TX:** `global_ipc_service_send` @0x25b78 → `ipc_service_send(ept@0x20007a78,
  data, len)` (Ghidra `FUN_0004cc50`). Transport globals:
  - `0x20007a80` — endpoint bound/ready flag (TX guarded on `== 1`).
  - `0x20007a78` — send endpoint handle passed to `ipc_service_send`.
  - `0x20007a74` — send retry counter (reset to 0 on success; >2 ⇒ reboot).
- **Fatal path:** after retries, `FUN_00074844(0x4000,0)` (delay) then
  `sys_reboot(1)` (Ghidra `FUN_0004c0a8`) — "sys reboot because ipc failed".

## Threads / semaphores / mutexes / work items
- **None defined by this module.** No `K_THREAD_DEFINE`, `k_sem_init`,
  `k_mutex_init`, or `k_work*_init` appears in any of the module's proven
  bodies. The module's only self-defined RTOS object is `g_uid_pipe` (msgq
  above); the IPC endpoint is a `ipc_service` transport object, and the
  response msgq is defined by the dashboard/UI module.
