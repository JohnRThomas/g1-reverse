/* net-core controller_interval_code_to_duration @ 0x0100d600.
 * Raw/address backmap: FUN_0100d600@0x0100d600. */
#include <stdint.h>
#define controller_interval_code_to_duration FUN_0100d600

uint32_t controller_interval_code_to_duration(uint32_t interval_code)
{
    if (interval_code >= 0xd01u && interval_code <= 0xd07u) {
        return (interval_code - 0xd00u) * 1000u;
    }
    return interval_code * 0x4e2u;
}
