/* net-core controller_duration_to_units @ 0x0100d538.
 * Raw/address backmap: FUN_0100d538@0x0100d538. */
#include <stdint.h>
#define controller_duration_to_units FUN_0100d538

uint32_t controller_duration_to_units(uint32_t duration, uint32_t mode)
{
    if ((mode & 0x0cu) != 0) {
        uint32_t base;
        uint32_t divisor;

        if ((mode & 4u) != 0) {
            base = 0x20eu;
            divisor = 0x10u;
        } else {
            base = 0x3d0u;
            divisor = 0x40u;
        }
        if (duration <= base) {
            return 0;
        }
        return ((duration - base) / divisor) & 0xffffu;
    }

    if (mode == 2u) {
        return duration > 0x3cu ? ((duration - 0x3cu) >> 2) & 0xffffu : 0;
    }
    return duration > 0x70u ? ((duration - 0x70u) >> 3) & 0xffffu : 0;
}
