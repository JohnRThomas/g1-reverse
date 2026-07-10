/* Reconstructed FUN_0004904c @ 0x4904c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_00074554(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_0004904c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a09cUL;
    FUN_00074554(*p, 0xfffffff0U, param_3, (unsigned int)(uintptr_t)p, param_4);
    *(volatile uint8_t *)0x2001d446UL = 1;
}

