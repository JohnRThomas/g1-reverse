#include "g1_net_symbols.h"
/* net-core FUN_0102e974 @ 0x102e974  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102eb70(void);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

void FUN_0102e974(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int iVar1 = ((uintptr_t)&g_net_evt_slot_tbl) /*=0x2100076c*/;
  unsigned int iVar2;

  iVar2 = FUN_0102eb70();
  if (iVar2 != 0) {
    FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "418c0500" /*=0x103d7fb*/, 0x55);
    FUN_01039bb0("418c0500" /*=0x103d7fb*/, 0x55);
  }
  *(volatile unsigned int *)(iVar1 + param_1 * 8) = param_3;
  *(volatile unsigned int *)(iVar1 + param_1 * 8 + 4) = param_2;
  return;
}

