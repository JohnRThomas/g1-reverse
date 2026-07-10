/* Reconstructed FUN_00065620 @ 0x65620  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000655ec(unsigned int);
unsigned int FUN_00065620(unsigned int param_1){
  unsigned int uVar3=0,uVar4=0,uVar2;
  int iVar1;
  do{
    iVar1=FUN_000655ec(uVar3&0xff);
    uVar2=1u<<((((unsigned int)(iVar1-0x100))>>2)&0xff);
    if((param_1&uVar2)!=0){
      if(*(volatile int*)(iVar1+0x5000d000)!=0){
        *(volatile int*)(iVar1+0x5000d000)=0;
        (void)*(volatile int*)(iVar1+0x5000d000);
        uVar4|=uVar2;
      }
    }
    uVar3++;
  }while(uVar3!=8);
  if(*(volatile int*)(0x5000d000+0x17c)!=0){
    *(volatile int*)(0x5000d000+0x17c)=0;
    (void)*(volatile int*)(0x5000d000+0x17c);
    uVar4|=0x80000000u;
  }
  return uVar4;
}

