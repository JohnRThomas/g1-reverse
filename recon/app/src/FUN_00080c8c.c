/* Reconstructed FUN_00080c8c @ 0x80c8c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t FUN_000527dc(void);
extern void FUN_00072880(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

void FUN_00080c8c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    uint64_t uVar1 = FUN_000527dc();
    unsigned int lo = (unsigned int)uVar1;
    unsigned int hi = (unsigned int)(uVar1 >> 32);
    if ((int)lo != 0) {
        FUN_00072880(lo + 0x6c, hi, param_3, param_4);
    }
}

