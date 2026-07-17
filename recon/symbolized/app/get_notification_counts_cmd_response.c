#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033a5c @ 0x00033a5c
 * public-name: get_notification_counts_cmd_response
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_notification_counts_cmd_response     <= FUN_00033a5c @ 0x00033a5c
 * address symbols (name @ address):
 *   rodata_a7cd6                             @ 0x000a7cd6
 *   rodata_a7cf4                             @ 0x000a7cf4
 *   rodata_a829f                             @ 0x000a829f
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00033a5c @ 0x33a5c.
 * Readable identity: get_notification_counts_cmd_response.
 * Exact standalone extent: 0x4c bytes; literal pool begins at 0x33aa8.
 */

#include <stdint.h>

extern int log_message(uintptr_t format, ...);
extern int debug_print(uintptr_t format, ...);
#define debug_print debug_print

uint32_t get_notification_counts_cmd_response(const uint8_t *notification,
                      uint8_t *unread_count)
{
    int32_t level;
    uint32_t sink;
    uint8_t count;

    if (notification == 0 || unread_count == 0) {
        level = *(volatile uint32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/;
        if (level > 1) {
            sink = *(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
            if (sink == 0U) {
                log_message(((unsigned long)&rodata_a7cd6) /*=0xa7cd6*/, ((unsigned long)&rodata_a829f) /*=0xa829f*/);
            } else {
                debug_print(((unsigned long)&rodata_a7cd6) /*=0xa7cd6*/, ((unsigned long)&rodata_a829f) /*=0xa829f*/);
            }
        }
        return 0;
    }

    count = notification[0xdd];
    *unread_count = count;
    level = *(volatile uint32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    if (level > 2) {
        sink = *(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (sink == 0U) {
            log_message(((unsigned long)&rodata_a7cf4) /*=0xa7cf4*/, ((unsigned long)&rodata_a829f) /*=0xa829f*/, count);
        } else {
            debug_print(((unsigned long)&rodata_a7cf4) /*=0xa7cf4*/, ((unsigned long)&rodata_a829f) /*=0xa829f*/, count);
        }
    }
    return 1;
}
