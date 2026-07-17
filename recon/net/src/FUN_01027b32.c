/* net-core FUN_01027b32 @ 0x1027b32  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t FUN_01027b0c(uint16_t value);
uint32_t FUN_01027b32(uint32_t raw_value)
{
    uint16_t value = (uint16_t)raw_value;
    uint16_t base = (uint16_t)FUN_01027b0c(value);
    int32_t delta = (int32_t)(uint32_t)value - (int32_t)(uint32_t)base;
    if (delta < 0x672)
        return (uint16_t)delta;
    return 0x672u;
}
