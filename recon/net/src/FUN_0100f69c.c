/* net-core FUN_0100f69c @ 0x100f69c  (CFG-directed candidate) */

#include <stdint.h>

int32_t FUN_0100f69c(int32_t drift, int32_t limit)
{
    if (drift < 0) {
        int32_t lower = (int32_t)(0U - (uint32_t)limit);
        if (drift >= lower)
            return drift;
        return (int16_t)lower;
    }
    if (drift < limit)
        return drift;
    return (int16_t)limit;
}
