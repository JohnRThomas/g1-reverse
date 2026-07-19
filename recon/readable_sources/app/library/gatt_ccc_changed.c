#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_bt_gatt_ccc_managed_user_data__param_0618 [param_0618; library]
 * Raw function identity: 0x000825c0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000825c0 @ 0x000825c0
 * public-name: gatt_ccc_changed
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_ccc_changed                         <= FUN_000825c0 @ 0x000825c0
 */
/* Reconstructed FUN_000825c0 @ 0x825c0  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr_t)(void);

void gatt_ccc_changed(unsigned int param_1, int param_2)
{
    unsigned short a = *(unsigned short *)(param_2 + 8);
    if (*(unsigned short *)(param_2 + 10) != a) {
        *(unsigned short *)(param_2 + 10) = a;
        fnptr_t fn = *(fnptr_t *)(param_2 + 0xc);
        if (fn != 0) {
            fn();
        }
    }
}
