#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_opt_record__param_0461                 [param_0461; G1-original]
 *   param_2          => struct g1_layout_opt_field3_ctx__param_0463             [param_0463; G1-original]
 * Raw function identity: 0x0007c48a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007c48a @ 0x0007c48a
 * public-name: opt_field3_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_field3_set                           <= FUN_0007c48a @ 0x0007c48a
 */
/* Reconstructed FUN_0007c48a @ 0x7c48a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int opt_field3_set(uint8_t *param_1, int *param_2)
{
    uint8_t bVar1;
    if (param_1 != (uint8_t*)0 && param_2 != (int*)0) {
        if (*param_2 == 0) {
            if ((char)*((uint8_t*)param_2 + 4) != 0) {
                return 7;
            }
            bVar1 = *param_1 & 0xf7;
        } else {
            bVar1 = *param_1 | 8;
        }
        *param_1 = bVar1;
        *(int*)(param_1 + 8) = *param_2;
        param_1[2] = *((uint8_t*)param_2 + 4);
        return 0;
    }
    return 7;
}
