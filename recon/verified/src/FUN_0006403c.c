/* Reconstructed FUN_0006403c @ 0x6403c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0007ef80(int, int, void*, ...);
extern int FUN_00084d8c(int, void*, int);
extern int FUN_00086be4(void*, uint32_t, int);
extern uint32_t FUN_00084d64(int);
extern int FUN_00084db2(int, void*, int);
extern uint32_t FUN_00084e66(int, void*);

uint32_t FUN_0006403c(int param_1, uint8_t *param_2){
  int iVar1;
  uint32_t uVar2;
  uint8_t uVar3;
  volatile uint8_t local_21;
  uint8_t auStack_20[20];
  iVar1 = FUN_0007ef80(param_1, *(int*)(param_1+8) - 0x10,
                       auStack_20, 0x10);
  if (iVar1 >= 0){
    iVar1 = FUN_00084d8c(param_1, auStack_20, 0x10);
    if (iVar1 == 0){
      iVar1 = FUN_00086be4(auStack_20, 0x9907c, 0x10);
      uVar3 = (iVar1 == 0) ? 1 : 2;
    } else {
      uVar3 = 3;
    }
    *param_2 = uVar3;
    uVar2 = FUN_00084d64(param_1);
    iVar1 = FUN_0007ef80(param_1, (int)uVar2, (void*)&local_21, 1);
    if (iVar1 >= 0){
      param_2[1] = local_21 & 0xf;
      param_2[4] = local_21 >> 4;
      iVar1 = FUN_00084d8c(param_1, (void*)&local_21, 1);
      if (iVar1 != 0 || param_2[1] > 4){
        param_2[1] = 1;
        param_2[4] = 0;
      }
      iVar1 = FUN_00084db2(param_1, param_2 + 2, ((*(int*)(param_1+8) - 0x18) & 0xfffffff8) - 8);
      if (iVar1 == 0){
        uVar2 = FUN_00084e66(param_1, param_2 + 3);
        return uVar2;
      }
    }
  }
  return 1;
}
