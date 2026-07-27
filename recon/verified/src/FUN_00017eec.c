/* Reconstructed FUN_00017eec @ 0x17eec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_000720d0(void);
extern int FUN_000720d0_i(uint32_t,void*,int,int);
extern void FUN_00072240(uint32_t,void*,int,int);
extern void FUN_00086c04(void*,uint32_t,int);
extern void FUN_00086c78(void*,int,int);
int FUN_00017eec(uint32_t param_1, uint8_t param_2){
  uint8_t local_114[0x101];
  FUN_00086c78(local_114,0,0x101);
  if(*(volatile int*)(0x200038f8UL+0x24)==0x30){
    FUN_00072240(0x200038f8,local_114,0,0);
    if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(0x9a18e);
    else FUN_00019c70(0x9a18e);
  }
  local_114[0]=param_2;
  FUN_00086c04(local_114+1,param_1,0x100);
  int iVar1=FUN_000720d0_i(0x200038f8,local_114,0,0);
  if(iVar1!=0){
    if(*(volatile int*)0x20007554UL==0) DEBUG_PRINT(0x9a1ae);
    else FUN_00019c70(0x9a1ae);
  }
  return iVar1;
}
