/* Reconstructed FUN_00033bf0 @ 0x33bf0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void FUN_00033bf0(int param_1, uint8_t param_2)
{
  *(volatile uint8_t*)(param_1 * 0x1b4 + 0x20007dacUL /* device_info_t+0x13B0  (message/display region) */ + 0xd) = param_2;
  return;
}

