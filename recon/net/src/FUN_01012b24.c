/* net-core controller_descriptor_octet_product @ 0x01012b24.
 * Raw backmap: FUN_01012b24@0x01012b24. */
#include <stdint.h>

uint32_t FUN_01012b24(const uint8_t *descriptor)
{
    uint32_t flags = descriptor[2];
    uint32_t dimensions = (flags & 1u) +
                          ((flags >> 1) & 1u) +
                          ((flags >> 2) & 1u);

    return (dimensions * descriptor[1] * descriptor[0]) & 0xffu;
}
