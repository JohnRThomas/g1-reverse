#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002685c @ 0x0002685c
 * public-name: low_speed_peripheral_dispatch_thread_for_test
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   handle_box_placement_event               <= FUN_00025528 @ 0x00025528
 *   low_speed_peripheral_dispatch_thread_for_test <= FUN_0002685c @ 0x0002685c
 *   watchdog_feed_retry                      <= FUN_0002ae84 @ 0x0002ae84
 *   disable_watchdog                         <= FUN_0002aeb4 @ 0x0002aeb4
 *   mark_master_or_low_battery_flag          <= FUN_0002efc0 @ 0x0002efc0
 *   set_click_dispatch_flag                  <= FUN_00032fd0 @ 0x00032fd0
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   k_msleep                                 <= FUN_0007cb8e @ 0x0007cb8e
 * address symbols (name @ address):
 *   rodata_28000                             @ 0x00028000
 *   rodata_87d70                             @ 0x00087d70
 *   rodata_9fc8b                             @ 0x0009fc8b   [INLINED -- G6 literal batch]
 *   rodata_9fc99                             @ 0x0009fc99   [INLINED -- G6 literal batch]
 *   rodata_a19e5                             @ 0x000a19e5   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_flash_crc_active_flag                  @ 0x2000302c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_flash_crc_skip_watchdog_flag           @ 0x20018d90
 */
/* Full reconstruction FUN_0002685c @ 0x2685c, exact extent 176 bytes.
 * CFG_VERIFY_PREFIX_FIRST CFG_VERIFY_PREFIX_K=150 */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern void handle_box_placement_event(void);
extern void watchdog_feed_retry(void);
extern int disable_watchdog(void);
extern unsigned int mark_master_or_low_battery_flag(void);
extern void set_click_dispatch_flag(long);
extern unsigned long sys_reboot(long);
extern int32_t k_msleep(int32_t);
extern void fuel_gauge_update(uintptr_t, uint32_t);
extern void wait_for_event(uint32_t, uint32_t);

void low_speed_peripheral_dispatch_thread_for_test(uintptr_t context)
{
    volatile int *const log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    if (*log_level > 1) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
            debug_print(((unsigned long)"%s(): #enter\n") /*=0x9fc8b*/, ((unsigned long)"low_speed_peripheral_dispatch_thread_for_test") /*=0xa19e5*/);
        else
            log_message(((unsigned long)"%s(): #enter\n") /*=0x9fc8b*/, ((unsigned long)"low_speed_peripheral_dispatch_thread_for_test") /*=0xa19e5*/);
    }

    *(volatile uint16_t *)(context + 0xfc0) = 0;
    *(volatile uint16_t *)(context + 0xfc4) = 0x8000;
    uint32_t count = 0;
    for (;;) {
        if (*(volatile uint8_t *)(context + 1) == 1) {
            disable_watchdog();
            set_click_dispatch_flag(0);
            mark_master_or_low_battery_flag();
            if (count > 0x22) {
                if (*log_level > 0) {
                    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)
                        debug_print(((unsigned long)"%s(): reboot because dfu exceed time\r\n\n") /*=0x9fc99*/, ((unsigned long)"low_speed_peripheral_dispatch_thread_for_test") /*=0xa19e5*/);
                    else
                        log_message(((unsigned long)"%s(): reboot because dfu exceed time\r\n\n") /*=0x9fc99*/, ((unsigned long)"low_speed_peripheral_dispatch_thread_for_test") /*=0xa19e5*/);
                }
                for (;;) {
                    k_msleep(500);
                    uintptr_t result = sys_reboot(1);
                    log_message(result);
                }
            }
            ++count;
            wait_for_event(((unsigned long)&rodata_28000) /*=0x28000*/, 0);
        } else {
            handle_box_placement_event();
            if (*(volatile uint8_t *)((unsigned long)&g_flash_crc_active_flag) /*=0x2000302c*/ == 0)
                disable_watchdog();
            else if (*(volatile uint8_t *)((unsigned long)&g_flash_crc_skip_watchdog_flag) /*=0x20018d90*/ == 0)
                watchdog_feed_retry();
            fuel_gauge_update(((unsigned long)&rodata_87d70) /*=0x87d70*/, 0);
            wait_for_event(0x8000, 0);
        }
    }
}
