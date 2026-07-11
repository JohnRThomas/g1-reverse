/* net-core FUN_0102521c @ 0x102521c */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t subsystem,
                                                   uint32_t reason);

uintptr_t FUN_0102521c(uint32_t channel)
{
    if (channel < 4)
        return UINT32_C(0x4100c1c0) + channel * 4;

    channel = (uint8_t)(channel - 4);
    if (channel < 2)
        return UINT32_C(0x410111c0) + channel * 4;

    FUN_010256dc(0x6c, 0x3cd);
}
