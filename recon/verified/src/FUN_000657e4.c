/* Reconstructed FUN_000657e4 @ 0x657e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
typedef unsigned long long u64;
extern u64 FUN_00065434(unsigned);
extern int FUN_00065460(unsigned);
extern u64 FUN_00065478(unsigned);
extern int FUN_00065494(unsigned);
extern void FUN_00085130(unsigned,void*,int,int,int,int);
unsigned FUN_000657e4(unsigned param_1, unsigned param_2, unsigned char *param_3)
{
  unsigned char bVar1,bVar2,bVar3;
  int iVar4,iVar6,iVar7;
  unsigned uVar5;
  unsigned short uVar8;
  u64 uVar9, uVar10;
  unsigned char enable = 1;
  uVar9 = FUN_00065434(param_1);
  if ((int)(uVar9 >> 0x20) != 0) {
    iVar4 = FUN_00065494(param_1);
    if ((iVar4 == 0) && (iVar4 = FUN_00065460(param_1), iVar4 != 0)) {
      return 0x0bad0004;
    }
    uVar10 = FUN_00065478(param_1);
    iVar4 = (int)(uVar10 >> 0x20);
    if (((int)uVar10 != 0) && (*(char*)(iVar4 + 1) == 1)) {
      return 0x0bad0004;
    }
    FUN_00085130(param_1, &enable, iVar4 + 1, iVar4 + 2, iVar4, 0);
    iVar4 = (int)uVar9 + 8;
    *(volatile unsigned short*)(0x20002bc0 + iVar4 * 2) =
        *(volatile unsigned short*)(0x20002bc0 + iVar4 * 2) | 3;
  }
  uVar5 = 0x0bad0000;
  if ((param_3 != 0) &&
      (iVar6 = FUN_00065494(param_1), iVar4 = 0x20002bc0, uVar5 = 0x0bad0004, iVar6 != 0)) {
    bVar3 = *param_3;
    iVar6 = (int)uVar9 + 8;
    iVar7 = (unsigned)bVar3 * 4;
    uVar8 = *(volatile unsigned short*)(0x20002bc0 + iVar6 * 2) & 0x1fdf;
    *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = 0;
    *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8;
    *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = 0;
    bVar1 = param_3[1];
    uVar5 = 0x0bad0000;
    if (bVar1 != 0) {
      bVar2 = param_3[2];
      *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) = *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) & 0xffecc0ff;
      *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) =
          (param_1 & 0x3f) << 8 | (bVar1 & 3) << 0x10 | *(volatile unsigned*)(iVar7 + (G1_NRF_GPIOTE0_S_BASE + 0x510)) |
          (bVar2 & 1) << 0x14;
      *(volatile unsigned short*)(iVar4 + iVar6 * 2) = uVar8 | (unsigned short)bVar3 << 0xd | 0x20;
      uVar5 = 0x0bad0000;
    }
  }
  return uVar5;
}
