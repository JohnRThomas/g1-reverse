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
        /* DEFECT REPAIR 2026-07-29 (net_test_coverage.md §12.5).
         * 0x0100d550 is `sdiv r0, r0, r2` -- SIGNED division, and the
         * guard at 0x0100d548 is `bls`, an UNSIGNED compare, so
         * `duration - base` may exceed 0x7fffffff; the shipped code
         * then truncates toward zero on a negative value and unsigned
         * division differs by one.  Measured against the shipped bytes:
         * 10 of 43 golden fixtures failed before this, 0 after. */
        return ((uint32_t)((int32_t)(duration - base) /
                           (int32_t)divisor)) & 0xffffu;
    }

    if (mode == 2u) {
        return duration > 0x3cu ? ((duration - 0x3cu) >> 2) & 0xffffu : 0;
    }
    return duration > 0x70u ? ((duration - 0x70u) >> 3) & 0xffffu : 0;
}
