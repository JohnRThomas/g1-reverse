/* readable reconstruction; identity: FUN_010208cc @ 0x010208cc
 * public-name: FUN_010208cc
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_010208cc @ 0x10208cc  (parity 300 trials PROVEN) */

#define DAT_010208e0 ((unsigned int)G1_NRF_RADIO_NS_BASE)

unsigned int FUN_010208cc(char *param_1)
{
    unsigned int uVar1 = *(volatile unsigned int *)(DAT_010208e0 + 0x548) & 0x7f;
    *param_1 = (char)(0 - uVar1);
    return 1;
}
