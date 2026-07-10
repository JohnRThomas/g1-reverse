/* Reconstructed FUN_0005a9f4 @ 0x5a9f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned int,...);
extern void FUN_0007e2ec(unsigned int,...);
unsigned int FUN_0005a9f4(unsigned int param_1){
  unsigned int uVar1=param_1; volatile unsigned int* puVar2;
  unsigned int uVar3,uVar4,uVar5,uVar6,uVar7;
  if(param_1!=0 && (uVar1=(unsigned int)*(unsigned short*)(param_1+0x10), uVar1==0)){
    puVar2=(volatile unsigned int*)0x00088058UL; uVar4=1;
    while(1){
      if((volatile unsigned int*)0x00088070UL < puVar2){
        FUN_0007e2fa(0x00099cbd,0x000f49a5,0x000f46b8,0x713);
        FUN_0007e2fa(0x000f0d20);
        FUN_0007e2ec(0x000f46b8,0x713);
      }
      if((volatile unsigned int*)0x00088070UL <= puVar2) break;
      uVar7=puVar2[0]; uVar6=puVar2[1];
      if((param_1<uVar7)||(((uVar6*0x14+uVar7)-0x14)<param_1)){
        uVar3=(uVar4+uVar6)&0xffff;
      } else {
        for(uVar5=0; uVar3=(uVar4+uVar5)&0xffff, uVar5!=uVar6; uVar5=uVar5+1){
          if(param_1==uVar5*0x14+uVar7) return uVar3;
        }
      }
      puVar2=puVar2+2; uVar4=uVar3;
    }
  }
  return uVar1;
}

