/* Full ABI-faithful reconstruction FUN_000184f0 @ 0x184f0. */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t format, ...);
extern uintptr_t FUN_000167a8(void);
extern void FUN_000182c8(uint32_t connection);
extern void FUN_00018334(const void *connection, char *description);
extern void FUN_00019c70(uintptr_t format, ...);
extern int32_t FUN_00032ee4(void);
extern void FUN_0004c0a8(uint32_t enabled);
extern void FUN_0007c0a8(uint32_t milliseconds);
extern void FUN_0008149a(uint32_t connection, uint32_t state);
extern uint32_t FUN_000814e2(uint32_t connection);
extern uintptr_t FUN_00081526(uint32_t connection);
extern int32_t FUN_00086be4(void *destination, uintptr_t source, uint32_t length);

void FUN_000184f0(uint32_t connection, uint32_t level, int32_t error)
{
    char description[32];
    uintptr_t active_connection = FUN_00081526(connection);

    FUN_00018334((const void *)active_connection, description);
    if (error == 0) {
        if (*(volatile int32_t *)0x2000230cu > 2) {
            if (*(volatile uint32_t *)0x20007554u == 0)
                DEBUG_PRINT(0x0009a52bu, 0x0009b229u, description, level);
            else
                FUN_00019c70(0x0009a52bu, 0x0009b229u, description, level);
        }

        if (FUN_000814e2(connection) > 1u) {
            *(volatile uint32_t *)0x20006ab4u = 0;
            active_connection = FUN_00081526(connection);
            if (FUN_00032ee4() == 0) {
                uintptr_t device = FUN_000167a8();
                if (*(volatile uint8_t *)(device + 0x1070u) == 1u) {
                    device = FUN_000167a8();
                    if (FUN_00086be4((void *)(device + 0x1069u),
                                     active_connection, 7u) == 0)
                        FUN_000182c8(connection);
                }
            }
        }

        *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006ab8u + 0x367u) = 0;
        *(volatile uint32_t *)0x20006a34u = 0;
        return;
    }

    if (*(volatile int32_t *)0x2000230cu > 2) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a53fu, 0x0009b229u, description, level, error);
        else
            FUN_00019c70(0x0009a53fu, 0x0009b229u, description, level, error);
    }

    for (;;) {
        int32_t attempts = *(volatile int32_t *)0x20006a34u + 1;
        *(volatile int32_t *)0x20006a34u = attempts;
        if (attempts < 10)
            break;

        if (*(volatile int32_t *)0x2000230cu > 0) {
            if (*(volatile uint32_t *)0x20007554u == 0)
                DEBUG_PRINT(0x0009a56bu, 0x0009b229u);
            else
                FUN_00019c70(0x0009a56bu, 0x0009b229u);
        }
        FUN_0007c0a8(500u);
        FUN_0004c0a8(1u);
        DEBUG_PRINT(0x0009a53fu, 0x0009b229u, description, level, error);
    }

    FUN_0008149a(connection, 2u);
}
