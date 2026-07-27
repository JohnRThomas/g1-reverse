/* Reconstructed FUN_00019b54 @ 0x19b54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_0002af4c(char *, unsigned char *, unsigned char *, unsigned int);
uint32_t FUN_00019b54(int param_1,uint8_t* param_2,uint32_t param_3){
  if(*(volatile int*)0x2000230cUL==5){
    volatile uint8_t* pbVar3=*(volatile uint8_t* volatile*)(param_1+0x10);
    DEBUG_PRINT(0x9b2ba,*(volatile uint32_t*)(param_1+0x14),pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3],pbVar3[0],pbVar3[1],pbVar3[2],pbVar3[3]);
  }
  uint32_t uVar2=FUN_0002af4c(param_1-0x77c,*(volatile uint32_t*)(param_1+0x10),param_2,param_3);
  if(*(volatile int*)0x2000230cUL==5){
    DEBUG_PRINT(0x9b2f5,param_3,param_2[0],param_2[1],param_2[2],param_2[3],param_2[0],param_2[1],param_2[2],param_2[3]);
  }
  return uVar2;
}

