/* readable reconstruction; identity: FUN_00048ff4 @ 0x00048ff4
 * public-name: stop_some_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   stop_some_timer                          <= FUN_00048ff4 @ 0x00048ff4
 *   z_impl_k_timer_stop                      <= FUN_0008673e @ 0x0008673e
 * address symbols (name @ address):
 *   g_some_k_timer                           @ 0x20004ce0
 */
/* Reconstructed FUN_00048ff4 @ 0x48ff4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_impl_k_timer_stop(uint32_t);
void stop_some_timer(void) {
    z_impl_k_timer_stop(0x20004ce0UL);
}
