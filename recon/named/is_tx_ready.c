/* readable reconstruction; identity: FUN_00084abe @ 0x00084abe
 * public-name: is_tx_ready
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed is_tx_ready @ 0x00084abe from configured NCS 2.5.1.
 * Raw backmap: FUN_00084abe@0x00084abe. */

#include <stdint.h>
#include <stdbool.h>
bool is_tx_ready(const uint32_t *device)
{
    const volatile uint8_t *config = (const volatile uint8_t *)(uintptr_t)device[0];
    if (*(const volatile uint32_t *)(config + 0x158u) != 0u) {
        return true;
    }
    if ((device[1] & 2u) != 0u) {
        return false;
    }
    return *(const volatile uint32_t *)(config + 0x120u) != 0u;
}
