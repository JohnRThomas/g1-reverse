#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010209c8 @ 0x010209c8
 * public-name: mpsl_timeslot_window_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   mpsl_timeslot_window_get                 <= FUN_010209c8 @ 0x010209c8
 */
/* net-core FUN_010209c8 @ 0x10209c8  (parity 300 trials PROVEN) */

#define DAT_010209dc ((unsigned int)G1N_210015f0)

void mpsl_timeslot_window_get(unsigned int *param_1, unsigned int *param_2)
{
    unsigned int uVar2 = *(volatile unsigned int *)(DAT_010209dc + 0x3c);
    unsigned int uVar1 = *(volatile unsigned int *)(DAT_010209dc + 0x40);
    *param_1 = *(volatile unsigned int *)(DAT_010209dc + 0x38);
    param_1[1] = uVar2;
    *param_2 = uVar1;
    return;
}
