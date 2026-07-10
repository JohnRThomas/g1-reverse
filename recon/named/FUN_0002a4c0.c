/* named: FUN_0002a4c0 */
/* Reconstructed FUN_0002a4c0 @ 0x2a4c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072880(void *arg);

void FUN_0002a4c0(void)
{
  if (*(volatile uint8_t*)0x20018d88UL != 0) {
    thunk_FUN_00072880((void*)0x20007b00UL);
    return;
  }
  return;
}

