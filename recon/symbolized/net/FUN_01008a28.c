#include "g1_net_symbols.h"
/* net-core FUN_01008a28 @ 0x1008a28  (parity 300 trials PROVEN) */

extern unsigned int FUN_01008670(void);
extern unsigned long long FUN_01008940(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_01008a28(unsigned long long *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int unaff_r4=0, unaff_r5=0, unaff_r6=0, unaff_r7=0;
  unsigned long long uVar1;

  (void)FUN_01008670();
  (void)FUN_01008940(0,0,0,0);
  uVar1 = FUN_01008940(0,0,0,0);
  *param_1 = uVar1;
  *(unsigned int *)((int)param_1 + 8) = param_3;
  *(unsigned int *)((int)param_1 + 0xc) = param_4;
  *(unsigned int *)((int)param_1 + 0x10) = unaff_r4;
  *(unsigned int *)((int)param_1 + 0x14) = unaff_r5;
  *(unsigned int *)((int)param_1 + 0x18) = unaff_r6;
  *(unsigned int *)((int)param_1 + 0x1c) = unaff_r7;
  return;
}

