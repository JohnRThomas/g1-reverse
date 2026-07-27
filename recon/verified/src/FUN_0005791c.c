/* Reconstructed FUN_0005791c @ 0x5791c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00057874(int,int,int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
void FUN_0005791c(int param_1,int param_2){
  uint16_t *puVar2=(uint16_t*)0x87fec;
  uint16_t *puVar5=(uint16_t*)0x87fc8;
  int local_14=param_2;
  while(1){
    if(puVar2<puVar5){ FUN_0007e2fa(0x99cbd,0xf402a,0xf3f55,0x185,param_1); FUN_0007e2fa(0xf0d20); FUN_0007e2ec(0xf3f55,0x185); }
    if(puVar2<=puVar5) break;
    int iVar3 = (*(int(**)(int,void*))(puVar5+2))(param_1,&local_14);
    if(iVar3>=0){
      uint16_t uVar1=*puVar5;
      *(volatile uint16_t*)(local_14+0x14)=uVar1;
      *(volatile uint16_t*)(local_14+0x24)=uVar1;
      iVar3=FUN_00057874(param_1,local_14,*(int*)(puVar5+4));
      if(iVar3==0) return;
      if(*(void**)(*(int*)(local_14+4))!=0){ (*(void(**)(void))(*(int*)(local_14+4)))(); }
      *(volatile unsigned*)(local_14+0x10) |= 1;
      void *pcVar4=*(void**)(*(int*)(local_14+4)+0x1c);
      if(pcVar4!=0){ (*(void(*)(int,int))pcVar4)(local_14,local_14+0x10); }
    }
    puVar5=puVar5+6;
  }
}

