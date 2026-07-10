# Wiring GAPS — WS2 kernel-object inventory vs reconciled definitions

Cross-check of the WS2 "reliable" kernel-object inventory
(`ws2_reliable.json`, 18 objects located by SRAM base address + type guess +
referencing functions) against the RTOS-object definitions reconciled into
`recon/wiring/app_objects.c` (harvested from every `recon/modules/*/wiring.md`).

Matching is by **SRAM control-block address**. WS2 addresses live mostly in the
low driver/kernel `.bss` band (0x20002xxx–0x2000cxxx); the app-defined kernel
objects live higher (0x20003xxx–0x20007xxx), so the two sets barely overlap.

## Counts

### WS2 inventory (18 objects) by guessed type
| type (WS2 guess)   | n |
|--------------------|---|
| k_work             | 5 |
| virtio_dispatch    | 2 |
| pwm_nrfx_config    | 2 |
| gpio_driver_api    | 1 |
| log_backend_api    | 1 |
| write_data         | 1 |
| spi_nrfx_config    | 1 |
| spi_context        | 1 |
| virtqueue          | 1 |
| k_mem_slab         | 1 |
| k_work_delayable   | 1 |
| k_mutex            | 1 |
Of these, the classic app-relevant kernel objects WS2 flags are:
6× k_work (incl. 1 delayable), 1× k_mutex, 1× k_mem_slab. The rest are
driver/transport structs (gpio/spi/pwm/log/virtio/virtqueue) or generic buffers.

### Reconciled definitions in app_objects.c by type
| type          | n (unique addr) |
|---------------|-----------------|
| K_MSGQ        | 9  |
| K_THREAD (concrete params) | 8 |
| K_THREAD (static, params UNRECOVERED) | >=5 |
| K_SEM         | 2  (+2 in-struct, external) |
| K_MUTEX       | 1  (+1 external Even-AI) |
| K_TIMER       | 1  |
| K_WORK        | 0  |

## The ONE address match

| addr | WS2 guess | reconciled definition | verdict |
|------|-----------|-----------------------|---------|
| **0x20003d28** | `pwm_nrfx_config` (fn FUN_0002201c) | `K_TIMER_DEFINE g_projector_timer` — `k_timer_init(0x20003d28, expiry=0x19ff0, stop=0)` @ FUN_0002201c (flash_store) | **MATCH.** WS2 mis-typed it as pwm config, but the referencing fn (FUN_0002201c) and address prove it is the projector k_timer. WS2 type guess is WRONG here; the wiring definition is authoritative. |

Near-miss worth noting (NOT an address match): WS2 `0x20003868` (span 96,
guessed `spi_context`, fns FUN_0002f688/FUN_0002f758/delAudioStreamRecord). Its
96-byte span 0x20003868..0x200038c8 overlaps the audio `g_audio_msgq`
control block @0x20003890, and FUN_0002f758 is exactly g_audio_msgq's used-count
accessor. Likely the same audio-record region, but WS2 anchored a different base
and type, so it is not counted as a clean match — flagged for review.

## GAP A — WS2 objects with NO matching definition (wiring gaps to CHASE)

17 of 18 WS2 objects have no definition in any module `wiring.md`. The ones that
are genuine app kernel objects (not driver structs) are the priority chase list:

| addr | WS2 type | referencing fns | why it's a gap |
|------|----------|-----------------|----------------|
| **0x20004df0** | k_work | FUN_0004a4b4, FUN_0004a4d0 | dashboard/session area (0x4a4b4 is in dashboard wiring as a k_uptime marker) — a real k_work with no k_work_init found. |
| **0x20002c30** | k_work | FUN_000659cc/d8, FUN_00068204/40 | k_work, no definition; low-band (likely BLE/GATT subsys). |
| **0x20006448** | k_work | FUN_0005a570, FUN_0005caa4 | k_work, no definition; sits next to WS2 k_mutex 0x20006380. |
| **0x20009fc0** | k_work | FUN_0003629c, FUN_00047ab8 | k_work, no definition; 0x47ab8 is near ble_worker_5 spawn (0x47ad0). |
| **0x2000cc24** | k_work | FUN_000778f4, FUN_00077e4c, FUN_00078570/98 | k_work, no definition; high-band (0x76xxx-0x78xxx = second virtio/ipc cluster). |
| **0x20002144** | k_work_delayable | FUN_00053530, FUN_00054ce0 | delayable work, no definition; kernel/timeout band. |
| **0x20006380** | k_mutex | FUN_0005a250, FUN_0005a28c | a k_mutex NOT captured by any wiring.md (g_ext_flash_mutex is 0x20007b54; this is a distinct one). CHASE its init. |
| **0x20002000** | k_mem_slab | FUN_00052f68, FUN_000549ec, ... | k_mem_slab — audio/wiring.md mentions an unaddressed PDM k_mem_slab (g_pdm_ctrl+0x14); this may be it, but the address was never pinned. |

Driver/transport structs WS2 flags (expected to have no app K_*_DEFINE — NOT
wiring gaps, listed for completeness): 0x20002bac gpio_driver_api,
0x2000ad1c log_backend_api, 0x20002404 & 0x200037f0 virtio_dispatch,
0x2000253c write_data, 0x20004948 spi_nrfx_config, 0x20003868 spi_context,
0x2000ab7c virtqueue, 0x20004ce0 pwm_nrfx_config (display brightness PWM).

## GAP B — definitions with NO WS2 object

Every reconciled K_MSGQ / K_SEM / K_MUTEX / K_TIMER / K_THREAD except the timer
0x20003d28 is absent from the WS2 inventory. This is expected: WS2 scanned the
low driver/kernel band and did not enumerate the app object band. Listed so the
absence is not mistaken for a contradiction:

- **Message queues (9):** g_ancs_msgq 0x20006a6c, g_dmic_msgq 0x20007b7c,
  g_audio_msgq 0x20003890, g_uid_pipe 0x20006a38, g_file_msg_pipe 0x200079a0,
  g_debug_msg_pipe 0x2000751c, g_display_msgq 0x200038c4,
  g_flash_store_cmd_msgq 0x20003994, g_quicknote_flash_msgq 0x20003960.
- **Semaphores (2):** g_app_language_sem 0x200079e4, g_some_module_sem 0x20007b1c.
- **Mutex (1):** g_ext_flash_mutex 0x20007b54.
- **Threads (8 concrete):** tcbs 0x20003c50, 0x20003e38, 0x20003f10,
  0x20004870, 0x20004798, 0x20004c08, 0x20004d18, 0x20003d60. (WS2 anchors on
  the object payload, not the TCB, and did not enumerate any of these.)

None of these are contradictions; they are coverage gaps in WS2, not wiring
errors. No reconciled definition is refuted by WS2.

## Takeaways for the wiring reconstruction
1. **k_work is the real hole.** WS2 finds 6 k_work/delayable objects; the module
   wiring docs define ZERO k_work. Chase init sites for 0x20004df0, 0x20002c30,
   0x20006448, 0x20009fc0, 0x2000cc24, 0x20002144.
2. **A second k_mutex (0x20006380)** exists beyond g_ext_flash_mutex — find its
   k_mutex_init and owning subsystem.
3. **Confirm the k_mem_slab (0x20002000)** against the audio PDM ctrl (+0x14).
4. **0x20003d28 type fix:** it is a k_timer, not pwm_nrfx_config — correct the
   WS2 type guess.
