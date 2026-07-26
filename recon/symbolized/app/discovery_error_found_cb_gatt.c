#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00018894 @ 0x00018894
 * public-name: discovery_error_found_cb_gatt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_error_found_cb_gatt            <= FUN_00018894 @ 0x00018894
 * address symbols (name @ address):
 *   rodata_9a688                             @ 0x0009a688   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_00018894 @ 0x18894  (parity: 300/300 trials, PROVEN) */

extern void gatt_discover(unsigned int a, unsigned int b);

void discovery_error_found_cb_gatt(unsigned int param_1)
{
    log_message(((unsigned long)"The discovery procedure for GATT Service failed, err %d\n") /*=0x9a688*/);
    gatt_discover(param_1, 0);
}
