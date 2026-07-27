#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032420 @ 0x00032420
 * public-name: aging_mode_thread
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_click_dispatch_flag                    @ 0x20019ef2
 */
/* Reconstructed aging_mode_thread @ 0x00032420; raw identity FUN_00032420.
 * Exact reachable extent: 0x00032420..0x000324a1 (0x82 bytes); 0x324a2 is
 * alignment and the literal pool starts at 0x324a4. CFG_VERIFY_PREFIX_FIRST
 */
#include <stdint.h>
#include "../../../headers/g1_log.h"

/* FUN_00019c70 @ 0x00019c70 */
extern uint32_t k_uptime_get_4(void);     /* FUN_0007d12e */
extern void k_msleep_ticks32768_b(int); /* FUN_0007d14a */
extern void set_display_page_index(uint32_t); /* FUN_000369dc */
extern void advance_display_page_index(void); /* FUN_000369f8 */
extern void check_sw0_status(void);           /* FUN_0002a868 */

void aging_mode_thread(void)
{
    volatile uint8_t *const mode = (volatile uint8_t *)((unsigned long)&g_click_dispatch_flag) /*=0x20019ef2*/;
    for (;;) {
        if (*mode == 1) {
            if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
                if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
                    log_message(0x000a7388u, 0x000a75b0u);
                else
                    debug_print(0x000a7388u, 0x000a75b0u);
            }
            uint32_t start_seconds = k_uptime_get_4() / 1000u;
            while (*mode == 1) {
                set_display_page_index(0);
                k_msleep_ticks32768_b(3000);
                set_display_page_index(2);
                k_msleep_ticks32768_b(1000);
                uint32_t elapsed = k_uptime_get_4() / 1000u - start_seconds;
                log_message(0x000a73c8u, elapsed);
            }
        }
        if (*mode == 2) {
            advance_display_page_index();
            *mode = 0;
        }
        check_sw0_status();
        k_msleep_ticks32768_b(100);
    }
}
