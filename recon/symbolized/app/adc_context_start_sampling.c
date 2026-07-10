#include "g1_app_symbols.h"
/* named: adc_context_start_sampling */
/* Reconstructed adc_context_start_sampling @ 0x5f638  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void adc_context_start_sampling(void *param_1) {
    *(volatile uint32_t*)REG_5000e500 /*=0x5000e500*/ = 1;
    if (*(volatile char*)((char*)param_1 + 0x86) != 0) {
        *(volatile uint32_t*)REG_5000e00c /*=0x5000e00c*/ = 1;
        return;
    }
    *(volatile uint32_t*)REG_5000e000 /*=0x5000e000*/ = 1;
    *(volatile uint32_t*)REG_5000e004 /*=0x5000e004*/ = 1;
}

