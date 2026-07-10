# esb_sync — Left/Right lens synchronisation

**Role.** G1 is two independent nRF5340 lenses (a *master* and a *slave*). The
master mirrors user-visible and system state to the slave so both displays and
settings stay consistent. The transport is **not** a Zephyr message queue: the
app core stages a frame into a **shared-SRAM mailbox** and hands it off through a
transceive callback bound at `ctx+0x774` (`spi_master_trans_data_tx_rx`), then
**spin-polls** a completion byte (`ctx+0x105a`) with 1-tick busy-waits. Every
frame is **sequence-numbered** (`ctx+0xda`); the slave RX entry demuxes inbound
frames against that counter. Role, channel and peer addressing are read from the
global sync context returned by `FUN_000167a8()` (`device_info_t`:
`device_type`, `esb_channel_number`, `mac_addresses`). At bring-up this module
logs `--role:%d --mode:%d, esb_channel %d --ret:%d esb_master_addr .. esb_slave_addr ..`.

## Key functions

### Public API (cross-module `api` set — 12)
- `local_esbs_ipc_service_recv(ctx, buf)` — **slave-side RX entry**. Copies the
  inbound frame, compares its seq (`buf` byte vs `ctx+0xda`) and emits
  `slave recv same package` / `... loss package` / `slave recv suspend/resume
  package` / `slave recv up/down recving`, then applies the payload locally.
- `spi_master_trans_data_tx_rx(dev, tx, txlen, rx, rxlen)` — **low-level SPI
  full-duplex transfer**; the actual bus clock-out for a staged mailbox frame.
  Bound into the context at `ctx+0x774` and invoked by the push routines.
- `sync_to_slave(payload, len, seq, flags)` — **generic single-frame push**.
  Builds a 0x21-byte frame (`buf120`), waits out the busy flag `0x20018d8f`,
  handles per-opcode timeouts (500/3000/5000 ms) and retry.
- `FUN_00027448(ctx, cmd, payload, len)` — **segmented / large-frame push**.
  Writes opcode 4 + up to 0xdc bytes into the TX mailbox `0x20018c6f`, sends
  0xda-byte chunks for cmd `0xb`/`0xc`, and for cmd `1` echoes/acks via
  `0x20018d6b` (0x16-byte compare). Spin-waits on `ctx+0x105a`.
- `FUN_000286f8(mode)` — **master sync pump / dispatcher**. Drives one sync tick:
  calls `sync_to_slave`, `FUN_00027448`, `FUN_000275fc`,
  `sync_message_signal_to_slave`, `FUN_0002efa8`, `FUN_0007ce60`,
  `update_persist_task_status`. This is the module's main entry point.
- `sync_message_signal_to_slave(a, b, c)` — signalling / event wrapper over
  `sync_to_slave` (control messages rather than bulk state).
- State-specific push helpers (each frames one subsystem's state):
  - `not_disturb_sync_data(buf, len, sub_step)` — DND settings
    (`slave sync not_disturb sub_step %d`).
  - `onboarding_sync_data(buf, len, sub_step)` — onboarding step
    (`SYNC onboarding action_cmd %d and sub_step %d to slave`).
  - `SendPowerInfoToSlave(dev)` — battery / power state.
  - `SendSystemLanguageInfoToSlave(dev)` — system language selection.
- `FUN_0007ce60(mode, ...)` — **transfer/display-sync context reset**: zeroes the
  recv/ack bytes (`ctx+0xe9,0xea,0xcc..0xcf`) and the 399-byte panel buffer at
  `*(ctx+0x100c)+8`; `mode` selects clear-vs-init of the display packet header.
- `FUN_0007d230(seq)` — **set/restore the sync sequence** field `ctx+0xd0`; used
  to roll the seq back on failure or commit it on success.

### Internal helpers (not public api)
- `runtime_info_sync(info)` — runtime/status snapshot push (cross-topic callers
  exist but the module partition keeps it internal).
- `FUN_000275fc()` — notification/message **delivery pump step**: dequeues a
  pending ring entry, branches on role, issues `sync_to_slave`/`FUN_00027448`
  (opcode `0xa`/`0xb`/`0xc`), advances the retry counter `0x20018d82`.
- `FUN_0002efa8()` — read inbound slave status byte from mailbox `0x2000302f`
  (master role only).
- `FUN_00033b88()` — dequeue next pending notification/message record from the
  ring at `0x20008dac`; copies the 0x1b4-byte entry to staging `0x20007bf4`.
- `FUN_00033bf0(idx, state)` — set the delivery-state byte of ring entry `idx`.
- `FUN_00033c18(id)` — find a ready ring-entry slot by `id` (scan 10..19).

## State it owns / touches
- The **global sync context** (`device_info_t` / `master_sync_pkg`) returned by
  `FUN_000167a8()`: role/mode, seq counter (`+0xda`), packet headers
  (`+0xc9..+0xe4`), the display packet buffer pointer (`+0x100c`), the bound
  transceive callback (`+0x774`), and the completion flag (`+0x105a`).
- **Shared-SRAM mailbox registers** used as the actual master↔slave channel — see
  `wiring.md` for the full address map (TX buffer `0x20018c6f`, inbound status
  `0x2000302b`/`0x2000302f`, busy/lock flags `0x20018d8f`/`0x20018d8c`, ack echo
  `0x20018d6b`, last-result `0x2000f6e6`, retry/sub-step state
  `0x20018d82`/`0x20018d98`/`0x20018d9f`).
- The **notification/message ring** at `0x20008dac` / `0x20007dac` (0x1b4-byte
  entries) that `FUN_00033b88/bf0/c18` and `FUN_000275fc` operate on.
- Does not own persistent storage; DND/language values are persisted by
  `flash_store`.

## Entry points
- **RX callback:** `local_esbs_ipc_service_recv` — registered with the ESB IPC
  service (slave side).
- **Transceive callback:** `spi_master_trans_data_tx_rx` — bound at `ctx+0x774`,
  called indirectly by every push routine.
- **Sync pump:** `FUN_000286f8` — the periodic master push driver (no in-module
  caller; invoked by the owning task/work loop).
- **TX API:** the `*_sync_data` / `Send*ToSlave` / `*_signal_to_slave` helpers,
  called from `ble_proto`, `system`, `onboarding`, key/display threads and the
  settings paths (external callers include `key_event_thread`,
  `display_dispatch_thread`, `fuel_gauge_update`, `ble_process_get_req`,
  `handle_attitude_trigger`, `check_work_mode`).

## Cross-module coupling
- The staged `*_sync_pkg` structs are the same payloads the display pipeline
  consumes and that the net core mirrors; the transport itself is the shared-SRAM
  mailbox rather than a Zephyr IPC object.

## Wiring note
This module **defines no Zephyr RTOS objects** (no `K_THREAD_DEFINE`,
`K_MSGQ_DEFINE`, sem/mutex/work) of its own — it is a spin-polled shared-SRAM
mailbox transport driven by threads that live in other modules. See `wiring.md`.
