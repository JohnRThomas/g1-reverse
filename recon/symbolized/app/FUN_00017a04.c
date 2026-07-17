#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017a04 @ 0x00017a04
 * public-name: FUN_00017a04
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a04 @ 0x17a04 (uncatalogued exact GPIO tail entry). */

#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t FUN_00017a04(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt(0x000889f0U, 0U, arg2, arg3);
}
