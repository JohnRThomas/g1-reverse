/* Reconstructed FUN_00026c28 @ 0x26c28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
extern unsigned int FUN_00019b2c(void);
int FUN_00026c28(void){
  int iVar2 = FUN_000167a8();
  int iVar3 = FUN_000167a8();
  int cVar1 = FUN_00019b2c();
  if(*(volatile uint8_t*)0x20018d91UL == 3 && (uint8_t)cVar1 != 0){
    int pcVar4 = FUN_000167a8();
    int v = *(volatile uint8_t*)pcVar4;
    uint8_t r3b = *(volatile uint8_t*)(iVar3+0x6de);
    if(v != 1){
      *(volatile uint8_t*)(iVar3+0x6de) = r3b | 1;
    } else {
      if(r3b & 1){
        *(volatile uint8_t*)(iVar2+0xe4) = *(volatile uint8_t*)(iVar2+0xe4) | 3;
      }
    }
  }
  return (*(volatile uint8_t*)(iVar2+0xe4) & 3) == 3;
}

