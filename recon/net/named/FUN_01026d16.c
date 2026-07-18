/* readable reconstruction; identity: FUN_01026d16 @ 0x01026d16
 * public-name: FUN_01026d16
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01026d16 @ 0x01026d16
 * Adapt a packed pair of 16-bit fields to its controller helper.
 */
#include <stdint.h>

extern uint32_t FUN_01026912(uint32_t first, uint32_t second);

uint32_t FUN_01026d16(const uint8_t *record)
{
    uint16_t first = *(const uint16_t *)(record + 4u);
    uint16_t second = *(const uint16_t *)(record + 6u);
    return FUN_01026912(first, second);
}
