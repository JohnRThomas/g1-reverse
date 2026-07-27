/* Full ABI-faithful reconstruction pairing_failed @ 0x18444. */
#include <stdint.h>

extern uintptr_t FUN_00081526(unsigned long);
extern void FUN_00018334(const void *connection, char description[36]);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00056a68(uint32_t connection, uint32_t reason);

void pairing_failed(uint32_t connection, uint32_t error)
{
    char description[36];
    uintptr_t active_connection = FUN_00081526(connection);

    FUN_00018334((const void *)active_connection, description);
    DEBUG_PRINT(0x0009a48bu, description, error);

    if (*(volatile int *)0x2000230cu > 0) {
        if (*(volatile int *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a4afu, 0x0009b126u);
        else
            FUN_00019c70(0x0009a4afu, 0x0009b126u);
    }

    FUN_00056a68(connection, 0x13);
}
