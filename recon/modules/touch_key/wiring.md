# touch_key — RTOS wiring (objects this module DEFINES / uses)

Every param below is transcribed from a reconstructed (PROVEN) body; the citing
function + address is given. Values that could not be recovered from a proven
body are marked `unrecovered` — do not guess them downstream.

## Semaphores

### g_some_module_sem  @ 0x20007b1c  — touch-panel hardware-reset semaphore
- **Defined by** `some_module_sem_init` @0x2953c (PROVEN 300/300):
  `z_impl_k_sem_init(0x20007b1c, initial=0, limit=5, 0, 0)`
  → **initial count = 0, max count / limit = 5**.
  On success sets `g_some_module_init_done_flag @0x20018d8a = 1`.
- **Init call site:** invoked from `key_event_thread` @0x2955c (i.e. the sem is
  created during key/display bring-up, not inside touch_key's own `button_init`).
- **Giver:** `trigger_touch_key_hw_reset` @0x2a0c0 (PROVEN):
  `if (*(u8*)0x20018d8a != 0) thunk_FUN_00072880(0x20007b1c)` — k_sem_give,
  guarded by the init-done flag. Called by `touch_key_thread` @0x2a0d8 and
  `click_event_dispatch_loop` @0x28a1c whenever a fault gesture is decoded
  (after writing the reset code 1/2/3/4/6 to @0x20007b18).
- **Taker:** `unrecovered` — the thread that blocks on 0x20007b1c to perform the
  actual panel power-cycle is outside the proven set (no PROVEN `k_sem_take`
  targets 0x20007b1c in the reconstructed bodies).

### touch IRQ signal semaphore  @ device_info + 0xb0  (NOT module-static)
- Lives inside the `device_info` struct, so there is **no** `K_SEM_DEFINE` /
  `k_sem_init` owned by this module for it.
- **Giver (ISR):** `touch_key_gpio_isr` FUN_0001793c @0x1793c (PROVEN):
  on the touch edge sets `g_touch_key_irq_pending @0x20006a00 = 1` then
  `FUN_00072880(device_info + 0xb0)` (k_sem_give).
- **Taker (thread):** `touch_key_thread` @0x2a0d8 (PROVEN):
  `thunk_FUN_00072908(param_1 + 0xb0)` (k_sem_take), where `param_1` is the
  device_info base passed as the thread arg. Same in `click_event_dispatch_loop`
  @0x28a1c.
- init count / limit = `unrecovered` (initialised wherever device_info is built,
  not in a proven touch_key body).

## Threads

### touch_key_thread  @ 0x2a0d8  — input worker / gesture engine
- **No runtime creator** in the reference graph (`callers: []`) → statically
  declared via `K_THREAD_DEFINE`. Thread arg = device_info base (`param_1`);
  the body dereferences `param_1+0xb0` (IRQ sem), `param_1+0x1078` (RTC scratch),
  `param_1+0x105c`, `param_1+1` (suspend gate).
- **stack address / stack_size / priority / entry-name** = `unrecovered` — the
  `K_THREAD_DEFINE(...)` initialiser lives in a static data section not present
  in the reconstructed function bodies.
- Blocking primitives used in-body: `k_sem_take(param_1+0xb0)`,
  `k_msleep_ticks32768_a(5000 / 500)`.

### click_event_dispatch_loop  @ 0x28a1c  — sibling worker variant
- Also `callers: []` → static `K_THREAD_DEFINE`; same arg contract and the same
  `k_sem_take(param_1+0xb0)` / `k_msleep_ticks32768_a` usage. stack/prio/entry =
  `unrecovered`. (Topic-adjacent; not a member of the touch_key topic group but
  drives the same gesture actions + HW-reset sem.)

## Message queues
- **None defined by this module.** The ISR→thread handoff uses the flag
  `g_touch_key_irq_pending @0x20006a00` plus the per-thread semaphore
  (device_info+0xb0) and the latched edge byte `g_touch_key_irq_line_status
  @0x20019dac` — there is no `K_MSGQ_DEFINE` / `k_msgq_init` in any proven
  touch_key body.

## Mutexes / work items
- **None recovered.** No `k_mutex_init` / `k_work` / `k_timer` object is created
  in the proven touch_key bodies. (The timing helpers the module calls —
  `k_uptime_ticks_impl` @0x74f68 via FUN_00086690, `read_rtc_counter_ms`,
  `get_uptime_ms` — are read-only clock reads, not defined objects.)

## Summary of defined/owned RTOS objects
| kind | symbol / addr | params (proven) | defined in |
|------|---------------|-----------------|------------|
| semaphore | g_some_module_sem @0x20007b1c | init=0, limit=5 | some_module_sem_init @0x2953c |
| semaphore (in struct) | device_info+0xb0 | unrecovered | (external; used by ISR @0x1793c + thread @0x2a0d8) |
| thread | touch_key_thread @0x2a0d8 | stack/prio unrecovered (static K_THREAD_DEFINE) | — |
| thread | click_event_dispatch_loop @0x28a1c | stack/prio unrecovered (static K_THREAD_DEFINE) | — |
