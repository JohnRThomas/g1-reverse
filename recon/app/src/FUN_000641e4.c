/* Reconstructed FUN_000641e4 @ 0x641e4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00063ff8(char*);
extern int FUN_0006403c(char*, void*);
extern int FUN_000640e8(char*, uint32_t, int);
extern void FUN_00076a94(uint32_t,int,uint32_t,uint32_t);
extern void FUN_0007efd4(char*, int, uint32_t);
extern int FUN_00084e58(char*);

int FUN_000641e4(char *param_1, int param_2, int param_3){
  volatile uint8_t local[12];
  *(char * volatile *)local = param_1;
  *(volatile int*)(local+4) = param_2;
  *(volatile int*)(local+8) = param_3;
  int iVar3 = param_3;
  if (param_2 != 0) iVar3 = param_2;
  int iVar2 = FUN_0006403c(param_1, (void*)local);
  if (iVar2 != 0) return iVar2;
  uint32_t uVar4 = local[0];
  if (uVar4 == 2){
    if (param_2 == 0){
      FUN_0007efd4(param_1, 0, *(uint32_t*)(param_1+8));
      return 3;
    }
  } else {
    if (uVar4 == 3){
      if (param_2 != 0) return 0;
      iVar2 = FUN_00063ff8(param_1);
      if (iVar2 != 0) return iVar2;
      uint32_t uVar5;
      if (iVar3 == 0){ uVar5 = 2; }
      else {
        iVar3 = FUN_00084e58(param_1);
        uVar5 = 3;
        if (iVar3 != 0) return iVar3;
      }
      char cVar1 = *param_1;
      int bVar6 = 0;
      if (cVar1 != 4 && cVar1 != 2){
        if (cVar1 == 1) bVar6 = 1;
        else bVar6 = (cVar1 == 8);
      }
      return FUN_000640e8(param_1, uVar5, bVar6);
    }
    if (uVar4 == 1){
      if (param_2 == 0) return 0;
      if (local[3] != 3) return 0;
      return FUN_00084e58(param_1);
    }
    FUN_00076a94(0xf68d7, 0x22e, 0xf692c, 0xf7a30);
  }
  return 4;
}

