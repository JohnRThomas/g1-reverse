/* Reconstructed FUN_00084e66 @ 0x84e66  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00084db2(int,unsigned int,unsigned int);
void FUN_00084e66(int param_1,unsigned int param_2)
{
  FUN_00084db2(param_1,param_2,*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8);
  return;
}

