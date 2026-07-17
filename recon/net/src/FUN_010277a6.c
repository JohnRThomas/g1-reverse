/* net-core FUN_010277a6 @ 0x10277a6  (CFG-directed candidate) */

#include <stdint.h>
uintptr_t FUN_010277a6(const uint16_t *entry)
{
    return (uintptr_t)entry + (uint32_t)*entry + 4u;
}
