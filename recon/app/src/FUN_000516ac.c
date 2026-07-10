/* Reconstructed FUN_000516ac @ 0x516ac  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004e048(int,...);
extern int FUN_0005169c(int,...);
extern int FUN_00076a94(int,...);
extern int FUN_0007ef7e(int,...);
extern int FUN_0007ef80(int,...);
extern int FUN_0007efd4(int,...);
extern int FUN_0007f012(int,...);
extern int FUN_0008096a(int,...);
int FUN_000516ac(void)
{
  unsigned int uVar1;
  int iVar5;
  int local_6c, local_64;
  int aiStack_60[17];
  int dummy[16];
  uVar1 = (unsigned int)FUN_0005169c(0);
  if ((int)uVar1 < 0) {
    iVar5 = 0xe;
  } else {
    local_6c = FUN_0004e048(uVar1 & 0xff, &local_64);
    iVar5 = local_64;
    if (local_6c < 0) {
      FUN_0008096a(0x88208, 0x2040, dummy);
      iVar5 = 10;
    } else {
      uVar1 = *(volatile unsigned int*)(local_64 + 8) & 3;
      if (uVar1 != 0) FUN_00076a94(0xf2634, 0x43, 0xf270e, 0xf261f);
      int iVar2 = FUN_0007f012(iVar5);
      int iVar7 = *(volatile int*)(iVar5 + 8);
      for (; (int)uVar1 < iVar7; uVar1 = uVar1 + 0x40) {
        int iVar6 = iVar7 - uVar1;
        if (0x3f < iVar6) iVar6 = 0x40;
        int iVar3 = FUN_0007ef80(iVar5, uVar1, aiStack_60, iVar6);
        if (iVar3 < 0) {
          FUN_0008096a(0x88208, 0x1840, dummy);
          iVar5 = 0xb;
          goto LAB;
        }
        int *piVar4 = aiStack_60;
        for (iVar3 = 0; iVar3 != iVar6 >> 2; iVar3 = iVar3 + 1) {
          if (*piVar4 != iVar2 * 0x1010101) {
            iVar5 = FUN_0007efd4(local_64, 0, *(volatile int*)(local_64 + 8));
            if (iVar5 != 0) {
              FUN_0008096a(0x88208, 0x1840, dummy);
              iVar5 = 0xd;
            }
            goto LAB;
          }
          piVar4 = piVar4 + 1;
        }
      }
      iVar5 = 1;
    LAB:
      FUN_0007ef7e(local_64);
    }
  }
  return iVar5;
}

