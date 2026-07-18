#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065ef0 @ 0x00065ef0
 * public-name: nvmc_readonly_mode_set
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   NRF_NVMC_S                               @ 0x50039000
 */
/* NCS 2.5.1 nvmc_readonly_mode_set @ 0x00065ef0 (FUN_00065ef0). */
#include <stdint.h>

void nvmc_readonly_mode_set(void)
{
    volatile uint32_t *const nvmc = (volatile uint32_t *)NRF_NVMC_S /*=0x50039000*/;
    nvmc[0x584u / 4u] = 0u;
    nvmc[0x504u / 4u] = 0u;
}
