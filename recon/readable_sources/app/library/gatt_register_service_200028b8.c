#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_44         => struct g1_layout_gatt_register_service_locals__stack_1136 [stack_1136; G1-original]
 * Raw function identity: 0x00052b48.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00052b48 @ 0x00052b48
 * public-name: gatt_register_service_200028b8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_register_service_200028b8           <= FUN_00052b48 @ 0x00052b48
 *   bt_gatt_service_register                 <= FUN_0005ad38 @ 0x0005ad38
 * address symbols (name @ address):
 *   g_200028b8                               @ 0x200028b8
 */
/* Reconstructed FUN_00052b48 @ 0x52b48  (parity: 300/300 trials, PROVEN) */

extern unsigned int bt_gatt_service_register(void *service);

unsigned int gatt_register_service_200028b8(void)
{
    return bt_gatt_service_register((void *)((unsigned long)&g_200028b8) /*=0x200028b8*/);
}
