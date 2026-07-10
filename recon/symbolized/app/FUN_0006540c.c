#include "g1_app_symbols.h"
/* named: FUN_0006540c */
/* Reconstructed FUN_0006540c @ 0x6540c  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_alloc(unsigned int, unsigned int);
void FUN_0006540c(unsigned int param_1)
{
    nrfx_flag32_alloc(((uintptr_t)&g_flag32_channel_alloc_mask) /*=0x20002bbc*/, param_1);
}

