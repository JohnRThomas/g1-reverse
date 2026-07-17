/* readable reconstruction; identity: FUN_000748ac @ 0x000748ac
 * public-name: k_current_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_current_get                            <= FUN_000748ac @ 0x000748ac
 * address symbols (name @ address):
 *   g_current_thread_ptr                     @ 0x2000b450
 */
/* Reconstructed FUN_000748ac @ 0x748ac  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint32_t k_current_get(void) {
    return *(volatile uint32_t*)0x2000b450UL;
}
