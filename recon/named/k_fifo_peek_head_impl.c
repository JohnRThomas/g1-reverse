/* readable reconstruction; identity: FUN_0008652c @ 0x0008652c
 * public-name: k_fifo_peek_head_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_queue_node_peek                        <= FUN_000864d0 @ 0x000864d0
 *   k_fifo_peek_head_impl                    <= FUN_0008652c @ 0x0008652c
 */
/* Reconstructed FUN_0008652c @ 0x8652c  (parity: 300/300 trials, PROVEN) */

extern void z_queue_node_peek(unsigned int, unsigned int);
void k_fifo_peek_head_impl(unsigned int *param_1)
{
    z_queue_node_peek(*param_1, 0);
}
