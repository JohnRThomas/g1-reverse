#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101fcf4 @ 0x0101fcf4
 * public-name: FUN_0101fcf4
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ccm_op_status                      @ 0x210014d8
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_0101fcf4 @ 0x101fcf4  (parity 300 trials PROVEN) */

extern void FUN_01020088(unsigned int a);

void FUN_0101fcf4(void)
{
  FUN_01020088(2);
  volatile unsigned int *base = (volatile unsigned int *)REG_4100e000 /*=0x4100e000*/;
  volatile unsigned char *flag = (volatile unsigned char *)((unsigned long)&g_net_ccm_op_status) /*=0x210014d8*/;
  *flag = 1;
  base[0x100/4] = 0;
  base[0x104/4] = 0;
  base[0x108/4] = 0;
  *base = 1;
  return;
}
