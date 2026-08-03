#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00050b8c @ 0x00050b8c
 * public-name: arm_mpu_configure_partition_region
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arm_mpu_configure_partition_region       <= FUN_00050b8c @ 0x00050b8c
 *   z_thread_abort                           <= FUN_000748b8 @ 0x000748b8
 * address symbols (name @ address):
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00050b8c @ 0x50b8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../../headers/g1_nrf_regs.h"
extern void z_thread_abort(int);

void arm_mpu_configure_partition_region(int param_1)
{
    volatile int *g = (volatile int*)((unsigned long)&_kernel) /*=0x2000b448*/;
    volatile uint32_t *scb = (volatile uint32_t*)G1_SCB_CPUID;
    /* Pend PendSV only when this abort runs from exception context. */
    if (g[2] == param_1 && __get_IPSR() != 0) {
        scb[1] = scb[1] | 0x10000000;
        scb[9] = scb[9] & 0xffff7fff;
    }
    z_thread_abort(param_1);
}
