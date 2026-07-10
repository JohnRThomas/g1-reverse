/* Reconstructed send_dmic_msg @ 0x19ed4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned,...);
extern int FUN_0002ecf4(void);
extern int FUN_0002ed00(void*);
extern void FUN_0007cbfe(int,int);
extern void FUN_00086c78(void*,int,int);
extern unsigned long long thunk_FUN_00074f68(void);
typedef int (*cf)(void*,int);
int send_dmic_msg(int param_1)
{
  unsigned char bVar1; volatile unsigned char *pbVar3; volatile int *piVar4; int iVar5, iVar8;
  unsigned local_e4; unsigned char auStack_e0[204];
  local_e4 = 0;
  FUN_00086c78(auStack_e0, 0, 199);
  piVar4 = (volatile int*)0x20007558;
  pbVar3 = (volatile unsigned char*)0x20010321;
  ((unsigned char*)&local_e4)[0] = 0xf1;
  do {
    ((unsigned char*)&local_e4)[1] = *pbVar3;
    iVar5 = FUN_0002ecf4();
    if (iVar5 == 0) return 0;
    iVar5 = FUN_0002ed00((char*)&local_e4 + 2);
    if (iVar5 != 0) return iVar5;
    iVar5 = (*(cf*)(param_1 + 0xc))(&local_e4, 0xca);
    if ((iVar5 < 0) && (iVar8 = *piVar4, *piVar4 = iVar8 + 1, 9 < iVar8 + 1)) {
      unsigned uVar6 = FUN_000167a8();
      FUN_0007cbfe(uVar6, 1);
      if (0 < *(int*)0x2000230c) {
        if (*(int*)0x20007554 == 0) DEBUG_PRINT(0x0009b45e, 0x0009e0a4, *piVar4);
        else FUN_00019c70(0x0009b45e, 0x0009e0a4, *piVar4);
      }
      *piVar4 = 0;
      return iVar5;
    }
    if (*(int*)0x2000755c + 1 < 100) {
      *(volatile int*)0x2000755c = *(int*)0x2000755c + 1;
    } else {
      *(volatile int*)0x2000755c = 0;
      unsigned long long uVar10 = thunk_FUN_00074f68();
      iVar5 = *(int*)0x20007560;
      *(volatile int*)0x20007560 = iVar5 + 1;
      if (0 < *(int*)0x2000230c) {
        if (*(int*)0x20007554 == 0)
          DEBUG_PRINT(0x0009b482, 0x0009e0a4, (iVar5 + 1) * 100, *piVar4, (unsigned)uVar10, (unsigned)(uVar10 >> 32));
        else FUN_00019c70(0x0009b482);
      }
    }
    bVar1 = *pbVar3;
    *pbVar3 = bVar1 + 1;
  } while (((bVar1 + 1) & 3) != 0);
  return 0;
}

