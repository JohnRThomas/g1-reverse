/* named: unlock_device_mutex */
/* Reconstructed unlock_device_mutex @ 0x7c8c4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072558(unsigned int);
void unlock_device_mutex(int param_1)
{
  if (param_1 != 0) {
    thunk_FUN_00072558(*(volatile uint32_t*)(param_1 + 0x10));
  }
  return;
}

