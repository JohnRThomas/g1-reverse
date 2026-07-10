#include "g1_app_symbols.h"
/* named: vprintf */
/* Reconstructed vprintf @ 0x4b1cc  (parity: 300/300 trials, PROVEN) */

extern void printf_like(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void vprintf(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    printf_like(((uintptr_t)&tbl_4b178) /*=0x4b1b5*/, 0, param_1, param_2, 0, param_2, param_3);
}

