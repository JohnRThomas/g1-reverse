#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018a38 @ 0x00018a38
 * public-name: indicate_sc_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   bt_conn_disconnect_by_state              <= FUN_00056a68 @ 0x00056a68
 * address symbols (name @ address):
 *   rodata_9a8f9                             @ 0x0009a8f9   [INLINED -- G6 literal batch]
 *   rodata_9b1da                             @ 0x0009b1da   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ble_indicate_sc_retry_count            @ 0x2000ff70
 */
/* Full ABI-faithful reconstruction indicate_sc_cb @ 0x18a38. */
#include <stdint.h>
#include "../../../headers/g1_log.h"

extern void gatt_discover(unsigned int, unsigned int);
extern void bt_conn_disconnect_by_state(unsigned int, int);

void indicate_sc_cb(const uint32_t *connection_ref, uint32_t security_level,
                    int32_t error)
{
    uint8_t attempt;

    (void)security_level;
    if (error != 0)
        return;

    attempt = (uint8_t)(*(volatile uint8_t *)((unsigned long)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/ + 1u);
    *(volatile uint8_t *)((unsigned long)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/ = attempt;
    if (attempt < 5u) {
        *(volatile uint32_t *)((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/ |= 4u;
        gatt_discover(*connection_ref, 1u);
        return;
    }

    *(volatile uint8_t *)((unsigned long)&g_ble_indicate_sc_retry_count) /*=0x2000ff70*/ = 0;
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): disconnect because can not discover ancs.\n") /*=0x9a8f9*/, ((unsigned long)"indicate_sc_cb") /*=0x9b1da*/);
        else
            debug_print(((unsigned long)"%s(): disconnect because can not discover ancs.\n") /*=0x9a8f9*/, ((unsigned long)"indicate_sc_cb") /*=0x9b1da*/);
    }

    bt_conn_disconnect_by_state(*connection_ref, 0x13u);
}
