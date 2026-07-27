/* readable reconstruction; identity: FUN_000574ec @ 0x000574ec
 * public-name: l2cap_chan_tx_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_chan_tx_init                       <= FUN_000574ec @ 0x000574ec
 *   k_work_init_delayable                    <= FUN_000732d4 @ 0x000732d4
 *   z_impl_k_queue_init                      <= FUN_000864e8 @ 0x000864e8
 * address symbols (name @ address):
 *   ADDR_att_send_with_retry_THUMB           @ 0x000818dd
 */
/* Reconstructed FUN_000574ec @ 0x574ec  (parity: 300/300 trials, PROVEN) */

#define z_impl_k_queue_init z_impl_k_queue_init
extern void z_impl_k_queue_init(struct k_queue *);
extern void k_work_init_delayable(struct k_work_delayable *, void (*)(struct k_work *));

void l2cap_chan_tx_init(int param_1)
{
    *(volatile unsigned int*)(param_1+0x24) = 0;
    *(volatile unsigned int*)(param_1+0x28) = 0;
    *(volatile unsigned int*)(param_1+0x2c) = 0;
    unsigned int uVar1 = __atomic_exchange_n(
        (unsigned int *)(param_1 + 0x2c), 0, __ATOMIC_ACQ_REL);
    z_impl_k_queue_init((void *)(param_1+0x30));
    k_work_init_delayable(param_1+0x50, 0x000818ddUL);
}
