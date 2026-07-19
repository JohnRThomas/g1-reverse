#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017a10 @ 0x00017a10
 * public-name: gpio_set_pin1_dt_wrapper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_set_pin1_dt_wrapper                 <= FUN_00017a10 @ 0x00017a10
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a10 @ 0x17a10 (uncatalogued exact GPIO tail entry). */

#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t gpio_set_pin1_dt_wrapper(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt(0x000889e8U, 1U, arg2, arg3);
}
