#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101ff9c @ 0x0101ff9c
 * public-name: FUN_0101ff9c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 * address symbols (name @ address):
 *   g_net_radio_pending_reset_flag           @ 0x210014dc
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_0101ff9c @ 0x101ff9c  (parity 300 trials PROVEN) */

extern void sdc_assertion_fail(unsigned int, unsigned int, unsigned int, unsigned int);

int FUN_0101ff9c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (*(volatile unsigned char *)((unsigned long)&g_net_radio_pending_reset_flag) /*=0x210014dc*/ == 0) {
    sdc_assertion_fail(0x3c, 0x274, param_3, param_4);
    sdc_assertion_fail(0x3c, 0x275, param_3, param_4);
    while (1) { sdc_assertion_fail(0x3c, 0x275, param_3, param_4); }
  }
  if (*(volatile int *)(REG_4100e000 /*=0x4100e000*/ + 0x104) != 0) {
    int iVar1 = *(volatile int *)(REG_4100e000 /*=0x4100e000*/ + 0x400);
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    return iVar1;
  }
  sdc_assertion_fail(0x3c, 0x275, param_3, param_4);
  while (1) { sdc_assertion_fail(0x3c, 0x275, param_3, param_4); }
}
