#include <zephyr/kernel.h>
#undef NRF_NVMC_S
#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cb66 @ 0x0007cb66
 * public-name: main_dispatch_thread_tick
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   main_dispatch_thread_tick                <= FUN_0007cb66 @ 0x0007cb66
 */
/* Reconstructed FUN_0007cb66 @ 0x7cb66  (parity: 300/300 trials, PROVEN) */

void main_dispatch_thread_tick(struct k_thread *thread, k_thread_stack_t *stack,
                               size_t stack_size, k_thread_entry_t entry,
                               void *p1, int prio, k_timeout_t delay)
{
  k_thread_create(thread, stack, stack_size, entry, p1, NULL, NULL, prio, 0, delay);
}
