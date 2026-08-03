#include "g1_net_symbols.h"
#include "../../headers/g1_nrf_regs.h"
/* readable reconstruction; identity: FUN_0100a760 @ 0x0100a760
 * public-name: FUN_0100a760
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100a760 @ 0x100a760  (parity 300 trials PROVEN) */

void FUN_0100a760(void)
{
    /* NVIC enable/disable writes require completion and instruction-stream
     * ordering.  Keep that contract in portable C through sequential fences. */
    volatile unsigned int *base = (volatile unsigned int *)G1_NVIC_ISER0;
    base[0x80/4] = 0x2000;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    base[0x180/4] = 0x2000;
    base[0x80/4] = 0x4000;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    base[0x180/4] = 0x4000;
}
