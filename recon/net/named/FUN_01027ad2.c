/* readable reconstruction; identity: FUN_01027ad2 @ 0x01027ad2
 * public-name: FUN_01027ad2
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_double_buffer_bank_base @ 0x01027ad2; raw FUN_01027ad2.
 * Retained private-controller reconstruction; exact executable extent 0x20.
 */
#include <stdint.h>

#define sdc_double_buffer_bank_base FUN_01027ad2

uint32_t sdc_double_buffer_bank_base(uint32_t raw_side)
{
    uint8_t side = (uint8_t)raw_side;
    return side == 0u ? 2u : 0u;
}
