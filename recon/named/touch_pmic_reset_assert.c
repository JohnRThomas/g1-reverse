/* readable reconstruction; identity: FUN_00017a28 @ 0x00017a28
 * public-name: touch_pmic_reset_assert
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   touch_pmic_reset_assert                  <= FUN_00017a28 @ 0x00017a28
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a28 @ 0x17a28: touch_pmic_reset_assert. */

#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t touch_pmic_reset_assert(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt(0x000889d8U, 1U, arg2, arg3);
}
