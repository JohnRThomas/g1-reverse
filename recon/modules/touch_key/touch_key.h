/*
 * touch_key: capacitive touchpad + SW0 button input and gesture decode.
 *
 * Handles the temple capacitive touchpad and the SW0 hardware button on the
 * nRF5340 app core. A GPIO interrupt (touch_key_gpio_isr @0x1793c) sets the
 * pending flag g_touch_key_irq_pending @0x20006a00 and gives a per-thread
 * semaphore (device_info+0xb0); the dedicated worker touch_key_thread wakes,
 * calls handle_touch_key_irq to read the touch attribute (attr_store_get 0x4410)
 * into g_touch_key_irq_line_status @0x20019dac, then debounces and time-classifies
 * the edges into gestures -- single / double / triple click, long-press, hold,
 * factory-reset hold -- and fires the matching UI action (open dashboard, wake,
 * QuickNote, work-mode change, hardware reset, reboot). Actions are mirrored
 * master->slave over ESB. button_init sets up the GPIO/IRQ; check_sw0_status
 * polls the SW0 button (a 3+ sample low run starts the NFC/EEPROM link path).
 *
 * PUBLIC API below == exactly the reference-graph `api` set (functions called
 * from OTHER modules). Everything reachable only inside this module is declared
 * `static` in the corresponding .c and is intentionally NOT exported here.
 */
#ifndef G1_TOUCH_KEY_H
#define G1_TOUCH_KEY_H

#include <stdint.h>

typedef uint8_t u8;

/* ---- Public API (graph `api` set: 6 functions) -------------------------- */

/* touch_key_thread @0x2a0d8 -- input worker thread main (static K_THREAD_DEFINE
 * entry). Waits on the touch IRQ semaphore, debounces, time-classifies gestures,
 * dispatches actions, and triggers the touch-panel HW reset on fault. */
void touch_key_thread(char *arg);

/* handle_touch_key_irq @0x30af0 -- read the touch-controller attribute
 * (attr_store_get 0x4410) and latch the edge into g_touch_key_irq_line_status
 * (1 = press, 2 = release); applies flash config table when requested. */
void handle_touch_key_irq(int a, int b, int c);

/* on_triple_click @0x289e4 -- triple-click gesture action: enter/prepare the
 * system suspend/sleep state (or FUN_00028964 fallback). */
void on_triple_click(void);

/* FUN_000179ec @0x179ec -- touch GPIO-line (re)configure hook, invoked from the
 * panel power sequence (power_for_panel @0x15df4). Thin wrapper over the GPIO
 * pin-config helper FUN_00017768. [role inferred from caller + callee] */
void FUN_000179ec(void);

/* FUN_0007d0aa @0x7d0aa -- thin attribute-read wrapper over attr_store_get
 * (@0x302f8). Shared read helper used by the touch thread and other modules.
 * [generic util topic-grouped here] */
void FUN_0007d0aa(void);

/* FUN_00086690 @0x86690 -- uptime/tick read wrapper over k_uptime_ticks_impl
 * (@0x74f68). Shared timing helper used by the touch thread and other modules.
 * [generic kernel util topic-grouped here] */
uint32_t FUN_00086690(void);

/* ---- Internal (NOT public; declared static in their .c) ------------------
 * button_init                    @0x17a40  GPIO + IRQ bring-up
 * read_sw0_pin (FUN_00017e30)    @0x17e30  read SW0 line (-> FUN_000177c4)
 * check_sw0_status               @0x2a868  poll SW0; 3+ lows -> NFC/EEPROM link
 * handle_touch_single_click      @0x3707c  single-click UI action (widget/lang)
 * trigger_touch_key_hw_reset     @0x2a0c0  k_sem_give(g_some_module_sem)
 * FUN_00017768/177c4/17980/613c4           GPIO pin-config helpers
 * FUN_00025284                   @0x25284  clear init state byte @0x20018c69
 * ------------------------------------------------------------------------- */

#endif /* G1_TOUCH_KEY_H */
