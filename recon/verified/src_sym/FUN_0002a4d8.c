/* Reconstructed FUN_0002a4d8 @ 0x2a4d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern unsigned long long k_uptime_get_1(void);

void FUN_0002a4d8(unsigned int param_1)
{
    uint64_t lVar1 = k_uptime_get_1();
    *(volatile uint64_t *)0x200040c8UL = lVar1 + (uint64_t)param_1;
}

