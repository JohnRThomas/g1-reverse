/* Reconstructed FUN_0002a4d8 @ 0x2a4d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t FUN_0007cb2c(void);

void FUN_0002a4d8(unsigned int param_1)
{
    uint64_t lVar1 = FUN_0007cb2c();
    *(volatile uint64_t *)0x200040c8UL = lVar1 + (uint64_t)param_1;
}

