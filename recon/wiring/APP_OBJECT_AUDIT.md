# CPUAPP object-value audit

This audit closes the three `UNRECOVERED` static message-queue dimensions in
`app_objects.c` and classifies its thread arguments without inventing fixed
addresses for runtime allocations.

## Static message queues — proven

Reset helper `0x00074b34` calls the firmware memcpy implementation with the
literals at `0x00074b50`: RAM start `0x20002000`, RAM end `0x20003c50`, and ROM
load start `0x000f8d64`. The NCS 2.5.1 `struct k_msgq` field order is documented
in `~/ncs251/zephyr/include/zephyr/kernel.h`: after wait-queue and spinlock
words, offsets `+0x0c/+0x10` are `msg_size/max_msgs` and offsets
`+0x14/+0x18` are `buffer_start/buffer_end`.

| Object | ROM initializer | Exact dimensions | Buffer-span cross-check |
|---|---:|---:|---:|
| `g_audio_msgq` @ `0x20003890` | `0x000fa5f4` | 204 × 18 | `0x2004c610-0x2004b7b8 = 3672` |
| `g_display_msgq` @ `0x200038c4` | `0x000fa628` | 24 × 30 | `0x2004cd60-0x2004ca90 = 720` |
| `g_quicknote_flash_msgq` @ `0x20003960` | `0x000fa6c4` | 6 × 20 | `0x200453b8-0x20045340 = 120` |
| `g_flash_store_cmd_msgq` @ `0x20003994` | `0x000fa6f8` | 6 × 5 | `0x2004533e-0x20045320 = 30` |

Thus all three formerly unknown depths are proven: display 30, QuickNote 20,
and settings/flash 5. The same initializers correct two stale message-size
assumptions: QuickNote and settings queues both copy six-byte slots. The audio
queue is 204 bytes, matching the 204-byte `audio_cache_record` in
`sendAudioStram2Cache`, not 208. `tools/app_object_data.py` reproduces the
decode directly from `app_update.bin`; its unit test locks these values.

## Thread arg0 values

The values below are exact call operands, but most are runtime pointers rather
than link-time constants:

| Spawn | Classification | Exact arg0 contract/evidence |
|---|---|---|
| ANCS worker `0x198cc` | derivable runtime | the current BLE connection/context passed by `ancs_main`; it is latched by entry `0x19950` |
| flash + brightness `0x23a54` | derivable runtime | device context forwarded from `run_main_dispatch_thread` |
| projector/settings `0x2201c` | derivable runtime | ANCS subcontext `device_context + 0x77c`; `ancs_ctx_init` installs `0x2201d` as that object's init hook and `main` invokes the hook with the subcontext |
| BLE workers `0x32fe8`, `0x3304c` | proven constant | both call `k_thread_create` with arg0 exactly `NULL` |
| proxy `0x47ad0`, display `0x49638` | derivable runtime | device context forwarded from `run_main_dispatch_thread` |
| eight-entry dispatch pool `0x2a65c` | proven operand | seven rows receive device context and entry `0x2a4f4` receives `NULL`; every TCB, stack, size, priority and conditional entry is recorded in `app_objects.c` |

The heap-allocated device context itself is intentionally still runtime-only:
`main` allocates `0x1188` bytes and passes that result into the dispatch tree.
Replacing it with a fixed SRAM address would be a guess and would contradict
the recovered allocation path.
