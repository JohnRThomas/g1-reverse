#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076bb4 @ 0x00076bb4
 * public-name: env_lock_acquire
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_acquire_or_fatal                    <= FUN_000510fc @ 0x000510fc
 *   env_lock_acquire                         <= FUN_00076bb4 @ 0x00076bb4
 * address symbols (name @ address):
 *   g_env_mutex                              @ 0x20003818
 */
/* Reconstructed FUN_00076bb4 @ 0x76bb4  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void lock_acquire_or_fatal(uint32_t);
void env_lock_acquire(void) {
    lock_acquire_or_fatal(((unsigned long)&g_env_mutex) /*=0x20003818*/);
}
