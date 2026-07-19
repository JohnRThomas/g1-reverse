#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047698 @ 0x00047698
 * public-name: projector_bus_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_bus_lock                       <= FUN_00047698 @ 0x00047698
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 * address symbols (name @ address):
 *   g_projector_bus_lock                     @ 0x2000a060
 */
/* Reconstructed FUN_00047698 @ 0x47698  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void projector_bus_lock(unsigned int param_1, unsigned int param_2)
{
  k_mutex_lock(((unsigned long)&g_projector_bus_lock) /*=0x2000a060*/, param_2, param_1, param_2);
}
