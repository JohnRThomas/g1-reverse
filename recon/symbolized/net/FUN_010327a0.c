#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010327a0 @ 0x010327a0
 * public-name: FUN_010327a0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_queue_stats_block_b                @ 0x21004a34
 */
/* net-core FUN_010327a0 @ 0x10327a0  (parity 300 trials PROVEN) */

#define DAT_010327b4 ((unsigned int)G1N_21004a60)
#define DAT_010327b8 ((unsigned int)((unsigned long)&g_net_queue_stats_block_b) /*=0x21004a34*/)

void FUN_010327a0(void)
{
    unsigned int iVar1 = DAT_010327b4;
    *(volatile unsigned int *)(DAT_010327b4 + 0x20) = 0;
    *(volatile unsigned int *)(iVar1 + 0x24) = 0;
    *(volatile unsigned int *)(iVar1 + 0x28) = 0;
    iVar1 = DAT_010327b8;
    *(volatile unsigned int *)(DAT_010327b8 + 0x20) = 0;
    *(volatile unsigned int *)(iVar1 + 0x24) = 0;
    *(volatile unsigned int *)(iVar1 + 0x28) = 0;
    return;
}
