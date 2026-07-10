#include "g1_app_symbols.h"
/* named: FUN_0006058c */
/* Reconstructed FUN_0006058c @ 0x6058c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005010c(int,int,int,unsigned,unsigned);
extern int nrfx_clock_init(unsigned);
extern void nrfx_clock_irq_enable(void);
extern int onoff_manager_init(int,unsigned);
int FUN_0006058c(int param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  unsigned uVar1; int iVar2,iVar3,iVar4;
  FUN_0005010c(5,1,0,param_4,param_4);
  iVar2=nrfx_clock_init(((uintptr_t)&tbl_605f0) /*=0x60635*/);
  if(iVar2==0x0bad0000){
    *(volatile unsigned*)REG_5000555c /*=0x5000555c*/=0x9ba5;
    nrfx_clock_irq_enable();
    uVar1=((uintptr_t)&tbl_8b5d8) /*=0x8b5fc*/; iVar2=0;
    do{
      iVar4=*(int*)(param_1+0x10);
      iVar3=onoff_manager_init(iVar4+iVar2*0x20,uVar1);
      if(iVar3<0) return iVar3;
      iVar3=iVar2*0xc; iVar2=iVar2+1;
      *(unsigned*)(iVar3+iVar4+0x88)=1;
    } while(iVar2!=4);
    iVar2=0;
  } else { iVar2=-5; }
  return iVar2;
}

