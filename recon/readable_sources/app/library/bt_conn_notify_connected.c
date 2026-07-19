#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn__param_0034                    [param_0034; library]
 * Raw function identity: 0x00055fb4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00055fb4 @ 0x00055fb4
 * public-name: bt_conn_notify_connected
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_notify_connected                 <= FUN_00055fb4 @ 0x00055fb4
 * address symbols (name @ address):
 *   g_ble_conn_cb_list_head                  @ 0x2000ad1c
 */
/* Reconstructed FUN_00055fb4 @ 0x55fb4  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(int, unsigned char);

void bt_conn_notify_connected(int param_1)
{
    unsigned int *puVar2;
    unsigned char b = *(unsigned char *)(param_1 + 0xc);

    puVar2 = *(unsigned int **)((unsigned long)&g_ble_conn_cb_list_head) /*=0x2000ad1c*/;
    while (puVar2 != (unsigned int *)0) {
        fn_t f = (fn_t)(*puVar2);
        if (f != (fn_t)0) {
            f(param_1, b);
        }
        puVar2 = (unsigned int *)puVar2[8];
    }
}
