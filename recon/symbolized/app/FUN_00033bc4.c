#include "g1_app_symbols.h"
/* named: FUN_00033bc4 */
/* Reconstructed FUN_00033bc4 @ 0x33bc4  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00033bc4(void)
{
  unsigned int uVar1;
  uVar1 = (unsigned int)*(volatile unsigned char *)(((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/ + 0x118);
  if (uVar1 != 0) {
    if (*(volatile unsigned char *)(((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/ + 0x116) == 0) {
      uVar1 = 0;
      if (*(volatile unsigned char *)(((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/ + 0x115) < 4) {
        uVar1 = ((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/ + 0x108;
        *(volatile unsigned char *)(((uintptr_t)&g_pending_ack_message) /*=0x20008dac*/ + 0x114) = 10;
        return uVar1;
      }
    } else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

