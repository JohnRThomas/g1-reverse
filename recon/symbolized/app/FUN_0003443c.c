#include "g1_app_symbols.h"
/* named: FUN_0003443c */
/* Reconstructed FUN_0003443c @ 0x3443c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void msg_content_decrement_timer(void);
void FUN_0003443c(int param_1)
{
  *(volatile uint8_t*)((uintptr_t)&g_message_pending_state) /*=0x2001a229*/ = (uint8_t)param_1;
  if (param_1 == 0) {
    msg_content_decrement_timer();
    return;
  }
  return;
}

