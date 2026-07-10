/* Reconstructed FUN_00022834 @ 0x22834  (parity: 300/300 trials, PROVEN) */

typedef int (*codeptr)(int,...);
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern int FUN_00074844(int,int);
extern int FUN_0008638c(int);
extern int FUN_00086be4(int,int,int);
extern int FUN_00086c78(void*,int,int);

int FUN_00022834(int param_1, int param_2, int param_3)
{
  unsigned int *puVar1;
  int uVar2;
  int iVar3;
  int uVar4;
  codeptr pcVar5;
  int iVar6;
  int local_1028;
  unsigned char auStack_1024[4096];

  local_1028 = 0;
  iVar6 = 1;
  FUN_00086c78(auStack_1024, 0, 0xffc);
  uVar2 = 0x9e430;
  puVar1 = (unsigned int*)0x87bf0;
  do {
    iVar3 = FUN_0008638c(0x87bf0);
    if (iVar3 == 0) {
      DEBUG_PRINT(0xa40ec, *(volatile unsigned int*)puVar1);
      iVar3 = -1;
    } else {
      iVar3 = FUN_000167a8();
      pcVar5 = *(codeptr*)(iVar3 + 0x1030);
      uVar4 = FUN_000167a8();
      iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
      if (iVar3 == 0) {
        iVar3 = FUN_00086be4(param_2, (int)&local_1028, param_3);
        if (iVar3 == 0) {
          DEBUG_PRINT(0x9e403);
          return 0;
        }
        iVar3 = FUN_000167a8();
        pcVar5 = *(codeptr*)(iVar3 + 0x1038);
        uVar4 = FUN_000167a8();
        iVar3 = (*pcVar5)(uVar4, param_1, 0x1000);
        uVar4 = uVar2;
        if (iVar3 == 0) {
          iVar3 = FUN_000167a8();
          pcVar5 = *(codeptr*)(iVar3 + 0x1034);
          uVar4 = FUN_000167a8();
          iVar3 = (*pcVar5)(uVar4, param_1, param_2, param_3);
          uVar4 = 0x9e44d;
          if (iVar3 == 0) {
            iVar3 = FUN_000167a8();
            pcVar5 = *(codeptr*)(iVar3 + 0x1030);
            uVar4 = FUN_000167a8();
            iVar3 = (*pcVar5)(uVar4, param_1, &local_1028, 0x1000);
            uVar4 = 0x9e3e7;
            if (iVar3 == 0) {
              iVar3 = FUN_00086be4(param_2, (int)&local_1028, param_3);
              if (iVar3 == 0) {
                return 0;
              }
              DEBUG_PRINT(0x9e46a);
              iVar3 = 1;
              goto LAB_874;
            }
          }
        }
        DEBUG_PRINT(uVar4, iVar3);
      } else {
        DEBUG_PRINT(0x9e3e7, iVar3);
      }
    }
LAB_874:
    iVar6 = iVar6 + 1;
    if (iVar6 == 0xb) {
      return iVar3;
    }
    FUN_00074844(0xccd, 0);
  } while (1);
}

