#include "g1_net_symbols.h"
/* net-core FUN_01020048 @ 0x1020048  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_01020050 = (volatile uint8_t *)REG_4100e000 /*=0x4100e000*/;
void FUN_01020048(void) {
    *(volatile uint32_t *)(DAT_01020050 + 8) = 1;
}

