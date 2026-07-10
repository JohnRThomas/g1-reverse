#include "g1_net_symbols.h"
/* net-core FUN_01025c38 @ 0x1025c38  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_01025c40 = (volatile uint8_t *)((uintptr_t)&g_net_task_state_struct) /*=0x21001c88*/;
void FUN_01025c38(void) { *(DAT_01025c40 + 0x1e) = 1; }

