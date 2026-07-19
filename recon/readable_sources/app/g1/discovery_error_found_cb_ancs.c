#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000188b0 @ 0x000188b0
 * public-name: discovery_error_found_cb_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_error_found_cb_ancs            <= FUN_000188b0 @ 0x000188b0
 *   atomic_and                               <= FUN_0007c08e @ 0x0007c08e
 * address symbols (name @ address):
 *   rodata_9a6c1                             @ 0x0009a6c1
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 */
/* Reconstructed FUN_000188b0 @ 0x188b0  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int);
extern void atomic_and(void *, unsigned int);
extern void gatt_discover(unsigned int, unsigned int);

void discovery_error_found_cb_ancs(unsigned int param_1)
{
  log_message(((unsigned long)&rodata_9a6c1) /*=0x9a6c1*/);
  atomic_and((void*)((unsigned long)&g_gatt_discovery_flags) /*=0x20006ab4*/,0xfffffffeUL);
  gatt_discover(param_1,1);
  return;
}
