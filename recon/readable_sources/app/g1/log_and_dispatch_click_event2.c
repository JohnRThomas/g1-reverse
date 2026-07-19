#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002893c @ 0x0002893c
 * public-name: log_and_dispatch_click_event2
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   log_and_dispatch_click_event2            <= FUN_0002893c @ 0x0002893c
 *   set_click_dispatch_flag                  <= FUN_00032fd0 @ 0x00032fd0
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 * address symbols (name @ address):
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002893c @ 0x2893c (uncatalogued exact click-event entry). */

#include <stdint.h>

extern uint32_t debug_print(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t log_message(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t set_click_dispatch_flag(uint32_t);

uint32_t log_and_dispatch_click_event2(uint32_t unused0, uint32_t arg1,
                      uint32_t arg2, uint32_t unused3)
{
    uint32_t logger = *(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;

    (void)unused0;
    (void)unused3;
    if (logger != 0U) {
        debug_print(0x000a0a97U, arg1, arg2, logger);
    } else {
        log_message(0x000a0a97U, arg1, arg2, 0U);
    }
    return set_click_dispatch_flag(2U);
}
