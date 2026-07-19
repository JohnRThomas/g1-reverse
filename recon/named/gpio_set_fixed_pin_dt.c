/* readable reconstruction; identity: FUN_00017a1c @ 0x00017a1c
 * public-name: gpio_set_fixed_pin_dt
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_set_fixed_pin_dt                    <= FUN_00017a1c @ 0x00017a1c
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a1c @ 0x17a1c (uncatalogued exact GPIO tail entry). */

#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t gpio_set_fixed_pin_dt(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt(0x000889e8U, 0U, arg2, arg3);
}
