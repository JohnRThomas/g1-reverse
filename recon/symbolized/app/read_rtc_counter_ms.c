#include "g1_app_symbols.h"
/* named: read_rtc_counter_ms */
/* Reconstructed read_rtc_counter_ms @ 0x7d0aa  (parity: 300/300 trials, PROVEN) */

extern void attr_store_get(unsigned int, int*);

void read_rtc_counter_ms(int *param_1)
{
    attr_store_get(0x1c04, param_1);
    *(volatile int*)param_1 = *(volatile int*)param_1 >> 10;
}

