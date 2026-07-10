#include "g1_net_symbols.h"
/* net-core FUN_010344ec @ 0x10344ec  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
unsigned short FUN_010344ec(void) {
  int iVar3 = FUN_010344a8();
  volatile unsigned short *DAT_01034504 = (volatile unsigned short *)((uintptr_t)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;
  unsigned short uVar1 = DAT_01034504[iVar3 + 8];
  unsigned short uVar2 = uVar1 & 0x1c;
  if (uVar2 != 0) uVar2 = 1;
  return uVar2;
}

