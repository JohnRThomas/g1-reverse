/* Reconstructed FUN_0002a0c0 @ 0x2a0c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072880(unsigned int);
void FUN_0002a0c0(void)
{
  if (*(volatile uint8_t*)0x20018d8aUL != 0) {
    thunk_FUN_00072880(0x20007b1cUL /* device_info.gap_10E0+64 */);
    return;
  }
  return;
}

