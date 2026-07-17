/* readable reconstruction; identity: FUN_00018444 @ 0x00018444
 * public-name: pairing_failed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9a48b                             @ 0x0009a48b
 *   rodata_9a4af                             @ 0x0009a4af
 *   rodata_9b126                             @ 0x0009b126
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction pairing_failed @ 0x18444. */
#include <stdint.h>

extern uintptr_t FUN_00081526(void);
extern void format_bt_addr_str(const void *connection, char description[36]);
extern void log_message(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);

void pairing_failed(uint32_t connection, uint32_t error)
{
    char description[36];
    uintptr_t active_connection = FUN_00081526();

    format_bt_addr_str((const void *)active_connection, description);
    log_message(0x0009a48bu, description, error);

    if (*(volatile int *)0x2000230cu > 0) {
        if (*(volatile int *)0x20007554u == 0)
            log_message(0x0009a4afu, 0x0009b126u);
        else
            debug_print(0x0009a4afu, 0x0009b126u);
    }

    FUN_00056a68(connection, 0x13);
}
