/* Reconstructed cleanNewsIndex @ 0x37234  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(uint32_t,uint32_t,uint32_t,uint32_t);
extern void debug_print(uint32_t,uint32_t);

void cleanNewsIndex(void)
{
  *(volatile uint8_t*)(0x20004950UL /* unknown global 0x20004950 */+5) = 0;
  *(volatile uint8_t*)0x2001b814UL /* unknown global 0x2001b814 */ = 0;
  if (*(volatile int32_t*)0x2000230cUL /* unknown global 0x2000230c */ <= 2) {
    return;
  }
  if (*(volatile int32_t*)0x20007554UL /* device_info.is_debug (+0xb58) */ != 0) {
    debug_print(0xa8ff3UL, 0xa958fUL);
    return;
  }
  DEBUG_PRINT(0xa8ff3UL, 0xa958fUL, 0xa958fUL, 0);
}

