/* Reconstructed FUN_0005c4f0 @ 0x5c4f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned,unsigned);
extern void FUN_0007e2ec(unsigned,unsigned);
extern int FUN_00059c70(void);
extern int FUN_00059e78(int);
extern int FUN_0005a540(int,int*);
extern int FUN_0008270c(int*);
extern void FUN_00082ab8(int,int*);
extern void FUN_00082e24(int,int*);
typedef int (*codef)(int,int*,int);
int FUN_0005c4f0(int param_1, int *param_2, unsigned param_3, unsigned param_4)
{
  int iVar1, iVar2, bVar4, bVar6; int *piVar5;
  if (param_1 == 0) {
    FUN_0007e2fa(0x00099cbd,0x000f3ebd,0x000f46b8,0x14dc,param_4);
    FUN_0007e2fa(0x000f4a0a,0,0,0,0);
    FUN_0007e2ec(0x000f46b8,0x14dc);
  }
  if (param_2 == 0) {
    FUN_0007e2fa(0x00099cbd,0x000f4b3d,0x000f46b8,0x14dd,param_4);
    FUN_0007e2fa(0x000f4a0a,0,0,0,0);
    FUN_0007e2ec(0x000f46b8,0x14dd);
  }
  if (*(char*)(param_1+0xd) != 7) return -0x80;
  iVar1 = FUN_00059c70();
  if ((iVar1 != 0) && (piVar5 = *(int**)(iVar1+8), piVar5 != 0)) {
    bVar4 = 0; bVar6 = 0;
    do {
      if (param_2 == piVar5 + -6) bVar4 = 1;
      else if ((unsigned short)piVar5[-3] == (unsigned short)param_2[3]) bVar6 = 1;
      piVar5 = (int*)*piVar5;
    } while (piVar5 != 0);
    if (bVar4) {
      iVar2 = FUN_0008270c(param_2 + 5);
      if (iVar2 << 0x1d < 0) FUN_00082e24(param_1, param_2);
      if (bVar6) {
        FUN_00082ab8(iVar1+8, param_2+6);
        if (*(int*)(iVar1+8) == 0) FUN_00059e78(iVar1);
        (*(codef)*param_2)(param_1, param_2, 0);
      } else {
        *(volatile short*)(param_2+4) = 0;
        iVar2 = FUN_0005a540(param_1, param_2);
        if (iVar2 != 0) return iVar2;
        FUN_00082ab8(iVar1+8, param_2+6);
        if (*(int*)(iVar1+8) == 0) FUN_00059e78(iVar1);
      }
      return 0;
    }
  }
  return -0x16;
}

