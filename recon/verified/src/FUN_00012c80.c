/* Reconstructed FUN_00012c80 @ 0x12c80 */
#include <stdint.h>

extern double FUN_00012db0(uint32_t, uint32_t, uint32_t, uint32_t);
extern unsigned int FUN_000869dc(double);
extern int FUN_0000de18(uint32_t, uint32_t, uint32_t, uint32_t);
extern int FUN_0000dddc(uint32_t, uint32_t, uint32_t, uint32_t);
extern int *FUN_000807f2(void);

double FUN_00012c80(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3,
                    double argument)
{
    double result = FUN_00012db0(r0, r1, r2, r3);
    if (*(volatile int8_t *)0x200035afu != -1 && FUN_000869dc(argument)) {
        union { double d; uint64_t u; } bits = { .d = argument };
        if (FUN_0000de18((uint32_t)bits.u, (uint32_t)(bits.u >> 32),
                         0xfefa39efu, 0x40862e42u)) {
            *FUN_000807f2() = 0x22;
            result = 0.0;
        } else if (FUN_0000dddc((uint32_t)bits.u, (uint32_t)(bits.u >> 32),
                                0xd52d3051u, 0xc0874910u)) {
            *FUN_000807f2() = 0x22;
            result = 0.0;
        }
    }
    return result;
}
