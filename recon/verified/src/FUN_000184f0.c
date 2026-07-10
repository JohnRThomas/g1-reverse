/* Reconstructed FUN_000184f0 @ 0x184f0  (parity: 161/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_000182c8(int,...);
extern int FUN_00018334(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_00032ee4(int,...);
extern int FUN_0004c0a8(int,...);
extern int FUN_0007c0a8(int,...);
extern int FUN_0008149a(int,...);
extern int FUN_000814e2(int,...);
extern int FUN_00081526(int,...);
extern int FUN_00086be4(int,...);
void FUN_000184f0(int param_1, int param_2, int param_3)
{
  unsigned char stack38[32];
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  volatile int *piVar2 = (volatile int*)0x20006a34UL;
  volatile int *E = (volatile int*)0x20007554UL;
  int uVar3 = FUN_00081526(0);
  FUN_00018334(uVar3, (int)stack38);
  int iVar5 = *piVar1;
  if (param_3 == 0) {
    if (2 < iVar5) {
      if (*E == 0) DEBUG_PRINT(0x9a52b,0x9b229,(int)stack38,param_2);
      else FUN_00019c70(0x9a52b,0x9b229,(int)stack38,param_2);
    }
    unsigned int uVar4 = (unsigned int)FUN_000814e2(param_1);
    if (1 < uVar4) {
      *(volatile int*)0x20006ab4UL = 0;
      uVar3 = FUN_00081526(param_1);
      iVar5 = FUN_00032ee4(0);
      if (iVar5 == 0) {
        iVar5 = FUN_000167a8(0);
        if (*(char*)(iVar5+0x1070) == 1) {
          iVar5 = FUN_000167a8(0);
          iVar5 = FUN_00086be4(iVar5+0x1069, uVar3, 7);
          if (iVar5 == 0) FUN_000182c8(param_1);
        }
      }
    }
    *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL + 0x367) = 0;
    *piVar2 = 0;
  } else {
    if (2 < iVar5) {
      if (*E == 0) goto LAB_185da;
      FUN_00019c70(0x9a53f,0x9b229,(int)stack38,param_2,param_3);
    }
    while (1) {
      iVar5 = *piVar2;
      *piVar2 = iVar5 + 1;
      if (iVar5 + 1 < 10) break;
      if (0 < *piVar1) {
        if (*E == 0) DEBUG_PRINT(0x9a56b,0x9b229);
        else FUN_00019c70(0);
      }
      FUN_0007c0a8(500);
      FUN_0004c0a8(1);
    LAB_185da:
      DEBUG_PRINT(0x9a53f,0x9b229,(int)stack38,param_2);
    }
    FUN_0008149a(param_1,2);
  }
}

