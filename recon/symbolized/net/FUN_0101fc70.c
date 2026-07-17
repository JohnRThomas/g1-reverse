#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101fc70 @ 0x0101fc70
 * public-name: FUN_0101fc70
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ccm_op_status                      @ 0x210014d8
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core FUN_0101fc70 @ 0x101fc70  (parity 300 trials PROVEN) */

extern void FUN_01020088(unsigned int a0);

void FUN_0101fc70(void)
{
  unsigned int iVar1;
  unsigned int uVar2;

  FUN_01020088(2);
  uVar2 = 0x80000003u;
  iVar1 = REG_4100e000 /*=0x4100e000*/;
  *(volatile unsigned char *)((unsigned long)&g_net_ccm_op_status) /*=0x210014d8*/ = 1;
  *(volatile unsigned int *)(iVar1 + 0x100) = 0;
  *(volatile unsigned int *)(iVar1 + 0x104) = 0;
  *(volatile unsigned int *)(iVar1 + 0x108) = 0;
  *(volatile unsigned int *)(iVar1 + 0x80) = uVar2;
  return;
}
