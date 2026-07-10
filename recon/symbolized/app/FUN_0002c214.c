#include "g1_app_symbols.h"
/* named: FUN_0002c214 */
/* Reconstructed FUN_0002c214 @ 0x2c214  (parity: 300/300 trials, PROVEN) */

void FUN_0002c214(void)
{
  if (*(volatile unsigned char *)((uintptr_t)&g_pending_message_flag) /*=0x20018d9e*/ != 0) {
    *(volatile unsigned char *)((uintptr_t)&g_pending_message_flag) /*=0x20018d9e*/ = 0;
  }
}

