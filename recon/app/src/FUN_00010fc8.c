/* Reconstructed FUN_00010fc8 @ 0x10fc8 */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, ...);
extern uint64_t FUN_0000d804(uint32_t);
extern uint64_t FUN_0000d848(uint32_t);
extern void FUN_0000d8f8(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint64_t FUN_0000db4c(uint32_t, uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_0000dea8(void);
extern uintptr_t FUN_000167a8(void);
extern void FUN_00019c70(uint32_t, ...);
extern uint32_t FUN_0002e648(uint32_t);

uint32_t FUN_00010fc8(uint32_t request, uint32_t context,
                      uint32_t *buffer_slot, uint8_t *encoded_size)
{
    DEBUG_PRINT(0x000a6a28u);
    if (buffer_slot == 0 || encoded_size == 0) {
        DEBUG_PRINT(0x000a6a61u);
        return UINT32_MAX;
    }

    uint8_t *out = (uint8_t *)(uintptr_t)*buffer_slot;
    *(volatile uint8_t *)(out + 1) = 1;
    *(volatile uint8_t *)(out + 0) = 0x20;
    *(volatile uint8_t *)(out + 2) = 3;
    *(volatile uint8_t *)(out + 3) = 0x20;

    uint32_t ticks = FUN_0002e648(0);
    *(uint32_t *)(out + 4) = ticks;
    *(uint32_t *)(out + 8)  = *(volatile uint32_t *)(FUN_000167a8() + 0xfa0);
    *(uint32_t *)(out + 12) = *(volatile uint32_t *)(FUN_000167a8() + 0xfa4);
    *(uint32_t *)(out + 16) = *(volatile uint32_t *)(FUN_000167a8() + 0xfa8);
    *(uint32_t *)(out + 20) = *(volatile uint32_t *)(FUN_000167a8() + 0xf94);
    *(uint32_t *)(out + 24) = *(volatile uint32_t *)(FUN_000167a8() + 0xfb0);
    *(uint32_t *)(out + 28) = *(volatile uint32_t *)(FUN_000167a8() + 0xfb4);

    int32_t counter = *(volatile int32_t *)(FUN_000167a8() + 0xfb0);
    union { float f; uint32_t u; } converted = { .f = (float)counter };
    uint64_t scaled = FUN_0000d848(converted.u);
    scaled = FUN_0000db4c((uint32_t)scaled, (uint32_t)(scaled >> 32),
                          0, 0x412e8480u);
    uint64_t tick_value = FUN_0000d804(ticks);
    FUN_0000d8f8((uint32_t)scaled, (uint32_t)(scaled >> 32),
                 (uint32_t)tick_value, (uint32_t)(tick_value >> 32));

    uint32_t value = FUN_0000dea8();
    *(uint32_t *)(out + 32) = value;
    if (*(volatile int32_t *)0x2000230cu > 2) {
        if (*(volatile int32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x000a6a7cu, 0x000a76beu, value);
        else
            FUN_00019c70(0x000a6a7cu, 0x000a76beu, value);
    }
    *encoded_size = 0x24;
    (void)request;
    return 0;
}
