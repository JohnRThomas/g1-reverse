/* Reconstructed FUN_00033c04 @ 0x33c04  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_00033c04(int param_1)
{
  return *(volatile uint8_t*)(param_1 * 0x1b4 + 0x20007dacUL /* device_info_t+0x13B0  (message/display region) */ + 0xd);
}

