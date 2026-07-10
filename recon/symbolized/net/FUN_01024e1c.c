#include "g1_net_symbols.h"
/* net-core FUN_01024e1c @ 0x1024e1c  (parity 300 trials PROVEN) */

extern void FUN_010256dc(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e) __attribute__((noreturn));

void FUN_01024e1c(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile unsigned char *pcVar2 = (volatile unsigned char *)((uintptr_t)&g_net_radio_timer_sync_state) /*=0x21001bf8*/;
  volatile unsigned char *iVar3 = (volatile unsigned char *)REG_41011000 /*=0x41011000*/;
  volatile unsigned char *dat_edc = (volatile unsigned char *)REG_4100f000 /*=0x4100f000*/;
  unsigned int uVar4 = 0x00fffffe;
  unsigned int uVar5;
  volatile unsigned char *iVar6;
  unsigned int uVar7;
  unsigned int uVar8;
  signed char cVar1;
  int iVar6b;

  cVar1 = *(volatile signed char *)pcVar2;
  uVar8 = *(volatile unsigned int *)(pcVar2 + 8);
  iVar6b = *(volatile int *)(pcVar2 + 0xc);

  if (cVar1 == 2) {
    if (iVar6b == param_2 && uVar8 == param_1) {
      return;
    }
  } else {
    if (iVar6b == param_2 && uVar8 == param_1) {
      FUN_010256dc(0x6c, 0x31c, param_3, (unsigned int)iVar6b, param_4);
    }
  }

  if (pcVar2[0x14] != 0) {
    *(volatile unsigned int *)(dat_edc + 0x508) = 6;
    *(volatile unsigned int *)(iVar3 + 0x308) = 0x10000;
    *(volatile unsigned int *)(iVar3 + 0x348) = 0x10000;
    *(volatile unsigned int *)(iVar3 + 0x140) = 0;
    uVar7 = (param_1 & 0xffffff) - *(volatile int *)(iVar3 + 0x504);
    if (((uVar7 & 0xffffff) < 0x800001) && ((uVar7 & uVar4) != 0)) {
      *(volatile unsigned int *)(iVar3 + 0x540) = param_1 & 0xffffff;
      *(volatile unsigned int *)(iVar3 + 0x344) = 0x10000;
      if (cVar1 != 0) {
        do {
        } while ((unsigned int)((uVar8 - *(volatile int *)(iVar3 + 0x504)) & uVar4) == 0);
      }
      *(volatile unsigned int *)(pcVar2 + 8) = param_1;
      iVar6 = (volatile unsigned char *)REG_4100c000 /*=0x4100c000*/;
      uVar5 = 0x80000001;
      *(volatile int *)(pcVar2 + 0xc) = param_2;
      *(volatile unsigned int *)(iVar3 + 0x1c0) = uVar5;
      *(volatile unsigned int *)(iVar6 + 0x8c) = uVar5;
      *(volatile unsigned int *)(dat_edc + 0x504) = 2;
      pcVar2[0] = 2;
      pcVar2[1] = 4;
      return;
    }
    FUN_010256dc(0x6c, 0x32c, (unsigned int)iVar3, uVar7, param_4);
  }
  FUN_010256dc(0x6c, 800, param_3, 0, param_4);
}

