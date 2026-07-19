#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x0007efd4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007efd4 @ 0x0007efd4
 * public-name: flash_area_erase
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_erase                         <= FUN_0007efd4 @ 0x0007efd4
 */
/* Reconstructed FUN_0007efd4 @ 0x7efd4  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fn_t)(int, int);
unsigned int flash_area_erase(int param_1, int param_2, int param_3)
{
    if (param_2 >= 0 && (unsigned int)(param_3 + param_2) <= *(unsigned int*)(param_1 + 8)) {
        int a = *(int*)(param_1 + 0xc);
        int b = *(int*)(a + 8);
        fn_t f = *(fn_t*)(b + 8);
        return f(*(int*)(param_1 + 0xc), param_2 + *(int*)(param_1 + 4));
    }
    return 0xffffffea;
}
