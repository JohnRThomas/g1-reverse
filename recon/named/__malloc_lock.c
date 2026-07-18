/* readable reconstruction; identity: FUN_000785bc @ 0x000785bc
 * public-name: __malloc_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_acquire_recursive <= FUN_000510fc @ 0x000510fc
 *   __malloc_lock                            <= FUN_000785bc @ 0x000785bc
 * address symbols (name @ address):
 *   g_malloc_lock                            @ 0x200037f0
 */
/* Reconstructed FUN_000785bc @ 0x785bc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#define g1_recon_retarget_lock_acquire_recursive g1_recon_retarget_lock_acquire_recursive
extern void g1_recon_retarget_lock_acquire_recursive(uint32_t); /* FUN_000510fc@0x000510fc */
void __malloc_lock(void) {
    g1_recon_retarget_lock_acquire_recursive(0x200037f0UL);
}
