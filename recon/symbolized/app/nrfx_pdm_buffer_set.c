#include "g1_app_symbols.h"
/* named: nrfx_pdm_buffer_set */
/* globals referenced:
//   0x2000b330  g_pdm_cb                     
//   0x50026000  NRF_PDM_BASE                 
*/
/* Reconstructed nrfx_pdm_buffer_set @ 0x66270  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void arch_irq_enable(int);
extern void arch_irq_disable(int);
unsigned int nrfx_pdm_buffer_set(int param_1,int param_2){
  int iVar1=((uintptr_t)&g_pdm_cb) /*=0x2000b330*/; unsigned int uVar4; int iVar3;
  unsigned int uVar5=0x0bad0005;
  if(*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/+0x10)!=0){
    uVar5=0x0bad000b;
    if(*(volatile unsigned char*)(((uintptr_t)&g_pdm_cb) /*=0x2000b330*/+0x11)!=3){
      uVar5=0x0bad0004;
      if(param_1!=0 && ((param_2<<0x10)>=0)){
        arch_irq_disable(0x26);
        if(*(volatile unsigned char*)(iVar1+0x11)==2) uVar4=0;
        else uVar4=~(unsigned int)*(volatile unsigned char*)(iVar1+0x12)&1;
        iVar3=iVar1+uVar4*4;
        uVar5=0x0bad000b;
        if(*(volatile int*)(iVar3+4)==0){
          *(volatile short*)(iVar1+uVar4*2+0xc)=(short)param_2;
          *(volatile int*)(iVar3+4)=param_1;
          *(volatile int*)(NRF_PDM_BASE /*=0x50026000*/+0x158*4)=param_1;
          *(volatile int*)(NRF_PDM_BASE /*=0x50026000*/+0x159*4)=param_2;
          uVar5=0x0bad0000;
          if(*(volatile unsigned char*)(iVar1+0x10)!=2){
            *(volatile unsigned char*)(iVar1+0x10)=2;
            *(volatile int*)(NRF_PDM_BASE /*=0x50026000*/+0x140*4)=1;
            *(volatile int*)NRF_PDM_BASE /*=0x50026000*/=1;
            uVar5=0x0bad0000;
          }
        }
        arch_irq_enable(0x26);
      }
    }
  }
  return uVar5;
}

