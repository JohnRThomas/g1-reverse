/* Reconstructed FUN_0004792c @ 0x4792c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_0004790c(int,...);
extern int FUN_0007d84c(int,...);
extern int FUN_00086c78(int,...);
typedef int (*codeptr)(int,...);
unsigned int FUN_0004792c(unsigned int param_1, short param_2, short param_3)
{
  unsigned int uVar1 = 0;
  int iVar2;
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  volatile int *E = (volatile int*)0x20007554UL;
  unsigned char dummy[16];
  unsigned short lh[4];
  unsigned int uVar3 = ((int)param_2 * (int)param_3) & 0xffff;
  if (param_1 - 0x20 < 0x60) {
    uVar1 = (unsigned int)FUN_0007d84c(param_1 & 0xff, uVar3);
  } else {
    iVar2 = FUN_000167a8(0);
    if (*(int*)(iVar2 + 0x1030) != 0) {
      iVar2 = FUN_000167a8(0);
      codeptr pcVar6 = *(codeptr*)(iVar2 + 0x1030);
      int u = FUN_000167a8(0);
      iVar2 = pcVar6(u, (param_1 - 0xa4)*4 + 0x140000, (int)lh);
      if (iVar2 != 0) {
        if (0 < *piVar1) {
          if (*E == 0) DEBUG_PRINT(0xbbfee, 0xd750b);
          else FUN_00019c70(0);
        }
        return 0;
      }
      DEBUG_PRINT(0xd74f4, (unsigned int)lh[0], (unsigned int)lh[1]);
      unsigned int puVar4 = (uVar3 >> 2) * (unsigned int)lh[1];
      if (uVar3 == 0x1b0) puVar4 = 0xcf120 + puVar4;
      FUN_00086c78((int)dummy, 0, uVar3);
      iVar2 = FUN_000167a8(0);
      pcVar6 = *(codeptr*)(iVar2 + 0x1030);
      u = FUN_000167a8(0);
      iVar2 = pcVar6(u, puVar4 + 0x200000, (int)dummy, uVar3 >> 2);
      if ((iVar2 != 0) && (0 < *piVar1)) {
        if (*E == 0) DEBUG_PRINT(0xa1ce0, 0xd750b, iVar2);
        else FUN_00019c70(0);
      }
    }
    uVar1 = 0x2001cf92;
    FUN_0004790c((int)dummy, uVar3, 0x2001cf92);
  }
  return uVar1;
}

