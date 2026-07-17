/* net-core FUN_01027b0c @ 0x1027b0c  (CFG-directed candidate) */

#include <stdint.h>
/* Readable role: controller_interval_half_saturating. Raw back-map: FUN_01027b0c @ 0x01027b0c. */
uint16_t FUN_01027b0c(uint32_t raw_value)
{
    uint16_t value = (uint16_t)raw_value;
    return value < 0x1feu ? (uint16_t)(value >> 1) : 0xffu;
}
