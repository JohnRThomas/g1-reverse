/* Reconstructed FUN_00052604 @ 0x52604  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0004d944(uint32_t,int,void*,...);
extern int FUN_0004e048(int, void*);
extern int FUN_0005160c(int,int,uint32_t);
extern void FUN_0007ef7e(int);
extern int FUN_0007efd4(int,int,uint32_t,int);
extern int FUN_0007f00e(int);

uint32_t FUN_00052604(int param_1){
  int iVar1;
  uint32_t uVar2;
  int iVar3;
  volatile int local_2c[5];
  volatile uint32_t local_18;
  volatile void* local_14;
  iVar3 = *(int*)(param_1+8);
  iVar1 = FUN_0004e048(9, (void*)local_2c);
  if (iVar1 < 0){
    uVar2 = 2;
    local_18 = 2;
    local_14 = (void*)0xf289a;
    FUN_0004d944(0x88220, 0x1040, (void*)&local_18, 0);
  } else {
    iVar1 = FUN_0007f00e(local_2c[0]);
    if (iVar1 == 0){
      local_14 = (void*)0xf28b4;
      local_18 = 2;
      FUN_0004d944(0x88220, 0x1040, (void*)&local_18);
      FUN_0007ef7e(local_2c[0]);
      uVar2 = 3;
    } else {
      uVar2 = (uint32_t)FUN_0007efd4(local_2c[0], 0, *(uint32_t*)(local_2c[0]+8), iVar1);
      if ((int)uVar2 < 0){
        local_14 = (void*)0xf28d4;
        local_18 = 2;
        FUN_0004d944(0x88220, 0x1040, (void*)&local_18, 0);
        FUN_0007ef7e(local_2c[0]);
        uVar2 = 4;
      } else {
        FUN_0007ef7e(local_2c[0]);
        if (uVar2 == 0) return 0;
      }
    }
  }
  iVar1 = FUN_0005160c(iVar3+4, 0x3f, uVar2 & 0xffff);
  if (iVar1 != 0) return 0;
  return 7;
}

