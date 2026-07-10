/* Reconstructed FUN_0004d678 @ 0x4d678  (parity: 298/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d334(int);
extern int FUN_0004d594(void);
extern int FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
void FUN_0004d678(void){
  volatile uint8_t *pcVar1 = (volatile uint8_t*)0x2001d44cUL;
  if(*pcVar1 == 0){
    FUN_0004d334(1);
    uint32_t piVar4 = 0x000882a0;
    uint32_t piVar2 = 0x000882b0;
    while(1){
      if(piVar4 > piVar2){
        FUN_0007e2fa(0x00099cbd, 0x000f0cff, 0x000f0cae, 0x188);
        FUN_0007e2fa(0x000f0d20);
        FUN_0007e2ec(0x000f0cae, 0x188);
      }
      if(piVar4 == piVar2) break;
      uint32_t e = *(volatile uint32_t*)(piVar4+4);
      if(*(volatile uint8_t*)(e+5) != 0){
        uint32_t f = *(volatile uint32_t*)(*(volatile uint32_t*)piVar4 + 8);
        ((void(*)(uint32_t))(uintptr_t)f)(piVar4);
      }
      piVar4 += 0x10;
    }
    int iVar3;
    do { iVar3 = FUN_0004d594(); } while(iVar3 != 0);
    *pcVar1 = 1;
  }
}

