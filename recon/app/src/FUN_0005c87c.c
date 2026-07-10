/* Reconstructed FUN_0005c87c @ 0x5c87c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00059b5c(int,int);
extern int FUN_0005a8bc(int,int);
extern int FUN_0005c80c(int,int);
extern int FUN_00080f92(int,int);
extern int FUN_000828da(int,int);
extern int FUN_00082c9c(int,int,int,void*);
void FUN_0005c87c(int param_1, uint32_t param_2, uint32_t param_3){
  int iVar3 = param_1 + 0x90;
  uint32_t local[2];
  local[0] = param_2;
  local[1] = param_3;
  int iVar1 = FUN_00080f92(*(volatile uint8_t*)(param_1+8), iVar3);
  FUN_00082c9c(1, 0xffff, 0x0005a2fd, local);
  if(iVar1 != 0){
    FUN_0005c80c(*(volatile uint8_t*)(param_1+8), iVar3);
  }
  int iVar2 = FUN_00059b5c(*(volatile uint8_t*)(param_1+8), param_2);
  if(iVar2 != 0){
    FUN_000828da(iVar2+1, param_3);
    if(iVar1 != 0){
      FUN_0005a8bc(*(volatile uint8_t*)(param_1+8), iVar3);
    }
  }
}

