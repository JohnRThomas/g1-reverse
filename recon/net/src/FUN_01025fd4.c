/* CPUNET two-stage controller feature gate @ 0x01025fd4.
 * Raw back-map: FUN_01025fd4=controller_feature_pair_enabled;
 * true executable extent 0x1c. */
#include <stdint.h>

extern uint32_t FUN_0100930c(uint32_t identifier);
extern uint32_t FUN_0100938c(uint32_t identifier);

uint32_t FUN_01025fd4(uint32_t type, uint32_t subtype)
{
    if (FUN_0100930c(type) != 0u && type == 0x3eu)
        return FUN_0100938c(subtype);
    return 0u;
}
