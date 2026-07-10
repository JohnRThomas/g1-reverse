#include "g1_app_symbols.h"
/* named: flowctl_release_credit_and_kick */
/* Reconstructed flowctl_release_credit_and_kick @ 0x84b32  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00084a54(int,int,int);
void flowctl_release_credit_and_kick(int param_1, uint32_t param_2){
  int iVar5 = *(volatile int*)(param_1+0x10);
  int iVar4 = *(volatile int*)(iVar5+0xc);
  *(volatile uint32_t*)(iVar4+0xc0) = *(volatile uint32_t*)(iVar4+0xc0) & ~param_2;
  int r5 = *(volatile int*)(iVar5+0xc);
  if(*(volatile int*)(r5+0xc0) == 0){
    if(param_2 == 2){
      int r = FUN_00084a54(*(volatile int*)(param_1+4), r5+0xc4, 5);
      *(volatile uint8_t*)(r5+0xc9) = (uint8_t)r;
    }
    int base = *(volatile int*)(*(volatile int*)(param_1+4));
    *(volatile uint32_t*)(base+0x500) = 0;
  }
}

