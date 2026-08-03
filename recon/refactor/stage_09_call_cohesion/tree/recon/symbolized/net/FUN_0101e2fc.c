#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e2fc @ 0x0101e2fc
 * public-name: FUN_0101e2fc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0101e2fc @ 0x0101e2fc
 * Validate and stage a four-way controller request.
 */
#include <stdint.h>

extern uint32_t FUN_0101f8cc(void);

uint32_t FUN_0101e2fc(uint8_t *owner, uint32_t selector,
                      uint8_t request_value, uint8_t request_tag)
{
    uint32_t controller_flags = FUN_0101f8cc();
    uint32_t index = (selector - 1u) & 0xffu;
    uint32_t request_bit;

    if (index > 3u) {
        return 0x11u;
    }
    request_bit = 1u << index;

    if ((controller_flags & (1u << 8)) != 0u) {
        if ((controller_flags & (1u << 11)) == 0u &&
            (request_bit & 3u) == 0u) {
            return 0x11u;
        }
    } else {
        uint32_t allowed = ((controller_flags & (1u << 11)) != 0u) ? 0xdu : 1u;
        if ((request_bit & allowed) == 0u) {
            return 0x11u;
        }
    }

    {
        uint8_t *state = *(uint8_t **)(owner + 4u);
        uint8_t gate = *(volatile uint8_t *)(state + 0x11au);
        if ((gate & 2u) == 0u) {
            return 0x1au;
        }

        {
            uint32_t state_flags = *(volatile uint32_t *)(state + 0x116u);
            uint32_t allowed = 1u;
            if ((state_flags & (1u << 8)) != 0u) {
                if ((state_flags & (1u << 11)) != 0u) {
                    goto accepted;
                }
                allowed = 3u;
            } else if ((state_flags & (1u << 11)) != 0u) {
                allowed = 0xdu;
            }
            if ((request_bit & allowed) == 0u) {
                return 0x1au;
            }
        }

accepted:
        if (*(volatile uint8_t *)(state + 0x1a9u) != 0u) {
            return 0x3au;
        }
        *(volatile uint8_t *)(state + 0x1a9u) = request_tag;
        *(volatile uint8_t *)(state + 0x1a7u) = (uint8_t)request_bit;
        *(volatile uint8_t *)(state + 0x1a8u) = request_value;
    }
    return 0u;
}
