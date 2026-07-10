#include "g1_net_symbols.h"
/* net-core FUN_010343a0 @ 0x10343a0  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_010343a8 = (volatile uint8_t *)REG_4100f000 /*=0x4100f000*/;
void FUN_010343a0(uint32_t param_1) {
    *(volatile uint32_t*)(DAT_010343a8 + 0x504) = param_1;
}

