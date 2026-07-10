/* Reconstructed FUN_00024684 @ 0x24684  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint;
extern int DEBUG_PRINT(int,...); extern int FUN_00019c70(int,...); extern int FUN_00072240(int,...);

int FUN_00024684(uint param_1,uint param_2,undefined4 param_3)
{
  uint local_30 = param_1, local_2c = param_2; undefined4 uStack_28 = param_3;
  int iVar4 = FUN_00072240(0x20003960,(int)&local_30,0,0);
  if (iVar4 != 0) {
    if (*(volatile int*)0x2000230c < 1) return -1;
    if (*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x9ef15,0x9f032);
    else FUN_00019c70(0);
    if (*(volatile int*)0x2000230c < 1) return -1;
    iVar4 = *(volatile int*)0x20007554;
    if (iVar4 != 0) { FUN_00019c70(0); return -1; }
    DEBUG_PRINT(0x9ef3f,0x9f050);
    return -1;
  }
  (void)local_2c; (void)uStack_28;
  return 0;
}

