#include "g1_net_symbols.h"
/* net-core FUN_0102023c @ 0x102023c  (parity 300 trials PROVEN) */

typedef unsigned int undefined4;
extern void FUN_01025a84(void*, int, int);

unsigned int FUN_0102023c(void)
{
  int iVar1;

  FUN_01025a84((void*)((uintptr_t)&g_nrf802154_core_state) /*=0x210015f0*/, 0, 0x48);
  iVar1 = REG_41007000 /*=0x41007000*/;
  *(volatile undefined4 *)REG_41000e00 /*=0x41000e00*/ = 0x1111;
  *(volatile undefined4 *)(iVar1 + 0xe40) = 0;
  *(volatile undefined4 *)(iVar1 + 0xe44) = 0;
  *(volatile undefined4 *)(iVar1 + 0xe00) = 0xaa;
  return REG_41000000 /*=0x41000000*/;
}

