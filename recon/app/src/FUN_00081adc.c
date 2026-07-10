/* Reconstructed FUN_00081adc @ 0x81adc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_00057394(void);
extern int FUN_000573f4(int,int,int);
extern int FUN_0005f24c(int);
extern void* FUN_0005f5d0(int,int);
extern int FUN_00081820(int,int,int,int,int,int);
int FUN_00081adc(int param_1, int param_2){
  unsigned long long uVar5 = (unsigned long long)FUN_00057394();
  volatile uint16_t *puVar4 = (volatile uint16_t*)(uintptr_t)(uint32_t)(uVar5 >> 32);
  int iVar1 = FUN_000573f4(0x12, (int)(uint32_t)uVar5, 8);
  if(iVar1 == 0){
    return -0xc;
  }
  volatile uint16_t *puVar2 = (volatile uint16_t*)FUN_0005f5d0(iVar1+0xc, 8);
  puVar2[0] = puVar4[0];
  puVar2[1] = puVar4[1];
  puVar2[2] = puVar4[2];
  puVar2[3] = puVar4[3];
  int iVar3 = FUN_00081820(param_1, 5, iVar1, 0, 0, param_2);
  if(iVar3 != 0){
    FUN_0005f24c(iVar1);
  }
  return iVar3;
}

