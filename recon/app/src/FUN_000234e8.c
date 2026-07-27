/* Reconstructed FUN_000234e8 @ 0x234e8 */
#include <stdint.h>

extern uint64_t FUN_00086448(uint32_t, uint32_t, uint32_t, uint32_t);
extern void DEBUG_PRINT(unsigned long, ...);

int FUN_000234e8(uint32_t inherited_r0, uint32_t inherited_r1,
                 uint32_t inherited_r2, uint32_t inherited_r3)
{
    uint64_t status = FUN_00086448(0x200079a0u, 0xc9u, 0x1eu,
                                   inherited_r3);
    uint32_t format = (int32_t)status == 0 ? 0x0009e810u : 0x0009e7fdu;
    DEBUG_PRINT(format, (uint32_t)(status >> 32), 0x1eu, inherited_r3);
    (void)inherited_r0;
    (void)inherited_r1;
    (void)inherited_r2;
    return (int32_t)status;
}
