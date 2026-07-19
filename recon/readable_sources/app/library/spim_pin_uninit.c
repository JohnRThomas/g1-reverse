#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067138 @ 0x00067138
 * public-name: spim_pin_uninit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_base_get               <= FUN_00066d1c @ 0x00066d1c
 */
/* Reconstructed spim_pin_uninit @ 0x67138  (CFG-directed candidate) */
#include <stdint.h>
extern uintptr_t nrf_gpio_pin_port_base_get(uint32_t *pin);
void spim_pin_uninit(uint32_t pin, uint32_t unused, uint32_t context)
{
    (void)unused;
    (void)context;
    if (pin != UINT32_MAX) {
        uint32_t normalized = pin;
        uintptr_t gpio = nrf_gpio_pin_port_base_get(&normalized);
        volatile uint32_t *config = (volatile uint32_t *)(gpio + 0x200u + normalized * 4u);
        *config = (*config & 0xfffcf0f0u) | 2u;
    }
}
