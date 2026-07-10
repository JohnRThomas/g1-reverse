/* Reconstructed FUN_00076ad0 @ 0x76ad0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00076bcc(void);
extern void FUN_000510fc(uint32_t);
extern uint32_t FUN_00086a0e(int,int);
extern void FUN_00051134(uint32_t);
uint32_t FUN_00076ad0(int param_1,int param_2){
  uint32_t uVar1;
  if(*(volatile int*)(param_2+0x10)!=0){
    if(param_1!=0 && *(volatile int*)(param_1+0x18)==0) FUN_00076bcc();
    if(param_2==0x9871c) param_2=*(volatile int*)(param_1+4);
    else if(param_2==0x986fc) param_2=*(volatile int*)(param_1+8);
    else if(param_2==0x986dc) param_2=*(volatile int*)(param_1+0xc);
    if(*(volatile int16_t*)(param_2+0xc)!=0){
      if((*(volatile int*)(param_2+100)<<0x1f)>=0 && ((int)*(volatile int16_t*)(param_2+0xc)<<0x16)>=0)
        FUN_000510fc(*(volatile uint32_t*)(param_2+0x58));
      uVar1=FUN_00086a0e(param_1,param_2);
      if((*(volatile int*)(param_2+100)<<0x1f)<0) return uVar1;
      if((int)((uint32_t)*(volatile uint16_t*)(param_2+0xc)<<0x16)<0) return uVar1;
      FUN_00051134(*(volatile uint32_t*)(param_2+0x58));
      return uVar1;
    }
  }
  return 0;
}

