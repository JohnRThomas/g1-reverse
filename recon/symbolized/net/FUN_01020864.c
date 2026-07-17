#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01020864 @ 0x01020864
 * public-name: FUN_01020864
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41008000                             @ 0x41008000
 */
/* net-core FUN_01020864 @ 0x1020864  (parity 300 trials PROVEN) */

void FUN_01020864(unsigned int param_1, unsigned int *param_2)
{
  unsigned int uVar2, uVar3;
  volatile unsigned int *p1 = (volatile unsigned int*)0x210015f0;
  volatile unsigned int *p2 = (volatile unsigned int*)REG_41008000 /*=0x41008000*/;
  volatile unsigned int *p3 = (volatile unsigned int*)0x4100f000;

  *(volatile unsigned int*)((unsigned int)p2 + 0x104) = param_1 | 0x80000000;
  uVar2 = 1u << (param_1 & 0xff);
  *param_2 = param_1 | 0x80000000;
  uVar3 = *(volatile unsigned int*)((unsigned int)p1 + 0x2c);
  *(volatile unsigned int*)((unsigned int)p3 + 0x504) = uVar2;
  *(volatile unsigned int*)((unsigned int)p1 + 0x2c) = uVar3 | uVar2;
}
