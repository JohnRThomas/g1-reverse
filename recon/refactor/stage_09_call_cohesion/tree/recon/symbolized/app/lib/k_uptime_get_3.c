#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ceda @ 0x0007ceda
 * public-name: k_uptime_get_3
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed k_uptime_get_3 @ 0x0007ceda from Zephyr kernel.h.
 * Raw backmap: FUN_0007ceda@0x0007ceda. */

#include <stdint.h>
#include "g1_lib.h"
int64_t k_uptime_get_3(void)
{
    return (int64_t)((uptime_ticks_get() * UINT64_C(1000)) >> 15);
}
