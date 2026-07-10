# esb_sync — RTOS wiring

## Summary

**esb_sync defines NO Zephyr RTOS objects.** Every proven body in the module was
scanned for `K_THREAD_DEFINE` / `k_thread_*`, `K_MSGQ_DEFINE` / `k_msgq_*`,
`k_sem_*`, `k_mutex_*`, `k_work_*`, `k_timer_*`, `k_fifo/queue_*` and none appear
in any of the 18 member functions. There are therefore **no `K_*_DEFINE` params
to extract** from this module's init code.

Instead of a kernel object, master↔slave synchronisation is a **spin-polled
shared-SRAM mailbox**: the app core writes a staged frame into fixed SRAM
addresses, invokes a bound transceive callback, and busy-waits on a completion
byte. The threads that *drive* the pump and the push helpers are **owned by other
modules** (e.g. `key_event_thread`, `display_dispatch_thread`, `fuel_gauge_update`),
so their `K_THREAD_DEFINE` params belong to those modules' `wiring.md`, not here.

## Synchronisation primitives this module actually uses

These are the objects the wiring reconstruction must model for esb_sync. All are
raw shared-SRAM locations, not kernel handles. Addresses cited from proven bodies.

### Concurrency guards (busy/lock flags, spin-polled)
| Address | Meaning | Cited from (fn @addr) |
|---|---|---|
| `0x20018d8f` | `sync_to_slave` TX busy/lock flag; set during frame build, cleared at exit | `sync_to_slave` @0x26f74 |
| `0x20018d8c` | `FUN_00027448` TX lock; spin up to 2000 iters (`FUN_0007cb8e(1)` per iter) then bail | `FUN_00027448` @0x27448 |
| `0x20018d9c` | pending/in-flight counter drained before a new send (0x1f5 spin budget) | `sync_to_slave` @0x26f74 |
| `ctx+0x105a` | per-frame completion byte; sender spins until `== 2` (done) | `sync_to_slave` @0x26f74, `FUN_00027448` @0x27448 |

The "wait" primitive is `FUN_0007cb8e(1)` (1-tick busy-wait / yield, kernel
wrapper @0x7cb8e) and the timebase is `FUN_0007cb2c()` (uptime, int64 @0x7cb2c);
neither is a k_sem — they are used to build the spin loops above.

### Shared-SRAM mailbox (the master↔slave channel)
| Address | Role | Cited from |
|---|---|---|
| `0x20018c6f` | TX frame buffer: byte0 = opcode `4`, then header + payload (0x21 or 0xdc bytes) | `FUN_00027448` @0x27448 |
| `0x20018d6b` | ack/echo buffer (0x16 bytes) for cmd `1`; sender `memcmp`s it (`FUN_00086be4`) to confirm | `FUN_00027448` @0x27448 |
| `0x2000302b` | inbound sync opcode/status byte read by the master (matched against sent opcode) | `sync_to_slave` @0x26f74 |
| `0x2000302f` | inbound slave status byte (read when role==master) | `FUN_0002efa8` @0x2efa8 |
| `0x2000f6e6` | last-result store; written with return code at end of `sync_to_slave` | `sync_to_slave` @0x26f74 |
| `0x20018d98` | notification-sync sub-state flag | `FUN_000275fc` @0x275fc |
| `0x20018d82` | notification-sync retry counter (increments, gated `<= 9`) | `FUN_000275fc` @0x275fc |
| `0x20018d9f` | slave-role guard for the notification pump | `FUN_000275fc` @0x275fc |

### Bound callback (indirect dispatch, not a kernel object)
| Slot | Bound target | Cited from |
|---|---|---|
| `ctx+0x774` (`fp774_t`) | `spi_master_trans_data_tx_rx` (@0x262ac) — clocks the staged mailbox frame out; called as `(*ctx+0x774)(buf, len)` | `sync_to_slave` @0x26f74, `FUN_00027448` @0x27448 |

### Notification / message ring (owned data, not a k_msgq)
A hand-rolled record array with 0x1b4-byte stride — not a Zephyr `k_msgq`.
| Address | Role | Cited from |
|---|---|---|
| `0x20008dac` | ring control/head block; entry gated `+0x118!=0 && +0x116==0 && +0x115<4` | `FUN_00033b88` @0x33b88 |
| `0x20007bf4` | staging slot the dequeued 0x1b4-byte record is copied into | `FUN_00033b88` @0x33b88 |
| `0x20007dac` | ring entry base; state byte at `idx*0x1b4 + 0xd` | `FUN_00033bf0` @0x33bf0 |
| `*0x33c48` / `*0x33c44` | ring table base / cursor for id lookup (scan idx 10..19) | `FUN_00033c18` @0x33c18 |

## RX registration (input to wiring, resolved elsewhere)
`local_esbs_ipc_service_recv` (@0x15960) is the slave receive handler. Its
registration with the ESB/IPC service endpoint is performed in `ipc_core`'s init,
not in this module — the callback pointer is the wiring artifact to connect there.

## Threads that drive this module (defined in OTHER modules)
For completeness of the wiring graph, the external callers that invoke the push
API / pump (their `K_THREAD_DEFINE` params live in their own modules):
`key_event_thread`, `display_dispatch_thread`, `fuel_gauge_update`,
`check_work_mode`, `handle_attitude_trigger`, `ble_process_get_req`, and the
onboarding/DND/power/language settings paths.
