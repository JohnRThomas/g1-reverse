/* net-core controller_count_to_duration @ 0x0100d624.
 * Raw/address backmap: FUN_0100d624@0x0100d624. */
#include <stdint.h>
#define controller_count_to_duration FUN_0100d624

uint32_t controller_count_to_duration(uint32_t count, uint32_t duration_limit)
{
    if (duration_limit > 0x1d4bu) {
        return (count * 0x4e2u) & 0xffffu;
    }
    return count * 100u;
}
