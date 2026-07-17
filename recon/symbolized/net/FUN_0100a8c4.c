#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a8c4 @ 0x0100a8c4
 * public-name: FUN_0100a8c4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a8c4 @ 0x100a8c4  (parity 300 trials PROVEN) */

#define DAT_0100a8d8 ((unsigned int)0x21000bf8)

void FUN_0100a8c4(void)
{
    unsigned int iVar1 = DAT_0100a8d8;
    *(volatile unsigned short *)(DAT_0100a8d8 + 0x34) = 0xffff;
    *(volatile unsigned short *)(iVar1 + 0x36) = 0xffff;
    *(volatile unsigned char *)(iVar1 + 0x32) = 0;
    *(volatile unsigned short *)(iVar1 + 0x38) = 0xffff;
    return;
}
