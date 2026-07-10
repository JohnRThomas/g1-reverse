# touch_key — touchpad & SW0 button input, gesture decode

## Responsibility
Physical input for the nRF5340 app core: the temple **capacitive touchpad** and
the **SW0 hardware button**. A touch GPIO interrupt latches a pending flag and
signals a per-thread semaphore; a dedicated worker thread reads the touch
controller, debounces, **time-classifies** the edges into gestures, and fires
the matching UI action (open dashboard, wake, QuickNote, work-mode change,
hardware reset, or reboot). Actions are mirrored master→slave over ESB. The
module also owns the touch-panel **hardware-reset** path and the SW0 poll that
kicks off the NFC/EEPROM link.

## Flow
```
touch GPIO edge ──► touch_key_gpio_isr (FUN_0001793c @0x1793c)
                      ├─ g_touch_key_irq_pending  @0x20006a00 = 1
                      └─ k_sem_give(device_info+0xb0)          (touch IRQ sem)
                                  │
      touch_key_thread @0x2a0d8 ──► k_sem_take(device_info+0xb0)
                                  ├─ handle_touch_key_irq @0x30af0
                                  │     attr_store_get(0x4410) → g_touch_key_irq_line_status @0x20019dac
                                  │        1 = press latch, 2 = release latch
                                  ├─ debounce + inter-edge timing classify
                                  │     ├ single click  → handle_touch_single_click @0x3707c
                                  │     ├ triple click  → on_triple_click @0x289e4 (suspend/sleep)
                                  │     ├ long / hold    → work-mode / QuickNote actions
                                  │     └ factory hold   → reset_all_usr_data / sys_reboot
                                  └─ on fault → trigger_touch_key_hw_reset @0x2a0c0
                                                  k_sem_give(g_some_module_sem @0x20007b1c)
SW0 poll ──► check_sw0_status @0x2a868 ──► read_sw0_pin (FUN_00017e30) ; 3+ lows → pt_nfc_eeprom_link_start
```

## Public API (graph `api` set — 6 functions)
| addr | name | role |
|------|------|------|
| 0x2a0d8 | `touch_key_thread` | input worker thread main; debounce + gesture classify + dispatch + HW-reset on fault (PROVEN) |
| 0x30af0 | `handle_touch_key_irq` | read touch attr (0x4410) → latch press/release into line_status; apply flash config (PROVEN) |
| 0x289e4 | `on_triple_click` | triple-click action → prepare system suspend/sleep (PROVEN) |
| 0x179ec | `FUN_000179ec` | touch GPIO-line (re)configure hook, called from `power_for_panel` @0x15df4 |
| 0x7d0aa | `FUN_0007d0aa` | thin attribute-read wrapper over `attr_store_get` @0x302f8 (generic util) |
| 0x86690 | `FUN_00086690` | uptime/tick read wrapper over `k_uptime_ticks_impl` @0x74f68 (generic util) |

> The graph does **not** list `button_init`, `check_sw0_status`, or
> `handle_touch_single_click` in the `api` set, so they are internal here (see
> below) even though display-side threads reach some of them — the reference
> ownership assigns those call sites to this unit.

## Internal / helper functions (deduced from callers+callees+data)
| addr | name | role |
|------|------|------|
| 0x17a40 | `button_init` | touch/SW0 GPIO + IRQ bring-up (888 B): wires FUN_00017768/177c4/17980/613c4 pin config, FUN_00025284, DEBUG_PRINT |
| 0x17768 | `FUN_00017768` | GPIO pin-config helper (→ FUN_0007e2ec/7e2fa register r/w) |
| 0x177c4 | `FUN_000177c4` | GPIO pin read/config helper (used by SW0 read + init) |
| 0x17980 | `FUN_00017980` | GPIO + interrupt/callback config helper (→ FUN_00083b1a) |
| 0x613c4 | `FUN_000613c4` | GPIO/status config helper (panel_power/touch_power log strings @0xf5dfc) |
| 0x25284 | `FUN_00025284` | 6-byte init helper: clears state byte @0x20018c69 |
| 0x17e30 | `read_sw0_pin` (FUN_00017e30) | 8-byte SW0 line read (→ FUN_000177c4) |
| 0x2a868 | `check_sw0_status` | poll SW0; count consecutive lows; >3 → `pt_nfc_eeprom_link_start` (PROVEN) |
| 0x3707c | `handle_touch_single_click` | single-click action: set widget state + dashboard default language (PROVEN) |
| 0x2a0c0 | `trigger_touch_key_hw_reset` | give `g_some_module_sem` if init-done flag set (PROVEN) |

Sibling (not in this topic group but same gesture engine):
`click_event_dispatch_loop` @0x28a1c — a second, near-identical worker variant
(also no runtime caller; static thread entry) that dispatches
`on_triple_click`, `handle_touch_key_irq`, `trigger_touch_key_hw_reset`.

## Owned data / structs
- `g_touch_key_irq_pending`      @0x20006a00 — ISR→thread pending flag.
- `g_touch_key_irq_line_status`  @0x20019dac — latched edge (1=press, 2=release).
- `g_some_module_sem`            @0x20007b1c — touch HW-reset semaphore (see wiring.md).
- `g_some_module_init_done_flag` @0x20018d8a — set once the sem is initialised.
- init state byte                @0x20018c69 — cleared by FUN_00025284.
- touch panel reset request code @0x20007b18 — thread writes 1/2/3/4/6 before HW reset.
- per-thread touch IRQ semaphore embedded at `device_info + 0xb0` (given by ISR,
  taken by the thread — lives in the device_info struct, not module-static).
- n_owned_data reported by the graph: **183** data symbols.

## Entry points
- **Thread main:** `touch_key_thread` @0x2a0d8 (static `K_THREAD_DEFINE`, no
  runtime creator in the graph). Sibling variant `click_event_dispatch_loop`
  @0x28a1c likewise.
- **GPIO ISR:** `touch_key_gpio_isr` (FUN_0001793c @0x1793c) — sets
  `g_touch_key_irq_pending` and gives the per-thread touch IRQ semaphore.
- **Callbacks reachable from other modules:** `handle_touch_single_click`
  @0x3707c (from `slave_display_thread` @0x27cfe), `FUN_000179ec` @0x179ec
  (from `power_for_panel` @0x15df4).
