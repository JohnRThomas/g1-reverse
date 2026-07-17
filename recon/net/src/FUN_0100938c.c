/* net-core FUN_0100938c @ 0x100938c  (CFG-directed candidate) */

#include <stdint.h>
uint32_t FUN_0100938c(uint32_t identifier)
{
    uint32_t bit = identifier - 1u;
    volatile const uint32_t *groups = (volatile const uint32_t *)0x21000008u;
    return (groups[(bit >> 5) & 7u] >> (bit & 31u)) & 1u;
}
