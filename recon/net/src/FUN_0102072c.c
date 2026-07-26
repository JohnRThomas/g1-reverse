/* net-core FUN_0102072c @ 0x102072c  (parity 300 trials PROVEN) */

#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
static volatile uint8_t * const DAT_01020734 = (volatile uint8_t *)G1_NRF_RADIO_NS_BASE;
void FUN_0102072c(uint32_t param_1) {
    *(volatile uint32_t *)(DAT_01020734 + 0x53c) = param_1;
}

