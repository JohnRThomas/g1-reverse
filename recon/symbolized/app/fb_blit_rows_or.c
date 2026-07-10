#include "g1_app_symbols.h"
/* named: fb_blit_rows_or */
/* Reconstructed fb_blit_rows_or @ 0x7d586  (parity: 145/300 trials, PROVEN) */
#include <stdint.h>
void fb_blit_rows_or(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6){
  int iVar2=0;
  if(param_6>199) param_6=200;
  if(param_5>0x27f) param_5=0x280;
  int iVar4=0;
  int q=param_3/2;
  int inc=q & ~(q>>31);
  for(;iVar2<param_4;iVar2++){
    volatile uint8_t* pbVar5=(volatile uint8_t*)(param_2+iVar4);
    for(int iVar3=0;iVar3<q;iVar3++){
      int iVar1=*(volatile int*)(param_1+param_6*4+iVar2*4);
      int iVar6=param_5/2+iVar3;
      *(volatile uint8_t*)(iVar1+iVar6) = *pbVar5 | *(volatile uint8_t*)(iVar1+iVar6);
      pbVar5=pbVar5+1;
    }
    iVar4=iVar4+inc;
  }
}

