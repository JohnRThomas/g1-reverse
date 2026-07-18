/* readable reconstruction; identity: FUN_000839dc @ 0x000839dc
 * public-name: is_regular_addr_valid
 * durable-map: recon/catalogs/function_names_app.json
 */
/* is_regular_addr_valid @ 0x000839dc; raw FUN_000839dc.
 * NCS 2.5.1 zephyr/drivers/flash/soc_flash_nrf.c. */

#include <stdint.h>
extern uint32_t nrfx_nvmc_flash_size_get(void); /*=0x000851e8*/
int is_regular_addr_valid(int32_t address, uint32_t length)
{
    uint32_t flash_size = nrfx_nvmc_flash_size_get();
    return address >= 0 && (uint32_t)address < flash_size &&
           length <= flash_size - (uint32_t)address;
}
