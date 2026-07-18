#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000574ec @ 0x000574ec
 * public-name: l2cap_chan_tx_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_tx_init                       <= FUN_000574ec @ 0x000574ec
 *   g1_recon_z_impl_k_queue_init             <= FUN_000864e8 @ 0x000864e8
 * address symbols (name @ address):
 *   ADDR_att_send_with_retry_THUMB           @ 0x000818dd
 */
/* Reconstructed FUN_000574ec @ 0x574ec  (parity: 300/300 trials, PROVEN) */

#define g1_recon_z_impl_k_queue_init g1_recon_z_impl_k_queue_init
extern void g1_recon_z_impl_k_queue_init(void *queue);
extern void FUN_000732d4(unsigned int a, unsigned int b);

void l2cap_chan_tx_init(int param_1)
{
    *(volatile unsigned int*)(param_1+0x24) = 0;
    *(volatile unsigned int*)(param_1+0x28) = 0;
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    unsigned int uVar1 = __atomic_exchange_n(
        (unsigned int *)(param_1 + 0x2c), 0, __ATOMIC_ACQ_REL);
    g1_recon_z_impl_k_queue_init((void *)(param_1+0x30));
    FUN_000732d4(param_1+0x50, ADDR_att_send_with_retry_THUMB /*=0x818dd*/);
}
