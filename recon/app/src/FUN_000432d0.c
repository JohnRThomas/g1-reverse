/* Reconstructed FUN_000432d0 @ 0x432d0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_000432d0(void)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a030UL;
    *p = *p | 2;
    return 0;
}

