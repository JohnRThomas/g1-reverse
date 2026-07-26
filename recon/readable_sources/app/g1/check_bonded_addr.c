#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000183e4 @ 0x000183e4
 * public-name: check_bonded_addr
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9a46f                             @ 0x0009a46f   [INLINED -- G6 literal batch]
 *   rodata_9b108                             @ 0x0009b108   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_active_conn                       @ 0x20006ab8
 *   g_bonded_count                           @ 0x20007514
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction check_bonded_addr @ 0x183e4. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern void format_bt_addr_str(const void *connection, char description[36]);

void check_bonded_addr(const void *connection)
{
    char description[36];

    format_bt_addr_str(connection, description);
    ++*(volatile uint32_t *)((unsigned long)&g_bonded_count) /*=0x20007514*/;
    *(volatile uint8_t *)(*(volatile uintptr_t *)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x367u) = 0;

    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): Got %s bind addr %d\n\n") /*=0x9a46f*/, ((unsigned long)"check_bonded_addr") /*=0x9b108*/, description);
        else
            debug_print(((unsigned long)"%s(): Got %s bind addr %d\n\n") /*=0x9a46f*/, ((unsigned long)"check_bonded_addr") /*=0x9b108*/, description);
    }
}
