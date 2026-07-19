#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_sys_dlist_t__param_0734                [param_0734; library]
 * Raw function identity: 0x00086688.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086688 @ 0x00086688
 * public-name: sys_dlist_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_dlist_init                           <= FUN_00086688 @ 0x00086688
 */
/* Reconstructed FUN_00086688 @ 0x86688  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int sys_dlist_init(void *param_1)
{
    *(volatile uint32_t*)param_1 = (uint32_t)(uintptr_t)param_1;
    *(volatile uint32_t*)((char*)param_1 + 4) = (uint32_t)(uintptr_t)param_1;
    return 0;
}
