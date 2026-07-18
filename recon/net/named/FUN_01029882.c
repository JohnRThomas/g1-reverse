/* readable reconstruction; identity: FUN_01029882 @ 0x01029882
 * public-name: FUN_01029882
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01029882 @ 0x1029882  (CFG-directed candidate) */
/* CPUNET 0x01029882, true executable extent 0x26. Raw backmap: FUN_01029882. */
#include <stdint.h>

uint32_t FUN_01029882(uint32_t first_mode, uint32_t second_mode,
                      uint16_t *pair, uint16_t value)
{
    if ((second_mode == 8u) && (first_mode == 1u)) {
        pair[0] = value;
        pair[1] = 4u;
        return first_mode;
    }
    if ((second_mode == 4u) && (first_mode != 1u)) {
        pair[0] = value;
        pair[1] = 8u;
        return 1u;
    }
    return 0u;
}
