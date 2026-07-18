#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00076ba8 @ 0x00076ba8
 * public-name: malloc_lock_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 *   malloc_lock_release                      <= FUN_00076ba8 @ 0x00076ba8
 * address symbols (name @ address):
 *   g_malloc_mutex                           @ 0x20003804
 */
/* Reconstructed FUN_00076ba8 @ 0x76ba8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#define g1_recon_retarget_lock_release_recursive g1_recon_retarget_lock_release_recursive
extern void g1_recon_retarget_lock_release_recursive(uint32_t); /* FUN_00051134@0x00051134 */
void malloc_lock_release(void) {
    g1_recon_retarget_lock_release_recursive(((unsigned long)&g_malloc_mutex) /*=0x20003804*/);
}
