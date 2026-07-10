# audio — RTOS objects DEFINED by this module

Read out of the module's init functions in the parity-proven bodies. All four
message queues are created at **runtime** with `z_impl_k_msgq_alloc_init(&q,
msg_size, max_msgs)` (dynamic buffer), except `g_audio_msgq` which is a **static**
`K_MSGQ` (no init call — used directly). The module defines **no thread and no
sem/mutex of its own**: its two workers run as callbacks driven by other threads.

## Message queues

| Global | Addr | msg_size | max_msgs | Defined in (addr) | Role |
|---|---|---|---|---|---|
| `g_dmic_msgq` | `0x20007b7c` | 200 | 8 | `init_dmic_msgq` @ `0x2ebd8` | raw DMIC/PCM blocks from capture |
| `g_audio_msgq` | `0x20003890` | 208 | 18 | *static K_MSGQ* (no init) | audio record/stream cache (typed 208-byte records) |
| `g_uid_pipe` | `0x20006a38` | 8 | 10 | `init_msgq_uid` @ `0x18e04` | captured-block → UID pairing |
| `g_file_msg_pipe` | `0x200079a0` | 201 (0xc9) | 30 (0x1e) | `file_subsystem_queue_init` | captured-block → phone file-id pairing |

Exact init calls:
- `init_dmic_msgq` @ `0x2ebd8`: `z_impl_k_msgq_alloc_init(0x20007b7c, 200, 8)`.
  Torn down by `clean_dmic_msgq` @ `0x2ec1c` via `k_msgq_cleanup(0x20007b7c)`.
- `init_msgq_uid` @ `0x18e04`: `z_impl_k_msgq_alloc_init(0x20006a38, 8, 10)`.
- `file_subsystem_queue_init`: `z_impl_k_msgq_alloc_init(0x200079a0, 0xc9, 0x1e)`.
- `g_audio_msgq` @ `0x20003890`: never alloc-init'd — a compile-time `K_MSGQ_DEFINE`.
  Size/depth inferred from usage: producers stage 208-byte records
  (`startAudioStreamRecord`/`sendAudioStram2Cache`, buffers `[208]`, payload
  `0xcc`), and `sendAudioStram2Cache` @ `0x2f6b0` rejects when the used-count word
  at `+0x24` equals `0x12` (18) → `max_msgs = 18`. Drained by
  `audioStreamFileManagerHandler` @ `0x2f94c` and `drain_audio_msgq` @ `0x2f688`
  (loops `k_msgq_get` over the `+0x24` used count).

## PDM / DMIC driver instance (nrfx PDM)

Not a `K_*_DEFINE`; a runtime driver control block at **`0x2000b008`** (call it
`g_pdm_ctrl`) configured during `dmic_stream_start`. Fields observed in the PDM
event handler `FUN_5ffa4` @ `0x5ffa4` and reader `FUN_5fa94` @ `0x5fa94`:
- `+0x14` → pointer to a **`k_mem_slab`** supplying the double-buffered PDM DMA
  capture buffers (`k_mem_slab_alloc` / `k_mem_slab_free`).
- `+0x1c` / used-count `+0x24` (`0x2000b024`) → a **`k_msgq`** the event handler
  posts filled capture blocks into (`k_msgq_put(0x2000b024, …)`), read back by
  `FUN_5fa94` (`k_msgq_get(ctrl+0x1c, …)`).
- Hardware programmed via `nrfx_pdm_init`/`nrfx_pdm_uninit` (`FUN_5fc7c`
  @ `0x5fc7c`), `nrfx_pdm_start` (`FUN_5fb30`), `nrfx_pdm_stop` (`FUN_5fb8c`),
  `nrfx_pdm_buffer_set` (in `FUN_5ffa4`).

The mem_slab and its msgq are owned by the Zephyr DMIC/nrfx driver layer and
pointed to from this instance; they are configured, not statically defined, here.

## Threads / sems / mutexes

None defined by this module. The two audio workers are **not** `K_THREAD_DEFINE`d:
- `audioStreamFileManagerHandler` @ `0x2f94c` — polled/called worker that drains
  `g_audio_msgq` and drives the BLE file transfer.
- The DMIC capture path is interrupt/callback-driven through `g_pdm_ctrl`.

Wakeups are signalled with `FUN_72880` (`0x72880`, a `k_poll`/scheduler
signal-raise): `startAudioStreamRecord`/`sendAudioStram2Cache` raise on
`g_app_language_msgq` (`0x200079e4`) after enqueue, and `dmic_record_start`
@ `0x3b78c` raises on a per-device event word (`get_device_info()+0x68`) and sets
`g_pending_event_word` @ `0x20007b78`.
