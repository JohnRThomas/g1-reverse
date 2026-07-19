#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_opt_node_t__param_0459                 [param_0459; G1-original]
 * Raw function identity: 0x0007c65c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007c65c @ 0x0007c65c
 * public-name: serialization_copy_fields_0c_10
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   serialization_copy_fields_0c_10          <= FUN_0007c65c @ 0x0007c65c
 */
/* Reconstructed FUN_0007c65c @ 0x7c65c  (parity: 300/300 trials, PROVEN) */

unsigned int serialization_copy_fields_0c_10(int param_1, unsigned int *param_2)
{
    if (param_1 != 0 && param_2 != 0) {
        *param_2 = *(unsigned int *)(param_1 + 0xc);
        param_2[1] = *(unsigned int *)(param_1 + 0x10);
        return 0;
    }
    return 7;
}
