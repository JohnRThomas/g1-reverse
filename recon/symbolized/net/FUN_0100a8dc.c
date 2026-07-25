#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a8dc @ 0x0100a8dc
 * public-name: FUN_0100a8dc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a8dc @ 0x100a8dc  (parity 300 trials PROVEN) */

#define DAT_0100a8f4 ((unsigned int)G1N_21000bf8)

void FUN_0100a8dc(unsigned int param_1)
{
    unsigned int iVar1 = DAT_0100a8f4;
    if (*(volatile unsigned short *)(DAT_0100a8f4 + 0x34) == param_1) {
        *(volatile unsigned char *)(iVar1 + 0x32) = 0;
        *(volatile unsigned short *)(iVar1 + 0x34) = 0xffff;
    }
    return;
}
