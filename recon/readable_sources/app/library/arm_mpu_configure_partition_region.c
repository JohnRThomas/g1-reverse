#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_thread__param_0168                   [param_0168; library]
 * Raw function identity: 0x00050b8c.  See ../include/g1_recovered_layouts.h. */
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
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void z_thread_abort(int);

void arm_mpu_configure_partition_region(int param_1)
{
    volatile int *g = (volatile int*)((unsigned long)&_kernel) /*=0x2000b448*/;
    volatile uint32_t *scb = (volatile uint32_t*)0xe000ed00;
    /* Pend PendSV only when this abort runs from exception context. */
    if (g[2] == param_1 && __get_IPSR() != 0) {
        scb[1] = scb[1] | 0x10000000;
        scb[9] = scb[9] & 0xffff7fff;
    }
    z_thread_abort(param_1);
}
