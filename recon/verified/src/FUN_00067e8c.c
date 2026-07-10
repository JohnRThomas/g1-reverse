/* Reconstructed FUN_00067e8c @ 0x67e8c  (parity: 1/400 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_00067e8c(int* param_1, uint8_t* param_2){
  uint8_t r4byte=*(volatile uint8_t*)((char*)param_1+4);
  if(param_2==0){
    FUN_0007e2fa(0x99cbd,0xf7a32,0xf79c8,0xa2);
    FUN_0007e2ec(0xf79c8,0xa2);
  }
  int iVar6=(int)(0x2000b41cUL + (uint)r4byte*8);
  while(*(volatile uint8_t*)iVar6 != 1){
    FUN_0007e2fa(0x99cbd,0xf7052,0xf79c8,0xa3);
    FUN_0007e2ec(0xf79c8,0xa3);
  }
  uint8_t bVar1=*(volatile uint8_t*)(iVar6+1);
  uint32_t uVar4=0x0bad0002;
  if(bVar1<8){
    *param_2=bVar1;
    *(volatile uint8_t*)(iVar6+1)=bVar1+1;
    uVar4=0x0bad0000;
    *(volatile uint32_t*)(*(volatile int*)param_1+0x508)=(1u<<bVar1)|*(volatile uint32_t*)(*(volatile int*)param_1+0x508);
  }
  return uVar4;
}

