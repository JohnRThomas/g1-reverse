#include "g1_net_symbols.h"
/* net-core FUN_01019128 @ 0x1019128  (parity 300 trials PROVEN) */

extern void FUN_0100ef88(unsigned int a0, unsigned int a1, unsigned int a2);

void FUN_01019128(void)
{
  unsigned int iVar1 = ((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned short uVar4;
  unsigned char bVar5;

  bVar5 = (*(volatile unsigned char *)(iVar1 + 0x54)) == 3;
  if (bVar5) {
    uVar4 = **(volatile unsigned short **)(iVar1 + 0x50);
  } else {
    uVar4 = 0;
  }
  *(volatile unsigned short *)(iVar1 + 0x40) = uVar4;
  uVar3 = ((uintptr_t)&g_21000fc6) /*=0x21000fc6*/;
  uVar2 = ((uintptr_t)&rodata_1017579) /*=0x1017579*/;
  *(volatile unsigned char *)(iVar1 + 0x3f) = bVar5;
  FUN_0100ef88(uVar3, uVar2, 2);
  return;
}

