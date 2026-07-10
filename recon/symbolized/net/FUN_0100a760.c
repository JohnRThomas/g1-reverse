#include "g1_net_symbols.h"
/* net-core FUN_0100a760 @ 0x100a760  (parity 300 trials PROVEN) */

void FUN_0100a760(void)
{
    volatile unsigned int *base = (volatile unsigned int *)0xe000e100;
    base[0x80/4] = 0x2000;
    __asm__ volatile ("dsb sy" ::: "memory");
    __asm__ volatile ("isb sy" ::: "memory");
    base[0x180/4] = 0x2000;
    base[0x80/4] = 0x4000;
    __asm__ volatile ("dsb sy" ::: "memory");
    __asm__ volatile ("isb sy" ::: "memory");
    base[0x180/4] = 0x4000;
}

