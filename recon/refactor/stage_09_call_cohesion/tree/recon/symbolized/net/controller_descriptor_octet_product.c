#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01012b24 @ 0x01012b24
 * public-name: controller_descriptor_octet_product
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_descriptor_octet_product      <= FUN_01012b24 @ 0x01012b24
 */
/* net-core controller_descriptor_octet_product @ 0x01012b24.
 * Raw backmap: FUN_01012b24@0x01012b24. */
#include <stdint.h>

uint32_t controller_descriptor_octet_product(const uint8_t *descriptor)
{
    uint32_t flags = descriptor[2];
    uint32_t dimensions = (flags & 1u) +
                          ((flags >> 1) & 1u) +
                          ((flags >> 2) & 1u);

    return (dimensions * descriptor[1] * descriptor[0]) & 0xffu;
}
