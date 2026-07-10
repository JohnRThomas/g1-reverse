#include "g1_app_symbols.h"
/* named: flash_verify_write_at_current_offset */
/* Reconstructed flash_verify_write_at_current_offset @ 0x84e66  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void flash_write_byte_and_verify(int,unsigned int,unsigned int);
void flash_verify_write_at_current_offset(int param_1,unsigned int param_2)
{
  flash_write_byte_and_verify(param_1,param_2,*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8);
  return;
}

