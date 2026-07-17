#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0001849c @ 0x0001849c
 * public-name: auth_cancel
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9a4e0                             @ 0x0009a4e0
 *   rodata_9a4f7                             @ 0x0009a4f7
 *   rodata_9b11a                             @ 0x0009b11a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction auth_cancel @ 0x1849c. */
#include <stdint.h>

extern uintptr_t FUN_00081526(void);
extern void format_bt_addr_str(const void *connection, char *description);
extern void log_message(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);

void auth_cancel(uint32_t connection)
{
    char description[32];
    uintptr_t active_connection = FUN_00081526();

    format_bt_addr_str((const void *)active_connection, description);
    log_message(((unsigned long)&rodata_9a4e0) /*=0x9a4e0*/, description);

    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)&rodata_9a4f7) /*=0x9a4f7*/, ((unsigned long)&rodata_9b11a) /*=0x9b11a*/);
        else
            debug_print(((unsigned long)&rodata_9a4f7) /*=0x9a4f7*/, ((unsigned long)&rodata_9b11a) /*=0x9b11a*/);
    }

    FUN_00056a68(connection, 0x13u);
}
