#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102f580 @ 0x0102f580
 * public-name: FUN_0102f580
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ipc_shm_pool_desc_ptr              @ 0x21004b30
 */
/* net-core FUN_0102f580 @ 0x102f580 — true extent 36 bytes */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

/* The final branch is the shared Zephyr thread-abort implementation at
   0x1037cc8; it is a tail call, not trailing code owned by this wrapper. */
extern void z_impl_k_thread_abort(void *thread);

void FUN_0102f580(void *thread)
{
    volatile uint32_t *const current_thread_slot =
        (volatile uint32_t *)((unsigned long)&g_net_ipc_shm_pool_desc_ptr) /*=0x21004b30*/;
    volatile uint32_t *const scb = (volatile uint32_t *)0xe000ed00U;

    if (*current_thread_slot == (uint32_t)(uintptr_t)thread && __get_IPSR() != 0) {
        scb[1] |= 0x10000000U;       /* PendSV set */
        scb[0x24 / 4] &= ~0x8000U;   /* clear active exception bookkeeping */
    }
    z_impl_k_thread_abort(thread);
}
