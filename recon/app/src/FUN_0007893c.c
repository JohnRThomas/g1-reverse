/* Reconstructed FUN_0007893c @ 0x7893c  (parity: 134/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int uint;
extern uint32_t FUN_00076a94(uint32_t,int,int,uint32_t);
extern uint32_t FUN_00076d6c(int);
extern void FUN_00078654(int,uint32_t);
extern uint32_t FUN_00078698(int,uint32_t,uint32_t,int,uint32_t);
extern uint32_t FUN_000787bc(int,int);
extern uint32_t FUN_000787e8(int,uint32_t,uint32_t);

uint32_t FUN_0007893c(int param_1, uint32_t param_2, uint param_3, uint32_t param_4){
  uint32_t *puVar1, *puVar2;
  int iVar3, iVar5;
  uint32_t uVar4;
  if ((param_3 & 3) != 0){
    param_2 = FUN_00078698(param_1, param_2, *(uint32_t*)(0x98774 + ((param_3&3)-1)*4), 0, param_4);
  }
  iVar3 = (int)param_3 >> 2;
  if (iVar3 != 0){
    if (*(int*)(param_1+0x24) == 0){
      puVar1 = (uint32_t*)FUN_00076d6c(0x10);
      *(uint32_t**)(param_1+0x24) = puVar1;
      if (puVar1 == 0){
        puVar1 = (uint32_t*)FUN_00076a94(0xf8cd5, 0x1ae, 0, 0xf8bb7);
      }
      puVar1[1] = 0; puVar1[2] = 0; puVar1[0] = 0; puVar1[3] = 0;
    }
    iVar5 = *(int*)(param_1+0x24);
    puVar1 = *(uint32_t**)(iVar5+8);
    uVar4 = param_2;
    if (puVar1 == 0){
      puVar1 = (uint32_t*)FUN_000787bc(param_1, 0x271);
      *(uint32_t**)(iVar5+8) = puVar1;
      puVar1[0] = 0;
    }
    while (1){
      puVar2 = puVar1;
      param_2 = uVar4;
      if (iVar3 & 1){
        param_2 = FUN_000787e8(param_1, uVar4, (uint32_t)puVar2);
        FUN_00078654(param_1, uVar4);
      }
      iVar3 = iVar3 >> 1;
      if (iVar3 == 0) break;
      puVar1 = (uint32_t*)*puVar2;
      uVar4 = param_2;
      if (*puVar2 == 0){
        puVar1 = (uint32_t*)FUN_000787e8(param_1, (uint32_t)puVar2, (uint32_t)puVar2);
        *puVar2 = (uint32_t)puVar1;
        puVar1[0] = 0;
      }
    }
  }
  return param_2;
}

