#include "g1_net_symbols.h"
/* net-core FUN_010243c0 @ 0x10243c0 */
#include <stdint.h>

extern uint32_t FUN_01024440(uint32_t source);
extern void FUN_01024524(uint32_t clock, uint32_t channel,
                         uint32_t *captured, uint8_t scratch[8],
                         uint8_t *quality);
extern void FUN_010256dc(unsigned module, unsigned line);

int32_t FUN_010243c0(uint32_t clock, uint32_t channel,
                     uint32_t source, uint32_t invalid,
                     uint32_t reference)
{
    uint8_t quality;
    uint8_t scratch[8];
    uint32_t captured;
    uint32_t current;
    uint32_t forward;
    uint32_t backward;
    uint32_t correction;

    if (invalid != 0) {
        FUN_010256dc(0x70, 0xc43);
        return 0;
    }

    current = FUN_01024440(source);
    FUN_01024524(clock, channel, &captured, scratch, &quality);
    forward = current - captured;
    if (forward < 0x0f424000u) {
        correction = forward;
    } else {
        backward = captured - current;
        if (backward < 0x0f424000u) {
            correction = 0u - backward;
        } else if (forward > 0x1e847fffu) {
            correction = forward + 0x1e848000u;
        } else if (backward <= 0x1e847fffu) {
            FUN_010256dc(0x70, 0xb76);
            return 0;
        } else {
            correction = 0xe17b8000u - backward;
        }
    }
    return (int32_t)((reference - 15u) - correction);
}
