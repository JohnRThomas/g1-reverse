/* Reconstructed FUN_00054250 @ 0x54250  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_00054250(unsigned int param_1)
{
  uint8_t uVar1;
  if (param_1 < 0x2a) {
    uVar1 = *(volatile uint8_t*)(0x000f33e9UL + param_1);
  } else {
    uVar1 = 9;
  }
  return uVar1;
}

