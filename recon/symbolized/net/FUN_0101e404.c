#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e404 @ 0x0101e404
 * public-name: FUN_0101e404
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101e404 @ 0x0101e404
 * Reject controller access-address patterns that alias a shifted copy of
 * themselves.  Raw address backmap: FUN_0101e404 @ 0x0101e404.
 */
#include <stdint.h>

#define controller_access_address_pattern_is_valid FUN_0101e404

uint32_t controller_access_address_pattern_is_valid(uint32_t access_address)
{
    uint32_t upper_half = access_address >> 16;
    uint32_t is_valid;
    uint32_t shifted_pattern = 0u;
    uint32_t ignored_bits = 0u;
    uint32_t pattern_source = (access_address >> 10) & 0x003fffe0u;
    uint32_t ignored_source = 0x1fu;
    uint32_t shifts_remaining = 22u;

    if (upper_half - 0x5554u < 2u) {
        is_valid = 0u;
    } else {
        is_valid = ((upper_half & 0x7fffu) != 0x2aaau);
    }

    do {
        if ((ignored_bits | ~(upper_half ^ shifted_pattern)) == UINT32_MAX) {
            return 0u;
        }

        shifted_pattern = (uint16_t)(((pattern_source & 1u) << 15) |
                                     (shifted_pattern >> 1));
        ignored_bits = (uint16_t)(((ignored_source & 1u) << 15) |
                                  (ignored_bits >> 1));
        pattern_source >>= 1;
        ignored_source >>= 1;
        shifts_remaining--;
    } while (shifts_remaining != 0u);

    return is_valid;
}
