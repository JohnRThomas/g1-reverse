/* Reconstructed FUN_0004a500 @ 0x4a500  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t k_uptime_get_9(void);
extern unsigned int __aeabi_ldivmod(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_0004a500(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    (void)param_1; (void)param_2; (void)param_3;
    uint64_t uVar2 = k_uptime_get_9();
    unsigned int lo = (unsigned int)uVar2;
    unsigned int hi = (unsigned int)(uVar2 >> 32);
    unsigned int uVar1 = __aeabi_ldivmod(lo, hi, 1000, 0, param_4);
    *(volatile uint32_t *)0x2000a0b0UL = uVar1;
}

