/* Reconstructed FUN_00080b42 @ 0x80b42  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int FUN_000526e4(void);
extern void FUN_00083740(int,int,uint);
uint FUN_00080b42(int param_1,int param_2,uint param_3){
  int iVar1;
  if(*(volatile int*)(param_1+0x40)==0){
    if(param_3<8) return 0xffffffc3;
    uint16_t h=*(volatile uint16_t*)(param_2+2);
    uint uVar2=(((h&0xff)<<8)|(h>>8))+8;
    uint uVar3=uVar2&0xffff;
    if(param_3>0x9ab || uVar3>0x9ab) return 0xffffffc1;
    if(uVar3<param_3) return 0xffffff75;
    iVar1=FUN_000526e4();
    *(volatile int*)(param_1+0x40)=iVar1;
    if(iVar1==0) return 0xfffffff4;
    *(volatile int16_t*)(param_1+0x44)=(int16_t)uVar2;
  } else if(*(volatile uint16_t*)(param_1+0x44)<param_3){
    return 0xffffff75;
  }
  FUN_00083740(*(volatile int*)(param_1+0x40)+0xc,param_2,param_3);
  param_3=*(volatile uint16_t*)(param_1+0x44)-param_3;
  *(volatile int16_t*)(param_1+0x44)=(int16_t)param_3;
  return param_3&0xffff;
}

