#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_timer__param_0736                    [param_0736; library]
 * Raw function identity: 0x00086726.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086726 @ 0x00086726
 * public-name: k_timer_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_timer_init                             <= FUN_00086726 @ 0x00086726
 */
/* Reconstructed FUN_00086726 @ 0x86726  (parity: 300/300 trials, PROVEN) */

void k_timer_init(unsigned int *param_1, unsigned int param_2, unsigned int param_3) {
    volatile unsigned int *p = (volatile unsigned int*)param_1;
    p[8] = param_2;
    p[9] = param_3;
    p[6] = (unsigned int)(param_1 + 6);
    p[7] = (unsigned int)(param_1 + 6);
    p[0] = 0;
    p[1] = 0;
    p[0xc] = 0;
    p[0xd] = 0;
}
