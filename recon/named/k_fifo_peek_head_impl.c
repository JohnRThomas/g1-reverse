/* readable reconstruction; identity: FUN_0008652c @ 0x0008652c
 * public-name: k_fifo_peek_head_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_fifo_peek_head_impl                    <= FUN_0008652c @ 0x0008652c
 */
/* Reconstructed FUN_0008652c @ 0x8652c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern uintptr_t g1_recon_tagged_heap_node_release(unsigned *node, int release);
void k_fifo_peek_head_impl(unsigned int *param_1)
{
    (void)g1_recon_tagged_heap_node_release((unsigned *)(uintptr_t)*param_1, 0);
}
