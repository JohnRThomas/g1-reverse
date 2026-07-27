/* Reconstructed FUN_0006522c @ 0x6522c.
 * Firmware checked nrfx_clock_start; raw/address back-map is preserved.
 */
#include <stdint.h>

#define CLOCK ((volatile uint32_t *)0x50005000UL)
extern void FUN_00065000(int domain);
extern void FUN_0007e2fa(unsigned long, ...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uint32_t, uint32_t);

void FUN_0006522c(unsigned domain)
{
    if (*(volatile uint8_t *)0x2000b320UL == 0u) {
        FUN_0007e2fa(0x00099cbd, 0x000f6acd, 0x000f6a4e, 0x168);
        FUN_0007e2ec(0x000f6a4e, 0x168);
    }

    switch (domain) {
    case 0: {
        uint32_t source;
        uint32_t status = CLOCK[0x418 / 4];
        if ((status & 0x10000u) != 0u) {
            source = status & 3u;
            if (source != 1u && source != 2u) {
                FUN_00065000(0);
                source = 1u;
            }
        } else if ((CLOCK[0x414 / 4] & 1u) != 0u) {
            source = CLOCK[0x41c / 4] & 3u;
            if (source == 1u || source == 2u) {
                CLOCK[0x304 / 4] = 2u;
                return;
            }
            source = 1u;
        } else {
            source = 1u;
        }
        CLOCK[0x518 / 4] = source;
        CLOCK[0x104 / 4] = 0u;
        (void)CLOCK[0x104 / 4];
        CLOCK[0x304 / 4] = 2u;
        CLOCK[0x008 / 4] = 1u;
        return;
    }
    case 1:
        CLOCK[0x100 / 4] = 0u;
        (void)CLOCK[0x100 / 4];
        CLOCK[0x304 / 4] = 1u;
        CLOCK[0x000 / 4] = 1u;
        return;
    case 2:
        CLOCK[0x124 / 4] = 0u;
        (void)CLOCK[0x124 / 4];
        CLOCK[0x304 / 4] = 0x200u;
        CLOCK[0x020 / 4] = 1u;
        return;
    case 3:
        CLOCK[0x120 / 4] = 0u;
        (void)CLOCK[0x120 / 4];
        CLOCK[0x304 / 4] = 0x100u;
        CLOCK[0x018 / 4] = 1u;
        return;
    default:
        FUN_0007e2fa(0x00099cbd, 0x000f7a30, 0x000f6a4e, 0x1a6);
        FUN_0007e2ec(0x000f6a4e, 0x1a6);
    }
}
