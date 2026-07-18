/* Reconstructed FUN_0006125c @ 0x6125c */
#include <stdint.h>

extern unsigned int FUN_000851ee(void);
extern unsigned long long FUN_000839dc(unsigned int address,
                                       unsigned int length);
extern void FUN_0004d944(unsigned int source, unsigned int level,
                         const unsigned int *arguments, unsigned int flags);
extern void FUN_00072908(unsigned int lock, unsigned int context,
                         unsigned int timeout_low,
                         unsigned int timeout_high);
extern void FUN_00072880(unsigned int lock);
extern unsigned int FUN_00065f1c(unsigned int address);

unsigned int FUN_0006125c(unsigned int unused, unsigned int address,
                          unsigned int length)
{
    unsigned int page_size = FUN_000851ee();
    unsigned long long range = FUN_000839dc(address, length);

    if ((unsigned int)range == 0) {
        unsigned int arguments[4] = {4, 0x000f5d81, address, length};
        FUN_0004d944(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if ((address % page_size) != 0 || (length % page_size) != 0) {
        unsigned int arguments[4] = {4, 0x000f5d9e, address, length};
        FUN_0004d944(0x000881b0, 0x2040, arguments, 0);
        return (unsigned int)-22;
    }
    if (page_size <= length) {
        FUN_00072908(0x2000b154, (unsigned int)(range >> 32),
                     (unsigned int)-1, (unsigned int)-1);
        page_size = FUN_000851ee();
        do {
            FUN_00065f1c(address);
            length -= page_size;
            address += page_size;
        } while (length != 0);
        FUN_00072880(0x2000b154);
    }
    return 0;
}
