#include "g1_app_symbols.h"
/* named: FUN_0002a4c0 */
/* Reconstructed FUN_0002a4c0 @ 0x2a4c0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void thunk_FUN_00072880(void *arg);

void FUN_0002a4c0(void)
{
  if (*(volatile uint8_t*)((uintptr_t)&g_misc_dispatch_pending_flag) /*=0x20018d88*/ != 0) {
    thunk_FUN_00072880((void*)((uintptr_t)&g_misc_dispatch_ctx) /*=0x20007b00*/);
    return;
  }
  return;
}

