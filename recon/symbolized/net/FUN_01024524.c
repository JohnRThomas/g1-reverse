#include "g1_net_symbols.h"
/* net-core FUN_01024524 @ 0x1024524  (parity 36 trials PROVEN) */
/* net-core FUN_01024524 @ 0x1024524  (parity 300 trials PROVEN) */

typedef unsigned int uint;
typedef unsigned long long ulonglong;

extern void FUN_010256dc(int,int);

#define DAT_010245c4 0x1e847fffu
#define DAT_010245c8 0x431bde83u
#define DAT_010245cc 0xf4240000u
#define DAT_010245d0 0x1e848000u
#define DAT_010245d4 0x00010c6fu

void FUN_01024524(uint param_1,uint param_2,uint *param_3,int *param_4,char *param_5)
{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  int iVar7;

  if (param_2 <= DAT_010245c4) {
    uVar3 = (param_1 >> 0x1d) | (param_2 << 3);
    uVar4 = (uint)(((ulonglong)DAT_010245c8 * (ulonglong)uVar3) >> 0x2e);
    uVar1 = (uint)(((ulonglong)DAT_010245c8 *
                   (ulonglong)((((param_1 << 3) >> 0x10) + uVar3 * 0x10000) - DAT_010245cc * uVar4))
                  >> 0x2e);
    uVar4 = uVar1 | (uVar4 << 0x10);
    param_1 = param_1 - DAT_010245d0 * uVar4;
    uVar5 = ((param_1 >> 0xd) * 0x8637) >> 0x10;
    uVar2 = param_1 + uVar5 * (uint)(-0x3d09);
    uVar3 = (uVar2 * DAT_010245d4) >> 0x15;
    iVar7 = (int)(uVar3 * 0x3d09);
    uVar3 = uVar3 + uVar5 * 0x200;
    if ((((uint)iVar7 + 0x3d08u) >> 9) < uVar2) {
      uVar3 = uVar3 + 1;
      cVar6 = '\0';
    } else {
      cVar6 = (char)uVar2 - (char)(((uint)iVar7 + 0x100u) >> 9);
    }
    *param_5 = cVar6;
    uVar1 = uVar1 * 0x1000000;
    *param_4 = uVar1 + uVar3;
    param_4[1] = (uVar4 >> 8) + (uint)((uVar1 + uVar3) < uVar1);
    *param_3 = param_1;
    return;
  }
  while (1) { FUN_010256dc(0x9b,0x96); }
}


