/* readable reconstruction; identity: FUN_010208b0 @ 0x010208b0
 * public-name: sdc_llcp_stop_rx_timeout
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_stop_rx_timeout                 <= FUN_010208b0 @ 0x010208b0
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_010208b0 @ 0x10208b0  (parity 300 trials PROVEN) */

#define DAT_010208c8 ((unsigned int)G1_NRF_RADIO_NS_BASE)

void sdc_llcp_stop_rx_timeout(void)
{
    unsigned int iVar1 = DAT_010208c8;
    *(volatile unsigned int *)(DAT_010208c8 + 0x200) = *(volatile unsigned int *)(DAT_010208c8 + 0x200) & 0xffffffbf;
    *(volatile unsigned int *)(iVar1 + 0x560) = 0;
    return;
}
