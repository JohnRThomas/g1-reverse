/* readable reconstruction; identity: FUN_00076b9c @ 0x00076b9c
 * public-name: malloc_lock_acquire
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   malloc_lock_acquire                      <= FUN_00076b9c @ 0x00076b9c
 * address symbols (name @ address):
 *   g_malloc_mutex                           @ 0x20003804
 */
/* Reconstructed FUN_00076b9c @ 0x76b9c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_acquire_or_fatal(uint32_t);
void malloc_lock_acquire(void) {
    lock_acquire_or_fatal(0x20003804UL);
}
