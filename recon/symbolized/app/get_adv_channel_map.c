#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008115c @ 0x0008115c
 * public-name: get_adv_channel_map
 * durable-map: recon/catalogs/function_names_app.json
 */
/* get_adv_channel_map @ 0x0008115c; raw FUN_0008115c */
#include <stdint.h>

uint8_t get_adv_channel_map(uint32_t options)
{
    uint8_t channel_map = 0x07;

    if (options & (1u << 15)) {
        channel_map &= (uint8_t)~0x01u;
    }
    if (options & (1u << 16)) {
        channel_map &= (uint8_t)~0x02u;
    }
    if (options & (1u << 17)) {
        channel_map &= (uint8_t)~0x04u;
    }
    return channel_map;
}
