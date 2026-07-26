#include "g1_net_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_01034464 @ 0x01034464
 * public-name: FUN_01034464
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_free_bitmap               @ 0x210006a4
 */
/* net-core FUN_01034464 @ 0x1034464  (parity 300 trials PROVEN) */

extern void FUN_01034368(unsigned int, unsigned int);
void FUN_01034464(unsigned int param_1)
{
    volatile unsigned int * const p = (volatile unsigned int * const)G1_NRF_DPPIC_NS_BASE;
    p[0x142] = 1u << (param_1 & 0xff);
    FUN_01034368(((unsigned long)&g_sdc_res_pool_free_bitmap) /*=0x210006a4*/, param_1);
}
