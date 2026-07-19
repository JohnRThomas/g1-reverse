#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000579b4 @ 0x000579b4
 * public-name: l2cap_find_chan_by_id
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_find_chan_by_id                    <= FUN_000579b4 @ 0x000579b4
 * address symbols (name @ address):
 *   g_2000ad2c                               @ 0x2000ad2c
 */
/* Reconstructed FUN_000579b4 @ 0x579b4  (parity: 300/300 trials, PROVEN) */

void l2cap_find_chan_by_id(unsigned int param_1)
{
    int *piVar1 = *(volatile int**)((unsigned long)&g_2000ad2c) /*=0x2000ad2c*/;
    while (piVar1 != (int*)0 && *(volatile unsigned short*)((char*)piVar1 - 8) != param_1) {
        piVar1 = *(volatile int**)piVar1;
    }
}
