#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100d2c8 @ 0x0100d2c8
 * public-name: controller_buffer_is_zero
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_buffer_is_zero                <= FUN_0100d2c8 @ 0x0100d2c8
 */
/* net-core controller_buffer_is_zero @ 0x0100d2c8.
 * Raw/address backmap: FUN_0100d2c8@0x0100d2c8. */
#include <stdbool.h>
#include <stdint.h>
#define controller_buffer_is_zero controller_buffer_is_zero

bool controller_buffer_is_zero(const void *buffer, uint32_t byte_count)
{
    const uint8_t *bytes = (const uint8_t *)buffer;
    uint32_t nonzero = 0;
    uint32_t offset;

    if (byte_count == 0) {
        return true;
    }

    if (byte_count >= 8u) {
        const uint32_t *words = (const uint32_t *)buffer;
        uint32_t word_count = byte_count >> 2;
        uint32_t limit = (uint8_t)(word_count - 1u);

        for (uint32_t index = 0; index <= limit; ++index) {
            nonzero |= words[index];
        }
        nonzero |= nonzero >> 8;
        nonzero |= nonzero >> 16;
        nonzero &= 0xffu;
        offset = byte_count & 0xfcu;
        if ((byte_count & 3u) == 0) {
            return nonzero == 0;
        }
    } else {
        offset = 0;
    }

    nonzero |= bytes[offset];
    for (uint32_t tail = 1; tail < 7; ++tail) {
        uint32_t index = (uint8_t)(offset + tail);
        if (index >= byte_count) {
            break;
        }
        nonzero |= bytes[index];
    }
    return nonzero == 0;
}
