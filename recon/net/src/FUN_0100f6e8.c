/* net-core FUN_0100f6e8 @ 0x100f6e8  (CFG-directed candidate) */
/* Role: population count of the low controller byte. Back-map: FUN_0100f6e8. */
#include <stdint.h>
uint32_t FUN_0100f6e8(uint32_t value)
{
    value = (value & 0x55u) + ((value >> 1) & 0x55u);
    value = (value & 0x33u) + ((value >> 2) & 0x33u);
    return (value & 0x0fu) + (value >> 4);
}
