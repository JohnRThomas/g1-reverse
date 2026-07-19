#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x00072074       => struct g1_layout_spinlock_validate_state__global_1394   [global_1394; library]
 * Raw function identity: 0x0007205c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007205c @ 0x0007205c
 * public-name: z_spin_unlock_valid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 * address symbols (name @ address):
 *   g_current_thread_ptr                     @ 0x2000b450
 *   g_spinlock_validate_owner                @ 0x2000b458
 */
/* Reconstructed FUN_0007205c @ 0x7205c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int z_spin_unlock_valid(unsigned int *param_1) {
    unsigned int cmp = (*(volatile uint32_t*)((unsigned long)&g_current_thread_ptr) /*=0x2000b450*/) | (unsigned int)(*(volatile uint8_t*)((unsigned long)&g_spinlock_validate_owner) /*=0x2000b458*/);
    int bVar1 = (*param_1 == cmp);
    if (bVar1) {
        *param_1 = 0;
    }
    return bVar1;
}
