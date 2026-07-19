#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x0005a9f0       => struct g1_layout_bt_gatt_cb__global_1218                [global_1218; library]
 * Raw function identity: 0x0005a9d8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0005a9d8 @ 0x0005a9d8
 * public-name: bt_gatt_cb_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_cb_register                      <= FUN_0005a9d8 @ 0x0005a9d8
 * address symbols (name @ address):
 *   g_bt_gatt_callback_list_head             @ 0x2000af10
 */
/* Reconstructed FUN_0005a9d8 @ 0x5a9d8  (parity: 300/300 trials, PROVEN) */

void bt_gatt_cb_register(void *param_1)
{
    *(volatile unsigned int*)((char*)param_1 + 4) = 0;
    unsigned int node = (unsigned int)((char*)param_1 + 4);
    unsigned int base = ((unsigned long)&g_bt_gatt_callback_list_head) /*=0x2000af10*/;
    unsigned int tail = *(volatile unsigned int*)(base + 4);
    if (tail == 0) {
        *(volatile unsigned int*)base = node;
        *(volatile unsigned int*)(base + 4) = node;
    } else {
        *(volatile unsigned int*)tail = node;
        *(volatile unsigned int*)(base + 4) = node;
    }
}
