#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027e1c @ 0x01027e1c
 * public-name: FUN_01027e1c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_double_buffer_take_ready @ 0x01027e1c; raw FUN_01027e1c.
 * Private controller identity; true executable extent 0xb8 bytes.
 */
#include <stdint.h>
extern uint32_t FUN_01027ad2(uint32_t mode);
#define sdc_double_buffer_bank_base FUN_01027ad2
struct sdc_ready_buffer { uint32_t payload; uint16_t length; };
#define sdc_double_buffer_take_ready FUN_01027e1c
uint32_t sdc_double_buffer_take_ready(uint8_t *state,
                                      struct sdc_ready_buffer *out,
                                      uint32_t mode)
{
    uint8_t base;
    uint8_t ready;
    uint8_t other;
    if (state[2] != 0u) return 0u;
    /* The original normalizes the raw AAPCS argument before the helper call. */
    base = (uint8_t)sdc_double_buffer_bank_base((uint8_t)mode);
    if (state[0x14u + base] == 2u) {
        ready = base;
        other = (uint8_t)(base + 1u);
    } else if (state[0x15u + base] == 2u) {
        ready = (uint8_t)(base + 1u);
        other = base;
    } else return 0u;
    if (out != 0) {
        state[0x14u + other] = 0u;
        *(uint16_t *)(state + 0x18u + (uint32_t)other * 2u) = 0u;
        state[0x14u + ready] = 3u;
        out->payload = *(uint32_t *)(state + 4u + (uint32_t)ready * 4u);
        out->length = *(uint16_t *)(state + 0x18u + (uint32_t)ready * 2u);
    }
    return 1u;
}

/* Raw identity/back-map: FUN_01027e1c@0x01027e1c. */
