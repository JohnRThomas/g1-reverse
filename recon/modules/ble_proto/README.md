# ble_proto — BLE application command dispatch

**Role.** Terminates the phone <-> glasses application protocol on top of the Nordic
SoftDevice GATT link. Inbound packets use the Even framing in
`../../application/app/src/even_protocol.h` (magic `0xAA`, 8-byte header,
2-byte service ID, trailing CRC-16/CCITT). This module decodes the 1-byte
command/opcode, routes to the right service handler, owns the BLE security
callbacks, and hosts the top-level dispatch thread that brings the rest of the
firmware's worker threads online. Outbound replies are fragmented and padded
before indication.

## Public API (cross-module, per reference graph — 16 functions)
Only these are called or address-taken from outside the module:

- `ble_process_req_dispatch(conn, packet, ctx)` @0x21460 — **core router.** Switches on
  `packet[0]`: PUT opcodes `0x01–0x27` -> `ble_process_put_req`; GET opcodes
  `0x29–0x45` -> `ble_process_get_req`; media/notify family `0x47–0x50` handled
  inline. Unknown opcodes fall through to the per-connection callback at `conn+0xc`.
- `subcontracing_send_data_pkcs7(dst, len, seq, buf)` @0x21a40 — outbound path: splits a
  reply into 0x11-byte fragments with PKCS#7 padding before indication.
- `FUN_00019b54(ctx, buf, len)` @0x19b54 — outbound-payload cipher wrapper (calls
  `FUN_0002af4c` with the `ctx-0x77c` crypto context; logs plaintext/ciphertext).
- `FUN_00071eac(...)` @0x71eac — **`k_thread_create` wrapper** (tid, stack, size,
  entry, args…, prio, options). The module's — and much of the firmware's —
  thread-spawn primitive.
- `FUN_00056a68(conn, val)` @0x56a68 — connection state-machine step (switch on
  state byte at `conn+0xd`).
- `disable_watchdog()` @0x2aeb4 — feed/stop the watchdog device instance @0x87cc8.
- `FUN_00025448()` @0x25448 / `FUN_0002efc0()` @0x2efc0 / `FUN_0003b800()` @0x3b800 —
  status/mode flag helpers (`0x20007a24`, `0x2000302f`, `0x20007b78`).
- `FUN_00085014(x)` @0x85014 — enable/trigger (`FUN_00064a88(x,1)`).
- `SlaveDoubleClickEventInject()` @0x48ad4 — injects a synthesized double-click on
  the slave lens (touch relay).
- BLE security callbacks (address-taken by the BT/SMP stack): `bt_send_enabled`
  @0x17e3c, `check_bonded_addr` @0x183e4, `pairing_failed` @0x18444,
  `auth_cancel` @0x1849c, `indicate_sc_cb` @0x18a38.

## Key internal functions
- `run_main_dispatch_thread(mode)` @0x2a65c — **main dispatch thread entry.** Inits a
  wait-list via `FUN_000864c2` (sys_dlist self-init), installs the watchdog
  (`FUN_0002ace0`, device @0x87cc8), then spawns the worker threads: always
  `FUN_00023a54` (2 threads + a semaphore); when `FUN_00032ee4()!=0` also
  `FUN_00032fe8`+`FUN_0003304c`; and, per `mode` byte, `FUN_00047ad0`/`FUN_00049638`.
- `ble_process_get_req(conn, packet, ctx)` @0x1a064 — read-side handlers
  (device info, settings, burial-point upload, etc.).
- `spec_ble_command_hook(a, b)` @0xef28 — special/vendor command interception
  hook, driven by the `FUN_00021d78` trampoline.
- `FUN_0007c20a(conn)` @0x7c20a — BLE RX worker loop: pulls frames (`FUN_00019c44`)
  into a 0xca-byte buffer and dispatches to the connection callback at `conn+0xc`.
- `FUN_0007c244` @0x7c244 — builds a 4-byte header and re-enters
  `ble_process_req_dispatch`.
- `onboarding_ble_process(...)` @0x42a64 — decodes `SVC_ONBOARDING` action packets.
- `FUN_00025ecc(dev)` @0x25ecc — recomputes display geometry/brightness from
  device params (called from `handle_attitude_trigger`).
- `check_is_release_mode` @0x86a06 — build/mode gate used by dispatch.
- Thread spawners `FUN_00023a54 / FUN_00032fe8 / FUN_0003304c / FUN_00047ad0 /
  FUN_00049638 / FUN_0007cb66` — thin `FUN_00071eac` wrappers (see `wiring.md`).

## State it owns / touches
- ~586 owned data symbols. Reassembly + command scratch fields inside the global
  `device_info_t` (accessed via `get_device_info()` / `get_device_type()`),
  notably the `+0x100c` media/notify sub-block and `display_command`/`sync_*` bytes.
- Log-level globals `g_log_level` (`0x2000230c`), `g_log_use_alt_sink`
  (`0x20007554`); status/flag words `0x20007a24`, `0x2000302f`, `0x20007b78`,
  `0x20007b50` (watchdog state), `0x20007a24`; display cache
  `0x200023f4/0x200023f8/0x20007a98/0x20007a9c`; slave-relay staging bytes.
- Worker-thread control blocks and stacks (see `wiring.md`), stored tids at
  `0x2000a090` and `0x2000a09c`; guard flag `0x20019ef1`.

## Entry points
- **Thread:** `run_main_dispatch_thread` @0x2a65c (the app-core "main dispatch" thread).
- **Registered callbacks:** the 5 BLE security callbacks above; the per-connection
  command callback at `conn+0xc`; `FUN_00021d78` (hook trampoline), `FUN_0003b800`,
  `SlaveDoubleClickEventInject`, `FUN_00025ecc`, `onboarding_ble_process`.
- **Dispatch table:** the opcode ranges inside `ble_process_req_dispatch`
  (a hand-rolled jump table keyed on `packet[0]`).

## Cross-module coupling
- Hands service payloads to `onboarding`, `translate`, `quicknote`, `analytics`
  (burial-point upload), and the display/audio pipelines.
- Fragment/relay writes feed `esb_sync` (L/R mirroring).
