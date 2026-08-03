#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039dec @ 0x01039dec
 * public-name: FUN_01039dec
 * durable-map: recon/catalogs/function_names_net.json
 */
/* nRF53 rtc_ticks_to_next_event_get @ 0x01039dec, exact extent 0x5e.
 * Raw/address backmap: FUN_01039dec@0x01039dec. */
#include <stdbool.h>
#include <stdint.h>
#define rtc_ticks_to_next_event_get FUN_01039dec

bool rtc_ticks_to_next_event_get(volatile uint8_t *rtc,
                                 uint32_t selected_cc_mask,
                                 uint32_t counter,
                                 uint32_t *ticks_to_next_event)
{
    uint32_t intenset = *(volatile uint32_t *)(rtc + 0x304);
    bool result = false;

    if (intenset & 2u) {
        *ticks_to_next_event = 0x01000000u - counter;
        result = true;
    }

    for (uint32_t channel = 0; channel < 4u; ++channel) {
        if ((selected_cc_mask & (1u << channel)) &&
            (intenset & (0x10000u << channel))) {
            uint32_t ticks =
                (*(volatile uint32_t *)(rtc + 0x540 + 4u * channel) - counter)
                & 0x00ffffffu;

            if (ticks == 0u) {
                ticks = 0x01000000u;
            }
            if (!result || ticks < *ticks_to_next_event) {
                *ticks_to_next_event = ticks;
            }
            result = true;
        }
    }
    return result;
}
