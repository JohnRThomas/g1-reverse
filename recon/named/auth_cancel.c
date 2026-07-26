/* readable reconstruction; identity: FUN_0001849c @ 0x0001849c
 * public-name: auth_cancel
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 * address symbols (name @ address):
 *   rodata_9a4e0                             @ 0x0009a4e0   [INLINED -- G6 literal batch]
 *   rodata_9a4f7                             @ 0x0009a4f7   [INLINED -- G6 literal batch]
 *   rodata_9b11a                             @ 0x0009b11a   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction auth_cancel @ 0x1849c. */
#include <stdint.h>

extern uintptr_t bt_conn_get_field_0x90(void);
extern void format_bt_addr_str(const void *connection, char *description);
extern void log_message(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);
extern void bt_conn_disconnect_by_state(uint32_t connection, uint32_t reason);

void auth_cancel(uint32_t connection)
{
    char description[32];
    uintptr_t active_connection = bt_conn_get_field_0x90();

    format_bt_addr_str((const void *)active_connection, description);
    log_message(0x0009a4e0u, description);

    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            log_message(0x0009a4f7u, 0x0009b11au);
        else
            debug_print(0x0009a4f7u, 0x0009b11au);
    }

    bt_conn_disconnect_by_state(connection, 0x13u);
}
