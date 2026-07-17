#include "g1_net_symbols.h"
/* net-core FUN_0102501c @ 0x102501c  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint64_t * const DAT_01025024 = (volatile uint64_t *)((unsigned long)&g_net_radio_timer_sync_state) /*=0x21001bf8*/;
uint64_t FUN_0102501c(void) { return *(uint64_t*)((uint8_t*)DAT_01025024 + 8); }
