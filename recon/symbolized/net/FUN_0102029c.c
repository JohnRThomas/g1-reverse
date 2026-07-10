#include "g1_net_symbols.h"
/* net-core FUN_0102029c @ 0x102029c  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_010202a4 = (volatile uint8_t *)((uintptr_t)&g_nrf802154_core_state) /*=0x210015f0*/;
uint8_t FUN_0102029c(void) {
    return *(DAT_010202a4 + 0x28);
}

