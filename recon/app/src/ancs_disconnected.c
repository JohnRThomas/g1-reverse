/* Reconstructed ancs_disconnected @ 0x18adc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned int,unsigned int,void*,unsigned int);
extern int FUN_000167a8(void);
extern void FUN_00018334(unsigned int,void*);
extern void FUN_00018ab0(void);
extern void FUN_00019c70(unsigned int,unsigned int,void*,unsigned int);
extern void FUN_00072908(int,int,unsigned int,unsigned int);
extern unsigned int FUN_00081526(void);
void ancs_disconnected(unsigned int param_1,unsigned int param_2){
  int iVar3; unsigned int uVar2; unsigned char auStack_30[36];
  *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL+0x365)=0;
  *(volatile int*)0x20007518UL=0;
  uVar2=FUN_00081526();
  FUN_00018334(uVar2,auStack_30);
  if(*(volatile int*)0x2000230cUL>0){
    if(*(volatile int*)0x20007554UL==0){
      DEBUG_PRINT(0x0009a92a,0x0009b1c8,auStack_30,param_2);
    } else {
      FUN_00019c70(0x0009a92a,0x0009b1c8,auStack_30,param_2);
    }
  }
  *(volatile unsigned char*)(*(volatile int*)0x20006ab8UL+0x367)=0;
  while(1){
    iVar3=FUN_000167a8();
    if(*(volatile int*)(iVar3+0x9b4)==0) break;
    iVar3=FUN_000167a8();
    FUN_00072908(iVar3+0x9ac,0,0xffffffff,0xffffffff);
  }
  FUN_00018ab0();
  (void)param_1;
}

