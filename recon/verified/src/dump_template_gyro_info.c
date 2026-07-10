/* Reconstructed dump_template_gyro_info @ 0x36164  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern unsigned long long FUN_0000d848(unsigned);
extern void FUN_00019c70(void);
void dump_template_gyro_info(int param_1){
  int iVar1; unsigned long long uVar2,uVar3,uVar4;
  iVar1=FUN_000167a8();
  if(2 < *(volatile int*)0x2000230cUL){
    uVar2=FUN_0000d848(*(uint32_t*)(iVar1+0xef));
    uVar3=FUN_0000d848(*(uint32_t*)(iVar1+0xf3));
    uVar4=FUN_0000d848(*(uint32_t*)(iVar1+0xf7));
    if(*(volatile int*)0x20007554UL==0){
      DEBUG_PRINT(0xa8cf4,0xa8d3a,(unsigned)*(uint8_t*)(param_1+1),0,(int)uVar2,(int)(uVar2>>0x20),(int)uVar3,(int)(uVar3>>0x20),(int)uVar4,(int)(uVar4>>0x20));
    } else { FUN_00019c70(); }
  }
  return;
}

