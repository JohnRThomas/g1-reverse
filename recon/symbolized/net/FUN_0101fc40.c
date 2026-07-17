#include "g1_net_symbols.h"
/* net-core FUN_0101fc40 @ 0x101fc40  (parity 300 trials PROVEN) */

extern void FUN_01020088(unsigned int);

void FUN_0101fc40(unsigned int param_1, unsigned int param_2, int param_3)
{
  FUN_01020088(2);
  *(volatile unsigned char*)((unsigned long)&g_net_ccm_op_status) /*=0x210014d8*/ = 1;
  *(volatile int*)(REG_4100e000 /*=0x4100e000*/ + 0x510) = param_3 - 3;
  *(volatile unsigned int*)(REG_4100e000 /*=0x4100e000*/ + 0x508) = param_1;
  *(volatile unsigned int*)(REG_4100e000 /*=0x4100e000*/ + 0x504) = param_2;
}
