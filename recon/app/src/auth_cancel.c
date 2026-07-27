/* Full ABI-faithful reconstruction auth_cancel @ 0x1849c. */
#include <stdint.h>

extern uintptr_t FUN_00081526(void);
extern void FUN_00018334(const void *connection, char *description);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);

void auth_cancel(uint32_t connection)
{
    char description[32];
    uintptr_t active_connection = FUN_00081526();

    FUN_00018334((const void *)active_connection, description);
    DEBUG_PRINT(0x0009a4e0u, description);

    if (*(volatile int32_t *)0x2000230cu > 0) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a4f7u, 0x0009b11au);
        else
            FUN_00019c70(0x0009a4f7u, 0x0009b11au);
    }

    FUN_00056a68(connection, 0x13u);
}
