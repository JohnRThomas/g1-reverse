/* Reconstructed FUN_00050b8c @ 0x50b8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_000748b8(int);

void FUN_00050b8c(int param_1)
{
    volatile int *g = (volatile int*)0x2000b448;
    volatile uint32_t *scb = (volatile uint32_t*)0xe000ed00;
    /* Pend PendSV only when this abort runs from exception context. */
    if (g[2] == param_1 && __get_IPSR() != 0) {
        scb[1] = scb[1] | 0x10000000;
        scb[9] = scb[9] & 0xffff7fff;
    }
    FUN_000748b8(param_1);
}
