/* readable reconstruction; identity: FUN_0002f940 @ 0x0002f940
 * public-name: atomic_get_3
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_atomic_scratch_20007bb0                @ 0x20007bb0
 */
/* Reconstructed atomic_get_3 @ 0x0002f940 from Zephyr atomic_builtin.h.
 * Raw backmap: FUN_0002f940@0x0002f940. */

#include <stdint.h>
int32_t atomic_get_3(void){return __atomic_load_n((volatile int32_t*)0x20007bb0u,__ATOMIC_ACQUIRE);}
