/* Reconstructed FUN_00066270 @ 0x66270  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
extern void FUN_000500ac(int);
extern void FUN_000500c8(int);
unsigned int FUN_00066270(int param_1,int param_2){
  int iVar1=0x2000b330; unsigned int uVar4; int iVar3;
  unsigned int uVar5=0x0bad0005;
  if(*(volatile unsigned char*)(0x2000b330+0x10)!=0){
    uVar5=0x0bad000b;
    if(*(volatile unsigned char*)(0x2000b330+0x11)!=3){
      uVar5=0x0bad0004;
      if(param_1!=0 && ((param_2<<0x10)>=0)){
        FUN_000500c8(0x26);
        if(*(volatile unsigned char*)(iVar1+0x11)==2) uVar4=0;
        else uVar4=~(unsigned int)*(volatile unsigned char*)(iVar1+0x12)&1;
        iVar3=iVar1+uVar4*4;
        uVar5=0x0bad000b;
        if(*(volatile int*)(iVar3+4)==0){
          *(volatile short*)(iVar1+uVar4*2+0xc)=(short)param_2;
          *(volatile int*)(iVar3+4)=param_1;
          *(volatile int*)(G1_NRF_PDM0_S_BASE+0x158*4)=param_1;
          *(volatile int*)(G1_NRF_PDM0_S_BASE+0x159*4)=param_2;
          uVar5=0x0bad0000;
          if(*(volatile unsigned char*)(iVar1+0x10)!=2){
            *(volatile unsigned char*)(iVar1+0x10)=2;
            *(volatile int*)(G1_NRF_PDM0_S_BASE+0x140*4)=1;
            *(volatile int*)0x50026000UL=1;
            uVar5=0x0bad0000;
          }
        }
        FUN_000500ac(0x26);
      }
    }
  }
  return uVar5;
}

