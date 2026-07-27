/* Reconstructed cleanStocksIndex @ 0x37154  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

void cleanStocksIndex(void)
{
  *(volatile uint8_t*)(0x20004950UL+3) = 0;
  *(volatile uint8_t*)0x2001b815UL = 0;
  if (*(volatile int32_t*)0x2000230cUL <= 2) {
    return;
  }
  if (*(volatile int32_t*)0x20007554UL != 0) {
    FUN_00019c70(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
    return;
  }
  DEBUG_PRINT(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
}
