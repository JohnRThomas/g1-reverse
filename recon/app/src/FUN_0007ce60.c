/* Reconstructed FUN_0007ce60 @ 0x7ce60  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
extern void FUN_00086c78(int,int,int,unsigned int);
void FUN_0007ce60(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
  int iVar1;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xe9)=0;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xea)=0;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xcc)=0;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xcd)=0;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xce)=0;
  iVar1=FUN_000167a8(); *(volatile unsigned char*)(iVar1+0xcf)=0;
  if(param_1==0){
    iVar1=FUN_000167a8(); *(volatile unsigned char*)(*(volatile int*)(iVar1+0x100c)+7)=0xd;
  } else {
    iVar1=FUN_000167a8(); *(volatile unsigned char*)(*(volatile int*)(iVar1+0x100c)+7)=0;
    iVar1=FUN_000167a8(); **(volatile unsigned char**)(iVar1+0x100c)=0;
  }
  iVar1=FUN_000167a8();
  FUN_00086c78(*(volatile int*)(iVar1+0x100c)+8,0,399,param_4);
}

