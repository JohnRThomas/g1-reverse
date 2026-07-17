#include "g1_app_symbols.h"
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
