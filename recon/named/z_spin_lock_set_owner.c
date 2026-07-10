/* named: z_spin_lock_set_owner */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed z_spin_lock_set_owner @ 0x72078  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void z_spin_lock_set_owner(unsigned int *param_1)
{
  *param_1 = *(volatile uint32_t*)(0x2000b448UL + 8) | (unsigned int)*(volatile uint8_t*)(0x2000b448UL + 0x10);
  return;
}

