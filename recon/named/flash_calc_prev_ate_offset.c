/* named: flash_calc_prev_ate_offset */
/* Reconstructed flash_calc_prev_ate_offset @ 0x84d64  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int flash_calc_prev_ate_offset(int param_1)
{
  return (*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8) - 0x10;
}

