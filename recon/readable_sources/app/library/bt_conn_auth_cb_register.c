#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_conn_auth_cb__param_0216            [param_0216; library]
 * Raw function identity: 0x000572fc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000572fc @ 0x000572fc
 * public-name: bt_conn_auth_cb_register
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_auth_cb_register                 <= FUN_000572fc @ 0x000572fc
 * address symbols (name @ address):
 *   g_bt_conn_auth_cb                        @ 0x2000ad28
 */
/* Reconstructed FUN_000572fc @ 0x572fc  (parity: 300/300 trials, PROVEN) */

unsigned int bt_conn_auth_cb_register(int *param_1)
{
    if (param_1 != (int*)0) {
        if (*(volatile int*)((unsigned long)&g_bt_conn_auth_cb) /*=0x2000ad28*/ != 0) {
            return 0xffffff88;
        }
        if (param_1[4] == 0 &&
            (param_1[0] != 0 || param_1[1] != 0 || param_1[2] != 0 || param_1[5] != 0)) {
            return 0xffffffea;
        }
    }
    *(volatile int*)((unsigned long)&g_bt_conn_auth_cb) /*=0x2000ad28*/ = (int)param_1;
    return 0;
}
