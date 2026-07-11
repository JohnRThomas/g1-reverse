/* Full ABI-faithful reconstruction ancs_disconnected @ 0x18adc. */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t format, ...);
extern uint64_t FUN_000167a8(void);
extern void FUN_00018334(const void *connection, char *description);
extern void FUN_00018ab0(void);
extern void FUN_00019c70(uintptr_t format, ...);
extern void FUN_00072908(uint32_t object_low, uint32_t object_high,
                        uint32_t timeout_low, uint32_t timeout_high);
extern uintptr_t FUN_00081526(uint32_t connection);

void ancs_disconnected(uint32_t connection, uint32_t reason)
{
    char description[36];
    uintptr_t device_state = *(volatile uintptr_t *)0x20006ab8u;

    *(volatile uint8_t *)(device_state + 0x365u) = 0;
    *(volatile uint32_t *)0x20007518u = 0;

    uintptr_t active_connection = FUN_00081526(connection);
    FUN_00018334((const void *)active_connection, description);
    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a92au, 0x0009b1c8u, description, reason);
        else
            FUN_00019c70(0x0009a92au, 0x0009b1c8u, description, reason);
    }

    *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006ab8u + 0x367u) = 0;
    for (;;) {
        uint64_t device = FUN_000167a8();
        if (*(volatile uint32_t *)((uintptr_t)(uint32_t)device + 0x9b4u) == 0)
            break;

        device = FUN_000167a8();
        FUN_00072908((uint32_t)device + 0x9acu, (uint32_t)(device >> 32),
                     UINT32_MAX, UINT32_MAX);
    }

    FUN_00018ab0();
}
