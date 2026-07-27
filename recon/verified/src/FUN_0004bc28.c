/* Reconstructed FUN_0004bc28 @ 0x4bc28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00086534(int,int,int);
extern int FUN_00086c78(int,int,int);
void FUN_0004bc28(int param_1, uint32_t *param_2, uint32_t param_3, uint32_t param_4){
  FUN_00086c78(param_1, 0, 0x20);
  *(volatile uint32_t*)(param_1+0x1c) = param_2[3];
  *(volatile uint32_t*)(param_1+0x18) = param_2[2];
  *(volatile uint32_t*)(param_1+0x20) = param_2[0];
  uint32_t uVar3 = param_2[1];
  *(volatile uint32_t*)(param_1+0x28) = 0;
  *(volatile uint32_t*)(param_1+0x24) = uVar3;
  uint32_t uVar2 = param_2[4];
  if(uVar3 != 0 && ((uVar3 - 1) & uVar3) == 0){
    uVar2 |= 1;
  }
  *(volatile uint32_t*)(param_1+0x10) = uVar2;
  int iVar1 = FUN_00086534(param_1+0x2c, 0, 1);
  if(iVar1 != 0){
    FUN_0007e2fa(0x00099cbd, 0x000a7a10, 0x000f0982, 0x2e);
    FUN_0007e2ec(0x000f0982, 0x2e);
  }
}

