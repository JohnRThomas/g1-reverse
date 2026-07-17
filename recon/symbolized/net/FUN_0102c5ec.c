#include "g1_net_symbols.h"
/* net-core FUN_0102c5ec @ 0x102c5ec  (parity 5 trials PROVEN) */
extern void FUN_01039752(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_01039774(unsigned int, unsigned int, unsigned int);
extern void FUN_010397a4(unsigned int, unsigned int, unsigned int);
extern int FUN_010397c0(unsigned int, unsigned int);
extern int FUN_010397d2(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_01039972(unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b62e(unsigned int, unsigned int, int);

#define DAT_0102c6f0 ((unsigned long)&rodata_103d373) /*=0x103d373*/
#define DAT_0102c6f4 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/

void FUN_0102c5ec(unsigned int *param_1, int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  int iVar4;
  int iVar5;
  unsigned int uVar6;
  unsigned int uVar7;

  if (param_3 < 0x40000) {
    if (param_3 < 5) {
      FUN_01039bbe(DAT_0102c6f4, DAT_0102c6f0, 0x1f2);
      FUN_01039bb0(DAT_0102c6f0, 0x1f2);
      __builtin_unreachable();
    }
    iVar5 = 4;
  } else {
    iVar5 = 8;
  }
  uVar6 = (param_2 + 7U) & 0xfffffff8;
  uVar3 = ((param_2 + (param_3 - iVar5)) & 0xfffffff8) - uVar6;
  uVar7 = uVar3 >> 3;
  if (uVar3 < 0x18) {
    FUN_01039bbe(DAT_0102c6f4, DAT_0102c6f0, 0x1fb);
    FUN_01039bb0(DAT_0102c6f0, 0x1fb);
    __builtin_unreachable();
  }
  *param_1 = uVar6;
  *(volatile unsigned int *)(uVar6 + 8) = uVar7;
  *(volatile unsigned int *)(uVar6 + 0xc) = 0;
  iVar5 = FUN_010397d2(uVar7, uVar7, param_3 - iVar5, iVar5);
  iVar4 = iVar5 + 5;
  iVar1 = FUN_010397c0(uVar7, 1);
  uVar3 = (unsigned int)(iVar4 * 4 + 7U) >> 3;
  if ((unsigned int)(iVar1 + uVar3) <= uVar7) {
    iVar1 = iVar4 * 4 + -0x10;
    if (iVar5 < -1) {
      iVar1 = 0;
    }
    FUN_0103b62e(uVar6 + 0x10, 0, iVar1);
    FUN_010397a4(uVar6, 0, uVar3);
    FUN_01039752(uVar6, 0, 0, 0);
    uVar2 = FUN_01039774(uVar6, 0, 1);
    FUN_010397a4(uVar2, uVar3, uVar7 - uVar3);
    FUN_01039752(uVar6, uVar3, 0, uVar3);
    FUN_010397a4(uVar6, uVar7, 0);
    FUN_01039752(uVar6, uVar7, 0, uVar7 - uVar3);
    uVar2 = FUN_01039774(uVar6, uVar7, 1);
    FUN_01039972(uVar2, uVar3);
    return;
  }
  FUN_01039bbe(DAT_0102c6f4, DAT_0102c6f0, 0x20c);
  FUN_01039bb0(DAT_0102c6f0, 0x20c);
  __builtin_unreachable();
}
