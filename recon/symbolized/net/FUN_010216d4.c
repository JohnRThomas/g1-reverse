#include "g1_net_symbols.h"
/* net-core FUN_010216d4 @ 0x10216d4  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern unsigned int FUN_0102028c(unsigned int);
extern int FUN_01021920(int, void *, unsigned int, unsigned int);
extern unsigned int FUN_01021934(void);
extern int FUN_01021940(unsigned int, unsigned int, int, char *);

int FUN_010216d4(unsigned int param_1, unsigned int param_2, int param_3, volatile unsigned short *param_4)
{
  volatile unsigned char * const pbVar3 = (volatile unsigned char *)((unsigned long)&g_net_clk_conv_cache_key) /*=0x2100003c*/;
  unsigned int uVar4 = FUN_01021934();

  if (pbVar3[0] == param_1 && pbVar3[1] == param_2 &&
      (int)(signed char)pbVar3[2] == param_3 && pbVar3[3] == uVar4) {
    unsigned char bVar2 = pbVar3[6];
    int iVar7 = (int)(signed char)pbVar3[7];
    *param_4 = *(volatile unsigned short *)(pbVar3 + 4);
    *((volatile unsigned char *)param_4 + 1) = bVar2;
    return iVar7;
  }

  unsigned int uVar5;
  switch (param_1) {
    case 1: uVar5 = 0; break;
    case 2: uVar5 = 1; break;
    case 4: uVar5 = 3; break;
    case 8: uVar5 = 2; break;
    default:
      FUN_01008d00(6, 0x405);
      for (;;) { FUN_01008d00(6, 0x405); }
  }

  char local_29[8];
  int iVar6 = FUN_01021940(uVar5, param_2, param_3, local_29);
  if (iVar6 != 0) {
    FUN_01008d00(0x75, 0x3d);
    for (;;) { FUN_01008d00(0x75, 0x3d); }
  }

  unsigned int uVar5b = FUN_0102028c(param_2);
  int iVar7 = FUN_01021920((int)(signed char)local_29[0], (void *)param_4, uVar5b, 0);

  volatile unsigned char * const p178c = (volatile unsigned char *)((unsigned long)&g_net_clk_conv_cache_ext) /*=0x21000040*/;
  *(volatile unsigned short *)(pbVar3 + 4) = *param_4;
  unsigned char uVar1 = *((volatile unsigned char *)param_4 + 1);
  pbVar3[0] = (unsigned char)param_1;
  pbVar3[1] = (unsigned char)param_2;
  pbVar3[2] = (unsigned char)param_3;
  pbVar3[3] = (unsigned char)uVar4;
  pbVar3[7] = (unsigned char)iVar7;
  p178c[2] = uVar1;

  return iVar7;
}
