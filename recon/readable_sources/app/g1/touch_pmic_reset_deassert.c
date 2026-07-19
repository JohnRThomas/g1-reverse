#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017a34 @ 0x00017a34
 * public-name: touch_pmic_reset_deassert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   touch_pmic_reset_deassert                <= FUN_00017a34 @ 0x00017a34
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a34 @ 0x17a34: touch_pmic_reset_deassert. */

#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t touch_pmic_reset_deassert(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt(0x000889d8U, 0U, arg2, arg3);
}
