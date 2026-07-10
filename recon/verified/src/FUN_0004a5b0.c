/* Reconstructed FUN_0004a5b0 @ 0x4a5b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...); extern int FUN_00019c70(int,...);
extern int FUN_0004a1b8(int,...); extern int FUN_0007d216(int,...);

undefined4 FUN_0004a5b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)
{
  undefined4 uVar2; uint local_24, local_20, local_1c;
  local_24 = param_2; local_20 = param_3; local_1c = param_4;
  uVar2 = FUN_0007d216(0);
  local_24 = 0; local_20 = 0; local_1c = 0;
  FUN_0004a1b8(uVar2,(int)&local_24);
  if ((local_24 & 0xffff) < 0x7e9) {
    if ((((local_24 >> 16) & 0xffff) | (local_20 & 0xffff)) < 2) {
      if (1 < *(volatile int*)0x2000230c) {
        if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0xf0310,0xf04c1,local_20 & 0xffff,0,param_1);
        else FUN_00019c70(0);
      }
      return 0xffffffff;
    }
  }
  (void)local_1c;
  return 0;
}

