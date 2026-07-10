#include "g1_app_symbols.h"
/* named: set_change_aware_no_store */
/* Reconstructed set_change_aware_no_store @ 0x82b98  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_or_0(int,unsigned int);
extern unsigned int atomic_and_4(int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int set_change_aware_no_store(int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uVar1;
  unsigned long long uVar2;
  if (param_2 == 0) {
    uVar1 = atomic_and_4(param_1 + 0xc,0xfffffffeU,param_3,param_4,param_4);
    uVar1 = uVar1 & 1;
  } else {
    uVar2 = atomic_or_0(param_1 + 0xc,1);
    uVar1 = ~(unsigned int)uVar2 & (unsigned int)(uVar2 >> 0x20);
  }
  return uVar1;
}

