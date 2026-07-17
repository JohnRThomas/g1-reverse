/* readable reconstruction; identity: FUN_0103a468 @ 0x0103a468
 * public-name: net_buf_simple_tailroom
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   net_buf_simple_tailroom                  <= FUN_0103a468 @ 0x0103a468
 */
/* net-core FUN_0103a468 @ 0x0103a468 */
#include <stdint.h>

uint32_t net_buf_simple_tailroom(const uint32_t *state)
{
    uint32_t byte_span =
        (uint32_t)*(const uint16_t *)((const uint8_t *)state + 6) -
        (uint32_t)*(const uint16_t *)((const uint8_t *)state + 4);
    uint32_t reserved_span = state[0] - state[2];
    return byte_span - reserved_span;
}
