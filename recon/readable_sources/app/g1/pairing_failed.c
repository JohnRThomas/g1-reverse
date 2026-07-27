#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018444 @ 0x00018444
 * public-name: pairing_failed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_bt_addr_str                       <= FUN_00018334 @ 0x00018334
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 *   bt_conn_get_field_0x90                   <= FUN_00081526 @ 0x00081526
 * address symbols (name @ address):
 *   rodata_9a48b                             @ 0x0009a48b   [INLINED -- G6 literal batch]
 *   rodata_9a4af                             @ 0x0009a4af   [INLINED -- G6 literal batch]
 *   rodata_9b126                             @ 0x0009b126   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction pairing_failed @ 0x18444. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern int bt_conn_get_field_0x90(int);
extern void format_bt_addr_str(const void*, char*);
extern int bt_conn_disconnect_by_state(unsigned short*, unsigned char);

void pairing_failed(uint32_t connection, uint32_t error)
{
    char description[36];
    uintptr_t active_connection = bt_conn_get_field_0x90(connection);

    format_bt_addr_str((const void *)active_connection, description);
    log_message(((unsigned long)"Pairing failed conn: %s, reason %d\n") /*=0x9a48b*/, description, error);

    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): bt_conn_disconnect because Pairing failed\n") /*=0x9a4af*/, ((unsigned long)"pairing_failed") /*=0x9b126*/);
        else
            debug_print(((unsigned long)"%s(): bt_conn_disconnect because Pairing failed\n") /*=0x9a4af*/, ((unsigned long)"pairing_failed") /*=0x9b126*/);
    }

    bt_conn_disconnect_by_state(connection, 0x13);
}
