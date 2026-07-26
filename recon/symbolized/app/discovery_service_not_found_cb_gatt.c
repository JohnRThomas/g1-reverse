#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00018a1c @ 0x00018a1c
 * public-name: discovery_service_not_found_cb_gatt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_service_not_found_cb_gatt      <= FUN_00018a1c @ 0x00018a1c
 * address symbols (name @ address):
 *   rodata_9a8c3                             @ 0x0009a8c3   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00018a1c @ 0x18a1c  (parity: 300/300 trials, PROVEN) */

extern void gatt_discover(unsigned int a, unsigned int b);

void discovery_service_not_found_cb_gatt(unsigned int param_1)
{
    log_message(((unsigned long)"GATT Service could not be found during the discovery\n") /*=0x9a8c3*/);
    gatt_discover(param_1, 0);
}
