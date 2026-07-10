#include "g1_app_symbols.h"
/* named: k_timer_init */
/* Reconstructed k_timer_init @ 0x86726  (parity: 300/300 trials, PROVEN) */

void k_timer_init(unsigned int *param_1, unsigned int param_2, unsigned int param_3) {
    volatile unsigned int *p = (volatile unsigned int*)param_1;
    p[8] = param_2;
    p[9] = param_3;
    p[6] = (unsigned int)(param_1 + 6);
    p[7] = (unsigned int)(param_1 + 6);
    p[0] = 0;
    p[1] = 0;
    p[0xc] = 0;
    p[0xd] = 0;
}

