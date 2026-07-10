/* Reconstructed FUN_000432ec @ 0x432ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int FUN_000432ec(void)
{
    volatile uint32_t *p = (volatile uint32_t *)0x2000a030UL;
    *p = *p & 0xfffffffdU;
    return 0;
}

