#include "g1_app_symbols.h"
/* named: gpiote_read_and_clear_pending_events */
/* Reconstructed gpiote_read_and_clear_pending_events @ 0x65620  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int gpiote_in_event_reg_offset(unsigned int);
unsigned int gpiote_read_and_clear_pending_events(unsigned int param_1){
  unsigned int uVar3=0,uVar4=0,uVar2;
  int iVar1;
  do{
    iVar1=gpiote_in_event_reg_offset(uVar3&0xff);
    uVar2=1u<<((((unsigned int)(iVar1-0x100))>>2)&0xff);
    if((param_1&uVar2)!=0){
      if(*(volatile int*)(iVar1+REG_5000d000 /*=0x5000d000*/)!=0){
        *(volatile int*)(iVar1+REG_5000d000 /*=0x5000d000*/)=0;
        (void)*(volatile int*)(iVar1+REG_5000d000 /*=0x5000d000*/);
        uVar4|=uVar2;
      }
    }
    uVar3++;
  }while(uVar3!=8);
  if(*(volatile int*)(REG_5000d000 /*=0x5000d000*/+0x17c)!=0){
    *(volatile int*)(REG_5000d000 /*=0x5000d000*/+0x17c)=0;
    (void)*(volatile int*)(REG_5000d000 /*=0x5000d000*/+0x17c);
    uVar4|=0x80000000u;
  }
  return uVar4;
}

