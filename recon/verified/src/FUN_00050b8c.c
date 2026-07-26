/* Reconstructed FUN_00050b8c @ 0x50b8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_nrf_regs.h"
extern void FUN_000748b8(int);

void FUN_00050b8c(int param_1)
{
    volatile int *g = (volatile int*)0x2000b448;
    volatile uint32_t *scb = (volatile uint32_t*)G1_SCB_CPUID;
    /* Pend PendSV only when this abort runs from exception context. */
    if (g[2] == param_1 && __get_IPSR() != 0) {
        scb[1] = scb[1] | 0x10000000;
        scb[9] = scb[9] & 0xffff7fff;
    }
    FUN_000748b8(param_1);
}
