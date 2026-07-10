# audio — DMIC/PDM capture, LC3 encode, voice streaming

## Responsibility
Captures audio from the on-glasses digital microphone (DMIC) through the nRF PDM
peripheral, encodes it with LC3, and streams the compressed voice blocks to the
phone over BLE. Used by Even-AI voice queries, QuickNote voice memos, and call
audio. Owns four message queues, the PDM driver instance and its DMA buffer slab,
the audio-codec register interface, and the mic power rail (shared with the IMU).

## Capture / stream pipeline
```
PDM hw ──▶ DMA buffer (mem_slab) ──▶ FUN_5ffa4 (PDM event) ──▶ ctrl msgq
   │                                                              │
   ▼                                                     FUN_5fa94 (read block)
dmic_stream_start / dmic_record_start                            │
   │                                                       LC3 encode
   │  g_dmic_msgq (200B×8)                              (lc3_encode_frame)
   │      ▲ enqueue_dmic / dequeue_dmic                          │
   │                                              sendAudioStram2Cache
   │                                                       ▼
   │                                          g_audio_msgq (208B×18)  ── cache
   │                                                       ▼
   │                         audioStreamFileManagerHandler (worker, drains queue)
   │                                                       │
   │  UID/file tagging: g_uid_pipe (8B×10),               ▼
   └─ g_file_msg_pipe (201B×30)      requestAudioInfoToApp ──▶ BLE ──▶ phone
```
Captured blocks are tagged with a UID (`enqueue_uid`/`dequeue_uid`) and a phone
file id (`enqueue_file`/`dequeue_file`) so the phone can reassemble them; the
phone ACKs received blocks and the glasses free them (`delVoiceBlock`; strings
"delete voice block num %d", "APP success received audio data").

## Key functions (name — role)
- `power_for_imu_and_mic` / `power_down_imu_and_mic` — mic power rail (shared with
  `imu_motion`). `check_device_readiness` gates capture start.
- `init_dmic_msgq` / `clean_dmic_msgq` / `get_dmic_msgq_count` / `enqueue_dmic` /
  `dequeue_dmic` — DMIC block queue (`g_dmic_msgq`) lifecycle + producer/consumer.
- `send_dmic_msg` — post a DMIC open/close control message ("received open/close
  dmic command").
- `dmic_stream_start` — bring up the PDM peripheral and begin continuous capture;
  `dmic_record_start` — begin a bounded record session.
- PDM driver glue (FUN_ names, semantics inferred from nrfx callees):
  `FUN_5fc7c` pdm (re)configure (init/uninit + rate math), `FUN_5fb30` pdm start,
  `FUN_5fb8c` pdm stop, `FUN_5ffa4` PDM buffer-done event handler (mem_slab
  alloc/free + msgq_put), `FUN_5fa94` read a filled block off the driver queue.
- `startAudioStreamRecord` / `stopAudioStreamRecord` / `delAudioStreamRecord` —
  record session lifecycle; `erase_audio_buffer` resets the cache flag
  (`0x20002404`).
- `sendAudioStram2Cache` / `getAudioMessageQueueCacheData` / `delVoiceBlock` /
  `drain_audio_msgq` — producer/consumer + flush over the audio record cache
  (`g_audio_msgq`).
- `audioStreamFileManagerHandler` — worker that drains `g_audio_msgq`, dispatches
  by record type (1/2/3/4), CRCs blocks, and drives the BLE transfer.
- `requestAudioInfoToApp` / `sendAudioStreamFileToApp` — notify/transfer to phone.
- `enqueue_uid`/`dequeue_uid`/`init_msgq_uid`, `enqueue_file`/`dequeue_file`/
  `file_subsystem_queue_init` — UID↔file-id bookkeeping queues.
- `audio_hw_lock_get_status_byte` / `audio_buf_release` — codec HW lock status;
  transport net_buf release.
- `burial_point_record_info_init` — usage-analytics counters for recording.
- `app_codec_lc3_test` — LC3 codec self-test. LC3 encode proper
  (`lc3_encode_frame` + `lc3_ltpf_*`, `lc3_ns`, `lc3_bits_accu_flush`, helpers
  `FUN_68b2c`/`FUN_6b364`) is a codec library the module drives, not glue.

## Owned data / structs
- `g_dmic_msgq` @ `0x20007b7c` — raw DMIC block queue (200B × 8).
- `g_audio_msgq` @ `0x20003890` — audio record/stream cache (208B × 18, static).
- `g_uid_pipe` @ `0x20006a38` — block→UID queue (8B × 10).
- `g_file_msg_pipe` @ `0x200079a0` — block→phone-file-id queue (201B × 30).
- `g_pdm_ctrl` @ `0x2000b008` — PDM driver instance; owns a mem_slab (`+0x14`) for
  DMA capture buffers and a data msgq (`+0x1c`/`0x2000b024`).
- `g_pending_event_word` @ `0x20007b78`, cache-reset flag @ `0x20002404`.
- Mic power rail (shared with `imu_motion`).
See `wiring.md` for exact `k_msgq_alloc_init` params and citations.

## Entry points (RTOS / cross-module callbacks, no in-module C caller)
- `audioStreamFileManagerHandler` @ `0x2f94c` — audio cache/file worker.
- `dmic_stream_start` @ `0x2f080` — PDM capture bring-up.
- `startAudioStreamRecord` @ `0x2f764`, `delAudioStreamRecord` @ `0x2f878`.
- `power_for_imu_and_mic` @ `0x15f80`, `check_device_readiness` @ `0x167b4`.
- `dequeue_uid` @ `0x18ff8`, `enqueue_file` @ `0x23514`, `dequeue_file` @ `0x235a4`.
- `sendAudioStreamFileToApp` @ `0x47bf8`, `burial_point_record_info_init`
  @ `0x4ab3c`.
- BLE command sinks: DMIC open/close and record commands arrive via
  `send_dmic_msg` / `dmic_record_start`, dispatched from `ble_proto`.

## Notes on the reference graph
The `api` set (functions called from *other* modules) is 55 addresses, but ~44 of
them are Zephyr kernel / driver primitives (`z_reschedule`, `k_msgq_*`,
`net_buf_*`, sys_heap `chunk_*`, `nrfx_clock/uarte/qspi`, `log_*`) that topic
clustering swept into "audio" via shared call edges — they are **not** audio's
public surface and are excluded from `audio.h`. The genuine cross-module audio API
is ~11 functions (see `audio.h` PUBLIC section). Of the 194 clustered functions,
the audio-specific bodies are the capture/cache/transport/codec set above; the
remainder are the mis-attributed kernel/driver helpers.
