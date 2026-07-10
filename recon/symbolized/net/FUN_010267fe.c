#include "g1_net_symbols.h"
/* net-core FUN_010267fe @ 0x10267fe  (parity 300 trials PROVEN) */
/* net-core FUN_010267fe @ 0x10267fe  (parity 300 trials PROVEN) */

typedef unsigned short ushort;

typedef unsigned char undefined1;
extern undefined1 FUN_01009d18(ushort,int,uint32_t,ushort,ushort);

undefined1 FUN_010267fe(ushort *param_1, ushort *param_2, uint32_t param_3)
{
  ushort uVar1 = *param_1;
  *param_2 = uVar1;
  return FUN_01009d18(uVar1,1,param_3,uVar1,uVar1);
}



