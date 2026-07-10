# display — RTOS wiring (objects this module DEFINES)

Read out of the module's init / thread-creator / command-sender functions in the
proven code. Every param below is transcribed from a reconstructed body; the
citing function + address is given for each. Where a value could not be recovered
from a PROVEN body it is marked `unrecovered` (do not guess it downstream).

## Message queues

### g_display_msgq  @ 0x200038c4  — display command queue
- **msg_size = 24 bytes (0x18)** — CONFIRMED from every producer: each builds a
  24-byte record `memset(buf,0,0x18)` then `k_msgq_put(0x200038c4, buf, 0, 0)`.
  Record layout: `buf[0]=command`, `buf[2..3]=payload_len(u16)`, `buf[4..]=payload`
  (≤20 bytes).
- **count / ring buffer** = `unrecovered` — no runtime `k_msgq_init` (0x86420)
  call targets 0x200038c4, so it is a static `K_MSGQ_DEFINE`; the buffer symbol
  and depth live in a data section not reconstructed.
- **Producers (command byte):**
  - `display_reflash`        @0x4967c → cmd **2** (reflash, len+payload)
  - `display_close`          @0x497b0 → cmd **3** (close, optional payload)
  - `display_DelayClose`     @0x498c0 → cmd **4** (u32 delay ms)
  - `display_inputEvent`     @0x49938 → cmd **5** (key a,b)
  - `display_powerEvent`     @0x49a28 → cmd **7** power-on / **8** power-off
  - `display_MasterSendClose`@0x499b8 → close broadcast
  - `display_close_screen`   @0x49858 → cmd **1** (per-screen close) via display_close
- **Consumer:** display dispatch thread body `FUN_00049090` (drains 0x200038c4,
  branches on cmd byte, calls `display_reflash_handler`/`ui_refalsh_warp`).

## Threads

### display dispatch / reflash worker thread
- **Created in `FUN_00049638` @ 0x49638** (called from app init `FUN_0002a65c`
  @0x2a65c) via the thread-create wrapper `FUN_00071eac` @0x71eac.
- Recovered from `FUN_00049638` data-refs:
  - thread control block: **0x20004d18**
  - stack base:           **0x20028e68**
  - entry point:          **FUN_00049090** (`0x49091`, thumb)
  - thread handle stored to **g_display_thread_id @ 0x2000a09c**
- **stack_size / priority** = `unrecovered` (the `FUN_00071eac(tcb, stack, size,
  entry, prio…)` argument values are in `FUN_00049638`'s body, which is not yet
  reconstructed — only its data-refs are known).
- Work submission onto this thread: `submit_display_reflash_work` @0x4904c and
  `FUN_0004906c` @0x4906c call `FUN_00074554(g_display_thread_id, 0xfffffff0…)`
  (k_work-style submit; guard flag `g_display_reflash_pending @ 0x2001d446`).

### app-level display threads (created by the same app init, entries proven-named)
`FUN_0002a65c` @0x2a65c is the master app-init that spawns the app thread pool
(control blocks 0x200040d0…0x200046b8 stride 0xd8; stacks 0x20023c68, 0x20024868,
0x20024c68, 0x20025068, 0x20025468, 0x20025a68, 0x20026268, 0x20026a68). The
display-related entries it wires up:
- `display_dispatch_thread` @0x28bec — app display command thread (uses
  `cal_panel_canvas_coord`, `set_brightness_to_panel_reg_in_running`,
  `projector_reflash_and_release`).
- `key_event_thread`        @0x2955c — feeds `display_inputEvent`/`display_DelayClose`.
- `slave_display_thread`    @0x27cfe — slave-lens display thread (created
  elsewhere; drives the same panel/close/brightness API).
Per-entry stack/prio pairing is `unrecovered` (bodies of 0x2a65c not reconstructed).

## Semaphores (defined at display/brightness bring-up)

### sem @ 0x200079e4 — set in `spawn_flash_ops_and_brightness_threads` @0x23a54
- `z_impl_k_sem_init(0x200079e4, initial = 0, limit = 0x14 /*20*/)`  — CONFIRMED.
- Same function spawns two threads via `FUN_00071eac` (EXACT params from proven body):
  - flash-ops thread:  tcb **0x20003e38**, stack **0x20021968**, size **0x800**
    (2048), entry **0x23481**, prio **0xfffffff4 (-12)**.
  - brightness thread: tcb **0x20003f10**, stack **0x20022168**, size **0x1400**
    (5120), entry **0x23845**, prio **0xfffffff5 (-11)**.
- These sit at the flash/settings ↔ display-brightness boundary (the brightness
  thread @0x23845 drives `set_brightness_lum_base`/panel brightness); recorded
  here because they are co-spawned with the display sem and feed this module.

## Guard / state globals (not RTOS objects, but wiring-relevant)
- `g_display_reflash_pending` @ 0x2001d446 — work-pending latch.
- last-refreshed screen id      @ 0x2001d448 — read by `display_reflash_handler`.
- raster placement cache        @ 0x2000253c / 0x20002540 — `ui_raster_height_task`.
