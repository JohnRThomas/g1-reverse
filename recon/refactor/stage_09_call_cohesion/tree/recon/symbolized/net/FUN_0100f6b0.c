#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f6b0 @ 0x0100f6b0
 * public-name: FUN_0100f6b0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* controller_word_popcount @ 0x0100f6b0; raw FUN_0100f6b0.
 * Retained private-controller reconstruction; exact executable extent 0x38.
 */
#include <stdint.h>

#define controller_word_popcount FUN_0100f6b0

uint32_t controller_word_popcount(uint32_t value)
{
    uint32_t count;

    count = (value & UINT32_C(0x55555555)) +
            ((value >> 1) & UINT32_C(0x55555555));
    count = (count & UINT32_C(0x33333333)) +
            ((count >> 2) & UINT32_C(0x33333333));
    count = (count & UINT32_C(0x0f0f0f0f)) +
            ((count >> 4) & UINT32_C(0x0f0f0f0f));
    count = (count & UINT32_C(0x00ff00ff)) +
            ((count >> 8) & UINT32_C(0x00ff00ff));
    return (count + (count >> 16)) & UINT32_C(0xff);
}
