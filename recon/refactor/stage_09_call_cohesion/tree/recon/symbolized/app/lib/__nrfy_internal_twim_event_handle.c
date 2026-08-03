#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085378 @ 0x00085378
 * public-name: __nrfy_internal_twim_event_handle
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed __nrfy_internal_twim_event_handle @ 0x85378  (CFG-directed candidate) */
#include <stdint.h>
void __nrfy_internal_twim_event_handle(uintptr_t reg, uint32_t mask, uint32_t event, uint32_t *events) {
    uint32_t bit = 1u << ((event - 0x100u) >> 2);
    if ((mask & bit) != 0 && *(volatile uint32_t *)(reg + event) != 0) {
        *(volatile uint32_t *)(reg + event) = 0;
        *events |= bit;
    }
}
