/* Reconstructed FUN_0005e6d4 @ 0x5e6d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_0005e6d4(uint32_t param_1, void* param_2, uint32_t param_3){
  volatile uint32_t local_20; volatile uint8_t local_1c[8];
  (void)local_1c;
  if(param_2==0){
    FUN_0007e2fa(0x99cbd,0xf52c0,0xf5268,0xa0);
    FUN_0007e2ec(0xf5268,0xa0);
  }
  if(*(volatile int16_t*)(0x2000af4cUL+0xe)!=0 && *(volatile uint8_t*)0x2000af4cUL==param_1){
    local_20=*(volatile uint32_t*)(0x2000af4cUL+1);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
  if(*(volatile int16_t*)(0x2000af4cUL+0x6a)!=0 && *(volatile uint8_t*)(0x2000af4cUL+0x5c)==param_1){
    local_20=*(volatile uint32_t*)(0x2000af4cUL+0x5d);
    ((void(*)(void*,uint32_t))param_2)((void*)&local_20,param_3);
  }
}

