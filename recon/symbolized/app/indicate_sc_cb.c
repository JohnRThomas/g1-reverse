#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018a38 @ 0x00018a38
 * public-name: indicate_sc_cb
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9a8f9                             @ 0x0009a8f9
 *   rodata_9b1da                             @ 0x0009b1da
 *   g_log_level                              @ 0x2000230c
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ble_indicate_sc_retry_count            @ 0x2000ff70
 */
/* Full ABI-faithful reconstruction indicate_sc_cb @ 0x18a38. */
#include <stdint.h>

extern void gatt_discover(uint32_t connection, uint32_t enabled);
extern void debug_print(uintptr_t format, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);
extern void log_message(uintptr_t format, ...);

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
            log_message(((unsigned long)&rodata_9a8f9) /*=0x9a8f9*/, ((unsigned long)&rodata_9b1da) /*=0x9b1da*/);
        else
            debug_print(((unsigned long)&rodata_9a8f9) /*=0x9a8f9*/, ((unsigned long)&rodata_9b1da) /*=0x9b1da*/);
    }

    FUN_00056a68(*connection_ref, 0x13u);
}
