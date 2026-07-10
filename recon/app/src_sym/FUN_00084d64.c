/* Reconstructed FUN_00084d64 @ 0x84d64  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int FUN_00084d64(int param_1)
{
  return (*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8) - 0x10;
}

