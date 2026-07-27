/* Reconstructed FUN_00012580 @ 0x12580 */
#include <stdint.h>

extern unsigned long long FUN_0000d89c(unsigned int, unsigned int);
extern uint64_t FUN_0000d8f8(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t FUN_0000ec34(void);
extern uint32_t FUN_0000e1a4(uint32_t, uint32_t, uint32_t, uint32_t);

void FUN_00012580(uint32_t result[2], uint32_t multiplicand,
                  uint32_t multiplier)
{
    uint64_t product = (uint64_t)multiplicand * multiplier;
    uint32_t high = (uint32_t)(product >> 32) +
                    multiplier * (uint32_t)((int32_t)multiplicand >> 31);
    uint64_t quotient = FUN_0000d89c((uint32_t)product, high);
    uint64_t state = FUN_0000d8f8((uint32_t)quotient,
                                  (uint32_t)(quotient >> 32),
                                  0x3a92a305u, 0x40239d01u);
    state = FUN_0000ec34();
    result[0] = FUN_0000e1a4((uint32_t)state, (uint32_t)(state >> 32),
                             1000000u, 0);
    result[1] = 1000000u;
}
