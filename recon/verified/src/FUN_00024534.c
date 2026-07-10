/* Reconstructed FUN_00024534 @ 0x24534  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern int FUN_0008638c(unsigned);
extern void FUN_00086c04(unsigned,int,int);
extern void FUN_00086c78(unsigned,int,int);

unsigned FUN_00024534(unsigned param_1, unsigned param_2, int param_3, unsigned param_4, int param_5){
  volatile int *piVar1 = (volatile int*)0x2000230cUL;
  int iVar7; unsigned uVar4; unsigned uVar5 = 0;
  if(param_1 >= 4){
    if(*piVar1 < 1) return 0xffffffff;
    iVar7 = *(volatile int*)0x20007554UL;
    uVar4 = 0x0009ee54;
    goto LAB_2arg;
  }
  if(*piVar1 > 2){
    if(*(volatile int*)0x20007554UL == 0)
      DEBUG_PRINT(0x0009ee80,0x0009f066);
    else
      FUN_00019c70();
  }
  {
    int iVar3 = FUN_0008638c(0x00087bf0);
    iVar7 = 0x20018465;
    if(iVar3 == 0){
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)0x20007554UL;
      uVar4 = 0x0009e9ea;
      uVar5 = *(volatile uint32_t*)0x00087bf0UL;
    } else {
      FUN_00086c78(0x20018465,0,0x800);
      int t = FUN_000167a8();
      int (*pcVar8)(unsigned,unsigned,int,int) = *(int(**)(unsigned,unsigned,int,int))(t+0x1030);
      unsigned a = FUN_000167a8();
      iVar3 = pcVar8(a, 0x00403000, iVar7, 0x800);
      if(iVar3 == 0){
        int off = (int)(param_1 * 0x200);
        if(*(char*)(iVar7 + off) == -0x56){
          if(param_3 > 0x28) param_3 = 0x29;
          FUN_00086c04(param_2, off + 1 + iVar7, param_3);
          int iVar6 = 0x119;
          if(param_5 < 0x11a) iVar6 = param_5;
          FUN_00086c04(param_4, off + 0x2a + iVar7, iVar6);
          if(*piVar1 > 2){
            if(*(volatile int*)0x20007554UL == 0){
              DEBUG_PRINT(0x0009eeeb,0x0009f066);
              return 0;
            }
            FUN_00019c70();
            return 0;
          }
          return 0;
        }
        if(*piVar1 < 3) return 0xffffffff;
        iVar7 = *(volatile int*)0x20007554UL;
        uVar4 = 0x0009eead;
        goto LAB_2arg;
      }
      if(*piVar1 < 1) return 0xffffffff;
      iVar7 = *(volatile int*)0x20007554UL;
      uVar4 = 0x0009ea0a;
      uVar5 = 0x00403000;
    }
    if(iVar7 == 0)
      DEBUG_PRINT(uVar4, 0x0009f066, uVar5);
    else
      FUN_00019c70();
    return 0xffffffff;
  }
LAB_2arg:
  if(iVar7 == 0)
    DEBUG_PRINT(uVar4, 0x0009f066);
  else
    FUN_00019c70();
  return 0xffffffff;
}

