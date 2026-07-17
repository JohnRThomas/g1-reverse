#include "g1_net_symbols.h"
/* net-core FUN_0102072c @ 0x102072c  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_01020734 = (volatile uint8_t *)REG_41008000 /*=0x41008000*/;
void FUN_0102072c(uint32_t param_1) {
    *(volatile uint32_t *)(DAT_01020734 + 0x53c) = param_1;
}
