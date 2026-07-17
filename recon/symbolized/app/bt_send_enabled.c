#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017e3c @ 0x00017e3c
 * public-name: bt_send_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_9a143                             @ 0x0009a143
 *   rodata_9a2cd                             @ 0x0009a2cd
 *   g_log_level                              @ 0x2000230c
 *   g_ble_conn_ctx_ptr                       @ 0x20006a30
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Full ABI-faithful reconstruction bt_send_enabled @ 0x17e3c. */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);

void bt_send_enabled(int32_t error)
{
    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            DEBUG_PRINT(((unsigned long)&rodata_9a143) /*=0x9a143*/, ((unsigned long)&rodata_9a2cd) /*=0x9a2cd*/, error);
        else
            debug_print(((unsigned long)&rodata_9a143) /*=0x9a143*/, ((unsigned long)&rodata_9a2cd) /*=0x9a2cd*/, error);
    }

    *(volatile uint8_t *)(*(volatile uintptr_t *)((unsigned long)&g_ble_conn_ctx_ptr) /*=0x20006a30*/ + 0x366u) =
        error == 0;
}
