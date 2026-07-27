/* Reconstructed cleanStocksIndex @ 0x37154  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void debug_print(unsigned long, ...);

void cleanStocksIndex(void)
{
  *(volatile uint8_t*)(0x20004950UL /* unknown global 0x20004950 */+3) = 0;
  *(volatile uint8_t*)0x2001b815UL /* unknown global 0x2001b815 */ = 0;
  if (*(volatile int32_t*)0x2000230cUL /* unknown global 0x2000230c */ <= 2) {
    return;
  }
  if (*(volatile int32_t*)0x20007554UL /* device_info.is_debug (+0xb58) */ != 0) {
    debug_print(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
    return;
  }
  DEBUG_PRINT(0xa8ff3UL, 0xa95b8UL, 0xa95b8UL, 0);
}

