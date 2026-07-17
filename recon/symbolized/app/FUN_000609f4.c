#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000609f4 @ 0x000609f4
 * public-name: FUN_000609f4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 */
/* Reconstructed FUN_000609f4 @ 0x609f4  (parity: 300/300 trials, PROVEN) */

extern void z_impl_k_sem_take(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_000609f4(unsigned int param_1, unsigned int param_2)
{
    if (param_2 == 0x0bad0000UL) {
        z_impl_k_sem_take(param_1 + 0x30, param_2, 0xffffffffUL, 0xffffffffUL);
        return;
    }
    return;
}
