/* readable reconstruction; identity: FUN_00076b9c @ 0x00076b9c
 * public-name: __sfp_lock_acquire
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_acquire_recursive <= FUN_000510fc @ 0x000510fc
 *   __sfp_lock_acquire                       <= FUN_00076b9c @ 0x00076b9c
 * address symbols (name @ address):
 *   g_malloc_mutex                           @ 0x20003804
 */
/* Reconstructed FUN_00076b9c @ 0x76b9c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#define g1_recon_retarget_lock_acquire_recursive g1_recon_retarget_lock_acquire_recursive
extern void g1_recon_retarget_lock_acquire_recursive(uint32_t); /* FUN_000510fc@0x000510fc */
void __sfp_lock_acquire(void) {
    g1_recon_retarget_lock_acquire_recursive(0x20003804UL);
}
