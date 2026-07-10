#include "g1_app_symbols.h"
/* named: img_mgmt_erase_slot */
/* Reconstructed img_mgmt_erase_slot @ 0x52604  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0004d944(uint32_t,int,void*,...);
extern int flash_area_open(int, void*);
extern int smp_add_cmd_err(int,int,uint32_t);
extern void nullsub_3(int);
extern int FUN_0007efd4(int,int,uint32_t,int);
extern int FUN_0007f00e(int);

uint32_t img_mgmt_erase_slot(int param_1){
  int iVar1;
  uint32_t uVar2;
  int iVar3;
  volatile int local_2c[5];
  volatile uint32_t local_18;
  volatile void* local_14;
  iVar3 = *(int*)(param_1+8);
  iVar1 = flash_area_open(9, (void*)local_2c);
  if (iVar1 < 0){
    uVar2 = 2;
    local_18 = 2;
    local_14 = (void*)"Failed to open flash area" /*=0xf289a*/;
    FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88220*/, 0x1040, (void*)&local_18, 0);
  } else {
    iVar1 = FUN_0007f00e(local_2c[0]);
    if (iVar1 == 0){
      local_14 = (void*)"Failed to get flash area device" /*=0xf28b4*/;
      local_18 = 2;
      FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88220*/, 0x1040, (void*)&local_18);
      nullsub_3(local_2c[0]);
      uVar2 = 3;
    } else {
      uVar2 = (uint32_t)FUN_0007efd4(local_2c[0], 0, *(uint32_t*)(local_2c[0]+8), iVar1);
      if ((int)uVar2 < 0){
        local_14 = (void*)"Failed to erase flash area" /*=0xf28d4*/;
        local_18 = 2;
        FUN_0004d944(((uintptr_t)&tbl_880d8) /*=0x88220*/, 0x1040, (void*)&local_18, 0);
        nullsub_3(local_2c[0]);
        uVar2 = 4;
      } else {
        nullsub_3(local_2c[0]);
        if (uVar2 == 0) return 0;
      }
    }
  }
  iVar1 = smp_add_cmd_err(iVar3+4, 0x3f, uVar2 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/);
  if (iVar1 != 0) return 0;
  return 7;
}

