/* Reconstructed FUN_0004c1f0 @ 0x4c1f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00084c76(void);
uint32_t FUN_0004c1f0(void){
  volatile uint8_t *pbVar2 = (volatile uint8_t*)0x2001d44aUL;
  uint32_t iVar3 = 0x2000a0b4;
  volatile uint8_t *pcVar4 = (volatile uint8_t*)0x2001d449UL;
  uint32_t uVar7 = ((uint32_t)*pbVar2 + 1) % 5;
  int iVar5 = FUN_00084c76();
  int enter;
  if(*pcVar4 == 0){
    enter = 1;
  } else {
    uint32_t diff = (uint32_t)(iVar5 - *(volatile int*)(iVar3 + uVar7*4));
    enter = (diff > 7);
  }
  if(!enter){
    return 0;
  }
  if(*(volatile uint32_t*)0x50005114UL != 0){
    *(volatile uint32_t*)0x50005114UL = 0;
    (void)*(volatile uint32_t*)0x50005114UL;
    *pbVar2 = (uint8_t)uVar7;
    if(uVar7 == 0){
      *pcVar4 = 1;
    }
  }
  uint8_t bVar1 = *pbVar2;
  uint32_t uVar6 = FUN_00084c76();
  *(volatile uint32_t*)(iVar3 + (uint32_t)bVar1*4) = uVar6;
  return 1;
}

