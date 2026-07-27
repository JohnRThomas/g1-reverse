#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072040 @ 0x00072040
 * public-name: z_spin_lock_valid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 * address symbols (name @ address):
 *   g_spinlock_validate_owner                @ 0x2000b458
 */
/* Reconstructed FUN_00072040 @ 0x72040  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int z_spin_lock_valid(unsigned int*param_1) {
    unsigned int v = *param_1;
    if (v != 0) {
        int iVar1 = (int)((v & 3) - *(volatile uint8_t*)((unsigned long)&g_spinlock_validate_owner) /*=0x2000b458*/);
        if (iVar1 != 0) iVar1 = 1;
        return iVar1;
    }
    return 1;
}
