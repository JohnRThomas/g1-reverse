/* Reconstructed FUN_0004e540 @ 0x4e540  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa(uint32_t,...);
extern int FUN_0007f1a0(uint32_t,uint32_t,void*);

uint32_t* FUN_0004e540(uint32_t param_1, uint32_t *param_2, uint32_t param_3){
  uint32_t *puVar1, *puVar3, *puVar5;
  int *piVar4;
  int iVar2;
  uint32_t uVar6, uVar7;
  volatile uint32_t *local_24;
  volatile uint32_t uStack_20;
  if (param_2 != 0) *param_2 = 0;
  puVar1 = (uint32_t*)0x88328;
  puVar5 = 0;
  puVar3 = (uint32_t*)0x882b0;
  uVar7 = param_1;
  local_24 = param_2;
  uStack_20 = param_3;
  while (1){
    if (puVar1 < puVar3){
      FUN_0007e2fa(0x99cbd, 0xf1158, 0xf1126, 0x94, uVar7);
      FUN_0007e2fa(0xf0d20);
      FUN_0007e2ec(0xf1126, 0x94);
    }
    if (puVar1 <= puVar3) break;
    uVar6 = *puVar3;
    iVar2 = FUN_0007f1a0(param_1, uVar6, (void*)&local_24);
    if (iVar2 != 0 && (puVar5 == 0 || (iVar2 = FUN_0007f1a0(uVar6, *puVar5, 0), iVar2 != 0))
        && (puVar5 = puVar3, param_2 != 0)){
      *param_2 = (uint32_t)local_24;
    }
    puVar3 = puVar3 + 5;
  }
  for (piVar4 = (int*)*(volatile uint32_t*)0x2000a10c; piVar4 != 0; piVar4 = (int*)*piVar4){
    uVar7 = piVar4[-5];
    iVar2 = FUN_0007f1a0(param_1, uVar7, (void*)&local_24);
    if (iVar2 != 0 && ((puVar5 == 0 || (iVar2 = FUN_0007f1a0(uVar7, *puVar5, 0), iVar2 != 0))
        && (puVar5 = (uint32_t*)(piVar4 - 5), param_2 != 0))){
      *param_2 = (uint32_t)local_24;
    }
  }
  return puVar5;
}

