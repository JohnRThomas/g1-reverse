/* Reconstructed FUN_000259d4 @ 0x259d4 */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern uint64_t FUN_0008638c(uint32_t);
extern void FUN_000864c2(uint32_t);

int FUN_000259d4(void)
{
    volatile uint8_t *descriptor = (volatile uint8_t *)0x20007a48u;
    volatile uint8_t *config = (volatile uint8_t *)0x200023ccu;

    *(volatile uint32_t *)(descriptor + 8) = 0x00088a38u;
    *(volatile uint16_t *)(config + 4) = 0x53;
    *(volatile uint16_t *)(config + 8) = 0x53;
    *(volatile uint32_t *)(config + 12) = 0x1000;
    *(volatile uint32_t *)(descriptor + 16) = 0x20007a60u;
    *(volatile uint32_t *)(descriptor + 4) = 0x200023ccu;

    FUN_000864c2(0x20007a60u);
    uint64_t status = FUN_0008638c(*(volatile uint32_t *)config);
    uint32_t format = (int32_t)status == 0 ? 0x0009f3fau : 0x0009f418u;
    DEBUG_PRINT(format, (uint32_t)(status >> 32), 0x1000u, 0x20007a48u);

    status = FUN_0008638c(*(volatile uint32_t *)config);
    if ((int32_t)status == 0) {
        uint32_t base = *(volatile uint32_t *)config;
        DEBUG_PRINT(0x0009f433u, *(volatile uint32_t *)(uintptr_t)base,
                    0x1000u, 0x20007a48u);
        return 0;
    }
    DEBUG_PRINT(0x0009f487u, (uint32_t)(status >> 32),
                0x1000u, 0x20007a48u);
    return 0x20007a48;
}
