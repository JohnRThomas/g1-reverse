/* Reconstructed FUN_00024d2c @ 0x24d2c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int thunk_FUN_00074f68(void);
int FUN_00024d2c(void)
{
  int iVar1;
  iVar1 = thunk_FUN_00074f68();
  return iVar1 - *(volatile int32_t*)0x20007a28UL;
}

