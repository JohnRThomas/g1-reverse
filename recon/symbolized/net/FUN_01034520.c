#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01034520 @ 0x01034520
 * public-name: FUN_01034520
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_sdc_res_pool_slot_tbl                  @ 0x210006a8
 */
/* net-core FUN_01034520 @ 0x1034520  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
static volatile unsigned short * const DAT_01034534 = (unsigned short *)((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;

unsigned short FUN_01034520(void)
{
    int iVar1 = FUN_010344a8();
    return DAT_01034534[iVar1 + 8] >> 0xd;
}
