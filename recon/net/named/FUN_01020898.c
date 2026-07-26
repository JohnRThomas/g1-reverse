/* readable reconstruction; identity: FUN_01020898 @ 0x01020898
 * public-name: FUN_01020898
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01020898 @ 0x1020898  (parity 300 trials PROVEN) */

#define DAT_010208ac ((unsigned int)G1_NRF_RADIO_NS_BASE)

void FUN_01020898(unsigned int param_1)
{
    unsigned int iVar1 = DAT_010208ac;
    *(volatile unsigned int *)(DAT_010208ac + 0x560) = param_1;
    *(volatile unsigned int *)(iVar1 + 0x200) = *(volatile unsigned int *)(iVar1 + 0x200) | 0x40;
    return;
}
