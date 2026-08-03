#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027fa6 @ 0x01027fa6
 * public-name: FUN_01027fa6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_double_buffer_has_slot_value @ 0x01027fa6; raw FUN_01027fa6.
 * Retained private-controller reconstruction; exact executable extent 0x46.
 */
#include <stdint.h>

extern uint32_t FUN_01027ad2(uint8_t side);
#define sdc_double_buffer_bank_base FUN_01027ad2
#define sdc_double_buffer_has_slot_value FUN_01027fa6

uint16_t sdc_double_buffer_has_slot_value(const void *state, uint32_t raw_side)
{
    const volatile uint16_t *slot_values =
        (const volatile uint16_t *)state;
    uint8_t side = (uint8_t)raw_side;
    uint8_t bank = (uint8_t)sdc_double_buffer_bank_base(side);

    return (slot_values[0x0cu + bank] != 0u ||
            slot_values[0x0du + bank] != 0u) ? 1u : 0u;
}
