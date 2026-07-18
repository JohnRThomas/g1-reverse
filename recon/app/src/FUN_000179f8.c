/* CPUAPP subsystem-enable helper @ 0x000179f8.
 * Raw/back-map identity: FUN_000179f8, exact extent 0x0c bytes.
 * The fixed GPIO descriptor at 0x000889f0 is P0.21. */
#include <stdint.h>

extern uint32_t FUN_0007c084(uint32_t descriptor, uint32_t value,
                             uint32_t arg2, uint32_t arg3);

uint32_t FUN_000179f8(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return FUN_0007c084(0x000889f0u, 1u, arg2, arg3);
}
