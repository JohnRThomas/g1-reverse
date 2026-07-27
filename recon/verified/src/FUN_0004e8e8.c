/* Reconstructed FUN_0004e8e8 @ 0x4e8e8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_000868ca(int,int);
int FUN_0004e8e8(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4){
  int iVar1=0x2000a154;
  uint uVar5=((uint)param_1+3)&0xfffffffcu;
  if(uVar5>0x74){ FUN_0007e2fa(0x99cbd,0xf11e7,0xf11bc,0x5b); FUN_0007e2ec(0xf11bc,0x5b); }
  uint uVar3=*(volatile uint*)(0x2000a154UL+0x150);
  uint32_t* puVar2;
  if(uVar3==0 || (uVar3=*(volatile uint*)(0x2000a154UL+0x158)+uVar5, uVar3>0x74)){
    puVar2=(uint32_t*)(uintptr_t)FUN_000868ca(1,0x78);
    if(puVar2==0) return 0;
    *(volatile uint32_t*)puVar2=0;
    if(*(volatile uint32_t*)(iVar1+0x154)==0){
      *(volatile uint32_t*)(iVar1+0x150)=(uint32_t)(uintptr_t)puVar2;
      *(volatile uint32_t*)(iVar1+0x154)=(uint32_t)(uintptr_t)puVar2;
    } else {
      *(volatile uint32_t*)(uintptr_t)(*(volatile uint32_t*)(iVar1+0x154))=(uint32_t)(uintptr_t)puVar2;
      *(volatile uint32_t*)(iVar1+0x154)=(uint32_t)(uintptr_t)puVar2;
    }
    *(volatile uint32_t*)(iVar1+0x158)=0;
  } else {
    puVar2=(uint32_t*)(uintptr_t)*(volatile uint32_t*)(iVar1+0x154);
  }
  int iVar4=*(volatile int*)(iVar1+0x158);
  *(volatile uint32_t*)(iVar1+0x158)=uVar5+iVar4;
  return (int)(uintptr_t)puVar2+iVar4+4;
}

