/* Reconstructed FUN_0005f638 @ 0x5f638  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void adc_context_start_sampling(void *param_1) {
    *(volatile uint32_t*)0x5000e500UL = 1;
    if (*(volatile char*)((char*)param_1 + 0x86) != 0) {
        *(volatile uint32_t*)0x5000e00cUL = 1;
        return;
    }
    *(volatile uint32_t*)0x5000e000UL = 1;
    *(volatile uint32_t*)0x5000e004UL = 1;
}

