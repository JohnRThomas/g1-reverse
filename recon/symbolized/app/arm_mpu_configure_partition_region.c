#include "g1_app_symbols.h"
/* named: arm_mpu_configure_partition_region */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed arm_mpu_configure_partition_region @ 0x50b8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_000748b8(int);

void arm_mpu_configure_partition_region(int param_1)
{
    volatile int *g = (volatile int*)((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/;
    volatile uint32_t *scb = (volatile uint32_t*)0xe000ed00;
    if (g[2] == param_1) {
        scb[1] = scb[1] | 0x10000000;
        scb[9] = scb[9] & 0xffff7fff;
    }
    FUN_000748b8(param_1);
}

