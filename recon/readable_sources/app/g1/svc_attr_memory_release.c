#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_svc_attr_memory_pool__param_0528       [param_0528; G1-original]
 * Raw function identity: 0x0007f3c2.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007f3c2 @ 0x0007f3c2
 * public-name: svc_attr_memory_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   svc_attr_memory_release                  <= FUN_0007f3c2 @ 0x0007f3c2
 */
/* Reconstructed FUN_0007f3c2 @ 0x7f3c2  (parity: 300/300 trials, PROVEN) */

extern void g1_recon_k_free(void *allocation);

void svc_attr_memory_release(int param_1)
{
    unsigned int *puVar1;
    unsigned int uVar2;
    *(unsigned int*)(param_1 + 0x134) = 0;
    while ((puVar1 = *(unsigned int**)(param_1 + 0x150)) != (unsigned int*)0) {
        uVar2 = *puVar1;
        *(unsigned int*)(param_1 + 0x150) = uVar2;
        if (puVar1 == *(unsigned int**)(param_1 + 0x154)) {
            *(unsigned int*)(param_1 + 0x154) = uVar2;
        }
        g1_recon_k_free(puVar1);
    }
    *(unsigned int*)(param_1 + 0x158) = 0;
    return;
}
