/* Reconstructed FUN_00061310 @ 0x61310 */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"

extern unsigned long long FUN_000839dc(unsigned int address,
                                       unsigned int length);
extern void FUN_0004d944(unsigned int source, unsigned int level,
                         const unsigned int *arguments, unsigned int flags);
extern void FUN_00072908(unsigned int lock, unsigned int context,
                         unsigned int timeout_low,
                         unsigned int timeout_high);
extern void FUN_00072880(unsigned int lock);
extern void FUN_00065f80(unsigned int address, unsigned int value);

unsigned int FUN_00061310(unsigned int unused, unsigned int address,
                          const unsigned int *source, unsigned int length)
{
    unsigned long long range = FUN_000839dc(address, length);

    if ((unsigned int)range == 0) {
        unsigned int arguments[4] = {4, 0x000f5d81, address, length};
        FUN_0004d944(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (((address | length) & 3) != 0) {
        unsigned int arguments[4] = {4, 0x000f5dbd, address, length};
        FUN_0004d944(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (length != 0) {
        unsigned int offset = 0;
        unsigned int rounded_length = length & ~3u;
        FUN_00072908(0x2000b154, (unsigned int)(range >> 32),
                     (unsigned int)-1, (unsigned int)-1);
        while (offset != rounded_length) {
            FUN_00065f80(address + offset, source[offset / 4]);
            offset += 4;
        }
        while ((*(volatile unsigned int *)(G1_NRF_KMU_S_BASE + 0x400) & 1) == 0) {}
        FUN_00072880(0x2000b154);
    }
    return 0;
}
