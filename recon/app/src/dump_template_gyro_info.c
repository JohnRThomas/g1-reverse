/* Reconstructed dump_template_gyro_info @ 0x36164  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern unsigned long long FUN_0000d848(unsigned);
extern void FUN_00019c70(int, ...);
void dump_template_gyro_info(int param_1){
  int iVar1; uint32_t raw_x,raw_y,raw_z; unsigned long long uVar2,uVar3,uVar4;
  iVar1=FUN_000167a8();
  if(2 < *(volatile int*)0x2000230cUL){
    /* These packed fields are intentionally at odd addresses.  Builtin memcpy
       lowers to the original unaligned loads on Cortex-M33 without creating
       misaligned uint32_t lvalues (which would be ISO-C undefined behavior). */
    __builtin_memcpy(&raw_x,(const void*)(uintptr_t)(iVar1+0xef),sizeof raw_x);
    __builtin_memcpy(&raw_y,(const void*)(uintptr_t)(iVar1+0xf3),sizeof raw_y);
    __builtin_memcpy(&raw_z,(const void*)(uintptr_t)(iVar1+0xf7),sizeof raw_z);
    uVar2=FUN_0000d848(raw_x);
    uVar3=FUN_0000d848(raw_y);
    uVar4=FUN_0000d848(raw_z);
    if(*(volatile int*)0x20007554UL==0){
      DEBUG_PRINT(0xa8cf4,0xa8d3a,(unsigned)*(uint8_t*)(param_1+1),uVar2,uVar3,uVar4);
    } else {
      FUN_00019c70(0xa8cf4,0xa8d3a,(unsigned)*(uint8_t*)(param_1+1),uVar2,uVar3,uVar4);
    }
  }
  return;
}
