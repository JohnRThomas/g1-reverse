#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039ade @ 0x01039ade
 * public-name: FUN_01039ade
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Zephyr onoff process_recheck @ 0x01039ade, exact extent 0x38.
 * Raw/address backmap: FUN_01039ade@0x01039ade. */
#include <stdint.h>
#define process_recheck FUN_01039ade

enum onoff_event {
    ONOFF_EVT_NOP = 0,
    ONOFF_EVT_START = 3,
    ONOFF_EVT_STOP = 4,
    ONOFF_EVT_RESET = 5,
};

int process_recheck(const uint8_t *manager)
{
    uint32_t state = *(const uint16_t *)(manager + 0x1c) & 7u;

    if (state == 0u) {
        return *(const uint32_t *)manager ? ONOFF_EVT_START : ONOFF_EVT_NOP;
    }
    if (state == 2u) {
        return *(const uint16_t *)(manager + 0x1e) == 0u
                   ? ONOFF_EVT_STOP : ONOFF_EVT_NOP;
    }
    if (state == 1u) {
        return *(const uint32_t *)manager ? ONOFF_EVT_RESET : ONOFF_EVT_NOP;
    }
    return ONOFF_EVT_NOP;
}
