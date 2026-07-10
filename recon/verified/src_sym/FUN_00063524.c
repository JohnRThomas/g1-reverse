/* Reconstructed FUN_00063524 @ 0x63524  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00063524(unsigned int param_1, int param_2)
{
  if (param_2 != 0) {
    volatile uint32_t *p0 = (volatile uint32_t*)0x2000b2d8UL;
    *p0 = *p0 | (1u << (param_1 & 0xff));
    *(volatile uint32_t*)(0x50015000UL + 0x304) = 0x10000u << (param_1 & 0xff);
    uint32_t v = *(volatile uint32_t*)0x2000b2d0UL;
    int iVar2 = (int)((v >> (param_1 & 0xff)) << 0x1f);
    if (iVar2 < 0) {
      *(volatile uint32_t*)(0xe000e100UL + 0x100) = 0x200000;
    }
  }
}

