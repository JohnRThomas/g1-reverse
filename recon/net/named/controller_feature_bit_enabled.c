/* readable reconstruction; identity: FUN_0100938c @ 0x0100938c
 * public-name: controller_feature_bit_enabled
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_feature_bit_enabled           <= FUN_0100938c @ 0x0100938c
 */
/* net-core FUN_0100938c @ 0x100938c  (CFG-directed candidate) */

#include <stdint.h>
uint32_t controller_feature_bit_enabled(uint32_t identifier)
{
    uint32_t bit = identifier - 1u;
    volatile const uint32_t *groups = (volatile const uint32_t *)0x21000008u;
    return (groups[(bit >> 5) & 7u] >> (bit & 31u)) & 1u;
}
