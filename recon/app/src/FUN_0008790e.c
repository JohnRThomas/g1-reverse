/* Reconstructed FUN_0008790e @ 0x8790e  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00076e20(uint32_t,int);
extern void FUN_00086c04(int,int,int);
extern int FUN_000876ec(uint32_t,int,int);
uint32_t FUN_0008790e(uint32_t param_1,volatile int* param_2){
  int iVar1,iVar2;
  if((int*)param_2[0xd]==(int*)(param_2+0x11)){
    iVar1=FUN_00076e20(param_1,0x400);
    if(iVar1!=0){
      param_2[0xd]=iVar1;
      param_2[0xe]=0x400;
      *(volatile uint8_t*)(iVar1+0x3ff)=*(volatile uint8_t*)((int)param_2+0x46);
      *(volatile uint8_t*)(iVar1+0x3fe)=*(volatile uint8_t*)((int)param_2+0x45);
      *(volatile uint8_t*)(iVar1+0x3fd)=*(volatile uint8_t*)((int)param_2+0x44);
      *param_2=iVar1+0x3fd;
      return 0;
    }
  } else {
    iVar2=param_2[0xe];
    iVar1=FUN_000876ec(param_1,param_2[0xd],iVar2<<1);
    if(iVar1!=0){
      FUN_00086c04(iVar1+iVar2,iVar1,iVar2);
      *param_2=iVar1+iVar2;
      param_2[0xd]=iVar1;
      param_2[0xe]=iVar2<<1;
      return 0;
    }
  }
  return 0xffffffff;
}

