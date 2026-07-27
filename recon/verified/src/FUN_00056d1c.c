/* Reconstructed FUN_00056d1c @ 0x56d1c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
void FUN_00056d1c(int param_1){
  int iVar4 = (*(volatile int8_t*)(param_1+3)==0) ? param_1+0x9e : param_1+0x97;
  int iVar2=*(volatile int*)0x2000ad1cUL;
  while(iVar2!=0){
    int t=*(volatile int*)(iVar2+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    iVar2=*(volatile int*)(iVar2+0x20);
  }
  uint uVar1=0x88058;
  uint uVar3=0x87fec;
  while(1){
    if(uVar1<uVar3){
      FUN_0007e2fa(0x99cbd,0xf3a8d,0xf3a5d,0x85c);
      FUN_0007e2fa(0xf0d20,0,0,0);
      FUN_0007e2ec(0xf3a5d,0x85c);
    }
    if(uVar1<=uVar3) break;
    int t=*(volatile int*)(uVar3+0x10);
    if(t!=0) ((void(*)(int,int,int))t)(param_1,iVar4,param_1+0x90);
    uVar3=uVar3+0x24;
  }
}

