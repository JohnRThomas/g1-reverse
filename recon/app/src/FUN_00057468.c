/* Reconstructed FUN_00057468 @ 0x57468  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern unsigned int FUN_00057438(unsigned int);

uint32_t FUN_00057468(uint32_t param_1, int *param_2)
{
    volatile uint32_t *p = (volatile uint32_t *)0x20006210UL;
    if (p[0] != 0) {
        return FUN_00057438(param_1);
    }
    p[1] = 0x8b264UL;
    *param_2 = (int)(uintptr_t)p;
    return 0;
}
