#include "g1_net_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_01033ee4 @ 0x01033ee4
 * public-name: FUN_01033ee4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_esb_ppi_ch_id_1                        @ 0x2100645b
 *   g_154_dppi_channel_ack                   @ 0x2100645c
 *   g_esb_ppi_ch_id_3                        @ 0x2100645d
 *   g_esb_ppi_ch_id_5                        @ 0x2100645f
 *   g_esb_ppi_ch_id_6                        @ 0x21006460
 */
/* net-core FUN_01033ee4 @ 0x1033ee4  (parity 300 trials PROVEN) */

void FUN_01033ee4(void)
{
    unsigned int v;
    v = 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_1) /*=0x2100645b*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_5) /*=0x2100645f*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_3) /*=0x2100645d*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_154_dppi_channel_ack) /*=0x2100645c*/;
    v |= 1u << *(volatile unsigned char*)((unsigned long)&g_esb_ppi_ch_id_6) /*=0x21006460*/;
    v |= 1;
    *(volatile unsigned int*)(G1_NRF_DPPIC_NS_BASE + 0x508) = v;
}
