/* Reconstructed FUN_0004e6a8 @ 0x4e6a8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000530c4(int,...);
extern void FUN_0007e2ec(int,...);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_0007f1a0(int,...);
int FUN_0004e6a8(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned *puVar1 = (unsigned*)0x88328UL;
  unsigned *puVar3 = (unsigned*)0x882b0UL;
  int iVar2=0;
  int iVar5=0;
  while(1){
    if(puVar1 < puVar3){
      FUN_0007e2fa(0x99cbd,0xf1158,0xf1126,0xf4,param_4);
      FUN_0007e2fa(0xf0d20);
      FUN_0007e2ec(0xf1126,0xf4);
    }
    if(puVar1 <= puVar3) break;
    if(((param_1!=0) && (iVar2=FUN_0007f1a0(puVar3[0],param_1,0), iVar2==0)) ||
       ((((void*)puVar3[3]==0) || (iVar2=((int(*)(void))puVar3[3])(), iVar5!=0)))){
      iVar2=iVar5;
    }
    puVar3 += 5;
    iVar5 = iVar2;
  }
  int *piVar4;
  for(piVar4=(int*)*(volatile unsigned*)0x2000a10cUL; piVar4!=0; piVar4=(int*)*piVar4){
    if((((param_1==0)||(iVar2=FUN_0007f1a0(piVar4[-5],param_1,0),iVar2!=0)) &&
        ((void*)piVar4[-2]!=0)) && (iVar2=((int(*)(void))piVar4[-2])(),iVar5==0)){
      iVar5=iVar2;
    }
  }
  return iVar5;
}

