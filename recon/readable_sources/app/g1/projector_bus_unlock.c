#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000476a8 @ 0x000476a8
 * public-name: projector_bus_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_bus_unlock                     <= FUN_000476a8 @ 0x000476a8
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_projector_bus_lock                     @ 0x2000a060
 */
/* Reconstructed FUN_000476a8 @ 0x476a8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void k_mutex_unlock(uint32_t);
void projector_bus_unlock(void) {
    k_mutex_unlock(((unsigned long)&g_projector_bus_lock) /*=0x2000a060*/);
}
